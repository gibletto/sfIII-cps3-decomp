/*
 * BG_SUB_TBL.C  background test stage list and zoom rates
 *
 * bg_test_stage_tbl is the stage and area of each entry the debug background test steps
 * through (ending in -1); read by TATE00.C, the stage background control task.
 * bg_zoom_rate_tbl is the zoom step per frame of the background zoom, by zoom position; read
 * by BG000.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s8 bg_test_stage_tbl[][2];
extern const s16 bg_zoom_rate_tbl[];

const s8 bg_test_stage_tbl[18][2] = {
    { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 }, { 3, 0 }, { 3, 1 }, { 4, 0 }, { 4, 1 },
    { 5, 0 }, { 6, 0 }, { 7, 0 }, { 7, 1 }, { 7, 2 }, { 8, 0 }, { 8, 1 }, { 9, 0 },
    { 12, 0 }, { -1, -1 },
};

/* provisional name */
const s16 bg_zoom_rate_tbl[112] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 2, 0, 1, 1, 1, 1, 1, 1, 1, 2, 0, 1, 1,
    1, 1, 1, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};
