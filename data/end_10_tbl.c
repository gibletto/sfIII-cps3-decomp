/*
 * END_10_TBL.C  Ken's ending tables (ending 10), and ending 11's cell pairs
 *
 * end_10_panel_tbl_0 and end_10_panel_tbl_1 list the BG0 and BG1 cells (map offset, cell
 * number) written at the start of Ken's ending, reached through end_10_panel_p in
 * OP_END_WORK.C; timer_10_tbl is the length in frames of each of its seven scenes, end_10_pos
 * the BG x and y of each scene and end_10_anm_tbl the steps of the BG0 animation cycle, read
 * by END_10.C. end_1100_cell0 .. end_1100_cell7 are the cell pairs Sean's ending (END_11.C)
 * writes per scene, reached through end_11_cell_ptr0 and end_11_cell_ptr1 in OP_END_WORK.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const PANEL end_10_panel_tbl_0[];
extern const PANEL end_10_panel_tbl_1[];
extern const s16 timer_10_tbl[];
extern const s16 end_10_pos[][2];
extern const s16 end_10_anm_tbl[];
extern const s32 end_1100_cell0[];
extern const s32 end_1100_cell1[];
extern const s32 end_1100_cell2[];
extern const s32 end_1100_cell3[];
extern const s32 end_1100_cell4[];
extern const s32 end_1100_cell5[];
extern const s32 end_1100_cell6[];
extern const s32 end_1100_cell7[];

const PANEL end_10_panel_tbl_0[16] = {
    { 0, 62 }, { 64, 63 }, { 128, 50 }, { 192, 51 },
    { 4096, 66 }, { 4160, 67 }, { 4224, 64 }, { 4288, 65 },
    { 8192, 68 }, { 8256, 69 }, { 8320, 72 }, { 8384, 73 },
    { 12288, 70 }, { 12352, 71 }, { 12416, 74 }, { 12480, 75 },
};

const PANEL end_10_panel_tbl_1[16] = {
    { 0, 48 }, { 64, 49 }, { 128, 48 }, { 192, 49 },
    { 4096, 52 }, { 4160, 53 }, { 4224, 54 }, { 4288, 55 },
    { 8192, 56 }, { 8256, 57 }, { 8320, 60 }, { 8384, 61 },
    { 12288, 58 }, { 12352, 59 }, { 12416, 48 }, { 12480, 49 },
};

const s16 timer_10_tbl[7] = {
    300, 180, 240, 240, 540, 300, 360,
};

const s16 end_10_pos[7][2] = {
    { 256, 768 }, { 768, 768 }, { 256, 512 }, { 720, 512 }, { 256, 256 }, { 720, 256 }, { 768, 0 },
};

const s16 end_10_anm_tbl[5] = {
    2, 3, 4, 5, 0,
};

const s32 end_1100_cell0[4] = {
    12352, 5, 12416, 6,
};

const s32 end_1100_cell1[4] = {
    12352, 13, 12416, 14,
};

const s32 end_1100_cell2[4] = {
    12352, 11, 12416, 12,
};

const s32 end_1100_cell3[4] = {
    12352, 7, 12416, 8,
};

const s32 end_1100_cell4[4] = {
    12352, 1, 12416, 2,
};

const s32 end_1100_cell5[4] = {
    12352, 9, 12416, 10,
};

const s32 end_1100_cell6[4] = {
    12352, 5, 12416, 6,
};

const s32 end_1100_cell7[4] = {
    12352, 1, 12416, 2,
};
