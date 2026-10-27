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
        { 418304, 2048, -5120, 0 }, { 17920, 704, 0, 384 },
        { 231424, 0, -6144, -256 }, { 166400, 736, -15616, -128 },
        { 418304, 1024, 5120, 512 }, { 345600, 704, 0, 384 },
        { 34816, 0, -6144, -512 }, { 276992, 0, -15616, 0 },
    },
    {
        { 287232, 1024, -5120, 0 }, { 267776, 0, 4096, 128 },
        { 231424, 0, -12288, -256 }, { 352256, 0, -8192, -128 },
        { 221696, 1024, 5120, 0 }, { 538112, 896, 4096, 0 },
        { 210944, 384, -12288, -256 }, { 399872, 0, -8192, 0 },
    },
    {
        { 163840, 0, 0, 0 }, { 558592, 0, 8192, 0 },
        { 223232, 0, -16384, -128 }, { 207360, 0, -6144, -640 },
        { 164352, 0, 4096, 512 }, { 558592, 448, 6144, 0 },
        { 473088, 384, -12288, -512 }, { 276992, 256, -8192, -640 },
    },
};

const s16 efff2_data_tbl[8][3] = {
    { 40, 4, 60 }, { 40, 6, 60 }, { 85, 3, 60 }, { 85, 5, 60 },
    { 40, 4, 60 }, { 40, 6, 60 }, { 85, 3, 60 }, { 85, 5, 60 },
};
