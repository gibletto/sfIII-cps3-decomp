/*
 * ENTRY_2.C  Player entry, credit, continue and break-in
 *
 * entry_task calls Entry_Task every frame; Entry_Task runs the step for the current game phase (E_No0:
 * Entry_00 to Entry_10) and the card message. The steps run Entry_Main_Sub for each player, which
 * follows the player's entry state: joining with a credit (Credit_Sub_1P / _2P, Credit_Continue_1P /
 * _2P, Pay_Start_Credit), the continue countdown (Entry_Continue_Sub), name entry (Name_In_Sub,
 * Naming_Cut_Sub_1P / _2P), losing (Loser_Sub_1P / _2P), game over (In_Game_Sub, Setup_Next_Step) and a
 * second player breaking in (Ck_Break_Into, Break_Into_Sub and Break_Into_02 to _10, which start the
 * break-in banner, effect A2). The flashing INSERT COIN, PRESS START, FREE PLAY and more-coins messages
 * and the credit display (credit_display_render, Disp_Start_Message) are drawn here, and
 * coin_in_sound_request plays the coin sound during the demo.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFA2_MAIN.h"
#include "win_2.h"
#include "continue.h"
#include "pow_pow.h"
#include "n_input.h"
#include "SYS_sub.h"
#include "cmb_win.h"
#include "eff87.h"
#include "eff88.h"
#include "eff89.h"
#include "eff90.h"
#include "eff91.h"
#include "eff92_code.h"
#include "Eff93.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "eeprom.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "sc_trans.h"
#include "sc_clear.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "entry_2.h"



extern const s8 str_INSERT_COIN[];
extern const s8 str_INSERT_COINS[];
extern const s8 str_INSERT_COINS_2[];
extern const s8 str_INSERT_COINS_3[];
extern const s8 str_INSERT_COINS_4[];
extern const s8 str_INSERT_COINS_5[];
extern const s8 str_INSERT_COINS_6[];
extern const s8 str_INSERT_COINS_7[];
extern const s8 str_INSERT_COINS_8[];

/* The insert coin line by coins per credit (coin_chute1_w.per_credit - 1). */
TM_STRING insert_coin_mes[9] = {
    { 2, 0, 18, str_INSERT_COIN },
    { 0, 0, 18, str_INSERT_COINS },
    { 0, 0, 18, str_INSERT_COINS_2 },
    { 0, 0, 18, str_INSERT_COINS_3 },
    { 0, 0, 18, str_INSERT_COINS_4 },
    { 0, 0, 18, str_INSERT_COINS_5 },
    { 0, 0, 18, str_INSERT_COINS_6 },
    { 0, 0, 18, str_INSERT_COINS_7 },
    { 0, 0, 18, str_INSERT_COINS_8 },
};



/* The entry task: runs Entry_Task once a frame, for ever. */
/* provisional name */
void entry_task(void) {
    do {
        Entry_Task();
        task_sleep(1);
    } while (1);
}



void Entry_Task(void) {
    void (*Main_Jmp_Tbl[11])() = { Entry_00, Entry_01, Entry_02, Entry_03, Entry_04, Entry_03, Entry_06, Entry_07, Entry_08, Entry_03, Entry_10 };
    if (Free_Play) {
        credit_1p = 9;
        credit_2p = 9;
    }
    Main_Jmp_Tbl[E_No0]();
    card_msg_disp();
}



void Entry_00(void) {
    switch (E_No1) {
    case 0:
        Text_Page_Y = 0;
        break;
    case 1:
        E_No1++;
        E_Timer = 50;
        if (Free_Play) {
            tilemap_print_string_attr(DE_X[0] + 18, Text_Page_Y + Insert_Y, 18, " FREE PLAY ");
        } else if (Two_Coin_Start) {
            tilemap_print_string(DE_X[0] + 17, Text_Page_Y + Insert_Y, 0xFFFF, &insert_coin_mes[1]);
        } else {
            tilemap_print_string(DE_X[0] + 17, Text_Page_Y + Insert_Y, 0xFFFF, insert_coin_mes + coin_chute1_w.per_credit - 1);
        }
        if (G_No1 == G1_DEMO_PLAY || G_No1 == G1_DEMO_PLAY2) {
            if (Free_Play) {
                tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[2][0][Game_setting.Screen_Mode], Text_Page_Y, 18, " FREE PLAY ");
                tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[2][1][Game_setting.Screen_Mode], Text_Page_Y, 18, " FREE PLAY ");
            } else if (Two_Coin_Start) {
                tilemap_print_string(4, Text_Page_Y, 0xFFFF, &insert_coin_mes[1]);
                tilemap_print_string(DE_X[4] + 29, Text_Page_Y, 0xFFFF, &insert_coin_mes[1]);
            } else {
                tilemap_print_string(4, Text_Page_Y, 0xFFFF, insert_coin_mes + coin_chute1_w.per_credit - 1);
                tilemap_print_string(DE_X[4] + 29, Text_Page_Y, 0xFFFF, insert_coin_mes + coin_chute1_w.per_credit - 1);
            }
        }
        break;
    case 2:
        if (--E_Timer) {
            break;
        }
        E_No1++;
        E_Timer = 30;
        tilemap_print_string_attr(DE_X[0] + 16, Text_Page_Y + Insert_Y, 18, "                  ");
        if (G_No1 == G1_DEMO_PLAY || G_No1 == G1_DEMO_PLAY2) {
            tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[0][0][Game_setting.Screen_Mode] - 2, Text_Page_Y, 18, "                 ");
            tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[0][1][Game_setting.Screen_Mode] - 2, Text_Page_Y, 18, "                 ");
        }
        break;
    case 3:
        if (--E_Timer) {
            break;
        }
        E_No1--;
        E_Timer = 50;
        if (Free_Play) {
            tilemap_print_string_attr(DE_X[0] + 18, Text_Page_Y + Insert_Y, 18, " FREE PLAY ");
        } else if (Two_Coin_Start) {
            tilemap_print_string(DE_X[0] + 17, Text_Page_Y + Insert_Y, 0xFFFF, &insert_coin_mes[1]);
        } else {
            tilemap_print_string(DE_X[0] + 17, Text_Page_Y + Insert_Y, 0xFFFF, insert_coin_mes + coin_chute1_w.per_credit - 1);
        }
        if (G_No1 == G1_DEMO_PLAY || G_No1 == G1_DEMO_PLAY2) {
            if (Free_Play) {
                tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[2][0][Game_setting.Screen_Mode], Text_Page_Y, 18, " FREE PLAY ");
                tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[2][1][Game_setting.Screen_Mode], Text_Page_Y, 18, " FREE PLAY ");
            } else if (Two_Coin_Start) {
                tilemap_print_string(4, Text_Page_Y, 0xFFFF, &insert_coin_mes[1]);
                tilemap_print_string(DE_X[4] + 29, Text_Page_Y, 0xFFFF, &insert_coin_mes[1]);
            } else {
                tilemap_print_string(4, Text_Page_Y, 0xFFFF, insert_coin_mes + coin_chute1_w.per_credit - 1);
                tilemap_print_string(DE_X[4] + 29, Text_Page_Y, 0xFFFF, insert_coin_mes + coin_chute1_w.per_credit - 1);
            }
        }
        break;
    case 4:
    case 5:
        E_No1++;
        break;
    case 6:
        E_No1 = 99;
        tilemap_print_string_attr(DE_X[0] + 18, Text_Page_Y + Insert_Y, 18, " FREE PLAY ");
        if (G_No1 == G1_DEMO_PLAY || G_No1 == G1_DEMO_PLAY2) {
            tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[2][0][Game_setting.Screen_Mode], Text_Page_Y, 18, " FREE PLAY ");
            tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[2][1][Game_setting.Screen_Mode], Text_Page_Y, 18, " FREE PLAY ");
        }
        break;
    }
}



