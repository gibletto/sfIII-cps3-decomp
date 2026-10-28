/*
 * PLS01.C  Player movement and state check subroutines
 *
 * Subroutines used by the player state checks. They test and start jumps (air, triangle and
 * 360 jumps, high jumps), forward/back dashes, walks and steps, turning round (check_turn_to_back),
 * standing up, and guard (check_defense_lever, check_defense_kind, check_attbox_dir).
 * jumping_union_process and jumping_process_ix move a work through the air under its speeds
 * and animation and land it.
 * Also the recovery-roll check.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CALDIR.h"
#include "PLS02.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "HITCHECK.h"
#include "PLS01.h"
#include "cmd_data.h"



/* provisional name */
s32 check_ukemi_flag(PLW* wk) {
    return wk->cp->waza_flag[7];
}



s32 check_rl_flag(WORK* wk) {
    return wk->rl_flag == wk->rl_waza;
}



void set_rl_waza(PLW* wk) {
    s16 d;
    WORK_Other* p;
    p = (WORK_Other*)wk->wu.target_adrs;
    d = wk->wu.xyz[0].disp.pos - p->wu.xyz[0].disp.pos;
    if (d) {
        if (d > 0) {
            wk->wu.rl_waza = 0;
        } else {
            wk->wu.rl_waza = 1;
        }
    } else {
        wk->wu.rl_waza = (p->wu.rl_waza + 1) & 1;
    }
}



s32 check_F_R_dash(PLW* wk) {
    s16 num;
    s16 rnum;
    if (wk->wu.xyz[1].disp.pos > 0) {
        return 0;
    }
    num = (wk->cp->waza_flag[0] != 0) + (wk->cp->waza_flag[1] != 0) * 2;
    rnum = 0;
loop:
    switch (num) {
    case 1:
        if (wk->spmv_ng_flag & 4) {
            break;
        }
        wk->wu.routine_no[1] = PLAYER_NORMAL;
        wk->wu.routine_no[2] = 5;
        wk->wu.routine_no[3] = RN3_START;
        rnum = 1;
        break;
    case 2:
        if (wk->spmv_ng_flag & 8) {
            break;
        }
        wk->wu.routine_no[1] = PLAYER_NORMAL;
        wk->wu.routine_no[2] = 6;
        wk->wu.routine_no[3] = RN3_START;
        rnum = 1;
        break;
    case 3:
        if (wk->cp->lever_dir < LVDIR_BACK) {
            num = 1;
        } else {
            num = 2;
        }
        goto loop;
    }
    return rnum;
}



/* provisional name */
s32 check_360_jump(PLW* wk) {
    if (wk->spmv_ng_flag & 0x10000) {
        return 0;
    }
    if (wk->cp->waza_flag[13] == 0) {
        return 0;
    }
    wk->wu.routine_no[1] = PLAYER_NORMAL;
    wk->wu.routine_no[2] = 19;
    wk->wu.routine_no[3] = RN3_START;
    wk->jpdir = LVDIR_NEUTRAL;
    return 1;
}



s32 check_jump_ready(PLW* wk) {
    if (!(wk->cp->sw_new & CMD_LV_UP)) {
        return 0;
    }
    if (wk->cp->waza_flag[2] == 0) {
        wk->wu.routine_no[2] = 16;
    } else {
        wk->wu.routine_no[2] = 17;
    }
    wk->wu.routine_no[1] = PLAYER_NORMAL;
    wk->wu.routine_no[3] = RN3_START;
    wk->jpdir = LVDIR_NEUTRAL;
    return 1;
}



s32 check_hijump_only(PLW* wk) {
    if (wk->spmv_ng_flag & 0x20000) {
        return 0;
    }
    if (!(wk->cp->sw_new & CMD_LV_UP)) {
        return 0;
    }
    if (wk->cp->waza_flag[2] == 0) {
        return 0;
    }
    if (wk->wu.xyz[1].disp.pos > 0) {
        return 0;
    }
    wk->wu.routine_no[1] = PLAYER_NORMAL;
    wk->wu.routine_no[2] = 17;
    wk->wu.routine_no[3] = RN3_START;
    wk->jpdir = LVDIR_NEUTRAL;
    return 1;
}



