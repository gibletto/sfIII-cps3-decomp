/*
 * EFFD4_TBL.C  tables read by EFFD4.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s32 swallow_speeds[];

const s32 swallow_speeds[16] = {
    0, 32768, 65536, 98304, 131072, 163840, 196608, 229376,
    262144, 294912, 327680, 360448, 393216, 425984, 458752, 491520,
};
