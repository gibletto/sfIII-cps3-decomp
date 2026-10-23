#ifndef EFF42_H
#define EFF42_H

#include "structs.h"

void Setup_Char_Index(WORK_Other* ewk);
s32 effect_41_init(PLW* wk, u8 data);
s32 effect_42_init(s16 Type);
void effect_42_move(WORK_Other* ewk);

s32 zoom_x_step_check();

#endif
