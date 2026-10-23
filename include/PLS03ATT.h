#ifndef PLS03ATT_H
#define PLS03ATT_H

#include "structs.h"

s32 check_jump_pat_status(PLW* wk);
s32 check_paring_attack(PLW* wk);
s32 check_lever_up_attack(PLW* wk);
s32 shot_data_convert();
s32 check_sp_waza_flag(PLW* wk);
s32 check_catch_attack(PLW* wk);
s32 check_meoshi_cancel(PLW* wk);
s32 check_nm_attack(PLW* wk);
s32 waza_select();
s32 check_renda_cancel(PLW* wk);
s32 cmd_ex_check();
s32 decode_wst_data();
s32 check_dm_shot_attack(PLW* wk);
s32 get_em_body_range(WORK* wk);
s32 get_nearing_range();
void set_attack_routine_number(PLW* wk);
s16 shot_data_refresh(s16 sw);
s32 get_catch_kos(PLW* wk);   /* provisional name */

#endif
