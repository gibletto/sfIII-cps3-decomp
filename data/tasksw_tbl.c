/*
 * TASKSW_TBL.C  boot settings and region table
 *
 * boot_setting_defaults gives the starting free play, area type and alternate area flag, and
 * region_area_tbl maps the BIOS region code to the area type. Read by _reset_entry in
 * TASKSW.SRC.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 boot_setting_defaults[];
extern const s16 region_area_tbl[];

const s16 boot_setting_defaults[2] = {
    256, 24,
};

const s16 region_area_tbl[16] = {
    0, 0, 0, 0, 0, 2, 0, 5, 0, 1, 0, 3, 0, 4, 0, 1,
};
