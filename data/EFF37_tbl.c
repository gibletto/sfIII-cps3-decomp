/*
 * EFF37_TBL.C  face panel position offsets
 *
 * panel_pos_hosei gives the x and y offset of the face panel from its master for each
 * character set and the master's display type (cg_type). Read by EFF37.C, the face panel shown
 * with a character.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 panel_pos_hosei[][4][2];

const s16 panel_pos_hosei[7][4][2] = {
    { { 25, 100 }, { 25, 101 }, { 0, 0 }, { 25, 101 } },
    { { 43, 104 }, { 42, 107 }, { 0, 0 }, { 42, 107 } },
    { { 18, 116 }, { 0, 0 }, { 0, 0 }, { 18, 116 } },
    { { 18, 116 }, { 0, 0 }, { 0, 0 }, { 18, 116 } },
    { { 18, 116 }, { 0, 0 }, { 0, 0 }, { 18, 116 } },
    { { 30, 91 }, { 30, 90 }, { 0, 0 }, { 30, 90 } },
    { { -23, 112 }, { 0, 0 }, { 0, 0 }, { -23, 112 } },
};
