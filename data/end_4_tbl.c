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
    { 0, 82 }, { 64, 83 }, { 128, 84 }, { 192, 85 }, { 4096, 80 }, { 4160, 81 }, { 4224, 0 }, { 4288, 0 },
    { 8192, 78 }, { 8256, 79 },
};

const PANEL end_400_panel1[10] = {
    { 0, 76 }, { 64, 77 }, { 128, 52 }, { 192, 53 }, { 4096, 52 }, { 4160, 53 }, { 4224, 0 }, { 4288, 0 },
    { 8192, 0 }, { 8256, 0 },
};

const s16 timer_4_tbl[5] = {
    540, 360, 180, 600, 480,
};

const s16 end_4_pos[5][2] = {
    { 256, 768 }, { 256, 512 }, { 768, 768 }, { 256, 256 }, { 256, 256 },
};
