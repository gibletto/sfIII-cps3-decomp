/*
 * EFFH9.C  Effects H7 and H8 (objects that pop out of the ground)
 *
 * Effects H7 and H8 are created at their owner's x, at floor level, with the owner's palette
 * and facing (plef_char_table). Each waits a per-type delay (effH7_wait_tbl / effH8_wait_tbl),
 * raises a dust effect (effect 3 types 69 / 70) and then appears with a pattern from
 * effH7_char_tbl / effH8_char_tbl at the offsets in effH7_pos_tbl / effH8_pos_tbl.
 * effect_H7_move bounces the object in (effH7_bound_tbl) and then bobs it along random height
 * tables (effH7_move_tbl, effH7_move_data_0 - 3). effect_H8_move plays its pattern once; on
 * stage 8 in the first round it later switches to a second pattern and flies upward. Both die
 * with dead_f or Suicide.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLS02.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFF03.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFH9.h"

/* routine_no[0], effects H7 and H8 */
#define R0_INIT         0       /* place, hidden */
#define R0_MOVE         1       /* come out of the ground */
#define R0_KILL         3       /* (default) put the work back */

/* routine_no[1], effect H7 (0 and 1 also H8) */
#define R1_WAIT         0       /* wait, then raise the dust */
#define R1_SHOW         1       /* a short wait, then show */
#define R1_BOUND        2       /* bounce out of the ground */
#define R1_HOLD         3       /* hold before bobbing */
#define R1_PICK         4       /* pick a random bob table */

/* routine_no[1], effect H8 */
#define R1_PLAY         2       /* play the pattern once */
#define R1_FLY_WAIT     3       /* wait for the stage to move */
#define R1_FLY          4       /* fly upward */
#define R1_STOP         9       /* stay as it is */

/* effH7_pos_tbl / effH8_pos_tbl columns */
#define H9_POS_X        0       /* x offset, toward the facing */
#define H9_POS_Y        1       /* y offset */
#define H9_POS_Z        2       /* priority offset */



/* 020070F4 */
const s16* effH7_move_tbl[16] = {
    effH7_move_data_0,
    effH7_move_data_0,
    effH7_move_data_0,
    effH7_move_data_0,
    effH7_move_data_1,
    effH7_move_data_1,
    effH7_move_data_1,
    effH7_move_data_1,
    effH7_move_data_1,
    effH7_move_data_0,
    effH7_move_data_1,
    effH7_move_data_0,
    effH7_move_data_2,
    effH7_move_data_2,
    effH7_move_data_1,
    effH7_move_data_3,
};


void effect_H7_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        if (ewk->wu.rl_waza) {
            ewk->wu.position_x += effH7_pos_tbl[ewk->wu.rl_waza][ewk->wu.type][H9_POS_X];
        } else {
            ewk->wu.position_x -= effH7_pos_tbl[ewk->wu.rl_waza][ewk->wu.type][H9_POS_X];
        }
        ewk->wu.position_y += effH7_pos_tbl[ewk->wu.rl_waza][ewk->wu.type][H9_POS_Y];
        ewk->wu.position_z += effH7_pos_tbl[ewk->wu.rl_waza][ewk->wu.type][H9_POS_Z];
        ewk->wu.xyz[0].disp.pos = ewk->wu.position_x;
        ewk->wu.xyz[1].disp.pos = ewk->wu.position_y;
        ewk->wu.disp_flag = 0;
        ewk->wu.rl_flag = 0;
        ewk->wu.dir_timer = effH7_wait_tbl[ewk->wu.type];
        set_char_move_init(&ewk->wu, 0, effH7_char_tbl[ewk->wu.rl_waza][ewk->wu.type]);
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            switch (ewk->wu.routine_no[1]) {
            case R1_WAIT:
                if (--ewk->wu.dir_timer > 0) {
                    break;
                }
                effect_03_init(&ewk->wu, 69);
                ewk->wu.routine_no[1]++;
                ewk->wu.dir_timer = 4;
                break;
            case R1_SHOW:
                if (--ewk->wu.dir_timer > 0) {
                    break;
                }
                ewk->wu.routine_no[1]++;
                ewk->wu.disp_flag = 1;
                ewk->wu.dir_timer = 0;
                break;
            case R1_BOUND:
                ewk->wu.dir_step = effH7_bound_tbl[ewk->wu.dir_timer++];
                if (ewk->wu.dir_step == 99) {
                    ewk->wu.routine_no[1]++;
                    ewk->wu.dir_timer = effH7_wait2_tbl[ewk->wu.type];
                    break;
                }
                ewk->wu.position_y += ewk->wu.dir_step;
                break;
            case R1_HOLD:
                if (--ewk->wu.dir_timer > 0) {
                    break;
                }
                ewk->wu.routine_no[1]++;
            case R1_PICK:
                ewk->wu.dir_timer = 0;
                ewk->wu.move_xy_table = effH7_move_tbl[random_16_com()];
                ewk->wu.routine_no[1]++;
            default:
                char_move(&ewk->wu);
                ewk->wu.dir_step = ewk->wu.move_xy_table[ewk->wu.dir_timer++];
                if (ewk->wu.dir_step == 99) {
                    ewk->wu.routine_no[1] = R1_PICK;
                } else {
                    ewk->wu.position_y += ewk->wu.dir_step;
                }
                break;
            }
        }
        sort_push_request(&ewk->wu);
        break;
    case 2:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_H7_init(WORK* wk, s16 type) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 177;
    ewk->wu.type = type;
    ewk->wu.work_id = 16;
    ewk->wu.rl_waza = wk->rl_flag;
    ewk->wu.my_family = wk->my_family;
    ewk->wu.cgromtype = wk->cgromtype;
    ewk->wu.my_col_mode = wk->my_col_mode;
    ewk->wu.my_col_code = wk->my_col_code;
    ewk->my_master = (u32*)wk;
    ewk->master_work_id = wk->work_id;
    ewk->master_id = ewk->wu.blink_timing = wk->id;
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = wk->position_x;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = -4;
    ewk->wu.position_z = wk->position_z;
    ewk->wu.char_table[0] = plef_char_table;
    return 0;
}



