/*
 * EFFD5.C  Effect D5: character-select face plates
 *
 * effect_D5_init(id) (from sel_pl.c) places the plate of face id at its spot in Face_Pos_Data;
 * effect_D5_init2 places one more plate (pattern 56) at a fixed spot. Each frame effect_D5_move shows
 * the face's pattern and, while a playing player's cursor is on that face, the highlighted pattern in
 * front (effD5_cursor). The shared Yun / Yang cell shows the twin the deciding player has there
 * (effD5_fix, effD5_sel_id). The plates are freed when Suicide is 1.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "EFFD5.h"

/* routine_no[0] */
#define R0_INIT         0       /* show the plate */
#define R0_MOVE         1       /* show the face and the cursors */
#define R0_KILL         2       /* (default) put the work back */

extern s8 ID_of_Face[2][2][5];
extern const s16 Face_Pos_Data[][2];

void effect_D5_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        /* fall through */
    case R0_MOVE:
        if (Suicide == 1) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
        } else {
            ewk->wu.position_z = 62;
            set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_timer + 1, 0);
            if (plw[0].wu.operator) {
                effD5_cursor(ewk, 0);
            }
            if (plw[1].wu.operator) {
                effD5_cursor(ewk, 1);
            }
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            ewk->wu.position_z = ewk->wu.xyz[2].disp.pos & 0x3FF;
            sort_push_request4(&ewk->wu);
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

void effD5_cursor(WORK_Other* ewk, s16 pl) {
    s16 id;
    id = effD5_sel_id(pl);
    effD5_fix(ewk, id);
    if (ewk->wu.dir_timer == ID_of_Face[id][Cursor_Y[pl]][Cursor_X[pl]]) {
        ewk->wu.dir_timer = ID_of_Face[id][Cursor_Y[pl]][Cursor_X[pl]];
        if (ewk->wu.dir_timer == 10) {
            ewk->wu.dir_timer = 3;
        }
        ewk->wu.xyz[2].disp.pos = 61;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_timer + 15, 0);
    }
}

void effD5_fix(ewk, id)
WORK_Other* ewk;
s16 id;
{
    if (ewk->wu.dir_timer == 3 || ewk->wu.dir_timer == 10) {
        ewk->wu.dir_timer = ID_of_Face[id][0][3];
    }
}

s32 effD5_sel_id(s16 pl) {
    if (Sel_PL_Complete[0] != 0 && Sel_PL_Complete[1] != 0) {
        return Last_Selected_ID;
    }
    if (Sel_PL_Complete[0] == 0) {
        return 0;
    }
    if (Sel_PL_Complete[1] == 0) {
        return 1;
    }
}

s32 effect_D5_init(s16 id) {
    WORK_Other* ewk;
    s16 ix;
    s16 x;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    Setup_EffD5(&ewk->wu);
    x = DE_X[10] + 0x100;
    ewk->wu.xyz[0].disp.pos = x + Face_Pos_Data[id][SEL_POS_X] + 0xC0;
    ewk->wu.xyz[1].disp.pos = Face_Pos_Data[id][SEL_POS_Y] + 65;
    ewk->wu.xyz[2].disp.pos = 62;
    ewk->wu.dir_timer = id;
}

s32 effect_D5_init2(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    Setup_EffD5(&ewk->wu);
    ewk->wu.xyz[0].disp.pos = DE_X[10] + 0x1C0;
    ewk->wu.xyz[1].disp.pos = 87;
    ewk->wu.xyz[2].disp.pos = 64;
    ewk->wu.char_index = 0;
    ewk->wu.dir_timer = 56;
    ewk->wu.char_table[0] = sel_pl_char_table;
}

void Setup_EffD5(WORK* wk) {
    wk->be_flag = 1;
    wk->id = 135;
    wk->work_id = 16;
    wk->cgromtype = 1;
    wk->my_col_mode = 0x4200;
    wk->my_col_code = 0x2040;
    wk->my_family = 2;
    wk->char_index = 0;
    wk->char_table[0] = sel_pl_char_table;
}
