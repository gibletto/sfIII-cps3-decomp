/*
 * EFF09_TBL.C  tables read by EFF09.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff09_data2[][8];
extern const s32 eff09_2000_data[][4];
extern const s32 eff09_add_tbl0[][2];
extern const s32 eff09_add_tbl1[][2];
extern const s32 eff09_add_tbl2[][2];
extern const s16 sean_ball_hit[];

const s16 eff09_data2[10][8] = {
    { 1, 0, 0, 4, 1, 25, 1, 0 }, { 2, 0, -34, 153, -10, 26, 1, 0 },
    { 3, 6, 48, 240, -1, 27, 1, 0 }, { 4, 0, 48, -4, -10, 28, 1, 0 },
    { 5, 0, 10, 96, -20, 46, 1, 0 }, { 6, 0, 0, 0, -20, 47, 1, 0 },
    { 7, 0, 0, 80, -10, 43, 1, 0 }, { 0, 0, -38, 84, -2, 41, 1, 0 },
    { 8, 0, 0, 0, -2, 55, 1, 0 }, { 8, 0, 0, 0, -2, 56, 1, 0 },
};

const s32 eff09_2000_data[2][4] = {
    { -65536, 327680, -4096, -24576 }, { -327680, 393216, -3072, -24576 },
};

const s32 eff09_add_tbl0[2][2] = {
    { 2048, -2048 }, { 2048, -4096 },
};

const s32 eff09_add_tbl1[2][2] = {
    { -2048, 2048 }, { -4608, 4096 },
};

const s32 eff09_add_tbl2[2][2] = {
    { -2048, 2048 }, { -4096, 4608 },
};

const s16 sean_ball_hit[4] = {
    -16, 32, -11, 22,
};