void Entry_01(void) {
    switch (E_No1) {
    case 0:
        E_No1++;
        Text_Page_Y = 0;
        credit_display_render(1);
        Disp_Start_Message();
        break;
    case 1:
        if (credit_display_render(0) != 0) {
            Disp_Start_Message();
        }
        if (~p1sw_1 & p1sw_0 & BUTTON_START) {
            if (Pay_Start_Credit(0) != 0) {
                Entry_01_Sub(0);
            }
        } else if (~p2sw_1 & p2sw_0 & BUTTON_START) {
            if (Pay_Start_Credit(1) != 0) {
                Entry_01_Sub(1);
            }
        }
        break;
    case 2:
        if (((u8)Request_E_No)) {
            E_No1++;
        }
        break;
    default:
        Exit_Title_Sub_Entry();
        break;
    }
}



void Entry_01_Sub(s16 PL_id) {
    E_No1++;
    Request_G_No = 1;
    if (Game_setting.Event) {
        plw[0].wu.operator = 1;
        plw[1].wu.operator = 1;
        Operator_Status[0] = 1;
        Operator_Status[1] = 1;
        Ignore_Entry[0] = 0;
        Ignore_Entry[1] = 0;
    } else {
        plw[PL_id].wu.operator = 1;
        Operator_Status[PL_id] = 1;
        Champion = PL_id;
        plw[PL_id ^ 1].wu.operator = 0;
        Operator_Status[PL_id ^ 1] = 0;
        Ignore_Entry[0] = 0;
        Ignore_Entry[1] = 0;
    }
}



void Exit_Title_Sub_Entry(void) {
    s16 i;
    s16 j;
    E_No0 = E0_SELECT;
    E_No1 = 0;
    E_No2 = 0;
    E_No3 = 0;
    F_No1[0] = F_No2[0] = F_No3[0] = 0;
    F_No1[1] = F_No2[1] = F_No3[1] = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            E_Number[i][j] = 0;
        }
    }
}



void Entry_02(void) {
    switch (E_No1) {
    case 0:
        E_No1++;
        Text_Page_Y = 32;
        break;
    }
    Entry_Main_Sub(0, 2);
    Entry_Main_Sub(1, 2);
}



void Entry_03(void) {
    switch (E_No1) {
    case 0:
        Entry_03_1st();
        break;
    default:
        Entry_03_2nd();
        break;
    }
}



void Entry_03_1st(void) {
    switch (E_No2) {
    case 0:
        E_No2++;
        Text_Page_Y = 32;
        break;
    }
    Entry_Main_Sub(0, 4);
    Entry_Main_Sub(1, 4);
}



void Entry_03_2nd(void) {
    switch (E_No2) {
    case 0:
        if (--E_Timer) {
            break;
        }
        E_No2++;
        Switch_Screen_Init(0, 2);
        break;
    case 1:
        if (Switch_Screen() != 0) {
            E_No2++;
            tilemap_clear_rect(DE_X[3] + 4, Text_Page_Y + 11, DE_X[3] + 43, Text_Page_Y + 14);
            sc_vram_to_ram();
            Switch_Screen_Init(0, 0);
        }
        break;
    case 2:
        if (Switch_Screen() != 0) {
            Cover_Timer = 23;
            G_No1 = G1_SELECT;
            G_No2 = G2_SEL_INIT;
            G_No3 = 0;
            E_No0 = E0_SELECT;
            E_No1 = 0;
            E_No2 = 0;
            E_No3 = 0;
            plw[New_Challenger].wu.operator = 1;
            Operator_Status[New_Challenger] = 1;
            Sel_Arts_Complete[Champion] = -1;
        }
        break;
    }
}



void Entry_04(void) {
    switch (E_No1) {
    case 0:
        Entry_04_1st();
        break;
    default:
        Entry_04_2nd();
        break;
    }
}



void Entry_04_1st(void) {
    switch (E_No2) {
    case 0:
        E_No2++;
        Text_Page_Y = 0;
        break;
    }
    Entry_Main_Sub(0, 5);
    Entry_Main_Sub(1, 5);
}



void Entry_04_2nd(void) {
    switch (E_No2) {
    case 0:
        if (--E_Timer) {
            break;
        }
        E_No2++;
        Switch_Screen_Init(0, 2);
        break;
    case 1:
        if (Switch_Screen() != 0) {
            E_No2++;
            tilemap_clear_rect(DE_X[3] + 4, Text_Page_Y + 11, DE_X[3] + 43, Text_Page_Y + 14);
            sc_vram_to_ram();
            Switch_Screen_Init(3, 3);
        }
        break;
    default:
        if (Switch_Screen() != 0) {
            Cover_Timer = 23;
            G_No1 = G1_SELECT;
            G_No2 = G2_SEL_INIT;
            G_No3 = 0;
            if (E_No3 == -1 && Continue_Flag) {
                E_Number[LOSER][0] = ENTRY_CONTINUE;
                E_Number[LOSER][1] = 0;
                E_Number[LOSER][2] = 0;
                E_Number[LOSER][3] = 0;
            }
            E_No0 = E0_SELECT;
            E_No1 = 0;
            E_No2 = 0;
            E_No3 = 0;
            Game_pause = 0;
            plw[New_Challenger].wu.operator = 1;
            Operator_Status[New_Challenger] = 1;
        }
        break;
    }
}



void Entry_06(void) {
    switch (E_No1) {
    case 0:
        Entry_06_1st();
        break;
    default:
        Entry_06_2nd();
        break;
    }
}



void Entry_06_1st(void) {
    switch (E_No2) {
    case 0:
        E_No2++;
        Text_Page_Y = 0;
        break;
    }
    Entry_Main_Sub(0, 7);
    Entry_Main_Sub(1, 7);
}



void Entry_06_2nd(void) {
    if (E_07_Flag[0] == 0) {
        Entry_Main_Sub(0, 7);
    }
    if (E_07_Flag[1] == 0) {
        Entry_Main_Sub(1, 7);
    }
    switch (E_No2) {
    case 0:
        E_No2++;
        sc_vram_to_ram();
        Switch_Screen_Init(0, 0);
        break;
    case 1:
        if (Switch_Screen() != 0) {
            E_No2++;
            Cover_Timer = 23;
            Switch_Screen_Init(0, 0);
        }
        break;
    default:
        if (Switch_Screen() != 0) {
            G_No1 = G1_SELECT;
            G_No2 = G2_SEL_INIT;
            G_No3 = 0;
            E_No0 = E0_SELECT;
            E_No1 = 0;
            E_No2 = 0;
            E_No3 = 0;
            Fade_Flag = 0;
            if (E_07_Flag[0]) {
                plw[0].wu.operator = 1;
                Operator_Status[0] = 1;
            }
            if (E_07_Flag[1]) {
                plw[1].wu.operator = 1;
                Operator_Status[1] = 1;
            }
            E_07_Flag[0] = 0;
            E_07_Flag[1] = 0;
            if (E_Number[LOSER][0] == ENTRY_LOSER && Continue_Flag != 0) {
                E_Number[LOSER][0] = ENTRY_CONTINUE;
            }
        }
        break;
    }
}



void Entry_07(void) {
    switch (E_No1) {
    case 0:
        Entry_07_1st();
        break;
    default:
        Entry_07_2nd();
        break;
    }
}



void Entry_07_1st(void) {
    switch (E_No2) {
    case 0:
        E_No2++;
        Text_Page_Y = 0;
        break;
    }
    Entry_Main_Sub(0, 8);
    Entry_Main_Sub(1, 8);
}



void Entry_07_2nd(void) {
    if (E_07_Flag[0] == 0) {
        Entry_Main_Sub(0, 8);
    }
    if (E_07_Flag[1] == 0) {
        Entry_Main_Sub(1, 8);
    }
    switch (E_No2) {
    case 0:
        if (--E_Timer) {
            break;
        }
        E_No2++;
        sc_vram_to_ram();
        Switch_Screen_Init(0, 1);
        break;
    default:
        if (Switch_Screen() != 0) {
            Cover_Timer = 23;
            G_No1 = G1_SELECT;
            G_No2 = G2_SEL_INIT;
            G_No3 = 0;
            E_No0 = E0_SELECT;
            E_No1 = 0;
            E_No2 = 0;
            E_No3 = 0;
            if (E_07_Flag[0]) {
                plw[0].wu.operator = 1;
                Operator_Status[0] = 1;
            }
            if (E_07_Flag[1]) {
                plw[1].wu.operator = 1;
                Operator_Status[1] = 1;
            }
            E_07_Flag[0] = 0;
            E_07_Flag[1] = 0;
        }
        break;
    }
}



