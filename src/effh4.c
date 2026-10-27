/*
 * EFFH4.C  Effect H4: ending object
 *
 * Effect H4 grows an object from zoom 14 to full size while it moves (effH4_sp_tbl), then flies
 * it off the side of the screen.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "ta_sub.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "end_main.h"
#include "effh4.h"

/* routine_no[1] */
#define R1_INIT         0       /* start small */
#define R1_GROW         1       /* grow to full size while moving */
#define R1_FLY          2       /* fly off the side */

/* effH4_sp_tbl columns */
#define H4_SPEED_X      0       /* x speed while growing */
#define H4_ACCEL_X      1       /* x speed change once full size */
#define H4_SPEED_Y      2       /* y speed */



void effect_H4_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.old_rno[1], ewk->wu.char_index, 0);
        ewk->wu.disp_flag = 1;
        ewk->wu.my_mr_flag = 1;
        ewk->wu.my_mr.size.x = 14;
        ewk->wu.my_mr.size.y = 14;
        ewk->wu.mvxy.a[0].sp = effH4_sp_tbl[ewk->wu.type][H4_SPEED_X];
        ewk->wu.mvxy.d[0].sp = 0;
        ewk->wu.mvxy.a[1].sp = effH4_sp_tbl[ewk->wu.type][H4_SPEED_Y];
        ewk->wu.mvxy.d[1].sp = 0;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    case R1_GROW:
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.my_mr.size.x < 63) {
            ewk->wu.my_mr.size.x++;
            ewk->wu.my_mr.size.y++;
        } else {
            ewk->wu.routine_no[1]++;
            ewk->wu.mvxy.d[0].sp = effH4_sp_tbl[ewk->wu.type][H4_ACCEL_X];
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    case R1_FLY:
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos < 288 || ewk->wu.xyz[0].disp.pos > 736) {
            ewk->wu.routine_no[1]++;
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



/* provisional name */
s32 effect_H4_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data_ptr;
    data_ptr = &effH4_data_tbl[0][0];
    for (i = 0; i < 4; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)((u32)frw + (ix << 11));
        ewk->wu.id = 174;
        ewk->wu.be_flag = 1;
        ewk->wu.type = i;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.old_rno[0] = end_w.r_no_2;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.char_table[0] = effH3_char_table;
        ewk->wu.my_family = 1;
        ewk->wu.my_col_code = 32;
        ewk->wu.old_rno[1] = 19;
        ewk->wu.char_index = *data_ptr++;
        ewk->wu.xyz[0].disp.pos = *data_ptr++;
        ewk->wu.xyz[1].disp.pos = *data_ptr++;
        ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
        ewk->wu.old_rno[0] = ewk->wu.char_index - 1;
    }
    return 0;
}
