/*
 * BG_WORK.C  background tables and work
 *
 * The background screen map tables, the BG cell list tables (bg000_tbl_b.c holds the lists) and the BG deformation
 * table: initialised work RAM (section D), read by bg000.c and CMD_MAIN.c. The background work (section B): the
 * line scroll (suzi) work, base positions, mark graphics, zoom, chase and quake state and the stage flags. A
 * <name>_tail table holds the bytes between <name> and the next named variable.
 */

#include "types.h"
#include "structs.h"

extern u32 bg_map_tbl[][4];
extern u32 bg_map_tbl2[][4];
extern const HUD_CELL* bg_rewrite_cell_tbl[][4];
extern const HUD_CELL* bg_rewrite_cell_tbl_8[][4];
extern const TILEREQ* bg_etc_cell_tbl[][4];
extern BG_DEFF_TBL bg_deff_tbl[][4];
extern const HUD_CELL bg_rewrite8_cells_03_0[];
extern const HUD_CELL bg_rewrite8_cells_03_1[];
extern const HUD_CELL bg_rewrite8_cells_11_1[];
extern const HUD_CELL bg_rewrite_cells_00_0[];
extern const HUD_CELL bg_rewrite_cells_00_1[];
extern const HUD_CELL bg_rewrite_cells_00_3[];
extern const HUD_CELL bg_rewrite_cells_01_0[];
extern const HUD_CELL bg_rewrite_cells_01_1[];
extern const HUD_CELL bg_rewrite_cells_01_2[];
extern const HUD_CELL bg_rewrite_cells_02_0[];
extern const HUD_CELL bg_rewrite_cells_02_1[];
extern const HUD_CELL bg_rewrite_cells_03_0[];
extern const HUD_CELL bg_rewrite_cells_03_1[];
extern const HUD_CELL bg_rewrite_cells_03_2[];
extern const HUD_CELL bg_rewrite_cells_04_0[];
extern const HUD_CELL bg_rewrite_cells_04_1[];
extern const HUD_CELL bg_rewrite_cells_04_2[];
extern const HUD_CELL bg_rewrite_cells_05_0[];
extern const HUD_CELL bg_rewrite_cells_05_1[];
extern const HUD_CELL bg_rewrite_cells_05_2[];
extern const HUD_CELL bg_rewrite_cells_06_0[];
extern const HUD_CELL bg_rewrite_cells_06_1[];
extern const HUD_CELL bg_rewrite_cells_07_0[];
extern const HUD_CELL bg_rewrite_cells_07_1[];
extern const HUD_CELL bg_rewrite_cells_07_2[];
extern const HUD_CELL bg_rewrite_cells_08_0[];
extern const HUD_CELL bg_rewrite_cells_08_1[];
extern const HUD_CELL bg_rewrite_cells_09_0[];
extern const HUD_CELL bg_rewrite_cells_09_1[];
extern const HUD_CELL bg_rewrite_cells_09_2[];
extern const HUD_CELL bg_rewrite_cells_10_0[];
extern const HUD_CELL bg_rewrite_cells_10_1[];
extern const HUD_CELL bg_rewrite_cells_11_0[];
extern const HUD_CELL bg_rewrite_cells_11_1[];
extern const HUD_CELL bg_rewrite_cells_11_2[];
extern const HUD_CELL bg_rewrite_cells_12_2[];
extern const HUD_CELL bg_rewrite_cells_14_0[];
extern const HUD_CELL bg_rewrite_cells_14_1[];
extern const HUD_CELL bg_rewrite_cells_15_0[];
extern const HUD_CELL bg_rewrite_cells_15_1[];
extern const HUD_CELL bg_rewrite_cells_16_0[];
extern const HUD_CELL bg_rewrite_cells_16_1[];
extern const HUD_CELL bg_rewrite_cells_16_2[];
extern const HUD_CELL bg_rewrite_cells_19_0[];
extern const HUD_CELL bg_rewrite_cells_20_0[];
extern const HUD_CELL bg_rewrite_cells_20_1[];
extern const HUD_CELL bg_rewrite_cells_20_2[];
extern const TILEREQ bg_etc_cells_0[];
extern const TILEREQ bg_etc_cells_1[];
extern const TILEREQ bg_etc_cells_2[];
extern const TILEREQ bg_etc_cells_3[];
extern const TILEREQ bg_etc_cells_4[];
extern const s16 bg_deff_minus0_tbl_0[][57];
extern const s16 bg_deff_minus0_tbl_1[][57];
extern const s16 bg_deff_minus0_tbl_2[][57];
extern const s16 bg_deff_minus0_tbl_3[][57];
extern const s16 bg_deff_minus0_tbl_4[][57];
extern const s16 bg_deff_minus1_tbl_0[][57];
extern const s16 bg_deff_minus1_tbl_1[][57];
extern const s16 bg_deff_minus1_tbl_2[][57];
extern const s16 bg_deff_minus1_tbl_3[][57];
extern const s16 bg_deff_minus1_tbl_4[][57];
extern const s16 bg_deff_plus0_tbl_0[][57];
extern const s16 bg_deff_plus0_tbl_1[][57];
extern const s16 bg_deff_plus0_tbl_2[][57];
extern const s16 bg_deff_plus0_tbl_3[][57];
extern const s16 bg_deff_plus0_tbl_4[][57];
extern const s16 bg_deff_plus1_tbl_0[][57];
extern const s16 bg_deff_plus1_tbl_1[][57];
extern const s16 bg_deff_plus1_tbl_2[][57];
extern const s16 bg_deff_plus1_tbl_3[][57];
extern const s16 bg_deff_plus1_tbl_4[][57];
extern const s16 bg_deff_rl0_tbl_0[][57];
extern const s16 bg_deff_rl0_tbl_1[][57];
extern const s16 bg_deff_rl0_tbl_2[][57];
extern const s16 bg_deff_rl0_tbl_3[][57];
extern const s16 bg_deff_rl0_tbl_4[][57];
extern const s16 bg_deff_rl1_tbl_0[][57];
extern const s16 bg_deff_rl1_tbl_1[][57];
extern const s16 bg_deff_rl1_tbl_2[][57];
extern const s16 bg_deff_rl1_tbl_3[][57];
extern const s16 bg_deff_rl1_tbl_4[][57];
extern const s16 bg_scr_record_data[];
extern const u16 ake_scr_record_data[];

