/*
 * COM_SUB.C  Computer player: pattern step library and decision helpers
 *
 * The building blocks used by every CPU pattern. Pattern steps: End_Pattern, Lever_On/Off,
 * Walk, Approach_Walk, Keep_Away, Wait, Look, Forced_Guard, Normal_Attack, Lever_Attack,
 * Jump_Attack, Hi_Jump_Attack, Command_Attack, SA_Term and the other
 * *_Term steps that attack when range and state conditions are met.
 * Checks and helpers: Ck_Distance, Ck_Area and the Check_* tests on the opponent, combo
 * speed and reaction time selection, Select_Active / Select_Passive / Decide_Follow_Menu
 * that pick the next pattern, and projectile handling (Check_Shell, Decide_Shell_Guard,
 * Guard_or_Jump_VS_Shell).
 * Exit_Term_* and ETC_Term_* are the term routines tested by patterns to end or branch.
 * Called from the pattern modules (ACTIVE*, Passive*, FOLLOW*) and Com_Pl.
 * The passive reaction checks are in CK_PASS.C.
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

/* Rapid_No[pl][0] in Rapid_Sub: the kind of rapid fire */
#define RAPID_OFF       0       /* none */
#define RAPID_BURST     2       /* three presses, a pause, then steady presses */
#define RAPID_STEADY    1       /* (default) steady presses */

/* a shell's routine_no[1] (EFF13) */
#define SHELL_VANISH    2       /* playing its end pattern: no longer a threat */

/* Rapid_No[pl][1] in Rapid_Sub */
#define RAPID1_INIT     0       /* set the timers */
#define RAPID1_BURST    1       /* the burst */
#define RAPID1_PAUSE    2       /* the pause (then steady) */

/* Rapid_No[pl][2]: when Check_Rapid_End stops the rapid fire */
#define RAPID_END_FALL  1       /* once falling */
#define RAPID_END_CAUTION 2     /* once caution_flag has come and gone */
#define RAPID_END_ATTACK 4      /* a while after the attack is out */

/* Rapid_No[pl][3] in Check_Rapid_End */
#define RAPID3_WAIT     0       /* until the first condition */
#define RAPID3_END      1       /* until the second, then stop */

/* Term_No[pl] in the Exit_Term_* routines */
#define TERM_INIT       0       /* set Timer_00 (then wait or watch for the end) */

extern const u16 cancel_shot_tbl[][8];    /* provisional name (063E5F44, [7][8]): 0x10 0x20 0x40 0x80 0x100 0x200, by cg_eftype bits 4-6 */
extern const u16 Meoshi_Lever_Data[16];   /* provisional name (063E5FD8): lever by cg_eftype bits 0-3; 0x8000/0x8001 = guard lever */

extern const FOLLOW_MENU_1ST Follow_Menu_1st_Unit_Data_0[];
extern const FOLLOW_MENU_1ST Follow_Menu_1st_Unit_Data_2[];
extern const FOLLOW_MENU_2ND Follow_Menu_2nd_Unit_Data_0[];
extern const FOLLOW_MENU_2ND Follow_Menu_2nd_Unit_Data_2[];

/* 02000CD4 */
const FOLLOW_MENU_1ST* Follow_Menu_1st_Unit_Data[13] = {
    Follow_Menu_1st_Unit_Data_0,
    Follow_Menu_1st_Unit_Data_0,
    Follow_Menu_1st_Unit_Data_2,
    Follow_Menu_1st_Unit_Data_0,
    Follow_Menu_1st_Unit_Data_0,
    Follow_Menu_1st_Unit_Data_0,
    Follow_Menu_1st_Unit_Data_0,
    Follow_Menu_1st_Unit_Data_0,
    Follow_Menu_1st_Unit_Data_0,
    Follow_Menu_1st_Unit_Data_0,
    Follow_Menu_1st_Unit_Data_0,
    Follow_Menu_1st_Unit_Data_0,
    Follow_Menu_1st_Unit_Data_0,
};
/* 02000D08 */
const FOLLOW_MENU_2ND* Follow_Menu_2nd_Unit_Data[13] = {
    Follow_Menu_2nd_Unit_Data_0,
    Follow_Menu_2nd_Unit_Data_0,
    Follow_Menu_2nd_Unit_Data_2,
    Follow_Menu_2nd_Unit_Data_0,
    Follow_Menu_2nd_Unit_Data_0,
    Follow_Menu_2nd_Unit_Data_0,
    Follow_Menu_2nd_Unit_Data_0,
    Follow_Menu_2nd_Unit_Data_0,
    Follow_Menu_2nd_Unit_Data_0,
    Follow_Menu_2nd_Unit_Data_0,
    Follow_Menu_2nd_Unit_Data_0,
    Follow_Menu_2nd_Unit_Data_0,
    Follow_Menu_2nd_Unit_Data_0,
};



s8 Lv;  /* 020138F0 */
s8 Rnd;  /* 020138F1 */



void End_Pattern(void) { Next_Be_Free(); }



void Next_Be_Passive(void) { Next_Be_Free(); }



void Turn_Over_On(PLW* wk) {
    Turn_Over[wk->wu.id] = 1;
    CP_Index[wk->wu.id][0]++;
}




void Lever_On(wk, LR_Lever, UD_Lever)
PLW* wk;
u16 LR_Lever;
u16 UD_Lever;
{
    CP_Index[wk->wu.id][0]++;
    Disposal_Again[wk->wu.id] = 1;
    if ((LR_Lever == 0) || (LR_Lever == 1)) {
        Lever_LR[wk->wu.id] = Setup_Guard_Lever(wk, LR_Lever);
    } else {
        Lever_LR[wk->wu.id] = 0;
    }
    Lever_LR[wk->wu.id] |= UD_Lever;
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
}



void Lever_Off(PLW* wk) {
    CP_Index[wk->wu.id][0]++;
    Disposal_Again[wk->wu.id] = 1;
    Lever_LR[wk->wu.id] = 0;
}



void Pierce_On(PLW* wk) {
    CP_Index[wk->wu.id][0]++;
    Pierce_Menu[wk->wu.id] = 1;
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
}



/* provisional name */
void Pierce_Off(PLW* wk) {
    CP_Index[wk->wu.id][0]++;
    Pierce_Menu[wk->wu.id] = 0;
    Disposal_Again[wk->wu.id] = 1;
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
}



/* provisional name: a second copy of Pierce_Off */
void Pierce_Off_2(PLW* wk) {
    CP_Index[wk->wu.id][0]++;
    Pierce_Menu[wk->wu.id] = 0;
    Disposal_Again[wk->wu.id] = 1;
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
}



void Setup_DENJIN_LEVEL(PLW* wk) {
    u16 xx;
    Disposal_Again[wk->wu.id] = 1;
    if ((xx = DENJIN_No[wk->wu.id])) {
        Next_Another_Menu(wk, 2, xx);
    } else {
        Next_Another_Menu(wk, 2, Denjin_Data[Area_Number[wk->wu.id]][random_16_com()]);
    }
}



void Push_Shot(wk, Power_Level)
PLW* wk;
s16 Power_Level;
{
    s16 xx;
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        if ((wk->wu.now_koc == 8) && (wk->wu.char_index == 13)) {
            xx = wk->wu.cg_ix / wk->wu.cgd_type;
            if (xx >= Power_Level) {
                CP_Index[wk->wu.id][1] = 0x63;
            }
        }
        if (Check_Exit_DENJIN(wk) != 0) {
            CP_Index[wk->wu.id][1] = 0x63;
        }
        break;
    case 1:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        if (Check_Exit_DENJIN(wk) != 0) {
            CP_Index[wk->wu.id][1] = 0x63;
        }
    default:
        if ((wk->wu.cg_type == 0x40) || (wk->wu.routine_no[1] == PLAYER_NORMAL)) {
            Reaction_Exit_Sub(wk);
        } else {
            Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
            Reaction_Sub(wk, 8, Power_Level);
        }
        break;
    }
}



s32 Check_Exit_DENJIN(PLW* wk) {
    s16 xx;
    WORK* em;
    if (!(DENJIN_Term[wk->wu.id] & 1)) {
        if (CP_Index[wk->wu.id][1] == 0) {
            return 0;
        }
    }
    if ((DENJIN_Term[wk->wu.id] & 8)) {
        if (Attack_Flag[wk->wu.id]) {
            return 1;
        }
    }
    em = (WORK*)wk->wu.target_adrs;
    xx = 0;
    if ((em->xyz[0].disp.pos) == (em->old_pos[0])) {
    } else if (Check_Attack_Direction(wk, em) != 0) {
        xx = -1;
    } else {
        xx = 1;
    }
    if ((DENJIN_Term[wk->wu.id] & 1) && (em->xyz[0].disp.pos != 0)) {
        if (CP_Index[wk->wu.id][2] == 0) {
            CP_Index[wk->wu.id][2]++;
            CP_Index[wk->wu.id][3] = Area_Number[wk->wu.id];
        }
        switch (CP_Index[wk->wu.id][3]) {
        case 0:
        case 1:
        case 2:
            if (em->mvxy.a[1].real.h > 0) {
                return 1;
            }
            if (em->mvxy.a[1].real.h < 0) {
                if (em->xyz[1].disp.pos <= 0x28) {
                    return 1;
                }
            }
            break;
        default:
            if ((em->mvxy.a[1].real.h > 0) && (xx == -1)) {
                return 1;
            }
            if (em->mvxy.a[1].real.h < 0) {
                if (em->xyz[1].disp.pos <= 0x28) {
                    return 1;
                }
            }
            break;
        }
    }
    if (xx == 0) {
        return 0;
    }
    if ((DENJIN_Term[wk->wu.id] & 2) && (xx == 1)) {
        return 1;
    }
    if ((DENJIN_Term[wk->wu.id] & 4) && (xx == -1)) {
        return 1;
    }
    if ((DENJIN_Term[wk->wu.id] & 0x20) && (Lie_Flag[wk->wu.id] == 0)) {
        return 1;
    }
    return 0;
}



void Keep_Away(wk, Target_Pos, Option)
PLW* wk;
s16 Target_Pos;
s16 Option;
{
    switch (CP_Index[wk->wu.id][3]) {
    case 0:
        if (Option == 0) {
            if (random_16_com() < 4) {
                Setup_KA_Jump(wk);
            } else {
                Setup_KA_Walk(wk);
            }
        } else {
            if (Option == 1) {
                Setup_KA_Jump(wk);
            } else {
                CP_Index[wk->wu.id][3] = Option + 1;
            }
        }
    case 1:
    case 2:
        Jump(wk, CP_Index[wk->wu.id][3] - 1);
        break;
    case 3:
    case 4:
        Approach_Walk(wk, Target_Pos, CP_Index[wk->wu.id][3] - 1);
        break;
    }
}



void Setup_KA_Jump(PLW* wk) {
    s16 xx;
    CP_Index[wk->wu.id][3] = 2;
    xx = Back_Jump_Data[wk->player_number];
    if (wk->wu.rl_waza) {
        xx = wk->wu.xyz[0].disp.pos - Back_Jump_Data[wk->player_number];
        if ((bg_w.bgw[1].l_limit2 - bg_w.pos_offset) > xx) {
            CP_Index[wk->wu.id][3] = 1;
        }
    } else {
        xx = wk->wu.xyz[0].disp.pos + Back_Jump_Data[wk->player_number];
        if ((bg_w.bgw[1].r_limit2 + bg_w.pos_offset) < xx) {
            CP_Index[wk->wu.id][3] = 1;
        }
    }
}



void Setup_KA_Walk(PLW* wk) {
    CP_Index[wk->wu.id][3] = 4;
}



void Search_Back_Term(wk, Move_Value, Next_Action, Next_Menu)
PLW* wk;
s16 Move_Value;
s16 Next_Action;
s16 Next_Menu;
{
    if (wk->wu.rl_waza) {
        Move_Value = wk->wu.xyz[0].disp.pos - Move_Value;
        if ((bg_w.bgw[1].l_limit2 - bg_w.pos_offset) > Move_Value) {
            Next_Another_Menu(wk, Next_Action, Next_Menu);
        } else {
            CP_Index[wk->wu.id][0]++;
        }
    } else {
        Move_Value = wk->wu.xyz[0].disp.pos + Move_Value;
        if (((bg_w.bgw[1].r_limit2) + (bg_w.pos_offset)) < (Move_Value)) {
            Next_Another_Menu(wk, Next_Action, Next_Menu);
        } else {
            CP_Index[wk->wu.id][0]++;
        }
    }
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
}



void Approach_Walk(wk, Target_Pos, Option)
PLW* wk;
s16 Target_Pos;
s16 Option;
{
    s16 xx;
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        CP_Index[wk->wu.id][1]++;
        dash_flag_clear(wk->wu.id);
        Timer_00[wk->wu.id] = 120;
    case 1:
        xx = Standing_Timer[wk->wu.id];
        if (Lie_Flag[wk->wu.id] == 0) {
            if (Check_Passive(wk) != 0) {
                break;
            }
        }
        Standing_Timer[wk->wu.id] = xx;
        if (--Timer_00[wk->wu.id] == 0) {
            Next_Be_Free(wk);
        }
        else if (Check_Arrival(wk, Target_Pos, Option) != 0) {
            Disposal_Again[wk->wu.id] = 1;
            CP_Index[wk->wu.id][0]++;
            CP_Index[wk->wu.id][1] = 0;
            CP_Index[wk->wu.id][2] = 0;
            CP_Index[wk->wu.id][3] = 0;
            Flip_Flag[wk->wu.id] = 0;
            Limited_Flag[wk->wu.id] = 0;
            if (CP_No[wk->wu.id][0] != COM_PASSIVE) {
                Passive_Flag[wk->wu.id] = 0;
            }
        } else {
            Ck_Distance_Lv(wk);
            if (Option == 3) {
                Lever_Buff[wk->wu.id] ^= LEVER_LR;
            }
        }
    }
}



s32 Check_Arrival(wk, Target_Pos, Option)
PLW* wk;
s16 Target_Pos;
s16 Option;
{
    if (Option == 3) {
        if (Target_Pos <= PL_Distance[wk->wu.id]) {
            return 1;
        }
        return wk->micchaku_flag;
    }
    if (wk->hos_em_flag) {
        return 1;
    }
    if (Target_Pos >= PL_Distance[wk->wu.id]) {
        return 1;
    }
    return 0;
}



/* provisional name */
void Approach_Until_Landed(wk, Target_Pos)
PLW* wk;
s16 Target_Pos;
{
    WORK* em;
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        CP_Index[wk->wu.id][1]++;
        dash_flag_clear(wk->wu.id);
        Timer_00[wk->wu.id] = 1;
    case 1:
        if (--Timer_00[wk->wu.id] != 0) {
            break;
        }
        if (Target_Pos < PL_Distance[wk->wu.id]) {
            Timer_00[wk->wu.id] = 1;
            Ck_Distance_Lv(wk);
            break;
        }
        em = (WORK*)wk->wu.target_adrs;
        if (em->xyz[1].disp.pos + em->cg_jphos > 0) {
            Timer_00[wk->wu.id] = 20;
            break;
        }
        CP_Index[wk->wu.id][0]++;
        CP_Index[wk->wu.id][1] = 0;
        CP_Index[wk->wu.id][2] = 0;
        CP_Index[wk->wu.id][3] = 0;
        Lever_Buff[wk->wu.id] = 0;
        Flip_Flag[wk->wu.id] = 0;
        Limited_Flag[wk->wu.id] = 0;
        if (CP_No[wk->wu.id][0] != COM_PASSIVE) {
            Passive_Flag[wk->wu.id] = 0;
        }
        break;
    }
}



void Walk(wk, Lever, Time, unused)
PLW* wk;
u16 Lever;
s16 Time;
s16 unused;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        CP_Index[wk->wu.id][1]++;
        dash_flag_clear(wk->wu.id);
        Timer_00[wk->wu.id] = Time;
        Timer_01[wk->wu.id] = wk->wu.rl_flag;
        Free_Lever[wk->wu.id] = Setup_Guard_Lever(wk, Lever);
    case 1:
        if (Lie_Flag[wk->wu.id] == 0) {
            if (Check_Passive(wk) != 0) {
                break;
            }
        }
        if (--Timer_00[wk->wu.id] == 0) {
            CP_Index[wk->wu.id][0]++;
            CP_Index[wk->wu.id][1] = 0;
            CP_Index[wk->wu.id][2] = 0;
            CP_Index[wk->wu.id][3] = 0;
            Flip_Flag[wk->wu.id] = 0;
            Limited_Flag[wk->wu.id] = 0;
            if (*CP_No[wk->wu.id] != 6) {
                Passive_Flag[wk->wu.id] = 0;
            }
        } else {
            if ((Timer_01[wk->wu.id] != (s16)wk->wu.rl_flag) || (wk->micchaku_flag != 0) || (wk->hos_em_flag != 0)) {
                Next_Be_Free(wk);
            }
            Lever_Buff[wk->wu.id] = Free_Lever[wk->wu.id];
        }
        break;
    }
}



