/*
 * CMB_CONT.C  Combo, reversal and parry bonus control and scoring
 *
 * Watches both players during a round and awards bonus messages and points.
 * combo_cont_main runs each frame (reset by Stop_Combo); combo_control checks for the end
 * of a combo (check_combo_end), reversals (reversal_check), parries (paring_check),
 * first attacks and super art finishes (super_arts_finish_check, arts_finish_check).
 * SCORE_CALCULATION totals the hits by attack kind against the points table and SCORE_PLUS
 * adds points to the round, game (capped at 9999900) or versus score.
 * combo_window_push queues a message for a player's combo window and combo_window_trans
 * draws queued messages with the CMB_WIN routines; grade_* calls feed the grading system.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLCNTDAT.h"
#include "plcntdat_2.h"
#include "cmb_win.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "win_2.h"
#include "continue.h"
#include "pow_pow.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "cmb_cont.h"

/* combo_score_tbl[slot] columns */
#define COMBO_SCORE_BASE 0      /* score for a slot that hit */
#define COMBO_SCORE_HIT 1       /* times the combo hits so far */


s16 old_cmb_flag[2];  /* 0201DCB0 */
s8 cmb_stock[2];  /* 0201DCB4 */
s8 first_attack;  /* 0201DCB6 */
s8 rever_attack[2];  /* 0201DCB7 */
s8 paring_attack[2];  /* 0201DCB9 */
s8 bonus_pts[2];  /* 0201DCBB */
s16 hit_num;  /* 0201DCBE */
u8 sa_kind;  /* 0201DCC0 */
u8 end_flag[2];  /* 0201DCC1 */
s16 calc_hit[2][10];  /* 0201DCC4 */
s16 score_calc[2][11];  /* 0201DCEC */
s8 cmb_all_stock;  /* 0201DD18 */
s8 sarts_finish_flag[2];  /* 0201DD19 */
s8 last_hit_time;  /* 0201DD1B */
u8 cst_read[2];  /* 0201DD1C */
u8 cst_write[2];  /* 0201DD1E */
CMST_WIN cmst_buff[2][4];  /* 0201DD20 */


/* reads a row of the points table and drops the value */
#define SCORE_ROW_READ(row) ((void)&((WORK*)combo_score_tbl[row])->be_flag)


void combo_cont_init(void) {
    old_cmb_flag[0] = 0;
    old_cmb_flag[1] = 0;
    cmb_stock[0] = 0;
    cmb_stock[1] = 0;
    first_attack = 0;
    rever_attack[0] = 0;
    rever_attack[1] = 0;
    paring_attack[0] = 0;
    paring_attack[1] = 0;
    bonus_pts[0] = 0;
    bonus_pts[1] = 0;
    hit_num = 0;
    sa_kind = 0;
    cmb_all_stock = 0;
    sarts_finish_flag[0] = 0;
    sarts_finish_flag[1] = 0;
    last_hit_time = 0;
    cst_read[0] = 0;
    cst_read[1] = 0;
    cst_write[0] = 0;
    cst_write[1] = 0;
    work_init_zero((s32*)&combo_type[0], sizeof(ComboType));
    work_init_zero((s32*)&combo_type[1], sizeof(ComboType));
    work_init_zero((s32*)&remake_power[0], sizeof(ComboType));
    work_init_zero((s32*)&remake_power[1], sizeof(ComboType));
    memset(cmst_buff[0], 0, 64);
    memset(cmst_buff[1], 0, 64);
    memset(calc_hit[0], 0, sizeof(calc_hit[0]));
    memset(calc_hit[1], 0, sizeof(calc_hit[0]));
    memset(score_calc[0], 0, sizeof(score_calc[0]));
    memset(score_calc[1], 0, sizeof(score_calc[0]));
}


void combo_cont_main(void) {
    if (Stop_Combo) {
        combo_window_all_clear();
        combo_cont_init();
        Stop_Combo = 0;
        return;
    }
    if (Game_pause) {
        combo_window_trans(0);
        combo_window_trans(1);
        return;
    }
    if (Game_timer & 1) {
        combo_control(0);
        combo_window_trans(0);
        combo_control(1);
        combo_window_trans(1);
    } else {
        combo_control(1);
        combo_window_trans(1);
        combo_control(0);
        combo_window_trans(0);
    }
    cmb_all_stock = cmb_stock[0] + cmb_stock[1];
}


