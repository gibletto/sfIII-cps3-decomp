/*
 * EFF24.C  Effect 24: part of the breakable stage object
 *
 * effect_24_init makes one work for its
 * master (effect 23) at (0x2D8, 48). effect_24_move shows pattern 23 until eff_hit_flag[8] is
 * set, then pattern 24 (straight away if the flag is already set when it starts).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "EFF24.h"
#include "eff05.h"

/* routine_no[0] */
#define R0_INIT         0       /* whole or already broken pattern */
#define R0_STAND        1       /* animate until the object is hit */
#define R0_BROKEN       2       /* animate the broken pattern */



/* Animate the part of the breakable object. */
void effect_24_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        if (eff_hit_flag[8]) {
            set_char_move_init(&ewk->wu, 0, 24);
            ewk->wu.routine_no[0] = R0_BROKEN;
            break;
        }
        set_char_move_init(&ewk->wu, 0, 23);
        break;
    case R0_STAND:
        if (!EXE_flag && !Game_pause) {
            if (eff_hit_flag[8]) {
                ewk->wu.routine_no[0]++;
                set_char_move_init(&ewk->wu, 0, 24);
            } else {
                char_move(&ewk->wu);
            }
        }
        disp_pos_trans_entry_r(ewk);
        break;
    case R0_BROKEN:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
        }
        disp_pos_trans_entry_r(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* Create one part for the master. */
s32 effect_24_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->my_master = (u32*)oya;
    ewk->wu.be_flag = 1;
    ewk->wu.id = 24;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2055;
    ewk->wu.xyz[0].disp.pos = ewk->wu.position_x = 0x2D8;
    ewk->wu.xyz[1].disp.pos = ewk->wu.position_y = 48;
    ewk->wu.position_z = ewk->wu.my_priority = 91;
    ewk->wu.char_table[0] = stg03_char_table;
    return 0;
}
