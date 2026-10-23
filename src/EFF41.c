/*
 * EFF41.C  Effect 41: super art sign
 *
 * effect_41_init creates the sign beside its player outside test mode. It plays the
 * sa_sign_data animation, flashes the super art gauge and marks the gauge as used
 * on the animation's cue. Each sa_sign_data row has four entries.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "effect_2.h"
#include "EFF41.h"
#include "SYS_sub.h"
#include "EFF42.h"



void effect_41_move(WORK_Other* ewk) {
    PLW* mwk = (PLW*)ewk->my_master;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2020;
        set_char_move_init(&ewk->wu, 0, sa_sign_data[ewk->wu.type][2]);
        /* fall through */
    case 1:
        if (ewk->wu.dead_f == 1 || mwk->wu.routine_no[1] != 4) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            if (ewk->wu.hit_stop) {
                ewk->wu.hit_stop--;
            } else {
                char_move(&ewk->wu);
            }
        }
        if (ewk->wu.cg_type == 0xFF) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
            mwk->sa->saeff_ok = -1;
            break;
        }
        ewk->wu.position_x = mwk->wu.position_x;
        if (mwk->wu.rl_flag) {
            ewk->wu.position_x -= sa_sign_data[ewk->wu.type][0];
        } else {
            ewk->wu.position_x += sa_sign_data[ewk->wu.type][0];
        }
        ewk->wu.position_y = mwk->wu.position_y + sa_sign_data[ewk->wu.type][1];
        ewk->wu.position_z = mwk->wu.position_z - 4;
        sort_push_request(&ewk->wu);
        break;
    case 2:
    default:
        erase_my_shell_ix((WORK*)ewk->my_master, ewk->wu.myself);
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_41_init(PLW* wk, u8 data) {
    WORK_Other* ewk;
    s16 ix;
    if (!test_flag) {
        if ((ix = pull_effect_work(3)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        write_my_shell_ix(&wk->wu, ix);
        ewk->wu.be_flag = 1;
        ewk->wu.type = data;
        ewk->wu.id = 41;
        ewk->wu.work_id = 16;
        ewk->wu.my_family = wk->wu.my_family;
        ewk->wu.cgromtype = 1;
        ewk->my_master = (u32*)wk;
        ewk->master_work_id = wk->wu.work_id;
        ewk->master_id = wk->wu.id;
        *ewk->wu.char_table = plef_char_table;
        return 0;
    }
}



