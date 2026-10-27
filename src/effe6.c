/*
 * EFFE6.C  Ending scene objects (effect E6)
 *
 * The general-purpose sprite of the character endings. effect_E6_init(char_num) reads family,
 * scene, animation, position, priority, picture and behaviour from effe6_data_tbl and records the
 * ending scene (end_w.r_no_2) it belongs to; effect_E6_move calls effe6_0000..0023 through a local
 * table: still or animated pictures, objects that move into place, scale up or down (my_mr),
 * flicker, wait for the scene or for the BG scroll, raise end_etc_flag for the ending script.
 * Every routine frees its object (routine_no[1] = 99) once the ending has moved past its scene.
 */

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
#include "PLS02.h"
#include "se_3.h"
#include "effh4.h"
#include "effe6.h"

/* routine_no[1]: states of the type routines */
#define R1_INIT         0       /* start the animation */
#define R1_MOVE         1       /* the type's main state */
#define R1_KILL         99      /* (default) put the work back */

/* routine_no[1], effe6_0001 */
#define R1_SLIDE        1       /* slide in to its place */
#define R1_REST         2       /* rest where it stopped */

/* routine_no[1], effe6_0002 */
#define R1_START        1       /* start again from its table place */
#define R1_FLY          2       /* fly along its path */

/* routine_no[1], effe6_0005 */
#define R1_WAIT         1       /* count the wait down */
#define R1_STAY         3       /* stay where it stopped */

/* routine_no[1], effe6_0006 */
#define R1_HOLD         1       /* wait for the BG scroll */
#define R1_LEAVE        2       /* fly up and away */

/* routine_no[1], effe6_0008 */
#define R1_SIGNAL       1       /* animate, signalling the script */
#define R1_LOOP         2       /* keep animating */

/* routine_no[1], effe6_0009 */
#define R1_RISE         1       /* rise to its place */

/* routine_no[1], effe6_0011 */
#define R1_BLINK        1       /* blink for 30 frames */

/* routine_no[1], effe6_0012 */
#define R1_PAUSE        2       /* pause 20 frames */
#define R1_SHRINK       3       /* shrink while settling */
#define R1_IDLE         4       /* stay where it settled */

/* routine_no[1], effe6_0014 */
#define R1_PLAY         3       /* play the animation to its cue */

/* routine_no[1], effe6_0017 */
#define R1_GROW         1       /* grow to full size, then start H4 */

/* routine_no[1], effe6_0019 */
#define R1_WALK         2       /* animate while moving to its place */

