/*
 * EFFH9_TBL.C  pop-up object tables for effects H7 and H8
 *
 * For the objects that pop out of the ground: per-type delays (effH7_wait_tbl,
 * effH7_wait2_tbl, effH8_wait_tbl), patterns by facing and type (effH7_char_tbl,
 * effH8_char_tbl, and effH8_char2_tbl for the second pattern), { x, y, priority } offsets by
 * facing and type (effH7_pos_tbl, effH8_pos_tbl), and the height steps of the H7 bounce
 * (effH7_bound_tbl) and of the bobbing sequences that effH7_move_tbl points at
 * (effH7_move_data_0 - 3). Read by EFFH9.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u8 effH7_wait_tbl[];
extern const u8 effH7_wait2_tbl[];
extern const s16 effH7_char_tbl[][4];
extern const s16 effH7_pos_tbl[][4][3];
extern const s16 effH7_bound_tbl[];
extern const s16 effH7_move_data_0[];
extern const s16 effH7_move_data_1[];
extern const s16 effH7_move_data_2[];
extern const s16 effH7_move_data_3[];
extern const u8 effH8_wait_tbl[];
extern const s16 effH8_char_tbl[][4];
extern const s16 effH8_char2_tbl[][4];
extern const s16 effH8_pos_tbl[][4][3];

const u8 effH7_wait_tbl[4] = {
    0, 15, 30, 45,
};

const u8 effH7_wait2_tbl[4] = {
    0, 0, 0, 0,
};

const s16 effH7_char_tbl[2][4] = {
    { 77, 76, 75, 74 }, { 74, 75, 76, 77 },
};

/*
 * Indexed by facing (rl_waza) and type: x offset (toward the facing), y offset and
 * priority offset of the object from where it was created.
 */
const s16 effH7_pos_tbl[2][4][3] = {
    { { -32, -6, -2 }, { -4, 4, 2 }, { 24, -6, -2 }, { 48, 4, 2 } },
    { { -32, -6, -2 }, { -8, 4, 2 }, { 20, -6, -2 }, { 48, 4, 2 } },
};

const s16 effH7_bound_tbl[57] = {
    4, 3, 3, 3, 2, 2, 1, 1,
    1, 0, 1, 0, 0, 0, -1, 0,
    -1, -1, -2, -2, -3, -3, -3, -4,
    -4, -4, 3, 3, 2, 2, 1, 1,
    1, 0, 1, 0, 0, -1, 0, -1,
    -1, -2, -2, -3, -3, 2, 2, 1,
    1, 1, 0, 0, -1, -1, -2, -2,
    99,
};

/* provisional name */
const s16 effH7_move_data_0[16] = {
    2, 1, 1, 1, 0, 1, 0, 0,
    0, -1, 0, -1, -1, -1, -2, 99,
};

/* provisional name */
const s16 effH7_move_data_1[24] = {
    3, 2, 2, 1, 1, 1, 0, 1,
    0, 1, 0, 0, 0, -1, 0, -1,
    0, -1, -1, -1, -2, -2, -3, 99,
};

/* provisional name */
const s16 effH7_move_data_2[28] = {
    4, 3, 3, 3, 2, 2, 2, 1,
    1, 1, 0, 1, 0, 0, 0, -1,
    0, -1, -1, -1, -2, -2, -2, -3,
    -3, -3, -4, 99,
};

/* provisional name */
const s16 effH7_move_data_3[39] = {
    5, 5, 4, 4, 4, 3, 3, 3,
    2, 2, 2, 2, 1, 1, 1, 0,
    1, 0, 0, 0, -1, 0, -1, -1,
    -1, -2, -2, -2, -2, -3, -3, -3,
    -4, -4, -4, -5, -5, 99, 0,
};

const u8 effH8_wait_tbl[4] = {
    0, 15, 30, 45,
};

const s16 effH8_char_tbl[2][4] = {
    { 162, 161, 160, 159 }, { 159, 160, 161, 162 },
};

const s16 effH8_char2_tbl[2][4] = {
    { 43, 41, 39, 37 }, { 37, 39, 41, 43 },
};

/* Indexed by facing (rl_waza) and type: x offset, y offset and priority offset. */
const s16 effH8_pos_tbl[2][4][3] = {
    { { -32, -4, -2 }, { -12, -4, -2 }, { 12, -4, -2 }, { 36, -4, -2 } },
    { { -32, -4, -2 }, { -8, -4, -2 }, { 16, -4, -2 }, { 36, -4, -2 } },
};
