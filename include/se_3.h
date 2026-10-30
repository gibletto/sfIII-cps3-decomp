#ifndef SE_3_H
#define SE_3_H

#include "structs.h"

void Call_Se(WORK_Other* ewk, u16 Code);
s32 Check_Finish_SE(void);
void bgm_fade_in_stage(s16 x);
void Se_Myself(WORK_Other* ewk, u16 Code);
void Se_Myself_Die(WORK_Other* ewk, u16 se);
void Se_Let_SP(WORK_Other* ewk, u16 Code);
s32 Se_Term(WORK_Other* ewk, u16 Code);
void Finish_SE(void);
s32 Get_Position(PLW* wk);
void Se_Let(WORK_Other* ewk, u16 Code);
void Stage_BGM();
void Se_Shock(WORK_Other* ewk, u16 se);
void SE_All_Off(void);
void Se_Dummy(WORK_Other* ewk, u16 Code);
void BGM_Stop(void);
s32 Check_Voice_SE();
void BGM_Request();
void Sound_SE();

#endif
