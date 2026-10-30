/*
 * EFF14_TBL.C  background colour-cycle, falling stone and blinking object tables
 *
 * eff14_ofs_tbl is the map offset of each of the 11 colour-cycle ids' cell rectangle;
 * eff14_data_tbl gives each id its scroll layer, work slot, script (eff14_script_n: rows of
 * timer and colour, looping at a -1 timer), cell pattern mask (eff14_pattern_n, 1 = recolour)
 * and size in columns and rows (eff14_size_n). Read by EFF14.C, the background colour-cycle
 * writer.
 * eff15_data_tbl holds the position, priority, cell, side speed limit and floor of each
 * falling stone, and eff15_y_speed_tbl, eff15_x_speed_tbl, eff15_x_acc_tbl and
 * eff15_x_acc_tbl2 the random speeds it picks from; read by EFF15.C. eff16_data_tbl is the x,
 * y and cg number of each blinking object, read by EFF16.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

/* a script step: the frames it lasts, then the colour, a big-endian word (EFF14.C reads it with *(s16*)) */
#define EFF14_STEP(time, col)   0, (time), (s8)((col) >> 8), (s8)(col)
#define EFF14_END               -1, -1

extern const u16 eff14_ofs_tbl[];
extern const s8 eff14_script_0[];
extern const s8 eff14_script_1[];
extern const s8 eff14_script_2[];
extern const s8 eff14_script_3[];
extern const s8 eff14_script_4[];
extern const s8 eff14_script_9[];
extern const s8 eff14_script_10[];
extern const s8 eff14_pattern_0[];
extern const s8 eff14_size_0[];
extern const s8 eff14_pattern_1[];
extern const s8 eff14_size_1[];
extern const s8 eff14_pattern_2[];
extern const s8 eff14_size_2[];
extern const s8 eff14_pattern_3[];
extern const s8 eff14_size_3[];
extern const s8 eff14_pattern_4[];
extern const s8 eff14_size_4[];
extern const s8 eff14_pattern_5[];
extern const s8 eff14_size_5[];
extern const s8 eff14_pattern_6[];
extern const s8 eff14_size_6[];
extern const s8 eff14_pattern_7[];
extern const s8 eff14_size_7[];
extern const s8 eff14_pattern_8[];
extern const s8 eff14_size_8[];
extern const s8 eff14_pattern_9[];
extern const s8 eff14_size_9[];
extern const s8 eff14_pattern_10[];
extern const s8 eff14_size_10[];
extern const u32 eff14_data_tbl[][5];
extern const s16 eff15_data_tbl[];
extern const s32 eff15_y_speed_tbl[];
extern const s32 eff15_x_speed_tbl[];
extern const s32 eff15_x_acc_tbl[];
extern const s32 eff15_x_acc_tbl2[];
extern const s16 eff16_data_tbl[][4];

const u16 eff14_ofs_tbl[11] = {
    0x1660, 0x197C, 0x1894, 0x1584, 0x1688, 0x1494, 0xDA0, 0xAA8, 0xACC, 0x19B8, 0x1618,
};

const s8 eff14_script_0[52] = {
    EFF14_STEP(5, 0x54), EFF14_STEP(5, 0x55), EFF14_STEP(5, 0x56), EFF14_STEP(5, 0x57),
    EFF14_STEP(5, 0x58), EFF14_STEP(5, 0x59), EFF14_STEP(5, 0x5A), EFF14_STEP(5, 0x5B),
    EFF14_STEP(5, 0x5C), EFF14_STEP(5, 0x5D), EFF14_STEP(5, 0x5E), EFF14_STEP(5, 0x5F),
    EFF14_END, 0, 0,
};

const s8 eff14_script_1[16] = {
    EFF14_STEP(3, 0x59), EFF14_STEP(3, 0x60), EFF14_STEP(3, 0x61),
    EFF14_END, 0, 0,
};

const s8 eff14_script_2[16] = {
    EFF14_STEP(3, 0x52), EFF14_STEP(3, 0x5C), EFF14_STEP(3, 0x5D),
    EFF14_END, 0, 0,
};

const s8 eff14_script_3[16] = {
    EFF14_STEP(3, 0x41), EFF14_STEP(3, 0x5E), EFF14_STEP(3, 0x5F),
    EFF14_END, 0, 0,
};

