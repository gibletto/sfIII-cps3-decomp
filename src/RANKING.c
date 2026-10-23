/*
 * RANKING.C  Ranking display screens
 *
 * Draws the score ranking. Ranking_Main runs either Ranking_00 (the attract-mode ranking shown
 * between demos) or Ranking_01 (the ranking shown during a game) step by step and returns 1
 * when finished. The steps clear the text layer, load the ranking background and effects,
 * change the BGM, flash the entries in, count down the display time and wipe out; Ranking_01
 * also sets up the next demo when needed.
 * The ranking is two tables of six (score and wins). Setup_grade (the rank number),
 * Setup_Name, Setup_Face (portrait and mark letter), Setup_Score_Small and Setup_Wins put each
 * entry's cells up through effect 51, each cell flashing in at its Rank_Flash_Timer_Data frame;
 * Setup_Ranking_Obj and Setup_Score_Obj put up the headings (effect 57).
 * Ranking_Init loads the default table and, with the extra DIP switch set, inserts player 1's
 * present score into the top six.
 * Called from the game and attract-mode flow in Game_Main.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "SYS_sub.h"
#include "Game_Main.h"
#include "demo00.h"
#include "demo01.h"
#include "demo02_code.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "cmb_win.h"
#include "sc_trans.h"
#include "sc_logo.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "eff56.h"
#include "EFF58.h"
#include "eff65.h"
#include "eff66.h"
#include "Eff76.h"
#include "bg000.h"
#include "win_2.h"
#include "continue.h"
#include "pow_pow.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "RANKING.h"



/* Ranking portrait effect. */
s32 effect_95_rank_init();
s32 effect_51_init();
s32 effect_57_init();
s32 effect_F3_init();


RANK_DATA Ranking_Data[12];  /* 0201381C */
RANK_DATA Present_Data[2];  /* 020138AC */
RANK_DATA Present_Data_tail[1];  /* after Present_Data; nothing refers to it by name or address */


/* the frame each cell of the ranking rows flashes in, by Rank_Demo_Loop, row and cell (Rank_X) */
const s8 Rank_Flash_Timer_Data[2][6][14] = {
    {
        { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28 },
        { 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30 },
        { 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32 },
        { 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34 },
        { 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36 },
        { 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38 },
    },
    {
        { 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, -1 },
        { 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, -1 },
        { 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, -1 },
        { 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, -1 },
        { 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, -1 },
        { 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, -1 },
    },
};



s32 Ranking_Main(void) {
    void (*jmp_tbl[2])() = { Ranking_01, Ranking_00 };
    Ranking_X = 0;
    jmp_tbl[D_No0]();
    return Ranking_X;
}



void Ranking_00(void) {
    void (*jmp_tbl[6])() = { Ranking_00_1st, Ranking_00_2nd, Ranking_00_3rd, Ranking_00_4th, Ranking_00_5th, Ranking_00_Last };
    Ranking_X = 0;
    jmp_tbl[D_No1]();
}



void Ranking_01(void) {
    void (*jmp_tbl[5])() = { Ranking_01_1st, Ranking_00_2nd, Ranking_00_3rd, Ranking_01_4th, Ranking_01_5th };
    Ranking_X = 0;
    jmp_tbl[D_No1]();
}



void Ranking_01_1st(void) {
    D_No1 = D_No1 + 1;
    Suicide = 0;
    tilemap_fill_all(0, 32);
    Present_Rank[0] = 99;
    Present_Rank[1] = 99;
    Ranking_Sub();
    Setup_Ranking_Obj();
    Setup_Rank_Head_Obj();
    Setup_Score_Obj();
    effect_58_init(1, 1, -1);
    bgm_request(8);
}



void Ranking_01_4th(void) {
    if (!(--D_Timer)) {
        D_No1++;
        D_Timer = 240;
    }
}



