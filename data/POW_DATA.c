/*
 * POW_DATA.C  score award table
 *
 * Score_Data is the list of score amounts a player can be awarded (0, 10, ... 100, 200, ...
 * 3400), indexed by score kind. Read by POW_POW.C, damage and score, which adds them to the
 * players' scores.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s32 Score_Data[];

const s32 Score_Data[44] = {
    0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600,
    700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200,
    2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400,
};
