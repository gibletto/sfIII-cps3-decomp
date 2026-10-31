/*
 * PLS00.C  Player lever and button check per state
 *
 * The input side of player control. check_lever_data is called from the player main routine
 * and, for each routine class (normal, damage, catch, caught, attack), runs the check that
 * decides whether the player's input starts a new action this frame.
 * process_normal dispatches nm_00000-nm_40000 by the current normal routine: each tries in turn
 * super arts, special moves, throws, leap attacks, normal attacks, jumps, dashes, walks, guards
 * and turns, depending on what that state allows. process_damage, process_catch and
 * process_attack do the same for the other classes; check_cg_cancel_data handles cancelling an
 * attack into another through the animation's cancel data.
 * The TO_nm_ routines switch a work into a given normal routine and run its first check.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "PLS01.h"
#include "PLS03ATT.h"
#include "PLS03.h"
#include "PLCNTSET.h"
#include "plcntset_2.h"
#include "PLPDM.h"
#include "PLS00.h"
#include "fighter.h"
#include "cmd_data.h"



void check_lever_data(PLW* wk) {
    if (wk->wu.routine_no[0] == PLAYER_MV_FIGHT) {
        process_ndcca[wk->wu.routine_no[1]](wk);
    }
}



void process_normal(PLW* wk) {
    plpnm_xxxxx[wk->wu.routine_no[2]](wk);
}



void TO_nm_01000(WORK* wk) {
    wk->routine_no[1] = PLAYER_NORMAL;
    wk->routine_no[2] = NORMAL_STAND;
    wk->routine_no[3] = RN3_START;
    wk->cg_type = 0;
    nm_01000((PLW*)wk);
}



void TO_nm_36000(WORK* wk) {
    wk->routine_no[1] = PLAYER_NORMAL;
    wk->routine_no[2] = 36;
    wk->routine_no[3] = RN3_START;
    wk->cg_type = 0;
    nm_01000((PLW*)wk);
}



void TO_nm_09000(WORK* wk) {
    wk->routine_no[1] = PLAYER_NORMAL;
    wk->routine_no[2] = 9;
    wk->routine_no[3] = RN3_START;
    wk->cg_type = 0;
    nm_09000((PLW*)wk);
}



void TO_nm_37000(WORK* wk) {
    wk->routine_no[1] = PLAYER_NORMAL;
    wk->routine_no[2] = 37;
    wk->routine_no[3] = RN3_START;
    wk->cg_type = 0;
    nm_09000((PLW*)wk);
}



void TO_nm_38000(WORK* wk) {
    wk->routine_no[1] = PLAYER_NORMAL;
    wk->routine_no[2] = 38;
    wk->routine_no[3] = 1;
    wk->cg_type = 0;
}



void TO_nm_18000_01(WORK* wk) {
    wk->routine_no[1] = PLAYER_NORMAL;
    wk->routine_no[2] = 18;
    wk->routine_no[3] = 1;
    wk->cg_type = 0;
    nm_18000((PLW*)wk);
}



void nm_00000(PLW* wk) {}



void nm_01000(PLW* wk) {
    if (setup_kuzureochi(wk)) {
        return;
    }
    if (check_super_arts_attack(wk)) {
        return;
    }
    if (check_special_attack(wk)) {
        return;
    }
    if (check_catch_attack(wk)) {
        return;
    }
    if (check_leap_attack(wk)) {
        return;
    }
    if (check_nm_attack(wk)) {
        return;
    }
    if (check_cg_cancel_data(wk)) {
        return;
    }
    if (check_turn_to_back(wk)) {
        return;
    }
    if (check_F_R_dash(wk)) {
        return;
    }
    if (check_360_jump(wk)) {
        return;
    }
    if (check_jump_ready(wk)) {
        return;
    }
    if (check_bend_myself(wk)) {
        return;
    }
    if (check_defense_lever(wk)) {
        return;
    }
    if (check_F_R_walk(wk)) {
        return;
    }
}



void nm_02000(PLW* wk) {
    if (wk->wu.cg_type == 0xFF) {
        TO_nm_01000((WORK*)wk);
        return;
    }
    if (wk->wu.cg_type == 64) {
        TO_nm_36000((WORK*)wk);
        return;
    }
    if (check_super_arts_attack(wk)) {
        return;
    }
    if (check_special_attack(wk)) {
        return;
    }
    if (check_catch_attack(wk)) {
        return;
    }
    if (check_leap_attack(wk)) {
        return;
    }
    if (check_nm_attack(wk)) {
        return;
    }
    if (check_cg_cancel_data(wk)) {
        return;
    }
    if (check_F_R_dash(wk)) {
        return;
    }
    if (check_360_jump(wk)) {
        return;
    }
    if (check_jump_ready(wk)) {
        return;
    }
    if (check_bend_myself(wk)) {
        return;
    }
    if (check_defense_lever(wk)) {
        return;
    }
    if (check_F_R_walk(wk)) {
        return;
    }
}



void nm_03000(PLW* wk) {
    if (check_super_arts_attack(wk)) {
        return;
    }
    if (check_special_attack(wk)) {
        return;
    }
    if (check_catch_attack(wk)) {
        return;
    }
    if (check_leap_attack(wk)) {
        return;
    }
    if (check_nm_attack(wk)) {
        return;
    }
    if (check_cg_cancel_data(wk)) {
        return;
    }
    if (check_turn_to_back(wk)) {
        return;
    }
    if (check_F_R_dash(wk)) {
        return;
    }
    if (check_360_jump(wk)) {
        return;
    }
    if (check_jump_ready(wk)) {
        return;
    }
    if (check_bend_myself(wk)) {
        return;
    }
    if (check_walking_lv_dir(wk)) {
        wk->wu.routine_no[2] = 39;
        wk->wu.routine_no[3] = RN3_START;
        wk->wu.cg_type = 0;
    }
    if (check_defense_lever(wk)) {
        return;
    }
}



void nm_05000(PLW* wk) {
    jumping_cg_type_check(wk);
}



void nm_07000(PLW* wk) {
    if (wk->wu.cg_type == 0xFF) {
        TO_nm_01000((WORK*)wk);
        return;
    }
    if (check_super_arts_attack(wk)) {
        return;
    }
    if (check_special_attack(wk)) {
        return;
    }
    if (check_catch_attack(wk)) {
        return;
    }
    if (check_leap_attack(wk)) {
        return;
    }
    if (check_nm_attack(wk)) {
        return;
    }
    if (check_cg_cancel_data(wk)) {
        return;
    }
    if (check_turn_to_back(wk)) {
        return;
    }
    if (check_F_R_dash(wk)) {
        return;
    }
    if (check_360_jump(wk)) {
        return;
    }
    if (check_jump_ready(wk)) {
        return;
    }
    if (check_defense_lever(wk)) {
        return;
    }
    if (check_F_R_walk(wk)) {
        return;
    }
    if (check_bend_myself(wk)) {
        return;
    }
}



void nm_08000(PLW* wk) {
    if (wk->wu.cg_type == 0xFF) {
        TO_nm_09000((WORK*)wk);
        return;
    }
    if (wk->wu.cg_type == 64) {
        TO_nm_37000((WORK*)wk);
        return;
    }
    if (check_super_arts_attack(wk)) {
        return;
    }
    if (check_special_attack(wk)) {
        return;
    }
    if (check_catch_attack(wk)) {
        return;
    }
    if (check_leap_attack(wk)) {
        return;
    }
    if (check_nm_attack(wk)) {
        return;
    }
    if (check_cg_cancel_data(wk)) {
        return;
    }
    if (check_turn_to_back(wk)) {
        return;
    }
    if (check_F_R_dash(wk)) {
        return;
    }
    if (check_360_jump(wk)) {
        return;
    }
    if (check_jump_ready(wk)) {
        return;
    }
    if (check_defense_lever(wk)) {
        return;
    }
    if (check_F_R_step(wk)) {
        return;
    }
    if (check_stand_up(wk)) {
        return;
    }
}



void nm_09000(PLW* wk) {
    if (setup_kuzureochi(wk)) {
        return;
    }
    if (check_super_arts_attack(wk)) {
        return;
    }
    if (check_special_attack(wk)) {
        return;
    }
    if (check_catch_attack(wk)) {
        return;
    }
    if (check_leap_attack(wk)) {
        return;
    }
    if (check_nm_attack(wk)) {
        return;
    }
    if (check_cg_cancel_data(wk)) {
        return;
    }
    if (check_turn_to_back(wk)) {
        return;
    }
    if (check_F_R_dash(wk)) {
        return;
    }
    if (check_360_jump(wk)) {
        return;
    }
    if (check_jump_ready(wk)) {
        return;
    }
    if (check_stand_up(wk)) {
        return;
    }
    if (check_defense_lever(wk)) {
        return;
    }
    if (check_F_R_step(wk)) {
        return;
    }
}



void nm_10000(PLW* wk) {
    if (wk->wu.cg_type == 0xFF) {
        TO_nm_09000((WORK*)wk);
        return;
    }
    if (check_super_arts_attack(wk)) {
        return;
    }
    if (check_special_attack(wk)) {
        return;
    }
    if (check_catch_attack(wk)) {
        return;
    }
    if (check_leap_attack(wk)) {
        return;
    }
    if (check_nm_attack(wk)) {
        return;
    }
    if (check_cg_cancel_data(wk)) {
        return;
    }
    if (check_F_R_dash(wk)) {
        return;
    }
    if (check_360_jump(wk)) {
        return;
    }
    if (check_jump_ready(wk)) {
        return;
    }
    if (check_defense_lever(wk)) {
        return;
    }
    if (check_stand_up(wk)) {
        return;
    }
}



void nm_11000(PLW* wk) {
    if (check_super_arts_attack(wk)) {
        return;
    }
    if (check_special_attack(wk)) {
        return;
    }
    if (check_catch_attack(wk)) {
        return;
    }
    if (check_leap_attack(wk)) {
        return;
    }
    if (check_nm_attack(wk)) {
        return;
    }
    if (check_cg_cancel_data(wk)) {
        return;
    }
    if (check_turn_to_back(wk)) {
        return;
    }
    if (check_F_R_dash(wk)) {
        return;
    }
    if (check_360_jump(wk)) {
        return;
    }
    if (check_jump_ready(wk)) {
        return;
    }
    if (check_stand_up(wk)) {
        return;
    }
    if (check_defense_lever(wk)) {
        return;
    }
    if (check_walking_lv_dir2(wk)) {
        return;
    }
}



void nm_13000(WORK* wk) {
    if (wk->cg_type == 0xFF) {
        TO_nm_01000(wk);
    }
}



void nm_16000(PLW* wk) {
    set_new_jpdir(wk);
    switch (wk->wu.cg_type) {
    case 0xFF:
        check_jump_rl_dir(wk);
        switch (wk->jpdir) {
        case LVDIR_FORWARD:
            wk->wu.routine_no[2] = 21;
            break;
        case LVDIR_BACK:
            wk->wu.routine_no[2] = 23;
            break;
        default:
            wk->wu.routine_no[2] = 22;
            break;
        }
        wk->wu.routine_no[3] = RN3_START;
        break;
    case 1:
        break;
    }
    if (check_super_arts_attack(wk)) {
        return;
    }
    if (check_special_attack(wk)) {
        return;
    }
    if (check_catch_attack(wk)) {
        return;
    }
    wk->wu.pat_status = jump_pat_status_data[wk->wu.rl_flag != wk->wu.rl_waza][wk->cp->lever_dir];
    if (check_leap_attack(wk)) {
        return;
    }
    if (check_nm_attack(wk)) {
        return;
    }
}



void nm_17000(PLW* wk) {
    set_new_jpdir(wk);
    if (wk->wu.cg_type == 0xFF) {
        check_jump_rl_dir(wk);
        switch (wk->jpdir) {
        case LVDIR_FORWARD:
            wk->wu.routine_no[2] = 24;
            break;
        case LVDIR_BACK:
            wk->wu.routine_no[2] = 26;
            break;
        default:
            wk->wu.routine_no[2] = 25;
            break;
        }
        wk->wu.routine_no[3] = RN3_START;
        return;
    }
    if (check_super_arts_attack(wk)) {
        return;
    }
    if (check_special_attack(wk)) {
        return;
    }
    check_catch_attack(wk);
}



void check_jump_rl_dir(PLW* wk) {
    if (check_rl_flag(&wk->wu) == 0) {
        wk->wu.rl_flag = wk->wu.rl_waza;
        wk->cp->lever_dir = lvdir_conv[wk->cp->lever_dir];
        wk->jpdir = lvdir_conv[wk->jpdir];
    }
}



void set_new_jpdir(PLW* wk) {
    if (wk->cp->sw_lvbt & LEVER_UP) {
        if (wk->cp->lever_dir) {
            wk->jpdir = wk->cp->lever_dir;
        }
    }
}



void nm_18000(PLW* wk) {
    if (wk->wu.routine_no[3] < 2) {
        if (check_super_arts_attack(wk)) {
            return;
        }
        if (check_special_attack(wk)) {
            return;
        }
        if (check_catch_attack(wk)) {
            return;
        }
        if (check_nm_attack(wk)) {
            return;
        }
        if (check_cg_cancel_data(wk)) {
            return;
        }
    }
    jumping_cg_type_check(wk);
}



void jumping_cg_type_check(PLW* wk) {
    if (wk->wu.pat_status < 32) {
        switch (wk->wu.cg_type) {
        case 0xFF:
            wk->guard_flag = 0;
            TO_nm_01000((WORK*)wk);
            break;
        case 2:
            wk->guard_flag = 0;
            if (check_super_arts_attack(wk)) {
                return;
            }
            if (check_special_attack(wk)) {
                return;
            }
            if (check_catch_attack(wk)) {
                return;
            }
            if (check_leap_attack(wk)) {
                return;
            }
            if (check_nm_attack(wk)) {
                return;
            }
            if (check_cg_cancel_data(wk)) {
                return;
            }
            if (check_360_jump(wk)) {
                return;
            }
            if (check_jump_ready(wk)) {
                return;
            }
            break;
        case 7:
            wk->guard_flag = 0;
            if (check_super_arts_attack(wk)) {
                return;
            }
            if (check_special_attack(wk)) {
                return;
            }
            if (check_catch_attack(wk)) {
                return;
            }
            if (check_leap_attack(wk)) {
                return;
            }
            if (check_nm_attack(wk)) {
                return;
            }
            if (check_cg_cancel_data(wk)) {
                return;
            }
            break;
        case 3:
            wk->guard_flag = 0;
            if (check_super_arts_attack(wk)) {
                return;
            }
            if (check_special_attack(wk)) {
                return;
            }
            if (check_catch_attack(wk)) {
                return;
            }
            if (check_leap_attack(wk)) {
                return;
            }
            if (check_nm_attack(wk)) {
                return;
            }
            if (check_cg_cancel_data(wk)) {
                return;
            }
            if (check_turn_to_back(wk)) {
                return;
            }
            if (check_F_R_dash(wk)) {
                return;
            }
            if (check_360_jump(wk)) {
                return;
            }
            if (check_jump_ready(wk)) {
                return;
            }
            if (check_bend_myself(wk)) {
                return;
            }
            check_F_R_walk(wk);
            break;
        case 64:
            wk->guard_flag = 0;
            if (wk->wu.pat_status < 14) {
                TO_nm_36000((WORK*)wk);
                break;
            }
            TO_nm_38000((WORK*)wk);
            break;
        }
    } else {
        switch (wk->wu.cg_type) {
        case 0xFF:
            wk->guard_flag = 0;
            TO_nm_09000((WORK*)wk);
            break;
        case 2:
            wk->guard_flag = 0;
            if (check_super_arts_attack(wk)) {
                return;
            }
            if (check_special_attack(wk)) {
                return;
            }
            if (check_catch_attack(wk)) {
                return;
            }
            if (check_leap_attack(wk)) {
                return;
            }
            if (check_nm_attack(wk)) {
                return;
            }
            if (check_cg_cancel_data(wk)) {
                return;
            }
            if (check_360_jump(wk)) {
                return;
            }
            if (check_jump_ready(wk)) {
                return;
            }
            break;
        case 7:
            wk->guard_flag = 0;
            if (check_super_arts_attack(wk)) {
                return;
            }
            if (check_special_attack(wk)) {
                return;
            }
            if (check_catch_attack(wk)) {
                return;
            }
            if (check_leap_attack(wk)) {
                return;
            }
            if (check_nm_attack(wk)) {
                return;
            }
            if (check_cg_cancel_data(wk)) {
                return;
            }
            break;
        case 3:
            wk->guard_flag = 0;
            if (check_super_arts_attack(wk)) {
                return;
            }
            if (check_special_attack(wk)) {
                return;
            }
            if (check_catch_attack(wk)) {
                return;
            }
            if (check_leap_attack(wk)) {
                return;
            }
            if (check_nm_attack(wk)) {
                return;
            }
            if (check_cg_cancel_data(wk)) {
                return;
            }
            if (check_turn_to_back(wk)) {
                return;
            }
            if (check_F_R_dash(wk)) {
                return;
            }
            if (check_360_jump(wk)) {
                return;
            }
            if (check_jump_ready(wk)) {
                return;
            }
            if (check_stand_up(wk)) {
                return;
            }
            if (check_F_R_step(wk)) {
                return;
            }
            break;
        case 64:
            wk->guard_flag = 0;
            TO_nm_37000((WORK*)wk);
            break;
        }
    }
}



void jumping_guard_type_check(PLW* wk) {
    switch (wk->wu.cg_type) {
    case 0xFF:
    case 64:
    case 2:
    case 3:
    case 7:
        wk->guard_flag = 0;
    }
}



void nm_27000(PLW* wk) {
    if (wk->wu.cg_type == 0xFF) {
        TO_nm_01000((WORK*)wk);
        return;
    }
    if (check_super_arts_attack(wk)) {
        return;
    }
    if (check_special_attack(wk)) {
        return;
    }
    if (check_catch_attack(wk)) {
        return;
    }
    if (check_leap_attack(wk)) {
        return;
    }
    if (check_nm_attack(wk)) {
        return;
    }
    if (check_cg_cancel_data(wk)) {
        return;
    }
    if (check_turn_to_back(wk)) {
        return;
    }
    if (check_F_R_dash(wk)) {
        return;
    }
    if (check_360_jump(wk)) {
        return;
    }
    if (check_jump_ready(wk)) {
        return;
    }
    if (wk->cp->lever_dir != LVDIR_BACK) {
        if (check_bend_myself(wk)) {
            return;
        }
        if (check_F_R_walk(wk)) {
            return;
        }
    }
    nm_27_cg_type_check(wk);
}



void nm_27_cg_type_check(PLW* wk) {
    s16 kind;
    if (wk->wu.routine_no[3] == RN3_START) {
        return;
    }
    switch (wk->wu.cg_type) {
    case 1:
        if (check_em_catt(wk) == 0) {
            return;
        }
        if ((kind = check_defense_kind(wk)) != 0) {
            wk->wu.cg_ix = defense_cg_ix_table[wk->player_number][kind - 1] * wk->wu.cgd_type - wk->wu.cgd_type;
        } else {
            wk->wu.cg_ix -= wk->wu.cgd_type * 2;
        }
        char_move_z(&wk->wu);
        return;
    case 64:
        if (wk->wu.routine_no[2] == 29) {
            wk->wu.routine_no[2] = 37;
        } else {
            wk->wu.routine_no[2] = 36;
        }
        wk->wu.routine_no[3] = RN3_START;
        wk->wu.cg_type = 0;
        return;
    case 32:
        break;
    case 0:
        check_defense_kind(wk);
        break;
    }
}



void nm_29000(PLW* wk) {
    if (wk->wu.cg_type == 0xFF) {
        TO_nm_09000((WORK*)wk);
        return;
    }
    if (check_super_arts_attack(wk)) {
        return;
    }
    if (check_special_attack(wk)) {
        return;
    }
    if (check_catch_attack(wk)) {
        return;
    }
    if (check_leap_attack(wk)) {
        return;
    }
    if (check_nm_attack(wk)) {
        return;
    }
    if (check_cg_cancel_data(wk)) {
        return;
    }
    if (check_turn_to_back(wk)) {
        return;
    }
    if (check_F_R_dash(wk)) {
        return;
    }
    if (check_360_jump(wk)) {
        return;
    }
    if (check_jump_ready(wk)) {
        return;
    }
    if (wk->cp->lever_dir != LVDIR_BACK) {
        if (check_stand_up(wk)) {
            return;
        }
        if (check_F_R_step(wk)) {
            return;
        }
    }
    nm_27_cg_type_check(wk);
}



void nm_31000(PLW* wk) {
    switch (wk->wu.cg_type) {
    case 1:
        if (check_super_arts_attack(wk)) {
            return;
        }
        if (check_special_attack(wk)) {
            return;
        }
        if (check_catch_attack(wk)) {
            return;
        }
        if (check_leap_attack(wk)) {
            return;
        }
        if (check_nm_attack(wk)) {
            return;
        }
        break;
    case 64:
        if (wk->wu.pat_status < 32) {
            TO_nm_36000((WORK*)wk);
            break;
        }
        TO_nm_37000((WORK*)wk);
        break;
    case 0xFF:
        if (wk->wu.pat_status < 32) {
            TO_nm_01000((WORK*)wk);
            break;
        }
        TO_nm_09000((WORK*)wk);
        break;
    }
}



void nm_34000(PLW* wk) {
    switch (wk->wu.cg_type) {
    case 64:
    case 0xFF:
        TO_nm_18000_01((WORK*)wk);
        break;
    default:
        if (wk->wu.routine_no[3] >= 2) {
            if (wk->wu.pat_status < 32) {
                TO_nm_36000((WORK*)wk);
            } else {
                TO_nm_37000((WORK*)wk);
            }
        }
    }
}



void nm_36000(PLW* wk) {
    if (wk->wu.cg_type == 0xFF) {
        if (wk->wu.now_koc == 0 && wk->wu.char_index == 0) {
            wk->wu.routine_no[2] = NORMAL_STAND;
            wk->wu.routine_no[3] = 1;
        } else {
            wk->wu.routine_no[2] = NORMAL_STAND;
            wk->wu.routine_no[3] = RN3_START;
        }
    } else if (wk->player_number == PL_ELENA && wk->wu.now_koc == 0 && wk->wu.char_index == 36) {
        exset_char_move_init(&wk->wu, 0, 0);
        wk->wu.routine_no[2] = NORMAL_STAND;
        wk->wu.routine_no[3] = 1;
    }
    nm_01000(wk);
}



void nm_37000(PLW* wk) {
    if (wk->wu.cg_type == 0xFF) {
        wk->wu.routine_no[2] = 9;
        wk->wu.routine_no[3] = RN3_START;
    }
    nm_09000(wk);
}



void nm_38000(PLW* wk) {
    if (wk->wu.routine_no[3] < 2) {
        if (check_super_arts_attack(wk)) {
            return;
        }
        if (check_special_attack(wk)) {
            return;
        }
        if (check_catch_attack(wk)) {
            return;
        }
        if (check_nm_attack(wk)) {
            return;
        }
        if (check_cg_cancel_data(wk)) {
            return;
        }
    }
    jumping_cg_type_check(wk);
}



void nm_39000(PLW* wk) {
    if (wk->wu.cg_type == 0xFF) {
        if (wk->wu.now_koc == 0 && wk->wu.char_index == 0) {
            wk->wu.routine_no[2] = NORMAL_STAND;
            wk->wu.routine_no[3] = 1;
        } else {
            wk->wu.routine_no[2] = NORMAL_STAND;
            wk->wu.routine_no[3] = RN3_START;
        }
    }
    nm_01000(wk);
}



void nm_40000(PLW* wk) {
    if (wk->wu.routine_no[3] && wk->wu.cg_type == 0xFF) {
        wk->wu.routine_no[3] = RN3_DONE;
    }
}



void process_damage(PLW* wk) {
    if (wk->wu.routine_no[3] != RN3_START) {
        plpdm_xxxxx[wk->wu.routine_no[2]](wk);
    }
}



void dm_00000(PLW* wk) {
    if (wk->wu.routine_no[2] != 0) {
        return;
    }
    if (wk->wu.routine_no[3] != 2) {
        return;
    }
    if (check_sa_type_rebirth(wk) != 0) {
        wk->py->flag = 0;
        execute_super_arts(wk);
    } else {
        wk->wu.routine_no[3]++;
    }
}



void dm_04000(PLW* wk) {
    switch (wk->wu.cg_type) {
    case 9:
        if (wk->py->flag == 0) {
        }
        break;
    case 64:
        if (wk->py->flag == 0) {
            wk->tsukamarenai_flag = 8;
            if (wk->wu.pat_status < 32) {
                TO_nm_36000((WORK*)wk);
            } else {
                TO_nm_37000((WORK*)wk);
            }
        } else {
            wk->wu.routine_no[2] = 19;
            wk->wu.routine_no[3] = RN3_START;
        }
        break;
    case 0xFF:
        if (wk->py->flag == 0) {
            wk->tsukamarenai_flag = 8;
            if (wk->wu.pat_status < 32) {
                TO_nm_01000((WORK*)wk);
            } else {
                TO_nm_09000((WORK*)wk);
            }
        } else {
            wk->wu.routine_no[2] = 19;
            wk->wu.routine_no[3] = RN3_START;
        }
        break;
    }
}



void dm_08000(PLW* wk) {
    switch (wk->wu.cg_type) {
    case 0xFF:
        wk->tsukamarenai_flag = 8;
        TO_nm_01000(&wk->wu);
        break;
    case 64:
        wk->tsukamarenai_flag = 8;
        TO_nm_36000(&wk->wu);
        break;
    default:
        if (wk->wu.routine_no[3] < 3 && check_dm_shot_attack(wk)) {
            wk->tsukamarenai_flag = 8;
        }
        break;
    }
}



void dm_17000(PLW* wk) {
    jumping_cg_type_check(wk);
}



void dm_18000(PLW* wk) {
    switch (wk->wu.cg_type) {
    case 0xFF:
        if (wk->wu.vital_new < 0 && (check_sa_type_rebirth(wk) != 0)) {
            wk->py->flag = 0;
            execute_super_arts(wk);
            break;
        }
        if (wk->dead_flag) {
            wk->wu.routine_no[2] = 16;
        } else {
            wk->wu.routine_no[2] = 1;
        }
        wk->wu.routine_no[3] = RN3_START;
        wk->wu.cg_type = 0;
        break;
    case 64:
        if (wk->py->flag == 0) {
            wk->tsukamarenai_flag = 8;
            TO_nm_36000(&wk->wu);
            break;
        }
        wk->wu.routine_no[2] = 19;
        wk->wu.routine_no[3] = RN3_START;
        break;
    }
}



void dm_25000(PLW* wk) {
    wk->py->time--;
    if (wk->py->time <= 0) {
        wk->tsukamarenai_flag = 8;
        TO_nm_01000(&wk->wu);
    }
}



void process_catch(PLW* wk) {
    if (wk->wu.routine_no[3] == RN3_START) {
        return;
    }
    switch (wk->wu.cg_type) {
    case 64:
        if (wk->wu.pat_status < 32) {
            TO_nm_36000((WORK*)wk);
            break;
        }
        TO_nm_37000((WORK*)wk);
        break;
    case 0xFF:
        if (wk->wu.pat_status < 32) {
            TO_nm_01000((WORK*)wk);
            break;
        }
        TO_nm_09000((WORK*)wk);
        break;
    }
}



void nm_91000(PLW* wk) {
    switch (wk->wu.cg_type) {
    case 64:
        if (wk->wu.pat_status < 32) {
            TO_nm_36000((WORK*)wk);
        } else {
            TO_nm_37000((WORK*)wk);
        }
        break;
    case 0xFF:
        if (wk->wu.pat_status < 32) {
            TO_nm_01000((WORK*)wk);
        } else {
            TO_nm_09000((WORK*)wk);
        }
        break;
    default:
        return;
    }
}



void process_caught(PLW* wk) {}



void nm_95000(PLW* wk) {}



void process_attack(PLW* wk) {
    if (wk->wu.routine_no[3]) {
        if (wk->cancel_timer && wk->wu.hit_stop == 0) {
            wk->cancel_timer--;
        }
        if (wk->cancel_timer) {
            if (check_super_arts_attack(wk)) {
                return;
            }
            if (check_special_attack(wk)) {
                return;
            }
            if (check_catch_attack(wk)) {
                return;
            }
        }
    }
    if (!check_cg_cancel_data(wk)) {
        jumping_cg_type_check(wk);
    }
}



s32 check_cg_cancel_data(PLW* wk) {
    if (wk->wu.cg_cancel == 0) {
        return 0;
    }
    if (wk->wu.meoshi_hit_flag != 0) {
        if (wk->wu.cg_cancel & 0x40) {
            if (check_super_arts_attack(wk)) {
                wk->wu.cg_cancel = 0;
                return 1;
            }
        }
        if (wk->wu.cg_cancel & 0x20) {
            if (check_special_attack(wk) != 0) {
                return 1;
            }
        }
    }
    if ((wk->wu.cg_cancel & 0x10) && (check_renda_cancel(wk) != 0)) {
        return 1;
    }
    if ((wk->wu.cg_cancel & 8) && (check_meoshi_cancel(wk) != 0)) {
        return 1;
    }
    if ((wk->wu.cg_cancel & 4) && ((wk->cp->sw_now & CMD_SW_SHOT) != ((wk->current_attack))) && (check_nm_attack(wk) != 0)) {
        return 1;
    }
    if ((wk->wu.cg_cancel & 2) && (check_F_R_dash(wk))) {
        return 1;
    }
    if ((wk->wu.cg_cancel & 1) && (check_hijump_only(wk) != 0)) {
        return 1;
    }
    return 0;
}
