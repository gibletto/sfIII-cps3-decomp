#ifndef PLS02_H
#define PLS02_H

#include "structs.h"

s32 random_32_ex_com(void);
void setup_air_paring_mvxy(WORK* wk);
void add_mvxy_speed(WORK* wk);
void add_mvxy_speed_direct(WORK* wk, s16 sx, s16 sy);
void add_mvxy_speed_no_use_rl(WORK* wk);
void add_to_mvxy_data();
s32 cal_attdir(WORK* wk);
void cal_mvxy_speed(WORK* wk);
void check_body_touch(void);
s32 check_work_position(WORK* p1, WORK* p2);
s32 get_guard_direction(WORK* as, WORK* ds);
s32 get_weight_point(WORK* wk);
s32 meri_case_switch();
s32 random_16_com(void);
s32 random_16_ex_com(void);
s32 random_32_com(void);
void read_adrs_store_mvxy(WORK* wk, s16* adrs);
void remake_mvxy_PoGR(WORK* wk);
void remake_mvxy_PoSB(WORK* wk);
void reset_mvxy_data(WORK* wk);
s32 set_field_hosei_flag();
void setup_butt_own_data();
void setup_mvxy_data();
void attack_hit_dummy(PLW* wk);   /* provisional name */

#endif
