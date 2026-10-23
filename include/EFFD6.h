#ifndef EFFD6_H
#define EFFD6_H

#include "structs.h"

void effect_D6_move(WORK_Other* ewk);
void EFFD6_WAIT(WORK_Other* ewk);
void EFFD6_RISE_IN(WORK_Other* ewk);
void EFFD6_SLIDE_IN(WORK_Other* ewk);
void EFFD6_SLIDE_OUT(WORK_Other* ewk);
void EFFD6_ZOOM_SLIDE(WORK_Other* ewk);
void EFFD6_RESET(WORK_Other* ewk);
s32 effect_D6_init(s16 dir_old);

#endif
