/*
 * BG_DATA2.C  tables read by aboutspr.c, bg000.c, end_5.c, manage_2.c and ta_sub.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 quake_x_tbl[];
extern const s16 quake_y_tbl[];
extern const u16 bg_color2_tbl[];
extern const u16 bg_palette_no_tbl[];
extern const u16 etc_bg_color_tbl[];
extern const u16 bg_color3_tbl[];
extern const s16 mark_cg_tbl[];
extern const char ake_cell1_data[];
extern const char ake_cell0_data[];
extern const char ake_cell2_data[];
extern const char str_BG_1_POS_X[];
extern const char str_BG_1_POS_Y[];
extern const char str_BG_2_POS_X[];
extern const char str_BG_2_POS_Y[];
extern const char str_BG_3_POS_X[];
extern const char str_BG_3_POS_Y[];
extern const char str_BG_4_POS_X[];
extern const char str_BG_4_POS_Y[];
extern const char str_BG_1[];
extern const char str_BG_2[];
extern const char str_BG_3[];
extern const char str_BG_4[];
extern const char str_STAGE_2[];
extern const char str_AREA[];

const s16 quake_x_tbl[130] = {
    0, -1, 1, -1, 1, -1, 1, -2, 2, -2, 2, -2, 2, -3, 3, -3,
    3, -3, 3, -4, 4, -4, 4, -4, 4, -5, 5, -5, 5, -5, 5, -6,
    6, -6, 6, -6, 6, -7, 7, -7, 7, -7, 7, -8, 8, -8, 8, -8,
    8, -9, 9, -9, 9, -9, 9, -10, 10, -10, 10, -10, 10, -11, 11, -11,
    11, -12, 12, -12, 12, -13, 13, -13, 13, -14, 14, -14, 14, -15, 15, -15,
    15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15,
    15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15,
    15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15,
    15, -15,
};

const s16 quake_y_tbl[130] = {
    0, -1, 1, -2, 2, -2, 2, -3, 3, -3, 3, -4, 4, -4, 4, -5,
    5, -5, 5, -6, 6, -6, 6, -7, 7, -7, 7, -8, 8, -8, 8, -9,
    9, -9, 9, -10, 10, -10, 10, -10, 10, -11, 11, -11, 11, -12, 12, -12,
    12, -13, 13, -11, 11, -11, 11, -12, 12, -12, 12, -13, 13, -11, 11, -11,
    11, -12, 12, -12, 12, -13, 13, -13, 13, -14, 14, -14, 14, -15, 15, -15,
    15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15,
    15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15,
    15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15, 15, -15,
    15, -15,
};

const u16 bg_color2_tbl[22] = {
    0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54,
    0x55, 0x4A, 0x4B, 8, 8, 8,
};

const u16 bg_palette_no_tbl[22] = {
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43,
    0x44, 0x39, 0x3A, 8, 8, 8,
};

const u16 etc_bg_color_tbl[5] = {
    6, 8, 6, 0xA, 0xA,
};

const u16 bg_color3_tbl[21] = {
    0x68, 0x69, 0x66, 0x67, 0x6A, 0x6B, 0x64, 0x65, 0x61, 0x60, 0x6D, 0x6E, 0x6F, 0x62, 0x63, 0x6C,
    0x6A, 0x6B, 8, 8, 8,
};

const s16 mark_cg_tbl[46] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 64, 65, 66, 67, 68,
    69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 80, 257,
};

const char ake_cell1_data[64] = {
    0, 0, 32, 0, 0, 0, 0, 5, 0, 0, 32, 64, 0, 0, 0, 6,
    0, 0, 32, -128, 0, 0, 0, 7, 0, 0, 32, -64, 0, 0, 0, 8,
    0, 0, 48, 0, 0, 0, 0, 1, 0, 0, 48, 64, 0, 0, 0, 2,
    0, 0, 48, -128, 0, 0, 0, 3, 0, 0, 48, -64, 0, 0, 0, 4,
};

const char ake_cell0_data[64] = {
    0, 0, 32, 0, 0, 0, 0, 25, 0, 0, 32, 64, 0, 0, 0, 26,
    0, 0, 32, -128, 0, 0, 0, 27, 0, 0, 32, -64, 0, 0, 0, 28,
    0, 0, 48, 0, 0, 0, 0, 29, 0, 0, 48, 64, 0, 0, 0, 30,
    0, 0, 48, -128, 0, 0, 0, 31, 0, 0, 48, -64, 0, 0, 0, 32,
};

const char ake_cell2_data[64] = {
    0, 0, 32, 0, 0, 0, 0, 13, 0, 0, 32, 64, 0, 0, 0, 14,
    0, 0, 32, -128, 0, 0, 0, 17, 0, 0, 32, -64, 0, 0, 0, 18,
    0, 0, 48, 0, 0, 0, 0, 21, 0, 0, 48, 64, 0, 0, 0, 22,
    0, 0, 48, -128, 0, 0, 0, 23, 0, 0, 48, -64, 0, 0, 0, 24,
};

const char str_BG_1_POS_X[16] = "BG 1 POS X = \n\0\x55";

const char str_BG_1_POS_Y[16] = "BG 1 POS Y = \n\0\x55";

const char str_BG_2_POS_X[16] = "BG 2 POS X = \n\0\x55";

const char str_BG_2_POS_Y[16] = "BG 2 POS Y = \n\0\x01";

const char str_BG_3_POS_X[16] = "BG 3 POS X = \n\0\x01";

const char str_BG_3_POS_Y[16] = "BG 3 POS Y = \n\0\x01";

const char str_BG_4_POS_X[16] = "BG 4 POS X = \n\0\x32";

const char str_BG_4_POS_Y[16] = "BG 4 POS Y = \0\x01\x01";

const char str_BG_1[12] = "BG 1 = \n\0\x01\x01\x01";

const char str_BG_2[12] = "BG 2 = \n\0\x01\x01\x01";

const char str_BG_3[12] = "BG 3 = \n\0\x01\x01\x01";

const char str_BG_4[8] = "BG 4 = ";

const char str_STAGE_2[12] = "STAGE = \n\0\x01\x01";

const char str_AREA[12] = "AREA  = \0\x01\x5F\x5F";
