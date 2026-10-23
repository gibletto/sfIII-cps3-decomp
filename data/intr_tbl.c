/*
 * INTR_TBL.C  tables read by intr.src
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 vbl_frame_mask_tbl[];

const s16 vbl_frame_mask_tbl[16] = {
    0, 1, 0, 3, 0, 7, 0, 15, 0, 15, 0, 15, 0, 15, 0, 15,
};
