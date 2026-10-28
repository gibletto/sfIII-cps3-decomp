/*
 * EFF45.C  Effect 45: a background object drifting across stage 14 (bg140)
 *
 * effect_45_init (from bg140) creates one object at x -4, y 80. effect_45_move plays its
 * animation and moves it left half a dot a frame; every 33 frames it resets its X
 * and steps the animation on (char_move_z).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "ta_sub.h"
#include "bg_sub_5.h"
#include "EFF45.h"

/* routine_no[0] */
#define R0_INIT         0       /* show and start the animation */
#define R0_MOVE         1       /* drift left and animate */
#define R0_KILL         2       /* put the work back */

void effect_45_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.old_pos[0] = 0;
        set_char_move_init(&ewk->wu, 0, 8);
        break;
    case R0_MOVE:
        if (!EXE_flag && !Game_pause) {
            ewk->wu.xyz[0].cal -= 0x8000;
            ewk->wu.old_pos[0]++;
            if (ewk->wu.old_pos[0] > 32) {
                ewk->wu.old_pos[0] = 0;
                ewk->wu.xyz[0].cal = -4;
                char_move_z(&ewk->wu);
            }
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos;
        }
        disp_pos_trans_entry_s(ewk);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_45_init(s16 type) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 45;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 1;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = -4;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 80;
    ewk->wu.position_z = ewk->wu.my_priority = 100;
    ewk->wu.sync_suzi = 1;
    ewk->wu.char_table[0] = eff45_char_table;
    suzi_offset_set(&ewk->wu);
    return 0;
}
