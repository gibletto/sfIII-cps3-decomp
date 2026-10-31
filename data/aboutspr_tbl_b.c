/*
 * ABOUTSPR_TBL_B.C  hit mark frame table
 *
 * mark_index_tbl gives, for each of the five mark types, the index of each of its nine frames
 * into the mark graphics tables (mark_gfx_cells, mark_gfx_ofs). Read by ABOUTSPR.C, the
 * character sprite graphics and display lists.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 mark_index_tbl[][9];

/* provisional name */
const s16 mark_index_tbl[5][9] = {
    { 0, 1, 2, 3, 4, 5, 6, 7, 8 }, { 9, 10, 11, 12, 13, 14, 15, 16, 17 },
    { 18, 19, 20, 21, 22, 23, 24, 25, 26 }, { 27, 28, 29, 30, 31, 32, 33, 34, 35 },
    { 36, 37, 38, 39, 40, 41, 42, 43, 44 },
};
