/*
 * EFF41_TBL_B.C  animated stage object, blinking mark and background page tables
 *
 * eff44_obj_data holds the 14 objects of effect 44 (family, colour, position, priority,
 * animation, animate flag and line-scroll sync); read by EFF44.C. eff46_char_tbl is the eight
 * patterns effect 46 picks from at random; read by EFF46.C. eff47_init_data gives the colour,
 * position and priority of the five blinking marks and eff47_timer_tbl their cell times; read
 * by EFF47.C. eff48_tile_tbl0 and eff48_tile_tbl1 are the tiles written into the BG 0 and BG 1
 * pages (eff48_tile_jp_tbl1 in place of eff48_tile_tbl1 for Country 8), and eff48_frame_tbl0
 * and eff48_frame_tbl1 the 20 frames (page, y offset, time) of each type; read by EFF48.C, the
 * animated background pages.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff44_obj_data[][9];
extern const s16 eff46_char_tbl[];
extern const s16 eff47_init_data[][4];
extern const u8 eff47_timer_tbl[];
extern const EFF48_ROW eff48_tile_tbl0[];
extern const s32 eff48_tile_tbl1[][16];
extern const s32 eff48_tile_jp_tbl1[][16];
extern const EFF48_FRAME eff48_frame_tbl0[];
extern const EFF48_FRAME eff48_frame_tbl1[];

const s16 eff44_obj_data[14][9] = {
    { 0, 3, 16, 512, 80, 100, 6, 1, 0 }, { 0, 3, 16, 512, 96, 100, 7, 0, 0 },
    { 1, 2, 8208, 260, 320, 100, 0, 0, 0 }, { 0, 2, 8208, 528, 8, 95, 1, 0, 0 },
    { 0, 5, 8208, 512, 124, 104, 2, 0, 0 }, { 0, 5, 16, 512, 112, 103, 3, 0, 0 },
    { 0, 2, 8208, 326, 252, 99, 8, 0, 0 }, { 0, 2, 8208, 398, 288, 101, 9, 0, 0 },
    { 0, 2, 8208, 144, 112, 93, 11, 0, 0 }, { 0, 2, 8208, 272, 112, 93, 12, 0, 0 },
    { 0, 2, 8208, 352, 112, 93, 13, 0, 0 }, { 0, 2, 8208, 624, 112, 93, 14, 0, 0 },
    { 0, 2, 8208, 720, 112, 93, 15, 0, 0 }, { 1, 2, 8208, 832, 112, 93, 16, 0, 0 },
};

const s16 eff46_char_tbl[8] = {
    2, 1, 4, 6, 3, 1, 5, 2,
};

const s16 eff47_init_data[5][4] = {
    { 8256, 288, 96, 84 }, { 8256, 416, 64, 84 }, { 64, 480, 64, 84 }, { 64, 544, 80, 84 },
    { 64, 672, 112, 84 },
};

const u8 eff47_timer_tbl[12] = {
    8, 8, 8, 8, 8, 8, 8, 8, 8, 0xF1, 0xFF, 0xF0,
};

const EFF48_ROW eff48_tile_tbl0[2] = {
    {
        {
            { 32, 8 }, { 96, 0 }, { 160, 10 }, { 4128, 21 },
            { 4192, 22 }, { 4256, 23 }, { 8224, 11 }, { 8288, 0 },
            { 8352, 10 }, { 12320, 24 }, { 12384, 22 }, { 12448, 23 },
        },
    },
    {
        {
            { 32, 12 }, { 96, 0 }, { 160, 10 }, { 4128, 25 },
            { 4192, 22 }, { 4256, 23 }, { 8224, 32 }, { 8288, 0 },
            { 8352, 10 }, { 12320, 45 }, { 12384, 22 }, { 12448, 23 },
        },
    },
};

const s32 eff48_tile_tbl1[4][16] = {
    { 8192, 1, 8256, 2, 8320, 3, 8384, 4, 12288, 14, 12352, 15, 12416, 16, 12480, 17 },
    { 8192, 26, 8256, 27, 8320, 3, 8384, 4, 12288, 39, 12352, 40, 12416, 16, 12480, 17 },
    { 8192, 28, 8256, 29, 8320, 3, 8384, 4, 12288, 41, 12352, 42, 12416, 16, 12480, 17 },
    { 8192, 30, 8256, 31, 8320, 3, 8384, 4, 12288, 43, 12352, 44, 12416, 16, 12480, 17 },
};

const s32 eff48_tile_jp_tbl1[4][16] = {
    { 8192, 1, 8256, 2, 8320, 3, 8384, 4, 12288, 14, 12352, 15, 12416, 13, 12480, 9 },
    { 8192, 26, 8256, 27, 8320, 3, 8384, 4, 12288, 39, 12352, 40, 12416, 13, 12480, 9 },
    { 8192, 28, 8256, 29, 8320, 3, 8384, 4, 12288, 41, 12352, 42, 12416, 13, 12480, 9 },
    { 8192, 30, 8256, 31, 8320, 3, 8384, 4, 12288, 43, 12352, 44, 12416, 13, 12480, 9 },
};

const EFF48_FRAME eff48_frame_tbl0[20] = {
    { 0, 512, 0xB }, { 0, 0, 0xB }, { 1, 512, 0xA }, { 0, 0, 9 },
    { 0, 512, 0xA }, { 0, 0, 0xB }, { 0, 512, 0xB }, { 0, 0, 0xA },
    { 1, 512, 9 }, { 1, 0, 9 }, { 1, 512, 9 }, { 1, 0, 9 },
    { 1, 512, 9 }, { 0, 0, 0xA }, { 0, 512, 0xB }, { 0, 0, 0xB },
    { 0, 512, 0xB }, { 0, 0, 0xB }, { 0, 512, 0xB }, { 0, 0, 0xB },
};

const EFF48_FRAME eff48_frame_tbl1[20] = {
    { 2, 0, 0xB }, { 3, 0, 0xB }, { 4, 0, 0xA }, { 3, 0, 9 },
    { 2, 0, 0xA }, { 3, 0, 0xB }, { 2, 0, 0xB }, { 3, 0, 0xA },
    { 4, 0, 9 }, { 5, 0, 9 }, { 4, 0, 9 }, { 5, 0, 9 },
    { 4, 0, 9 }, { 3, 0, 0xA }, { 2, 0, 0xB }, { 3, 0, 0xB },
    { 2, 0, 0xB }, { 3, 0, 0xB }, { 2, 0, 0xB }, { 3, 0, 0xB },
};
