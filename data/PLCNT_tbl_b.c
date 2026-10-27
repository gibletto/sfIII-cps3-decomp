/*
 * PLCNT_TBL_B.C  stun limits
 *
 * pl_piyo_tbl gives each character's stun limit. Read by PLCNTSET_2.C when it sets up a
 * player's stun state; the recovery rates are pl_nr_piyo_tbl in PLCNT_TBL_C.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 pl_piyo_tbl[];

const s16 pl_piyo_tbl[16] = {
    80, 80, 64, 64, 72, 64, 88, 64, 64, 72, 64, 64, 64, 0, 0, 0,
};