void Entry_08(void) {
    switch (E_No1) {
    case 0:
        Entry_08_1st();
        break;
    default:
        Entry_08_2nd();
        break;
    }
}



void Entry_08_1st(void) {
    switch (E_No2) {
    case 0:
        E_No2++;
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][0][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][1][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
        if (Game_setting.Event) {
            E_No2 = 99;
        }
        /* fall through */
    case 1:
        Entry_Main_Sub(0, 9);
        Entry_Main_Sub(1, 9);
        break;
    }
}



void Entry_08_2nd(void) {
    if (E_07_Flag[0] == 0) {
        Entry_Main_Sub(0, 9);
    }
    if (E_07_Flag[1] == 0) {
        Entry_Main_Sub(1, 9);
    }
    switch (E_No2) {
    case 0:
        E_No2++;
        if (E_Number[LOSER][0] == ENTRY_GAME_OVER && E_Number[LOSER][1] == 1) {
            Clear_Personal_Data(LOSER);
        }
        sc_vram_to_ram();
        Switch_Screen_Init(0, 1);
        break;
    default:
        if (Switch_Screen() != 0) {
            Cover_Timer = 23;
            G_No1 = G1_SELECT;
            G_No2 = G2_SEL_INIT;
            G_No3 = 0;
            E_No0 = E0_SELECT;
            E_No1 = 0;
            E_No2 = 0;
            E_No3 = 0;
            if (E_07_Flag[0]) {
                plw[0].wu.operator = 1;
                Operator_Status[0] = 1;
            }
            if (E_07_Flag[1]) {
                plw[1].wu.operator = 1;
                Operator_Status[1] = 1;
            }
            E_07_Flag[0] = 0;
            E_07_Flag[1] = 0;
            Request_Disp_Rank[0][RANK_SCORE] = -1;
            Request_Disp_Rank[0][RANK_WINS] = -1;
            Request_Disp_Rank[1][RANK_SCORE] = -1;
            Request_Disp_Rank[1][RANK_WINS] = -1;
        }
        break;
    }
}



void Entry_10(void) {
    switch (E_No1) {
    case 0:
        Entry_10_1st();
        break;
    default:
        Entry_10_2nd();
        break;
    }
}



void Entry_10_1st(void) {
    switch (E_No2) {
    case 0:
        E_No2++;
        Text_Page_Y = 0;
        Score[WINNER][SCORE_CPU] += Continue_Coin[WINNER];
        if (Check_Ranking(WINNER) != 0) {
            E_Number[WINNER][0] = ENTRY_NAME;
            E_Number[WINNER][1] = 0;
            E_Number[WINNER][2] = 0;
            E_Number[WINNER][3] = 0;
            Score[WINNER][SCORE_CPU] += Continue_Coin[WINNER];
            Request_Disp_Rank[WINNER][RANK_SCORE] = Rank_In[WINNER][RANK_SCORE];
            Request_Disp_Rank[WINNER][RANK_WINS] = Rank_In[WINNER][RANK_WINS];
        } else {
            E_Number[WINNER][0] = ENTRY_GAME_OVER;
            E_Number[WINNER][1] = 0;
        }
        /* fall through */
    default:
        Entry_Main_Sub(0, 10);
        Entry_Main_Sub(1, 10);
        break;
    }
}



void Entry_10_2nd(void) {
    if (E_07_Flag[0] == 0) {
        Entry_Main_Sub(0, 10);
    }
    if (E_07_Flag[1] == 0) {
        Entry_Main_Sub(1, 10);
    }
    switch (E_No2) {
    case 0:
        E_No2++;
        if ((E_Number[LOSER][0] == ENTRY_GAME_OVER) && (E_Number[LOSER][1] == 1)) {
            Clear_Personal_Data(LOSER);
        }
        sc_vram_to_ram();
        Switch_Screen_Init(0, 1);
        break;
    default:
        if (Switch_Screen() != 0) {
            Cover_Timer = 23;
            G_No1 = G1_SELECT;
            G_No2 = G2_SEL_INIT;
            G_No3 = 0;
            E_No0 = E0_SELECT;
            E_No1 = 0;
            E_No2 = 0;
            E_No3 = 0;
            if (E_07_Flag[0]) {
                plw[0].wu.operator = 1;
                Operator_Status[0] = 1;
            }
            if (E_07_Flag[1]) {
                plw[1].wu.operator = 1;
                Operator_Status[1] = 1;
            }
            E_07_Flag[0] = 0;
            E_07_Flag[1] = 0;
            Request_Disp_Rank[0][RANK_SCORE] = -1;
            Request_Disp_Rank[0][RANK_WINS] = -1;
            Request_Disp_Rank[1][RANK_SCORE] = -1;
            Request_Disp_Rank[1][RANK_WINS] = -1;
        }
        break;
    }
}



/* One player's entry work for the frame, by E_Number[PL_id][0]: start checks, continue, name entry, game over
   and the loser scene. Jump_Index tells Break_Into_Sub which entry scene a new challenger comes in from. */
void Entry_Main_Sub(PL_id, Jump_Index)
s16 PL_id;
s16 Jump_Index;
{
    ENTRY_X = 0;
    switch (E_Number[PL_id][0]) {
    case ENTRY_NONE:
        if (Game_setting.Event) {
            break;
        }
        if (Ignore_Entry[LOSER]) {
            break;
        }
        if (plw[PL_id].wu.operator == 0) {
            Entry_Common_Sub(PL_id, Jump_Index);
        }
        break;
    case ENTRY_CONTINUE:
        if (PL_id) {
            if (Credit_Continue_2P() != 0) {
                Break_Into_Sub(PL_id, Jump_Index);
            }
        } else if (Credit_Continue_1P() != 0) {
            Break_Into_Sub(PL_id, Jump_Index);
        }
        if (Request_Break[PL_id]) {
            break;
        }
        if ((E_Number[PL_id][0] == ENTRY_CONTINUE) && (E_07_Flag[PL_id ^ 1] == 0)) {
            Entry_Continue_Sub(PL_id);
        }
        break;
    case ENTRY_NAME:
        switch (E_Number[PL_id][1]) {
        case 0:
            E_Number[PL_id][1]++;
            Personal_Timer[PL_id] = 30;
            tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[4][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "          ");
            break;
        case 1:
            if (--Personal_Timer[PL_id] != 0) {
                break;
            }
            E_Number[PL_id][1]++;
            Naming_Cut[PL_id] = 0;
            Name_00[PL_id] = 0;
            name_wk[PL_id].r_no_0 = 0;
            name_wk[PL_id].r_no_1 = 0;
            break;
        case 2:
            if (Forbid_Break == 1) {
                break;
            }
            if (PL_id == 0) {
                Naming_Cut_Sub_1P();
            } else {
                Naming_Cut_Sub_2P();
            }
            if (Name_Input(PL_id) != 0) {
                tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[1][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "             ");
                Name_In_Sub(PL_id);
                if (Naming_Cut[PL_id]) {
                    Clear_Personal_Data(PL_id);
                    break;
                }
                E_Number[PL_id][2] = 0;
                E_Number[PL_id][3] = 0;
                if (E_No0 == E0_GAME_OVER) {
                    E_Number[PL_id][0] = ENTRY_GAME_OVER;
                    E_Number[PL_id][1] = 1;
                } else {
                    E_Number[PL_id][0] = ENTRY_GAME_OVER;
                    E_Number[PL_id][1] = 0;
                }
            }
            break;
        }
        break;
    case ENTRY_NAME_WAIT:
        switch (E_Number[PL_id][1]) {
        case 0:
            if ((E_No0 != E0_GAME_OVER) && (E_No0 != E0_SELECT)) {
                break;
            }
            E_Number[PL_id][0] = ENTRY_NAME;
            E_Number[PL_id][1] = 2;
            E_Number[PL_id][2] = 0;
            E_Number[PL_id][3] = 0;
            Name_00[PL_id] = 0;
            name_wk[PL_id].r_no_0 = 0;
            name_wk[PL_id].r_no_1 = 0;
            tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[4][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "          ");
            break;
        case 1:
            if ((E_No0 != E0_GAME_OVER) && (E_No0 != E0_SELECT)) {
                break;
            }
            E_Number[PL_id][0] = ENTRY_GAME_OVER;
            E_Number[PL_id][1] = 1;
            E_Number[PL_id][2] = 0;
            E_Number[PL_id][3] = 0;
            if (E_No0 == E0_SELECT) {
                E_Number[PL_id][1] = 0;
            }
            break;
        }
        break;
    case ENTRY_GAME_OVER:
        switch (E_Number[PL_id][1]) {
        case 0:
            In_Game_Sub(PL_id);
            break;
        case 1:
            In_Over_Sub(PL_id);
            break;
        }
        break;
    case ENTRY_LOSER:
        Loser_Scene_Sub(PL_id, Jump_Index);
        break;
    }
}



