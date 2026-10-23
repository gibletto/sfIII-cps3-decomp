/*
 * EFF80.C  Effect 80: second companion of the effect 77 stage character
 *
 * effect_80_init (from effect 77, first area only) places the companion at (496, 322) under the
 * effect 82 controller. While the controller is in state 0 it waits until BG 1's Y is above 48 and a
 * player is within 144 dots, then plays its pattern once and hides. When the controller moves to
 * state 1 it waits for the effect 77 character to reach its third step, then flies in from above to a
 * point beside that character's target (eff80_0101) and plays its pattern there. It is freed in the
 * controller's state 2.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "ta_sub.h"
#include "bg_sub_5.h"
#include "CALDIR.h"
#include "Eff80.h"

extern const u32 eff80_char_table[];
void eff80_0000(WORK_Other* ewk);
void eff80_0001(WORK_Other* ewk);
void eff80_0100(WORK_Other* ewk);
void eff80_0101(WORK_Other* ewk);
void eff80_0102(WORK_Other* ewk);
void eff80_0103(WORK_Other* ewk);
void (*eff80_jp_tbl[2])(WORK_Other*) = { eff80_0000, eff80_0001 };
void (*eff80_jp_tbl2[4])(WORK_Other*) = { eff80_0100, eff80_0101, eff80_0102, eff80_0103 };

void effect_80_move(WORK_Other* ewk) {
    WORK_Other* mwk = (WORK_Other*)ewk->my_master;
    switch (mwk->wu.routine_no[0]) {
    case 0:
        if (!EXE_flag && !Game_pause) {
            eff80_jp_tbl[ewk->wu.routine_no[0]](ewk);
        }
        disp_pos_trans_entry_s(ewk);
        break;
    case 1:
        if (!EXE_flag && !Game_pause) {
            eff80_jp_tbl2[ewk->wu.routine_no[1]](ewk);
        }
        disp_pos_trans_entry_rs(ewk);
        break;
    case 2:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

void eff80_0000(WORK_Other* ewk) {
    ewk->wu.routine_no[0]++;
    ewk->wu.disp_flag = 1;
    set_char_move_init(&ewk->wu, 0, 0);
    ewk->wu.my_priority = ewk->wu.position_z = 70;
}

void eff80_0001(WORK_Other* ewk) {
    s16 x0, x1;
    switch (ewk->wu.routine_no[2]) {
    case 0:
        x0 = ewk->wu.xyz[0].disp.pos - plw[0].wu.xyz[0].disp.pos;
        if (x0 < 0) {
            x0 = -x0;
        }
        x1 = ewk->wu.xyz[0].disp.pos - plw[1].wu.xyz[0].disp.pos;
        if (x1 < 0) {
            x1 = -x1;
        }
        if (bg_w.bgw[1].xy[1].disp.pos > 48 && (x0 < 144 || x1 < 144)) {
            ewk->wu.routine_no[2]++;
        }
        break;
    case 1:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[2]++;
            ewk->wu.disp_flag = 0;
        }
        break;
    case 2:
    default:
        break;
    }
}

void eff80_0100(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;
    ewk->wu.disp_flag = 0;
    set_char_move_init(&ewk->wu, 0, 1);
}

void eff80_0101(WORK_Other* ewk) {
    WORK_Other* pwk = (WORK_Other*)ewk->wu.target_adrs;
    if (pwk->wu.routine_no[1] > 2) {
        ewk->wu.routine_no[1]++;
        ewk->wu.my_priority = ewk->wu.position_z = 70;
        ewk->wu.disp_flag = 1;
        ewk->wu.xyz[0].disp.pos = ewk->wu.old_rno[0] = pwk->wu.old_rno[0] + 128;
        ewk->wu.xyz[1].disp.pos = 384;
        ewk->wu.old_rno[1] = pwk->wu.old_rno[1] + 56;
        ewk->wu.old_rno[2] = 128;
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[2], ewk->wu.old_rno[0], ewk->wu.old_rno[1], 1, 2);
    }
}

void eff80_0102(WORK_Other* ewk) {
    add_x_sub(ewk);
    add_y_sub(ewk);
    char_move(&ewk->wu);
    ewk->wu.old_rno[2]--;
    if (ewk->wu.old_rno[2] <= 0) {
        ewk->wu.routine_no[1]++;
    }
}

void eff80_0103(WORK_Other* ewk) {
    char_move(&ewk->wu);
}

s32 effect_80_init(WORK_Other* pwk) {
    WORK_Other* ewk;
    s16 ix;
    if (bg_w.area != 0) {
        return -1;
    }
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 80;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.sync_suzi = 0;
    ewk->my_master = pwk->my_master;
    ewk->wu.target_adrs = (u32*)pwk;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2051;
    ewk->wu.my_priority = ewk->wu.position_z = 70;
    ewk->wu.xyz[0].disp.pos = 496;
    ewk->wu.xyz[1].disp.pos = 322;
    ewk->wu.char_table[0] = eff80_char_table;
    suzi_offset_set(&ewk->wu);
    return 0;
}
