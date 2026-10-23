/*
 * END_9_TBL.C  tables read by end_9.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 timer_9_tbl[];
extern const s16 end_9_pos[][2];

const s16 timer_9_tbl[7] = {
    240, 240, 240, 180, 180, 180, 660,
};

const s16 end_9_pos[7][2] = {
    { 768, 256 }, { 768, 256 }, { 768, 256 }, { 768, 256 }, { 768, 256 }, { 768, 256 }, { 768, 48 },
};
