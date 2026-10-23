#ifndef CMB_CONT_H
#define CMB_CONT_H

#include "structs.h"

void SCORE_PLUS();
s32 arts_finish_check();
void combo_cont_init(void);
void combo_cont_main(void);
void combo_control(s8 PL);
void check_and_set_combo();
void combo_hensuu_clear();
void combo_window_push();
u32 SCORE_CALCULATION();
void combo_window_trans(s8 PL);
void first_attack_pts_check();
void hit_combo_check();
s32 paring_check();
s32 reversal_check();
void reversal_continue_check();
void super_arts_finish_check();
s32 arts_finish_check2();
void super_arts_last_check();

#endif
