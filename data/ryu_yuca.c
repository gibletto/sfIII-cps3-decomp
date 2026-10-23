/*
 * RYU_YUCA.C  Ryu's yuca scripts
 *
 * char_table[9] (yuca, the viewer's second ETC kind): the scripts of Ryu's appearances, wins and
 * losses in the scripts' usual form (see ryu_char.c and charscr.h).
 */

#include "types.h"
#include "structs.h"
#include "charscr.h"

#pragma section CHR

extern const u16 ryu_yuca_000[], ryu_yuca_008[], ryu_yuca_016[], ryu_yuca_024[], ryu_yuca_032[], ryu_yuca_036[],
                 ryu_yuca_040[], ryu_yuca_048[], ryu_yuca_060[], ryu_yuca_061[], ryu_yuca_062[], ryu_yuca_063[];

/* yuca scripts (debug viewer: ETC): 64 entries */
const u32 ryu_yuca[65] = {
    (u32)ryu_yuca_000,  /* 0 APPEAR JUNBI 1 */
    (u32)ryu_yuca_000,  /* 1 APPEAR JUNBI 2 */
    (u32)ryu_yuca_000,  /* 2 APPEAR JUNBI 3 */
    (u32)ryu_yuca_000,  /* 3 APPEAR JUNBI 4 */
    (u32)ryu_yuca_000,  /* 4 APPEAR JUNBI 5 */
    (u32)ryu_yuca_000,  /* 5 APPEAR JUNBI 6 */
    (u32)ryu_yuca_000,  /* 6 APPEAR JUNBI 7 */
    (u32)ryu_yuca_000,  /* 7 APPEAR JUNBI 8 */
    (u32)ryu_yuca_008,  /* 8 APPEAR 1 */
    (u32)ryu_yuca_008,  /* 9 APPEAR 2 */
    (u32)ryu_yuca_008,  /* 10 APPEAR 3 */
    (u32)ryu_yuca_008,  /* 11 APPEAR 4 */
    (u32)ryu_yuca_008,  /* 12 APPEAR 5 */
    (u32)ryu_yuca_008,  /* 13 APPEAR 6 */
    (u32)ryu_yuca_008,  /* 14 APPEAR 7 */
    (u32)ryu_yuca_008,  /* 15 APPEAR 8 */
    (u32)ryu_yuca_016,  /* 16 SP APPEAR 1 */
    (u32)ryu_yuca_016,  /* 17 SP APPEAR 2 */
    (u32)ryu_yuca_016,  /* 18 SP APPEAR 3 */
    (u32)ryu_yuca_016,  /* 19 SP APPEAR 4 */
    (u32)ryu_yuca_016,  /* 20 SP APPEAR 5 */
    (u32)ryu_yuca_016,  /* 21 SP APPEAR 6 */
    (u32)ryu_yuca_016,  /* 22 SP APPEAR 7 */
    (u32)ryu_yuca_016,  /* 23 SP APPEAR 8 */
    (u32)ryu_yuca_024,  /* 24 ZANNEN 1 */
    (u32)ryu_yuca_024,  /* 25 ZANNEN 2 */
    (u32)ryu_yuca_024,  /* 26 ZANNEN 3 */
    (u32)ryu_yuca_024,  /* 27 ZANNEN 4 */
    (u32)ryu_yuca_024,  /* 28 ZANNEN 5 */
    (u32)ryu_yuca_024,  /* 29 ZANNEN 6 */
    (u32)ryu_yuca_024,  /* 30 ZANNEN 7 */
    (u32)ryu_yuca_024,  /* 31 ZANNEN 8 */
    (u32)ryu_yuca_032,  /* 32 WIN 1 */
    (u32)ryu_yuca_032,  /* 33 WIN 2 */
    (u32)ryu_yuca_032,  /* 34 WIN 3 */
    (u32)ryu_yuca_032,  /* 35 WIN 4 */
    (u32)ryu_yuca_036,  /* 36 WIN 5 */
    (u32)ryu_yuca_036,  /* 37 WIN 6 */
    (u32)ryu_yuca_036,  /* 38 WIN 7 */
    (u32)ryu_yuca_036,  /* 39 WIN 8 */
    (u32)ryu_yuca_040,  /* 40 SP WIN 1 */
    (u32)ryu_yuca_040,  /* 41 SP WIN 2 */
    (u32)ryu_yuca_040,  /* 42 SP WIN 3 */
    (u32)ryu_yuca_040,  /* 43 SP WIN 4 */
    (u32)ryu_yuca_040,  /* 44 SP WIN 5 */
    (u32)ryu_yuca_040,  /* 45 SP WIN 6 */
    (u32)ryu_yuca_040,  /* 46 SP WIN 7 */
    (u32)ryu_yuca_040,  /* 47 SP WIN 8 */
    (u32)ryu_yuca_048,  /* 48 JUDGMENT WAIT */
    (u32)ryu_yuca_048,  /* 49 JUDGMENT WAIT */
    (u32)ryu_yuca_048,  /* 50 JUDGMENT WAIT */
    (u32)ryu_yuca_048,  /* 51 JUDGMENT WAIT */
    (u32)ryu_yuca_032,  /* 52 JUDGMENT WIN */
    (u32)ryu_yuca_032,  /* 53 JUDGMENT WIN */
    (u32)ryu_yuca_032,  /* 54 JUDGMENT WIN */
    (u32)ryu_yuca_032,  /* 55 JUDGMENT WIN */
    (u32)ryu_yuca_024,  /* 56 JUDGMENT LOSE */
    (u32)ryu_yuca_024,  /* 57 JUDGMENT LOSE */
    (u32)ryu_yuca_024,  /* 58 JUDGMENT LOSE */
    (u32)ryu_yuca_024,  /* 59 JUDGMENT LOSE */
    (u32)ryu_yuca_060,  /* 60 no name */
    (u32)ryu_yuca_061,  /* 61 no name */
    (u32)ryu_yuca_062,  /* 62 no name */
    (u32)ryu_yuca_063,  /* 63 no name */
    0
};

