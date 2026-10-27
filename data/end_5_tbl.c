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
    { 0, 9 }, { 64, 10 }, { 128, 13 }, { 192, 14 }, { 4224, 1 }, { 4288, 2 }, { 8192, 3 }, { 8256, 4 },
    { 12288, 5 }, { 12352, 6 }, { 12416, 5 }, { 12480, 6 },
};
