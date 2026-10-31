#ifndef SYS_TEST_2_H
#define SYS_TEST_2_H

#include "structs.h"

s32 iotest_input_page(void);
s32 iotest_output_page(void);
void soundtest_draw_title(void);
s32 soundtest_page(void);
void colortest_draw_title(void);
s32 colortest_page(void);
s32 screentest_page(void);
void colortest_draw_palette_grid(void);
void iotest_draw_sw_grid(void);
void iotest_output_toggle(void);
void soundtest_print_lr_balance(s32 x, s32 y, s32 now, s32 old);
void soundtest_print_level_bar(s32 x, s32 y, s32 level);
void soundtest_print_pan_bar(s32 x, s32 y, s32 pan);
void screentest_draw_crosshatch(void);
void soundtest_monitor_task(void);
void soundtest_code_select(void);

#endif
