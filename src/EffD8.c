/*
 * EFFD8.C  Effect D8: the player's face cursor on the character select screen
 *
 * effect_D8_entry(player, n) (from sel_pl.c) makes the cursor, its priority from effD8_priority_tbl.
 * effect_D8_move waits for Appear_Cursor, then follows the player's Cursor_X / Cursor_Y over the face
 * grid (ID_of_Face, placed from Face_Pos_Data by effect_D8_init), cycling its colour
 * (effD8_colour_step). When Sel_PL_Complete is set it flashes for 20 frames, marks the choice done
 * (Sel_PL_Complete -0x8000), restarts the select timer and stays until Suicide.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"

/* routine_no[0] */
#define R0_WAIT         0       /* wait for the cursor to appear */
#define R0_SELECT       1       /* follow the cursor */
#define R0_DECIDE       2       /* flash for 20 frames */
#define R0_HOLD         3       /* stay until the scene ends */
#define R0_KILL         4       /* (default) put the work back */


extern const s16 effD8_priority_tbl[];

void effD8_char_set(WORK_Other* ewk);
void effect_D8_init(WORK_Other* ewk);
void effD8_colour_step(WORK_Other* ewk, s16 num, s16 time);

void effect_D8_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_WAIT:
        if (Appear_Cursor == 0) {
            return;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.char_index = ID_of_Face[ewk->master_id][Cursor_Y[ewk->master_id]][Cursor_X[ewk->master_id]];
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index + 37, ewk->wu.vital_new + 1, 0);
        break;
    case R0_SELECT:
        if (Sel_PL_Complete[ewk->master_id]) {
            ewk->wu.routine_no[0]++;
            ewk->wu.dir_timer = 20;
            ewk->wu.vitality = 3;
            ewk->wu.char_index = ID_of_Face[ewk->master_id][Cursor_Y[ewk->master_id]][Cursor_X[ewk->master_id]];
            set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index + 37, ewk->wu.vital_new + 1, 0);
        }
        if (ewk->wu.dir_step != Cursor_X[ewk->master_id] || ewk->wu.dir_old != Cursor_Y[ewk->master_id]) {
            ewk->wu.dir_step = Cursor_X[ewk->master_id];
            ewk->wu.dir_old = Cursor_Y[ewk->master_id];
            ewk->wu.vitality = 1;
            effD8_colour_step(ewk, 3, 4);
            effD8_char_set(ewk);
            effect_D8_init(ewk);
            set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index + 37, ewk->wu.vital_new + 1, 0);
        } else {
            effD8_colour_step(ewk, 3, 4);
        }
        break;
    case R0_DECIDE:
        if (--ewk->wu.dir_timer) {
            effD8_colour_step(ewk, 4, 2);
        } else {
            ewk->wu.routine_no[0]++;
            Sel_PL_Complete[ewk->master_id] = -0x8000;
            if (Select_Start[ewk->master_id] == 0) {
                Select_Timer = 32;
            }
            Unit_Of_Timer = 40;
            ewk->wu.my_col_code = 0x2040;
            ewk->wu.char_index = ID_of_Face[ewk->master_id][Cursor_Y[ewk->master_id]][Cursor_X[ewk->master_id]];
            set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index + 37, ewk->wu.vital_new + 1, 0);
        }
        break;
    case R0_HOLD:
        if (Suicide != 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}

/* provisional name */
s32 effect_D8_entry(s16 PL_id, s16 vital) {
    s16 ix;
    WORK_Other* ewk;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 138;
    ewk->wu.work_id = 0x10;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.my_family = 2;
    ewk->wu.char_table[0] = sel_pl_char_table;
    ewk->wu.old_rno[0] = 0;
    ewk->wu.old_rno[1] = 1;
    ewk->wu.old_rno[2] = 2;
    ewk->wu.old_rno[3] = 15;
    ewk->wu.vital_old = 0;
    ewk->wu.vitality = 6;
    ewk->master_id = PL_id;
    ewk->wu.vital_new = vital;
    ewk->wu.dir_step = Cursor_X[ewk->master_id];
    ewk->wu.dir_old = Cursor_Y[ewk->master_id];
    ewk->wu.position_z = effD8_priority_tbl[vital];
    effD8_char_set(ewk);
    effect_D8_init(ewk);
    return 0;
}

/* provisional name */
void effD8_char_set(WORK_Other* ewk) {
    ewk->wu.char_index = ID_of_Face[ewk->master_id][Cursor_Y[ewk->master_id]][Cursor_X[ewk->master_id]];
}

void effect_D8_init(WORK_Other* ewk) {
    ewk->wu.xyz[0].disp.pos = Face_Pos_Data[ewk->wu.char_index][SEL_POS_X] + DE_X[10] + 0x1C0;
    ewk->wu.xyz[1].disp.pos = Face_Pos_Data[ewk->wu.char_index][SEL_POS_Y] + 65;
}

/* provisional name */
void effD8_colour_step(WORK_Other* ewk, s16 num, s16 time) {
    if (--ewk->wu.vitality == 0) {
        if (++ewk->wu.vital_old >= num) {
            ewk->wu.vital_old = 0;
        }
        ewk->wu.vitality = time;
        ewk->wu.my_col_code = ewk->wu.old_rno[ewk->wu.vital_old] + 0x2040;
        ewk->wu.char_index = ID_of_Face[ewk->master_id][Cursor_Y[ewk->master_id]][Cursor_X[ewk->master_id]];
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index + 37, ewk->wu.vital_new + 1, 0);
    }
}