/* script: 0 APPEAR JUNBI 1, 1 APPEAR JUNBI 2, 2 APPEAR JUNBI 3, 3 APPEAR JUNBI 4 ... */
const u16 ryu_yuca_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ryu_yuca_000[8] = {
    L2(4, 9, 0, 0, 0, 0, 0, 0x0AD0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 APPEAR 1, 9 APPEAR 2, 10 APPEAR 3, 11 APPEAR 4 ... */
const u16 ryu_yuca_008_head[4] = { HEAD(4, 0, 0, 0, 0, 0, 0) };
const u16 ryu_yuca_008[76] = {
    L4(32, 0, 0, 0, 0, 0, 0, 0x0AD0, 0, 1, 0, 0, 0, 0),
    L4(7, 0, 511, 0, 0, 0, 0, 0x0AD1, 0, 1, 0, 0, 0, 0),
    L4(7, 0, 0, 0, 0, 0, 0, 0x0AD2, 0, 1, 0, 0, 0, 0),
    L4(7, 0, 0, 0, 0, 0, 0, 0x0AD3, 0, 1, 0, 0, 0, 0),
    CMD(CM_EXEC, 12, 0, 0), 0x0000, 0x0001, 0x0000, 0x0000,
    L4(7, 0, 0, 0, 0, 0, 0, 0x082E, 0, 1, 0, 0, 0, 0),
    L4(7, 0, 0, 0, 0, 0, 0, 0x082F, 0, 1, 0, 0, 0, 0),
    L4(7, 0, 0, 0, 0, 0, 0, 0x0893, 0, 1, 0, 0, 0, 0),
    L4(250, 255, 0, 0, 0, 0, 0, 0x0893, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 16 SP APPEAR 1, 17 SP APPEAR 2, 18 SP APPEAR 3, 19 SP APPEAR 4 ... */
const u16 ryu_yuca_016_head[4] = { HEAD(2, 24, 0, 0, 0, 0, 0) };
const u16 ryu_yuca_016[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x0801),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 24 ZANNEN 1, 25 ZANNEN 2, 26 ZANNEN 3, 27 ZANNEN 4 ... */
const u16 ryu_yuca_024_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ryu_yuca_024[32] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x0B3E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x0B3F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x0B40),
    L2(6, 0, 0, 0, 0, 0, 0, 0x0B41),
    L2(6, 0, 0, 0, 0, 0, 0, 0x0B42),
    L2(6, 255, 0, 0, 0, 0, 0, 0x0B42),
    CMD(CM_END, 0, 0, 6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 32 WIN 1, 33 WIN 2, 34 WIN 3, 35 WIN 4 ... */
const u16 ryu_yuca_032_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ryu_yuca_032[48] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x0AF0),
    CMD(CM_PA_X, 0, -256, 0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x0AF1),
    CMD(CM_PA_X, 0, -256, 0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0AF2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0AF3),
    CMD(CM_PA_X, 0, -256, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0AF4),
    L2(12, 0, 0, 0, 0, 0, 0, 0x0AF5),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0AF5),
    CMD(CM_END, 0, 0, 10),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 36 WIN 5, 37 WIN 6, 38 WIN 7, 39 WIN 8 */
const u16 ryu_yuca_036_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ryu_yuca_036[120] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x0AF6),
    CMD(CM_PA_X, 0, 512, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0AF7),
    CMD(CM_PA_X, 0, 512, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0AF8),
    CMD(CM_PA_X, 0, 512, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0AF9),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0AFA),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0AFB),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0AFC),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0AFD),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0AFE),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0AFF),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0B01),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0B02),
    L2(7, 255, 0, 0, 0, 0, 0, 0x0B03),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0B04),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0B05),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0B06),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0B07),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0B08),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0B09),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0B0A),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0B0B),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0B0C),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0B0D),
    L2(7, 0, 0, 0, 0, 0, 0, 0x0AFA),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0AFA),
    CMD(CM_END, 0, 0, 28),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 40 SP WIN 1, 41 SP WIN 2, 42 SP WIN 3, 43 SP WIN 4 ... */
