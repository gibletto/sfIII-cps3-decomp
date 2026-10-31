/*
 * COM_PL.C  Computer player control
 *
 * CPU_Sub is called by PLMAIN for each CPU player and returns its lever data. Main_Program measures
 * distance and area and runs the CPU state from Com_Jmp_Tbl (Com_Initialize, Com_Free, Com_Active,
 * Com_Follow, Com_Passive, Com_Guard, Com_VS_Shell, Com_Damage, Com_Float, Com_Flip, Com_Caught,
 * Com_Catch, Com_Wait_Lie), which run the per-character patterns (13 characters).
 * The level tables (Receive_Data, Guard_Data, Get_Up_*, Flip_Attack_Data) are indexed by character;
 * the flip state has three steps (Flip_Zero, Flip_1st, Flip_2nd); a caught or catching CPU rapids from
 * fixed tables, and Check_Hamari watches a run of the same attack.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Sub.h"
#include "ACTIVE00.h"
#include "active01.h"
#include "active02.h"
#include "active03.h"
#include "active04.h"
#include "active05.h"
#include "active07.h"
#include "active08.h"
#include "active09.h"
#include "active11.h"
#include "active12.h"
#include "FOLLOW01.h"
#include "FOLLOW02.h"
#include "fifo.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "pass00.h"
#include "PASS01.h"
#include "PASS02.h"
#include "PASS03.h"
#include "PASS04.h"
#include "PASS05.h"
#include "PASS07.h"
#include "PASS08.h"
#include "PASS09.h"
#include "PASS11.h"
#include "PASS12.h"
#include "SHELL00.h"
#include "SHELL01.h"
#include "SHELL03.h"
#include "SHELL04.h"
#include "SHELL11.h"
#include "SHELL12.h"
#include "Entry.h"
#include "entry_2.h"
#include "CMD_MAIN.h"
#include "cmd_main_2.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "PLS02.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sc_trans.h"
#include "Manage.h"
#include "manage_2.h"
#include "bg0001.h"
#include "Com_Pl.h"
#include "cps3.h"
#include "fighter.h"
#include "RANKING.h"

/* CP_No[pl][1] under COM_DAMAGE: the Damage_Jmp_Tbl routine (2 and 3 only get up) */
#define DMG_DECIDE      0       /* Damage_1st: dizzy, a plain hit or a knockdown; choose the get-up */
#define DMG_HIT         1       /* Damage_2nd: a hit without a knockdown */
#define DMG_GETUP_SP    4       /* Damage_5th: a special move (command 46) on getting up */
#define DMG_GETUP_ATTACK 5      /* Damage_6th: an attack from Get_Up_Action_Tech_Data on getting up */
#define DMG_GUARD_0     6       /* Damage_7th with Guard_Type 0 */
#define DMG_GUARD_1     7       /* Damage_7th with Guard_Type 1 */
#define DMG_GUARD_2     8       /* Damage_7th with Guard_Type 2 */
#define DMG_FAINT       9       /* Damage_8th: dizzy, mash the lever */

/* CP_No[pl][2] in Damage_1st */
#define D1_DECIDE       0       /* decide on the hit */
#define D1_DOWN         1       /* knocked down: when it ends, choose the get-up */

/* CP_No[pl][2] in Damage_5th and Damage_6th */
#define DG_DOWN         0       /* until the get-up (cg_type 9 or 12) */
#define DG_COMMAND      1       /* enter the command */
#define DG_ATTACK       2       /* (default) until the move is over */

/* CP_No[pl][2] in Damage_7th */
#define D7_INIT         0       /* set the guard type */
#define D7_GUARD        1       /* (default) guard until free */

/* CP_No[pl][2] in Damage_8th */
#define D8_WAIT         0       /* until dizzy */
#define D8_MASH         1       /* mash the lever */

/* CP_No[pl][2] in Float_2nd, Float_3rd and Float_4th */
#define FLOAT_INIT      0       /* set up the lever */
#define FLOAT_RUN       1       /* (default) hold it until free */

/* CP_No[pl][2] in Flip_Zero */
#define FZ_WAIT         0       /* while the opponent attacks, until a parry is right */
#define FZ_PARRY        1       /* parry for Timer_00 frames */

/* CP_No[pl][1] in Com_Caught and Com_Catch */
#define THROW_INIT      0       /* set up */
#define THROW_WAIT      1       /* until the throw is over */



/* The CPU player's lever data for this frame (0 while the fight does not allow input). */
s32 CPU_Sub(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Allow_a_battle_f == 0 || pcon_dp_flag == 1) {
        return 0;
    }
    Lever_Buff[wk->wu.id] = 0;
    if (em->pat_status == 38) {
        Lie_Flag[wk->wu.id] = 1;
    } else {
        Lie_Flag[wk->wu.id] = 0;
    }
    Last_Pattern_Index[wk->wu.id] = Pattern_Index[wk->wu.id];
    Main_Program(wk);
    Check_Store_Lv(wk);
    Shift_Resume_Lv(wk);
    return Lever_Buff[wk->wu.id];
}



/* Measure the distance and area, then run the CPU state CP_No[id][0] (twice when it sets
   Disposal_Again). */
