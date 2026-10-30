/*
 * EFFC1.C  Player companions
 *
 * Places a companion for characters 3 and 10. Its animation follows the player
 * position, facing and completed victory state.
 */
#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFC1.h"
#include "fighter.h"

/* routine_no[0] */
#define R0_INIT         0       /* show the first pose */
#define R0_WATCH        1       /* turn to face the player */
#define R0_RESULT       2       /* hold the result pose */

extern const s16 effC1_reverse_tbl[5];
extern const s16 effC1_position_tbl[2][5];

void effect_C1_move(WORK_Other* ewk) {
    s16 x;
    s16 id;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.old_rno[3], ewk->wu.old_rno[0] + 1, 0);
        ewk->wu.old_rno[1] = ewk->wu.old_rno[0];
        break;
    case R0_WATCH:
        if (Allow_a_battle_f == 0 && Conclusion_Flag == 1 && C_No0 >= C0_FIGHT) {
            if (Complete_Victory != 0 && Conclusion_Flag) {
                s32 pattern;
                ewk->wu.routine_no[0]++;
                if (Winner_id != ewk->wu.old_rno[2]) {
                    pattern = ewk->wu.old_rno[3] + 2;
                } else {
                    pattern = ewk->wu.old_rno[3] + 1;
                }
                set_char_move_init(&ewk->wu, 0, pattern);
                break;
            }
        }
        id = ewk->wu.old_rno[2];
        x = plw[id].wu.position_x;
        if (x < effC1_position_tbl[id][0]) {
            ewk->wu.old_rno[0] = 0;
        } else if (x < effC1_position_tbl[(s8)ewk->wu.old_rno[2]][1]) {
            ewk->wu.old_rno[0] = 1;
        } else if (x < effC1_position_tbl[(s8)ewk->wu.old_rno[2]][2]) {
            ewk->wu.old_rno[0] = 2;
        } else if (x < effC1_position_tbl[(s8)ewk->wu.old_rno[2]][3]) {
            ewk->wu.old_rno[0] = 3;
        } else {
            if (x < effC1_position_tbl[(s8)ewk->wu.old_rno[2]][4]) { }
            ewk->wu.old_rno[0] = 4;
        }
        if (ewk->wu.rl_flag) {
            ewk->wu.old_rno[0] = effC1_reverse_tbl[ewk->wu.old_rno[0]];
        }
        if (ewk->wu.old_rno[1] != ewk->wu.old_rno[0]) {
            set_char_move_init2(&ewk->wu, 0, ewk->wu.old_rno[3], ewk->wu.old_rno[0] + 1, 0);
            ewk->wu.old_rno[1] = ewk->wu.old_rno[0];
        }
        break;
    case R0_RESULT:
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
    sort_push_request(&ewk->wu);
}

s32 effect_C1_init(PLW* wk) {
    s16 id;
    WORK_Other* ewk;
    s16 pattern = -1;
    s16 ix;
    id = wk->wu.id ^ 1;
    if (wk->player_number == PL_YANG) {
        if (plw[id].player_number != PL_YUN && plw[id].player_number != PL_YANG) {
            pattern = 3;
        }
    } else if (wk->player_number == PL_YUN) {
        if (plw[id].player_number != PL_YUN && plw[id].player_number != PL_YANG) {
            pattern = 0;
        }
    }
    if (pattern < 0) {
        return;
    }
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 121;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.disp_flag = 0;
    ewk->wu.type = pattern;
    ewk->wu.old_rno[2] = wk->wu.id;
    ewk->wu.my_family = 2;
    ewk->wu.old_rno[0] = 0;
    ewk->wu.old_rno[3] = pattern;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.kage_flag = 1;
    ewk->wu.kage_hx = 2;
    ewk->wu.kage_hy = 7;
    ewk->wu.kage_char = 13;
    ewk->wu.my_priority = ewk->wu.position_z = 70;
    ewk->wu.kage_prio = ewk->wu.my_priority + 1;
    ewk->wu.xyz[0].disp.low = 0;
    ewk->wu.xyz[1].disp.low = 0;
    ewk->wu.char_table[0] = direct_03_char_table;
    if (ewk->wu.type) {
        ewk->wu.my_col_code = 0x205C;
    } else {
        ewk->wu.my_col_code = 0x205D;
    }
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 6;
    if (ewk->wu.old_rno[2]) {
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 656;
        if (ewk->wu.type) {
            ewk->wu.rl_flag = 0;
        } else {
            ewk->wu.rl_flag = 1;
        }
    } else {
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 368;
        if (ewk->wu.type) {
            ewk->wu.rl_flag = 1;
        } else {
            ewk->wu.rl_flag = 0;
        }
    }
}

void effect_C1_entry(void) {
    effect_C1_init(&plw[0]);
    effect_C1_init(&plw[1]);
}
