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
extern const s16 scr_obj_data87_1_0[];
extern const s16 scr_obj_data87_1_1[];
extern const s16 scr_obj_data87_1_2[];
extern const s16 scr_obj_data87_1_3[];
extern const s16 scr_obj_data87_2_0[];
extern const s16 scr_obj_data87_3_0[];
extern const s16 scr_obj_data87_4_0[];

/* 02006CC8 */
const s16* scr_obj_data87[5][4] = {
    { scr_obj_data87_0, scr_obj_data87_0, scr_obj_data87_0, scr_obj_data87_0 },
    { scr_obj_data87_1_0, scr_obj_data87_1_1, scr_obj_data87_1_2, scr_obj_data87_1_3 },
    { scr_obj_data87_2_0, scr_obj_data87_2_0, scr_obj_data87_2_0, scr_obj_data87_2_0 },
    { scr_obj_data87_3_0, scr_obj_data87_3_0, scr_obj_data87_3_0, scr_obj_data87_3_0 },
    { scr_obj_data87_4_0, scr_obj_data87_4_0, scr_obj_data87_4_0, scr_obj_data87_4_0 },
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
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



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



