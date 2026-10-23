/*
 * EFFA8.C  Effect A8: super art plate highlight
 *
 * effect_A8_init(player, slot) (nothing calls it) makes a highlight (sel_pl_char_table pattern
 * 8 + player) over one of the player's super art plates (Plate_X / Plate_Y). effect_A8_move opens it
 * vertically, marks the plate (sel_plate_state 20) and starts effect A9, closes it again and raises
 * Arts_Cursor_Timer; when the request is answered (-1) it opens once more, sets the plate's state back
 * to 52 and closes for good.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFECT.h"
#include "aboutspr.h"
#include "CHARMOVE.h"
#include "effa9.h"

extern s16 sel_plate_state[2][3];

void effect_A8_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
        break;
    case 1:
        if ((ewk->wu.my_mr.size.y += 8) >= 63) {
            ewk->wu.my_mr.size.y = 63;
            ewk->wu.routine_no[0]++;
            ewk->wu.dir_timer = 4;
            sel_plate_state[(s8)ewk->master_id][ewk->master_player] = 20;
            effect_A9_init(ewk->master_id, ewk->master_player);
        }
        break;
    case 2:
        if (--ewk->wu.dir_timer) {
            break;
        }
        ewk->wu.routine_no[0]++;
        break;
    case 3:
        if ((ewk->wu.my_mr.size.y -= 8) <= 0) {
            ewk->wu.my_mr.size.y = 0;
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
            Arts_Cursor_Timer[ewk->master_id] = 1;
        }
        break;
    case 4:
        if (Arts_Cursor_Timer[ewk->master_id] != -1) {
            break;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        /* fall through */
    case 5:
        if ((ewk->wu.my_mr.size.y += 8) >= 63) {
            ewk->wu.my_mr.size.y = 63;
            ewk->wu.routine_no[0]++;
            ewk->wu.dir_timer = 4;
            sel_plate_state[(s8)ewk->master_id][ewk->master_player] = 52;
        }
        break;
    case 6:
        if (--ewk->wu.dir_timer) {
            break;
        }
        ewk->wu.routine_no[0]++;
        break;
    case 7:
        if ((ewk->wu.my_mr.size.y -= 8) <= 0) {
            ewk->wu.my_mr.size.y = 0;
            ewk->wu.routine_no[0] = 99;
            Arts_Cursor_Timer[ewk->master_id] = 0;
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
    ewk->wu.position_x = Plate_X[(s8)ewk->master_id][ewk->master_player];
    ewk->wu.position_y = Plate_Y[(s8)ewk->master_id][ewk->master_player] + 7;
    sort_push_request4(&ewk->wu);
}

s32 effect_A8_init(s16 player, s16 slot) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 108;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.my_family = 3;
    ewk->wu.position_z = 44;
    ewk->wu.char_table[0] = sel_pl_char_table;
    ewk->master_id = player;
    ewk->master_player = slot;
    ewk->wu.char_index = 8;
    ewk->wu.dir_step = player;
    ewk->wu.my_mr_flag = 1;
    ewk->wu.my_mr.size.x = 63;
    ewk->wu.my_mr.size.y = 0;
    return 0;
}
