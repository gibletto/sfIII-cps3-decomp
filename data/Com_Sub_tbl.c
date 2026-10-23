/*
 * COM_SUB_TBL.C  tables read by Com_Sub.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u16 cancel_shot_tbl[][8];
extern const u8 YAGYOU_Data[];
extern const u16 Rolling_Lv_Data[][5];
extern const u16 Meoshi_Lever_Data[];
extern const s8 PL_Status[];
extern const Term_Tbl_t Exit_Term_Tbl[];
extern const Term_Tbl_t ETC_Term_Tbl[];
extern void ETC_Term_0000();
extern void ETC_Term_0001();
extern void ETC_Term_0002();
extern void ETC_Term_0003();
extern void ETC_Term_0004();
extern void Exit_Term_0000();
extern void Exit_Term_0001();
extern void Exit_Term_0002();
extern void Exit_Term_0003();
extern void Exit_Term_0004();
extern void Exit_Term_0005();
extern void Exit_Term_0006();
extern void Exit_Term_0007();

const u16 cancel_shot_tbl[7][8] = {
    { 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0xFFFF, 0x10 },
    { 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0xFFFF, 0x10 },
    { 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0xFFFF, 0x20 },
    { 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0xFFFF, 0x40 },
    { 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0xFFFF, 0x80 },
    { 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0xFFFF, 0x100 },
    { 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0xFFFF, 0x200 },
};

const u8 YAGYOU_Data[16] = {
    0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3,
};

const u16 Rolling_Lv_Data[2][5] = {
    { 4, 1, 8, 2, 0xFFFF }, { 0x90, 0x120, 0x240, 0x3F0, 0xFFFF },
};

const u16 Meoshi_Lever_Data[16] = {
    0, 1, 2, 0, 0x8000, 0, 0, 0,
    0x8001, 0, 0, 0, 0, 0, 0, 0,
};

const s8 PL_Status[12] = {
    1, 0, 0, 0, 1, 1, 0, 0, 0, 0, -117, 1,
};

const Term_Tbl_t Exit_Term_Tbl[8] = {
    (const Term_Tbl_t)Exit_Term_0000, (const Term_Tbl_t)Exit_Term_0001,
    (const Term_Tbl_t)Exit_Term_0002, (const Term_Tbl_t)Exit_Term_0003,
    (const Term_Tbl_t)Exit_Term_0004, (const Term_Tbl_t)Exit_Term_0005,
    (const Term_Tbl_t)Exit_Term_0006, (const Term_Tbl_t)Exit_Term_0007,
};

const Term_Tbl_t ETC_Term_Tbl[5] = {
    (const Term_Tbl_t)ETC_Term_0000, (const Term_Tbl_t)ETC_Term_0001,
    (const Term_Tbl_t)ETC_Term_0002, (const Term_Tbl_t)ETC_Term_0003,
    (const Term_Tbl_t)ETC_Term_0004,
};
