#ifndef END_MAIN_H
#define END_MAIN_H

#include "structs.h"

void Ending_init(void);
s32 Ending_main(s16 pl_num);
void end_scn_pos_set(u16 bg_no);
void end_bg_block_attr_add(s16 bg, u16 ofs, s16 w, s32 cell, s16 h);
void common_end_init00(s16 pl_num);
void common_end_init01(void);
void end_X_com01(void);
void end_bg_pos_hosei(s16 bg_no);
void end_bg_pos_hosei2(void);
void end_fade_bgm(void);
s16 end_fade_complete(void);
void end_fam_set(s16 i);
void end_fam_set2(void);
void end_main_move(s16 pl_num);
void end_reset_etc();
void end_scn_pos_set2(void);
void fadeout_to_staff_roll(void);
s32 Cut_Cut_Cut_t(void);
void end_00000(void);

void op_w_clear(void);
s16 opening_demo_tick(void);
void opning_init_00000(void);
void opning_init_01000(void);
void op_02_move(void);
void op_04_move(void);
void op_03_move(void);
void op_08_move(void);
void op_09_move(void);
void op_10_move(void);
void op_11_move(void);
void op_fade_46(void);
void op_fade_45(void);
void op_12_move(void);
void op_13_move(void);
void op_15_move(void);
void op_16_move(void);
void op_17_move(void);
void op_14_move(void);
void op_20_move(void);
void op_21_move(void);
void op_scrn_map_set();
void op_scrn_pos_set();
void opening_family_set(void);

void scrn_map_set(u16 n, u32 p);
void scrn_map_set_now(u16 n, u32 p);

#endif
