/*
 * SYS_SUB.C  System subroutines for scenes and screens
 *
 * General helpers used by the scene and menu code. System_all_clear_Ex also empties the effect
 * lists. Request_Fade/Check_Fade_Complete(_SP) run fades; Switch_Screen_Init,
 * Switch_Screen and Switch_Screen_Revival run the screen wipes built from the patterns in SE.
 * scfont_page0_fill / scfont_page1_fill fill a whole page of the text (SS) layer.
 * Ranking entry (Check_Ranking, Check_Sort_Ranking, Check_Partners_Rank) and Setup_Play_Type are
 * here, with scene-cut helpers (Button_Cut_Hold, Cut_Cut_Cut and friends) that let a
 * player's button shorten a scene. Disp_Digit8x16/16x24 draw score digits, Disp_Win_Type the round
 * win marks, and Disp_Copyright the copyright lines chosen by Country.
 * There are two rankings of six (score, then consecutive wins) in 12-byte records; Ck_Range_Out_Y is the
 * vertical range check, and the button tests use 0x7F0.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sc_trans.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "effd2.h"
#include "effd3.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "fifo.h"
#include "sc_sub.h"
#include "sc_sub_2.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "n_input.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "SYS_sub.h"
#include "cps3.h"



/* Clears the text layer and runs System_all_clear, then waits a frame. */
/* provisional name */
void Scr_all_clear_Wait(void)
{
    tilemap_fill_all(0, 0x20);
    System_all_clear();
    task_sleep(1);
}

/* Runs System_all_clear, then waits a frame. */
/* provisional name */
void System_all_clear_Wait(void)
{
    System_all_clear();
    task_sleep(1);
}

/* Clears text page 0 and runs System_all_clear_Ex, then waits a frame. */
/* provisional name */
void System_all_clear_Ex_Wait(void)
{
    scfont_page0_fill(0, 0x20);
    System_all_clear_Ex();
    task_sleep(1);
}

/* Clears the render lists, character graphics tables, scroll layer state and all effect work, then reloads the
   common character graphics and cells. */
/* provisional name */
void System_all_clear(void)
{
    init_render_lists();
    init_char_gfx_tables();
    clear_scroll_layer_state_and_mask();
    Family_Init();
    effect_work_quick_clear();
    load_char_gfx(0x4000, 1);
    setup_kage_cells();
    setup_hit_mark_cells();
}



/* As System_all_clear, but clears only effect lists 2 to 7. */
/* provisional name */
void System_all_clear_Ex(void) {
    s16 i;
    init_render_lists();
    init_char_gfx_tables();
    clear_scroll_layer_state_and_mask();
    Family_Init();
    for (i = 2; i <= 7; i++) {
        effect_work_list_init(i, -1);
    }
    load_char_gfx(0x4000, 1);
    setup_kage_cells();
    setup_hit_mark_cells();
}

/* Runs the palette fade for a frame (fade_cont_main). */
/* provisional name */
void Fade_Cont(void)
{
    fade_cont_main();
}



/* Run the fade for a frame; 1 once it has finished. */
s32 Check_Fade_Complete_SP(void) {
    fade_cont_main();
    return Fade_Flag ^ 1;
}



/* Run the fade; once it has finished, count down Fade_Gap_Timer (3 from Request_Fade) and return 1
   when it runs out. */
s32 Check_Fade_Complete(void) {
    if (Fade_Flag) {
        fade_cont_main();
        return 0;
    }
    if (Fade_Gap_Timer == 3) {
        Scrn_Move_Set(4, 0, 0x100);
    }
    if (--Fade_Gap_Timer != 0) {
        return 0;
    }
    Forbid_Break = 1;
    return 1;
}



/* Start fade fade_code in mode fade_mode.  Returns 0 if a fade is already running. */
s32 Request_Fade(fade_code, fade_mode)
u16 fade_code;
u8 fade_mode;
{
    if (Fade_Flag == 0) {
        Fade_Flag = 1;
        Fade_Mode = fade_mode;
        Fade_R_No0 = Fade_R_No1 = 0;
        Fade_Number = fade_code;
        Forbid_Break = 1;
        fade_cont_init();
        Fade_Gap_Timer = 3;
        return 1;
    }
    return 0;
}



/* Start screen wipe kind, drawn in wipe_mode (see Switch_Screen). */
void Switch_Screen_Init(kind, wipe_mode)
s16 kind;
u8 wipe_mode;
{
    Forbid_Break = 1;
    Exec_Wipe = 1;
    Wipe_Kind = kind;
    Wipe_Limit = wipe_set_pattern_tbl[kind].limit;
    Wipe_Mode = wipe_mode;
    Wipe_Count = 0;
    Stop_SG = 1;
}



