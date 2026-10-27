/*
 * TASKSW_TBL.C  boot settings and region table
 *
 * boot_setting_defaults gives the starting free play, area type and alternate area flag, and
 * region_area_tbl maps the BIOS region code to the area type. Read by reset_entry in
 * RESET.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s8 boot_setting_defaults[];
extern const s32 region_area_tbl[];

const s8 boot_setting_defaults[4] = {
    1, 0, 0, 24,
};

const s32 region_area_tbl[8] = {
    0, 0, 2, 5, 1, 3, 4, 1,
};
