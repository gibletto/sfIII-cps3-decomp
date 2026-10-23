#ifndef EFF18_H
#define EFF18_H

#include "structs.h"

void eff18_00(WORK* wk);
void eff18_01(WORK* wk);
s32 effect_18_init(s16 disp_index, s16 cursor_id, s16 sync_bg, s16 master_player);
void effect_18_move(WORK_Other* ewk);

#endif
