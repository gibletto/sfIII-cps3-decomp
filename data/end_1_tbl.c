/*
 * END_1_TBL.C  Alex's ending tables (ending 1)
 *
 * end_100_panel0 and end_100_panel1 list the BG0 and BG1 cells (map offset, cell number)
 * written by end_100_cell_set at the start of the ending, timer_1_tbl the length in frames of
 * each of its eight scenes and end_1_pos the BG0 x and y of each scene. Read by END_1.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const PANEL end_100_panel0[];
extern const PANEL end_100_panel1[];
extern const s16 timer_1_tbl[];
extern const s16 end_1_pos[][2];

const PANEL end_100_panel0[8] = {
    { 0x2000, 1 }, { 0x2040, 2 }, { 0x2080, 5 }, { 0x20C0, 6 },
    { 0x3000, 7 }, { 0x3040, 8 }, { 0x3080, 11 }, { 0x30C0, 12 },
};

const PANEL end_100_panel1[4] = {
    { 0x2080, 3 }, { 0x20C0, 4 }, { 0x3080, 9 }, { 0x30C0, 10 },
};

const s16 timer_1_tbl[8] = {
    1140, 240, 240, 240, 240, 480, 480, 600,
};

const s16 end_1_pos[8][2] = {
    { 256, 256 }, { 336, 256 }, { 256, 256 }, { 768, 256 }, { 768, 256 }, { 768, 256 }, { 256, 0 }, { 768, 0 },
};
