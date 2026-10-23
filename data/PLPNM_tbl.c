/*
 * PLPNM_TBL.C  tables read by PLPNM.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const plpnm_lv_00[])(PLW* wk);
extern void (*const normal_05[])(PLW* wk);
extern void (*const normal_06[])(PLW* wk);
extern const u16 jpdat_tbl[][2];
extern void Normal_00000();
extern void Normal_01000();
extern void Normal_02000();
extern void Normal_03000();
extern void Normal_04000();
extern void Normal_05000();
extern void Normal_06000();
extern void Normal_07000();
extern void Normal_08000();
extern void Normal_09000();
extern void Normal_10000();
extern void Normal_11000();
extern void Normal_12000();
extern void Normal_13000();
extern void Normal_16000();
extern void Normal_17000();
extern void Normal_18000();
extern void Normal_27000();
extern void Normal_31000();
extern void Normal_35000();
extern void Normal_36000();
extern void Normal_37000();
extern void Normal_38000();
extern void Normal_39000();
extern void Normal_40000();
extern void Normal_41000();
extern void Normal_air_paring();
extern void nm_05_0000();
extern void nm_05_0100();
extern void nm_06_0000();
extern void nm_06_0100();
extern void nm_06_0200();

void (*const plpnm_lv_00[42])(PLW* wk) = {
    Normal_00000, Normal_01000, Normal_02000, Normal_03000,
    Normal_04000, Normal_05000, Normal_06000, Normal_07000,
    Normal_08000, Normal_09000, Normal_10000, Normal_11000,
    Normal_12000, Normal_13000, Normal_13000, Normal_13000,
    Normal_16000, Normal_17000, Normal_18000, Normal_18000,
    Normal_18000, Normal_18000, Normal_18000, Normal_18000,
    Normal_18000, Normal_18000, Normal_18000, Normal_27000,
    Normal_27000, Normal_27000, Normal_27000, Normal_31000,
    Normal_31000, Normal_31000, Normal_35000, Normal_air_paring,
    Normal_36000, Normal_37000, Normal_38000, Normal_39000,
    Normal_40000, Normal_41000,
};

void (*const normal_05[16])(PLW* wk) = {
    nm_05_0000, nm_05_0000, nm_05_0100, nm_05_0000, nm_05_0000, nm_05_0000, nm_05_0000, nm_05_0000,
    nm_05_0100, nm_05_0000, nm_05_0000, nm_05_0100, nm_05_0100, nm_05_0000, nm_05_0000, nm_05_0000,
};

void (*const normal_06[16])(PLW* wk) = {
    nm_06_0100, nm_06_0100, nm_06_0200, nm_06_0000, nm_06_0100, nm_06_0100, nm_06_0100, nm_06_0100,
    nm_06_0000, nm_06_0100, nm_06_0000, nm_06_0200, nm_06_0200, nm_06_0000, nm_06_0000, nm_06_0000,
};

const u16 jpdat_tbl[9][2] = {
    { 0x11, 6 }, { 0x12, 7 }, { 0x13, 8 }, { 0xE, 9 },
    { 0xF, 0xA }, { 0x10, 0xB }, { 0x14, 0xC }, { 0x15, 0xD },
    { 0x16, 0xE },
};
