/*
 * EFF79.C  Effect 79: first companion of the effect 77 stage character
 *
 * effect_79_init (from effect 77, first area only) places the companion at (480, 51) under the
 * effect 82 controller. While the controller is in state 0 it plays its idle pattern. When the
 * controller moves to state 1 it runs a short scene (eff79_0100 to eff79_0108): it rises out of sight,
 * reappears and flies down beside the losing player (the controller's master_id), plays its patterns
 * there and flies back up. It is freed in the controller's state 2.
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
#include "Eff79.h"

extern const u32 eff79_char_table[];
void eff79_0000(WORK_Other* ewk);
void eff79_0001(WORK_Other* ewk);
void eff79_0100(WORK_Other* ewk);
void eff79_0101(WORK_Other* ewk);
void eff79_0102(WORK_Other* ewk);
void eff79_0103(WORK_Other* ewk);
void eff79_0104(WORK_Other* ewk);
void eff79_0105(WORK_Other* ewk);
void eff79_0106(WORK_Other* ewk);
void eff79_0107(WORK_Other* ewk);
void eff79_0108(WORK_Other* ewk);

void (*eff79_jp_tbl[2])(WORK_Other*) = { eff79_0000, eff79_0001 };
void (*eff79_jp_tbl2[9])(WORK_Other*) = {
    eff79_0100, eff79_0101, eff79_0102, eff79_0103, eff79_0104,
    eff79_0105, eff79_0106, eff79_0107, eff79_0108,
};

void effect_79_move(WORK_Other* ewk) {
    WORK_Other* mwk = (WORK_Other*)ewk->my_master;
    switch (mwk->wu.routine_no[0]) {
    case 0:
        if (!EXE_flag && !Game_pause) {
            eff79_jp_tbl[ewk->wu.routine_no[0]](ewk);
        }
        disp_pos_trans_entry_rs(ewk);
        break;
    case 1:
        if (!EXE_flag && !Game_pause) {
            eff79_jp_tbl2[ewk->wu.routine_no[1]](ewk);
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

void eff79_0000(WORK_Other* ewk) {
    ewk->wu.routine_no[0]++;
    ewk->wu.disp_flag = 1;
    set_char_move_init(&ewk->wu, 0, 0);
    ewk->wu.my_priority = ewk->wu.position_z = 70;
}

void eff79_0001(WORK_Other* ewk) {
    char_move(&ewk->wu);
}

void eff79_0100(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;
    set_char_move_init(&ewk->wu, 0, 1);
    ewk->wu.my_priority = ewk->wu.position_z = 68;
}

void eff79_0101(WORK_Other* ewk) {
    char_move(&ewk->wu);
    if (ewk->wu.cg_type) {
        ewk->wu.routine_no[1]++;
        ewk->wu.mvxy.a[1].sp = 0x80000;
        ewk->wu.mvxy.d[1].sp = 0x2000;
        ewk->wu.old_rno[2] = 32;
    }
}

void eff79_0102(WORK_Other* ewk) {
    char_move(&ewk->wu);
    add_x_sub(ewk);
    add_y_sub(ewk);
    ewk->wu.old_rno[2]--;
    if (ewk->wu.old_rno[2] < 0) {
        ewk->wu.disp_flag = 0;
        ewk->wu.routine_no[1]++;
        ewk->wu.old_rno[2] = 16;
    }
}

void eff79_0103(WORK_Other* ewk) {
    WORK_Other* mwk = (WORK_Other*)ewk->my_master;
    ewk->wu.old_rno[2]--;
    if (ewk->wu.old_rno[2] < 0) {
        ewk->wu.routine_no[1]++;
        set_char_move_init(&ewk->wu, 0, 2);
        ewk->wu.disp_flag = 1;
        ewk->wu.old_rno[0] = plw[mwk->master_id].wu.xyz[0].disp.pos - 64;
        ewk->wu.old_rno[1] = 64;
        ewk->wu.old_rno[2] = 24;
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[2], ewk->wu.old_rno[0], ewk->wu.old_rno[1], 1, 1);
    }
}

void eff79_0104(WORK_Other* ewk) {
    add_x_sub(ewk);
    add_y_sub(ewk);
    ewk->wu.old_rno[2]--;
    if (ewk->wu.old_rno[2] <= 0) {
        ewk->wu.routine_no[1]++;
        set_char_move_init(&ewk->wu, 0, 3);
    }
}

void eff79_0105(WORK_Other* ewk) {
    char_move(&ewk->wu);
    if (ewk->wu.cg_type == 2) {
        ewk->wu.routine_no[1]++;
        ewk->wu.old_rno[2] = 16;
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[2], ewk->wu.xyz[0].disp.pos, 152, 1, 1);
    }
}

void eff79_0106(WORK_Other* ewk) {
    char_move(&ewk->wu);
    add_y_sub(ewk);
    ewk->wu.old_rno[2]--;
    if (ewk->wu.old_rno[2] <= 0) {
        ewk->wu.routine_no[1]++;
        set_char_move_init(&ewk->wu, 0, 4);
        ewk->wu.old_rno[2] = 16;
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[2], ewk->wu.old_rno[0], ewk->wu.old_rno[1], 1, 1);
    }
}

void eff79_0107(WORK_Other* ewk) {
    char_move(&ewk->wu);
    if (ewk->wu.cg_type) {
        add_y_sub(ewk);
        ewk->wu.old_rno[2]--;
        if (ewk->wu.old_rno[2] <= 0) {
            ewk->wu.routine_no[1]++;
            set_char_move_init2(&ewk->wu, 0, 4, 6, 0);
        }
    }
}

void eff79_0108(WORK_Other* ewk) {
    char_move(&ewk->wu);
}

s32 effect_79_init(WORK_Other* mwk) {
    WORK_Other* ewk;
    s16 ix;
    if (bg_w.area != 0) {
        return -1;
    }
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->my_master = mwk->my_master;
    ewk->wu.target_adrs = (u32*)mwk;
    ewk->wu.be_flag = 1;
    ewk->wu.id = 79;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.sync_suzi = 0;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 81;
    ewk->wu.char_table[0] = eff79_char_table;
    ewk->wu.xyz[0].disp.pos = 480;
    ewk->wu.xyz[1].disp.pos = 51;
    suzi_offset_set(&ewk->wu);
    return 0;
}
