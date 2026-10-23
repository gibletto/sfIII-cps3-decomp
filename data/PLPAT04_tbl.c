/*
 * PLPAT04_TBL.C  tables read by PLPAT04.c, PLPAT05.c and PLPAT06.c: the characters' special attack routine tables
 * (plNN_exatt_table)
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const pl04_exatt_table[])(PLW*);
extern void (*const pl05_exatt_table[])(PLW*);
extern void (*const pl06_exatt_table[])(PLW*);
extern void Att_ABISEGERI();
extern void Att_CHOUCHUURENGEKI();
extern void Att_DUMMY();
extern void Att_HADOUKEN();
extern void Att_HADOUKEN2();
extern void Att_NM_OKIAGARI();
extern void Att_SENPUUKYAKU();
extern void Att_SHOURYUUREPPA();

void (*const pl04_exatt_table[11])(PLW*) = {
    Att_SENPUUKYAKU, Att_SENPUUKYAKU, Att_HADOUKEN, Att_SHOURYUUREPPA,
    Att_HADOUKEN2, Att_CHOUCHUURENGEKI, Att_CHOUCHUURENGEKI, Att_HADOUKEN,
    Att_ABISEGERI, Att_HADOUKEN, Att_NM_OKIAGARI,
};

void (*const pl05_exatt_table[9])(PLW*) = {
    Att_CHOUCHUURENGEKI, Att_HADOUKEN, Att_HADOUKEN, Att_HADOUKEN,
    Att_HADOUKEN, Att_SENPUUKYAKU, Att_HADOUKEN, Att_HADOUKEN,
    Att_HADOUKEN,
};

void (*const pl06_exatt_table[1])(PLW*) = {
    Att_DUMMY,
};
