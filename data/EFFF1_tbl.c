/*
 * EFFF1_TBL.C  another-BG switch tables for effect F1
 *
 * effF1_data_tbl has a row per switch number: end-condition flags, another-BG value, timer,
 * and two further end settings (dramatic-battle mode, shell gone). Read by EFFF1.C, the
 * another-BG switch control.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effF1_data_tbl[][5];

const s16 effF1_data_tbl[5][5] = {
    { 83, 1, 48, 1, 0 }, { 80, 1, 0, 0, 0 }, { 4, 1, 0, 0, 0 }, { 80, 1, 0, 1, 0 },
    { 0, 1, 0, 1, 1 },
};