void Naming_Cut_Sub_1P(void) {
    s8 state;
    if (Naming_Cut[0]) {
        return;
    }
    if (Two_Coin_Start != 0 && Request_Break[0] == 0 && credit_1p < 2) {
        state = 99;
    } else {
        state = Request_Break[0] | credit_1p;
    }
    switch (state) {
    case 0:
        break;
    case 99:
        break;
    default:
        if (Ck_Break_Into_SP(p1sw_0, p1sw_1, 0) != 0) {
            Game_pause = 0;
            Naming_Cut[0] = 1;
            Request_Break[0] = 1;
        }
        break;
    }
}



void Naming_Cut_Sub_2P(void) {
    s8 credit;
    s8 state;
    if (Naming_Cut[1]) {
        return;
    }
    if (Two_Coin_Start != 0 && Request_Break[1] == 0 && credit < 2) {
        state = 99;
    } else {
        state = Request_Break[1] | credit;
    }
    switch (state) {
    case 0:
        break;
    case 99:
        break;
    default:
        if (Ck_Break_Into_SP(p2sw_0, p2sw_1, 1) != 0) {
            Game_pause = 0;
            Naming_Cut[1] = 1;
            Request_Break[1] = 1;
        }
        break;
    }
}



/* Writes the entered name into each ranking table the player placed in. */
void Name_In_Sub(PL_id)
s16 PL_id;
{
    s16 xx;

    if (Rank_In[PL_id][RANK_SCORE] >= 0) {
        xx = Rank_In[PL_id][RANK_SCORE];
        Ranking_Data[xx].name[0] = rank_name_w[PL_id].code[0];
        Ranking_Data[xx].name[1] = rank_name_w[PL_id].code[1];
        Ranking_Data[xx].name[2] = rank_name_w[PL_id].code[2];
        if (G_No1 == G1_ENDING) {
            if (Continue_Coin[PL_id]) {
                Ranking_Data[xx].mark = 'I';
            } else {
                Ranking_Data[xx].mark = 'H';
            }
        } else {
            Ranking_Data[xx].mark = 0;
        }
    }
    if (Rank_In[PL_id][RANK_WINS] >= 0) {
        xx = Rank_In[PL_id][RANK_WINS] + 6;
        Ranking_Data[xx].name[0] = rank_name_w[PL_id].code[0];
        Ranking_Data[xx].name[1] = rank_name_w[PL_id].code[1];
        Ranking_Data[xx].name[2] = rank_name_w[PL_id].code[2];
        if (G_No1 == G1_ENDING) {
            if (Continue_Coin[PL_id]) {
                Ranking_Data[xx].mark = 'I';
            } else {
                Ranking_Data[xx].mark = 'H';
            }
        } else {
            Ranking_Data[xx].mark = 0;
        }
    }
}



/* Watches a player who is not in the game for a paid start, and brings a new challenger in through
   Break_Into_Sub. */
void Entry_Common_Sub(PL_id, Jump_Index)
s16 PL_id;
s16 Jump_Index;
{
    if (PL_id) {
        if (Credit_Sub_2P() != 0) {
            Break_Into_Sub(PL_id, Jump_Index);
        }
    } else if (Credit_Sub_1P() != 0) {
        Break_Into_Sub(PL_id, Jump_Index);
    }
}



/* The loser's start check in the loser scene: a paid start brings the player back in through Break_Into_Sub. */
void Loser_Scene_Sub(PL_id, Jump_Index)
s16 PL_id;
s16 Jump_Index;
{
    if (PL_id) {
        if (Loser_Sub_2P() != 0) {
            Break_Into_Sub(PL_id, Jump_Index);
        }
    } else if (Loser_Sub_1P() != 0) {
        Break_Into_Sub(PL_id, Jump_Index);
    }
}



s32 Loser_Sub_1P(void) {
    s8 status;
    if (Two_Coin_Start != 0 && Request_Break[0] == 0 && credit_1p < 2) {
        status = 99;
    } else {
        status = Request_Break[0] | credit_1p;
    }
    switch (status) {
    default:
        if (Ck_Break_Into(p1sw_0, p1sw_1, 0) == 0) {
            if (Request_Break[0]) {
                tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][0][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
            } else if (LOSER == 0) {
                tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[3][0][Game_setting.Screen_Mode], Text_Page_Y, 18, "    CONTINUEo     ");
            } else {
                Flash_Start(0, ENTRY_MSG_X_PAIRS[1][0][Game_setting.Screen_Mode]);
            }
        }
        break;
    }
    return ENTRY_X;
}



s32 Loser_Sub_2P(void) {
    s8 credits;
    s8 status;
    if (Chute_Mode < 2) {
        credits = credit_1p;
    } else {
        credits = credit_2p;
    }
    if (Two_Coin_Start != 0 && Request_Break[1] == 0 && credits < 2) {
        status = 99;
    } else {
        status = Request_Break[1] | credits;
    }
    switch (status) {
    default:
        if (Ck_Break_Into(p2sw_0, p2sw_1, 1) == 0) {
            if (Request_Break[1]) {
                tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][1][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
            } else if (LOSER == 1) {
                tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[3][1][Game_setting.Screen_Mode], Text_Page_Y, 18, "    CONTINUEo     ");
            } else {
                Flash_Start(1, ENTRY_MSG_X_PAIRS[1][1][Game_setting.Screen_Mode]);
            }
        }
        break;
    }
    return ENTRY_X;
}



s32 Credit_Sub_1P(void) {
    s8 status;
    if (Two_Coin_Start != 0 && Request_Break[0] == 0 && credit_1p < 2) {
        status = 99;
    } else {
        status = Request_Break[0] | credit_1p;
    }
    switch (status) {
    case 0:
        if (coin_chute1_w.count) {
            Flash_More_Coins(0, Entry_Msg_X_Data[4][Game_setting.Screen_Mode], (s8)(coin_chute1_w.per_credit - coin_chute1_w.count));
        } else {
            Flash_Insert_Coin(0, Entry_Msg_X_Data[0][Game_setting.Screen_Mode]);
        }
        break;
    case 99:
        if (credit_1p) {
            Flash_More_Coins(0, Entry_Msg_X_Data[4][Game_setting.Screen_Mode], 1);
        } else {
            Flash_Insert_Coin(0, Entry_Msg_X_Data[0][Game_setting.Screen_Mode]);
        }
        break;
    default:
        if (Ck_Break_Into(p1sw_0, p1sw_1, 0) == 0) {
            if (Request_Break[0]) {
                Flash_Please(0);
            } else {
                Flash_Start(0, Entry_Msg_X_Data[2][Game_setting.Screen_Mode]);
            }
        }
        break;
    }
    return ENTRY_X;
}



