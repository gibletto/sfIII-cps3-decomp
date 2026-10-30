/*
 * EFFH0.C  Effect H0: a pattern played once at a player's position
 *
 * effect_H0_init(player, data) creates the effect at the player's position and facing; effect_H0_move
 * takes its display flag, direction and pattern from effh0_data[data], plays the pattern
 * (effh0_char_table) once and frees itself. It stops during EXE_flag / Game_pause.
 */

#include "structs.h"
#include "work.h"
#include "extern.h"
#include "charmove_2.h"
#include "effect_2.h"

/* routine_no[0] */
#define R0_INIT         0       /* set up from effh0_data */
#define R0_MOVE         1       /* play the pattern once */
#define R0_KILL         2       /* put the work back */


extern const EFFH0_DATA effh0_data[];
extern const u32 effh0_char_table[];

void effect_H0_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.mvxy.a[0].sp = effh0_data[ewk->wu.type].x;
        ewk->wu.mvxy.a[1].sp = effh0_data[ewk->wu.type].y;
        ewk->wu.disp_flag = effh0_data[ewk->wu.type].disp_flag;
        ewk->wu.direction = effh0_data[ewk->wu.type].direction;
        ewk->wu.char_index = effh0_data[ewk->wu.type].char_index;
        ewk->wu.mvxy.a[0].sp <<= 8;
        ewk->wu.mvxy.a[1].sp <<= 8;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 0xFF) {
                ewk->wu.disp_flag = 0;
                ewk->wu.routine_no[0]++;
                break;
            }
        }
        break;
    case R0_KILL:
    default:
        push_effect_work(&ewk->wu);
        break;
    }
}

s32 effect_H0_init(PLW* wk, u8 data) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 170;
    ewk->wu.work_id = 16;
    ewk->wu.type = data;
    ewk->wu.rl_flag = wk->wu.rl_flag;
    ewk->wu.my_family = 2;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2020;
    ewk->wu.xyz[0].disp.pos = wk->wu.xyz[0].disp.pos;
    ewk->wu.xyz[1].disp.pos = wk->wu.xyz[1].disp.pos;
    ewk->my_master = (u32*)wk;
    ewk->master_work_id = wk->wu.work_id;
    ewk->master_id = wk->wu.id;
    ewk->wu.blink_timing = wk->wu.blink_timing;
    ewk->wu.char_table[0] = effh0_char_table;
    return 0;
}
