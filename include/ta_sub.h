#ifndef TA_SUB_H
#define TA_SUB_H

#include "structs.h"

void pl_eff_trans_entry_r(WORK_Other* ewk);
s32 complete_victory_check(void);
u32 range_abs_check(s16 a, s16 b, s16 range);
s32 either_pl_hissatsu_check(void);
s32 pl_shot_on_check();
void add_x_sub(WORK_Other* ewk);
void add_x_sub2(WORK_Other* ewk);
void add_x_sub_flip(WORK_Other* ewk);
void add_y_sub(WORK_Other* ewk);
void add_y_sub2(WORK_Other* ewk);
s32 compel_dead_check(WORK_Other* ewk);
void disp_pos_trans_entry(WORK_Other* ewk);
void disp_pos_trans_entry5(WORK_Other* ewk);
void disp_pos_trans_entry_r(WORK_Other* ewk);
void disp_pos_trans_entry_rs(WORK_Other* ewk);
void disp_pos_trans_entry_s(WORK_Other* ewk);
s32 eff_hit_check(WORK_Other* ewk, s16 type);
s32 eff_hit_check_sub(WORK_Other* ewk, PLW* pl);
void eff_hit_flag_clear(void);
s32 range_x_check(WORK* wk);
s32 obr_no_disp_check(void);
void pl_eff_trans_entry(WORK_Other* ewk);
void sync_fam_set3();
void sync_fam_set(s16 num_of_bg);
void sync_fam_set2(s16 num_of_bg);

#endif
