/*
 * EFF94.C  Effect 94: the bystander next to a player
 *
 * effect_94_entry makes one for each player whose player_number is 7
 * (none when either player is 8). With old_rno[3] set it follows its player: eff94_00-07
 * (jp_a) wait, turn round, walk to and from the player, react to the player's attack and
 * leave at the end of the fight; eff94_select picks the next state. Without it the object
 * stands at its stage position and runs eff94_10-13 (jp_b) by the round result.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "CALDIR.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLS02.h"
#include "aboutspr.h"
#include "bg_sub_5.h"
#include "eff94.h"

const s16 eff94_wait_tbl[16] = { 8, 34, 278, 40, 42, 140, 238, 0, 240, 18, 6, 72, 26, 124, 80, 32 };
const s8 eff94_attack_tbl[8] = { 0, 1, 0, 0, 1, 0, 0, 1 };
extern const s16 eff94_time_tbl[32];


#pragma inline(eff94_check_and_go)



void effect_94_move(WORK_Other* ewk) {
    void (*const eff94_jp_a[8])(WORK_Other*) = { eff94_00, eff94_01, eff94_02, eff94_03,
                                                 eff94_04, eff94_05, eff94_06, eff94_07 };
    void (*const eff94_jp_b[4])(WORK_Other*) = { eff94_10, eff94_11, eff94_12, eff94_13 };
    if (ewk->wu.old_rno[3]) {
        switch (ewk->wu.routine_no[0]) {
        case 0:
            ewk->wu.routine_no[0]++;
            break;
        case 1:
            ewk->wu.routine_no[0]++;
            ewk->wu.old_rno[1] = ewk->wu.xyz[0].disp.pos = plw[ewk->master_id].wu.xyz[0].disp.pos;
            ewk->wu.old_rno[0] = 0;
            ewk->wu.disp_flag = 1;
            break;
        case 2:
            ewk->wu.rl_waza = ewk->wu.old_rno[5];
            ewk->wu.old_rno[5] = plw[ewk->master_id].wu.xyz[0].disp.pos - ewk->wu.xyz[0].disp.pos;
            ewk->wu.old_rno[6] = (ewk->wu.old_rno[5] < 0) ? -ewk->wu.old_rno[5] : ewk->wu.old_rno[5];
            if (!EXE_flag && !Game_pause) {
                eff94_jp_a[ewk->wu.routine_no[1]](ewk);
            }
            disp_pos_trans_entry_s(ewk);
            break;
        }
    } else {
        switch (ewk->wu.routine_no[0]) {
        case 0:
            ewk->wu.routine_no[0]++;
            if (bg_w.stage == 7 && bg_w.area == 1) {
                ewk->wu.xyz[0].disp.pos = 0x1A0;
            } else {
                ewk->wu.xyz[0].disp.pos = bg_w.bgw[1].pos_x_work;
            }
            break;
        case 1:
            if (!EXE_flag && !Game_pause) {
                eff94_jp_b[ewk->wu.routine_no[1]](ewk);
            }
            disp_pos_trans_entry_s(ewk);
            break;
        }
    }
}

const s16 eff94_time_tbl[32] = { 16, 16, 16, 32, 32, 32, 48, 48, 48, 56, 56, 56, 64, 64, 64, 72,
                                 72, 72, 72, 80, 80, 80, 88, 88, 88, 96, 96, 96, 104, 104, 104, 104 };



/* stand */
/* provisional name */
void eff94_00(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.routine_no[2]++;
        set_char_move_init(&ewk->wu, 0, 17);
        break;
    case 1:
        char_move(&ewk->wu);
        if (eff94_select(ewk)) {
            ewk->wu.dir_step++;
            if (ewk->wu.dir_step > 60) {
                eff94_go_06(ewk);
            }
        }
        break;
    }
}



/* provisional name */
void eff94_go_00(WORK_Other* ewk) {
    ewk->wu.routine_no[1] = 0;
    ewk->wu.routine_no[2] = 0;
    eff94_set_wait(ewk);
}



