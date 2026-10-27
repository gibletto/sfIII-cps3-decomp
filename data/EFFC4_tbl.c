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
    { 0, 0, 0, 0 }, { -262144, 65536, 0, -24576 },
    { -229376, 196608, -8192, -24576 }, { -196608, 65536, -4096, -24576 },
    { -163840, 0, -512, 0 }, { -196608, 0, 0, 0 },
};
