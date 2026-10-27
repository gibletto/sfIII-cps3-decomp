/*
 * EFFG1.C  Effect G1: follower controller for a player
 *
 * effect_G1_init (called from PLMAIN.c) is empty, so the controller is never made; effG1_dummy is
 * empty too. effect_G1_move would keep the controller on its player and work out each frame
 * (effG1_sync) four follow points beside the player (effG1_x_offsets, by facing and pose; over the
 * player while airborne) for the effect G2 parts it creates on its first frame, and end them
 * (effect_work_kill) when it ends.
 */

#include "structs.h"
#include "work.h"
#include "extern.h"
#include "EFFG1.h"

/* routine_no[0] */
#define R0_INIT         0       /* make the follower parts */
#define R0_MOVE         1       /* track the player during the round */
#define R0_AFTER        2       /* track the player after the round */
#define R0_KILL         3       /* (default) put the work back */

s32 push_effect_work(WORK* wkhd);
void effect_work_kill();

extern const s16 effG1_x_offsets[2][4];
void effG1_sync(WORK* ewk, PLW* pwk);
s32 effect_G2_init();

void effect_G1_move(WORK_Other* ewk) {
    PLW* pwk = (PLW*)ewk->my_master;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        effG1_sync(&ewk->wu, pwk);
        ewk->wu.cmwk[0] = ewk->wu.cmwk[1] = ewk->wu.cmwk[2] = ewk->wu.cmwk[3] = 0;
        ewk->wu.dmcal_d = ewk->wu.dmcal_m = 0;
        if (ewk->master_id) {
            effect_G2_init(ewk, 0);
            effect_G2_init(ewk, 1);
            effect_G2_init(ewk, 2);
        } else {
            effect_G2_init(ewk, 0);
            effect_G2_init(ewk, 1);
            effect_G2_init(ewk, 3);
        }
        break;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0] = R0_KILL;
            effect_work_kill(3, 162);
            break;
        }
        ewk->wu.dmcal_d = ewk->wu.dmcal_m;
        effG1_sync(&ewk->wu, pwk);
        ewk->wu.routine_no[1] = pwk->wu.routine_no[1];
        ewk->wu.routine_no[2] = pwk->wu.routine_no[2];
        if (pcon_dp_flag) {
            ewk->wu.routine_no[0] = R0_AFTER;
        }
        break;
    case R0_AFTER:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0] = R0_KILL;
            effect_work_kill(3, 162);
            break;
        }
        ewk->wu.dmcal_d = ewk->wu.dmcal_m;
        effG1_sync(&ewk->wu, pwk);
        ewk->wu.routine_no[1] = pwk->wu.routine_no[1];
        ewk->wu.routine_no[2] = pwk->wu.routine_no[2];
        break;
    default:
        push_effect_work(&ewk->wu);
        break;
    }
}

void effG1_sync(WORK* ewk, PLW* pwk) {
    s16 width;
    const s16* offsets;
    ewk->position_x = pwk->wu.position_x;
    ewk->position_y = 0;
    ewk->position_z = pwk->wu.position_z;
    if (pwk->wu.now_koc == 0 && (pwk->wu.char_index == 0 || pwk->wu.char_index == 33)) {
        ewk->position_z -= 2;
    }
    if (pwk->wu.xyz[1].disp.pos > 0) {
        ewk->old_pos[0] = ewk->position_x;
        ewk->dmcal_m = 1;
        ewk->cmwk[0] = ewk->cmwk[1] = 1;
        ewk->cmwk[2] = ewk->cmwk[3] = 1;
    } else {
        width = 0;
        if (pwk->wu.pat_status != 38) {
            width = 88;
        }
        if (pwk->wu.pat_status == 32) {
            width = 56;
        }
        if (pwk->dead_flag) {
            width = 64;
        }
        if (pwk->wu.rl_flag) {
            ewk->old_pos[0] = ewk->position_x - width;
        } else {
            ewk->old_pos[0] = ewk->position_x + width;
        }
        if (ewk->cmwk[0] + ewk->cmwk[1] + ewk->cmwk[2] + ewk->cmwk[3]) {
            ewk->dmcal_m = 2;
        } else {
            ewk->dmcal_m = 0;
        }
    }
    ewk->old_pos[1] = ewk->position_y;
    ewk->old_pos[2] = ewk->position_z;
    if (pwk->wu.rl_flag) {
        ewk->old_rno[0] = ewk->old_pos[0] + (offsets = effG1_x_offsets[0])[0];
        ewk->old_rno[2] = ewk->old_pos[0] + offsets[1];
        ewk->old_rno[4] = ewk->old_pos[0] + offsets[2];
        ewk->old_rno[6] = ewk->old_pos[0] + offsets[3];
    } else {
        ewk->old_rno[0] = ewk->old_pos[0] + (offsets = effG1_x_offsets[1])[0];
        ewk->old_rno[2] = ewk->old_pos[0] + offsets[1];
        ewk->old_rno[4] = ewk->old_pos[0] + offsets[2];
        ewk->old_rno[6] = ewk->old_pos[0] + offsets[3];
    }
}

void effect_G1_init(PLW* wk) {
}

void effG1_dummy(void) {
}
