#ifndef EFFD4_H
#define EFFD4_H

#include "structs.h"

s32 effect_D4_init(WORK* wk, u8 data);
void effect_D4_move(WORK_Other* ewk);
s32 distance2speed(WORK_Other* ewk, WORK* wk, s32 dir);

#endif