void Forced_Guard(wk, Guard_Type)
PLW* wk;
s16 Guard_Type;
{
    WORK* em;
    s16 xx;
    em = (WORK*)wk->wu.target_adrs;
    if (Attack_Flag[wk->wu.id] == 0) {
        Next_Be_Free(wk);
    }
    xx = Hit_Range_Data[em->hit_range];
    xx += Com_Width_Data[wk->wu.id];
    if (PL_Distance[wk->wu.id] > xx) {
        Next_Be_Free(wk);
    }
    Next_Be_Guard(wk, em, Guard_Type);
    Lever_Buff[wk->wu.id] |= Lever_Squat[wk->wu.id];
}




void Normal_Attack(wk, Reaction, Lever_Data)
PLW* wk;
s16 Reaction;
u16 Lever_Data;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Lever_Data & LEVER_DOWN) {
            Lever_LR[wk->wu.id] = Setup_Guard_Lever(wk, 1);
        } else {
            Lever_LR[wk->wu.id] = 0;
        }
        Lever_LR[wk->wu.id] |= Lever_Data & LEVER_DOWN;
        (&Lever_Buff[0])[wk->wu.id] = Lever_LR[wk->wu.id];
        if (Check_Start_Normal_Attack(wk, Lever_Data) != 0) {
            break;
        }
        CP_Index[wk->wu.id][1]++;
        Check_First_Menu(wk);
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id] == 0) {
            CP_Index[wk->wu.id][1]++;
            Lever_Buff[wk->wu.id] = Lever_Data;
            Lever_Buff[wk->wu.id] |= Lever_LR[wk->wu.id];
        } else {
            Lever_Buff[wk->wu.id] |= Lever_LR[wk->wu.id];
        }
        break;
    default:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        Reaction_Sub(wk, Reaction, 0);
        break;
    }
}



s32 Small_Jump_Measure(PLW* wk) {
    if (Lever_Squat[wk->wu.id] & LEVER_DOWN) {
        return Setup_Guard_Lever(wk, 1);
    }
    return 0;
}



void Normal_Attack_SP(wk, Reaction, Lever_Data, Time)
PLW* wk;
s16 Reaction;
u16 Lever_Data;
s16 Time;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Check_Start_Normal_Attack(wk, Lever_Data) != 0) {
            break;
        }
        CP_Index[wk->wu.id][1]++;
        Timer_00[wk->wu.id] = Time;
        Check_First_Menu(wk);
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id] == 0) {
            Lever_Buff[wk->wu.id] = Lever_Data;
            Lever_Squat[wk->wu.id] = Lever_Data & LEVER_DOWN;
            CP_Index[wk->wu.id][1]++;
            Timer_00[wk->wu.id]--;
        } else {
            Lever_Buff[wk->wu.id] = Lever_Squat[wk->wu.id];
        }
        break;
    case 2:
        if (--Timer_00[wk->wu.id]) {
            Lever_Buff[wk->wu.id] = Lever_Data;
            Lever_Squat[wk->wu.id] = Lever_Data & LEVER_DOWN;
        } else {
            CP_Index[wk->wu.id][1]++;
        }
        break;
    default:
        Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        Reaction_Sub(wk, Reaction, 0);
        break;
    }
}



#pragma inline(Check_Squat)

static s32 Check_Squat(wk)
PLW* wk;
{
    if (((WORK*)wk->wu.target_adrs)->pat_status == 32) {
        return 0;
    }
    return 2;
}



void Adjust_Attack(wk, Reaction, Lever_Data)
PLW* wk;
s16 Reaction;
u16 Lever_Data;
{
    u16 xx;
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Check_Start_Normal_Attack(wk, Lever_Data) != 0) {
            break;
        }
        CP_Index[wk->wu.id][1]++;
        Check_First_Menu(wk);
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id] == 0) {
            xx = Check_Squat(wk);
            Lever_Buff[wk->wu.id] = Lever_Data | xx;
            Lever_LR[wk->wu.id] = xx;
            Lever_Buff[wk->wu.id] |= Small_Jump_Measure(wk);
            CP_Index[wk->wu.id][1]++;
        } else {
            (&Lever_Buff[0])[wk->wu.id] = Lever_LR[wk->wu.id];
            Lever_Buff[wk->wu.id] |= Small_Jump_Measure(wk);
        }
        break;
    default:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        Reaction_Sub(wk, Reaction, 0);
        break;
    }
}


/* provisional name */
s32 Check_Target_Pat_Status(WORK* wk) {
    if (((WORK*)wk->target_adrs)->pat_status == 32) {
        return 0;
    }
    return 2;
}



s32 Check_Start_Normal_Attack(PLW* wk, u16 Lever_Data) {
    if ((wk->wu.routine_no[1] != PLAYER_ATTACK) || (wk->wu.cg_type == 0x40)) {
        return 0;
    }
    if (wk->wu.cg_cancel & 4) {
        return 0;
    }
    if (wk->permited_koa & 0x10) {
        return 0;
    }
    return 1;
}



void Lever_Attack(wk, Reaction, Lever, Lever_Data)
PLW* wk;
s16 Reaction;
u16 Lever;
u16 Lever_Data;
{
    s16 xx;
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Check_Start_Lever_Attack(wk, Lever, Lever_Data) != 0) {
            break;
        }
        dash_flag_clear(wk->wu.id);
        CP_Index[wk->wu.id][1]++;
        Check_First_Menu(wk);
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id]) {
            break;
        }
        xx = Setup_Guard_Lever(wk, Lever);
        Lever_Buff[wk->wu.id] = (Lever_Data | xx);
        CP_Index[wk->wu.id][1]++;
        break;
    default:
        if (wk->wu.routine_no[1] == PLAYER_CATCH) {
            Be_Catch(wk);
        } else {
            Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
            Reaction_Sub(wk, Reaction, 0);
        }
        break;
    }
}




s32 Setup_Guard_Lever(PLW* wk, u16 Lever) {
    if (Lever == 0) {
        if (wk->wu.rl_waza == 0) {
            return 4;
        }
        return 8;
    }
    if (wk->wu.rl_waza == 1) {
        return 4;
    }
    return 8;
}



s32 Check_Start_Lever_Attack(wk, Lever, Lever_Data)
PLW* wk;
u16 Lever;
u16 Lever_Data;
{
    u16 dir;
    u16 idx;
    if ((wk->wu.routine_no[1] != PLAYER_ATTACK) || (wk->wu.cg_type == 0x40)) {
        return 0;
    }
    if (wk->wu.cg_cancel & 4) {
        return 0;
    }
    if (wk->wu.cg_cancel & 8) {
        dir = wk->wu.cg_eftype & 0xC;
        if (dir == 0) {
            return 1;
        }
        if (Lever == 0 && dir != 8) {
            return 1;
        }
        if (Lever == 1 && dir != 4) {
            return 1;
        }
        idx = (wk->wu.cg_eftype & 0x70) >> 4;
        dir |= cancel_shot_tbl[0][idx];
        if (dir == Lever_Data) {
            return 0;
        }
    }
    return 1;
}



void SA_Term(wk, SA0, SA1, SA2, Term_No)
PLW* wk;
u16 SA0;
u16 SA1;
u16 SA2;
u16 Term_No;
{
    s16 xx[3];
    if (((Passive_Flag[wk->wu.id]) == 0) && (Check_Passive(wk) != 0)) {
        return;
    }
    xx[0] = SA0;
    xx[1] = SA1;
    xx[2] = SA2;
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    if (xx[plw[wk->wu.id].sa->kind_of_arts] == -1) {
        CP_Index[wk->wu.id][0]++;
    } else if (plw[wk->wu.id].sa->ok) {
        Disposal_Again[wk->wu.id] = 1;
        if ((Term_No != -1) || (Term_No != 0)) {
            switch (My_char[wk->wu.id]) {
            case PL_RYU:
                if (SA_Range_Check(wk, 1, Term_No) != 0) {
                    return;
                }
                DENJIN_Check(wk, SA2, &xx[2], Term_No);
                Next_Another_Menu(wk, 2, xx[plw[wk->wu.id].sa->kind_of_arts]);
                return;
            case PL_KEN:
                if (SA_Range_Check(wk, 1, Term_No) != 0) {
                    return;
                }
                Next_Another_Menu(wk, 2, xx[plw[wk->wu.id].sa->kind_of_arts]);
                return;
            case PL_ALEX:
                if (SA_Range_Check(wk, 1, Term_No) != 0) {
                    return;
                }
                Next_Another_Menu(wk, 2, xx[plw[wk->wu.id].sa->kind_of_arts]);
                return;
                break;
            case PL_NECRO:
                if (((WORK*)wk->wu.target_adrs)->xyz[1].disp.pos >= 0x10) {
                    CP_Index[wk->wu.id][0]++;
                    return;
                }
                if (SA_Range_Check(wk, 1, Term_No) != 0) {
                    return;
                }
                Next_Another_Menu(wk, 2, xx[plw[wk->wu.id].sa->kind_of_arts]);
                return;
            case PL_ORO:
                YAGYOU_Check(wk, &xx[1], Term_No);
                Next_Another_Menu(wk, 2, xx[plw[wk->wu.id].sa->kind_of_arts]);
                return;
            }
        }
        Next_Another_Menu(wk, 2, xx[plw[wk->wu.id].sa->kind_of_arts]);
    } else {
        CP_Index[wk->wu.id][0]++;
    }
}



s32 DENJIN_Check(wk, SA2, xx, Term_No)
PLW* wk;
u16 SA2;
s16* xx;
u16 Term_No;
{
    if (plw[wk->wu.id].sa->kind_of_arts != 2) {
        return;
    }
    DENJIN_No[wk->wu.id] = Term_No;
    DENJIN_Term[wk->wu.id] = SA2;
    xx[0] = 0x37;
    return 1;
}



s32 YAGYOU_Check(wk, xx, Term_No)
PLW* wk;
s16* xx;
u16 Term_No;
{
    if (plw[wk->wu.id].sa->kind_of_arts != 1) {
        return;
    }
    if (Term_No == 0) {
        Term_No = YAGYOU_Data[random_16_com()];
        Term_No += 0x36;
    }
    xx[0] = Term_No;
    return 1;
}



s32 SA_Range_Check(wk, SA_No, Range)
PLW* wk;
u16 SA_No;
u16 Range;
{
    if (plw[wk->wu.id].sa->kind_of_arts != SA_No) {
        return 0;
    }
    if (PL_Distance[wk->wu.id] > Range) {
        CP_Index[wk->wu.id][0]++;
        return 1;
    }
    return 0;
}



void Check_SA(wk, Next_Action, Next_Menu)
PLW* wk;
s16 Next_Action;
s16 Next_Menu;
{
    if (plw[wk->wu.id].sa->ok) {
        CP_Index[wk->wu.id][0]++;
    } else {
        CP_No[wk->wu.id][0] = Next_Action;
        Disposal_Again[wk->wu.id] = 1;
        Next_Another_Menu(wk, Next_Action, Next_Menu);
    }
}





/* provisional name */
void Check_SA_Range(wk, SA_No, Range, Next_Action, Next_Menu)
PLW* wk;
s16 SA_No;
s16 Range;
s16 Next_Action;
s16 Next_Menu;
{
    Disposal_Again[wk->wu.id] = 1;
    if (plw[wk->wu.id].sa->kind_of_arts == SA_No) {
        if (PL_Distance[wk->wu.id] > Range) {
            CP_No[wk->wu.id][0] = Next_Action;
            Next_Another_Menu(wk, Next_Action, Next_Menu);
        }
    }
}



void Branch_Unit_Area(wk, Next_Action, Menu_00, Menu_01, Menu_02, Menu_03)
PLW* wk;
s16 Next_Action;
s16 Menu_00;
s16 Menu_01;
s16 Menu_02;
s16 Menu_03;
{
    s16 xx[4];
    CP_No[wk->wu.id][0] = Next_Action;
    xx[0] = Menu_00;
    xx[1] = Menu_01;
    xx[2] = Menu_02;
    xx[3] = Menu_03;
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    Disposal_Again[wk->wu.id] = 1;
    Next_Another_Menu(wk, Next_Action, xx[Area_Number[wk->wu.id]]);
}



void Com_Random_Select(wk, Next_Action, Menu_00, Menu_01, Menu_02, Menu_03, Rnd_Type)
PLW* wk;
s16 Next_Action;
s16 Menu_00;
s16 Menu_01;
s16 Menu_02;
s16 Menu_03;
s16 Rnd_Type;
{
    s16 xx[4];
    s16 zz;
    zz = Com_Rnd_Select_Data[Rnd_Type][random_16_com()];
    xx[0] = Menu_00;
    xx[1] = Menu_01;
    xx[2] = Menu_02;
    xx[3] = Menu_03;
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    if (xx[zz] == 0xFF) {
        Next_End(wk);
    } else {
        Disposal_Again[wk->wu.id] = 1;
        Next_Another_Menu(wk, Next_Action, xx[zz]);
    }
}



void Branch_Wait_Area(wk, Time_00, Time_01, Time_02, Time_03)
PLW* wk;
s16 Time_00;
s16 Time_01;
s16 Time_02;
s16 Time_03;
{
    s16 xx[4];
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        CP_Index[wk->wu.id][1]++;
        xx[0] = Time_00;
        xx[1] = Time_01;
        xx[2] = Time_02;
        xx[3] = Time_03;
        Timer_00[wk->wu.id] = xx[Area_Number[wk->wu.id]];
        break;
    default:
        if (--Timer_00[wk->wu.id]) {
            break;
        }
        CP_Index[wk->wu.id][0]++;
        CP_Index[wk->wu.id][1] = 0;
        CP_Index[wk->wu.id][2] = 0;
        CP_Index[wk->wu.id][3] = 0;
        Flip_Flag[wk->wu.id] = 0;
        Limited_Flag[wk->wu.id] = 0;
        if (CP_No[wk->wu.id][0] != COM_PASSIVE) {
            Passive_Flag[wk->wu.id] = 0;
        }
        break;
    }
}



void Wait(wk, Time)
PLW* wk;
s16 Time;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        CP_Index[wk->wu.id][1]++;
        if (Time == 0) {
            Timer_00[wk->wu.id] = Setup_WT_Data(wk);
        } else {
            Timer_00[wk->wu.id] = Time;
        }
        break;
    default:
        if (--Timer_00[wk->wu.id] == 0) {
            CP_Index[wk->wu.id][0]++;
            CP_Index[wk->wu.id][1] = 0;
            CP_Index[wk->wu.id][2] = 0;
            CP_Index[wk->wu.id][3] = 0;
            Flip_Flag[wk->wu.id] = 0;
            Limited_Flag[wk->wu.id] = 0;
            if (CP_No[wk->wu.id][0] != COM_PASSIVE) {
                Passive_Flag[wk->wu.id] = 0;
            }
        }
        break;
    }
}



void Look(wk, Time)
PLW* wk;
s16 Time;
{
    s16* tm = Timer_00;
    Passive_Flag[wk->wu.id] = 0;
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        if (Check_Passive(wk) == 0) {
            CP_Index[wk->wu.id][1]++;
            if (Time == 0) {
                tm[wk->wu.id] = Setup_LP_Data(wk);
            } else {
                tm[wk->wu.id] = Time;
            }
        }
        break;
    default:
        if (Check_Passive(wk) == 0 && --tm[wk->wu.id] == 0) {
            CP_Index[wk->wu.id][0]++;
            CP_Index[wk->wu.id][1] = 0;
            CP_Index[wk->wu.id][2] = 0;
            CP_Index[wk->wu.id][3] = 0;
            Flip_Flag[wk->wu.id] = 0;
            Limited_Flag[wk->wu.id] = 0;
            Before_Look[wk->wu.id] = 1;
        }
        break;
    }
}



void Keep_Status(wk, Lever_Data, Option_Data)
PLW* wk;
u16 Lever_Data;
s16 Option_Data;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        CP_Index[wk->wu.id][1]++;
        dash_flag_clear(wk->wu.id);
        Timer_00[wk->wu.id] = 10;
        Free_Lever[wk->wu.id] = Lever_Data;
        if (Option_Data != -1) {
            Free_Lever[wk->wu.id] |= Setup_Guard_Lever(wk, Option_Data);
        }
        Lever_Buff[wk->wu.id] = Free_Lever[wk->wu.id];
        break;
    default:
        Lever_Buff[wk->wu.id] = Free_Lever[wk->wu.id];
        if (--Timer_00[wk->wu.id]) {
            break;
        }
        Timer_00[wk->wu.id] = 1;
        if (Attack_Flag[wk->wu.id] == 0) {
            CP_Index[wk->wu.id][0]++;
            CP_Index[wk->wu.id][1] = 0;
            CP_Index[wk->wu.id][2] = 0;
            CP_Index[wk->wu.id][3] = 0;
            Flip_Flag[wk->wu.id] = 0;
            Limited_Flag[wk->wu.id] = 0;
            if (CP_No[wk->wu.id][0] != COM_PASSIVE) {
                Passive_Flag[wk->wu.id] = 0;
            }
        }
        break;
    }
}



