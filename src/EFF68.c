/*
 * EFF68.C  Effect 68: a stage object that reacts to a nearby player
 *
 * effect_68_init (called from bgst070) places the object at 0x2A0,47 with the stage's character
 * table from char_add. effect_68_move runs eff68_jp while it waits: eff68_0000 starts the waiting
 * animation, eff68_0001 plays it and, on animation frame type 2, switches to routine 1 when
 * either player is within 32 pixels of it. Routine 1 (eff68_0002) plays the reaction animation
 * and goes back to waiting when it ends.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLS02.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFF68.h"

/* routine_no[0] */
#define R0_IDLE         0       /* idle until a player comes near */
#define R0_REACT        1       /* play the reaction */
#define R0_KILL         99      /* (default) put the work back */

/* routine_no[1] */
#define R1_INIT         0       /* start the animation */
#define R1_PLAY         1       /* play it */

extern void (*eff68_jp[2])(WORK_Other*);


void effect_68_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_IDLE:
        if (compel_dead_check(ewk)) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
        if (!EXE_flag && !Game_pause) {
            eff68_jp[ewk->wu.routine_no[1]](ewk);
        }
        disp_pos_trans_entry_rs(ewk);
        break;
    case R0_REACT:
        if (compel_dead_check(ewk)) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
        if (!EXE_flag && !Game_pause) {
            eff68_0002(ewk);
        }
        disp_pos_trans_entry_s(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

void (*eff68_jp[2])(WORK_Other*) = { eff68_0000, eff68_0001 };

/* provisional name */
void eff68_0000(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;
    ewk->wu.disp_flag = 1;
    ewk->wu.step_xy_table = (s16*)eff64_stepxy_table;
    set_char_move_init(&ewk->wu, 0, 17);
}

/* provisional name */
void eff68_0001(WORK_Other* ewk) {
    char_move(&ewk->wu);
    if (ewk->wu.cg_type == 2) {
        if (range_abs_check(plw[0].wu.position_x, ewk->wu.position_x, 32) || range_abs_check(plw[1].wu.position_x, ewk->wu.position_x, 32)) {
            ewk->wu.routine_no[0] = R0_REACT;
            ewk->wu.routine_no[1] = R1_INIT;
        }
    }
}

/* provisional name */
void eff68_0002(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 18);
        break;
    case R1_PLAY:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[0] = R0_IDLE;
            ewk->wu.routine_no[1] = R1_INIT;
        }
        suzi_sync_pos_set(ewk);
        sort_push_request4(&ewk->wu);
        break;
    }
}

s32 effect_68_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 68;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.dead_f = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 0x2058;
    ewk->wu.xyz[0].disp.pos = 0xA0;
    ewk->wu.xyz[1].disp.pos = 47;
    ewk->wu.my_priority = ewk->wu.position_z = 75;
    ewk->wu.char_index = 17;
    ewk->wu.hit_stop = 1;
    ewk->wu.sync_suzi = 1;
    ewk->wu.char_table[0] = char_add[bg_w.stage][bg_w.area];
    suzi_offset_set(&ewk->wu);
    return 0;
}
