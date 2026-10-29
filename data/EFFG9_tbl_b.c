/*
 * EFFG9_TBL_B.C  ending objects that fly in
 *
 * effh1_data_tbl gives the pattern, start x, y and priority of each of the four objects, and
 * effh1_speed_tbl their x speed and acceleration and y speed and acceleration. Read by
 * EFFH1.C, the ending objects that fly in when the scroll arrives.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effh1_data_tbl[][4];
extern const s32 effh1_speed_tbl[][4];

const s16 effh1_data_tbl[4][4] = {
    { 1, 296, 160, 72 }, { 2, 312, 144, 70 }, { 3, 328, 116, 68 }, { 4, 360, 80, 66 },
};

const s32 effh1_speed_tbl[4][4] = {
    { 0x18000, 0x400, -0x10000, 0x2800 }, { 0x28000, 0x400, -0x10000, 0x2800 },
    { 0x38000, 0x800, -0x10000, 0x2A00 }, { 0x48000, 0x800, -0x10000, 0x3000 },
};
