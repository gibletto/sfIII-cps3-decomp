/*
 * EFF39.C  Effect 39: the player's name plate on the character select screen
 *
 * effect_39_init(player, wait) (from sel_pl.c) makes the name plate (sel_pl_char_table pattern 1).
 * After the wait it slides 140 dots in from the player's side and counts down Select_Start; while the
 * player is still choosing it then shows the name for the face under the cursor (ID_of_Face). A
 * negative wait puts it straight in place. eff39_arts_flag, eff39_pl_flag and eff39_move_y are not
 * called.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "fighter.h"
#include "Eff39.h"

/* routine_no[0] */
#define R0_WAIT         0       /* count the start wait down, then show */
#define R0_SLIDE_IN     1       /* slide in to the place */
#define R0_FOLLOW       2       /* follow the cursor while choosing */
#define R0_STAY         99      /* (default) stay in place */

void effect_39_move(WORK_Other* ewk) {
    Cut_Cut_Sub(3);
    switch (ewk->wu.routine_no[0]) {
    case R0_WAIT:
        if (--ewk->wu.dir_timer != 0) {
            return;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
        break;
    case R0_SLIDE_IN:
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp * 3;
        if (ewk->wu.mvxy.a[0].sp > 0) {
            if (ewk->wu.hit_quake < ewk->wu.xyz[0].disp.pos) {
                if (Sel_PL_Complete[ewk->master_id] || plw[ewk->master_id].wu.operator == 0) {
                    ewk->wu.routine_no[0] = R0_STAY;
                } else {
                    ewk->wu.routine_no[0]++;
                }
                ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
                Select_Start[ewk->master_id]--;
            }
        } else if (ewk->wu.hit_quake > ewk->wu.xyz[0].disp.pos) {
            if (Sel_PL_Complete[ewk->master_id] || plw[ewk->master_id].wu.operator == 0) {
                ewk->wu.routine_no[0] = R0_STAY;
            } else {
                ewk->wu.routine_no[0]++;
            }
            ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
            Select_Start[ewk->master_id]--;
        }
        break;
    case R0_FOLLOW:
        if (ewk->wu.dir_step != ID_of_Face[ewk->master_id][Cursor_Y[ewk->master_id]][Cursor_X[ewk->master_id]]) {
            ewk->wu.dir_step = ID_of_Face[ewk->master_id][Cursor_Y[ewk->master_id]][Cursor_X[ewk->master_id]];
            set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
        }
        break;
    default:
        break;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}

s32 eff39_arts_flag(WORK_Other* ewk) {
    if (Sel_Arts_Complete[ewk->master_id] != -1) {
        return Sel_Arts_Complete[ewk->master_id] & 0x8000;
    }
    return Sel_Arts_Complete[ewk->master_id ^ 1] & 0x8000;
}

s32 eff39_move_y(WORK_Other* ewk, s32 speed) {
    ewk->wu.xyz[1].cal += speed;
    if (ewk->wu.hit_quake <= ewk->wu.xyz[1].disp.pos) {
        ewk->wu.xyz[1].disp.pos = ewk->wu.hit_quake;
        return 1;
    }
    return 0;
}

s32 eff39_pl_flag(WORK_Other* ewk) {
    if (Sel_Arts_Complete[ewk->master_id] != -1) {
        return Sel_PL_Complete[ewk->master_id] & 0x8000;
    }
    return Sel_PL_Complete[ewk->master_id ^ 1] & 0x8000;
}

s32 effect_39_init(s16 PL_id, s16 Wait) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 39;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.my_family = 3;
    ewk->wu.xyz[1].disp.pos = 56;
    ewk->wu.my_priority = 10;
    ewk->wu.position_z = 10;
    ewk->wu.char_index = 1;
    ewk->wu.char_table[0] = sel_pl_char_table;
    ewk->master_id = PL_id;
    if (PL_id) {
        ewk->wu.xyz[0].disp.pos = DE_X[5] + 0x3D0;
        ewk->wu.hit_quake = ewk->wu.xyz[0].disp.pos - 140;
        ewk->wu.mvxy.a[0].sp = -0xF0000;
    } else {
        ewk->wu.xyz[0].disp.pos = 0x1B0;
        ewk->wu.hit_quake = ewk->wu.xyz[0].disp.pos + 140;
        ewk->wu.mvxy.a[0].sp = 0xF0000;
    }
    if (plw[PL_id].wu.operator == 0 && EM_id == PL_GILL) {
        ewk->wu.dir_step = 0;
    } else {
        ewk->wu.dir_step = ID_of_Face[ewk->master_id][Cursor_Y[ewk->master_id]][Cursor_X[ewk->master_id]];
    }
    if ((ewk->wu.dir_timer = Wait) < 0) {
        ewk->wu.routine_no[0] = R0_STAY;
        ewk->wu.disp_flag = 1;
        ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
        if ((My_char[ewk->master_id] & 0x7F) == PL_YANG) {
            ewk->wu.dir_step = 10;
        }
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
    }
    return 0;
}
