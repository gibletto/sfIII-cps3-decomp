/*
 * PLPAT07_TBL.C  tables read by PLPAT07.c: the characters' special attack routine tables (plNN_exatt_table)
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const pl07_exatt_table[])(PLW*);
extern void Att_CHOUCHUURENGEKI();
extern void Att_PL07_AT1();
extern void Att_PL07_AT2();
extern void Att_PL07_AT3();
extern void Att_PL07_SA2();
extern void Att_PL07_SA3();
extern void Att_SHOURYUUKEN();

void (*const pl07_exatt_table[9])(PLW*) = {
    Att_SHOURYUUKEN, Att_PL07_AT1, Att_CHOUCHUURENGEKI, Att_CHOUCHUURENGEKI,
    Att_CHOUCHUURENGEKI, Att_PL07_SA2, Att_PL07_AT2, Att_PL07_AT3,
    Att_PL07_SA3,
};
