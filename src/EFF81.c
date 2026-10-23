/*
 * EFF81.C  Effect 81: three more companions of the effect 77 stage character
 *
 * effect_81_init (nothing calls it; first area only) creates three companions under the given work's
 * master. When that master moves to state 1 they wait for the given work to reach its third step, then
 * each takes its pattern, priority and offset from eff81_data_tbl and flies to its place beside that
 * work's target over 103 frames. They are freed in the master's state 2. eff81_area1 and eff81_0104
 * are not used.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Eff81.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "ta_sub.h"
#include "bg_sub_5.h"
#include "CALDIR.h"

extern const u32 eff81_char_table[];
extern const s16 eff81_data_tbl[3][4];
void eff81_0000(WORK_Other* ewk);
void eff81_0001(WORK_Other* ewk);
void eff81_0100(WORK_Other* ewk);
void eff81_0101(WORK_Other* ewk);
void eff81_0102(WORK_Other* ewk);
void eff81_0103(WORK_Other* ewk);
void (*eff81_jp_tbl[2])(WORK_Other*) = { eff81_0000, eff81_0001 };
void (*eff81_jp_tbl2[4])(WORK_Other*) = { eff81_0100, eff81_0101, eff81_0102, eff81_0103 };

void effect_81_move(WORK_Other* ewk) {
    WORK_Other* mwk = (WORK_Other*)ewk->my_master;
    switch (mwk->wu.routine_no[0]) {
    case 0:
        break;
    case 1:
        if (!EXE_flag && !Game_pause) {
            eff81_jp_tbl2[ewk->wu.routine_no[1]](ewk);
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

void eff81_0000(WORK_Other* ewk) {
    ewk->wu.routine_no[0]++;
    ewk->wu.my_priority = ewk->wu.position_z = 70;
}

void eff81_0001(WORK_Other* ewk) {
}

void eff81_0100(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;
}

void eff81_0101(WORK_Other* ewk) {
    WORK_Other* pwk = (WORK_Other*)ewk->wu.target_adrs;
    const s16* data;
    if (pwk->wu.routine_no[1] > 2) {
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        data = eff81_data_tbl[ewk->wu.type];
        ewk->wu.char_index = *data++;
        ewk->wu.my_priority = ewk->wu.position_z = *data++;
        ewk->wu.old_rno[0] = *data++;
        ewk->wu.old_rno[1] = *data;
        ewk->wu.old_rno[0] += pwk->wu.old_rno[0];
        ewk->wu.old_rno[1] += pwk->wu.old_rno[1] - 16;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        ewk->wu.old_rno[2] = 103;
        cal_all_speed_data(&ewk->wu, 103, ewk->wu.old_rno[0], ewk->wu.old_rno[1], 1, 1);
    }
}

void eff81_0102(WORK_Other* ewk) {
    add_x_sub(ewk);
    add_y_sub(ewk);
    ewk->wu.old_rno[2]--;
    if (ewk->wu.old_rno[2] <= 0) {
        ewk->wu.routine_no[1]++;
    }
}

void eff81_0103(WORK_Other* ewk) {
}

void eff81_area1(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 2);
        ewk->wu.xyz[0].disp.pos = 512;
        ewk->wu.xyz[1].disp.pos = 40;
        break;
    case 1:
        char_move(&ewk->wu);
        if (range_x_check(&ewk->wu)) {
            suzi_sync_pos_set(ewk);
            sort_push_request4(&ewk->wu);
        }
        break;
    default:
        break;
    }
}

void eff81_0104(WORK_Other* ewk) {
    char_move(&ewk->wu);
}

s32 effect_81_init(WORK_Other* pwk) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    if (bg_w.area != 0) {
        return -1;
    }
    for (i = 0; i < 3; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->my_master = pwk->my_master;
        ewk->wu.target_adrs = (u32*)pwk;
        ewk->wu.be_flag = 1;
        ewk->wu.id = 81;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.sync_suzi = 0;
        ewk->wu.type = i;
        ewk->wu.my_family = 2;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2051;
        ewk->wu.char_table[0] = eff81_char_table;
        ewk->wu.xyz[0].disp.pos = 512;
        ewk->wu.xyz[1].disp.pos = 368;
        suzi_offset_set(&ewk->wu);
    }
    return 0;
}
