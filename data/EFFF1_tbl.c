/*
 * EFFF1_TBL.C  tables read by EFFF1.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effF1_data_tbl[][5];

const s16 effF1_data_tbl[5][5] = {
    { 83, 1, 48, 1, 0 }, { 80, 1, 0, 0, 0 }, { 4, 1, 0, 0, 0 }, { 80, 1, 0, 1, 0 },
    { 0, 1, 0, 1, 1 },
};
