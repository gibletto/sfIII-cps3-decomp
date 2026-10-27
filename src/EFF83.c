/*
 * EFF83.C  Effect 83: three background objects crossing the stage
 *
 * effect_83_init (from bgst110's stage) creates three objects with the stage's character table
 * (char_add by stage and area). Each takes the next of its eight entries in eff83_data_tbl (pattern,
 * position, priority) and speed in eff83_speed_tbl, moves right with its animation and, once past
 * x 896, starts again with the following entry. They are drawn blinking.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFF83.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "ta_sub.h"

/* routine_no[0] */
#define R0_INIT         0       /* take the next entry */
#define R0_MOVE         1       /* move right, then start again */

extern const s16 eff83_data_tbl[3][8][4];
extern const s32 eff83_speed_tbl[3][8];

void effect_83_move(WORK_Other* ewk) {
    const s16* data;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 2;
        ewk->wu.blink_timing = 1;
        data = eff83_data_tbl[ewk->wu.type][ewk->wu.old_rno[0]];
        ewk->wu.char_index = *data++;
        ewk->wu.xyz[0].disp.pos = *data++;
        ewk->wu.xyz[1].disp.pos = *data++;
        ewk->wu.my_priority = ewk->wu.position_z = *data;
        ewk->wu.mvxy.a[0].sp = eff83_speed_tbl[ewk->wu.type][ewk->wu.old_rno[0]];
        ewk->wu.mvxy.d[0].sp = 0;
        ewk->wu.old_rno[0]++;
        ewk->wu.old_rno[0] &= 7;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R0_MOVE:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            add_x_sub(ewk);
            if (ewk->wu.xyz[0].disp.pos > 896) {
                ewk->wu.routine_no[0] = R0_INIT;
            }
        }
        disp_pos_trans_entry_r(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

s32 effect_83_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    for (i = 0; i < 3; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 83;
        ewk->wu.work_id = 16;
        ewk->wu.type = i;
        ewk->wu.old_rno[0] = 0;
        ewk->wu.cgromtype = 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_family = 3;
        ewk->wu.my_col_code = 0x2040;
        ewk->wu.char_table[0] = char_add[bg_w.stage][bg_w.area];
    }
    return 0;
}
