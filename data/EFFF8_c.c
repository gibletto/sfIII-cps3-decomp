/*
 * EFFF8_C.C  follower controller and follower part tables
 *
 * effG1_x_offsets gives, by facing, the x offsets of the four follow points beside the player;
 * read by EFFG1.C, the follower controller, whose init is empty. effG2_char_tbl gives each
 * part its pattern while the player is not hit, while hit or thrown, and at the end;
 * effG2_speed_tbl and effG2_distance_tbl its running speed by distance to the follow point;
 * and effG2_fall_tbl its speeds when the parts fall away on stage 8. Read by EFFG2.C, the
 * follower parts.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effG1_x_offsets[][4];
extern const s16 effG2_fall_tbl[][2];
extern const s16 effG2_char_tbl[][3];
extern const s16 effG2_speed_tbl[][4][8];
extern const s16 effG2_distance_tbl[][8];

const s16 effG1_x_offsets[2][4] = {
    { 36, 12, -12, -12 }, { -36, -12, 12, 12 },
};

const s16 effG2_fall_tbl[4][2] = {
    { 512, -64 }, { 512, -64 }, { 512, -64 }, { 512, -64 },
};

/*
 * One row per part (type): pattern while the player is not hit, pattern while hit or
 * thrown, and the pattern played once at the end.
 */
const s16 effG2_char_tbl[4][3] = {
    { 36, 37, 159 }, { 38, 39, 160 }, { 40, 41, 161 }, { 42, 43, 162 },
};

const s16 effG2_speed_tbl[3][4][8] = {
    {
        { 64, 128, 256, 448, 704, 1024, 1408, 1856 },
        { 48, 96, 208, 384, 624, 928, 1296, 1728 },
        { 32, 64, 160, 320, 544, 832, 1184, 1600 },
        { 16, 32, 112, 256, 464, 736, 1072, 1472 },
    },
    {
        { 64, 128, 192, 256, 320, 384, 448, 512 },
        { 56, 116, 176, 236, 296, 356, 416, 476 },
        { 48, 104, 160, 216, 272, 328, 384, 440 },
        { 40, 92, 144, 196, 248, 300, 352, 404 },
    },
    {
        { 128, 256, 384, 640, 896, 1152, 1408, 1664 },
        { 136, 272, 408, 672, 936, 1200, 1464, 1728 },
        { 144, 288, 432, 704, 976, 1248, 1520, 1792 },
        { 152, 304, 456, 736, 1016, 1296, 1576, 1856 },
    },
};

const s16 effG2_distance_tbl[4][8] = {
    { 4, 10, 22, 40, 64, 94, 130, 172 }, { 6, 11, 21, 36, 56, 81, 111, 146 },
    { 8, 12, 20, 32, 48, 68, 92, 120 }, { 10, 13, 19, 28, 40, 55, 73, 94 },
};