void combo_control(s8 PL) {
    s16 cmb_flag;
    cmb_flag = check_combo_end(PL);
    if (reversal_check(PL) != 0) {
        return;
    }
    if (rever_attack[PL]) {
        reversal_continue_check(PL);
    }
    if (paring_check(PL) != 0) {
        return;
    }
    if (plw[PL].cb->total) {
        if (first_attack == 0) {
            first_attack = plw[PL].wu.id + 1;
            combo_window_push(PL, 4);
            return;
        }
    } else {
        return;
    }
    if (pcon_dp_flag == 1 && last_hit_time == 0) {
        super_arts_last_check(PL);
    }
    if (cmb_flag != 0) {
        return;
    }
    if (plw[PL].cb->total == 1) {
        super_arts_finish_check(PL);
        combo_hensuu_clear(PL);
        first_attack = 3;
        return;
    }
    check_and_set_combo(PL);
}

void check_and_set_combo(PL)
s8 PL;
{
    s8 PLS;
    if (PL == 0) {
        PLS = 1;
    } else {
        PLS = 0;
    }
    hit_num = plw[PL].cb->total;
    if (hit_num > 99) {
        hit_num = 99;
    }
    if (first_attack == 1 || first_attack == 2) {
        first_attack_pts_check(PL);
    }
    if (rever_attack[PLS] == 1) {
        s8 index = PL;
        bonus_pts[index]++;
    }
    hit_combo_check(PL);
    combo_hensuu_clear(PL);
}


void combo_hensuu_clear(PL)
s8 PL;
{
    work_init_zero((s32*)plw[PL].cb, sizeof(ComboType));
    work_init_zero((s32*)plw[PL].rp, sizeof(ComboType));
    memset(calc_hit[PL], 0, sizeof(calc_hit[0]));
    memset(score_calc[PL], 0, sizeof(score_calc[0]));
    bonus_pts[PL] = 0;
    plw[PL].cb->total = 0;
    hit_num = 0;
}


void super_arts_finish_check(PL)
s8 PL;
{
    if (arts_finish_check2(PL)) {
        if ((plw[PL].cb->new_dm & 0x3F) <= 0x2F) {
            sa_kind = 2;
        } else {
            sa_kind = 3;
        }
        combo_window_push(PL, 3);
    }
}


void super_arts_last_check(PL)
s8 PL;
{
    if ((plw[PL].cb->new_dm & 0x3F) >= 0x20) {
        sarts_finish_flag[PL] = 1;
    } else {
        sarts_finish_flag[PL] = 0;
    }
    last_hit_time = 1;
}


void first_attack_pts_check(PL)
s8 PL;
{
    if (plw[PL].wu.id == first_attack - 1) {
        first_attack = 3;
        bonus_pts[PL] += 2;
    }
}


s32 reversal_check(PL)
s8 PL;
{
    s8 PLS;
    if (rever_attack[PL]) {
        return 0;
    }
    if (plw[PL].wu.routine_no[1] == PLAYER_ATTACK && plw[PL].wu.old_rno[1] == 1 && pcon_dp_flag == 0) {
        if (plw[PL].wu.routine_no[2] >= 0x10) {
            rever_attack[PL] = 1;
            if (PL == 0) {
                PLS = 1;
            } else {
                PLS = 0;
            }
            combo_window_push(PLS, 5);
            return 1;
        }
    }
    return 0;
}


void reversal_continue_check(PL)
s8 PL;
{
    if (plw[PL].wu.routine_no[1] != PLAYER_ATTACK) {
        rever_attack[PL] = 0;
    } else {
        return;
    }
}


void reversal_attack_pts_check(s8 id) {
    bonus_pts[id]++;
}


