/*
 * CK_PASS_TBL.C  tables read by Ck_Pass.c: computer player: passive reaction checks
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
    (void (*)())GILL_vs,
    (void (*)())KEN_vs,
    (void (*)())KEN_vs,
    (void (*)())KEN_vs,
    (void (*)())KEN_vs,
    (void (*)())KEN_vs,
    (void (*)())KEN_vs,
    (void (*)())KEN_vs,
    (void (*)())KEN_vs,
    (void (*)())KEN_vs,
    (void (*)())KEN_vs,
    (void (*)())KEN_vs,
    (void (*)())KEN_vs,
};

void (*const Passive_AS_tbl[13])() = {
    (void (*)())VS_GILL_AS,
    (void (*)())VS_ALEX_AS,
    (void (*)())VS_RYU_AS,
    (void (*)())VS_YUN_AS,
    (void (*)())VS_DUDLEY_AS,
    (void (*)())VS_NECRO_AS,
    (void (*)())VS_YUN_AS,
    (void (*)())VS_IBUKI_AS,
    (void (*)())VS_ELENA_AS,
    (void (*)())VS_ORO_AS,
    (void (*)())VS_YUN_AS,
    (void (*)())VS_KEN_AS,
    (void (*)())VS_SEAN_AS,
};

void (*const Passive_A_tbl[13])() = {
    (void (*)())VS_GILL_A,
    (void (*)())VS_ALEX_A,
    (void (*)())VS_RYU_A,
    (void (*)())VS_YUN_A,
    (void (*)())VS_DUDLEY_A,
    (void (*)())VS_NECRO_A,
    (void (*)())VS_YUN_A,
    (void (*)())VS_IBUKI_A,
    (void (*)())VS_ELENA_A,
    (void (*)())VS_ORO_A,
    (void (*)())VS_YUN_A,
    (void (*)())VS_KEN_A,
    (void (*)())VS_SEAN_A,
};

void (*const Passive_BS_tbl[13])() = {
    (void (*)())VS_GILL_BS,
    (void (*)())VS_ALEX_BS,
    (void (*)())VS_RYU_BS,
    (void (*)())VS_YUN_BS,
    (void (*)())VS_DUDLEY_BS,
    (void (*)())VS_NECRO_BS,
    (void (*)())VS_YUN_BS,
    (void (*)())VS_IBUKI_BS,
    (void (*)())VS_ELENA_BS,
    (void (*)())VS_ORO_BS,
    (void (*)())VS_YUN_BS,
    (void (*)())VS_KEN_BS,
    (void (*)())VS_SEAN_BS,
};

void (*const Passive_B_tbl[13])() = {
    (void (*)())VS_GILL_B,
    (void (*)())VS_ALEX_B,
    (void (*)())VS_RYU_B,
    (void (*)())VS_YUN_B,
    (void (*)())VS_DUDLEY_B,
    (void (*)())VS_NECRO_B,
    (void (*)())VS_YUN_B,
    (void (*)())VS_IBUKI_B,
    (void (*)())VS_ELENA_B,
    (void (*)())VS_ORO_B,
    (void (*)())VS_YUN_B,
    (void (*)())VS_KEN_B,
    (void (*)())VS_SEAN_B,
};

void (*const Passive_CS_tbl[13])() = {
    (void (*)())VS_GILL_CS,
    (void (*)())VS_ALEX_CS,
    (void (*)())VS_RYU_CS,
    (void (*)())VS_YUN_CS,
    (void (*)())VS_DUDLEY_CS,
    (void (*)())VS_NECRO_CS,
    (void (*)())VS_YUN_CS,
    (void (*)())VS_IBUKI_CS,
    (void (*)())VS_ELENA_CS,
    (void (*)())VS_ORO_CS,
    (void (*)())VS_YUN_CS,
    (void (*)())VS_KEN_CS,
    (void (*)())VS_SEAN_CS,
};

void (*const Passive_C_tbl[13])() = {
    (void (*)())VS_GILL_C,
    (void (*)())VS_ALEX_C,
    (void (*)())VS_RYU_C,
    (void (*)())VS_YUN_C,
    (void (*)())VS_DUDLEY_C,
    (void (*)())VS_NECRO_C,
    (void (*)())VS_YUN_C,
    (void (*)())VS_IBUKI_C,
    (void (*)())VS_ELENA_C,
    (void (*)())VS_ORO_C,
    (void (*)())VS_YUN_C,
    (void (*)())VS_KEN_C,
    (void (*)())VS_SEAN_C,
};

void (*const Passive_DS_tbl[13])() = {
    (void (*)())VS_GILL_DS,
    (void (*)())VS_ALEX_DS,
    (void (*)())VS_RYU_DS,
    (void (*)())VS_YUN_DS,
    (void (*)())VS_DUDLEY_DS,
    (void (*)())VS_NECRO_DS,
    (void (*)())VS_YUN_DS,
    (void (*)())VS_IBUKI_DS,
    (void (*)())VS_ELENA_DS,
    (void (*)())VS_ORO_DS,
    (void (*)())VS_YUN_DS,
    (void (*)())VS_KEN_DS,
    (void (*)())VS_SEAN_DS,
};

void (*const Passive_D_tbl[13])() = {
    (void (*)())VS_GILL_D,
    (void (*)())VS_ALEX_D,
    (void (*)())VS_RYU_D,
    (void (*)())VS_YUN_D,
    (void (*)())VS_DUDLEY_D,
    (void (*)())VS_NECRO_D,
    (void (*)())VS_YUN_D,
    (void (*)())VS_IBUKI_D,
    (void (*)())VS_ELENA_D,
    (void (*)())VS_ORO_D,
    (void (*)())VS_YUN_D,
    (void (*)())VS_KEN_D,
    (void (*)())VS_SEAN_D,
};
