/*
 * WIN_PL_TBL.C  round winner type table
 *
 * win_type_tbl selects, by character, which winner routine (Win_00000 .. Win_06000) plays at
 * the end of a won round. Read by WIN_PL.C, the round winner poses.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 win_type_tbl[];

const s16 win_type_tbl[14] = {
    0, 0, 0, 6, 2, 0, 0, 3, 4, 1, 0, 0, 5, 0,
};
