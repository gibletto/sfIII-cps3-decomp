/*
 * YANG_YUCA.C  Yang's yuca scripts
 *
 * char_table[9] (yuca, the viewer's second ETC kind): the scripts of Yang's appearances, wins and
 * losses in the scripts' usual form (see yang_char.c and charscr.h).
 */

#include "types.h"
#include "structs.h"
#include "charscr.h"

#pragma section CHR

extern const u16 yang_yuca_000[], yang_yuca_008[], yang_yuca_016[], yang_yuca_018[], yang_yuca_019[], yang_yuca_020[],
                 yang_yuca_024[], yang_yuca_032[], yang_yuca_036[], yang_yuca_038[], yang_yuca_040[], yang_yuca_048[],
                 yang_yuca_052[], yang_yuca_060[], yang_yuca_061[], yang_yuca_062[], yang_yuca_063[];

/* yuca scripts (debug viewer: ETC): 64 entries */
const u32 yang_yuca[65] = {
    (u32)yang_yuca_000,  /* 0 APPEAR JUNBI 1 */
    (u32)yang_yuca_000,  /* 1 APPEAR JUNBI 2 */
    (u32)yang_yuca_000,  /* 2 APPEAR JUNBI 3 */
    (u32)yang_yuca_000,  /* 3 APPEAR JUNBI 4 */
    (u32)yang_yuca_000,  /* 4 APPEAR JUNBI 5 */
    (u32)yang_yuca_000,  /* 5 APPEAR JUNBI 6 */
    (u32)yang_yuca_000,  /* 6 APPEAR JUNBI 7 */
    (u32)yang_yuca_000,  /* 7 APPEAR JUNBI 8 */
    (u32)yang_yuca_008,  /* 8 APPEAR 1 */
    (u32)yang_yuca_008,  /* 9 APPEAR 2 */
    (u32)yang_yuca_008,  /* 10 APPEAR 3 */
    (u32)yang_yuca_008,  /* 11 APPEAR 4 */
    (u32)yang_yuca_008,  /* 12 APPEAR 5 */
    (u32)yang_yuca_008,  /* 13 APPEAR 6 */
    (u32)yang_yuca_008,  /* 14 APPEAR 7 */
    (u32)yang_yuca_008,  /* 15 APPEAR 8 */
    (u32)yang_yuca_016,  /* 16 SP APPEAR 1 */
    (u32)yang_yuca_016,  /* 17 SP APPEAR 2 */
    (u32)yang_yuca_018,  /* 18 SP APPEAR 3 */
    (u32)yang_yuca_019,  /* 19 SP APPEAR 4 */
    (u32)yang_yuca_020,  /* 20 SP APPEAR 5 */
    (u32)yang_yuca_020,  /* 21 SP APPEAR 6 */
    (u32)yang_yuca_020,  /* 22 SP APPEAR 7 */
    (u32)yang_yuca_020,  /* 23 SP APPEAR 8 */
    (u32)yang_yuca_024,  /* 24 ZANNEN 1 */
    (u32)yang_yuca_024,  /* 25 ZANNEN 2 */
    (u32)yang_yuca_024,  /* 26 ZANNEN 3 */
    (u32)yang_yuca_024,  /* 27 ZANNEN 4 */
    (u32)yang_yuca_024,  /* 28 ZANNEN 5 */
    (u32)yang_yuca_024,  /* 29 ZANNEN 6 */
    (u32)yang_yuca_024,  /* 30 ZANNEN 7 */
    (u32)yang_yuca_024,  /* 31 ZANNEN 8 */
    (u32)yang_yuca_032,  /* 32 WIN 1 */
    (u32)yang_yuca_032,  /* 33 WIN 2 */
    (u32)yang_yuca_032,  /* 34 WIN 3 */
    (u32)yang_yuca_032,  /* 35 WIN 4 */
    (u32)yang_yuca_036,  /* 36 WIN 5 */
    (u32)yang_yuca_036,  /* 37 WIN 6 */
    (u32)yang_yuca_038,  /* 38 WIN 7 */
    (u32)yang_yuca_038,  /* 39 WIN 8 */
    (u32)yang_yuca_040,  /* 40 SP WIN 1 */
    (u32)yang_yuca_040,  /* 41 SP WIN 2 */
    (u32)yang_yuca_040,  /* 42 SP WIN 3 */
    (u32)yang_yuca_040,  /* 43 SP WIN 4 */
    (u32)yang_yuca_040,  /* 44 SP WIN 5 */
    (u32)yang_yuca_040,  /* 45 SP WIN 6 */
    (u32)yang_yuca_040,  /* 46 SP WIN 7 */
    (u32)yang_yuca_040,  /* 47 SP WIN 8 */
    (u32)yang_yuca_048,  /* 48 JUDGMENT WAIT */
    (u32)yang_yuca_048,  /* 49 JUDGMENT WAIT */
    (u32)yang_yuca_048,  /* 50 JUDGMENT WAIT */
    (u32)yang_yuca_048,  /* 51 JUDGMENT WAIT */
    (u32)yang_yuca_052,  /* 52 JUDGMENT WIN */
    (u32)yang_yuca_052,  /* 53 JUDGMENT WIN */
    (u32)yang_yuca_052,  /* 54 JUDGMENT WIN */
    (u32)yang_yuca_052,  /* 55 JUDGMENT WIN */
    (u32)yang_yuca_024,  /* 56 JUDGMENT LOSE */
    (u32)yang_yuca_024,  /* 57 JUDGMENT LOSE */
    (u32)yang_yuca_024,  /* 58 JUDGMENT LOSE */
    (u32)yang_yuca_024,  /* 59 JUDGMENT LOSE */
    (u32)yang_yuca_060,  /* 60 no name */
    (u32)yang_yuca_061,  /* 61 no name */
    (u32)yang_yuca_062,  /* 62 no name */
    (u32)yang_yuca_063,  /* 63 no name */
    0
};

