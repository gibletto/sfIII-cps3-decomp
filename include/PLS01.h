#ifndef PLS01_H
#define PLS01_H

#include "structs.h"

s32 check_ukemi_flag(PLW* wk);
void jumping_process_ix(WORK* wk, s16 ix, s16 num);
s32 check_360_jump(PLW* wk);
s32 check_F_R_dash(PLW* wk);
s32 check_F_R_walk(PLW* wk);
s32 check_attbox_dir(PLW* wk);
s32 check_bend_myself(PLW* wk);
s32 check_defense_kind(PLW* wk);
s32 check_defense_lever(PLW* wk);
s32 check_em_catt(PLW* wk);
s32 check_hijump_only(PLW* wk);
s32 check_jump_ready(PLW* wk);
s32 check_rl_flag(WORK* wk);
s32 check_stand_up(PLW* wk);
s32 check_turn_to_back(PLW* wk);
s32 check_walking_lv_dir(PLW* wk);
s32 check_walking_lv_dir2(PLW* wk);
s32 check_F_R_step(PLW* wk);
void jumping_union_process();
void set_rl_waza(PLW* wk);

#endif
