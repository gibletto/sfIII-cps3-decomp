/*
 * ABOUTSPR_TBL.C  shadow width table
 *
 * gkw_table is the width of a character's shadow by height above the ground (in steps of
 * 4 dots, 64 entries; higher than that the width is 16). Read by get_kage_width in ABOUTSPR.C,
 * the character sprite graphics and display lists.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 gkw_table[];

const s16 gkw_table[64] = {
    0, 1, 2, 3, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7,
    8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11,
    11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13,
    13, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15,
};
