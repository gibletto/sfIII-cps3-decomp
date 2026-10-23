#ifndef EFF48_H
#define EFF48_H

#include "structs.h"

s32 effect_48_init(s16 type);
void effect_48_move(WORK_Other* ewk);
void eff48_set_wait(WORK_Other* ewk);
void eff48_page0_write(void);
void eff48_page1_write(void);

#endif
