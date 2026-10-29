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
    0, 0x8000, 0x10000, 0x18000, 0x20000, 0x28000, 0x30000, 0x38000,
    0x40000, 0x48000, 0x50000, 0x58000, 0x60000, 0x68000, 0x70000, 0x78000,
};