void Main_Program(PLW* wk) {
    void (*Com_Jmp_Tbl[16])(PLW*) = { Com_Initialize, Com_Free, Com_Active, Com_Before_Follow, Com_Follow, Com_Before_Passive, Com_Passive, Com_Guard, Com_VS_Shell, Check_No12_Shell_Guard, Com_Damage, Com_Float, Com_Flip, Com_Caught, Com_Wait_Lie, Com_Catch };
    Ck_Distance(wk);
    Area_Number[wk->wu.id] = Ck_Area(wk);
    Attack_Flag[wk->wu.id] = plw[wk->wu.id ^ 1].caution_flag;
    Check_At_Count(wk);
    Disposal_Again[wk->wu.id] = 0;
    Com_Jmp_Tbl[CP_No[wk->wu.id][0]](wk);
    if (Disposal_Again[wk->wu.id]) {
        Com_Jmp_Tbl[CP_No[wk->wu.id][0]](wk);
    }
}



void Com_Initialize(PLW* wk) {
    const s16* xx;
    s16 i;
    register s16 j;
    CP_No[wk->wu.id][0] = COM_FREE;
    CP_No[wk->wu.id][1] = 0;
    CP_No[wk->wu.id][2] = 0;
    CP_No[wk->wu.id][3] = 0;
    Lever_Squat[wk->wu.id] = 0;
    Lever_Store[wk->wu.id][0] = 0;
    Lever_Store[wk->wu.id][1] = 0;
    Lever_Store[wk->wu.id][2] = 0;
    Attack_Counter[wk->wu.id] = 0;
    Bullet_No[wk->wu.id] = 0;
    Last_Attack_Counter[wk->wu.id] = -1;
    Guard_Counter[wk->wu.id] = -1;
    Turn_Over_Timer[wk->wu.id] = 1;
    Attack_Count_Index[wk->wu.id] = 0;
    xx = Area_Unit_Data[wk->player_number];
    Separate_Area[wk->wu.id][0] = xx[0];
    Separate_Area[wk->wu.id][1] = xx[1];
    Separate_Area[wk->wu.id][2] = xx[2];
    xx = Shell_Area_Unit_Data[wk->player_number];
    Shell_Separate_Area[wk->wu.id][0] = xx[0];
    Shell_Separate_Area[wk->wu.id][1] = xx[1];
    Shell_Separate_Area[wk->wu.id][2] = xx[2];
    Com_Width_Data[wk->wu.id] = PL_Body_Width_Data[wk->player_number];
    Clear_Com_Flag(wk);
    Standing_Master_Timer[wk->wu.id] = Setup_Next_Stand_Timer(wk);
    Squat_Master_Timer[wk->wu.id] = Setup_Next_Squat_Timer(wk);
    Setup_Bullet_Counter(wk);
    for (i = 0; i < 20; i++) {
        (&Resume_Lever[wk->wu.id][0])[i] = 0;
    }
    for (j = 0; j < 3; j++) {
        Attack_Count_Buff[wk->wu.id][j] = -1;
    }
}



/* Unless hit or thrown, choose the next active pattern (Select_Active): COM_ACTIVE. */
void Com_Free(PLW* wk) {
    s16 xx;
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    if (Check_Damage(wk)) {
        return;
    }
    if (Check_Caught(wk)) {
        return;
    }
    CP_No[wk->wu.id][0] = COM_ACTIVE;
    CP_No[wk->wu.id][1] = 0;
    CP_No[wk->wu.id][2] = 0;
    CP_No[wk->wu.id][3] = 0;
    if (Before_Look[wk->wu.id]) {
        xx = Standing_Timer[wk->wu.id];
    } else {
        xx = 0;
    }
    Clear_Com_Flag(wk);
    Standing_Timer[wk->wu.id] = xx;
    for (xx = 0; xx <= 7; xx++) {
        CP_Index[wk->wu.id][xx] = 0;
    }
    Select_Active(wk);
}



/* Wait Timer_00 frames, reacting to a hit, a throw, a guard or a parry chance, then choose a
   follow-up pattern (Decide_Follow_Menu): COM_FOLLOW. */
void Com_Before_Follow(PLW* wk) {
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    if (Check_Damage(wk)) {
        return;
    }
    if (Check_Caught(wk)) {
        return;
    }
    if (Check_Guard(wk)) {
        return;
    }
    if (Check_Flip(wk)) {
        return;
    }
    if (--Timer_00[wk->wu.id] != 0) {
        return;
    }
    Decide_Follow_Menu(wk);
    CP_No[wk->wu.id][0] = COM_FOLLOW;
    CP_No[wk->wu.id][1] = 0;
    CP_No[wk->wu.id][2] = 0;
    CP_No[wk->wu.id][3] = 0;
    CP_Index[wk->wu.id][0] = 0;
    CP_Index[wk->wu.id][1] = 0;
    CP_Index[wk->wu.id][2] = 0;
    CP_Index[wk->wu.id][3] = 0;
    Clear_Com_Flag(wk);
}



void Com_Before_Passive(PLW* wk) {
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    if (Check_Damage(wk)) {
        return;
    }
    if (Check_Caught(wk)) {
        return;
    }
    if (Check_Flip(wk)) {
        return;
    }
    if (Limited_Flag[wk->wu.id]) {
    } else if (Counter_Attack[wk->wu.id]) {
    } else if (Passive_Guard_Off_Data[wk->player_number][Pattern_Index[wk->wu.id]]) {
    } else if (Check_Guard(wk)) {
        return;
    }
    if (--Timer_00[wk->wu.id] != 0) {
        return;
    }
    CP_No[wk->wu.id][0] = COM_PASSIVE;
    CP_No[wk->wu.id][1] = 0;
    CP_No[wk->wu.id][2] = 0;
    CP_No[wk->wu.id][3] = 0;
    CP_Index[wk->wu.id][0] = 0;
    CP_Index[wk->wu.id][1] = 0;
    CP_Index[wk->wu.id][2] = 0;
    CP_Index[wk->wu.id][3] = 0;
}