const s16 effe6_data_tbl[69][8] = {
    { 2, 0, 0, 512, 0, 80, 1, 0 },
    { 2, 0, 0, 512, 0, 82, 2, 0 },
    { 2, 0, 0, 784, 0, 82, 3, 18 },
    { 2, 0, 0, 832, 0, 80, 4, 18 },
    { 2, 0, 0, 784, 0, 82, 5, 18 },
    { 2, 0, 0, 832, 0, 80, 6, 18 },
    { 2, 0, 0, 512, 0, 82, 7, 0 },
    { 2, 0, 0, 512, 0, 80, 8, 0 },
    { 2, 0, 0, 784, 144, 80, 9, 1 },
    { 2, 0, 0, 976, 144, 82, 10, 1 },
    { 2, 0, 0, 512, 0, 80, 11, 0 },
    { 2, 0, 0, 512, 0, 82, 12, 0 },
    { 2, 1, 0, 512, 0, 80, 13, 0 },
    { 2, 1, 0, 512, 0, 82, 14, 0 },
    { 2, 1, 0, 512, 0, 82, 15, 0 },
    { 2, 1, 0, 512, 0, 80, 16, 0 },
    { 2, 0, 0, 976, 144, 82, 9, 1 },
    { 2, 0, 0, 784, 144, 80, 10, 1 },
    { 1, 0, 1, 512, 192, 80, 1, 3 },
    { 2, 0, 2, 160, 0, 88, 1, 2 },
    { 2, 0, 2, 160, 0, 81, 2, 2 },
    { 2, 0, 2, 256, 24, 87, 3, 2 },
    { 2, 0, 2, 176, 64, 87, 4, 2 },
    { 2, 0, 9, 512, 0, 87, 1, 0 },
    { 2, 0, 9, 512, 0, 80, 2, 0 },
    { 2, 0, 9, 512, 0, 80, 2, 0 },
    { 2, 0, 9, 512, -96, 80, 3, 9 },
    { 2, 0, 9, 512, 0, 80, 4, 0 },
    { 2, 0, 9, 448, 80, 80, 5, 4 },
    { 2, 0, 10, 584, 64, 80, 1, 5 },
    { 2, 0, 13, 416, 64, 80, 1, 3 },
    { 1, 0, 12, 416, 176, 70, 1, 6 },
    { 1, 2, 10, 208, 64, 82, 2, 7 },
    { 2, 1, 11, 416, 64, 80, 1, 8 },
    { 2, 0, 16, 512, -4, 74, 1, 10 },
    { 2, 0, 15, 512, 0, 74, 1, 11 },
    { 2, 1, 15, 512, 24, 74, 3, 12 },
    { 2, 1, 15, 512, 24, 74, 2, 13 },
    { 2, 1, 17, 752, 32, 74, 1, 14 },
    { 2, 0, 19, 512, 0, 74, 1, 0 },
    { 2, 0, 19, 512, 0, 74, 2, 0 },
    { 2, 0, 19, 512, 0, 74, 3, 0 },
    { 2, 0, 19, 512, 0, 74, 4, 0 },
    { 2, 0, 19, 512, 0, 73, 5, 0 },
    { 2, 0, 20, 512, 0, 74, 1, 15 },
    { 2, 0, 19, 288, 80, 74, 6, 16 },
    { 2, 1, 19, 512, 148, 74, 7, 17 },
    { 2, 0, 25, 512, 0, 80, 1, 0 },
    { 2, 0, 25, 512, 0, 78, 2, 0 },
    { 2, 0, 25, 512, 0, 76, 3, 0 },
    { 2, 0, 25, 512, 0, 78, 4, 0 },
    { 2, 0, 25, 512, 0, 80, 5, 0 },
    { 2, 1, 25, 512, 0, 82, 6, 0 },
    { 2, 1, 25, 512, 0, 76, 7, 0 },
    { 2, 1, 25, 512, 0, 78, 8, 0 },
    { 2, 1, 25, 512, 0, 80, 9, 0 },
    { 2, 1, 25, 512, 0, 76, 10, 0 },
    { 2, 0, 25, 512, 0, 80, 11, 0 },
    { 2, 0, 25, 512, 0, 78, 13, 0 },
    { 2, 0, 25, 512, 128, 76, 12, 20 },
    { 2, 0, 21, 736, 162, 90, 1, 19 },
    { 2, 0, 24, 288, 162, 90, 1, 19 },
    { 2, 0, 22, 512, 0, 76, 1, 21 },
    { 2, 0, 23, 511, 16, 76, 1, 22 },
    { 2, 0, 26, 512, 0, 76, 1, 0 },
    { 2, 1, 9, 512, 0, 87, 1, 0 },
    { 2, 1, 25, 512, 0, 80, 1, 0 },
    { 2, 1, 33, 512, 0, 78, 1, 3 },
    { 1, 2, 10, 128, 64, 82, 2, 7 },
};

void effect_E6_move(WORK_Other* ewk) {
    void (*effe6_jp[24])(WORK_Other*) = { effe6_0000, effe6_0001, effe6_0002, effe6_0003, effe6_0004, effe6_0005, effe6_0006, effe6_0007, effe6_0008, effe6_0009, effe6_0010, effe6_0011, effe6_0012, effe6_0013, effe6_0014, effe6_0015, effe6_0016, effe6_0017, effe6_0018, effe6_0019, effe6_0020, effe6_0021, effe6_0022, effe6_0023 };
    effe6_jp[ewk->wu.routine_no[0]](ewk);
}

