/*
 * CONTINUE.C  Continue scene
 *
 * continue_task runs Continue_Scene once a frame: it puts up the countdown objects and the continue
 * music, waits for the loser's countdown to run out, asks Check_Exit_Continue whether the scene may end
 * and then hands over to the game flow (G_No1 = G1_GAME_OVER) and ends the task. Check_Count_Cut and Check_Coin_In
 * read the buttons and the coin chutes; Disp_Personal_Count, Clear_Personal_Data and Clear_Win_Type are
 * small helpers for the player number display, the per-player records and the win-type marks.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "eff87.h"
#include "eff88.h"
#include "eff89.h"
#include "eff90.h"
#include "eff91.h"
#include "eff92_code.h"
#include "Eff93.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "SYS_sub.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sc_trans.h"
#include "cmb_win.h"
#include "Eff95.h"
#include "EFFB8.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "eff56.h"
#include "eff57.h"
#include "EFF58.h"
#include "Eff76.h"
#include "EFFA7.h"
#include "effa8.h"
#include "effa9.h"
#include "aboutspr.h"
#include "bg000.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "win_2.h"
#include "continue.h"
#include "fighter.h"
#include "Entry.h"

/* Cont_No: the Continue_Scene step (the last one, default, waits Cont_Timer and ends the task) */
#define CONT_INIT       0       /* start the count */
#define CONT_COUNT      1       /* until the continue count runs out */
#define CONT_EXIT       2       /* until Check_Exit_Continue gives the time left */



/* effect_49_init takes two arguments */
s32 effect_49_init();


s16 Cont_No;  /* 020138E4 */
s16 Cont_Sub_No;  /* 020138E6 */
s16 Cont_Sub2_No;  /* 020138E8 */
s16 Cont_Sub3_No;  /* 020138EA */
s16 Cont_Timer;  /* 020138EC */



void continue_task(void) {
    for (;;) {
        Continue_Scene();
        task_sleep(1);
    }
}



void Continue_Scene(void) {
    s16 i;
    switch (Cont_No) {
    case CONT_INIT:
        Cont_No++;
        Clear_Flash_No();
        for (i = 0; i < 10; i++) {
            effect_49_init(i, i * 4 + 1);
        }
        sound_request(0x99);
        BGM_Request(9);
        break;
    case CONT_COUNT:
        if (Continue_Count[LOSER] < 0) {
            Cont_No++;
        }
        break;
    case CONT_EXIT:
        if (Cont_Timer = Check_Exit_Continue()) {
            Cont_No++;
        }
        break;
    default:
        if (--Cont_Timer == 0) {
            G_No1 = G1_GAME_OVER;
            G_No2 = G2_OVER_INIT;
            destroy_current_task();
        }
        break;
    }
}



/* The frames to wait before the continue scene ends, or 0 while it may not: 0 while either player is
   in name entry; 60 when the other player is out (ENTRY_NONE); 1 when both are out or waiting for name
   entry (ENTRY_NAME_WAIT); 0 otherwise. */
s32 Check_Exit_Continue(void) {
    s16* p;
    s8 id;
    if (E_Number[0][0] == ENTRY_NAME || E_Number[1][0] == ENTRY_NAME) {
        return 0;
    }
    id = LOSER;
    p = E_Number[id ^ 1];
    if (p[0] == ENTRY_NONE) {
        return 60;
    }
    if (p[0] != ENTRY_NAME_WAIT && p[0] != ENTRY_NONE) {
        return 0;
    }
    if (E_Number[id][0] != ENTRY_NAME_WAIT && E_Number[id][0] != ENTRY_NONE) {
        return 0;
    }
    return 1;
}



/* Prints a player's continue count beside the continue message on the text layer. */
void Disp_Personal_Count(id, count)
s16 id;
char count;
{
    if (id) {
        tilemap_print_hex_block(ENTRY_MSG_X_PAIRS[3][1][Game_setting.Screen_Mode] + 13, Text_Page_Y, 18, count, 1, 1);
    } else {
        tilemap_print_hex_block(ENTRY_MSG_X_PAIRS[3][0][Game_setting.Screen_Mode] + 13, Text_Page_Y, 18, count, 1, 1);
    }
}



/* Nonzero when the player newly presses a button while Continue_Count is below Limit: the press cuts the
   continue count short. */
s32 Check_Count_Cut(PL_id, Limit)
s16 PL_id;
s16 Limit;
{
    s16 sw;
    if (Continue_Count[PL_id] >= Limit) {
        return 0;
    }
    if (PL_id) {
        sw = p2sw_0 & ~p2sw_1;
    } else {
        sw = p1sw_0 & ~p1sw_1;
    }
    return sw & 0x7F0;
}



/* Resets one player's personal game data (records, continue counts, selections and entry state) for a fresh
   start. */
s32 Clear_Personal_Data(PL_id)
s16 PL_id;
{
    s16 i;
    Score[PL_id][SCORE_CPU] = 0;
    Continue_Coin[PL_id] = 0;
    Win_Record[PL_id] = 0;
    VS_Index[PL_id] = -1;
    Used_char[PL_id] = 0xFF;
    Arts_Y[PL_id] = 0;
    Continue_Count[PL_id] = 0;
    Continue_Coin2[PL_id] = 0;
    Sel_PL_Complete[PL_id] = 0;
    Sel_Arts_Complete[PL_id] = 0;
    Personal_Continue_Flag[PL_id] = 0;
    Last_Super_Arts[PL_id] = 0;
    Last_My_char[PL_id] = -1;
    Select_Start[PL_id] = 0;
    paring_ctr_vs[0][PL_id] = 0;
    paring_ctr_vs[1][PL_id] = 0;
    SC_Personal_Time[PL_id] = 481;
    card_pl_work_clear(PL_id);
    E_Number[PL_id][0] = ENTRY_NONE;
    E_Number[PL_id][1] = 0;
    E_Number[PL_id][2] = 0;
    E_Number[PL_id][3] = 0;
    E_07_Flag[PL_id] = 0;
    Cursor_Y[PL_id] = 0;
    if (PL_id) {
        Cursor_X[1] = 4;
    } else {
        Cursor_X[0] = 0;
    }
    if (Continue_Flag == 0) {
        Last_Player_id = -1;
        for (i = 0; i <= 12; i++) {
            Break_Com[PL_id][i] = 0;
        }
    }
}



void Clear_Win_Type(void) {
    s16 i;
    for (i = 0; i < 4; i++) {
        win_type[0][i] = 0;
        win_type[1][i] = 0;
    }
}



/* Nonzero when a coin dropped in the player's chute this frame; in chute modes 0 and 1 a coin in either chute
   counts. */
s32 Check_Coin_In(pl)
s16 pl;
{
    s32 sw1 = coin_chute1_w.dropped;
    s32 sw2 = coin_chute2_w.dropped;
    switch (Chute_Mode) {
    case 0:
    case 1:
        return sw1 | sw2;
    }
    switch (pl) {
    case 0:
        return sw1;
    default:
        return sw2;
    }
}
