#ifndef PLPDM_H
#define PLPDM_H

#include "structs.h"

void Damage_00000(PLW* wk);
void Damage_01000(PLW* wk);
void Damage_04000(PLW* wk);
void Damage_12000(PLW* wk);
void Damage_14000(PLW* wk);
void Damage_16000(PLW* wk);
void Damage_17000(PLW* wk);
void Damage_18000(PLW* wk);
void Damage_19000(PLW* wk);
void Damage_20000(PLW* wk);
void Damage_21000(PLW* wk);
void Damage_23000(PLW* wk);
void Damage_24000(PLW* wk);
void Damage_25000(PLW* wk);
void Damage_26000(PLW* wk);
void Damage_27000(PLW* wk);
void Damage_28000(PLW* wk);
void Damage_29000(PLW* wk);
void Damage_07000(PLW* wk);
void Damage_08000(PLW* wk);
void setup_smoke_type(PLW* wk);
void set_dm_hos_flag_grd(PLW* wk);
void get_catch_off_data(PLW* wk, s16 ix);
void Player_damage(PLW* wk);
void add_dm_step_tbl(PLW* wk);
void buttobi_chakuchi_cg_type_check(PLW* wk);
void check_bullet_damage(PLW* wk);
void check_dmpat_to_dmpat(PLW* wk);
void first_TtktV_union(PLW* wk, s16 num, s16 dv);
void first_flight_union(PLW* wk, s16 num, s16 dv);
void get_damage_reaction_data(PLW* wk);
void subtract_dm_vital(PLW* wk);
void get_sky_dm_timer(PLW* wk);
void set_dm_hos_flag_sky(PLW* wk);
s32 setup_kuzureochi(PLW* wk);
void subtract_dm_vital_aiuchi(PLW* wk);

#endif
