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
    { 98304, 1024, -65536, 10240 }, { 163840, 1024, -65536, 10240 },
    { 229376, 2048, -65536, 10752 }, { 294912, 2048, -65536, 12288 },
};