void effect_H8_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        if (ewk->wu.rl_waza) {
            ewk->wu.position_x += effH8_pos_tbl[ewk->wu.rl_waza][ewk->wu.type][H9_POS_X];
        } else {
            ewk->wu.position_x -= effH8_pos_tbl[ewk->wu.rl_waza][ewk->wu.type][H9_POS_X];
        }
        ewk->wu.position_y += effH8_pos_tbl[ewk->wu.rl_waza][ewk->wu.type][H9_POS_Y];
        ewk->wu.position_z += effH8_pos_tbl[ewk->wu.rl_waza][ewk->wu.type][H9_POS_Z];
        ewk->wu.xyz[0].disp.pos = ewk->wu.position_x;
        ewk->wu.xyz[1].disp.pos = ewk->wu.position_y;
        ewk->wu.disp_flag = 0;
        ewk->wu.rl_flag = 0;
        ewk->wu.dir_timer = effH8_wait_tbl[ewk->wu.type];
        set_char_move_init(&ewk->wu, 0, effH8_char_tbl[ewk->wu.rl_waza][ewk->wu.type]);
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            switch (ewk->wu.routine_no[1]) {
            case R1_WAIT:
                if (--ewk->wu.dir_timer > 0) {
                    break;
                }
                effect_03_init(&ewk->wu, 70);
                ewk->wu.routine_no[1]++;
                ewk->wu.dir_timer = 4;
                break;
            case R1_SHOW:
                if (--ewk->wu.dir_timer > 0) {
                    break;
                }
                ewk->wu.routine_no[1]++;
                ewk->wu.disp_flag = 1;
                break;
            case R1_PLAY:
                char_move(&ewk->wu);
                if (ewk->wu.cg_type == 0xFF) {
                    if (bg_w.stage == 8 && Round_num == 0) {
                        ewk->wu.routine_no[1] = R1_FLY_WAIT;
                    } else {
                        ewk->wu.routine_no[1] = R1_STOP;
                    }
                }
                break;
            case R1_FLY_WAIT:
                if (bg_w.bgw[1].r_no_1 >= 1) {
                    set_char_move_init(&ewk->wu, 0, effH8_char2_tbl[ewk->wu.rl_waza][ewk->wu.type]);
                    ewk->wu.xyz[0].disp.pos = ewk->wu.position_x;
                    ewk->wu.xyz[1].disp.pos = ewk->wu.position_y;
                    ewk->wu.mvxy.a[0].sp = ewk->wu.mvxy.d[0].sp = 0;
                    ewk->wu.mvxy.a[1].sp = 0;
                    ewk->wu.mvxy.d[1].sp = -0x3400;
                    ewk->wu.mvxy.kop[0] = ewk->wu.mvxy.kop[1] = 0;
                    ewk->wu.kage_flag = 0;
                    ewk->wu.routine_no[1]++;
                }
                break;
            case R1_FLY:
                char_move(&ewk->wu);
                add_mvxy_speed(&ewk->wu);
                cal_mvxy_speed(&ewk->wu);
                if (ewk->wu.mvxy.a[1].sp < -0x100000) {
                    ewk->wu.mvxy.d[1].sp = 0;
                }
                ewk->wu.position_x = ewk->wu.xyz[0].disp.pos;
                ewk->wu.position_y = ewk->wu.xyz[1].disp.pos;
            default:
                break;
            }
        }
        sort_push_request(&ewk->wu);
        break;
    case 2:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_H8_init(WORK* wk, s16 type) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 178;
    ewk->wu.type = type;
    ewk->wu.work_id = 16;
    ewk->wu.rl_waza = wk->rl_flag;
    ewk->wu.my_family = wk->my_family;
    ewk->wu.cgromtype = wk->cgromtype;
    ewk->wu.my_col_mode = wk->my_col_mode;
    ewk->wu.my_col_code = wk->my_col_code;
    ewk->my_master = (u32*)wk;
    ewk->master_work_id = wk->work_id;
    ewk->master_id = ewk->wu.blink_timing = wk->id;
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = wk->position_x;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = -4;
    ewk->wu.position_z = wk->position_z - 6;
    ewk->wu.char_table[0] = plef_char_table;
    return 0;
}



