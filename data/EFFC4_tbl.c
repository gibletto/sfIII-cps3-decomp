/*
 * EFFC4_TBL.C  bouncing object speeds
 *
 * effC4_sp_tbl gives the x and y speeds and accelerations of the object for each state of its
 * flight; each landing starts the next. Read by EFFC4.C, the bouncing object.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s32 effC4_sp_tbl[][4];

const s32 effC4_sp_tbl[6][4] = {
    { 0, 0, 0, 0 }, { -0x40000, 0x10000, 0, -0x6000 },
    { -0x38000, 0x30000, -0x2000, -0x6000 }, { -0x30000, 0x10000, -0x1000, -0x6000 },
    { -0x28000, 0, -0x200, 0 }, { -0x30000, 0, 0, 0 },
};