/* One step of the wipe that covers the screen, drawn in Wipe_Mode; 1 when the wipe is complete. */
s32 Switch_Screen(void) {
    switch ((s8)Wipe_Mode) {
    case 0:
        wipe_pattern_set((s8)Wipe_Kind, Wipe_Count, 0);
        if (++Wipe_Count < (s8)Wipe_Limit) {
            return 0;
        }
        Exec_Wipe = 0;
        Stop_Combo = 0;
        return 1;
    case 1:
        wipe_pattern_or_cols((s8)Wipe_Kind, Wipe_Count);
        if (++Wipe_Count < (s8)Wipe_Limit) {
            return 0;
        }
        Exec_Wipe = 0;
        Stop_Combo = 0;
        return 1;
    case 2:
        wipe_pattern_and_low((s8)Wipe_Kind, Wipe_Count);
        if (++Wipe_Count < (s8)Wipe_Limit) {
            return 0;
        }
        Exec_Wipe = 0;
        Stop_Combo = 0;
        return 1;
    case 3:
    case 4:
        wipe_pattern_or_cols((s8)Wipe_Kind, Wipe_Count);
        if (++Wipe_Count < (s8)Wipe_Limit) {
            return 0;
        }
        Exec_Wipe = 0;
        Stop_Combo = 0;
        return 1;
    }
    return 0;
}



/* One step of the wipe that uncovers the screen again; 1 when the wipe is complete. */
s32 Switch_Screen_Revival(void) {
    switch ((s8)Wipe_Mode) {
    case 0:
        wipe_pattern_set((s8)Wipe_Kind, Wipe_Count, 1);
        if (++Wipe_Count < (s8)Wipe_Limit) {
            return 0;
        }
        Exec_Wipe = 0;
        return 1;
    case 1:
        wipe_pattern_restore_cols((s8)Wipe_Kind, Wipe_Count);
        if (++Wipe_Count < (s8)Wipe_Limit) {
            return 0;
        }
        Exec_Wipe = 0;
        return 1;
    case 3:
    case 4:
        wipe_pattern_restore_cols((s8)Wipe_Kind, Wipe_Count);
        if (++Wipe_Count < (s8)Wipe_Limit) {
            return 0;
        }
        Exec_Wipe = 0;
        return 1;
    }
    return 0;
}



/* The text (SS) layer is one 64-row tilemap in SS RAM, 4 bytes per cell (code, attribute): page 0 is rows 0-31
 * (+0x0000-0x1FFF), page 1 rows 32-63 (+0x2000-0x3FFF). The layer is scrolled to show one page: Text_Page_Y (0 or 32)
 * is the row text is printed on, and Scrn_Move_Set(4, 0, 0 / 0x100) shows page 0 / page 1. Bit 8 of the cell code
 * goes into the attribute's low bit. These two fill a whole page with one cell: (0, 32) clears it with spaces. */
void scfont_page0_fill(u32 attr, u16 code) {
    u16 att;
    u16* p;
    att = (s32)(code & 0x100) >> 8 | attr;
    p = (u16*)SS_RAM;
    do {
        p[0] = code;
        p[1] = att;
        p += 2;
    } while (p < (u16*)(SS_RAM + 0x2000));
}



/* Page 1 of the text layer (see scfont_page0_fill). */
void scfont_page1_fill(u32 attr, u16 code) {
    u16 att;
    u16* p;
    att = (s32)(code & 0x100) >> 8 | attr;
    p = (u16*)(SS_RAM + 0x2000);
    do {
        p[0] = code;
        p[1] = att;
        p += 2;
    } while (p < (u16*)(SS_RAM + 0x3FFF));
}



/* provisional name */
void scrn_pos_clear(void) {
    SCRLPOS* p;
    SCRLPOS* q;
    p = scrn_pos;
    while (p < &scrn_pos[4]) {
        q = p;
        p->set_x.cal = 0;
        p++;
        q->cur_x.cal = 0;
        q->set_y.cal = 0;
        q->cur_y.cal = 0;
        q = p;
        p->set_x.cal = 0;
        p++;
        q->cur_x.cal = 0;
        q->set_y.cal = 0;
        q->cur_y.cal = 0;
    }
}



void Clear_Flash_No(void) {
    F_No0[0] = F_No1[0] = F_No2[0] = F_No3[0] = 0;
    F_No0[1] = F_No1[1] = F_No2[1] = F_No3[1] = 0;
    Personal_Disp_Flag = 0;
}



/* Erases the 18-character banner on the text layer: at the right-hand column when the new challenger is player 2. */
/* provisional name */
void challenger_banner_clear(void) {
    Forbid_Break = 1;
    if (New_Challenger) {
        tilemap_print_string_attr(30, 0, 18, "                  ");
    } else {
        tilemap_print_string_attr(0, 0, 18, "                  ");
    }
}



