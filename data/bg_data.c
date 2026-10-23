/*
 * BG_DATA.C  tables read by bg000.c and CMD_MAIN.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 bg_index_tbl[][3];
extern const s16 etc_bg_limit_tbl[][6];
extern const s32 etc_bg_pos_tbl[][4][2];
extern const TM_STRING bg_test_menu_scr[];
extern const char str_AREA[];
extern const char str_BG_1[];
extern const char str_BG_1_POS_X[];
extern const char str_BG_1_POS_Y[];
extern const char str_BG_2[];
extern const char str_BG_2_POS_X[];
extern const char str_BG_2_POS_Y[];
extern const char str_BG_3[];
extern const char str_BG_3_POS_X[];
extern const char str_BG_3_POS_Y[];
extern const char str_BG_4[];
extern const char str_BG_4_POS_X[];
extern const char str_BG_4_POS_Y[];
extern const char str_STAGE_2[];

const s16 bg_index_tbl[14][3] = {
    { 0, 0, 0 }, { 1, 1, 1 }, { 3, 4, 4 }, { 5, 6, 6 },
    { 7, 8, 8 }, { 9, 9, 9 }, { 10, 10, 10 }, { 11, 12, 13 },
    { 14, 15, 15 }, { 16, 16, 16 }, { 18, 17, 17 }, { 4, 3, 3 },
    { 2, 2, 2 }, { 19, 19, 19 },
};

const s16 etc_bg_limit_tbl[5][6] = {
    { 256, 256, 312, 0, 0, 0 }, { 256, 256, 312, 0, 0, 0 }, { 256, 256, 312, 0, 0, 0 }, { 256, 256, 312, 0, 0, 0 },
    { 256, 256, 312, 0, 0, 0 },
};

const s32 etc_bg_pos_tbl[5][4][2] = {
    { { 33554432, 0 }, { 33554432, 0 }, { 0, 0 }, { 0, 0 } },
    { { 33554432, 0 }, { 33554432, 0 }, { 0, 0 }, { 0, 0 } },
    { { 33554432, 0 }, { 33554432, 0 }, { 0, 0 }, { 0, 0 } },
    { { 33554432, 0 }, { 33554432, 0 }, { 0, 0 }, { 0, 0 } },
    { { 33554432, 0 }, { 33554432, 0 }, { 0, 0 }, { 0, 0 } },
};

/* nothing in the program refers to it (provisional name) */
const TM_STRING bg_test_menu_scr[14] = {
    { 0x1E, 0x14, 0xE, (const s8 *)str_BG_1_POS_X },
    { 0x1E, 0x15, 0xE, (const s8 *)str_BG_1_POS_Y },
    { 0x1E, 0x16, 0xE, (const s8 *)str_BG_2_POS_X },
    { 0x1E, 0x17, 0xE, (const s8 *)str_BG_2_POS_Y },
    { 0x1E, 0x18, 0xE, (const s8 *)str_BG_3_POS_X },
    { 0x1E, 0x19, 0xE, (const s8 *)str_BG_3_POS_Y },
    { 0x1E, 0x1A, 0xE, (const s8 *)str_BG_4_POS_X },
    { 0x1E, 0x1B, 0xE, (const s8 *)str_BG_4_POS_Y },
    { 3, 0x16, 0xE, (const s8 *)str_BG_1 },
    { 3, 0x17, 0xE, (const s8 *)str_BG_2 },
    { 3, 0x18, 0xE, (const s8 *)str_BG_3 },
    { 3, 0x19, 0xE, (const s8 *)str_BG_4 },
    { 3, 0x13, 0xE, (const s8 *)str_STAGE_2 },
    { 3, 0x14, 0xE, (const s8 *)str_AREA },
};
