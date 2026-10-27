/*
 * EFFD4_TBL.C  suction pull speeds
 *
 * swallow_speeds gives the pull speed of each speed number (0 to 15) that the
 * swallow_areas_x / _y tables of EFFD0_TBL.C pick. Read by EFFD4.C, the suction pull of an attack.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s32 swallow_speeds[];

const s32 swallow_speeds[16] = {
    0, 32768, 65536, 98304, 131072, 163840, 196608, 229376,
    262144, 294912, 327680, 360448, 393216, 425984, 458752, 491520,
};