void Com_Guard(PLW* wk) {
    WORK* em;
    if (Check_Caught(wk)) {
        return;
    }
    if (Check_Flip(wk)) {
        return;
    }
    if (wk->wu.routine_no[1] == PLAYER_DAMAGE && PL_Blow_Off_Data[wk->wu.routine_no[2]] == 2) {
        Next_Be_Float(wk);
        return;
    }
    em = (WORK*)wk->wu.target_adrs;
    if (Ck_Exit_Guard(wk, em)) {
        Check_Guard_Type(wk, em);
        return;
    }
    Passive_Flag[wk->wu.id] = 0;
    Passive_Mode = 4;
    if (Ck_Guard_Passive_Term(wk)) {
        Select_Passive(wk);
        return;
    }
    if (!Check_Counter_Attack(wk)) {
        Next_Be_Free(wk);
    } else if (Select_Passive(wk) == -1) {
        Next_Be_Free(wk);
    }
}



s32 Check_Counter_Attack(PLW* wk) {
    s16 xx;
    if (Area_Number[wk->wu.id] >= 3) {
        return 0;
    }
    xx = Type_of_Attack[wk->wu.id] & 0xF8;
    if (xx == 8) {
        VS_Tech[wk->wu.id] = 14;
        return;
    }
    if (xx == 24) {
        VS_Tech[wk->wu.id] = 14;
        return;
    }
    if (xx == 32) {
        VS_Tech[wk->wu.id] = 14;
        return;
    }
    if (xx == 48) {
        VS_Tech[wk->wu.id] = 14;
        return;
    }
    return Check_Hamari(wk);
}



s32 Check_Hamari(PLW* wk) {
    u8 tech;
    s16 xx;
    if (Area_Number[wk->wu.id] >= 2) {
        return 0;
    }
    tech = Attack_Count_Buff[wk->wu.id][0];
    if (tech == 0 || tech == 1) {
        for (xx = 1; xx < 4; xx++) {
            if (Attack_Count_Buff[wk->wu.id][xx] != tech) {
                return 0;
            }
        }
        return VS_Tech[wk->wu.id] = 32;
    }
}



void Check_No12_Shell_Guard(PLW* wk) {
    WORK_Other* tmw;
    if (Check_Caught(wk)) {
        return;
    }
    if (Check_Flip(wk)) {
        return;
    }
    tmw = (WORK_Other*)Shell_Address[wk->wu.id];
    Check_Guard_Type(wk, &tmw->wu);
    if (Timer_00[wk->wu.id] == 0) {
        if (wk->wu.routine_no[1] != PLAYER_DAMAGE) {
            Exit_Damage_Sub(wk);
        }
        if (tmw->wu.routine_no[0] == 2) {
            Exit_Damage_Sub(wk);
        }
        if (tmw->wu.id != 13) {
            Exit_Damage_Sub(wk);
        }
        return;
    }
    Timer_00[wk->wu.id]--;
}



void Check_Guard_Type(PLW* wk, WORK* em) {
    u16* lever = Lever_Buff;
    lever[wk->wu.id] = Setup_Guard_Lever(wk, 1);
    switch (Guard_Type[wk->wu.id]) {
    case 0:
        if (em->att.dipsw & 2) {
            break;
        }
        if (em->att.dipsw & 1) {
            lever[wk->wu.id] |= 2;
        }
        break;
    case 1:
        break;
    case 2:
        lever[wk->wu.id] |= 2;
        break;
    }
}



s32 Ck_Exit_Guard(PLW* wk, WORK* em) {
    s16 Lv;
    if (--Timer_00[wk->wu.id]) {
        return 1;
    }
    Timer_00[wk->wu.id] = 1;
    if (wk->wu.routine_no[1] == PLAYER_DAMAGE) {
        return 1;
    }
    if (Attack_Flag[wk->wu.id]) {
        if (Guard_Counter[wk->wu.id] == Attack_Counter[wk->wu.id]) {
            return 1;
        }
        Guard_Counter[wk->wu.id] = Attack_Counter[wk->wu.id];
        Lv = Setup_Lv10(0);
        if (Demo_Flag == 0 && Weak_PL == wk->wu.id) {
            Lv = 2;
        }
        Lv += CC_Value[0];
        Guard_Type[wk->wu.id] = Guard_Data[wk->player_number][Lv][random_16_com()];
        return 1;
    }
    return 0;
}



/* The character's active patterns (Computer00.., the active files), unless hit, thrown or parrying. */
void Com_Active(PLW* wk) {
    void (*Char_Jmp_Tbl[13])(PLW*) = { Computer00, Computer01, Computer02, Computer03, Computer04, Computer05, Computer02, Computer07, Computer08, Computer09, Computer03, Computer11, Computer12 };
    if (Check_Damage(wk)) {
        return;
    }
    if (Check_Caught(wk)) {
        return;
    }
    if (Check_Flip(wk)) {
        return;
    }
    Pattern_Insurance(wk, 0, 0);
    Char_Jmp_Tbl[wk->player_number](wk);
}



/* The follow-up patterns (Decide_Follow_Menu chose one): every character uses Follow02. */
void Com_Follow(PLW* wk) {
    void (*Follow_Jmp_Tbl[13])(PLW*) = { Follow02, Follow02, Follow02, Follow02, Follow02, Follow02, Follow02, Follow02, Follow02, Follow02, Follow02, Follow02, Follow02 };
    if (Check_Damage(wk)) {
        return;
    }
    if (Check_Caught(wk)) {
        return;
    }
    if (Check_Flip(wk)) {
        return;
    }
    Pattern_Insurance(wk, 3, 2);
    Follow_Jmp_Tbl[wk->player_number](wk);
}



