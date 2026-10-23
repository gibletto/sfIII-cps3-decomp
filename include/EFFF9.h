#ifndef EFFF9_H
#define EFFF9_H

#include "structs.h"

s32 effect_F9_init(s16 pl_no);
s32 Set_Direct_Message(s16 mes);
s32 Rewrite_End_Message(u16 mes_no);
void effect_F9_move(WORK_Other_CONN* ewk);
s32 Next_Talk_Message(void);
void efff9_wk_set(WORK_Other_CONN* ewk);

#endif
