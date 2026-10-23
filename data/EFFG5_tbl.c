/*
 * EFFG5_TBL.C  tables read by EFFG5.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 num_of_ase[];
extern const s16 ase_dir_hosei[][6];
extern const s16 ase_speed_hosei[][6];
extern const s16 ase_delta_hosei[][6];

const s16 num_of_ase[4] = {
    2, 4, 6, 6,
};

const s16 ase_dir_hosei[4][6] = {
    { -2, 3, -1, 30, 1, 33 }, { 2, -3, 1, 33, -1, 30 }, { 1, -2, 2, 34, 0, 31 }, { -1, 2, -2, 31, 0, 34 },
};

const s16 ase_speed_hosei[4][6] = {
    { 960, 1216, 1408, 832, 1728, 864 }, { 1024, 1120, 1536, 960, 1792, 864 },
    { 960, 1216, 1408, 832, 1728, 992 }, { 1024, 1120, 1536, 960, 1792, 992 },
};

const s16 ase_delta_hosei[4][6] = {
    { -64, -72, -80, -72, -88, -52 }, { -64, -72, -80, -72, -88, -52 },
    { -64, -72, -80, -72, -88, -52 }, { -64, -72, -80, -72, -88, -52 },
};
