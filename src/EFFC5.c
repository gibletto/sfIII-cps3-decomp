/*
 * EFFC5.C  Effect C5: the car of the car entrance
 *
 * Effect C5 is the car used by the entrance routine Appear_06000 (appear.c). effect_C5_init
 * places it off-screen on the player's side (distance by Game_setting), aims it at a stop point
 * 60 frames away and spawns its C6 child. effect_C5_move drives in with the engine sound,
 * brakes (with a demo sound), raises demo_car_flag while its door pattern plays, then drives
 * away over 48 frames and frees itself. The player number chooses the side;
 * voices are at player * 0x200.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFC6.h"
#include "ta_sub.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFFC5.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the engine sound */
#define R0_DRIVE        1       /* drive in to the stop point */
#define R0_DOOR         2       /* play the door pattern */
#define R0_WAIT         3       /* wait 20 frames */
#define R0_LEAVE        4       /* drive away */
#define R0_END          5       /* clear the door flag */
#define R0_KILL         6       /* (default) put the work back */

void effect_C5_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        Sound_SE(0x134);
        break;
    case R0_DRIVE:
        char_move(&ewk->wu);
        ewk->wu.old_rno[0]--;
        if (ewk->wu.old_rno[0] <= 0) {
            ewk->wu.routine_no[0]++;
            set_char_move_init(&ewk->wu, 0, 9);
            if (Demo_Sound != 0 || Demo_Flag != 0) {
                sound_request_pan(0x135, 0x40, 0x40, 0, 2);
            }
        } else {
            add_x_sub(ewk);
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case R0_DOOR:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[0]++;
            ewk->wu.old_rno[0] = 20;
        } else if (ewk->wu.cg_type == 2) {
            demo_car_flag[ewk->master_id] = 1;
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case R0_WAIT:
        ewk->wu.old_rno[0]--;
        if (ewk->wu.old_rno[0] < 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.old_rno[0] = 48;
            if (ewk->wu.rl_flag != 0) {
                ewk->wu.mvxy.a[0].sp = -0x20000;
                ewk->wu.mvxy.d[0].sp = -0x1000;
            } else {
                ewk->wu.mvxy.a[0].sp = 0x20000;
                ewk->wu.mvxy.d[0].sp = 0x1000;
            }
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case R0_LEAVE:
        ewk->wu.old_rno[0]--;
        if (ewk->wu.old_rno[0] < 0) {
            ewk->wu.routine_no[0]++;
        } else {
            add_x_sub(ewk);
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case R0_END:
        ewk->wu.routine_no[0]++;
        demo_car_flag[ewk->master_id] = 0;
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* The car for player pl. */
/* provisional name */
s32 effC5_init_sub(s16 pl) {
    WORK_Other* ewk;
    s16 ix;
    s16 work;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    demo_car_flag[pl] = 0;
    ewk->wu.be_flag = 1;
    ewk->wu.id = 125;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.disp_flag = 0;
    ewk->wu.my_family = 2;
    ewk->wu.char_index = 8;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_priority = ewk->wu.position_z = 57;
    *ewk->wu.char_table = etc_char_table;
    ewk->wu.my_col_code = plw[pl].wu.my_col_code + 6;
    ewk->wu.sync_suzi = 0;
    ewk->master_id = pl;
    if (pl) {
        ewk->wu.xyz[0].disp.low = 0;
        ewk->wu.xyz[1].cal = 0;
        ewk->wu.rl_flag = 0;
        ewk->wu.old_rno[0] = 60;
        if (Game_setting.mode) {
            work = (bg_w.bgw[1].pos_x_work + 208) & 0x3FF;
            ewk->wu.xyz[0].disp.pos = (bg_w.bgw[1].pos_x_work + 352) & 0x3FF;
        } else {
            work = (bg_w.bgw[1].pos_x_work + 168) & 0x3FF;
            ewk->wu.xyz[0].disp.pos = (bg_w.bgw[1].pos_x_work + 304) & 0x3FF;
        }
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[0], work, 0, 1, 1);
    } else {
        ewk->wu.xyz[1].cal = 0;
        ewk->wu.xyz[0].disp.low = 0;
        ewk->wu.rl_flag = 1;
        ewk->wu.old_rno[0] = 60;
        if (Game_setting.mode) {
            work = (bg_w.bgw[1].pos_x_work - 216) & 0x3FF;
            ewk->wu.xyz[0].disp.pos = (bg_w.bgw[1].pos_x_work - 352) & 0x3FF;
        } else {
            work = (bg_w.bgw[1].pos_x_work - 168) & 0x3FF;
            ewk->wu.xyz[0].disp.pos = (bg_w.bgw[1].pos_x_work - 304) & 0x3FF;
        }
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[0], work, 0, 1, 1);
    }
    suzi_offset_set(&ewk->wu);
    return effect_C6_init(ewk);
}



/* Create the car on the player's side. */
s32 effect_C5_init(PLW* oya) {
    s16 pl = oya->wu.id ? 1 : 0;
    return effC5_init_sub(pl);
}
