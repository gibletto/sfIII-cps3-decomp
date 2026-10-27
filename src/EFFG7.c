/*
 * EFFG7.C  Effect G7: ten ending objects that drift across the screen
 *
 * effect_G7_init (ending 9)
 * makes ten objects from effg7_data_tbl, two to each speed of effg7_speed_tbl; they drift
 * left and wrap at x 0x330 until end_w.r_no_2 passes 2, then fall off the screen.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "EFFG7.h"

/* routine_no[1] */
#define R1_INIT         0       /* start the pattern */
#define R1_DRIFT        1       /* drift and wrap until the scene moves on */
#define R1_FALL         2       /* fall off the screen */



extern const s16 effg7_data_tbl[10][5];
extern const s32 effg7_speed_tbl[5];



void effect_G7_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        if (ewk->wu.type > 1) {
            ewk->wu.disp_flag = 1;
        } else {
            ewk->wu.disp_flag = 2;
            ewk->wu.blink_timing = 1;
        }
        set_char_move_init2(&ewk->wu, 0, ewk->wu.old_rno[4], ewk->wu.char_index, 0);
        ewk->wu.mvxy.a[1].sp = -0x10000;
        ewk->wu.mvxy.d[1].sp = 0;
        disp_pos_trans_entry(ewk);
        break;
    case R1_DRIFT:
        if (end_w.r_no_2 > 2) {
            ewk->wu.routine_no[1]++;
        } else {
            add_x_sub(ewk);
            if (ewk->wu.xyz[0].disp.pos > 0x330) {
                ewk->wu.xyz[0].disp.pos = effg7_data_tbl[ewk->wu.type][1];
            }
            disp_pos_trans_entry(ewk);
        }
        break;
    case R1_FALL:
        add_x_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos > 0x330) {
            ewk->wu.xyz[0].disp.pos = effg7_data_tbl[ewk->wu.type][1];
        }
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos < -128) {
            ewk->wu.routine_no[1]++;
        }
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



static void end_rno_disp(s16 r_no_2) {}

s32 effect_G7_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data_ptr = &effg7_data_tbl[0][0];
    for (i = 0; i < 10; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.id = 167;
        ewk->wu.be_flag = 1;
        ewk->wu.type = i;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.old_rno[0] = end_w.r_no_2;
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
        ewk->wu.routine_no[0] = *data_ptr++;
        ewk->wu.mvxy.a[0].sp = effg7_speed_tbl[i / 2];
        ewk->wu.mvxy.d[0].sp = 0;
    }
    end_rno_disp(end_w.r_no_2);
    return 0;
}