const s8 eff14_script_4[28] = {
    EFF14_STEP(4, 0x45), EFF14_STEP(4, 0x49), EFF14_STEP(4, 0x4A), EFF14_STEP(4, 0x4B),
    EFF14_STEP(4, 0x4C), EFF14_STEP(4, 0x4D),
    EFF14_END, 0, 0,
};

const s8 eff14_script_9[108] = {
    EFF14_STEP(4, 0x43), EFF14_STEP(4, 0x4E), EFF14_STEP(4, 0x43), EFF14_STEP(4, 0x4E),
    EFF14_STEP(2, 0x43), EFF14_STEP(2, 0x4E), EFF14_STEP(4, 0x43), EFF14_STEP(4, 0x4E),
    EFF14_STEP(5, 0x43), EFF14_STEP(3, 0x4E), EFF14_STEP(4, 0x43), EFF14_STEP(4, 0x4E),
    EFF14_STEP(4, 0x43), EFF14_STEP(4, 0x4E), EFF14_STEP(6, 0x43), EFF14_STEP(5, 0x4E),
    EFF14_STEP(4, 0x43), EFF14_STEP(4, 0x4E), EFF14_STEP(4, 0x43), EFF14_STEP(4, 0x4E),
    EFF14_STEP(5, 0x43), EFF14_STEP(4, 0x4E), EFF14_STEP(4, 0x43), EFF14_STEP(4, 0x4E),
    EFF14_STEP(6, 0x43), EFF14_STEP(6, 0x4E),
    EFF14_END, 0, 0,
};

const s8 eff14_script_10[108] = {
    EFF14_STEP(4, 0x40), EFF14_STEP(4, 0x4F), EFF14_STEP(4, 0x40), EFF14_STEP(4, 0x4F),
    EFF14_STEP(3, 0x40), EFF14_STEP(3, 0x4F), EFF14_STEP(2, 0x40), EFF14_STEP(3, 0x4F),
    EFF14_STEP(4, 0x40), EFF14_STEP(5, 0x4F), EFF14_STEP(4, 0x40), EFF14_STEP(4, 0x4F),
    EFF14_STEP(4, 0x40), EFF14_STEP(4, 0x4F), EFF14_STEP(2, 0x40), EFF14_STEP(3, 0x4F),
    EFF14_STEP(4, 0x40), EFF14_STEP(5, 0x4F), EFF14_STEP(4, 0x40), EFF14_STEP(4, 0x4F),
    EFF14_STEP(4, 0x40), EFF14_STEP(4, 0x4F), EFF14_STEP(5, 0x40), EFF14_STEP(6, 0x4F),
    EFF14_STEP(5, 0x40), EFF14_STEP(4, 0x4F),
    EFF14_END, 0, 0,
};

const s8 eff14_pattern_0[190] = {
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

const s8 eff14_size_0[2] = {
    19, 10,
};

const s8 eff14_pattern_1[35] = {
    0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1,
};

const s8 eff14_size_1[2] = {
    7, 5,
};

const s8 eff14_pattern_2[2] = {
    1, 1,
};

const s8 eff14_size_2[2] = {
    2, 1,
};

const s8 eff14_pattern_3[21] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
};

const s8 eff14_size_3[2] = {
    7, 3,
};

const s8 eff14_pattern_4[18] = {
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1,
};

const s8 eff14_size_4[2] = {
    6, 3,
};

const s8 eff14_pattern_5[2] = {
    1, 1,
};

const s8 eff14_size_5[2] = {
    1, 2,
};