const u16 ryu_yuca_040_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ryu_yuca_040[8] = {
    L2(7, 255, 0, 0, 0, 0, 0, 0x0801),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 48 JUDGMENT WAIT, 49 JUDGMENT WAIT, 50 JUDGMENT WAIT, 51 JUDGMENT WAIT */
const u16 ryu_yuca_048_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ryu_yuca_048[44] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x0801),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0802),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0803),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0804),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0805),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0806),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0807),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0808),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0809),
    L2(2, 255, 0, 0, 0, 0, 0, 0x080A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 60 no name */
const u16 ryu_yuca_060_head[4] = { HEAD(4, 0, 0, 0, 0, 0, 0) };
const u16 ryu_yuca_060[84] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x0801, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x0802, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x0803, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x0804, 0, 1, 0, 0, 0, 0),
    L4(5, 0, 0, 0, 0, 0, 0, 0x0805, 0, 1, 0, 0, 0, 0),
    L4(5, 0, 0, 0, 0, 0, 0, 0x0806, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x0807, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x0808, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x0809, 0, 1, 0, 0, 0, 0),
    L4(3, 255, 0, 0, 0, 0, 0, 0x080A, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 61 no name */
const u16 ryu_yuca_061_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ryu_yuca_061[76] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x0829),
    L2(1, 0, 281, 0, 0, 0, 0, 0x0840),
    L2(1, 0, 0, 0, 0, 0, 0, 0x0841),
    L2(1, 0, 0, 0, 0, 0, 0, 0x086A),
    L2(1, 0, 0, 0, 0, 0, 0, 0x0840),
    L2(1, 0, 0, 0, 0, 0, 0, 0x0841),
    L2(1, 0, 0, 0, 0, 0, 0, 0x086A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0842),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0843),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0844),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0845),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0846),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0847),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0848),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0849),
    L2(3, 0, 0, 0, 0, 0, 0, 0x084A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x086B),
    CMD(CM_END, 0, 0, 15),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 62 no name */
const u16 ryu_yuca_062_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ryu_yuca_062[20] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x082A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x084B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x082F),
    L2(3, 255, 0, 0, 0, 0, 0, 0x082F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 63 no name */
const u16 ryu_yuca_063_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ryu_yuca_063[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x08B3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x08B4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x08B5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x08B6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x08B7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x0999),
    L2(4, 0, 0, 0, 0, 0, 0, 0x099A),
    L2(250, 255, 0, 0, 0, 0, 0, 0x099A),
    CMD(CM_ROA, 0, 0, 0),
};
