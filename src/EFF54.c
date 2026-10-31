/*
 * EFF54.C  Effect 54: a stage object that flies a fixed course
 *
 * effect_54_init places one object above its parent's x;
 * effect_54_move flies it through the timer and speed rows of eff54_move_tbl, rests, and frees it
 * once it has gone off the top.
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
#include "EFF54.h"

/* routine_no[0] */
#define R0_INIT         0       /* show and take the first course row */
#define R0_FLY          1       /* fly the row for its time */
#define R0_REST         2       /* rest, then take the last row */
#define R0_LEAVE        3       /* fly off the top */
#define R0_KILL         4       /* (default) put the work back */

/* Fly the object through the rows of eff54_move_tbl, then free it once it is off the top. */
void effect_54_move(WORK_Other* ewk) {
    const s32* p;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 2);
        p = eff54_move_tbl[ewk->wu.routine_no[0]];
        ewk->wu.direction = *p;
        p++;
        ewk->wu.mvxy.a[0].sp = *p++;
        ewk->wu.mvxy.a[1].sp = *p++;
        ewk->wu.mvxy.d[0].sp = *p++;
        ewk->wu.mvxy.d[1].sp = *p;
        ewk->wu.routine_no[0]++;
        disp_pos_trans_entry(ewk);
        break;
    case R0_FLY:
        if (!EXE_flag && !Game_pause) {
            ewk->wu.direction--;
            if (ewk->wu.direction < 0) {
                ewk->wu.direction = eff54_move_tbl[ewk->wu.routine_no[0]][0];
                ewk->wu.routine_no[0]++;
            } else {
                char_move(&ewk->wu);
                add_x_sub(ewk);
                add_y_sub(ewk);
            }
        }
        disp_pos_trans_entry(ewk);
        break;
    case R0_REST:
        if (!EXE_flag && !Game_pause) {
            ewk->wu.direction--;
            if (ewk->wu.direction < 0) {
                p = eff54_move_tbl[ewk->wu.routine_no[0]];
                ewk->wu.direction = *p;
                p++;
                ewk->wu.mvxy.a[0].sp = *p++;
                ewk->wu.mvxy.a[1].sp = *p++;
                ewk->wu.mvxy.d[0].sp = *p++;
                ewk->wu.mvxy.d[1].sp = *p;
                ewk->wu.routine_no[0]++;
            }
        }
        disp_pos_trans_entry(ewk);
        break;
    case R0_LEAVE:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
            if (ewk->wu.xyz[1].disp.pos < 0) {
                ewk->wu.routine_no[0]++;
            }
        }
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* Create the object that flies the course of eff54_move_tbl, starting 21 dots right of its parent. */
s32 effect_54_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 54;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->my_master = (u32*)oya;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2057;
    ewk->wu.position_x = (oya->wu.xyz[0].disp.pos + 21) & 0x3FF;
    ewk->wu.position_y = 95;
    ewk->wu.xyz[0].disp.pos = ewk->wu.position_x;
    ewk->wu.xyz[1].disp.pos = ewk->wu.position_y;
    ewk->wu.position_z = ewk->wu.my_priority = 10;
    ewk->wu.char_table[0] = eff54_char_table;
    return 0;
}
