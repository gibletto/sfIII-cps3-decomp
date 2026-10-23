/*
 * END_MAIN_TBL_B.C  tables read by end_main.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const OP_PRIO op_prio_tbl[];

const OP_PRIO op_prio_tbl[10] = {
    { 6, 4 }, { 2, 5 }, { 2, 6 }, { 2, 7 }, { 2, 8 }, { 2, 9 }, { 2, 10 }, { 2, 11 },
    { 2, 12 }, { 2, 19 },
};
