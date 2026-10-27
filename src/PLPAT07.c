/*
 * PLPAT07.C  Player 07 (Ibuki) special attack routines
 *
 * Character-specific attack routines for player number 7, dispatched by pl07_extra_attack
 * through pl07_exatt_table for attack routine numbers 16 and up.
 * Att_PL07_AT1/AT2/AT3 are jumping special moves that step through mvxy speed data on the
 * animation's cg_type marks; Att_PL07_SA2 and Att_PL07_SA3 run two of the super arts.
 * Att_PL07_BOUND_JUMP and Att_PL07_HOP_JUMP are hop/bounce movements not used by the table.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLS02.h"
#include "PLSGAUGE.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "PLPAT.h"
#include "PLS01.h"
#include "PLPAT07.h"

/* routine_no[3], Att_PL07_BOUND_JUMP */
#define BOUND_JUMP_CUE  1       /* run the animation to cue 1 */
#define BOUND_JUMP_AIR  2       /* in the air until it lands */
#define BOUND_JUMP_AIR2 3       /* in the air until it lands */
#define BOUND_JUMP_CUE2 4       /* run the animation to cue 10 */
#define BOUND_JUMP_MOVE 5       /* move and run the animation */
#define BOUND_JUMP_AIR3 6       /* in the air until it lands */
#define BOUND_JUMP_LAND 7       /* the landing */

/* routine_no[3], Att_PL07_HOP_JUMP */
#define HOP_JUMP_CUE    1       /* run the animation to cue 1 */
#define HOP_JUMP_AIR    2       /* in the air until it lands */
#define HOP_JUMP_AIR2   3       /* in the air until it lands */
#define HOP_JUMP_CUE2   4       /* run the animation to cue 1 */
#define HOP_JUMP_AIR3   5       /* in the air until it lands */
#define HOP_JUMP_LAND   6       /* the landing */

/* routine_no[3], Att_PL07_AT1 */
#define AT1_MOVE        1       /* move and run the animation */
#define AT1_CUE         2       /* run the animation to cue 1 */
#define AT1_AIR         3       /* in the air until it lands */
#define AT1_LAND        4       /* the landing */

/* routine_no[3], Att_PL07_AT2 */
#define AT2_MOVE        1       /* move and run the animation to cue 20 */
#define AT2_AIR         2       /* in the air until it lands */
#define AT2_LAND        3       /* the landing */

/* routine_no[3], Att_PL07_AT3 */
#define AT3_CUE         1       /* run the animation to cue 20 */
#define AT3_AIR         2       /* in the air until it lands */
#define AT3_LAND        3       /* the landing */

/* routine_no[3], Att_PL07_SA3 */
#define SA3_AIR         1       /* in the air until it lands */
#define SA3_LAND        2       /* the landing */



void pl07_extra_attack(PLW* wk) {
    pl07_exatt_table[wk->wu.routine_no[2] - ATTACK_SPECIAL](wk);
}



/* provisional name */
void Att_PL07_BOUND_JUMP(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        reset_mvxy_data(&wk->wu);
        wk->wu.mvxy.index = wk->as->r_no;
        break;
    case BOUND_JUMP_CUE:
        char_move(&wk->wu);
        if ((u8)wk->wu.cg_type == 1) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3] = BOUND_JUMP_AIR;
            wk->wu.cg_type = 0;
        }
        break;
    case BOUND_JUMP_AIR:
        jumping_union_process(&wk->wu, 1);
        if ((u8)wk->wu.cg_type == 8) {
            wk->wu.routine_no[3] = BOUND_JUMP_AIR2;
            wk->wu.cg_type = 0;
        }
        break;
    case BOUND_JUMP_AIR2:
        jumping_union_process(&wk->wu, 4);
        break;
    case BOUND_JUMP_CUE2:
        char_move(&wk->wu);
        if ((u8)wk->wu.cg_type == 10) {
            reset_mvxy_data(&wk->wu);
            wk->wu.routine_no[3] = BOUND_JUMP_MOVE;
            wk->wu.cg_type = 0;
        }
        break;
    case BOUND_JUMP_MOVE:
        char_move(&wk->wu);
        add_mvxy_speed(&wk->wu);
        cal_mvxy_speed(&wk->wu);
        switch (wk->wu.cg_type) {
        case 20:
            setup_mvxy_data(&wk->wu, 97);
            wk->wu.cg_type = 0;
            return;
        default:
            break;
        case 30:
            setup_mvxy_data(&wk->wu, 98);
            wk->wu.routine_no[3] = BOUND_JUMP_AIR2;
            wk->wu.cg_type = 0;
            break;
        }
        break;
    case BOUND_JUMP_AIR3:
        jumping_union_process(&wk->wu, 7);
        break;
    case BOUND_JUMP_LAND:
        char_move(&wk->wu);
        break;
    }
}



