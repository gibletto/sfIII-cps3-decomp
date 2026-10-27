/*
 * EFF29.C  Effect 29: two stage objects that walk their own routes
 *
 * effect_29_init
 * creates two objects from eff29_pos_tbl; type 0 walks left and right on the x axis
 * (eff29_type0), type 1 runs a ten-step route on both axes (eff29_type1).
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
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFF29.h"

/* routine_no[0] */
#define R0_INIT         0       /* clear the sub-states and show */
#define R0_MOVE         1       /* walk the type's route */
#define R0_END          2       /* one more frame */
#define R0_KILL         99      /* (default) put the work back */

/* routine_no[1], eff29_type0 */
#define R1_INIT         0       /* start walking left */
#define R1_LEFT         1       /* walk left to the turn */
#define R1_TURN_R       2       /* turn, then walk right */
#define R1_RIGHT        3       /* walk right to the turn */
#define R1_TURN_L       4       /* turn, then walk left again */

/* routine_no[2], eff29_type1 */
#define R2_INIT         0       /* start the route heading right */
#define R2_RIGHT        1       /* walk right to the turn */
#define R2_LEFT         2       /* walk left to the turn */
#define R2_RETURN       3       /* walk right again to the turn */
#define R2_TURN         4       /* wait for the pattern, then go down */
#define R2_DOWN         5       /* move down and left */
#define R2_LAND         6       /* wait for the pattern, then walk left */
#define R2_WALK         7       /* walk left */
#define R2_RISE         8       /* wait for the pattern, then go up */
#define R2_UP           9       /* move up and left, then start over */



extern const s16 eff29_pos_tbl[2][3];
extern u32 eff29_type0_char_table[];
extern u32 eff29_type1_char_table[];

void eff29_type0(WORK_Other* ewk);
void eff29_type1(WORK_Other* ewk);



void effect_29_move(WORK_Other* ewk) {
    if (compel_dead_check(ewk)) {
        ewk->wu.routine_no[0] = R0_KILL;
    } else {
        switch (ewk->wu.routine_no[0]) {
        case R0_INIT:
            ewk->wu.routine_no[0]++;
            ewk->wu.routine_no[1] = R1_INIT;
            ewk->wu.routine_no[2] = R2_INIT;
            ewk->wu.disp_flag = 1;
            break;
        case R0_MOVE:
            if (!EXE_flag && !Game_pause) {
                if (ewk->wu.type) {
                    eff29_type1(ewk);
                } else {
                    eff29_type0(ewk);
                }
            }
            disp_pos_trans_entry_rs(ewk);
            break;
        case R0_END:
            ewk->wu.routine_no[0]++;
            break;
        default:
            all_cgps_put_back(ewk);
            push_effect_work(&ewk->wu);
            break;
        }
    }
}



void eff29_type0(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        set_char_move_init(&ewk->wu, 0, 0);
        ewk->wu.mvxy.a[0].sp = -0x6000;
        ewk->wu.mvxy.d[0].sp = 0;
        break;
    case R1_LEFT:
        char_move(&ewk->wu);
        add_x_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos < 0xA0) {
            ewk->wu.xyz[0].disp.pos = 0xA0;
            ewk->wu.routine_no[1]++;
            set_char_move_init(&ewk->wu, 0, 1);
        }
        break;
    case R1_TURN_R:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[1]++;
            set_char_move_init(&ewk->wu, 0, 2);
            ewk->wu.mvxy.a[0].sp = 0x6000;
            ewk->wu.mvxy.d[0].sp = 0;
        }
        break;
    case R1_RIGHT:
        char_move(&ewk->wu);
        add_x_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos > 0xF0) {
            ewk->wu.xyz[0].disp.pos = 0xF0;
            ewk->wu.routine_no[1]++;
            set_char_move_init(&ewk->wu, 0, 3);
        }
        break;
    case R1_TURN_L:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[1] = R1_LEFT;
            set_char_move_init(&ewk->wu, 0, 0);
            ewk->wu.mvxy.a[0].sp = -0x6000;
            ewk->wu.mvxy.d[0].sp = 0;
        }
        break;
    default:
        ewk->wu.routine_no[0] = R0_END;
        break;
    }
}