s32 check_bend_myself(PLW* wk) {
    if (!(wk->cp->sw_new & CMD_LV_DOWN)) {
        return 0;
    }
    wk->wu.routine_no[1] = PLAYER_NORMAL;
    wk->wu.routine_no[2] = 8;
    wk->wu.routine_no[3] = RN3_START;
    return 1;
}



s32 check_F_R_walk(PLW* wk) {
    s16 r = 0;
    switch (wk->cp->lever_dir) {
    case LVDIR_FORWARD:
        wk->wu.routine_no[1] = PLAYER_NORMAL;
        wk->wu.routine_no[2] = 3;
        wk->wu.routine_no[3] = RN3_START;
        r = 1;
        break;
    case LVDIR_BACK:
        wk->wu.routine_no[1] = PLAYER_NORMAL;
        wk->wu.routine_no[2] = 4;
        r = 1;
        wk->wu.routine_no[3] = RN3_START;
        break;
    }
    return r;
}



/* provisional name */
s32 check_F_R_step(PLW* wk) {
    s16 rnum = 0;
    switch (wk->cp->lever_dir) {
    case LVDIR_FORWARD:
        if (!(wk->spmv_ng_flag & 1)) {
            wk->wu.routine_no[1] = PLAYER_NORMAL;
            wk->wu.routine_no[2] = 11;
            wk->wu.routine_no[3] = RN3_START;
            rnum = 1;
        }
        break;
    case LVDIR_BACK:
        if (!(wk->spmv_ng_flag & 2)) {
            wk->wu.routine_no[1] = PLAYER_NORMAL;
            wk->wu.routine_no[2] = 12;
            wk->wu.routine_no[3] = RN3_START;
            rnum = 1;
        }
        break;
    }
    return rnum;
}



/* provisional name: the work already faces the way its move wants */
static s32 facing_matches_waza(WORK* wk) {
    return wk->rl_flag == wk->rl_waza;
}



s32 check_turn_to_back(PLW* wk) {
    if (facing_matches_waza(&wk->wu)) {
        return 0;
    }
    if (wk->cp->sw_lvbt & LEVER_DOWN) {
        wk->wu.routine_no[2] = 10;
    } else {
        wk->wu.routine_no[2] = 2;
    }
    wk->wu.routine_no[1] = PLAYER_NORMAL;
    wk->wu.routine_no[3] = RN3_START;
    wk->wu.cg_type = 0;
    return 1;
}



s32 check_walking_lv_dir(PLW* wk) {
    s16 rnum = 0;
    switch (wk->cp->lever_dir) {
    case LVDIR_FORWARD:
        if (wk->wu.routine_no[2] != 3) {
            rnum = 1;
        }
        break;
    case LVDIR_BACK:
        if (wk->wu.routine_no[2] != 4) {
            rnum = 1;
        }
        break;
    default:
        rnum = 1;
        break;
    }
    if (rnum) {
        if (wk->wu.pat_status < 32) {
            wk->wu.routine_no[2] = 1;
        } else {
            wk->wu.routine_no[2] = 9;
        }
        wk->wu.routine_no[1] = PLAYER_NORMAL;
        wk->wu.routine_no[3] = RN3_START;
    }
    return rnum;
}



/* provisional name: check_walking_lv_dir for the other walk states (11/12) */
s32 check_walking_lv_dir2(PLW* wk) {
    s16 rnum = 0;
    switch (wk->cp->lever_dir) {
    case LVDIR_FORWARD:
        if (wk->wu.routine_no[2] != 11) {
            rnum = 1;
        }
        break;
    case LVDIR_BACK:
        if (wk->wu.routine_no[2] != 12) {
            rnum = 1;
        }
        break;
    default:
        rnum = 1;
        break;
    }
    if (rnum) {
        if (wk->wu.pat_status < 32) {
            wk->wu.routine_no[2] = 1;
        } else {
            wk->wu.routine_no[2] = 9;
        }
        wk->wu.routine_no[1] = PLAYER_NORMAL;
        wk->wu.routine_no[3] = RN3_START;
    }
    return rnum;
}



s32 check_stand_up(PLW* wk) {
    if (wk->cp->sw_new & CMD_LV_DOWN) {
        return 0;
    }
    wk->wu.routine_no[1] = PLAYER_NORMAL;
    wk->wu.routine_no[2] = 7;
    wk->wu.routine_no[3] = RN3_START;
    return 1;
}



