/*
 * EFFH6_CODE.C  Effect H6: staff-roll lines
 *
 * effect_H6_init(timer, str, x, y, colour) (from end_sub_2.c) makes one staff-roll line: the string
 * becomes a row of connected character cells through code_tab, 9 dots apart (characters with no cell
 * leave a gap); a string starting with '#' is a picture instead. effect_H6_move shows the line on
 * family 6 until it is more than 248 dots past BG 5's position, then frees it.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "effh6_code.h"

/* routine_no[0] */
#define R0_INIT         0       /* show the line */
#define R0_MOVE         1       /* show until it scrolls away */

void effect_H6_move(WORK_Other* ewk) {
    s16 y;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        if (!ewk->wu.dir_step) {
            ewk->wu.old_cgnum = ewk->wu.cg_number = 0;
            ewk->wu.cg_number++;
            ewk->wu.cg_number &= 0x7FFF;
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        break;
    case R0_MOVE:
        if (ewk->wu.dir_step) {
            y = (ewk->wu.xyz[1].disp.pos - bg_w.bgw[5].position_y) & 0x3FF;
            if (y > 248) {
                ewk->wu.routine_no[0]++;
            }
            sort_push_request4(&ewk->wu);
        } else {
            y = (ewk->wu.xyz[1].disp.pos + base_y_pos - bg_w.bgw[5].position_y) & 0x3FF;
            if (y > 248) {
                ewk->wu.routine_no[0]++;
            }
            sort_push_request3(&ewk->wu);
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

s32 effect_H6_init(s16 timer, s8* str, s16 X, s16 Y, s16 Original_Color) {
    WORK_Other_CONN* ewk;
    s16 ix;
    s16 x;
    s16 i;
    s16 c;
    s8* su = str;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other_CONN*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 176;
    ewk->wu.type = timer;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_family = 6;
    ewk->wu.my_priority = ewk->wu.position_z = 25;
    ewk->wu.my_col_mode = 0x4200;
    if (*su == '#') {
        ewk->wu.dir_step = 1;
        ewk->wu.xyz[0].disp.pos = X;
        ewk->wu.xyz[1].disp.pos = Y;
        ewk->wu.my_col_code = Original_Color + 0x2090;
        ewk->wu.cg_number = 0x649E;
    } else {
        ewk->wu.dir_step = 0;
        ewk->wu.xyz[0].disp.pos = X;
        ewk->wu.xyz[1].disp.pos = Y - base_y_pos;
        ewk->wu.my_col_code = 0;
        for (x = 0, i = 0; *su != '\0'; i += 9, su++) {
            if ((c = code_tab[*su]) == -1) {
                continue;
            }
            ewk->conn[x].nx = i;
            ewk->conn[x].ny = 0;
            ewk->conn[x].chr = c + 0x76B8;
            ewk->conn[x].col = 0x8B + Original_Color;
            x++;
        }
        ewk->num_of_conn = x;
    }
    return 0;
}


