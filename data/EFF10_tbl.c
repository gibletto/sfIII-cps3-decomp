/*
 * EFF10_TBL.C  character scene objects and animated background map tables
 *
 * scr_obj_num10 starts with the number of objects of each of the four types, followed by the
 * rows of each type (x offset from the owner, y position, animation number) reached through
 * scr_obj_data10; read by EFF10.C, the character scene objects. eff11_tile_tbl gives the tiles
 * (map offset and cell) written into each of the four map pages, eff11_frame_tbl the page, y
 * offset and time of each frame, and eff11_anime_tbl each animation's repeat count and frame
 * set; read by EFF11.C, the animated background map of stage 07. eff12_tile_tbl and
 * eff12_frame_tbl do the same for the two pages and four frames of EFF12.C, the animated BG 0
 * map.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 scr_obj_num10[];
extern const EFF11_ROW eff11_tile_tbl[];
extern const EFF11_FRAME eff11_frame_tbl[][4];
extern const EFF11_ANIME eff11_anime_tbl[];
extern const EFF12_ROW eff12_tile_tbl[];
extern const EFF12_FRAME eff12_frame_tbl[];

const s16 scr_obj_num10[30] = {
    4, 3, 1, 0, -64, 100, 8, -71, 42, 9, 26, 96, 10, 70, 26, 11,
    16, 100, 10, -80, 48, 9, 70, 26, 11, -61, 50, 12, 0, 0,
};

const EFF11_ROW eff11_tile_tbl[4] = {
    {
        {
            { 0, 16 }, { 64, 17 }, { 128, 18 }, { 192, 19 },
            { 4096, 24 }, { 4160, 25 }, { 4224, 26 }, { 4288, 27 },
            { 8192, 20 }, { 8256, 21 }, { 8320, 22 }, { 8384, 23 },
            { 12288, 28 }, { 12352, 29 }, { 12416, 30 }, { 12480, 31 },
        },
    },
    {
        {
            { 0, 32 }, { 64, 33 }, { 128, 34 }, { 192, 35 },
            { 4096, 40 }, { 4160, 41 }, { 4224, 42 }, { 4288, 43 },
            { 8192, 36 }, { 8256, 37 }, { 8320, 38 }, { 8384, 39 },
            { 12288, 44 }, { 12352, 45 }, { 12416, 46 }, { 12480, 47 },
        },
    },
    {
        {
            { 0, 48 }, { 64, 49 }, { 128, 50 }, { 192, 51 },
            { 4096, 56 }, { 4160, 57 }, { 4224, 58 }, { 4288, 59 },
            { 8192, 52 }, { 8256, 53 }, { 8320, 54 }, { 8384, 55 },
            { 12288, 60 }, { 12352, 61 }, { 12416, 62 }, { 12480, 63 },
        },
    },
    {
        {
            { 0, 64 }, { 64, 65 }, { 128, 66 }, { 192, 67 },
            { 4096, 72 }, { 4160, 73 }, { 4224, 74 }, { 4288, 75 },
            { 8192, 68 }, { 8256, 69 }, { 8320, 70 }, { 8384, 71 },
            { 12288, 12 }, { 12352, 13 }, { 12416, 14 }, { 12480, 15 },
        },
    },
};

const EFF11_FRAME eff11_frame_tbl[8][4] = {
    { { 0, 512, 3 }, { 0, 0, 3 }, { 1, 512, 3 }, { 1, 0, 3 } },
    { { 0, 512, 4 }, { 0, 0, 4 }, { 1, 512, 4 }, { 1, 0, 4 } },
    { { 0, 512, 7 }, { 0, 0, 7 }, { 1, 512, 7 }, { 1, 0, 7 } },
    { { 0, 512, 7 }, { 0, 0, 7 }, { 1, 512, 7 }, { 1, 0, 7 } },
    { { 2, 512, 4 }, { 2, 0, 4 }, { 3, 512, 4 }, { 3, 0, 4 } },
    { { 2, 512, 5 }, { 2, 0, 5 }, { 3, 512, 5 }, { 3, 0, 5 } },
    { { 2, 512, 6 }, { 2, 0, 6 }, { 3, 512, 6 }, { 3, 0, 6 } },
    { { 2, 512, 7 }, { 2, 0, 7 }, { 3, 512, 7 }, { 3, 0, 7 } },
};

const EFF11_ANIME eff11_anime_tbl[14] = {
    { 8, 1 }, { 20, 2 }, { 20, 3 }, { 24, 4 }, { 20, 5 }, { 20, 6 }, { 20, 7 }, { 20, 6 },
    { 20, 5 }, { 24, 4 }, { 20, 3 }, { 20, 2 }, { 20, 1 }, { 20, 0 },
};

const EFF12_ROW eff12_tile_tbl[2] = {
    {
        {
            { 0, 4 }, { 64, 5 }, { 128, 6 }, { 192, 7 },
            { 4096, 56 }, { 4160, 57 }, { 4224, 58 }, { 4288, 59 },
            { 8192, 4 }, { 8256, 5 }, { 8320, 6 }, { 8384, 7 },
            { 12288, 60 }, { 12352, 61 }, { 12416, 62 }, { 12480, 63 },
        },
    },
    {
        {
            { 0, 4 }, { 64, 5 }, { 128, 6 }, { 192, 7 },
            { 4096, 12 }, { 4160, 13 }, { 4224, 14 }, { 4288, 15 },
            { 8192, 4 }, { 8256, 5 }, { 8320, 6 }, { 8384, 7 },
            { 12288, 52 }, { 12352, 53 }, { 12416, 54 }, { 12480, 55 },
        },
    },
};

const EFF12_FRAME eff12_frame_tbl[4] = {
    { 0, 512, 0xC }, { 0, 0, 0xC }, { 1, 512, 0xC }, { 1, 0, 0xC },
};
