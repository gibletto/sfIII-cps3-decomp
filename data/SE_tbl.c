/*
 * SE_TBL.C  tables read by SE.c, se_2.c and se_3.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const BitmapSrc wipe_clear_pattern_tbl[];
extern const u8 wipe_column_map_0[];
extern const u8 wipe_column_map_1[];
extern const u8 wipe_column_map_2[];
extern const ByteMapSrc wipe_column_tbl[];
extern const s16 stage_bgm_tbl[];
extern const s8 init_fade_voice_tbl[];
extern const s16 SE_Shock_Data[];
extern const s16 Finish_SE_Data[][7];
extern const u32 wipe_clear_pattern_3[];
extern const u8 wipe_clear_bitmap_0[];
extern const u8 wipe_clear_bitmap_1[];
extern const u8 wipe_clear_bitmap_3[];

const BitmapSrc wipe_clear_pattern_tbl[5] = {
    { (u8 *)wipe_clear_bitmap_0, 0, 8, 0 }, { (u8 *)wipe_clear_bitmap_1, 0, 3, 0 },
    { (u8 *)wipe_clear_bitmap_1, 0, 3, 0 }, { (u8 *)wipe_clear_pattern_3, 0, 8, 0 },
    { (u8 *)wipe_clear_bitmap_3, 0, 4, 0 },
};

const u8 wipe_column_map_0[64] = {
    0, 4, 9, 0xD, 0x12, 0x16, 0x1B, 0x1F, 0, 5, 9, 0xE, 0x12, 0x17, 0x1B, 0x1C,
    1, 5, 0xA, 0xE, 0x13, 0x17, 0x18, 0x1C, 1, 6, 0xA, 0xF, 0x13, 0x14, 0x18, 0x1D,
    2, 6, 0xB, 0xF, 0x10, 0x14, 0x19, 0x1D, 2, 7, 0xB, 0xC, 0x10, 0x15, 0x19, 0x1E,
    3, 7, 8, 0xC, 0x11, 0x15, 0x1A, 0x1E, 3, 4, 8, 0xD, 0x11, 0x16, 0x1A, 0x1F,
};

const u8 wipe_column_map_1[32] = {
    0x1C, 0x1D, 0x1E, 0x1F, 0x18, 0x19, 0x1A, 0x1B, 0x14, 0x15, 0x16, 0x17, 0x10, 0x11, 0x12, 0x13,
    0xC, 0xD, 0xE, 0xF, 8, 9, 0xA, 0xB, 4, 5, 6, 7, 0, 1, 2, 3,
};

const u8 wipe_column_map_2[64] = {
    0, 4, 8, 0xC, 0x10, 0x14, 0x18, 0x1C, 0, 4, 8, 0xC, 0x10, 0x14, 0x18, 0x1C,
    1, 5, 9, 0xD, 0x11, 0x15, 0x19, 0x1D, 1, 5, 9, 0xD, 0x11, 0x15, 0x19, 0x1D,
    2, 6, 0xA, 0xE, 0x12, 0x16, 0x1A, 0x1E, 2, 6, 0xA, 0xE, 0x12, 0x16, 0x1A, 0x1E,
    3, 7, 0xB, 0xF, 0x13, 0x17, 0x1B, 0x1F, 3, 7, 0xB, 0xF, 0x13, 0x17, 0x1B, 0x1F,
};

const ByteMapSrc wipe_column_tbl[5] = {
    { (u8 *)wipe_column_map_0, 8, 0 }, { (u8 *)wipe_column_map_0, 8, 0 },
    { (u8 *)wipe_column_map_0, 8, 0 }, { (u8 *)wipe_column_map_1, 4, 0 },
    { (u8 *)wipe_column_map_2, 4, 0 },
};

const s16 stage_bgm_tbl[13] = {
    19, 11, 12, 13, 14, 15, 19, 16, 17, 18, 13, 12, 29,
};

const s8 init_fade_voice_tbl[14] = {
    0, 1, 2, 3, 4, 5, 6, 7, 10, 11, 12, 13, 14, 15,
};

const s16 SE_Shock_Data[7] = {
    285, 286, 287, 288, 289, 305, 306,
};

const s16 Finish_SE_Data[2][7] = {
    { 305, 306, 285, 286, 287, 288, 272 }, { 292, 293, 290, 291, 287, 288, 272 },
};