void eff29_type1(WORK_Other* ewk) {
    char_move(&ewk->wu);
    switch (ewk->wu.routine_no[2]) {
    case R2_INIT:
        ewk->wu.routine_no[2]++;
        set_char_move_init(&ewk->wu, 0, 0);
        ewk->wu.mvxy.a[0].sp = 0x4000;
        ewk->wu.mvxy.d[0].sp = 0;
    case R2_RIGHT:
        add_x_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos > 0x100) {
            ewk->wu.routine_no[2]++;
            ewk->wu.xyz[0].disp.pos = 0x100;
            ewk->wu.mvxy.a[0].sp = -0x4000;
            ewk->wu.mvxy.d[0].sp = 0;
        }
        break;
    case R2_LEFT:
        add_x_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos < 0x80) {
            ewk->wu.routine_no[2]++;
            ewk->wu.xyz[0].disp.pos = 0x80;
            ewk->wu.mvxy.a[0].sp = 0x4000;
            ewk->wu.mvxy.d[0].sp = 0;
        }
        break;
    case R2_RETURN:
        add_x_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos > 0x100) {
            ewk->wu.routine_no[2]++;
            ewk->wu.xyz[0].disp.pos = 0x100;
            set_char_move_init(&ewk->wu, 0, 1);
        }
        break;
    case R2_TURN:
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[2]++;
            ewk->wu.mvxy.a[0].sp = -0x4000;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.a[1].sp = -0x5000;
            ewk->wu.mvxy.d[1].sp = 0;
            set_char_move_init(&ewk->wu, 0, 2);
        }
        break;
    case R2_DOWN:
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos < 112) {
            ewk->wu.routine_no[2]++;
            ewk->wu.xyz[1].disp.pos = 112;
            set_char_move_init(&ewk->wu, 0, 3);
        }
        break;
    case R2_LAND:
        if (ewk->wu.cg_type) {
            ewk->wu.mvxy.a[0].sp = -0x4000;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.routine_no[2]++;
            set_char_move_init(&ewk->wu, 0, 4);
        }
        break;
    case R2_WALK:
        add_x_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos < 0xA0) {
            ewk->wu.routine_no[2]++;
            ewk->wu.xyz[0].disp.pos = 0xA0;
            set_char_move_init(&ewk->wu, 0, 5);
        }
        break;
    case R2_RISE:
        if (ewk->wu.cg_type) {
            ewk->wu.mvxy.a[0].sp = -0x4000;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.a[1].sp = 0x8000;
            ewk->wu.mvxy.d[1].sp = 0;
            ewk->wu.routine_no[2]++;
            set_char_move_init(&ewk->wu, 0, 6);
        }
        break;
    case R2_UP:
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos > 0x97) {
            ewk->wu.routine_no[2] = R2_RIGHT;
            ewk->wu.xyz[1].disp.pos = 0x97;
            ewk->wu.mvxy.a[0].sp = 0x4000;
            ewk->wu.mvxy.d[0].sp = 0;
            set_char_move_init(&ewk->wu, 0, 0);
        }
        break;
    }
}



s32 effect_29_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data_ptr = &eff29_pos_tbl[0][0];
    for (i = 0; i < 2; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 29;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.type = i;
        ewk->wu.dead_f = 1;
        ewk->wu.my_family = 2;
        ewk->wu.my_col_code = 80;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = *data_ptr++;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = *data_ptr++;
        ewk->wu.position_z = ewk->wu.my_priority = *data_ptr++;
        if (i) {
            ewk->wu.char_table[0] = eff29_type1_char_table;
        } else {
            ewk->wu.char_table[0] = eff29_type0_char_table;
        }
    }
    (void)&((WORK*)eff29_type1_char_table)->id;
    (void)&((WORK*)eff29_type0_char_table)->id;
    return 0;
}
