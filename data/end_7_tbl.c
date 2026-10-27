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

const PANEL end_700_panel0[16] = {
    { 0, 18 }, { 64, 19 }, { 128, 16 }, { 192, 17 },
    { 4096, 14 }, { 4160, 15 }, { 4224, 24 }, { 4288, 25 },
    { 8192, 1 }, { 8256, 2 }, { 8320, 32 }, { 8384, 33 },
    { 12288, 36 }, { 12352, 37 }, { 12416, 40 }, { 12480, 41 },
};

const PANEL end_700_panel1[14] = {
    { 0, 46 }, { 64, 47 }, { 128, 22 }, { 192, 23 },
    { 4096, 20 }, { 4160, 21 }, { 4224, 12 }, { 4288, 13 },
    { 8192, 28 }, { 8256, 29 }, { 8320, 34 }, { 8384, 35 },
    { 12288, 38 }, { 12352, 39 },
};

const s16 timer_7_tbl[12] = {
    180, 180, 1080, 180, 60, 180, 120, 120, 60, 180, 540, 300,
};

const s16 end_7_pos[12][2] = {
    { 768, 768 }, { 256, 768 }, { 256, 512 }, { 256, 768 }, { 768, 768 }, { 256, 768 }, { 256, 256 }, { 256, 256 },
    { 256, 256 }, { 768, 256 }, { 256, 0 }, { 768, 0 },
};
