/*
 * END_2_TBL.C  Ryu's ending tables (ending 2)
 *
 * end_200_panel0 lists the BG0 cells (map offset, cell number) written by end_200_cell_set at
 * the start of the ending, and timer_2_tbl the length in frames of each of its four scenes.
 * Read by END_2.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const PANEL end_200_panel0[];
extern const s16 timer_2_tbl[];

const PANEL end_200_panel0[8] = {
    { 0, 3 }, { 0x40, 4 }, { 0x80, 5 }, { 0xC0, 6 }, { 0x1000, 7 }, { 0x1040, 8 }, { 0x1080, 10 }, { 0x10C0, 11 },
};

const s16 timer_2_tbl[4] = {
    420, 360, 180, 1200,
};
