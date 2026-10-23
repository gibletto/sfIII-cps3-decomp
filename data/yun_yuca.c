/*
 * YUN_YUCA.C  Yun's yuca scripts
 *
 * char_table[9] (yuca, the viewer's second ETC kind): the scripts of Yun's appearances, wins and
 * losses in the scripts' usual form (see yun_char.c and charscr.h).
 */

#include "types.h"
#include "structs.h"
#include "charscr.h"

#pragma section CHR

extern const u16 yun_yuca_000[], yun_yuca_008[], yun_yuca_016[], yun_yuca_017[], yun_yuca_018[], yun_yuca_019[],
                 yun_yuca_020[], yun_yuca_024[], yun_yuca_032[], yun_yuca_034[], yun_yuca_036[], yun_yuca_040[],
                 yun_yuca_048[], yun_yuca_052[], yun_yuca_060[], yun_yuca_061[], yun_yuca_062[], yun_yuca_063[];

/* yuca scripts (debug viewer: ETC): 64 entries */
const u32 yun_yuca[65] = {
    (u32)yun_yuca_000,  /* 0 APPEAR JUNBI 1 */
    (u32)yun_yuca_000,  /* 1 APPEAR JUNBI 2 */
    (u32)yun_yuca_000,  /* 2 APPEAR JUNBI 3 */
    (u32)yun_yuca_000,  /* 3 APPEAR JUNBI 4 */
    (u32)yun_yuca_000,  /* 4 APPEAR JUNBI 5 */
    (u32)yun_yuca_000,  /* 5 APPEAR JUNBI 6 */
    (u32)yun_yuca_000,  /* 6 APPEAR JUNBI 7 */
    (u32)yun_yuca_000,  /* 7 APPEAR JUNBI 8 */
    (u32)yun_yuca_008,  /* 8 APPEAR 1 */
    (u32)yun_yuca_008,  /* 9 APPEAR 2 */
    (u32)yun_yuca_008,  /* 10 APPEAR 3 */
    (u32)yun_yuca_008,  /* 11 APPEAR 4 */
    (u32)yun_yuca_008,  /* 12 APPEAR 5 */
    (u32)yun_yuca_008,  /* 13 APPEAR 6 */
    (u32)yun_yuca_008,  /* 14 APPEAR 7 */
    (u32)yun_yuca_008,  /* 15 APPEAR 8 */
    (u32)yun_yuca_016,  /* 16 SP APPEAR 1 */
    (u32)yun_yuca_017,  /* 17 SP APPEAR 2 */
    (u32)yun_yuca_018,  /* 18 SP APPEAR 3 */
    (u32)yun_yuca_019,  /* 19 SP APPEAR 4 */
    (u32)yun_yuca_020,  /* 20 SP APPEAR 5 */
    (u32)yun_yuca_020,  /* 21 SP APPEAR 6 */
    (u32)yun_yuca_020,  /* 22 SP APPEAR 7 */
    (u32)yun_yuca_020,  /* 23 SP APPEAR 8 */
    (u32)yun_yuca_024,  /* 24 ZANNEN 1 */
    (u32)yun_yuca_024,  /* 25 ZANNEN 2 */
    (u32)yun_yuca_024,  /* 26 ZANNEN 3 */
    (u32)yun_yuca_024,  /* 27 ZANNEN 4 */
    (u32)yun_yuca_024,  /* 28 ZANNEN 5 */
    (u32)yun_yuca_024,  /* 29 ZANNEN 6 */
    (u32)yun_yuca_024,  /* 30 ZANNEN 7 */
    (u32)yun_yuca_024,  /* 31 ZANNEN 8 */
    (u32)yun_yuca_032,  /* 32 WIN 1 */
    (u32)yun_yuca_032,  /* 33 WIN 2 */
    (u32)yun_yuca_034,  /* 34 WIN 3 */
    (u32)yun_yuca_034,  /* 35 WIN 4 */
    (u32)yun_yuca_036,  /* 36 WIN 5 */
    (u32)yun_yuca_036,  /* 37 WIN 6 */
    (u32)yun_yuca_036,  /* 38 WIN 7 */
    (u32)yun_yuca_036,  /* 39 WIN 8 */
    (u32)yun_yuca_040,  /* 40 SP WIN 1 */
    (u32)yun_yuca_040,  /* 41 SP WIN 2 */
    (u32)yun_yuca_040,  /* 42 SP WIN 3 */
    (u32)yun_yuca_040,  /* 43 SP WIN 4 */
    (u32)yun_yuca_040,  /* 44 SP WIN 5 */
    (u32)yun_yuca_040,  /* 45 SP WIN 6 */
    (u32)yun_yuca_040,  /* 46 SP WIN 7 */
    (u32)yun_yuca_040,  /* 47 SP WIN 8 */
    (u32)yun_yuca_048,  /* 48 JUDGMENT WAIT */
    (u32)yun_yuca_048,  /* 49 JUDGMENT WAIT */
    (u32)yun_yuca_048,  /* 50 JUDGMENT WAIT */
    (u32)yun_yuca_048,  /* 51 JUDGMENT WAIT */
    (u32)yun_yuca_052,  /* 52 JUDGMENT WIN */
    (u32)yun_yuca_052,  /* 53 JUDGMENT WIN */
    (u32)yun_yuca_052,  /* 54 JUDGMENT WIN */
    (u32)yun_yuca_052,  /* 55 JUDGMENT WIN */
    (u32)yun_yuca_024,  /* 56 JUDGMENT LOSE */
    (u32)yun_yuca_024,  /* 57 JUDGMENT LOSE */
    (u32)yun_yuca_024,  /* 58 JUDGMENT LOSE */
    (u32)yun_yuca_024,  /* 59 JUDGMENT LOSE */
    (u32)yun_yuca_060,  /* 60 no name */
    (u32)yun_yuca_061,  /* 61 no name */
    (u32)yun_yuca_062,  /* 62 no name */
    (u32)yun_yuca_063,  /* 63 no name */
    0
};