void Setup_Play_Type(void) {
    if ((Operator_Status[0] & 0x7F) && (Operator_Status[1] & 0x7F)) {
        Play_Type = PLAY_VS_PLAYER;
    } else {
        Play_Type = PLAY_VS_CPU;
    }
}

/* Build this player's ranking entry and try it against both ranking tables: score, then
   consecutive wins (Win_Record).  Returns 1 if the player made either. */
u32 Check_Ranking(PL_id)
s16 PL_id;
{
    Present_Data[PL_id].player = Stock_My_char[PL_id] & 0x7F;
    Present_Data[PL_id].player_color = Stock_Player_Color[PL_id];
    Present_Data[PL_id].score = Score[PL_id][SCORE_CPU];
    Rank_In[PL_id][RANK_SCORE] = Check_Sort_Ranking(0, PL_id);
    if (Rank_In[PL_id][RANK_SCORE] >= 0 && Rank_In[PL_id ^ 1][RANK_SCORE] >= 0) {
        Check_Partners_Rank(0, PL_id);
    }
    Present_Data[PL_id].score = Win_Record[PL_id];
    Rank_In[PL_id][RANK_WINS] = Check_Sort_Ranking(6, PL_id);
    if (Rank_In[PL_id][RANK_WINS] >= 0 && Rank_In[PL_id ^ 1][RANK_WINS] >= 0) {
        Check_Partners_Rank(1, PL_id);
    }
    if (Rank_In[PL_id][RANK_SCORE] >= 0 || Rank_In[PL_id][RANK_WINS] >= 0) {
        return 1;
    }
    return 0;
}



/* After PL_id's entry goes into ranking table dir_step at or above the partner's place, moves the partner's
   place down one (off the table past the last place). */
void Check_Partners_Rank(dir_step, PL_id)
s16 dir_step;
s16 PL_id;
{
    if (Rank_In[PL_id][dir_step] > Rank_In[PL_id ^ 1][dir_step]) {
        return;
    }
    Rank_In[PL_id ^ 1][dir_step]++;
    if (Rank_In[PL_id ^ 1][dir_step] > 5) {
        Rank_In[PL_id ^ 1][dir_step] = -1;
    }
}



/* provisional name: one ranking's insertion (ofs 0: score, 6: the second ranking) */
s32 Check_Sort_Ranking(ofs, PL_id)
s16 ofs;
s16 PL_id;
{
    s16 i;
    s16 j;
    for (i = 0; i < 6; i++) {
        if (Ranking_Data[ofs + i].score < Present_Data[PL_id].score) {
            for (j = 4; j >= i; j--) {
                Ranking_Data[ofs + j + 1] = Ranking_Data[ofs + j];
            }
            Ranking_Data[ofs + i] = Present_Data[PL_id];
            return i;
        }
    }
    return -1;
}



/* provisional name */
s32 Button_Cut_Hold(s16* timer, s16 first, s16 repeat) {
    s16 side;
    s16 trig;
    if (Reserve_Cut) {
        if (repeat >= *timer) {
            Reserve_Cut = 0;
            return 1;
        } else {
            return 0;
        }
    }
    side = Setup_Target_PL();
    if (side) {
        trig = ~p2sw_1 & p2sw_0;
    } else {
        trig = ~p1sw_1 & p1sw_0;
    }
    if (trig & 0x7F0) {
        if (repeat >= *timer) {
            Reserve_Cut = 0;
            return 1;
        } else {
            Reserve_Cut = 1;
            return 0;
        }
    } else {
        if (first < *timer) {
            return 0;
        }
        if (side) {
            if (p2sw_0 & 0x7F0) {
                Reserve_Cut = 0;
                return 1;
            }
            return 0;
        }
        if (p1sw_0 & 0x7F0) {
            Reserve_Cut = 0;
            return 1;
        }
    }
    return 0;
}






/* Which side's buttons may cut a scene short: the winner in a two-player match,
   otherwise the side that is being played (1P unless only 2P is in). */
int Setup_Target_PL(void)
{
    if (Play_Type == PLAY_VS_PLAYER) {
        return Winner_id;
    }
    if (Round_Operator[0]) {
        return 0;
    }
    return 1;
}



