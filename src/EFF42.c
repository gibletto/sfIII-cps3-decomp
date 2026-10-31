/*
 * EFF42.C  Effect 42 (select timer digits)
 *
 * Effect 42 is the select-screen timer: one work per digit (effect_42_init's Type picks
 * the tens or the units). It waits dir_timer frames, restarts Time_Stop, zooms in from 63,
 * then follows Select_Timer, flipping its zoom through 0 when the digit changes at 32 and
 * Setup_Char_Index picks the new digit. When Time_Stop goes negative it zooms out and
 * releases itself.
 * zoom_x_step_check steps a work's horizontal zoom toward 0 or 63.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFF42.h"

/* routine_no[0] */
#define R0_MOVE         0       /* run the select timer */
#define R0_CLOSE        1       /* (default) zoom out and put the work back */

/* routine_no[1], while the timer runs */
#define R1_WAIT         0       /* count the delay down, start the timer */
#define R1_ZOOM         1       /* flip a few times, then settle */
#define R1_COUNT        2       /* show the digit of the select timer */
#define R1_NARROW       3       /* narrow to nothing for a new digit */
#define R1_WIDEN        4       /* (default) widen back with the new digit */

/* routine_no[1], closing */
#define R1_SHUT         0       /* start the zoom-out */
#define R1_CLOSE        1       /* narrow to nothing, then hide */



void effect_42_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_MOVE:
        if (Time_Stop < 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.routine_no[1] = R1_SHUT;
            sort_push_request4(&ewk->wu);
            return;
        }
        switch (ewk->wu.routine_no[1]) {
        case R1_WAIT:
            if (--ewk->wu.dir_timer != 0) {
                return;
            } else {
                ewk->wu.routine_no[1]++;
                ewk->wu.routine_no[2] = 5;
                ewk->wu.disp_flag = 1;
                Time_Stop = 0;
                set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
            }
            break;
        case R1_ZOOM:
            if (zoom_x_step_check(ewk)) {
                if (--ewk->wu.routine_no[2] != 0) {
                    ewk->wu.mvxy.a[0].sp = -ewk->wu.mvxy.a[0].sp;
                } else {
                    ewk->wu.routine_no[1]++;
                    ewk->wu.my_mr_flag = 0;
                }
            }
            break;
        case R1_COUNT:
            if (ewk->wu.rl_waza != Select_Timer) {
                ewk->wu.rl_waza = Select_Timer;
                if (Select_Timer == 32) {
                    ewk->wu.routine_no[1]++;
                    ewk->wu.my_mr_flag = 1;
                    ewk->wu.mvxy.a[0].sp = -0x80000;
                    ewk->wu.my_mr.size.x = 63;
                    ewk->wu.my_mr.size.y = 63;
                } else {
                    Setup_Char_Index(ewk);
                    set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
                }
            }
            break;
        case R1_NARROW:
            if (zoom_x_step_check(ewk)) {
                ewk->wu.routine_no[1]++;
                ewk->wu.mvxy.a[0].sp = -ewk->wu.mvxy.a[0].sp;
                Setup_Char_Index(ewk);
                set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
            }
            break;
        default:
            if (zoom_x_step_check(ewk)) {
                ewk->wu.routine_no[1] = R1_COUNT;
                ewk->wu.my_mr_flag = 0;
            }
            break;
        }
        break;
    default:
        switch (ewk->wu.routine_no[1]) {
        case R1_SHUT:
            ewk->wu.routine_no[1]++;
            ewk->wu.my_mr_flag = 1;
            ewk->wu.mvxy.a[0].sp = -0x80000;
        case R1_CLOSE:
            if (zoom_x_step_check(ewk)) {
                ewk->wu.routine_no[1]++;
                ewk->wu.disp_flag = 0;
                return;
            }
            break;
        default:
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
            return;
        }
        break;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}



void Setup_Char_Index(WORK_Other* ewk) {
    s16 xx = Select_Timer & (s8)ewk->wu.routine_no[7];
    if (ewk->wu.routine_no[7] == 240) {
        xx >>= 4;
    }
    ewk->wu.dir_step = xx;
}



s32 effect_42_init(s16 Type) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 42;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.sync_suzi = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.my_family = 3;
    ewk->wu.xyz[1].disp.pos = 160;
    ewk->wu.mvxy.a[0].sp = -0x80000;
    ewk->wu.position_z = 54;
    ewk->wu.dir_timer = 10;
    ewk->wu.rl_waza = Select_Timer;
    ewk->wu.char_table[0] = sel_pl_char_table;
    ewk->wu.char_index = 3;
    ewk->wu.my_mr_flag = 1;
    ewk->wu.my_mr.size.x = 0;
    ewk->wu.my_mr.size.y = 63;
    ewk->wu.mvxy.a[0].sp = 0x80000;
    if (Type) {
        ewk->wu.xyz[0].disp.pos = DE_X[10] + 696;
        ewk->wu.dir_step = 2;
        ewk->wu.routine_no[7] = 240;
    } else {
        ewk->wu.xyz[0].disp.pos = DE_X[10] + 712;
        ewk->wu.dir_step = 0;
        ewk->wu.routine_no[7] = 15;
    }
    return 0;
}



s32 zoom_x_step_check(wk)
WORK* wk;
{
    if (wk->mvxy.a[0].sp <= 0) {
        if ((wk->my_mr.size.x += *(s16*)&wk->mvxy.a[0]) <= 0) {
            wk->my_mr.size.x = 0;
            return 1;
        }
        return 0;
    } else {
        if ((wk->my_mr.size.x += *(s16*)&wk->mvxy.a[0]) >= 63) {
            wk->my_mr.size.x = 63;
            return 1;
        }
        return 0;
    }
}