/* No final return: the routine's result is only read when Check_Guard succeeded (return 1). */
s32 VS_Jump_Guard(PLW* wk) {
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        if (Check_Guard(wk)) {
            return 1;
        }
        dash_flag_clear(wk->wu.id);
        CP_Index[wk->wu.id][1]++;
        break;
    default:
        if (Check_Guard(wk)) {
            return 1;
        }
        if (((WORK*)wk->wu.target_adrs)->xyz[1].disp.pos <= 0x18) {
            CP_Index[wk->wu.id][0]++;
            CP_Index[wk->wu.id][1] = 0;
            CP_Index[wk->wu.id][2] = 0;
            CP_Index[wk->wu.id][3] = 0;
            Passive_Flag[wk->wu.id] = 0;
            Flip_Flag[wk->wu.id] = 0;
            Limited_Flag[wk->wu.id] = 0;
        }
        break;
    }
}



void Wait_Lie(wk, Lever_Data)
PLW* wk;
u16 Lever_Data;
{
    WORK* em;
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        CP_Index[wk->wu.id][1]++;
        dash_flag_clear(wk->wu.id);
        Rolling_Flag[wk->wu.id] = 0;
        if (Lever_Data != 0) {
            Free_Lever[wk->wu.id] = Setup_Guard_Lever(wk, 1);
            Free_Lever[wk->wu.id] |= Lever_Data & LEVER_DOWN;
        } else {
            Free_Lever[wk->wu.id] = 0;
        }
    default:
        Lever_Buff[wk->wu.id] = Free_Lever[wk->wu.id];
        em = (WORK*)wk->wu.target_adrs;
        if ((Check_Blow_Off(wk, em, 0) == 0) || (Lie_Flag[wk->wu.id] != 0)) {
            CP_Index[wk->wu.id][0]++;
            CP_Index[wk->wu.id][1] = 0;
            CP_Index[wk->wu.id][2] = 0;
            CP_Index[wk->wu.id][3] = 0;
            Flip_Flag[wk->wu.id] = 0;
            Limited_Flag[wk->wu.id] = 0;
        }
        break;
    }
}



void Wait_Get_Up(wk, Lever_Data, Option)
PLW* wk;
u16 Lever_Data;
s16 Option;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        CP_Index[wk->wu.id][1]++;
        dash_flag_clear(wk->wu.id);
        Rolling_Flag[wk->wu.id] = 0;
        if (Lever_Data != 0) {
            Lever_LR[wk->wu.id] = Setup_Guard_Lever(wk, 1);
            Lever_LR[wk->wu.id] |= Lever_Data & LEVER_DOWN;
        } else {
            Lever_LR[wk->wu.id] = 0;
        }
    default:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        if (Check_Wait_Term(wk, Option) != 0) {
            CP_Index[wk->wu.id][0]++;
            CP_Index[wk->wu.id][1] = 0;
            CP_Index[wk->wu.id][2] = 0;
            CP_Index[wk->wu.id][3] = 0;
            Disposal_Again[wk->wu.id] = 1;
            Passive_Flag[wk->wu.id] = 1;
            Flip_Flag[wk->wu.id] = 0;
            Limited_Flag[wk->wu.id] = 0;
        }
        break;
    }
}



s32 Check_Wait_Term(wk, Option)
PLW* wk;
s16 Option;
{
    WORK* em;
    em = (WORK*)wk->wu.target_adrs;
    if (em->routine_no[1] == PLAYER_DAMAGE && em->pat_status == 24) {
        return 0;
    }
    if (Lie_Flag[wk->wu.id] == 0) {
        return 1;
    }
    if (Option != 0) {
        return 0;
    }
    if (em->cg_type == 0xB) {
        return 1;
    }
    return 0;
}



void Wait_Attack_Complete(wk, Lever_Data, Option)
PLW* wk;
u16 Lever_Data;
s16 Option;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        CP_Index[wk->wu.id][1]++;
        dash_flag_clear(wk->wu.id);
        if (Lever_Data != 0) {
            Lever_LR[wk->wu.id] = Setup_Guard_Lever(wk, 1);
            Lever_LR[wk->wu.id] |= Lever_Data & LEVER_DOWN;
            Guard_Flag[wk->wu.id] = 1;
        } else {
            Lever_LR[wk->wu.id] = 0;
        }
    }
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    {
        s32 k = Option;
        if (!Check_Exit_Guard(wk, k)) {
            CP_Index[wk->wu.id][0]++;
            CP_Index[wk->wu.id][1] = 0;
            CP_Index[wk->wu.id][2] = 0;
            CP_Index[wk->wu.id][3] = 0;
            Guard_Flag[wk->wu.id] = 0;
            Flip_Flag[wk->wu.id] = 0;
            Limited_Flag[wk->wu.id] = 0;
            if (!k) {
                Passive_Flag[wk->wu.id] = 0;
            }
        }
    }
}



s32 Check_Exit_Guard(wk, Option)
PLW* wk;
s16 Option;
{
    WORK* em;
    if (wk->wu.routine_no[1] == PLAYER_DAMAGE) {
        return 1;
    }
    if (Option == 0) {
        em = (WORK*)wk->wu.target_adrs;
        if (em->routine_no[1] != PLAYER_ATTACK) {
            return 0;
        }
        return 1;
    }
    return Attack_Flag[wk->wu.id];
}



void Short_Range_Attack(wk, Reaction, Lever_Data, Next_Action, Next_Menu)
PLW* wk;
s16 Reaction;
u16 Lever_Data;
s16 Next_Action;
s16 Next_Menu;
{
    u16 xx;
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Check_Start_Normal_Attack(wk, Lever_Data) == 0) {
            CP_Index[wk->wu.id][1]++;
            Check_First_Menu(wk);
            Ck_Distance_LvJ(wk);
            xx = get_nearing_range(wk->player_number, xx = Lever_Data & 0x7F0);
            if (PL_Distance[wk->wu.id] > xx) {
                Next_Another_Menu(wk, Next_Action, Next_Menu);
            }
        }
        break;
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id]) {
            break;
        }
        Lever_Buff[wk->wu.id] = Lever_Data;
        CP_Index[wk->wu.id][1]++;
        break;
    default:
        Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        Reaction_Sub(wk, Reaction, 0);
        break;
    }
}



void EM_Term(wk, Range_X, Range_Y, Exit_Number, Next_Action, Next_Menu)
PLW* wk;
s16 Range_X;
s16 Range_Y;
s16 Exit_Number;
s16 Next_Action;
s16 Next_Menu;
{
    WORK* em;
    em = (WORK*)wk->wu.target_adrs;
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        CP_Index[wk->wu.id][1]++;
        Term_No[wk->wu.id] = TERM_INIT;
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        switch (Check_Exit_Term(wk, em, Exit_Number)) {
        case 0:
            if (Check_Term_Sub(wk, PL_Distance[wk->wu.id], Range_X) == 0) {
                break;
            }
            if (Check_Term_Sub_Y(wk, em->xyz[1].disp.pos, Range_Y) == 0) {
                break;
            }
            Disposal_Again[wk->wu.id] = 1;
            CP_Index[wk->wu.id][0]++;
            CP_Index[wk->wu.id][1] = 0;
            CP_Index[wk->wu.id][2] = 0;
            CP_Index[wk->wu.id][3] = 0;
            Flip_Flag[wk->wu.id] = 0;
            Limited_Flag[wk->wu.id] = 0;
            break;
        case 1:
            Disposal_Again[wk->wu.id] = 1;
            Next_Another_Menu(wk, Next_Action, Next_Menu);
            break;
        case 2:
            break;
        case 3:
            Select_Passive(wk);
            break;
        default:
            Counter_Attack[wk->wu.id] = 1;
            Select_Passive(wk);
            break;
        }
        break;
    }
}



void SHELL_Term(wk, Next_Command, Exit_Number, Next_Action, Next_Menu, unused)
PLW* wk;
s16 Next_Command;
s16 Exit_Number;
s16 Next_Action;
s16 Next_Menu;
s16 unused;
{
    WORK* em;
    WORK_Other* tmw;
    s16 xx;
    em = (WORK*)Shell_Address[wk->wu.id];
    tmw = (WORK_Other*)Shell_Address[wk->wu.id];
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        CP_Index[wk->wu.id][1]++;
        Term_No[wk->wu.id] = TERM_INIT;
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Check_Exit_Term(wk, em, Exit_Number) == -1) {
            Next_Another_Menu(wk, Next_Action, Next_Menu);
        } else {
            xx = Compute_Hit_Time(wk, tmw);
            if (xx < Shell_Dodge_Data[Next_Command][wk->player_number]) {
                Disposal_Again[wk->wu.id] = 1;
                CP_Index[wk->wu.id][0]++;
                CP_Index[wk->wu.id][1] = 0;
                CP_Index[wk->wu.id][2] = 0;
                CP_Index[wk->wu.id][3] = 0;
                Flip_Flag[wk->wu.id] = 0;
                Limited_Flag[wk->wu.id] = 0;
            }
        }
        break;
    }
}




s32 Check_Term_Sub(PLW* wk, s16 Distance, s16 Range) {
    if (Range == -1) {
        return 1;
    }
    if (!(Range & 0x8000)) {
        if (Distance >= Range) {
            return 1;
        }
        return 0;
    } else {
        if (Distance <= (Range & 0x7FFF)) {
            return 1;
        }
        return 0;
    }
}




s32 Check_Term_Sub_Y(wk, Distance, Range)
PLW* wk;
s16 Distance;
s16 Range;
{
    WORK* em;
    if (Range == -1) {
        return 1;
    }
    em = (WORK*)wk->wu.target_adrs;
    if (!(Range & 0x8000)) {
        if (Distance >= Range) {
            return 1;
        }
        return 0;
    } else {
        if (em->mvxy.a[1].real.h > 0) {
            return 0;
        }
        if (Distance <= (Range & 0x7FFF)) {
            return 1;
        }
        return 0;
    }
}



void Jump(wk, Jump_Dir)
PLW* wk;
s16 Jump_Dir;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        if (Check_Passive(wk) != 0) {
            break;
        }
        if ((wk->wu.routine_no[1] != PLAYER_ATTACK) || (wk->wu.cg_type == 0x40)) {
            CP_Index[wk->wu.id][1]++;
            hi_jump_flag_clear(wk->wu.id);
            Check_First_Menu(wk);
        }
        break;
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id] != 0) {
            break;
        }
        CP_Index[wk->wu.id][1]++;
        Jump_Init(wk, Jump_Dir);
        Check_Air_Guard(wk);
        break;
    case 2:
        Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
        if (wk->wu.xyz[1].disp.pos > 0) {
            CP_Index[wk->wu.id][1]++;
            Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        }
        break;
    default:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        Lever_Buff[wk->wu.id] |= Air_Guard_Lever(wk);
        if (wk->wu.xyz[1].disp.pos) {
            break;
        }
        CP_Index[wk->wu.id][0]++;
        CP_Index[wk->wu.id][1] = 0;
        CP_Index[wk->wu.id][2] = 0;
        CP_Index[wk->wu.id][3] = 0;
        break;
    }
}



void Hi_Jump(wk, Pl_Number, Jump_Dir)
PLW* wk;
s16 Pl_Number;
s16 Jump_Dir;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Check_Start_Hi_Jump(wk) == 0) {
            CP_Index[wk->wu.id][1]++;
            Tech_Address[wk->wu.id] = player_cmd[Pl_Number][2];
            Check_First_Menu(wk);
        }
        break;
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id] != 0) {
            break;
        }
        CP_Index[wk->wu.id][1]++;
        Tech_Index[wk->wu.id] = 0xC;
        Jump_Init(wk, Jump_Dir);
        Lever_Pool[wk->wu.id] &= LEVER_LR;
        Lever_Buff[wk->wu.id] = 0;
        Check_Air_Guard(wk);
        break;
    case 2:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Command_Type_00(wk, 8, -1) == -1) {
            CP_Index[wk->wu.id][1]++;
            Lever_Buff[wk->wu.id] |= Lever_Pool[wk->wu.id];
            break;
        }
        if (!(Lever_Buff[wk->wu.id] & LEVER_DOWN)) {
            Lever_Buff[wk->wu.id] |= Lever_Pool[wk->wu.id];
        }
        break;
    case 3:
        Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
        if (wk->wu.xyz[1].disp.pos > 0) {
            CP_Index[wk->wu.id][1]++;
            Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        }
        break;
    default:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        Lever_Buff[wk->wu.id] |= Air_Guard_Lever(wk);
        if (wk->wu.xyz[1].disp.pos) {
            break;
        }
        CP_Index[wk->wu.id][0]++;
        CP_Index[wk->wu.id][1] = 0;
        CP_Index[wk->wu.id][2] = 0;
        CP_Index[wk->wu.id][3] = 0;
        break;
    }
}


s32 Check_Start_Hi_Jump(PLW* wk) {
    if ((wk->wu.routine_no[1] != PLAYER_ATTACK) || (wk->wu.cg_type == 0x40)) {
        return 0;
    }
    if (wk->wu.cg_cancel & 4) {
        return 0;
    }
    if (wk->wu.cg_cancel & 1) {
        return 0;
    }
    return 1;
}



/* provisional name: the air guard lever while the jump lasts */
s32 Air_Guard_Lever(PLW* wk) {
    switch (Air_Guard_Type[wk->wu.id]) {
    case 0:
        return 0;
    case 1:
        if (Attack_Flag[wk->wu.id] == 0) {
            return 0;
        }
        if (--Timer_01[wk->wu.id]) {
            return 0;
        }
        Timer_01[wk->wu.id] = 11;
        return Free_Lever[wk->wu.id];
    default:
        if (Attack_Flag[wk->wu.id] == 0) {
            return 0;
        }
        if (--Timer_01[wk->wu.id]) {
            return 0;
        }
        Timer_01[wk->wu.id] = 15;
        return Free_Lever[wk->wu.id];
    }
}



/* decides the air guard when the jump starts */
s32 Check_Air_Guard(PLW* wk) {
    Free_Lever[wk->wu.id] = 0;
    if (Lever_LR) {
        return;
    }
    Lv = Setup_Lv10(0);
    if ((Demo_Flag == 0) && (Weak_PL == wk->wu.id)) {
        Lv = 2;
    }
    Rnd = random_16_com();
    Air_Guard_Type[wk->wu.id] = Air_Guard_Data[wk->player_number][Lv][Rnd];
    if (Air_Guard_Type[wk->wu.id] == 0) {
        return 0;
    }
    Timer_01[wk->wu.id] = 1;
    Free_Lever[wk->wu.id] = Setup_Guard_Lever(wk, Air_Guard_Type[wk->wu.id] - 1);
    return 1;
}




/* provisional name */
void Jump_Air_Guard(wk, Lever)
PLW* wk;
s16 Lever;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (wk->wu.routine_no[1] == PLAYER_ATTACK && wk->wu.cg_type != 64) {
            break;
        }
        CP_Index[wk->wu.id][1]++;
        Free_Lever[wk->wu.id] = Setup_Guard_Lever(wk, Lever);
    case 1:
        Lever_Buff[wk->wu.id] = Free_Lever[wk->wu.id] | 1;
        if (wk->wu.xyz[1].disp.pos > 0) {
            CP_Index[wk->wu.id][1]++;
        }
        break;
    default:
        if (wk->wu.xyz[1].disp.pos) {
            break;
        }
        Lever_Buff[wk->wu.id] = 0;
        CP_Index[wk->wu.id][0]++;
        CP_Index[wk->wu.id][1] = 0;
        CP_Index[wk->wu.id][2] = 0;
        CP_Index[wk->wu.id][3] = 0;
        break;
    }
}



void Jump_Attack(wk, Reaction, Time_Data, Lever_Data, Jump_Dir)
PLW* wk;
s16 Reaction;
s16 Time_Data;
u16 Lever_Data;
s16 Jump_Dir;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        Setup_Lever_LR(wk, wk->wu.id, Reaction & 0xF000);
        if (Check_Passive(wk) != 0) {
            break;
        }
        if ((wk->wu.routine_no[1] == PLAYER_ATTACK) && (wk->wu.cg_type != 0x40)) {
            break;
        }
        CP_Index[wk->wu.id][1]++;
        Timer_00[wk->wu.id] = Time_Data;
        Continue_Menu[wk->wu.id] = 0;
        wk->wu.hf.hit.player = 0;
        hi_jump_flag_clear(wk->wu.id);
        Check_First_Menu(wk);
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id] != 0) {
            break;
        } else {
            Timer_00[wk->wu.id] = Time_Data;
            CP_Index[wk->wu.id][1]++;
            dash_flag_clear(wk->wu.id);
            Jump_Init(wk, Jump_Dir);
            Check_Air_Guard(wk);
            break;
        }
    case 2:
        if (wk->wu.xyz[1].disp.pos > 0) {
            CP_Index[wk->wu.id][1]++;
        }
        else {
            Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
        }
        break;
    case 3:
        Lever_Buff[wk->wu.id] |= Air_Guard_Lever(wk);
        if (--Timer_00[wk->wu.id] != 0) {
            break;
        }
        Lever_Data = Check_SP_Jump_Attack(wk, Lever_Data);
        Lever_Buff[wk->wu.id] = Lever_Data;
        CP_Index[wk->wu.id][1]++;
        break;
    default:
        if (wk->wu.hf.hit.player) {
            Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        }
        Check_Landed(wk, Reaction & 0xFFF);
        break;
    }
    Lever_Buff[wk->wu.id] |= Lever_LR[wk->wu.id];
}



