/*
 * INTR_TBL.C  vertical blank frame mask table
 *
 * vbl_frame_mask_tbl is a 16-entry table of frame masks. Its only reference is the vertical
 * blank interrupt in INTR.SRC, which copies it into a local array.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 vbl_frame_mask_tbl[];

const s16 vbl_frame_mask_tbl[16] = {
    0, 1, 0, 3, 0, 7, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15,
};
