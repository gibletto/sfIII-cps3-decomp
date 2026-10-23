/*
 * EFFC0_TBL_B.C  tables read by EFFC2.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effc2_data_tbl[][4];

const s16 effc2_data_tbl[4][4] = {
    { 784, 32, 20, 9 }, { 720, 64, 77, 10 }, { 240, 32, 20, 11 }, { 304, 64, 77, 12 },
};