/* script: 0 APPEAR JUNBI 1, 1 APPEAR JUNBI 2, 2 APPEAR JUNBI 3, 3 APPEAR JUNBI 4 ... */
const u16 yang_yuca_000_head[4] = { HEAD(2, 6, 0, 0, 0, 0, 0) };
const u16 yang_yuca_000[8] = {
    L2(8, 9, 0, 0, 0, 0, 0, 0x2B80),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 APPEAR 1, 9 APPEAR 2, 10 APPEAR 3, 11 APPEAR 4 ... */
const u16 yang_yuca_008_head[4] = { HEAD(4, 0, 0, 0, 0, 0, 0) };
const u16 yang_yuca_008[324] = {
    L4(8, 0, 0, 0, 0, 0, 0, 0x2B80, 0, 1, 0, 0, 0, 0),
    L4(5, 0, 0, 0, 0, 0, 0, 0x2B81, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B82, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B83, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x2B84, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x2B85, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x2B86, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x2B87, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x2B88, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x2B87, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x2B86, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x2B85, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x2B84, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x2B85, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x2B86, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x2B87, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x2B88, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, -256, 0), 0, 0, 0, 0,
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B89, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, -256, 0), 0, 0, 0, 0,
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B8A, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x2B8B, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x2B66, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, 256, 0), 0, 0, 0, 0,
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B67, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, 256, 0), 0, 0, 0, 0,
    L4(10, 0, 0, 0, 0, 0, 0, 0x2B68, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, -256, 0), 0, 0, 0, 0,
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B67, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, -256, 0), 0, 0, 0, 0,
    L4(5, 0, 0, 0, 0, 0, 0, 0x2B66, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B64, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, -256, 0), 0, 0, 0, 0,
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B63, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, -256, 0), 0, 0, 0, 0,
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B62, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x2841, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2840, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x283F, 0, 1, 0, 0, 0, 0),
    L4(250, 255, 0, 0, 0, 0, 0, 0x283F, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 16 SP APPEAR 1, 17 SP APPEAR 2 */
const u16 yang_yuca_016_head[4] = { HEAD(4, 6, 0, 0, 0, 0, 0) };
const u16 yang_yuca_016[20] = {
    L4(2, 0, 0, 0, 0, 0, 0, 0x287B, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x287C, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 18 SP APPEAR 3 */
const u16 yang_yuca_018_head[4] = { HEAD(4, 6, 0, 0, 0, 0, 0) };
const u16 yang_yuca_018[44] = {
    L4(1, 0, 0, 0, 0, 0, 0, 0x287D, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x287E, 0, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x287F, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x2841, 0, 1, 0, 0, 0, 0),
    L4(8, 1, 0, 0, 0, 0, 0, 0x2841, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 19 SP APPEAR 4 */
const u16 yang_yuca_019_head[4] = { HEAD(4, 6, 0, 0, 0, 0, 0) };
const u16 yang_yuca_019[164] = {
    L4(6, 0, 0, 0, 0, 0, 0, 0x2B62, 0, 1, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x2B63, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B64, 0, 1, 0, 0, 0, 0),
    L4(5, 0, 0, 0, 0, 0, 0, 0x2B65, 0, 1, 0, 0, 0, 0),
    L4(5, 0, 0, 0, 0, 0, 0, 0x2B66, 0, 1, 0, 0, 0, 0),
    L4(5, 0, 0, 0, 0, 0, 0, 0x2B67, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, 512, 0), 0, 0, 0, 0,
    L4(12, 0, 0, 0, 0, 0, 0, 0x2B68, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B67, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B66, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, -256, 0), 0, 0, 0, 0,
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B64, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, -256, 0), 0, 0, 0, 0,
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B63, 0, 1, 0, 0, 0, 0),
    CMD(CM_PA_X, 0, -256, 0), 0, 0, 0, 0,
    L4(4, 0, 0, 0, 0, 0, 0, 0x2B62, 0, 1, 0, 0, 0, 0),
    L4(6, 0, 0, 0, 0, 0, 0, 0x2841, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x2840, 0, 1, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x283F, 0, 1, 0, 0, 0, 0),
    L4(250, 255, 0, 0, 0, 0, 0, 0x283F, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 20 SP APPEAR 5, 21 SP APPEAR 6, 22 SP APPEAR 7, 23 SP APPEAR 8 */
const u16 yang_yuca_020_head[4] = { HEAD(2, 6, 0, 0, 0, 0, 0) };
const u16 yang_yuca_020[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x2B8C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 24 ZANNEN 1, 25 ZANNEN 2, 26 ZANNEN 3, 27 ZANNEN 4 ... */
const u16 yang_yuca_024_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yang_yuca_024[20] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B56),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B57),
    L2(4, 255, 0, 0, 0, 0, 0, 0x2B58),
    CMD(CM_END, 0, 0, 2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 32 WIN 1, 33 WIN 2, 34 WIN 3, 35 WIN 4 */
const u16 yang_yuca_032_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yang_yuca_032[84] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x2801),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B62),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B63),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B64),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B69),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B6A),
    CMD(CM_PA_X, 0, 512, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B6B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B6C),
    CMD(CM_PA_X, 0, -512, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B6B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B6A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B6D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B6E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B6F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B70),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B6F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B6E),
    L2(250, 255, 0, 0, 0, 0, 0, 0x2B6E),
    CMD(CM_END, 0, 0, 18),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 36 WIN 5, 37 WIN 6 */
