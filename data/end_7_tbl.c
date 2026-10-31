/*
 * END_7_TBL.C  Ibuki's ending tables (ending 7)
 *
 * end_700_panel0 and end_700_panel1 list the BG0 and BG1 cells (map offset, cell number)
 * written at the start of the ending, timer_7_tbl the length in frames of each of its twelve
 * scenes and end_7_pos the BG x and y of each scene. Read by END_7.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const PANEL end_700_panel0[];
extern const PANEL end_700_panel1[];
extern const s16 timer_7_tbl[];
extern const s16 end_7_pos[][2];

/* provisional name */
const PANEL end_700_panel0[16] = {
    { 0, 18 }, { 0x40, 19 }, { 0x80, 16 }, { 0xC0, 17 },
    { 0x1000, 14 }, { 0x1040, 15 }, { 0x1080, 24 }, { 0x10C0, 25 },
    { 0x2000, 1 }, { 0x2040, 2 }, { 0x2080, 32 }, { 0x20C0, 33 },
    { 0x3000, 36 }, { 0x3040, 37 }, { 0x3080, 40 }, { 0x30C0, 41 },
};

/* provisional name */
const PANEL end_700_panel1[14] = {
    { 0, 46 }, { 0x40, 47 }, { 0x80, 22 }, { 0xC0, 23 },
    { 0x1000, 20 }, { 0x1040, 21 }, { 0x1080, 12 }, { 0x10C0, 13 },
    { 0x2000, 28 }, { 0x2040, 29 }, { 0x2080, 34 }, { 0x20C0, 35 },
    { 0x3000, 38 }, { 0x3040, 39 },
};

const s16 timer_7_tbl[12] = {
    180, 180, 1080, 180, 60, 180, 120, 120, 60, 180, 540, 300,
};

const s16 end_7_pos[12][2] = {
    { 768, 768 }, { 256, 768 }, { 256, 512 }, { 256, 768 }, { 768, 768 }, { 256, 768 }, { 256, 256 }, { 256, 256 },
    { 256, 256 }, { 768, 256 }, { 256, 0 }, { 768, 0 },
};
