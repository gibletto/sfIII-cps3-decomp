/*
 * PLPAT.C  Player attack routines
 *
 * Player_attack is the attack state of a player work: it clears the per-attack flags, dispatches on
 * routine_no[2] to the common attack routines (Attack_00000 - 10000: normal, jump and command attacks)
 * or, above 15, to the character's own table of special moves (the PLPATxx modules) and sets the draw
 * priority. get_cancel_timer sets the cancel window. The jumping attacks (Attack_01000, 09000, 10000)
 * check the jump guard type themselves, Attack_03000 has no rising phase, and Attack_05000 sets
 * guard_flag and the cancel window.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLNORMAL.h"
#include "PLS02.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "PLS01.h"
#include "EFFG6.h"
#include "PLS00.h"
#include "PLSGAUGE.h"
#include "PLPAT.h"

/* routine_no[3], Attack_01000 */
#define A01_MOVE        1       /* move and run the animation to cue 1 */
#define A01_AIR         2       /* in the air until it lands */
#define A01_LAND        3       /* the landing */

/* routine_no[3], Attack_02000 */
#define A02_MOVE        1       /* move and run the animation to cue 1 */
#define A02_MOVE2       2       /* move and run the animation */
#define A02_CUE         3       /* run the animation to cue 1 */

/* routine_no[3], Attack_03000 */
#define A03_AIR         1       /* in the air until it lands */
#define A03_LAND        2       /* the landing */

/* routine_no[3], Attack_04000 */
#define A04_RUN         1       /* run the animation */

/* routine_no[3], Attack_05000 */
#define A05_MOVE        1       /* move and run the animation to cue 1 */
#define A05_AIR         2       /* in the air until it lands */
#define A05_LAND        3       /* the landing */

/* routine_no[3], Attack_07000 */
#define A07_CUE         1       /* run the animation to cue 20 */

/* routine_no[3], Attack_08000 */
#define A08_CUE         1       /* run the animation to cue 1 */
#define A08_MOVE        2       /* move and run the animation */
#define A08_RUN         3       /* run the animation */

/* routine_no[3], Attack_09000 */
#define A09_MOVE        1       /* move and run the animation to cue 1 */
#define A09_AIR         2       /* in the air until it lands */
#define A09_LAND        3       /* the landing */

/* routine_no[3], Attack_10000 */
#define A10_AIR         1       /* in the air until it lands */
#define A10_LAND        2       /* the landing */

void attack_hit_dummy(PLW* wk);   /* provisional name (0600BABE, PLS02): empty */


void Player_attack(PLW* wk) {
    wk->wu.next_z = wk->wu.my_priority;
    wk->running_f = 0;
    wk->py->flag = 0;
    wk->guard_flag = 3;
    wk->guard_chuu = 0;
    wk->tsukami_f = 0;
    wk->tsukamare_f = 0;
    wk->scr_pos_set_flag = 1;
    wk->dm_hos_flag = 0;
    wk->ukemi_success = 0;
    wk->zuru_timer = 0;
    wk->zuru_ix_counter = 0;
    wk->sa_stop_flag = 0;
    wk->ukemi_success = 0;
    wk->ukemi_ok_timer = 0;
    wk->uot_cd_ok_flag = 0;
    if (wk->wu.routine_no[3] == RN3_START) {
        wk->caution_flag = 1;
    }
    if (wk->wu.routine_no[2] > 15) {
        plxx_extra_attack_table[wk->player_number](wk);
    } else {
        wk->sa->saeff_ok = 0;
        plpat_lv_00[wk->wu.routine_no[2]](wk);
    }
    wk->wu.next_z = ((PLW*)wk->wu.target_adrs)->wu.my_priority - 1;
    if (wk->wu.cg_prio) {
        if (wk->wu.cg_prio == 1) {
            wk->wu.next_z += 3;
        } else {
            wk->wu.next_z -= 3;
        }
    }
}



void Attack_00000(PLW* wk) {
    wk->scr_pos_set_flag = 0;
    Attack_04000(wk);
}



void Attack_01000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.xyz[1].cal = 0;
        wk->wu.rl_flag = wk->wu.rl_waza;
        setup_lvdir_after_autodir(wk);
        set_char_move_init(&wk->wu, 4, wk->as->char_ix);
        get_cancel_timer(wk);
        setup_mvxy_data(&wk->wu, wk->as->data_ix);
        break;
    case A01_MOVE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            add_mvxy_speed(&wk->wu);
            wk->wu.routine_no[3] = A01_AIR;
            wk->wu.cg_type = 0;
        }
        break;
    case A01_AIR:
        jumping_union_process(&wk->wu, 3);
        break;
    case A01_LAND:
        char_move(&wk->wu);
        break;
    }
    jumping_guard_type_check(wk);
}



void Attack_02000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.xyz[1].cal = 0;
        wk->wu.rl_flag = wk->wu.rl_waza;
        setup_lvdir_after_autodir(wk);
        set_char_move_init(&wk->wu, 4, wk->as->char_ix);
        setup_mvxy_data(&wk->wu, wk->as->data_ix);
        get_cancel_timer(wk);
        break;
    case A02_MOVE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            add_mvxy_speed(&wk->wu);
            wk->wu.routine_no[3] = A02_MOVE2;
            wk->wu.cg_type = 0;
        }
        break;
    case A02_MOVE2:
        cal_mvxy_speed(&wk->wu);
        add_mvxy_speed(&wk->wu);
        /* fall through */
    case A02_CUE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            reset_mvxy_data(&wk->wu);
            wk->wu.cg_type = 0;
        }
        break;
    }
}



