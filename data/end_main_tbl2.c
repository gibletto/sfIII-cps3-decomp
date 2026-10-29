/*
 * END_MAIN_TBL2.C  ending background set-up tables
 *
 * Indexed by the ending's character number: end_bg_index_tbl picks the ending's entry in
 * end_bg_gfx_tbl (scroll graphics preparation data, size and source) and end_scno_tbl gives
 * its number of BG layers; read by END_MAIN_C.C, the ending main control. end_map_data_0 .. 3
 * are the screen map records of the four ending BG layers, reached through end_map_tbl in
 * OP_END_WORK.C. end_cg_src_tbl, the screen maps of end_bg_gfx_tbl's entries, is not referred
 * to.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 end_scno_tbl[];
extern const s16 end_bg_index_tbl[];
extern const END_BG_GFX end_bg_gfx_tbl[];
extern const u32 end_cg_src_tbl[];
extern const s16 end_map_data_0[];
extern const s16 end_map_data_1[];
extern const s16 end_map_data_2[];
extern const s16 end_map_data_3[];
extern const u16 end_100_scrn_data[][16][32];
extern const u16 end_1100_scrn_data[][16][32];
extern const u16 end_200_scrn_data[][16][32];
extern const u16 end_500_scrn_data[][16][32];
extern const u16 end_900_scrn_data[][16][32];
extern const u16 end_scrn_data[][16][32];

const s16 end_scno_tbl[13] = {
    0, 2, 2, 2, 2, 2, 0, 2, 3, 1, 2, 2, 3,
};

const s16 end_bg_index_tbl[13] = {
    0, 1, 2, 3, 3, 4, 0, 3, 3, 5, 3, 3, 6,
};

const END_BG_GFX end_bg_gfx_tbl[7] = {
    { 0, 0, 0 }, { 0xF00000, 10831, 0xF00080 },
    { 0xF14000, 9215, 0xF14080 }, { 0xE00000, 92143, 0xE00080 },
    { 0xF2C000, 14159, 0xF2C080 }, { 0xF44000, 7903, 0xF44080 },
    { 0xF54000, 19679, 0xF54080 },
};

/* the screen maps of end_bg_gfx_tbl's entries; nothing in the program refers to it */
const u32 end_cg_src_tbl[7] = {
    (u32)end_100_scrn_data, (u32)end_100_scrn_data, (u32)end_200_scrn_data, (u32)end_scrn_data,
    (u32)end_500_scrn_data, (u32)end_900_scrn_data, (u32)end_1100_scrn_data,
};

/* provisional name */
const s16 end_map_data_0[28] = {
    /* [0] */
    1, 84,  0x7F, 0x3F00, 12,  0xFF, 0x7F00, 12,  0x17F, 0x7F00, 12,  0x1FF, 0x7F00, 12,  0x27F, 0x7F00, 12,
           0x2FF, 0x7F00, 12,  0x37F, 0x7F00, 12,  0x3FF, 0x7F00, 12,  -1,
    -1,
};

/* provisional name */
const s16 end_map_data_1[28] = {
    /* [0] */
    2, 94,  0x7F, 0x3F00, 28,  0xFF, 0x7F00, 28,  0x17F, 0x7F00, 28,  0x1FF, 0x7F00, 28,  0x27F, 0x7F00, 28,
           0x2FF, 0x7F00, 28,  0x37F, 0x7F00, 28,  0x3FF, 0x7F00, 28,  -1,
    -1,
};

/* provisional name */
const s16 end_map_data_2[28] = {
    /* [0] */
    3, 104,  0x7F, 0x3F00, 44,  0xFF, 0x7F00, 44,  0x17F, 0x7F00, 44,  0x1FF, 0x7F00, 44,  0x27F, 0x7F00, 44,
           0x2FF, 0x7F00, 44,  0x37F, 0x7F00, 44,  0x3FF, 0x7F00, 44,  -1,
    -1,
};

/* provisional name */
const s16 end_map_data_3[28] = {
    /* [0] */
    4, 114,  0x7F, 0x3F00, 60,  0xFF, 0x7F00, 60,  0x17F, 0x7F00, 60,  0x1FF, 0x7F00, 60,  0x27F, 0x7F00, 60,
           0x2FF, 0x7F00, 60,  0x37F, 0x7F00, 60,  0x3FF, 0x7F00, 60,  -1,
    -1,
};
