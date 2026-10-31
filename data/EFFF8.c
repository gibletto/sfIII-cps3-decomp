/*
 * EFFF8.C  tables read by EffG0.c, and the ending scene lists
 *
 * Each scene list is a run of (message number, frames) ending with 0, 0xFFFF; txt_no_tbl's tables (efff9_mes.c,
 * work RAM) point at them, and a list is named after the first entry that points at it (txt_no_NN_K: player table
 * NN, entry K).
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u16 plXXtxt0[];
extern const u16 txt_no_00_1[];
extern const u16 txt_no_00_2[];
extern const u16 txt_no_00_3[];
extern const u16 txt_no_00_4[];
extern const u16 txt_no_00_5[];
extern const u16 txt_no_00_6[];
extern const u16 txt_no_00_7[];
extern const u16 txt_no_00_8[];
extern const u16 txt_no_02_1[];
extern const u16 txt_no_02_2[];
extern const u16 txt_no_02_3[];
extern const u16 txt_no_02_4[];
extern const u16 txt_no_03_1[];
extern const u16 txt_no_03_2[];
extern const u16 txt_no_03_3[];
extern const u16 txt_no_03_4[];
extern const u16 txt_no_03_5[];
extern const u16 txt_no_03_6[];
extern const u16 txt_no_03_7[];
extern const u16 txt_no_03_8[];
extern const u16 txt_no_03_9[];
extern const u16 txt_no_04_1[];
extern const u16 txt_no_04_2[];
extern const u16 txt_no_04_3[];
extern const u16 txt_no_04_4[];
extern const u16 txt_no_04_5[];
extern const u16 txt_no_05_1[];
extern const u16 txt_no_05_2[];
extern const u16 txt_no_05_3[];
extern const u16 txt_no_05_4[];
extern const u16 txt_no_05_5[];
extern const u16 txt_no_05_6[];
extern const u16 txt_no_07_1[];
extern const u16 txt_no_07_2[];
extern const u16 txt_no_07_3[];
extern const u16 txt_no_07_4[];
extern const u16 txt_no_07_5[];
extern const u16 txt_no_07_6[];
extern const u16 txt_no_07_7[];
extern const u16 txt_no_07_8[];
extern const u16 txt_no_07_9[];
extern const u16 txt_no_07_10[];
extern const u16 txt_no_08_1[];
extern const u16 txt_no_08_2[];
extern const u16 txt_no_08_3[];
extern const u16 txt_no_08_4[];
extern const u16 txt_no_09_1[];
extern const u16 txt_no_09_2[];
extern const u16 txt_no_09_3[];
extern const u16 txt_no_09_4[];
extern const u16 txt_no_09_5[];
extern const u16 txt_no_11_1[];
extern const u16 txt_no_11_2[];
extern const u16 txt_no_11_3[];
extern const u16 txt_no_11_4[];
extern const u16 txt_no_11_5[];
extern const u16 txt_no_11_6[];
extern const u16 txt_no_12_1[];
extern const u16 txt_no_12_2[];
extern const u16 txt_no_12_3[];
extern const u16 txt_no_12_4[];
extern const u16 txt_no_12_5[];
extern const s16 effg0_col_tbl[];
extern const s16 effg0_pos_tbl[][3];
extern const s16 effg0_flash_tbl[][4];
extern const s16 effg0_name_tbl[][3];
extern const s16 effg0_name_tbl2[][3];

const u16 plXXtxt0[2] = {
    0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_00_1[14] = {
    1, 0xA0, 2, 0xC8, 3, 0xB4, 4, 0xDC,
    5, 0xDC, 6, 0x118, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_00_2[4] = {
    7, 0x200, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_00_3[6] = {
    8, 0xF0, 9, 0x5A, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_00_4[4] = {
    0xA, 0xB4, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_00_5[8] = {
    0xB, 0x8C, 0xC, 0xB4, 0xD, 0x17C, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_00_6[6] = {
    0xE, 0x118, 0xF, 0x12C, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_00_7[2] = {
    0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_00_8[6] = {
    0x10, 0xF0, 0x11, 0x168, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_02_1[6] = {
    1, 0x104, 2, 0xDC, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_02_2[6] = {
    3, 0x82, 4, 0xE6, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_02_3[8] = {
    7, 0x78, 8, 0x78, 5, 0xB4, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_02_4[6] = {
    9, 0x78, 6, 0x118, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_03_1[4] = {
    1, 0x100, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_03_2[4] = {
    2, 0x100, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_03_3[8] = {
    3, 0x5A, 4, 0x78, 5, 0x120, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_03_4[8] = {
    6, 0x5A, 7, 0xB4, 8, 0x120, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_03_5[6] = {
    9, 0x78, 0xA, 0xF0, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_03_6[4] = {
    0xB, 0x100, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_03_7[4] = {
    0xC, 0x120, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_03_8[4] = {
    0xD, 0x120, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_03_9[6] = {
    0xE, 0xF0, 0xF, 0x120, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_04_1[8] = {
    1, 0xAA, 2, 0xC8, 3, 0x100, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_04_2[4] = {
    4, 0xB4, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_04_3[4] = {
    5, 0x100, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_04_4[8] = {
    6, 0x9A, 7, 0xB4, 8, 0x100, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_04_5[6] = {
    9, 0x40, 0xA, 0x200, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_05_1[4] = {
    1, 0x156, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_05_2[6] = {
    2, 0x100, 3, 0x114, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_05_3[4] = {
    4, 0x200, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_05_4[14] = {
    5, 0x124, 9, 0x3C, 0xA, 0x3C, 0xB, 0x3C,
    0xC, 0x3C, 6, 0x3C, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_05_5[2] = {
    0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_05_6[6] = {
    7, 0xD4, 8, 0x14A, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_07_1[2] = {
    0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_07_2[16] = {
    1, 0x78, 2, 0x5A, 3, 0xA0, 4, 0xC4,
    5, 0x64, 6, 0xC4, 7, 0x100, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_07_3[2] = {
    0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_07_4[2] = {
    0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_07_5[2] = {
    0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_07_6[4] = {
    8, 0x200, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_07_7[4] = {
    9, 0x200, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_07_8[2] = {
    0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_07_9[4] = {
    0xA, 0x200, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_07_10[10] = {
    0xB, 0xB0, 0xC, 0xE6, 0xD, 0x86, 0xE, 0x200,
    0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_08_1[8] = {
    1, 0xA0, 2, 0x118, 3, 0x300, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_08_2[4] = {
    4, 0x300, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_08_3[6] = {
    5, 0xB4, 6, 0x300, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_08_4[2] = {
    0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_09_1[4] = {
    1, 0x200, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_09_2[4] = {
    2, 0x340, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_09_3[2] = {
    0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_09_4[4] = {
    3, 0x300, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_09_5[6] = {
    4, 0xF0, 5, 0x300, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_11_1[6] = {
    1, 0xF0, 2, 0x200, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_11_2[4] = {
    3, 0x200, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_11_3[4] = {
    4, 0x200, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_11_4[2] = {
    0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_11_5[4] = {
    5, 0x200, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_11_6[4] = {
    6, 0x200, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_12_1[4] = {
    1, 0x300, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_12_2[10] = {
    2, 0x5A, 3, 0xB4, 4, 0x78, 5, 0x300,
    0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_12_3[4] = {
    6, 0x300, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_12_4[4] = {
    7, 0x300, 0, 0xFFFF,
};

/* provisional name */
const u16 txt_no_12_5[4] = {
    8, 0x300, 0, 0xFFFF,
};