void effe6_0000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;
    case R1_MOVE:
        if (ewk->wu.old_rno[6] < end_w.r_no_2) {
            ewk->wu.routine_no[1] = R1_KILL;
        } else {
            disp_pos_trans_entry(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}

void effe6_0001(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        switch (ewk->wu.type) {
        case 2:
        case 4:
            ewk->wu.old_rno[3] = 0x200;
            ewk->wu.mvxy.a[0].sp = -0x60000;
            ewk->wu.mvxy.a[1].sp = 0;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.d[1].sp = 0;
            break;
        case 3:
        case 5:
            ewk->wu.old_rno[3] = 0x200;
            ewk->wu.mvxy.a[0].sp = -0x40000;
            ewk->wu.mvxy.a[1].sp = 0;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.d[1].sp = 0;
            break;
        case 8:
        case 9:
        case 16:
        case 17:
            ewk->wu.old_rno[3] = 0xA0;
            ewk->wu.mvxy.a[0].sp = -0x200000;
            ewk->wu.mvxy.a[1].sp = 0x40000;
            ewk->wu.mvxy.d[0].sp = -0x800;
            ewk->wu.mvxy.d[1].sp = -0x6000;
            break;
        }
        break;
    case R1_SLIDE:
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.old_rno[3] > ewk->wu.xyz[0].disp.pos) {
            ewk->wu.routine_no[1]++;
        }
    case R1_REST:
        if (ewk->wu.old_rno[6] < end_w.r_no_2) {
            ewk->wu.routine_no[1] = R1_KILL;
        } else {
            disp_pos_trans_entry(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}

void effe6_0002(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
    case R1_START:
        ewk->wu.routine_no[1]++;
        ewk->wu.xyz[0].disp.pos = effe6_data_tbl[ewk->wu.type][3];
        ewk->wu.xyz[1].disp.pos = effe6_data_tbl[ewk->wu.type][4];
        switch (ewk->wu.type) {
        case 19:
            ewk->wu.old_rno[3] = 0x380;
            ewk->wu.mvxy.a[0].sp = 0xA0000;
            ewk->wu.mvxy.a[1].sp = 0x20000;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.d[1].sp = 0;
            break;
        case 20:
            ewk->wu.old_rno[3] = 0x330;
            ewk->wu.mvxy.a[0].sp = 0xA0000;
            ewk->wu.mvxy.a[1].sp = 0x20000;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.d[1].sp = 0;
            break;
        case 21:
            ewk->wu.old_rno[3] = 0x330;
            ewk->wu.mvxy.a[0].sp = 0xA0000;
            ewk->wu.mvxy.a[1].sp = 0x20000;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.d[1].sp = 0;
            break;
        case 22:
            ewk->wu.old_rno[3] = 0x350;
            ewk->wu.mvxy.a[0].sp = 0x40000;
            ewk->wu.mvxy.a[1].sp = -0x10000;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.d[1].sp = 0;
            break;
        }
        break;
    case R1_FLY:
        if (ewk->wu.old_rno[6] < end_w.r_no_2) {
            ewk->wu.routine_no[1] = R1_KILL;
        } else {
            if (ewk->wu.old_rno[3] > ewk->wu.xyz[0].disp.pos) {
                add_x_sub(ewk);
                add_y_sub(ewk);
            } else {
                ewk->wu.routine_no[1] = R1_START;
            }
            disp_pos_trans_entry(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}

void effe6_0003(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        break;
    case R1_MOVE:
        if (ewk->wu.old_rno[6] < end_w.r_no_2) {
            ewk->wu.routine_no[1] = R1_KILL;
        } else {
            char_move(&ewk->wu);
            disp_pos_trans_entry(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}

void effe6_0004(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        ewk->wu.my_mr_flag = 1;
        ewk->wu.my_mr.size.x = 16;
        ewk->wu.my_mr.size.y = 16;
        ewk->wu.mvxy.a[0].sp = 0x18000;
        ewk->wu.mvxy.d[0].sp = 0x100;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    case R1_MOVE:
        if (ewk->wu.old_rno[6] < end_w.r_no_2) {
            ewk->wu.routine_no[1] = R1_KILL;
        } else {
            if (ewk->wu.my_mr.size.x < 63) {
                ewk->wu.my_mr.size.x++;
                ewk->wu.my_mr.size.y++;
                add_x_sub(ewk);
            }
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            sort_push_request4(&ewk->wu);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}

void effe6_0005(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        ewk->wu.old_rno[5] = 12;
        disp_pos_trans_entry(ewk);
        break;
    case R1_WAIT:
        ewk->wu.old_rno[5]--;
        if (ewk->wu.old_rno[5] < 0) {
            ewk->wu.routine_no[1]++;
            ewk->wu.old_rno[5] = 4;
            cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[5], 0x210, 16, 1, 1);
        }
        disp_pos_trans_entry(ewk);
        break;
    case R1_FLY:
        ewk->wu.old_rno[5]--;
        if (ewk->wu.old_rno[5] <= 0) {
            ewk->wu.routine_no[1]++;
        } else {
            add_x_sub(ewk);
            add_y_sub(ewk);
        }
        disp_pos_trans_entry(ewk);
        break;
    case R1_STAY:
        disp_pos_trans_entry(ewk);
        return;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



void effe6_0006(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        ewk->wu.mvxy.a[0].sp = 0x20000;
        ewk->wu.mvxy.a[1].sp = 0x8000;
        ewk->wu.mvxy.d[0].sp = 0;
        ewk->wu.mvxy.d[1].sp = -0x180;
        disp_pos_trans_entry(ewk);
        break;
    case R1_HOLD:
        if (ewk->wu.old_rno[0] != end_w.r_no_2) {
            ewk->wu.routine_no[1] = R1_KILL;
        } else {
            if (bg_w.bgw[0].r_no_1 > 1) {
                ewk->wu.routine_no[1]++;
            }
            disp_pos_trans_entry(ewk);
        }
        break;
    case R1_LEAVE:
        if (ewk->wu.old_rno[0] != end_w.r_no_2) {
            ewk->wu.routine_no[1] = R1_KILL;
        } else {
            add_x_sub(ewk);
            add_y_sub(ewk);
            char_move(&ewk->wu);
            if (ewk->wu.xyz[1].disp.pos > 0x3F0) {
                ewk->wu.routine_no[1]++;
            }
            disp_pos_trans_entry(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}

const s16 effe6_0007_col_tbl[4] = { 208, 128, 160, 64 };

void effe6_0007(WORK_Other* ewk) {
    s16 ix;
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        ewk->wu.old_rno[3] = effe6_data_tbl[ewk->wu.type][3];
    case R1_START:
        ewk->wu.routine_no[1]++;
        ewk->wu.my_mr_flag = 1;
        ewk->wu.my_mr.size.x = 63;
        ewk->wu.my_mr.size.y = 63;
        ewk->wu.mvxy.a[0].sp = 0x38000;
        ewk->wu.mvxy.d[0].sp = 0;
        ewk->wu.old_rno[1] = 0;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = ewk->wu.old_rno[3];
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = effe6_data_tbl[ewk->wu.type][4];
        sort_push_request4(&ewk->wu);
        break;
    case R1_FLY:
        add_x_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos > 0x310) {
            ewk->wu.routine_no[1] = R1_START;
            ix = random_16_com();
            ix &= 3;
            ewk->wu.old_rno[3] = effe6_0007_col_tbl[ix];
        } else {
            if (ewk->wu.my_mr.size.x > 0) {
                ewk->wu.old_rno[1]++;
                ewk->wu.old_rno[1] &= 3;
                if (!ewk->wu.old_rno[1]) {
                    ewk->wu.my_mr.size.x--;
                    ewk->wu.my_mr.size.y--;
                }
            }
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            sort_push_request4(&ewk->wu);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}




void effe6_0008(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;
    case R1_SIGNAL:
        char_move(&ewk->wu);
        switch (ewk->wu.cg_type) {
        case 1:
            end_etc_flag = 1;
            ewk->wu.cg_type = 0;
            break;
        case 0xFF:
            ewk->wu.routine_no[1]++;
            end_etc_flag = 2;
            ewk->wu.cg_type = 0;
            set_char_move_init(&ewk->wu, 0, 13);
            break;
        }
        disp_pos_trans_entry(ewk);
        break;
    case R1_LOOP:
        char_move(&ewk->wu);
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}


void effe6_0009(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        ewk->wu.mvxy.a[1].sp = 0x20000;
        ewk->wu.mvxy.d[1].sp = 0;
        disp_pos_trans_entry(ewk);
        break;
    case R1_RISE:
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos > 0) {
            ewk->wu.xyz[1].cal = 0;
            ewk->wu.routine_no[1]++;
        }
    case R1_REST:
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



void effe6_0010(WORK_Other* ewk) {
    switch (end_w.r_no_2) {
    case 0:
    case 1:
        switch (ewk->wu.routine_no[1]) {
        case R1_INIT:
            effe6_init_common(ewk);
            ewk->wu.mvxy.a[1].sp = -0x8000;
            ewk->wu.mvxy.d[1].sp = 0;
            disp_pos_trans_entry(ewk);
            break;
        case R1_MOVE:
            char_move(&ewk->wu);
            disp_pos_trans_entry(ewk);
            break;
        }
        break;
    case 2:
        if (ewk->wu.xyz[1].disp.pos > -128) {
            add_y_sub(ewk);
        }
        char_move(&ewk->wu);
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}

void effe6_0011(WORK_Other* ewk) {
    switch (end_w.r_no_2) {
    case 0:
    case 1:
        switch (ewk->wu.routine_no[1]) {
        case R1_INIT:
            effe6_init_common(ewk);
            ewk->wu.disp_flag = 2;
            ewk->wu.blink_timing = 1;
            ewk->wu.old_rno[5] = 30;
        case R1_BLINK:
            ewk->wu.old_rno[5]--;
            if (ewk->wu.old_rno[5] < 0) {
                ewk->wu.routine_no[1]++;
                ewk->wu.disp_flag = 1;
            }
        case R1_REST:
            disp_pos_trans_entry(ewk);
            break;
        }
        break;
    case 2:
        ewk->wu.disp_flag = 2;
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}

void effe6_0012(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        ewk->wu.my_mr_flag = 1;
        ewk->wu.my_mr.size.x = 63;
        ewk->wu.my_mr.size.y = 63;
        ewk->wu.mvxy.a[1].sp = 0x10000;
        ewk->wu.mvxy.d[1].sp = 0;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    case R1_RISE:
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos > 80) {
            ewk->wu.routine_no[1]++;
            ewk->wu.old_rno[5] = 20;
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    case R1_PAUSE:
        ewk->wu.old_rno[5]--;
        if (ewk->wu.old_rno[5] < 0) {
            ewk->wu.routine_no[1]++;
            ewk->wu.old_rno[5] = 120;
            ewk->wu.old_rno[2] = 0;
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    case R1_SHRINK:
        if (ewk->wu.xyz[1].disp.pos < 0x88) {
            add_y_sub(ewk);
        }
        ewk->wu.old_rno[5]--;
        if (ewk->wu.old_rno[5] < 0) {
            ewk->wu.routine_no[1]++;
        } else {
            ewk->wu.old_rno[2]++;
            ewk->wu.old_rno[2] &= 3;
            if (!ewk->wu.old_rno[2]) {
                ewk->wu.my_mr.size.x--;
                ewk->wu.my_mr.size.y--;
            }
        }
    case R1_IDLE:
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


void effe6_0013(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        ewk->wu.my_mr_flag = 1;
        ewk->wu.my_mr.size.x = 83;
        ewk->wu.my_mr.size.y = 83;
        ewk->wu.mvxy.a[1].sp = 0x10000;
        ewk->wu.mvxy.d[1].sp = 0;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    case R1_RISE:
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos > 80) {
            ewk->wu.routine_no[1]++;
            ewk->wu.old_rno[5] = 20;
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    case R1_PAUSE:
        ewk->wu.old_rno[5]--;
        if (ewk->wu.old_rno[5] < 0) {
            ewk->wu.routine_no[1]++;
            ewk->wu.old_rno[5] = 120;
            ewk->wu.old_rno[2] = 0;
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    case R1_SHRINK:
        if (ewk->wu.xyz[1].disp.pos < 0x88) {
            add_y_sub(ewk);
        }
        ewk->wu.old_rno[5]--;
        if (ewk->wu.old_rno[5] < 0) {
            ewk->wu.routine_no[1]++;
        } else {
            ewk->wu.old_rno[2]++;
            ewk->wu.old_rno[2] &= 3;
            if (!ewk->wu.old_rno[2]) {
                ewk->wu.my_mr.size.x--;
                ewk->wu.my_mr.size.y--;
            }
        }
    case R1_IDLE:
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


void effe6_0014(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        ewk->wu.old_rno[5] = 60;
        disp_pos_trans_entry(ewk);
        break;
    case R1_WAIT:
        ewk->wu.old_rno[5]--;
        if (ewk->wu.old_rno[5] < 0) {
            ewk->wu.routine_no[1]++;
            ewk->wu.old_rno[5] = 0x120;
            cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[5], 0x1E0, 96, 0, 0);
        }
        disp_pos_trans_entry(ewk);
        break;
    case R1_FLY:
        ewk->wu.old_rno[5]--;
        if (ewk->wu.old_rno[5] < 0) {
            ewk->wu.routine_no[1]++;
        } else {
            add_x_sub(ewk);
            add_y_sub(ewk);
        }
        disp_pos_trans_entry(ewk);
        break;
    case R1_PLAY:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[1]++;
        }
        disp_pos_trans_entry(ewk);
        break;
    case R1_IDLE:
        disp_pos_trans_entry(ewk);
        return;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}


void effe6_0015(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        break;
    case R1_MOVE:
        if (bg_w.bgw[0].r_no_1 > 1) {
            char_move(&ewk->wu);
        }
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}

void effe6_0016(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        ewk->wu.mvxy.a[0].sp = 0x78000;
        ewk->wu.mvxy.d[0].sp = 0;
        ewk->wu.mvxy.a[1].sp = 0x30000;
        ewk->wu.mvxy.d[1].sp = -0x1000;
        break;
    case R1_MOVE:
        add_y_sub(ewk);
        add_x_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos > 0x300) {
            ewk->wu.routine_no[1] = R1_KILL;
        }
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}

void effe6_0017(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        ewk->wu.my_mr_flag = 1;
        ewk->wu.my_mr.size.x = 10;
        ewk->wu.my_mr.size.y = 10;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    case R1_GROW:
        ewk->wu.my_mr.size.x++;
        ewk->wu.my_mr.size.y++;
        if (ewk->wu.my_mr.size.x == 63) {
            ewk->wu.routine_no[1]++;
            set_char_move_init2(&ewk->wu, 0, 19, 8, 0);
            effect_H4_init();
        }
    case R1_REST:
        sort_push_request4(&ewk->wu);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}

void effe6_0018(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        ewk->wu.old_rno[3] = 120;
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[3], 0x200, 0, 2, 2);
        disp_pos_trans_entry(ewk);
        break;
    case R1_SLIDE:
        ewk->wu.old_rno[3]--;
        if (ewk->wu.old_rno[3] > 0) {
            add_x_sub(ewk);
        } else {
            ewk->wu.routine_no[1]++;
        }
    case R1_REST:
        if (ewk->wu.old_rno[6] < end_w.r_no_2) {
            ewk->wu.routine_no[1] = R1_KILL;
        } else {
            disp_pos_trans_entry(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}

void effe6_0019(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.my_col_code |= 0x2000;
        effe6_init_common(ewk);
        ewk->wu.old_rno[2] = 0xF0;
        ewk->wu.old_rno[3] = 0xC8;
        if (ewk->wu.type == 60) {
            cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[3], 0x272, 0, 2, 2);
        } else {
            cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[3], 0x18E, 0, 2, 2);
        }
        disp_pos_trans_entry(ewk);
        break;
    case R1_WAIT:
        ewk->wu.old_rno[2]--;
        if (ewk->wu.old_rno[2] < 0) {
            ewk->wu.routine_no[1]++;
        }
        disp_pos_trans_entry(ewk);
        break;
    case R1_WALK:
        char_move(&ewk->wu);
        ewk->wu.old_rno[3]--;
        if (ewk->wu.old_rno[3] > 0) {
            add_x_sub(ewk);
        } else {
            ewk->wu.routine_no[1]++;
        }
        disp_pos_trans_entry(ewk);
        break;
    case R1_STAY:
        disp_pos_trans_entry(ewk);
        return;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}


void effe6_0020(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        ewk->wu.mvxy.a[0].sp = 0x4000;
        ewk->wu.mvxy.d[0].sp = 0;
        disp_pos_trans_entry(ewk);
        break;
    case R1_SLIDE:
        add_x_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos > 0x230) {
            ewk->wu.routine_no[1]++;
        }
    case R1_REST:
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}


void effe6_0021(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        break;
    case R1_MOVE:
        if (ewk->wu.old_rno[0] != end_w.r_no_2) {
            ewk->wu.routine_no[1] = R1_KILL;
        } else {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                end_etc_flag = 1;
            }
            disp_pos_trans_entry(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}


void effe6_0022(WORK_Other* ewk) {
    if (ewk->wu.old_rno[0] != end_w.r_no_2) {
        ewk->wu.routine_no[1] = R1_KILL;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        ewk->wu.mvxy.a[1].sp = 0x4000;
        ewk->wu.mvxy.d[1].sp = 0;
        break;
    case R1_MOVE:
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos > 0x140) {
            ewk->wu.routine_no[1]++;
        } else {
            disp_pos_trans_entry(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}

void effe6_0023(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        effe6_init_common(ewk);
        break;
    case R1_MOVE:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[1]++;
        } else {
            disp_pos_trans_entry(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



void effe6_init_common(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;
    ewk->wu.disp_flag = 1;
    set_char_move_init2(&ewk->wu, 0, ewk->wu.old_rno[4], ewk->wu.char_index, 0);
}

s32 effect_E6_init(u8 char_num) {
    WORK_Other* ewk;
    s16 ix;
    const s16* data_ptr;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.id = 146;
    ewk->wu.be_flag = 1;
    ewk->wu.type = char_num;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.old_rno[0] = end_w.r_no_2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.char_table[0] = effH3_char_table;
    ewk->wu.my_col_code = 32;
    data_ptr = &effe6_data_tbl[char_num][0];
    ewk->wu.my_family = *data_ptr++;
    ewk->wu.old_rno[6] = *data_ptr++;
    ewk->wu.old_rno[6] += end_w.r_no_2;
    ewk->wu.old_rno[4] = *data_ptr++;
    ewk->wu.xyz[0].disp.pos = *data_ptr++;
    ewk->wu.xyz[1].disp.pos = *data_ptr++;
    ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
    ewk->wu.char_index = *data_ptr++;
    ewk->wu.old_rno[1] = ewk->wu.char_index - 1;
    ewk->wu.routine_no[0] = *data_ptr;
    return 0;
}
