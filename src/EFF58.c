/*
 * EFF58.C  Effect 58: timed screen commands
 *
 * Effect 58 is a timer: after time0 frames it performs one of 11 screen commands - stop a scroll,
 * screen switch or fill, scroll BG 0 for 180 frames (EFF58_Type_04), sound and BGM requests, or
 * put a screen cell list (sc_celllist_put_scr); command 7 does nothing. Used by the game flow,
 * select, continue and ranking screens (Game_Main, Manage, Win, sel_pl, next_cpu, ...).
 * EFF58_Type_05 is the type routine for a marker that follows the player.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "win_2.h"
#include "continue.h"
#include "pow_pow.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "Eff59.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "sc_trans.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "aboutspr.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFF58.h"
#include "sc_logo.h"

/* routine_no[0] */
#define R0_WAIT         0       /* count the start time down */
#define R0_MOVE         1       /* carry out the command */
#define R0_KILL         99      /* (default) put the work back */

/* routine_no[1]: command, from effect_58_init */
#define R1_STOP         0       /* stop the scroll */
#define R1_SWITCH       1       /* switch the screen back after the cover */
#define R1_SIGN         2       /* show a sign */
#define R1_CLEAR        3       /* clear the screen and tone it down */
#define R1_WIN_SCROLL   4       /* scroll BG 0 for the winner */
#define R1_AREA         5       /* marker that follows the player */
#define R1_SOUND        6       /* sound request */
#define R1_NONE         7       /* do nothing */
#define R1_BGM          8       /* music request */
#define R1_FADE_IN      9       /* fade the music in */
#define R1_CELLS        10      /* put a screen cell list */

/* routine_no[2], EFF58_Type_01 */
#define R2_WAIT         0       /* count the cover time down */
#define R2_SWITCH       1       /* until the screen is back */

/* routine_no[2], EFF58_Type_02 */
#define R2_INIT         0       /* first frame: set up */
#define R2_SHOW         1       /* stay on screen */

/* routine_no[2], EFF58_Type_04 */
#define R2_SCROLL       1       /* scroll BG 0 for its time */

/* routine_no[2], EFF58_Type_05 */
#define R2_FOLLOW       1       /* follow the player */



void effect_58_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_WAIT:
        if (--ewk->wu.dir_timer == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case R0_MOVE:
        switch (ewk->wu.routine_no[1]) {
        case R1_STOP:
            Scrn_Move_Set(4, 0, 0);
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        case R1_SWITCH:
            EFF58_Type_01(ewk);
            break;
        case R1_SIGN:
            EFF58_Type_02(ewk);
            break;
        case R1_CLEAR:
            EFF58_Type_03(ewk);
            break;
        case R1_WIN_SCROLL:
            EFF58_Type_04(ewk);
            break;
        case R1_AREA:
            EFF58_Type_05(ewk);
            break;
        case R1_SOUND:
            if (Demo_Sound != 0 || Demo_Flag) {
                sound_request(ewk->wu.direction);
            }
            push_effect_work(&ewk->wu);
            break;
        case R1_NONE:
            break;
        case R1_BGM:
            if (Demo_Sound != 0 || Demo_Flag != 0) {
                if (PB_Music_Off == 0) {
                    BGM_Request(ewk->wu.direction);
                }
            }
            push_effect_work(&ewk->wu);
            break;
        case R1_FADE_IN:
            if (Demo_Sound != 0 || Demo_Flag) {
                if (!PB_Music_Off) {
                    sound_fade_in_submit(ewk->wu.direction, 0x222);
                }
            }
            push_effect_work(&ewk->wu);
            break;
        case R1_CELLS:
            sc_celllist_put_scr(ewk->wu.direction);
            push_effect_work(&ewk->wu);
            break;
        }
        break;
    default:
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_58_init(s16 id, s16 time0, s16 option) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 58;
    ewk->wu.work_id = 16;
    ewk->wu.dir_timer = time0;
    ewk->wu.dir_old = time0;
    ewk->wu.direction = option;
    ewk->wu.routine_no[1] = id;
    return 0;
}



