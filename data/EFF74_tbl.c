/*
 * EFF74_TBL.C  tables read by EFF74.c: the birds of effect 74: their placement and flight
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff74_data_tbl[][3];
extern const s32 eff74_move_tbl[][6];

const s16 eff74_data_tbl[4][3] = {
    { 567, 288, 80 }, { 396, 320, 79 }, { 502, 337, 79 }, { 535, 313, 79 },
};

const s32 eff74_move_tbl[8][6] = {
    { 0, 33, 0, 0, 0, 0 },
    { 1, 32, 294912, 512, -32768, -256 },
    { 2, 36, -294912, -256, 0, -256 },
    { 2, 36, -425984, -512, 0, -256 },
    { 1, 32, 491520, 0, 256, 0 },
    { 0, 37, 0, 0, 0, 0 },
    { 1, 32, 491520, -163840, 0, 8192 },
    { 2, 36, -491520, -294912, -1024, 12288 },
};
