/*
 * END_MAIN_TBL_B.C  opening demo BG0 step table
 *
 * op_prio_tbl gives the frame count and pattern value of each step of the BG0 pattern sequence
 * the opening plays through oh_opening_demo. Read by END_MAIN.C, the opening demo.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const OP_PRIO op_prio_tbl[];

const OP_PRIO op_prio_tbl[10] = {
    { 6, 4 }, { 2, 5 }, { 2, 6 }, { 2, 7 }, { 2, 8 }, { 2, 9 }, { 2, 10 }, { 2, 11 },
    { 2, 12 }, { 2, 19 },
};
