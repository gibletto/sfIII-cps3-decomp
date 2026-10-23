#ifndef EFF51_H
#define EFF51_H

#include "structs.h"

s32 effect_51_init(s16 step, s16 x, s16 y, s16 timer, s16 dir_old, s16 col_ofs, s16 use_ofs, s16 col2_ofs);
s32 Flash_Violent();
void effect_51_move(WORK_Other_CONN* ewk);

#endif
