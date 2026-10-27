/*
 * PLPAT12_TBL.C  Sean's special attack table
 *
 * pl12_exatt_table is the list of Sean's nine special attack routines, indexed by attack
 * routine number minus 16. Read by PLPAT12.C, which dispatches through it from
 * pl12_extra_attack.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const pl12_exatt_table[])(PLW*);
extern void Att_ABISEGERI();
extern void Att_CHOUCHUURENGEKI();
extern void Att_HADOUKEN();
extern void Att_KUUCHUUNICHIRINSHOU();
extern void Att_SENPUUKYAKU();
extern void Att_SHOURYUUKEN();
extern void Att_SHOURYUUREPPA();
extern void Att_SLIDE_and_JUMP();

void (*const pl12_exatt_table[9])(PLW*) = {
    Att_HADOUKEN, Att_SHOURYUUREPPA, Att_SLIDE_and_JUMP, Att_ABISEGERI,
    Att_CHOUCHUURENGEKI, Att_SHOURYUUKEN, Att_CHOUCHUURENGEKI, Att_KUUCHUUNICHIRINSHOU,
    Att_SENPUUKYAKU,
};
