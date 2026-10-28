/*
 * CK_PASS.C  Computer player: passive reaction checks
 *
 * Ck_Passive_Term picks a reaction to what the opponent is doing, through Passive_jmp_tbl by the
 * CPU's own character: GILL_vs for Gill, KEN_vs for every other character. They select by area
 * and passive mode; the Check_* routines test for particular
 * situations (special techniques, attack direction, jumps, rushes, dashes,
 * super-art punishes, throws, knock-downs, faints, turn-overs) and set VS_Tech and
 * Counter_Attack.
 * Check_PL_Unit_AS and its companions dispatch by the opponent's character to the
 * VS_<name>_ routines, one per opponent and screen area A-D, with and without an attack in
 * progress (the ...S variants); each tests the opponent's special techniques and returns 1
 * when a reaction has been chosen. Called from the passive and guard logic in Com_Pl.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Pl.h"
#include "PLS03ATT.h"
#include "PLS02.h"
#include "CMD_MAIN.h"
#include "cmd_main_2.h"
#include "HITCHECK.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "Com_Sub.h"
#include "fighter.h"

s8 PASSIVE_X;  /* 02013908 */



/* provisional name */
s32 Ck_Passive_Term(PLW* wk) {
    PASSIVE_X = 0;
    Passive_jmp_tbl[wk->player_number](wk);
    return PASSIVE_X;
}



s32 KEN_vs(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    switch (Area_Number[wk->wu.id] + Passive_Mode) {
    case 0:
        if (Check_Dash(wk, em, 1)) {
            break;
        }
        break;
    case 1:
        if (Check_Dash(wk, em, 1)) {
            break;
        }
        break;
    case 2:
        if (Check_Dash(wk, em, 1)) {
            break;
        }
        break;
    case 3:
        if (Check_Dash(wk, em, 1)) {
            break;
        }
        break;
    case 4:
        if (Attack_Flag[wk->wu.id]) {
            if (Check_PL_Unit_A(wk)) {
                break;
            }
            if (Check_Limited_Attack(wk, em, 12, 32, 3, 0)) {
                break;
            }
            if (Check_Limited_Attack(wk, em, 7, 32, 5, 0)) {
                break;
            }
            if (Check_Special_Technique(wk, em, 15, 0, 33, 1, -1)) {
                return 1;
            }
        } else {
            if (Check_PL_Unit_AS(wk)) {
                break;
            }
            if (Check_After_Attack(wk, em, 28)) {
                break;
            }
            if (Check_VS_Squat(wk, em, 29, 33, 32)) {
                break;
            }
            if (Check_Stand(wk, em, 4105)) {
                break;
            }
        }
        if (Check_VS_Jump(wk, em, 16)) {
            break;
        }
        break;
    case 5:
        if (Attack_Flag[wk->wu.id]) {
            if (Check_PL_Unit_B(wk)) {
                break;
            }
            if (Check_Limited_Attack(wk, em, 12, 32, 3, 0)) {
                break;
            }
            if (Check_Limited_Attack(wk, em, 7, 32, 5, 0)) {
                break;
            }
            if (Check_Special_Technique(wk, em, 15, 0, 33, 1, -1)) {
                return 1;
            }
        } else {
            if (Check_PL_Unit_BS(wk)) {
                break;
            }
            if (Check_After_Attack(wk, em, 28)) {
                break;
            }
            if (Check_VS_Squat(wk, em, 29, 33, 32)) {
                break;
            }
            if (Check_Stand(wk, em, 4105)) {
                break;
            }
        }
        if (Check_VS_Jump(wk, em, 32)) {
            break;
        }
        break;
    case 6:
        if (Attack_Flag[wk->wu.id]) {
            if (Check_PL_Unit_C(wk)) {
                break;
            }
            if (Check_Limited_Attack(wk, em, 12, 32, 3, 0)) {
                break;
            }
            if (Check_Limited_Attack(wk, em, 7, 32, 5, 0)) {
                break;
            }
        } else {
            if (Check_PL_Unit_CS(wk)) {
                break;
            }
            if (Check_After_Attack(wk, em, 28)) {
                break;
            }
            if (Check_Stand(wk, em, 4105)) {
                break;
            }
        }
        if (Check_VS_Jump(wk, em, 64)) {
            break;
        }
        break;
    default:
        if (Attack_Flag[wk->wu.id]) {
            if (Check_PL_Unit_D(wk)) {
                break;
            }
        } else {
            if (Check_PL_Unit_DS(wk)) {
                break;
            }
            if (Check_Stand(wk, em, 4105)) {
                break;
            }
        }
        break;
    }
}



