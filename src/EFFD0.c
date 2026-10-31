/*
 * EFFD0.C  Effect D0: thrown object that bounces along the floor
 *
 * effect_D0_move plays the object's start pattern, then switches to pattern 15, moves it 96 dots
 * up and 22 dots forward, and flies it through a series of arcs whose timers and speeds come from
 * effd0_conter / effd0_data_tbl (d0_speed_set, mirrored for facing). When it falls below the
 * floor it plays its landing pattern 16 and rests. effect_D0_init creates it at a player's
 * position with a palette chosen by side (etc_char_table pattern 14).
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
#include "EFFD0.h"
#include "CALDIR.h"
#include "EFFD1.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the first pattern */
#define R0_THROW        1       /* play it, then take off */
#define R0_BOUNCE       2       /* bounce along the floor */
#define R0_LAND         3       /* play the landing pattern */
#define R0_REST         4       /* rest on the floor */



void effect_D0_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.old_rno[1] = 0;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R0_THROW:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[0]++;
            set_char_move_init(&ewk->wu, 0, 15);
            d0_speed_set(&ewk->wu, ewk->wu.old_rno[1]);
            ewk->wu.xyz[1].disp.pos += 96;
            if (ewk->wu.rl_flag) {
                ewk->wu.xyz[0].disp.pos += 22;
            } else {
                ewk->wu.xyz[0].disp.pos -= 22;
            }
        }
        pl_eff_trans_entry(ewk);
        break;
    case R0_BOUNCE:
        ewk->wu.old_rno[0]--;
        if (ewk->wu.old_rno[0] < 0) {
            d0_speed_set(&ewk->wu, ewk->wu.old_rno[1]);
        } else {
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
        }
        if (ewk->wu.xyz[1].disp.pos < 0) {
            ewk->wu.routine_no[0]++;
            set_char_move_init(&ewk->wu, 0, 16);
        }
        pl_eff_trans_entry(ewk);
        break;
    case R0_LAND:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[0]++;
        }
        /* fall through */
    case R0_REST:
        pl_eff_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



void d0_speed_set(WORK* ewk, s16 num) {
    ewk->old_rno[0] = effd0_conter[num];
    ewk->old_rno[1]++;
    if (ewk->rl_flag) {
        ewk->mvxy.a[0].sp = -effd0_data_tbl[num][0];
        ewk->mvxy.d[0].sp = -effd0_data_tbl[num][1];
    } else {
        ewk->mvxy.a[0].sp = effd0_data_tbl[num][0];
        ewk->mvxy.d[0].sp = effd0_data_tbl[num][1];
    }
    ewk->mvxy.a[1].sp = effd0_data_tbl[num][2];
    ewk->mvxy.d[1].sp = effd0_data_tbl[num][3];
}



s32 effect_D0_init(PLW* oya) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 130;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.disp_flag = 0;
    ewk->my_master = (u32*)oya;
    ewk->wu.my_family = 2;
    ewk->wu.char_index = 14;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_priority = ewk->wu.position_z = oya->wu.my_priority + 1;
    ewk->wu.sync_suzi = 1;
    ewk->master_id = oya->wu.id;
    ewk->wu.xyz[0].cal = oya->wu.xyz[0].cal;
    ewk->wu.xyz[1].cal = oya->wu.xyz[1].cal;
    ewk->wu.rl_flag = oya->wu.rl_flag;
    ewk->wu.char_table[0] = etc_char_table;
    if (oya->wu.id) {
        ewk->wu.my_col_code = 22;
    } else {
        ewk->wu.my_col_code = 6;
    }
}



