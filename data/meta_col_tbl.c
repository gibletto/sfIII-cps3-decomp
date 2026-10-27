/*
 * META_COL_TBL.C  BCD weights and screen mode register tables
 *
 * bcd_weight holds the four-byte BCD values of 2^0 .. 2^15, which hex_to_bcd in META_COL_BCD.C
 * reads backwards from bcd_weight_end; bcd_weight_end holds those of 2^16 .. 2^26. Per screen
 * mode, screen_window_tbl gives the window register values, screen_origin_tbl the screen base
 * position, screen_disp_reg_tbl the display register values and screen_flip_ofs_tbl the
 * object, screen, scroll and zoom offsets used when the monitor is flipped; these are read by
 * SCRN_CTRL.C, the screen mode, window and zoom registers.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u8 bcd_weight[];
extern const u8 bcd_weight_end[];
extern const s16 screen_window_tbl[][9];
extern const s16 screen_origin_tbl[][2];
extern const s16 screen_disp_reg_tbl[][4];
extern const s16 screen_flip_ofs_tbl[][8];

const u8 bcd_weight[64] = {
    0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 8,
    0, 0, 0, 0x16, 0, 0, 0, 0x32, 0, 0, 0, 0x64, 0, 0, 1, 0x28,
    0, 0, 2, 0x56, 0, 0, 5, 0x12, 0, 0, 0x10, 0x24, 0, 0, 0x20, 0x48,
    0, 0, 0x40, 0x96, 0, 0, 0x81, 0x92, 0, 1, 0x63, 0x84, 0, 3, 0x27, 0x68,
};

const u8 bcd_weight_end[44] = {
    0, 6, 0x55, 0x36, 0, 0x13, 0x10, 0x72, 0, 0x26, 0x21, 0x44, 0, 0x52, 0x42, 0x88,
    1, 4, 0x85, 0x76, 2, 9, 0x71, 0x52, 4, 0x19, 0x43, 4, 8, 0x38, 0x86, 8,
    0x16, 0x77, 0x72, 0x16, 0x33, 0x55, 0x44, 0x32, 0x67, 0x10, 0x88, 0x64,
};

const s16 screen_window_tbl[8][9] = {
    { 38, 80, 379, 454, 3, 21, 245, 262, 96 },
    { 35, 83, 411, 454, 3, 21, 245, 262, 97 },
    { 35, 92, 448, 454, 3, 21, 246, 262, 98 },
    { 42, 111, 495, 454, 3, 21, 245, 262, 99 },
    { 35, 98, 497, 454, 3, 21, 245, 262, 99 },
    { 35, 114, 551, 454, 3, 21, 245, 262, 100 },
    { 42, 143, 618, 454, 3, 21, 245, 262, 101 },
    { 35, 118, 613, 454, 3, 21, 245, 262, 101 },
};

const s16 screen_origin_tbl[8][2] = {
    { -65, -19 }, { 0, 0 }, { -80, -35 }, { -101, -24 },
    { 0, 0 }, { -114, -36 }, { 0, 0 }, { -107, -24 },
};

const s16 screen_disp_reg_tbl[8][4] = {
    { 46, 0, 152, 1 }, { 46, 0, 187, 1 }, { 49, 0, 229, 1 }, { 62, 0, 22, 2 },
    { 54, 0, 22, 2 }, { 58, 0, 83, 2 }, { 74, 0, 159, 2 }, { 64, 0, 159, 2 },
};

const s16 screen_flip_ofs_tbl[8][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 261, 128, 288, 0, 265, 128, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 262, 0, 288, 0, 265, 0, 0 },
};
