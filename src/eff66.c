/*
 * EFF66.C  Effect 66: reacting stage objects
 *
 * Effect 66 objects react when a player comes near (eff66_00..03).
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
#include "PLS02.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "eff66.h"



/* 02006D78 */
void (*eff66_jp_tbl[4])(WORK_Other*) = {
    eff66_00,
    eff66_01,
    eff66_02,
    eff66_03,
};


void effect_66_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.routine_no[2] = 0;
        break;
    case 1:
        if (compel_dead_check(ewk)) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (!EXE_flag && !Game_pause) {
            eff66_jp_tbl[ewk->wu.routine_no[1]](ewk);
        }
        if (!ewk->wu.old_rno[2] || range_x_check(&ewk->wu)) {
            disp_pos_trans_entry_s(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



/* provisional name */
void eff66_00(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.routine_no[2]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[0]);
        break;
    case 1:
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        if (range_abs_check(plw[0].wu.position_x, ewk->wu.position_x, 32) ||
            range_abs_check(plw[1].wu.position_x, ewk->wu.position_x, 32)) {
            ewk->wu.routine_no[2]++;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
        }
        break;
    case 2:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[2] = 0;
        }
        break;
    }
}



/* provisional name */
void eff66_01(WORK_Other* ewk) {}



void eff66_02(WORK_Other* ewk) {}



void eff66_03(WORK_Other* ewk) {
    s16 bg_x;
    s16 right;
    s16 left;
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.routine_no[2]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[0]);
        break;
    case 1:
        char_move(&ewk->wu);
        if (range_abs_check(plw[0].wu.xyz[0].disp.pos, ewk->wu.xyz[0].disp.pos, 16) ||
            range_abs_check(plw[1].wu.xyz[0].disp.pos, ewk->wu.xyz[0].disp.pos, 16)) {
            ewk->wu.routine_no[2]++;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
        }
        break;
    case 2:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[2]++;
        }
        break;
    case 3:
        bg_x = bg_w.bgw[ewk->wu.my_family - 1].xy[0].disp.pos;
        right = bg_x + 288;
        left = bg_x - 288;
        if (ewk->wu.xyz[0].disp.pos > right || ewk->wu.xyz[0].disp.pos < left) {
            ewk->wu.routine_no[2] = 0;
        }
        break;
    }
}



/* char_add by stage and area */
s32 effect_66_init(s16 type) {
    WORK_Other* ewk;
    s16 ix;
    const s16* data_ptr = eff66_data_tbl[type];
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 66;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.dead_f = *data_ptr++;
    ewk->wu.my_family = *data_ptr++;
    ewk->wu.my_col_code = *data_ptr++;
    ewk->wu.xyz[0].disp.pos = *data_ptr++;
    ewk->wu.xyz[1].disp.pos = *data_ptr++;
    ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
    ewk->wu.old_rno[0] = *data_ptr++;
    ewk->wu.hit_stop = *data_ptr++;
    ewk->wu.sync_suzi = *data_ptr++;
    ewk->wu.routine_no[1] = *data_ptr++;
    ewk->wu.old_rno[1] = *data_ptr++;
    ewk->wu.old_rno[2] = *data_ptr;
    ewk->wu.char_table[0] = char_add[bg_w.stage][bg_w.area];
    suzi_offset_set(&ewk->wu);
    return 0;
}
