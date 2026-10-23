/*
 * HITEFEF.C  Effect attack against effect
 *
 * effect_at_vs_effect_dm is called from HITCHECK for a judged hit where both the attacker and the
 * defender are effects (for example two projectiles). It sets both works' damage facing, the hit mark
 * position, the damage and hit stop, and checks the extended hit data (hit_pattern_extdat_check).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "HITCHECK.h"
#include "EFF02.h"
#include "HITEFEF.h"

void cal_hit_mark_pos();



void effect_at_vs_effect_dm(ix2, ix)
s16 ix2;
s16 ix;
{
    WORK_Other* as = (WORK_Other*)q_hit_push[ix2];
    WORK_Other* ds = (WORK_Other*)q_hit_push[ix];
    ds->wu.dm_rl = as->wu.rl_flag;
    as->wu.dm_rl = ds->wu.rl_flag;
    cal_hit_mark_pos(&as->wu, &ds->wu, ix2, ix);
    if (ds->wu.id == 13) {
        switch (as->wu.work_id) {
        case 4:
            ds->wu.dm_vital = as->wu.vital_new;
            as->wu.dm_vital = ds->wu.vital_new;
            break;
        default:
            break;
        }
    } else {
        ds->wu.dm_vital = 256;
    }
    if (ds->wu.xyz[1].disp.pos > 0) {
        as->wu.hf.hit.effect = ds->wu.hf.hit.effect = 2;
    } else {
        as->wu.hf.hit.effect = ds->wu.hf.hit.effect = 1;
    }
    ds->wu.routine_no[1] = 1;
    ds->wu.routine_no[2] = 0;
    as->wu.hit_stop = ds->wu.hit_stop = 6;
    if (ds->wu.work_id == 1) {
        effect_02_init(&as->wu, 2, 1, ds->wu.dm_rl);
    }
    hit_pattern_extdat_check(&as->wu);
}
