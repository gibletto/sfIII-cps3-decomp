/*
 * EFF10.C  Effect 10: character scene objects
 *
 * effect_10_init creates the objects listed in scr_obj_data10 for a character. Depending on
 * type, effect_10_move just animates, runs eff10_run_away (animates, waits for the win
 * sequence to move on, then runs off screen away from its owner, sooner if the owner presses
 * a button) or eff10_anime_end_wait (plays once, waits 32 frames and ends).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFF10.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the animation */
#define R0_MOVE         1       /* run the object's behaviour */
#define R0_END          2       /* hidden for a frame */
#define R0_KILL         3       /* (default) put the work back */

/* routine_no[1], eff10_run_away */
#define R1_STAY         0       /* animate until the win scene moves on */
#define R1_COUNT        1       /* count down, faster on the owner's button */
#define R1_RUN          2       /* run off screen away from the owner */

/* routine_no[1], eff10_anime_end_wait */
#define R1_PLAY         0       /* play the animation once */
#define R1_WAIT         1       /* wait 32 frames, then end */



/* 02006AA8 */
const s16* scr_obj_data10[4] = {
    scr_obj_data10_0,
    scr_obj_data10_1,
    scr_obj_data10_2,
    scr_obj_data10_3,
};


void effect_10_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R0_MOVE:
        switch (ewk->wu.type) {
        case 0:
            char_move(&ewk->wu);
            break;
        case 1:
            eff10_run_away(ewk);
            break;
        case 2:
        case 3:
            eff10_anime_end_wait(ewk);
            break;
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case R0_END:
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



/* provisional name */
void eff10_run_away(WORK_Other* ewk) {
    WORK* oya_ptr = (WORK*)ewk->my_master;
    switch (ewk->wu.routine_no[1]) {
    case R1_STAY:
        char_move(&ewk->wu);
        if (win_rno[1] > 2) {
            ewk->wu.routine_no[1]++;
            ewk->wu.old_rno[0] = 16;
        }
        break;
    case R1_COUNT:
        char_move(&ewk->wu);
        ewk->wu.old_rno[0]--;
        if (pl_shot_on_check(oya_ptr->id)) {
            ewk->wu.old_rno[0]--;
        }
        if (ewk->wu.old_rno[0] < 0) {
            ewk->wu.routine_no[1]++;
            if (oya_ptr->xyz[0].disp.pos < bg_w.bgw[1].pos_x_work) {
                ewk->wu.direction = 0;
                ewk->wu.mvxy.a[0].sp = -0x28000;
                ewk->wu.mvxy.d[0].sp = -0x4000;
            } else {
                ewk->wu.direction = 1;
                ewk->wu.mvxy.a[0].sp = 0x28000;
                ewk->wu.mvxy.a[1].sp = 0x4000;
            }
        }
        break;
    case R1_RUN:
        char_move(&ewk->wu);
        add_x_sub(ewk);
        if (ewk->wu.direction) {
            if (bg_w.bgw[1].xy[0].disp.pos + 0x130 < ewk->wu.xyz[0].disp.pos) {
                ewk->wu.routine_no[0]++;
            }
        } else if (bg_w.bgw[1].xy[0].disp.pos - 0x130 > ewk->wu.xyz[0].disp.pos) {
            ewk->wu.routine_no[0]++;
        }
        break;
    }
}



/* provisional name */
void eff10_anime_end_wait(wk)
WORK* wk;
{
    switch (wk->routine_no[1]) {
    case R1_PLAY:
        char_move(wk);
        if (wk->cg_type == 0xFF) {
            wk->routine_no[1]++;
            wk->old_rno[0] = 32;
        }
        break;
    case R1_WAIT:
        wk->old_rno[0]--;
        if (wk->old_rno[0] < 0) {
            wk->routine_no[0]++;
        }
        break;
    }
}



s32 effect_10_init(WORK* wk, u8 type) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data;
    if (!scr_obj_num10[type]) {
        return;
    }
    data = scr_obj_data10[type];
    for (i = 0; i < scr_obj_num10[type]; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 10;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->my_master = (u32*)wk;
        ewk->wu.my_col_mode = wk->my_col_mode;
        ewk->wu.my_col_code = wk->my_col_code;
        ewk->wu.my_family = 2;
        ewk->wu.type = type;
        ewk->wu.position_z = wk->position_z - 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.char_table[0] = etc2_char_table;
        if (wk->rl_flag) {
            ewk->wu.xyz[0].disp.pos = wk->xyz[0].disp.pos - *data;
        } else {
            ewk->wu.xyz[0].disp.pos = wk->xyz[0].disp.pos + *data;
        }
        data++;
        ewk->wu.xyz[1].disp.pos = *data++;
        ewk->wu.char_index = *data++;
        ewk->wu.sync_suzi = 0;
        suzi_offset_set(&ewk->wu);
    }
    return 0;
}