s32 GILL_vs(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    switch (Area_Number[wk->wu.id] + Passive_Mode) {
    case 0:
        if (Check_Dash(wk, em, 1)) {
            break;
        }
        break;
    case 1:
        if (Check_Dash(wk, em, 1)) {
            break;
        }
        break;
    case 2:
        if (Check_Dash(wk, em, 1)) {
            break;
        }
        break;
    case 3:
        if (Check_Dash(wk, em, 1)) {
            break;
        }
        break;
    case 4:
        if (Attack_Flag[wk->wu.id]) {
            if (Check_PL_Unit_A(wk)) {
                break;
            }
            if (Check_Limited_Attack(wk, em, 12, 32, 3, 0)) {
                break;
            }
            if (Check_Limited_Attack(wk, em, 7, 32, 5, 0)) {
                break;
            }
            if (Check_Special_Technique(wk, em, 15, 0, 33, 1, -1)) {
                return 1;
            }
        } else {
            if (Check_PL_Unit_AS(wk)) {
                break;
            }
            if (Check_After_Attack(wk, em, 28)) {
                break;
            }
            if (Check_VS_Squat(wk, em, 29, 33, 32)) {
                break;
            }
            if (Check_Stand(wk, em, 4105)) {
                break;
            }
        }
        if (Check_VS_Jump(wk, em, 16)) {
            break;
        }
        break;
    case 5:
        if (Attack_Flag[wk->wu.id]) {
            if (Check_PL_Unit_B(wk)) {
                break;
            }
            if (Check_Limited_Attack(wk, em, 12, 32, 3, 0)) {
                break;
            }
            if (Check_Limited_Attack(wk, em, 7, 32, 5, 0)) {
                break;
            }
            if (Check_Special_Technique(wk, em, 15, 0, 33, 1, -1)) {
                return 1;
            }
        } else {
            if (Check_PL_Unit_BS(wk)) {
                break;
            }
            if (Check_After_Attack(wk, em, 28)) {
                break;
            }
            if (Check_VS_Squat(wk, em, 29, 33, 32)) {
                break;
            }
            if (Check_Stand(wk, em, 4105)) {
                break;
            }
        }
        if (Check_VS_Jump(wk, em, 32)) {
            break;
        }
        break;
    case 6:
        if (Attack_Flag[wk->wu.id]) {
            if (Check_PL_Unit_C(wk)) {
                break;
            }
            if (Check_Limited_Attack(wk, em, 12, 32, 3, 0)) {
                break;
            }
            if (Check_Limited_Attack(wk, em, 7, 32, 5, 0)) {
                break;
            }
        } else {
            if (Check_PL_Unit_CS(wk)) {
                break;
            }
            if (Check_After_Attack(wk, em, 28)) {
                break;
            }
            if (Check_Stand(wk, em, 4105)) {
                break;
            }
        }
        if (Check_VS_Jump(wk, em, 64)) {
            break;
        }
        break;
    default:
        if (Attack_Flag[wk->wu.id]) {
            if (Check_PL_Unit_D(wk)) {
                break;
            }
        } else {
            if (Check_PL_Unit_DS(wk)) {
                break;
            }
            if (Check_Stand(wk, em, 4105)) {
                break;
            }
            if (Check_VS_Squat(wk, em, 7, 33, 32)) {
                break;
            }
        }
        break;
    }
}



