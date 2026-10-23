/*
 * EFFB1_TBL.C  tables read by effb3.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effb3_round_tbl[][2];
extern const s16 effb3_final_tbl[][2];
extern const s16 effb3_fight_tbl[][3];

const s16 effb3_round_tbl[5][2] = {
    { 1, -56 }, { 2, -36 }, { 3, -16 }, { 4, 6 }, { 5, 28 },
};

const s16 effb3_final_tbl[10][2] = {
    { 1, -96 }, { 2, -78 }, { 3, -64 }, { 4, -46 }, { 5, -22 }, { 6, 8 }, { 7, 28 }, { 8, 48 },
    { 9, 68 }, { 10, 92 },
};

const s16 effb3_fight_tbl[6][3] = {
    { 1, -48, -64 }, { 2, -32, -47 }, { 3, -16, -42 }, { 4, 0, 4 },
    { 5, 16, 58 }, { 6, 32, 63 },
};
