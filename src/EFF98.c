/*
 * EFF98.C  Effect 98: the super art plate on the select screen
 *
 * effect_98_init places one plate per player and art; effect_98_move
 * waits until Stop_Cursor clears, then eff98_arts_check compares the player's choice
 * (Super_Arts) with this plate: the chosen one shows its pattern for 20 frames and then
 * closes the art selection (Select_Timer restarts unless Sel_Sub_No[0] is 3), the others slide out. Every frame the plate follows
 * Plate_X / Plate_Y / eff98_plate_z and takes a new pattern when eff98_arts_req is set.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "aboutspr.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFF98.h"

/* routine_no[0] */
#define R0_INIT         0       /* show the plate */
#define R0_WAIT         1       /* wait for the cursor to stop */
#define R0_CHECK        2       /* wait for the art to be chosen */
#define R0_CHOSEN       3       /* chosen: flash, then close the select */
#define R0_OUT          4       /* wait until off the screen */
#define R0_ANIM         5       /* animate in place */
#define R0_HOLD         6       /* stay at the plate position */
#define R0_KILL         99      /* (default) put the work back */

extern s16 Flash_Complete[2];
extern s16 eff98_plate_z[2][3];         /* provisional name */
extern s8 eff98_arts_req[2][3];         /* provisional name */

#pragma inline(eff98_pattern)



void effect_98_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R0_WAIT:
        if (Stop_Cursor[ewk->master_id] == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case R0_CHECK:
        switch (eff98_arts_check(ewk)) {
        case 1:
            ewk->wu.routine_no[0] = R0_OUT;
            break;
        case -1:
            ewk->wu.routine_no[0] = R0_CHOSEN;
            ewk->wu.dir_timer = 20;
            set_char_move_init(&ewk->wu, 0, ewk->master_id + 6);
        }
        char_move(&ewk->wu);
        break;
    case R0_CHOSEN:
        if (--ewk->wu.dir_timer == 0) {
            Flash_Complete[ewk->master_id] = 1;
            Sel_Arts_Complete[ewk->master_id] = -0x8000;
            Select_Timer = 32;
            Unit_Of_Timer = 40;
            ewk->wu.routine_no[0] = R0_HOLD;
            set_char_move_init(&ewk->wu, 0, ewk->master_id + 35);
        }
        char_move(&ewk->wu);
        break;
    case R0_OUT:
        if (Ck_Range_Out_S(ewk, 2, 80)) {
            ewk->wu.disp_flag = 0;
            ewk->wu.routine_no[0] = R0_KILL;
        }
        break;
    case R0_ANIM:
        char_move(&ewk->wu);
        break;
    case R0_HOLD:
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = Plate_X[ewk->master_id][ewk->master_player];
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = Plate_Y[ewk->master_id][ewk->master_player] + 6;
    ewk->wu.position_z = ewk->wu.xyz[2].disp.pos = eff98_plate_z[ewk->master_id][ewk->master_player] + 1;
    if (eff98_arts_req[ewk->master_id][ewk->master_player]) {
        (&eff98_arts_req[ewk->master_id][0])[ewk->master_player] = 0;
        ewk->wu.char_index = eff98_pattern(ewk->master_id, PP_Priority[ewk->master_id][ewk->master_player]);
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
    }
    sort_push_request4(&ewk->wu);
}



/* -1 for the chosen art, 1 for the others, 0 while undecided */
/* provisional name */
s32 eff98_arts_check(WORK_Other* ewk) {
    if (Sel_Arts_Complete[ewk->master_id] == 0) {
        return 0;
    }
    if (Super_Arts[ewk->master_id] == ewk->master_player) {
        return -1;
    }
    return 1;
}



s32 effect_98_init(s16 PL_id, s16 Art, s16 Arts_No) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 98;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.my_family = 3;
    *ewk->wu.char_table = sel_pl_char_table;
    ewk->master_id = PL_id;
    ewk->master_player = Art;
    ewk->master_priority = Arts_No;
    if (Sel_Arts_Complete[PL_id] < 0 || plw[PL_id].wu.operator == 0) {
        ewk->wu.routine_no[0] = R0_HOLD;
        ewk->wu.disp_flag = 1;
        if (PL_id == 0) {
            ewk->wu.char_index = 29;
        } else {
            ewk->wu.char_index = 32;
        }
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
    } else {
        ewk->wu.char_index = eff98_pattern(ewk->master_id, Arts_No);
    }
    return 0;
}



/* the plate pattern of a player's art */
/* provisional name */
s32 eff98_pattern(s16 PL_id, s16 Arts_No) {
    return PL_id * 3 + Arts_No + 29;
}
