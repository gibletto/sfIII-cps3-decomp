#ifndef EFFF4_H
#define EFFF4_H

#include "structs.h"

s32 effect_F3_init(s16 step, s16 delay, s16 x, s16 y);
void effF3_pos_set(WORK_Other* ewk, s16 x);
void effect_F3_move(WORK_Other* ewk);
void effect_F4_move(WORK_Other* ewk);
void effect_F4_init(WORK_Other* ewk);

#endif
