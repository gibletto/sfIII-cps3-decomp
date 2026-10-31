/*
 * EFFC0_TBL_B.C  placement of the objects that drop on the landing
 *
 * effc2_data_tbl gives the x, y, priority and pattern of each of the four objects of effect
 * C2. Read by EFFC2.C, the stage objects that drop on the landing.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effc2_data_tbl[][4];

/* provisional name */
const s16 effc2_data_tbl[4][4] = {
    { 784, 32, 20, 9 }, { 720, 64, 77, 10 }, { 240, 32, 20, 11 }, { 304, 64, 77, 12 },
};
