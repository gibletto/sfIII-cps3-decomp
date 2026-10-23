/*
 * HUGO_YUCA.C  Hugo's yuca scripts
 *
 * char_table[9] (yuca, the viewer's second ETC kind): the scripts of Hugo's appearances, wins and
 * losses in the scripts' usual form (see hugo_char.c and charscr.h).
 */

#include "types.h"
#include "structs.h"
#include "charscr.h"

#pragma section CHR

extern const u16 hugo_yuca_000[], hugo_yuca_008[], hugo_yuca_016[], hugo_yuca_024[], hugo_yuca_032[], hugo_yuca_040[],
                 hugo_yuca_048[], hugo_yuca_052[], hugo_yuca_056[], hugo_yuca_060[], hugo_yuca_063[];

/* yuca scripts (debug viewer: ETC): 64 entries */
const u32 hugo_yuca[65] = {
    (u32)hugo_yuca_000,  /* 0 APPEAR JUNBI 1 */
    (u32)hugo_yuca_000,  /* 1 APPEAR JUNBI 2 */
    (u32)hugo_yuca_000,  /* 2 APPEAR JUNBI 3 */
    (u32)hugo_yuca_000,  /* 3 APPEAR JUNBI 4 */
    (u32)hugo_yuca_000,  /* 4 APPEAR JUNBI 5 */
    (u32)hugo_yuca_000,  /* 5 APPEAR JUNBI 6 */
    (u32)hugo_yuca_000,  /* 6 APPEAR JUNBI 7 */
    (u32)hugo_yuca_000,  /* 7 APPEAR JUNBI 8 */
    (u32)hugo_yuca_008,  /* 8 APPEAR 1 */
    (u32)hugo_yuca_008,  /* 9 APPEAR 2 */
    (u32)hugo_yuca_008,  /* 10 APPEAR 3 */
    (u32)hugo_yuca_008,  /* 11 APPEAR 4 */
    (u32)hugo_yuca_008,  /* 12 APPEAR 5 */
    (u32)hugo_yuca_008,  /* 13 APPEAR 6 */
    (u32)hugo_yuca_008,  /* 14 APPEAR 7 */
    (u32)hugo_yuca_008,  /* 15 APPEAR 8 */
    (u32)hugo_yuca_016,  /* 16 SP APPEAR 1 */
    (u32)hugo_yuca_016,  /* 17 SP APPEAR 2 */
    (u32)hugo_yuca_016,  /* 18 SP APPEAR 3 */
    (u32)hugo_yuca_016,  /* 19 SP APPEAR 4 */
    (u32)hugo_yuca_016,  /* 20 SP APPEAR 5 */
    (u32)hugo_yuca_016,  /* 21 SP APPEAR 6 */
    (u32)hugo_yuca_016,  /* 22 SP APPEAR 7 */
    (u32)hugo_yuca_016,  /* 23 SP APPEAR 8 */
    (u32)hugo_yuca_024,  /* 24 ZANNEN 1 */
    (u32)hugo_yuca_024,  /* 25 ZANNEN 2 */
    (u32)hugo_yuca_024,  /* 26 ZANNEN 3 */
    (u32)hugo_yuca_024,  /* 27 ZANNEN 4 */
    (u32)hugo_yuca_024,  /* 28 ZANNEN 5 */
    (u32)hugo_yuca_024,  /* 29 ZANNEN 6 */
    (u32)hugo_yuca_024,  /* 30 ZANNEN 7 */
    (u32)hugo_yuca_024,  /* 31 ZANNEN 8 */
    (u32)hugo_yuca_032,  /* 32 WIN 1 */
    (u32)hugo_yuca_032,  /* 33 WIN 2 */
    (u32)hugo_yuca_032,  /* 34 WIN 3 */
    (u32)hugo_yuca_032,  /* 35 WIN 4 */
    (u32)hugo_yuca_032,  /* 36 WIN 5 */
    (u32)hugo_yuca_032,  /* 37 WIN 6 */
    (u32)hugo_yuca_032,  /* 38 WIN 7 */
    (u32)hugo_yuca_032,  /* 39 WIN 8 */
    (u32)hugo_yuca_040,  /* 40 SP WIN 1 */
    (u32)hugo_yuca_040,  /* 41 SP WIN 2 */
    (u32)hugo_yuca_040,  /* 42 SP WIN 3 */
    (u32)hugo_yuca_040,  /* 43 SP WIN 4 */
    (u32)hugo_yuca_040,  /* 44 SP WIN 5 */
    (u32)hugo_yuca_040,  /* 45 SP WIN 6 */
    (u32)hugo_yuca_040,  /* 46 SP WIN 7 */
    (u32)hugo_yuca_040,  /* 47 SP WIN 8 */
    (u32)hugo_yuca_048,  /* 48 JUDGMENT WAIT */
    (u32)hugo_yuca_048,  /* 49 JUDGMENT WAIT */
    (u32)hugo_yuca_048,  /* 50 JUDGMENT WAIT */
    (u32)hugo_yuca_048,  /* 51 JUDGMENT WAIT */
    (u32)hugo_yuca_052,  /* 52 JUDGMENT WIN */
    (u32)hugo_yuca_052,  /* 53 JUDGMENT WIN */
    (u32)hugo_yuca_052,  /* 54 JUDGMENT WIN */
    (u32)hugo_yuca_052,  /* 55 JUDGMENT WIN */
    (u32)hugo_yuca_056,  /* 56 JUDGMENT LOSE */
    (u32)hugo_yuca_056,  /* 57 JUDGMENT LOSE */
    (u32)hugo_yuca_056,  /* 58 JUDGMENT LOSE */
    (u32)hugo_yuca_056,  /* 59 JUDGMENT LOSE */
    (u32)hugo_yuca_060,  /* 60 no name */
    (u32)hugo_yuca_060,  /* 61 no name */
    (u32)hugo_yuca_060,  /* 62 no name */
    (u32)hugo_yuca_063,  /* 63 no name */
    0
};

