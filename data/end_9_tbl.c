/*
 * END_9_TBL.C  Oro's ending scene tables (ending 9)
 *
 * timer_9_tbl is the length in frames of each of the seven scenes of the ending and end_9_pos
 * the BG x and y of each scene; the BG0 cells are in END_8_TBL.C. Read by END_9.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 timer_9_tbl[];
extern const s16 end_9_pos[][2];

const s16 timer_9_tbl[7] = {
    240, 240, 240, 180, 180, 180, 660,
};

const s16 end_9_pos[7][2] = {
    { 768, 256 }, { 768, 256 }, { 768, 256 }, { 768, 256 }, { 768, 256 }, { 768, 256 }, { 768, 48 },
};
