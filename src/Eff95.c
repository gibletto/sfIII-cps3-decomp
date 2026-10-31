/*
 * EFF95.C  Effect 95: the win and ranking screen characters
 *
 * effect_95_init(kind, pl) (from win_2.c: kind 13 for the winner, 0 for the loser) puts the player's
 * character picture (sel_pl_char_table) on BG 1 through eff95_set_obj, adding the extra parts some
 * characters have (types 1, -1 and 0x80, by My_char). eff95_set_position places it by WINNER and gives
 * it a slow slide; its colour comes from eff95_col_tbl_win / _lose and the player's colour.
 * effect_95_rank_init (RANKING.c) makes the ranking screen's character on BG 0. effect_95_move shows
 * the object and slides it in x while win_slide_flag is set.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "win_2.h"
#include "continue.h"
#include "pow_pow.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLS02.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "fighter.h"

/* routine_no[0] */
#define R0_INIT         0       /* show and start the pose */
#define R0_MOVE         1       /* slide with the win screen */

/* eff95_ofs_tbl columns */
#define E95_WIN_X       0       /* x offset of the winner's picture */
#define E95_LOSE_X      1       /* x offset of the loser's picture */

s32 eff95_set_obj();
void eff95_set_position();

/* Character colours and placement offsets. */
const s8 eff95_col_tbl_win[13] = { 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 1, 1, 2 };
const s8 eff95_col_tbl_lose[13] = { -1, 2, 3, 3, 3, 2, 2, 2, 2, 1, 2, 2, 3 };
/* One row per fighter: x offset of the picture when the fighter won, and when it lost. */
const s16 eff95_ofs_tbl[13][2] = {
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 32, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 32, 0 }, { 0, 0 }, { 0, 0 },
};



/* An object drifting in x; its speed is kept only while win_slide_flag is set. */
void effect_95_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_timer + 1, 0);
        break;
    case R0_MOVE:
        if (win_slide_flag == 0) {
            ewk->wu.mvxy.a[0].sp = 0;
        }
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request4(&ewk->wu);
        break;
    }
}



s32 effect_95_init(s16 kind, s16 pl) {
    eff95_set_obj(kind, pl, 0);
    if (kind == 0 && (My_char[pl] & 0x7F) == PL_ELENA) {
        eff95_set_obj(kind, pl, 1);
    }
    if (kind == 13 && (My_char[pl] & 0x7F) == PL_DUDLEY) {
        eff95_set_obj(kind, pl, -1);
    }
    if (kind == 13 && (My_char[pl] & 0x7F) == PL_SEAN) {
        eff95_set_obj(kind, pl, 0x80);
    }
    if (kind == 0 && (My_char[pl] & 0x7F) == PL_SEAN) {
        eff95_set_obj(kind, pl, 0x80);
    }
    return 0;
}



/* provisional name */
s32 eff95_set_obj(kind, pl, typ)
s16 kind;
s16 pl;
s16 typ;
{
    s16 type = typ;
    WORK_Other* ewk;
    s16 ix;
    s16 col;
    s32 player;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 95;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    eff95_set_position(ewk, player = pl);
    if (WINNER == 0) { ewk->wu.rl_flag = 0; } else { ewk->wu.rl_flag = 1; }
    if (kind == 0) {
        ewk->wu.position_z = 41;
        col = eff95_col_tbl_lose[My_char[pl] & 0x7F];
        ewk->wu.my_col_code = col * Player_Color[LOSER] + 0xDC;
    } else {
        ewk->wu.position_z = 50;
        col = eff95_col_tbl_win[My_char[pl] & 0x7F];
        ewk->wu.my_col_code = col * Player_Color[WINNER] + 112;
        if (My_char[WINNER] == PL_GILL) {
            if (player == 0) {
                ewk->wu.my_col_code = 112;
            } else {
                ewk->wu.my_col_code = col + 112;
            }
        }
    }
    ewk->wu.dir_timer = (My_char[pl] & 0x7F) + kind;
    ewk->wu.char_index = 9;
    ewk->wu.char_table[0] = sel_pl_char_table;
    switch (type) {
    case 0:
        break;
    case 1:
        ewk->wu.my_priority = 40;
        ewk->wu.position_z = 40;
        ewk->wu.dir_timer = 26;
        break;
    case 0x80:
        if (kind == 0) {
            ewk->wu.my_priority = 40;
            ewk->wu.position_z = 40;
            ewk->wu.dir_timer = 29;
        } else {
            ewk->wu.my_priority = 49;
            ewk->wu.position_z = 49;
            ewk->wu.dir_timer = 30;
        }
        break;
    default:
        ewk->wu.position_z = 51;
        ewk->wu.dir_timer = 27;
        ewk->wu.mvxy.a[0].sp /= 2;
        if (WINNER == 0) {
            ewk->wu.xyz[0].disp.pos += 32;
        } else {
            ewk->wu.xyz[0].disp.pos -= 32;
        }
        break;
    }
    return 0;
}



s32 effect_95_rank_init(s16 kind, s16 pl, s16 flag, s16 color) {
    WORK_Other* ewk;
    s16 ix;
    s16 col;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 95;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 1;
    ewk->wu.mvxy.a[0].sp = 0;
    ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
    if (Game_setting.Screen_Mode) {
        ewk->wu.xyz[0].disp.pos = bg_w.bgw[0].xy[0].disp.pos - 64;
    } else {
        ewk->wu.xyz[0].disp.pos = bg_w.bgw[0].xy[0].disp.pos - 32;
    }
    ewk->wu.xyz[1].disp.pos = bg_w.bgw[0].xy[1].disp.pos - 48;
    ewk->wu.position_z = 85;
    ewk->wu.dir_timer = pl + kind;
    ewk->wu.char_index = 9;
    ewk->wu.char_table[0] = sel_pl_char_table;
    col = eff95_col_tbl_win[pl];
    ewk->wu.my_col_code = col * color + 112;
    return 0;
}



/* provisional name */
void eff95_set_position(WORK_Other* ewk, s16 pl) {
    ewk->wu.xyz[1].disp.pos = bg_w.bgw[1].xy[1].disp.pos;
    if (WINNER == 0) {
        ewk->wu.xyz[0].disp.pos = bg_w.bgw[1].xy[0].disp.pos + DE_X[10] + 0x80;
    } else {
        ewk->wu.xyz[0].disp.pos = bg_w.bgw[1].xy[0].disp.pos + DE_X[10] + 0x100;
    }
    if (WINNER == 0) {
        if (pl) {
            ewk->wu.mvxy.a[0].sp = 0x8000;
            ewk->wu.xyz[0].disp.pos += eff95_ofs_tbl[My_char[pl] & 0x7F][E95_LOSE_X];
        } else {
            ewk->wu.mvxy.a[0].sp = 0x4000;
            ewk->wu.xyz[0].disp.pos += eff95_ofs_tbl[My_char[pl] & 0x7F][E95_WIN_X];
        }
    } else {
        if (pl) {
            ewk->wu.mvxy.a[0].sp = -0x4000;
            ewk->wu.xyz[0].disp.pos -= eff95_ofs_tbl[My_char[pl] & 0x7F][E95_WIN_X];
        } else {
            ewk->wu.mvxy.a[0].sp = -0x8000;
            ewk->wu.xyz[0].disp.pos -= eff95_ofs_tbl[My_char[pl] & 0x7F][E95_LOSE_X];
        }
    }
}
