/*
 * PLPDM_TBL_B.C  a countdown table after exdm_ix_data; nothing in the program refers to it
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u16 exdm_ix_data_tail[];

const u16 exdm_ix_data_tail[18] = {
    0x20, 0x1F, 0x1E, 0x1D, 0x1C, 0x1B, 0x1A, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11,
    0x10, 0,
};
