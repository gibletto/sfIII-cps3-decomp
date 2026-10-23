/*
 * KEN_YUCA.C  Ken's yuca scripts
 *
 * char_table[9] (yuca, the viewer's second ETC kind): the scripts of Ken's appearances, wins and
 * losses in the scripts' usual form (see ken_char.c and charscr.h).
 */

#include "types.h"
#include "structs.h"
#include "charscr.h"

#pragma section CHR

extern const u16 ken_yuca_000[], ken_yuca_008[], ken_yuca_016[], ken_yuca_024[], ken_yuca_032[], ken_yuca_036[],
                 ken_yuca_040[], ken_yuca_048[], ken_yuca_060[], ken_yuca_061[], ken_yuca_062[], ken_yuca_063[];

/* yuca scripts (debug viewer: ETC): 64 entries */
const u32 ken_yuca[65] = {
    (u32)ken_yuca_000,  /* 0 APPEAR JUNBI 1 */
    (u32)ken_yuca_000,  /* 1 APPEAR JUNBI 2 */
    (u32)ken_yuca_000,  /* 2 APPEAR JUNBI 3 */
    (u32)ken_yuca_000,  /* 3 APPEAR JUNBI 4 */
    (u32)ken_yuca_000,  /* 4 APPEAR JUNBI 5 */
    (u32)ken_yuca_000,  /* 5 APPEAR JUNBI 6 */
    (u32)ken_yuca_000,  /* 6 APPEAR JUNBI 7 */
    (u32)ken_yuca_000,  /* 7 APPEAR JUNBI 8 */
    (u32)ken_yuca_008,  /* 8 APPEAR 1 */
    (u32)ken_yuca_008,  /* 9 APPEAR 2 */
    (u32)ken_yuca_008,  /* 10 APPEAR 3 */
    (u32)ken_yuca_008,  /* 11 APPEAR 4 */
    (u32)ken_yuca_008,  /* 12 APPEAR 5 */
    (u32)ken_yuca_008,  /* 13 APPEAR 6 */
    (u32)ken_yuca_008,  /* 14 APPEAR 7 */
    (u32)ken_yuca_008,  /* 15 APPEAR 8 */
    (u32)ken_yuca_016,  /* 16 SP APPEAR 1 */
    (u32)ken_yuca_016,  /* 17 SP APPEAR 2 */
    (u32)ken_yuca_016,  /* 18 SP APPEAR 3 */
    (u32)ken_yuca_016,  /* 19 SP APPEAR 4 */
    (u32)ken_yuca_016,  /* 20 SP APPEAR 5 */
    (u32)ken_yuca_016,  /* 21 SP APPEAR 6 */
    (u32)ken_yuca_016,  /* 22 SP APPEAR 7 */
    (u32)ken_yuca_016,  /* 23 SP APPEAR 8 */
    (u32)ken_yuca_024,  /* 24 ZANNEN 1 */
    (u32)ken_yuca_024,  /* 25 ZANNEN 2 */
    (u32)ken_yuca_024,  /* 26 ZANNEN 3 */
    (u32)ken_yuca_024,  /* 27 ZANNEN 4 */
    (u32)ken_yuca_024,  /* 28 ZANNEN 5 */
    (u32)ken_yuca_024,  /* 29 ZANNEN 6 */
    (u32)ken_yuca_024,  /* 30 ZANNEN 7 */
    (u32)ken_yuca_024,  /* 31 ZANNEN 8 */
    (u32)ken_yuca_032,  /* 32 WIN 1 */
    (u32)ken_yuca_032,  /* 33 WIN 2 */
    (u32)ken_yuca_032,  /* 34 WIN 3 */
    (u32)ken_yuca_032,  /* 35 WIN 4 */
    (u32)ken_yuca_036,  /* 36 WIN 5 */
    (u32)ken_yuca_036,  /* 37 WIN 6 */
    (u32)ken_yuca_036,  /* 38 WIN 7 */
    (u32)ken_yuca_036,  /* 39 WIN 8 */
    (u32)ken_yuca_040,  /* 40 SP WIN 1 */
    (u32)ken_yuca_040,  /* 41 SP WIN 2 */
    (u32)ken_yuca_040,  /* 42 SP WIN 3 */
    (u32)ken_yuca_040,  /* 43 SP WIN 4 */
    (u32)ken_yuca_040,  /* 44 SP WIN 5 */
    (u32)ken_yuca_040,  /* 45 SP WIN 6 */
    (u32)ken_yuca_040,  /* 46 SP WIN 7 */
    (u32)ken_yuca_040,  /* 47 SP WIN 8 */
    (u32)ken_yuca_048,  /* 48 JUDGMENT WAIT */
    (u32)ken_yuca_048,  /* 49 JUDGMENT WAIT */
    (u32)ken_yuca_048,  /* 50 JUDGMENT WAIT */
    (u32)ken_yuca_048,  /* 51 JUDGMENT WAIT */
    (u32)ken_yuca_032,  /* 52 JUDGMENT WIN */
    (u32)ken_yuca_032,  /* 53 JUDGMENT WIN */
    (u32)ken_yuca_032,  /* 54 JUDGMENT WIN */
    (u32)ken_yuca_032,  /* 55 JUDGMENT WIN */
    (u32)ken_yuca_024,  /* 56 JUDGMENT LOSE */
    (u32)ken_yuca_024,  /* 57 JUDGMENT LOSE */
    (u32)ken_yuca_024,  /* 58 JUDGMENT LOSE */
    (u32)ken_yuca_024,  /* 59 JUDGMENT LOSE */
    (u32)ken_yuca_060,  /* 60 no name */
    (u32)ken_yuca_061,  /* 61 no name */
    (u32)ken_yuca_062,  /* 62 no name */
    (u32)ken_yuca_063,  /* 63 no name */
    0
};

