#ifndef EFFD1_H
#define EFFD1_H

#include "structs.h"

s32 effect_D0_init(PLW* oya);
s32 effect_D1_init(WORK_Other* oya, s32 );
void effect_D1_move(WORK_Other* ewk);
void fall_data_set(WORK_Other* ewk);

#endif