void Jump_Attack_Term(wk, Range_X, Range_Y, Reaction, Lever_Data, Jump_Dir, Range_JX, Range_JY, J_Lever_Data)
PLW* wk;
s16 Range_X;
s16 Range_Y;
s16 Reaction;
u16 Lever_Data;
s16 Jump_Dir;
s16 Range_JX;
s16 Range_JY;
s16 J_Lever_Data;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        Setup_Lever_LR(wk, wk->wu.id, Reaction & 0xF000);
        if ((wk->wu.routine_no[1] == PLAYER_ATTACK) && (wk->wu.cg_type != 0x40)) {
            break;
        }
        hi_jump_flag_clear(wk->wu.id);
        Continue_Menu[wk->wu.id] = 0;
        wk->wu.hf.hit.player = 0;
        CP_Index[wk->wu.id][1]++;
        Check_First_Menu(wk);
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id] == 0) {
            CP_Index[wk->wu.id][1]++;
            dash_flag_clear(wk->wu.id);
            Jump_Init(wk, Jump_Dir);
            Check_Air_Guard(wk);
        }
        break;
    case 2:
        if (wk->wu.xyz[1].disp.pos > 0) {
            CP_Index[wk->wu.id][1]++;
        } else {
            Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
        }
        break;
    case 3:
        Lever_Buff[wk->wu.id] |= Air_Guard_Lever(wk);
        if (Check_Landed(wk, Reaction) != 0) {
            break;
        }
        if (Check_VS_Air_Attack(wk, Range_JX, Range_JY, J_Lever_Data) != 0) {
            break;
        }
        if (Check_Term_ABS_Distance(wk) == 0) {
            if (Turn_Over[wk->wu.id]) {
                Range_Y = -1;
                Range_X = Distance_XX_Index[wk->wu.id];
            }
            if (Check_Term_Sub(wk, PL_Distance[wk->wu.id], Range_X) == 0) {
                break;
            }
            if (Check_Com_Add_Y(wk, wk->wu.xyz[1].disp.pos, Range_Y) == 0) {
                break;
            }
            if (Check_Term_Sub(wk, wk->wu.xyz[1].disp.pos, Range_Y) == 0) {
                break;
            }
        }
        Lever_Data = Check_SP_Jump_Attack(wk, Lever_Data);
        Lever_Buff[wk->wu.id] = Lever_Data;
        CP_Index[wk->wu.id][1]++;
        Stock_Hit_Flag[wk->wu.id] = 0;
        break;
    case 4:
        if (wk->wu.hf.hit.player) {
            Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        }
        if (Check_Landed(wk, Reaction) != 0) {
            break;
        }
        break;
    case 5:
        if (Check_Landed(wk, Reaction) == 0) {
            switch (Tech_Address[wk->wu.id][Tech_Index[wk->wu.id]]) {
            case 1:
            case 10:
            default:
                if (Command_Type_00(wk, 8, -1) == -1) {
                    CP_Index[wk->wu.id][1] = 0x63;
                }
                break;
            }
        }
        break;
    default:
        Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        Check_Landed(wk, Reaction & 0xFFF);
        break;
    }
    Lever_Buff[wk->wu.id] |= Lever_LR[wk->wu.id];
}



s32 Check_SP_Jump_Attack(wk, Lever_Data)
PLW* wk;
s16 Lever_Data;
{
    u16 xx;
    if (!(Lever_Data & 0x8000)) {
        return Lever_Data;
    }
    xx = Setup_Guard_Lever(wk, 0);
    xx |= Lever_Data & 0x7FFF;
    return xx | 2;
}



s32 Check_VS_Air_Attack(PLW* wk, s16 Range_JX, s16 Range_JY, s16 J_Lever_Data) {
    WORK* em;
    if ((Range_JX == -1) && (Range_JY == -1)) {
        return 0;
    }
    em = (WORK*)wk->wu.target_adrs;
    if ((em->pat_status != 14) && (em->pat_status != 20) && (em->pat_status != 26) && (em->xyz[1].disp.pos <= 0)) {
        return 0;
    }
    if (Check_Term_Sub(wk, PL_Distance[wk->wu.id], Range_JX) == 0) {
        return 0;
    }
    if (Check_Term_Sub(wk, Ck_Distance_Height(wk), Range_JY) != 0) {
        switch (CP_Index[wk->wu.id][2]) {
        case 0:
            CP_Index[wk->wu.id][2]++;
            Timer_01[wk->wu.id] = Select_Reflection_Time(wk);
            Timer_01[wk->wu.id]++;
            break;
        default:
            if (--Timer_01[wk->wu.id] != 0) {
                break;
            }
            if (J_Lever_Data & 0x4000) {
                CP_Index[wk->wu.id][1] += 2;
                Tech_Address[wk->wu.id] = player_cmd[wk->player_number][J_Lever_Data & 0x3FFF];
                Continue_Menu[wk->wu.id] = 1;
                return -1;
            }
            Lever_Buff[wk->wu.id] = J_Lever_Data;
            CP_Index[wk->wu.id][1]++;
            Continue_Menu[wk->wu.id] = 1;
            return 1;
        }
    }
    return 0;
}



void Hi_Jump_Attack(wk, Reaction, Time_Data, Lever_Data, Jump_Dir)
PLW* wk;
s16 Reaction;
s16 Time_Data;
u16 Lever_Data;
s16 Jump_Dir;
{
    u16 lever;
    u16 idx;
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        Setup_Lever_LR(wk, wk->wu.id, Reaction & 0xF000);
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Check_Start_Hi_Jump(wk) == 0) {
            Continue_Menu[wk->wu.id] = 0;
            wk->wu.hf.hit.player = 0;
            CP_Index[wk->wu.id][1]++;
            Tech_Address[wk->wu.id] = player_cmd[wk->player_number][2];
            Timer_00[wk->wu.id] = Time_Data;
            Check_First_Menu(wk);
        }
        break;
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id] != 0) {
            break;
        } else {
            CP_Index[wk->wu.id][1]++;
            Tech_Index[wk->wu.id] = 0xC;
            dash_flag_clear(wk->wu.id);
            Jump_Init(wk, Jump_Dir);
            Lever_Pool[wk->wu.id] &= LEVER_LR;
            Lever_Buff[wk->wu.id] = 0;
            Check_Air_Guard(wk);
            break;
        }
    case 2:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Command_Type_00(wk, 8, -1) == -1) {
            CP_Index[wk->wu.id][1]++;
            Lever_Buff[wk->wu.id] |= Lever_Pool[wk->wu.id];
            break;
        }
        if (Lever_Buff[wk->wu.id] & LEVER_DOWN) {
            return;
        }
        Lever_Buff[wk->wu.id] |= Lever_Pool[wk->wu.id];
        break;
    case 3:
        if (wk->wu.xyz[1].disp.pos > 0) {
            CP_Index[wk->wu.id][1]++;
        }
        else {
            Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id] | 1;
        }
        break;
    case 4:
        Lever_Buff[wk->wu.id] |= Air_Guard_Lever(wk);
        if (--Timer_00[wk->wu.id] != 0) {
            break;
        }
        Lever_Data = Check_SP_Jump_Attack(wk, (s16)Lever_Data);
        Lever_Buff[wk->wu.id] = Lever_Data;
        CP_Index[wk->wu.id][1] += 2;
        if (Reaction & 0x80) {
            CP_Index[wk->wu.id][1]++;
        }
        break;
    case 6:
        if (Attack_Flag[wk->wu.id]) {
            break;
        }
        CP_Index[wk->wu.id][1]++;
        if (wk->wu.hf.hit.player == 0) {
            break;
        }
        if (!(wk->wu.cg_cancel & 8)) {
            break;
        }
        lever = wk->wu.cg_eftype & 0xC;
        if (lever) {
            lever = Setup_Guard_Lever(wk, lever >> 3);
        }
        lever |= wk->wu.cg_eftype & 3;
        idx = (wk->wu.cg_eftype & 0x70) >> 4;
        lever |= cancel_shot_tbl[0][idx];
        Lever_Buff[wk->wu.id] = lever;
        break;
    default:
        if (wk->wu.hf.hit.player) {
            Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        }
        Check_Landed(wk, Reaction & 0xFFF);
        break;
    }
    Lever_Buff[wk->wu.id] |= Lever_LR[wk->wu.id];
}



void Hi_Jump_Attack_Term(wk, Range_X, Range_Y, Reaction, Lever_Data, Jump_Dir, Range_JX, Range_JY, J_Lever_Data)
PLW* wk;
s16 Range_X;
s16 Range_Y;
s16 Reaction;
u16 Lever_Data;
s16 Jump_Dir;
s16 Range_JX;
s16 Range_JY;
u16 J_Lever_Data;
{
    u16 lever;
    u16 idx;
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        Setup_Lever_LR(wk, wk->wu.id, Reaction & 0xF000);
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Check_Start_Hi_Jump(wk) != 0) {
            break;
        }
        Continue_Menu[wk->wu.id] = 0;
        wk->wu.hf.hit.player = 0;
        CP_Index[wk->wu.id][1]++;
        Tech_Address[wk->wu.id] = player_cmd[wk->player_number][2];
        Check_First_Menu(wk);
        break;
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id] == 0) {
            CP_Index[wk->wu.id][1]++;
            Tech_Index[wk->wu.id] = 0xC;
            dash_flag_clear(wk->wu.id);
            Jump_Init(wk, Jump_Dir);
            Lever_Pool[wk->wu.id] &= LEVER_LR;
            Lever_Buff[wk->wu.id] = 0;
            Check_Air_Guard(wk);
        }
        break;
    case 2:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Command_Type_00(wk, 8, -1) == -1) {
            CP_Index[wk->wu.id][1]++;
            Lever_Buff[wk->wu.id] |= Lever_Pool[wk->wu.id];
        } else {
            if (Lever_Buff[wk->wu.id] & LEVER_DOWN) {
                return;
            }
            Lever_Buff[wk->wu.id] |= Lever_Pool[wk->wu.id];
        }
        break;
    case 3:
        if (wk->wu.xyz[1].disp.pos > 0) {
            CP_Index[wk->wu.id][1]++;
        }
        else {
            Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id] | 1;
        }
        break;
    case 4:
        Lever_Buff[wk->wu.id] |= Air_Guard_Lever(wk);
        if (Check_Landed(wk, Reaction) != 0) {
            break;
        }
        if (Check_VS_Air_Attack(wk, Range_JX, Range_JY, J_Lever_Data) != 0) {
            break;
        }
        if (Check_Term_Sub(wk, PL_Distance[wk->wu.id], Range_X) == 0) {
            break;
        }
        if (Check_Com_Add_Y(wk, wk->wu.xyz[1].disp.pos, Range_Y) == 0) {
            break;
        }
        if (Check_Term_Sub(wk, wk->wu.xyz[1].disp.pos, Range_Y) == 0) {
            break;
        }
        Lever_Data = Check_SP_Jump_Attack(wk, (s16)Lever_Data);
        Lever_Buff[wk->wu.id] = Lever_Data;
        CP_Index[wk->wu.id][1]++;
        if (Reaction & 0x80) {
            CP_Index[wk->wu.id][1] = 8;
        }
        break;
    case 5:
        if (wk->wu.hf.hit.player) {
            Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        }
        Check_Landed(wk, Reaction & 0xFFF);
        break;
    case 6:
        if (Check_Landed(wk, Reaction) != 0) {
            break;
        }
        switch (Tech_Address[wk->wu.id][Tech_Index[wk->wu.id]]) {
        default:
        case 1:
        case 10:
            if (Command_Type_00(wk, -1) == -1) {
                CP_Index[wk->wu.id][1] = 0x63;
            }
            break;
        }
        break;
    case 7:
        if (--Combo_Speed[wk->wu.id]) {
            break;
        }
        Lever_Buff[wk->wu.id] = Tech_Address[wk->wu.id][8];
        CP_Index[wk->wu.id][1]++;
        break;
    case 8:
        Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        Check_Landed(wk, Reaction & 0xFFF);
        break;
    default:
        if (Attack_Flag[wk->wu.id]) {
            break;
        }
        CP_Index[wk->wu.id][1] = 8;
        if (wk->wu.hf.hit.player == 0) {
            break;
        }
        if (wk->wu.cg_cancel & 8) {
            lever = wk->wu.cg_eftype & 0xC;
            if (lever) {
                lever = Setup_Guard_Lever(wk, lever >> 3);
            }
            lever |= wk->wu.cg_eftype & 3;
            idx = (wk->wu.cg_eftype & 0x70) >> 4;
            lever |= cancel_shot_tbl[0][idx];
            Lever_Buff[wk->wu.id] = lever;
        }
        break;
    }
    Lever_Buff[wk->wu.id] |= Lever_LR[wk->wu.id];
}



s32 Check_Term_ABS_Distance(PLW* wk) {
    if (Turn_Over[wk->wu.id]) {
        return 0;
    }
    if (My_char[wk->wu.id] == PL_NECRO) {
        return 0;
    }
    if (PL_Distance[wk->wu.id] <= 0x30) {
        return 1;
    }
    if (wk->wu.mvxy.a[1].real.h >= 0) {
        return 0;
    }
    if (wk->wu.xyz[1].disp.pos <= 0x30) {
        return 1;
    }
    return 0;
}



s32 Check_Com_Add_Y(PLW* wk, s16 Pos_Y, s16 Range) {
    if (Range == -1) {
        return 1;
    }
    if (!(Range & 0x8000)) {
        if (Pos_Y >= Range) {
            return 1;
        }
        return 0;
    } else {
        if (wk->wu.mvxy.a[1].real.h >= 0) {
            return 0;
        }
        if (Pos_Y <= (Range & 0x7FFF)) {
            return 1;
        }
        return 0;
    }
}


/* provisional name */
s32 Check_Com_Add_Y_Sub(PLW* wk) {
    if (wk->wu.routine_no[1] != PLAYER_ATTACK || wk->wu.cg_type == 64) {
        return 1;
    }
    return 0;
}




void Command_Attack(wk, Reaction, Tech_Number, Power_Level, Ex_Shot)
PLW* wk;
s16 Reaction;
u16 Tech_Number;
s16 Power_Level;
s16 Ex_Shot;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        dash_flag_clear(wk->wu.id);
        Tech_Address[wk->wu.id] = player_cmd[wk->player_number][Tech_Number & 0xFF];
        Tech_Index[wk->wu.id] = 0xC;
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        if (Check_Start_Command_Attack(wk, Tech_Number & 0x80FF) != 0) {
            break;
        }
        if (Check_Dash_Hit(wk, Tech_Number & 0x80FF) != 0) {
            Next_Be_Free(wk);
        }
        CP_Index[wk->wu.id][1]++;
        Check_First_Menu(wk);
        if (Power_Level & 0x4000) {
            Free_Lever[wk->wu.id] = Power_Lv_Data[(Power_Level & 0xF) - 8];
        } else {
            Free_Lever[wk->wu.id] = 0;
        }
    case 1:
        if (--Combo_Speed[wk->wu.id]) {
            Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
            break;
        }
        if (Hadou_Check(wk, Tech_Number & 0x80FF) != 0) {
            if (Check_Passive(wk) == 0) {
                Combo_Speed[wk->wu.id] = 1;
            }
            break;
        } else {
            CP_Index[wk->wu.id][1]++;
            Check_Rapid(wk, Tech_Number);
        }
    case 2:
        if (Check_Passive(wk) != 0) {
            break;
        }
        switch (Tech_Address[wk->wu.id][Tech_Index[wk->wu.id]]) {
        case 1:
        default:
            if (Command_Type_00(wk, Power_Level & 0xF, Tech_Number) == -1) {
                if ((Tech_Number & 0xF) == 0 || (Tech_Number & 0xF) == 1) {
                    if (Reaction == 0xC) {
                        CP_Index[wk->wu.id][1] = 0x63;
                        Timer_00[wk->wu.id] = Dash_Time_Data[wk->player_number][Tech_Number];
                    } else {
                        CP_Index[wk->wu.id][1] = 4;
                    }
                } else {
                    CP_Index[wk->wu.id][1] = 3;
                }
            }
            break;
        case 2:
            if (Command_Type_01(wk, Power_Level & 0xF) != 0) {
                CP_Index[wk->wu.id][1]++;
            }
            break;
        case 7:
            if (Command_Type_06(wk, Power_Level & 0xF) != 0) {
                CP_Index[wk->wu.id][1]++;
            }
            break;
        }
        break;
    case 3:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        if (plw[wk->wu.id].tsukami_f) {
            break;
        }
        if (((wk->wu.cg_type) == 0x40) || (wk->wu.routine_no[1] == PLAYER_NORMAL)) {
            Reaction_Exit_Sub(wk);
        } else {
            Lever_Buff[wk->wu.id] = Free_Lever[wk->wu.id];
            Rapid_Sub(wk);
            Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
            Reaction_Sub(wk, Reaction, Power_Level);
        }
        break;
    case 4:
        if (((wk->wu.cg_type) == 0x40) || (wk->running_f == 0)) {
            Reaction_Exit_Sub(wk);
        }
        break;
    default:
        if (--Timer_00[wk->wu.id] == 0) {
            Reaction_Exit_Sub(wk);
        }
        break;
    }
}




