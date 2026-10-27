/*
 * TA_SUB_TBL.C  stage object hit box tables
 *
 * eff_hit_data gives the hit box (offset and size) of each stage object type and pl_hit_eff
 * each character's box against them, checked while a player is knocked through the stage. Read
 * by eff_hit_check_sub in TA_SUB.C, the stage object helpers.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff_hit_data[][4];
extern const s16 pl_hit_eff[][4];

const s16 eff_hit_data[11][4] = {
    { -159, 48, 65, 93 }, { 90, 63, 98, 45 }, { 5, 61, 41, 40 }, { -117, 87, 19, 42 },
    { -135, 25, 18, 37 }, { 33, 81, 58, 44 }, { -53, 39, 20, 25 }, { 6, 64, 33, 69 },
    { 12, 61, 16, 28 }, { -28, 17, 21, 36 }, { -28, 17, 21, 36 },
};

const s16 pl_hit_eff[13][4] = {
    { -11, 56, 33, 38 },  /* Gill */
    { -11, 56, 35, 53 },  /* Alex */
    { -13, 47, 50, 38 },  /* Ryu */
    { -18, 42, 36, 32 },  /* Yun */
    { -24, 48, 40, 48 },  /* Dudley */
    { -21, 48, 37, 42 },  /* Necro */
    { -13, 47, 50, 38 },  /* Hugo */
    { -22, 38, 36, 36 },  /* Ibuki */
    { -13, 47, 50, 38 },  /* Elena */
    { -28, 50, 28, 34 },  /* Oro */
    { -18, 42, 36, 32 },  /* Yang */
    { -13, 47, 50, 38 },  /* Ken */
    { -13, 47, 50, 38 },  /* Sean */
};
