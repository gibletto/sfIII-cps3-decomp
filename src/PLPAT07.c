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



void pl07_extra_attack(PLW* wk) {
    pl07_exatt_table[wk->wu.routine_no[2] - 16](wk);
}



/* provisional name */
void Att_PL07_BOUND_JUMP(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        reset_mvxy_data(&wk->wu);
        wk->wu.mvxy.index = wk->as->r_no;
        break;
    case 1:
        char_move(&wk->wu);
        if ((u8)wk->wu.cg_type == 1) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3] = 2;
            wk->wu.cg_type = 0;
        }
        break;
    case 2:
        jumping_union_process(&wk->wu, 1);
        if ((u8)wk->wu.cg_type == 8) {
            wk->wu.routine_no[3] = 3;
            wk->wu.cg_type = 0;
        }
        break;
    case 3:
        jumping_union_process(&wk->wu, 4);
        break;
    case 4:
        char_move(&wk->wu);
        if ((u8)wk->wu.cg_type == 10) {
            reset_mvxy_data(&wk->wu);
            wk->wu.routine_no[3] = 5;
            wk->wu.cg_type = 0;
        }
        break;
    case 5:
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
            wk->wu.routine_no[3] = 3;
            wk->wu.cg_type = 0;
            break;
        }
        break;
    case 6:
        jumping_union_process(&wk->wu, 7);
        break;
    case 7:
        char_move(&wk->wu);
        break;
    }
}



void Att_PL07_SA2(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
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
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        reset_mvxy_data(&wk->wu);
        wk->wu.mvxy.index = wk->as->r_no;
        break;
    case 1:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.routine_no[3] = 2;
            wk->wu.cg_type = 0;
        }
        break;
    case 2:
        jumping_union_process(&wk->wu, 1);
        if (wk->wu.cg_type == 8) {
            wk->wu.routine_no[3] = 3;
            wk->wu.cg_type = 0;
        }
        break;
    case 4:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.routine_no[3] = 5;
            wk->wu.cg_type = 0;
        }
        break;
    case 3:
        jumping_union_process(&wk->wu, 6);
        break;
    case 5:
        jumping_union_process(&wk->wu, 6);
        break;
    case 6:
        char_move(&wk->wu);
        break;
    }
}



void Att_PL07_AT1(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.xyz[1].cal = 0;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init((WORK*)wk, 5, wk->as->char_ix);
        reset_mvxy_data((WORK*)wk);
        wk->wu.mvxy.index = wk->as->r_no;
        break;
    case 1:
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
            wk->wu.routine_no[3] = 2;
            wk->wu.cg_type = 0;
            goto out;
        }
    out:
        break;
    case 2:
        char_move((WORK*)wk);
        if ((u8)wk->wu.cg_type == 1) {
            setup_mvxy_data((WORK*)wk, wk->wu.mvxy.index);
            wk->wu.routine_no[3] = 3;
            wk->wu.cg_type = 0;
        }
        break;
    case 3:
        jumping_union_process((WORK*)wk, 4);
        break;
    case 4:
        char_move((WORK*)wk);
        break;
    }
}



void Att_PL07_AT2(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        reset_mvxy_data(&wk->wu);
        break;
    case 1:
        char_move(&wk->wu);
        add_mvxy_speed(&wk->wu);
        cal_mvxy_speed(&wk->wu);
        if (wk->wu.cg_type == 20) {
            setup_mvxy_data(&wk->wu, wk->as->r_no);
            wk->wu.routine_no[3] = 2;
            wk->wu.cg_type = 0;
        }
        break;
    case 2:
        jumping_union_process(&wk->wu, 3);
        if (wk->wu.cg_type == 30) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.cg_type = 0;
        }
        break;
    case 3:
        char_move(&wk->wu);
        break;
    }
}



void Att_PL07_AT3(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        break;
    case 1:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 20) {
            wk->wu.routine_no[3]++;
        }
        break;
    case 2:
        jumping_union_process(&wk->wu, 3);
        break;
    case 3:
        char_move(&wk->wu);
        break;
    }
}



void Att_PL07_SA3(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
    case 1:
        jumping_union_process(&wk->wu, 2);
        if (wk->wu.routine_no[3] != 2) {
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
    case 2:
        char_move(&wk->wu);
        break;
    }
}