s32 Check_Special_Technique(PLW* wk, WORK* em, s16 VS_Technique, u8 Kind_of_Tech, u8 SP_Tech_ID, s16 Option, s16 Option2) {
    u8 xx;
    if (Option == 8 && Attack_Flag[wk->wu.id] != 0) {
        return 0;
    }
    if (VS_Technique != 23 && Check_Attack_Direction(wk, em)) {
        return 0;
    }
    if (Last_Attack_Counter[wk->wu.id] == Attack_Counter[wk->wu.id]) {
        return 0;
    }
    xx = em->kind_of_waza & 0xF8;
    if (xx == Kind_of_Tech && (em->sp_tech_id == SP_Tech_ID)) {
        if (Option2 == (em->kind_of_waza & 7)) {
            Last_Attack_Counter[(wk->wu.id)] = Attack_Counter[(wk->wu.id)];
            return 0;
        }
        if (Option == 8) {
            Counter_Attack[(wk->wu.id)] = 1;
        }
        if (Option == 1) {
            Counter_Attack[(wk->wu.id)] = 1;
        }
        VS_Tech[wk->wu.id] = VS_Technique;
        return PASSIVE_X = 1;
    }
    return 0;
}



s32 Check_Attack_Direction(PLW* wk, WORK* em) {
    if (wk->wu.xyz[0].disp.pos < em->xyz[0].disp.pos) {
        if (em->xyz[0].disp.pos > em->old_pos[0]) {
            return 1;
        }
    } else if (em->xyz[0].disp.pos < em->old_pos[0]) {
        return 1;
    }
    return 0;
}



/* provisional name */
s32 Check_Special_Tech_ID(PLW* wk, WORK* em, s16 VS_Technique, u8 SP_Tech_ID, s16 Option) {
    if (Option == 8 && Attack_Flag[wk->wu.id]) {
        return 0;
    }
    if (em->kind_of_waza & 0xF8) {
        return 0;
    }
    if (em->sp_tech_id == SP_Tech_ID) {
        Counter_Attack[wk->wu.id] = 1;
        VS_Tech[wk->wu.id] = VS_Technique;
        return PASSIVE_X = 1;
    }
    return 0;
}



s32 Check_VS_Jump(wk, em, Option, Height)
PLW* wk;
PLW* em;
s16 Option;
s16 Height;
{
    if (em->wu.routine_no[1] == PLAYER_DAMAGE) {
        return 0;
    }
    if (Jump_Pass_Timer[wk->wu.id][Area_Number[wk->wu.id]]) {
        Jump_Pass_Timer[wk->wu.id][Area_Number[wk->wu.id]]--;
        return 0;
    }
    if (em->wu.mvxy.a[1].real.h < 0 && em->wu.xyz[1].disp.pos <= Height) {
        return 0;
    }
    if (Check_Specific_Term(wk, &em->wu, 4099, 14, 20, 26)) {
        return Counter_Attack[wk->wu.id] = 1;
    } else if (em->wu.xyz[1].disp.pos == 0) {
        return 0;
    }
    if (em->wu.xyz[1].disp.pos < 32 && em->wu.mvxy.a[1].real.h > 0) {
        return 0;
    }
    if (em->micchaku_flag) {
        VS_Tech[wk->wu.id] = 18;
        return PASSIVE_X = 1;
    }
    if (Check_Specific_Term(wk, &em->wu, 18, 22, 28, 16)) {
        return 1;
    }
    return 0;
}



/* provisional name */
s32 Check_Rolling(PLW* wk, WORK* em) {
    if (em->pat_status != 34) {
        return 0;
    }
    if (Check_Attack_Direction(wk, em)) {
        VS_Tech[wk->wu.id] = 6;
    } else {
        VS_Tech[wk->wu.id] = 5;
    }
    return PASSIVE_X = 1;
}



s32 Check_Specific_Term(PLW* wk, WORK* em, s16 VS_Technique, u8 Status_00, u8 Status_01, u8 Status_02) {
    VS_Tech[wk->wu.id] = VS_Technique;
    if (em->pat_status == Status_00) {
        return PASSIVE_X = 1;
    }
    if (em->pat_status == Status_01) {
        return PASSIVE_X = 1;
    }
    if (em->pat_status == Status_02) {
        return PASSIVE_X = 1;
    }
    return 0;
}