/* tests Ryu and Ken directly */
s32 Hadou_Check(wk, Tech_Number)
PLW* wk;
u16 Tech_Number;
{
    if ((wk->player_number != PL_KEN) && (wk->player_number != PL_RYU)) {
        return 0;
    }
    if (Tech_Number != 23) {
        return 0;
    }
    return Check_Resume_Lever(wk);
}



s32 Check_Resume_Lever(PLW* wk) {
    u16 Target_Lever;
    s16 xx;
    if (wk->wu.rl_waza) {
        Target_Lever = 8;
    } else {
        Target_Lever = 4;
    }
    for (xx = 0; xx <= 10; xx++) {
        if (Target_Lever == Resume_Lever[wk->wu.id][xx]) {
            return 1;
        }
    }
    return 0;
}



void J_Command_Attack(wk, Reaction, Tech_Number, Power_Level, Ex_Shot)
PLW* wk;
s16 Reaction;
u16 Tech_Number;
s16 Power_Level;
s16 Ex_Shot;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        dash_flag_clear(wk->wu.id);
        Tech_Address[wk->wu.id] = player_cmd[wk->player_number][Tech_Number & 0xFF];
        Tech_Index[wk->wu.id] = 0xC;
        (&Lever_Buff[0])[wk->wu.id] = Lever_LR[wk->wu.id];
        if (Check_Start_Command_Attack(wk, Tech_Number & 0x80FF) != 0) {
            break;
        }
        if (Check_Dash_Hit(wk, Tech_Number & 0x80FF) != 0) {
            Next_Be_Free(wk);
        }
        Continue_Menu[wk->wu.id] = 0;
        CP_Index[wk->wu.id][1]++;
        Check_First_Menu(wk);
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id]) {
            Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
            break;
        }
        CP_Index[wk->wu.id][1]++;
    case 2:
        if (Check_Passive(wk) != 0) {
            break;
        }
        switch (Tech_Address[wk->wu.id][Tech_Index[wk->wu.id]]) {
        case 2:
            if (Command_Type_01(wk, Power_Level & 0xF) != 0) {
                CP_Index[wk->wu.id][1]++;
            }
            break;
        default:
        case 1:
        case 10:
            if (Command_Type_00(wk, Power_Level & 0xF, Tech_Number) == -1) {
                CP_Index[wk->wu.id][1] = 0x63;
            }
            break;
        }
        break;
    case 3:
        Check_Rapid(wk, Tech_Number);
        CP_Index[wk->wu.id][1]++;
        return;
    default:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        if ((wk->wu.cg_type == 0x40) || (wk->wu.routine_no[1] == PLAYER_NORMAL)) {
            Reaction_Exit_Sub(wk);
        } else {
            Rapid_Sub(wk);
            if (Reaction == 0xC) {
                Reaction_Sub(wk, Reaction, Power_Level);
                break;
            }
            Check_Landed(wk, Reaction & 0xFFF);
        }
        break;
    }
}




void Check_Rapid(PLW* wk, u16 Tech_Number) {
    if (!(Tech_Number & 0xF00)) {
        Rapid_No[wk->wu.id][0] = RAPID_OFF;
    } else {
        Rapid_No[wk->wu.id][0] = Rapid_SA_Data[Setup_Lv08(0)][random_32_com() & 7];
        Rapid_No[wk->wu.id][1] = RAPID1_INIT;
        Setup_Rapid_End_Term(wk, Tech_Number);
        Rapid_Index[wk->wu.id] = 0x3F0;
    }
}



void Setup_Rapid_End_Term(wk, Tech_Number)
PLW* wk;
s16 Tech_Number;
{
    Rapid_No[wk->wu.id][2] = (Tech_Number & 0xF00) >> 8;
    if ((Tech_Number & 0xF00) == 0x400) {
        Rapid_No[wk->wu.id][3] = Setup_Rapid_Time(wk, Tech_Number);
    }
}



s32 Setup_Rapid_Time(wk, Tech_Number)
PLW* wk;
u16 Tech_Number;
{
    return 60;
}



void Rapid_Sub(PLW* wk) {
    if (Check_Rapid_End(wk) != 0) {
        return;
    }
    switch (Rapid_No[wk->wu.id][0]) {
    case RAPID_OFF:
        break;
    case RAPID_BURST:
        switch (Rapid_No[wk->wu.id][1]) {
        case RAPID1_INIT:
            Rapid_No[wk->wu.id][1]++;
            Timer_00[wk->wu.id] = 1;
            Timer_01[wk->wu.id] = 3;
            return;
        case RAPID1_BURST:
            if (--Timer_00[wk->wu.id] == 0) {
                Lever_Buff[wk->wu.id] = Rapid_Index[wk->wu.id];
                Timer_00[wk->wu.id] = 2;
                if (--Timer_01[wk->wu.id] == 0) {
                    Rapid_No[wk->wu.id][1]++;
                    Timer_01[wk->wu.id] = 24;
                }
            }
            break;
        case RAPID1_PAUSE:
            if (--Timer_01[wk->wu.id] == 0) {
                Rapid_No[wk->wu.id][1]++;
                Timer_00[wk->wu.id] = 1;
                Timer_01[wk->wu.id] = 2;
            }
            break;
        default:
            if (--Timer_00[wk->wu.id] == 0) {
                Lever_Buff[wk->wu.id] = Rapid_Index[wk->wu.id];
                Timer_00[wk->wu.id] = Timer_01[wk->wu.id];
            }
            break;
        }
        break;
    default:
        switch (Rapid_No[wk->wu.id][1]) {
        case RAPID1_INIT:
            Rapid_No[wk->wu.id][1]++;
            Timer_00[wk->wu.id] = 1;
            Timer_01[wk->wu.id] = 2;
            break;
        default:
            if (--Timer_00[wk->wu.id] == 0) {
                Lever_Buff[wk->wu.id] = Rapid_Index[wk->wu.id];
                Timer_00[wk->wu.id] = Timer_01[wk->wu.id];
            }
            break;
        }
        break;
    }
}



s32 Check_Rapid_End(PLW* wk) {
    switch (Rapid_No[wk->wu.id][2]) {
    case RAPID_END_FALL:
        if (wk->wu.mvxy.a[1].real.h < 0) {
            Rapid_No[wk->wu.id][0] = RAPID_OFF;
            return 1;
        }
        break;
    case RAPID_END_CAUTION:
        switch (Rapid_No[wk->wu.id][3]) {
        case RAPID3_WAIT:
            if (plw[wk->wu.id].caution_flag) {
                Rapid_No[wk->wu.id][3]++;
            }
            break;
        case RAPID3_END:
            if (plw[wk->wu.id].caution_flag == 0) {
                Rapid_No[wk->wu.id][0] = RAPID_OFF;
                return 1;
            }
            break;
        }
        break;
    case RAPID_END_ATTACK:
        if (--Rapid_No[wk->wu.id][3] == 0) {
            Rapid_No[wk->wu.id][0] = RAPID_OFF;
            return 1;
        }
        break;
    }
    return 0;
}



s32 Check_Start_Command_Attack(wk, Tech_Number)
PLW* wk;
u16 Tech_Number;
{
    if (Before_Jump[wk->wu.id]) {
        return Before_Jump[wk->wu.id] = 0;
    }
    if (wk->wu.routine_no[1] == PLAYER_CATCH) {
        return 1;
    }
    if ((wk->wu.routine_no[1] != PLAYER_ATTACK) || (wk->wu.cg_type == 0x40)) {
        return 0;
    }
    if ((Tech_Number == 0) || (Tech_Number == 1)) {
        if (wk->wu.cg_cancel & 3) {
            return 0;
        }
        return 1;
    }
    if (Tech_Number & 0x8000) {
        if (wk->wu.cg_cancel & 0x80) {
            return 0;
        }
    }
    if (wk->wu.cg_cancel & 0x40) {
        return 0;
    }
    return 1;
}




void Jump_Command_Attack_Term(wk, Reaction, Tech_Number, Power_Level, RX, RY, Jump_Dir, JRX, JRY, JLD)
PLW* wk;
s16 Reaction;
u16 Tech_Number;
s16 Power_Level;
s16 RX;
s16 RY;
s16 Jump_Dir;
s16 JRX;
s16 JRY;
u16 JLD;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        if (Check_Passive(wk) != 0) {
            break;
        }
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        if ((wk->wu.routine_no[1] != PLAYER_ATTACK) || (wk->wu.cg_type == 0x40)) {
            Continue_Menu[wk->wu.id] = 0;
            CP_Index[wk->wu.id][1]++;
            Tech_Address[wk->wu.id] = player_cmd[wk->player_number][Tech_Number & 0xFF];
            Check_First_Menu(wk);
        }
        break;
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id] == 0) {
            CP_Index[wk->wu.id][1]++;
            Tech_Index[wk->wu.id] = 0xC;
            Jump_Init(wk, Jump_Dir);
            Check_Rapid(wk, Tech_Number);
        }
        break;
    case 2:
        Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
        if (wk->wu.xyz[1].disp.pos > 0) {
            CP_Index[wk->wu.id][1]++;
        }
        break;
    case 3:
        Lever_Buff[wk->wu.id] |= Air_Guard_Lever(wk);
        Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        if (Check_Landed(wk, Reaction) != 0) {
            break;
        }
        if (Check_VS_Air_Attack(wk, JRX, JRY, JLD) != 0) {
            break;
        }
        if (Check_Term_Sub(wk, PL_Distance[wk->wu.id], RX) == 0) {
            break;
        }
        if (Check_Com_Add_Y(wk, wk->wu.xyz[1].disp.pos, RY) == 0) {
            break;
        }
        if (Check_Term_Sub(wk, wk->wu.xyz[1].disp.pos, RY) == 0) {
            break;
        }
        CP_Index[wk->wu.id][1] += 2;
        break;
    case 4:
        if (wk->wu.hf.hit.player) {
            Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        }
        Check_Landed(wk, Reaction & 0xFFF);
        break;
    case 5:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        if (Check_Landed(wk, Reaction) != 0) {
            break;
        }
        switch (Tech_Address[wk->wu.id][Tech_Index[wk->wu.id]]) {
        default:
        case 1:
        case 10:
            if (Command_Type_00(wk, Power_Level & 0xF, Tech_Number) == -1) {
                CP_Index[wk->wu.id][1] = 0x63;
            }
            break;
        }
        break;
    default:
        Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        Rapid_Sub(wk);
        Check_Landed(wk, Reaction & 0xFFF);
        break;
    }
}



void Hi_Jump_Command_Attack_Term(wk, Reaction, Tech_Number, Power_Level, RX, RY, Jump_Dir, JRX, JRY, JLD)
PLW* wk;
s16 Reaction;
u16 Tech_Number;
s16 Power_Level;
s16 RX;
s16 RY;
s16 Jump_Dir;
s16 JRX;
s16 JRY;
u16 JLD;
{
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Check_Start_Hi_Jump(wk) == 0) {
            Continue_Menu[wk->wu.id] = 0;
            CP_Index[wk->wu.id][1]++;
            Tech_Address[wk->wu.id] = player_cmd[wk->player_number][Tech_Number & 0x7FFF];
            Check_First_Menu(wk);
        }
        break;
    case 1:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (--Combo_Speed[wk->wu.id == 0]) {
            CP_Index[wk->wu.id][1]++;
            Tech_Index[wk->wu.id] = 0xC;
            Jump_Init(wk, Jump_Dir);
            Lever_Pool[wk->wu.id] &= LEVER_LR;
            Lever_Buff[wk->wu.id] = 0;
            Check_Air_Guard(wk);
        }
        break;
    case 2:
        if (Check_Passive(wk) != 0) {
            break;
        }
        if (Command_Type_00(wk, Power_Level & 0xF) != 0) {
            if (!(Lever_Buff[wk->wu.id] & LEVER_DOWN)) {
                Lever_Buff[wk->wu.id] |= Lever_Pool[wk->wu.id];
            }
            break;
        }
        Lever_Pool[wk->wu.id] |= LEVER_UP;
        Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
        break;
    case 3:
        Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id] | 1;
        if (wk->wu.xyz[1].disp.pos > 0) {
            CP_Index[wk->wu.id][1]++;
        }
        break;
    case 4:
        Lever_Buff[wk->wu.id] |= Air_Guard_Lever(wk);
        if (Check_Landed(wk, Reaction) != 0) {
            break;
        }
        if (Check_VS_Air_Attack(wk, JRX, JRY, JLD) != 0) {
            break;
        }
        if (Check_Term_Sub(wk, PL_Distance[wk->wu.id], RX) == 0) {
            break;
        }
        if (Check_Com_Add_Y(wk, wk->wu.xyz[1].disp.pos, RY) == 0) {
            break;
        }
        if (Check_Term_Sub(wk, wk->wu.xyz[1].disp.pos, RY) == 0) {
            break;
        }
        CP_Index[wk->wu.id][1] += 2;
        break;
    case 5:
        if (wk->wu.hf.hit.player) {
            Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        }
        Check_Landed(wk, Reaction & 0xFFF);
        break;
    case 6:
        Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
        if (Check_Landed(wk, Reaction) != 0) {
            break;
        }
        switch (Tech_Address[wk->wu.id][Tech_Index[wk->wu.id]]) {
        default:
        case 1:
        case 10:
            Command_Type_00(wk, 8);
            CP_Index[wk->wu.id][1] = 0x63;
            break;
        }
        break;
    default:
        Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
        Check_Landed(wk, Reaction & 0xFFF);
        break;
    }
}



s32 Check_Landed(wk, Reaction)
PLW* wk;
s16 Reaction;
{
    if ((wk->wu.old_pos[1] != 0) && (wk->wu.xyz[1].disp.pos == 0)) {
        Lever_Buff[wk->wu.id] = 0;
        if (Continue_Menu[wk->wu.id]) {
            Next_End(wk);
            Before_Jump[wk->wu.id] = 1;
            return 1;
        } else {
            Reaction_Sub(wk, Reaction, 0);
            if (Check_Guard(wk) != 0) {
                return 1;
            }
            Before_Jump[wk->wu.id] = 1;
            return 1;
        }
    }
    if ((wk->wu.old_pos[1] == 0) && (wk->wu.xyz[1].disp.pos == 0) && (wk->wu.routine_no[1] != PLAYER_ATTACK)) {
        Lever_Buff[wk->wu.id] = 0;
        if (Continue_Menu[wk->wu.id]) {
            Next_End(wk);
            Before_Jump[wk->wu.id] = 1;
            return 1;
        } else {
            Reaction_Sub(wk, Reaction, 0);
            if (Check_Guard(wk) != 0) {
                return 1;
            }
            Before_Jump[wk->wu.id] = 1;
            return 1;
        }
    }
    return 0;
}



s32 Check_Dash_Hit(wk, Tech_Number)
PLW* wk;
u16 Tech_Number;
{
    WORK_Other* tmw;
    WORK* em;
    s16 i;
    s16 xx;
    s16 zz;
    if ((Tech_Number != 0) && (Tech_Number != 1)) {
        return 0;
    }
    em = (WORK*)wk->wu.target_adrs;
    for (i = 0; i < 8; i++) {
        if (get_my_shell_ix(em, i, &tmw) == 0) {
            return 0;
        }
        if (tmw->wu.routine_no[1] == SHELL_VANISH) {
            continue;
        }
        xx = wk->wu.xyz[0].disp.pos - tmw->wu.xyz[0].disp.pos;
        zz = Setup_Front_or_Back(wk, xx);
        if (Tech_Number == 0) {
            if (zz != 1) {
                if (Check_Hit_Shell(wk, tmw, Tech_Number) != 0) {
                    return 1;
                }
            }
        } else {
            if (zz != 0) {
                if (Check_Hit_Shell(wk, tmw, Tech_Number) != 0) {
                    return 1;
                }
            }
        }
    }
}



s32 Setup_Front_or_Back(wk, xx)
PLW* wk;
s16 xx;
{
    if (wk->wu.rl_waza == 0) {
        if (xx >= 0) {
            return 0;
        }
        return 1;
    } else {
        if (xx >= 0) {
            return 1;
        }
        return 0;
    }
}



s32 Check_Hit_Shell(wk, tmw, Tech_Number)
PLW* wk;
WORK_Other* tmw;
u16 Tech_Number;
{
    s16 xx;
    if (wk->wu.rl_waza == 1) {
        Tech_Number ^= 1;
    }
    if (Tech_Number == 0) {
        xx = wk->wu.xyz[0].disp.pos - Dash_Distance_Data[wk->player_number][Tech_Number];
        if (xx <= tmw->wu.xyz[0].disp.pos) {
            return 1;
        }
        return 0;
    } else {
        xx = wk->wu.xyz[0].disp.pos + Dash_Distance_Data[wk->player_number][Tech_Number];
        if (xx >= tmw->wu.xyz[0].disp.pos) {
            return 1;
        }
        return 0;
    }
}



