/*
 * HITPLPL.C  Player attack against player
 *
 * player_at_vs_player_dm is called from HITCHECK for a hit between the two players. It sets the damage point and guard direction, then the damage facing (setup_dm_rl), the hit mark
 * position and damage and stun (set_damage_and_piyo), and resolves the hit (plef_at_vs_player_damage_union).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLS02.h"
#include "PLSGAUGE.h"
#include "HITPLPL.h"
#include "HITCHECK.h"



void player_at_vs_player_dm(ix2, ix)
s16 ix2;
s16 ix;
{
    PLW* as = (PLW*)q_hit_push[ix2];
    PLW* ds = (PLW*)q_hit_push[ix];
    s8 gddir;
    ds->dm_point = hs[ix].dm_body;
    gddir = get_guard_direction(&as->wu, &ds->wu);
    setup_saishin_lvdir(ds, gddir);
    setup_dm_rl(&as->wu, &ds->wu);
    cal_hit_mark_pos(&as->wu, &ds->wu, ix2, ix);
    set_damage_and_piyo(as, ds);
    plef_at_vs_player_damage_union(as, ds, gddir);
}
