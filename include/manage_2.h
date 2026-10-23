#ifndef MANAGE_2_H
#define MANAGE_2_H

#include "structs.h"

void Additional_Bonus(s16 PL_id);
void Check_Naming();
void Game_Manage_10th(void);
void Game_Manage_1st(void);
void Game_Manage_2nd(void);
void Game_Manage_3rd(void);
void Game_Manage_4th(void);
void Game_Manage_5th(void);
void Game_Manage_6th(void);
void Game_Manage_7th(void);
void Game_Manage_8th(void);
void Game_Manage_9th(void);
void Game_Management(void);
void Setup_Win_Mark(void);
void Ck_Win_Record(void);
void Erase_Win_Record();
void Disp_Win_Record_Sub();
void Disp_Win_Record(void);
void BGM_Fade_Sub(void);
s32 Check_Ending();
void Disp_Winner(void);
s32 Judge_Next_Disposal(void);
void Check_Perfect(s16 PL_id);
void Quick_Entry(void);
s32 Check_Entry_Again(void);
void Loser_Sub(void);
void Be_Continue(void);
void Update_VS_Data(void);
void Check_Fade_Out_BGM(s16 code);
void Control_Music_Fade(void);
void complete_victory_pause(void);
void Judge_Winner(void);
void Setup_BGM_Fade_In(s16 time);
void Update_Level_Control(void);
void request_center_message(s16 Kind_of_Message);

#endif
