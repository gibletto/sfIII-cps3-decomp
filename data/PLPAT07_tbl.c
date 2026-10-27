/*
 * PLPAT07_TBL.C  Ibuki's special attack table
 *
 * pl07_exatt_table is the list of Ibuki's nine special attack routines, indexed by attack
 * routine number minus 16. Read by PLPAT07.C, which dispatches through it from
 * pl07_extra_attack.
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
