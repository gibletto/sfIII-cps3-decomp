/*
 * EFFB4_TBL.C  ball spark patterns and palette cycle colours
 *
 * s_mark_tbl gives the pattern added to the spark's animation, picked at random; read by
 * EFFB4.C, the ball hit spark. effB6_col_tbl gives the six colour numbers each of the three
 * cycle types steps through; read by EFFB6.C, the palette cycle.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 s_mark_tbl[];
extern const u16 effB6_col_tbl[][6];

const s16 s_mark_tbl[32] = {
    0, 1, 0, 1, 0, 3, 0, 0, 0, 2, 4, 0, 0, 1, 0, 2,
    6, 3, 0, 2, 0, 0, 6, 3, 0, 4, 0, 0, 6, 0, 0, 4,
};

const u16 effB6_col_tbl[3][6] = {
    { 0x70, 0x71, 0x72, 0x73, 0x74, 0x75 }, { 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B },
    { 0x7C, 0x7D, 0x7E, 0x7F, 0x80, 0x81 },
};
