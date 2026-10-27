/*
 * EFFG9_TBL.C  trail particle scatter offsets and the effect H0 record
 *
 * g9_pos_hos is the 16 random offsets added to a G9 particle's x and y when it appears, which
 * also choose whether it is drawn in front of or behind the characters; read by EFFG9.C, the
 * trail particle. effh0_data is the single record { x, y, flag, display flag, direction,
 * pattern } of effect H0; read by EFFH0.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 g9_pos_hos[];
extern const EFFH0_DATA effh0_data[];

const s16 g9_pos_hos[16] = {
    0, 1, -1, 2, -2, 0, 3, -3, 1, -1, 2, -2, 4, 3, 0, 3,
};

const EFFH0_DATA effh0_data[1] = {
    { -32, 32, 0, 2, 30, 0 },
};
