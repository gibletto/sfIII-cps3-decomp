/*
 * EFFB9.C  Round-call number sprite (effect B9)
 *
 * A child sprite of the round-call banner (effect B4). effect_B9_init places it to the
 * right of the banner on family 4 and shows either the round number (Round_num + 1) or,
 * for the other banner type, a fixed label. effect_B9_move copies the parent's zoom each
 * frame so it scales in and out with the banner, hides with it and frees itself when the
 * parent finishes.
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
#include "charmove_2.h"
#include "effb2.h"
#include "effb9.h"

/* routine_no[1] */
#define R1_WAIT         0       /* wait, then show the number */
#define R1_OPEN         1       /* open it out */
#define R1_SHOW         2       /* show at full size */



WORK_Other * oya_p;

extern const s16 effb9_round_char_tbl[];


void effect_B9_move(WORK_Other* ewk) {
    oya_p = (WORK_Other*)ewk->my_master;
    b3_Break_Into_check(ewk);
    switch (oya_p->wu.routine_no[0]) {
    case 2:
        switch (ewk->wu.routine_no[1]) {
        case R1_WAIT:
            ewk->wu.hit_stop--;
            if (ewk->wu.hit_stop < 0) {
                ewk->wu.routine_no[1]++;
                set_char_move_init2(&ewk->wu, 0, 3, ewk->wu.char_index, 0);
                ewk->wu.disp_flag = 1;
                ewk->wu.my_mr_flag = 1;
                ewk->wu.my_mr.size.x = 63;
                ewk->wu.my_mr.size.y = 0;
                ewk->wu.hit_stop = 6;
            }
            break;
        case R1_OPEN:
            ewk->wu.hit_stop--;
            if (ewk->wu.hit_stop < 0) {
                ewk->wu.routine_no[1]++;
                ewk->wu.my_mr.size.y = 63;
                rf_b2_flag = 1;
            } else {
                ewk->wu.my_mr.size.y += 10;
            }
            disp_pos_trans_entry5(ewk);
            break;
        case R1_SHOW:
        default:
            disp_pos_trans_entry(ewk);
            break;
        }
        break;
    case 4:
        ewk->wu.my_mr.size.y -= 8;
        if (ewk->wu.my_mr.size.y < 0) {
            ewk->wu.disp_flag = 0;
        }
        disp_pos_trans_entry5(ewk);
        break;
    case 5:
    case 99:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    default:
        disp_pos_trans_entry(ewk);
        break;
    }
}



s32 effect_B9_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 119;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->my_master = (u32*)oya;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 57;
    ewk->wu.my_priority = ewk->wu.position_z = 10;
    ewk->wu.position_y = ewk->wu.scr_mv_y = 129;
    ewk->wu.xyz[1].cal = 0x810000;
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = bg_w.bgw[1].pos_x_work + 70;
    ewk->wu.scr_mv_x = bg_w.bgw[1].pos_x_work + 70;
    ewk->wu.xyz[0].disp.low = 0;
    ewk->wu.char_table[0] = etc_char_table;
    ewk->wu.char_index = effb9_round_char_tbl[Round_num];
    ewk->wu.position_x &= 0x3FF;
    ewk->wu.hit_stop = 4;
    return 0;
}