s32 Check_Dash(PLW* wk, WORK* em, s16 VS_Technique) {
    if ((em->routine_no[1] == PLAYER_NORMAL) && (em->routine_no[2] == NORMAL_DASH) && (em->routine_no[3] != 0)) {
        VS_Tech[wk->wu.id] = VS_Technique;
        return PASSIVE_X = 1;
    }
    return 0;
}



s32 Check_Limited_Attack(PLW* wk, WORK* em, s16 VS_Technique, u8 PL_Status, s8 Status_00, s16 Limit_Number) {
    s16 xx;
    if (Attack_Flag[wk->wu.id] == 0) {
        return 0;
    }
    if (Last_Attack_Counter[wk->wu.id] == Attack_Counter[wk->wu.id]) {
        return 0;
    }
    if ((em->pat_status != PL_Status) || em->kind_of_waza != Status_00) {
        return 0;
    }
    xx = (em->cg_ix / em->cgd_type);
    if (xx > Limit_Number) {
        return 0;
    }
    VS_Tech[wk->wu.id] = VS_Technique;
    Limited_Flag[wk->wu.id] = 1;
    Counter_Attack[wk->wu.id] = 1;
    return PASSIVE_X = 1;
}



s32 Check_Limited_Jump_Attack(PLW* wk, WORK* em, u8 PL_Status, s8 Status_00) {
    if ((em->pat_status != PL_Status) || (em->kind_of_waza != Status_00)) {
        return 0;
    }
    return 1;
}


/* provisional name */
s32 limited_jump_attack_set(PLW* wk, WORK* em, s16 VS_Technique) {
    if (Attack_Flag[wk->wu.id] == 0) {
        return 0;
    }
    if (em->kind_of_waza & 0xF0) {
        return 0;
    }
    VS_Tech[wk->wu.id] = VS_Technique;
    Counter_Attack[wk->wu.id] = 1;
    return PASSIVE_X = 1;
}



s32 Check_Stand(PLW* wk, WORK* em, s16 VS_Technique) {
    if (Attack_Flag[wk->wu.id]) {
        return 0;
    }
    if (em->routine_no[1] != PLAYER_NORMAL) {
        return 0;
    }
    if ((Standing_Timer[wk->wu.id] += 1) < Standing_Master_Timer[wk->wu.id]) {
        return 0;
    }
    Standing_Master_Timer[wk->wu.id] = Setup_Next_Stand_Timer(wk);
    VS_Tech[wk->wu.id] = VS_Technique;
    return PASSIVE_X = 1;
}



s32 Setup_Next_Stand_Timer(PLW* wk) {
    return Standing_Time_Data[wk->player_number][Area_Number[wk->wu.id]][(random_16_com() & 7)];
}



/* provisional name */
s32 Check_Turn_Over(PLW* wk, WORK* em, s16 VS_Technique) {
    if (Attack_Flag[wk->wu.id] || em->routine_no[1] || em->xyz[1].disp.pos) {
        goto reset;
    }
    if (Ck_Distance_XX(wk) != 0) {
        if (--Turn_Over_Timer[wk->wu.id] != 0) {
            return 0;
        }
        Turn_Over_Timer[wk->wu.id] = 90;
        Turn_Over[wk->wu.id] = 1;
        VS_Tech[wk->wu.id] = VS_Technique;
        return PASSIVE_X = 1;
    }
reset:
    Turn_Over_Timer[wk->wu.id] = 1;
    return 0;
}



