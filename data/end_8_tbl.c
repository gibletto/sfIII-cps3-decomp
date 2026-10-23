/*
 * END_8_TBL.C  tables read by end_7.c, end_8.c and end_9.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 end_7_anm_tbl[];
extern const PANEL end_800_panel0[];
extern const PANEL end_800_panel1[];
extern const s16 timer_8_tbl[];
extern const s16 end_8_pos[][2];
extern const PANEL end_900_bg0_cell_tbl[];

const s16 end_7_anm_tbl[8] = {
    74, 75, 76, 77, 78, 79, 80, 81,
};

const PANEL end_800_panel0[8] = {
    { 4096, 86 }, { 4160, 87 }, { 8192, 92 }, { 8256, 93 },
    { 8320, 96 }, { 8384, 97 }, { 12416, 30 }, { 12480, 31 },
};

const PANEL end_800_panel1[8] = {
    { 4096, 94 }, { 4160, 95 }, { 8192, 90 }, { 8256, 91 },
    { 8320, 94 }, { 8384, 95 }, { 12416, 98 }, { 12480, 99 },
};

const s16 timer_8_tbl[4] = {
    780, 300, 480, 480,
};

const s16 end_8_pos[4][2] = {
    { 256, 256 }, { 768, 256 }, { 256, 512 }, { 768, 0 },
};

const PANEL end_900_bg0_cell_tbl[7] = {
    { 8192, 1 }, { 8256, 2 }, { 8320, 3 }, { 12288, 4 }, { 12352, 5 }, { 12416, 6 }, { 12480, 7 },
};
