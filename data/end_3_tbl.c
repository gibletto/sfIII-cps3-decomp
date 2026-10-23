/*
 * END_3_TBL.C  tables read by end_3.c: the ending panels, positions and timers of end_3
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const PANEL end_300_panel[];
extern const s16 end_3_pos[][2];
extern const s16 timer_3_tbl[];

const PANEL end_300_panel[8] = {
    { 0, 3 }, { 64, 4 }, { 128, 5 }, { 192, 6 }, { 4096, 7 }, { 4160, 8 }, { 4224, 10 }, { 4288, 11 },
};

const s16 end_3_pos[9][2] = {
    { 176, 784 }, { 736, 768 }, { 256, 512 }, { 256, 256 }, { 256, 512 }, { 176, 768 }, { 752, 768 }, { 256, 512 },
    { 768, 512 },
};

const s16 timer_3_tbl[10] = {
    190, 190, 360, 420, 360, 180, 180, 180, 480, 2313,
};
