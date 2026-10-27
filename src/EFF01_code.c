/*
 * EFF01.C  Effect 01 (overlay parts)
 *
 * effect_01_move runs the overlay-parts work that follows its master's motion and flip;
 * get_new_parts_data takes the next parts record and its display flag; effect_01_init creates it for one of a character's parts
 * slots and records it in the master's olc_work_ix.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFF00.h"
#include "fighter.h"

/* routine_no[0] */
#define R0_INIT         0       /* set up from the master */
#define R0_MOVE         1       /* follow the master's parts animation */
#define R0_KILL         2       /* put the work back */

void effect_01_move(WORK_Other* ewk) {
    WORK* mwk = (WORK*)ewk->my_master;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.cgromtype = mwk->cgromtype;
        ewk->wu.cg_number = ewk->wu.old_cgnum = 0;
        ewk->wu.blink_timing = mwk->blink_timing;
        goto clear_ix;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1 || mwk->olc_work_ix[ewk->wu.type] != ewk->wu.myself) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (mwk->cg_olc.olc_ix[ewk->wu.type] == 0) {
        clear_ix:
            ewk->wu.cg_olc.olc_ix[ewk->wu.type] = 0;
            return;
        }
        if (!Game_pause && !EXE_flag) {
            if (ewk->wu.cg_olc.olc_ix[ewk->wu.type] != mwk->cg_olc.olc_ix[ewk->wu.type]) {
                ewk->wu.cg_olc.olc_ix[ewk->wu.type] = ewk->wu.cg_ix = mwk->cg_olc.olc_ix[ewk->wu.type];
                ewk->wu.now_koc = ewk->wu.cg_ix;
                if (ewk->wu.type == 0 && ((PLW*)mwk)->player_number == PL_GILL && mwk->rl_flag) {
                    ewk->wu.now_koc++;
                }
                get_new_parts_data(ewk, (PLW*)mwk);
            } else if (((PLW*)mwk)->sa_stop_flag == 0) {
                if (--ewk->wu.cg_ctr == 0) {
                    if (ewk->wu.overlap_char_tbl->parts_nix) {
                        ewk->wu.cg_ix = ewk->wu.overlap_char_tbl->parts_nix;
                    } else {
                        ewk->wu.cg_ix++;
                    }
                    ewk->wu.now_koc = ewk->wu.cg_ix;
                    get_new_parts_data(ewk, (PLW*)mwk);
                }
            }
            if (ewk->wu.cg_number == 0) {
                break;
            }
            ewk->wu.rl_flag = mwk->rl_flag;
            ewk->wu.cg_flip = mwk->cg_flip ^ ewk->wu.overlap_char_tbl->parts_flip;
            ewk->wu.position_x = mwk->position_x;
            ewk->wu.position_y = mwk->position_y;
            ewk->wu.position_z = mwk->position_z;
            if (ewk->wu.rl_flag) {
                ewk->wu.position_x -= ewk->wu.overlap_char_tbl->parts_hos_x;
            } else {
                ewk->wu.position_x += ewk->wu.overlap_char_tbl->parts_hos_x;
            }
            ewk->wu.position_y += ewk->wu.overlap_char_tbl->parts_hos_y;
            if (ewk->wu.overlap_char_tbl->parts_prio == 2) {
                ewk->wu.position_z -= (ewk->wu.type + 1) * 2;
            } else {
                ewk->wu.position_z += (ewk->wu.type + 1) * 2;
            }
        }
        if (ewk->wu.cg_number == 0) {
            break;
        }
        if (ewk->wu.overlap_char_tbl->parts_colcd == 0) {
            ewk->wu.my_col_code = mwk->my_col_code;
            ewk->wu.extra_col = mwk->extra_col;
            ewk->wu.extra_col_2 = mwk->extra_col_2;
        }
        sort_push_request(&ewk->wu);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* provisional name */
void get_new_parts_data(WORK_Other* ewk, PLW* mwk) {
    ewk->wu.overlap_char_tbl = mwk->wu.overlap_char_tbl + ewk->wu.now_koc;
    ewk->wu.cg_ctr = ewk->wu.overlap_char_tbl->parts_timer;
    switch (ewk->wu.overlap_char_tbl->parts_disp) {
    case 1:
        if (mwk->wu.disp_flag) {
            ewk->wu.disp_flag = 1;
        } else {
            ewk->wu.disp_flag = 0;
        }
        break;
    case 2:
        if (mwk->wu.disp_flag) {
            ewk->wu.disp_flag = 2;
        } else {
            ewk->wu.disp_flag = 0;
        }
        break;
    case 11:
        ewk->wu.disp_flag = 1;
        break;
    case 12:
        ewk->wu.disp_flag = 2;
        break;
    default:
        ewk->wu.disp_flag = mwk->wu.disp_flag;
        break;
    }
    if (ewk->wu.overlap_char_tbl->parts_colmd) {
        if (ewk->wu.overlap_char_tbl->parts_colmd == 1) {
            ewk->wu.my_col_mode = ((WORK*)mwk->wu.target_adrs)->my_col_mode;
        } else {
            ewk->wu.my_col_mode = parts_colmd_table[ewk->wu.overlap_char_tbl->parts_colmd];
        }
    } else {
        ewk->wu.my_col_mode = mwk->wu.my_col_mode;
    }
    if (ewk->wu.overlap_char_tbl->parts_colcd) {
        ewk->wu.my_col_code = parts_colcd_table[ewk->wu.overlap_char_tbl->parts_colcd];
        if (!(parts_colcd_table[ewk->wu.overlap_char_tbl->parts_colcd] & 0x2000)) {
            ewk->wu.my_col_code += mwk->wu.my_col_code;
        }
    } else {
        ewk->wu.my_col_code = mwk->wu.my_col_code;
        ewk->wu.extra_col = mwk->wu.extra_col;
        ewk->wu.extra_col_2 = mwk->wu.extra_col_2;
    }
    ewk->wu.cg_number = ewk->wu.overlap_char_tbl->parts_char;
}



s32 effect_01_init(WORK* wk, u8 koolc) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(1)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 1;
    ewk->wu.work_id = 32;
    ewk->wu.type = koolc;
    ewk->wu.my_family = wk->my_family;
    ewk->wu.blink_timing = wk->blink_timing;
    ewk->my_master = (u32*)wk;
    ewk->master_work_id = wk->work_id;
    ewk->master_id = wk->id;
    wk->olc_work_ix[koolc] = ewk->wu.myself;
    return 0;
}
