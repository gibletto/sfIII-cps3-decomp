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
    { 0x1000, 86 }, { 0x1040, 87 }, { 0x2000, 92 }, { 0x2040, 93 },
    { 0x2080, 96 }, { 0x20C0, 97 }, { 0x3080, 30 }, { 0x30C0, 31 },
};

const PANEL end_800_panel1[8] = {
    { 0x1000, 94 }, { 0x1040, 95 }, { 0x2000, 90 }, { 0x2040, 91 },
    { 0x2080, 94 }, { 0x20C0, 95 }, { 0x3080, 98 }, { 0x30C0, 99 },
};

const s16 timer_8_tbl[4] = {
    780, 300, 480, 480,
};

const s16 end_8_pos[4][2] = {
    { 256, 256 }, { 768, 256 }, { 256, 512 }, { 768, 0 },
};

const PANEL end_900_bg0_cell_tbl[7] = {
    { 0x2000, 1 }, { 0x2040, 2 }, { 0x2080, 3 }, { 0x3000, 4 }, { 0x3040, 5 }, { 0x3080, 6 }, { 0x30C0, 7 },
};
