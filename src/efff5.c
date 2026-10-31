/*
 * EFFF5.C  Opening demo picture objects (effect F5)
 *
 * Sprites used by the attract-mode opening. effect_F5_init(type) reads routine, position,
 * priority and animation from efff5_data_tbl; effect_F5_move dispatches to efff5_0000-0005:
 * play once and raise the opening's free_work flag, play until the opening reaches step 15,
 * scroll downward with wrap, loop an animation, a still frame, and triple-speed playback.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "efff5.h"

/* routine_no[1]: states of the picture routines */
#define R1_INIT         0       /* start the animation */
#define R1_MOVE         1       /* the type's main state */
#define R1_KILL         2       /* (default) put the work back */

/* routine, x, y, priority, pattern, hit_stop */
const s16 efff5_data_tbl[14][6] = {
    { 0, 512, 48, 50, 52, 1 },
    { 0, 512, 48, 50, 54, 1 },
    { 1, 512, 40, 52, 62, 1 },
    { 0, 512, 48, 50, 57, 1 },
    { 2, 512, 64, 78, 58, 1 },
    { 2, 512, 0, 78, 58, 1 },
    { 0, 512, 48, 50, 63, 1 },
    { 0, 512, 48, 50, 64, 1 },
    { 3, 512, 53, 52, 58, 1 },
    { 4, 653, 70, 52, 66, 1 },
    { 5, 512, 48, 50, 52, 1 },
    { 5, 512, 48, 50, 54, 1 },
    { 5, 512, 48, 50, 63, 1 },
    { 5, 512, 48, 50, 64, 1 },
};



void effect_F5_move(WORK_Other* ewk) {
    void (*efff5_jp[6])(WORK_Other*) = { efff5_0000, efff5_1000, efff5_2000, efff5_3000, efff5_4000, efff5_5000 };
    efff5_jp[ewk->wu.routine_no[0]](ewk);
}



void efff5_0000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R1_MOVE:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 0xFF) {
            ewk->wu.routine_no[1]++;
            op_w.free_work = 1;
        } else {
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            sort_push_request4(&ewk->wu);
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



void efff5_1000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R1_MOVE:
        char_move(&ewk->wu);
        if (op_w.r_no_0 == 15) {
            ewk->wu.routine_no[1]++;
            op_w.free_work = 1;
        } else {
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            sort_push_request4(&ewk->wu);
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



void efff5_2000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R1_MOVE:
        ewk->wu.xyz[1].disp.pos += 2;
        if (ewk->wu.xyz[1].disp.pos > 96) {
            ewk->wu.xyz[1].disp.pos = 0;
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    }
}



void efff5_3000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R1_MOVE:
        char_move(&ewk->wu);
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



void efff5_4000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        break;
    case R1_MOVE:
        sort_push_request4(&ewk->wu);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



void efff5_5000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R1_MOVE:
        char_move(&ewk->wu);
        char_move(&ewk->wu);
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 0xFF) {
            ewk->wu.routine_no[1]++;
            op_w.free_work = 1;
        } else {
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            sort_push_request4(&ewk->wu);
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_F5_init(s16 type) {
    WORK_Other* ewk;
    s16 ix;
    const s16* data_ptr;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    data_ptr = efff5_data_tbl[type];
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.id = 155;
    ewk->wu.be_flag = 1;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 64;
    ewk->wu.char_table[0] = etc_char_table;
    ewk->wu.old_rno[0] = type;
    ewk->wu.routine_no[0] = *data_ptr++;
    ewk->wu.xyz[0].disp.pos = *data_ptr++;
    ewk->wu.xyz[1].disp.pos = *data_ptr++;
    ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
    ewk->wu.char_index = *data_ptr++;
    ewk->wu.hit_stop = *data_ptr;
    return 0;
}
