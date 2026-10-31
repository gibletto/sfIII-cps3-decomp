/*
 * END_5_TBL_B.C  Necro's ending tables (ending 5), continued
 *
 * end_500_bg1_cell_tbl lists the BG1 cells (map offset, cell number) written at the start of
 * the ending, timer_5_tbl the length in frames of each of its six scenes and end_5_pos the BG
 * x and y of each scene. Read by END_5.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const PANEL end_500_bg1_cell_tbl[];
extern const s16 timer_5_tbl[];
extern const s16 end_5_pos[][2];

/* provisional name */
const PANEL end_500_bg1_cell_tbl[8] = {
    { 0x80, 11 }, { 0xC0, 12 }, { 0x1000, 15 }, { 0x1040, 16 }, { 0x2000, 1 }, { 0x2040, 2 }, { 0x3000, 7 }, { 0x3040, 8 },
};

const s16 timer_5_tbl[6] = {
    300, 600, 360, 780, 150, 1020,
};

const s16 end_5_pos[6][2] = {
    { 256, 768 }, { 768, 768 }, { 256, 512 }, { 768, 512 }, { 256, 256 }, { 256, 0 },
};
