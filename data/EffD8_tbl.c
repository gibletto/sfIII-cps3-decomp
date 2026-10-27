/*
 * EFFD8_TBL.C  face cursor priorities
 *
 * effD8_priority_tbl gives the priority of the face cursor for each cursor number given to
 * effect_D8_entry. Read by EFFD8.C, the player's face cursor on the character select screen.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effD8_priority_tbl[];

const s16 effD8_priority_tbl[4] = {
    56, 58, 57, -8,
};
