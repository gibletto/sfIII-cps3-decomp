/*
 * PLPAT00.C  Character 0 (Gill) special attack routines
 *
 * pl00_extra_attack runs the character-0 special moves from pl00_exatt_table for attack routine
 * numbers 16 and up:
 * Att_MOONSALT_KNEE_DROP and Att_RESURRECTION, with get_life_add_point giving the vitality gained
 * per frame during the resurrection animation.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLS02.h"
#include "PLSGAUGE.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "PLPAT.h"
#include "PLS01.h"
#include "PLPAT00.h"

/* routine_no[3], Att_MOONSALT_KNEE_DROP */
#define MOONSALT_KNEE__MOVE 1   /* move and run the animation to cue 20 */
#define MOONSALT_KNEE__AIR 2    /* in the air until it lands */
#define MOONSALT_KNEE__LAND 3   /* the landing */

/* routine_no[3], Att_RESURRECTION */
#define RESURRECTION_CUE 1      /* run the animation to its next cue */
#define RESURRECTION_AIR 2      /* in the air until it lands */


void pl00_extra_attack(PLW* wk) {
    pl00_exatt_table[wk->wu.routine_no[2] - ATTACK_SPECIAL](wk);
}



void Att_MOONSALT_KNEE_DROP(PLW* wk) {
    PLW* twk;
    s16 ex;
    s16 ey;
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        setup_mvxy_data(&wk->wu, wk->as->data_ix);
        twk = (PLW*)wk->wu.target_adrs;
        if (wk->wu.rl_flag) {
            ex = twk->wu.position_x - mnd_em_tall[twk->player_number][0];
        } else {
            ex = twk->wu.position_x + mnd_em_tall[twk->player_number][0];
        }
        ey = mnd_em_tall[twk->player_number][1];
        wk->wu.mvxy.a[0].sp = 0;
        cal_delta_speed(&wk->wu, wk->as->r_no, ex, ey, 2, 2);
        if (wk->wu.rl_flag == 0) {
            wk->wu.mvxy.a[0].sp = -wk->wu.mvxy.a[0].sp;
            wk->wu.mvxy.d[0].sp = -wk->wu.mvxy.d[0].sp;
        }
        break;
    case MOONSALT_KNEE__MOVE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 20) {
            wk->wu.routine_no[3]++;
            wk->wu.cg_type = 0;
            add_mvxy_speed(&wk->wu);
        }
        break;
    case MOONSALT_KNEE__AIR:
        jumping_union_process(&wk->wu, 3);
        break;
    case MOONSALT_KNEE__LAND:
        char_move(&wk->wu);
        break;
    }
}



void Att_RESURRECTION(PLW* wk) {
    wk->scr_pos_set_flag = 0;
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.direction = 0;
        reset_mvxy_data((WORK*)wk);
        set_char_move_init((WORK*)wk, 5, wk->as->char_ix);
        round_slow_flag = 0;
        break;
    case RESURRECTION_CUE:
        char_move((WORK*)wk);
        if (wk->wu.cg_type) {
            wk->wu.direction = get_life_add_point(wk->wu.cg_type, wk->wu.direction);
            wk->wu.cg_type = 0;
        }
        wk->wu.vital_new += wk->wu.direction;
        if (wk->wu.vital_new < wk->wu.vitality) {
            return;
        } else {
            wk->wu.vital_new = wk->wu.vitality;
        }
        wk->wu.mvxy.d[1].sp = -0x8000;
        wk->wu.direction = 0;
        wk->wu.routine_no[3]++;
        if (wk->wu.vital_new < 0) {
            wk->wu.vital_new = 0;
        }
        char_move_cmja((WORK*)wk);
        break;
    case RESURRECTION_AIR:
        jumping_union_process((WORK*)wk, 3);
        break;
    default:
        char_move((WORK*)wk);
        break;
    }
}



s32 get_life_add_point(num, ori_add)
u8 num;
s32 ori_add;
{
    s16 add_pts = ori_add;
    u16 ix = num - 20;
    if (ix < 9) {
        add_pts = glap_table[ix / 2];
    }
    return add_pts;
}