/* script: 0 APPEAR JUNBI 1, 1 APPEAR JUNBI 2, 2 APPEAR JUNBI 3, 3 APPEAR JUNBI 4 ... */
const u16 yun_yuca_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yun_yuca_000[20] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x0F70),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F71),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F72),
    L2(4, 9, 0, 0, 0, 0, 0, 0x0F73),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 APPEAR 1, 9 APPEAR 2, 10 APPEAR 3, 11 APPEAR 4 ... */
const u16 yun_yuca_008_head[4] = { HEAD(4, 0, 0, 0, 0, 0, 0) };
const u16 yun_yuca_008[276] = {
    L4(40, 0, 0, 0, 0, 0, 0, 0x0F70, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x0F71, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x0F72, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x0F73, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x0F70, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x0F71, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x0F72, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x0F70, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x0F74, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x0F75, 0, 1, 0, 0, 0, 0),
    L4(5, 0, 0, 0, 0, 0, 0, 0x0F76, 0, 1, 0, 0, 0, 0),
    L4(8, 0, 0, 0, 0, 0, 0, 0x0F77, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x0F78, 0, 1, 0, 0, 0, 0),
    L4(5, 0, 0, 0, 0, 0, 0, 0x0F79, 0, 1, 0, 0, 0, 0),
    L4(13, 0, 0, 0, 0, 0, 0, 0x0F63, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, 256, 0), 0, 0, 0, 0,
    L4(6, 0, 0, 0, 0, 0, 0, 0x0F64, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, 256, 0), 0, 0, 0, 0,
    L4(12, 0, 0, 0, 0, 0, 0, 0x0F65, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, -256, 0), 0, 0, 0, 0,
    L4(7, 0, 0, 0, 0, 0, 0, 0x0F64, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, -256, 0), 0, 0, 0, 0,
    L4(6, 0, 0, 0, 0, 0, 0, 0x0F63, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x0F62, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x0F61, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, -512, 0), 0, 0, 0, 0,
    L4(4, 0, 0, 0, 0, 0, 0, 0x0F60, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, -256, 0), 0, 0, 0, 0,
    L4(4, 0, 0, 0, 0, 0, 0, 0x0F5F, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x0C41, 0, 1, 0, 0, 0, 0),
    L4(7, 0, 0, 0, 0, 0, 0, 0x0C40, 0, 1, 0, 0, 0, 0),
    L4(5, 0, 0, 0, 0, 0, 0, 0x0C3F, 0, 1, 0, 0, 0, 0),
    L4(5, 0, 0, 0, 0, 0, 0, 0x0C01, 0, 1, 0, 0, 0, 0),
    L4(8, 255, 0, 0, 0, 0, 0, 0x0C01, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 16 SP APPEAR 1 */
const u16 yun_yuca_016_head[4] = { HEAD(2, 6, 0, 0, 0, 0, 0) };
const u16 yun_yuca_016[28] = {
    L2(4, 0, 312, 0, 0, 0, 0, 0x0F8C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F8D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F8E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F8D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F8C),
    CMD(CM_END, 0, 0, 2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 17 SP APPEAR 2 */
const u16 yun_yuca_017_head[4] = { HEAD(2, 6, 0, 0, 0, 0, 0) };
const u16 yun_yuca_017[12] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x0C6B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x0C6C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 18 SP APPEAR 3 */
const u16 yun_yuca_018_head[4] = { HEAD(2, 6, 0, 0, 0, 0, 0) };
const u16 yun_yuca_018[24] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x0C6D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x0C6E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x0C6F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x0C41),
    L2(8, 1, 0, 0, 0, 0, 0, 0x0C41),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 19 SP APPEAR 4 */
const u16 yun_yuca_019_head[4] = { HEAD(2, 6, 0, 0, 0, 0, 0) };
const u16 yun_yuca_019[128] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x0C01),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F5F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x0F60),
    L2(5, 0, 0, 0, 0, 0, 0, 0x0F61),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0F62),
    L2(6, 0, 0, 0, 0, 0, 0, 0x0F63),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0F78),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0F76),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0F77),
    L2(2, 0, 0, 0, 0, 0, 0, 0x0F78),
    L2(6, 0, 0, 0, 0, 0, 0, 0x0F79),
    L2(10, 0, 0, 0, 0, 0, 0, 0x0F63),
    CMD(CM_PA_X, 0, 256, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F64),
    CMD(CM_PA_X, 0, 512, 0),
    L2(16, 0, 0, 0, 0, 0, 0, 0x0F65),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F64),
    L2(2, 0, 0, 0, 0, 0, 0, 0x0F63),
    L2(2, 0, 0, 0, 0, 0, 0, 0x0F62),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F61),
    CMD(CM_PA_X, 0, -256, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F60),
    CMD(CM_PA_X, 0, -256, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F5F),
    CMD(CM_PA_X, 0, -512, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0C41),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0C40),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0C3F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0C01),
    L2(8, 255, 0, 0, 0, 0, 0, 0x0C01),
    CMD(CM_DUMMY, 1, 0, 0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 20 SP APPEAR 5, 21 SP APPEAR 6, 22 SP APPEAR 7, 23 SP APPEAR 8 */
const u16 yun_yuca_020_head[4] = { HEAD(2, 6, 0, 0, 0, 0, 0) };
const u16 yun_yuca_020[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x0F9D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 24 ZANNEN 1, 25 ZANNEN 2, 26 ZANNEN 3, 27 ZANNEN 4 ... */
const u16 yun_yuca_024_head[4] = { HEAD(2, 38, 0, 0, 0, 0, 0) };
const u16 yun_yuca_024[24] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F56),
    CMD(CM_PA_X, 0, 256, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F57),
    L2(4, 255, 0, 0, 0, 0, 0, 0x0F58),
    CMD(CM_END, 0, 0, 3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 32 WIN 1, 33 WIN 2 */
const u16 yun_yuca_032_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yun_yuca_032[44] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F66),
    CMD(CM_PA_X, 0, 512, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F67),
    CMD(CM_PA_X, 0, 512, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F68),
    CMD(CM_PA_X, 0, 512, 0),
    L2(4, 0, 410, 0, 0, 0, 0, 0x0F69),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F6A),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0F6A),
    CMD(CM_END, 0, 0, 9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 34 WIN 3, 35 WIN 4 */
const u16 yun_yuca_034_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yun_yuca_034[44] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F66),
    CMD(CM_PA_X, 0, 512, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F67),
    CMD(CM_PA_X, 0, 512, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F68),
    CMD(CM_PA_X, 0, 512, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F69),
    L2(4, 0, 411, 0, 0, 0, 0, 0x0F6A),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0F6A),
    CMD(CM_END, 0, 0, 9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 36 WIN 5, 37 WIN 6, 38 WIN 7, 39 WIN 8 */
const u16 yun_yuca_036_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yun_yuca_036[68] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F5F),
    CMD(CM_PA_X, 0, 256, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F60),
    CMD(CM_PA_X, 0, 256, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F61),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F62),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F63),
    CMD(CM_PA_X, 0, 256, 0),
    L2(4, 0, 409, 0, 0, 0, 0, 0x0F64),
    CMD(CM_PA_X, 0, -256, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F65),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F64),
    CMD(CM_PA_X, 0, -256, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F63),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0F63),
    CMD(CM_END, 0, 0, 15),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 40 SP WIN 1, 41 SP WIN 2, 42 SP WIN 3, 43 SP WIN 4 ... */
