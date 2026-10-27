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



const s16* scr_obj_data88[1][4] = {
    { scr_obj_data88_0, scr_obj_data88_0, scr_obj_data88_0, scr_obj_data88_0 },
};
/* Stored after scr_obj_data88. Nothing in the program refers to it by name or address; if it is read,
   it is through an index past the end of scr_obj_data88. */
const s16* scr_obj_data88_tail[1][4] = {
    { &scr_obj_data88_0[9], &scr_obj_data88_0[9], &scr_obj_data88_0[45], &scr_obj_data88_0[72] },
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
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



s32 effect_88_init(s16 type) {
    s16 n;
    s16 i;
    s16 s;
    const s16* t;
    WORK_Other* o;
    n = eff88_loop_tbl[type][bg_w.compel_flag];
    if (n != 0) {
        t = scr_obj_data88[type][bg_w.compel_flag];
        for (i = 0; i < n; i++) {
            if ((s = pull_effect_work(4)) == -1) {
                return -1;
            }
            o = (WORK_Other*)frw[s];
            o->wu.be_flag = 1;
            o->wu.id = 88;
            o->wu.work_id = 16;
            o->wu.cgromtype = 1;
            o->wu.rl_flag = 0;
            o->wu.my_col_mode = 0x4200;
            o->wu.dead_f = *t++;
            o->wu.my_family = *t++;
            o->wu.my_col_code = *t++;
            o->wu.xyz[0].disp.pos = *t++;
            o->wu.xyz[1].disp.pos = *t++;
            o->wu.my_priority = o->wu.position_z = *t++;
            o->wu.char_index = *t++;
            o->wu.hit_stop = *t++;
            o->wu.sync_suzi = *t++;
            o->wu.char_table[0] = char_add[bg_w.stage][bg_w.area];
            suzi_offset_set(&o->wu);
        }
        return 0;
    }
}

/* Animated text-layer panel: steps through its attribute script, repainting
   the panel each step.  It freezes (and is removed) while a screen wipe or a
   break-in is running, unless it is type 6. */