/* The character's passive patterns (Passive00.., the PASS files), unless hit, thrown or parrying. */
void Com_Passive(PLW* wk) {
    void (*Passive_Jmp_Tbl[13])(PLW*) = { Passive00, Passive01, Passive02, Passive03, Passive04, Passive05, Passive02, Passive07, Passive08, Passive09, Passive03, Passive11, Passive12 };
    if (Check_Damage(wk)) {
        return;
    }
    if (Check_Caught(wk)) {
        return;
    }
    if (Check_Flip(wk)) {
        return;
    }
    Pattern_Insurance(wk, 1, 1);
    Passive_Jmp_Tbl[wk->player_number](wk);
}



/* The character's patterns against a projectile (the SHELL files; some characters share one),
   unless hit, thrown or parrying. */
void Com_VS_Shell(PLW* wk) {
    void (*VS_Shell_Jmp_Tbl[13])(PLW*) = { Shell11, Shell01, Shell11, Shell03, Shell04, Shell11, Shell11, Shell11, Shell11, Shell11, Shell03, Shell11, Shell12 };
    if (Check_Damage(wk)) {
        return;
    }
    if (Check_Caught(wk)) {
        return;
    }
    if (Check_Flip(wk)) {
        return;
    }
    Pattern_Insurance(wk, 2, 0);
    VS_Shell_Jmp_Tbl[wk->player_number](wk);
}



void Com_Damage(PLW* wk) {
    void (*Damage_Jmp_Tbl[10])(PLW*) = { Damage_1st, Damage_2nd, Damage_3rd, Damage_4th, Damage_5th, Damage_6th, Damage_7th, Damage_7th, Damage_7th, Damage_8th };
    if (Check_Caught(wk)) {
        return;
    }
    Damage_Jmp_Tbl[CP_No[wk->wu.id][1]](wk);
}



void Damage_1st(PLW* wk) {
    u8 Lv;
    u8 Rnd;
    WORK* em;
    Lever_Buff[wk->wu.id] = LEVER_DOWN;
    switch (CP_No[wk->wu.id][2]) {
    case D1_DECIDE:
        if (wk->py->flag) {
            CP_No[wk->wu.id][1] = DMG_FAINT;
            break;
        }
        if (PL_Blow_Off_Data[wk->wu.routine_no[2]] == 0) {
            CP_No[wk->wu.id][1] = DMG_HIT;
            break;
        }
        CP_No[wk->wu.id][2]++;
        Lv = Setup_Lv08(0);
        if (Demo_Flag == 0 && Weak_PL == wk->wu.id) {
            Lv = 0;
        }
        Rnd = random_32_com();
        if (Receive_Data[wk->player_number][Lv] > Rnd) {
            Receive_Flag[wk->wu.id] = 1;
            break;
        } else {
            break;
        }
    case D1_DOWN:
        if (wk->wu.routine_no[3] == RN3_START) {
            CP_No[wk->wu.id][2] = D1_DECIDE;
            break;
        }
        Lv = Setup_Lv04(0);
        if (Demo_Flag == 0 && Weak_PL == wk->wu.id) {
            Lv = 0;
        }
        Rnd = random_32_com();
        CP_No[wk->wu.id][1] = Get_Up_Data[wk->player_number][Lv][Rnd] + 1;
        CP_No[wk->wu.id][2] = 0;
        if (Get_Up_Action_Check_Data[wk->player_number][CP_No[wk->wu.id][1] - 1][Area_Number[wk->wu.id]] == 1) {
            CP_No[wk->wu.id][1] = Get_Up_Action_Check_Data[wk->player_number][CP_No[wk->wu.id][1] + 1][0];
        }
        if (CP_No[wk->wu.id][1] != DMG_DECIDE) {
            break;
        } else {
            Lv = Setup_Lv10(0);
            if (Demo_Flag == 0 && Weak_PL == wk->wu.id) {
                Lv = 0;
            }
            Rnd = random_16_com();
            Lv += CC_Value[0];
            em = (WORK*)wk->wu.target_adrs;
            Guard_Type[wk->wu.id] = Guard_Data[wk->player_number][Lv][Rnd];
            Check_Guard_Type(wk, em);
            break;
        }
    }
}



void Damage_2nd(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    Check_Guard_Type(wk, em);
    if (wk->wu.routine_no[2] == DAMAGE_STUN) {
        CP_No[wk->wu.id][1] = DMG_FAINT;
        CP_No[wk->wu.id][2] = D8_WAIT;
        return;
    }
    if (Receive_Flag[wk->wu.id] != 0 && plw[wk->wu.id].uot_cd_ok_flag != 0) {
        Lever_Buff[wk->wu.id] = LEVER_DOWN;
    }
    if (wk->wu.routine_no[1] != PLAYER_DAMAGE) {
        Exit_Damage_Sub(wk);
    }
}



void Damage_3rd(PLW* wk) {}



void Damage_4th(PLW* wk) {}



void Damage_5th(PLW* wk) {
    if (wk->wu.routine_no[3] == RN3_START) {
        CP_No[wk->wu.id][1] = DMG_DECIDE;
        CP_No[wk->wu.id][2] = D1_DECIDE;
        return;
    }
    switch (CP_No[wk->wu.id][2]) {
    case DG_DOWN:
        if (wk->wu.routine_no[1] != PLAYER_DAMAGE) {
            Exit_Damage_Sub(wk);
            break;
        }
        if (wk->wu.cg_type == 9) {
            CP_No[wk->wu.id][2]++;
            CP_Index[wk->wu.id][1] = 0;
        }
        break;
    case DG_COMMAND:
        if (Command_Attack_SP(wk, wk->player_number, 46, 8)) {
            CP_No[wk->wu.id][2]++;
        }
        break;
    default:
        if (wk->wu.routine_no[1] != PLAYER_ATTACK || wk->wu.cg_type == 64) {
            Exit_Damage_Sub(wk);
        }
        break;
    }
}



