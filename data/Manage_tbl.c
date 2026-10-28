/*
 * MANAGE_TBL.C  default score ranking
 *
 * Rank_Default_Data is the 12 default RANK_DATA entries { initials, mark, character, flag,
 * colour, score } that Ranking_Init copies into the ranking. Read by RANKING.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const RANK_DATA Rank_Default_Data[];

const RANK_DATA Rank_Default_Data[12] = {
    { { 28, 13, 22 }, 0, 1, 0, 0, 100000 },
    { { 28, 14, 29 }, 0, 5, 0, 0, 90000 },
    { { 17, 27, 10 }, 0, 4, 0, 0, 80000 },
    { { 24, 11, 10 }, 0, 10, 0, 0, 70000 },
    { { 24, 23, 30 }, 0, 8, 0, 0, 60000 },
    { { 16, 14, 24 }, 0, 9, 0, 0, 50000 },
    { { 20, 10, 18 }, 0, 11, 0, 0, 7 },
    { { 21, 29, 1 }, 0, 2, 0, 0, 6 },
    { { 34, 30, 20 }, 0, 7, 0, 0, 5 },
    { { 27, 10, 24 }, 0, 7, 0, 0, 4 },
    { { 34, 24, 19 }, 0, 3, 0, 0, 3 },
    { { 34, 24, 20 }, 0, 9, 0, 0, 2 },
};
