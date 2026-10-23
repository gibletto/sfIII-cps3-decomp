/*
 * EFFH5.C  Effect H5: ending objects
 *
 * Effect H5 objects read family, colour, pattern, position, priority and behaviour from
 * effH5_data_tbl; effH5_0000..0004 give a still frame, a loop, a single play, a bobbing flight
 * and a two-step move into place. They are freed when the ending scene changes.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "ta_sub.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "end_main.h"
#include "effh5.h"

extern const u32 effH3_char_table[];   /* provisional name (EFFH3.c) */



void effect_H5_move(WORK_Other* ewk) {
    void (*H5_Jmp_Tbl[5])(WORK_Other*) = { effH5_0000, effH5_0001, effH5_0002, effH5_0003, effH5_0004 };
    H5_Jmp_Tbl[ewk->wu.routine_no[0]](ewk);
}



void effH5_0000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effH5_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;
    case 1:
        if (ewk->wu.old_rno[0] != end_w.r_no_2) {
            ewk->wu.routine_no[1] = 99;
        } else {
            disp_pos_trans_entry(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



void effH5_0001(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effH5_init_common(ewk);
        break;
    case 1:
        if (ewk->wu.old_rno[0] != end_w.r_no_2) {
            ewk->wu.routine_no[1] = 99;
            break;
        }
        char_move(&ewk->wu);
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



void effH5_0002(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effH5_init_common(ewk);
        break;
    case 1:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[1]++;
            break;
        }
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



void effH5_0003(WORK_Other* ewk) {
    if (ewk->wu.old_rno[0] != end_w.r_no_2) {
        ewk->wu.routine_no[1] = 99;
    }
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effH5_init_common(ewk);
        ewk->wu.old_rno[5] = 20;
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[5], 512, 56, 1, 1);
        disp_pos_trans_entry(ewk);
        break;
    case 1:
        if (bg_w.bgw[0].r_no_1 == 2) {
            ewk->wu.routine_no[1]++;
            char_move_z(&ewk->wu);
        }
        disp_pos_trans_entry(ewk);
        break;
    case 2:
        ewk->wu.old_rno[5]--;
        if (ewk->wu.old_rno[5] <= 0) {
            ewk->wu.routine_no[1]++;
            ewk->wu.old_rno[5] = 16;
            cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[5], 512, 40, 1, 1);
        } else {
            add_x_sub(ewk);
            add_y_sub(ewk);
        }
        char_move(&ewk->wu);
        disp_pos_trans_entry(ewk);
        break;
    case 3:
        ewk->wu.old_rno[5]--;
        if (ewk->wu.old_rno[5] <= 0) {
            ewk->wu.routine_no[1]--;
            ewk->wu.old_rno[5] = 16;
            cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[5], 512, 56, 1, 1);
        } else {
            add_x_sub(ewk);
            add_y_sub(ewk);
        }
        char_move(&ewk->wu);
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



void effH5_0004(WORK_Other* ewk) {
    if (ewk->wu.old_rno[0] != end_w.r_no_2) {
        ewk->wu.routine_no[1] = 99;
    }
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effH5_init_common(ewk);
        break;
    case 1:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[1]++;
            ewk->wu.my_priority = ewk->wu.position_z = 85;
            ewk->wu.old_rno[5] = 20;
            cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[5], 474, 131, 1, 1);
            disp_pos_trans_entry(ewk);
            return;
        } else {
            disp_pos_trans_entry(ewk);
            return;
        }
    case 2:
        ewk->wu.old_rno[5]--;
        if (ewk->wu.old_rno[5] <= 0) {
            ewk->wu.routine_no[1]++;
            ewk->wu.old_rno[5] = 40;
            cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[5], 484, 141, 1, 1);
            char_move_z(&ewk->wu);
        } else {
            add_x_sub(ewk);
            add_y_sub(ewk);
        }
        disp_pos_trans_entry(ewk);
        break;
    case 3:
        ewk->wu.old_rno[5]--;
        if (ewk->wu.old_rno[5] <= 0) {
            ewk->wu.routine_no[1]++;
        } else {
            add_x_sub(ewk);
            add_y_sub(ewk);
        }
    case 4:
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



/* provisional name */
void effH5_init_common(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;
    ewk->wu.disp_flag = 1;
    set_char_move_init2(&ewk->wu, 0, ewk->wu.old_rno[4], ewk->wu.char_index, 0);
}



/* sets char_table[0] (effH3_char_table) */
s32 effect_H5_init(u8 type) {
    WORK_Other* ewk;
    s16 ix;
    const s16* data_ptr;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.id = 175;
    ewk->wu.be_flag = 1;
    ewk->wu.type = type;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.old_rno[0] = end_w.r_no_2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.char_table[0] = effH3_char_table;
    data_ptr = effH5_data_tbl[type];
    ewk->wu.my_family = *data_ptr++;
    ewk->wu.my_col_code = *data_ptr++;
    ewk->wu.old_rno[4] = *data_ptr++;
    ewk->wu.xyz[0].disp.pos = *data_ptr++;
    ewk->wu.xyz[1].disp.pos = *data_ptr++;
    ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
    ewk->wu.char_index = *data_ptr++;
    ewk->wu.old_rno[1] = ewk->wu.char_index - 1;
    ewk->wu.routine_no[0] = *data_ptr;
    return 0;
}