const u16 yun_yuca_040_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yun_yuca_040[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F66),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 48 JUDGMENT WAIT, 49 JUDGMENT WAIT, 50 JUDGMENT WAIT, 51 JUDGMENT WAIT */
const u16 yun_yuca_048_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yun_yuca_048[52] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x0C01),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0C02),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0C03),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0C04),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0C05),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0C06),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0C07),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0C08),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0C09),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0C0A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0C0B),
    L2(8, 255, 0, 0, 0, 0, 0, 0x0C0C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 52 JUDGMENT WIN, 53 JUDGMENT WIN, 54 JUDGMENT WIN, 55 JUDGMENT WIN */
const u16 yun_yuca_052_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yun_yuca_052[40] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F59),
    CMD(CM_PA_X, 0, 512, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F5A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F5B),
    CMD(CM_PA_X, 0, -512, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F5C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0F5D),
    L2(250, 0, 0, 0, 0, 0, 0, 0x0F5E),
    CMD(CM_END, 0, 0, 8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 60 no name */
const u16 yun_yuca_060_head[4] = { HEAD(4, 0, 0, 0, 0, 0, 0) };
const u16 yun_yuca_060[100] = {
    L4(16, 0, 0, 0, 0, 0, 0, 0x0C01, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x0C02, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x0C03, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x0C04, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x0C05, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x0C06, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x0C07, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x0C08, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x0C09, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x0C0A, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x0C0B, 0, 1, 0, 0, 0, 0),
    L4(16, 255, 0, 0, 0, 0, 0, 0x0C0C, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 61 no name */
const u16 yun_yuca_061_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yun_yuca_061[64] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x0C7F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x0C60),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0C61),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0C62),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0C63),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0C64),
    L2(2, 0, 0, 0, 0, 0, 0, 0x0C65),
    L2(2, 0, 0, 0, 0, 0, 0, 0x0C66),
    L2(2, 0, 0, 0, 0, 0, 0, 0x0C67),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0C68),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0C69),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0C6A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0C6B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0C6C),
    CMD(CM_END, 0, 0, 13),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 62 no name */
const u16 yun_yuca_062_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yun_yuca_062[28] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x0C6E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x0C6F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0C41),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0C40),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0C3F),
    L2(4, 255, 0, 0, 0, 0, 0, 0x0C3F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 63 no name */
const u16 yun_yuca_063_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yun_yuca_063[28] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x0D00),
    L2(1, 0, 0, 0, 0, 0, 0, 0x0D01),
    L2(2, 0, 0, 0, 0, 0, 0, 0x0D02),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0D03),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0D04),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0D04),
    CMD(CM_ROA, 0, 0, 0),
};
