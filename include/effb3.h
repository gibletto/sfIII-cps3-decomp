#ifndef EFFB3_H
#define EFFB3_H

#include "structs.h"

s32 effect_B3_init(WORK_Other* wk);
void effect_B3_move(WORK_Other* ewk);
void fight_move(WORK_Other* ewk);
void round_move_init(WORK_Other* ewk);
void round_vanish(WORK_Other* ewk);
void effB3_kill(WORK_Other* ewk);

#endif