/* 02005B14 */
u32 bg_map_tbl[22][4] = {
    {
        (u32)&ake_scr_record_data[16], (u32)&ake_scr_record_data[29],
        (u32)&ake_scr_record_data[36], (u32)&ake_scr_record_data[49],
    },
    { (u32)&ake_scr_record_data[56], (u32)&ake_scr_record_data[72], (u32)&ake_scr_record_data[88], 0 },
    { (u32)&ake_scr_record_data[98], (u32)&ake_scr_record_data[111], 0, 0 },
    { (u32)&ake_scr_record_data[118], (u32)&bg_scr_record_data[16], (u32)&ake_scr_record_data[131], 0 },
    { (u32)&ake_scr_record_data[147], (u32)&ake_scr_record_data[157], (u32)&ake_scr_record_data[173], 0 },
    { (u32)&ake_scr_record_data[189], (u32)&ake_scr_record_data[205], (u32)&ake_scr_record_data[221], 0 },
    { (u32)&ake_scr_record_data[234], (u32)&ake_scr_record_data[247], 0, 0 },
    { (u32)&ake_scr_record_data[260], (u32)&ake_scr_record_data[276], (u32)&ake_scr_record_data[286], 0 },
    { (u32)&ake_scr_record_data[302], (u32)&ake_scr_record_data[315], 0, 0 },
    { (u32)bg_scr_record_data, (u32)&bg_scr_record_data[16], (u32)&ake_scr_record_data[325], 0 },
    { (u32)&ake_scr_record_data[332], (u32)&bg_scr_record_data[16], 0, 0 },
    { (u32)&ake_scr_record_data[345], (u32)&bg_scr_record_data[16], (u32)&ake_scr_record_data[361], 0 },
    { (u32)&ake_scr_record_data[345], (u32)&bg_scr_record_data[16], (u32)&ake_scr_record_data[361], 0 },
    { (u32)&ake_scr_record_data[345], (u32)&bg_scr_record_data[16], (u32)&ake_scr_record_data[361], 0 },
    { (u32)&ake_scr_record_data[377], (u32)&ake_scr_record_data[399], 0, 0 },
    { (u32)bg_scr_record_data, (u32)&ake_scr_record_data[406], 0, 0 },
    { (u32)&ake_scr_record_data[434], (u32)&bg_scr_record_data[16], (u32)&ake_scr_record_data[444], 0 },
    { (u32)&ake_scr_record_data[189], (u32)&ake_scr_record_data[205], (u32)&ake_scr_record_data[221], 0 },
    { (u32)&ake_scr_record_data[234], (u32)&ake_scr_record_data[247], 0, 0 },
    { (u32)&ake_scr_record_data[454], 0, 0, 0 },
    { (u32)&ake_scr_record_data[467], (u32)&ake_scr_record_data[483], (u32)&ake_scr_record_data[499], 0 },
    { (u32)&ake_scr_record_data[467], (u32)&ake_scr_record_data[483], (u32)&ake_scr_record_data[499], 0 },
};