void Damage_6th(PLW* wk) {
    u8 Lv;
    u8 Rnd;
    if (wk->wu.routine_no[3] == RN3_START) {
        CP_No[wk->wu.id][1] = DMG_DECIDE;
        CP_No[wk->wu.id][2] = D1_DECIDE;
        return;
    }
    if (wk->wu.routine_no[2] == DAMAGE_STUN) {
        CP_No[wk->wu.id][1] = DMG_FAINT;
        CP_No[wk->wu.id][2] = D8_WAIT;
        return;
    }
    Lever_Buff[wk->wu.id] = LEVER_DOWN;
    switch (CP_No[wk->wu.id][2]) {
    case DG_DOWN:
        if (wk->wu.routine_no[1] != PLAYER_DAMAGE) {
            Exit_Damage_Sub(wk);
            break;
        }
        if (wk->wu.cg_type == 12) {
            if (Get_Up_Action_Check_Data[wk->player_number][CP_No[wk->wu.id][1] - 1][Area_Number[wk->wu.id]] == 1) {
                CP_No[wk->wu.id][1] = Get_Up_Action_Check_Data[wk->player_number][CP_No[wk->wu.id][1] + 1][0];
            }
            CP_No[wk->wu.id][2]++;
            CP_Index[wk->wu.id][1] = 0;
            Lv = Setup_Lv04(0);
            if (Demo_Flag == 0 && Weak_PL == wk->wu.id) {
                Lv = 0;
            }
            Rnd = random_32_com() & 3;
            CP_Index[wk->wu.id][0] = Get_Up_Action_Tech_Data[wk->player_number][Lv][Rnd];
            if (CP_Index[wk->wu.id][0] == 0xFF) {
                CP_Index[wk->wu.id][0] = Get_Up_Action_Tech_Data[wk->player_number][Lv][0];
                if (plw[wk->wu.id].sa->ok) {
                    if (Arts_Super_Name_Data[wk->player_number][plw[wk->wu.id].sa->kind_of_arts] != -1) {
                        CP_Index[wk->wu.id][0] = Arts_Super_Name_Data[wk->player_number][plw[wk->wu.id].sa->kind_of_arts];
                    }
                }
            }
        }
        break;
    case DG_COMMAND:
        if (Command_Attack_SP(wk, wk->player_number, CP_Index[wk->wu.id][0], 8)) {
            CP_No[wk->wu.id][2]++;
        }
        break;
    default:
        if (Command_Attack_SP(wk, wk->player_number, CP_Index[wk->wu.id][0], 8)) {
            Exit_Damage_Sub(wk);
        }
        break;
    }
}



void Damage_7th(PLW* wk) {
    WORK* em;
    switch (CP_No[wk->wu.id][2]) {
    case D7_INIT:
        if (wk->wu.routine_no[1] != PLAYER_DAMAGE) {
            Exit_Damage_Sub(wk);
            break;
        }
        if (wk->wu.cg_type == 11) {
            CP_No[wk->wu.id][2]++;
            Timer_00[wk->wu.id] = 3;
            switch (CP_No[wk->wu.id][1]) {
            case DMG_GUARD_0:
                Guard_Type[wk->wu.id] = 0;
                break;
            case DMG_GUARD_1:
                Guard_Type[wk->wu.id] = 1;
                break;
            default:
                Guard_Type[wk->wu.id] = 2;
                break;
            }
        }
        break;
    case D7_GUARD:
        if (--Timer_00[wk->wu.id]) {
            break;
        }
        CP_No[wk->wu.id][2]++;
        /* fall through */
    default:
        em = (WORK*)wk->wu.target_adrs;
        Check_Guard_Type(wk, em);
        if (wk->wu.cg_type == 0x40 || wk->wu.routine_no[1] == PLAYER_NORMAL) {
            Exit_Damage_Sub(wk);
        }
        break;
    }
}



void Damage_8th(PLW* wk) {
    s16 Rnd;
    if (wk->wu.routine_no[1] != PLAYER_DAMAGE) {
        Exit_Damage_Sub(wk);
    }
    switch (CP_No[wk->wu.id][2]) {
    case D8_WAIT:
        if (wk->wu.routine_no[2] == DAMAGE_STUN) {
            CP_No[wk->wu.id][2]++;
            Timer_00[wk->wu.id] = 1;
            Timer_01[wk->wu.id] = Faint_Rapid_Data[Setup_Lv08(0)][(Rnd = random_16_com() & 7)];
        }
        break;
    case D8_MASH:
        Lever_Buff[wk->wu.id] = Com_Rapid_Sub(wk, 0, &CP_No[wk->wu.id][3]);
        break;
    }
}



void Exit_Damage_Sub(PLW* wk) {
    Clear_Com_Flag(wk);
    if (Check_Passive(wk)) {
        return;
    }
    Next_Be_Free(wk);
}



s32 Check_Damage(PLW* wk) {
    if (wk->wu.routine_no[1] == PLAYER_DAMAGE && CP_No[wk->wu.id][0] != COM_GUARD && CP_No[wk->wu.id][0] != COM_SHELL_GUARD &&
        Guard_Flag[wk->wu.id] == 0) {
        CP_No[wk->wu.id][0] = COM_DAMAGE;
        CP_No[wk->wu.id][1] = DMG_DECIDE;
        CP_No[wk->wu.id][2] = D1_DECIDE;
        CP_No[wk->wu.id][3] = 0;
        Receive_Flag[wk->wu.id] = 0;
        Lever_Buff[wk->wu.id] = LEVER_DOWN;
        Clear_Com_Flag(wk);
        return 1;
    }
    return 0;
}



