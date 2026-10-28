/*
 * PLPDM_TBL_B.C  a countdown table after exdm_ix_data
 *
 * exdm_ix_data_tail is a table of values counting down from 0x20 to 0x10, ending in 0, placed
 * after exdm_ix_data in PLPDM_TBL.C; nothing in the program refers to it.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u16 exdm_ix_data_tail[];

const u16 exdm_ix_data_tail[18] = {
    32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,
    16, 0,
};