void Ranking_01_5th(void) {
    switch (D_No2) {
    case 0:
        if (--D_Timer) {
            break;
        }
        D_No2++;
        if ((Demo_Flag == 0) && (Rank_Demo_Loop == 0)) {
            Text_Page_Y = 0;
            Setup_Demo_PL();
            Setup_Demo_Arts();
            Setup_Demo_Stage();
            Clear_Personal_Data(0);
            Clear_Personal_Data(1);
            Ranking_00_6th(0);
            Game01_Sub();
            SF3_logo(0);
        }
        sc_vram_to_ram();
        Switch_Screen_Init(3, 3);
        break;
    case 1:
        if (Switch_Screen() != 0) {
            D_No2++;
            Cover_Timer = 24;
        }
        break;
    default:
        Ranking_X = 1;
        break;
    }
}



void Ranking_00_1st(void)
{
    D_No1++;
    Rank_Demo_Loop = 0;
    Flash_Sign[0] = 1;
    Ranking_Sub();
    Setup_Ranking_Obj();
    Setup_Rank_Head_Obj();
    Setup_Score_Obj();
}



void Ranking_Sub(void)
{
    System_all_clear_Wait();
    bg_etc_write(2);
    bg_pos_hosei2();
    Bg_Family_Set();
    load_any_color(11);
    load_any_color(4);
    effect_95_rank_init(13, Ranking_Data[Rank_Type].player, Ranking_Data[Rank_Type].flag, Ranking_Data[Rank_Type].player_color, 0);
}



void Ranking_00_2nd(void) {
    D_No1++;
    D_Timer = 300;
    Rank_X = 0;
    Flash_Rank_Time = 0;
    if (Game_setting.mode) {
        Rank_Pos_X = bg_w.bgw[0].xy[0].disp.pos - 56;
    } else {
        Rank_Pos_X = bg_w.bgw[0].xy[0].disp.pos - 88;
    }
    Rank_Pos_Y = bg_w.bgw[0].xy[1].disp.pos + 148;
    Setup_Rank_Number(Rank_Pos_Y);
    for (Rank = Rank_Type; Rank < (Rank_Type + 6); Rank++) {
        if ((Present_Rank[0] == (Rank - Rank_Type)) || (Present_Rank[1] == (Rank - Rank_Type))) {
            Flash_Rank_Interval = 1;
        } else {
            Flash_Rank_Interval = 0;
        }
        Setup_grade();
        Setup_Name();
        Setup_Face();
        if (Rank_Type == 0) {
            Setup_Score_Small();
        } else {
            Setup_Wins();
        }
        if (Game_setting.mode) {
            Rank_Pos_X = bg_w.bgw[0].xy[0].disp.pos - 56;
        } else {
            Rank_Pos_X = bg_w.bgw[0].xy[0].disp.pos - 88;
        }
        Rank_Pos_Y -= 24;
        Rank_X = 0;
        Flash_Rank_Time = 0;
    }
    if ((Present_Rank[0] < 6) || (Present_Rank[1] < 6)) {
        D_No1++;
    } else {
        D_No1 = 4;
    }
}



void Ranking_00_3rd(void) {
    if (Flash_Sign[0] == 1) {
        D_No1 = D_No1 + 1;
        D_Timer = 1;
    }
}



void Ranking_00_4th(void) {
    if (!(--D_Timer)) {
        D_No1++;
        D_Timer = 30;
        Flash_Sign[0] = 0;
        Flash_Sign[1] = 1;
    }
}



void Ranking_00_5th(void)
{
    if (--D_Timer == 0) {
        D_No1++;
        D_Timer = 180;
        Flash_Sign[1] = 0;
    }
}



void Ranking_00_Last(void) {
    if (--D_Timer == 0) {
        D_Timer = 1;
        Ranking_X = 1;
    }
}



