/*
 * EFFE1.C  Effect E1: opening scene windows
 *
 * effect_E1_init(id, time, ready) (from the opening, end_main.c) makes window id 0-2 (etc_char_table);
 * with ready set it starts in its final place. Otherwise, after its delay, window 0 shrinks from double
 * size at its place and windows 1 and 2 fly in from the left and right to the centre over 10 frames;
 * each then plays its own pattern (window 1 sounds 124). Once the opening reaches step 17
 * (op_w.r_no_0) a window rises 32 dots and sets effE1_end_flag.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CALDIR.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "se_3.h"

extern s8 effE1_end_flag;

void effect_E1_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        if (--ewk->wu.dir_timer) {
            return;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        if (ewk->wu.old_rno[0]) {
            ewk->wu.my_mr_flag = 1;
            ewk->wu.my_mr.size.x = 127;
            ewk->wu.my_mr.size.y = 127;
        }
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.old_rno[0] + 1, 0);
        break;
    case 1:
        switch (ewk->wu.routine_no[1]) {
        case 0:
            if (ewk->wu.old_rno[0]) {
                if (ewk->wu.my_mr.size.x >= 67) {
                    ewk->wu.my_mr.size.x -= 4;
                    ewk->wu.my_mr.size.y -= 4;
                }
            }
            ewk->wu.old_rno[1]--;
            if (ewk->wu.old_rno[1] <= 0) {
                ewk->wu.routine_no[1]++;
                ewk->wu.dir_timer = 1;
                ewk->wu.xyz[0].disp.pos = ewk->wu.old_rno[2];
                ewk->wu.xyz[1].disp.pos = ewk->wu.old_rno[3];
                ewk->wu.mvxy.a[1].sp = 0x20000;
                ewk->wu.mvxy.d[1].sp = 0;
                ewk->wu.my_mr.size.x = 63;
                ewk->wu.my_mr.size.y = 63;
                set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[4]);
                if (ewk->wu.old_rno[0] == 1) {
                    Sound_SE(124);
                }
            } else {
                add_x_sub(ewk);
                add_y_sub(ewk);
            }
            break;
        case 1:
            char_move(&ewk->wu);
            if (op_w.r_no_0 != 17) {
                break;
            }
            add_y_sub(ewk);
            if (ewk->wu.xyz[1].disp.pos > ewk->wu.old_rno[3] + 32) {
                ewk->wu.routine_no[0]++;
                effE1_end_flag = 1;
            }
            break;
        }
        break;
    case 2:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[4]);
        break;
    case 3:
        if (--ewk->wu.dir_timer) {
            break;
        }
        ewk->wu.routine_no[0]++;
        /* fall through */
    case 4:
        char_move(&ewk->wu);
        break;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}

s32 effect_E1_init(s16 id, s16 Time, s16 ready) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 141;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 64;
    ewk->wu.my_family = 2;
    ewk->wu.dir_timer = Time;
    ewk->wu.char_table[0] = etc_char_table;
    ewk->wu.char_index = 48;
    ewk->wu.old_rno[0] = id;
    ewk->wu.my_mr.size.x = 63;
    ewk->wu.my_mr.size.y = 63;
    switch (id) {
    case 0:
        ewk->wu.old_rno[2] = ewk->wu.xyz[0].disp.pos = 0x200;
        ewk->wu.old_rno[3] = 40;
        ewk->wu.my_priority = ewk->wu.position_z = 51;
        ewk->wu.old_rno[4] = 61;
        if (ready) {
            ewk->wu.routine_no[0] = 2;
            ewk->wu.char_index = 61;
            ewk->wu.xyz[1].disp.pos = 72;
        } else {
            ewk->wu.old_rno[1] = 0;
            ewk->wu.mvxy.a[0].sp = 0;
            ewk->wu.mvxy.a[1].sp = 0;
            ewk->wu.old_rno[2] = ewk->wu.xyz[0].disp.pos = 0x200;
            ewk->wu.xyz[1].disp.pos = 40;
        }
        break;
    case 1:
        ewk->wu.my_priority = ewk->wu.position_z = 50;
        ewk->wu.old_rno[4] = 59;
        if (ready) {
            ewk->wu.xyz[0].disp.pos = 0x200;
            ewk->wu.xyz[1].disp.pos = 152;
            ewk->wu.routine_no[0] = 2;
            ewk->wu.char_index = 59;
        } else {
            ewk->wu.xyz[0].disp.pos = 0x100;
            ewk->wu.xyz[1].disp.pos = 120;
            ewk->wu.old_rno[2] = 0x200;
            ewk->wu.old_rno[3] = 120;
            ewk->wu.old_rno[1] = 10;
            cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[1], ewk->wu.old_rno[2], ewk->wu.old_rno[3], 1, 1);
        }
        break;
    case 2:
        ewk->wu.my_priority = ewk->wu.position_z = 50;
        ewk->wu.old_rno[4] = 60;
        if (ready) {
            ewk->wu.xyz[0].disp.pos = 0x200;
            ewk->wu.xyz[1].disp.pos = 152;
            ewk->wu.routine_no[0] = 2;
            ewk->wu.char_index = 60;
        } else {
            ewk->wu.old_rno[2] = 0x200;
            ewk->wu.old_rno[3] = 120;
            ewk->wu.xyz[0].disp.pos = 0x300;
            ewk->wu.xyz[1].disp.pos = 120;
            ewk->wu.old_rno[1] = 10;
            cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[1], ewk->wu.old_rno[2], ewk->wu.old_rno[3], 1, 1);
        }
        break;
    }
    return 0;
}
