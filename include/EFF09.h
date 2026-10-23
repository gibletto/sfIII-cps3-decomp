#ifndef EFF09_H
#define EFF09_H

#include "structs.h"

void sean_ball_move();
void ball_bound_set(WORK_Other* ewk);
s32 effect_09_init(WORK_Other* mk, s8 kind);
void eff09_0000(WORK_Other* ewk);
void eff09_1000(WORK_Other* ewk);
void eff09_2000(WORK_Other* ewk);
void eff09_3000(WORK_Other* ewk);
void eff09_4000(WORK_Other* ewk);
void eff09_5000(WORK_Other* ewk);
void eff09_6000(WORK_Other* ewk);
void eff09_7000(WORK_Other* ewk);
void eff09_8000(WORK_Other* ewk);
s32 effect_09_init2(WORK* wk, u8 data);
void effect_09_move(WORK_Other* ewk);

#endif
