#ifndef EFFD5_H
#define EFFD5_H

#include "structs.h"

void effect_D5_move(WORK_Other* ewk);
void effD5_cursor(WORK_Other* ewk, s16 pl);
void effD5_fix();
s32 effD5_sel_id(s16 pl);
s32 effect_D5_init(s16 id);
s32 effect_D5_init2(void);
void Setup_EffD5(WORK* wk);

#endif
