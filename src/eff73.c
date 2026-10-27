/*
 * EFF73.C  Effect 73: a stage object that follows its parent's state
 *
 * effect_73_init (bg stage code) places one brz_char_table object at (0x1ED, 81) under the work that
 * creates it. effect_73_move follows the parent's routine_no[0]: state 0 shows pattern 17, state 1
 * pattern 18 (once pattern 18 reaches cg_type 2 it stops); it is freed with the stage.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "bg_sub_5.h"
#include "eff73.h"

/* routine_no[0]: copy of the parent's state */
#define R0_IDLE         0       /* parent idle: pattern 17 */
#define R0_REACT        1       /* parent reacting: pattern 18 */

/* routine_no[1], eff73_0000 */
#define R1_INIT         0       /* start the animation */
#define R1_PLAY         1       /* play it */

void eff73_0000(WORK_Other* ewk);
void eff73_1000(WORK_Other* ewk);



void effect_73_move(WORK_Other* ewk) {
    WORK_Other* mwk;
    if (compel_dead_check(ewk)) {
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
    mwk = (WORK_Other*)ewk->my_master;
    if (mwk->wu.routine_no[0] != ewk->wu.routine_no[0]) {
        ewk->wu.routine_no[0] = mwk->wu.routine_no[0];
        ewk->wu.routine_no[1] = R1_INIT;
    }
    if (!EXE_flag && !Game_pause) {
        switch (ewk->wu.routine_no[0]) {
        case R0_IDLE:
            eff73_0000(ewk);
            break;
        case R0_REACT:
            eff73_1000(ewk);
            break;
        }
    }
    if (range_x_check(&ewk->wu)) {
        suzi_sync_pos_set(ewk);
        sort_push_request4(&ewk->wu);
    }
}



/* provisional name */
void eff73_0000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 17);
        break;
    case R1_PLAY:
        char_move(&ewk->wu);
        break;
    }
}



/* provisional name */
void eff73_1000(WORK_Other* ewk) {
    if (ewk->wu.cg_type == 2) {
        return;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        set_char_move_init(&ewk->wu, 0, 18);
        break;
    case R1_PLAY:
        char_move(&ewk->wu);
        break;
    }
}



s32 effect_73_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 73;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->my_master = (u32*)oya;
    ewk->wu.dead_f = 1;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 0x2058;
    ewk->wu.my_priority = 75;
    ewk->wu.position_z = 75;
    ewk->wu.sync_suzi = 0;
    *ewk->wu.char_table = brz_char_table;
    ewk->wu.xyz[0].disp.pos = 0x1ED;
    ewk->wu.xyz[1].disp.pos = 81;
    suzi_offset_set(&ewk->wu);
    return 0;
}
