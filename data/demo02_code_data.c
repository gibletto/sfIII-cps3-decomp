/*
 * DEMO02_CODE_DATA.C  tables read by demo02_code.c: the demonstration's players, super arts and stages
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s8 Demo_PL_Play_Data[];
extern const u8 Arts_Rnd_Demo_Data[];
extern const s8 Demo_Stage_Play_Data[];
extern const s8 Demo_PL_Data[];

const s8 Demo_PL_Play_Data[10] = {
    1, 2, 7, 4, 5, 7, 2, 5, 2, 11,
};

const u8 Arts_Rnd_Demo_Data[8] = {
    0, 0, 0, 1, 1, 1, 2, 2,
};

const s8 Demo_Stage_Play_Data[5] = {
    2, 4, 7, 5, 11,
};

const s8 Demo_PL_Data[5] = {
    0, 1, 0, 1, 17,
};
