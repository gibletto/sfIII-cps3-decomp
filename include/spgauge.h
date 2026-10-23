#ifndef SPGAUGE_H
#define SPGAUGE_H

#include "structs.h"

void spgauge_cont_init(void);
void sa_color_chenge();
void satime_stock_clear(void);
void sa_gauge_trans();
void sa_moji_trans();
void sa_time_moji_send(void);
void sa_waku_trans(s8 pl_kind, s8 pl);
void sa_stock_trans();
void sa_lv_mark_trans();
void sa_lv_mark_put();
void sa_gauge_end_trans();
void samoji_control();
void sast_color_chenge();
void sast_control();
void spgauge_cont_demo_init(void);
void spgauge_cont_main(void);
void spgauge_control(s8 Spg_Num);
void spgauge_sound_request();
void spgauge_wipe_write(s8 Stpl_Num);
void spgauge_work_clear(s8 Stpl_Num);
void wipe_check(void);

#endif
