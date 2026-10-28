/*
 * END_4_TBL.C  Dudley's ending tables (ending 4)
 *
 * end_400_panel0 and end_400_panel1 list the BG0 and BG1 cells (map offset, cell number)
 * written by end_400_cell_set at the start of the ending, reached through end_4_panel_p in
 * OP_END_WORK.C. timer_4_tbl is the length in frames of each of the five scenes and end_4_pos
 * the BG x and y of each scene. Read by END_4.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const PANEL end_400_panel0[];
extern const PANEL end_400_panel1[];
extern const s16 timer_4_tbl[];
extern const s16 end_4_pos[][2];

const PANEL end_400_panel0[10] = {
    { 0, 82 }, { 0x40, 83 }, { 0x80, 84 }, { 0xC0, 85 }, { 0x1000, 80 }, { 0x1040, 81 }, { 0x1080, 0 }, { 0x10C0, 0 },
    { 0x2000, 78 }, { 0x2040, 79 },
};

const PANEL end_400_panel1[10] = {
    { 0, 76 }, { 0x40, 77 }, { 0x80, 52 }, { 0xC0, 53 }, { 0x1000, 52 }, { 0x1040, 53 }, { 0x1080, 0 }, { 0x10C0, 0 },
    { 0x2000, 0 }, { 0x2040, 0 },
};

const s16 timer_4_tbl[5] = {
    540, 360, 180, 600, 480,
};

const s16 end_4_pos[5][2] = {
    { 256, 768 }, { 256, 512 }, { 768, 768 }, { 256, 256 }, { 256, 256 },
};
