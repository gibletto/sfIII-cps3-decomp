/*
 * APPEAR_TBL_B.C  entrance smoke check table
 *
 * smoke_check gives, per stage background (bg_index), whether the Appear_16000 entrance starts
 * with its smoke animation (cg 10) instead of the plain one (cg 8). Read by APPEAR.C, the
 * fighter entrance sequences.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 smoke_check[];

const s16 smoke_check[20] = {
    1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0,
    0, 0, 0, 0,
};
