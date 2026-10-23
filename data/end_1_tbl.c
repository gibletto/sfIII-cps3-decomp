/*
 * END_1_TBL.C  tables read by end_1.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const PANEL end_100_panel0[];
extern const PANEL end_100_panel1[];
extern const s16 timer_1_tbl[];
extern const s16 end_1_pos[][2];

const PANEL end_100_panel0[8] = {
    { 8192, 1 }, { 8256, 2 }, { 8320, 5 }, { 8384, 6 },
    { 12288, 7 }, { 12352, 8 }, { 12416, 11 }, { 12480, 12 },
};

const PANEL end_100_panel1[4] = {
    { 8320, 3 }, { 8384, 4 }, { 12416, 9 }, { 12480, 10 },
};

const s16 timer_1_tbl[8] = {
    1140, 240, 240, 240, 240, 480, 480, 600,
};

const s16 end_1_pos[8][2] = {
    { 256, 256 }, { 336, 256 }, { 256, 256 }, { 768, 256 }, { 768, 256 }, { 768, 256 }, { 256, 0 }, { 768, 0 },
};
