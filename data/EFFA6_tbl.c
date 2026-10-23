/*
 * EFFA6_TBL.C  tables read by EFFA6.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effA6_x_wide_lead[];
extern const SCROLL_TARGET effA6_x_tbl_wide[];

/* the wide screen targets are 3 per country like effA6_x_tbl's; these are country 0's first two, and
   effA6_x_tbl_wide starts at its third, the one effA6_set_target reads (provisional name) */
const s16 effA6_x_wide_lead[2] = {
    -136, -64,
};

const SCROLL_TARGET effA6_x_tbl_wide[38] = {
    { -104 }, { 72 }, { 144 }, { 176 }, { -48 }, { 24 }, { -19 }, { -64 },
    { -8 }, { -44 }, { -136 }, { -104 }, { -184 }, { -208 }, { -136 }, { -184 },
    { -176 }, { -136 }, { -184 }, { -48 }, { 24 }, { -19 }, { -208 }, { -112 },
    { -176 }, { 112 }, { 176 }, { 184 }, { -64 }, { -8 }, { -44 }, { -48 },
    { 24 }, { -19 }, { 128 }, { 200 }, { 176 }, { 0 },
};
