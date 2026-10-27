/*
 * EFFC7_TBL.C  parry mark positions and entrance prop speeds
 *
 * paring_mark_data gives the x and y offset of the parry mark from the player for each parry
 * type and character; read by EFFC7.C, the parry (blocking) mark. effc8_data_tbl holds the x
 * speed and acceleration and y speed and acceleration with which the entrance prop is thrown
 * clear; read by EFFC8.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 paring_mark_data[][2];
extern const s32 effc8_data_tbl[];

const s16 paring_mark_data[48][2] = {
    { 64, 96 }, { 66, 82 }, { 50, 72 }, { 32, 60 }, { 36, 82 }, { 42, 70 }, { 0, 0 }, { 44, 74 },
    { 38, 52 }, { 50, 72 }, { 32, 60 }, { 50, 72 }, { 50, 72 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 40, 92 }, { 42, 62 }, { 28, 76 }, { 28, 76 }, { 38, 68 }, { 30, 84 }, { 0, 0 }, { 28, 56 },
    { 38, 52 }, { 40, 60 }, { 28, 76 }, { 32, 48 }, { 32, 48 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 12, 40 }, { 32, 44 }, { 28, 34 }, { 22, 40 }, { 30, 40 }, { 28, 44 }, { 0, 0 }, { 22, 36 },
    { 32, 36 }, { 40, 36 }, { 22, 40 }, { 28, 34 }, { 28, 34 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
};

const s32 effc8_data_tbl[4] = {
    196608, 512, 0, -6144,
};
