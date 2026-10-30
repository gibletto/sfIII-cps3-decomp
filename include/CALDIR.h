#ifndef CALDIR_H
#define CALDIR_H

#include "structs.h"

s32 caldir_pos_256();
s16 caldir_pos_128(s16 x1, s16 x2, s16 y1, s16 y2);
s16 caldir_pos_064(s16 x1, s16 x2, s16 y1, s16 y2);
s16 caldir_pos_032();
s16 caldir_pos_016(s16 x1, s16 x2, s16 y1, s16 y2);
s16 caldir_pos_008(s16 x1, s16 x2, s16 y1, s16 y2);
s32 caldir_wk_256(WORK* wk, WORK* emwk);
s16 caldir_wk_128(WORK* wk, WORK* emwk);
s16 caldir_wk_064(WORK* wk, WORK* emwk);
s16 caldir_wk_032(WORK* wk, WORK* emwk);
s16 caldir_wk_016(WORK* wk, WORK* emwk);
s16 caldir_wk_008(WORK* wk, WORK* emwk);
s16 cal_move_quantity(WORK* wk, s16 t);
void cal_initial_speed_y0(WORK* wk, s16 tm);
void add_pos_dir_064(WORK* wk, s16 sp);
void add_pos_dir_256(WORK* wk, s16 sp);
void add_pos_dir_128(WORK* wk, s16 sp);
void add_pos_dir_032(WORK* wk, s16 sp);
void add_pos_dir_016(WORK* wk, s16 sp);
void add_pos_dir_008(WORK* wk, s16 sp);
s16 dir256_to_128(s16 dir);
s16 dir256_to_064(s16 dir);
s16 dir256_to_032(s16 dir);
s16 dir256_to_016(s16 dir);
s16 dir256_to_008(s16 dir);
void cal_all_speed_data();
void cal_delta_speed();
void cal_initial_speed();
void cal_initial_speed_y(WORK* wk, s16 tm, s16 y1);
s32 cal_move_dir_forecast(WORK* wk, s16 tm);
s16 cal_move_quantity2(s16 x1, s16 x2, s16 y1, s16 y2);
s16 cal_move_quantity3(WORK* wk, s16 tm);
s32 cal_time_of_sign_change(WORK* wk);
s16 cal_top_of_position_y(WORK* wk);
void cmsd_all_x_speed_data(MotionState* cc);
void cmsd_all_y_speed_data(MotionState* cc);
void cmsd_swx_0(MotionState* cc);
void cmsd_swx_1(MotionState* cc);
void cmsd_swx_2(MotionState* cc);
void cmsd_swy_0(MotionState* cc);
void cmsd_swy_1(MotionState* cc);
void cmsd_swy_2(MotionState* cc);
void cmsd_x_delta_speed(MotionState* cc);
void cmsd_x_initial_speed(MotionState* cc);
void cmsd_y_delta_speed(MotionState* cc);
void cmsd_y_initial_speed(MotionState* cc);

#endif
