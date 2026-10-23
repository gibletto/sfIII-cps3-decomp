/*
 * EFFG9_TBL.C  tables read by EFFG9.c and EFFH0.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 g9_pos_hos[];
extern const EFFH0_DATA effh0_data[];

const s16 g9_pos_hos[16] = {
    0, 1, -1, 2, -2, 0, 3, -3, 1, -1, 2, -2, 4, 3, 0, 3,
};

const EFFH0_DATA effh0_data[1] = {
    { -32, 32, 0, 2, 30, 0 },
};