/* script: 0 APPEAR JUNBI 1, 1 APPEAR JUNBI 2, 2 APPEAR JUNBI 3, 3 APPEAR JUNBI 4 ... */
const u16 hugo_yuca_000_head[4] = { HEAD(4, 6, 0, 0, 0, 0, 0) };
const u16 hugo_yuca_000[188] = {
    L4(3, 0, 0, 0, 0, 0, 0, 0x1836, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x1837, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x1838, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x1839, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x183A, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x183B, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x1801, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x1802, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x1803, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x1804, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x1805, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x1806, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x1807, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x1808, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x1809, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x180A, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x180B, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x180C, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x180D, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x180E, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x180F, 0, 1, 0, 0, 0, 0),
    L4(6, 9, 0, 0, 0, 0, 0, 0x1810, 0, 1, 0, 0, 0, 0),
    CMD(CM_END, 0, 0, 7), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 8 APPEAR 1, 9 APPEAR 2, 10 APPEAR 3, 11 APPEAR 4 ... */
const u16 hugo_yuca_008_head[4] = { HEAD(4, 0, 0, 0, 0, 0, 0) };
const u16 hugo_yuca_008[36] = {
    L4(8, 0, 0, 0, 0, 0, 0, 0x1841, 0, 1, 0, 0, 0, 0),
    L4(8, 0, 0, 0, 0, 0, 0, 0x1840, 0, 1, 0, 0, 0, 0),
    L4(8, 0, 0, 0, 0, 0, 0, 0x183F, 0, 1, 0, 0, 0, 0),
    L4(250, 255, 0, 0, 0, 0, 0, 0x183F, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 16 SP APPEAR 1, 17 SP APPEAR 2, 18 SP APPEAR 3, 19 SP APPEAR 4 ... */
const u16 hugo_yuca_016_head[4] = { HEAD(4, 24, 0, 0, 0, 0, 0) };
const u16 hugo_yuca_016[12] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x1801, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 24 ZANNEN 1, 25 ZANNEN 2, 26 ZANNEN 3, 27 ZANNEN 4 ... */
const u16 hugo_yuca_024_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 hugo_yuca_024[20] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x1841),
    L2(8, 0, 0, 0, 0, 0, 0, 0x1840),
    L2(8, 0, 0, 0, 0, 0, 0, 0x183F),
    L2(250, 255, 0, 0, 0, 0, 0, 0x183F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 32 WIN 1, 33 WIN 2, 34 WIN 3, 35 WIN 4 ... */
const u16 hugo_yuca_032_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 hugo_yuca_032[20] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x1841),
    L2(8, 0, 0, 0, 0, 0, 0, 0x1840),
    L2(8, 0, 0, 0, 0, 0, 0, 0x183F),
    L2(250, 255, 0, 0, 0, 0, 0, 0x183F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 40 SP WIN 1, 41 SP WIN 2, 42 SP WIN 3, 43 SP WIN 4 ... */
const u16 hugo_yuca_040_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 hugo_yuca_040[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x1801),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 48 JUDGMENT WAIT, 49 JUDGMENT WAIT, 50 JUDGMENT WAIT, 51 JUDGMENT WAIT */
const u16 hugo_yuca_048_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 hugo_yuca_048[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x1801),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 52 JUDGMENT WIN, 53 JUDGMENT WIN, 54 JUDGMENT WIN, 55 JUDGMENT WIN */
const u16 hugo_yuca_052_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 hugo_yuca_052[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x1801),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 56 JUDGMENT LOSE, 57 JUDGMENT LOSE, 58 JUDGMENT LOSE, 59 JUDGMENT LOSE */
const u16 hugo_yuca_056_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 hugo_yuca_056[8] = {
    L2(250, 0, 0, 0, 0, 0, 0, 0x1801),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 60 no name, 61 no name, 62 no name */
const u16 hugo_yuca_060_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 hugo_yuca_060[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x1801),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 63 no name */
const u16 hugo_yuca_063_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 hugo_yuca_063[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x1801),
    CMD(CM_ROA, 0, 0, 0),
};