s32 Credit_Sub_2P(void) {
    s8 credits;
    s8 status;
    if (Chute_Mode < 2) {
        credits = credit_1p;
    } else {
        credits = credit_2p;
    }
    if (Two_Coin_Start != 0 && Request_Break[1] == 0 && credits < 2) {
        status = 99;
    } else {
        status = Request_Break[1] | credits;
    }
    switch (status) {
    case 0:
        if (Get_2P_Coin_Count()) {
            if (Chute_Mode < 2) {
                Flash_More_Coins(1, Entry_Msg_X_Data[5][Game_setting.Screen_Mode], (s8)(coin_chute1_w.per_credit - coin_chute1_w.count));
            } else {
                Flash_More_Coins(1, Entry_Msg_X_Data[5][Game_setting.Screen_Mode], (s8)(coin_chute2_w.per_credit - coin_chute2_w.count));
            }
        } else {
            Flash_Insert_Coin(1, Entry_Msg_X_Data[1][Game_setting.Screen_Mode]);
        }
        break;
    case 99:
        if (credits != 0) {
            Flash_More_Coins(1, Entry_Msg_X_Data[5][Game_setting.Screen_Mode], 1);
        } else {
            Flash_Insert_Coin(1, Entry_Msg_X_Data[1][Game_setting.Screen_Mode]);
        }
        break;
    default:
        if (Ck_Break_Into(p2sw_0, p2sw_1, 1) == 0) {
            if (Request_Break[1]) {
                Flash_Please(1);
            } else {
                Flash_Start(1, Entry_Msg_X_Data[3][Game_setting.Screen_Mode]);
            }
        }
        break;
    }
    return ENTRY_X;
}



s32 Credit_Continue_1P(void) {
    s8 state;
    state = Request_Break[0] | credit_1p;
    switch (state) {
    case 0:
        return 0;
        break;
    default:
        Ck_Break_Into(p1sw_0, p1sw_1, 0);
        break;
    }
    return ENTRY_X;
}



s32 Credit_Continue_2P(void) {
    s8 state;
    if (Chute_Mode < 2) {
        state = Request_Break[1] | credit_1p;
    } else {
        state = Request_Break[1] | credit_2p;
    }
    switch (state) {
    case 0:
        return 0;
        break;
    default:
        Ck_Break_Into(p2sw_0, p2sw_1, 1);
        break;
    }
    return ENTRY_X;
}



/* Runs a player's continue count: a coin restarts it, a button press cuts it short, and when it runs out
   Setup_Next_Step decides between name entry and game over. */
void Entry_Continue_Sub(PL_id)
s16 PL_id;
{
    switch (E_Number[PL_id][1]) {
    case 0:
        E_Number[PL_id][1]++;
        Personal_Disp_Flag = 1;
        Personal_Timer[PL_id] = 70;
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[3][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "    CONTINUEo\011    ");
        Disp_Personal_Count(PL_id, Continue_Count[PL_id]);
        break;
    case 1:
        if (Personal_Disp_Flag == 0) {
            Personal_Disp_Flag = 1;
            Personal_Timer[PL_id] = 70;
            tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[3][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "    CONTINUEo\011    ");
            Disp_Personal_Count(PL_id, Continue_Count[PL_id]);
        }
        if (Check_Coin_In(PL_id) != 0) {
            Continue_Count[PL_id] = 10;
            Personal_Timer[PL_id] = 1;
        }
        if (Check_Count_Cut(PL_id, 8) == 0) {
            if (--Personal_Timer[PL_id] != 0) {
                break;
            }
        }
        if (--Continue_Count[PL_id] >= 0) {
            Personal_Timer[PL_id] = 70;
            Disp_Personal_Count(PL_id, Continue_Count[PL_id]);
            break;
        }
        Setup_Next_Step(PL_id);
        break;
    }
}



/* Ends a player's continue: moves the entry on to name entry when the player made the rankings, otherwise to
   game over. */
void Setup_Next_Step(PL_id)
s16 PL_id;
{
    E_Number[PL_id][1] = 0;
    E_Number[PL_id][2] = 0;
    E_Number[PL_id][3] = 0;
    Score[PL_id][SCORE_CPU] += Continue_Coin[PL_id];
    if (E_No0 != E0_CONTINUE) {
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[3][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "          ");
        if (Check_Ranking(PL_id) != 0) {
            E_Number[PL_id][0] = ENTRY_NAME;
            if (E_No0 == E0_LOSER) {
                Request_Disp_Rank[PL_id][RANK_SCORE] = Rank_In[PL_id][RANK_SCORE];
                Request_Disp_Rank[PL_id][RANK_WINS] = Rank_In[PL_id][RANK_WINS];
            }
            return;
        }
        E_Number[PL_id][0] = ENTRY_GAME_OVER;
        E_Number[PL_id][1] = 0;
        return;
    } else {
        if (Check_Ranking(PL_id) != 0) {
            Request_Disp_Rank[PL_id][RANK_SCORE] = Rank_In[PL_id][RANK_SCORE];
            Request_Disp_Rank[PL_id][RANK_WINS] = Rank_In[PL_id][RANK_WINS];
            if (E_Number[PL_id ^ 1][0] != ENTRY_NONE) {
                E_Number[PL_id][0] = ENTRY_NAME;
                return;
            }
            E_Number[PL_id][0] = ENTRY_NAME_WAIT;
            E_Number[PL_id][1] = 0;
            return;
        } else {
            if (E_Number[PL_id ^ 1][0] != ENTRY_NONE) {
                E_Number[PL_id][0] = ENTRY_GAME_OVER;
                E_Number[PL_id][1] = 0;
            } else {
                E_Number[PL_id][0] = ENTRY_NAME_WAIT;
                E_Number[PL_id][1] = 1;
            }
        }
    }
}



/* Shows GAME OVER in a player's message space for a while during play, then clears the player's data. */
void In_Game_Sub(PL_id)
s16 PL_id;
{
    switch (E_Number[PL_id][2]) {
    case 0:
        E_Number[PL_id][2]++;
        Personal_Timer[PL_id] = 30;
        if (Game_setting.Event == 0) {
            tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[4][PL_id][Game_setting.Screen_Mode] - 2, Text_Page_Y, 18, "            ");
        }
        break;
    case 1:
        if (--Personal_Timer[PL_id] == 0) {
            E_Number[PL_id][2]++;
            Personal_Timer[PL_id] = 60;
            if (Game_setting.Event == 0) {
                tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[4][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "GAME OVER ");
            }
        }
        break;
    case 2:
        if (Personal_Disp_Flag == 0) {
            Personal_Disp_Flag = 1;
            if (Personal_Timer[PL_id] < 20) {
                Personal_Timer[PL_id] = 20;
            }
            if (Game_setting.Event == 0) {
                tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[4][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "GAME OVER ");
            }
        }
        if (--Personal_Timer[PL_id]) {
            break;
        }
        E_Number[PL_id][2]++;
        Personal_Timer[PL_id] = 30;
        if (Game_setting.Event == 0) {
            tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[4][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "GAME OVER ");
        }
        break;
    default:
        if (--Personal_Timer[PL_id] == 0) {
            Clear_Personal_Data(PL_id);
            Clear_Flash_No();
        }
        break;
    }
}



/* Shows GAME OVER in a player's message space during the game-over scene. */
void In_Over_Sub(PL_id)
s16 PL_id;
{
    switch (E_Number[PL_id][2]) {
    case 0:
        E_Number[PL_id][2]++;
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "                  ");
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[4][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "GAME OVER ");
        break;
    default:
        break;
    }
}



/* Flashes the insert-coin message (with the coins per credit) in a player's message space, alternating with
   the join-in message. */
/* provisional name */
s32 Flash_Insert_Coin(PL_id, x)
s16 PL_id;
u16 x;
{
    if (E_No0 == E0_LOSER || E_No0 == E0_GAME_OVER || E_No0 == E0_CONTINUE) {
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "                  ");
        return 0;
    }
    switch (F_No0[PL_id]) {
    case 0:
        F_No0[PL_id]++;
        F_No1[PL_id] = F_No2[PL_id] = 0;
        F_Timer[PL_id] = 1;
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "                  ");
        break;
    case 1:
        if (--F_Timer[PL_id] != 0) {
            break;
        }
        F_No0[PL_id]++;
        F_Timer[PL_id] = 50;
        if (Two_Coin_Start) {
            tilemap_print_string_attr(x, Text_Page_Y, 18, str_INSERT_COINS);
            break;
        }
        if (coin_chute1_w.per_credit == 1) {
            tilemap_print_string_attr(x, Text_Page_Y, 18, str_INSERT_COIN);
        } else {
            tilemap_print_string_attr(x, Text_Page_Y, 18, "INSERT   COINS");
            tilemap_print_hex_block(x + 7, Text_Page_Y, 18, coin_chute1_w.per_credit, 1, 1);
        }
        break;
    case 2:
        if (--F_Timer[PL_id] != 0) {
            break;
        }
        F_No0[PL_id]--;
        F_Timer[PL_id] = 50;
        if (coin_chute1_w.per_credit == 1 && Two_Coin_Start == 0) {
            tilemap_print_string_attr(x, Text_Page_Y, 18, "  JOIN IN  ");
        } else {
            tilemap_print_string_attr(x, Text_Page_Y, 18, "    JOIN IN   ");
        }
    }
    return 0;
}



