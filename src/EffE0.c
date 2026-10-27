/*
 * EFFE0.C  Effect E0: VS-screen characters
 *
 * effect_E0_init(type, timer, priority) (from sel_pl.c) makes a character picture (sel_pl_char_table
 * pattern type + 1) at double size. After its delay effect_E0_move shrinks it to normal size (faster
 * with the cut button, Cut_Cut_Sub) five times over, then counts it off vs_object_count and frees it.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"

/* routine_no[0] */
#define R0_DELAY        0       /* wait the delay, then show */
#define R0_SHRINK       1       /* shrink to normal size */
#define R0_END          2       /* count off and hide */
#define R0_KILL         3       /* (default) put the work back */

extern s8 vs_object_count;
s32 effE0_shrink(WORK_Other* ewk);

void effect_E0_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_DELAY:
        if (--ewk->wu.dir_timer != 0) {
            return;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.dir_timer = 5;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_old + 1, 0);
        break;
    case R0_SHRINK:
        if (effE0_shrink(ewk)) {
            if (--ewk->wu.dir_timer != 0) {
                ewk->wu.my_mr.size.x = 127;
                ewk->wu.my_mr.size.y = 127;
            } else {
                ewk->wu.my_mr.size.x = 63;
                ewk->wu.my_mr.size.y = 63;
                ewk->wu.routine_no[0]++;
            }
        }
        break;
    case R0_END:
        vs_object_count--;
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 0;
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}

s32 effE0_shrink(WORK_Other* ewk) {
    u16 speed = Cut_Cut_Sub(3);
    if ((ewk->wu.my_mr.size.x -= *(s16*)&ewk->wu.mvxy.a[0] * speed) <= 63) {
        ewk->wu.my_mr.size.x = 63;
    }
    if ((ewk->wu.my_mr.size.y -= *(s16*)&ewk->wu.mvxy.a[0] * speed) <= 63) {
        ewk->wu.my_mr.size.y = 63;
    }
    if (ewk->wu.my_mr.size.x <= 63 && ewk->wu.my_mr.size.y <= 63) {
        return 1;
    }
    return 0;
}

s32 effect_E0_init(s16 type, s16 timer, s16 priority) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 140;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.my_family = 3;
    ewk->wu.dir_timer = timer;
    ewk->wu.char_table[0] = sel_pl_char_table;
    ewk->wu.char_index = 21;
    ewk->wu.dir_old = type;
    ewk->wu.position_z = priority;
    ewk->wu.my_mr_flag = 1;
    ewk->wu.my_mr.size.x = 127;
    ewk->wu.my_mr.size.y = 127;
    ewk->wu.xyz[0].disp.pos = DE_X[10] + 0x2C0;
    ewk->wu.xyz[1].disp.pos = 64;
    ewk->wu.mvxy.a[0].sp = 0x80000;
    return 0;
}