void Attack_03000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        if (wk->wu.xyz[1].disp.pos <= 0) {
            wk->wu.rl_flag = wk->wu.rl_waza;
            setup_lvdir_after_autodir(wk);
            wk->wu.xyz[1].disp.pos = 0;
            Normal_18000_init_unit(wk, wk->wu.pat_status);
        }
        set_char_move_init(&wk->wu, 4, wk->as->char_ix);
        get_cancel_timer(wk);
        break;
    case A03_AIR:
        jumping_union_process(&wk->wu, 2);
        if (wk->wu.hf.hit_flag) {
            attack_hit_dummy(wk);
            wk->wu.hf.hit_flag = 0;
        }
        break;
    case A03_LAND:
        char_move(&wk->wu);
        break;
    }
}



void Attack_04000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.xyz[1].cal = 0;
        wk->wu.rl_flag = wk->wu.rl_waza;
        setup_lvdir_after_autodir(wk);
        set_char_move_init(&wk->wu, 4, wk->as->char_ix);
        get_cancel_timer(wk);
        break;
    case A04_RUN:
        char_move(&wk->wu);
        break;
    }
}



void Attack_05000(PLW* wk) {
    wk->guard_flag = 1;
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        if (wk->wu.xyz[1].disp.pos > 0) {
            wk->wu.routine_no[3] = A05_AIR;
            char_move_wca(&wk->wu);
        } else {
            wk->wu.xyz[1].cal = 0;
            wk->wu.routine_no[3] = A05_MOVE;
        }
        get_cancel_timer(wk);
        break;
    case A05_MOVE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            add_mvxy_speed(&wk->wu);
            wk->wu.routine_no[3] = A05_AIR;
            wk->wu.cg_type = 0;
        }
        break;
    case A05_AIR:
        jumping_union_process(&wk->wu, 3);
        break;
    case A05_LAND:
        char_move(&wk->wu);
        break;
    }
}



void Attack_06000(PLW* wk) {
    wk->scr_pos_set_flag = 0;
    Attack_07000(wk);
}



void Attack_07000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.xyz[1].cal = 0;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        get_cancel_timer(wk);
        if (wk->wu.cg_type == 20) {
            wk->wu.cg_type = 0;
            wk->wu.rl_flag = wk->wu.rl_waza;
        }
        break;
    case A07_CUE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 20) {
            wk->wu.cg_type = 0;
            wk->wu.rl_flag = wk->wu.rl_waza;
        }
        break;
    }
}



void Attack_08000(PLW* wk) {
    s16 ixx;
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        if (wk->wu.xyz[1].disp.pos <= 0) {
            wk->wu.rl_flag = wk->wu.rl_waza;
            wk->wu.xyz[1].disp.pos = 0;
            ixx = ((wk->wu.pat_status - 20) / 2 & 3) + 9;
            if (ixx > 11) {
                ixx = 10;
            }
            setup_mvxy_data(&wk->wu, ixx);
        }
        get_cancel_timer(wk);
        set_char_move_init(&wk->wu, 4, wk->as->char_ix);
        wk->wu.mvxy.index = wk->as->data_ix;
        break;
    case A08_CUE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            wk->wu.routine_no[3]++;
        }
        if (wk->wu.cg_type == 20) {
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.cg_type = 0;
            wk->wu.mvxy.index++;
        }
        break;
    case A08_MOVE:
        jumping_union_process(&wk->wu, 3);
        if ((wk->wu.routine_no[3] != A08_RUN) && (wk->wu.cg_type == 20)) {
            add_to_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.cg_type = 0;
            wk->wu.mvxy.index++;
        }
        break;
    case A08_RUN:
        char_move(&wk->wu);
        break;
    }
}



void Attack_09000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.xyz[1].cal = 0;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        get_cancel_timer(wk);
        setup_mvxy_data(&wk->wu, wk->as->data_ix);
        if (wk->wu.cg_type == 20) {
            wk->wu.cg_type = 0;
            wk->wu.rl_flag = wk->wu.rl_waza;
        }
        break;
    case A09_MOVE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 20) {
            wk->wu.cg_type = 0;
            wk->wu.rl_flag = wk->wu.rl_waza;
        }
        if (wk->wu.cg_type == 1) {
            add_mvxy_speed(&wk->wu);
            wk->wu.routine_no[3] = A09_AIR;
            wk->wu.cg_type = 0;
        }
        break;
    case A09_AIR:
        jumping_union_process(&wk->wu, 3);
        break;
    case A09_LAND:
        char_move(&wk->wu);
        break;
    }
    jumping_guard_type_check(wk);
}



void Attack_10000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.xyz[1].cal = 0;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        get_cancel_timer(wk);
        setup_mvxy_data(&wk->wu, wk->as->data_ix);
        break;
    case A10_AIR:
        jumping_union_process(&wk->wu, 2);
        break;
    case A10_LAND:
        char_move(&wk->wu);
        break;
    }
    jumping_guard_type_check(wk);
}



void get_cancel_timer(PLW* wk) {
    if (wk->wu.xyz[1].disp.pos > 0) {
        wk->cancel_timer = 2;
    } else {
        wk->cancel_timer = 5;
    }
}

