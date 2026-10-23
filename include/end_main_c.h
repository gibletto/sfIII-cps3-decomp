#ifndef END_MAIN_C_H
#define END_MAIN_C_H

#include "structs.h"

void Ending_init(void);
s32 Ending_main(s16 pl_num);
void end_main_move(s16 pl_num);
void end_00000(void);
void end_06000(void);
void end_color_load(void);
void fadeout_to_staff_roll(void);
void common_end_init00(s16 pl_num);
void common_end_init01(void);
void end_fam_set(s16 i);
void end_fam_set2(void);
void end_bg_pos_hosei(s16 bg_no);
void end_bg_pos_hosei2(void);
void end_scn_pos_set(u16 bg_no);
void end_scn_pos_set2(void);
void end_bg_block_attr_add(s16 bg, s32 ofs, s16 w, s32 cell, s16 h);
void end_reset_etc(void);
void end_X_com01(void);
void end_fade_bgm(void);
s16 end_fade_complete(void);
s32 Cut_Cut_Cut_t(void);
void end_staff_flag_set(void);

#endif
