/*
 * EFF70_TBL.C  breakable stage object pieces
 *
 * eff70_data_tbl gives the position, priority and first animation of each of the three pieces,
 * and eff70_char_tbl the animation each piece takes in each state of the effect 69 object.
 * Read by EFF70.C, the three pieces of the breakable stage object.
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