s32 Check_VS_Squat(PLW* wk, WORK* em, s16 VS_Technique, u8 Status_00, u8 Status_01) {
    if (Attack_Flag[wk->wu.id]) {
        return Squat_Timer[wk->wu.id] = 0;
    }
    if (em->routine_no[1] != PLAYER_NORMAL) {
        return Squat_Timer[wk->wu.id] = 0;
    }
    if (em->xyz[1].disp.pos) {
        return Squat_Timer[wk->wu.id] = 0;
    }
    if (em->pat_status != Status_00 && em->pat_status != Status_01) {
        return Squat_Timer[wk->wu.id] = 0;
    }
    if ((Squat_Timer[wk->wu.id] += 1) < Squat_Master_Timer[wk->wu.id]) {
        return 0;
    }
    Squat_Master_Timer[wk->wu.id] = Setup_Next_Squat_Timer(wk);
    VS_Tech[wk->wu.id] = VS_Technique;
    return PASSIVE_X = 1;
}



s32 Setup_Next_Squat_Timer(PLW* wk) {
    return Squat_Time_Data[Setup_Lv10(0)][(random_16_com() & 7)];
}



s32 Check_Thrown(PLW* wk, WORK* em) {
    if (Attack_Flag[wk->wu.id]) {
        return 0;
    }
    if (em->xyz[1].disp.pos) {
        return 0;
    }
    switch (Area_Number[wk->wu.id]) {
    case 0:
        if (Check_Catch(wk, em, 25)) {
            return 1;
        }
        break;
    default:
        break;
    }
    return 0;
}



s32 Check_Catch(PLW* wk, WORK* em, s16 VS_Technique) {
    u16 xx;
    if (Demo_Flag == 0) {
        return 0;
    }
    if (em->routine_no[1] != PLAYER_NORMAL) {
        return 0;
    }
    if (em->xyz[1].disp.pos) {
        return 0;
    }
    if (wk->wu.id == 0) {
        xx = p2sw_0;
    } else {
        xx = p1sw_0;
    }
    if (wk->wu.rl_waza) {
        if (!(xx & LEVER_LEFT)) {
            return 0;
        }
    } else if (!(xx & LEVER_RIGHT)) {
        return 0;
    }
    Counter_Attack[wk->wu.id] = 1;
    VS_Tech[wk->wu.id] = VS_Technique;
    return PASSIVE_X = 1;
}



/* provisional name */
s32 Check_Lie_Reset(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Blow_Off(wk, em, 0)) {
        return;
    }
    if (Check_Specific_Term(wk, em, 0, 38, 38, 38)) {
        return;
    }
    return Lie_Flag[wk->wu.id] &= 0x80;
}



/* provisional name */
s32 Check_Down_Term(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Blow_Off(wk, em, 0)) {
        return 1;
    }
    if (Check_Specific_Term(wk, em, 0, 38, 38, 38)) {
        return 1;
    }
    return 0;
}



s32 Check_Lie(PLW* wk) {
    WORK* em;
    PLW* enemy;
    em = (WORK*)wk->wu.target_adrs;
    enemy = (PLW*)wk->wu.target_adrs;
    if (Check_Faint(wk, enemy, 2)) {
        return Select_Passive(wk);
    }
    if (Check_Specific_Term(wk, em, 0, 38, 38, 38)) {
        return Select_Passive(wk);
    }
    return 0;
}



s32 Check_Faint(PLW* wk, PLW* enemy, s16 VS_Technique) {
    Counter_Attack[wk->wu.id] = 1;
    VS_Tech[wk->wu.id] = VS_Technique;
    if ((enemy->wu.routine_no[1] == PLAYER_DAMAGE) && (enemy->wu.routine_no[2] == DAMAGE_STUN)) {
        return 1;
    }
    return Counter_Attack[wk->wu.id] = 0;
}



s32 Check_Blow_Off(PLW* wk, WORK* em, s16 VS_Technique) {
    if (em->routine_no[1] != PLAYER_DAMAGE) {
        return 0;
    }
    if (PL_Blow_Off_Data[em->routine_no[2]] == 0) {
        return 0;
    }
    if (em->xyz[1].disp.pos == 0) {
        return 0;
    }
    VS_Tech[(wk->wu.id)] = VS_Technique;
    return PASSIVE_X = 1;
}