void Setup_grade(void) {
    Flash_Rank_Time += Flash_Rank_Interval;
    effect_51_init(Rank - Rank_Type + 1, Rank_Pos_X, Rank_Pos_Y, Rank_Flash_Timer_Data[Rank_Demo_Loop][Rank - Rank_Type][Rank_X], Flash_Rank_Time, -2, 1, -1);
    Flash_Rank_Time += Flash_Rank_Interval;
    effect_51_init(Rank - Rank_Type + 65, Rank_Pos_X + 16, Rank_Pos_Y, Rank_Flash_Timer_Data[Rank_Demo_Loop][Rank - Rank_Type][Rank_X + 1], Flash_Rank_Time, 1, 0, 1);
    Flash_Rank_Time += Flash_Rank_Interval;
    Rank_X += 2;
    Rank_Pos_X += 38;
}



void Setup_Name(void) {
    Name_Sub(0);
    Name_Sub(1);
    Name_Sub(2);
    Rank_X += 3;
    Rank_Pos_X += 14;
}



void Name_Sub(s16 name_ix) {
    effect_51_init(Ranking_Data[Rank].name[name_ix], Rank_Pos_X, Rank_Pos_Y, Rank_Flash_Timer_Data[Rank_Demo_Loop][Rank - Rank_Type][Rank_X + name_ix], Flash_Rank_Time, 3, 0, -1);
    Flash_Rank_Time += Flash_Rank_Interval;
    Rank_Pos_X += 16;
}



void Setup_Face(void) {
    effect_51_init(Ranking_Data[Rank].player + 47, Rank_Pos_X, Rank_Pos_Y, Rank_Flash_Timer_Data[Rank_Demo_Loop][Rank - Rank_Type][Rank_X], Flash_Rank_Time, Ranking_Data[Rank].player_color * 4, 1, -(Ranking_Data[Rank].player / 4) - 5);
    Flash_Rank_Time += Flash_Rank_Interval;
    if (Rank_Type == 0) {
        if (Ranking_Data[Rank].mark) {
            effect_51_init(Ranking_Data[Rank].mark, Rank_Pos_X + 30, Rank_Pos_Y, Rank_Flash_Timer_Data[Rank_Demo_Loop][Rank - Rank_Type][Rank_X + 1], Flash_Rank_Time, 3, 0, -1);
        }
    }
    Rank_Pos_X += 40;
    Rank_X += 2;
    Flash_Rank_Time += Flash_Rank_Interval;
}



void Setup_Score_Small(void) {
    s16 i;
    s16 First_Digit;
    u32 xx;
    u32 Score_Buff;
    s16 Digit[7];
    Score_Buff = Ranking_Data[Rank].score;
    First_Digit = -1;
    for (i = 6, xx = 1000000; i > 0; i--, xx = xx / 10) {
        Digit[i] = Score_Buff / xx;
        Score_Buff -= Digit[i] * xx;
        if (First_Digit < 0) {
            if (Digit[i]) {
                First_Digit = i;
            }
        }
    }
    Digit[0] = Score_Buff;
    if (First_Digit < 0) {
        First_Digit = 0;
    }
    for (i = 0, xx = 6; i < 7; i++, xx--) {
        Flash_Rank_Time += Flash_Rank_Interval;
        Rank_Pos_X += 16;
        if (First_Digit < xx) {
            continue;
        }
        effect_51_init(Digit[xx], Rank_Pos_X, Rank_Pos_Y, Rank_Flash_Timer_Data[Rank_Demo_Loop][Rank - Rank_Type][Rank_X + i], Flash_Rank_Time, 1, 1, -1);
    }
}



