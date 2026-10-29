/*
 * EFF83_TBL.C  background objects crossing the stage
 *
 * eff83_data_tbl gives, for each of the three objects, its eight successive entries (pattern,
 * x, y, priority), and eff83_speed_tbl the x speed of each entry. Read by EFF83.C, the three
 * background objects crossing the stage.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s32 eff83_speed_tbl[][8];
extern const s16 eff83_data_tbl[][8][4];

const s32 eff83_speed_tbl[3][8] = {
    { 0x1800, 0x2800, 0x1A00, 0x800, 0x800, 0x1000, 0xA00, 0x2000 },
    { 0x1A00, 0x2C00, 0x2000, 0x1800, 0xA00, 0x1A00, 0x1000, 0x2000 },
    { 0x2000, 0x3000, 0x2200, 0x1000, 0x1000, 0x1800, 0xF00, 0x2800 },
};

const s16 eff83_data_tbl[3][8][4] = {
    {
        { 7, 200, 292, 102 }, { 9, 200, 292, 102 }, { 8, 200, 292, 102 }, { 7, 200, 292, 102 },
        { 8, 200, 248, 102 }, { 9, 248, 288, 102 }, { 10, 200, 292, 102 }, { 7, 200, 292, 102 },
    },
    {
        { 9, 240, 284, 102 }, { 8, 240, 268, 102 }, { 7, 240, 268, 102 }, { 8, 240, 268, 102 },
        { 7, 240, 300, 102 }, { 10, 240, 268, 102 }, { 7, 240, 268, 102 }, { 9, 264, 268, 102 },
    },
    {
        { 10, 288, 240, 100 }, { 7, 290, 240, 100 }, { 10, 290, 264, 100 }, { 8, 288, 240, 100 },
        { 8, 216, 248, 102 }, { 10, 288, 240, 100 }, { 7, 288, 240, 100 }, { 10, 288, 256, 100 },
    },
};
