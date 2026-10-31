/*
 * EFF76.C  Effect 76: the second figure crossing the far left of the stage
 *
 * effect_76_init (from effect 75) places a second, larger figure at the same spot with pattern 1 of
 * eff75_char_table. effect_76_move plays its animation, moving it in the direction and at the priority
 * each step gives (eff76_dir_tbl, eff76_prio_tbl) and shrinking it a little every 3 frames, and frees
 * it when the animation ends (step 99).
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

/* routine_no[0] */
#define R0_MOVE         0       /* walk and shrink to the animation's end */
#define R0_KILL         1       /* put the work back */

extern const s16 eff76_dir_tbl[];
extern const s16 eff76_prio_tbl[];

s32 effect_76_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 76;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 81;
    ewk->wu.char_table[0] = eff75_char_table;
    ewk->wu.xyz[0].disp.pos = ewk->wu.position_x = -384;
    ewk->wu.xyz[1].disp.pos = ewk->wu.position_y = 240;
    ewk->wu.position_z = ewk->wu.my_priority = 86;
    ewk->wu.my_mr_flag = 1;
    ewk->wu.my_mr.size.x = 90;
    ewk->wu.my_mr.size.y = 90;
    ewk->wu.old_rno[1] = 3;
    ewk->wu.disp_flag = 1;
    set_char_move_init(&ewk->wu, 0, 1);
}

void effect_76_move(WORK_Other* ewk) {
    const s16* data;
    if (ewk->wu.dead_f == 1) {
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
    switch (ewk->wu.routine_no[0]) {
    case R0_MOVE:
        if (EXE_flag == 0 && Game_pause == 0) {
            if (ewk->wu.cg_type == 99) {
                ewk->wu.routine_no[0]++;
                ewk->wu.disp_flag = 0;
                return;
            }
            ewk->wu.direction = ewk->wu.cg_type;
            char_move(&ewk->wu);
            data = &eff76_dir_tbl[ewk->wu.cg_type - 13];
            add_pos_dir_064(&ewk->wu, *data);
            data = &eff76_prio_tbl[ewk->wu.cg_type - 13];
            ewk->wu.position_z = ewk->wu.my_priority = *data;
            ewk->wu.old_rno[1]--;
            if (ewk->wu.old_rno[1] == 0) {
                ewk->wu.my_mr.size.x--;
                ewk->wu.my_mr.size.y--;
                ewk->wu.old_rno[1] = 3;
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