void Jump_Init(wk, Jump_Dir)
PLW* wk;
s16 Jump_Dir;
{
    u16* a;
    u16* b;

    a = Lever_Buff;
    b = Lever_Pool;
    switch (Jump_Dir) {
    case 0:
        Ck_Distance_LvJ(wk);
        a[wk->wu.id] = b[wk->wu.id];
        break;
    case 2:
        b[wk->wu.id] = 1;
        a[wk->wu.id] = 1;
        break;
    default:
        Ck_Distance_LvJ(wk);
        b[wk->wu.id] ^= 0xC;
        a[wk->wu.id] = b[wk->wu.id];
        break;
    }
}



s32 Command_Type_00(wk, Power_Level, Tech_Number)
PLW* wk;
s16 Power_Level;
u16 Tech_Number;
{
    if (Tech_Address[wk->wu.id][Tech_Index[wk->wu.id] + 4] != 27) {
        Lever_Buff[wk->wu.id] = Tech_Address[wk->wu.id][Tech_Index[wk->wu.id] + 3] & 0x7FFF;
        if (wk->wu.rl_waza) {
            if (Lever_Buff[wk->wu.id] & LEVER_LR) {
                Lever_Buff[wk->wu.id] ^= LEVER_LR;
            }
        }
        Tech_Index[wk->wu.id] += 4;
        return 1;
    } else {
        Lever_Buff[wk->wu.id] = Tech_Address[wk->wu.id][Tech_Index[wk->wu.id] + 3] & 0x7FFF;
        if (wk->wu.rl_waza) {
            if (Lever_Buff[wk->wu.id] & LEVER_LR) {
                Lever_Buff[wk->wu.id] ^= LEVER_LR;
            }
        }
        if (Tech_Address[wk->wu.id][7] == 0x4000) {
            return -1;
        }
        Tech_Index[wk->wu.id] = 7;
        Lever_Buff[wk->wu.id] |= Tech_Address[wk->wu.id][Power_Level & 0xF];
        if ((My_char[wk->wu.id] == PL_RYU) && ((Tech_Number) == 0x8011) && (Power_Level != 8)) {
            CP_Index[wk->wu.id][0]++;
            Lever_LR[wk->wu.id] = Lever_Buff[wk->wu.id] & BUTTON_SHOTS;
            if (Power_Level == 0xA) {
                CP_Index[wk->wu.id][1] = 1;
            } else {
                CP_Index[wk->wu.id][1] = 0;
            }
        } else {
            CP_Index[wk->wu.id][1]++;
        }
        return 0;
    }
}



s32 Command_Type_06(wk, Power_Level)
PLW* wk;
s16 Power_Level;
{
    Lever_Buff[wk->wu.id] = Rolling_Lv_Data[0][CP_Index[wk->wu.id][2]];
    CP_Index[wk->wu.id][2]++;
    if ((Rolling_Lv_Data[0][CP_Index[wk->wu.id][2]]) == 0xFFFF) {
        Lever_Buff[wk->wu.id] |= Rolling_Lv_Data[1][(Power_Level & 0xF) - 8];
        return 1;
    }
    return 0;
}



s32 Command_Type_01(wk, Power_Level)
PLW* wk;
s16 Power_Level;
{
    switch (CP_Index[wk->wu.id][2]) {
    case 0:
        CP_Index[wk->wu.id][2]++;
        Timer_01[wk->wu.id] = Tech_Address[wk->wu.id][Tech_Index[wk->wu.id] + 1] + 2;
        (&Lever_Pool[0])[wk->wu.id] = Tech_Address[wk->wu.id][Tech_Index[wk->wu.id] + 3];
        Setup_Command_01(wk);
        if (wk->wu.rl_waza) {
            if (Lever_Pool[wk->wu.id] & LEVER_LR) {
                Lever_Pool[wk->wu.id] ^= LEVER_LR;
            }
        }
    case 1:
        if (wk->permited_koa & 2) {
            CP_Index[wk->wu.id][2]++;
        } else {
            Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
            Timer_00[wk->wu.id]++;
            break;
        }
    default:
        if (++Timer_00[wk->wu.id] < Timer_01[wk->wu.id]) {
            Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
        } else {
            Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
            Tech_Index[wk->wu.id] += 4;
            if (Tech_Address[wk->wu.id][Tech_Index[wk->wu.id]] == 27) {
                return 1;
            }
        }
        break;
    }
    return 0;
}



void Setup_Command_01(PLW* wk) {
    switch (Lever_Pool[wk->wu.id]) {
    case 2:
        (&Timer_00[0])[wk->wu.id] = Lever_Store[wk->wu.id][0];
        break;
    default:
        (&Timer_00[0])[wk->wu.id] = Lever_Store[wk->wu.id][2];
        break;
    }
}



void Check_Store_Lever(wk, Tech_Number, Next_Action, Next_Menu)
PLW* wk;
u16 Tech_Number;
s16 Next_Action;
s16 Next_Menu;
{
    s16 time;
    u16 lever;
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    Tech_Address[wk->wu.id] = player_cmd[wk->player_number][Tech_Number & 0xFF];
    time = Tech_Address[wk->wu.id][13] + 2;
    lever = Tech_Address[wk->wu.id][15];
    if (Check_Store_Direction(wk, lever, time) != 0) {
        CP_Index[wk->wu.id][0]++;
    } else {
        Next_Another_Menu(wk, Next_Action, Next_Menu);
    }
}



s32 Check_Store_Direction(wk, lever, time)
PLW* wk;
u16 lever;
s16 time;
{
    if (wk->wu.rl_waza) {
        if (lever & 0xC) {
            lever ^= 0xC;
        }
    }
    switch (lever) {
    case 2:
        if (time <= Lever_Store[wk->wu.id][0]) {
            return 1;
        }
        break;
    case 8:
        if (time <= Lever_Store[wk->wu.id][1]) {
            return 1;
        }
        break;
    case 4:
        if (time <= Lever_Store[wk->wu.id][2]) {
            return 1;
        }
        break;
    }
}



s32 Select_Combo_Speed(PLW* wk) {
    s8 xx;
    s8 zz;
    xx = (u8)random_32_com();
    Lv = Setup_Lv18(8);
    Lv += CC_Value[0];
    if ((Demo_Flag == 0) && (Weak_PL == wk->wu.id)) {
        Lv = 2;
    }
    return zz = Combo_Speed_Unit_Data[wk->player_number][Lv][xx];
}



s32 Select_Reflection_Time(PLW* wk) {
    s8 Lv;
    s8 xx;
    s8 zz;
    xx = random_32_com();
    Lv = Setup_Lv18(Game_setting.Difficulty);
    Lv += CC_Value[0];
    if ((Demo_Flag == 0) && (Weak_PL == wk->wu.id)) {
        Lv = 2;
    }
    return zz = Reflection_Speed_Unit_Data[wk->player_number][Lv][xx];
}



s32 Setup_Lv04(xx)
s16 xx;
{
    s16 i;
    const s16* zz;
    zz = (const s16*)&Level_04_Data[CC_Type][xx];
    for (i = 0; i < 3; i++) {
        if (Control_Time <= zz[i]) {
            return i;
        }
    }
    return 3;
}



s32 Setup_Lv08(xx)
s16 xx;
{
    s16 i;
    const s16* zz;
    zz = Level_08_Data[CC_Type][xx];
    for (i = 0; i < 7; i++) {
        if (Control_Time <= zz[i]) {
            break;
        }
    }
    return i;
}



s32 Setup_Lv10(xx)
s16 xx;
{
    s16 i;
    const s16* zz;
    zz = (const s16*)&Level_10_Data[CC_Type][xx];
    for (i = 0; i < 9; i++) {
        if (Control_Time <= zz[i]) {
            break;
        }
    }
    return i;
}



s32 Setup_Lv18(xx)
s16 xx;
{
    s16 i;
    const s16* zz;
    zz = (const s16*)&Level_18_Data[CC_Type][xx];
    for (i = 0; i < 17; i++) {
        if (Control_Time <= zz[i]) {
            break;
        }
    }
    return i;
}




s32 Setup_LP_Data(PLW* wk) {
    Lv = Setup_Lv08(0);
    if ((Demo_Flag == 0) && (Weak_PL == wk->wu.id)) {
        Lv = 2;
    }
    return LOOK_POSITION_Data[Lv][random_32_com()];
}



s32 Setup_WT_Data(PLW* wk) {
    Lv = Setup_Lv04(0);
    if ((Demo_Flag == 0) && (Weak_PL == wk->wu.id)) {
        Lv = 2;
    }
    return Wait_Time_Data[Lv][random_16_com() & 7];
}



void Ck_Distance(PLW* wk) {
    PL_Distance[wk->wu.id] = ((WORK*)wk->wu.target_adrs)->xyz[0].disp.pos - wk->wu.xyz[0].disp.pos;
    if (PL_Distance[wk->wu.id] < 0) {
        PL_Distance[wk->wu.id] = PL_Distance[wk->wu.id] * -1;
    }
}



s32 Ck_Distance_Height(PLW* wk) {
    s16 xx;
    xx = ((WORK*)wk->wu.target_adrs)->xyz[1].disp.pos - wk->wu.xyz[1].disp.pos;
    if (xx < 0) {
        xx = -xx;
    }
    return xx;
}



s32 Ck_Area(PLW* wk) {
    s16 i;
    for (i = 0; i < 3; i++) {
        if (PL_Distance[wk->wu.id] <= Separate_Area[wk->wu.id][i]) {
            return i;
        }
    }
    return 3;
}



s32 Ck_Area_Shell(PLW* wk) {
    s16 i;
    for (i = 0; i < 3; i++) {
        if (PL_Distance[wk->wu.id] <= Shell_Separate_Area[wk->wu.id][i]) {
            return i;
        }
    }
    return 3;
}



void Ck_Distance_Lv(PLW* wk) {
    PL_Distance[wk->wu.id] = ((WORK*)wk->wu.target_adrs)->xyz[0].disp.pos - wk->wu.xyz[0].disp.pos;
    if (PL_Distance[wk->wu.id] > 0) {
        Lever_Buff[wk->wu.id] = LEVER_RIGHT;
    } else {
        Lever_Buff[wk->wu.id] = LEVER_LEFT;
        PL_Distance[wk->wu.id] = PL_Distance[wk->wu.id] * -1;
    }
}



void Ck_Distance_LvJ(PLW* wk) {
    PL_Distance[wk->wu.id] = ((WORK*)wk->wu.target_adrs)->xyz[0].disp.pos - wk->wu.xyz[0].disp.pos;
    if (PL_Distance[wk->wu.id] > 0) {
        Lever_Pool[wk->wu.id] = (LEVER_UP | LEVER_RIGHT);
    } else {
        Lever_Pool[wk->wu.id] = (LEVER_UP | LEVER_LEFT);
        PL_Distance[wk->wu.id] = PL_Distance[wk->wu.id] * -1;
    }
}



s32 Next_End(PLW* wk) {
    if (Check_Guard(wk) != 0) {
        return 1;
    }
    CP_Index[wk->wu.id][0] = -1;
    CP_Index[wk->wu.id][1] = 0;
    CP_Index[wk->wu.id][2] = 0;
    CP_Index[wk->wu.id][3] = 0;
}



void Next_Another_Menu(PLW* wk, s16 Next_Action, s16 Next_Menu) {
    if (Next_Action != 1) {
        CP_No[wk->wu.id][0] = Next_Action;
        Pattern_Index[wk->wu.id] = Next_Menu;
        CP_Index[wk->wu.id][0] = 0;
        CP_Index[wk->wu.id][1] = 0;
        CP_Index[wk->wu.id][2] = 0;
        CP_Index[wk->wu.id][3] = 0;
    } else {
        Next_Be_Free(wk);
    }
}



void Reaction_Sub(wk, Reaction, Power_Level)
PLW* wk;
s16 Reaction;
s16 Power_Level;
{
    switch (Reaction & 0x7F) {
    case 9:
        if (Stock_Hit_Flag[wk->wu.id]) {
            Reaction_Exit_Sub(wk);
        } else if ((wk->wu.routine_no[1] != PLAYER_ATTACK) || (wk->wu.cg_type == 0x40)) {
            Next_End(wk);
        }
        break;
    case 10:
        if ((Stock_Hit_Flag[wk->wu.id] >> 2) != 0) {
            Next_End(wk);
            break;
        }
        if (Stock_Hit_Flag[wk->wu.id] || wk->wu.routine_no[1] != PLAYER_ATTACK || wk->wu.cg_type == 0x40) {
            Reaction_Exit_Sub(wk);
        }
        break;
    case 11:
        if (plw[wk->wu.id].caution_flag) {
            break;
        }
        if (plw[wk->wu.id].tsukami_f) {
            break;
        }
        if ((Stock_Hit_Flag[wk->wu.id] >> 2) != 0) {
            Next_End(wk);
            break;
        }
        if (Stock_Hit_Flag[wk->wu.id]) {
            Reaction_Exit_Sub(wk);
        } else if ((wk->wu.routine_no[1] != PLAYER_ATTACK) || (wk->wu.cg_type == 0x40)) {
            Next_End(wk);
        }
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        if ((Stock_Hit_Flag[wk->wu.id] >> 2) != 0) {
            Setup_Follow(wk, Reaction & 0xFFF);
            break;
        }
        if (Stock_Hit_Flag[wk->wu.id]) {
            Reaction_Exit_Sub(wk);
        } else if ((wk->wu.routine_no[1] != PLAYER_ATTACK) || (wk->wu.cg_type == 0x40)) {
            Setup_Follow(wk, Reaction & 0xFFF);
        }
        break;
    case 12:
        Reaction_Exit_Sub(wk);
        Counter_Attack[wk->wu.id] = 1;
        break;
    case 13:
        if ((Stock_Hit_Flag[wk->wu.id] >> 2) != 0) {
            Next_End(wk);
            break;
        }
        if (wk->permited_koa & 0x10) {
            if (Check_Meoshi_Attack(wk, Reaction, Power_Level) != 0) {
                break;
            }
        }
        Last_Eftype[wk->wu.id] = -1;
        if ((wk->wu.routine_no[1] != PLAYER_ATTACK) || (wk->wu.cg_type == 0x40)) {
            if (Stock_Hit_Flag[wk->wu.id]) {
                if ((CP_No[wk->wu.id][0] == COM_PASSIVE) && (Pattern_Index[wk->wu.id] == 0)) {
                    CP_No[wk->wu.id][0] = Return_CP_No[wk->wu.id];
                    CP_Index[wk->wu.id][0] = Return_CP_Index[wk->wu.id];
                    CP_Index[wk->wu.id][1] = 0;
                    CP_Index[wk->wu.id][2] = 0;
                    CP_Index[wk->wu.id][3] = 0;
                    Pattern_Index[wk->wu.id] = Return_Pattern_Index[wk->wu.id];
                } else {
                    Reaction_Exit_Sub(wk);
                }
            } else {
                Next_End(wk);
            }
        }
        break;
    default:
        if (plw[wk->wu.id].caution_flag) {
            break;
        }
        if (plw[wk->wu.id].tsukami_f) {
            break;
        }
        if (Stock_Hit_Flag[wk->wu.id] || (wk->wu.routine_no[1] != PLAYER_ATTACK) || (wk->wu.cg_type == 0x40)) {
            Reaction_Exit_Sub(wk);
        }
        break;
    }
}



s32 Check_Meoshi_Attack(wk, Reaction, Power_Level)
PLW* wk;
s16 Reaction;
s16 Power_Level;
{
    u16 lever;
    u16 idx;
    u16 row;
    if (Last_Eftype[wk->wu.id] == wk->wu.cg_eftype) {
        return 0;
    }
    if (wk->permited_koa & 0x10) {
        Last_Eftype[wk->wu.id] = wk->wu.cg_eftype;
        lever = wk->wu.cg_eftype & 0xF;
        lever = Meoshi_Lever_Data[lever];
        if ((lever == 0x8000) || (lever == 0x8001)) {
            lever = Setup_Guard_Lever(wk, lever);
        }
        idx = (wk->wu.cg_eftype & 0x70) >> 4;
        row = (Power_Level & 0xF00) >> 8;
        lever |= cancel_shot_tbl[row][idx];
        M_Lv[wk->wu.id] = lever;
        if (Pattern_Index[wk->wu.id] != 0) {
            Return_CP_No[wk->wu.id] = CP_No[wk->wu.id][0];
            Return_CP_Index[wk->wu.id] = CP_Index[wk->wu.id][0] + 1;
            CP_Index[wk->wu.id][1] = 0;
            CP_Index[wk->wu.id][2] = 0;
            CP_Index[wk->wu.id][3] = 0;
            Return_Pattern_Index[wk->wu.id] = Pattern_Index[wk->wu.id];
        }
        CP_No[wk->wu.id][0] = COM_PASSIVE;
        CP_Index[wk->wu.id][0] = 0;
        CP_Index[wk->wu.id][1] = 0;
        CP_Index[wk->wu.id][2] = 0;
        CP_Index[wk->wu.id][3] = 0;
        Pattern_Index[wk->wu.id] = 0;
        return 1;
    }
    return 0;
}



