/*
 * BG000_TBL_B.C  the BG cell lists: per stage and layer, the cells bg000.c rewrites, as bg_rewrite_cell_tbl,
 * bg_rewrite_cell_tbl_8 and bg_etc_cell_tbl (work RAM) point at them; a list is named after the first entry that
 * points at it
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const HUD_CELL end_1300_panel1[];
extern const HUD_CELL bg_rewrite_cells_00_1[];
extern const HUD_CELL bg_rewrite_cells_00_0[];
extern const HUD_CELL bg_rewrite_cells_00_3[];
extern const HUD_CELL bg_rewrite_cells_01_0[];
extern const HUD_CELL bg_rewrite_cells_01_1[];
extern const HUD_CELL bg_rewrite_cells_01_2[];
extern const HUD_CELL bg_rewrite_cells_02_0[];
extern const HUD_CELL bg_rewrite_cells_02_1[];
extern const HUD_CELL bg_rewrite_cells_03_0[];
extern const HUD_CELL bg_rewrite_cells_03_1[];
extern const HUD_CELL bg_rewrite_cells_03_2[];
extern const HUD_CELL bg_rewrite8_cells_03_0[];
extern const HUD_CELL bg_rewrite8_cells_03_1[];
extern const HUD_CELL bg_rewrite_cells_04_0[];
extern const HUD_CELL bg_rewrite_cells_04_1[];
extern const HUD_CELL bg_rewrite_cells_04_2[];
extern const HUD_CELL bg_rewrite_cells_05_0[];
extern const HUD_CELL bg_rewrite_cells_05_1[];
extern const HUD_CELL bg_rewrite_cells_05_2[];
extern const HUD_CELL bg_rewrite_cells_06_0[];
extern const HUD_CELL bg_rewrite_cells_06_1[];
extern const HUD_CELL bg_rewrite_cells_07_0[];
extern const HUD_CELL bg_rewrite_cells_07_1[];
extern const HUD_CELL bg_rewrite_cells_07_2[];
extern const HUD_CELL bg_rewrite_cells_08_0[];
extern const HUD_CELL bg_rewrite_cells_08_1[];
extern const HUD_CELL bg_rewrite_cells_09_0[];
extern const HUD_CELL bg_rewrite_cells_09_1[];
extern const HUD_CELL bg_rewrite_cells_09_2[];
extern const HUD_CELL bg_rewrite_cells_10_0[];
extern const HUD_CELL bg_rewrite_cells_10_1[];
extern const HUD_CELL bg_rewrite_cells_11_0[];
extern const HUD_CELL bg_rewrite_cells_11_1[];
extern const HUD_CELL bg_rewrite_cells_12_2[];
extern const HUD_CELL bg_rewrite_cells_11_2[];
extern const HUD_CELL bg_rewrite8_cells_11_1[];
extern const HUD_CELL bg_rewrite_cells_14_0[];
extern const HUD_CELL bg_rewrite_cells_14_1[];
extern const HUD_CELL bg_rewrite_cells_15_0[];
extern const HUD_CELL bg_rewrite_cells_15_1[];
extern const HUD_CELL bg_rewrite_cells_16_0[];
extern const HUD_CELL bg_rewrite_cells_16_1[];
extern const HUD_CELL bg_rewrite_cells_16_2[];
extern const HUD_CELL bg_rewrite_cells_19_0[];
extern const HUD_CELL bg_rewrite_cells_20_0[];
extern const HUD_CELL bg_rewrite_cells_20_1[];
extern const HUD_CELL bg_rewrite_cells_20_2[];
extern const TILEREQ bg_etc_cells_0[];
extern const TILEREQ bg_etc_cells_1[];
extern const TILEREQ bg_etc_cells_2[];
extern const TILEREQ bg_etc_cells_3[];
extern const TILEREQ bg_etc_cells_4[];

/* nothing in the program refers to it */
/* provisional name */
const HUD_CELL end_1300_panel1[8] = {
    { 8192, 0 }, { 8256, 0 }, { 8320, 0 }, { 8384, 0 },
    { 12288, 16 }, { 12352, 17 }, { 12416, 18 }, { 12480, 19 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_00_1[8] = {
    { 8192, 0 }, { 8256, 0 }, { 8320, 0 }, { 8384, 0 },
    { 12288, 8 }, { 12352, 9 }, { 12416, 10 }, { 12480, 11 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_00_0[8] = {
    { 8192, 4 }, { 8256, 5 }, { 8320, 6 }, { 8384, 7 },
    { 12288, 60 }, { 12352, 61 }, { 12416, 62 }, { 12480, 63 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_00_3[1] = {
    { 0, 4 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_01_0[4] = {
    { 8320, 4 }, { 8384, 5 }, { 12416, 12 }, { 12480, 13 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_01_1[8] = {
    { 8192, 0 }, { 8256, 1 }, { 8320, 2 }, { 8384, 3 },
    { 12288, 8 }, { 12352, 9 }, { 12416, 10 }, { 12480, 11 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_01_2[2] = {
    { 8320, 6 }, { 8384, 7 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_02_0[8] = {
    { 8192, 4 }, { 8256, 5 }, { 8320, 6 }, { 8384, 7 },
    { 12288, 12 }, { 12352, 13 }, { 12416, 14 }, { 12480, 15 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_02_1[8] = {
    { 8192, 0 }, { 8256, 1 }, { 8320, 2 }, { 8384, 3 },
    { 12288, 8 }, { 12352, 9 }, { 12416, 10 }, { 12480, 11 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_03_0[6] = {
    { 8224, 4 }, { 8288, 5 }, { 8352, 6 }, { 12320, 20 },
    { 12384, 21 }, { 12448, 22 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_03_1[8] = {
    { 8192, 7 }, { 8256, 8 }, { 8320, 9 }, { 8384, 10 },
    { 12288, 23 }, { 12352, 24 }, { 12416, 25 }, { 12480, 26 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_03_2[6] = {
    { 8224, 1 }, { 8288, 2 }, { 8352, 3 }, { 12320, 17 },
    { 12384, 18 }, { 12448, 19 },
};

/* provisional name */
const HUD_CELL bg_rewrite8_cells_03_0[6] = {
    { 8224, 4 }, { 8288, 5 }, { 8352, 6 }, { 12320, 27 },
    { 12384, 21 }, { 12448, 28 },
};

/* provisional name */
const HUD_CELL bg_rewrite8_cells_03_1[8] = {
    { 8192, 7 }, { 8256, 8 }, { 8320, 9 }, { 8384, 11 },
    { 12288, 12 }, { 12352, 13 }, { 12416, 25 }, { 12480, 26 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_04_0[8] = {
    { 8192, 5 }, { 8256, 12 }, { 8320, 13 }, { 8384, 5 },
    { 12288, 5 }, { 12352, 18 }, { 12416, 19 }, { 12480, 5 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_04_1[8] = {
    { 8192, 1 }, { 8256, 2 }, { 8320, 3 }, { 8384, 4 },
    { 12288, 7 }, { 12352, 8 }, { 12416, 9 }, { 12480, 10 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_04_2[8] = {
    { 8192, 14 }, { 8256, 15 }, { 8320, 16 }, { 8384, 17 },
    { 12288, 20 }, { 12352, 21 }, { 12416, 22 }, { 12480, 23 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_05_0[6] = {
    { 8224, 4 }, { 8288, 5 }, { 8352, 6 }, { 12320, 12 },
    { 12384, 13 }, { 12448, 14 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_05_1[6] = {
    { 8224, 16 }, { 8288, 17 }, { 8352, 18 }, { 12320, 24 },
    { 12384, 25 }, { 12448, 26 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_05_2[6] = {
    { 8224, 0 }, { 8288, 1 }, { 8352, 2 }, { 12320, 8 },
    { 12384, 9 }, { 12448, 10 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_06_0[6] = {
    { 8224, 0 }, { 8288, 1 }, { 8352, 2 }, { 12320, 8 },
    { 12384, 9 }, { 12448, 10 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_06_1[6] = {
    { 8224, 4 }, { 8288, 5 }, { 8352, 6 }, { 12320, 12 },
    { 12384, 13 }, { 12448, 14 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_07_0[8] = {
    { 8192, 48 }, { 8256, 49 }, { 8320, 50 }, { 8384, 51 },
    { 12288, 56 }, { 12352, 57 }, { 12416, 58 }, { 12480, 59 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_07_1[8] = {
    { 8192, 0 }, { 8224, 0 }, { 8288, 0 }, { 8352, 0 },
    { 12288, 0 }, { 12320, 2 }, { 12384, 76 }, { 12448, 77 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_07_2[8] = {
    { 8192, 8 }, { 8256, 9 }, { 8320, 10 }, { 8384, 11 }, { 12288, 0 }, { 12352, 6 }, { 12416, 7 }, { 12480, 0 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_08_0[8] = {
    { 8192, 8 }, { 8256, 9 }, { 8320, 10 }, { 8384, 11 }, { 12288, 0 }, { 12352, 6 }, { 12416, 7 }, { 12480, 0 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_08_1[8] = {
    { 8192, 0 }, { 8224, 0 }, { 8288, 0 }, { 8352, 0 }, { 12288, 0 }, { 12320, 2 }, { 12384, 3 }, { 12448, 4 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_09_0[8] = {
    { 8192, 0 }, { 8256, 1 }, { 8320, 2 }, { 8384, 3 },
    { 12288, 8 }, { 12352, 9 }, { 12416, 10 }, { 12480, 11 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_09_1[8] = {
    { 8192, 4 }, { 8256, 5 }, { 8320, 6 }, { 8384, 7 },
    { 12288, 12 }, { 12352, 13 }, { 12416, 14 }, { 12480, 15 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_09_2[4] = {
    { 12288, 16 }, { 12352, 17 }, { 12416, 18 }, { 12480, 19 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_10_0[6] = {
    { 8224, 5 }, { 8288, 6 }, { 8352, 7 }, { 12320, 13 },
    { 12384, 14 }, { 12448, 15 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_10_1[8] = {
    { 8192, 1 }, { 8256, 2 }, { 8320, 3 }, { 8384, 4 },
    { 12288, 9 }, { 12352, 10 }, { 12416, 11 }, { 12480, 12 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_11_0[6] = {
    { 8224, 8 }, { 8288, 0 }, { 8352, 10 }, { 12320, 21 },
    { 12384, 22 }, { 12448, 23 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_11_1[8] = {
    { 8192, 1 }, { 8256, 2 }, { 8320, 3 }, { 8384, 4 },
    { 12288, 14 }, { 12352, 15 }, { 12416, 16 }, { 12480, 17 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_12_2[6] = {
    { 8224, 5 }, { 8288, 6 }, { 8352, 7 }, { 12320, 18 },
    { 12384, 19 }, { 12448, 20 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_11_2[6] = {
    { 8224, 33 }, { 8288, 34 }, { 8352, 35 }, { 12320, 36 },
    { 12384, 37 }, { 12448, 38 },
};

/* provisional name */
const HUD_CELL bg_rewrite8_cells_11_1[8] = {
    { 8192, 1 }, { 8256, 2 }, { 8320, 3 }, { 8384, 4 },
    { 12288, 14 }, { 12352, 15 }, { 12416, 13 }, { 12480, 9 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_14_0[10] = {
    { 64, 8 }, { 128, 9 }, { 8192, 0 }, { 8256, 1 }, { 8320, 2 }, { 8384, 3 }, { 12288, 4 }, { 12352, 5 },
    { 12416, 6 }, { 12480, 7 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_14_1[1] = {
    { 0, 0 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_15_0[6] = {
    { 8224, 0 }, { 8288, 1 }, { 8352, 2 }, { 12320, 8 },
    { 12384, 9 }, { 12448, 10 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_15_1[6] = {
    { 8224, 3 }, { 8288, 4 }, { 8352, 5 }, { 12320, 6 },
    { 12384, 7 }, { 12448, 14 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_16_0[8] = {
    { 8192, 0 }, { 8256, 0 }, { 8320, 0 }, { 8384, 0 }, { 12288, 5 }, { 12352, 6 }, { 12416, 7 }, { 12480, 8 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_16_1[8] = {
    { 8192, 9 }, { 8256, 10 }, { 8320, 11 }, { 8384, 12 },
    { 12288, 13 }, { 12352, 14 }, { 12416, 15 }, { 12480, 16 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_16_2[8] = {
    { 8192, 0 }, { 8256, 0 }, { 8320, 0 }, { 8384, 0 }, { 12288, 1 }, { 12352, 2 }, { 12416, 3 }, { 12480, 4 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_19_0[4] = {
    { 12288, 1 }, { 12352, 2 }, { 12416, 3 }, { 12480, 4 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_20_0[2] = {
    { 8192, 0 }, { 8256, 1 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_20_1[2] = {
    { 8192, 0 }, { 8256, 1 },
};

/* provisional name */
const HUD_CELL bg_rewrite_cells_20_2[10] = {
    { 8192, 0 }, { 8256, 1 }, { 4096, 0 }, { 4160, 0 }, { 4224, 1 }, { 4288, 1 }, { 12288, 2 }, { 12352, 2 },
    { 12416, 3 }, { 12480, 3 },
};

/* provisional name */
const TILEREQ bg_etc_cells_0[2] = {
    { 64, 12352, 1 }, { 64, 12416, 2 },
};

/* provisional name */
const TILEREQ bg_etc_cells_1[4] = {
    { 126, 12288, 1 }, { 126, 12352, 2 }, { 126, 12416, 3 }, { 126, 12480, 4 },
};

/* provisional name */
const TILEREQ bg_etc_cells_2[2] = {
    { 64, 12352, 3 }, { 64, 12416, 4 },
};

/* provisional name */
const TILEREQ bg_etc_cells_3[2] = {
    { 64, 12352, 1 }, { 64, 12416, 2 },
};

/* provisional name */
const TILEREQ bg_etc_cells_4[2] = {
    { 64, 12352, 3 }, { 64, 12416, 4 },
};
