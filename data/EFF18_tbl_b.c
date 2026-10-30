/*
 * EFF18_TBL_B.C  breakable stage object part tables
 *
 * eff21_data_tbl_00 gives the pattern, x, y, priority and flip of the three parts of effect
 * 21, and eff21_sp_tbl their speeds and accelerations when they fly off; read by EFF21.C, the
 * breakable stage parts. eff23_data_tbl holds the settings of the three pieces that fly off
 * when the effect 23 object breaks; read by EFF23.C, the breakable stage object.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff21_data_tbl_00[];
extern const s32 eff21_sp_tbl[][4];
extern const s16 eff23_data_tbl[];

const s16 eff21_data_tbl_00[16] = {
    0, 696, 64, 74, 0, 2, 752, 84, 74, 0, 4, 752, 63, 74, 1, 0,
};

const s32 eff21_sp_tbl[3][4] = {
    { 0, 0, -0x1000, 0x480 }, { 0, 0, -0x1800, 0x400 }, { 0x10000, 0, 0x2400, 0x480 },
};

const s16 eff23_data_tbl[34] = {
    8, 752, 104, 2, 0x8000, 0, 12288, 8,
    0, -1, 0x8000, 9, 752, 96, 3, 0x8000,
    0, 12288, 3, 0, -1, 0x8000, 11, 672,
    80, 4, 0x8000, 0, 16384, 5, 0x8000, -1,
    0x8000, 0,
};
