/*
 * EFF78.C  Effect 78: companion of the effect 77 stage character
 *
 * effect_78_init (from effect 77) places the companion at (512, 51). In the first area it plays its
 * idle pattern while the effect 82 controller waits; when the controller moves to state 1 it plays
 * pattern 2 for 40 frames and vanishes, and 72 frames later flies in from above to 80 dots beside the
 * effect 77 character's target, where it plays pattern 3. It is freed in the controller's state 2. In
 * the later areas it only plays pattern 4 in place.
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
#include "CALDIR.h"
#include "bg_sub_5.h"

/* routine_no[0], later areas */
#define R0_INIT         0       /* show in place */
#define R0_MOVE         1       /* animate */

extern const u32 eff78_char_table[];
void eff78_area0(WORK_Other* ewk);
void eff78_area1(WORK_Other* ewk);
void eff78_0000(WORK_Other* ewk);
void eff78_0001(WORK_Other* ewk);
void eff78_0100(WORK_Other* ewk);
void eff78_0101(WORK_Other* ewk);
void eff78_0102(WORK_Other* ewk);
void eff78_0103(WORK_Other* ewk);
void eff78_0104(WORK_Other* ewk);

void (*eff78_jp_tbl[2])(WORK_Other*) = { eff78_0000, eff78_0001 };
void (*eff78_jp_tbl2[5])(WORK_Other*) = {
    eff78_0100, eff78_0101, eff78_0102, eff78_0103, eff78_0104,
};

void effect_78_move(WORK_Other* ewk) {
    if (bg_w.area) {
        eff78_area1(ewk);
    } else {
        eff78_area0(ewk);
    }
}

void eff78_area0(WORK_Other* ewk) {
    WORK_Other* mwk = (WORK_Other*)ewk->my_master;
    switch (mwk->wu.routine_no[0]) {
    case 0:
        if (!EXE_flag && !Game_pause) {
            eff78_jp_tbl[ewk->wu.routine_no[0]](ewk);
        }
        disp_pos_trans_entry_rs(ewk);
        break;
    case 1:
        if (!EXE_flag && !Game_pause) {
            eff78_jp_tbl2[ewk->wu.routine_no[1]](ewk);
        }
        disp_pos_trans_entry_rs(ewk);
        break;
    case 2:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
}

void eff78_0000(WORK_Other* ewk) {
    ewk->wu.routine_no[0]++;
    ewk->wu.disp_flag = 1;
    set_char_move_init(&ewk->wu, 0, 0);
    ewk->wu.my_priority = ewk->wu.position_z = 71;
}

void eff78_0001(WORK_Other* ewk) {
    char_move(&ewk->wu);
}

void eff78_0100(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;
    set_char_move_init(&ewk->wu, 0, 2);
    ewk->wu.my_priority = ewk->wu.position_z = 69;
    ewk->wu.old_rno[2] = 40;
}

void eff78_0101(WORK_Other* ewk) {
    ewk->wu.old_rno[2]--;
    if (ewk->wu.old_rno[2] < 0) {
        ewk->wu.disp_flag = 0;
        ewk->wu.routine_no[1]++;
        ewk->wu.old_rno[2] = 72;
    }
    if (!ewk->wu.cg_type) {
        char_move(&ewk->wu);
    } else {
        ewk->wu.disp_flag = 0;
    }
}

void eff78_0102(WORK_Other* ewk) {
    WORK_Other* pwk = (WORK_Other*)ewk->wu.target_adrs;
    ewk->wu.old_rno[2]--;
    if (ewk->wu.old_rno[2] < 0) {
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.xyz[0].disp.pos = ewk->wu.old_rno[0] = pwk->wu.old_rno[0] + 80;
        ewk->wu.xyz[1].disp.pos = 384;
        ewk->wu.old_rno[1] = 72;
        ewk->wu.old_rno[2] = 28;
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[2], ewk->wu.old_rno[0], ewk->wu.old_rno[1], 1, 1);
        set_char_move_init(&ewk->wu, 0, 3);
    }
}

void eff78_0103(WORK_Other* ewk) {
    add_x_sub(ewk);
    add_y_sub(ewk);
    ewk->wu.old_rno[2]--;
    if (ewk->wu.old_rno[2] <= 0) {
        ewk->wu.routine_no[1]++;
        set_char_move_init2(&ewk->wu, 0, 3, 2, 0);
    }
}

void eff78_0104(WORK_Other* ewk) {
    char_move(&ewk->wu);
}

void eff78_area1(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 4);
        ewk->wu.xyz[0].disp.pos = 512;
        ewk->wu.xyz[1].disp.pos = 51;
        ewk->wu.my_priority = ewk->wu.position_z = 71;
        break;
    case R0_MOVE:
        char_move(&ewk->wu);
        suzi_sync_pos_set(ewk);
        sort_push_request4(&ewk->wu);
        break;
    default:
        break;
    }
}

s32 effect_78_init(WORK_Other* pwk) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->my_master = pwk->my_master;
    ewk->wu.target_adrs = (u32*)pwk;
    ewk->wu.be_flag = 1;
    ewk->wu.id = 78;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.sync_suzi = 0;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2051;
    *ewk->wu.char_table = eff78_char_table;
    ewk->wu.xyz[0].disp.pos = 512;
    ewk->wu.xyz[1].disp.pos = 51;
    suzi_offset_set(&ewk->wu);
    return 0;
}
