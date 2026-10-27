/*
 * LOSE_PL.C  Lose poses after a round
 *
 * Player routines for the end of a round: lose_player dispatches the loser through Lose_00000 or
 * Lose_10000 by the character's lose type. A judged loss (pcon_rno 2/3) picks one of four lose poses,
 * any other loss one of eight; a loss on stage 8 area 0 runs lose_stage8_action instead.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "aboutspr.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "SYS_sub.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "sc_trans.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "fifo.h"
#include "eff36.h"
#include "EFF48.h"
#include "EFFC1.h"
#include "efff6.h"
#include "end_main.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "PLS02.h"
#include "Com_Pl.h"
#include "lose_pl.h"

/* wk->wu.routine_no[3] in a win or lose pose */
#define POSE_RUN        1       /* the pose runs until its script sets RN3_DONE */

s16 lose_rno[3];  /* 02023A7C */
s16 lose_free[2];  /* 02023A82 */


void lose_player(PLW* wk) {
    void (*lose_jp_tbl[2])(PLW*) = { Lose_00000, Lose_10000 };
    lose_jp_tbl[lose_type_tbl[wk->player_number]](wk);
}



void Lose_00000(PLW* wk) {
    if (pcon_rno[0] == PCON_DIE && pcon_rno[1] == SETTLE_JUDGE) {
        Judge_normal_loser(wk);
    } else {
        Normal_normal_Loser(wk);
    }
}



void Lose_10000(PLW* wk) {
    if (bg_w.stage == 8 && bg_w.area == 0) {
        lose_stage8_action(wk);
        return;
    }
    if ((pcon_rno[0] == PCON_DIE) && (pcon_rno[1] == SETTLE_JUDGE)) {
        switch (wk->wu.routine_no[3]) {
        case RN3_START:
            wk->wu.routine_no[3]++;
            lose_rno[0] = lose_rno[1] = lose_rno[2] = 0;
            wk->wu.char_index = random_16_com();
            wk->wu.char_index &= 3;
            set_char_move_init(&wk->wu, 9, wk->wu.char_index + 0x38);
            break;
        default:
        case POSE_RUN:
        case RN3_DONE:
            char_move(&wk->wu);
            break;
        }
    } else if (pcon_rno[1] == SETTLE_KO) {
        return;
    } else {
        switch (wk->wu.routine_no[3]) {
        case RN3_START:
            wk->wu.routine_no[3]++;
            lose_rno[0] = lose_rno[1] = lose_rno[2] = 0;
            wk->wu.char_index = random_16_com();
            wk->wu.char_index &= 7;
            set_char_move_init(&wk->wu, 9, wk->wu.char_index + 0x18);
            break;
        case POSE_RUN:
        case RN3_DONE:
            char_move(&wk->wu);
            break;
        }
    }
}



void Normal_normal_Loser(PLW* wk) {
    s16 work;
    if (bg_w.stage == 8 && bg_w.area == 0) {
        lose_stage8_action(wk);
        return;
    } else if (pcon_rno[1] == SETTLE_KO) {
        return;
    }
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        lose_rno[0] = lose_rno[1] = lose_rno[2] = 0;
        work = random_16_com();
        work &= 7;
        set_char_move_init(&wk->wu, 9, work + 0x18);
        break;
    case POSE_RUN:
    case RN3_DONE:
        char_move(&wk->wu);
        break;
    }
}




void Judge_normal_loser(PLW* wk) {
    s16 work;
    if (bg_w.stage == 8 && bg_w.area == 0) {
        lose_stage8_action(wk);
        return;
    }
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3] += 1;
        work = random_16_com();
        work &= 3;
        set_char_move_init(&wk->wu, 9, work + 0x38);
        break;
    case POSE_RUN:
    case RN3_DONE:
    default:
        char_move(&wk->wu);
        break;
    }
}



void lose_stage8_action(PLW* wk) {
    if (wk->wu.routine_no[3] == RN3_START) {
        wk->wu.routine_no[3]++;
        lose_rno[0] = lose_rno[1] = lose_rno[2] = 0;
    }
    switch (lose_rno[2]) {
    case 0:
        lose_rno[2]++;
        lose_rno[1] = 0;
        if (wk->wu.pat_status != 38) {
            lose_rno[0] = 0;
            set_char_move_init(&wk->wu, 9, 60);
        } else {
            lose_rno[0] = 1;
            wk->wu.kage_flag = 0;
        }
        break;
    case 1:
        if (lose_rno[0]) {
            wk->wu.kage_flag = 0;
            wk->wu.position_y = wk->wu.xyz[1].disp.pos = stage8_base_y - 40;
        } else {
            switch (lose_rno[1]) {
            case 0:
                if (bg_w.bgw[1].r_no_1 >= 1) {
                    lose_rno[1]++;
                    set_char_move_init(&wk->wu, 9, 61);
                    wk->wu.mvxy.a[1].sp = 0x60000;
                    wk->wu.mvxy.d[1].sp = -0x4000;
                    lose_free[wk->wu.id] = 110;
                } else {
                    char_move(&wk->wu);
                }
                break;
            case 1:
                lose_free[wk->wu.id]--;
                if (lose_free[wk->wu.id] < 0) {
                    wk->wu.routine_no[3]++;
                } else {
                    add_y_sub((WORK_Other*)wk);
                }
                /* fall through */
            case 2:
                char_move(&wk->wu);
                wk->wu.kage_flag = 0;
                break;
            }
        }
        break;
    }
}



