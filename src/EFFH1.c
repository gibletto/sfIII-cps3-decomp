/*
 * EFFH1.C  Effect H1: four ending objects that fly in when the scroll arrives
 *
 * effect_H1_init (ending 9) makes four objects from effh1_data_tbl; each waits until bg 0 has scrolled
 * below x 0x1E0, flies with the speeds in effh1_speed_tbl until it passes y 0x100, then
 * goes back to its start for the second pass.
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
#include "PLS02.h"
#include "aboutspr.h"
#include "bg_sub.h"
#include "EFFH1.h"

/* routine_no[1] */
#define R1_WAIT         0       /* wait for the scroll */
#define R1_SET_1        1       /* set the speeds for the first pass */
#define R1_FLY_1        2       /* fly the first pass */
#define R1_SET_2        3       /* set the speeds for the second pass */
#define R1_FLY_2        4       /* fly the second pass */



void effect_H1_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_WAIT:
        if (bg_w.bgw[0].xy[0].disp.pos < 0x1E0) {
            ewk->wu.routine_no[1]++;
            ewk->wu.disp_flag = 2;
            ewk->wu.blink_timing = 1;
            set_char_move_init2(&ewk->wu, 0, ewk->wu.old_rno[1], ewk->wu.char_index, 0);
        }
        break;
    case R1_SET_1:
    case R1_SET_2:
        ewk->wu.routine_no[1]++;
        ewk->wu.mvxy.a[0].sp = effh1_speed_tbl[ewk->wu.type][0];
        ewk->wu.mvxy.d[0].sp = effh1_speed_tbl[ewk->wu.type][1];
        ewk->wu.mvxy.a[1].sp = effh1_speed_tbl[ewk->wu.type][2];
        ewk->wu.mvxy.d[1].sp = effh1_speed_tbl[ewk->wu.type][3];
        disp_pos_trans_entry(ewk);
        break;
    case R1_FLY_1:
    case R1_FLY_2:
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos > 0x100) {
            ewk->wu.routine_no[1]++;
            ewk->wu.xyz[0].disp.pos = effh1_data_tbl[ewk->wu.type][1];
            ewk->wu.xyz[1].disp.pos = effh1_data_tbl[ewk->wu.type][2];
        } else {
            disp_pos_trans_entry(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_H1_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data_ptr = &effh1_data_tbl[0][0];
    for (i = 0; i < 4; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)((u32)frw + (ix << 11));
        ewk->wu.id = 171;
        ewk->wu.be_flag = 1;
        ewk->wu.type = i;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.old_rno[0] = end_w.r_no_2;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.char_table[0] = effH3_char_table;
        ewk->wu.my_family = 1;
        ewk->wu.my_col_code = 32;
        ewk->wu.old_rno[1] = 18;
        ewk->wu.char_index = *data_ptr++;
        ewk->wu.xyz[0].disp.pos = *data_ptr++;
        ewk->wu.xyz[1].disp.pos = *data_ptr++;
        ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
        ewk->wu.old_rno[0] = ewk->wu.char_index - 1;
    }
    return 0;
}
