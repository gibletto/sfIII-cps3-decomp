/*
 * PLPNM.C  Player normal (free movement) process and the normal-state routines
 *
 * Player_normal runs a player who is not attacking, damaged or throwing: standing, walking,
 * crouching, jumping, dashing, turning and the like. It clears the per-frame guard, throw, parry
 * and cancel flags itself, dispatches the routine for routine_no[2] through the normal routine
 * table (plpnm_lv_00) and then sets the draw priority relative to the opponent when the animation
 * asks for it. Normal_00000 is the entry routine that runs appear_player for the round
 * introduction; Normal_01000 is the standing routine (pcon_dp_flag holds it in pose 9/60).
 * The other normal routines: crouching and turning (Normal_02000 - 04000), walking and jump starts
 * (Normal_05000, 06000 through nm_05_xxxx/nm_06_xxxx), dashes, jumps (Normal_16000 - 18000), parry
 * (Normal_31000, 35000, Normal_air_paring) and the other special movement states up to Normal_41000.
 * Called from the player main routine (PLMAIN).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLS01.h"
#include "appear.h"
#include "PLPNM.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "lose_pl.h"
#include "PLS02.h"
#include "PLSGAUGE.h"
#include "PLS00.h"
#include "EFFG6.h"
#include "win_pl.h"
#include "PLNORMAL.h"



void Player_normal(wk)
PLW* wk;
{
    wk->wu.next_z = wk->wu.my_priority;
    wk->running_f = 0;
    wk->py->flag = 0;
    wk->guard_flag = 0;
    wk->guard_chuu = 0;
    wk->tsukami_f = 0;
    wk->tsukamare_f = 0;
    wk->scr_pos_set_flag = 1;
    wk->dm_hos_flag = 0;
    wk->ukemi_success = 0;
    wk->zuru_timer = 0;
    wk->zuru_ix_counter = 0;
    wk->sa_stop_flag = 0;
    wk->atemi_flag = 0;
    wk->caution_flag = 0;
    wk->sa->saeff_ok = 0;
    wk->ukemi_success = 0;
    wk->ukemi_ok_timer = 0;
    wk->uot_cd_ok_flag = 0;
    wk->cancel_timer = 0;
    plpnm_lv_00[wk->wu.routine_no[2]](wk);
    if (wk->wu.cg_prio) {
        wk->wu.next_z = ((WORK*)wk->wu.target_adrs)->my_priority;
        if (wk->wu.cg_prio == 1) {
            wk->wu.next_z++;
        } else {
            wk->wu.next_z -= 3;
        }
    }
}



void Normal_00000(PLW* wk) {
    appear_player(wk);
}


void Normal_01000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        if (pcon_dp_flag) {
            if (wk->wu.now_koc == 0 && wk->wu.char_index == 0) {
                exset_char_move_init((WORK*)wk, 9, 60);
            } else {
                set_char_move_init((WORK*)wk, 0, 0);
            }
        } else {
            set_char_move_init((WORK*)wk, 0, 0);
            wk->scr_pos_set_flag = 0;
        }
    case 1:
        if (pcon_dp_flag) {
            if (wk->wu.now_koc != 9 || wk->wu.char_index != 60) {
                exset_char_move_init((WORK*)wk, 9, 60);
            }
        } else if (wk->wu.now_koc == 9 && wk->wu.char_index == 60) {
            exset_char_move_init((WORK*)wk, 0, 0);
            wk->scr_pos_set_flag = 0;
        }
        char_move((WORK*)wk);
        break;
    }
}



void Normal_02000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init((WORK*)wk, 0, 1);
        break;
    case 1:
        char_move((WORK*)wk);
        break;
    }
}



void Normal_03000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority - 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init(&wk->wu, 0, 2);
        setup_mvxy_data(&wk->wu, 0);
        wk->wu.mvxy.a[0].sp >>= 1;
        add_mvxy_speed(&wk->wu);
        wk->wu.mvxy.a[0].sp *= 2;
        break;
    case 1:
        cal_mvxy_speed(&wk->wu);
        add_mvxy_speed(&wk->wu);
        char_move(&wk->wu);
        break;
    }
}



void Normal_04000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init((WORK*)wk, 0, 3);
        setup_mvxy_data((WORK*)wk, 1);
        add_mvxy_speed((WORK*)wk);
        break;
    case 1:
        cal_mvxy_speed((WORK*)wk);
        add_mvxy_speed((WORK*)wk);
        char_move((WORK*)wk);
        break;
    }
}



void Normal_05000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority - 1;
    }
    wk->running_f = 1;
    wk->guard_flag = 3;
    normal_05[wk->player_number](wk);
    jumping_guard_type_check(wk);
}



void nm_05_0000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init((WORK*)wk, 0, 4);
        setup_mvxy_data((WORK*)wk, 2);
    case 1:
        if (wk->wu.cg_type == 1) {
            add_mvxy_speed((WORK*)wk);
            wk->wu.routine_no[3]++;
        } else {
            char_move((WORK*)wk);
        }
        break;
    case 2:
        jumping_union_process((WORK*)wk, 3);
        break;
    case 3:
        char_move((WORK*)wk);
        break;
    }
}



void nm_05_0100(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init((WORK*)wk, 0, 4);
        setup_mvxy_data((WORK*)wk, 2);
        if (wk->wu.cg_type == 1) {
            add_mvxy_speed((WORK*)wk);
            wk->wu.routine_no[3]++;
            wk->wu.cg_type = 0;
        }
        break;
    case 1:
        char_move((WORK*)wk);
        if (wk->wu.cg_type == 1) {
            add_mvxy_speed((WORK*)wk);
            wk->wu.routine_no[3]++;
            wk->wu.cg_type = 0;
        }
        break;
    case 2:
        char_move((WORK*)wk);
        if (wk->wu.cg_type == 1) {
            wk->wu.routine_no[3]++;
            wk->wu.cg_type = 0;
            break;
        }
        cal_mvxy_speed((WORK*)wk);
        add_mvxy_speed((WORK*)wk);
        break;
    case 3:
        char_move((WORK*)wk);
        break;
    }
}



void Normal_06000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + 1;
    }
    wk->running_f = 2;
    wk->guard_flag = 3;
    normal_06[wk->player_number](wk);
    jumping_guard_type_check(wk);
}



void nm_06_0000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init((WORK*)wk, 0, 5);
        break;
    case 1:
        char_move((WORK*)wk);
        break;
    }
}



void nm_06_0100(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init((WORK*)wk, 0, 5);
        setup_mvxy_data((WORK*)wk, 3);
    case 1:
        if (wk->wu.cg_type == 1) {
            add_mvxy_speed((WORK*)wk);
            wk->wu.routine_no[3]++;
        } else {
            char_move((WORK*)wk);
        }
        break;
    case 2:
        jumping_union_process((WORK*)wk, 3);
        break;
    case 3:
        char_move((WORK*)wk);
        break;
    }
}



void nm_06_0200(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init((WORK*)wk, 0, 5);
        setup_mvxy_data((WORK*)wk, 3);
        if (wk->wu.cg_type == 1) {
            add_mvxy_speed((WORK*)wk);
            wk->wu.routine_no[3]++;
            wk->wu.cg_type = 0;
        }
        break;
    case 1:
        char_move((WORK*)wk);
        if (wk->wu.cg_type == 1) {
            add_mvxy_speed((WORK*)wk);
            wk->wu.routine_no[3]++;
            wk->wu.cg_type = 0;
        }
        break;
    case 2:
        char_move((WORK*)wk);
        if (wk->wu.cg_type == 1) {
            wk->wu.routine_no[3]++;
            wk->wu.cg_type = 0;
            break;
        }
        cal_mvxy_speed((WORK*)wk);
        add_mvxy_speed((WORK*)wk);
        break;
    case 3:
        char_move((WORK*)wk);
        break;
    }
}



void Normal_07000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority - 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init((WORK*)wk, 0, 11);
        break;
    case 1:
        char_move((WORK*)wk);
        break;
    }
}



void Normal_08000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority - 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init((WORK*)wk, 0, 6);
        break;
    case 1:
        char_move((WORK*)wk);
        break;
    }
}



void Normal_09000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority - 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init((WORK*)wk, 0, 7);
        break;
    case 1:
        char_move((WORK*)wk);
        break;
    }
}



void Normal_10000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority - 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init((WORK*)wk, 0, 8);
        break;
    case 1:
        char_move((WORK*)wk);
        break;
    }
}



void Normal_11000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + -1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init(&wk->wu, 0, 0x9);
        setup_mvxy_data(&wk->wu, 0x4);
        add_mvxy_speed(&wk->wu);
        break;
    case 1:
        cal_mvxy_speed(&wk->wu);
        add_mvxy_speed(&wk->wu);
        char_move(&wk->wu);
        break;
    }
}



void Normal_12000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init(&wk->wu, 0, 10);
        setup_mvxy_data(&wk->wu, 5);
        add_mvxy_speed(&wk->wu);
        break;
    case 1:
        cal_mvxy_speed(&wk->wu);
        add_mvxy_speed(&wk->wu);
        char_move(&wk->wu);
        break;
    }
}



void Normal_13000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init((WORK*)wk, 0, 50);
        break;
    case 1:
        char_move((WORK*)wk);
        break;
    }
}



void Normal_16000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init((WORK*)wk, 0, 12);
        break;
    case 1:
        char_move((WORK*)wk);
        break;
    }
}



void Normal_17000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init((WORK*)wk, 0, 13);
        break;
    case 1:
        char_move((WORK*)wk);
        break;
    }
}



void Normal_18000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init(&wk->wu, 0, jpdat_tbl[wk->wu.routine_no[2] - 18][0]);
        setup_mvxy_data(&wk->wu, jpdat_tbl[wk->wu.routine_no[2] - 18][1]);
        add_mvxy_speed(&wk->wu);
        break;
    case 1:
        jumping_union_process(&wk->wu, 2);
        break;
    case 2:
        char_move(&wk->wu);
        break;
    }
    jumping_guard_type_check(wk);
}



void Normal_18000_init_unit(wk, ps)
PLW* wk;
u8 ps;
{
    u8 i = (ps - 14) / 2;
    if (i > 8) {
        i = 4;
    }
    set_char_move_init(&wk->wu, 0, jpdat_tbl[i][0]);
    setup_mvxy_data(&wk->wu, jpdat_tbl[i][1]);
    add_mvxy_speed(&wk->wu);
}



void Normal_27000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init(&wk->wu, 0, wk->wu.routine_no[2] + 2);
        break;
    case 1:
        char_move(&wk->wu);
        break;
    }
}



void Normal_31000(PLW* wk) {
    if (((WORK*)wk->wu.target_adrs)->cg_prio != 2) {
        wk->wu.next_z = 32;
    }
    wk->guard_chuu = guard_kind[wk->wu.routine_no[2] - 27];
    wk->scr_pos_set_flag = 0;
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        set_char_move_init((WORK*)wk, 0, wk->wu.routine_no[2] - 7);
        set_hit_stop_hit_quake((WORK*)wk);
        Flash_MT[(wk->wu.id)] = 2;
        add_sp_arts_gauge_paring(wk);
        break;
    case 1:
        char_move((WORK*)wk);
        break;
    }
}



void Normal_35000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority - 1;
    }
    wk->guard_chuu = guard_kind[wk->wu.routine_no[2] - 27];
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_hit_stop_hit_quake((WORK*)wk);
        if (wk->wu.rl_flag != ((wk->wu.dm_rl + 1) & 1)) {
            wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
            wk->wu.mvxy.a[0].sp = -wk->wu.mvxy.a[0].sp;
            wk->wu.mvxy.d[0].sp = -wk->wu.mvxy.d[0].sp;
        }
        remake_mvxy_PoSB((WORK*)wk);
        set_char_move_init((WORK*)wk, 0, 27);
        Flash_MT[(wk->wu.id)] = 2;
        break;
    case 1:
        if (((WORK*)wk->wu.target_adrs)->cg_prio != 2) {
            wk->wu.next_z = 32;
        }
        jumping_union_process((WORK*)wk, 2);
        break;
    case 2:
        char_move((WORK*)wk);
        break;
    }
}



/* provisional name */
void Normal_air_paring(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority - 1;
    }
    wk->guard_chuu = guard_kind[wk->wu.routine_no[2] - 27];
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_hit_stop_hit_quake((WORK*)wk);
        if (wk->wu.rl_flag != ((wk->wu.dm_rl + 1) & 1)) {
            wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
            wk->wu.mvxy.a[0].sp = -wk->wu.mvxy.a[0].sp;
            wk->wu.mvxy.d[0].sp = -wk->wu.mvxy.d[0].sp;
        }
        setup_air_paring_mvxy((WORK*)wk);
        set_char_move_init((WORK*)wk, 0, 27);
        Flash_MT[(wk->wu.id)] = 2;
        break;
    case 1:
        if (((WORK*)wk->wu.target_adrs)->cg_prio != 2) {
            wk->wu.next_z = 32;
        }
        jumping_union_process((WORK*)wk, 2);
        break;
    case 2:
        char_move((WORK*)wk);
        break;
    }
}



void Normal_36000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + 1;
    }
    char_move((WORK*)wk);
}



void Normal_37000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + 1;
    }
    char_move((WORK*)wk);
}



void Normal_38000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority + 1;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
    case 1:
        jumping_union_process(&wk->wu, 2);
        break;
    case 2:
        char_move(&wk->wu);
        break;
    }
    jumping_guard_type_check(wk);
}



void Normal_39000(PLW* wk) {
    if (wk->the_same_players) {
        wk->wu.next_z = wk->wu.my_priority - 1;
    }
    if (wk->wu.routine_no[3]) {
        char_move((WORK*)wk);
    } else {
        wk->wu.routine_no[3]++;
        set_char_move_init((WORK*)wk, 0, 23);
    }
}



void Normal_40000(PLW* wk) {
    wk->wu.next_z = 38;
    win_player(wk);
}



void Normal_41000(PLW* wk) {
    wk->wu.next_z = 34;
    lose_player(wk);
}