/* 02005C74 */
u32 bg_map_tbl2[5][4] = {
    {
        (u32)bg_scr_record_data, (u32)&bg_scr_record_data[16],
        (u32)&bg_scr_record_data[32], (u32)&bg_scr_record_data[48],
    },
    { (u32)bg_scr_record_data, 0, 0, 0 },
    { (u32)bg_scr_record_data, 0, 0, 0 },
    { (u32)bg_scr_record_data, 0, 0, 0 },
    { (u32)bg_scr_record_data, 0, 0, 0 },
};

/* 02005CC4 */
const HUD_CELL* bg_rewrite_cell_tbl[22][4] = {
    {
        bg_rewrite_cells_00_0, bg_rewrite_cells_00_1,
        bg_rewrite_cells_00_0, bg_rewrite_cells_00_3,
    },
    {
        bg_rewrite_cells_01_0, bg_rewrite_cells_01_1,
        bg_rewrite_cells_01_2, 0,
    },
    { bg_rewrite_cells_02_0, bg_rewrite_cells_02_1, 0, 0 },
    {
        bg_rewrite_cells_03_0, bg_rewrite_cells_03_1,
        bg_rewrite_cells_03_2, 0,
    },
    {
        bg_rewrite_cells_04_0, bg_rewrite_cells_04_1,
        bg_rewrite_cells_04_2, 0,
    },
    {
        bg_rewrite_cells_05_0, bg_rewrite_cells_05_1,
        bg_rewrite_cells_05_2, 0,
    },
    { bg_rewrite_cells_06_0, bg_rewrite_cells_06_1, 0, 0 },
    {
        bg_rewrite_cells_07_0, bg_rewrite_cells_07_1,
        bg_rewrite_cells_07_2, 0,
    },
    { bg_rewrite_cells_08_0, bg_rewrite_cells_08_1, 0, 0 },
    {
        bg_rewrite_cells_09_0, bg_rewrite_cells_09_1,
        bg_rewrite_cells_09_2, 0,
    },
    { bg_rewrite_cells_10_0, bg_rewrite_cells_10_1, 0, 0 },
    {
        bg_rewrite_cells_11_0, bg_rewrite_cells_11_1,
        bg_rewrite_cells_11_2, 0,
    },
    {
        bg_rewrite_cells_11_0, bg_rewrite_cells_11_1,
        bg_rewrite_cells_12_2, 0,
    },
    {
        bg_rewrite_cells_11_0, bg_rewrite_cells_11_1,
        bg_rewrite_cells_12_2, 0,
    },
    { bg_rewrite_cells_14_0, bg_rewrite_cells_14_1, 0, 0 },
    { bg_rewrite_cells_15_0, bg_rewrite_cells_15_1, 0, 0 },
    {
        bg_rewrite_cells_16_0, bg_rewrite_cells_16_1,
        bg_rewrite_cells_16_2, 0,
    },
    {
        bg_rewrite_cells_05_0, bg_rewrite_cells_05_1,
        bg_rewrite_cells_05_2, 0,
    },
    { bg_rewrite_cells_06_0, bg_rewrite_cells_06_1, 0, 0 },
    { bg_rewrite_cells_19_0, 0, 0, 0 },
    {
        bg_rewrite_cells_20_0, bg_rewrite_cells_20_1,
        bg_rewrite_cells_20_2, 0,
    },
    {
        bg_rewrite_cells_20_0, bg_rewrite_cells_20_1,
        bg_rewrite_cells_20_2, 0,
    },
};

