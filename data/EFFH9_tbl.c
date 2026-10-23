/*
 * EFFH9_TBL.C  tables read by EFFH9.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u8 effH7_wait_tbl[];
extern const u8 effH7_wait2_tbl[];
extern const s16 effH7_char_tbl[][4];
extern const s16 effH7_pos_tbl[][4][3];
extern const s16 effH7_bound_tbl[];
extern const u8 effH8_wait_tbl[];
extern const s16 effH8_char_tbl[][4];
extern const s16 effH8_char2_tbl[][4];
extern const s16 effH8_pos_tbl[][4][3];

const u8 effH7_wait_tbl[4] = {
    0, 0xF, 0x1E, 0x2D,
};

const u8 effH7_wait2_tbl[4] = {
    0, 0, 0, 0,
};

const s16 effH7_char_tbl[2][4] = {
    { 77, 76, 75, 74 }, { 74, 75, 76, 77 },
};

const s16 effH7_pos_tbl[2][4][3] = {
    { { -32, -6, -2 }, { -4, 4, 2 }, { 24, -6, -2 }, { 48, 4, 2 } },
    { { -32, -6, -2 }, { -8, 4, 2 }, { 20, -6, -2 }, { 48, 4, 2 } },
};

const s16 effH7_bound_tbl[164] = {
    4, 3, 3, 3, 2, 2, 1, 1, 1, 0, 1, 0, 0, 0, -1, 0,
    -1, -1, -2, -2, -3, -3, -3, -4, -4, -4, 3, 3, 2, 2, 1, 1,
    1, 0, 1, 0, 0, -1, 0, -1, -1, -2, -2, -3, -3, 2, 2, 1,
    1, 1, 0, 0, -1, -1, -2, -2, 99, 2, 1, 1, 1, 0, 1, 0,
    0, 0, -1, 0, -1, -1, -1, -2, 99, 3, 2, 2, 1, 1, 1, 0,
    1, 0, 1, 0, 0, 0, -1, 0, -1, 0, -1, -1, -1, -2, -2, -3,
    99, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 0, 1, 0, 0, 0,
    -1, 0, -1, -1, -1, -2, -2, -2, -3, -3, -3, -4, 99, 5, 5, 4,
    4, 4, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 0, 1, 0, 0,
    0, -1, 0, -1, -1, -1, -2, -2, -2, -2, -3, -3, -3, -4, -4, -4,
    -5, -5, 99, 0,
};

const u8 effH8_wait_tbl[4] = {
    0, 0xF, 0x1E, 0x2D,
};

const s16 effH8_char_tbl[2][4] = {
    { 162, 161, 160, 159 }, { 159, 160, 161, 162 },
};

const s16 effH8_char2_tbl[2][4] = {
    { 43, 41, 39, 37 }, { 37, 39, 41, 43 },
};

const s16 effH8_pos_tbl[2][4][3] = {
    { { -32, -4, -2 }, { -12, -4, -2 }, { 12, -4, -2 }, { 36, -4, -2 } },
    { { -32, -4, -2 }, { -8, -4, -2 }, { 16, -4, -2 }, { 36, -4, -2 } },
};
