/*
 * EFF61.C  Result figure and its companion
 *
 * The figure changes its animation and facing for the winner, then advances through
 * the result poses. Effect 62 supplies its companion.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFECT.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "bg_sub.h"
#include "bg_sub_5.h"
#include "PLS02.h"
#include "ta_sub.h"
#include "EFF61.h"
#include "EFF62.h"

s16 get_winner_id(void);
void eff61_0000(WORK_Other* ewk);
void eff61_1000(WORK_Other* ewk);
void eff61_3000(WORK_Other* ewk);
void eff61_4000(WORK_Other* ewk);
void eff61_wait(WORK_Other* ewk);
void eff61_check_result(WORK_Other* ewk, s16 flag);

void effect_61_move(WORK_Other* ewk) {
    void (*eff61_jp[8])(WORK_Other*) = {
        eff61_0000, eff61_1000, eff61_wait, eff61_3000,
        eff61_4000, eff61_wait, eff61_wait, eff61_wait
    };
    eff61_jp[ewk->wu.routine_no[0]](ewk);
}

void eff61_0000(WORK_Other* ewk) {
    ewk->wu.routine_no[0]++;
    ewk->wu.routine_no[1] = 0;
    ewk->wu.old_rno[0] = 0;
    ewk->wu.disp_flag = 1;
    set_char_move_init(&ewk->wu, 0, 0);
    ewk->wu.xyz[0].disp.pos = 392;
    suzi_sync_pos_set(ewk);
    sort_push_request4(&ewk->wu);
}

void eff61_1000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                ewk->wu.routine_no[1]++;
            }
        }
        eff61_check_result(ewk, 0);
        break;
    case 1:
        eff61_check_result(ewk, 1);
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 1);
        break;
    case 2:
        eff61_check_result(ewk, 1);
        ewk->wu.routine_no[1]++;
        break;
    case 3:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                ewk->wu.routine_no[0] = 0;
            } else {
                eff61_check_result(ewk, 1);
            }
        }
        break;
    }
    disp_pos_trans_entry_s(ewk);
}

void eff61_3000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        if (check_work_position(&ewk->wu, (WORK*)&plw[ewk->wu.old_rno[0]])) {
            ewk->wu.char_index = 3;
        } else {
            ewk->wu.char_index = 4;
        }
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case 1:
        ewk->wu.routine_no[1]++;
        break;
    case 2:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
        }
        break;
    }
    disp_pos_trans_entry_s(ewk);
}

void eff61_4000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        set_char_move_init(&ewk->wu, 0, 2);
        break;
    case 1:
        ewk->wu.routine_no[1]++;
        break;
    case 2:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
        }
        break;
    }
    disp_pos_trans_entry_s(ewk);
}

void eff61_wait(WORK_Other* ewk) {
    disp_pos_trans_entry_s(ewk);
}

void eff61_check_result(WORK_Other* ewk, s16 flag) {
    s16 winner;
    if (complete_victory_check()) {
        ewk->wu.routine_no[1] = 0;
        winner = get_winner_id();
        if (winner == ewk->wu.old_rno[0]) {
            if (flag) {
                ewk->wu.routine_no[0] = 4;
                ewk->wu.char_index = 2;
            } else {
                ewk->wu.routine_no[0] = 6;
            }
        } else if (flag) {
            ewk->wu.routine_no[0] = 7;
        } else {
            ewk->wu.routine_no[0] = 3;
        }
    }
}

s32 effect_61_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 61;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 88;
    ewk->wu.xyz[0].disp.pos = 392;
    ewk->wu.xyz[1].disp.pos = 58;
    ewk->wu.my_priority = ewk->wu.position_z = 77;
    ewk->wu.char_index = 0;
    ewk->wu.hit_stop = 1;
    ewk->wu.sync_suzi = 0;
    ewk->wu.char_table[0] = &result_char_table[1];
    suzi_offset_set(&ewk->wu);
    effect_62_init(ewk);
    return 0;
}
