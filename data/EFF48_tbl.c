/*
 * EFF48_TBL.C  continue display offsets and a stage object's flight course
 *
 * eff49_pos_tbl gives the x offset from the screen position of each of the ten effect 49 works
 * that CONTINUE.C starts; read by EFF49.C, the continue count down. eff54_move_tbl is the
 * course of the effect 54 object, a row per phase: time, then x and y speeds and
 * accelerations; read by EFF54.C.
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
