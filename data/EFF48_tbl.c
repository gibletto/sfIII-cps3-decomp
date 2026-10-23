/*
 * EFF48_TBL.C  tables read by EFF49.c and EFF54.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff49_pos_tbl[];
extern const s32 eff54_move_tbl[][5];

const s16 eff49_pos_tbl[10] = {
    -80, -64, -48, -32, -16, 0, 16, 32, 56, 80,
};

const s32 eff54_move_tbl[3][5] = {
    { 12, 131072, 98304, 16384, 24576 }, { 30, 0, 0, 0, 0 },
    { 0, 0, -256, -256, -512 },
};
