#ifndef SYS_SUB_H
#define SYS_SUB_H

#include "structs.h"

s32 Check_Fade_Complete_SP(void);
s32 Ck_Range_Out_S(WORK_Other* ewk, s16 BG_No, s16 R);
s32 Ck_Range_Out_Y(WORK_Other* ewk, s16 BG_No, s16 R);  /* provisional name */
s32 Cut_Cut_Cut(void);
void Scr_all_clear_Wait(void);
void System_all_clear_Wait(void);
void System_all_clear_Ex_Wait(void);
void System_all_clear(void);
void System_all_clear_Ex(void);
s32 Check_Fade_Complete(void);
s32 Request_Fade();
void Switch_Screen_Init();
s32 Switch_Screen(void);
s32 Switch_Screen_Revival(void);
void scfont_page0_fill(u32 attr, u16 code);
void scfont_page1_fill(u32 attr, u16 code);
s32 Button_Cut_Hold(s16* timer, s16 first, s16 repeat);
void Disp_Digit8x16(u32 value, s16 x, s16 y);
void Disp_Win_Type(void);
void Disp_Copyright(void);
s32 Cut_Cut_Sub(s16 xx);
void Setup_Play_Type(void);
void scrn_pos_clear(void);
void challenger_banner_clear(void);
void commit_name_entry_row_both_players();
void Clear_Flash_No(void);
s32 Check_Sort_Ranking();       /* provisional name */
s32 Setup_Target_PL(void);
u32 Check_Ranking();
void Check_Partners_Rank();
void Fade_Cont(void);
void Disp_Digit16x24();

#endif