/* provisional name */
void Disp_Digit8x16(u32 value, s16 x, s16 y) {
    s16 i;
    s16 j;
    s32 div;
    s16 First_Digit;
    s16 Digit[8];
    if (value == 0) {
        score8x16_put(x, y, 24, 0);
    }
    for (i = 7, div = 10000000, First_Digit = -1; i > 0; i--, div = div / 10) {
        Digit[i] = value / div;
        value -= div * Digit[i];
        if (First_Digit < 0) {
            if (Digit[i]) {
                First_Digit = i;
            }
        }
    }
    Digit[0] = value;
    i = x - First_Digit;
    for (j = First_Digit; j >= 0; j--, i++) {
        score8x16_put(i, y, 24, Digit[j]);
    }
}



void Disp_Digit16x24(value, x, y)
u32 value;
s16 x;
s16 y;
{
    s16 i;
    s16 j;
    s32 div;
    s16 First_Digit;
    s16 Digit[8];
    if (value == 0) {
        score16x24_put(x, y, 14, 0);
    }
    for (i = 7, div = 10000000, First_Digit = -1; i > 0; i--, div = div / 10) {
        Digit[i] = value / div;
        value -= div * Digit[i];
        if (First_Digit < 0) {
            if (Digit[i]) {
                First_Digit = i;
            }
        }
    }
    Digit[0] = value;
    i = x - (First_Digit * 2);
    for (j = First_Digit; j >= 0; j--, i += 2) {
        score16x24_put(i, y, 14, Digit[j]);
    }
}



/* provisional name */
void Disp_Win_Type(void) {
    s16 i;
    for (i = 0; i <= Game_setting.Battle_Number; i++) {
        win_mark_put(i, win_type[0][i], 28);
        win_mark_put(i + 4, win_type[1][i], 28);
    }
}

/* provisional name */
void commit_name_entry_row_both_players(pos_y)
s16 pos_y;
{
    if (E_Number[0][0] == ENTRY_NAME && name_wk[0].dmm) {
        rank_display_set(0, pos_y);
    }
    if (E_Number[1][0] == ENTRY_NAME && name_wk[1].dmm) {
        rank_display_set(1, pos_y);
    }
}


/* provisional name: the vertical range check */
s32 Ck_Range_Out_Y(WORK_Other* ewk, s16 BG_No, s16 R) {
    u16 y;
    y = ewk->wu.xyz[1].disp.pos;
    y += R;
    y -= bg_w.bgw[BG_No].xy[1].disp.pos;
    if (y > 320) {
        return 1;
    }
    return 0;
}



s32 Ck_Range_Out_S(WORK_Other* ewk, s16 BG_No, s16 R) {
    u16 x;
    x = ewk->wu.xyz[0].disp.pos;
    x -= bg_w.bgw[BG_No].position_x - 64;
    if (DE_X[5] + R + 384 < x) {
        return 1;
    }
    return 0;
}


/* provisional name */
s32 Count_Tens(s16 x) {
    s16 n = 0;
    while (x > 10) {
        x -= 10;
        n++;
    }
    return n;
}



void Disp_Copyright(void) {
    void (*fp)(s32 x, s32 y, s32 attr, const s8* str) = (void (*)(s32, s32, s32, const s8*))tilemap_print_string_attr;
    register s16* py = &Text_Page_Y;
    s16* px = &DE_X[0];
    switch (Country) {
    case 1:
    case 2:
    case 3:
    case 6:
    case 8:
        fp(*px + 3, *py + 26, 18, "@CAPCOM CO., LTD. \001\011\011\007 ALL RIGHTS RESERVED.");
        break;
    case 4:
        fp(*px + 1, *py + 25, 18, "@CAPCOM CO., LTD. \001\011\011\007");
        fp(*px + 1, *py + 26, 18, "@CAPCOM U.S.A., INC. \001\011\011\007 ALL RIGHTS RESERVED.");
        break;
    case 5:
    case 7:
        fp(*px + 14, *py + 24, 18, "@CAPCOM CO., LTD. \001\011\011\007");
        fp(*px + 12, *py + 25, 18, "@CAPCOM MEXICO S,A. DE C.V.");
        fp(*px + 13, *py + 26, 18, "\001\011\011\007 ALL RIGHTS RESERVED.");
        break;
    }
}



/* 1 while a player (not the CPU) holds a button. */
s32 Cut_Cut_Cut(void) {
    s32 m = 0x7F0;
    PLW* pl = plw;
    if (pl[0].wu.operator && (p1sw_0 & m)) {
        return 1;
    }
    if (pl[1].wu.operator && (p2sw_0 & m)) {
        return 1;
    }
    return 0;
}



s32 Cut_Cut_Sub(s16 cut) {
    if (plw[0].wu.operator) {
        if (p1sw_0 & 0x7F0) {
            return cut;
        }
    }
    if (plw[1].wu.operator) {
        if (p2sw_0 & 0x7F0) {
            return cut;
        }
    }
    return 1;
}



/* Counts the scene timer down; returns what is left, 0 when a button cut the scene. */