s32 Check_After_Attack(PLW* wk, WORK* em, s16 VS_Technique) {
    u8 xx;
    if (CP_No[wk->wu.id][0] == COM_GUARD) {
        return 0;
    }
    if (Last_Attack_Counter[wk->wu.id] == Attack_Counter[wk->wu.id]) {
        return 0;
    }
    if (em->xyz[1].disp.pos) {
        return 0;
    }
    if (em->routine_no[1] != PLAYER_ATTACK) {
        return 0;
    }
    Last_Attack_Counter[wk->wu.id] = Attack_Counter[wk->wu.id];
    if ((em->kind_of_waza & 0x20) == 0) {
        if ((em->kind_of_waza & 0x30) == 0) {
            if ((em->kind_of_waza & 0x28) == 0) {
                if ((em->kind_of_waza & 0x38) == 0) {
                    if ((em->kind_of_waza & 8) == 0) {
                        xx = em->kind_of_waza & 6;
                        if (xx == 0) {
                            return 0;
                        }
                        if (xx == 2) {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    VS_Tech[wk->wu.id] = VS_Technique;
    return PASSIVE_X = 1;
}



s32 Check_F_Cross_Chop(PLW* wk, WORK* em, s16 VS_Technique) {
    if (Last_Attack_Counter[wk->wu.id] == Attack_Counter[wk->wu.id]) {
        return 0;
    }
    if (em->kind_of_waza != 4) {
        return 0;
    }
    if (em->pat_status != 0x16) {
        if (em->pat_status != 0x14) {
            if (em->pat_status != 0x1A) {
                if (em->pat_status != 0x1C) {
                    return 0;
                }
            }
        }
    }
    VS_Tech[wk->wu.id] = VS_Technique;
    Counter_Attack[wk->wu.id] = 1;
    return PASSIVE_X = 1;
}



/* Opponent-specific passive check (table AS): returns the chosen response, 0 when none. */
s32 Check_PL_Unit_AS(PLW* wk) {
    Passive_AS_tbl[((PLW*)wk->wu.target_adrs)->player_number](wk);
}



s32 VS_GILL_AS(PLW* wk) {
    return 0;
}



s32 VS_ALEX_AS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 24, 23, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 24, 22, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 56, 37, -1, -1)) {
        return 1;
    }
    if (Check_Rolling(wk, em)) {
        return 1;
    }
    return 0;
}



s32 VS_RYU_AS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 1, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 11, 8, 0, 1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 11, 32, 4, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 11, 32, 5, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_YUN_AS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 29, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 36, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_DUDLEY_AS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 1, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 24, 8, 2, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 32, 13, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 11, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 32, 12, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_NECRO_AS(PLW* wk) {
    return 0;
}



s32 VS_IBUKI_AS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 28, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 25, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ELENA_AS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 17, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 14, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 32, 15, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 2, 48, 16, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ORO_AS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 39, -1, 0)) {
        return 1;
    }
    return 0;
}



s32 VS_KEN_AS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 11, 8, 0, 1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 8, 1, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 8, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 6, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 2, 32, 7, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_SEAN_AS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 32, 8, -1, -1)) {
        return 1;
    }
    return 0;
}



/* Opponent-specific passive check (table A): returns the chosen response, 0 when none. */
s32 Check_PL_Unit_A(PLW* wk) {
    Passive_A_tbl[((PLW*)wk->wu.target_adrs)->player_number](wk);
}



s32 VS_GILL_A(PLW* wk) {
    return 0;
}



