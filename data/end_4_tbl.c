/*
 * END_4_TBL.C  tables read by end_4.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const PANEL end_400_panel0[];
extern const PANEL end_400_panel1[];
extern const s16 timer_4_tbl[];
extern const s16 end_4_pos[][2];

const PANEL end_400_panel0[10] = {
    { 0, 82 }, { 64, 83 }, { 128, 84 }, { 192, 85 }, { 4096, 80 }, { 4160, 81 }, { 4224, 0 }, { 4288, 0 },
    { 8192, 78 }, { 8256, 79 },
};

const PANEL end_400_panel1[10] = {
    { 0, 76 }, { 64, 77 }, { 128, 52 }, { 192, 53 }, { 4096, 52 }, { 4160, 53 }, { 4224, 0 }, { 4288, 0 },
    { 8192, 0 }, { 8256, 0 },
};

const s16 timer_4_tbl[5] = {
    540, 360, 180, 600, 480,
};

const s16 end_4_pos[5][2] = {
    { 256, 768 }, { 256, 512 }, { 768, 768 }, { 256, 256 }, { 256, 256 },
};
