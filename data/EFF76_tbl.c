/*
 * EFF76_TBL.C  tables read by EFF76.c: stage object 76's directions and priorities
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff76_dir_tbl[];
extern const s16 eff76_prio_tbl[];

const s16 eff76_dir_tbl[22] = {
    1120, 896, 640, 512, 384, 352, 320, 288, 256, 224, 192, 152, 136, 128, 120, 112,
    104, 96, 88, 80, 72, 64,
};

const s16 eff76_prio_tbl[22] = {
    86, 86, 87, 87, 88, 89, 90, 91, 92, 93, 94, 96, 96, 96, 96, 96,
    96, 96, 96, 96, 96, 96,
};