s32 VS_ALEX_A(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 25, 24, 22, 1, -1)) {
        return 1;
    }
    if (Check_F_Cross_Chop(wk, em, 15)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 15, 8, 30, 1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_RYU_A(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 11, 8, 0, 1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 48, 3, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 16, 32, 4, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 16, 32, 5, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_YUN_A(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 8, 8, 31, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_DUDLEY_A(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 24, 8, 2, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_NECRO_A(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 24, 8, 38, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 15, 8, 40, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 17, 24, 24, 1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 11, 32, 41, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_IBUKI_A(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 24, 24, 26, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ELENA_A(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 8, 8, 18, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 2, 48, 16, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ORO_A(PLW* wk) {
    return 0;
}



s32 VS_KEN_A(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 11, 8, 0, 1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_SEAN_A(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 24, 8, 21, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 15, 8, 32, -1, 0)) {
        return 1;
    }
    if (Check_Rolling(wk, em)) {
        return 1;
    }
    return 0;
}



/* Opponent-specific passive check (table BS): returns the chosen response, 0 when none. */
s32 Check_PL_Unit_BS(PLW* wk) {
    Passive_BS_tbl[((PLW*)wk->wu.target_adrs)->player_number](wk);
}



s32 VS_GILL_BS(PLW* wk) {
    return 0;
}



s32 VS_ALEX_BS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 24, 23, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 24, 22, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 56, 37, -1, -1)) {
        return 1;
    }
    if (Check_Rolling(wk, em)) {
        return 1;
    }
    return 0;
}



s32 VS_RYU_BS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 1, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 11, 8, 0, 1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 24, 8, 2, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 48, 3, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 16, 32, 4, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 16, 32, 5, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_YUN_BS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 29, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 36, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_DUDLEY_BS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 1, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 32, 13, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 11, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 32, 12, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_NECRO_BS(PLW* wk) {
    return 0;
}



s32 VS_IBUKI_BS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 28, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 25, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ELENA_BS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 17, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 14, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 32, 15, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 2, 48, 16, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ORO_BS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 39, -1, 0)) {
        return 1;
    }
    return 0;
}



s32 VS_KEN_BS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 11, 8, 0, 1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 8, 1, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 24, 8, 2, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 8, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 6, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 2, 32, 7, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_SEAN_BS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 32, 8, -1, -1)) {
        return 1;
    }
    return 0;
}



/* Opponent-specific passive check (table B): returns the chosen response, 0 when none. */
s32 Check_PL_Unit_B(PLW* wk) {
    Passive_B_tbl[((PLW*)wk->wu.target_adrs)->player_number](wk);
}



s32 VS_GILL_B(PLW* wk) {
    return 0;
}



s32 VS_ALEX_B(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 25, 24, 22, 1, -1)) {
        return 1;
    }
    if (Check_F_Cross_Chop(wk, em, 15)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 15, 8, 30, 1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_RYU_B(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 11, 8, 0, 1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 24, 8, 2, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 16, 32, 4, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 16, 32, 5, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_YUN_B(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 8, 8, 31, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_DUDLEY_B(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 24, 8, 2, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_NECRO_B(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 24, 8, 38, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 15, 8, 40, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 17, 24, 24, 1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 11, 32, 41, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_IBUKI_B(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 24, 24, 26, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ELENA_B(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 8, 8, 18, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 2, 48, 16, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ORO_B(PLW* wk) {
    return 0;
}



s32 VS_KEN_B(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 11, 8, 0, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 24, 8, 2, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_SEAN_B(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 15, 8, 32, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 24, 8, 21, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 24, 8, 20, -1, -1)) {
        return 1;
    }
    if (Check_Rolling(wk, em)) {
        return 1;
    }
    return 0;
}



/* Opponent-specific passive check (table CS): returns the chosen response, 0 when none. */
s32 Check_PL_Unit_CS(PLW* wk) {
    Passive_CS_tbl[((PLW*)wk->wu.target_adrs)->player_number](wk);
}



s32 VS_GILL_CS(PLW* wk) {
    return 0;
}



s32 VS_ALEX_CS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 24, 23, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 24, 22, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 56, 37, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_RYU_CS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 1, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 11, 8, 0, 1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 48, 3, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 16, 32, 4, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 16, 32, 5, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_YUN_CS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 29, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 36, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_DUDLEY_CS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 1, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 24, 8, 2, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 32, 13, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 11, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 32, 12, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_NECRO_CS(PLW* wk) {
    return 0;
}



s32 VS_IBUKI_CS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 32, 25, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ELENA_CS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 17, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 14, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 14, 32, 15, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 2, 48, 16, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ORO_CS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 8, 39, -1, 0)) {
        return 1;
    }
    return 0;
}



s32 VS_KEN_CS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 11, 8, 0, 1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 8, 1, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 8, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 23, 32, 6, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 2, 32, 7, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_SEAN_CS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 23, 32, 8, -1, -1)) {
        return 1;
    }
    return 0;
}



