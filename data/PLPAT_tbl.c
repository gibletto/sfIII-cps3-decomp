/*
 * PLPAT_TBL.C  tables read by PLPAT.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const plpat_lv_00[])(PLW* wk);
extern void (*const plxx_extra_attack_table[])();
extern void Attack_00000();
extern void Attack_01000();
extern void Attack_02000();
extern void Attack_03000();
extern void Attack_04000();
extern void Attack_05000();
extern void Attack_06000();
extern void Attack_07000();
extern void Attack_08000();
extern void Attack_09000();
extern void Attack_10000();
extern void pl00_extra_attack();
extern void pl01_extra_attack();
extern void pl02_extra_attack();
extern void pl03_extra_attack();
extern void pl04_extra_attack();
extern void pl05_extra_attack();
extern void pl06_extra_attack();
extern void pl07_extra_attack();
extern void pl08_extra_attack();
extern void pl09_extra_attack();
extern void pl10_extra_attack();
extern void pl11_extra_attack();
extern void pl12_extra_attack();

void (*const plpat_lv_00[16])(PLW* wk) = {
    Attack_00000, Attack_01000, Attack_02000, Attack_03000, Attack_04000, Attack_05000, Attack_06000, Attack_07000,
    Attack_08000, Attack_09000, Attack_10000, Attack_00000, Attack_00000, Attack_00000, Attack_00000, Attack_00000,
};

void (*const plxx_extra_attack_table[16])() = {
    pl00_extra_attack, pl01_extra_attack, pl02_extra_attack, pl03_extra_attack,
    pl04_extra_attack, pl05_extra_attack, pl06_extra_attack, pl07_extra_attack,
    pl08_extra_attack, pl09_extra_attack, pl10_extra_attack, pl11_extra_attack,
    pl12_extra_attack, pl00_extra_attack, pl00_extra_attack, pl00_extra_attack,
};
