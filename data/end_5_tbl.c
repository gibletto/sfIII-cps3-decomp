/*
 * END_5_TBL.C  Necro's ending BG0 cells (ending 5)
 *
 * end_500_bg0_cell_tbl lists the BG0 cells (map offset, cell number) written by
 * end_500_cell_set at the start of the ending; its BG1 cells and scene tables are in
 * END_5_TBL_B.C. Read by END_5.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const PANEL end_500_bg0_cell_tbl[];

const PANEL end_500_bg0_cell_tbl[12] = {
    { 0, 9 }, { 0x40, 10 }, { 0x80, 13 }, { 0xC0, 14 }, { 0x1080, 1 }, { 0x10C0, 2 }, { 0x2000, 3 }, { 0x2040, 4 },
    { 0x3000, 5 }, { 0x3040, 6 }, { 0x3080, 5 }, { 0x30C0, 6 },
};
