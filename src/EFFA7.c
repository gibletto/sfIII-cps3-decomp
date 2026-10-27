/*
 * EFFA7.C  Effect A7: hit marks
 *
 * Effect A7 is the hit mark. effect_A7_init is called by the player damage code (PLPDM.c,
 * PLPCU.c) with the attacker's work and records the hit-mark number (hm_dm_side). On its first
 * frame effect_A7_move reads the hmdt entry: it requests the hit sound, sets the mark's colour
 * (hcct or the target's palette), offsets it by the explem / explem2 tables, jitters it at random,
 * selects the hit or offset-record pattern and arms a screen quake (gqdt).
 * The mark animates while EXE_flag and Game_pause are clear and uses the list-8 sort queue.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "aboutspr.h"
#include "sc_trans.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "Eff59.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "sc_sub.h"
#include "sc_sub_2.h"
#include "PLS02.h"
#include "EFFA7.h"

/* routine_no[0] */
#define R0_INIT         0       /* read the hit data and set the mark up */
#define R0_MOVE         1       /* animate until the pattern ends */
#define R0_KILL         2       /* put the work back */



/* no directional pattern, explem2 rows of 16 */
void effect_A7_move(WORK_Other* ewk) {
    const HMDT* tad;
    const EXPLEM* edt;
    s32 index;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        *ewk->wu.char_table = ef01_char_table;
        tad = &hmdt[ewk->wu.kohm];
        if (tad->hits == 0) {
            if (tad->se) {
                sound_effect_request[tad->se](ewk, tad->se);
                Last_Called_SE = tad->se;
            } else {
                Last_Called_SE = 0;
            }
            push_effect_work(&ewk->wu);
            return;
        }
        if (tad->status & 8) {
            ewk->wu.disp_flag = 2;
        } else {
            ewk->wu.disp_flag = 1;
        }
        if (tad->status & 0x40) {
            if (((WORK*)ewk->wu.target_adrs)->work_id == 1) {
                ewk->wu.dir_timer = ((PLW*)ewk->wu.target_adrs)->player_number;
            } else {
                ewk->wu.dir_timer = ((WORK_Other*)ewk->wu.target_adrs)->master_player;
            }
        }
        if (tad->col) {
            ewk->wu.my_col_code = hcct[tad->col];
        } else if (tad->status & 0x80) {
            ewk->wu.my_col_code = ((WORK*)ewk->wu.target_adrs)->my_col_code + 7;
        }
        if (tad->se) {
            sound_effect_request[tad->se](ewk, tad->se);
            Last_Called_SE = tad->se;
        } else {
            Last_Called_SE = 0;
        }
        if (tad->status & 0x10) {
            if (tad->status & 0x20) {
                edt = &explem2[tad->emhix][ewk->wu.dir_timer];
            } else {
                edt = &explem[tad->myhix];
            }
            if (ewk->wu.rl_flag) {
                ewk->wu.xyz[0].disp.pos -= edt->hx;
            } else {
                ewk->wu.xyz[0].disp.pos += edt->hx;
            }
            ewk->wu.xyz[1].disp.pos += edt->hy;
        }
        if (tad->status & 2) {
            ewk->wu.xyz[0].disp.pos += random_16_com() - 7;
            ewk->wu.xyz[1].disp.pos += (random_16_com() & 7) - 3;
        }
        ewk->wu.scr_mv_x = gqdt[tad->quake][GQ_DELAY];
        ewk->wu.scr_mv_y = gqdt[tad->quake][GQ_INDEX];
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos;
        ewk->wu.position_z = ewk->wu.xyz[2].disp.pos;
        if (tad->status & 0x10) {
            index = edt->chix;
        } else {
            index = tad->hits;
        }
        set_char_move_init(&ewk->wu, 0, index);
        sort_push_request8(&ewk->wu);
        break;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 0xFF) {
                ewk->wu.routine_no[0]++;
                return;
            }
            if (ewk->wu.scr_mv_x && --ewk->wu.scr_mv_x == 0) {
                bg_w.quake_y_index = ewk->wu.scr_mv_y;
            }
        }
        sort_push_request8(&ewk->wu);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_A7_init(PLW* wk) {
    WORK_Other* ewk;
    PLW* twk;
    s16 ix;
    if (wk->wu.work_id != 1) {
        return -1;
    }
    if ((ix = pull_effect_work(2)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    twk = (PLW*)wk->wu.target_adrs;
    ewk->wu.be_flag = 1;
    ewk->wu.id = 107;
    ewk->wu.work_id = 64;
    ewk->wu.rl_flag = wk->wu.rl_flag;
    ewk->wu.kohm = wk->wu.hm_dm_side;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    ewk->wu.my_mr_flag = 0;
    ewk->wu.xyz[0].disp.pos = ewk->wu.position_x = wk->wu.xyz[0].disp.pos;
    ewk->wu.xyz[1].disp.pos = ewk->wu.position_y = wk->wu.xyz[1].disp.pos;
    ewk->wu.xyz[2].disp.pos = 26;
    ewk->my_master = wk->wu.target_adrs;
    ewk->master_id = twk->wu.id;
    ewk->master_work_id = twk->wu.work_id;
    ewk->wu.target_adrs = (u32*)wk;
    ewk->wu.my_col_code = twk->wu.my_col_code + 7;
    ewk->master_player = ewk->wu.dir_timer = twk->player_number;
    ewk->wu.blink_timing = ewk->master_id;
    return 0;
}



