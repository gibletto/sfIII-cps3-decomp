/*
 * EFF88.C  Effect 88: stage background object
 *
 * effect_88: a stage background object spawned from ROM records for the stage type and compel
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
#include "eff88.h"
#include "cps3.h"

/* routine_no[0] */
#define R0_INIT         0       /* show and start the pattern */
#define R0_MOVE         1       /* animate until the stage retires it */
#define R0_KILL         2       /* (default) put the work back */



const s16* scr_obj_data88[5][4] = {
    { scr_obj_data88_0, scr_obj_data88_0, scr_obj_data88_0, scr_obj_data88_0 },
    { scr_obj_data88_1_0, scr_obj_data88_1_0, scr_obj_data88_1_2, scr_obj_data88_1_3 },
    { scr_obj_data88_2_0, scr_obj_data88_2_1, scr_obj_data88_2_2, scr_obj_data88_2_3 },
    { scr_obj_data88_3_0, scr_obj_data88_3_0, scr_obj_data88_3_2, scr_obj_data88_3_2 },
    { scr_obj_data88_4_0, scr_obj_data88_4_0, scr_obj_data88_4_0, scr_obj_data88_4_0 },
};


void effect_88_move(WORK_Other* ewk) {
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
        disp_pos_trans_entry_rs(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_88_init(s16 type) {
    s16 n;
    s16 i;
    s16 ix;
    const s16* data;
    WORK_Other* ewk;
    n = eff88_loop_tbl[type][bg_w.compel_flag];
    if (n != 0) {
        data = scr_obj_data88[type][bg_w.compel_flag];
        for (i = 0; i < n; i++) {
            if ((ix = pull_effect_work(4)) == -1) {
                return -1;
            }
            ewk = (WORK_Other*)frw[ix];
            ewk->wu.be_flag = 1;
            ewk->wu.id = 88;
            ewk->wu.work_id = 16;
            ewk->wu.cgromtype = 1;
            ewk->wu.rl_flag = 0;
            ewk->wu.my_col_mode = 0x4200;
            ewk->wu.dead_f = *data++;
            ewk->wu.my_family = *data++;
            ewk->wu.my_col_code = *data++;
            ewk->wu.xyz[0].disp.pos = *data++;
            ewk->wu.xyz[1].disp.pos = *data++;
            ewk->wu.my_priority = ewk->wu.position_z = *data++;
            ewk->wu.char_index = *data++;
            ewk->wu.hit_stop = *data++;
            ewk->wu.sync_suzi = *data++;
            ewk->wu.char_table[0] = char_add[bg_w.stage][bg_w.area];
            suzi_offset_set(&ewk->wu);
        }
        return 0;
    }
}

/* Animated text-layer panel: steps through its attribute script, repainting
   the panel each step.  It freezes (and is removed) while a screen wipe or a
   break-in is running, unless it is type 6. */
