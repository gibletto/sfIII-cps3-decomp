/*
 * EFFF2.C  flying objects of an ending scene
 *
 * efff2_data_tbl gives the settings (priority, pattern) of each of the eight objects,
 * efff2_speed_tbl their speeds and accelerations in each of the three flight stages, and
 * efff2_pos_tbl the position each starts again from. Read by EFFF2_CODE.C, the flying objects
 * of an ending scene.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 efff2_pos_tbl[][2];
extern const s32 efff2_speed_tbl[][8][4];
extern const s16 efff2_data_tbl[][3];

const s16 efff2_pos_tbl[8][2] = {
    { 160, 144 }, { 272, 96 }, { 0, 208 }, { 272, 176 }, { 304, 64 }, { 320, 240 }, { 96, 208 }, { 320, 176 },
};

const s32 efff2_speed_tbl[3][8][4] = {
    {
        { 0x66200, 0x800, -0x1400, 0 }, { 0x4600, 0x2C0, 0, 0x180 },
        { 0x38800, 0, -0x1800, -0x100 }, { 0x28A00, 0x2E0, -0x3D00, -0x80 },
        { 0x66200, 0x400, 0x1400, 0x200 }, { 0x54600, 0x2C0, 0, 0x180 },
        { 0x8800, 0, -0x1800, -0x200 }, { 0x43A00, 0, -0x3D00, 0 },
    },
    {
        { 0x46200, 0x400, -0x1400, 0 }, { 0x41600, 0, 0x1000, 0x80 },
        { 0x38800, 0, -0x3000, -0x100 }, { 0x56000, 0, -0x2000, -0x80 },
        { 0x36200, 0x400, 0x1400, 0 }, { 0x83600, 0x380, 0x1000, 0 },
        { 0x33800, 0x180, -0x3000, -0x100 }, { 0x61A00, 0, -0x2000, 0 },
    },
    {
        { 0x28000, 0, 0, 0 }, { 0x88600, 0, 0x2000, 0 },
        { 0x36800, 0, -0x4000, -0x80 }, { 0x32A00, 0, -0x1800, -0x280 },
        { 0x28200, 0, 0x1000, 0x200 }, { 0x88600, 0x1C0, 0x1800, 0 },
        { 0x73800, 0x180, -0x3000, -0x200 }, { 0x43A00, 0x100, -0x2000, -0x280 },
    },
};

const s16 efff2_data_tbl[8][3] = {
    { 40, 4, 60 }, { 40, 6, 60 }, { 85, 3, 60 }, { 85, 5, 60 },
    { 40, 4, 60 }, { 40, 6, 60 }, { 85, 3, 60 }, { 85, 5, 60 },
};
