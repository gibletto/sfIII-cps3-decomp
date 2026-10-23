/*
 * EFF25.C  Effect 25: breakable stage objects (bg130)
 *
 * Effect 25 objects can be hit by the players. Behaviour routines (eff25_jp_tbl) check for a
 * hit with eff_hit_check, play the break animation and throw out pieces with piece_set
 * (effect 27); eff_hit_flag remembers objects already broken. effect_25_init is called from
 * bg130 and creates effect 26 child parts.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "EFF26.h"
#include "EFF27.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFF25.h"



extern const s16 scr_obj_data25_0[];
extern const s16 scr_obj_data25_1[];
extern const s16 scr_obj_data25_2[];
extern const s16 scr_obj_data25_3[];
extern const s16 scr_obj_data25_4[];

/* 02007C74 */
const s16* scr_obj_data25[9] = {
    scr_obj_data25_0,
    scr_obj_data25_1,
    scr_obj_data25_2,
    scr_obj_data25_3,
    scr_obj_data25_4,
    scr_obj_data25_4,
    scr_obj_data25_4,
    scr_obj_data25_4,
    scr_obj_data25_4,
};
/* 02007C98 */
void (*eff25_jp_tbl[8])(WORK_Other* ewk) = {
    eff25_00,
    eff25_00,
    eff25_02,
    eff25_02,
    eff25_08,
    eff25_08,
    eff25_06,
    eff25_06,
};


void effect_25_move(WORK_Other* ewk) {
    if (compel_dead_check(ewk)) {
        ewk->wu.routine_no[0] = 99;
    } else {
        switch (ewk->wu.routine_no[0]) {
        case 0:
            if (!EXE_flag && !Game_pause) {
                eff25_jp_tbl[ewk->wu.old_rno[2]](ewk);
            }
            disp_pos_trans_entry_rs(ewk);
            break;
        case 1:
        case 2:
        case 3:
            ewk->wu.routine_no[0]++;
            break;
        case 4:
        default:
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
            break;
        }
    }
}

void eff25_00(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (eff_hit_flag[ewk->wu.type]) {
            ewk->wu.routine_no[0] = 4;
            break;
        }
        eff25_char_set(ewk);
        break;
    case 1:
        if (eff_hit_check(ewk, ewk->wu.old_rno[4])) {
            piece_set(ewk);
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
            ewk->wu.routine_no[1]++;
            break;
        }
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        break;
    case 2:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[1]++;
        }
        /* fall through */
    case 3:
        ewk->wu.routine_no[0]++;
        break;
    }
}



void eff25_02(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (eff_hit_flag[ewk->wu.type]) {
            ewk->wu.disp_flag = 1;
            ewk->wu.routine_no[1] = 4;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[7]);
            break;
        }
        eff25_char_set(ewk);
        break;
    case 1:
        if (eff_hit_check(ewk, ewk->wu.old_rno[4])) {
            piece_set(ewk);
            ewk->wu.routine_no[1]++;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
            break;
        }
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        break;
    case 2:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case 3:
        break;
    case 4:
        char_move(&ewk->wu);
        break;
    }
}



void eff25_08(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (eff_hit_flag[ewk->wu.type]) {
            ewk->wu.routine_no[0] = 4;
            break;
        }
        eff25_char_set(ewk);
        break;
    case 1:
        if (eff_hit_check(ewk, ewk->wu.old_rno[4])) {
            piece_set(ewk);
            ewk->wu.routine_no[1]++;
            break;
        }
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        break;
    case 2:
        ewk->wu.routine_no[0]++;
        break;
    }
}



void eff25_06(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (eff_hit_flag[ewk->wu.type]) {
            ewk->wu.disp_flag = 1;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[7]);
            ewk->wu.routine_no[1] = 4;
            break;
        }
        eff25_char_set(ewk);
        return;
    case 1:
        if (eff_hit_check(ewk, ewk->wu.old_rno[4])) {
            piece_set(ewk);
            ewk->wu.routine_no[1]++;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
            break;
        }
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        break;
    case 2:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[3]);
            ewk->wu.routine_no[1]++;
        }
        break;
    case 4:
        char_move(&ewk->wu);
        break;
    case 3:
        break;
    }
}






void eff25_char_set(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;
    ewk->wu.disp_flag = 1;
    set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
}



void piece_set(WORK_Other* ewk) {
    if (!(ewk->wu.old_rno[2] & 1)) {
        return;
    }
    if (ewk->wu.old_rno[0] < 0) {
        return;
    }
    effect_27_init(ewk, ewk->wu.old_rno[0]);
}



s32 effect_25_init(s8 num) {
    WORK_Other* ewk;
    s16 ix;
    const s16* data_ptr = scr_obj_data25[num];
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 25;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.type = num;
    ewk->wu.dead_f = *data_ptr++;
    ewk->wu.my_family = *data_ptr++;
    ewk->wu.my_col_code = *data_ptr++;
    ewk->wu.xyz[0].disp.pos = *data_ptr++;
    ewk->wu.xyz[1].disp.pos = *data_ptr++;
    ewk->wu.my_priority = *data_ptr++;
    ewk->wu.char_index = *data_ptr++;
    ewk->wu.hit_stop = *data_ptr++;
    ewk->wu.sync_suzi = *data_ptr++;
    ewk->wu.old_rno[0] = *data_ptr++;
    ewk->wu.old_rno[1] = *data_ptr++;
    ewk->wu.old_rno[7] = *data_ptr++;
    ewk->wu.old_rno[3] = *data_ptr++;
    ewk->wu.old_rno[2] = *data_ptr++;
    ewk->wu.old_rno[4] = *data_ptr++;
    ewk->wu.position_z = ewk->wu.my_priority;
    if (*data_ptr >= 0) {
        effect_26_init(ewk, *data_ptr);
    }
    *data_ptr++;
    ewk->wu.char_table[0] = char_add[bg_w.stage][bg_w.area];
    suzi_offset_set(&ewk->wu);
    return 0;
}
