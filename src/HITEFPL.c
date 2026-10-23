/*
 * HITEFPL.C  Effect attack against player
 *
 * effect_at_vs_player_dm is called from HITCHECK (set_struck_status) when an effect's attack hits a
 * player. It sets the damage point and facing (the attacker's), the hit mark position and the damage
 * (with combo damage reduction), then runs the shared damage/guard handling
 * (plef_at_vs_player_damage_union).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "pow_pow.h"
#include "PLSGAUGE.h"
#include "PLS02.h"
#include "HITEFPL.h"

void cal_combo_waribiki(PLW* as, PLW* ds);
void cal_hit_mark_pos();
void plef_at_vs_player_damage_union();



void effect_at_vs_player_dm(ix2, ix)
s16 ix2;
s16 ix;
{
    WORK_Other* as = (WORK_Other*)q_hit_push[ix2];
    PLW* ds = (PLW*)q_hit_push[ix];
    s8 gddir;
    ds->dm_point = hs[ix].dm_body;
    gddir = get_guard_direction(&as->wu, &ds->wu);
    setup_saishin_lvdir(ds, gddir);
    ds->wu.dm_rl = as->wu.rl_flag;
    cal_hit_mark_pos(&as->wu, &ds->wu, ix2, ix);
    cal_damage_vitality_eff(as, ds);
    cal_combo_waribiki((PLW*)as, ds);
    cal_dm_vital_gauge_hosei(ds);
    ds->wu.dm_piyo = add_piyo_gauge[as->master_player][as->wu.att.piyo];
    as->wu.dm_vital = 256;
    ds->atemi_flag = 0;
    plef_at_vs_player_damage_union((PLW*)as, ds, gddir);
}
