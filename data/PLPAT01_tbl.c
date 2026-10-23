/*
 * PLPAT01_TBL.C  tables read by PLPAT01.c, PLPAT02.c and PLPAT03.c: the characters' special attack routine tables
 * (plNN_exatt_table)
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const pl01_exatt_table[])(PLW*);
extern void (*const pl02_exatt_table[])(PLW*);
extern void (*const pl03_exatt_table[])(PLW*);
extern void Att_CHOUCHUURENGEKI();
extern void Att_HADOUKEN();
extern void Att_HADOUKEN2();
extern void Att_KUUCHUUNICHIRINSHOU();
extern void Att_NM_OKIAGARI();
extern void Att_SENPUUKYAKU();
extern void Att_SENPUUKYAKU2();
extern void Att_SHINSHOURYUUKEN();
extern void Att_SHOURYUUKEN();
extern void Att_SLIDE_and_JUMP();
extern void Att_TENSHINSENKYUUTAI();

void (*const pl01_exatt_table[8])(PLW*) = {
    Att_CHOUCHUURENGEKI, Att_SHOURYUUKEN, Att_HADOUKEN, Att_HADOUKEN2,
    Att_CHOUCHUURENGEKI, Att_SENPUUKYAKU2, Att_SENPUUKYAKU, Att_NM_OKIAGARI,
};

void (*const pl02_exatt_table[8])(PLW*) = {
    Att_HADOUKEN, Att_SHOURYUUKEN, Att_SENPUUKYAKU, Att_HADOUKEN,
    Att_SHINSHOURYUUKEN, Att_HADOUKEN, Att_KUUCHUUNICHIRINSHOU, Att_HADOUKEN2,
};

void (*const pl03_exatt_table[7])(PLW*) = {
    Att_HADOUKEN, Att_TENSHINSENKYUUTAI, Att_SENPUUKYAKU, Att_HADOUKEN,
    Att_SLIDE_and_JUMP, Att_TENSHINSENKYUUTAI, Att_HADOUKEN,
};
