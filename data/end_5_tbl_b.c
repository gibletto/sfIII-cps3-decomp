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

const PANEL end_500_bg1_cell_tbl[8] = {
    { 128, 11 }, { 192, 12 }, { 4096, 15 }, { 4160, 16 }, { 8192, 1 }, { 8256, 2 }, { 12288, 7 }, { 12352, 8 },
};

const s16 timer_5_tbl[6] = {
    300, 600, 360, 780, 150, 1020,
};

const s16 end_5_pos[6][2] = {
    { 256, 768 }, { 768, 768 }, { 256, 512 }, { 768, 512 }, { 256, 256 }, { 256, 0 },
};
