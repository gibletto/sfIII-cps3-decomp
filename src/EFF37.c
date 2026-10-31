/*
 * EFF37.C  Effect 37: face panel shown with a character
 *
 * Effect 37 is a face panel (ag_face_panel_table) shown with a character from effect C9.
 * It picks the panel for its player number, follows the master's animation with
 * panel_pos_hosei offsets and is shown only while the master's cg_type says so. When both
 * players are the same character it also creates effect H2.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "EFFH2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFF37.h"
#include "fighter.h"

/* routine_no[0] */
#define R0_INIT         0       /* pick the panel for the player */
#define R0_MOVE         1       /* follow the master's animation */
#define R0_KILL         3       /* (default) put the work back */



/* Colour 138 + Player_Color * 4; pattern 21 for player 2 when player_number is 0. */
void effect_37_move(WORK_Other* ewk) {
    WORK* mwk = (WORK*)ewk->my_master;
    s16 ix;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 0;
        ewk->wu.my_col_mode = 0x4000;
        ewk->wu.my_col_code = 0x21FE;
        if (ewk->wu.type) {
            ewk->wu.my_col_code = 0x21FF;
        }
        if (plw[ewk->wu.type].player_number == PL_GILL && ewk->wu.type == 1) {
            set_char_move_init2(&ewk->wu, 0, 0, 14, 0);
        } else {
            set_char_move_init2(&ewk->wu, 0, 0, plw[ewk->wu.type].player_number + 1, 0);
        }
        if (plw[0].player_number == plw[1].player_number) {
            effect_H2_init(&ewk->wu, ewk->wu.charset_id, ewk->wu.type);
            break;
        }
        break;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
        if (mwk->cg_type) {
            ewk->wu.disp_flag = 1;
            if (mwk->cg_type == 0xFF) {
                ix = 3;
            } else {
                ix = mwk->cg_type - 1;
            }
            if (ewk->wu.rl_waza) {
                ewk->wu.position_x = mwk->position_x - panel_pos_hosei[ewk->wu.charset_id][ix][0];
            } else {
                ewk->wu.position_x = mwk->position_x + panel_pos_hosei[ewk->wu.charset_id][ix][0];
            }
            ewk->wu.position_y = mwk->position_y + panel_pos_hosei[ewk->wu.charset_id][ix][1];
        } else {
            ewk->wu.disp_flag = 0;
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



s32 effect_37_init(wk, gal, ohen)
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
    ewk->wu.id = 37;
    ewk->wu.work_id = 16;
    ewk->wu.charset_id = gal;
    ewk->wu.type = ohen;
    ewk->my_master = (u32*)wk;
    ewk->wu.rl_waza = wk->rl_flag;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_family = 2;
    ewk->wu.position_z = wk->position_z - 1;
    ewk->wu.char_table[0] = ag_face_panel_table;
    return 0;
}
