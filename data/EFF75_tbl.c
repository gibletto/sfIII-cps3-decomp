/*
 * EFF75_TBL.C  tables read by EFF75.c: stage object 75's directions and priorities
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff75_dir_tbl[];
extern const s16 eff75_prio_tbl[];

const s16 eff75_dir_tbl[22] = {
    480, 304, 288, 272, 256, 224, 208, 192, 176, 160, 144, 128, 112, 64, 32, 16,
    8, 8, 4, 4, 2, 1,
};

const s16 eff75_prio_tbl[22] = {
    86, 86, 87, 87, 88, 89, 90, 91, 92, 93, 94, 96, 96, 96, 96, 96,
    96, 96, 96, 96, 96, 96,
};
