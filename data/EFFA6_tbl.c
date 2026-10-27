/*
 * EFFA6_TBL.C  wide-screen scroll targets for the battle country
 *
 * effA6_x_tbl_wide holds the x targets of the BG 0 scroll on the wide screen, three per battle
 * country, of which effect A6 reads one (Battle_Country * 3); effA6_x_wide_lead holds the two
 * values stored before it and is not referred to by name. Read by EFFA6.C, the BG 0 scroll to
 * the battle country, in place of effA6_x_tbl when Game_setting.mode is set.
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
