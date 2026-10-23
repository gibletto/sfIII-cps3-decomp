/*
 * EFFE4.C  Effect E4: the marker beside a super art plate
 *
 * effect_E4_init(player, art, plate) (from effect D7 and sel_pl.c; not for character 0) makes the
 * marker (sel_pl_char_table pattern 10) for one of the player's super art plates. effect_E4_move keeps
 * it 74 dots to the outer side of its plate (Plate_X, Plate_Y and eff98_plate_z, written by effect D7)
 * and recolours it from PP_Priority when effE4_col_req asks. After the choice (eff98_arts_check) it
 * follows its plate off the screen or stays. Once the player has chosen, or for a CPU player, it is
 * shown straight away.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "HITCHECK.h"

extern s16 eff98_plate_z[2][3];
extern s8 effE4_col_req[2][3];
s32 eff98_arts_check(WORK_Other* ewk);
s32 effE4_colour(WORK_Other* ewk);

void effect_E4_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.dir_timer = 1;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.vital_new + 1, 0);
        break;
    case 1:
        if (Stop_Cursor[ewk->master_id] == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case 2:
        switch (eff98_arts_check(ewk)) {
        case 1:
            ewk->wu.routine_no[0] = 3;
            break;
        case -1:
            ewk->wu.routine_no[0] = 4;
        }
        break;
    case 3:
        if (Ck_Range_Out_S(ewk, 2, 8)) {
            ewk->wu.disp_flag = 0;
            ewk->wu.routine_no[0] = 99;
        }
        break;
    case 4:
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
    if (effE4_col_req[ewk->master_id][ewk->master_player]) {
        (&effE4_col_req[ewk->master_id][0])[ewk->master_player] = 0;
        ewk->wu.my_col_code = effE4_colour(ewk);
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.vital_new + 1, 0);
    }
    if (ewk->master_id == 0) {
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = Plate_X[ewk->master_id][ewk->master_player] - 74;
    } else {
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = Plate_X[ewk->master_id][ewk->master_player] + 74;
    }
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = Plate_Y[ewk->master_id][ewk->master_player] + 16;
    ewk->wu.position_z = ewk->wu.xyz[2].disp.pos = eff98_plate_z[ewk->master_id][ewk->master_player];
    sort_push_request4(&ewk->wu);
}

s32 effect_E4_init(s16 PL_id, s16 Art, s16 Arts_No) {
    WORK_Other* ewk;
    s16 ix;
    if (My_char[PL_id] == 0) {
        return;
    }
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 144;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 3;
    *ewk->wu.char_table = sel_pl_char_table;
    ewk->wu.char_index = 10;
    ewk->master_id = PL_id;
    ewk->wu.vital_new = Art;
    ewk->master_player = Art;
    ewk->master_priority = Arts_No;
    ewk->wu.my_col_code = Arts_No + 0x2040;
    if (Sel_Arts_Complete[PL_id] < 0 || plw[PL_id].wu.operator == 0) {
        ewk->wu.routine_no[0] = 4;
        ewk->wu.disp_flag = 1;
        ewk->wu.my_col_code = 0x2040;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.vital_new + 1, 0);
    }
    return 0;
}

s32 effE4_colour(WORK_Other* ewk) {
    return PP_Priority[ewk->master_id][ewk->master_player] + 0x2040;
}