/* Opponent-specific passive check (table C): returns the chosen response, 0 when none. */
s32 Check_PL_Unit_C(PLW* wk) {
    Passive_C_tbl[((PLW*)wk->wu.target_adrs)->player_number](wk);
}



s32 VS_GILL_C(PLW* wk) {
    return 0;
}



s32 VS_ALEX_C(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 15, 8, 30, 1, -1)) {
        return 1;
    }
    if (Check_F_Cross_Chop(wk, em, 15)) {
        return 1;
    }
    return 0;
}



s32 VS_RYU_C(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 11, 8, 0, 1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 24, 8, 2, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 16, 32, 4, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 16, 32, 5, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_YUN_C(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 8, 8, 31, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_DUDLEY_C(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 24, 8, 2, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_NECRO_C(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 24, 8, 38, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 15, 8, 40, 1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 17, 24, 24, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 11, 32, 41, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_IBUKI_C(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 24, 24, 26, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ELENA_C(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 8, 8, 18, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 2, 48, 16, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ORO_C(PLW* wk) {
    return 0;
}



s32 VS_KEN_C(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 11, 8, 0, 1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 24, 8, 2, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_SEAN_C(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 15, 8, 32, -1, 0)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 24, 8, 21, -1, -1)) {
        return 1;
    }
    if (Check_Special_Technique(wk, em, 24, 8, 20, -1, -1)) {
        return 1;
    }
    return 0;
}



/* Opponent-specific passive check (table DS): returns the chosen response, 0 when none. */
s32 Check_PL_Unit_DS(PLW* wk) {
    Passive_DS_tbl[((PLW*)wk->wu.target_adrs)->player_number](wk);
}



s32 VS_GILL_DS(PLW* wk) {
    return 0;
}



s32 VS_ALEX_DS(PLW* wk) {
    return 0;
}



s32 VS_RYU_DS(PLW* wk) {
    return 0;
}



s32 VS_YUN_DS(PLW* wk) {
    return 0;
}



s32 VS_DUDLEY_DS(PLW* wk) {
    return 0;
}



s32 VS_NECRO_DS(PLW* wk) {
    return 0;
}



s32 VS_IBUKI_DS(PLW* wk) {
    return 0;
}



s32 VS_ELENA_DS(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 2, 48, 16, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ORO_DS(PLW* wk) {
    return 0;
}



s32 VS_KEN_DS(PLW* wk) {
    return 0;
}



s32 VS_SEAN_DS(PLW* wk) {
    return 0;
}



/* Opponent-specific passive check (table D): returns the chosen response, 0 when none. */
s32 Check_PL_Unit_D(PLW* wk) {
    Passive_D_tbl[((PLW*)wk->wu.target_adrs)->player_number](wk);
}



s32 VS_GILL_D(PLW* wk) {
    return 0;
}



s32 VS_ALEX_D(PLW* wk) {
    return 0;
}



s32 VS_RYU_D(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 11, 8, 0, 1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_YUN_D(PLW* wk) {
    return 0;
}



s32 VS_DUDLEY_D(PLW* wk) {
    return 0;
}



s32 VS_NECRO_D(PLW* wk) {
    return 0;
}



s32 VS_IBUKI_D(PLW* wk) {
    return 0;
}



s32 VS_ELENA_D(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 2, 48, 16, -1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_ORO_D(PLW* wk) {
    return 0;
}



s32 VS_KEN_D(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Special_Technique(wk, em, 11, 8, 0, 1, -1)) {
        return 1;
    }
    return 0;
}



s32 VS_SEAN_D(PLW* wk) {
    return 0;
}


