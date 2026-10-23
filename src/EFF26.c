/*
 * EFF26.C  Effect 26: parts of breakable stage objects
 *
 * Effect 26 works belong to an effect 25 object. The eff26_* routines keep them animating
 * while the parent is intact and, when the parent is broken, play their own break animation
 * and throw out pieces (piece_set, effect 27, and effect 28).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "eff28.h"
#include "EFF29.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "EFF27.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFF25.h"
#include "aboutspr.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFF26.h"



/* 02006C74 */
void (*eff26_jp_tbl[6])(WORK_Other*) = {
    eff26_00,
    eff26_01,
    eff26_02,
    eff26_03,
    eff26_04,
    eff26_05,
};
/* Object records for the two part types. */
const s16* scr_obj_data26[2] = {
    (const s16*)&eff26_num[2],
    (const s16*)&eff26_num[19],
};


void effect_26_move(WORK_Other* ewk) {
    WORK_Other* oya;
    if (compel_dead_check(ewk)) {
        ewk->wu.routine_no[0] = 99;
    } else {
        oya = (WORK_Other*)ewk->my_master;
        switch (ewk->wu.routine_no[0]) {
        case 0:
            ewk->wu.routine_no[0]++;
            ewk->wu.routine_no[1] = 0;
            ewk->wu.disp_flag = 1;
            set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
            break;
        case 1:
            if (!EXE_flag && !Game_pause) {
                eff26_jp_tbl[ewk->wu.old_rno[2] / 2](ewk);
            }
            disp_pos_trans_entry_rs(ewk);
            break;
        case 2:
            ewk->wu.routine_no[0]++;
            break;
        default:
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
            break;
        }
    }
}



void eff26_00(WORK_Other* ewk) {
    WORK_Other* self = ewk;
    ewk = (WORK_Other*)self->my_master;
    if (ewk->wu.routine_no[1] > 1) {
        self->wu.routine_no[0] = 2;
        piece_set(self);
        return;
    } else if (self->wu.hit_stop) {
        char_move(&self->wu);
    }
}



void eff26_01(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[0] = 99;
            break;
        }
    case 1:
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        if (oya->wu.routine_no[1] > 1) {
            ewk->wu.routine_no[1]++;
            piece_set(ewk);
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
        }
        break;
    case 2:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[0] = 2;
        }
        break;
    }
}



void eff26_02(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[1] = 3;
            ewk->wu.disp_flag = 1;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[7]);
            break;
        }
    case 1:
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        if (oya->wu.routine_no[1] > 1) {
            ewk->wu.routine_no[1]++;
            piece_set(ewk);
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
        }
        break;
    case 2:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case 3:
        char_move(&ewk->wu);
        break;
    }
}

void eff26_03(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;

    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[1] = 3;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
            goto case_3;
        }
    case 1:
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        if (oya->wu.routine_no[1] > 1) {
            ewk->wu.routine_no[1]++;
            piece_set(ewk);
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
            return;
        }
        break;
    case 2:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case 3:
    case_3:
        ewk->wu.routine_no[1]++;
        if (eff_hit_flag[ewk->wu.type]) {
            ewk->wu.routine_no[0] = 99;
            break;
        }
        ewk->wu.disp_flag = 1;
    case 4:
        if (eff_hit_check(ewk, ewk->wu.old_rno[4])) {
            if (ewk->wu.old_rno[2] & 1) {
                if (ewk->wu.old_rno[5] > 0) {
                    effect_27_init(ewk, ewk->wu.old_rno[5]);
                }
            }
            ewk->wu.routine_no[0] = 2;
        }
        break;
    }
}



void eff26_04(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;
    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[1] = 2;
            goto case_2;
        }
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        if (oya->wu.routine_no[1] > 1) {
            ewk->wu.routine_no[1]++;
            piece_set(ewk);
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
        }
        break;
    case 1:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case 2:
    case_2:
        ewk->wu.routine_no[1]++;
        if (eff_hit_flag[ewk->wu.type]) {
            ewk->wu.routine_no[0] = 99;
            break;
        }
    case 3:
        if (eff_hit_check(ewk, ewk->wu.old_rno[4])) {
            ewk->wu.routine_no[1]++;
            if (ewk->wu.old_rno[2] & 1) {
                if (ewk->wu.old_rno[5] > 0) {
                    effect_27_init(ewk, ewk->wu.old_rno[5]);
                }
            }
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[3]);
        }
    case 4:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[0] = 2;
        }
        break;
    }
}



void eff26_05(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;

    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[2] = 3;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
            goto case_3;
        }
    case 1:
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        if (oya->wu.routine_no[1] > 1) {
            ewk->wu.routine_no[1]++;
            piece_set(ewk);
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
        }
        break;
    case 2:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case 3:
    case_3:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        if (eff_hit_flag[ewk->wu.type]) {
            ewk->wu.routine_no[1] = 7;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[7]);
            break;
        }
    case 4:
        if (eff_hit_check(ewk, ewk->wu.old_rno[4])) {
            ewk->wu.routine_no[1]++;
            if (ewk->wu.old_rno[2] & 1) {
                if (ewk->wu.old_rno[5] > 0) {
                    effect_27_init(ewk, ewk->wu.old_rno[5]);
                }
            }
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[3]);
        }
        break;
    case 5:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case 6:
        break;
    case 7:
        char_move(&ewk->wu);
        break;
    }
}



/* char_add by stage and area */
s32 effect_26_init(WORK_Other* oya, s16 type26) {
    WORK_Other* ewk;
    s16 ix;
    s16 lp_cnt = eff26_num[type26];
    s16 i;
    const s16* data_ptr;
    if (lp_cnt) {
        if (!type26) {
            effect_28_init(oya);
        }
        data_ptr = scr_obj_data26[type26];
        for (i = 0; i < lp_cnt; i++) {
            if ((ix = pull_effect_work(4)) == -1) {
                return -1;
            }
            ewk = (WORK_Other*)frw[ix];
            ewk->wu.be_flag = 1;
            ewk->wu.id = 26;
            ewk->wu.work_id = 16;
            ewk->my_master = (u32*)oya;
            ewk->wu.cgromtype = 1;
            ewk->wu.rl_flag = 0;
            ewk->wu.my_col_mode = 0x4200;
            ewk->wu.dead_f = *data_ptr++;
            ewk->wu.type = (s8)*data_ptr++;
            ewk->wu.my_family = *data_ptr++;
            ewk->wu.my_col_code = *data_ptr++;
            ewk->wu.xyz[0].disp.pos = *data_ptr++;
            ewk->wu.xyz[1].disp.pos = *data_ptr++;
            ewk->wu.position_z = *data_ptr++;
            ewk->wu.char_index = *data_ptr++;
            ewk->wu.hit_stop = *data_ptr++;
            ewk->wu.sync_suzi = *data_ptr++;
            ewk->wu.old_rno[0] = *data_ptr++;
            ewk->wu.old_rno[1] = *data_ptr++;
            ewk->wu.old_rno[2] = *data_ptr++;
            ewk->wu.old_rno[3] = *data_ptr++;
            ewk->wu.old_rno[7] = *data_ptr++;
            ewk->wu.old_rno[4] = *data_ptr++;
            ewk->wu.old_rno[5] = *data_ptr++;
            ewk->wu.char_table[0] = char_add[bg_w.stage][bg_w.area];
            suzi_offset_set((WORK*)ewk);
        }
        return 0;
    }
}
