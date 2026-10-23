/*
 * EFF21.C  Effect 21: breakable stage parts
 *
 * effect_21_init makes three works
 * for its master (effect 23) from eff21_data_adrs_0 (pattern, X, Y, priority, flip) and
 * eff21_sp_tbl (speed and acceleration). effect_21_move waits on its pattern until
 * eff_hit_flag[8] is set, plays the next pattern, then flies off with add_x_sub/add_y_sub
 * until it leaves the screen.
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
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFF21.h"

extern const u32 eff21_char_table[];   /* provisional name */



/* Animate the breakable parts. */
void effect_21_move(WORK_Other* ewk) {
    if (compel_dead_check(ewk) != 0) {
        ewk->wu.routine_no[0] = 99;
    }
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.dead_f = 1;
        if (eff_hit_flag[8]) {
            ewk->wu.routine_no[0] = 99;
            break;
        }
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case 1:
        if (!EXE_flag && !Game_pause) {
            if (eff_hit_flag[8]) {
                ewk->wu.routine_no[0]++;
                set_char_move_init(&ewk->wu, 0, ewk->wu.char_index + 1);
            } else {
                char_move(&ewk->wu);
            }
        }
        sort_push_request4(&ewk->wu);
        break;
    case 2:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
            if (ewk->wu.xyz[0].disp.pos < 0x80 || ewk->wu.xyz[0].disp.pos > 0x380 || ewk->wu.xyz[1].disp.pos > 0x200) {
                ewk->wu.routine_no[0]++;
            }
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        }
        sort_push_request4(&ewk->wu);
        break;
    case 3:
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* Create three parts for the master. */
s32 effect_21_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data_ptr = eff21_data_adrs_0;
    const s32* sp_ptr = eff21_sp_tbl[0];
    for (i = 0; i < 3; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->my_master = (u32*)oya;
        ewk->wu.be_flag = 1;
        ewk->wu.id = 21;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.type = i;
        ewk->wu.my_family = 2;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2055;
        ewk->wu.char_index = *data_ptr++;
        ewk->wu.xyz[0].disp.pos = ewk->wu.position_x = *data_ptr++;
        ewk->wu.xyz[1].disp.pos = ewk->wu.position_y = *data_ptr++;
        ewk->wu.position_z = ewk->wu.my_priority = *data_ptr++;
        ewk->wu.rl_flag = *data_ptr++;
        ewk->wu.mvxy.a[0].sp = *sp_ptr++;
        ewk->wu.mvxy.a[1].sp = *sp_ptr++;
        ewk->wu.mvxy.d[0].sp = *sp_ptr++;
        ewk->wu.mvxy.d[1].sp = *sp_ptr++;
        ewk->wu.char_table[0] = eff21_char_table;
    }
    return 0;
}
