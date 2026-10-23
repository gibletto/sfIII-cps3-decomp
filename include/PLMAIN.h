#ifndef PLMAIN_H
#define PLMAIN_H

#include "structs.h"

void Player_move(PLW* wk, u16 lv_data);
s32 check_hit_stop(PLW* wk);
void player_mv_2000(PLW* wk);
void player_mv_3000(PLW* wk);
void sag_normal(PLW* wk);
void sag_timer(PLW* wk);
void sag_timer_dummy(void);
void sag_rebirth(PLW* wk);
void demo_set_sa_full(SA_WORK* sa);
void get_saikinnno_idouryou(PLW* wk);
void look_after_timers(PLW* wk);
void player_mv_0000(PLW* wk);
void player_mv_1000(PLW* wk);
void player_mv_4000(PLW* wk);
void plmv_1010(PLW* wk);
void plmv_1020(PLW* wk, s16 step);
s32 select_hit_stop(s16 ms, s16 sb);

#endif
