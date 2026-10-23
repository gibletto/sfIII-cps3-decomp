/*
 * EFFF3.C  Effect F3: slide-in select sprite
 *
 * Effect F3 (effect_F3_init with step, delay, y and entry side) shows sel_pl_char_table pattern
 * 52 after its delay and slides it in from the left or right edge of BG0 (effF3_pos_set) with a
 * decelerating speed until it stops at DE_X[14] + 32 relative to BG0.
 * The stop position is kept in hit_quake and the step in vital_new.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFF4.h"



void effect_F3_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        if (--ewk->wu.dir_timer != 0) {
            return;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.vital_new + 1, 0);
        break;
    case 1:
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
        ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp;
        if (ewk->wu.mvxy.a[0].sp > 0) {
            if (ewk->wu.hit_quake <= ewk->wu.xyz[0].disp.pos) {
                ewk->wu.routine_no[0]++;
                ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
            }
        } else if (ewk->wu.hit_quake >= ewk->wu.xyz[0].disp.pos) {
            ewk->wu.routine_no[0]++;
            ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
        }
        break;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}



s32 effect_F3_init(s16 step, s16 delay, s16 x, s16 y) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 153;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 1;
    ewk->wu.dir_timer = delay;
    ewk->wu.char_table[0] = sel_pl_char_table;
    ewk->wu.char_index = 52;
    ewk->wu.vital_new = step;
    ewk->wu.my_col_code = 0x2043;
    ewk->wu.xyz[1].disp.pos = y;
    ewk->wu.position_z = 80;
    effF3_pos_set(ewk, x);
    return 0;
}



/* provisional name */
void effF3_pos_set(WORK_Other* ewk, s16 x) {
    if (x == 4) {
        ewk->wu.xyz[0].disp.pos = bg_w.bgw[0].xy[0].disp.pos + 576;
        ewk->wu.mvxy.a[0].sp = -0x150000;
        ewk->wu.mvxy.d[0].sp = -0x18000;
        ewk->wu.hit_quake = bg_w.bgw[0].xy[0].disp.pos + DE_X[14] + 32;
    } else {
        ewk->wu.xyz[0].disp.pos = bg_w.bgw[0].xy[0].disp.pos - 384;
        ewk->wu.mvxy.a[0].sp = 0x150000;
        ewk->wu.mvxy.d[0].sp = 0x18000;
        ewk->wu.hit_quake = bg_w.bgw[0].xy[0].disp.pos + DE_X[14] + 32;
    }
}
