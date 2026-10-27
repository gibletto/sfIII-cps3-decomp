/*
 * DEMO02_CODE_DATA.C  demonstration play characters, super arts and stages
 *
 * Demo_PL_Play_Data lists the character pairs of the demonstration fights (two per fight, five
 * fights), Demo_Stage_Play_Data the stage of each fight, and Arts_Rnd_Demo_Data the super arts
 * a demonstration fighter is given at random. Demo_PL_Data is the player side that takes the
 * controls in each character select demonstration. Read by DEMO02_CODE.C, the attract mode
 * demonstration play.
 */

#include "types.h"
#include "structs.h"
#include "fighter.h"

#pragma section TBL

extern const s8 Demo_PL_Play_Data[];
extern const u8 Arts_Rnd_Demo_Data[];
extern const s8 Demo_Stage_Play_Data[];
extern const s8 Demo_PL_Data[];

const s8 Demo_PL_Play_Data[10] = {
    PL_ALEX, PL_RYU, PL_IBUKI, PL_DUDLEY, PL_NECRO, PL_IBUKI, PL_RYU, PL_NECRO, PL_RYU, PL_KEN,
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