void Reaction_Exit_Sub(PLW* wk) {
    CP_Index[wk->wu.id][0]++;
    CP_Index[wk->wu.id][1] = 0;
    CP_Index[wk->wu.id][2] = 0;
    CP_Index[wk->wu.id][3] = 0;
    Flip_Flag[wk->wu.id] = 0;
    Counter_Attack[wk->wu.id] = 0;
    Limited_Flag[wk->wu.id] = 0;
    Before_Jump[wk->wu.id] = 0;
    if (CP_No[wk->wu.id][0] != COM_PASSIVE) {
        Passive_Flag[wk->wu.id] = 0;
    }
}



/* provisional name */
s32 Check_Stock_Hit_Menu(wk, Menu)
PLW* wk;
s16 Menu;
{
    s32 hit;
    switch (Menu) {
    case 8:
        break;
    case 9:
        if (Stock_Hit_Flag[wk->wu.id] == 0) {
            return 1;
        }
        break;
    case 10:
        if (Stock_Hit_Flag[wk->wu.id] >> 2) {
            return 1;
        }
        break;
    case 11:
        if (Stock_Hit_Flag[wk->wu.id] >> 2) {
            return 1;
        }
        if (Stock_Hit_Flag[wk->wu.id] == 0) {
            return 1;
        }
        break;
    default:
        hit = Stock_Hit_Flag[wk->wu.id];
        if (hit == 0 || hit >> 2) {
            Setup_Follow(wk, Menu & 0xFFF);
            return -1;
        }
        break;
    }
    return 0;
}



void Check_First_Menu(PLW* wk) {
    if (CP_Index[wk->wu.id][0] == 0) {
        Combo_Speed[wk->wu.id] = 1;
    } else {
        Combo_Speed[wk->wu.id] = Select_Combo_Speed(wk);
    }
}



void Select_Active(PLW* wk) {
    s16 pl_id;
    Lv = Setup_Lv08(0);
    if ((Demo_Flag == 0) && (Weak_PL == wk->wu.id)) {
        Lv = 2;
    }
    Rnd = (u8)random_32_ex_com();
    if (Check_SA_Active(wk, &pl_id) != 0) {
        Lv = Setup_Lv04(0);
        if ((Demo_Flag == 0) && (Weak_PL == wk->wu.id)) {
            Lv = 2;
        }
        switch (Area_Number[wk->wu.id]) {
        case 0:
            Pattern_Index[wk->wu.id] = SA_Active_A_Unit_Data[pl_id - 1][Lv][Rnd];
            break;
        case 1:
            Pattern_Index[wk->wu.id] = SA_Active_B_Unit_Data[pl_id - 1][Lv][Rnd];
            break;
        case 2:
            Pattern_Index[wk->wu.id] = SA_Active_C_Unit_Data[pl_id - 1][Lv][Rnd];
            break;
        default:
            Pattern_Index[wk->wu.id] = SA_Active_D_Unit_Data[pl_id - 1][Lv][Rnd];
            break;
        }
    } else {
        switch (Area_Number[wk->wu.id]) {
        case 0:
            Pattern_Index[wk->wu.id] = Active_A_Unit_Data[wk->player_number][Lv][Rnd];
            Check_Bullet_Counter(wk);
            break;
        case 1:
            Pattern_Index[wk->wu.id] = Active_B_Unit_Data[wk->player_number][Lv][Rnd];
            Check_Bullet_Counter(wk);
            break;
        case 2:
            Pattern_Index[wk->wu.id] = Active_C_Unit_Data[wk->player_number][Lv][Rnd];
            Check_Bullet_Counter(wk);
            break;
        default:
            Pattern_Index[wk->wu.id] = Active_D_Unit_Data[wk->player_number][Lv][Rnd];
            Check_Bullet_Counter(wk);
            break;
        }
    }
}



/* provisional name */
void Check_Bullet_Counter(PLW* wk) {
    if (Bullet_No[wk->wu.id] != 0) {
        if (plw[wk->wu.id].bullet_hcnt == 0) {
            Bullet_No[wk->wu.id] = 0;
            Setup_Bullet_Counter(wk);
        } else {
            Pattern_Index[wk->wu.id] = 0;
            if (--Bullet_Counter[wk->wu.id] == 0) {
                Bullet_No[wk->wu.id] = 0;
                Setup_Bullet_Counter(wk);
            }
        }
        return;
    }
    if (plw[wk->wu.id].bullet_hcnt >= Bullet_Counter[wk->wu.id]) {
        Bullet_No[wk->wu.id] = 1;
        Bullet_Counter[wk->wu.id] = 5;
        Bullet_Counter[wk->wu.id] += random_32_com() & 3;
        Pattern_Index[wk->wu.id] = 0;
    }
}



s32 Check_SA_Active(wk, pl_id)
PLW* wk;
s16* pl_id;
{
    if (wk->sa->ok != -1) {
        return 0;
    }
    if (My_char[wk->wu.id] == PL_ORO) {
        if (plw[wk->wu.id].sa->kind_of_arts == 0) {
            return *pl_id = 3;
        }
        return *pl_id = 2;
    }
    if (My_char[wk->wu.id] == PL_YUN && plw[wk->wu.id].sa->kind_of_arts == 2) {
        return *pl_id = 1;
    }
    if (My_char[wk->wu.id] == PL_YANG && plw[wk->wu.id].sa->kind_of_arts == 2) {
        return *pl_id = 1;
    }
    return 0;
}



void Setup_Follow(wk, Follow_Type)
PLW* wk;
s16 Follow_Type;
{
    CP_No[wk->wu.id][0] = COM_BEFORE_FOLLOW;
    CP_No[wk->wu.id][1] = Follow_Type;
    if (wk->wu.hf.hit.player == 0) {
        CP_No[wk->wu.id][2] = 0;
    } else {
        CP_No[wk->wu.id][2] = 1;
    }
    CP_No[wk->wu.id][3] = 0;
    Timer_00[wk->wu.id] = Select_Reflection_Time(wk);
    Timer_00[wk->wu.id]++;
}



void Decide_Follow_Menu(PLW* wk) {
    s8 xx;
    const FOLLOW_MENU_1ST* Menu_Add_Ptr0;
    const FOLLOW_MENU_2ND* Menu_Add_Ptr1;
    Menu_Add_Ptr0 = Follow_Menu_1st_Unit_Data[wk->player_number];
    Rnd = (u8)random_32_com();
    xx = Menu_Add_Ptr0->xxxx[CP_No[wk->wu.id][1]][CP_No[wk->wu.id][2]][Rnd];
    Menu_Add_Ptr1 = Follow_Menu_2nd_Unit_Data[wk->player_number];
    Pattern_Index[wk->wu.id] = Menu_Add_Ptr1->zzzz[xx][Area_Number[wk->wu.id]];
}



s32 Select_Passive(PLW* wk) {
    u16 xx;
    if (VS_Tech[wk->wu.id] == 0xB) {
        Area_Number[wk->wu.id] = Ck_Area_Shell(wk);
    }
    if (VS_Tech[wk->wu.id] == 0x1E) {
        Area_Number[wk->wu.id] = Ck_Area_Shell(wk);
    }
    Last_Attack_Counter[wk->wu.id] = Attack_Counter[wk->wu.id];
    Standing_Timer[wk->wu.id] = 0;
    Devide_Level(VS_Tech[wk->wu.id] >> 0xC);
    if ((Demo_Flag == 0) && (Weak_PL == wk->wu.id)) {
        Lv = 1;
    }
    VS_Tech[wk->wu.id] &= 0xFFF;
    Setup_Random(wk);
    switch (Area_Number[wk->wu.id]) {
    case 0:
        xx = Passive_A_Unit_Data_04[wk->player_number][VS_Tech[wk->wu.id]][Lv][Rnd];
        if (xx == 0xFF) {
            Counter_Attack[wk->wu.id] = 0;
            Passive_Flag[wk->wu.id] = 0;
            Jump_Pass_Timer[wk->wu.id][0] = 120;
            return -1;
        }
        Pattern_Index[wk->wu.id] = xx;
        Jump_Pass_Timer[wk->wu.id][0] = 0;
        break;
    case 1:
        xx = Passive_B_Unit_Data_04[wk->player_number][VS_Tech[wk->wu.id]][Lv][Rnd];
        if (xx == 0xFF) {
            Counter_Attack[wk->wu.id] = 0;
            Passive_Flag[wk->wu.id] = 0;
            Jump_Pass_Timer[wk->wu.id][1] = 120;
            return -1;
        }
        Pattern_Index[wk->wu.id] = xx;
        Jump_Pass_Timer[wk->wu.id][1] = 0;
        break;
    case 2:
        xx = Passive_C_Unit_Data_04[wk->player_number][VS_Tech[wk->wu.id]][Lv][Rnd];
        if (xx == 0xFF) {
            Counter_Attack[wk->wu.id] = 0;
            Passive_Flag[wk->wu.id] = 0;
            Jump_Pass_Timer[wk->wu.id][2] = 120;
            return -1;
        }
        Pattern_Index[wk->wu.id] = xx;
        Jump_Pass_Timer[wk->wu.id][2] = 0;
        break;
    default:
        xx = Passive_D_Unit_Data_04[wk->player_number][VS_Tech[wk->wu.id]][Lv][Rnd];
        if (xx == 0xFF) {
            Counter_Attack[wk->wu.id] = 0;
            Passive_Flag[wk->wu.id] = 0;
            Jump_Pass_Timer[wk->wu.id][3] = 120;
            return -1;
        }
        Pattern_Index[wk->wu.id] = xx;
        Jump_Pass_Timer[wk->wu.id][3] = 0;
        break;
    }
    Passive_Flag[wk->wu.id] = 1;
    CP_No[wk->wu.id][1] = 0;
    CP_No[wk->wu.id][2] = 0;
    CP_No[wk->wu.id][3] = 0;
    Timer_00[wk->wu.id] = Select_Reflection_Time(wk);
    if ((VS_Tech[wk->wu.id] == 0x19) || (Timer_00[wk->wu.id] == 0)) {
        CP_No[wk->wu.id][0] = COM_PASSIVE;
        CP_Index[wk->wu.id][0] = 0;
        CP_Index[wk->wu.id][1] = 0;
        CP_Index[wk->wu.id][2] = 0;
        CP_Index[wk->wu.id][3] = 0;
    } else {
        CP_No[wk->wu.id][0] = COM_BEFORE_PASSIVE;
    }
    return 1;
}



void Devide_Level(xx)
s16 xx;
{
    switch (xx) {
    case 0:
        Lv = Setup_Lv04(0);
        break;
    default:
        Lv = Setup_Lv08(2);
        break;
    }
}



void Setup_Random(PLW* wk) {
    if (VS_Tech[wk->wu.id] == 0x20) {
        Rnd = (u8)random_16_com() & 7;
        VS_Tech[wk->wu.id] = 0x1C;
    } else {
        Rnd = (u8)random_16_com();
        Rnd = Check_Dramatic(wk, wk->wu.id);
    }
}



s32 Check_Dramatic(wk, PL_id)
PLW* wk;
s16 PL_id;
{
    if (plw[wk->wu.id].sa->ok) {
        return Rnd | 8;
    }
    if ((plw[PL_id].wu.vital_new <= 48) || (plw[PL_id ^ 1].wu.vital_new <= 48)) {
        return Rnd | 8;
    }
    return Rnd;
}



s32 Check_Passive(PLW* wk) {
    WORK* em;
    if ((Counter_Attack[wk->wu.id] != 0) || (Pierce_Menu[wk->wu.id])) {
        return 0;
    }
    em = (WORK*)wk->wu.target_adrs;
    if (Check_Blow_Off(wk, em, 0) != 0) {
        *CP_No[wk->wu.id] = 0xE;
        CP_No[wk->wu.id][1] = 0;
        CP_No[wk->wu.id][2] = 0;
        CP_No[wk->wu.id][3] = 0;
        return -1;
    }
    if (Check_Thrown(wk, em) != 0) {
        if (Select_Passive(wk) != -1) {
            return 1;
        }
    }
    if (Check_Shell(wk) != 0) {
        return 1;
    }
    if ((Passive_Flag[wk->wu.id]) || (Flip_Flag[wk->wu.id])) {
        return Check_Guard(wk);
    }
    if (Check_Lie(wk) == 1) {
        return 1;
    }
    if (PL_Status[em->routine_no[1]] == 0) {
        return Check_Shell(wk);
    }
    Passive_Mode = 4;
    if (Ck_Guard_Passive_Term(wk) != 0) {
        if (Select_Passive(wk) != -1) {
            return 1;
        }
    }
    if (Check_Guard(wk) != 0) {
        return 1;
    }
    if ((Passive_Flag[wk->wu.id]) || (Flip_Flag[wk->wu.id])) {
        return 0;
    }
    Passive_Mode = 0;
    if (Ck_Guard_Passive_Term(wk) != 0) {
        return Select_Passive(wk);
    }
    return 0;
}



/* provisional name: the passive term check by screen area */
s32 Ck_Guard_Passive_Term(PLW* wk) {
    switch (Area_Number[wk->wu.id]) {
    case 0:
        if (Ck_Passive_Term(wk)) {
            return 1;
        }
        return 0;
    case 1:
        if (Ck_Passive_Term(wk)) {
            return 1;
        }
        return 0;
    case 2:
        if (Ck_Passive_Term(wk)) {
            return 1;
        }
        return 0;
    default:
        if (Ck_Passive_Term(wk)) {
            return 1;
        }
        return 0;
    }
}



s32 Check_Guard(PLW* wk) {
    WORK* em;
    s16 xx;
    em = (WORK*)wk->wu.target_adrs;
    if (Attack_Flag[wk->wu.id] == 0) {
        return 0;
    }
    if (Guard_Counter[wk->wu.id] == Attack_Counter[wk->wu.id]) {
        return 0;
    }
    xx = Hit_Range_Data[em->hit_range];
    xx += Com_Width_Data[wk->wu.id];
    if (PL_Distance[wk->wu.id] > xx) {
        return 0;
    }
    Lv = Setup_Lv10(0);
    if ((Demo_Flag == 0) && (Weak_PL == wk->wu.id)) {
        Lv = 2;
    }
    Lv = Correct_Lv_Gill(wk, Lv);
    Rnd = random_16_com();
    Lv += CC_Value[0];
    if (Guard_Data[wk->player_number][Lv][Rnd] == 3) {
        Guard_Counter[wk->wu.id] = Attack_Counter[wk->wu.id];
        return 0;
    }
    if (Check_Flip_Term(wk) != 0) {
        Next_Be_Flip(wk);
    } else {
        Next_Be_Guard(wk, em, Guard_Data[wk->player_number][Lv][random_16_ex_com()]);
    }
    return 1;
}



s32 Correct_Lv_Gill(wk, lv)
PLW* wk;
s16 lv;
{
    if (My_char[wk->wu.id] != PL_GILL) {
        return lv;
    }
    if (bg_w.area == 0) {
        lv -= 2;
        if (lv < 0) {
            lv = 0;
        }
    }
    return lv;
}




s32 Check_Flip_Term(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Flip_Tech(em) == 0) {
        return 0;
    }
    Lv = Setup_Lv08(0);
    if ((Demo_Flag == 0) && (Weak_PL == wk->wu.id)) {
        Lv = 2;
    }
    Rnd = random_32_com();
    Rnd -= Flip_Term_Correct(wk);
    if (Rnd >= (Flip_Data[wk->player_number][Lv])) {
        return 0;
    }
    return 1;
}



s32 Flip_Term_Correct(PLW* wk) {
    s16 xx = 0;
    if (plw[wk->wu.id].wu.vital_new <= 48) {
        xx++;
    }
    if ((PL_Wins[wk->wu.id]) < (PL_Wins[wk->wu.id ^ 1])) {
        xx += 2;
    }
    if (Counter_hi < 0xF) {
        xx += 1;
    }
    return xx;
}



void Next_Be_Guard(wk, em, Type_Of_Guard)
PLW* wk;
WORK* em;
s16 Type_Of_Guard;
{
    CP_No[wk->wu.id][0] = COM_GUARD;
    CP_No[wk->wu.id][1] = 0;
    CP_No[wk->wu.id][2] = 0;
    CP_No[wk->wu.id][3] = 0;
    Timer_00[wk->wu.id] = 10;
    dash_flag_clear(wk->wu.id);
    Guard_Type[wk->wu.id] = Type_Of_Guard;
    Check_Guard_Type(wk, em);
}



s32 Check_Flip_Tech(WORK* em) {
    if (em->kind_of_waza & 0xF8) {
        return 0;
    }
    if (em->kind_of_waza == 0) {
        return 0;
    }
    if (em->kind_of_waza == 1) {
        return 0;
    }
    return 1;
}



