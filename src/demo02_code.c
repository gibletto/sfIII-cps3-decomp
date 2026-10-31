/*
 * DEMO02_CODE.C  Attract mode: demonstration play
 *
 * Play_Demo runs the current demo step from Demo_Jmp_Tbl; Setup_Demo_PL, Setup_Demo_Arts
 * and Setup_Demo_Stage pick the characters, super arts and stage for demonstration fights.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Game_Main.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "Entry.h"
#include "entry_2.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "SYS_sub.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "cmb_win.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "eeprom.h"
#include "sc_trans.h"
#include "sc_clear.h"
#include "bg000.h"
#include "lose_pl.h"
#include "PLS02.h"
#include "SLOWF.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "demo02_code.h"

/* D_No1 in Demo00 */
#define DM_INIT         0       /* set up the demo fight */
#define DM_COVER        1       /* until Cover_Timer, then wipe in */
#define DM_REVIVAL      2       /* finish the wipe */
#define DM_PLAY         3       /* the demo fight for D_Timer */
#define DM_STOP         4       /* wait D_Timer, then wipe out */
#define DM_WIPE         5       /* until the wipe is done */

/* D_No1 in Demo01 */
#define DS_INIT         0       /* set up the select demo */
#define DS_SELECT       1       /* the select screen, until it stops */
#define DS_COVER        2       /* until Cover_Timer, then wipe in */
#define DS_REVIVAL      3       /* finish the wipe */
#define DS_PLAY         4       /* the demo fight for D_Timer */
#define DS_WIPE         5       /* until the wipe is done */



s32 Play_Demo(void) {
    void (*Demo_Jmp_Tbl[2])() = { Demo00, Demo01 };
    Next_Demo = 0;
    Demo_Jmp_Tbl[D_No0]();
    return Next_Demo;
}

void Demo00(void) {
    switch (D_No1) {
    case DM_INIT:
        D_No1++;
        G_No2 = G2_FIGHT_INIT;
        Game_pause = 0;
        appear_type = APPEAR_ENTRY;
        Control_Time = 2048;
        Round_Level = 7;
        Text_Page_Y = 0;
        Weak_PL = random_16_com() & 1;
        scfont_page1_fill(0, 32);
        break;
    case DM_COVER:
        Game02();
        if (--Cover_Timer == 0) {
            D_No1++;
            Switch_Screen_Init(3, 3);
        }
        break;
    case DM_REVIVAL:
        Game02();
        if (Switch_Screen_Revival()) {
            D_No1++;
            D_Timer = 1800;
            Stop_SG = 0;
        }
        break;
    case DM_PLAY:
        Game02();
        if (--D_Timer == 1) {
            Stop_Combo = 1;
        } else if (D_Timer == 0 || Conclusion_Flag) {
            D_No1++;
            D_Timer = 90;
        }
        break;
    case DM_STOP:
        Game02();
        if (--D_Timer == 0) {
            D_No1++;
            Game_pause = 1;
            sc_vram_to_ram();
            Switch_Screen_Init(3, 3);
        }
        break;
    case DM_WIPE:
        Game02();
        if (!Switch_Screen()) {
            break;
        }
        D_No1++;
        Demo_Flag = 0;
        Cover_Timer = 23;
        BGM_Stop();
        break;
    default:
        Next_Demo = 1;
        break;
    }
}



void Demo01(void) {
    switch (D_No1) {
    case DS_INIT:
        D_No1++;
        Game_pause = 0;
        Demo_Time_Stop = 0;
        Text_Page_Y = 32;
        scfont_page1_fill(0, 32);
        Before_Select_Sub();
        Setup_Select_Demo_PL();
        Setup_Demo_Arts();
        Weak_PL = random_16_com() & 1;
        break;
    case DS_SELECT:
        Game01();
        if (Demo_Time_Stop) {
            D_No1++;
            G_No2 = G2_FIGHT_INIT;
            Text_Page_Y = 0;
        }
        break;
    case DS_COVER:
        Game02();
        if (--Cover_Timer != 0) {
            return;
        }
        D_No1++;
        Switch_Screen_Init(3, 3);
        break;
    case DS_REVIVAL:
        Game02();
        if (Switch_Screen_Revival()) {
            D_No1++;
            D_Timer = 1200;
            Stop_SG = 0;
        }
        break;
    case DS_PLAY:
        Game02();
        if (--D_Timer == 1) {
            Stop_Combo = 1;
            break;
        }
        if (D_Timer) {
            break;
        }
        D_No1++;
        Demo_Time_Stop = 1;
        Game_pause = 1;
        sc_vram_to_ram();
        Switch_Screen_Init(3, 3);
        break;
    case DS_WIPE:
        Game02();
        if (Switch_Screen()) {
            D_No1++;
            Cover_Timer = 23;
            if (++Select_Demo_Index > 3) {
                Select_Demo_Index = 0;
            }
            BGM_Stop();
        }
        break;
    default:
        Next_Demo = 1;
        break;
    }
}



void Setup_Demo_PL(void) {
    My_char[0] = Demo_PL_Play_Data[Demo_PL_Index[0]];
    My_char[1] = Demo_PL_Play_Data[Demo_PL_Index[0] + 1];
}



void Setup_Demo_Arts(void) {
    Super_Arts[0] = Arts_Rnd_Demo_Data[random_16_com() & 7];
    Super_Arts[1] = Arts_Rnd_Demo_Data[random_16_com() & 7];
    Player_Color[0] = 0;
    Player_Color[1] = 0;
}



void Setup_Demo_Stage(void) {
    bg_w.area = 0;
    bg_w.stage = Demo_Stage_Play_Data[Demo_Stage_Index];
    Demo_Stage_Index++;
    if ((Demo_PL_Index[0] += 2) > 9) {
        Demo_PL_Index[0] = 0;
        Demo_Stage_Index = 0;
    }
}



void Setup_Select_Demo_PL(void) {
    plw[0].wu.operator = 0;
    plw[1].wu.operator = 0;
    Operator_Status[0] = 0;
    Operator_Status[1] = 0;
    plw[Demo_PL_Data[Select_Demo_Index]].wu.operator = 1;
    (&Operator_Status[0])[Demo_PL_Data[Select_Demo_Index]] = 1;
}
