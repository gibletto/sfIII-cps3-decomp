/*
 * EFFC3.C  Effect C3 (123): a stage 8 background object
 *
 * effect_C3_init(type) creates the object for the stage 8 backgrounds. Type 0 rides on
 * background layer 1: it waits for bg_w.bgw[1].r_no_1 to reach 1, then rises with the layer and
 * keeps stage8_base_y at its height. Other types start at 0x200,0x180, rise until y 40 and then
 * set bg_land_flag, which effect C2's objects wait for.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFC3.h"

/* routine_no[0], types 1 and up */
#define R0_INIT         0       /* set up and show */
#define R0_RISE         1       /* rise until y 40, then land */
#define R0_KILL         2       /* (default) put the work back */

/* routine_no[0], type 0 */
#define R0_WAIT         1       /* wait for background layer 1 */
#define R0_RIDE         2       /* rise with the layer */
#define R0_RIDE_KILL    3       /* (default) put the work back */

extern const u32 eff45_char_table[];    /* provisional name */



void effect_C3_move(WORK_Other* ewk) {
    if (ewk->wu.type) {
        switch (ewk->wu.routine_no[0]) {
        case R0_INIT:
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 1;
            set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 0x200;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 0x180;
            ewk->wu.mvxy.a[1].sp = -0xA8000;
            ewk->wu.mvxy.d[1].sp = -0x1000;
            bg_land_flag = 0;
            break;
        case R0_RISE:
            if (EXE_flag == 0 && Game_pause == 0) {
                add_y_sub(ewk);
                if (ewk->wu.xyz[1].disp.pos < 40) {
                    ewk->wu.routine_no[0]++;
                    bg_land_flag = 1;
                }
            }
            disp_pos_trans_entry(ewk);
            break;
        default:
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
            return;
        }
    } else {
        switch (ewk->wu.routine_no[0]) {
        case R0_INIT:
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 1;
            set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
            stage8_base_y = ewk->wu.xyz[1].disp.pos;
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 0x200;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 40;
            break;
        case R0_WAIT:
            if (bg_w.bgw[1].r_no_1 == 1) {
                ewk->wu.routine_no[0]++;
                ewk->wu.mvxy.a[1].sp = -0x68000;
                ewk->wu.mvxy.d[1].sp = -0xA80;
            }
            disp_pos_trans_entry(ewk);
            stage8_base_y = ewk->wu.xyz[1].disp.pos;
            break;
        case R0_RIDE:
            if (EXE_flag == 0 && Game_pause == 0) {
                if (bg_w.bgw[1].r_no_1 < 2) {
                    add_y_sub(ewk);
                } else {
                    ewk->wu.routine_no[0]++;
                }
            }
            disp_pos_trans_entry(ewk);
            stage8_base_y = ewk->wu.xyz[1].disp.pos;
            break;
        default:
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
            return;
        }
    }
}



s32 effect_C3_init(u8 type) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 123;
    ewk->wu.type = type;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.disp_flag = 0;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.my_priority = ewk->wu.position_z = 76;
    ewk->wu.char_index = 0;
    ewk->wu.xyz[0].disp.low = 0;
    ewk->wu.xyz[1].disp.low = 0;
    *ewk->wu.char_table = eff45_char_table;
    return 0;
}