s32 paring_check(PL)
s8 PL;
{
    s8 PLS;
    if (paring_bonus_r[PL]) {
        paring_bonus_r[PL] = 0;
        paring_attack[PL] = 1;
        if (PL == 0) {
            PLS = 1;
        } else {
            PLS = 0;
        }
        combo_window_push(PLS, 6);
        return 1;
    }
    return 0;
}


void hit_combo_check(PL)
s8 PL;
{
    s32* sa_ptr = (s32*)plw[PL].cb->kind_of[4][0];
    s8 lpx;
    for (lpx = 0; lpx < 16; lpx++) {
        if (*sa_ptr++ != 0) {
            if (arts_finish_check(PL)) {
                if (lpx <= 7) {
                    bonus_pts[PL] += 2;
                    sa_kind = 2;
                } else {
                    bonus_pts[PL] += 3;
                    sa_kind = 3;
                }
                combo_window_push(PL, 2);
                return;
            } else {
                combo_window_push(PL, 1);
                return;
            }
        }
    }
    combo_window_push(PL, 0);
}


s32 arts_finish_check(PL)
s8 PL;
{
    if (Conclusion_Flag && Conclusion_Type == CONCLUSION_KO && Loser_id == PL) {
        if (sarts_finish_flag[PL]) {
            return 1;
        }
    }
    return 0;
}


s32 arts_finish_check2(PL)
s8 PL;
{
    if (Conclusion_Flag) {
        if (Conclusion_Type == CONCLUSION_KO) {
            if (Loser_id == PL && (plw[PL].cb->new_dm & 0x3F) >= 32) {
                return 1;
            }
        }
    }
    return 0;
}


u32 SCORE_CALCULATION(PL)
s8 PL;
{
    s16* c_ptr;
    s16* s_ptr;
    s16* k_ptr;
    s8 lpx;
    s8 lpy;
    s16 hit;
    s16 h;
    u32 score;
    s8 last;
    k_ptr = plw[PL].cb->kind_of[0][0];
    c_ptr = &calc_hit[PL][1];
    s_ptr = score_calc[PL];
    for (lpx = 0; lpx < 4; lpx++) {
        *s_ptr++ = k_ptr[0] + k_ptr[1];
        k_ptr = k_ptr + 2;
    }
    s_ptr = &score_calc[PL][4];
    for (lpy = 0; lpy < 7; lpy++) {
        *s_ptr++ = *c_ptr++;
    }
    hit = 0;
    score = 0;
    for (lpy = 0, s_ptr = score_calc[PL]; lpy < 11; lpy++) {
        if (s_ptr[lpy]) {
            last = lpy;
            h = s_ptr[lpy];
            hit += h;
            score += *combo_score_tbl[lpy];
            SCORE_ROW_READ(last);
            if (h - 1) {
                score += (hit - 1) * combo_score_tbl[lpy][COMBO_SCORE_HIT];
            }
        }
    }
    if (bonus_pts[PL]) {
        score += bonus_pts[PL] * combo_score_tbl[last][COMBO_SCORE_HIT];
    }
    return score;
}


void SCORE_PLUS(pl, pts)
s8 pl;
u32 pts;
{
    Score[pl][SCORE_ROUND] += pts;
    if (Play_Type == PLAY_VS_CPU) {
        Score[pl][SCORE_CPU] += pts;
        if (Score[pl][SCORE_CPU] >= 9999900) {
            Score[pl][SCORE_CPU] = 9999900;
        }
    } else {
        Score[pl][SCORE_VS] += pts;
    }
}


