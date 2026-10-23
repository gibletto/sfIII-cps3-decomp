/*
 * EFFC0_TBL.C  tables read by EFFC0.c and EFFC1.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 hok_table_ef[];
extern const s16 plhos_data[][3];
extern const s16 effC1_reverse_tbl[];
extern const s16 effC1_position_tbl[][5];

const s16 hok_table_ef[8] = {
    1, 1, 2, 2, 3, 3, 3, 3,
};

const s16 plhos_data[16][3] = {
    { 2, 136, 4 }, { 40, 92, 3 }, { -4, 104, 2 }, { 2, 92, 5 },
    { 40, 88, 5 }, { 8, 94, 2 }, { 0, 0, 2 }, { 20, 78, 2 },
    { 30, 96, 2 }, { 10, 88, 3 }, { 2, 92, 5 }, { -4, 104, 2 },
    { -4, 104, 5 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
};

const s16 effC1_reverse_tbl[5] = {
    4, 3, 2, 1, 0,
};

const s16 effC1_position_tbl[2][5] = {
    { 224, 384, 544, 672, 768 }, { 429, 528, 624, 704, 768 },
};