void Next_Be_Flip(PLW* wk) {
    WORK* em;
    em = (WORK*)wk->wu.target_adrs;
    CP_No[wk->wu.id][0] = COM_FLIP;
    CP_No[wk->wu.id][1] = 0;
    CP_No[wk->wu.id][2] = 0;
    CP_No[wk->wu.id][3] = 0;
    Timer_00[wk->wu.id] = 9;
    if ((em->pat_status == 33) || (em->pat_status == 32)) {
        Lever_Buff[wk->wu.id] = LEVER_DOWN;
    } else {
        Lever_Buff[wk->wu.id] = Setup_Guard_Lever(wk, 0);
    }
}




s32 Check_Shell(PLW* wk) {
    WORK* em;
    WORK_Other* tmw;
    s16 i;
    s16 xx;
    if (Shell_Ignore_Timer[wk->wu.id]) {
        Shell_Ignore_Timer[wk->wu.id]--;
        return 0;
    }
    if (CP_No[wk->wu.id][0] == COM_VS_SHELL) {
        return 0;
    }
    em = (WORK*)wk->wu.target_adrs;
    for (i = 0; i < 8; i++) {
        if (get_my_shell_ix(em, i, &tmw) == 0) {
            return 0;
        }
        if (tmw->wu.routine_no[1] == SHELL_VANISH) {
            continue;
        }
        if (wk->wu.rl_waza == tmw->wu.rl_flag) {
            continue;
        }
        if (tmw->wu.routine_no[0] != 1) {
            continue;
        }
        if (Check_Behind(wk, tmw)) {
            continue;
        }
        if (tmw->wu.charset_id == 2) {
            continue;
        }
        if (Check_Ignore_Shell(tmw)) {
            continue;
        }
        xx = Compute_Hit_Time(wk, tmw);
        if (Decide_Shell_Guard(wk, tmw)) {
            return 0;
        }
        CP_No[wk->wu.id][0] = COM_VS_SHELL;
        CP_No[wk->wu.id][1] = 0;
        CP_No[wk->wu.id][2] = 0;
        CP_No[wk->wu.id][3] = 0;
        CP_Index[wk->wu.id][0] = 0;
        CP_Index[wk->wu.id][1] = 0;
        CP_Index[wk->wu.id][2] = 0;
        CP_Index[wk->wu.id][3] = 0;
        Shell_Address[wk->wu.id] = (u32*)tmw;
        Guard_or_Jump_VS_Shell(wk, tmw, xx);
        return 1;
    }
}



s32 Check_Ignore_Shell(WORK_Other* tmw) {
    if ((tmw->wu.type >= 0x24) && (tmw->wu.type <= 0x27)) {
        return 1;
    }
    if ((tmw->wu.type >= 0xD) && (tmw->wu.type <= 0xF)) {
        return 1;
    }
    return 0;
}



s32 Compute_Hit_Time(PLW* wk, WORK_Other* tmw) {
    s32 lx1;
    s16 x2;
    lx1 = wk->wu.xyz[0].cal - tmw->wu.xyz[0].cal;
    x2 = lx1 / tmw->wu.mvxy.a[0].sp;
    if (x2 < 0) {
        return (s16)(x2 * -1);
    }
    return x2;
}



s32 Decide_Shell_Guard(PLW* wk, WORK_Other* tmw) {
    Lv = Setup_Lv10(0);
    if ((Demo_Flag == 0) && (Weak_PL == wk->wu.id)) {
        Lv = 2;
    }
    Rnd = random_32_com();
    if (Shell_Guard_Data[wk->player_number][Lv] > Rnd) {
        return 0;
    }
    Shell_Ignore_Timer[wk->wu.id] = 60;
    return 1;
}



void Guard_or_Jump_VS_Shell(wk, tmw, xx)
PLW* wk;
WORK_Other* tmw;
s16 xx;
{
    if (xx <= Shell_Dodge_Data[0][wk->player_number]) {
        if (Check_Flip_Term(wk) != 0) {
            Pattern_Index[wk->wu.id] = 9;
        } else {
            Pattern_Index[wk->wu.id] = 0;
        }
    } else if (plw[wk->wu.id].wu.vital_new > 10) {
        Pattern_Index[wk->wu.id] = Decide_Shell_Reaction(wk, tmw, Shell_Change_Data_For_Reaction[tmw->wu.type]);
    } else {
        Pattern_Index[wk->wu.id] = 9;
    }
    Setup_Shell_Disposal(wk, tmw);
}



void Setup_Shell_Disposal(PLW* wk, WORK_Other* tmw) {
    switch (Pattern_Index[wk->wu.id]) {
    case 0:
        Next_Be_Shell_Guard(wk, &tmw->wu);
        break;
    case 9:
        Passive_Flag[wk->wu.id] = 1;
        break;
    case 10:
        Pattern_Index[wk->wu.id] = Decide_Shell_Reaction(wk, tmw, 0);
        if (Pattern_Index[wk->wu.id] != 0) {
            break;
        }
        Next_Be_Shell_Guard(wk, &tmw->wu);
        break;
    }
}




void Next_Be_Shell_Guard(PLW* wk, WORK* tmw) {
    CP_No[wk->wu.id][0] = COM_SHELL_GUARD;
    CP_No[wk->wu.id][1] = 0;
    CP_No[wk->wu.id][2] = 0;
    CP_No[wk->wu.id][3] = 0;
    Timer_00[wk->wu.id] = 10;
    dash_flag_clear(wk->wu.id);
    Guard_Type[wk->wu.id] = 0;
    Check_Guard_Type(wk, tmw);
}



s32 Decide_Shell_Reaction(wk, tmw, dir_step)
PLW* wk;
WORK_Other* tmw;
u16 dir_step;
{
    if (dir_step == 0xFF) {
        return 0;
    }
    Lv = Setup_Lv08(0);
    if ((Demo_Flag == 0) && (Weak_PL == wk->wu.id)) {
        Lv = 2;
    }
    Rnd = random_16_com();
    return VS_Shell_Active_Data[wk->player_number][dir_step][Lv][Rnd];
}


/* provisional name */
s32 calc_abs_diff(s16 a, s16 b) {
    a -= b;
    if (a < 0) {
        a = -a;
    }
    return a;
}



s32 Check_Behind(PLW* wk, WORK_Other* tmw) {
    if (!wk->wu.rl_waza) {
        if (wk->wu.xyz[0].disp.pos < tmw->wu.xyz[0].disp.pos) {
            return 1;
        }
        return 0;
    }
    if (wk->wu.xyz[0].disp.pos > tmw->wu.xyz[0].disp.pos) {
        return 1;
    }
    return 0;
}



s32 Ck_Distance_XX(PLW* wk) {
    if (Ck_Distance_Wall(wk) == 0) {
        return 0;
    }
    if (PL_Distance[wk->wu.id] >= Distance_XX_Data[wk->player_number][0] &&
        PL_Distance[wk->wu.id] <= Distance_XX_Data[wk->player_number][1]) {
        Distance_XX_Index[wk->wu.id] = Distance_XX_Data[wk->player_number][2];
        return 1;
    }
    return 0;
}



/* provisional name */
s32 Ck_Distance_Wall(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    s16 xx;
    if (wk->wu.rl_waza) {
        xx = bg_w.bgw[1].r_limit2 + bg_w.pos_offset - em->xyz[0].disp.pos;
        if (xx <= 96) {
            return 0;
        }
    } else {
        xx = em->xyz[0].disp.pos - bg_w.bgw[1].l_limit2 + bg_w.pos_offset;
        if (xx <= 96) {
            return 0;
        }
    }
    return 1;
}



void Setup_Lever_LR(wk, PL_id, Lever)
PLW* wk;
s16 PL_id;
s16 Lever;
{
    if (Lever == 0) {
        Lever_LR[PL_id] = 0;
    } else {
        if (Lever & 0x1000) {
            Lever_LR[PL_id] = LEVER_UP;
        }
        else if (Lever & 0x2000) {
            Lever_LR[PL_id] |= LEVER_DOWN;
        }
        if (Lever & 0x4000) {
            Lever_LR[PL_id] |= Setup_Guard_Lever(wk, 0);
        } else {
            if (Lever & 0x8000) {
                Lever_LR[PL_id] |= Setup_Guard_Lever(wk, 1);
            }
        }
    }
}



s32 Check_Exit_Term(wk, em, Exit_No)
PLW* wk;
WORK* em;
s16 Exit_No;
{
    s16 xx;
    if (VS_Jump_Term(wk, em, &xx) != 0) {
        return xx;
    }
    return Exit_Term_Tbl[Exit_No](wk, em);
}



s32 VS_Jump_Term(wk, em, xx)
PLW* wk;
WORK* em;
s16* xx;
{
    if (Attack_Flag[wk->wu.id] == 0) {
        return 0;
    }
    switch (My_char[em->id]) {
    case PL_ALEX:
        if (Check_F_Cross_Chop(wk, em, 0xF) != 0) {
            return *xx = 3;
        }
        break;
    case PL_YUN:
    case PL_YANG:
        if (Check_Special_Technique(wk, em, 0, 0, 0x2B, -1, -1) != 0) {
            return *xx = 2;
        }
        break;
    case PL_NECRO:
        if (Check_Special_Technique(wk, em, 0, 0, 0x2A, -1, -1) != 0) {
            return *xx = 2;
        }
        if (Check_Limited_Jump_Attack(wk, em, 0x14, 4) != 0) {
            VS_Tech[wk->wu.id] = 0xF;
            return *xx = 3;
        }
        break;
    case PL_ELENA:
        if (Check_Limited_Jump_Attack(wk, em, 0x14, 5) != 0) {
            VS_Tech[wk->wu.id] = 0xF;
            return *xx = 3;
        }
        break;
    case PL_ORO:
        if (Check_Special_Technique(wk, em, 0xF, 8, 0x2C, 1, -1) != 0) {
            return *xx = 3;
        }
        break;
    }
    return 0;
}



s32 Exit_Term_0000(PLW* wk, WORK* em) {
    switch (Term_No[wk->wu.id]) {
    case TERM_INIT:
        Term_No[wk->wu.id]++;
        Timer_00[wk->wu.id] = 30;
        break;
    default:
        if (--Timer_00[wk->wu.id]) {
            break;
        }
        Timer_00[wk->wu.id] = 1;
        return 1;
    }
    return 0;
}


s32 Exit_Term_0001(PLW* wk, WORK* em) {
    return 1;
}



s32 Exit_Term_0002(PLW* wk, WORK* em) {
    if (em->routine_no[1] == PLAYER_CATCH) {
        return 1;
    }
    if (em->id != 0xD) {
        return 1;
    }
    return 0;
}



s32 Exit_Term_0003(PLW* wk, WORK* em) {
    switch (Term_No[wk->wu.id]) {
    case TERM_INIT:
        Term_No[wk->wu.id]++;
        Timer_00[wk->wu.id] = 10;
        break;
    default:
        if (--Timer_00[wk->wu.id]) {
            break;
        }
        if (Check_SHINRYU(wk)) {
            return 0;
        }
        Timer_00[wk->wu.id] = 1;
        return 1;
    }
    return 0;
}



s32 Exit_Term_0004(PLW* wk, WORK* em) {
    switch (Term_No[wk->wu.id]) {
    case TERM_INIT:
        Term_No[wk->wu.id]++;
        Timer_00[wk->wu.id] = 1;
        break;
    default:
        if (--Timer_00[wk->wu.id]) {
            break;
        }
        if (Check_SHINRYU(wk)) {
            return 0;
        }
        Timer_00[wk->wu.id] = 1;
        return 1;
    }
    return 0;
}



s32 Exit_Term_0005(PLW* wk, WORK* em) {
    switch (Term_No[wk->wu.id]) {
    case TERM_INIT:
        Term_No[wk->wu.id]++;
        Timer_00[wk->wu.id] = 5;
        break;
    default:
        if (--Timer_00[wk->wu.id]) {
            break;
        }
        if (Check_SHINRYU(wk)) {
            return 0;
        }
        Timer_00[wk->wu.id] = 1;
        return 1;
    }
    return 0;
}



s32 Exit_Term_0006(PLW* wk, WORK* em) {
    switch (Term_No[wk->wu.id]) {
    case TERM_INIT:
        Term_No[wk->wu.id]++;
        Timer_00[wk->wu.id] = 60;
        break;
    default:
        if (--Timer_00[wk->wu.id]) {
            break;
        }
        if (Check_SHINRYU(wk)) {
            return 0;
        }
        Timer_00[wk->wu.id] = 1;
        return 1;
    }
    return 0;
}



s32 Exit_Term_0007(PLW* wk, WORK* em) {
    switch (Term_No[wk->wu.id]) {
    case TERM_INIT:
        Term_No[wk->wu.id]++;
        Timer_00[wk->wu.id] = 30;
    default:
        if (Check_Drop_Term(em, 0x28) != 0) {
            if (Area_Number[wk->wu.id] >= 3) {
                return 1;
            }
            VS_Tech[wk->wu.id] = 0x1A;
            return -1;
        }
        if (--Timer_00[wk->wu.id]) {
            break;
        }
        Timer_00[wk->wu.id] = 1;
        return 1;
    }
    return 0;
}




s32 Check_Drop_Term(em, Y)
WORK* em;
s16 Y;
{
    if (em->mvxy.a[1].real.h >= 0) {
        return 0;
    }
    if (em->xyz[1].disp.pos >= Y) {
        return 0;
    }
    return 1;
}



s32 Check_SHINRYU(PLW* wk) {
    PLW* em;
    em = (PLW*)wk->wu.target_adrs;
    if (em->sa->ok != -1) {
        return 0;
    }
    if (My_char[em->wu.id] != PL_KEN) {
        return 0;
    }
    if (plw[em->wu.id].sa->kind_of_arts != 1) {
        return 0;
    }
    return 1;
}



void ETC_Term(wk, Exit_No, Next_Action, Next_Menu)
PLW* wk;
s16 Exit_No;
u32 Next_Action;
s16 Next_Menu;
{
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (ETC_Term_Tbl[Exit_No](wk, em)) {
        Disposal_Again[wk->wu.id] = 1;
        CP_Index[wk->wu.id][0]++;
        CP_Index[wk->wu.id][1] = 0;
        CP_Index[wk->wu.id][2] = 0;
        CP_Index[wk->wu.id][3] = 0;
        Flip_Flag[wk->wu.id] = 0;
        Limited_Flag[wk->wu.id] = 0;
    } else {
        Disposal_Again[wk->wu.id] = 1;
        Next_Another_Menu(wk, Next_Action, Next_Menu);
    }
}



s32 ETC_Term_0000(PLW* wk, WORK* em) {
    if (Check_VS_Squat(wk, em, 0x1D, 0x21, 0x20) != 0) {
        return 1;
    }
    return 0;
}



s32 ETC_Term_0001(PLW* wk, WORK* em) {
    if (wk->sa->ok != -1) {
        return 0;
    }
    if (My_char[wk->wu.id] != PL_ORO) {
        return 0;
    }
    if (!plw[wk->wu.id].sa->kind_of_arts) {
        return 1;
    }
}



s32 ETC_Term_0002(PLW* wk, WORK* em) {
    if (plw[wk->wu.id].wu.vital_new <= 48) {
        return 1;
    }
    return 0;
}



s32 ETC_Term_0003(PLW* wk, WORK* em) {
    if ((em->pat_status != 32) && (em->pat_status != 33) && (em->pat_status != 2)) {
        return 1;
    }
    return 0;
}



s32 ETC_Term_0004(PLW* wk, WORK* em) {
    if (em->vital_new >= 49) {
        return 0;
    }
    if (plw[wk->wu.id].wu.vital_new < 120) {
        return 0;
    }
    return 1;
}



/* provisional name */
void Setup_Com_Max_Range(void) {
    s16 limit;
    s16 xx;
    const s16* row;
    u8 type = CC_Type;
    if (type == 2) {
        limit = Level_18_Data[type][Game_setting.Difficulty][14] + 20;
    } else {
        limit = ((const s16*)&Level_18_Data[type][Game_setting.Difficulty][0])[16] + 20;
    }
    if (type == 2) {
        xx = Level_18_Data[type][8][14] + 20;
    } else {
        xx = Level_18_Data[type][8][16] + 20;
    }
    if (limit < xx) {
        limit = xx;
    }
    if (type == 2) {
        xx = Level_10_Data[type][0][7] + 20;
    } else {
        xx = Level_10_Data[type][0][8] + 20;
    }
    if (limit < xx) {
        limit = xx;
    }
    xx = Level_08_Data[type][0][6] + 20;
    if (limit < xx) {
        limit = xx;
    }
    xx = Level_08_Data[type][1][6] + 20;
    if (limit < xx) {
        limit = xx;
    }
    row = Level_08_Data[type][2];
    xx = row[6] + 20;
    if (limit < xx) {
        limit = xx;
    }
    xx = Level_04_Data[type][0][2] + 20;
    if (limit < xx) {
        limit = xx;
    }
    Limit_Time = limit;
}



/* provisional name: an empty routine nothing calls */
void Com_Sub_Dummy(void) {
}
