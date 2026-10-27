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
    { { 0x1C, 0xD, 0x16 }, 0, 1, 0, 0, 0x186A0 },
    { { 0x1C, 0xE, 0x1D }, 0, 5, 0, 0, 0x15F90 },
    { { 0x11, 0x1B, 0xA }, 0, 4, 0, 0, 0x13880 },
    { { 0x18, 0xB, 0xA }, 0, 0xA, 0, 0, 0x11170 },
    { { 0x18, 0x17, 0x1E }, 0, 8, 0, 0, 0xEA60 },
    { { 0x10, 0xE, 0x18 }, 0, 9, 0, 0, 0xC350 },
    { { 0x14, 0xA, 0x12 }, 0, 0xB, 0, 0, 7 },
    { { 0x15, 0x1D, 1 }, 0, 2, 0, 0, 6 },
    { { 0x22, 0x1E, 0x14 }, 0, 7, 0, 0, 5 },
    { { 0x1B, 0xA, 0x18 }, 0, 7, 0, 0, 4 },
    { { 0x22, 0x18, 0x13 }, 0, 3, 0, 0, 3 },
    { { 0x22, 0x18, 0x14 }, 0, 9, 0, 0, 2 },
};
