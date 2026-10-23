#ifndef HITCHECK_H
#define HITCHECK_H

#include "structs.h"

void add_combo_work(PLW* as, PLW* ds);
void attack_hit_check(void);
void cal_combo_waribiki(PLW* as, PLW* ds);
void cal_combo_waribiki2(PLW* ds);
void cal_hit_mark_pos();
void cal_hit_mark_position(WORK* wk1, WORK* wk2, s16* hd1, s16* hd2);
void catch_hit_check(void);
s32 change_damage_attribute();
s32 check_ttk_damage_request();
s32 check_dm_att_guard(WORK* as, WORK* ds);
s32 check_head_damage(s16 ix);
void check_result_extra(void);
s32 check_trunk_damage(s16 ix);
void clear_hit_queue(void);
s32 defense_ground();
s32 defense_sky();
void dm_reaction_init_set(PLW* as, PLW* ds);
void dm_status_copy(WORK* as, WORK* ds);
s16 get_grd_hand_damage(u16 ix);
s16 get_kagami_damage(u16 ix);
s16 get_kagami2_damage(u16 ix);
s16 get_sky_nm_damage(u16 ix);
s16 get_sky_nm2_damage(u16 ix);
s16 get_sky_sp_damage(u16 ix);
void get_target_att_position(WORK* wk, s16* tx, s16* ty);
void hit_check_main_process(void);
s32 hit_check_subroutine(WORK* wk1, WORK* wk2, const s16* hd1, const s16* hd2);
void hit_pattern_extdat_check(WORK* as);
void hit_push_request(WORK* hpr_wk);
void plef_at_vs_player_damage_union();
s16 remake_score_index(s16 dmv);
void same_dm_stop(WORK* as, WORK* ds);
void set_paring_status(PLW* as, PLW* ds);
void set_catch_hit_mark_pos(WORK* as, WORK* ds);
void set_caught_status();
void set_char_base_data_init(WORK* wk);
void set_damage_and_piyo(PLW* as, PLW* ds);
void set_guard_status(PLW* as, PLW* ds);
s32 set_judge_result(void);
void set_struck_status();
void setup_catch_atthit(WORK* as, WORK* ds);
void setup_dm_rl(WORK* as, WORK* ds);

#endif