void Com_Float(PLW* wk) {
    void (*Float_Jmp_Tbl[4])(PLW*) = { Damage_2nd, Float_2nd, Float_3rd, Float_4th };
    if (Check_Caught(wk)) {
        return;
    }
    if (Check_Flip(wk)) {
        return;
    }
    Float_Jmp_Tbl[CP_No[wk->wu.id][1]](wk);
}



void Float_2nd(PLW* wk) {
    switch (CP_No[wk->wu.id][2]) {
    case FLOAT_INIT:
        CP_No[wk->wu.id][2]++;
        Lever_Buff[wk->wu.id] = BUTTON_LP;
        break;
    default:
        if (wk->wu.routine_no[1] == PLAYER_NORMAL) {
            Next_Be_Free(wk);
            break;
        }
        Check_Damage(wk);
        break;
    }
}



void Float_3rd(register PLW* wk) {
    if (wk->wu.routine_no[1] != PLAYER_DAMAGE) {
        Next_Be_Free(wk);
    }
    switch (CP_No[wk->wu.id][2]) {
    case FLOAT_INIT:
        CP_No[wk->wu.id][2]++;
        Timer_00[wk->wu.id] = 4;
        Lever_Pool[wk->wu.id] = Setup_Guard_Lever(wk, 0);
        Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
        break;
    default:
        if (--Timer_00[wk->wu.id] == 0) {
            Timer_00[wk->wu.id] = 3;
            Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
        }
        break;
    }
}



void Float_4th(PLW* wk) {
    if (wk->wu.routine_no[1] != PLAYER_DAMAGE) {
        Next_Be_Free(wk);
    }
    switch (CP_No[wk->wu.id][2]) {
    case FLOAT_INIT:
        CP_No[wk->wu.id][2]++;
        Timer_00[wk->wu.id] = 4;
        Lever_Pool[wk->wu.id] = Setup_Guard_Lever(wk, 1);
        Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
        return;
    default:
        if (--Timer_00[wk->wu.id] != 0) {
            break;
        }
        Timer_00[wk->wu.id] = 3;
        Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
        break;
    }
}



void Com_Flip(PLW* wk) {
    void (*Flip_Jmp_Tbl[3])(PLW*) = { Flip_Zero, Flip_1st, Flip_2nd };
    if (Check_Damage(wk)) {
        return;
    }
    if (Check_Caught(wk)) {
        return;
    }
    Flip_Jmp_Tbl[CP_No[wk->wu.id][1]](wk);
}



void Flip_Zero(PLW* wk) {
    if (Check_Flip(wk)) {
        return;
    }
    if (--Timer_00[wk->wu.id] != 0) {
        return;
    }
    Exit_Damage_Sub(wk);
}



void Flip_1st(PLW* wk) {
    if (wk->wu.xyz[1].disp.pos <= 0) {
        Exit_Damage_Sub(wk);
    }
}



void Flip_2nd(PLW* wk) {
    if (PL_Damage_Data[wk->wu.routine_no[2]] != 0) {
        return;
    }
    if (Check_Flip_Attack(wk) != 0) {
        if (Select_Passive(wk) == -1) {
            Exit_Damage_Sub(wk);
        }
    } else {
        Exit_Damage_Sub(wk);
    }
}



s32 Check_Flip(PLW* wk) {
    if (Flip_Flag[wk->wu.id]) {
        return 0;
    }
    if (wk->wu.routine_no[1] != PLAYER_NORMAL) {
        return 0;
    }
    if (PL_Damage_Data[wk->wu.routine_no[2]] == 0) {
        return 0;
    }
    CP_No[wk->wu.id][0] = COM_FLIP;
    CP_No[wk->wu.id][1] = 2;
    CP_No[wk->wu.id][2] = 0;
    CP_No[wk->wu.id][3] = 0;
    Timer_00[wk->wu.id] = 12;
    if (wk->wu.xyz[1].disp.pos > 0) {
        CP_No[wk->wu.id][1] = 1;
    }
    return 1;
}

s32 Check_Flip_Attack(PLW* wk) {
    s16 lv;
    s16 rnd;
    lv = Setup_Lv08(0);
    if (Demo_Flag == 0 && Weak_PL == wk->wu.id) {
        lv = 0;
    }
    rnd = random_32_com();
    rnd -= Flip_Term_Correct(wk);
    if (rnd >= Flip_Attack_Data[wk->player_number][CC_Type][lv]) {
        return 0;
    } else {
        Flip_Flag[wk->wu.id] = 0;
        VS_Tech[wk->wu.id] = 13;
        Counter_Attack[wk->wu.id] = 1;
        return 1;
    }
}



void Com_Caught(PLW* wk) {
    s16 Rnd;
    switch (CP_No[wk->wu.id][1]) {
    case THROW_INIT:
        CP_No[wk->wu.id][1]++;
        CP_No[wk->wu.id][2] = 0;
        Timer_00[wk->wu.id] = 1;
        Timer_01[wk->wu.id] = Rapid_Exit_Data[Setup_Lv08(0)][(Rnd = random_16_com() & 7)];
        break;
    case THROW_WAIT:
        if (wk->wu.routine_no[1] != PLAYER_CAUGHT) {
            Check_Damage(wk);
            break;
        }
        Lever_Buff[wk->wu.id] = Com_Rapid_Sub(wk, BUTTON_SHOTS, &CP_No[wk->wu.id][2]);
        break;
    }
}