/* Flashes the press-start (or free play) message in a player's message space; the loser of the loser scene is
   shown the continue message instead. */
s32 Flash_Start(PL_id, x)
s16 PL_id;
u16 x;
{
    switch (F_No1[PL_id]) {
    case 0:
        F_No1[PL_id]++;
        F_No0[PL_id] = 0;
        F_No2[PL_id] = 0;
        F_No3[PL_id] = 0;
        F_Timer[PL_id] = 1;
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
        if (E_No0 == E0_LOSER && PL_id == LOSER) {
            if (Continue_Flag) {
                F_No1[PL_id] = 3;
            }
        }
        break;
    case 1:
        if (--F_Timer[PL_id]) {
            break;
        }
        F_No1[PL_id]++;
        F_Timer[PL_id] = 50;
        if (Free_Play) {
            tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[2][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, " FREE PLAY ");
            break;
        } else {
            if (PL_id) {
                tilemap_print_string_attr(x, Text_Page_Y, 18, "PRESS \002P START");
            } else {
                tilemap_print_string_attr(x, Text_Page_Y, 18, "PRESS \001P START");
            }
        }
        break;
    case 2:
        if (--F_Timer[PL_id]) {
            break;
        }
        F_No1[PL_id]--;
        F_Timer[PL_id] = 30;
        tilemap_print_string_attr(x, Text_Page_Y, 18, "              ");
        break;
    case 3:
        F_No1[PL_id] = 99;
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[3][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "    CONTINUEo     ");
        break;
    }
    return 0;
}



/* Displays the free-play prompt for an inactive player. */
void Disp_Free_Play(PL_id)
s16 PL_id;
{
    if (Free_Play && Round_Operator[PL_id] == 0) {
        tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[2][PL_id][Game_setting.Screen_Mode], 0, 18, " FREE PLAY ");
        tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[2][PL_id][Game_setting.Screen_Mode], 32, 18, " FREE PLAY ");
    }
}