const u16 yang_yuca_036_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yang_yuca_036[64] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x2801),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B71),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B72),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B73),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B74),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B75),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B76),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B77),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B78),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B79),
    L2(4, 0, 421, 0, 0, 0, 0, 0x2B7A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B7B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B7C),
    L2(250, 255, 0, 0, 0, 0, 0, 0x2B7C),
    CMD(CM_END, 0, 0, 13),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 38 WIN 7, 39 WIN 8 */
const u16 yang_yuca_038_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yang_yuca_038[64] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x2801),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B71),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B72),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B73),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B74),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B75),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B76),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B77),
    L2(4, 0, 423, 0, 0, 0, 0, 0x2B78),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B79),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B7A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B7B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B7C),
    L2(250, 255, 0, 0, 0, 0, 0, 0x2B7C),
    CMD(CM_END, 0, 0, 13),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 40 SP WIN 1, 41 SP WIN 2, 42 SP WIN 3, 43 SP WIN 4 ... */
const u16 yang_yuca_040_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yang_yuca_040[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x2801),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 48 JUDGMENT WAIT, 49 JUDGMENT WAIT, 50 JUDGMENT WAIT, 51 JUDGMENT WAIT */
const u16 yang_yuca_048_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yang_yuca_048[52] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x2801),
    L2(8, 0, 0, 0, 0, 0, 0, 0x2802),
    L2(8, 0, 0, 0, 0, 0, 0, 0x2803),
    L2(8, 0, 0, 0, 0, 0, 0, 0x2804),
    L2(8, 0, 0, 0, 0, 0, 0, 0x2805),
    L2(8, 0, 0, 0, 0, 0, 0, 0x2806),
    L2(8, 0, 0, 0, 0, 0, 0, 0x2807),
    L2(8, 0, 0, 0, 0, 0, 0, 0x2808),
    L2(8, 0, 0, 0, 0, 0, 0, 0x2809),
    L2(8, 0, 0, 0, 0, 0, 0, 0x280A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x280B),
    L2(8, 255, 0, 0, 0, 0, 0, 0x280C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 52 JUDGMENT WIN, 53 JUDGMENT WIN, 54 JUDGMENT WIN, 55 JUDGMENT WIN */
const u16 yang_yuca_052_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yang_yuca_052[32] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B59),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B5A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B5B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B5C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2B5D),
    L2(250, 0, 0, 0, 0, 0, 0, 0x2B5E),
    CMD(CM_END, 0, 0, 6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 60 no name */
const u16 yang_yuca_060_head[4] = { HEAD(4, 0, 0, 0, 0, 0, 0) };
const u16 yang_yuca_060[100] = {
    L4(16, 0, 0, 0, 0, 0, 0, 0x2801, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x2802, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x2803, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x2804, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x2805, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x2806, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x2807, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x2808, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x2809, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x280A, 0, 1, 0, 0, 0, 0),
    L4(16, 0, 0, 0, 0, 0, 0, 0x280B, 0, 1, 0, 0, 0, 0),
    L4(16, 255, 0, 0, 0, 0, 0, 0x280C, 0, 1, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 61 no name */
const u16 yang_yuca_061_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yang_yuca_061[60] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x2860),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2861),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2862),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2863),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2864),
    L2(2, 0, 0, 0, 0, 0, 0, 0x2865),
    L2(2, 0, 0, 0, 0, 0, 0, 0x2866),
    L2(2, 0, 0, 0, 0, 0, 0, 0x2867),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2868),
    L2(3, 0, 0, 0, 0, 0, 0, 0x2869),
    L2(3, 0, 0, 0, 0, 0, 0, 0x286A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x286B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x286C),
    CMD(CM_END, 0, 0, 12),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 62 no name */
const u16 yang_yuca_062_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yang_yuca_062[32] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x286D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x286E),
    L2(1, 0, 0, 0, 0, 0, 0, 0x286F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2841),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2840),
    L2(4, 0, 0, 0, 0, 0, 0, 0x283F),
    L2(4, 255, 0, 0, 0, 0, 0, 0x283F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 63 no name */
const u16 yang_yuca_063_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 yang_yuca_063[28] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x2900),
    L2(2, 0, 0, 0, 0, 0, 0, 0x2901),
    L2(2, 0, 0, 0, 0, 0, 0, 0x2902),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2903),
    L2(4, 0, 0, 0, 0, 0, 0, 0x2904),
    L2(250, 255, 0, 0, 0, 0, 0, 0x2904),
    CMD(CM_ROA, 0, 0, 0),
};
