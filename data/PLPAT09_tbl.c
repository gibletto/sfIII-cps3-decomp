/*
 * PLPAT09_TBL.C  tables read by PLPAT09.c, plpat10.c and PLPAT11.c: the characters' special attack routine tables
 * (plNN_exatt_table)
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const pl09_exatt_table[])(PLW*);
extern void (*const pl10_exatt_table[])(PLW*);
extern void (*const pl11_exatt_table[])(PLW*);
extern void Att_CHOUCHUURENGEKI();
extern void Att_HADOUKEN();
extern void Att_JINNCHUUWATARI();
extern void Att_KUUCHUUJINNCHUUWATARI();
extern void Att_KUUCHUUNICHIRINSHOU();
extern void Att_SENPUUKYAKU();
extern void Att_SHOURYUUKEN();
extern void Att_SHOURYUUREPPA();
extern void Att_SLIDE_and_JUMP();
extern void Att_TENSHINSENKYUUTAI();

void (*const pl09_exatt_table[9])(PLW*) = {
    Att_HADOUKEN, Att_SHOURYUUKEN, Att_KUUCHUUNICHIRINSHOU, Att_HADOUKEN,
    Att_HADOUKEN, Att_HADOUKEN, Att_HADOUKEN, Att_KUUCHUUJINNCHUUWATARI,
    Att_JINNCHUUWATARI,
};

void (*const pl10_exatt_table[7])(PLW*) = {
    Att_HADOUKEN, Att_TENSHINSENKYUUTAI, Att_SENPUUKYAKU, Att_HADOUKEN,
    Att_SLIDE_and_JUMP, Att_TENSHINSENKYUUTAI, Att_HADOUKEN,
};

void (*const pl11_exatt_table[8])(PLW*) = {
    Att_HADOUKEN, Att_SHOURYUUKEN, Att_SENPUUKYAKU, Att_SHOURYUUREPPA,
    Att_SHOURYUUREPPA, Att_SLIDE_and_JUMP, Att_KUUCHUUNICHIRINSHOU, Att_CHOUCHUURENGEKI,
};