/* Flashes the please-wait message in a player's message space. */
s32 Flash_Please(PL_id)
s16 PL_id;
{
    if (E_No0 == E0_LOSER || E_No0 == E0_GAME_OVER) {
        return 0;
    }
    switch (F_No3[PL_id]) {
    case 0:
        F_No3[PL_id]++;
        F_No1[PL_id] = 0;
        F_Timer[PL_id] = 1;
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[1][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "                 ");
        break;
    case 1:
        if (--F_Timer[PL_id] == 0) {
            F_No3[PL_id]++;
            F_Timer[PL_id] = 50;
            tilemap_print_string_attr(ENTRY_SCORE_X_PAIRS[1][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "PLEASE WAIT");
        }
        break;
    default:
        if (--F_Timer[PL_id] == 0) {
            F_No3[PL_id]--;
            F_Timer[PL_id] = 30;
            tilemap_print_string_attr(ENTRY_SCORE_X_PAIRS[1][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "           ");
        }
        break;
    }
    return 0;
}



/* Flashes how many more coins a player needs to insert, in the player's message space. */
/* provisional name */
s32 Flash_More_Coins(PL_id, x, coins)
s16 PL_id;
s16 x;
s8 coins;
{
    s32 count;
    switch (F_No2[PL_id]) {
    case 0:
        F_No2[PL_id]++;
        F_No0[PL_id] = F_No1[PL_id] = 0;
        F_Timer[PL_id] = 1;
        tilemap_print_string_attr(x, Text_Page_Y, 18, "                   ");
        if (E_No0 == E0_LOSER && PL_id == LOSER) {
            F_No2[PL_id] = 3;
        }
        break;
    case 1:
        count = coins;
        if (Disp_More_Coins(PL_id, x, coins) == 0) {
            if (--F_Timer[PL_id] == 0) {
                F_No2[PL_id]++;
                F_Timer[PL_id] = 50;
                if (count == 1) {
                    tilemap_print_string_attr(x, Text_Page_Y, 18, "INSERT   MORE COIN ");
                } else {
                    tilemap_print_string_attr(x, Text_Page_Y, 18, "INSERT   MORE COINS");
                }
                tilemap_print_hex_block(x + 7, Text_Page_Y, 18, count, 1, 1);
            }
        } else {
            F_No2[PL_id]++;
        }
        break;
    case 2:
        Disp_More_Coins(PL_id, x, coins);
        if (--F_Timer[PL_id] == 0) {
            F_No2[PL_id]--;
            F_Timer[PL_id] = 30;
            tilemap_print_string_attr(x, Text_Page_Y, 18, "                   ");
        }
        break;
    }
    return 0;
}



/* Redraws the more-coins message at once when a coin drops in the player's chute; returns nonzero when it did. */
/* provisional name */
s32 Disp_More_Coins(PL_id, x, coins)
s16 PL_id;
u16 x;
s16 coins;
{
    if (Check_Coin_In(PL_id) != 0) {
        if (coins == 1) {
            tilemap_print_string_attr(x, Text_Page_Y, 18, "INSERT   MORE COIN ");
        } else {
            tilemap_print_string_attr(x, Text_Page_Y, 18, "INSERT   MORE COINS");
        }
        tilemap_print_hex_block(x + 7, Text_Page_Y, 18, (s8)coins, 1, 1);
        F_Timer[PL_id] = 50;
        return 1;
    }
    return 0;
}



/* provisional name */
s32 Get_2P_Coin_Count(void) {
    switch (Chute_Mode) {
    case 0:
    case 1:
        return coin_chute1_w.count;
    default:
        return coin_chute2_w.count;
    }
}



/* provisional name */
s32 credit_display_render(s8 force) {
    COINCHUTE* chute = &coin_chute1_w;
    s32 per;
    s8 two_coin;
    const s8* msg;
    s16* dx;
    if ((force | chute->dropped | coin_chute2_w.dropped) == 0) {
        return 0;
    }
    switch (per = chute->per_credit, two_coin = Two_Coin_Start, dx = DE_X, Chute_Mode) {
    case 0:
    case 1:
        switch (per) {
        case 0:
        case 1:
            if (two_coin != 0) {
                tilemap_print_string_attr(dx[0] + 21, 20, 18, (const s8 *)&"COINS:");
                tilemap_print_hex_block(dx[0] + 27, 20, 18, credit_1p, 1, 1);
            } else {
                tilemap_print_string_attr(dx[0] + 20, 20, 18, (const s8 *)&"CREDIT :");
                if (credit_1p >= 2) {
                    tilemap_print_string_attr(DE_X[0] + 26, 20, 18, "S");
                }
                tilemap_print_hex_block(DE_X[0] + 28, 20, 18, credit_1p, 1, 1);
            }
            break;
        default:
            tilemap_print_string_attr(dx[0] + 18, 20, 18, (const s8 *)&"CREDITS:");
            if (credit_1p < 2) {
                tilemap_print_string_attr(DE_X[0] + 24, 20, 18, " ");
            }
            tilemap_print_hex_block(DE_X[0] + 26, 20, 18, credit_1p, 1, 1);
            if (credit_1p >= 9) {
                tilemap_print_string_attr(DE_X[0] + 27, 20, 18, "      ");
            } else {
                tilemap_print_string_attr(DE_X[0] + 27, 20, 18, "( / )");
                tilemap_print_hex_block(DE_X[0] + 28, 20, 18, chute->count, 1, 1);
                tilemap_print_hex_block(DE_X[0] + 30, 20, 18, chute->per_credit, 1, 1);
            }
            break;
        }
        break;
    default:
        switch (per) {
        case 0:
        case 1:
            if (two_coin != 0) {
                tilemap_print_string_attr(dx[0] + 5, 20, 18, (const s8 *)&"COINS:");
                tilemap_print_hex_block(dx[0] + 11, 20, 18, credit_1p, 1, 1);
                tilemap_print_string_attr(dx[0] + 31, 20, 18, (const s8 *)&"COINS:");
                tilemap_print_hex_block(dx[0] + 37, 20, 18, credit_2p, 1, 1);
            } else {
                msg = (credit_1p < 2) ? (const s8 *)&"CREDIT :" : (const s8 *)&"CREDITS:";
                tilemap_print_string_attr(dx[0] + 6, 20, 18, msg);
                tilemap_print_hex_block(DE_X[0] + 14, 20, 18, credit_1p, 1, 1);
                if (credit_2p < 2) {
                    tilemap_print_string_attr(DE_X[0] + 32, 20, 18, (const s8 *)&"CREDIT :");
                } else {
                    tilemap_print_string_attr(DE_X[0] + 32, 20, 18, (const s8 *)&"CREDITS:");
                }
                tilemap_print_hex_block(DE_X[0] + 40, 20, 18, credit_2p, 1, 1);
            }
            break;
        default:
            if (credit_1p < 2) {
                tilemap_print_string_attr(dx[0] + 5, 20, 18, (const s8 *)&"CREDIT :");
            } else {
                tilemap_print_string_attr(dx[0] + 5, 20, 18, (const s8 *)&"CREDITS:");
            }
            tilemap_print_hex_block(DE_X[0] + 13, 20, 18, credit_1p, 1, 1);
            if (credit_1p >= 9) {
                tilemap_print_string_attr(DE_X[0] + 14, 20, 18, "      ");
            } else {
                tilemap_print_string_attr(DE_X[0] + 14, 20, 18, "( / )");
                tilemap_print_hex_block(DE_X[0] + 15, 20, 18, chute->count, 1, 1);
                tilemap_print_hex_block(DE_X[0] + 17, 20, 18, chute->per_credit, 1, 1);
            }
            if (credit_2p < 2) {
                tilemap_print_string_attr(DE_X[0] + 30, 20, 18, (const s8 *)&"CREDIT :");
            } else {
                tilemap_print_string_attr(DE_X[0] + 30, 20, 18, (const s8 *)&"CREDITS:");
            }
            tilemap_print_hex_block(DE_X[0] + 38, 20, 18, credit_2p, 1, 1);
            if (credit_2p >= 9) {
                tilemap_print_string_attr(DE_X[0] + 39, 20, 18, "      ");
            } else {
                tilemap_print_string_attr(DE_X[0] + 39, 20, 18, "( / )");
                tilemap_print_hex_block(DE_X[0] + 40, 20, 18, coin_chute2_w.count, 1, 1);
                tilemap_print_hex_block(DE_X[0] + 42, 20, 18, coin_chute2_w.per_credit, 1, 1);
            }
            break;
        }
        break;
    }
    return 1;
}



/* provisional name */
void Disp_Start_Message(void) {
    s8 credits;
    s8 coins;
    s8 needed;
    const s8* blank = "                         ";
    const s8* one_more;
    if (Two_Coin_Start != 0 && credit_1p < 2) {
        credits = 99;
    } else {
        credits = credit_1p;
    }
    one_more = "INSERT 1 MORE COIN";
    blank = "                         ";
    switch (Chute_Mode) {
    case 0:
    case 1:
        switch (credits) {
        case 0:
            needed = coin_chute1_w.per_credit - coin_chute1_w.count;
            tilemap_print_string_attr(DE_X[0] + 12, 18, 18, blank);
            if (needed == 1) {
                tilemap_print_string_attr(DE_X[0] + 15, 18, 18, "INSERT   MORE COIN ");
            } else {
                tilemap_print_string_attr(DE_X[0] + 15, 18, 18, "INSERT   MORE COINS");
            }
            tilemap_print_hex_block(DE_X[0] + 22, 18, 18, needed, 1, 1);
            break;
        case 99:
            tilemap_print_string_attr(DE_X[0] + 15, 18, 18, one_more);
            break;
        default:
            tilemap_print_string_attr(DE_X[0] + 12, 18, 18, "PRESS \001 OR \002 START BUTTON");
            break;
        }
        return;
    default:
        switch (credits) {
        case 0:
            tilemap_print_string_attr(DE_X[0] + 2, 18, 18, blank);
            coins = coin_chute1_w.count;
            needed = coin_chute1_w.per_credit - coins;
            if (coins) {
                if (needed == 1) {
                    tilemap_print_string_attr(DE_X[0] + 2, 18, 18, "INSERT   MORE COIN ");
                } else {
                    tilemap_print_string_attr(DE_X[0] + 2, 18, 18, "INSERT   MORE COINS");
                }
                tilemap_print_hex_block(DE_X[0] + 9, 18, 18, needed, 1, 1);
            } else {
                tilemap_print_string(6, 18, 0xFFFF, insert_coin_mes + coin_chute1_w.per_credit - 1);
            }
            break;
        case 99:
            if (credit_1p) {
                tilemap_print_string_attr(DE_X[0] + 2, 18, 18, one_more);
            } else {
                tilemap_print_string_attr(DE_X[0] + 2, 18, 18, "INSERT 2 MORE COINS");
            }
            break;
        default:
            tilemap_print_string_attr(DE_X[0] + 2, 18, 18, "PRESS \001P START BUTTON");
            break;
        }
    }
    if (Two_Coin_Start != 0 && credit_2p < 2) {
        credits = 99;
    } else {
        credits = credit_2p;
    }
    switch (credits) {
    case 0:
        tilemap_print_string_attr(DE_X[0] + 25, 18, 18, blank);
        coins = coin_chute2_w.count;
        needed = coin_chute2_w.per_credit - coins;
        if (coins) {
            if (needed == 1) {
                tilemap_print_string_attr(DE_X[0] + 25, 18, 18, "INSERT   MORE COIN ");
            } else {
                tilemap_print_string_attr(DE_X[0] + 25, 18, 18, "INSERT   MORE COINS");
            }
            tilemap_print_hex_block(DE_X[0] + 32, 18, 18, needed, 1, 1);
        } else {
            tilemap_print_string(DE_X[4] + 29, 18, 0xFFFF, insert_coin_mes + coin_chute1_w.per_credit - 1);
        }
        break;
    case 99:
        if (credit_2p) {
            tilemap_print_string_attr(DE_X[0] + 25, 18, 18, one_more);
        } else {
            tilemap_print_string_attr(DE_X[0] + 25, 18, 18, "INSERT 2 MORE COINS");
        }
        break;
    default:
        tilemap_print_string_attr(DE_X[0] + 25, 18, 18, "PRESS \002P START BUTTON");
        break;
    }
}



/* Brings a new challenger in, by the entry scene the start came from (Jump_Index, passed down by the Entry_NN
   scenes). */
void Break_Into_Sub(PL_id, Jump_Index)
s16 PL_id;
s16 Jump_Index;
{
    switch (Jump_Index) {
    case 0:
    case 1:
    case 2:
    case 3:
        Break_Into_02(PL_id);
        break;
    case 4:
    case 6:
        Break_Into_04(PL_id);
        break;
    case 5:
        Break_Into_05(PL_id);
        break;
    case 7:
        Break_Into_07(PL_id);
        break;
    case 8:
        Break_Into_08(PL_id);
        break;
    case 9:
        Break_Into_09(PL_id);
        break;
    case 10:
        Break_Into_10(PL_id);
        break;
    default:
        break;
    }
}



/* Checks a player who is not in the game for a paid start: when breaking in is allowed it pauses the game and
   makes the player the new challenger (nonzero return), otherwise the request waits in Request_Break. */
s32 Ck_Break_Into(Sw_0, Sw_1, PL_id)
u16 Sw_0;
u16 Sw_1;
s16 PL_id;
{
    if (Request_Break[PL_id]) {
        if (Forbid_Break) {
            return 0;
        }
        Game_pause = 1;
        New_Challenger = PL_id;
        Champion = New_Challenger ^ 1;
        Request_Break[PL_id] = 0;
        return ENTRY_X = 1;
    } else {
        if (!(~Sw_1 & Sw_0 & 0x1000)) {
            return 0;
        }
        if (!Pay_Start_Credit(PL_id)) {
            return 0;
        }
        if (E_No0 == E0_LOSER) {
            effect_58_init(6, 1, 116);
        }
        if (Forbid_Break) {
            Request_Break[PL_id] = 1;
            tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
        } else {
            Game_pause = 1;
            New_Challenger = PL_id;
            Champion = New_Challenger ^ 1;
            return ENTRY_X = 1;
        }
        return 0;
    }
}



/* The start check during name entry: a paid start press makes the player the new challenger at once. */
s32 Ck_Break_Into_SP(Sw_0, Sw_1, PL_id)
u16 Sw_0;
u16 Sw_1;
s16 PL_id;
{
    if (!(~Sw_1 & Sw_0 & 0x1000)) {
        return 0;
    }
    if (!Pay_Start_Credit(PL_id)) {
        return 0;
    }
    New_Challenger = PL_id;
    Champion = New_Challenger ^ 1;
    return ENTRY_X = 1;
}



/* Pays for a start, nonzero when paid: free play only books it, and with Two_Coin_Start a fresh start (not a
   continue) takes two credits. */
/* provisional name */
s32 Pay_Start_Credit(PL_id)
s16 PL_id;
{
    s8* credit;
    if (Free_Play) {
        bookkeep_freeplay_count();
        return 1;
    }
    if (E_Number[PL_id][0] == ENTRY_CONTINUE || E_Number[PL_id][0] == ENTRY_LOSER) {
        return (s8)credit_use(PL_id);
    }
    if (Two_Coin_Start) {
        switch (Chute_Mode) {
        case 0:
        case 1:
            if (credit_1p < 2) {
                return 0;
            } else {
                credit_1p -= 2;
                return 1;
            }
            break;
        default:
            if (PL_id) {
                credit = &credit_2p;
            } else {
                credit = &credit_1p;
            }
            if (*credit < 2) {
                return 0;
            } else {
                *credit -= 2;
                return 1;
            }
            break;
        }
    } else {
        return (s8)credit_use(PL_id);
    }
}



/* A new challenger joins at player select: the player becomes an operator and the select timer restarts. */
void Break_Into_02(PL_id)
s16 PL_id;
{
    Continue_Score_Sub(PL_id);
    plw[New_Challenger].wu.operator = 1;
    Operator_Status[New_Challenger] = 1;
    E_Number[New_Challenger][0] = ENTRY_NONE;
    E_Number[New_Challenger][1] = 0;
    E_Number[New_Challenger][2] = 0;
    E_Number[New_Challenger][3] = 0;
    tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][New_Challenger][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
    Select_Timer = 32;
    Unit_Of_Timer = 40;
}



/* A new challenger breaks into an Entry_03 scene: sets Break_Into and moves the entry scene on after a
   150-frame wait. */
void Break_Into_04(PL_id)
s16 PL_id;
{
    Continue_Score_Sub(PL_id);
    Break_Into = 1;
    E_No1++;
    E_No2 = 0;
    E_Timer = 150;
    E_Number[New_Challenger][0] = ENTRY_NONE;
    E_Number[New_Challenger][1] = 0;
    E_Number[New_Challenger][2] = 0;
    E_Number[New_Challenger][3] = 0;
    effect_A2_init();
    BGM_Request(6);
    effect_58_init(6, 30, 160);
    if (New_Challenger) {
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][1][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
    } else {
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][0][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
    }
}



/* A new challenger breaks into a fight: against the CPU after the fight is decided the scene moves on at once,
   otherwise as in Break_Into_04. */
void Break_Into_05(PL_id)
s16 PL_id;
{
    Continue_Score_Sub(PL_id);
    Break_Into = 1;
    Stop_Combo = 1;
    E_No1++;
    E_No2 = 0;
    E_Number[New_Challenger][0] = ENTRY_NONE;
    E_Number[New_Challenger][1] = 0;
    E_Number[New_Challenger][2] = 0;
    E_Number[New_Challenger][3] = 0;
    if ((Play_Type == PLAY_VS_CPU) && (Conclusion_Flag != 0) && (plw[Champion].wu.operator == 0)) {
        E_Timer = 1;
        if (LOSER != New_Challenger) {
            E_No3 = -1;
        } else {
            E_No3 = 0;
        }
    } else {
        E_Timer = 150;
        effect_A2_init();
        BGM_Request(6);
        effect_58_init(6, 30, 160);
    }
    if (New_Challenger) {
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][1][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
    } else {
        tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][0][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
    }
}



/* A new challenger breaks into the loser scene: the first of the two players to join sets Break_Into and moves
   the entry scene on. */
void Break_Into_07(PL_id)
s16 PL_id;
{
    Continue_Score_Sub(PL_id);
    E_Number[New_Challenger][0] = ENTRY_NONE;
    E_Number[New_Challenger][1] = 0;
    E_Number[New_Challenger][2] = 0;
    E_Number[New_Challenger][3] = 0;
    E_07_Flag[PL_id] = 1;
    if (E_07_Flag[0] != 0 && E_07_Flag[1] != 0) {
        return;
    }
    E_No1++;
    E_No2 = 0;
    Break_Into = 1;
}



/* A new challenger breaks into the continue scene: the first of the two players to join sets Break_Into and
   moves the entry scene on, waiting longer while the other player's continue count runs. */
void Break_Into_08(PL_id)
s16 PL_id;
{
    tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
    Continue_Score_Sub(PL_id);
    E_Number[New_Challenger][0] = ENTRY_NONE;
    E_Number[New_Challenger][1] = 0;
    E_Number[New_Challenger][2] = 0;
    E_Number[New_Challenger][3] = 0;
    E_07_Flag[PL_id] = 1;
    if (E_07_Flag[0] == 0 || E_07_Flag[1] == 0) {
        Break_Into = -1;
        E_No1++;
        E_No2 = 0;
        if (Continue_Count[PL_id ^ 1] >= 0) {
            E_Timer = 60;
            effect_58_init(6, 1, 116);
        } else {
            E_Timer = 10;
        }
        kill_tasks_by_func(continue_task);
    }
}



/* A new challenger breaks into the game-over scene: the first of the two players to join sets Break_Into,
   moves the entry scene on and becomes the champion. */
void Break_Into_09(PL_id)
s16 PL_id;
{
    tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
    E_Number[New_Challenger][0] = ENTRY_NONE;
    E_Number[New_Challenger][1] = 0;
    E_Number[New_Challenger][2] = 0;
    E_Number[New_Challenger][3] = 0;
    E_07_Flag[PL_id] = 1;
    if (E_07_Flag[0] != 0 && E_07_Flag[1] != 0) {
        return;
    }
    Break_Into = -1;
    E_No1++;
    E_No2 = 0;
    Champion = New_Challenger;
}



/* A new challenger breaks into the ending: the first of the two players to join sets Break_Into, moves the
   entry scene on and becomes the champion. */
void Break_Into_10(PL_id)
s16 PL_id;
{
    tilemap_print_string_attr(ENTRY_MSG_X_PAIRS[2][PL_id][Game_setting.Screen_Mode], Text_Page_Y, 18, "                   ");
    E_Number[New_Challenger][0] = ENTRY_NONE;
    E_Number[New_Challenger][1] = 0;
    E_Number[New_Challenger][2] = 0;
    E_Number[New_Challenger][3] = 0;
    E_07_Flag[PL_id] = 1;
    if (E_07_Flag[0] != 0 && E_07_Flag[1] != 0) {
        return;
    }
    Break_Into = -1;
    E_No1++;
    E_No2 = 0;
    Champion = New_Challenger;
}



/* Counts a continue (up to 99) when the player pays to come back from the continue or loser scene. */
void Continue_Score_Sub(PL_id)
s16 PL_id;
{
    if ((E_Number[PL_id][0] == ENTRY_CONTINUE) || (E_Number[PL_id][0] == ENTRY_LOSER)) {
        Continue_Coin[PL_id]++;
        if (Continue_Coin[PL_id] >= 99) {
            Continue_Coin[PL_id] = 99;
        }
    }
}



/* provisional name */
void coin_in_sound_request(void) {
    if ((coin_chute1_w.dropped | coin_chute2_w.dropped) && Demo_Flag == 1) {
        sound_request(E_No0 == E0_TITLE ? 115 : 106);
    }
}










