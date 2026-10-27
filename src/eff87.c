/*
 * EFF87.C  Effect 87: stage background object
 *
 * effect_87: a stage background object spawned from ROM records for the stage type and compel
 * flag; it animates while not paused and hides on compel_dead_check.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sc_trans.h"
#include "fifo.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "eff87.h"
#include "cps3.h"

/* routine_no[0] */
#define R0_INIT         0       /* show and start the pattern */
#define R0_MOVE         1       /* animate until the stage retires it */
#define R0_KILL         2       /* (default) put the work back */



extern const s16 scr_obj_data87_0[];

/* 02006D8C */
const s16* scr_obj_data87[1][4] = {
    { scr_obj_data87_0, scr_obj_data87_0, scr_obj_data87_0, scr_obj_data87_0 },
};
/* Stored after scr_obj_data87. Nothing in the program refers to it by name or address; if it is read,
   it is through an index past the end of scr_obj_data87. */
const s16* scr_obj_data87_tail[4][4] = {
    { &scr_obj_data87_0[9], &scr_obj_data87_0[10], &scr_obj_data87_0[19], &scr_obj_data87_0[28] },
    { &scr_obj_data87_0[55], &scr_obj_data87_0[55], &scr_obj_data87_0[55], &scr_obj_data87_0[55] },
    { &scr_obj_data87_0[64], &scr_obj_data87_0[64], &scr_obj_data87_0[64], &scr_obj_data87_0[64] },
    { &scr_obj_data87_0[73], &scr_obj_data87_0[73], &scr_obj_data87_0[73], &scr_obj_data87_0[73] },
};


void effect_87_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R0_MOVE:
        if (compel_dead_check(ewk)) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (!EXE_flag && !Game_pause && ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        disp_pos_trans_entry_s(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



/* char_add by stage and area */
s32 effect_87_init(s16 type) {
    WORK_Other* ewk;
    s16 ix;
    s16 lp_cnt = eff87_loop_tbl[type][bg_w.compel_flag];
    s16 i;
    const s16* data_ptr;
    if (!lp_cnt) {
        return;
    }
    data_ptr = scr_obj_data87[type][bg_w.compel_flag];
    for (i = 0; i < lp_cnt; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 87;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.type = type;
        ewk->wu.dead_f = *data_ptr++;
        ewk->wu.my_family = *data_ptr++;
        ewk->wu.my_col_code = *data_ptr++;
        ewk->wu.xyz[0].disp.pos = *data_ptr++;
        ewk->wu.xyz[1].disp.pos = *data_ptr++;
        ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
        ewk->wu.char_index = *data_ptr++;
        ewk->wu.hit_stop = *data_ptr++;
        ewk->wu.sync_suzi = *data_ptr++;
        ewk->wu.char_table[0] = char_add[bg_w.stage][bg_w.area];
        suzi_offset_set(&ewk->wu);
    }
    return 0;
}



