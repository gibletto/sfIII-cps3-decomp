/*
 * EFFB3.C  Effect B3: round / FIGHT display
 *
 * Effect B3 is the display child of the round-call effect B2 (EFFB2.C), one work per letter:
 * effect_B3_init makes the ROUND letters (6 works, then effect B9 for the round number) or the
 * FINAL ROUND letters (10 works), each with its own cell and goal x.
 * effect_B3_move follows the parent's state each frame:
 *   round_move_init    (state 1) grows each letter in while it flies to its goal, one letter
 *                      after another (b2_curr_no), with the round call voice
 *   round_vanish       (state 4) shrinks the letter away
 *   fight_move         (state 5) flies the FIGHT letters in from 127 shrinking to 63
 * Each routine counts rf_b2_flag up (or sets it) when its part is done.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
void set_char_move_init2();
#include "charmove_2.h"
#include "ta_sub.h"
#include "aboutspr.h"
#include "effb9.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLS02.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "CALDIR.h"
#include "effb2.h"
#include "effb3.h"



WORK_Other * oya_adrs;  

extern const s16 effb3_round_tbl[6][2];
extern const s16 effb3_final_tbl[10][2];
extern const s16 effb3_fight_tbl[6][3];
void load_any_color();

#pragma inline(effB3_kill)


void effect_B3_move(WORK_Other* ewk) {
    oya_adrs = (WORK_Other*)ewk->my_master;
    b3_Break_Into_check(ewk);
    switch (oya_adrs->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0] = ewk->wu.routine_no[1] = ewk->wu.routine_no[2] = 0;
        break;
    case 1:
        round_move_init(ewk);
        break;
    case 2:
    case 3:
    case 6:
        disp_pos_trans_entry(ewk);
        break;
    case 4:
        round_vanish(ewk);
        break;
    case 5:
        fight_move(ewk);
        break;
    case 7:
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



void round_move_init(WORK_Other* ewk) {
    if (ewk->wu.vital_new == 5 && !ewk->wu.hit_quake) {
        return;
    }
    if (b2_curr_no < ewk->wu.vital_new) {
        return;
    }
    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (!ewk->wu.vital_new) {
            if (oya_adrs->wu.type) {
                Sound_SE(0x8C);
            } else {
                Sound_SE(Round_num + 0x80);
            }
        }
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.my_mr.size.x = 0;
        ewk->wu.my_mr.size.y = 0;
        ewk->wu.my_mr_flag = 1;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.old_rno[0], 0);
        ewk->wu.hit_stop = 4;
        cal_all_speed_data(ewk, ewk->wu.hit_stop, ewk->wu.scr_mv_x, ewk->wu.scr_mv_y, 1, 1);
        break;
    case 1:
        ewk->wu.my_mr.size.x += 10;
        ewk->wu.my_mr.size.y += 10;
        ewk->wu.hit_stop--;
        if (ewk->wu.hit_stop < 0) {
            ewk->wu.routine_no[1]++;
            rf_b2_flag++;
            ewk->wu.my_mr.size.x = 63;
            ewk->wu.my_mr.size.y = 63;
        } else {
            add_x_sub(ewk);
            add_y_sub(ewk);
            if (ewk->wu.hit_stop == 3) {
                b2_curr_no++;
            }
        }
        disp_pos_trans_entry5(ewk);
        break;
    case 2:
    default:
        disp_pos_trans_entry(ewk);
        break;
    }
}



/* provisional name */
void round_vanish(WORK_Other* ewk) {
    if (ewk->wu.vital_new == 5 && !ewk->wu.hit_quake) {
        return;
    }
    switch (ewk->wu.routine_no[3]) {
    case 0:
        ewk->wu.disp_flag = 1;
        ewk->wu.my_mr.size.y -= 8;
        if (ewk->wu.my_mr.size.y < 0) {
            ewk->wu.disp_flag = 0;
            ewk->wu.hit_stop = 16;
            ewk->wu.routine_no[3]++;
        }
        disp_pos_trans_entry5(ewk);
        break;
    case 1:
        ewk->wu.hit_stop--;
        if (ewk->wu.hit_stop < 0) {
            rf_b2_flag++;
        }
        break;
    }
}



