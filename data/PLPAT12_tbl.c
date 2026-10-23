/*
 * PLPAT12_TBL.C  tables read by PLPAT12.c: the characters' special attack routine tables (plNN_exatt_table)
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
