/*
 * EFF28.C  Effect 28: stage object that follows its master
 *
 * effect_26_init creates it with the stage object as master; it plays patterns 0 and 1 (5 when
 * eff_hit_flag[1] is set), and eff28_master_check switches it to pattern 4 once the master has gone
 * past routine 1.
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
#include "PLS02.h"
#include "aboutspr.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "eff28.h"

/* routine_no[0] */
#define R0_INIT         0       /* show and pick the first pattern */
#define R0_START        1       /* play the opening pattern */
#define R0_MOVE         2       /* loop while the master stays */
#define R0_LEAVE        5       /* master gone: play the leaving pattern */
#define R0_STAY         6       /* loop the last pattern */



extern const u32 eff28_char_table[];

static s32 eff28_master_check(WORK_Other* ewk);



void effect_28_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        if (eff_hit_flag[1]) {
            set_char_move_init(&ewk->wu, 0, 5);
            ewk->wu.routine_no[0] = R0_STAY;
            break;
        }
        set_char_move_init(&ewk->wu, 0, 0);
        break;
    case R0_START:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                set_char_move_init(&ewk->wu, 0, 1);
                ewk->wu.routine_no[0]++;
            }
        }
        break;
    case R0_MOVE:
        if (!EXE_flag && !Game_pause) {
            if (!eff28_master_check(ewk)) {
                char_move(&ewk->wu);
            }
        }
        break;
    case 3:
        if (!EXE_flag && !Game_pause) {
            if (!eff28_master_check(ewk)) {
                char_move(&ewk->wu);
                if (ewk->wu.cg_type) {
                    ewk->wu.routine_no[0] = R0_MOVE;
                    set_char_move_init(&ewk->wu, 0, 1);
                }
            }
        }
        break;
    case 4:
        if (!EXE_flag && !Game_pause) {
            if (!eff28_master_check(ewk)) {
                char_move(&ewk->wu);
                if (ewk->wu.cg_type) {
                    ewk->wu.routine_no[0] = R0_MOVE;
                    set_char_move_init(&ewk->wu, 0, 1);
                }
            }
        }
        break;
    case R0_LEAVE:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                ewk->wu.routine_no[0]++;
                set_char_move_init(&ewk->wu, 0, 5);
            }
        }
        break;
    case R0_STAY:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
    disp_pos_trans_entry_r(ewk);
}



static s32 eff28_master_check(WORK_Other* ewk) {
    WORK_Other* mwk = (WORK_Other*)ewk->my_master;
    if (mwk->wu.routine_no[1] > 1) {
        ewk->wu.routine_no[0] = R0_LEAVE;
        set_char_move_init(&ewk->wu, 0, 4);
        return 1;
    }
    return 0;
}



s32 effect_28_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 28;
    ewk->wu.work_id = 16;
    ewk->my_master = (u32*)oya;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 80;
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 0x1F0;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 64;
    ewk->wu.position_z = ewk->wu.my_priority = 83;
    ewk->wu.char_table[0] = eff28_char_table;
    return 0;
}