/* provisional name */
s32 effect_58_area_init(s16 time0, s16 step) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 58;
    ewk->wu.work_id = 16;
    ewk->wu.dir_timer = 1;
    ewk->wu.dir_old = time0;
    ewk->wu.dir_step = step;
    ewk->wu.routine_no[1] = R1_AREA;
    return 0;
}



void EFF58_Type_01(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case R2_WAIT:
        if (--Cover_Timer) {
            break;
        }
        ewk->wu.routine_no[2]++;
        Switch_Screen_Init(0, 0);
        break;
    case R2_SWITCH:
        if (Switch_Screen_Revival()) {
            ewk->wu.routine_no[0] = R0_KILL;
        }
        break;
    }
}



void EFF58_Type_03(WORK_Other* ewk) {
    tilemap_fill_all(0, 32);
    ToneDown(0);
    ewk->wu.routine_no[0] = R0_KILL;
}



void EFF58_Type_02(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case R2_INIT:
        ewk->wu.routine_no[2]++;
        ewk->wu.cgromtype = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2043;
        ewk->wu.my_family = 2;
        ewk->wu.xyz[0].disp.pos = bg_w.bgw[1].position_x + DE_X[10] + 0xC0;
        ewk->wu.xyz[1].disp.pos = bg_w.bgw[1].position_y;
        ewk->wu.my_priority = 40;
        ewk->wu.position_z = 40;
        ewk->wu.dir_step = 28;
        ewk->wu.char_index = 9;
        ewk->wu.char_table[0] = sel_pl_char_table;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
        break;
    case R2_SHOW:
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}


void EFF58_Type_04(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case R2_INIT:
        ewk->wu.routine_no[2]++;
        ewk->wu.dir_timer = 180;
        if (WINNER == 0) {
            ewk->wu.mvxy.a[0].sp = 0x2000;
        } else {
            ewk->wu.mvxy.a[0].sp = -0x2000;
        }
        break;
    case R2_SCROLL:
        if (--ewk->wu.dir_timer == 0) {
            ewk->wu.routine_no[1]++;
            win_slide_flag = 0;
            break;
        }
        bg_w.bgw[0].xy[0].cal += ewk->wu.mvxy.a[0].sp;
        bg_w.bgw[0].old_pos_x = bg_w.bgw[0].xy[0].disp.pos;
        bg_w.bgw[0].hos_xy[0].disp.pos = bg_w.bgw[0].wxy[0].disp.pos = bg_w.bgw[0].xy[0].disp.pos;
        suzi_line_calc(0);
        bg_pos_hosei2();
        Bg_Family_Set();
        break;
    }
}


void EFF58_Type_05(WORK_Other* ewk) {
    s16 x;
    switch (ewk->wu.routine_no[2]) {
    case R2_INIT:
        ewk->wu.routine_no[2]++;
        ewk->wu.cgromtype = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2040;
        ewk->wu.my_family = 2;
        ewk->wu.my_priority = plw[ewk->wu.dir_old].wu.my_priority - 10;
        ewk->wu.position_z = plw[ewk->wu.dir_old].wu.position_z - 10;
        ewk->wu.char_index = 26;
        ewk->wu.char_table[0] = sel_pl_char_table;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 11, 0);
        break;
    case R2_FOLLOW:
        x = Separate_Area[ewk->wu.dir_old][ewk->wu.dir_step - 1];
        if (plw[ewk->wu.dir_old].wu.rl_waza == 0) {
            x = -x;
        }
        ewk->wu.xyz[0].disp.pos = plw[ewk->wu.dir_old].wu.xyz[0].disp.pos + x;
        ewk->wu.xyz[1].disp.pos = plw[ewk->wu.dir_old].wu.xyz[1].disp.pos + 32;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}

