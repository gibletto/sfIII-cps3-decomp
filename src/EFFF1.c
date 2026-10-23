/*
 * EFFF1.C  Effect F1: another-BG switch control
 *
 * Effect F1 is started from character move data (CHARMOVE.c) to switch a player's another-BG.
 * effect_F1_move loads its type, duration and end conditions from effF1_data_tbl,
 * sets another_bg[] for the player and clears it
 * again when a condition is met: the timer runs out, the player's or opponent's state or move
 * changes, the super art ends, dramatic-battle mode is on, or the player's shell is gone.
 * effect_F1_init creates the effect for the player wk.
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
#include "PLS02.h"
#include "aboutspr.h"
#include "EFFF1.h"



void effect_F1_move(WORK_Other* ewk) {
    PLW* mwk = (PLW*)ewk->my_master;
    s32 rno;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        effF1_data_set(ewk, mwk);
        another_bg[ewk->master_id] = ewk->wu.type;
        ewk->wu.routine_no[0]++;
    case 1:
        if (ewk->wu.dead_f == 1) {
            goto end;
        }
        if ((ewk->wu.dir_old & 1) && (--ewk->wu.direction == 0)) {
            goto end;
        }
        if ((ewk->wu.dir_old & 2)) {
            if (((ewk->wu.routine_no[5] != mwk->wu.routine_no[1]) ||
                                      (ewk->wu.routine_no[6] != mwk->wu.routine_no[2]))) {
                goto end;
            }
        }
        if ((ewk->wu.dir_old & 4) && (mwk->sa->ok != -1)) {
            goto end;
        }
        if (ewk->wu.dir_old & 8) {
            rno = ((WORK*)mwk->wu.target_adrs)->routine_no[1];
            if (rno != 4 && rno != 2) {
                goto end;
            }
        }
        if (ewk->wu.dir_old & 0x10) {
            rno = mwk->wu.routine_no[1];
            if (rno != 4 && rno != 2) {
                goto end;
            }
        }
        if ((ewk->wu.dir_old & 0x20) && (ewk->wu.total_att_set != ((WORK*)mwk->wu.target_adrs)->kind_of_waza)) {
            goto end;
        }
        if ((ewk->wu.dir_old & 0x40) && (ewk->wu.total_paring != mwk->wu.kind_of_waza)) {
            goto end;
        }
        if (ewk->wu.old_rno[3] == 0 && pcon_dp_flag) {
            goto end;
        }
        if (ewk->wu.old_rno[2] && (ewk->wu.total_paring != mwk->wu.kind_of_waza) && (mwk->wu.shell_ix[0] == -1)) {
            goto end;
        }
        if (another_bg[ewk->master_id] != ewk->wu.type) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (another_bg[ewk->master_id] == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    end:
        ewk->wu.routine_no[0]++;
        another_bg[ewk->master_id] = 0;
        break;
    case 2:
    default:
        push_effect_work((WORK*)ewk);
        break;
    }
}



/* provisional name */
void effF1_data_set(WORK_Other* ewk, PLW* mwk) {
    const s16* tbl = effF1_data_tbl[ewk->wu.type];
    ewk->wu.dir_old = tbl[0];
    ewk->wu.type = tbl[1];
    ewk->wu.direction = tbl[2];
    ewk->wu.old_rno[3] = tbl[3];
    ewk->wu.old_rno[2] = tbl[4];
    ewk->wu.routine_no[5] = mwk->wu.routine_no[1];
    ewk->wu.routine_no[6] = mwk->wu.routine_no[2];
    ewk->wu.total_paring = mwk->wu.kind_of_waza;
    ewk->wu.total_att_set = ((WORK*)mwk->wu.target_adrs)->kind_of_waza;
}

/* Create the effect for the player. */
u32 effect_F1_init(wk, type)
WORK* wk;
u8 type;
{
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 151;
    ewk->wu.work_id = 16;
    ewk->wu.type = type;
    ewk->my_master = (u32*)wk;
    ewk->master_work_id = wk->work_id;
    ewk->master_id = wk->id;
    ewk->master_player = ((PLW*)wk)->player_number;
    return 0;
}



