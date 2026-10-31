/*
 * VITAL_TBL.C  vitality bar, round timer and super art gauge tables
 *
 * vital_cell_tbl and vital_cell_1p_tbl are the text-layer cells of the two vitality bars,
 * vital_npos_0 .. vital_npos_3 the cell columns of the 1P and 2P bars in the normal and wide
 * screen modes and vital_attr_0 .. vital_attr_2 the cell attributes for each bar colour,
 * reached through vital_npos_tbl and vital_attr_tbl; read by VITAL.C. vital_unref_0 is not
 * referred to. hoji_counter_tbl is the round timer
 * tick length for each game-speed setting, read by COUNT.C. spgauge_puttbl_0 and _1 are the
 * gauge cell codes, spgauge_postbl_0 .. spgauge_postbl_1_2 the cell columns of each player's
 * gauge for the two screen modes, and sa_time_data_tbl the cell sheets of the timed super art
 * countdown; these are read by SPGAUGE.C, the super art gauge display.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u16 vital_cell_tbl[];
extern const u16 vital_cell_1p_tbl[];
extern const u16 vital_npos_0[];
extern const u16 vital_npos_1[];
extern const u16 vital_npos_2[];
extern const u16 vital_npos_3[];
extern const u16 vital_attr_0[];
extern const u16 vital_attr_1[];
extern const u16 vital_attr_2[];
extern const u16 vital_unref_0[];
extern const s16 hoji_counter_tbl[];
extern const u16 spgauge_puttbl_0[];
extern const u16 spgauge_puttbl_1[];
extern const u16 spgauge_postbl_0[];
extern const u16 spgauge_postbl_1[];
extern const u16 spgauge_postbl_0_2[];
extern const u16 spgauge_postbl_1_2[];
extern const u16 sa_time_data_tbl[][6];

const u16 vital_cell_tbl[81] = {
    0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80, 0xAC, 0xAB, 0xAA, 0xA9, 0xA8, 0xA7, 0xA6, 0xA5,
    0x88, 0, 0xA4, 0xA3, 0xA2, 0xA1, 0xA0, 0x9F, 0x89, 0, 0, 0x9E, 0x9D, 0x9C, 0x9B, 0x9A,
    0x8A, 0, 0, 0, 0x99, 0x98, 0x97, 0x96, 0x8B, 0, 0, 0, 0, 0x95, 0x94, 0x93,
    0x8C, 0, 0, 0, 0, 0, 0x92, 0x91, 0x8D, 0, 0, 0, 0, 0, 0, 0x90,
    0x8E, 0, 0, 0, 0, 0, 0, 0, 0x8F, 0, 0, 0, 0, 0, 0, 0,
    0,
};

const u16 vital_cell_1p_tbl[81] = {
    0x137, 0x136, 0x135, 0x134, 0x133, 0x132, 0x131, 0x130,
    0x15C, 0x15B, 0x15A, 0x159, 0x158, 0x157, 0x156, 0x155,
    0x138, 0, 0x154, 0x153, 0x152, 0x151, 0x150, 0x15F,
    0x139, 0, 0, 0x14E, 0x14D, 0x14C, 0x14B, 0x14A,
    0x13A, 0, 0, 0, 0x149, 0x148, 0x147, 0x146,
    0x13B, 0, 0, 0, 0, 0x145, 0x144, 0x143,
    0x13C, 0, 0, 0, 0, 0, 0x142, 0x141,
    0x13D, 0, 0, 0, 0, 0, 0, 0x140,
    0x13E, 0, 0, 0, 0, 0, 0, 0,
    0x13F, 0, 0, 0, 0, 0, 0, 0,
    0,
};

/* cell columns of the 1P bar in the normal screen mode, reached through vital_npos_tbl[0]; provisional name */
const u16 vital_npos_0[20] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x10,
    0x11, 0x12, 0x13, 0x14,
};

/* cell columns of the 2P bar in the normal screen mode, reached through vital_npos_tbl[1]; provisional name */
const u16 vital_npos_1[20] = {
    0x2E, 0x2D, 0x2C, 0x2B, 0x2A, 0x29, 0x28, 0x27,
    0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20, 0x1F,
    0x1E, 0x1D, 0x1C, 0x1B,
};

/* cell columns of the 1P bar in the wide screen mode, reached through vital_npos_tbl[2]; provisional name */
const u16 vital_npos_2[20] = {
    8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B,
};

/* cell columns of the 2P bar in the wide screen mode, reached through vital_npos_tbl[3]; provisional name */
const u16 vital_npos_3[20] = {
    0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x2F, 0x2E,
    0x2D, 0x2C, 0x2B, 0x2A, 0x29, 0x28, 0x27, 0x26,
    0x25, 0x24, 0x23, 0x22,
};

/* cell attributes for each bar colour, reached through vital_attr_tbl[0]; provisional name */
const u16 vital_attr_0[3] = {
    2, 4, 6,
};

/* cell attributes for each bar colour, reached through vital_attr_tbl[1]; provisional name */
const u16 vital_attr_1[3] = {
    0x82, 0x84, 0x86,
};

/* cell attributes for each bar colour, reached through vital_attr_tbl[2]; provisional name */
const u16 vital_attr_2[3] = {
    2, 4, 6,
};

/* not referred to; provisional name */
const u16 vital_unref_0[49] = {
    0xFFD4, 0x16, 1, 0x17, 1, 0x16, 2, 0x17,
    2, 0x16, 3, 0x17, 3, 0x18, 1, 0x19,
    1, 0x18, 2, 0x19, 2, 0x18, 3, 0x19,
    3, 0x1D, 1, 0x1E, 1, 0x1D, 2, 0x1E,
    2, 0x1D, 3, 0x1E, 3, 0x1F, 1, 0x20,
    1, 0x1F, 2, 0x20, 2, 0x1F, 3, 0x20,
    3,
};

const s16 hoji_counter_tbl[4] = {
    60, 53, 37, 29,
};

/* provisional name */
const u16 spgauge_puttbl_0[9] = {
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8,
};

const u16 spgauge_puttbl_1[9] = {
    0x160, 0x161, 0x162, 0x163, 0x164, 0x165, 0x166, 0x167, 0x168,
};

const u16 spgauge_postbl_0[16] = {
    20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5,
};

const u16 spgauge_postbl_1[16] = {
    27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
};

const u16 spgauge_postbl_0_2[16] = {
    0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0xF, 0xE, 0xD, 0xC, 0xB, 0xA, 9, 8, 7, 6,
};

const u16 spgauge_postbl_1_2[16] = {
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
};

const u16 sa_time_data_tbl[2][6] = {
    { 0x900, 0x903, 0x906, 0x909, 0x90C, 0x920 },
    { 0x8A0, 0x8A4, 0x8A8, 0x8AC, 0x8C0, 0x8C4 },
};
