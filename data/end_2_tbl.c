/*
 * END_2_TBL.C  tables read by end_2.c: the ending panels and timers of end_2
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const PANEL end_200_panel0[];
extern const s16 timer_2_tbl[];

const PANEL end_200_panel0[8] = {
    { 0, 3 }, { 64, 4 }, { 128, 5 }, { 192, 6 }, { 4096, 7 }, { 4160, 8 }, { 4224, 10 }, { 4288, 11 },
};

const s16 timer_2_tbl[4] = {
    420, 360, 180, 1200,
};
