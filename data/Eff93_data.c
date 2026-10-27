/*
 * EFF93_DATA.C  ending scene BG 3 screen record
 *
 * effb0_scr_record_data is the screen record list that effect B0 passes to sprite_list_setup
 * when it sets up BG 3 for the scene changes of an ending. Read by EFFB0.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effb0_scr_record_data[];

const s16 effb0_scr_record_data[14] = {
    4, 88, 127, 32512, 60, 255, 32512, 60, 383, 32512, 60, -1, -1, 0,
};