/* The lever Com_Rapid_Sub adds to the shot, right and left in turn (dir_step). */
const u16 Rapid_Lever_Data[2] = {
    LEVER_RIGHT, LEVER_LEFT,
};

/* Stored after Rapid_Lever_Data; nothing in the program refers to it. */
const u8 Rapid_Lever_Data_tail[4] = {
    0, 0, 0, 0,
};

/* The attack pattern a computer player starts from when it turns active, per character (thirteen). */
const s8 Active_Pattern_Data[13] = {
    9, 9, 37, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
};


s32 Com_Rapid_Sub(PLW* wk, s16 Shot, s16* dir_step) {
    u16 xx;
    if (--Timer_00[wk->wu.id] == 0) {
        Timer_00[wk->wu.id] = Timer_01[wk->wu.id];
        xx = Rapid_Lever_Data[dir_step[0]];
        xx |= Shot;
        dir_step[0]++;
        dir_step[0] &= 1;
        return xx;
    }
    return 0;
}



s32 Check_Caught(PLW* wk) {
    if (wk->wu.routine_no[1] == PLAYER_CAUGHT) {
        CP_No[wk->wu.id][0] = COM_CAUGHT;
        CP_No[wk->wu.id][1] = THROW_INIT;
        CP_No[wk->wu.id][2] = 0;
        CP_No[wk->wu.id][3] = 0;
        Clear_Com_Flag(wk);
        return 1;
    }
    return 0;
}



void Com_Catch(PLW* wk) {
    WORK* em;
    s16 Rnd;
    switch (CP_No[wk->wu.id][1]) {
    case THROW_INIT:
        CP_No[wk->wu.id][1]++;
        CP_No[wk->wu.id][2] = 0;
        Timer_00[wk->wu.id] = 1;
        Timer_01[wk->wu.id] = Rapid_Hit_Data[Setup_Lv04(0)][(Rnd = random_16_com() & 7)];
        break;
    case THROW_WAIT:
        em = (WORK*)wk->wu.target_adrs;
        if (wk->wu.routine_no[1] != PLAYER_CATCH || em->routine_no[1] != PLAYER_CAUGHT) {
            Next_Be_Free(wk);
            break;
        }
        Lever_Buff[wk->wu.id] = Com_Rapid_Sub(wk, BUTTON_SHOTS, &CP_No[wk->wu.id][2]);
        break;
    }
}



void Be_Catch(PLW* wk) {
    CP_No[wk->wu.id][0] = COM_CATCH;
    CP_No[wk->wu.id][1] = THROW_INIT;
    CP_No[wk->wu.id][2] = 0;
    CP_No[wk->wu.id][3] = 0;
    Clear_Com_Flag(wk);
}



void Com_Wait_Lie(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Check_Blow_Off(wk, em, 0)) {
        return;
    }
    Exit_Damage_Sub(wk);
}



s32 Command_Attack_SP(PLW* wk, s8 Pl_Number, s16 Tech_Number, s16 Power_Level) {
    switch (CP_Index[wk->wu.id][1]) {
    case 0:
        CP_Index[wk->wu.id][1]++;
        dash_flag_clear(wk->wu.id);
        Tech_Address[wk->wu.id] = player_cmd[Pl_Number][Tech_Number & 0xFF];
        Tech_Index[wk->wu.id] = 0xC;
        Check_Rapid(wk, Tech_Number);
        Rapid_Index[wk->wu.id] = 0x90;
        Lever_Pool[wk->wu.id] = 0x90;
        break;
    case 1:
        switch (Tech_Address[wk->wu.id][Tech_Index[wk->wu.id]]) {
        default:
        case 1:
        case 10:
            if (Command_Type_00(wk, 8, -1) == -1) {
                CP_Index[wk->wu.id][1] = 99;
            }
            break;
        case 2:
            if (Command_Type_01(wk, Power_Level & 0xF)) {
                CP_Index[wk->wu.id][1]++;
            }
            break;
        }
        if (CP_Index[wk->wu.id][1] == 2) {
            return 1;
        }
        break;
    case 2:
        if (wk->wu.cg_type == 64) {
            Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
            CP_Index[wk->wu.id][1]++;
        }
        /* fall through */
    default:
        Rapid_Sub(wk);
        if (wk->wu.routine_no[1] == PLAYER_NORMAL && plw[wk->wu.id].caution_flag == 0) {
            return 1;
        }
    }
    return 0;
}

/* provisional name */
void Next_Be_Active(PLW* wk) {
    s16 xx;
    CP_No[wk->wu.id][0] = COM_ACTIVE;
    CP_No[wk->wu.id][1] = 0;
    CP_No[wk->wu.id][2] = 0;
    CP_No[wk->wu.id][3] = 0;
    for (xx = 0; xx <= 7; xx++) {
        CP_Index[wk->wu.id][xx] = 0;
    }
    Pattern_Index[wk->wu.id] = Active_Pattern_Data[wk->player_number];
}

void Next_Be_Free(wk)
PLW* wk;
{
    CP_No[wk->wu.id][0] = COM_FREE;
    CP_No[wk->wu.id][1] = 0;
    CP_No[wk->wu.id][2] = 0;
    CP_No[wk->wu.id][3] = 0;
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
}



void Next_Be_Float(PLW* wk) {
    s16 Rnd;
    s16 Lv;
    CP_No[wk->wu.id][0] = COM_FLOAT;
    CP_No[wk->wu.id][2] = 0;
    CP_No[wk->wu.id][3] = 0;
    Clear_Com_Flag(wk);
    Lv = Setup_Lv04(0);
    Rnd = random_16_com();
    CP_No[wk->wu.id][1] = Float_Attack_Data[Lv][Rnd];
}