/* script: 0 APPEAR JUNBI 1, 1 APPEAR JUNBI 2, 2 APPEAR JUNBI 3, 3 APPEAR JUNBI 4 ... */
const u16 ken_yuca_000_head[4] = { HEAD(4, 0, 0, 0, 0, 0, 0) };
const u16 ken_yuca_000[28] = {
    CMD(CM_PA_X, 0, -1024, 0), 0, 0, 0, 0,
    L4(32, 9, 0, 0, 0, 0, 0, 0x2ED0, 0, 1, 0, 0, 0, 0),
    CMD(CM_IXBW, 0, 0, 1), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 8 APPEAR 1, 9 APPEAR 2, 10 APPEAR 3, 11 APPEAR 4 ... */
const u16 ken_yuca_008_head[4] = { HEAD(4, 0, 0, 0, 0, 0, 0) };
const u16 ken_yuca_008[148] = {
    L4(32, 0, 0, 0, 0, 0, 0, 0x2ED0, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 506, 0, 0, 0, 0, 0x2ED1, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2ED2, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x2ED3, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x2ED9, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x2EDA, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x2EDB, 0, 1, 0, 0, 0, 0),
    L4(24, 0, 0, 0, 0, 0, 0, 0x2EDC, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2ED4, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2ED5, 0, 1, 0, 0, 0, 0),
    L4(14, 0, 0, 0, 0, 0, 0, 0x2ED6, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2ED7, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, 256, 0), 0, 0, 0, 0,
    L4(4, 0, 0, 0, 0, 0, 0, 0x2ED8, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, 256, 0), 0, 0, 0, 0,
    L4(4, 0, 0, 0, 0, 0, 0, 0x2C93, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, 256, 0), 0, 0, 0, 0,
    L4(250, 255, 0, 0, 0, 0, 0, 0x2C93, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 16 SP APPEAR 1, 17 SP APPEAR 2, 18 SP APPEAR 3, 19 SP APPEAR 4 ... */
const u16 ken_yuca_016_head[4] = { HEAD(4, 24, 0, 0, 0, 0, 0) };
const u16 ken_yuca_016[12] = {
    L4(4, 255, 0, 0, 0, 0, 0, 0x2C01, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 24 ZANNEN 1, 25 ZANNEN 2, 26 ZANNEN 3, 27 ZANNEN 4 ... */
const u16 ken_yuca_024_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ken_yuca_024[20] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x2D11),
    L2(6, 0, 0, 0, 0, 0, 0, 0x2D12),
    L2(250, 255, 0, 0, 0, 0, 0, 0x2D12),
    CMD(CM_END, 0, 0, 3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 32 WIN 1, 33 WIN 2, 34 WIN 3, 35 WIN 4 ... */
const u16 ken_yuca_032_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ken_yuca_032[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x2EF0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x2EF1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2EF2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2EF3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2EF4),
    L2(12, 0, 0, 0, 0, 0, 0, 0x2EF5),
    L2(250, 255, 0, 0, 0, 0, 0, 0x2EF5),
    CMD(CM_END, 0, 0, 7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 36 WIN 5, 37 WIN 6, 38 WIN 7, 39 WIN 8 */
const u16 ken_yuca_036_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ken_yuca_036[28] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x2EF6),
    L2(6, 0, 268, 0, 0, 0, 0, 0x2EF7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2EF8),
    L2(5, 0, 0, 0, 0, 0, 0, 0x2EF9),
    L2(250, 255, 0, 0, 0, 0, 0, 0x2EF9),
    CMD(CM_END, 0, 0, 5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 40 SP WIN 1, 41 SP WIN 2, 42 SP WIN 3, 43 SP WIN 4 ... */
const u16 ken_yuca_040_head[4] = { HEAD(4, 0, 0, 0, 0, 0, 0) };
const u16 ken_yuca_040[8] = {
    L4(8, 0, 0, 0, 0, 0, 0, 0x2C01, 1, 0, 0, 0, 0, 0),
};

/* script: 48 JUDGMENT WAIT, 49 JUDGMENT WAIT, 50 JUDGMENT WAIT, 51 JUDGMENT WAIT */
const u16 ken_yuca_048_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ken_yuca_048[44] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C01),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2C02),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C03),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C04),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C05),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C06),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C07),
    L2(2, 0, 0, 0, 0, 0, 0, 0x2C08),
    L2(2, 0, 0, 0, 0, 0, 0, 0x2C09),
    L2(3, 255, 0, 0, 0, 0, 0, 0x2C0A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 60 no name */
const u16 ken_yuca_060_head[4] = { HEAD(4, 0, 0, 0, 0, 0, 0) };
const u16 ken_yuca_060[84] = {
    L4(3, 0, 0, 0, 0, 0, 0, 0x2C01, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x2C02, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x2C03, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2C04, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2C05, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2C06, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2C07, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x2C08, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x2C09, 0, 1, 0, 0, 0, 0),
    L4(3, 255, 0, 0, 0, 0, 0, 0x2C0A, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 61 no name */
const u16 ken_yuca_061_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ken_yuca_061[76] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x2C29),
    L2(1, 0, 0, 0, 0, 0, 0, 0x2C40),
    L2(1, 0, 0, 0, 0, 0, 0, 0x2C41),
    L2(1, 0, 0, 0, 0, 0, 0, 0x2C6A),
    L2(1, 0, 0, 0, 0, 0, 0, 0x2C40),
    L2(1, 0, 0, 0, 0, 0, 0, 0x2C41),
    L2(1, 0, 0, 0, 0, 0, 0, 0x2C6A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C42),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C43),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C44),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C45),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C46),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C47),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C48),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C49),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C4A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C6B),
    CMD(CM_END, 0, 0, 15),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 62 no name */
const u16 ken_yuca_062_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ken_yuca_062[20] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C2A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C4B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2C2F),
    L2(3, 255, 0, 0, 0, 0, 0, 0x2C2F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 63 no name */
const u16 ken_yuca_063_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ken_yuca_063[40] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x2CB3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x2CB4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2CB5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2CB5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x2CB6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2CB7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2D99),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2D9A),
    L2(250, 255, 0, 0, 0, 0, 0, 0x2D9A),
    CMD(CM_ROA, 0, 0, 0),
};
