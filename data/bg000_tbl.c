/*
 * BG000_TBL.C  stage background set-up tables
 *
 * Per stage background (bg_index), and for the special screens drawn by bg_etc_write (the etc_
 * tables, by screen type): the scroll graphics count (bg_scno_tbl), graphics transfer data
 * (bg_gfx_tbl), layer scroll speeds (bg_speed_tbl), layer zoom split flags
 * (etc_bg_zuubun_tbl), cell attributes, cell counts per layer and cell graphics sources in the
 * scrn_ files (bg_attr_tbl, bg_cell_cnt_tbl, bg_cg_src_tbl). bg_scr_record_data and
 * ake_scr_record_data are the screen map records of the layers, set up with sprite_list_setup
 * and reached per stage through bg_map_tbl in BG_WORK.C. Read by BG000.C, the stage background
 * services; the etc_ scroll count, speed, zoom split and graphics tables also by CMD_MAIN.C
 * (debug menu screen), and bg_scr_record_data by EFFG0.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 bg_scno_tbl[];
extern const s16 etc_bg_scno_tbl[];
extern const s16 bg_scr_record_data[];
extern const u16 ake_scr_record_data[];
extern const s32 bg_speed_tbl[][4][2];
extern const s32 etc_bg_speed_tbl[][4][2];
extern const s32 etc_bg_zuubun_tbl[][4];
extern const BG_GFX bg_gfx_tbl[];
extern const BG_GFX etc_bg_gfx_tbl[];
extern const s16 bg_attr_tbl[];
extern const s16 etc_bg_attr_tbl[];
extern const s16 bg_cell_cnt_tbl[][4];
extern const s16 etc_bg_cell_cnt_tbl[][4];
extern const u32 bg_cg_src_tbl[];
extern const u32 etc_bg_cg_src_tbl[];
extern const u16 bg050_cell_data[][16][32];
extern const u16 bg070_cell_data[][16][32];
extern const u16 bg_scrn_data_01[][16][32];
extern const u16 bg_scrn_data_02[][16][32];
extern const u16 bg_scrn_data_03[][16][32];
extern const u16 bg_scrn_data_05[][16][32];
extern const u16 bg_scrn_data_06[][16][32];
extern const u16 bg_scrn_data_09[][16][32];
extern const u16 bg_scrn_data_14[][16][32];
extern const u16 bg_scrn_data_16[][16][32];
extern const u16 eff48_scrn_data[][16][32];
extern const u16 etc_bg_scrn_data_0[][16][32];
extern const u16 etc_bg_scrn_data_3[][16][32];
extern const u32 bg040_scrn_data;
extern const u16 bg100_scrn_data[][16][32];
extern const u16 effb0_scrn_data[][16][32];
extern const u16 bg150_scrn_data[][16][32];

const s16 bg_scno_tbl[20] = {
    2, 3, 2, 3, 3, 3, 2, 3, 2, 3, 2, 3, 3, 3, 2, 2,
    3, 3, 2, 1,
};

const s16 etc_bg_scno_tbl[47] = {
    1, 1, 1, 1, 1, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024,
    1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

const s16 bg_scr_record_data[92] = {
    1, 94, 127, 32512, 12, 255, 32512, 12, 383, 32512, 12, 511, 32512, 12, -1, -1,
    2, 84, 127, 32512, 28, 255, 32512, 28, 383, 32512, 28, 511, 32512, 28, -1, -1,
    3, 104, 127, 32512, 44, 255, 32512, 44, 383, 32512, 44, 511, 32512, 44, -1, -1,
    4, 94, 127, 32512, 60, 255, 32512, 60, 383, 32512, 60, 511, 32512, 60, -1, -1,
    0, 94, 127, 32512, 12, 255, 32512, 12, 383, 32512, 12, 511, 32512, 12, 639, 32512,
    12, 767, 32512, 12, 895, 32512, 12, 1023, 32512, 12, -1, -1,
};

const u16 ake_scr_record_data[515] = {
    4, 0x45, 0x7F, 0x7F00, 0x3C, 0xFF, 0x7F00, 0x3C,
    0x17F, 0x7F00, 0x3C, 0x1FF, 0x7F00, 0x3C, 0xFFFF, 0xFFFF,
    1, 0x5E, 0xFF, 0x6F00, 0x2C, 0x17F, 0x7F00, 0x2C,
    0x1FF, 0x7F00, 0x2C, 0xFFFF, 0xFFFF, 2, 0x54, 0x40,
    0x4000, 0x1C, 0xFFFF, 0xFFFF, 3, 0x68, 0xFF, 0x6F00,
    0x2C, 0x17F, 0x7F00, 0x2C, 0x1FF, 0x7F00, 0x2C, 0xFFFF,
    0xFFFF, 4, 0x66, 0x2FF, 0x100, 0x3C, 0xFFFF, 0xFFFF,
    1, 0x5E, 0x7F, 0x7F00, 0xC, 0xFF, 0x7F00, 0xC,
    0x17F, 0x7F00, 0xC, 0x1FF, 0x7F00, 0xC, 0xFFFF, 0xFFFF,
    2, 0x54, 0x7F, 0x6F00, 0x1C, 0xFF, 0x7F00, 0x1C,
    0x17F, 0x7F00, 0x1C, 0x1FF, 0x7F00, 0x1C, 0xFFFF, 0xFFFF,
    3, 0x68, 0x17F, 0x3F00, 0x2C, 0x1FF, 0x7F00, 0x2C,
    0xFFFF, 0xFFFF, 1, 0x72, 0xFF, 0x6600, 0xC, 0x17F,
    0x7F00, 0xC, 0x1FF, 0x7F00, 0xC, 0xFFFF, 0xFFFF, 2,
    0x5E, 0x7F, 0x7F00, 0x1C, 0xFFFF, 0xFFFF, 1, 0x5E,
    0x7F, 0x4F00, 0xC, 0xFF, 0x7F00, 0xC, 0x17F, 0x7F00,
    0xC, 0xFFFF, 0xFFFF, 3, 0x68, 0x7F, 0x1F00, 0x2C,
    0xFF, 0x7F00, 0x2C, 0x17F, 0x7F00, 0x2C, 0x1FF, 0x7F00,
    0x2C, 0xFFFF, 0xFFFF, 1, 0x5E, 0xFF, 0x4F00, 0xC,
    0x17F, 0x7F00, 0xC, 0xFFFF, 0xFFFF, 2, 0x54, 0x7F,
    0x7F00, 0x1C, 0xFF, 0x7F00, 0x1C, 0x17F, 0x7F00, 0x1C,
    0x1FF, 0x7F00, 0x1C, 0xFFFF, 0xFFFF, 3, 0x68, 0x7F,
    0x1F00, 0x2C, 0xFF, 0x7F00, 0x2C, 0x17F, 0x7F00, 0x2C,
    0x1FF, 0x7F00, 0x2C, 0xFFFF, 0xFFFF, 1, 0x68, 0x7F,
    0x1800, 0xC, 0xFF, 0x7F00, 0xC, 0x17F, 0x7F00, 0xC,
    0x1FF, 0x7F00, 0xC, 0xFFFF, 0xFFFF, 1, 0x5E, 0x7F,
    0x7F00, 0x1C, 0xFF, 0x7F00, 0x1C, 0x17F, 0x7F00, 0x1C,
    0x1FF, 0x7F00, 0x1C, 0xFFFF, 0xFFFF, 3, 0x72, 0xFF,
    0x1F00, 0x2C, 0x17F, 0x7F00, 0x2C, 0x1FF, 0x7F00, 0x2C,
    0xFFFF, 0xFFFF, 1, 0x72, 0x7F, 0x1F00, 0xC, 0x17F,
    0x7F00, 0xC, 0x1FF, 0x7F00, 0xC, 0xFFFF, 0xFFFF, 2,
    0x68, 0x7F, 0x7F00, 0x1C, 0xFF, 0x7F00, 0x1C, 0x17F,
    0x7F00, 0x1C, 0xFFFF, 0xFFFF, 1, 0x14, 0x7F, 0x7F00,
    0xC, 0xFF, 0x7F00, 0xC, 0x17F, 0x7F00, 0xC, 0x1FF,
    0x7F00, 0xC, 0xFFFF, 0xFFFF, 2, 0x54, 0x7F, 0x6F00,
    0x1C, 0xFF, 0x7F00, 0x1C, 0xFFFF, 0xFFFF, 3, 0x68,
    0xFF, 0x7F00, 0x2C, 0x17F, 0x7F00, 0x2C, 0x17F, 0x7F00,
    0x2C, 0x1FF, 0x7F00, 0x2C, 0xFFFF, 0xFFFF, 1, 0x68,
    0xFF, 0x7F00, 0x2C, 0x17F, 0x7F00, 0x2C, 0x1FF, 0x7F00,
    0x2C, 0xFFFF, 0xFFFF, 2, 0x54, 0x7F, 0x6F00, 0x1C,
    0xFF, 0x7F00, 0x1C, 0xFFFF, 0xFFFF, 3, 0x68, 0xFF,
    0x7F00, 0x2C, 0xFFFF, 0xFFFF, 1, 0x5E, 0xFF, 0x6F00,
    0xC, 0x17F, 0x7F00, 0xC, 0x1FF, 0x7F00, 0xC, 0xFFFF,
    0xFFFF, 1, 0x5E, 0x7F, 0x1000, 0xC, 0xFF, 0x7F00,
    0xC, 0x17F, 0x7F00, 0xC, 0x1FF, 0x7F00, 0xC, 0xFFFF,
    0xFFFF, 3, 0x68, 0x7F, 0x2C00, 0x2C, 0xFF, 0x7F00,
    0x2C, 0x17F, 0x7F00, 0x2C, 0x1FF, 0x7F00, 0x2C, 0xFFFF,
    0xFFFF, 1, 0x5E, 0x7F, 0x7F00, 0xC, 0xFF, 0x7F00,
    0xC, 0x17F, 0x7F00, 0xC, 0x1FF, 0x7F00, 0xC, 0x37F,
    0x7F00, 0xC, 0x3FF, 0x7F00, 0xC, 0xFFFF, 0xFFFF, 2,
    0x78, 0x17F, 0x100, 0x1C, 0xFFFF, 0xFFFF, 2, 0x54,
    0x7F, 0x7F00, 0x1C, 0xFF, 0x7F00, 0x1C, 0x17F, 0x7F00,
    0x1C, 0x1FF, 0x7F00, 0x1C, 0x27F, 0x7F00, 0x1C, 0x2FF,
    0x7F00, 0x1C, 0x37F, 0x7F00, 0x1C, 0x3FF, 0x7F00, 0x1C,
    0xFFFF, 0xFFFF, 1, 0x5E, 0x7F, 0x3F00, 0xC, 0xCF,
    0x4F00, 0xC, 0xFFFF, 0xFFFF, 3, 0x68, 0x7F, 0x3F00,
    0x2C, 0xCF, 0x4F00, 0x2C, 0xFFFF, 0xFFFF, 1, 0x54,
    0x7F, 0x7F00, 0xC, 0xFF, 0x7F00, 0xC, 0x17F, 0x7F00,
    0xC, 0xFFFF, 0xFFFF, 1, 0x54, 0x7F, 0x7F00, 0xC,
    0xFF, 0x7F00, 0xC, 0x17F, 0x7F00, 0xC, 0x1FF, 0x7F00,
    0xC, 0xFFFF, 0xFFFF, 2, 0x5E, 0x7F, 0x7F00, 0x1C,
    0xFF, 0x7F00, 0x1C, 0x17F, 0x7F00, 0x1C, 0x1FF, 0x7F00,
    0x1C, 0xFFFF, 0xFFFF, 3, 0x68, 0x7F, 0x7F00, 0x2C,
    0xFF, 0x7F00, 0x2C, 0x17F, 0x7F00, 0x2C, 0x1FF, 0x7F00,
    0x2C, 0xFFFF, 0xFFFF,
};

const s32 bg_speed_tbl[19][4][2] = {
    { { 57344, 65536 }, { 65536, 65536 }, { 0, 0 }, { 65536, 65536 } },
    { { 57344, 57344 }, { 65536, 65536 }, { 40960, 65536 }, { 0, 0 } },
    { { 40960, 61440 }, { 65536, 65536 }, { 0, 0 }, { 0, 0 } },
    { { 57344, 49152 }, { 65536, 65536 }, { 16384, 40960 }, { 0, 0 } },
    { { 49152, 65536 }, { 65536, 65536 }, { 32768, 45056 }, { 0, 0 } },
    { { 57344, 57344 }, { 65536, 65536 }, { 49152, 61440 }, { 0, 0 } },
    { { 57344, 69632 }, { 65536, 65536 }, { 0, 0 }, { 0, 0 } },
    { { 65536, 65536 }, { 65536, 65536 }, { 49152, 65536 }, { 0, 0 } },
    { { 49152, 65536 }, { 65536, 65536 }, { 0, 0 }, { 0, 0 } },
    { { 65536, 65536 }, { 65536, 65536 }, { 65536, 65536 }, { 0, 0 } },
    { { 49152, 57344 }, { 65536, 65536 }, { 0, 0 }, { 0, 0 } },
    { { 49152, 65536 }, { 65536, 65536 }, { 32768, 40960 }, { 0, 0 } },
    { { 49152, 65536 }, { 65536, 65536 }, { 32768, 40960 }, { 0, 0 } },
    { { 49152, 65536 }, { 65536, 65536 }, { 32768, 40960 }, { 0, 0 } },
    { { 4096, 32768 }, { 65536, 65536 }, { 0, 0 }, { 0, 0 } },
    { { 32768, 32768 }, { 65536, 65536 }, { 0, 0 }, { 0, 0 } },
    { { 49152, 57344 }, { 65536, 65536 }, { 32768, 61440 }, { 0, 0 } },
    { { 57344, 57344 }, { 65536, 65536 }, { 49152, 61440 }, { 0, 0 } },
    { { 57344, 69632 }, { 65536, 65536 }, { 0, 0 }, { 0, 0 } },
};

const s32 etc_bg_speed_tbl[5][4][2] = {
    { { 65536, 65536 }, { 65536, 65536 }, { 63488, 61440 }, { 65536, 65536 } },
    { { 65536, 65536 }, { 65536, 65536 }, { 57344, 57344 }, { 0, 0 } },
    { { 65536, 65536 }, { 65536, 65536 }, { 57344, 57344 }, { 0, 0 } },
    { { 65536, 65536 }, { 65536, 65536 }, { 57344, 57344 }, { 0, 0 } },
    { { 65536, 65536 }, { 65536, 65536 }, { 57344, 57344 }, { 0, 0 } },
};

const s32 etc_bg_zuubun_tbl[5][4] = {
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
};

const BG_GFX bg_gfx_tbl[22] = {
    { 0x1200000, 24303, 0x1200080, 1 }, { 0x1212160, 29311, 0x12121E0, 1 },
    { 0x122D150, 22927, 0x122D1D0, 2 }, { 0x124C5C0, 25263, 0x124C640, 1 },
    { 0x1261FF8, 27375, 0x1262078, 1 }, { 0x1278970, 27583, 0x12789F0, 1 },
    { 0x128D850, 20767, 0x128D8D0, 1 }, { 0x129BAD0, 33567, 0x129BB50, 1 },
    { 0x129BAD0, 33567, 0x129BB50, 1 }, { 0x12AB358, 39343, 0x12AB3D8, 1 },
    { 0x12C7680, 41263, 0x12C7700, 1 }, { 0x12E3220, 66591, 0x12E32A0, 1 },
    { 0x12E3220, 66591, 0x12E32A0, 1 }, { 0x12E3220, 66591, 0x12E32A0, 1 },
    { 0x13122C8, 10303, 0x1312348, 1 }, { 0x13193E8, 21007, 0x1319468, 1 },
    { 0x132B458, 24671, 0x132B4D8, 1 }, { 0x1278970, 27583, 0x12789F0, 1 },
    { 0x128D850, 20767, 0x128D8D0, 1 }, { 0x133BCF8, 17519, 0x133BD78, 1 },
    { 0x133BCF8, 17519, 0x133BD78, 1 }, { 0x133BCF8, 17519, 0x133BD78, 1 },
};

const BG_GFX etc_bg_gfx_tbl[16] = {
    { 0x134A888, 5679, 0x134A908, 1 },
    { 0x133BCF8, 16879, 0x133BD78, 1 },
    { 0x134A888, 5679, 0x134A908, 1 },
    { 0x134F420, 4383, 0x134F4A0, 1 },
    { 0x134F420, 4383, 0x134F4A0, 1 },
    { 0x5E0054, 6815838, 0x5E0054, 0x680000 },
    { 0x72005E, 6815858, 0x5E0054, 0x680000 },
    { 0x5E0054, 6815744, 0x68005E, 0x720000 },
    { 0x720068, 0, 0x140054, 0x680072 },
    { 0x5E0068, 0, 0x5E0054, 0x680000 },
    { 0x5E0054, 6815744, 0x5E0054, 0x680000 },
    { 0x5E0054, 6815744, 0x5E0054, 0x680000 },
    { 0x5E0054, 0, 0x5E0054, 0x680072 },
    { 0x5E0054, 6815744, 0x68005E, 0x720000 },
    { 0x720068, 0, 0x54005E, 0x680000 },
    { 0x54005E, 6815744, 0x54005E, 0x680000 },
};

const s16 bg_attr_tbl[23] = {
    512, 512, 0, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512,
    512, 512, 512, 512, 512, 512, 512,
};

const s16 etc_bg_attr_tbl[5] = {
    512, 512, 512, 512, 512,
};

const s16 bg_cell_cnt_tbl[22][4] = {
    { 8, 8, 0, 0 }, { 4, 8, 2, 0 }, { 8, 8, 0, 0 }, { 6, 8, 6, 0 },
    { 8, 8, 8, 0 }, { 6, 6, 6, 0 }, { 6, 6, 0, 0 }, { 8, 8, 8, 0 },
    { 8, 8, 0, 0 }, { 8, 8, 4, 0 }, { 6, 8, 0, 0 }, { 6, 8, 6, 0 },
    { 6, 8, 6, 0 }, { 6, 8, 6, 0 }, { 10, 0, 0, 0 }, { 6, 6, 0, 0 },
    { 8, 8, 8, 0 }, { 6, 6, 6, 0 }, { 6, 6, 0, 0 }, { 4, 0, 0, 0 },
    { 2, 2, 2, 0 }, { 8, 8, 8, 0 },
};

const s16 etc_bg_cell_cnt_tbl[5][4] = {
    { 2, 0, 0, 0 }, { 4, 0, 0, 0 }, { 2, 0, 0, 0 }, { 2, 0, 0, 0 },
    { 2, 0, 0, 0 },
};

const u32 bg_cg_src_tbl[22] = {
    (u32)bg050_cell_data, (u32)bg_scrn_data_01, (u32)bg_scrn_data_02, (u32)bg_scrn_data_03,
    (u32)&bg040_scrn_data, (u32)bg_scrn_data_05, (u32)bg_scrn_data_06, (u32)bg070_cell_data,
    (u32)bg070_cell_data, (u32)bg_scrn_data_09, (u32)bg100_scrn_data, (u32)eff48_scrn_data,
    (u32)eff48_scrn_data, (u32)eff48_scrn_data, (u32)bg_scrn_data_14, (u32)bg150_scrn_data,
    (u32)bg_scrn_data_16, (u32)bg_scrn_data_05, (u32)bg_scrn_data_06, (u32)effb0_scrn_data,
    (u32)effb0_scrn_data, (u32)effb0_scrn_data,
};

const u32 etc_bg_cg_src_tbl[5] = {
    (u32)etc_bg_scrn_data_0, (u32)effb0_scrn_data, (u32)etc_bg_scrn_data_0, (u32)etc_bg_scrn_data_3,
    (u32)etc_bg_scrn_data_3,
};