/* walk towards the player */
/* provisional name */
void eff94_01(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.routine_no[2]++;
        set_char_move_init(&ewk->wu, 0, 17);
    case 1:
        ewk->wu.old_rno[0]--;
        if (ewk->wu.old_rno[0] < 0) {
            ewk->wu.dir_step = 0;
            ewk->wu.routine_no[2]++;
            set_char_move_init(&ewk->wu, 0, 18);
            ewk->wu.old_rno[4] = plw[ewk->master_id].wu.xyz[0].disp.pos;
            ewk->wu.old_rno[0] = eff94_time_tbl[(ewk->wu.old_rno[6] >> 5) & 31];
            cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[0], ewk->wu.old_rno[4], ewk->wu.xyz[1].disp.pos, 0, 0);
        } else {
            char_move(&ewk->wu);
        }
        break;
    case 2:
        char_move(&ewk->wu);
        if (eff94_check_front(ewk)) {
            eff94_check_and_go(ewk);
            ewk->wu.old_rno[0] = 0;
        } else {
            ewk->wu.old_rno[0]--;
            if (ewk->wu.old_rno[0] <= 0) {
                ewk->wu.routine_no[2]++;
            } else {
                add_x_sub(ewk);
            }
        }
        break;
    case 3:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            eff94_check_and_go(ewk);
            ewk->wu.old_rno[0] = 0;
        } else {
            add_x_sub(ewk);
        }
        break;
    }
}



/* provisional name */
void eff94_go_01(WORK_Other* ewk) {
    ewk->wu.routine_no[1] = 1;
    ewk->wu.routine_no[2] = 0;
    eff94_set_wait(ewk);
}



/* turn round */
/* provisional name */
void eff94_02(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.routine_no[2]++;
        set_char_move_init(&ewk->wu, 0, 19);
        break;
    case 1:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            eff94_go_01(ewk);
            ewk->wu.rl_flag = ewk->wu.rl_flag ^ 1;
        }
        break;
    }
}



/* provisional name */
void eff94_go_02(WORK_Other* ewk) {
    ewk->wu.routine_no[1] = 2;
    ewk->wu.routine_no[2] = 0;
}



/* react to the player's attack */
/* provisional name */
void eff94_03(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.old_rno[0]--;
        if (ewk->wu.old_rno[0] < 0) {
            ewk->wu.routine_no[2]++;
            set_char_move_init(&ewk->wu, 0, 20);
        }
        break;
    case 1:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            eff94_check_and_go(ewk);
        }
        break;
    }
}



/* the fight is over */
/* provisional name */
void eff94_04(WORK_Other* ewk) {
    if (pcon_rno[0] == 2 && pcon_rno[1] == 3) {
        ewk->wu.old_rno[0] = 60;
        ewk->wu.routine_no[1] = 7;
        ewk->wu.routine_no[2] = 0;
    } else {
        switch (ewk->wu.routine_no[2]) {
        case 0:
            ewk->wu.routine_no[2]++;
            set_char_move_init(&ewk->wu, 0, 23);
            break;
        case 1:
            char_move(&ewk->wu);
            if (plw[ewk->master_id].wu.char_index == 39) {
                ewk->wu.routine_no[1] = 5;
                ewk->wu.routine_no[2] = 0;
            }
            break;
        }
    }
}



/* provisional name */
void eff94_05(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.routine_no[2]++;
        ewk->wu.rl_flag = 0;
        set_char_move_init(&ewk->wu, 0, 24);
        break;
    case 1:
        char_move(&ewk->wu);
        break;
    case 2:
        break;
    }
}



/* provisional name */
void eff94_06(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.routine_no[2]++;
        set_char_move_init(&ewk->wu, 0, 28);
        break;
    case 1:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            eff94_check_and_go(ewk);
        }
        break;
    }
}



/* provisional name */
void eff94_go_06(WORK_Other* ewk) {
    ewk->wu.dir_step = 0;
    ewk->wu.routine_no[1] = 6;
    ewk->wu.routine_no[2] = 0;
    eff94_set_wait(ewk);
}



/* provisional name */
void eff94_07(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.routine_no[2]++;
        ewk->wu.disp_flag = 0;
        break;
    case 1:
        break;
    }
}



/* the round has been decided */
/* provisional name */
s32 eff94_check_end(WORK_Other* ewk) {
    if (!Allow_a_battle_f && Conclusion_Flag == 1 && C_No0 >= 2) {
        ewk->wu.routine_no[1] = 4;
        ewk->wu.routine_no[2] = 0;
        return 1;
    }
    return 0;
}



/* in front of the player */
/* provisional name */
s32 eff94_check_front(WORK_Other* ewk) {
    if (ewk->wu.rl_flag) {
        if (ewk->wu.xyz[0].disp.pos > plw[ewk->master_id].wu.xyz[0].disp.pos) {
            return 1;
        }
        return 0;
    }
    if (ewk->wu.xyz[0].disp.pos < plw[ewk->master_id].wu.xyz[0].disp.pos) {
        return 1;
    }
    return 0;
}



