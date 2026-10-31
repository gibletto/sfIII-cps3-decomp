/*
 * EFFG9.C  Effect G9: single trail particle
 *
 * effect_G9_init is called by the G6 emitter (EFFG6.C) and copies its pattern, facing, colour,
 * speed and position. effect_G9_move scatters the particle by a random offset from g9_pos_hos
 * (which also chooses whether it is drawn in front of or behind the characters), plays its
 * pattern while drifting at the copied speed and frees itself when the pattern ends. It is drawn
 * through the list-8 sort queue and stands still while EXE_flag or Game_pause is set.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "PLS02.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFG9.h"

/* routine_no[0] */
#define R0_INIT         0       /* scatter and start the pattern */
#define R0_MOVE         1       /* drift until the pattern ends */
#define R0_KILL         2       /* put the work back */



void effect_G9_move(WORK_Other* ewk) {
    s16 rnd_ix;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = ewk->wu.type;
        ewk->wu.xyz[0].disp.pos += g9_pos_hos[random_16_com()];
        rnd_ix = random_16_com();
        ewk->wu.xyz[1].disp.pos += g9_pos_hos[rnd_ix];
        if (g9_pos_hos[rnd_ix] > 1) {
            ewk->wu.position_z = 67;
        } else {
            ewk->wu.position_z = 33;
        }
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if ((EXE_flag == 0) && (Game_pause == 0)) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 0xFF) {
                ewk->wu.disp_flag = 0;
                ewk->wu.routine_no[0]++;
                break;
            }
            add_mvxy_speed(&ewk->wu);
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos;
        sort_push_request8(&ewk->wu);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_G9_init(WORK* wk) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.type = wk->disp_flag;
    ewk->wu.id = 169;
    ewk->wu.work_id = 0x10;
    ewk->wu.rl_flag = wk->rl_flag;
    ewk->wu.char_index = wk->direction;
    ewk->wu.my_family = wk->my_family;
    ewk->wu.cgromtype = wk->cgromtype;
    ewk->wu.my_col_mode = wk->my_col_mode;
    ewk->wu.my_col_code = wk->my_col_code;
    ewk->wu.mvxy.a[0].sp = wk->mvxy.a[0].sp;
    ewk->wu.mvxy.a[1].sp = wk->mvxy.a[1].sp;
    ewk->wu.blink_timing = wk->blink_timing;
    ewk->wu.xyz[0].disp.pos = wk->xyz[0].disp.pos;
    ewk->wu.xyz[1].disp.pos = wk->xyz[1].disp.pos;
    ewk->wu.char_table[0] = plef_char_table;
    return 0;
}
