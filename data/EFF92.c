/*
 * EFF92.C  tables read by eff92_code.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 Rewrite_Mark_Data[];
extern const s16 win_mark_col_tbl[];

const s16 Rewrite_Mark_Data[26] = {
    -32768, 2, 8, 2, -32768, 2, 8, 2,
    -32768, 2, 8, 2, -32768, 2, 8, 2,
    -32768, 2, 8, 2, -32768, 2, 8, 3,
    -32768, -1,
};

const s16 win_mark_col_tbl[10] = {
    28, 28, 28, 28, 28, 28, 28, 16, 28, 0,
};