void Att_PL07_SA2(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.xyz[1].cal = 0;
        wk->wu.rl_flag = wk->wu.rl_waza;
        reset_mvxy_data((WORK*)wk);
        wk->wu.mvxy.index = wk->as->r_no;
        set_char_move_init((WORK*)wk, 5, wk->as->char_ix);
        break;
    default:
        char_move((WORK*)wk);
        cal_mvxy_speed((WORK*)wk);
        add_mvxy_speed((WORK*)wk);
        switch ((u8)wk->wu.cg_type) {
        case 20:
            setup_mvxy_data((WORK*)wk, wk->wu.mvxy.index);
            wk->wu.cg_type = 0;
            break;
        case 30:
            wk->wu.mvxy.index = wk->as->data_ix;
            setup_mvxy_data((WORK*)wk, wk->wu.mvxy.index);
            wk->wu.cg_type = 0;
            break;
        case 88:
            reset_mvxy_data((WORK*)wk);
            wk->wu.cg_type = 0;
            return;
        }
        break;
    }
}



/* provisional name */
void Att_PL07_HOP_JUMP(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        reset_mvxy_data(&wk->wu);
        wk->wu.mvxy.index = wk->as->r_no;
        break;
    case HOP_JUMP_CUE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3] = HOP_JUMP_AIR;
            wk->wu.cg_type = 0;
        }
        break;
    case HOP_JUMP_AIR:
        jumping_union_process(&wk->wu, 1);
        if (wk->wu.cg_type == 8) {
            wk->wu.routine_no[3] = HOP_JUMP_AIR2;
            wk->wu.cg_type = 0;
        }
        break;
    case HOP_JUMP_CUE2:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.routine_no[3] = HOP_JUMP_AIR3;
            wk->wu.cg_type = 0;
        }
        break;
    case HOP_JUMP_AIR2:
        jumping_union_process(&wk->wu, 6);
        break;
    case HOP_JUMP_AIR3:
        jumping_union_process(&wk->wu, 6);
        break;
    case HOP_JUMP_LAND:
        char_move(&wk->wu);
        break;
    }
}



void Att_PL07_AT1(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.xyz[1].cal = 0;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init((WORK*)wk, 5, wk->as->char_ix);
        reset_mvxy_data((WORK*)wk);
        wk->wu.mvxy.index = wk->as->r_no;
        break;
    case AT1_MOVE:
        char_move((WORK*)wk);
        cal_mvxy_speed((WORK*)wk);
        add_mvxy_speed((WORK*)wk);
        switch ((u8)wk->wu.cg_type) {
        case 20:
            setup_mvxy_data((WORK*)wk, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            goto clear;
        case 21:
            reset_mvxy_data((WORK*)wk);
        clear:
            wk->wu.cg_type = 0;
            break;
        case 30:
            wk->wu.routine_no[3] = AT1_CUE;
            wk->wu.cg_type = 0;
            goto out;
        }
    out:
        break;
    case AT1_CUE:
        char_move((WORK*)wk);
        if ((u8)wk->wu.cg_type == 1) {
            setup_mvxy_data((WORK*)wk, wk->wu.mvxy.index);
            wk->wu.routine_no[3] = AT1_AIR;
            wk->wu.cg_type = 0;
        }
        break;
    case AT1_AIR:
        jumping_union_process((WORK*)wk, 4);
        break;
    case AT1_LAND:
        char_move((WORK*)wk);
        break;
    }
}



void Att_PL07_AT2(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        reset_mvxy_data(&wk->wu);
        break;
    case AT2_MOVE:
        char_move(&wk->wu);
        add_mvxy_speed(&wk->wu);
        cal_mvxy_speed(&wk->wu);
        if (wk->wu.cg_type == 20) {
            setup_mvxy_data(&wk->wu, wk->as->r_no);
            wk->wu.routine_no[3] = AT2_AIR;
            wk->wu.cg_type = 0;
        }
        break;
    case AT2_AIR:
        jumping_union_process(&wk->wu, 3);
        if (wk->wu.cg_type == 30) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.cg_type = 0;
        }
        break;
    case AT2_LAND:
        char_move(&wk->wu);
        break;
    }
}



void Att_PL07_AT3(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        break;
    case AT3_CUE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 20) {
            wk->wu.routine_no[3]++;
        }
        break;
    case AT3_AIR:
        jumping_union_process(&wk->wu, 3);
        break;
    case AT3_LAND:
        char_move(&wk->wu);
        break;
    }
}



void Att_PL07_SA3(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
    case SA3_AIR:
        jumping_union_process(&wk->wu, 2);
        if (wk->wu.routine_no[3] != SA3_LAND) {
            if (wk->wu.cg_type == 20) {
                setup_mvxy_data(&wk->wu, wk->as->data_ix);
                wk->wu.cg_type = 0;
            }
            if (wk->wu.cg_type == 30) {
                setup_mvxy_data(&wk->wu, wk->as->r_no);
                wk->wu.cg_type = 0;
            }
        }
        break;
    case SA3_LAND:
        char_move(&wk->wu);
        break;
    }
}
