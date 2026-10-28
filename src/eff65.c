/*
 * EFF65.C  Effect 65: a stage 4 object that drifts left (not while aku_flag is set)
 *
 * effect_65_init makes it at (0x1A0, 64). effect_65_move shows it at size 55, drifts it left and
 * up for 600 frames, waits 196 more, then moves it faster, bobbing with its pattern (cg_type 1/2)
 * and shrinking by one every eight frames. Left of x 48 it starts over.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "bg_sub_5.h"
#include "aboutspr.h"
#include "eff65.h"
#include "eff05.h"

/* routine_no[0] */
#define R0_INIT         0       /* set up at the start point */
#define R0_MOVE         1       /* drift across the stage */
#define R0_KILL         99      /* (default) put the work back */

/* routine_no[1] */
#define R1_WAIT         0       /* wait 600 frames */
#define R1_DRIFT        1       /* drift for 196 frames */
#define R1_SHRINK       2       /* go faster and shrink, then start over */

void eff65_char_move(WORK_Other* ewk);



void effect_65_move(WORK_Other* ewk) {
    if (compel_dead_check(ewk)) {
        ewk->wu.routine_no[0] = R0_KILL;
    } else {
        switch (ewk->wu.routine_no[0]) {
        case R0_INIT:
            ewk->wu.routine_no[0]++;
            ewk->wu.routine_no[1] = R1_WAIT;
            ewk->wu.disp_flag = 1;
            set_char_move_init(&ewk->wu, 0, 10);
            ewk->wu.old_rno[0] = 600;
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 0x1A0;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 64;
            ewk->wu.my_mr_flag = 1;
            ewk->wu.mvxy.a[0].sp = -0x12000;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.a[1].sp = 0x800;
            ewk->wu.mvxy.d[1].sp = 0;
            ewk->wu.my_mr.size.x = 55;
            ewk->wu.my_mr.size.y = 55;
            break;
        case R0_MOVE:
            switch (ewk->wu.routine_no[1]) {
            case R1_WAIT:
                if (!EXE_flag && !Game_pause) {
                    ewk->wu.old_rno[0]--;
                    if (ewk->wu.old_rno[0] < 0) {
                        ewk->wu.routine_no[1]++;
                        ewk->wu.old_rno[0] = 196;
                    }
                }
                break;
            case R1_DRIFT:
                if (!EXE_flag && !Game_pause) {
                    eff65_char_move(ewk);
                    add_x_sub(ewk);
                    ewk->wu.old_rno[0]--;
                    if (ewk->wu.old_rno[0] < 0) {
                        ewk->wu.routine_no[1]++;
                        ewk->wu.old_rno[0] = 0;
                        ewk->wu.mvxy.a[0].sp = -0x10000;
                        ewk->wu.mvxy.d[0].sp = 0;
                        ewk->wu.mvxy.a[1].sp = 0x1800;
                        ewk->wu.mvxy.d[1].sp = 0;
                    }
                }
                if (range_x_check(&ewk->wu)) {
                    suzi_sync_pos_set(ewk);
sync_done:;
                    goto draw;
                }
                break;
            case R1_SHRINK:
                if (ewk->wu.xyz[0].disp.pos < 48) {
                    ewk->wu.routine_no[0] = R0_INIT;
                } else if (!EXE_flag && !Game_pause) {
                    char_move(&ewk->wu);
                    add_x_sub(ewk);
                    add_y_sub(ewk);
                    ewk->wu.old_rno[0]++;
                    ewk->wu.old_rno[0] &= 7;
                    if (ewk->wu.old_rno[0] == 7 && ewk->wu.my_mr.size.x != 0) {
                        ewk->wu.my_mr.size.x--;
                        ewk->wu.my_mr.size.y--;
                    }
                }
                if (range_x_check(&ewk->wu)) {
                    suzi_sync_pos_set(ewk);
draw:;
                    sort_push_request4(&ewk->wu);
                }
                break;
            }
            break;
        default:
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
            break;
        }
    }
}



/* provisional name */
/* its pattern's cg_type 1 / 2 moves it down / up by one */
void eff65_char_move(WORK_Other* ewk) {
    char_move(&ewk->wu);
    switch (ewk->wu.cg_type) {
    case 1:
        ewk->wu.xyz[1].disp.pos++;
        ewk->wu.cg_type = 0;
        break;
    case 2:
        ewk->wu.xyz[1].disp.pos--;
        ewk->wu.cg_type = 0;
        break;
    }
}



u32 effect_65_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if (!aku_flag) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 65;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.dead_f = 1;
        ewk->wu.my_family = 2;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2059;
        ewk->wu.position_z = ewk->wu.my_priority = 79;
        ewk->wu.char_table[0] = stg04_char_table;
        ewk->wu.sync_suzi = 1;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 0x1A0;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 64;
        suzi_offset_set(&ewk->wu);
        return 0;
    }
}
