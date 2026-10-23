#ifndef PLS00_H
#define PLS00_H

#include "structs.h"

void dm_00000(PLW* wk);
void TO_nm_01000(WORK* wk);
void TO_nm_09000(WORK* wk);
void TO_nm_18000_01(WORK* wk);
void nm_00000(PLW* wk);
void TO_nm_36000(WORK* wk);
void TO_nm_37000(WORK* wk);
void TO_nm_38000(WORK* wk);
s32 check_cg_cancel_data(PLW* wk);
void check_jump_rl_dir(PLW* wk);
void check_lever_data(PLW* wk);
void dm_25000(PLW* wk);
void jumping_cg_type_check(PLW* wk);
void jumping_guard_type_check(PLW* wk);
void nm_01000(PLW* wk);
void nm_02000(PLW* wk);
void nm_03000(PLW* wk);
void nm_05000(PLW* wk);
void nm_07000(PLW* wk);
void nm_08000(PLW* wk);
void nm_09000(PLW* wk);
void nm_10000(PLW* wk);
void nm_11000(PLW* wk);
void nm_13000(WORK* wk);
void nm_16000(PLW* wk);
void nm_17000(PLW* wk);
void nm_18000(PLW* wk);
void nm_27000(PLW* wk);
void nm_27_cg_type_check(PLW* wk);
void nm_29000(PLW* wk);
void nm_31000(PLW* wk);
void nm_34000(PLW* wk);
void nm_36000(PLW* wk);
void nm_37000(PLW* wk);
void nm_38000(PLW* wk);
void nm_39000(PLW* wk);
void nm_40000(PLW* wk);
void dm_04000(PLW* wk);
void dm_08000(PLW* wk);
void dm_18000(PLW* wk);
void dm_17000(PLW* wk);
void nm_91000(PLW* wk);
void process_caught(PLW* wk);
void nm_95000(PLW* wk);
void process_attack(PLW* wk);
void process_catch(PLW* wk);
void process_damage(PLW* wk);
void process_normal(PLW* wk);
void set_new_jpdir(PLW* wk);

#endif