void Setup_Wins(void) {
    s16 i;
    u32 Score_Buff;
    s16 Digit[2];
    Score_Buff = Ranking_Data[Rank].score;
    Rank_Pos_X += 8;
    Digit[1] = Score_Buff / 10;
    Score_Buff -= Digit[1] * 10;
    Digit[0] = Score_Buff;
    if (Digit[1]) {
        effect_51_init(Digit[1], Rank_Pos_X, Rank_Pos_Y, Rank_Flash_Timer_Data[Rank_Demo_Loop][Rank - Rank_Type][Rank_X], Flash_Rank_Time, 1, 1, -1);
    }
    Rank_Pos_X += 16;
    Rank_X += 1;
    Flash_Rank_Time += Flash_Rank_Interval;
    effect_51_init(Digit[0], Rank_Pos_X, Rank_Pos_Y, Rank_Flash_Timer_Data[Rank_Demo_Loop][Rank - Rank_Type][Rank_X], Flash_Rank_Time, 1, 1, -1);
    Rank_Pos_X += 24;
    Rank_X += 1;
    Flash_Rank_Time += Flash_Rank_Interval;
    for (i = 0; i < 4; i++) {
        effect_51_init(i + 61, Rank_Pos_X, Rank_Pos_Y, Rank_Flash_Timer_Data[Rank_Demo_Loop][Rank - Rank_Type][Rank_X], Flash_Rank_Time, 0, 0, 2);
        Rank_Pos_X += Wins_Pos_X_Data[i];
        Rank_X += 1;
        Flash_Rank_Time += Flash_Rank_Interval;
    }
}



const s8 Wins_Pos_X_Data[4] = { 8, 8, 16, 0 };



/* provisional name */
void Setup_Rank_Number(s16 y) {
    s16 i;
    s16 delay;
    for (i = 0, delay = 161; i <= 5; i++, y -= 24, delay += 3) {
        effect_F3_init(i, delay, 4, y + 5);
    }
}



/* provisional name */
void Setup_Rank_Head_Obj(void) {
    s16 x;
    s16 y;
    s16 i;
    if (Game_setting.mode) {
        x = bg_w.bgw[0].xy[0].disp.pos - 40;
    } else {
        x = bg_w.bgw[0].xy[0].disp.pos - 56;
    }
    y = bg_w.bgw[0].xy[1].disp.pos + 195;
    for (i = 0; i < 7; i++) {
        effect_57_init(24, x, y, 1, i, 85);
        x += 16;
    }
}



void Setup_Score_Obj(void) {
    s16 x = bg_w.bgw[0].xy[0].disp.pos + DE_X[15] + 72;
    s16 y = bg_w.bgw[0].xy[1].disp.pos + 179;
    if (Rank_Type == 0) {
        effect_57_init(11, x, y, 1, 0, 85);
        effect_57_init(11, x, y, 1, 1, 85);
        effect_57_init(11, x, y, 1, 2, 85);
        effect_57_init(11, x, y, 1, 3, 85);
        effect_57_init(11, x, y, 1, 4, 85);
    } else {
        effect_57_init(11, x, y, 1, 5, 85);
        effect_57_init(11, x, y, 1, 6, 85);
        effect_57_init(11, x, y, 1, 7, 85);
        effect_57_init(11, x, y, 1, 8, 85);
    }
}



void Setup_Ranking_Obj(void) {
    effect_57_init(11, bg_w.bgw[0].xy[0].disp.pos - 16, bg_w.bgw[0].xy[1].disp.pos + 192, 1, 9, 90);
}



void Ranking_Init(void) {
    s16 ix = 0;
    const RANK_DATA* src = Rank_Default_Data;
    RANK_DATA* dst = Ranking_Data;
    for (; ix < 12; ix++) {
        *dst = *src;
        src++;
        dst++;
    }
    if (exsw_3 & 0x80) {
        ranking_insert_present(0, 0);
    }
}



void ranking_insert_present(s16 top, s16 PL_id) {
    s16 i;
    s16 j;
    for (i = 0; i < 6; i++) {
        if (Ranking_Data[top + i].score < Present_Data[PL_id].score) {
            for (j = 4; j >= i; j--) {
                Ranking_Data[j + top + 1] = Ranking_Data[j + top];
            }
            Ranking_Data[i + top] = Present_Data[PL_id];
            break;
        }
    }
}
