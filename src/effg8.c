/*
 * EFFG8.C  Effect G8 (168): the ending's flying birds
 *
 * effect_G8_init makes sixteen birds in four groups of four from effg8_data_tbl (x, y, priority,
 * pattern, height timer) with the group's speeds from effg8_speed_tbl. effect_G8_move flies them
 * across; every 60 frames the group speeds up (dir_step), and a bird leaving the screen re-enters
 * at a position from effg8_pos_tbl. All of them go when the ending scene (end_w.r_no_2) passes 7.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "effg8.h"

/* routine_no[1] */
#define R1_INIT         0       /* start the pattern and the climb */
#define R1_FLY          1       /* fly across, speeding up */
#define R1_KILL         99      /* (default) put the work back */

extern const s16 effg8_data_tbl[16][5];
extern const s32 effg8_speed_tbl[4][2];
extern const s8 effg8_pos_ix_tbl[4][4][4];
extern const s16 effg8_pos_tbl[8];



void effect_G8_move(WORK_Other* ewk) {
    s8 ix;
    if (end_w.r_no_2 > 7) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        ewk->wu.mvxy.d[1].sp = 0;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.old_rno[4], ewk->wu.char_index, 0);
        cal_initial_speed_y(&ewk->wu, ewk->wu.old_rno[5], ewk->wu.old_rno[2]);
        ewk->wu.old_rno[3] = 0;
        ewk->wu.dir_step = 0;
        disp_pos_trans_entry(ewk);
        break;
    case R1_FLY:
        ewk->wu.old_rno[3]++;
        if (ewk->wu.old_rno[3] > 60) {
            if (ewk->wu.dir_step < 3) {
                ewk->wu.dir_step++;
            } else {
                ewk->wu.mvxy.d[0].sp = 0;
            }
            ewk->wu.old_rno[3] = 0;
        }
        add_x_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos > 0x380 || ewk->wu.xyz[0].disp.pos < 127) {
            ix = effg8_pos_ix_tbl[ewk->wu.dir_step][ewk->wu.type][ewk->wu.old_rno[6]];
            ewk->wu.xyz[0].disp.pos = effg8_pos_tbl[ix];
            ewk->wu.xyz[0].disp.low = 0;
        }
        ewk->wu.old_rno[5]--;
        if (ewk->wu.old_rno[5] > 0) {
            add_y_sub(ewk);
        }
        /* fall through */
    case 2:
        if (range_x_check(&ewk->wu) == 0) {
            return;
        }
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_G8_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data_ptr = effg8_data_tbl[0];
    for (i = 0; i < 16; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.id = 168;
        ewk->wu.be_flag = 1;
        ewk->wu.type = (u8)i / 4;
        ewk->wu.old_rno[6] = i % 4;
        ewk->wu.old_rno[7] = i;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.char_table[0] = effH3_char_table;
        ewk->wu.my_family = 2;
        ewk->wu.my_col_code = 32;
        ewk->wu.old_rno[4] = 14;
        ewk->wu.xyz[0].disp.pos = *data_ptr++;
        ewk->wu.xyz[1].disp.pos = *data_ptr++;
        ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
        ewk->wu.char_index = *data_ptr++;
        ewk->wu.old_rno[1] = ewk->wu.char_index - 1;
        ewk->wu.old_rno[2] = *data_ptr++;
        ewk->wu.old_rno[5] = 0x280;
        ewk->wu.mvxy.a[0].sp = effg8_speed_tbl[i / 4][0];
        ewk->wu.mvxy.d[0].sp = effg8_speed_tbl[i / 4][1];
    }
    return 0;
}



/* One row per group of four birds: x, y, priority, pattern, height timer. */
const s16 effg8_data_tbl[16][5] = {
    { 720, 180, 82, 9, 74 }, { 736, 184, 82, 9, 74 }, { 832, 184, 82, 9, 72 }, { 896, 168, 82, 8, 72 },
    { 712, 164, 80, 8, 68 }, { 768, 160, 80, 8, 68 }, { 816, 160, 80, 8, 64 }, { 896, 144, 80, 8, 64 },
    { 304, 128, 78, 7, 60 }, { 272, 136, 78, 7, 60 }, { 240, 128, 78, 7, 56 }, { 208, 128, 78, 7, 56 },
    { 312, 80, 76, 7, 52 }, { 256, 80, 76, 6, 52 }, { 224, 80, 76, 6, 48 }, { 160, 80, 76, 6, 48 },
};
/* By group: x speed, x acceleration. */
const s32 effg8_speed_tbl[4][2] = {
    { -0x80000, 0xA00 }, { -0x60000, 0x600 }, { 0x60000, -0x100 }, { 0x80000, -0x100 },
};
/* By speed step (dir_step), group (type) and bird (old_rno[6]): the effg8_pos_tbl entry to re-enter at. */
const s8 effg8_pos_ix_tbl[4][4][4] = {
    { { 0, 1, 2, 3 }, { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 4, 5, 6, 7 } },
    { { 0, 1, 2, 3 }, { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 4, 5, 6, 7 } },
    { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 4, 5, 6, 7 }, { 4, 5, 6, 7 } },
    { { 4, 5, 6, 7 }, { 4, 5, 6, 7 }, { 4, 5, 6, 7 }, { 4, 5, 6, 7 } },
};
const s16 effg8_pos_tbl[8] = { 720, 752, 800, 832, 256, 240, 208, 160 };