/* provisional name */
void eff94_check_and_go(WORK_Other* ewk) {
    if (eff94_select(ewk)) {
        eff94_go_00(ewk);
    }
}



/* the next state; 1 when it stays */
/* provisional name */
s32 eff94_select(WORK_Other* ewk) {
    s16 ix;
    if (eff94_check_end(ewk)) {
        return;
    }
    if (ewk->wu.old_rno[6] > 96) {
        if (ewk->wu.rl_flag) {
            if (ewk->wu.xyz[0].disp.pos > plw[ewk->master_id].wu.xyz[0].disp.pos) {
                eff94_go_02(ewk);
            } else {
                eff94_go_01(ewk);
            }
        } else if (ewk->wu.xyz[0].disp.pos < plw[ewk->master_id].wu.xyz[0].disp.pos) {
            eff94_go_02(ewk);
        } else {
            eff94_go_01(ewk);
        }
        return 0;
    } else {
        ix = random_16_com();
        ix &= 7;
        if (eff94_pl_attack_check(&plw[ewk->master_id])) {
            if (eff94_attack_tbl[ix]) {
                ewk->wu.routine_no[1] = 3;
                ewk->wu.routine_no[2] = 0;
                ewk->wu.old_rno[0] = 8;
            }
            return 0;
        }
        return 1;
    }
}



/* provisional name */
void eff94_10(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.routine_no[2]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 26);
        break;
    case 1:
        char_move(&ewk->wu);
        if (!Allow_a_battle_f && Conclusion_Flag == 1 && C_No0 >= 2) {
            ewk->wu.routine_no[1] = 1;
            ewk->wu.routine_no[2] = 0;
        }
        break;
    }
}



/* provisional name */
void eff94_11(WORK_Other* ewk) {
    if (Winner_id != ewk->master_id) {
        ewk->wu.routine_no[1] = 2;
        ewk->wu.routine_no[2] = 0;
    } else if (plw[ewk->master_id].wu.char_index == 39) {
        ewk->wu.routine_no[1] = 5;
        ewk->wu.routine_no[2] = 0;
    }
}



/* provisional name */
void eff94_12(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.routine_no[2]++;
        set_char_move_init(&ewk->wu, 0, 29);
        break;
    case 1:
        if (pcon_rno[0] == 2 && pcon_rno[1] == 3) {
            ewk->wu.disp_flag = 0;
        }
        char_move(&ewk->wu);
        break;
    }
}



/* provisional name */
void eff94_13(WORK_Other* ewk) {
}



/* provisional name */
void eff94_set_wait(WORK_Other* ewk) {
    s16 ix;
    ix = random_16_com();
    ix &= 15;
    ewk->wu.old_rno[0] = eff94_wait_tbl[ix];
}






s32 effect_94_init(s16 PL_id, s16 sw) {
    WORK_Other* ewk;
    s16 ix;
    s16 y;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 94;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->my_master = (u32*)&plw[PL_id];
    ewk->master_id = PL_id;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = plw[PL_id].wu.my_col_code;
    ewk->wu.my_family = 2;
    ewk->wu.old_rno[3] = sw;
    ewk->wu.my_priority = 67;
    ewk->wu.position_z = 67;
    ewk->wu.sync_suzi = 0;
    ewk->wu.kage_flag = 1;
    ewk->wu.kage_hx = -2;
    ewk->wu.kage_char = 9;
    ewk->wu.kage_prio = ewk->wu.my_priority + 1;
    *ewk->wu.char_table = etc2_char_table;
    if (bg_w.stage != 1) {
        y = 46;
    } else {
        y = 43;
    }
    ewk->wu.kage_hy = ewk->wu.xyz[1].disp.pos = y;
    suzi_offset_set(&ewk->wu);
    if (PL_id) {
        ewk->wu.rl_flag = 0;
    } else {
        ewk->wu.rl_flag = 1;
    }
    ewk->wu.dir_step = 0;
    return 0;
}



/* provisional name */
void effect_94_entry(s16 sw) {
    if (sw) {
        if (plw[0].player_number == 8 || plw[1].player_number == 8) {
            sw = 0;
        }
    }
    if (plw[0].player_number == 7 && plw[1].player_number == 7) {
        effect_94_init(0, 0);
        return;
    }
    if (plw[0].player_number == 7) {
        effect_94_init(0, sw);
    }
    if (plw[1].player_number == 7) {
        effect_94_init(1, sw);
    }
}
