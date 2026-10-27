/*
 * EFFE5_TBL.C  after-image setup pairs
 *
 * illusion_setup_table gives { who, parameter set } pairs for setup_after_images: who 0 is
 * this player, 1 the opponent and any other value both, and the parameter set picks a row of
 * after_image_data. Read by EFFE5.C, the after-image controller.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 illusion_setup_table[][2];

const s16 illusion_setup_table[7][2] = {
    { 0, 0 }, { 2, 0 }, { 0, 4 }, { 0, 5 }, { 0, 2 }, { 1, 3 }, { 0, 11 },
};