const s16 effg0_col_tbl[7] = {
    8320, 8321, 8322, 8323, 8324, 8325, 8326,
};

const s16 effg0_pos_tbl[7][3] = {
    { 72, -6, -2 }, { 320, -6, -2 }, { 168, -6, -2 }, { 208, -6, -2 },
    { 248, -6, -2 }, { 16, -6, -3 }, { 120, -6, -2 },
};

const s16 effg0_flash_tbl[40][4] = {
    { 25, 101, 17, 32 }, { 42, 107, 37, 85 }, { 18, 116, 23, 35 }, { 18, 116, 20, 35 },
    { 18, 116, 28, 35 }, { 30, 90, 29, 30 }, { 23, 112, 10, 34 }, { 29, 32, 192, 17 },
    { 48, 192, 10, 64 }, { 192, 23, 80, 192 }, { 20, 96, 192, 34 }, { 128, 192, 24, 144 },
    { 192, 30, 160, 192 }, { 15, 192, 192, 24 }, { 208, 192, 27, 224 }, { 192, 25, 256, 192 },
    { 21, 272, 192, 10 }, { 288, 192, 34, 304 }, { 192, 18, 320, 192 }, { 23, 336, 192, 16 },
    { 352, 192, 28, 64 }, { 48, 29, 80, 48 }, { 27, 96, 48, 14 }, { 112, 48, 14, 128 },
    { 48, 29, 144, 48 }, { 15, 176, 48, 18 }, { 192, 48, 16, 208 }, { 48, 17, 224, 48 },
    { 29, 240, 48, 14 }, { 256, 48, 27, 272 }, { 48, 41, 304, 48 }, { 12, 96, 32, 24 },
    { 112, 32, 22, 128 }, { 32, 18, 144, 32 }, { 23, 160, 32, 16 }, { 176, 32, 28, 208 },
    { 32, 24, 224, 32 }, { 24, 240, 32, 23 }, { 256, 32, 37, 272 }, { 32, -1, 0, 0 },
};