void Clear_Com_Flag(PLW* wk) {
    Passive_Flag[wk->wu.id] = 0;
    Flip_Flag[wk->wu.id] = 0;
    Counter_Attack[wk->wu.id] = 0;
    Limited_Flag[wk->wu.id] = 0;
    Guard_Flag[wk->wu.id] = 0;
    Before_Jump[wk->wu.id] = 0;
    Shell_Ignore_Timer[wk->wu.id] = 0;
    Pierce_Menu[wk->wu.id] = 0;
    Continue_Menu[wk->wu.id] = 0;
    Standing_Timer[wk->wu.id] = 0;
    Before_Look[wk->wu.id] = 0;
    Attack_Count_No0[wk->wu.id] = 0;
    Turn_Over[wk->wu.id] = 0;
    Jump_Pass_Timer[wk->wu.id][0] = 0;
    Jump_Pass_Timer[wk->wu.id][1] = 0;
    Jump_Pass_Timer[wk->wu.id][2] = 0;
    Jump_Pass_Timer[wk->wu.id][3] = 0;
    Last_Eftype[wk->wu.id] = 0;
}



void Check_At_Count(PLW* wk) {
    WORK* em = (WORK*)wk->wu.target_adrs;
    if (Attack_Count_No0[wk->wu.id] == 0) {
        if (Attack_Flag[wk->wu.id]) {
            Attack_Counter[wk->wu.id]++;
            Attack_Count_No0[wk->wu.id] = 1;
            Type_of_Attack[wk->wu.id] = em->kind_of_waza;
            (&Attack_Count_Buff[wk->wu.id][0])[Attack_Count_Index[wk->wu.id]] = em->kind_of_waza;
            Attack_Count_Index[wk->wu.id]++;
            Attack_Count_Index[wk->wu.id] &= 3;
        }
    } else if (Attack_Flag[wk->wu.id] == 0) {
        Attack_Count_No0[wk->wu.id] = 0;
    }
}



void Shift_Resume_Lv(PLW* wk) {
    s16 xx;
    for (xx = 18; xx >= 0; xx--) {
        Resume_Lever[wk->wu.id][xx + 1] = Resume_Lever[wk->wu.id][xx];
    }
    Resume_Lever[wk->wu.id][0] = Lever_Buff[wk->wu.id];
}



void Check_Store_Lv(PLW* wk) {
    s16 xx = Lever_Buff[wk->wu.id] & LEVER_ALL;
    switch (xx) {
    case LEVER_DOWN:
        Lever_Store[wk->wu.id][0]++;
        break;
    case LEVER_DOWN | LEVER_LEFT:
    case LEVER_DOWN | LEVER_RIGHT:
        Store_LR_Sub(wk);
        Lever_Store[wk->wu.id][0]++;
        break;
    default:
        Lever_Store[wk->wu.id][0] = 0;
        Lever_Store[wk->wu.id][1] = 0;
        Lever_Store[wk->wu.id][2] = 0;
        break;
    }
}



void Store_LR_Sub(PLW* wk) {
    if (wk->wu.rl_waza) {
        if (Lever_Buff[wk->wu.id] & LEVER_RIGHT) {
            Lever_Store[wk->wu.id][1]++;
            Lever_Store[wk->wu.id][2] = 0;
        }
        if (Lever_Buff[wk->wu.id] & LEVER_LEFT) {
            Lever_Store[wk->wu.id][1] = 0;
            Lever_Store[wk->wu.id][2]++;
        }
    } else {
        if (Lever_Buff[wk->wu.id] & LEVER_LEFT) {
            Lever_Store[wk->wu.id][1]++;
            Lever_Store[wk->wu.id][2] = 0;
        }
        if (Lever_Buff[wk->wu.id] & LEVER_RIGHT) {
            Lever_Store[wk->wu.id][1] = 0;
            Lever_Store[wk->wu.id][2]++;
        }
    }
}



void Setup_Bullet_Counter(PLW* wk) {
    Bullet_Counter[wk->wu.id] = 3;
    Bullet_Counter[wk->wu.id] += random_32_com() & 1;
}



/*
 * By character, the highest pattern number of the active, passive, projectile (VS shell) and
 * follow patterns: Pattern_Insurance replaces a Pattern_Index past it with the forced number.
 */
const u8 Pattern_Insurance_Data[13][4] = {
    { 56, 131, 10, 3 },  /* Gill */
    { 55, 127, 9, 3 },  /* Alex */
    { 70, 109, 10, 3 },  /* Ryu */
    { 66, 119, 10, 3 },  /* Yun */
    { 63, 97, 11, 3 },  /* Dudley */
    { 65, 98, 10, 3 },  /* Necro */
    { 56, 130, 10, 3 },  /* Hugo */
    { 63, 202, 10, 3 },  /* Ibuki */
    { 63, 202, 10, 3 },  /* Elena */
    { 79, 111, 10, 3 },  /* Oro */
    { 66, 119, 10, 3 },  /* Yang */
    { 71, 230, 10, 3 },  /* Ken */
    { 83, 218, 10, 3 },  /* Sean */
};


void Pattern_Insurance(PLW* wk, s16 Kind_Of_Insurance, s16 Forced_Number) {
    if (Pattern_Insurance_Data[My_char[wk->wu.id]][Kind_Of_Insurance] < Pattern_Index[wk->wu.id]) {
        Pattern_Index[wk->wu.id] = Forced_Number;
    }
}