void combo_window_push(PL, KIND)
s8 PL;
s8 KIND;
{
    u32 score;
    s8 PLS;
    if (KIND < 3) {
        score = SCORE_CALCULATION(PL);
    }
    if (PL == 0) {
        PLS = 1;
    } else {
        PLS = 0;
    }
    if (cmb_stock[PL] == 4) {
        switch (KIND) {
        case 2:
            if (sa_kind == 2) {
                score += 20000;
            } else {
                score += 30000;
            }
            break;
        case 3:
            if (sa_kind == 2) {
                score = 20000;
            } else {
                score = 30000;
            }
            break;
        case 4:
            score = 1500;
            break;
        case 6:
            score = paring_counter[PLS];
            score *= 100;
            break;
        default:
            break;
        }
        if (score >= 1000000) {
            score = 999900;
        }
        SCORE_PLUS(PLS, score);
        if (plw[PLS].wu.operator) {
            Disp_Player_Score(PLS);
        }
        return;
    } else {
        cmb_stock[PL]++;
        cmst_buff[PL][cst_write[PL]].routine_num = 0;
        cmst_buff[PL][cst_write[PL]].hit = hit_num;
        cmst_buff[PL][cst_write[PL]].kind = KIND;
        if (plw[PLS].wu.operator) {
            cmst_buff[PL][cst_write[PL]].pts_flag = 1;
        } else {
            cmst_buff[PL][cst_write[PL]].pts_flag = 0;
        }
        switch (KIND) {
        case 0:
        case 1:
            break;
        case 2:
            if (sa_kind == 2) {
                score += 20000;
            } else {
                score += 30000;
            }
            break;
        case 3:
            if (sa_kind == 2) {
                score = 20000;
            } else {
                score = 30000;
            }
            break;
        case 4:
            score = 1500;
            break;
        case 5:
            score = 0;
            cmst_buff[PL][cst_write[PL]].pts_flag = 0;
            break;
        case 6:
            score = paring_counter[PLS];
                score *= 100;
            break;
        }
        if (score >= 1000000) {
            score = 999900;
        }
        cmst_buff[PL][cst_write[PL]].pts = score;
        if (cst_write[PL] == 3) {
            cst_write[PL] = 0;
        } else {
            cst_write[PL]++;
        }
    }
}