/* 02005E24 */
const HUD_CELL* bg_rewrite_cell_tbl_8[22][4] = {
    {
        bg_rewrite_cells_00_0, bg_rewrite_cells_00_1,
        bg_rewrite_cells_00_0, bg_rewrite_cells_00_3,
    },
    {
        bg_rewrite_cells_01_0, bg_rewrite_cells_01_1,
        bg_rewrite_cells_01_2, 0,
    },
    { bg_rewrite_cells_02_0, bg_rewrite_cells_02_1, 0, 0 },
    {
        bg_rewrite8_cells_03_0, bg_rewrite8_cells_03_1,
        bg_rewrite_cells_03_2, 0,
    },
    {
        bg_rewrite_cells_04_0, bg_rewrite_cells_04_1,
        bg_rewrite_cells_04_2, 0,
    },
    {
        bg_rewrite_cells_05_0, bg_rewrite_cells_05_1,
        bg_rewrite_cells_05_2, 0,
    },
    { bg_rewrite_cells_06_0, bg_rewrite_cells_06_1, 0, 0 },
    {
        bg_rewrite_cells_07_0, bg_rewrite_cells_07_1,
        bg_rewrite_cells_07_2, 0,
    },
    { bg_rewrite_cells_08_0, bg_rewrite_cells_08_1, 0, 0 },
    {
        bg_rewrite_cells_09_0, bg_rewrite_cells_09_1,
        bg_rewrite_cells_09_2, 0,
    },
    { bg_rewrite_cells_10_0, bg_rewrite_cells_10_1, 0, 0 },
    {
        bg_rewrite_cells_11_0, bg_rewrite8_cells_11_1,
        bg_rewrite_cells_11_2, 0,
    },
    {
        bg_rewrite_cells_11_0, bg_rewrite8_cells_11_1,
        bg_rewrite_cells_12_2, 0,
    },
    {
        bg_rewrite_cells_11_0, bg_rewrite8_cells_11_1,
        bg_rewrite_cells_12_2, 0,
    },
    { bg_rewrite_cells_14_0, bg_rewrite_cells_14_1, 0, 0 },
    { bg_rewrite_cells_15_0, bg_rewrite_cells_15_1, 0, 0 },
    {
        bg_rewrite_cells_16_0, bg_rewrite_cells_16_1,
        bg_rewrite_cells_16_2, 0,
    },
    {
        bg_rewrite_cells_05_0, bg_rewrite_cells_05_1,
        bg_rewrite_cells_05_2, 0,
    },
    { bg_rewrite_cells_06_0, bg_rewrite_cells_06_1, 0, 0 },
    { bg_rewrite_cells_19_0, 0, 0, 0 },
    {
        bg_rewrite_cells_20_0, bg_rewrite_cells_20_1,
        bg_rewrite_cells_20_2, 0,
    },
    {
        bg_rewrite_cells_20_0, bg_rewrite_cells_20_1,
        bg_rewrite_cells_20_2, 0,
    },
};

