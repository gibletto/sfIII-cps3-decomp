/*
 * END_8_TBL.C  Elena's ending tables (ending 8), with parts of endings 7 and 9
 *
 * end_800_panel0 and end_800_panel1 list the BG0 and BG1 cells (map offset, cell number)
 * written at the start of Elena's ending, reached through end_8_panel_p in OP_END_WORK.C;
 * timer_8_tbl is the length in frames of each of its four scenes and end_8_pos the BG x and y
 * of each scene, read by END_8.C. end_7_anm_tbl holds the cells of BG0's animation cycle in
 * Ibuki's ending, read by END_7.C, and end_900_bg0_cell_tbl the BG0 cells written at the start
 * of Oro's ending, read by END_9.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 end_7_anm_tbl[];
extern const PANEL end_800_panel0[];
extern const PANEL end_800_panel1[];
extern const s16 timer_8_tbl[];
extern const s16 end_8_pos[][2];
extern const PANEL end_900_bg0_cell_tbl[];

const s16 end_7_anm_tbl[8] = {
    74, 75, 76, 77, 78, 79, 80, 81,
};

const PANEL end_800_panel0[8] = {
    { 4096, 86 }, { 4160, 87 }, { 8192, 92 }, { 8256, 93 },
    { 8320, 96 }, { 8384, 97 }, { 12416, 30 }, { 12480, 31 },
};

const PANEL end_800_panel1[8] = {
    { 4096, 94 }, { 4160, 95 }, { 8192, 90 }, { 8256, 91 },
    { 8320, 94 }, { 8384, 95 }, { 12416, 98 }, { 12480, 99 },
};

const s16 timer_8_tbl[4] = {
    780, 300, 480, 480,
};

const s16 end_8_pos[4][2] = {
    { 256, 256 }, { 768, 256 }, { 256, 512 }, { 768, 0 },
};

const PANEL end_900_bg0_cell_tbl[7] = {
    { 8192, 1 }, { 8256, 2 }, { 8320, 3 }, { 12288, 4 }, { 12352, 5 }, { 12416, 6 }, { 12480, 7 },
};
