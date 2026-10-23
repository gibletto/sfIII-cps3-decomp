#ifndef BG_SUB_3_H
#define BG_SUB_3_H

#include "structs.h"

s32 zoom_frame_judge(void);
void zoom_x_width_check(void);
void zoom_y_width_check(void);
void bg_x_move_check(void);
void bg_y_move_check(void);
void bg_base_y_move_check(void);
void suzi_line_calc(s16 bg_num);
void suzi_line_calc_fill(s16 bg_num);
void suzi_line_clear(s16 bg_num);
void zoom_ud_check(void);

#endif
