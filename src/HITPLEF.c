/*
 * HITPLEF.C  Player attack against effect
 *
 * player_at_vs_effect_dm is called from HITCHECK when a player's attack hits an effect such as a
 * projectile or a bonus-stage object. It checks the extended hit data, copies the damage status
 * to the effect (dm_status_copy) and sets the hit mark position.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "win_2.h"
#include "continue.h"
#include "pow_pow.h"
#include "HITCHECK.h"
#include "EFF02.h"
#include "HITPLEF.h"


void player_at_vs_effect_dm(ix2, ix)
s16 ix2;
s16 ix;
{
    PLW* as = (PLW*)q_hit_push[ix2];
    WORK_Other* ds = (WORK_Other*)q_hit_push[ix];
    ds->wu.dm_rl = as->wu.rl_flag;
    cal_hit_mark_pos(&as->wu, &ds->wu, ix2, ix);
    ds->wu.dm_vital = 256;
    if (ds->wu.xyz[1].disp.pos <= 0) {
        as->wu.hf.hit.player = 2;
    } else {
        as->wu.hf.hit.player = 1;
    }
    ds->wu.routine_no[1] = 1;
    ds->wu.routine_no[2] = 0;
    if (ds->wu.id != 13) {
        effect_02_init(&as->wu, 2, 1, ds->wu.dm_rl);
    } else if (ds->wu.charset_id == 2) {
        effect_02_init(&as->wu, 2, 2, ds->wu.dm_rl);
    }
    dm_status_copy(&as->wu, &ds->wu);
    if (ds->wu.work_id == 2) {
        as->wu.att_hit_ok = 1;
        as->wu.hit_stop /= 2;
        ds->wu.dm_stop /= 2;
    }
    hit_pattern_extdat_check(&as->wu);
}
