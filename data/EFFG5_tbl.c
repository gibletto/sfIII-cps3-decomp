/*
 * EFFG5_TBL.C  flying drop burst tables for effect G5
 *
 * num_of_ase gives how many drops each burst size spawns (2, 4, 6 or 6); ase_dir_hosei,
 * ase_speed_hosei and ase_delta_hosei are four random sets of the drops' direction offsets,
 * speeds and slow-down, six per set. Read by EFFG5.C (setup_ase_extra), the burst of small
 * flying drops.
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
