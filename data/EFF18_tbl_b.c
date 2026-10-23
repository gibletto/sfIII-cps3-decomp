/*
 * EFF18_TBL_B.C  tables read by EFF21.c and EFF23.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff21_data_adrs_0[];
extern const s32 eff21_sp_tbl[][4];
extern const s16 eff23_data_tbl[];

const s16 eff21_data_adrs_0[16] = {
    0, 696, 64, 74, 0, 2, 752, 84, 74, 0, 4, 752, 63, 74, 1, 0,
};

const s32 eff21_sp_tbl[3][4] = {
    { 0, 0, -4096, 1152 }, { 0, 0, -6144, 1024 }, { 65536, 0, 9216, 1152 },
};

const s16 eff23_data_tbl[34] = {
    8, 752, 104, 2, -32768, 0, 12288, 8,
    0, -1, -32768, 9, 752, 96, 3, -32768,
    0, 12288, 3, 0, -1, -32768, 11, 672,
    80, 4, -32768, 0, 16384, 5, -32768, -1,
    -32768, 0,
};