s32 check_defense_lever(PLW* wk) {
    if (!check_em_catt(wk)) {
        return 0;
    }
    if (wk->cp->sw_new & CMD_LV_DOWN) {
        wk->wu.routine_no[2] = 29;
    } else if (check_attbox_dir(wk)) {
        wk->wu.routine_no[2] = 28;
    } else {
        wk->wu.routine_no[2] = 27;
    }
    wk->wu.routine_no[1] = PLAYER_NORMAL;
    wk->wu.routine_no[3] = RN3_START;
    return 1;
}



s32 check_em_catt(PLW* wk) {
    PLW* em = (PLW*)wk->wu.target_adrs;
    s16 xd;
    s8 rlf;
    if (em->caution_flag == 0) {
        return 0;
    }
    if ((rlf = (wk->wu.rl_flag + em->wu.rl_flag) & 1) == 0) {
        return 0;
    }
    if (wk->cp->lever_dir != LVDIR_BACK || wk->cp->sw_new & CMD_LV_UP) {
        return 0;
    }
    xd = wk->wu.xyz[0].disp.pos - em->wu.xyz[0].disp.pos;
    if (xd < 0) {
        xd = -xd;
    }
    if (xd > 128) {
        return 0;
    }
    return 1;
}



s32 check_attbox_dir(PLW* wk) {
    s16 target_pos_x;
    s16 target_pos_y;
    s16 emdir;
    s16* dttbl;
    get_target_att_position((WORK*)wk->wu.target_adrs, &target_pos_x, &target_pos_y);
    dttbl = sel_hd_fg_hos[wk->player_number];
    if (wk->wu.rl_flag) {
        emdir = caldir_pos_032(
            wk->wu.xyz[0].disp.pos - dttbl[0], wk->wu.xyz[1].disp.pos + dttbl[1], target_pos_x, target_pos_y);
    } else {
        emdir = caldir_pos_032(
            wk->wu.xyz[0].disp.pos + dttbl[0], wk->wu.xyz[1].disp.pos + dttbl[1], target_pos_x, target_pos_y);
        emdir = dir32_rl_conv[emdir];
    }
    emdir = (emdir + dttbl[2]) & 0x1F;
    return emdir > dttbl[2] + dttbl[3];
}



s32 check_defense_kind(PLW* wk) {
    u16 rnum = 0;
    switch (wk->wu.routine_no[2]) {
    case 27:
        if (wk->cp->sw_new & CMD_LV_DOWN) {
            rnum = 3;
        } else if (check_attbox_dir(wk)) {
            rnum = 2;
        }
        break;
    case 28:
        if (wk->cp->sw_new & CMD_LV_DOWN) {
            rnum = 3;
        } else if (check_attbox_dir(wk) == 0) {
            rnum = 1;
        }
        break;
    case 29:
        if (!(wk->cp->sw_new & CMD_LV_DOWN)) {
            if (check_attbox_dir(wk)) {
                rnum = 2;
            } else {
                rnum = 1;
            }
        }
        break;
    }
    if (rnum) {
        wk->wu.routine_no[2] = rnum + 26;
        exset_char_move_init(&wk->wu, 0, rnum + 28);
    }
    return rnum;
}



void jumping_union_process(wk, num)
WORK* wk;
s16 num;
{
    add_mvxy_speed(wk);
    cal_mvxy_speed(wk);
    if ((wk->xyz[1].disp.pos + wk->cg_jphos) <= 0) {
        wk->xyz[1].cal = 0;
        wk->mvxy.a[1].sp = 0;
        wk->routine_no[3] = num;
        char_move_cmja(wk);
    } else {
        char_move(wk);
    }
}



/* provisional name */
void jumping_process_ix(WORK* wk, s16 ix, s16 num) {
    cal_mvxy_speed(wk);
    add_mvxy_speed(wk);
    if ((wk->xyz[1].disp.pos + wk->cg_jphos) <= 0) {
        wk->xyz[1].cal = 0;
        wk->routine_no[ix] = num;
        char_move_cmja(wk);
    } else {
        char_move(wk);
    }
}

