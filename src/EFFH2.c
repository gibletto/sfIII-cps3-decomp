/*
 * EFFH2.C  Effect H2: marker on a judge's vote panel
 *
 * effect_H2_init is called by effect 37 (EFF37.c), the panel a judge raises to show her vote,
 * with the judge and the player she supports; it uses ag_face_panel_table. effect_H2_move shows
 * pattern 0x17 + supported player once the panel is visible and moves the marker around the
 * panel through the eight offsets of panel_guide, one step every eight frames.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFH2.h"



/* my_col_code 0x2039, char index type + 0x16 */
void effect_H2_move(WORK_Other* ewk) {
    WORK* mwk = (WORK*)ewk->my_master;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 0;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2039;
        set_char_move_init2(&ewk->wu, 0, 0, ewk->wu.type + 0x11, 0);
        ewk->wu.disp_flag = 0;
        ewk->wu.direction = 7;
        ewk->wu.dir_old = 7;
        ewk->wu.dir_timer = 0;
        ewk->wu.dir_step = 0;
        break;
    case 1:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0] = 3;
            break;
        }
        if (mwk->disp_flag == 1) {
            ewk->wu.disp_flag = 1;
        }
        ewk->wu.dir_timer = ewk->wu.dir_timer + 1 & ewk->wu.dir_old;
        if (ewk->wu.dir_timer == 0) {
            ewk->wu.dir_step = ewk->wu.dir_step + 1 & ewk->wu.direction;
        }
        ewk->wu.position_x = mwk->position_x + panel_guide[ewk->wu.dir_step][0];
        ewk->wu.position_y = mwk->position_y + panel_guide[ewk->wu.dir_step][1] + 17;
        sort_push_request(&ewk->wu);
        break;
    case 2:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_H2_init(wk, gal, ohen)
WORK* wk;
u8 gal;
u8 ohen;
{
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 172;
    ewk->wu.work_id = 16;
    ewk->wu.charset_id = gal;
    ewk->wu.type = ohen;
    ewk->my_master = (u32*)wk;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_family = 2;
    ewk->wu.position_z = wk->position_z - 1;
    ewk->wu.char_table[0] = ag_face_panel_table;
    return 0;
}
