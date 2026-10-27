/*
 * EFF92.C  win mark redraw sequence and colours
 *
 * Rewrite_Mark_Data is the sequence of { mark kind, time } pairs drawn when a win mark is
 * earned, blinking between the earned mark (0x8000) and mark 8; a time of -1 ends it.
 * win_mark_col_tbl gives the colour of each mark kind. Read by EFF92_CODE.C, the win marks.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 Rewrite_Mark_Data[];
extern const s16 win_mark_col_tbl[];

const s16 Rewrite_Mark_Data[26] = {
    0x8000, 2, 8, 2, 0x8000, 2, 8, 2,
    0x8000, 2, 8, 2, 0x8000, 2, 8, 2,
    0x8000, 2, 8, 2, 0x8000, 2, 8, 3,
    0x8000, -1,
};

const s16 win_mark_col_tbl[10] = {
    28, 28, 28, 28, 28, 28, 28, 16, 28, 0,
};
