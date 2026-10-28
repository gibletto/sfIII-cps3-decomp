/*
 * BG_DATA2.C  screen quake, stage colour and mark graphics tables
 *
 * quake_x_tbl and quake_y_tbl are the screen shake offsets stepped by the quake index; read by
 * BG000.C and TA_SUB.C, quake_y_tbl also by END_5.C. bg_palette_no_tbl and bg_color2_tbl give
 * each background's palette numbers, read by BG000.C and MANAGE_2.C (which also fades in
 * bg_color3_tbl), and etc_bg_color_tbl the palette of each special screen, read by BG000.C.
 * mark_cg_tbl lists the cg numbers of the 45 mark graphics loaded by ABOUTSPR.C.
 * ake_cell0_data .. ake_cell2_data place the cells of the three akebono screen layers, read by
 * akebono_scr_write in BG000.C. The str_BG_ .. str_AREA labels are reached through
 * bg_test_menu_scr in BG_DATA.C.
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
extern const PANEL ake_cell1_data[];
extern const PANEL ake_cell0_data[];
extern const PANEL ake_cell2_data[];
extern const s8 str_BG_1_POS_X[];
extern const s8 str_BG_1_POS_Y[];
extern const s8 str_BG_2_POS_X[];
extern const s8 str_BG_2_POS_Y[];
extern const s8 str_BG_3_POS_X[];
extern const s8 str_BG_3_POS_Y[];
extern const s8 str_BG_4_POS_X[];
extern const s8 str_BG_4_POS_Y[];
extern const s8 str_BG_1[];
extern const s8 str_BG_2[];
extern const s8 str_BG_3[];
extern const s8 str_BG_4[];
extern const s8 str_STAGE_2[];
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

const PANEL ake_cell1_data[8] = {
    { 0x2000, 5 }, { 0x2040, 6 }, { 0x2080, 7 }, { 0x20C0, 8 },
    { 0x3000, 1 }, { 0x3040, 2 }, { 0x3080, 3 }, { 0x30C0, 4 },
};

const PANEL ake_cell0_data[8] = {
    { 0x2000, 25 }, { 0x2040, 26 }, { 0x2080, 27 }, { 0x20C0, 28 },
    { 0x3000, 29 }, { 0x3040, 30 }, { 0x3080, 31 }, { 0x30C0, 32 },
};

const PANEL ake_cell2_data[8] = {
    { 0x2000, 13 }, { 0x2040, 14 }, { 0x2080, 17 }, { 0x20C0, 18 },
    { 0x3000, 21 }, { 0x3040, 22 }, { 0x3080, 23 }, { 0x30C0, 24 },
};

const s8 str_BG_1_POS_X[16] = "BG 1 POS X = \n\0\x55";

const s8 str_BG_1_POS_Y[16] = "BG 1 POS Y = \n\0\x55";

const s8 str_BG_2_POS_X[16] = "BG 2 POS X = \n\0\x55";

const s8 str_BG_2_POS_Y[16] = "BG 2 POS Y = \n\0\x01";

const s8 str_BG_3_POS_X[16] = "BG 3 POS X = \n\0\x01";

const s8 str_BG_3_POS_Y[16] = "BG 3 POS Y = \n\0\x01";

const s8 str_BG_4_POS_X[16] = "BG 4 POS X = \n\0\x32";

const s8 str_BG_4_POS_Y[16] = "BG 4 POS Y = \0\x01\x01";

const s8 str_BG_1[12] = "BG 1 = \n\0\x01\x01\x01";

const s8 str_BG_2[12] = "BG 2 = \n\0\x01\x01\x01";

const s8 str_BG_3[12] = "BG 3 = \n\0\x01\x01\x01";

const s8 str_BG_4[8] = "BG 4 = ";

const s8 str_STAGE_2[12] = "STAGE = \n\0\x01\x01";

const char str_AREA[12] = "AREA  = \0\x01\x5F\x5F";
