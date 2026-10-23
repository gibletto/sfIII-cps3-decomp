/*
 * EFF70_TBL.C  tables read by EFF70.c: effect 70's placements and characters
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff70_data_tbl[][4];
extern const s16 eff70_char_tbl[][4];

const s16 eff70_data_tbl[3][4] = {
    { 192, 48, 79, 20 }, { 208, 48, 78, 24 }, { 182, 50, 77, 28 },
};

const s16 eff70_char_tbl[3][4] = {
    { 20, 21, 22, 23 }, { 24, 25, 26, 27 }, { 28, 29, 30, 31 },
};
