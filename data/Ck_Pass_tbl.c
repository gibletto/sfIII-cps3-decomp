/*
 * CK_PASS_TBL.C  the computer player's reaction dispatch tables
 *
 * Each table has one routine per character number. Passive_jmp_tbl picks the reaction selector
 * by the CPU's own character (GILL_vs for Gill, KEN_vs for every other character);
 * Passive_A_tbl .. Passive_D_tbl and their S companions Passive_AS_tbl .. Passive_DS_tbl pick
 * the VS_<name>_ check by the opponent's character for screen areas A to D. Read by CK_PASS.C,
 * the passive reaction checks.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Passive_jmp_tbl[])();
extern void (*const Passive_AS_tbl[])();
extern void (*const Passive_A_tbl[])();
extern void (*const Passive_BS_tbl[])();
extern void (*const Passive_B_tbl[])();
extern void (*const Passive_CS_tbl[])();
extern void (*const Passive_C_tbl[])();
extern void (*const Passive_DS_tbl[])();
extern void (*const Passive_D_tbl[])();
extern void GILL_vs();
extern void KEN_vs();
extern void VS_ALEX_A();
extern void VS_ALEX_AS();
extern void VS_ALEX_B();
extern void VS_ALEX_BS();
extern void VS_ALEX_C();
extern void VS_ALEX_CS();
extern void VS_ALEX_D();
extern void VS_ALEX_DS();
extern void VS_DUDLEY_A();
extern void VS_DUDLEY_AS();
extern void VS_DUDLEY_B();
extern void VS_DUDLEY_BS();
extern void VS_DUDLEY_C();
extern void VS_DUDLEY_CS();
extern void VS_DUDLEY_D();
extern void VS_DUDLEY_DS();
extern void VS_ELENA_A();
extern void VS_ELENA_AS();
extern void VS_ELENA_B();
extern void VS_ELENA_BS();
extern void VS_ELENA_C();
extern void VS_ELENA_CS();
extern void VS_ELENA_D();
extern void VS_ELENA_DS();
extern void VS_GILL_A();
extern void VS_GILL_AS();
extern void VS_GILL_B();
extern void VS_GILL_BS();
extern void VS_GILL_C();
extern void VS_GILL_CS();
extern void VS_GILL_D();
extern void VS_GILL_DS();
extern void VS_IBUKI_A();
extern void VS_IBUKI_AS();
extern void VS_IBUKI_B();
extern void VS_IBUKI_BS();
extern void VS_IBUKI_C();
extern void VS_IBUKI_CS();
extern void VS_IBUKI_D();
extern void VS_IBUKI_DS();
extern void VS_KEN_A();
extern void VS_KEN_AS();
extern void VS_KEN_B();
extern void VS_KEN_BS();
extern void VS_KEN_C();
extern void VS_KEN_CS();
extern void VS_KEN_D();
extern void VS_KEN_DS();
extern void VS_NECRO_A();
extern void VS_NECRO_AS();
extern void VS_NECRO_B();
extern void VS_NECRO_BS();
extern void VS_NECRO_C();
extern void VS_NECRO_CS();
extern void VS_NECRO_D();
extern void VS_NECRO_DS();
extern void VS_ORO_A();
extern void VS_ORO_AS();
extern void VS_ORO_B();
extern void VS_ORO_BS();
extern void VS_ORO_C();
extern void VS_ORO_CS();
extern void VS_ORO_D();
extern void VS_ORO_DS();
extern void VS_RYU_A();
extern void VS_RYU_AS();
extern void VS_RYU_B();
extern void VS_RYU_BS();
extern void VS_RYU_C();
extern void VS_RYU_CS();
extern void VS_RYU_D();
extern void VS_RYU_DS();
extern void VS_SEAN_A();
extern void VS_SEAN_AS();
extern void VS_SEAN_B();
extern void VS_SEAN_BS();
extern void VS_SEAN_C();
extern void VS_SEAN_CS();
extern void VS_SEAN_D();
extern void VS_SEAN_DS();
extern void VS_YUN_A();
extern void VS_YUN_AS();
extern void VS_YUN_B();
extern void VS_YUN_BS();
extern void VS_YUN_C();
extern void VS_YUN_CS();
extern void VS_YUN_D();
extern void VS_YUN_DS();

void (*const Passive_jmp_tbl[13])() = {
    GILL_vs,
    KEN_vs,
    KEN_vs,
    KEN_vs,
    KEN_vs,
    KEN_vs,
    KEN_vs,
    KEN_vs,
    KEN_vs,
    KEN_vs,
    KEN_vs,
    KEN_vs,
    KEN_vs,
};

void (*const Passive_AS_tbl[13])() = {
    VS_GILL_AS,
    VS_ALEX_AS,
    VS_RYU_AS,
    VS_YUN_AS,
    VS_DUDLEY_AS,
    VS_NECRO_AS,
    VS_YUN_AS,
    VS_IBUKI_AS,
    VS_ELENA_AS,
    VS_ORO_AS,
    VS_YUN_AS,
    VS_KEN_AS,
    VS_SEAN_AS,
};

void (*const Passive_A_tbl[13])() = {
    VS_GILL_A,
    VS_ALEX_A,
    VS_RYU_A,
    VS_YUN_A,
    VS_DUDLEY_A,
    VS_NECRO_A,
    VS_YUN_A,
    VS_IBUKI_A,
    VS_ELENA_A,
    VS_ORO_A,
    VS_YUN_A,
    VS_KEN_A,
    VS_SEAN_A,
};

void (*const Passive_BS_tbl[13])() = {
    VS_GILL_BS,
    VS_ALEX_BS,
    VS_RYU_BS,
    VS_YUN_BS,
    VS_DUDLEY_BS,
    VS_NECRO_BS,
    VS_YUN_BS,
    VS_IBUKI_BS,
    VS_ELENA_BS,
    VS_ORO_BS,
    VS_YUN_BS,
    VS_KEN_BS,
    VS_SEAN_BS,
};

void (*const Passive_B_tbl[13])() = {
    VS_GILL_B,
    VS_ALEX_B,
    VS_RYU_B,
    VS_YUN_B,
    VS_DUDLEY_B,
    VS_NECRO_B,
    VS_YUN_B,
    VS_IBUKI_B,
    VS_ELENA_B,
    VS_ORO_B,
    VS_YUN_B,
    VS_KEN_B,
    VS_SEAN_B,
};

void (*const Passive_CS_tbl[13])() = {
    VS_GILL_CS,
    VS_ALEX_CS,
    VS_RYU_CS,
    VS_YUN_CS,
    VS_DUDLEY_CS,
    VS_NECRO_CS,
    VS_YUN_CS,
    VS_IBUKI_CS,
    VS_ELENA_CS,
    VS_ORO_CS,
    VS_YUN_CS,
    VS_KEN_CS,
    VS_SEAN_CS,
};

void (*const Passive_C_tbl[13])() = {
    VS_GILL_C,
    VS_ALEX_C,
    VS_RYU_C,
    VS_YUN_C,
    VS_DUDLEY_C,
    VS_NECRO_C,
    VS_YUN_C,
    VS_IBUKI_C,
    VS_ELENA_C,
    VS_ORO_C,
    VS_YUN_C,
    VS_KEN_C,
    VS_SEAN_C,
};

void (*const Passive_DS_tbl[13])() = {
    VS_GILL_DS,
    VS_ALEX_DS,
    VS_RYU_DS,
    VS_YUN_DS,
    VS_DUDLEY_DS,
    VS_NECRO_DS,
    VS_YUN_DS,
    VS_IBUKI_DS,
    VS_ELENA_DS,
    VS_ORO_DS,
    VS_YUN_DS,
    VS_KEN_DS,
    VS_SEAN_DS,
};

void (*const Passive_D_tbl[13])() = {
    VS_GILL_D,
    VS_ALEX_D,
    VS_RYU_D,
    VS_YUN_D,
    VS_DUDLEY_D,
    VS_NECRO_D,
    VS_YUN_D,
    VS_IBUKI_D,
    VS_ELENA_D,
    VS_ORO_D,
    VS_YUN_D,
    VS_KEN_D,
    VS_SEAN_D,
};
