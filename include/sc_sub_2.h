#ifndef SC_SUB_2_H
#define SC_SUB_2_H

#include "structs.h"

void fade_cont_init(void);
s32 fade_cont_main();
void stngauge_cont_init(void);
void stngauge_cont_main();
void stngauge_control(s32 player);
void stngauge_work_clear(void);
void stun_gauge_waku_write(s8 pl);
void stun_mark_write(s8 pl, s8 kind);
void stun_put();

#endif
