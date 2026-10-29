/*
 * EFF14_TBL.C  background colour-cycle, falling stone and blinking object tables
 *
 * eff14_data_tbl gives each of the 11 colour-cycle ids its scroll layer, work slot, script and
 * cell patterns (in eff14_pattern_0); eff14_ofs_tbl starts with the map offset of each id's
 * rectangle, followed by the scripts. Read by EFF14.C, the background colour-cycle writer.
 * eff15_data_tbl holds the position, priority, cell, side speed limit and floor of each
 * falling stone, and eff15_y_speed_tbl, eff15_x_speed_tbl, eff15_x_acc_tbl and
 * eff15_x_acc_tbl2 the random speeds it picks from; read by EFF15.C. eff16_data_tbl is the x,
 * y and cg number of each blinking object, read by EFF16.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u16 eff14_ofs_tbl[];
extern const s8 eff14_pattern_0[];
extern const u32 eff14_data_tbl[][5];
extern const s16 eff15_data_tbl[];
extern const s32 eff15_y_speed_tbl[];
extern const s32 eff15_x_speed_tbl[];
extern const s32 eff15_x_acc_tbl[];
extern const s32 eff15_x_acc_tbl2[];
extern const s16 eff16_data_tbl[][4];

const u16 eff14_ofs_tbl[183] = {
    0x1660, 0x197C, 0x1894, 0x1584, 0x1688, 0x1494, 0xDA0, 0xAA8,
    0xACC, 0x19B8, 0x1618, 5, 0x54, 5, 0x55, 5,
    0x56, 5, 0x57, 5, 0x58, 5, 0x59, 5,
    0x5A, 5, 0x5B, 5, 0x5C, 5, 0x5D, 5,
    0x5E, 5, 0x5F, 0xFFFF, 0, 3, 0x59, 3,
    0x60, 3, 0x61, 0xFFFF, 0, 3, 0x52, 3,
    0x5C, 3, 0x5D, 0xFFFF, 0, 3, 0x41, 3,
    0x5E, 3, 0x5F, 0xFFFF, 0, 4, 0x45, 4,
    0x49, 4, 0x4A, 4, 0x4B, 4, 0x4C, 4,
    0x4D, 0xFFFF, 0, 4, 0x43, 4, 0x4E, 4,
    0x43, 4, 0x4E, 2, 0x43, 2, 0x4E, 4,
    0x43, 4, 0x4E, 5, 0x43, 3, 0x4E, 4,
    0x43, 4, 0x4E, 4, 0x43, 4, 0x4E, 6,
    0x43, 5, 0x4E, 4, 0x43, 4, 0x4E, 4,
    0x43, 4, 0x4E, 5, 0x43, 4, 0x4E, 4,
    0x43, 4, 0x4E, 6, 0x43, 6, 0x4E, 0xFFFF,
    0, 4, 0x40, 4, 0x4F, 4, 0x40, 4,
    0x4F, 3, 0x40, 3, 0x4F, 2, 0x40, 3,
    0x4F, 4, 0x40, 5, 0x4F, 4, 0x40, 4,
    0x4F, 4, 0x40, 4, 0x4F, 2, 0x40, 3,
    0x4F, 4, 0x40, 5, 0x4F, 4, 0x40, 4,
    0x4F, 4, 0x40, 4, 0x4F, 5, 0x40, 6,
    0x4F, 5, 0x40, 4, 0x4F, 0xFFFF, 0,
};

const s8 eff14_pattern_0[566] = {
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
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 19, 10,
    0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 7, 5, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 3,
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 6, 3, 1, 1, 1, 2, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 16, 12, 0, 0, 0, 0, 1, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 3, 0, 0, 0, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 3, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 6, 3,
    0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 9, 4,
};

const u32 eff14_data_tbl[11][5] = {
    { 0, 0, (u32)&eff14_ofs_tbl[11], (u32)eff14_pattern_0, (u32)&eff14_pattern_0[190] },
    { 0, 0, (u32)&eff14_ofs_tbl[37], (u32)&eff14_pattern_0[192], (u32)&eff14_pattern_0[227] },
    { 0, 1, (u32)&eff14_ofs_tbl[45], (u32)&eff14_pattern_0[229], (u32)&eff14_pattern_0[231] },
    { 2, 2, (u32)&eff14_ofs_tbl[53], (u32)&eff14_pattern_0[233], (u32)&eff14_pattern_0[254] },
    { 0, 0, (u32)&eff14_ofs_tbl[61], (u32)&eff14_pattern_0[256], (u32)&eff14_pattern_0[274] },
    { 0, 1, (u32)&eff14_ofs_tbl[61], (u32)&eff14_pattern_0[276], (u32)&eff14_pattern_0[278] },
    { 0, 2, (u32)&eff14_ofs_tbl[61], (u32)&eff14_pattern_0[280], (u32)&eff14_pattern_0[472] },
    { 0, 3, (u32)&eff14_ofs_tbl[61], (u32)&eff14_pattern_0[474], (u32)&eff14_pattern_0[489] },
    { 0, 4, (u32)&eff14_ofs_tbl[61], (u32)&eff14_pattern_0[491], (u32)&eff14_pattern_0[506] },
    { 1, 6, (u32)&eff14_ofs_tbl[75], (u32)&eff14_pattern_0[508], (u32)&eff14_pattern_0[526] },
    { 1, 7, (u32)&eff14_ofs_tbl[129], (u32)&eff14_pattern_0[528], (u32)&eff14_pattern_0[564] },
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