/* 02005F84 */
const TILEREQ* bg_etc_cell_tbl[5][4] = {
    { bg_etc_cells_0, 0, 0, 0 },
    { bg_etc_cells_1, 0, 0, 0 },
    { bg_etc_cells_2, 0, 0, 0 },
    { bg_etc_cells_3, 0, 0, 0 },
    { bg_etc_cells_4, 0, 0, 0 },
};

/* 02005FD4 */
/* per stage and BG layer, the six deformation tables of a layer's deff_* pointers; nothing in the program refers to
   it (provisional name) */
BG_DEFF_TBL bg_deff_tbl[18][4] = {
    {
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_4, (const s16 *)bg_deff_plus0_tbl_4,
            (const s16 *)bg_deff_rl1_tbl_4, (const s16 *)bg_deff_plus1_tbl_4,
            (const s16 *)bg_deff_minus0_tbl_4, (const s16 *)bg_deff_minus1_tbl_4,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_3, (const s16 *)bg_deff_plus0_tbl_3,
            (const s16 *)bg_deff_rl1_tbl_3, (const s16 *)bg_deff_plus1_tbl_3,
            (const s16 *)bg_deff_minus0_tbl_3, (const s16 *)bg_deff_minus1_tbl_3,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_2, (const s16 *)bg_deff_plus0_tbl_2,
            (const s16 *)bg_deff_rl1_tbl_2, (const s16 *)bg_deff_plus1_tbl_2,
            (const s16 *)bg_deff_minus0_tbl_2, (const s16 *)bg_deff_minus1_tbl_2,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_2, (const s16 *)bg_deff_plus0_tbl_2,
            (const s16 *)bg_deff_rl1_tbl_2, (const s16 *)bg_deff_plus1_tbl_2,
            (const s16 *)bg_deff_minus0_tbl_2, (const s16 *)bg_deff_minus1_tbl_2,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_4, (const s16 *)bg_deff_plus0_tbl_4,
            (const s16 *)bg_deff_rl1_tbl_4, (const s16 *)bg_deff_plus1_tbl_4,
            (const s16 *)bg_deff_minus0_tbl_4, (const s16 *)bg_deff_minus1_tbl_4,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_1, (const s16 *)bg_deff_plus0_tbl_1,
            (const s16 *)bg_deff_rl1_tbl_1, (const s16 *)bg_deff_plus1_tbl_1,
            (const s16 *)bg_deff_minus0_tbl_1, (const s16 *)bg_deff_minus1_tbl_1,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_3, (const s16 *)bg_deff_plus0_tbl_3,
            (const s16 *)bg_deff_rl1_tbl_3, (const s16 *)bg_deff_plus1_tbl_3,
            (const s16 *)bg_deff_minus0_tbl_3, (const s16 *)bg_deff_minus1_tbl_3,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_2, (const s16 *)bg_deff_plus0_tbl_2,
            (const s16 *)bg_deff_rl1_tbl_2, (const s16 *)bg_deff_plus1_tbl_2,
            (const s16 *)bg_deff_minus0_tbl_2, (const s16 *)bg_deff_minus1_tbl_2,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_4, (const s16 *)bg_deff_plus0_tbl_4,
            (const s16 *)bg_deff_rl1_tbl_4, (const s16 *)bg_deff_plus1_tbl_4,
            (const s16 *)bg_deff_minus0_tbl_4, (const s16 *)bg_deff_minus1_tbl_4,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_3, (const s16 *)bg_deff_plus0_tbl_3,
            (const s16 *)bg_deff_rl1_tbl_3, (const s16 *)bg_deff_plus1_tbl_3,
            (const s16 *)bg_deff_minus0_tbl_3, (const s16 *)bg_deff_minus1_tbl_3,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_4, (const s16 *)bg_deff_plus0_tbl_4,
            (const s16 *)bg_deff_rl1_tbl_4, (const s16 *)bg_deff_plus1_tbl_4,
            (const s16 *)bg_deff_minus0_tbl_4, (const s16 *)bg_deff_minus1_tbl_4,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_3, (const s16 *)bg_deff_plus0_tbl_3,
            (const s16 *)bg_deff_rl1_tbl_3, (const s16 *)bg_deff_plus1_tbl_3,
            (const s16 *)bg_deff_minus0_tbl_3, (const s16 *)bg_deff_minus1_tbl_3,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_3, (const s16 *)bg_deff_plus0_tbl_3,
            (const s16 *)bg_deff_rl1_tbl_3, (const s16 *)bg_deff_plus1_tbl_3,
            (const s16 *)bg_deff_minus0_tbl_3, (const s16 *)bg_deff_minus1_tbl_3,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_3, (const s16 *)bg_deff_plus0_tbl_3,
            (const s16 *)bg_deff_rl1_tbl_3, (const s16 *)bg_deff_plus1_tbl_3,
            (const s16 *)bg_deff_minus0_tbl_3, (const s16 *)bg_deff_minus1_tbl_3,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_3, (const s16 *)bg_deff_plus0_tbl_3,
            (const s16 *)bg_deff_rl1_tbl_3, (const s16 *)bg_deff_plus1_tbl_3,
            (const s16 *)bg_deff_minus0_tbl_3, (const s16 *)bg_deff_minus1_tbl_3,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_2, (const s16 *)bg_deff_plus0_tbl_2,
            (const s16 *)bg_deff_rl1_tbl_2, (const s16 *)bg_deff_plus1_tbl_2,
            (const s16 *)bg_deff_minus0_tbl_2, (const s16 *)bg_deff_minus1_tbl_2,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_3, (const s16 *)bg_deff_plus0_tbl_3,
            (const s16 *)bg_deff_rl1_tbl_3, (const s16 *)bg_deff_plus1_tbl_3,
            (const s16 *)bg_deff_minus0_tbl_3, (const s16 *)bg_deff_minus1_tbl_3,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_2, (const s16 *)bg_deff_plus0_tbl_2,
            (const s16 *)bg_deff_rl1_tbl_2, (const s16 *)bg_deff_plus1_tbl_2,
            (const s16 *)bg_deff_minus0_tbl_2, (const s16 *)bg_deff_minus1_tbl_2,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_3, (const s16 *)bg_deff_plus0_tbl_3,
            (const s16 *)bg_deff_rl1_tbl_3, (const s16 *)bg_deff_plus1_tbl_3,
            (const s16 *)bg_deff_minus0_tbl_3, (const s16 *)bg_deff_minus1_tbl_3,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_2, (const s16 *)bg_deff_plus0_tbl_2,
            (const s16 *)bg_deff_rl1_tbl_2, (const s16 *)bg_deff_plus1_tbl_2,
            (const s16 *)bg_deff_minus0_tbl_2, (const s16 *)bg_deff_minus1_tbl_2,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_1, (const s16 *)bg_deff_plus0_tbl_1,
            (const s16 *)bg_deff_rl1_tbl_1, (const s16 *)bg_deff_plus1_tbl_1,
            (const s16 *)bg_deff_minus0_tbl_1, (const s16 *)bg_deff_minus1_tbl_1,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_2, (const s16 *)bg_deff_plus0_tbl_2,
            (const s16 *)bg_deff_rl1_tbl_2, (const s16 *)bg_deff_plus1_tbl_2,
            (const s16 *)bg_deff_minus0_tbl_2, (const s16 *)bg_deff_minus1_tbl_2,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_3, (const s16 *)bg_deff_plus0_tbl_3,
            (const s16 *)bg_deff_rl1_tbl_3, (const s16 *)bg_deff_plus1_tbl_3,
            (const s16 *)bg_deff_minus0_tbl_3, (const s16 *)bg_deff_minus1_tbl_3,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_2, (const s16 *)bg_deff_plus0_tbl_2,
            (const s16 *)bg_deff_rl1_tbl_2, (const s16 *)bg_deff_plus1_tbl_2,
            (const s16 *)bg_deff_minus0_tbl_2, (const s16 *)bg_deff_minus1_tbl_2,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
    {
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
        {
            (const s16 *)bg_deff_rl0_tbl_0, (const s16 *)bg_deff_plus0_tbl_0,
            (const s16 *)bg_deff_rl1_tbl_0, (const s16 *)bg_deff_plus1_tbl_0,
            (const s16 *)bg_deff_minus0_tbl_0, (const s16 *)bg_deff_minus1_tbl_0,
        },
    },
};

s16 stage8_base_y;  /* 0201C258 */
BGW* bgw_ptr;  /* 0201C25C */
SUZI_CALC suzi_calc_w[2];  /* 0201C260 */
u16 suzi_line_buf[2048];  /* 0201C270 */
MVXY bg_mvxy;  /* 0201D270 */
s16 bg_stop;  /* 0201D288 */
s16 base_y_pos;  /* 0201D28A */
/* after base_y_pos: nothing refers to it by name or address */
u8 base_y_pos_tail[12];  /* 0201D28C */
s16 mark_gfx_ofs[128];  /* 0201D298 */
s16 mark_gfx_cells[128];  /* 0201D398 */
s16 mark_gfx_colcd[128];  /* 0201D498 */
s16 bg_ofs_work[3];  /* 0201D598 */
s16 bg_zoom_x_pos;  /* 0201D59E */
s16 bg_sp_work;  /* 0201D5A0 */
s16 bg_zoom_d;  /* 0201D5A2 */
s16 bg_deff_type;  /* 0201D5A4 */
s16 bg_zoom_old_x;  /* 0201D5A6 */
s16 bg_land_flag;  /* 0201D5A8 */
s8 demo_car_flag[2];  /* 0201D5AA */
s16 bg_etc_flag;  /* 0201D5AC */
s16 bg_stop2;  /* 0201D5AE */
s16 chase_x;  /* 0201D5B0 */
s16 chase_y;  /* 0201D5B2 */
s16 chase_time_x;  /* 0201D5B4 */
s16 chase_time_y;  /* 0201D5B6 */
/* after chase_time_y: nothing refers to it by name or address */
u8 chase_time_y_tail[4];  /* 0201D5B8 */
s8 akebono_flag;  /* 0201D5BC */
s8 seraph_flag;  /* 0201D5BD */
s8 aku_flag;  /* 0201D5BE */
s8 bg_select_no;  /* 0201D5BF */
s8 sa_pa_flag;  /* 0201D5C0 */
s8 bg_app;  /* 0201D5C1 */
s8 bg_vbl_trans_flag;  /* 0201D5C2 */
s16 ls_rate0;  /* 0201D5C4 */
s16 ls_cnt1;  /* 0201D5C6 */
s16 ls_cnt2;  /* 0201D5C8 */
/* after ls_cnt2: nothing refers to it by name or address */
u8 ls_cnt2_tail[2];  /* 0201D5CA */
s8 bg_demo_shot;  /* 0201D5CC */
s8 bg_demo_cnt;  /* 0201D5CD */
/* after bg_demo_cnt: nothing refers to it by name or address */
u8 bg_demo_cnt_tail[2];  /* 0201D5CE */
s16 bg100_cnt;  /* 0201D5D0 */
s16 bg100_timer;  /* 0201D5D2 */
s16 bg080_quake_sw;  /* 0201D5D4 */
/* after bg080_quake_sw: nothing refers to it by name or address */
u8 bg080_quake_sw_tail[2];  /* 0201D5D6 */
