#ifndef EFFE2_H
#define EFFE2_H

#include "structs.h"

void effE2_sort_push(WORK* ewk, WORK* mwk);
void effe2_erase_or_die(WORK* wk);
s32 effect_E2_init(PLW* wk, const s16* data, u8 ff);
void effect_E2_move(WORK_Other* ewk);
s32 setup_accessories();

#endif