const s16 effg0_name_tbl[53][3] = {
    { 22, 80, 208 }, { 14, 96, 208 }, { 27, 112, 208 }, { 27, 128, 208 },
    { 34, 144, 208 }, { 33, 176, 208 }, { 42, 192, 208 }, { 22, 208, 208 },
    { 10, 224, 208 }, { 28, 240, 208 }, { 10, 272, 208 }, { 23, 288, 208 },
    { 13, 304, 208 }, { 10, 64, 192 }, { 17, 96, 192 }, { 10, 112, 192 },
    { 25, 128, 192 }, { 25, 144, 192 }, { 34, 160, 192 }, { 23, 192, 192 },
    { 14, 208, 192 }, { 32, 224, 192 }, { 34, 256, 192 }, { 14, 272, 192 },
    { 10, 288, 192 }, { 27, 304, 192 }, { 37, 320, 192 }, { 28, 64, 48 },
    { 29, 80, 48 }, { 27, 96, 48 }, { 14, 112, 48 }, { 14, 128, 48 },
    { 29, 144, 48 }, { 15, 176, 48 }, { 18, 192, 48 }, { 16, 208, 48 },
    { 17, 224, 48 }, { 29, 240, 48 }, { 14, 256, 48 }, { 27, 272, 48 },
    { 41, 304, 48 }, { 12, 96, 32 }, { 24, 112, 32 }, { 22, 128, 32 },
    { 18, 144, 32 }, { 23, 160, 32 }, { 16, 176, 32 }, { 28, 208, 32 },
    { 24, 224, 32 }, { 24, 240, 32 }, { 23, 256, 32 }, { 37, 272, 32 },
    { -1, 0, 0 },
};

/* provisional name */
const s16 effg0_name_tbl2[44][3] = {
    { 10, 64, 208 }, { 17, 96, 208 }, { 10, 112, 208 }, { 25, 128, 208 },
    { 25, 144, 208 }, { 34, 160, 208 }, { 23, 192, 208 }, { 14, 208, 208 },
    { 32, 224, 208 }, { 34, 256, 208 }, { 14, 272, 208 }, { 10, 288, 208 },
    { 27, 304, 208 }, { 37, 320, 208 }, { 1, 144, 192 }, { 9, 176, 192 },
    { 9, 208, 192 }, { 7, 240, 192 }, { 28, 64, 48 }, { 29, 80, 48 },
    { 27, 96, 48 }, { 14, 112, 48 }, { 14, 128, 48 }, { 29, 144, 48 },
    { 15, 176, 48 }, { 18, 192, 48 }, { 16, 208, 48 }, { 17, 224, 48 },
    { 29, 240, 48 }, { 14, 256, 48 }, { 27, 272, 48 }, { 41, 304, 48 },
    { 12, 96, 32 }, { 24, 112, 32 }, { 22, 128, 32 }, { 18, 144, 32 },
    { 23, 160, 32 }, { 16, 176, 32 }, { 28, 208, 32 }, { 24, 224, 32 },
    { 24, 240, 32 }, { 23, 256, 32 }, { 37, 272, 32 }, { -1, 0, 0 },
};