void combo_window_trans(s8 PL) {
    s8 PLS;
    if (cmb_stock[PL] != 0) {
        if (cmst_buff[PL][cst_read[PL]].pts_flag) {
            switch (cmst_buff[PL][cst_read[PL]].routine_num) {
            case 0:
                end_flag[PL] = 0;
                combo_message_set(PL, cmst_buff[PL][cst_read[PL]].kind);
                switch (cmst_buff[PL][cst_read[PL]].kind) {
                case 0:
                case 1:
                case 2:
                    combo_hitnum_set(PL, cmst_buff[PL][cst_read[PL]].kind, cmst_buff[PL][cst_read[PL]].hit);
                    break;
                case 3:
                case 4:
                case 5:
                case 6:
                    break;
                }
                cmst_buff[PL][cst_read[PL]].move[0] = cmb_window_move_tbl[cmst_buff[PL][cst_read[PL]].kind];
                cmst_buff[PL][cst_read[PL]].x_posnum[0] = 0;
                cmst_buff[PL][cst_read[PL]].timer[0] = 8;
                cmst_buff[PL][cst_read[PL]].move[1] = combo_pts_set(PL, cmst_buff[PL][cst_read[PL]].pts);
                cmst_buff[PL][cst_read[PL]].x_posnum[1] = 0;
                cmst_buff[PL][cst_read[PL]].routine_num++;
                break;
            case 1:
                if (!(end_flag[PL] & 1)) {
                    if (cmst_buff[PL][cst_read[PL]].x_posnum[0] < cmst_buff[PL][cst_read[PL]].move[0]) {
                        combo_window_slide(PL,
                                                cmb_pos_tbl[Game_setting.Screen_Mode][PL][cmst_buff[PL][cst_read[PL]].x_posnum[0]],
                                                0,
                                                cmst_buff[PL][cst_read[PL]].x_posnum[0]);
                        cmst_buff[PL][cst_read[PL]].x_posnum[0]++;
                    } else {
                        end_flag[PL] |= 1;
                    }
                }
                if (!(end_flag[PL] & 2)) {
                    cmst_buff[PL][cst_read[PL]].timer[0]--;
                    if (cmst_buff[PL][cst_read[PL]].timer[0] < 0) {
                        if (cmst_buff[PL][cst_read[PL]].x_posnum[1] < cmst_buff[PL][cst_read[PL]].move[1] + 2) {
                            if (cmst_buff[PL][cst_read[PL]].x_posnum[1] < cmst_buff[PL][cst_read[PL]].move[1]) {
                                combo_window_slide(PL,
                                                        cmb_pos_tbl[Game_setting.Screen_Mode][PL][cmst_buff[PL][cst_read[PL]].x_posnum[1]],
                                                        1,
                                                        cmst_buff[PL][cst_read[PL]].x_posnum[1]);
                            } else {
                                combo_window_slide(PL,
                                                        cmb_pos_tbl[Game_setting.Screen_Mode][PL][cmst_buff[PL][cst_read[PL]].x_posnum[1]],
                                                        1,
                                                        cmst_buff[PL][cst_read[PL]].move[1] - 1);
                            }
                            cmst_buff[PL][cst_read[PL]].x_posnum[1]++;
                        } else {
                            end_flag[PL] |= 2;
                        }
                    }
                }
                if ((end_flag[PL] & 3) == 3) {
                    cmst_buff[PL][cst_read[PL]].routine_num++;
                    cmst_buff[PL][cst_read[PL]].timer[1] = cmb_window_time_tbl[cmst_buff[PL][cst_read[PL]].kind];
                    if (PL == 0) {
                        PLS = 1;
                    } else {
                        PLS = 0;
                    }
                    SCORE_PLUS(PLS, cmst_buff[PL][cst_read[PL]].pts);
                    if (plw[PLS].wu.operator) {
                        Disp_Player_Score(PLS);
                    }
                }
                break;
            case 2:
                cmst_buff[PL][cst_read[PL]].timer[1]--;
                if (cmst_buff[PL][cst_read[PL]].timer[1] == 0) {
                    combo_window_erase(PL, cmst_buff[PL][cst_read[PL]].kind, 0);
                    combo_window_erase(PL, 7, 1);
                    if (cst_read[PL] == 3) {
                        cst_read[PL] = 0;
                    } else {
                        cst_read[PL]++;
                    }
                    cmb_stock[PL]--;
                }
                break;
            }
        } else {
            switch (cmst_buff[PL][cst_read[PL]].routine_num) {
            case 0:
                combo_message_set(PL, cmst_buff[PL][cst_read[PL]].kind);
                switch (cmst_buff[PL][cst_read[PL]].kind) {
                case 0:
                case 1:
                case 2:
                    combo_hitnum_set(PL, cmst_buff[PL][cst_read[PL]].kind, cmst_buff[PL][cst_read[PL]].hit);
                    break;
                case 3:
                case 4:
                case 5:
                case 6:
                    break;
                }
                cmst_buff[PL][cst_read[PL]].move[0] = cmb_window_move_tbl[cmst_buff[PL][cst_read[PL]].kind];
                cmst_buff[PL][cst_read[PL]].x_posnum[0] = 0;
                cmst_buff[PL][cst_read[PL]].routine_num++;
                break;
            case 1:
                if (cmst_buff[PL][cst_read[PL]].x_posnum[0] < cmst_buff[PL][cst_read[PL]].move[0]) {
                    combo_window_slide(PL,
                                            cmb_pos_tbl[Game_setting.Screen_Mode][PL][cmst_buff[PL][cst_read[PL]].x_posnum[0]],
                                            0,
                                            cmst_buff[PL][cst_read[PL]].x_posnum[0]);
                    cmst_buff[PL][cst_read[PL]].x_posnum[0]++;
                } else {
                    cmst_buff[PL][cst_read[PL]].timer[1] = 36;
                    cmst_buff[PL][cst_read[PL]].routine_num++;
                }
                break;
            case 2:
                cmst_buff[PL][cst_read[PL]].timer[1]--;
                if (cmst_buff[PL][cst_read[PL]].timer[1] == 0) {
                    combo_window_erase(PL, cmst_buff[PL][cst_read[PL]].kind, 0);
                    if (cmst_buff[PL][cst_read[PL]].pts_flag) {
                        cmst_buff[PL][cst_read[PL]].routine_num++;
                        break;
                    }
                    if (cst_read[PL] == 3) {
                        cst_read[PL] = 0;
                    } else {
                        cst_read[PL]++;
                    }
                    cmb_stock[PL]--;
                }
                break;
            }
        }
    }
}

