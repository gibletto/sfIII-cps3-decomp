/*
 * EFF75.C  Effect 75: a figure crossing the far left of the stage
 *
 * effect_75_init (from bgst110's stage) places the figure, scaled down, beyond the left of the stage.
 * Once a player has spent 192 frames far to the left, effect_75_move shows it and plays its animation,
 * moving it in the direction and at the priority each animation step gives (eff75_dir_tbl,
 * eff75_prio_tbl) and shrinking it a little every 6 frames; 224 frames in it starts effect 76. It is
 * freed when its animation ends (step 99).
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
#include "ta_sub.h"
#include "EFF75.h"
#include "Eff76.h"

/* routine_no[0] */
#define R0_WAIT         0       /* wait for a player to stay far left */
#define R0_MOVE         1       /* walk and shrink to the animation's end */
#define R0_KILL         2       /* put the work back */


s32 effect_75_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 75;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 81;
    *ewk->wu.char_table = eff75_char_table;
    ewk->wu.xyz[0].disp.pos = ewk->wu.position_x = -384;
    ewk->wu.xyz[1].disp.pos = ewk->wu.position_y = 240;
    ewk->wu.position_z = ewk->wu.my_priority = 86;
    ewk->wu.my_mr_flag = 1;
    ewk->wu.my_mr.size.x = 73;
    ewk->wu.my_mr.size.y = 73;
    ewk->wu.old_rno[0] = 192;
    ewk->wu.old_rno[1] = 6;
    ewk->wu.old_rno[3] = 0;
    ewk->wu.old_rno[2] = 224;
    ewk->wu.disp_flag = 0;
    set_char_move_init(&ewk->wu, 0, 0);
}

void effect_75_move(WORK_Other* ewk) {
    const s16* data;
    if (ewk->wu.dead_f == 1) {
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
    switch (ewk->wu.routine_no[0]) {
    case R0_WAIT:
        if (plw[0].wu.xyz[0].disp.pos < -240 || plw[1].wu.xyz[0].disp.pos < -208) {
            ewk->wu.old_rno[0]--;
            if (ewk->wu.old_rno[0] < 0) {
                ewk->wu.routine_no[0]++;
                ewk->wu.disp_flag = 1;
            }
        }
        break;
    case R0_MOVE:
        if (EXE_flag == 0 && Game_pause == 0) {
            if (ewk->wu.old_rno[3] == 0) {
                ewk->wu.old_rno[2]--;
                if (ewk->wu.old_rno[2] == 0) {
                    ewk->wu.old_rno[3] = 1;
                    effect_76_init();
                }
            }
            if (ewk->wu.cg_type == 99) {
                ewk->wu.routine_no[0]++;
                ewk->wu.disp_flag = 0;
                return;
            }
            ewk->wu.direction = ewk->wu.cg_type;
            char_move(&ewk->wu);
            data = &eff75_dir_tbl[ewk->wu.cg_type - 13];
            add_pos_dir_064(&ewk->wu, *data);
            data = &eff75_prio_tbl[ewk->wu.cg_type - 13];
            ewk->wu.position_z = ewk->wu.my_priority = *data;
            ewk->wu.old_rno[1]--;
            if (ewk->wu.old_rno[1] == 0) {
                ewk->wu.my_mr.size.x--;
                ewk->wu.my_mr.size.y--;
                ewk->wu.old_rno[1] = 6;
            }
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        }
        sort_push_request4(&ewk->wu);
        break;
    case R0_KILL:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    default:
        break;
    }
}

