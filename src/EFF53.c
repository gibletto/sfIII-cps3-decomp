/*
 * EFF53.C  Effect 53: stage bird
 *
 * The bgst140 background creates effect 53. It waits 120 frames, walks
 * on screen, then sits until complete_victory_check: it then starts a zoomed take-off from
 * background layer 1 (my_mr grows while it climbs), flies across, and is dropped once it is
 * 0x120 past the layer. eff53_disp follows xyz and pushes the sprite for the flying states.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "EFF53.h"
#include "EFF54.h"

/* routine_no[0] */
#define R0_INIT         0       /* show and start the pattern */
#define R0_WAIT         1       /* stand for a while */
#define R0_WALK         2       /* walk to its place */
#define R0_HIDE         3       /* play to the end, then hide */
#define R0_IDLE         4       /* hidden until the victory */
#define R0_RISE         5       /* take off, growing */
#define R0_CLIMB        6       /* climb away to full size */
#define R0_GLIDE        7       /* glide for a while */
#define R0_SWOOP        8       /* swoop, growing, to the cue */
#define R0_FLY          9       /* fly off past the layer */
#define R0_KILL         99      /* (default) put the work back */



void effect_53_move(WORK_Other* ewk) {
    if (pcon_rno[0] == PCON_DIE && pcon_rno[1] == 3) {
        ewk->wu.routine_no[0] = R0_KILL;
    }
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 0);
        ewk->wu.direction = 120;
        break;
    case R0_WAIT:
        ewk->wu.direction--;
        if (ewk->wu.direction < 0) {
            ewk->wu.routine_no[0]++;
        }
        disp_pos_trans_entry(ewk);
        break;
    case R0_WALK:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 2) {
                ewk->wu.routine_no[0]++;
                ewk->wu.position_z = ewk->wu.my_priority = 79;
            }
        }
        disp_pos_trans_entry(ewk);
        break;
    case R0_HIDE:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                ewk->wu.routine_no[0]++;
                ewk->wu.disp_flag = 0;
            }
        }
        disp_pos_trans_entry(ewk);
        break;
    case R0_IDLE:
        if (complete_victory_check()) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 1;
            ewk->wu.old_rno[0] = 67;
            set_char_move_init(&ewk->wu, 0, 1);
            ewk->wu.xyz[0].disp.pos = bg_w.bgw[1].position_x + 88;
            ewk->wu.xyz[1].disp.pos = bg_w.bgw[1].position_y + 0x88;
            ewk->wu.my_mr_flag = 1;
            ewk->wu.my_mr.size.x = 4;
            ewk->wu.my_mr.size.y = 4;
            ewk->wu.mvxy.a[0].sp = 0x200;
            ewk->wu.mvxy.a[1].sp = 0x200;
            ewk->wu.mvxy.d[0].sp = 0x140;
            ewk->wu.mvxy.d[1].sp = -0x140;
        }
        break;
    case R0_RISE:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            ewk->wu.direction++;
            ewk->wu.direction &= 3;
            if (ewk->wu.direction == 3) {
                ewk->wu.my_mr.size.x++;
                ewk->wu.my_mr.size.y++;
            }
            ewk->wu.old_rno[0]--;
            if (ewk->wu.old_rno[0] < 0) {
                ewk->wu.routine_no[0]++;
                ewk->wu.direction = 0;
                set_char_move_init(&ewk->wu, 0, 4);
                ewk->wu.mvxy.a[0].sp = 0x6000;
                ewk->wu.mvxy.a[1].sp = 0x10000;
                ewk->wu.mvxy.d[0].sp = 0x600;
                ewk->wu.mvxy.d[1].sp = -0x180;
            }
        }
        eff53_disp(ewk);
        break;
    case R0_CLIMB:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
            ewk->wu.direction++;
            ewk->wu.direction &= 1;
            if (ewk->wu.direction == 1) {
                ewk->wu.my_mr.size.x++;
                ewk->wu.my_mr.size.y++;
                if (ewk->wu.my_mr.size.x >= 63) {
                    ewk->wu.routine_no[0]++;
                    ewk->wu.direction = 0;
                    ewk->wu.old_rno[0] = 36;
                    set_char_move_init(&ewk->wu, 0, 3);
                    ewk->wu.position_z = ewk->wu.my_priority = 10;
                    ewk->wu.mvxy.a[0].sp = 0x5000;
                    ewk->wu.mvxy.d[0].sp = 0;
                }
            }
        }
        eff53_disp(ewk);
        break;
    case R0_GLIDE:
        if (!EXE_flag && !Game_pause) {
            add_x_sub(ewk);
            ewk->wu.old_rno[0]--;
            if (ewk->wu.old_rno[0] <= 0) {
                ewk->wu.cg_ctr = 1;
                ewk->wu.routine_no[0]++;
                ewk->wu.mvxy.a[0].sp = -0x20000;
                ewk->wu.mvxy.a[1].sp = -0xA0000;
                ewk->wu.mvxy.d[0].sp = 0x3000;
                ewk->wu.mvxy.d[1].sp = 0x8000;
            }
        }
        eff53_disp(ewk);
        break;
    case R0_SWOOP:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
            ewk->wu.my_mr.size.x++;
            ewk->wu.my_mr.size.y++;
            if (ewk->wu.cg_type == 2) {
                ewk->wu.routine_no[0]++;
                ewk->wu.mvxy.a[0].sp = 0;
                ewk->wu.mvxy.a[1].sp = 0;
                ewk->wu.mvxy.d[0].sp = 0x24000;
                ewk->wu.mvxy.d[1].sp = 0x18000;
            }
        }
        eff53_disp(ewk);
        break;
    case R0_FLY:
        if (!EXE_flag && !Game_pause) {
            add_x_sub(ewk);
            add_y_sub(ewk);
            if (ewk->wu.xyz[0].disp.pos > bg_w.bgw[1].xy[0].disp.pos + 0x120) {
                ewk->wu.routine_no[0]++;
                break;
            }
            if (ewk->wu.my_mr.size.x < 127) {
                ewk->wu.my_mr.size.x++;
                ewk->wu.my_mr.size.y++;
            }
        }
        eff53_disp(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* provisional name */
void eff53_disp(WORK_Other* ewk) {
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}



s32 effect_53_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 53;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 87;
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 0x290;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 48;
    ewk->wu.position_z = ewk->wu.my_priority = 67;
    *ewk->wu.char_table = eff54_char_table;
    return 0;
}