const s8 eff14_pattern_6[192] = {
    0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

const s8 eff14_size_6[2] = {
    16, 12,
};

const s8 eff14_pattern_7[15] = {
    0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

const s8 eff14_size_7[2] = {
    5, 3,
};

const s8 eff14_pattern_8[15] = {
    0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

const s8 eff14_size_8[2] = {
    5, 3,
};

const s8 eff14_pattern_9[18] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1,
    1, 1,
};

const s8 eff14_size_9[2] = {
    6, 3,
};

const s8 eff14_pattern_10[36] = {
    0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0,
};

const s8 eff14_size_10[2] = {
    9, 4,
};

const u32 eff14_data_tbl[11][5] = {
    { 0, 0, (u32)eff14_script_0, (u32)eff14_pattern_0, (u32)eff14_size_0 },
    { 0, 0, (u32)eff14_script_1, (u32)eff14_pattern_1, (u32)eff14_size_1 },
    { 0, 1, (u32)eff14_script_2, (u32)eff14_pattern_2, (u32)eff14_size_2 },
    { 2, 2, (u32)eff14_script_3, (u32)eff14_pattern_3, (u32)eff14_size_3 },
    { 0, 0, (u32)eff14_script_4, (u32)eff14_pattern_4, (u32)eff14_size_4 },
    { 0, 1, (u32)eff14_script_4, (u32)eff14_pattern_5, (u32)eff14_size_5 },
    { 0, 2, (u32)eff14_script_4, (u32)eff14_pattern_6, (u32)eff14_size_6 },
    { 0, 3, (u32)eff14_script_4, (u32)eff14_pattern_7, (u32)eff14_size_7 },
    { 0, 4, (u32)eff14_script_4, (u32)eff14_pattern_8, (u32)eff14_size_8 },
    { 1, 6, (u32)eff14_script_9, (u32)eff14_pattern_9, (u32)eff14_size_9 },
    { 1, 7, (u32)eff14_script_10, (u32)eff14_pattern_10, (u32)eff14_size_10 },
};

const s16 eff15_data_tbl[66] = {
    352, 224, 1, 23, 8, 38, 676, 225, 1, 23, 8, 51, 370, 240, 1, 23,
    7, 34, 536, 184, 1, 23, 7, 36, 384, 220, 1, 23, 8, 52, 642, 236,
    1, 23, 8, 37, 494, 200, 1, 23, 7, 36, 668, 207, 1, 23, 7, 38,
    367, 210, 1, 23, 8, 49, 598, 228, 1, 23, 8, 34, 452, 228, 1, 23,
    7, 36,
};

const s32 eff15_y_speed_tbl[64] = {
    -0x1400, -0x480, -0x1800, -0x380, -0x2C00, -0x330, -0x2E00, -0x310,
    -0x3000, -0x300, -0x3200, -0x2E0, -0x3600, -0x280, -0x3800, -0x260,
    -0x3A00, -0x240, -0x3C00, -0x230, -0x3D00, -0x220, -0x3F00, -0x200,
    -0x4000, -0x180, -0x4100, -0x160, -0x4200, -0x140, -0x4E00, -0x100,
    -0x1400, -0x100, -0x1800, -0x140, -0x2C00, -0x130, -0x2E00, -0x110,
    -0x3000, -0x200, -0x3200, -0x1E0, -0x3600, -0x120, -0x3800, -0x2E0,
    -0x3A00, -0x180, -0x3C00, -0x130, -0x3D00, -0x280, -0x3F00, -0x240,
    -0x4000, -0x1E0, -0x4100, -0x200, -0x4200, -0x280, -0x4E00, -0x330,
};

const s32 eff15_x_speed_tbl[16] = {
    -0x40, -0xA0, -0x100, -0x200, -0x400, -0x800, -0xC00, -0x1000,
    -0x1400, -0x1600, -0x1800, -0x1A00, -0x1E00, -0x2200, -0x2800, -0x3000,
};

const s32 eff15_x_acc_tbl[16] = {
    0, -0x80, -0xC0, -0x100, -0x140, -0x180, -0x1C0, -0x200, -0x220, -0x240, -0x280, -0x2A0, -0x300, -0x320, -0x340, -0x400,
};

const s32 eff15_x_acc_tbl2[16] = {
    0, -0x40, -0x60, -0x80, -0xC0, -0xE0, -0x100, -0x120, -0x140, -0x160, -0x180, -0x1C0, -0x1E0, -0x200, -0x220, -0x300,
};

/* One row per object (effect_16_init's type): x and y from BG 1, unused, cell number. */
const s16 eff16_data_tbl[15][4] = {
    { -321, 329, 0, 16461 }, { -321, 206, 0, 16461 }, { -321, 83, 0, 16461 }, { -198, 329, 0, 16461 },
    { -198, 206, 0, 16461 }, { -198, 83, 0, 16461 }, { -75, 329, 0, 16461 }, { -75, 206, 0, 16461 },
    { -75, 83, 0, 16461 }, { 48, 329, 0, 16461 }, { 48, 206, 0, 16461 }, { 48, 83, 0, 16461 },
    { 171, 329, 0, 16461 }, { 171, 206, 0, 16461 }, { 171, 83, 0, 16461 },
};