void fight_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        if (!ewk->wu.vital_new) {
            Sound_SE(0x89);
        }
        if (ewk->wu.vital_new > 5) {
            effB3_kill(ewk);
            break;
        }
        ewk->wu.routine_no[2]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.my_mr.size.x = 127;
        ewk->wu.my_mr.size.y = 127;
        ewk->wu.my_mr_flag = 1;
        ewk->wu.xyz[1].cal = 0x800000;
        ewk->wu.scr_mv_y = ewk->wu.position_y = 128;
        ewk->wu.old_rno[0] = effb3_fight_tbl[ewk->wu.vital_new][0];
        ewk->wu.scr_mv_x = effb3_fight_tbl[ewk->wu.vital_new][1];
        ewk->wu.xyz[0].disp.pos = effb3_fight_tbl[ewk->wu.vital_new][2];
        ewk->wu.scr_mv_x += bg_w.bgw[1].pos_x_work;
        ewk->wu.xyz[0].disp.pos += bg_w.bgw[1].pos_x_work;
        ewk->wu.xyz[0].disp.low = 0;
        set_char_move_init2(&ewk->wu, 0, 4, ewk->wu.old_rno[0], 0);
        ewk->wu.hit_stop = 8;
        cal_all_speed_data(ewk, ewk->wu.hit_stop, ewk->wu.scr_mv_x, ewk->wu.scr_mv_y, 1, 1);
        break;
    case 1:
        ewk->wu.hit_stop--;
        if (!ewk->wu.hit_stop) {
            ewk->wu.my_mr.size.x = 63;
            ewk->wu.my_mr.size.y = 63;
            if (ewk->wu.vital_new == 5) {
                rf_b2_flag = 1;
            }
            ewk->wu.routine_no[2]++;
        } else {
            add_x_sub(ewk);
            add_y_sub(ewk);
            ewk->wu.my_mr.size.x -= 4;
            ewk->wu.my_mr.size.y -= 4;
        }
        disp_pos_trans_entry5(ewk);
        break;
    case 2:
        disp_pos_trans_entry(ewk);
        break;
    }
}



/* provisional name */
void effB3_kill(WORK_Other* ewk) {
    all_cgps_put_back(ewk);
    push_effect_work(&ewk->wu);
}



s32 effect_B3_init(WORK_Other* wk) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    s16 num;
    const s16* ptr;
    load_any_color(3);
    if (wk->wu.type) {
        ptr = &effb3_final_tbl[0][0];
        num = 10;
    } else {
        ptr = &effb3_round_tbl[0][0];
        num = 6;
    }
    for (i = 0; i < num; i++) {
        if ((ix = pull_effect_work(3)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 113;
        ewk->wu.work_id = 16;
        ewk->wu.vital_new = i;
        ewk->wu.cgromtype = 1;
        ewk->my_master = (u32*)wk;
        ewk->wu.rl_flag = 0;
        ewk->wu.my_family = 2;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 57;
        ewk->wu.my_priority = ewk->wu.position_z = 10;
        ewk->wu.position_y = ewk->wu.scr_mv_y = 128;
        ewk->wu.xyz[1].cal = 0x780000;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = bg_w.bgw[1].pos_x_work;
        ewk->wu.xyz[0].disp.low = 0;
        ewk->wu.char_table[0] = etc_char_table;
        if (wk->wu.type) {
            ewk->wu.hit_quake = 1;
            ewk->wu.old_rno[0] = *ptr++;
            ewk->wu.scr_mv_x = *ptr++;
            ewk->wu.char_index = 5;
        } else {
            ewk->wu.hit_quake = 0;
            ewk->wu.old_rno[0] = *ptr++;
            ewk->wu.scr_mv_x = *ptr++;
            ewk->wu.char_index = 2;
        }
        ewk->wu.scr_mv_x += bg_w.bgw[1].pos_x_work;
    }
    if (wk->wu.type == 0) {
        effect_B9_init(wk);
    }
    return 0;
}
