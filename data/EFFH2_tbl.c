/*
 * EFFH2_TBL.C  tables read by EFFH2.c and EFFH3.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 panel_guide[][2];
extern const s16 effH3_data_tbl[][3];

const s16 panel_guide[8][2] = {
    { 0, 6 }, { 0, 5 }, { 0, 4 }, { 0, 2 }, { 0, 0 }, { 0, 2 }, { 0, 4 }, { 0, 5 },
};

const s16 effH3_data_tbl[5][3] = {
    { 512, 0, 0 }, { 256, 136, 2 }, { 768, 136, 2 }, { 256, 280, 2 },
    { 768, 280, 2 },
};
