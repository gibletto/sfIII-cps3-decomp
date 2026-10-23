/*
 * PLPAT00_TBL.C  tables read by PLPAT00.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 mnd_em_tall[][2];
extern const s16 glap_table[];
extern void (*const pl00_exatt_table[])(PLW*);
extern void Att_ABISEGERI();
extern void Att_HADOUKEN();
extern void Att_MOONSALT_KNEE_DROP();
extern void Att_RESURRECTION();
extern void Att_SENPUUKYAKU();

const s16 mnd_em_tall[16][2] = {
    { 28, 56 }, { 24, 44 }, { 24, 40 }, { 20, 32 }, { 24, 48 }, { 24, 40 }, { 28, 60 }, { 16, 44 },
    { 32, 32 }, { 28, 24 }, { 20, 32 }, { 24, 40 }, { 24, 40 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
};

const s16 glap_table[6] = {
    1, 2, 3, 4, 0, 33,
};

void (*const pl00_exatt_table[6])(PLW*) = {
    Att_HADOUKEN, Att_MOONSALT_KNEE_DROP, Att_ABISEGERI, Att_SENPUUKYAKU,
    Att_HADOUKEN, Att_RESURRECTION,
};
