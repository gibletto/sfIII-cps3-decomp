/*
 * EFF22.C  Effect 22: part of the breakable stage object
 *
 * effect_22_init makes one work for its master (effect 23) at (0x2C8, 56). It waits on pattern 0
 * until eff_hit_flag[8] is set, plays pattern 1, then walks pattern by pattern with add_pos_dir_032
 * (the pattern's direction byte) until the pattern says 99, plays pattern 2 and settles at (0x2DC,
 * 54). If eff_hit_flag[8] is already set when it starts, it goes straight to pattern 2.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "CHARMOVE.h"
#include "CALDIR.h"
#include "EFF22.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the pattern, or settle if broken */
#define R0_STAND        1       /* animate until the object is hit */
#define R0_WALK         2       /* walk by the pattern's direction */
#define R0_SETTLE       3       /* move to the resting place */
#define R0_BROKEN       4       /* animate at the resting place */
#define R0_KILL         99      /* (default) put the work back */



/* Animate the part and move it to its resting position once the object is hit. */
void effect_22_move(WORK_Other* ewk) {
    if (compel_dead_check(ewk) != 0) {
        ewk->wu.routine_no[0] = R0_KILL;
    } else {
        switch (ewk->wu.routine_no[0]) {
        case R0_INIT:
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 1;
            ewk->wu.dead_f = 1;
            if (eff_hit_flag[8]) {
                set_char_move_init(&ewk->wu, 0, 2);
                ewk->wu.routine_no[0] = R0_SETTLE;
                break;
            }
            set_char_move_init(&ewk->wu, 0, 0);
            break;
        case R0_STAND:
            if (!EXE_flag && !Game_pause) {
                if (eff_hit_flag[8]) {
                    ewk->wu.routine_no[0]++;
                    set_char_move_init(&ewk->wu, 0, 1);
                } else {
                    char_move(&ewk->wu);
                }
            }
            sort_push_request4(&ewk->wu);
            break;
        case R0_WALK:
            if (!EXE_flag && !Game_pause) {
                if (ewk->wu.cg_type != 99) {
                    ewk->wu.direction = ewk->wu.cg_type;
                    char_move(&ewk->wu);
                    add_pos_dir_032(&ewk->wu, 0x300);
                } else {
                    ewk->wu.routine_no[0]++;
                    set_char_move_init(&ewk->wu, 0, 2);
                }
                ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
                ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            }
            sort_push_request4(&ewk->wu);
            break;
        case R0_SETTLE:
            ewk->wu.position_x = 0x2DC;
            ewk->wu.position_y = 54;
            ewk->wu.routine_no[0]++;
            /* fall through */
        case R0_BROKEN:
            if (!EXE_flag && !Game_pause) {
                char_move(&ewk->wu);
            }
            sort_push_request4(&ewk->wu);
            break;
        default:
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
            break;
        }
    }
}



/* Create the part of the breakable stage object (effect 23) that moves to a resting position
 * when the object is hit; made with that object. */
s32 effect_22_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->my_master = (u32*)oya;
    ewk->wu.be_flag = 1;
    ewk->wu.id = 22;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2055;
    ewk->wu.xyz[0].disp.pos = ewk->wu.position_x = 0x2C8;
    ewk->wu.xyz[1].disp.pos = ewk->wu.position_y = 56;
    ewk->wu.position_z = ewk->wu.my_priority = 74;
    ewk->wu.char_table[0] = eff22_char_table;
    return 0;
}
