#ifndef EFF13_H
#define EFF13_H

#include "structs.h"

void kotp_00000(WORK_Other* ewk, TAMA* twk);
void kotp_02000(WORK_Other* ewk, TAMA* twk);
void kotp_03000(WORK_Other* ewk, TAMA* twk);
void kotp_01000(WORK_Other* ewk, TAMA* twk);
void set_tengu_my_home(WORK* ewk, WORK* mwk);
s32 check_tengu_attack(WORK* ewk, WORK* mwk, TAMA* twk);
s32 screen_range_check(WORK* wk);
void tama_display(WORK_Other* ewk);
void set_tengu_init_pos(WORK_Other* ewk, WORK* twk);
void effect_13_move(WORK_Other* ewk);
void make_speed_xy_back(WORK* ewk, WORK* mwk, TAMA* twk);
void make_speed_xy_att(WORK* ewk, WORK* mwk, s16 tm, u8 xsw, u8 ysw);

#endif
