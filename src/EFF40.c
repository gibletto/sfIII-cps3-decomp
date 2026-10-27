/*
 * EFF40.C  Effect 40: select-screen zoom object
 *
 * Effect 40 waits for its delay, appears at double size and shrinks to normal while moving
 * forward in priority; it is placed by direction from eff40_pos_x_tbl.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "Eff76.h"
#include "aboutspr.h"
#include "Eff59.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "charmove_2.h"
#include "Eff39.h"
#include "EFFD9.h"
#include "EFF41.h"
#include "EFF42.h"

/* routine_no[0] */
#define R0_WAIT         0       /* count the delay down, then show */
#define R0_HOLD         1       /* one frame at double size */
#define R0_SHRINK       2       /* shrink to normal size */
#define R0_STAY         3       /* (default) stay at normal size */

void set_char_move_init2();

void effect_40_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_WAIT:
        if (--ewk->wu.dir_timer != 0) {
            return;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.dir_timer = 1;
        ewk->wu.mvxy.a[0].sp = 0x80000;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
        break;
    case R0_HOLD:
        if (--ewk->wu.dir_timer == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case R0_SHRINK:
        ewk->wu.my_priority++;
        ewk->wu.position_z++;
        if ((ewk->wu.my_mr.size.x -= *(s16*)&ewk->wu.mvxy.a[0]) <= 63) {
            ewk->wu.my_mr.size.x = 63;
        }
        if ((ewk->wu.my_mr.size.y -= *(s16*)&ewk->wu.mvxy.a[0]) <= 63) {
            ewk->wu.my_mr.size.y = 63;
        }
        if (ewk->wu.my_mr.size.x <= 63 && ewk->wu.my_mr.size.y <= 63) {
            ewk->wu.routine_no[0]++;
        }
        break;
    default:
        break;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}



s32 effect_40_init(s16 dir, s16 timer) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 40;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2043;
    ewk->wu.my_family = 1;
    ewk->wu.position_z = 40;
    ewk->wu.dir_timer = timer;
    ewk->wu.char_table[0] = sel_pl_char_table;
    ewk->wu.dir_step = dir;
    ewk->wu.char_index = 22;
    ewk->wu.my_mr_flag = 1;
    ewk->wu.my_mr.size.x = 127;
    ewk->wu.my_mr.size.y = 127;
    ewk->wu.xyz[0].disp.pos = eff40_pos_x_tbl[dir] + DE_X[5] / 2 + bg_w.bgw[0].position_x;
    ewk->wu.xyz[1].disp.pos = bg_w.bgw[0].position_y + 0x80;
    return 0;
}
