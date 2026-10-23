/*
 * STAGE_CHAR.C  Stage object scripts
 *
 * Each *_char_table is an index of animation scripts followed by the scripts, in the format of the
 * fighters' tables: an effect's work takes the table as its char_table and set_char_move_init
 * starts its scripts. See charscr.h for the line layouts. The comment of each index table names the
 * modules that use it.
 *
 * Index tables here: stg00_char_table, eff19_char_table, stg01_char_table, stg12_char_table,
 * result_char_table, eff44_char_table, stg02_char_table, eff35_char_table1, eff35_char_table2,
 * stg11_char_table, stg03_char_table, eff21_char_table, eff22_char_table, stg10_char_table,
 * eff28_char_table, eff29_type0_char_table, eff29_type1_char_table, stg04_char_table,
 * stg05_char_table, eff08_char_table, eff07_char_table, stg06_char_table, stg07_char_table,
 * eff77_char_table, eff78_char_table, eff79_char_table, eff80_char_table, eff81_char_table,
 * eff45_char_table, eff56_char_table, eff54_char_table, eff86_char_table, eff09_char_table,
 * brz_char_table, eff90_char_table, eff75_char_table, eff67_char_table.
 */

#include "types.h"
#include "structs.h"
#include "charscr.h"

#pragma section CHR

extern const u16 stg00_char_table_000[], stg00_char_table_001[], stg00_char_table_002[], stg00_char_table_003[],
                 stg00_char_table_004[], stg00_char_table_005[], stg00_char_table_006[], stg00_char_table_007[],
                 stg00_char_table_008[], stg00_char_table_009[], stg00_char_table_010[];

/* stg00_char_table: 11 entries (no closing 0: the next table follows); debug viewer: BOSS STAGE OBJ; used by EFF47, dbg_work, eff05 */
const u32 stg00_char_table[11] = {
    (u32)stg00_char_table_000,  /* 0 */
    (u32)stg00_char_table_001,  /* 1 */
    (u32)stg00_char_table_002,  /* 2 */
    (u32)stg00_char_table_003,  /* 3 */
    (u32)stg00_char_table_004,  /* 4 */
    (u32)stg00_char_table_005,  /* 5 */
    (u32)stg00_char_table_006,  /* 6 */
    (u32)stg00_char_table_007,  /* 7 */
    (u32)stg00_char_table_008,  /* 8 */
    (u32)stg00_char_table_009,  /* 9 */
    (u32)stg00_char_table_010,  /* 10 */
};

extern const u16 eff19_char_table_000[], eff19_char_table_001[], eff19_char_table_002[], eff19_char_table_003[],
                 eff19_char_table_004[], eff19_char_table_005[], eff19_char_table_006[], eff19_char_table_007[],
                 eff19_char_table_008[], eff19_char_table_009[], eff19_char_table_010[], eff19_char_table_011[],
                 eff19_char_table_012[], eff19_char_table_013[], eff19_char_table_014[], eff19_char_table_015[],
                 eff19_char_table_016[], eff19_char_table_017[], eff19_char_table_018[];

/* eff19_char_table: 19 entries; used by EFF19 */
const u32 eff19_char_table[20] = {
    (u32)eff19_char_table_000,  /* 0 */
    (u32)eff19_char_table_001,  /* 1 */
    (u32)eff19_char_table_002,  /* 2 */
    (u32)eff19_char_table_003,  /* 3 */
    (u32)eff19_char_table_004,  /* 4 */
    (u32)eff19_char_table_005,  /* 5 */
    (u32)eff19_char_table_006,  /* 6 */
    (u32)eff19_char_table_007,  /* 7 */
    (u32)eff19_char_table_008,  /* 8 */
    (u32)eff19_char_table_009,  /* 9 */
    (u32)eff19_char_table_010,  /* 10 */
    (u32)eff19_char_table_011,  /* 11 */
    (u32)eff19_char_table_012,  /* 12 */
    (u32)eff19_char_table_013,  /* 13 */
    (u32)eff19_char_table_014,  /* 14 */
    (u32)eff19_char_table_015,  /* 15 */
    (u32)eff19_char_table_016,  /* 16 */
    (u32)eff19_char_table_017,  /* 17 */
    (u32)eff19_char_table_018,  /* 18 */
    0
};

/* script: 0 */
const u16 stg00_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg00_char_table_000[108] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x600E),
    L2(11, 0, 0, 0, 0, 0, 0, 0x600F),
    L2(11, 0, 0, 0, 0, 0, 0, 0x6010),
    L2(11, 0, 0, 0, 0, 0, 0, 0x6011),
    L2(11, 0, 0, 0, 0, 0, 0, 0x6012),
    L2(11, 0, 0, 0, 0, 0, 0, 0x6013),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6014),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6015),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6016),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6017),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6018),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6019),
    CMD(CM_FOR, 0, 0, 3),
    L2(11, 0, 0, 0, 0, 0, 0, 0x600E),
    L2(11, 0, 0, 0, 0, 0, 0, 0x600F),
    L2(11, 0, 0, 0, 0, 0, 0, 0x6010),
    L2(11, 0, 0, 0, 0, 0, 0, 0x6011),
    L2(11, 0, 0, 0, 0, 0, 0, 0x6012),
    L2(11, 0, 0, 0, 0, 0, 0, 0x6013),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6014),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6015),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6016),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6017),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6018),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6019),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 stg00_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg00_char_table_001[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x6090),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 stg00_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg00_char_table_002[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x604E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 stg00_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg00_char_table_003[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x6092),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 stg00_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg00_char_table_004[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x6093),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 stg00_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg00_char_table_005[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x6094),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 stg00_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg00_char_table_006[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x6095),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 stg00_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg00_char_table_007[8] = {
    L2(26, 0, 0, 0, 0, 0, 0, 0x6096),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 stg00_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg00_char_table_008[24] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6097),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6098),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6099),
    L2(8, 0, 0, 0, 0, 0, 0, 0x609A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x609B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 stg00_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg00_char_table_009[8] = {
    L2(26, 0, 0, 0, 0, 0, 0, 0x6091),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 stg00_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg00_char_table_010[8] = {
    L2(26, 0, 0, 0, 0, 0, 0, 0x6024),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff19_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_000[40] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x604A),
    L2(9, 0, 0, 0, 0, 0, 0, 0x604B),
    L2(9, 0, 0, 0, 0, 0, 0, 0x604C),
    L2(9, 0, 0, 0, 0, 0, 0, 0x604D),
    L2(9, 0, 0, 0, 0, 0, 0, 0x604D),
    L2(9, 0, 0, 0, 0, 0, 0, 0x604D),
    L2(9, 0, 0, 0, 0, 0, 0, 0x604D),
    L2(9, 0, 0, 0, 0, 0, 0, 0x604D),
    L2(9, 0, 0, 0, 0, 0, 0, 0x604D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff19_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_001[24] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x602E),
    L2(9, 0, 0, 0, 0, 0, 0, 0x602F),
    L2(9, 0, 0, 0, 0, 0, 0, 0x6030),
    L2(9, 0, 0, 0, 0, 0, 0, 0x6031),
    L2(9, 1, 0, 0, 0, 0, 0, 0x6031),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff19_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_002[32] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x6032),
    L2(9, 0, 0, 0, 0, 0, 0, 0x6033),
    L2(9, 0, 0, 0, 0, 0, 0, 0x6034),
    L2(9, 0, 0, 0, 0, 0, 0, 0x6035),
    L2(9, 0, 0, 0, 0, 0, 0, 0x6036),
    L2(9, 0, 0, 0, 0, 0, 0, 0x6037),
    L2(9, 1, 0, 0, 0, 0, 0, 0x6037),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff19_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_003[24] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x6038),
    L2(9, 0, 0, 0, 0, 0, 0, 0x6039),
    L2(9, 0, 0, 0, 0, 0, 0, 0x603A),
    L2(9, 0, 0, 0, 0, 0, 0, 0x603B),
    L2(9, 1, 0, 0, 0, 0, 0, 0x603B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff19_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_004[28] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x603C),
    L2(9, 0, 0, 0, 0, 0, 0, 0x603D),
    L2(9, 0, 0, 0, 0, 0, 0, 0x603E),
    L2(9, 0, 0, 0, 0, 0, 0, 0x603F),
    L2(9, 0, 0, 0, 0, 0, 0, 0x6040),
    L2(9, 1, 0, 0, 0, 0, 0, 0x6040),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 eff19_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_005[16] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x6041),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6042),
    L2(2, 1, 0, 0, 0, 0, 0, 0x6042),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 eff19_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_006[28] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x6045),
    L2(9, 0, 0, 0, 0, 0, 0, 0x6046),
    L2(9, 0, 0, 0, 0, 0, 0, 0x6047),
    L2(9, 0, 0, 0, 0, 0, 0, 0x6048),
    L2(9, 0, 0, 0, 0, 0, 0, 0x6049),
    L2(2, 1, 0, 0, 0, 0, 0, 0x6049),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 eff19_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_007[40] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x604F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6050),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6051),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6052),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6053),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6054),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6055),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6056),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6057),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 eff19_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_008[40] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6058),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6059),
    L2(8, 0, 0, 0, 0, 0, 0, 0x605A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x605B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x605C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x605D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x605E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x605F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6060),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 eff19_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_009[40] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6061),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6062),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6063),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6064),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6065),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6066),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6067),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6068),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6069),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 eff19_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_010[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x606A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 eff19_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_011[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x606B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 eff19_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_012[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x606C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 eff19_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_013[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x606D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 eff19_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_014[40] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6390),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6391),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6392),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6393),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6394),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6395),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6396),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6397),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6398),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 eff19_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_015[40] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6399),
    L2(8, 0, 0, 0, 0, 0, 0, 0x639A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x639B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x639C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x639D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x639E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x639F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63A0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63A1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16 */
const u16 eff19_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_016[40] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x63A2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63A3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63A4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63A5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63A6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63A7),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63A8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63A9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63AA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 17 */
const u16 eff19_char_table_017_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_017[40] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x63D0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63D1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63D2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63D3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63D4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63D5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63D6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63D7),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63D8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 18 */
const u16 eff19_char_table_018_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff19_char_table_018[40] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x63D9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63DA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63DB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63DC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63DD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63DE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63DF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63E0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x63E1),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 stg01_char_table_000[], stg01_char_table_001[], stg01_char_table_002[], stg01_char_table_003[],
                 stg01_char_table_004[], stg01_char_table_005[], stg01_char_table_006[], stg01_char_table_007[],
                 stg01_char_table_008[], stg01_char_table_009[], stg01_char_table_010[], stg01_char_table_011[],
                 stg01_char_table_012[], stg01_char_table_013[], stg01_char_table_014[], stg01_char_table_015[],
                 stg01_char_table_016[], stg01_char_table_019[], stg01_char_table_020[], stg01_char_table_022[],
                 stg01_char_table_023[], stg01_char_table_024[], stg01_char_table_026[], stg01_char_table_027[],
                 stg01_char_table_028[], stg01_char_table_029[], stg01_char_table_030[], stg01_char_table_031[],
                 stg01_char_table_032[], stg01_char_table_033[], stg01_char_table_034[];

/* stg01_char_table: 35 entries; debug viewer: N.Y 1 OBJ; used by EFF69, EFF70, dbg_work, eff05 */
const u32 stg01_char_table[36] = {
    (u32)stg01_char_table_000,  /* 0 */
    (u32)stg01_char_table_001,  /* 1 */
    (u32)stg01_char_table_002,  /* 2 */
    (u32)stg01_char_table_003,  /* 3 */
    (u32)stg01_char_table_004,  /* 4 */
    (u32)stg01_char_table_005,  /* 5 */
    (u32)stg01_char_table_006,  /* 6 */
    (u32)stg01_char_table_007,  /* 7 */
    (u32)stg01_char_table_008,  /* 8 */
    (u32)stg01_char_table_009,  /* 9 */
    (u32)stg01_char_table_010,  /* 10 */
    (u32)stg01_char_table_011,  /* 11 */
    (u32)stg01_char_table_012,  /* 12 */
    (u32)stg01_char_table_013,  /* 13 */
    (u32)stg01_char_table_014,  /* 14 */
    (u32)stg01_char_table_015,  /* 15 */
    (u32)stg01_char_table_016,  /* 16 */
    (u32)stg01_char_table_016,  /* 17 */
    (u32)stg01_char_table_016,  /* 18 */
    (u32)stg01_char_table_019,  /* 19 */
    (u32)stg01_char_table_020,  /* 20 */
    (u32)stg01_char_table_020,  /* 21 */
    (u32)stg01_char_table_022,  /* 22 */
    (u32)stg01_char_table_023,  /* 23 */
    (u32)stg01_char_table_024,  /* 24 */
    (u32)stg01_char_table_024,  /* 25 */
    (u32)stg01_char_table_026,  /* 26 */
    (u32)stg01_char_table_027,  /* 27 */
    (u32)stg01_char_table_028,  /* 28 */
    (u32)stg01_char_table_029,  /* 29 */
    (u32)stg01_char_table_030,  /* 30 */
    (u32)stg01_char_table_031,  /* 31 */
    (u32)stg01_char_table_032,  /* 32 */
    (u32)stg01_char_table_033,  /* 33 */
    (u32)stg01_char_table_034,  /* 34 */
    0
};

/* script: 0 */
const u16 stg01_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_000[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x5625),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 stg01_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_001[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5626),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 stg01_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_002[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5627),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 stg01_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_003[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5628),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 stg01_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_004[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5629),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 stg01_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_005[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x562A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 stg01_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_006[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x562B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 stg01_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_007[8] = {
    L2(26, 0, 0, 0, 0, 0, 0, 0x562C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 stg01_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_008[124] = {
    L2(24, 0, 0, 0, 0, 0, 0, 0x5631),
    L2(32, 0, 0, 0, 0, 0, 0, 0x5632),
    L2(56, 0, 0, 0, 0, 0, 0, 0x5633),
    CMD(CM_FOR, 0, 0, 2),
    L2(24, 0, 0, 0, 0, 0, 0, 0x5632),
    L2(32, 0, 0, 0, 0, 0, 0, 0x5631),
    L2(24, 0, 0, 0, 0, 0, 0, 0x5632),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5633),
    CMD(CM_NEX, 0, 0, 0),
    L2(24, 0, 0, 0, 0, 0, 0, 0x5632),
    L2(32, 0, 0, 0, 0, 0, 0, 0x5631),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5632),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5634),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5630),
    L2(8, 0, 0, 0, 0, 0, 0, 0x562F),
    CMD(CM_FOR, 0, 0, 4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x562E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x562D),
    CMD(CM_NEX, 0, 0, 0),
    L2(16, 0, 0, 0, 0, 0, 0, 0x5635),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5636),
    L2(16, 0, 0, 0, 0, 0, 0, 0x5637),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5638),
    L2(16, 0, 0, 0, 0, 0, 0, 0x5639),
    L2(8, 0, 0, 0, 0, 0, 0, 0x563A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x563B),
    L2(104, 0, 0, 0, 0, 0, 0, 0x563C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5639),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5637),
    L2(88, 0, 0, 0, 0, 0, 0, 0x5631),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 stg01_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_009[140] = {
    L2(14, 0, 0, 0, 0, 0, 0, 0x5653),
    L2(14, 0, 0, 0, 0, 0, 0, 0x5654),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5655),
    L2(7, 0, 0, 0, 0, 0, 0, 0x565D),
    L2(7, 0, 0, 0, 0, 0, 0, 0x565E),
    CMD(CM_FOR, 0, 0, 2),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5653),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5654),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5655),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5656),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5657),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5658),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5659),
    L2(7, 0, 0, 0, 0, 0, 0, 0x565A),
    L2(7, 0, 0, 0, 0, 0, 0, 0x565B),
    L2(7, 0, 0, 0, 0, 0, 0, 0x565C),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_FOR, 0, 0, 2),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5653),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5654),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5655),
    L2(7, 0, 0, 0, 0, 0, 0, 0x565D),
    CMD(CM_NEX, 0, 0, 0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x565E),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5653),
    L2(14, 0, 0, 0, 0, 0, 0, 0x5654),
    L2(14, 0, 0, 0, 0, 0, 0, 0x5655),
    L2(14, 0, 0, 0, 0, 0, 0, 0x565D),
    L2(14, 0, 0, 0, 0, 0, 0, 0x565E),
    L2(140, 0, 0, 0, 0, 0, 0, 0x5653),
    L2(14, 0, 0, 0, 0, 0, 0, 0x5654),
    L2(14, 0, 0, 0, 0, 0, 0, 0x5655),
    L2(14, 0, 0, 0, 0, 0, 0, 0x565D),
    L2(14, 0, 0, 0, 0, 0, 0, 0x565E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 stg01_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_010[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x565F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 stg01_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_011[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x5660),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 stg01_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_012[68] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x5661),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5662),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5663),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5664),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5665),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5666),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5667),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5668),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5669),
    L2(8, 0, 0, 0, 0, 0, 0, 0x566A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x566B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x566C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x566D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x566E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x566F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5670),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 stg01_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_013[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x56C6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 stg01_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_014[160] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x5721),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5722),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5723),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5724),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5725),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5726),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5727),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5728),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5729),
    L2(9, 0, 0, 0, 0, 0, 0, 0x572A),
    L2(9, 0, 0, 0, 0, 0, 0, 0x572B),
    L2(9, 0, 0, 0, 0, 0, 0, 0x572C),
    L2(9, 0, 0, 0, 0, 0, 0, 0x572D),
    L2(9, 0, 0, 0, 0, 0, 0, 0x572E),
    L2(9, 0, 0, 0, 0, 0, 0, 0x572F),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5730),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5731),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5732),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5733),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5734),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5735),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5736),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5737),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5738),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5739),
    L2(9, 0, 0, 0, 0, 0, 0, 0x573A),
    L2(9, 0, 0, 0, 0, 0, 0, 0x573B),
    L2(9, 0, 0, 0, 0, 0, 0, 0x573C),
    L2(9, 0, 0, 0, 0, 0, 0, 0x573D),
    L2(9, 0, 0, 0, 0, 0, 0, 0x573E),
    L2(9, 0, 0, 0, 0, 0, 0, 0x573F),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5740),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5741),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5742),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5743),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5744),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5745),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5746),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5747),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 stg01_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_015[52] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x5751),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5752),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5753),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5754),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5755),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5756),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5757),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5758),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5759),
    L2(9, 0, 0, 0, 0, 0, 0, 0x575A),
    L2(9, 0, 0, 0, 0, 0, 0, 0x575B),
    L2(9, 0, 0, 0, 0, 0, 0, 0x575C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16, 17, 18 */
const u16 stg01_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_016[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x563D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 19 */
const u16 stg01_char_table_019_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_019[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x563E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 20, 21 */
const u16 stg01_char_table_020_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_020[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x563F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 22 */
const u16 stg01_char_table_022_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_022[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x5640),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 23 */
const u16 stg01_char_table_023_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_023[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x5641),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 24, 25 */
const u16 stg01_char_table_024_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_024[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x5642),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 26 */
const u16 stg01_char_table_026_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_026[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x5643),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 27 */
const u16 stg01_char_table_027_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_027[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x5644),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 28 */
const u16 stg01_char_table_028_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_028[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x5645),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 29 */
const u16 stg01_char_table_029_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_029[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x5646),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 30 */
const u16 stg01_char_table_030_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_030[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x5647),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 31 */
const u16 stg01_char_table_031_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_031[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x5648),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 32 */
const u16 stg01_char_table_032_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_032[44] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x56C7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x56C8),
    L2(2, 0, 0, 0, 0, 0, 0, 0x56C9),
    L2(2, 0, 0, 0, 0, 0, 0, 0x56CA),
    L2(2, 0, 0, 0, 0, 0, 0, 0x56CB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x56CC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x56CD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x56CE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x56CF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x56D0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 33 */
const u16 stg01_char_table_033_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_033[496] = {
    L2(48, 0, 0, 0, 0, 0, 0, 0x5721),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5722),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5723),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5724),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5723),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5722),
    CMD(CM_FOR, 0, 0, 2),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5721),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5722),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5723),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5724),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5723),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5722),
    CMD(CM_NEX, 0, 0, 0),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5721),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5725),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5726),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5725),
    CMD(CM_FOR, 0, 0, 2),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5721),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5722),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5723),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5724),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5723),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5722),
    CMD(CM_NEX, 0, 0, 0),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5721),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5722),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5723),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5724),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5723),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5722),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5721),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5725),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5726),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5725),
    L2(64, 0, 0, 0, 0, 0, 0, 0x5721),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5722),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5736),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5737),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5738),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5739),
    L2(8, 0, 0, 0, 0, 0, 0, 0x573A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x573B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x573C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x573D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x573E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x573F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5740),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5741),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5742),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5743),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5744),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5745),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5746),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5747),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5721),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5725),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5726),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5727),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5728),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5729),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572A),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572B),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572D),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572B),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572D),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572E),
    CMD(CM_FOR, 0, 0, 3),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572F),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5730),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5731),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5732),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5733),
    CMD(CM_NEX, 0, 0, 0),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572D),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572B),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572D),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572E),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572F),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5730),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5731),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5732),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5733),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5734),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5725),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5726),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5727),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5726),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5725),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5721),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5735),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5721),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5725),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5726),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5727),
    CMD(CM_FOR, 0, 0, 2),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5728),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5729),
    L2(10, 0, 0, 0, 0, 0, 0, 0x572A),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5729),
    CMD(CM_NEX, 0, 0, 0),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5728),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5727),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5726),
    CMD(CM_FOR, 0, 0, 2),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5721),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5722),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5723),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5724),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5723),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5722),
    CMD(CM_NEX, 0, 0, 0),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5721),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5725),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5726),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5725),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5721),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 34 */
const u16 stg01_char_table_034_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg01_char_table_034[52] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5751),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5759),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5753),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5754),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5755),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5756),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5757),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5758),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5759),
    L2(6, 0, 0, 0, 0, 0, 0, 0x575A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x575B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x575C),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 stg12_char_table_000[], stg12_char_table_001[], stg12_char_table_002[], stg12_char_table_003[],
                 stg12_char_table_004[], stg12_char_table_005[], stg12_char_table_006[], stg12_char_table_007[],
                 stg12_char_table_008[], stg12_char_table_009[], stg12_char_table_010[], stg12_char_table_011[],
                 stg12_char_table_012[], stg12_char_table_013[], stg12_char_table_014[], stg12_char_table_015[],
                 stg12_char_table_016[], stg12_char_table_017[], stg12_char_table_018[], stg12_char_table_019[],
                 stg12_char_table_020[], stg12_char_table_021[], stg12_char_table_022[], stg12_char_table_023[],
                 stg12_char_table_024[];

/* stg12_char_table: 25 entries (no closing 0: the next table follows); debug viewer: N.Y 2 64 OBJ; used by dbg_work, eff05 */
const u32 stg12_char_table[25] = {
    (u32)stg12_char_table_000,  /* 0 */
    (u32)stg12_char_table_001,  /* 1 */
    (u32)stg12_char_table_002,  /* 2 */
    (u32)stg12_char_table_003,  /* 3 */
    (u32)stg12_char_table_004,  /* 4 */
    (u32)stg12_char_table_005,  /* 5 */
    (u32)stg12_char_table_006,  /* 6 */
    (u32)stg12_char_table_007,  /* 7 */
    (u32)stg12_char_table_008,  /* 8 */
    (u32)stg12_char_table_009,  /* 9 */
    (u32)stg12_char_table_010,  /* 10 */
    (u32)stg12_char_table_011,  /* 11 */
    (u32)stg12_char_table_012,  /* 12 */
    (u32)stg12_char_table_013,  /* 13 */
    (u32)stg12_char_table_014,  /* 14 */
    (u32)stg12_char_table_015,  /* 15 */
    (u32)stg12_char_table_016,  /* 16 */
    (u32)stg12_char_table_017,  /* 17 */
    (u32)stg12_char_table_018,  /* 18 */
    (u32)stg12_char_table_019,  /* 19 */
    (u32)stg12_char_table_020,  /* 20 */
    (u32)stg12_char_table_021,  /* 21 */
    (u32)stg12_char_table_022,  /* 22 */
    (u32)stg12_char_table_023,  /* 23 */
    (u32)stg12_char_table_024,  /* 24 */
};

extern const u16 result_char_table_000[], result_char_table_001[], result_char_table_002[], result_char_table_003[],
                 result_char_table_004[], result_char_table_005[];

/* result_char_table: 6 entries; used by EFF61, EFF62 */
const u32 result_char_table[7] = {
    (u32)result_char_table_000,  /* 0 */
    (u32)result_char_table_001,  /* 1 */
    (u32)result_char_table_002,  /* 2 */
    (u32)result_char_table_003,  /* 3 */
    (u32)result_char_table_004,  /* 4 */
    (u32)result_char_table_005,  /* 5 */
    0
};

/* script: 0 */
const u16 stg12_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_000[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x5D30),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 stg12_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_001[12] = {
    L2(12, 0, 0, 0, 0, 0, 0, 0x5D36),
    L2(12, 0, 0, 0, 0, 0, 0, 0x5D37),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 stg12_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_002[12] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x5D7D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5D7E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 stg12_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_003[12] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x5D7F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5D80),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 stg12_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_004[36] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x5DAD),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5DAE),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5DAF),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5DB0),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5DB1),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5DB2),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5DB3),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5DB4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 stg12_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_005[12] = {
    L2(24, 0, 0, 0, 0, 0, 0, 0x5E06),
    L2(24, 0, 0, 0, 0, 0, 0, 0x5E07),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 stg12_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_006[188] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E4A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E4B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E4C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E4D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E4E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E4F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E50),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E51),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E52),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E53),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E54),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E55),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E56),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E57),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E58),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E59),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E5A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E5B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E5C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E5D),
    CMD(CM_FOR, 0, 0, 4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E4A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E4B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E4C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E4D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E4E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E4F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E50),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E51),
    CMD(CM_NEX, 0, 0, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E52),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E53),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E54),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E55),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E56),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5E57),
    CMD(CM_FOR, 0, 0, 5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5E4A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5E4B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5E4C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5E4D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5E4E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5E4F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5E50),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5E51),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 stg12_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_007[8] = {
    L2(16, 0, 0, 0, 0, 0, 0, 0x5E5E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 stg12_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_008[36] = {
    L2(16, 0, 0, 0, 0, 0, 0, 0x5E5E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5E5F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5E60),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5E61),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5E62),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5E63),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5E64),
    L2(8, 1, 0, 0, 0, 0, 0, 0x5E64),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 stg12_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_009[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x5E08),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 stg12_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_010[276] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E08),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E09),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E0A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E0B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E65),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E0C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E0D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E0E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E0F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E10),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E11),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E12),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E13),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E14),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E15),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E16),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E17),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E18),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E19),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E1A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E1B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E1C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E1D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E1E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E1F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E20),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E21),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E22),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E23),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E24),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E25),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E26),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E27),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E28),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E29),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E30),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E31),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E32),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E33),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E34),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E35),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E36),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E37),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E38),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E39),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E3A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E3B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E3C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E3D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E3E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E3F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E40),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E41),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E42),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E43),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E44),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E45),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E46),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E47),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E48),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E49),
    CMD(CM_JMP, 0, 23, 1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 23 */
const u16 stg12_char_table_023_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_023[280] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E1F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E20),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E21),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E22),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E23),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E24),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E25),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E26),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E27),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E28),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E29),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E30),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E31),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E32),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E33),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E34),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E35),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E36),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E37),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E38),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E39),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E3A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E3B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E3C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E3D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E3E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E3F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E40),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E41),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E42),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E43),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E44),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E45),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E46),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E47),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E48),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E49),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E1F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E20),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E21),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E22),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E23),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E24),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E25),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E26),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E27),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E28),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E29),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E2F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E30),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E31),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E32),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E33),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E34),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E35),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E36),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E37),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E38),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5E39),
    CMD(CM_END, 0, 0, 1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 24 */
const u16 stg12_char_table_024_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_024[8] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x5E64),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 stg12_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_011[100] = {
    CMD(CM_PA_X, 0, 1792, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F58),
    CMD(CM_PA_X, 0, 1792, 0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5F59),
    CMD(CM_PA_X, 0, 1792, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F5A),
    CMD(CM_PA_X, 0, 2816, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F5B),
    CMD(CM_PA_X, 0, 1792, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F5C),
    CMD(CM_PA_X, 0, 1792, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F5D),
    CMD(CM_PA_X, 0, 1792, 0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5F5E),
    CMD(CM_PA_X, 0, 1792, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F5F),
    CMD(CM_PA_X, 0, 1792, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F60),
    CMD(CM_PA_X, 0, 2816, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F61),
    CMD(CM_PA_X, 0, 1792, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F62),
    CMD(CM_PA_X, 0, 1792, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F63),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 stg12_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_012[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F68),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 stg12_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_013[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F69),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 stg12_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_014[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F6A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 stg12_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_015[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F6B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16 */
const u16 stg12_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_016[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F6C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 17 */
const u16 stg12_char_table_017_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_017[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F6D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 18 */
const u16 stg12_char_table_018_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_018[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F48),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 19 */
const u16 stg12_char_table_019_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_019[92] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x5F48),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F49),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F4A),
    L2(32, 0, 0, 0, 0, 0, 0, 0x5F4B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F4C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F4D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F4E),
    L2(16, 0, 0, 0, 0, 0, 0, 0x5F4F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F50),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F51),
    L2(16, 0, 0, 0, 0, 0, 0, 0x5F52),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F54),
    L2(32, 0, 0, 0, 0, 0, 0, 0x5F55),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F53),
    CMD(CM_FOR, 0, 0, 3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F55),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F53),
    CMD(CM_NEX, 0, 0, 0),
    L2(32, 0, 0, 0, 0, 0, 0, 0x5F55),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F53),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5F50),
    L2(6, 1, 0, 0, 0, 0, 0, 0x5F50),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 20 */
const u16 stg12_char_table_020_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_020[260] = {
    L2(100, 0, 0, 0, 0, 0, 0, 0x5F18),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F20),
    L2(32, 0, 0, 0, 0, 0, 0, 0x5F21),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F20),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1F),
    L2(32, 0, 0, 0, 0, 0, 0, 0x5F18),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F19),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1B),
    L2(32, 0, 0, 0, 0, 0, 0, 0x5F1C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F19),
    L2(200, 0, 0, 0, 0, 0, 0, 0x5F18),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F18),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F20),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F21),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F22),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F23),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5F24),
    CMD(CM_FOR, 0, 0, 2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F25),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F26),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F27),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F26),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F25),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F23),
    L2(16, 0, 0, 0, 0, 0, 0, 0x5F24),
    CMD(CM_NEX, 0, 0, 0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F28),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F29),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F2A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F2B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F29),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F28),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F23),
    L2(16, 0, 0, 0, 0, 0, 0, 0x5F24),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F25),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F26),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F27),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F26),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F25),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F23),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F24),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F28),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F29),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F2A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F2B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F29),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F28),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5F23),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5F24),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F20),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 21 */
const u16 stg12_char_table_021_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_021[72] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F18),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F1F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F2C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F2D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F2E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5F2F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5F30),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5F31),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5F30),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F32),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F33),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F34),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5F35),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5F36),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5F37),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5F38),
    CMD(CM_END, 0, 0, 13),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 22 */
const u16 stg12_char_table_022_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg12_char_table_022[52] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F18),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F22),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F21),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F22),
    L2(16, 0, 0, 0, 0, 0, 0, 0x5F39),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F3A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F3B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F3C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F3D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F3E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F3A),
    CMD(CM_END, 0, 0, 4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 result_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 result_char_table_000[136] = {
    L2(50, 0, 0, 0, 0, 0, 0, 0x5EB8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EB9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EB9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EB8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EB9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBD),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5EBE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5EBB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EB9),
    CMD(CM_FOR, 0, 0, 4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EB8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EB9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EB9),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBD),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5EBE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EC0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EB8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EB9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EBA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EB9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 result_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 result_char_table_001[440] = {
    L2(18, 0, 0, 0, 0, 0, 0, 0x5EE8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEA),
    CMD(CM_FOR, 0, 0, 3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEA),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_FOR, 0, 0, 2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE8),
    CMD(CM_NEX, 0, 0, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5EE9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5EEA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EED),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF4),
    CMD(CM_FOR, 0, 0, 3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF4),
    CMD(CM_NEX, 0, 0, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EED),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEB),
    L2(200, 0, 0, 0, 0, 0, 0, 0x5EE8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEA),
    CMD(CM_FOR, 0, 0, 3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEA),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_FOR, 0, 0, 2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE8),
    CMD(CM_NEX, 0, 0, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5EE8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5EE9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5EEA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEA),
    L2(200, 0, 0, 0, 0, 0, 0, 0x5EE8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EE8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EED),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF4),
    CMD(CM_FOR, 0, 0, 4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF4),
    CMD(CM_NEX, 0, 0, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EF0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EED),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5EEB),
    L2(6, 1, 0, 0, 0, 0, 0, 0x5EEB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 result_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 result_char_table_004[60] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EE8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EF6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EF7),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EF8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EF9),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5EFA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5EFB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5EFC),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5EFD),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5EFC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5EFE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5EFC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5EFE),
    CMD(CM_END, 0, 0, 12),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 result_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 result_char_table_005[60] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x5EE8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F0A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F0B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F0C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F0D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F0E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5F0F),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5F10),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5F11),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5F12),
    L2(48, 0, 0, 0, 0, 0, 0, 0x5F13),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5F12),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5F14),
    CMD(CM_END, 0, 0, 12),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 result_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 result_char_table_002[648] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FC8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FC9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FCA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FCB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FCC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FCD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FCE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FCF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FD8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FD9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDB),
    CMD(CM_FOR, 0, 0, 4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FE1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDD),
    CMD(CM_NEX, 0, 0, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FE1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FDB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FE2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FD9),
    L2(64, 0, 0, 0, 0, 0, 0, 0x5FD8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FD8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FD9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDB),
    CMD(CM_FOR, 0, 0, 3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FE1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDD),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FE1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FDB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FE2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FD9),
    L2(64, 0, 0, 0, 0, 0, 0, 0x5FD8),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FD8),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FD9),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDA),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDB),
    CMD(CM_FOR, 0, 0, 3),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDC),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDD),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FE1),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDD),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_FOR, 0, 0, 2),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDC),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDD),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FE1),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDD),
    CMD(CM_NEX, 0, 0, 0),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDC),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDD),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FE1),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDC),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FDB),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FE2),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5FD9),
    L2(64, 0, 0, 0, 0, 0, 0, 0x5FD8),
    CMD(CM_FOR, 0, 0, 4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FE8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FE9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FEA),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_FOR, 0, 0, 2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FE8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FE9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FEA),
    CMD(CM_NEX, 0, 0, 0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FD8),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FD9),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDA),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDB),
    CMD(CM_FOR, 0, 0, 4),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDC),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDD),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FE1),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDD),
    CMD(CM_NEX, 0, 0, 0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDC),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDD),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDF),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FE0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FE1),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDE),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDC),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FDB),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FE2),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5FD9),
    L2(64, 0, 0, 0, 0, 0, 0, 0x5FD8),
    CMD(CM_FOR, 0, 0, 4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FE8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FE9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FEA),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_FOR, 0, 0, 3),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5FE8),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5FE9),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5FEA),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FCF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FCE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FCD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FCC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FCB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FCA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FC9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5FC8),
    L2(8, 1, 0, 0, 0, 0, 0, 0x5FC8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 result_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 result_char_table_003[96] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FA8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FA9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FAA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FAB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FAC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FAD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FAE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FAF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FB0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FB1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FB2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FB3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FB4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FB5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FB6),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FB7),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FB8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FB9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FBA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5FBB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5FBA),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5FBB),
    CMD(CM_END, 0, 0, 21),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 eff44_char_table_000[], eff44_char_table_001[], eff44_char_table_002[], eff44_char_table_003[],
                 eff44_char_table_004[], eff44_char_table_005[], eff44_char_table_006[], eff44_char_table_007[],
                 eff44_char_table_008[], eff44_char_table_009[], eff44_char_table_010[], eff44_char_table_011[],
                 eff44_char_table_012[], eff44_char_table_013[], eff44_char_table_014[], eff44_char_table_015[],
                 eff44_char_table_016[];

/* eff44_char_table: 17 entries; debug viewer: N.Y 2 256 OBJ; used by EFF44, dbg_work */
const u32 eff44_char_table[18] = {
    (u32)eff44_char_table_000,  /* 0 */
    (u32)eff44_char_table_001,  /* 1 */
    (u32)eff44_char_table_002,  /* 2 */
    (u32)eff44_char_table_003,  /* 3 */
    (u32)eff44_char_table_004,  /* 4 */
    (u32)eff44_char_table_005,  /* 5 */
    (u32)eff44_char_table_006,  /* 6 */
    (u32)eff44_char_table_007,  /* 7 */
    (u32)eff44_char_table_008,  /* 8 */
    (u32)eff44_char_table_009,  /* 9 */
    (u32)eff44_char_table_010,  /* 10 */
    (u32)eff44_char_table_011,  /* 11 */
    (u32)eff44_char_table_012,  /* 12 */
    (u32)eff44_char_table_013,  /* 13 */
    (u32)eff44_char_table_014,  /* 14 */
    (u32)eff44_char_table_015,  /* 15 */
    (u32)eff44_char_table_016,  /* 16 */
    0
};

/* script: 0 */
const u16 eff44_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_000[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x5872),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff44_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_001[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x5875),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff44_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_002[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x58C7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff44_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_003[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x58C8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff44_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_004[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x58C9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 eff44_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_005[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x58CA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 eff44_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_006[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x58CB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 eff44_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_007[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x58CC),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 eff44_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_008[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x58CD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 eff44_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_009[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x58CE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 eff44_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_010[116] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x58CB),
    CMD(CM_FOR, 0, 0, 3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x58CF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x58D0),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_FOR, 0, 0, 3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x58D1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x58D2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x58D3),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_FOR, 0, 0, 3),
    L2(16, 0, 0, 0, 0, 0, 0, 0x58D4),
    L2(16, 0, 0, 0, 0, 0, 0, 0x58D5),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_FOR, 0, 0, 4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x58CB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x58CF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x58D0),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x58CB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x58CF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x58CB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x58D0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x58CB),
    CMD(CM_FOR, 0, 0, 4),
    L2(16, 0, 0, 0, 0, 0, 0, 0x58D6),
    L2(16, 0, 0, 0, 0, 0, 0, 0x58D7),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 eff44_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_011[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x587F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 eff44_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_012[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x5880),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 eff44_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_013[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x5881),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 eff44_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_014[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x5882),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 eff44_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_015[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x5883),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16 */
const u16 eff44_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff44_char_table_016[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x5884),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 stg02_char_table_000[], stg02_char_table_001[];

/* stg02_char_table: 2 entries (no closing 0: the next table follows); debug viewer: JAPAN 1 OBJ; used by dbg_work, eff05 */
const u32 stg02_char_table[2] = {
    (u32)stg02_char_table_000,  /* 0 */
    (u32)stg02_char_table_001,  /* 1 */
};

extern const u16 eff35_char_table1_000[], eff35_char_table1_001[], eff35_char_table1_002[], eff35_char_table1_003[];

/* eff35_char_table1: 4 entries (no closing 0: the next table follows); used by EFF35 */
const u32 eff35_char_table1[4] = {
    (u32)eff35_char_table1_000,  /* 0 */
    (u32)eff35_char_table1_001,  /* 1 */
    (u32)eff35_char_table1_002,  /* 2 */
    (u32)eff35_char_table1_003,  /* 3 */
};

extern const u16 eff35_char_table2_000[], eff35_char_table2_001[], eff35_char_table2_002[], eff35_char_table2_003[],
                 eff35_char_table2_004[], eff35_char_table2_005[], eff35_char_table2_006[], eff35_char_table2_007[],
                 eff35_char_table2_008[], eff35_char_table2_009[], eff35_char_table2_010[], eff35_char_table2_011[],
                 eff35_char_table2_012[], eff35_char_table2_013[], eff35_char_table2_014[], eff35_char_table2_015[];

/* eff35_char_table2: 16 entries; used by EFF35 */
const u32 eff35_char_table2[17] = {
    (u32)eff35_char_table2_000,  /* 0 */
    (u32)eff35_char_table2_001,  /* 1 */
    (u32)eff35_char_table2_002,  /* 2 */
    (u32)eff35_char_table2_003,  /* 3 */
    (u32)eff35_char_table2_004,  /* 4 */
    (u32)eff35_char_table2_005,  /* 5 */
    (u32)eff35_char_table2_006,  /* 6 */
    (u32)eff35_char_table2_007,  /* 7 */
    (u32)eff35_char_table2_008,  /* 8 */
    (u32)eff35_char_table2_009,  /* 9 */
    (u32)eff35_char_table2_010,  /* 10 */
    (u32)eff35_char_table2_011,  /* 11 */
    (u32)eff35_char_table2_012,  /* 12 */
    (u32)eff35_char_table2_013,  /* 13 */
    (u32)eff35_char_table2_014,  /* 14 */
    (u32)eff35_char_table2_015,  /* 15 */
    0
};

/* script: 0 */
const u16 stg02_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg02_char_table_000[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x41C6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 stg02_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg02_char_table_001[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x41C7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff35_char_table2_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_000[20] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x7718),
    L2(9, 0, 0, 0, 0, 0, 0, 0x7719),
    L2(9, 0, 0, 0, 0, 0, 0, 0x771A),
    L2(9, 0, 0, 0, 0, 0, 0, 0x771B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff35_char_table1_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table1_000[20] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x771C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x771D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x771E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x771F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff35_char_table2_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_001[20] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x7720),
    L2(9, 0, 0, 0, 0, 0, 0, 0x7721),
    L2(9, 0, 0, 0, 0, 0, 0, 0x7722),
    L2(9, 0, 0, 0, 0, 0, 0, 0x7723),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff35_char_table1_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table1_001[20] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x7724),
    L2(6, 0, 0, 0, 0, 0, 0, 0x7725),
    L2(6, 0, 0, 0, 0, 0, 0, 0x7726),
    L2(6, 0, 0, 0, 0, 0, 0, 0x7727),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff35_char_table2_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_002[20] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x7728),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7729),
    L2(8, 0, 0, 0, 0, 0, 0, 0x772A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x772B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff35_char_table1_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table1_002[20] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x772C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x772D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x772E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x772F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff35_char_table2_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_003[20] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x7730),
    L2(9, 0, 0, 0, 0, 0, 0, 0x7731),
    L2(9, 0, 0, 0, 0, 0, 0, 0x7732),
    L2(9, 0, 0, 0, 0, 0, 0, 0x7733),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff35_char_table1_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table1_003[20] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x7734),
    L2(6, 0, 0, 0, 0, 0, 0, 0x7735),
    L2(6, 0, 0, 0, 0, 0, 0, 0x7736),
    L2(6, 0, 0, 0, 0, 0, 0, 0x7737),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff35_char_table2_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_004[24] = {
    L2(13, 0, 0, 0, 0, 0, 0, 0x41F2),
    L2(13, 0, 0, 0, 0, 0, 0, 0x41F3),
    L2(13, 0, 0, 0, 0, 0, 0, 0x41F4),
    L2(13, 0, 0, 0, 0, 0, 0, 0x41F5),
    L2(13, 0, 0, 0, 0, 0, 0, 0x41F6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 eff35_char_table2_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_005[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4230),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 eff35_char_table2_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_006[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4231),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 eff35_char_table2_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_007[24] = {
    L2(13, 0, 0, 0, 0, 0, 0, 0x4232),
    L2(13, 0, 0, 0, 0, 0, 0, 0x4233),
    L2(13, 0, 0, 0, 0, 0, 0, 0x4234),
    L2(13, 0, 0, 0, 0, 0, 0, 0x4235),
    L2(13, 0, 0, 0, 0, 0, 0, 0x4236),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 eff35_char_table2_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_008[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x41F8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 eff35_char_table2_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_009[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x41F9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 eff35_char_table2_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_010[36] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x41FA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x41FB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x41FC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x41FD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x41FE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x41FF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4200),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4201),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 eff35_char_table2_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_011[36] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4202),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4203),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4204),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4205),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4206),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4207),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4208),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4209),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 eff35_char_table2_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_012[344] = {
    CMD(CM_FOR2, 0, 0, 4),
    CMD(CM_FOR, 0, 0, 3),
    L2(64, 0, 0, 0, 0, 0, 0, 0x4272),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4271),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4272),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4273),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4272),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4271),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4270),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4271),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4272),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4273),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4274),
    L2(32, 0, 0, 0, 0, 0, 0, 0x4275),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4276),
    CMD(CM_FOR, 0, 0, 9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4277),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4278),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4277),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4276),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4274),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4273),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4272),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4271),
    L2(64, 0, 0, 0, 0, 0, 0, 0x4272),
    CMD(CM_NEX2, 0, 0, 0),
    CMD(CM_FOR2, 0, 0, 2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4279),
    CMD(CM_FOR, 0, 0, 2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427B),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427A),
    L2(128, 0, 0, 0, 0, 0, 0, 0x4279),
    L2(32, 0, 0, 0, 0, 0, 0, 0x4278),
    L2(64, 0, 0, 0, 0, 0, 0, 0x4275),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4274),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4273),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4272),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4271),
    CMD(CM_FOR, 0, 0, 3),
    L2(64, 0, 0, 0, 0, 0, 0, 0x4272),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4271),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4272),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4273),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4272),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4271),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4270),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4271),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4272),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4273),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_FOR2, 0, 0, 2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4279),
    CMD(CM_FOR, 0, 0, 2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427B),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427A),
    L2(64, 0, 0, 0, 0, 0, 0, 0x4279),
    L2(32, 0, 0, 0, 0, 0, 0, 0x4278),
    L2(64, 0, 0, 0, 0, 0, 0, 0x4275),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4276),
    CMD(CM_FOR, 0, 0, 12),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4277),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4278),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4277),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4276),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4274),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4273),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4272),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4271),
    L2(128, 0, 0, 0, 0, 0, 0, 0x4272),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 eff35_char_table2_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_013[104] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4270),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4274),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x427F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4280),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4281),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4282),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4283),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4284),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4285),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4286),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4287),
    L2(32, 0, 0, 0, 0, 0, 0, 0x4288),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4289),
    L2(8, 0, 0, 0, 0, 0, 0, 0x428A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x428B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x428A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4289),
    L2(32, 0, 0, 0, 0, 0, 0, 0x4288),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4289),
    L2(8, 0, 0, 0, 0, 0, 0, 0x428A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x428B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4288),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4288),
    CMD(CM_END, 0, 0, 24),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 eff35_char_table2_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_014[164] = {
    L2(100, 0, 0, 0, 0, 0, 0, 0x4290),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4291),
    L2(100, 0, 0, 0, 0, 0, 0, 0x4290),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4291),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4292),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4293),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4294),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4295),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4296),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4297),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4298),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4299),
    L2(12, 0, 0, 0, 0, 0, 0, 0x429A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x429B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x429C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x429D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x429E),
    L2(32, 0, 0, 0, 0, 0, 0, 0x429F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x42A0),
    CMD(CM_FOR, 0, 0, 5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x429E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x429F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x42A0),
    CMD(CM_NEX, 0, 0, 0),
    L2(32, 0, 0, 0, 0, 0, 0, 0x429F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x429D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x429C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x429B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4299),
    L2(8, 0, 0, 0, 0, 0, 0, 0x429A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x429B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x42A1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x42A2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x42A3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x42A4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x42A5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x42A6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4292),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4291),
    L2(100, 0, 0, 0, 0, 0, 0, 0x4290),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 eff35_char_table2_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff35_char_table2_015[424] = {
    L2(32, 0, 0, 0, 0, 0, 0, 0x4320),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4321),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4322),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4323),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4324),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4325),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4326),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4327),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4328),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4329),
    L2(8, 0, 0, 0, 0, 0, 0, 0x432A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x432B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x432C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x432D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x432E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x432F),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4330),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4331),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4332),
    L2(99, 0, 0, 0, 0, 0, 0, 0x4320),
    CMD(CM_FOR, 0, 0, 2),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4340),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4341),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4342),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4343),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4344),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4345),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4346),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4347),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4348),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4349),
    L2(4, 0, 0, 0, 0, 0, 0, 0x434A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x434B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x434C),
    L2(5, 0, 0, 0, 0, 0, 0, 0x434D),
    L2(10, 0, 0, 0, 0, 0, 0, 0x434E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4345),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4344),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4343),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4342),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4341),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4320),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_FOR, 0, 0, 3),
    L2(64, 0, 0, 0, 0, 0, 0, 0x4350),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4351),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4352),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4353),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4354),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4355),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4356),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4357),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4358),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4359),
    L2(3, 0, 0, 0, 0, 0, 0, 0x435A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x435B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x435C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x435D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x435E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x435F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4360),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4361),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4362),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4363),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4364),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4365),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4366),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4367),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4368),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4369),
    L2(4, 0, 0, 0, 0, 0, 0, 0x436A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x436B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x436C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x436D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x436E),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4370),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4371),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4372),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4373),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4374),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4375),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4350),
    L2(200, 0, 0, 0, 0, 0, 0, 0x4350),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4340),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4341),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4342),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4343),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4344),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4345),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4346),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4347),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4348),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4349),
    L2(4, 0, 0, 0, 0, 0, 0, 0x434A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x434B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x434C),
    L2(5, 0, 0, 0, 0, 0, 0, 0x434D),
    L2(10, 0, 0, 0, 0, 0, 0, 0x434E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4345),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4344),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4343),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4342),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4341),
    L2(128, 0, 0, 0, 0, 0, 0, 0x4320),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 stg11_char_table_000[], stg11_char_table_001[], stg11_char_table_002[], stg11_char_table_003[],
                 stg11_char_table_004[], stg11_char_table_005[], stg11_char_table_006[], stg11_char_table_007[],
                 stg11_char_table_008[], stg11_char_table_009[], stg11_char_table_010[], stg11_char_table_011[],
                 stg11_char_table_012[], stg11_char_table_013[], stg11_char_table_014[], stg11_char_table_015[],
                 stg11_char_table_016[], stg11_char_table_017[], stg11_char_table_018[], stg11_char_table_020[],
                 stg11_char_table_022[], stg11_char_table_023[], stg11_char_table_024[], stg11_char_table_025[],
                 stg11_char_table_026[], stg11_char_table_028[], stg11_char_table_029[], stg11_char_table_030[],
                 stg11_char_table_031[], stg11_char_table_032[];

/* stg11_char_table: 33 entries; debug viewer: JAPAN 2 OBJ; used by dbg_work, eff05 */
const u32 stg11_char_table[34] = {
    (u32)stg11_char_table_000,  /* 0 */
    (u32)stg11_char_table_001,  /* 1 */
    (u32)stg11_char_table_002,  /* 2 */
    (u32)stg11_char_table_003,  /* 3 */
    (u32)stg11_char_table_004,  /* 4 */
    (u32)stg11_char_table_005,  /* 5 */
    (u32)stg11_char_table_006,  /* 6 */
    (u32)stg11_char_table_007,  /* 7 */
    (u32)stg11_char_table_008,  /* 8 */
    (u32)stg11_char_table_009,  /* 9 */
    (u32)stg11_char_table_010,  /* 10 */
    (u32)stg11_char_table_011,  /* 11 */
    (u32)stg11_char_table_012,  /* 12 */
    (u32)stg11_char_table_013,  /* 13 */
    (u32)stg11_char_table_014,  /* 14 */
    (u32)stg11_char_table_015,  /* 15 */
    (u32)stg11_char_table_016,  /* 16 */
    (u32)stg11_char_table_017,  /* 17 */
    (u32)stg11_char_table_018,  /* 18 */
    (u32)stg11_char_table_018,  /* 19 */
    (u32)stg11_char_table_020,  /* 20 */
    (u32)stg11_char_table_020,  /* 21 */
    (u32)stg11_char_table_022,  /* 22 */
    (u32)stg11_char_table_023,  /* 23 */
    (u32)stg11_char_table_024,  /* 24 */
    (u32)stg11_char_table_025,  /* 25 */
    (u32)stg11_char_table_026,  /* 26 */
    (u32)stg11_char_table_026,  /* 27 */
    (u32)stg11_char_table_028,  /* 28 */
    (u32)stg11_char_table_029,  /* 29 */
    (u32)stg11_char_table_030,  /* 30 */
    (u32)stg11_char_table_031,  /* 31 */
    (u32)stg11_char_table_032,  /* 32 */
    0
};

/* script: 0 */
const u16 stg11_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_000[40] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x43A0),
    L2(9, 0, 0, 0, 0, 0, 0, 0x43A1),
    L2(9, 0, 0, 0, 0, 0, 0, 0x43A2),
    L2(9, 0, 0, 0, 0, 0, 0, 0x43A3),
    L2(9, 0, 0, 0, 0, 0, 0, 0x43A4),
    L2(9, 0, 0, 0, 0, 0, 0, 0x43A5),
    L2(9, 0, 0, 0, 0, 0, 0, 0x43A6),
    L2(9, 0, 0, 0, 0, 0, 0, 0x43A7),
    L2(9, 0, 0, 0, 0, 0, 0, 0x43A8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 stg11_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_001[28] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x43A9),
    L2(9, 0, 0, 0, 0, 0, 0, 0x43AA),
    L2(9, 0, 0, 0, 0, 0, 0, 0x43AB),
    L2(9, 0, 0, 0, 0, 0, 0, 0x43AC),
    L2(9, 0, 0, 0, 0, 0, 0, 0x43AD),
    L2(9, 0, 0, 0, 0, 0, 0, 0x43AE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 stg11_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_002[40] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x43C5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43C6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43C7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43C8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43C9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43CA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43CB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43CC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43CD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 stg11_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_003[40] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x43CE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43CF),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43D0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43D1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43D2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43D3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43D4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43D5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43D6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 stg11_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_004[40] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x43E0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43E1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43E2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43E3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43E4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43E5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43E6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43E7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43E8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 stg11_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_005[40] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x43D7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43D8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43D9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43DA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43DB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43DC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43DD),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43DE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x43DF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 stg11_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_006[36] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x43B3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43B4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43B5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43B6),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43B7),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43B8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43B9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43BA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 stg11_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_007[36] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x43BB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43BC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43BD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43BE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43BF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43C0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43C1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x43C2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 stg11_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_008[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x43C3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 stg11_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_009[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x43C4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 stg11_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_010[204] = {
    L2(72, 0, 0, 0, 0, 0, 0, 0x4431),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4432),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4433),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4434),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4435),
    L2(38, 0, 0, 0, 0, 0, 0, 0x4436),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4435),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4436),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4435),
    L2(15, 0, 0, 0, 0, 0, 0, 0x4437),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4435),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4436),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4437),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4436),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4435),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4436),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4435),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4437),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4436),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4437),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4435),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4434),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4433),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4432),
    L2(71, 0, 0, 0, 0, 0, 0, 0x4431),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4438),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4439),
    L2(20, 0, 0, 0, 0, 0, 0, 0x443A),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4439),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4438),
    L2(23, 0, 0, 0, 0, 0, 0, 0x4431),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443B),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443C),
    CMD(CM_FOR, 0, 0, 2),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443D),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443E),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443F),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443E),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443D),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443E),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443F),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443E),
    CMD(CM_NEX, 0, 0, 0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443D),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443E),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443F),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443E),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443D),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443C),
    L2(7, 0, 0, 0, 0, 0, 0, 0x443B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 stg11_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_011[56] = {
    L2(7, 0, 0, 0, 0, 0, 0, 0x44CC),
    L2(7, 0, 0, 0, 0, 0, 0, 0x44CD),
    L2(7, 0, 0, 0, 0, 0, 0, 0x44CE),
    L2(7, 0, 0, 0, 0, 0, 0, 0x44CF),
    L2(7, 0, 0, 0, 0, 0, 0, 0x44D0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x44CF),
    L2(5, 0, 0, 0, 0, 0, 0, 0x44D0),
    L2(9, 0, 0, 0, 0, 0, 0, 0x44CF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x44D0),
    L2(9, 0, 0, 0, 0, 0, 0, 0x44CF),
    L2(7, 0, 0, 0, 0, 0, 0, 0x44D0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x44CF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x44D0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 stg11_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_012[52] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x44D1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x44D2),
    L2(14, 0, 0, 0, 0, 0, 0, 0x44D3),
    L2(7, 0, 0, 0, 0, 0, 0, 0x44D4),
    L2(7, 0, 0, 0, 0, 0, 0, 0x44D5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x44D6),
    L2(6, 0, 0, 0, 0, 0, 0, 0x44D7),
    L2(6, 0, 0, 0, 0, 0, 0, 0x44D8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x44D9),
    L2(5, 0, 0, 0, 0, 0, 0, 0x44DA),
    L2(5, 0, 0, 0, 0, 0, 0, 0x44DB),
    L2(5, 1, 0, 0, 0, 0, 0, 0x44DB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 stg11_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_013[48] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x4445),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4446),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4447),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4448),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4449),
    L2(9, 0, 0, 0, 0, 0, 0, 0x444A),
    L2(9, 0, 0, 0, 0, 0, 0, 0x444B),
    L2(9, 0, 0, 0, 0, 0, 0, 0x444C),
    L2(9, 0, 0, 0, 0, 0, 0, 0x444D),
    L2(9, 0, 0, 0, 0, 0, 0, 0x444E),
    L2(9, 0, 0, 0, 0, 0, 0, 0x444F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 stg11_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_014[48] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4450),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4451),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4452),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4453),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4451),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4452),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4453),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4451),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4452),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4453),
    L2(13, 0, 0, 0, 0, 0, 0, 0x4451),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 stg11_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_015[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x4454),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16 */
const u16 stg11_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_016[48] = {
    L2(36, 0, 0, 0, 0, 0, 0, 0x445E),
    L2(7, 0, 0, 0, 0, 0, 0, 0x445F),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4460),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4461),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4462),
    L2(21, 0, 0, 0, 0, 0, 0, 0x4463),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4464),
    L2(14, 0, 0, 0, 0, 0, 0, 0x4465),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4461),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4460),
    L2(200, 0, 0, 0, 0, 0, 0, 0x445F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 17 */
const u16 stg11_char_table_017_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_017[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x4466),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 18, 19 */
const u16 stg11_char_table_018_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_018[104] = {
    CMD(CM_FOR, 0, 0, 3),
    L2(35, 0, 0, 0, 0, 0, 0, 0x4467),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4468),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4469),
    L2(13, 0, 0, 0, 0, 0, 0, 0x446A),
    L2(25, 0, 0, 0, 0, 0, 0, 0x446B),
    L2(20, 0, 0, 0, 0, 0, 0, 0x446A),
    L2(18, 0, 0, 0, 0, 0, 0, 0x4469),
    L2(14, 0, 0, 0, 0, 0, 0, 0x4468),
    CMD(CM_NEX, 0, 0, 0),
    L2(14, 0, 0, 0, 0, 0, 0, 0x446C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x446D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x446E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x446F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x446E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x446D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x446E),
    L2(11, 0, 0, 0, 0, 0, 0, 0x446F),
    L2(11, 0, 0, 0, 0, 0, 0, 0x446E),
    L2(11, 0, 0, 0, 0, 0, 0, 0x446D),
    L2(11, 0, 0, 0, 0, 0, 0, 0x446E),
    L2(11, 0, 0, 0, 0, 0, 0, 0x446F),
    L2(11, 0, 0, 0, 0, 0, 0, 0x446E),
    L2(11, 0, 0, 0, 0, 0, 0, 0x446D),
    L2(11, 0, 0, 0, 0, 0, 0, 0x446C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 20, 21 */
const u16 stg11_char_table_020_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_020[92] = {
    CMD(CM_FOR, 0, 0, 2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4470),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4471),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4472),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4473),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4474),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4473),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4472),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4471),
    CMD(CM_NEX, 0, 0, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4470),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4471),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4472),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4473),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4474),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4475),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4472),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4471),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4470),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4476),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4477),
    L2(6, 1, 0, 0, 0, 0, 0, 0x4476),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 22 */
const u16 stg11_char_table_022_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_022[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x4478),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 23 */
const u16 stg11_char_table_023_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_023[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x4479),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 24 */
const u16 stg11_char_table_024_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_024[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x447A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 25 */
const u16 stg11_char_table_025_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_025[64] = {
    L2(53, 0, 0, 0, 0, 0, 0, 0x4455),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4456),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4457),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4458),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4457),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4456),
    L2(49, 0, 0, 0, 0, 0, 0, 0x4457),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4456),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4457),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4458),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4457),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4456),
    L2(10, 0, 0, 0, 0, 0, 0, 0x445B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x445A),
    L2(6, 1, 0, 0, 0, 0, 0, 0x445A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 26, 27 */
const u16 stg11_char_table_026_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_026[56] = {
    L2(49, 0, 0, 0, 0, 0, 0, 0x4459),
    L2(8, 0, 0, 0, 0, 0, 0, 0x445A),
    L2(28, 0, 0, 0, 0, 0, 0, 0x445B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x445A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4458),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4457),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4456),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4457),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4458),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4457),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4456),
    L2(8, 0, 0, 0, 0, 0, 0, 0x445D),
    L2(8, 1, 0, 0, 0, 0, 0, 0x445D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 28 */
const u16 stg11_char_table_028_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_028[892] = {
    L2(56, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4421),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4422),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(61, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(5, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(35, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4421),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4422),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(35, 0, 0, 0, 0, 0, 0, 0x4427),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4428),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4429),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(35, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(33, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(31, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4427),
    L2(68, 0, 0, 0, 0, 0, 0, 0x4428),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(56, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4421),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4422),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(61, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(5, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(35, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(33, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(31, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4427),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4428),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4429),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(56, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4421),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4422),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(61, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(5, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(35, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(33, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(31, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4427),
    L2(68, 0, 0, 0, 0, 0, 0, 0x4428),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(35, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4421),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4422),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(35, 0, 0, 0, 0, 0, 0, 0x4427),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4428),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4429),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(56, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4421),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4422),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(61, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(5, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(35, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(33, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(31, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4427),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4428),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4429),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(56, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4421),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4422),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(61, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(5, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(35, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(33, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(31, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4427),
    L2(68, 0, 0, 0, 0, 0, 0, 0x4428),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(35, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(33, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(31, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4427),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4428),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4429),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(126, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4421),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4422),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(35, 0, 0, 0, 0, 0, 0, 0x4427),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4428),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4429),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(1, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4429),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(1, 1, 0, 0, 0, 0, 0, 0x4430),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4429),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4430),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4430),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 29 */
const u16 stg11_char_table_029_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_029[68] = {
    L2(44, 0, 0, 0, 0, 0, 0, 0x4420),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4421),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4422),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4423),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4424),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4425),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4426),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4427),
    L2(35, 0, 0, 0, 0, 0, 0, 0x4428),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4429),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x442D),
    L2(5, 0, 0, 0, 0, 0, 0, 0x442E),
    L2(2, 1, 0, 0, 0, 0, 0, 0x442E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 30 */
const u16 stg11_char_table_030_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_030[8] = {
    L2(44, 0, 0, 0, 0, 0, 0, 0x43E9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 31 */
const u16 stg11_char_table_031_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_031[8] = {
    L2(44, 0, 0, 0, 0, 0, 0, 0x43EA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 32 */
const u16 stg11_char_table_032_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg11_char_table_032[8] = {
    L2(44, 0, 0, 0, 0, 0, 0, 0x43EB),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 stg03_char_table_000[], stg03_char_table_001[], stg03_char_table_002[], stg03_char_table_003[],
                 stg03_char_table_004[], stg03_char_table_005[], stg03_char_table_006[], stg03_char_table_007[],
                 stg03_char_table_008[], stg03_char_table_009[], stg03_char_table_010[], stg03_char_table_011[],
                 stg03_char_table_012[], stg03_char_table_013[], stg03_char_table_014[], stg03_char_table_015[],
                 stg03_char_table_016[], stg03_char_table_017[], stg03_char_table_018[], stg03_char_table_019[],
                 stg03_char_table_020[], stg03_char_table_021[], stg03_char_table_022[], stg03_char_table_023[],
                 stg03_char_table_024[], stg03_char_table_026[], stg03_char_table_027[], stg03_char_table_028[],
                 stg03_char_table_029[], stg03_char_table_030[], stg03_char_table_031[], stg03_char_table_033[],
                 stg03_char_table_034[], stg03_char_table_035[];

/* stg03_char_table: 36 entries (no closing 0: the next table follows); debug viewer: CHAINA 1 OBJ; used by EFF23, EFF24, dbg_work, eff05 */
const u32 stg03_char_table[36] = {
    (u32)stg03_char_table_000,  /* 0 */
    (u32)stg03_char_table_001,  /* 1 */
    (u32)stg03_char_table_002,  /* 2 */
    (u32)stg03_char_table_003,  /* 3 */
    (u32)stg03_char_table_004,  /* 4 */
    (u32)stg03_char_table_005,  /* 5 */
    (u32)stg03_char_table_006,  /* 6 */
    (u32)stg03_char_table_007,  /* 7 */
    (u32)stg03_char_table_008,  /* 8 */
    (u32)stg03_char_table_009,  /* 9 */
    (u32)stg03_char_table_010,  /* 10 */
    (u32)stg03_char_table_011,  /* 11 */
    (u32)stg03_char_table_012,  /* 12 */
    (u32)stg03_char_table_013,  /* 13 */
    (u32)stg03_char_table_014,  /* 14 */
    (u32)stg03_char_table_015,  /* 15 */
    (u32)stg03_char_table_016,  /* 16 */
    (u32)stg03_char_table_017,  /* 17 */
    (u32)stg03_char_table_018,  /* 18 */
    (u32)stg03_char_table_019,  /* 19 */
    (u32)stg03_char_table_020,  /* 20 */
    (u32)stg03_char_table_021,  /* 21 */
    (u32)stg03_char_table_022,  /* 22 */
    (u32)stg03_char_table_023,  /* 23 */
    (u32)stg03_char_table_024,  /* 24 */
    (u32)stg03_char_table_024,  /* 25 */
    (u32)stg03_char_table_026,  /* 26 */
    (u32)stg03_char_table_027,  /* 27 */
    (u32)stg03_char_table_028,  /* 28 */
    (u32)stg03_char_table_029,  /* 29 */
    (u32)stg03_char_table_030,  /* 30 */
    (u32)stg03_char_table_031,  /* 31 */
    (u32)stg03_char_table_015,  /* 32 */
    (u32)stg03_char_table_033,  /* 33 */
    (u32)stg03_char_table_034,  /* 34 */
    (u32)stg03_char_table_035,  /* 35 */
};

extern const u16 eff21_char_table_000[], eff21_char_table_001[], eff21_char_table_002[], eff21_char_table_003[],
                 eff21_char_table_004[], eff21_char_table_005[];

/* eff21_char_table: 6 entries (no closing 0: the next table follows); used by EFF21 */
const u32 eff21_char_table[6] = {
    (u32)eff21_char_table_000,  /* 0 */
    (u32)eff21_char_table_001,  /* 1 */
    (u32)eff21_char_table_002,  /* 2 */
    (u32)eff21_char_table_003,  /* 3 */
    (u32)eff21_char_table_004,  /* 4 */
    (u32)eff21_char_table_005,  /* 5 */
};

extern const u16 eff22_char_table_000[], eff22_char_table_001[], eff22_char_table_002[];

/* eff22_char_table: 3 entries; used by EFF22 */
const u32 eff22_char_table[4] = {
    (u32)eff22_char_table_000,  /* 0 */
    (u32)eff22_char_table_001,  /* 1 */
    (u32)eff22_char_table_002,  /* 2 */
    0
};

/* script: 0 */
const u16 stg03_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_000[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x4540),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 stg03_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_001[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4542),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 stg03_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_002[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x461F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 stg03_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_003[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x461E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 stg03_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_004[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4546),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 stg03_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_005[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4547),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 stg03_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_006[20] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4548),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4549),
    L2(6, 0, 0, 0, 0, 0, 0, 0x454A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x454B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 stg03_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_007[8] = {
    L2(26, 0, 0, 0, 0, 0, 0, 0x4575),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 stg03_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_008[48] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x454C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x454D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x454E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x454F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4550),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4551),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4552),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4553),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4554),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4555),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4555),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 stg03_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_009[20] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4557),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4558),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4559),
    L2(4, 1, 0, 0, 0, 0, 0, 0x455A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 stg03_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_010[60] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x455D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x455E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x455F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4560),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4561),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4562),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4563),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4564),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4565),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4566),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4567),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4568),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4569),
    L2(6, 1, 0, 0, 0, 0, 0, 0x4569),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 stg03_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_011[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x456A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x456B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x456C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x456D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x456E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x456F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4570),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4570),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 stg03_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_012[128] = {
    L2(8, 0, 113, 0, 0, 0, 0, 0x4611),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4612),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4613),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4614),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4615),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4616),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4617),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4618),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4619),
    L2(8, 0, 0, 0, 0, 0, 0, 0x461A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x461B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x461C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x461D),
    L2(8, 1, 0, 0, 0, 0, 0, 0x461D),
    CMD(CM_ROA, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4576),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4577),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4578),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4579),
    L2(8, 0, 0, 0, 0, 0, 0, 0x457A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x457B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x457C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x457D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x457E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x457F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4580),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4581),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4582),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4583),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4584),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4584),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 stg03_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_013[56] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4611),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4612),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4613),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4614),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4615),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4616),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4617),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4618),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4619),
    L2(8, 0, 0, 0, 0, 0, 0, 0x461A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x461B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x461C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x461D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 stg03_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_014[8] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x4610),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16 */
const u16 stg03_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_016[60] = {
    L2(84, 0, 0, 0, 0, 0, 0, 0x468C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x468D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x468E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x468F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4690),
    L2(6, 0, 0, 0, 0, 0, 0, 0x468F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x468E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x468D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x468E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x468F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4690),
    L2(6, 0, 0, 0, 0, 0, 0, 0x468F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x468E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x468D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 17 */
const u16 stg03_char_table_017_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_017[36] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4691),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4692),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4693),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4692),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4691),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4692),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4693),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4692),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 18 */
const u16 stg03_char_table_018_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_018[64] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x4694),
    L2(129, 0, 0, 0, 0, 0, 0, 0x4694),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4695),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4696),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4697),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4698),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4699),
    L2(7, 0, 0, 0, 0, 0, 0, 0x469A),
    L2(7, 0, 0, 0, 0, 0, 0, 0x469B),
    L2(7, 0, 0, 0, 0, 0, 0, 0x469A),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4699),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4698),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4697),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4696),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4695),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 19 */
const u16 stg03_char_table_019_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_019[40] = {
    L2(155, 0, 0, 0, 0, 0, 0, 0x469E),
    L2(11, 0, 0, 0, 0, 0, 0, 0x469D),
    L2(11, 0, 0, 0, 0, 0, 0, 0x469C),
    L2(11, 0, 0, 0, 0, 0, 0, 0x469D),
    L2(155, 1, 0, 0, 0, 0, 0, 0x469E),
    L2(11, 0, 0, 0, 0, 0, 0, 0x469F),
    L2(11, 0, 0, 0, 0, 0, 0, 0x46A0),
    L2(11, 0, 0, 0, 0, 0, 0, 0x469F),
    L2(11, 1, 0, 0, 0, 0, 0, 0x469F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 20 */
const u16 stg03_char_table_020_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_020[32] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x469E),
    L2(11, 0, 0, 0, 0, 0, 0, 0x46A1),
    L2(11, 0, 0, 0, 0, 0, 0, 0x46A2),
    L2(11, 0, 0, 0, 0, 0, 0, 0x46A3),
    L2(11, 0, 0, 0, 0, 0, 0, 0x46A4),
    L2(11, 0, 0, 0, 0, 0, 0, 0x46A5),
    L2(11, 1, 0, 0, 0, 0, 0, 0x46A5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 21 */
const u16 stg03_char_table_021_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_021[8] = {
    L2(6, 1, 0, 0, 0, 0, 0, 0x46A6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 22 */
const u16 stg03_char_table_022_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_022[112] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x46A7),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46A8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46A9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AF),
    CMD(CM_FOR, 0, 0, 2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46B0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AF),
    CMD(CM_NEX, 0, 0, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46AA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46A9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46A8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46A7),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46A7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 23 */
const u16 stg03_char_table_023_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_023[28] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x46B1),
    L2(9, 0, 0, 0, 0, 0, 0, 0x46B2),
    L2(9, 0, 0, 0, 0, 0, 0, 0x46B3),
    L2(9, 0, 0, 0, 0, 0, 0, 0x46B4),
    L2(9, 0, 0, 0, 0, 0, 0, 0x46B5),
    L2(9, 0, 0, 0, 0, 0, 0, 0x46B6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 24, 25 */
const u16 stg03_char_table_024_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_024[36] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x46B7),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46B8),
    L2(9, 0, 0, 0, 0, 0, 0, 0x46B9),
    L2(9, 0, 0, 0, 0, 0, 0, 0x46BA),
    L2(9, 0, 0, 0, 0, 0, 0, 0x46BB),
    L2(9, 0, 0, 0, 0, 0, 0, 0x46BC),
    L2(9, 0, 0, 0, 0, 0, 0, 0x46BD),
    CMD(CM_END, 0, 0, 4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 26 */
const u16 stg03_char_table_026_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_026[28] = {
    L2(32, 0, 0, 0, 0, 0, 0, 0x46BF),
    L2(11, 0, 0, 0, 0, 0, 0, 0x46C0),
    L2(11, 0, 0, 0, 0, 0, 0, 0x46C1),
    L2(11, 0, 0, 0, 0, 0, 0, 0x46C2),
    L2(11, 0, 0, 0, 0, 0, 0, 0x46C3),
    L2(11, 0, 0, 0, 0, 0, 0, 0x46C4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 27 */
const u16 stg03_char_table_027_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_027[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x46D6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 28 */
const u16 stg03_char_table_028_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_028[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x46D7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 29 */
const u16 stg03_char_table_029_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_029[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x46D8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 30 */
const u16 stg03_char_table_030_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_030[136] = {
    L2(6, 1, 0, 0, 0, 0, 0, 0x46C5),
    L2(4, 1, 0, 0, 0, 0, 0, 0x46C6),
    L2(4, 1, 0, 0, 0, 0, 0, 0x46C7),
    L2(4, 1, 0, 0, 0, 0, 0, 0x46C8),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46C9),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46C8),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46C7),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46C6),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46C5),
    L2(4, 1, 0, 0, 0, 0, 0, 0x46C6),
    L2(4, 1, 0, 0, 0, 0, 0, 0x46C7),
    L2(3, 1, 0, 0, 0, 0, 0, 0x46C8),
    L2(1, 1, 0, 0, 0, 0, 0, 0x46C8),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46C9),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46C8),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46C7),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46C6),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46C5),
    L2(4, 1, 0, 0, 0, 0, 0, 0x46C6),
    L2(4, 1, 0, 0, 0, 0, 0, 0x46CA),
    L2(4, 1, 0, 0, 0, 0, 0, 0x46CB),
    CMD(CM_FOR, 0, 0, 2),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46CC),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46CF),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46CD),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46CE),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46CD),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46CF),
    CMD(CM_NEX, 0, 0, 0),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46CC),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46CB),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46CA),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46C6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 31 */
const u16 stg03_char_table_031_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_031[56] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x46CA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46D0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46D1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46D2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46D3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x46D4),
    L2(12, 0, 0, 0, 0, 0, 0, 0x46D5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x46D4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46D3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46D2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46D1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x46CA),
    L2(6, 1, 0, 0, 0, 0, 0, 0x46CA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15, 32 */
const u16 stg03_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_015[148] = {
    L2(8, 1, 0, 0, 0, 0, 0, 0x4670),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4671),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4672),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4673),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4674),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4675),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4676),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4677),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4678),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4679),
    L2(8, 1, 0, 0, 0, 0, 0, 0x467A),
    L2(8, 1, 0, 0, 0, 0, 0, 0x467B),
    L2(8, 1, 0, 0, 0, 0, 0, 0x467C),
    L2(8, 1, 0, 0, 0, 0, 0, 0x467D),
    L2(8, 1, 0, 0, 0, 0, 0, 0x467E),
    L2(8, 1, 0, 0, 0, 0, 0, 0x467F),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4680),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4681),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4682),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4683),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4684),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4685),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4686),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4687),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4670),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4671),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4672),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4673),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4674),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4675),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4676),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4677),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4678),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4679),
    L2(8, 1, 0, 0, 0, 0, 0, 0x467A),
    L2(8, 1, 0, 0, 0, 0, 0, 0x467B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 33 */
const u16 stg03_char_table_033_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_033[56] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4685),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4686),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4687),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4688),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4689),
    L2(8, 0, 0, 0, 0, 0, 0, 0x468A),
    L2(12, 0, 0, 0, 0, 0, 0, 0x468B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x468A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4689),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4688),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4687),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4670),
    L2(6, 1, 0, 0, 0, 0, 0, 0x4670),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 34 */
const u16 stg03_char_table_034_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_034[8] = {
    L2(4, 1, 0, 0, 0, 0, 0, 0x4569),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 35 */
const u16 stg03_char_table_035_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg03_char_table_035[8] = {
    L2(4, 1, 0, 0, 0, 0, 0, 0x458F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff21_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff21_char_table_000[56] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x46DD),
    L2(3, 0, 0, 0, 0, 0, 0, 0x46DE),
    L2(5, 0, 0, 0, 0, 0, 0, 0x46DF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x46E0),
    L2(5, 0, 0, 0, 0, 0, 0, 0x46DE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x46E0),
    L2(11, 0, 0, 0, 0, 0, 0, 0x46DE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x46E1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x46E2),
    L2(5, 0, 0, 0, 0, 0, 0, 0x46E3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x46E4),
    L2(5, 0, 0, 0, 0, 0, 0, 0x46E5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x46E4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff21_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff21_char_table_001[12] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x46DA),
    L2(2, 0, 0, 0, 0, 0, 0, 0x46DB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff21_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff21_char_table_002[52] = {
    L2(32, 0, 0, 0, 0, 0, 0, 0x46EC),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46ED),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46EE),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46ED),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46EE),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46EC),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46EB),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46EA),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46EF),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46F0),
    L2(12, 0, 0, 0, 0, 0, 0, 0x46EF),
    L2(12, 0, 0, 0, 0, 0, 0, 0x46E9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff21_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff21_char_table_003[16] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x46E6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x46E7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x46E8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff21_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff21_char_table_004[64] = {
    L2(32, 0, 0, 0, 0, 0, 0, 0x46F1),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46F4),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46F3),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46F4),
    CMD(CM_FOR, 0, 0, 3),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46F2),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46F3),
    L2(14, 0, 0, 0, 0, 0, 0, 0x46F4),
    CMD(CM_NEX, 0, 0, 0),
    L2(12, 0, 0, 0, 0, 0, 0, 0x46F2),
    L2(12, 0, 0, 0, 0, 0, 0, 0x46F2),
    L2(12, 0, 0, 0, 0, 0, 0, 0x46F4),
    L2(12, 0, 0, 0, 0, 0, 0, 0x46F2),
    L2(12, 0, 0, 0, 0, 0, 0, 0x46F1),
    L2(12, 0, 0, 0, 0, 0, 0, 0x46F5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 eff21_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff21_char_table_005[16] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x470B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x470C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x470D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff22_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff22_char_table_000[20] = {
    L2(80, 0, 0, 0, 0, 0, 0, 0x46F7),
    L2(48, 0, 0, 0, 0, 0, 0, 0x46F6),
    L2(15, 0, 0, 0, 0, 0, 0, 0x46F7),
    L2(10, 0, 0, 0, 0, 0, 0, 0x46F6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff22_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff22_char_table_001[272] = {
    L2(2, 8, 0, 0, 0, 0, 0, 0x4707),
    L2(2, 8, 0, 0, 0, 0, 0, 0x4708),
    L2(2, 7, 0, 0, 0, 0, 0, 0x4707),
    L2(2, 7, 0, 0, 0, 0, 0, 0x4708),
    L2(2, 6, 0, 0, 0, 0, 0, 0x4707),
    L2(2, 6, 0, 0, 0, 0, 0, 0x4708),
    L2(2, 5, 0, 0, 0, 0, 0, 0x4707),
    L2(2, 5, 0, 0, 0, 0, 0, 0x4708),
    L2(2, 4, 0, 0, 0, 0, 0, 0x4709),
    L2(2, 4, 0, 0, 0, 0, 0, 0x470A),
    L2(2, 3, 0, 0, 0, 0, 0, 0x4709),
    L2(2, 3, 0, 0, 0, 0, 0, 0x470A),
    L2(2, 2, 0, 0, 0, 0, 0, 0x4709),
    L2(2, 2, 0, 0, 0, 0, 0, 0x470A),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4709),
    L2(2, 1, 0, 0, 0, 0, 0, 0x470A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x46DB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x46DC),
    L2(2, 31, 0, 0, 0, 0, 0, 0x46DB),
    L2(2, 31, 0, 0, 0, 0, 0, 0x46DC),
    L2(2, 30, 0, 0, 0, 0, 0, 0x46DB),
    L2(2, 30, 0, 0, 0, 0, 0, 0x46DC),
    L2(2, 29, 0, 0, 0, 0, 0, 0x46DB),
    L2(2, 29, 0, 0, 0, 0, 0, 0x46DC),
    L2(2, 28, 0, 0, 0, 0, 0, 0x46D9),
    L2(2, 28, 0, 0, 0, 0, 0, 0x46DA),
    L2(2, 27, 0, 0, 0, 0, 0, 0x46D9),
    L2(2, 27, 0, 0, 0, 0, 0, 0x46DA),
    L2(2, 26, 0, 0, 0, 0, 0, 0x46D9),
    L2(2, 26, 0, 0, 0, 0, 0, 0x46DA),
    L2(2, 25, 0, 0, 0, 0, 0, 0x46D9),
    L2(2, 25, 0, 0, 0, 0, 0, 0x46DA),
    L2(2, 24, 0, 0, 0, 0, 0, 0x46D9),
    L2(2, 24, 0, 0, 0, 0, 0, 0x46DA),
    L2(2, 23, 0, 0, 0, 0, 0, 0x46D9),
    L2(2, 23, 0, 0, 0, 0, 0, 0x46DA),
    L2(2, 22, 0, 0, 0, 0, 0, 0x46D9),
    L2(2, 22, 0, 0, 0, 0, 0, 0x46DA),
    L2(2, 21, 0, 0, 0, 0, 0, 0x46D9),
    L2(2, 21, 0, 0, 0, 0, 0, 0x46DA),
    L2(2, 20, 0, 0, 1, 0, 0, 0x46DB),
    L2(2, 20, 0, 0, 1, 0, 0, 0x46DC),
    L2(2, 19, 0, 0, 1, 0, 0, 0x46DB),
    L2(2, 19, 0, 0, 1, 0, 0, 0x46DC),
    L2(2, 18, 0, 0, 1, 0, 0, 0x46DB),
    L2(2, 18, 0, 0, 1, 0, 0, 0x46DC),
    L2(2, 17, 0, 0, 1, 0, 0, 0x46DB),
    L2(2, 17, 0, 0, 1, 0, 0, 0x46DC),
    L2(2, 16, 0, 0, 1, 0, 0, 0x4709),
    L2(2, 16, 0, 0, 1, 0, 0, 0x470A),
    L2(2, 15, 0, 0, 1, 0, 0, 0x4709),
    L2(2, 15, 0, 0, 1, 0, 0, 0x470A),
    L2(2, 14, 0, 0, 1, 0, 0, 0x4709),
    L2(2, 14, 0, 0, 1, 0, 0, 0x470A),
    L2(2, 13, 0, 0, 1, 0, 0, 0x4709),
    L2(2, 13, 0, 0, 1, 0, 0, 0x470A),
    L2(2, 12, 0, 0, 0, 0, 0, 0x4707),
    L2(2, 12, 0, 0, 0, 0, 0, 0x4708),
    L2(2, 11, 0, 0, 0, 0, 0, 0x4707),
    L2(2, 11, 0, 0, 0, 0, 0, 0x4708),
    L2(2, 10, 0, 0, 0, 0, 0, 0x4707),
    L2(2, 10, 0, 0, 0, 0, 0, 0x4708),
    L2(2, 9, 0, 0, 0, 0, 0, 0x4707),
    L2(2, 9, 0, 0, 0, 0, 0, 0x4708),
    L2(2, 8, 0, 0, 0, 0, 0, 0x4707),
    L2(2, 8, 0, 0, 0, 0, 0, 0x4708),
    L2(2, 99, 0, 0, 0, 0, 0, 0x4708),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff22_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff22_char_table_002[36] = {
    L2(80, 0, 0, 0, 0, 0, 0, 0x46F9),
    L2(48, 0, 0, 0, 0, 0, 0, 0x46F8),
    L2(15, 0, 0, 0, 0, 0, 0, 0x46F9),
    L2(10, 0, 0, 0, 0, 0, 0, 0x46F8),
    L2(40, 0, 0, 0, 0, 0, 0, 0x46F9),
    L2(24, 0, 0, 0, 0, 0, 0, 0x46F8),
    L2(7, 0, 0, 0, 0, 0, 0, 0x46F9),
    L2(5, 0, 0, 0, 0, 0, 0, 0x46F8),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 stg10_char_table_000[], stg10_char_table_001[], stg10_char_table_002[], stg10_char_table_003[],
                 stg10_char_table_004[], stg10_char_table_005[], stg10_char_table_006[], stg10_char_table_007[],
                 stg10_char_table_008[], stg10_char_table_009[], stg10_char_table_010[], stg10_char_table_011[],
                 stg10_char_table_012[], stg10_char_table_013[], stg10_char_table_014[], stg10_char_table_015[],
                 stg10_char_table_016[], stg10_char_table_017[], stg10_char_table_018[], stg10_char_table_019[],
                 stg10_char_table_020[], stg10_char_table_021[], stg10_char_table_022[], stg10_char_table_023[],
                 stg10_char_table_024[], stg10_char_table_025[], stg10_char_table_026[], stg10_char_table_027[],
                 stg10_char_table_028[], stg10_char_table_029[], stg10_char_table_030[], stg10_char_table_031[],
                 stg10_char_table_032[], stg10_char_table_033[], stg10_char_table_034[], stg10_char_table_035[],
                 stg10_char_table_036[], stg10_char_table_037[], stg10_char_table_038[], stg10_char_table_039[],
                 stg10_char_table_040[], stg10_char_table_041[], stg10_char_table_042[], stg10_char_table_043[],
                 stg10_char_table_044[], stg10_char_table_045[], stg10_char_table_046[], stg10_char_table_047[],
                 stg10_char_table_048[], stg10_char_table_049[], stg10_char_table_050[], stg10_char_table_051[],
                 stg10_char_table_052[], stg10_char_table_053[], stg10_char_table_054[], stg10_char_table_055[],
                 stg10_char_table_056[], stg10_char_table_057[], stg10_char_table_058[], stg10_char_table_059[],
                 stg10_char_table_060[], stg10_char_table_061[], stg10_char_table_062[], stg10_char_table_063[],
                 stg10_char_table_064[], stg10_char_table_065[], stg10_char_table_066[], stg10_char_table_067[],
                 stg10_char_table_068[], stg10_char_table_069[], stg10_char_table_070[], stg10_char_table_071[],
                 stg10_char_table_072[], stg10_char_table_073[], stg10_char_table_074[], stg10_char_table_075[];

/* stg10_char_table: 76 entries (no closing 0: the next table follows); debug viewer: CHAINA 2 OBJ; used by dbg_work, eff05 */
const u32 stg10_char_table[76] = {
    (u32)stg10_char_table_000,  /* 0 */
    (u32)stg10_char_table_001,  /* 1 */
    (u32)stg10_char_table_002,  /* 2 */
    (u32)stg10_char_table_003,  /* 3 */
    (u32)stg10_char_table_004,  /* 4 */
    (u32)stg10_char_table_005,  /* 5 */
    (u32)stg10_char_table_006,  /* 6 */
    (u32)stg10_char_table_007,  /* 7 */
    (u32)stg10_char_table_008,  /* 8 */
    (u32)stg10_char_table_009,  /* 9 */
    (u32)stg10_char_table_010,  /* 10 */
    (u32)stg10_char_table_011,  /* 11 */
    (u32)stg10_char_table_012,  /* 12 */
    (u32)stg10_char_table_013,  /* 13 */
    (u32)stg10_char_table_014,  /* 14 */
    (u32)stg10_char_table_015,  /* 15 */
    (u32)stg10_char_table_016,  /* 16 */
    (u32)stg10_char_table_017,  /* 17 */
    (u32)stg10_char_table_018,  /* 18 */
    (u32)stg10_char_table_019,  /* 19 */
    (u32)stg10_char_table_020,  /* 20 */
    (u32)stg10_char_table_021,  /* 21 */
    (u32)stg10_char_table_022,  /* 22 */
    (u32)stg10_char_table_023,  /* 23 */
    (u32)stg10_char_table_024,  /* 24 */
    (u32)stg10_char_table_025,  /* 25 */
    (u32)stg10_char_table_026,  /* 26 */
    (u32)stg10_char_table_027,  /* 27 */
    (u32)stg10_char_table_028,  /* 28 */
    (u32)stg10_char_table_029,  /* 29 */
    (u32)stg10_char_table_030,  /* 30 */
    (u32)stg10_char_table_031,  /* 31 */
    (u32)stg10_char_table_032,  /* 32 */
    (u32)stg10_char_table_033,  /* 33 */
    (u32)stg10_char_table_034,  /* 34 */
    (u32)stg10_char_table_035,  /* 35 */
    (u32)stg10_char_table_036,  /* 36 */
    (u32)stg10_char_table_037,  /* 37 */
    (u32)stg10_char_table_038,  /* 38 */
    (u32)stg10_char_table_039,  /* 39 */
    (u32)stg10_char_table_040,  /* 40 */
    (u32)stg10_char_table_041,  /* 41 */
    (u32)stg10_char_table_042,  /* 42 */
    (u32)stg10_char_table_043,  /* 43 */
    (u32)stg10_char_table_044,  /* 44 */
    (u32)stg10_char_table_045,  /* 45 */
    (u32)stg10_char_table_046,  /* 46 */
    (u32)stg10_char_table_047,  /* 47 */
    (u32)stg10_char_table_048,  /* 48 */
    (u32)stg10_char_table_049,  /* 49 */
    (u32)stg10_char_table_050,  /* 50 */
    (u32)stg10_char_table_051,  /* 51 */
    (u32)stg10_char_table_052,  /* 52 */
    (u32)stg10_char_table_053,  /* 53 */
    (u32)stg10_char_table_054,  /* 54 */
    (u32)stg10_char_table_055,  /* 55 */
    (u32)stg10_char_table_056,  /* 56 */
    (u32)stg10_char_table_057,  /* 57 */
    (u32)stg10_char_table_058,  /* 58 */
    (u32)stg10_char_table_059,  /* 59 */
    (u32)stg10_char_table_060,  /* 60 */
    (u32)stg10_char_table_061,  /* 61 */
    (u32)stg10_char_table_062,  /* 62 */
    (u32)stg10_char_table_063,  /* 63 */
    (u32)stg10_char_table_064,  /* 64 */
    (u32)stg10_char_table_065,  /* 65 */
    (u32)stg10_char_table_066,  /* 66 */
    (u32)stg10_char_table_067,  /* 67 */
    (u32)stg10_char_table_068,  /* 68 */
    (u32)stg10_char_table_069,  /* 69 */
    (u32)stg10_char_table_070,  /* 70 */
    (u32)stg10_char_table_071,  /* 71 */
    (u32)stg10_char_table_072,  /* 72 */
    (u32)stg10_char_table_073,  /* 73 */
    (u32)stg10_char_table_074,  /* 74 */
    (u32)stg10_char_table_075,  /* 75 */
};

extern const u16 eff28_char_table_000[], eff28_char_table_001[], eff28_char_table_002[], eff28_char_table_003[],
                 eff28_char_table_004[], eff28_char_table_005[];

/* eff28_char_table: 6 entries (no closing 0: the next table follows); used by eff28 */
const u32 eff28_char_table[6] = {
    (u32)eff28_char_table_000,  /* 0 */
    (u32)eff28_char_table_001,  /* 1 */
    (u32)eff28_char_table_002,  /* 2 */
    (u32)eff28_char_table_003,  /* 3 */
    (u32)eff28_char_table_004,  /* 4 */
    (u32)eff28_char_table_005,  /* 5 */
};

extern const u16 eff29_type0_char_table_000[], eff29_type0_char_table_001[], eff29_type0_char_table_002[],
                 eff29_type0_char_table_003[];

/* eff29_type0_char_table: 4 entries (no closing 0: the next table follows); used by EFF29 */
const u32 eff29_type0_char_table[4] = {
    (u32)eff29_type0_char_table_000,  /* 0 */
    (u32)eff29_type0_char_table_001,  /* 1 */
    (u32)eff29_type0_char_table_002,  /* 2 */
    (u32)eff29_type0_char_table_003,  /* 3 */
};

extern const u16 eff29_type1_char_table_000[], eff29_type1_char_table_001[], eff29_type1_char_table_002[],
                 eff29_type1_char_table_003[], eff29_type1_char_table_004[], eff29_type1_char_table_005[],
                 eff29_type1_char_table_006[];

/* eff29_type1_char_table: 7 entries; used by EFF29 */
const u32 eff29_type1_char_table[8] = {
    (u32)eff29_type1_char_table_000,  /* 0 */
    (u32)eff29_type1_char_table_001,  /* 1 */
    (u32)eff29_type1_char_table_002,  /* 2 */
    (u32)eff29_type1_char_table_003,  /* 3 */
    (u32)eff29_type1_char_table_004,  /* 4 */
    (u32)eff29_type1_char_table_005,  /* 5 */
    (u32)eff29_type1_char_table_006,  /* 6 */
    0
};

/* script: 0 */
const u16 stg10_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_000[8] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x47C0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 stg10_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_001[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x47C2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 stg10_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_002[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x47C5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 stg10_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_003[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x47C6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 stg10_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_004[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x47C8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 stg10_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_005[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x47C9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 stg10_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_006[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x47CA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 stg10_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_007[8] = {
    L2(26, 0, 0, 0, 0, 0, 0, 0x47CB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 stg10_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_008[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x47CC),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 stg10_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_009[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x47CD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 stg10_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_010[12] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x47D0),
    L2(8, 1, 0, 0, 0, 0, 0, 0x47D0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 stg10_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_011[68] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x47E1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x47E2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x47E3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x47E4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x47E5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x47E6),
    L2(3, 2, 0, 0, 0, 0, 0, 0x47E7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x47E8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x47E9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x47EA),
    L2(3, 0, 0, 0, 0, 0, 0, 0x47EB),
    L2(3, 2, 0, 0, 0, 0, 0, 0x47EC),
    L2(3, 0, 0, 0, 0, 0, 0, 0x47ED),
    L2(3, 0, 0, 0, 0, 0, 0, 0x47EE),
    L2(3, 0, 0, 0, 0, 0, 0, 0x47EF),
    L2(3, 1, 0, 0, 0, 0, 0, 0x47EF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 stg10_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_012[40] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x47F1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x47F2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x47F3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x47F4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x47F5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x47F6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x47F7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x47F8),
    L2(4, 1, 0, 0, 0, 0, 0, 0x47F8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 stg10_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_013[16] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x489C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x489D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x489E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 stg10_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_014[32] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4801),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4802),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4803),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4804),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4805),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4806),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4806),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 stg10_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_015[52] = {
    CMD(CM_FOR, 0, 0, 2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4810),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4811),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4812),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4813),
    CMD(CM_NEX, 0, 0, 0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4814),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4815),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4816),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4817),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4818),
    CMD(CM_END, 0, 0, 9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16 */
const u16 stg10_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_016[20] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4820),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4821),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4822),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4823),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 17 */
const u16 stg10_char_table_017_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_017[60] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x4831),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4832),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4833),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4834),
    L2(3, 2, 0, 0, 0, 0, 0, 0x4835),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4836),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4837),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4838),
    L2(3, 2, 0, 0, 0, 0, 0, 0x4839),
    L2(3, 0, 0, 0, 0, 0, 0, 0x483A),
    L2(5, 0, 0, 0, 0, 0, 0, 0x483C),
    L2(5, 0, 0, 0, 0, 0, 0, 0x483B),
    L2(5, 0, 0, 0, 0, 0, 0, 0x483A),
    L2(5, 1, 0, 0, 0, 0, 0, 0x483A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 18 */
const u16 stg10_char_table_018_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_018[20] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4907),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4908),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4909),
    L2(6, 0, 0, 0, 0, 0, 0, 0x490A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 19 */
const u16 stg10_char_table_019_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_019[20] = {
    L2(7, 0, 0, 0, 0, 0, 0, 0x4845),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4846),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4847),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4848),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 20 */
const u16 stg10_char_table_020_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_020[28] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4851),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4852),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4853),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4854),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4855),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4856),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 21 */
const u16 stg10_char_table_021_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_021[60] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4861),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4862),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4863),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4864),
    L2(4, 2, 0, 0, 0, 0, 0, 0x4865),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4866),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4867),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4868),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4869),
    L2(4, 2, 0, 0, 0, 0, 0, 0x486A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x486B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x486C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x486D),
    L2(4, 1, 0, 0, 0, 0, 0, 0x486D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 22 */
const u16 stg10_char_table_022_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_022[56] = {
    L2(4, 0, 112, 0, 0, 0, 0, 0x4871),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4872),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4873),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4874),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4875),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4876),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4877),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4878),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4879),
    L2(3, 0, 0, 0, 0, 0, 0, 0x487A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x487B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x487C),
    L2(4, 1, 0, 0, 0, 0, 0, 0x487C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 23 */
const u16 stg10_char_table_023_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_023[48] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4891),
    L2(2, 2, 0, 0, 0, 0, 0, 0x4891),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4892),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4893),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4894),
    L2(2, 2, 0, 0, 0, 0, 0, 0x4891),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4891),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4892),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4893),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4894),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4894),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 24 */
const u16 stg10_char_table_024_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_024[16] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4899),
    L2(4, 0, 0, 0, 0, 0, 0, 0x489A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x489B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 25 */
const u16 stg10_char_table_025_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_025[20] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x48B0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48B1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48B2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48B3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 26 */
const u16 stg10_char_table_026_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_026[20] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x48B4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48B5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48B6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48B7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 27 */
const u16 stg10_char_table_027_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_027[20] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x48B8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48B9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48BA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48BB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 28 */
const u16 stg10_char_table_028_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_028[16] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x48BC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48BD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48BE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 29 */
const u16 stg10_char_table_029_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_029[28] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x48CB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48CC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48CD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48CE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48CF),
    L2(8, 1, 0, 0, 0, 0, 0, 0x48CF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 30 */
const u16 stg10_char_table_030_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_030[24] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x48D0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x48D1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x48D2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x48D3),
    L2(8, 1, 0, 0, 0, 0, 0, 0x48D3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 31 */
const u16 stg10_char_table_031_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_031[20] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x48D4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48D5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48D6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48D7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 32 */
const u16 stg10_char_table_032_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_032[64] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x47D0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48DE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48DF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E7),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48EA),
    L2(8, 1, 0, 0, 0, 0, 0, 0x48EA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 33 */
const u16 stg10_char_table_033_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_033[24] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x48ED),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48EE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48EF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48F0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48F1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 34 */
const u16 stg10_char_table_034_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_034[20] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4895),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4896),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4897),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4898),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 35 */
const u16 stg10_char_table_035_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_035[20] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E7),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 36 */
const u16 stg10_char_table_036_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_036[40] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x48E9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48EA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48EB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48EC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48ED),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48EE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48EF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48F0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48F1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 37 */
const u16 stg10_char_table_037_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_037[40] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x48F2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48F3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48F4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48F5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48F6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48F7),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48F8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48F9),
    L2(8, 1, 0, 0, 0, 0, 0, 0x48F9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 38 */
const u16 stg10_char_table_038_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_038[16] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x48FA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48FB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x48FC),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 39 */
const u16 stg10_char_table_039_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_039[40] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4960),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4961),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4962),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4963),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4964),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4965),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4966),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4967),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4967),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 40 */
const u16 stg10_char_table_040_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_040[52] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4970),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4971),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4972),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4973),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4974),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4975),
    L2(2, 2, 0, 0, 0, 0, 0, 0x4976),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4977),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4978),
    L2(2, 2, 0, 0, 0, 0, 0, 0x4979),
    L2(2, 0, 0, 0, 0, 0, 0, 0x497A),
    L2(4, 1, 0, 0, 0, 0, 0, 0x497A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 41 */
const u16 stg10_char_table_041_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_041[56] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4980),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4981),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4982),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4983),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4984),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4985),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4986),
    L2(2, 2, 0, 0, 0, 0, 0, 0x4987),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4988),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4989),
    L2(2, 0, 0, 0, 0, 0, 0, 0x498A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x498B),
    L2(4, 1, 0, 0, 0, 0, 0, 0x498B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 42 */
const u16 stg10_char_table_042_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_042[56] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4990),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4991),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4992),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4993),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4994),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4995),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4996),
    L2(2, 2, 0, 0, 0, 0, 0, 0x4997),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4998),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4999),
    L2(2, 2, 0, 0, 0, 0, 0, 0x499A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x499B),
    L2(2, 1, 0, 0, 0, 0, 0, 0x499B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 43 */
const u16 stg10_char_table_043_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_043[56] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x49A0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49A1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49A2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49A3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49A4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49A5),
    L2(2, 2, 0, 0, 0, 0, 0, 0x49A6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49A7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49A8),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49A9),
    L2(2, 2, 0, 0, 0, 0, 0, 0x49AA),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49AB),
    L2(2, 1, 0, 0, 0, 0, 0, 0x49AB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 44 */
const u16 stg10_char_table_044_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_044[52] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x49B0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49B1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49B2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49B3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49B4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49B5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49B6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49B7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49B8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49B9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49BA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49BB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 45 */
const u16 stg10_char_table_045_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_045[52] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x49C0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49C1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49C2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49C3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49C4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49C5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49C6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49C7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49C8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49C9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49CA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x49CB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 46 */
const u16 stg10_char_table_046_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_046[60] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x49E0),
    L2(1, 0, 0, 0, 0, 0, 0, 0x49E1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49E2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49E3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49E4),
    L2(1, 0, 0, 0, 0, 0, 0, 0x49E5),
    L2(1, 0, 0, 0, 0, 0, 0, 0x49E6),
    L2(2, 2, 0, 0, 0, 0, 0, 0x49E7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49E4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49E5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49E6),
    L2(2, 2, 0, 0, 0, 0, 0, 0x49E7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49E8),
    L2(2, 1, 0, 0, 0, 0, 0, 0x49E8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 47 */
const u16 stg10_char_table_047_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_047[60] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x49F0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49F1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49F2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49F3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49F4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49F5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49F6),
    L2(2, 2, 0, 0, 0, 0, 0, 0x49F7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49F6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49F5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49F4),
    L2(2, 2, 0, 0, 0, 0, 0, 0x49F3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x49F2),
    L2(2, 1, 0, 0, 0, 0, 0, 0x49F2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 48 */
const u16 stg10_char_table_048_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_048[56] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A00),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A01),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A02),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A03),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A04),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A05),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A06),
    L2(4, 2, 0, 0, 0, 0, 0, 0x4A07),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A08),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A09),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A0A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A0B),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4A0B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 49 */
const u16 stg10_char_table_049_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_049[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A10),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A11),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A12),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A13),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A14),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A15),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A16),
    L2(200, 0, 0, 0, 0, 0, 0, 0x4A17),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 50 */
const u16 stg10_char_table_050_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_050[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A20),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A21),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A22),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A23),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A24),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A25),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A26),
    L2(200, 0, 0, 0, 0, 0, 0, 0x4A27),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 51 */
const u16 stg10_char_table_051_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_051[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A30),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A31),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A32),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A33),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A34),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A35),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A36),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A37),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 52 */
const u16 stg10_char_table_052_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_052[40] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A40),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A42),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A43),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A45),
    L2(2, 2, 0, 0, 0, 0, 0, 0x4A47),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A4A),
    L2(2, 2, 0, 0, 0, 0, 0, 0x4A4B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A4A),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4A4A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 53 */
const u16 stg10_char_table_053_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_053[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A50),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A51),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A52),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A53),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A54),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A55),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A56),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A57),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 54 */
const u16 stg10_char_table_054_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_054[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A60),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A61),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A62),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A63),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A64),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A65),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A66),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A67),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 55 */
const u16 stg10_char_table_055_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_055[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A70),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A71),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A72),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A73),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A74),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A75),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4A76),
    L2(200, 0, 0, 0, 0, 0, 0, 0x4A77),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 56 */
const u16 stg10_char_table_056_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_056[64] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A80),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A81),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A82),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A83),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A84),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A85),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A86),
    L2(2, 2, 0, 0, 0, 0, 0, 0x4A87),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A88),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A89),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A8A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A8B),
    L2(2, 2, 0, 0, 0, 0, 0, 0x4A8C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A8D),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4A8D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 57 */
const u16 stg10_char_table_057_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_057[28] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A97),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A95),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A96),
    L2(2, 2, 0, 0, 0, 0, 0, 0x4A97),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4A98),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4A98),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 58 */
const u16 stg10_char_table_058_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_058[28] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4AA0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4AA1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4AA2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4AA3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4AA4),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4AA4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 59 */
const u16 stg10_char_table_059_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_059[40] = {
    L2(4, 0, 111, 0, 0, 0, 0, 0x4AB0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AB1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AB2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AB3),
    L2(4, 2, 0, 0, 0, 0, 0, 0x4AB4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AB5),
    L2(4, 2, 0, 0, 0, 0, 0, 0x4AB6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AB7),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4AB7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 60 */
const u16 stg10_char_table_060_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_060[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ABC),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 61 */
const u16 stg10_char_table_061_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_061[20] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ABE),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ABF),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4AC0),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4AC1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 62 */
const u16 stg10_char_table_062_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_062[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4900),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 63 */
const u16 stg10_char_table_063_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_063[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4901),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 64 */
const u16 stg10_char_table_064_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_064[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4904),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 65 */
const u16 stg10_char_table_065_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_065[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4903),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 66 */
const u16 stg10_char_table_066_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_066[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4902),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 67 */
const u16 stg10_char_table_067_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_067[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x47C7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 68 */
const u16 stg10_char_table_068_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_068[36] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x4B00),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4B01),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4B02),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4B03),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4B04),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4B05),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4B06),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4B07),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 69 */
const u16 stg10_char_table_069_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_069[16] = {
    L2(70, 0, 111, 0, 0, 0, 0, 0x4906),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4906),
    CMD(CM_END, 0, 0, 2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 70 */
const u16 stg10_char_table_070_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_070[12] = {
    L2(50, 0, 0, 0, 0, 0, 0, 0x4905),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4905),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 71 */
const u16 stg10_char_table_071_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_071[20] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x48A0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x48A1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x48A2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x48A3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 72 */
const u16 stg10_char_table_072_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_072[16] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4902),
    L2(200, 0, 0, 0, 0, 0, 0, 0x4902),
    CMD(CM_END, 0, 0, 2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 73 */
const u16 stg10_char_table_073_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_073[8] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x4904),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 74 */
const u16 stg10_char_table_074_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_074[8] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x487C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 75 */
const u16 stg10_char_table_075_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg10_char_table_075[8] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x48EA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff28_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff28_char_table_000[84] = {
    L2(128, 0, 0, 0, 0, 0, 0, 0x4AD0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD6),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4AD6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff28_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff28_char_table_001[36] = {
    L2(32, 0, 0, 0, 0, 0, 0, 0x4AD7),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADA),
    L2(32, 0, 0, 0, 0, 0, 0, 0x4ADB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff28_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff28_char_table_002[96] = {
    L2(32, 0, 0, 0, 0, 0, 0, 0x4AD7),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADA),
    CMD(CM_FOR, 0, 0, 2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADC),
    CMD(CM_NEX, 0, 0, 0),
    L2(32, 0, 0, 0, 0, 0, 0, 0x4ADB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADC),
    L2(32, 0, 0, 0, 0, 0, 0, 0x4ADB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ADA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD8),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4AD8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff28_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff28_char_table_003[44] = {
    CMD(CM_FOR, 0, 0, 3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD4),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD3),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4AD3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff28_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff28_char_table_004[180] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AD7),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AD6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AD5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4ADF),
    L2(68, 0, 0, 0, 0, 0, 0, 0x4AE0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AE1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AE2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AE3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AE4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AE5),
    CMD(CM_FOR, 0, 0, 2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4AE6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4AE7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AE8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AE9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AE8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AE7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4AE6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4AE5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4AE4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4AE5),
    CMD(CM_NEX, 0, 0, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AE6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AE7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4AE8),
    L2(33, 0, 0, 0, 0, 0, 0, 0x4AE9),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4AEA),
    L2(32, 0, 0, 0, 0, 0, 0, 0x4AEB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4AEC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4AED),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4AEE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4AEF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4AF0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AF1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AF2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AF3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AF4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AF5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AF6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AF5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AF4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AF5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4AF6),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4AF5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 eff28_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff28_char_table_005[100] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF4),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF5),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF6),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF7),
    L2(32, 0, 0, 0, 0, 0, 0, 0x4AF8),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF7),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF6),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF5),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF4),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF5),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF6),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF5),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF4),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF5),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF6),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF5),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF4),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF5),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF6),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF7),
    L2(42, 0, 0, 0, 0, 0, 0, 0x4AF8),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF7),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF6),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4AF5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff29_type0_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff29_type0_char_table_000[52] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B5E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B5F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B60),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B61),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B62),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B63),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B64),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B65),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B66),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B67),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B68),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4B68),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff29_type0_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff29_type0_char_table_001[44] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B1C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B1D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B1E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B1F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B20),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B21),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B22),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B23),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B24),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4B24),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff29_type0_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff29_type0_char_table_002[56] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B11),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B12),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B13),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B14),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B15),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B16),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B11),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B17),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B18),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B19),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B1A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B1B),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4B1B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff29_type0_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff29_type0_char_table_003[44] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B55),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B56),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B57),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B58),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B59),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B5A),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B5B),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B5C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B5D),
    L2(10, 1, 0, 0, 0, 0, 0, 0x4B5D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff29_type1_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff29_type1_char_table_000[108] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B3A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B3B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B3C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B3D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B3E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B3F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B40),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B69),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B6A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B6B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B6C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B6D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B6E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B6F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B3A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B3B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B3C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B3D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B3E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B3F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B40),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B69),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B6A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B6B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B6C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B6D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff29_type1_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff29_type1_char_table_001[44] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B41),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B42),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B43),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B44),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B45),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B46),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B47),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B48),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B49),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4B49),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff29_type1_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff29_type1_char_table_002[36] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B4A),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B4B),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B4C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B4D),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B4E),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B4F),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B50),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B51),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff29_type1_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff29_type1_char_table_003[16] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B52),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B53),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4B53),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff29_type1_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff29_type1_char_table_004[52] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B25),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B26),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B27),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B28),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B29),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B2A),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B25),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B2B),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B2C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B2D),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B2E),
    L2(10, 1, 0, 0, 0, 0, 0, 0x4B2F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 eff29_type1_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff29_type1_char_table_005[16] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B30),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4B31),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4B31),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 eff29_type1_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff29_type1_char_table_006[36] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B32),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B33),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B34),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B35),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B36),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B37),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B38),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4B39),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 stg04_char_table_000[], stg04_char_table_001[], stg04_char_table_002[], stg04_char_table_003[],
                 stg04_char_table_004[], stg04_char_table_005[], stg04_char_table_006[], stg04_char_table_007[],
                 stg04_char_table_008[], stg04_char_table_009[], stg04_char_table_010[], stg04_char_table_011[],
                 stg04_char_table_012[], stg04_char_table_013[], stg04_char_table_014[], stg04_char_table_015[],
                 stg04_char_table_016[], stg04_char_table_017[], stg04_char_table_018[], stg04_char_table_019[],
                 stg04_char_table_020[], stg04_char_table_021[], stg04_char_table_022[], stg04_char_table_023[],
                 stg04_char_table_024[], stg04_char_table_025[], stg04_char_table_026[], stg04_char_table_027[],
                 stg04_char_table_028[], stg04_char_table_029[], stg04_char_table_030[], stg04_char_table_031[],
                 stg04_char_table_032[], stg04_char_table_033[], stg04_char_table_034[], stg04_char_table_035[],
                 stg04_char_table_036[], stg04_char_table_037[];

/* stg04_char_table: 38 entries; debug viewer: ENFLAND OBJ; used by dbg_work, eff05, eff65 */
const u32 stg04_char_table[39] = {
    (u32)stg04_char_table_000,  /* 0 */
    (u32)stg04_char_table_001,  /* 1 */
    (u32)stg04_char_table_002,  /* 2 */
    (u32)stg04_char_table_003,  /* 3 */
    (u32)stg04_char_table_004,  /* 4 */
    (u32)stg04_char_table_005,  /* 5 */
    (u32)stg04_char_table_006,  /* 6 */
    (u32)stg04_char_table_007,  /* 7 */
    (u32)stg04_char_table_008,  /* 8 */
    (u32)stg04_char_table_009,  /* 9 */
    (u32)stg04_char_table_010,  /* 10 */
    (u32)stg04_char_table_011,  /* 11 */
    (u32)stg04_char_table_012,  /* 12 */
    (u32)stg04_char_table_013,  /* 13 */
    (u32)stg04_char_table_014,  /* 14 */
    (u32)stg04_char_table_015,  /* 15 */
    (u32)stg04_char_table_016,  /* 16 */
    (u32)stg04_char_table_017,  /* 17 */
    (u32)stg04_char_table_018,  /* 18 */
    (u32)stg04_char_table_019,  /* 19 */
    (u32)stg04_char_table_020,  /* 20 */
    (u32)stg04_char_table_021,  /* 21 */
    (u32)stg04_char_table_022,  /* 22 */
    (u32)stg04_char_table_023,  /* 23 */
    (u32)stg04_char_table_024,  /* 24 */
    (u32)stg04_char_table_025,  /* 25 */
    (u32)stg04_char_table_026,  /* 26 */
    (u32)stg04_char_table_027,  /* 27 */
    (u32)stg04_char_table_028,  /* 28 */
    (u32)stg04_char_table_029,  /* 29 */
    (u32)stg04_char_table_030,  /* 30 */
    (u32)stg04_char_table_031,  /* 31 */
    (u32)stg04_char_table_032,  /* 32 */
    (u32)stg04_char_table_033,  /* 33 */
    (u32)stg04_char_table_034,  /* 34 */
    (u32)stg04_char_table_035,  /* 35 */
    (u32)stg04_char_table_036,  /* 36 */
    (u32)stg04_char_table_037,  /* 37 */
    0
};

/* script: 0 */
const u16 stg04_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_000[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x52EB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 stg04_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_001[32] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x52DB),
    L2(200, 0, 0, 0, 0, 0, 0, 0x52DB),
    L2(80, 0, 0, 0, 0, 0, 0, 0x52DB),
    L2(120, 0, 0, 0, 0, 0, 0, 0x52DC),
    L2(200, 0, 0, 0, 0, 0, 0, 0x52DD),
    L2(200, 0, 0, 0, 0, 0, 0, 0x52DD),
    L2(80, 0, 0, 0, 0, 0, 0, 0x52DD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 stg04_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_002[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5310),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 stg04_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_003[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5311),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 stg04_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_004[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x52EA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 stg04_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_005[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x52E9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 stg04_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_006[8] = {
    L2(26, 0, 0, 0, 0, 0, 0, 0x52E8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 stg04_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_007[8] = {
    L2(26, 0, 0, 0, 0, 0, 0, 0x5314),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 stg04_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_008[8] = {
    L2(26, 0, 0, 0, 0, 0, 0, 0x5312),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 stg04_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_009[8] = {
    L2(26, 0, 0, 0, 0, 0, 0, 0x5313),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 stg04_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_010[36] = {
    L2(8, 1, 0, 0, 0, 0, 0, 0x5320),
    L2(8, 2, 0, 0, 0, 0, 0, 0x5321),
    L2(8, 1, 0, 0, 0, 0, 0, 0x5322),
    L2(8, 2, 0, 0, 0, 0, 0, 0x5323),
    L2(8, 1, 0, 0, 0, 0, 0, 0x5324),
    L2(8, 2, 0, 0, 0, 0, 0, 0x5325),
    L2(8, 1, 0, 0, 0, 0, 0, 0x5326),
    L2(8, 2, 0, 0, 0, 0, 0, 0x5327),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 stg04_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_011[56] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x5328),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5329),
    L2(8, 0, 0, 0, 0, 0, 0, 0x532A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x532B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x532C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x532D),
    L2(64, 0, 0, 0, 0, 0, 0, 0x532E),
    L2(10, 0, 0, 0, 0, 0, 0, 0x532D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x532C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x532B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x532A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5329),
    L2(200, 0, 0, 0, 0, 0, 0, 0x5328),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 stg04_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_012[8] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x532F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 stg04_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_013[8] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x5330),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 stg04_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_014[8] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x5331),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 stg04_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_015[56] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x5332),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5333),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5334),
    L2(5, 0, 0, 0, 0, 0, 0, 0x5335),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5336),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5337),
    L2(28, 0, 0, 0, 0, 0, 0, 0x5338),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5337),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5336),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5335),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5334),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5333),
    L2(200, 0, 0, 0, 0, 0, 0, 0x5332),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16 */
const u16 stg04_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_016[52] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x5332),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5339),
    L2(10, 0, 0, 0, 0, 0, 0, 0x533A),
    L2(10, 0, 0, 0, 0, 0, 0, 0x533B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x533C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x533D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x533C),
    L2(7, 0, 0, 0, 0, 0, 0, 0x533B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x533A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5339),
    L2(20, 0, 0, 0, 0, 0, 0, 0x5332),
    L2(8, 1, 0, 0, 0, 0, 0, 0x5332),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 17 */
const u16 stg04_char_table_017_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_017[164] = {
    L2(10, 2, 0, 0, 0, 0, 0, 0x537D),
    L2(18, 2, 0, 0, 0, 0, 0, 0x5371),
    L2(10, 2, 0, 0, 0, 0, 0, 0x537D),
    L2(18, 2, 0, 0, 0, 0, 0, 0x5371),
    L2(10, 2, 0, 0, 0, 0, 0, 0x537D),
    L2(18, 2, 0, 0, 0, 0, 0, 0x5371),
    L2(10, 2, 0, 0, 0, 0, 0, 0x537D),
    L2(20, 2, 0, 0, 0, 0, 0, 0x5371),
    CMD(CM_PA_X, 0, 1024, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5372),
    CMD(CM_PA_X, 0, 1024, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5373),
    CMD(CM_PA_X, 0, 2048, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5374),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5375),
    CMD(CM_PA_X, 0, 1024, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5376),
    CMD(CM_PA_X, 0, 2048, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5377),
    CMD(CM_PA_X, 0, 2048, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5378),
    CMD(CM_PA_X, 0, 2048, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x537D),
    CMD(CM_PA_X, 0, 1024, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x537D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x537E),
    L2(16, 0, 0, 0, 0, 0, 0, 0x537F),
    CMD(CM_PA_X, 0, -3072, 0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x535C),
    CMD(CM_PA_X, 0, -3072, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x535D),
    CMD(CM_PA_X, 0, -3072, 0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x535E),
    CMD(CM_PA_X, 0, -3072, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x535F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x535C),
    L2(5, 0, 0, 0, 0, 0, 0, 0x537F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x537E),
    L2(6, 2, 0, 0, 0, 0, 0, 0x537D),
    L2(60, 2, 0, 0, 0, 0, 0, 0x5371),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 18 */
const u16 stg04_char_table_018_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_018[44] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x5379),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5379),
    L2(6, 0, 0, 0, 0, 0, 0, 0x537A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x537B),
    L2(14, 0, 0, 0, 0, 0, 0, 0x537C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x537B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x537A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5379),
    L2(10, 0, 0, 0, 0, 0, 0, 0x537D),
    L2(10, 1, 0, 0, 0, 0, 0, 0x537D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 19 */
const u16 stg04_char_table_019_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_019[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x5364),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 20 */
const u16 stg04_char_table_020_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_020[32] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x5364),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5365),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5366),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5367),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5368),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5369),
    L2(4, 1, 0, 0, 0, 0, 0, 0x5369),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 21 */
const u16 stg04_char_table_021_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_021[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x536A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 22 */
const u16 stg04_char_table_022_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_022[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x536B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 23 */
const u16 stg04_char_table_023_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_023[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x536C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 24 */
const u16 stg04_char_table_024_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_024[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x5370),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 25 */
const u16 stg04_char_table_025_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_025[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x536F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 26 */
const u16 stg04_char_table_026_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_026[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x52E1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 27 */
const u16 stg04_char_table_027_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_027[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x52DE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 28 */
const u16 stg04_char_table_028_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_028[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x52E2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 29 */
const u16 stg04_char_table_029_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_029[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x52EB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 30 */
const u16 stg04_char_table_030_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_030[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x52D4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 31 */
const u16 stg04_char_table_031_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_031[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x52EC),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 32 */
const u16 stg04_char_table_032_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_032[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x52D7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 33 */
const u16 stg04_char_table_033_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_033[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x52D2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 34 */
const u16 stg04_char_table_034_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_034[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x52D3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 35 */
const u16 stg04_char_table_035_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_035[8] = {
    L2(26, 0, 0, 0, 0, 0, 0, 0x5315),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 36 */
const u16 stg04_char_table_036_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_036[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x52EF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 37 */
const u16 stg04_char_table_037_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg04_char_table_037[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x5306),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 stg05_char_table_000[], stg05_char_table_001[], stg05_char_table_002[], stg05_char_table_003[],
                 stg05_char_table_004[], stg05_char_table_005[], stg05_char_table_006[], stg05_char_table_007[],
                 stg05_char_table_008[], stg05_char_table_009[], stg05_char_table_010[], stg05_char_table_011[],
                 stg05_char_table_012[], stg05_char_table_013[], stg05_char_table_014[], stg05_char_table_015[],
                 stg05_char_table_016[], stg05_char_table_017[];

/* stg05_char_table: 18 entries (no closing 0: the next table follows); debug viewer: ROSIA OBJ; used by dbg_work, eff05 */
const u32 stg05_char_table[18] = {
    (u32)stg05_char_table_000,  /* 0 */
    (u32)stg05_char_table_001,  /* 1 */
    (u32)stg05_char_table_002,  /* 2 */
    (u32)stg05_char_table_003,  /* 3 */
    (u32)stg05_char_table_004,  /* 4 */
    (u32)stg05_char_table_005,  /* 5 */
    (u32)stg05_char_table_006,  /* 6 */
    (u32)stg05_char_table_007,  /* 7 */
    (u32)stg05_char_table_008,  /* 8 */
    (u32)stg05_char_table_009,  /* 9 */
    (u32)stg05_char_table_010,  /* 10 */
    (u32)stg05_char_table_011,  /* 11 */
    (u32)stg05_char_table_012,  /* 12 */
    (u32)stg05_char_table_013,  /* 13 */
    (u32)stg05_char_table_014,  /* 14 */
    (u32)stg05_char_table_015,  /* 15 */
    (u32)stg05_char_table_016,  /* 16 */
    (u32)stg05_char_table_017,  /* 17 */
};

extern const u16 eff08_char_table_000[], eff08_char_table_001[], eff08_char_table_002[], eff08_char_table_003[],
                 eff08_char_table_004[], eff08_char_table_005[], eff08_char_table_006[], eff08_char_table_007[],
                 eff08_char_table_008[], eff08_char_table_009[], eff08_char_table_010[], eff08_char_table_011[],
                 eff08_char_table_012[], eff08_char_table_013[], eff08_char_table_014[], eff08_char_table_015[];

/* eff08_char_table: 16 entries (no closing 0: the next table follows); used by eff08 */
const u32 eff08_char_table[16] = {
    (u32)eff08_char_table_000,  /* 0 */
    (u32)eff08_char_table_001,  /* 1 */
    (u32)eff08_char_table_002,  /* 2 */
    (u32)eff08_char_table_003,  /* 3 */
    (u32)eff08_char_table_004,  /* 4 */
    (u32)eff08_char_table_005,  /* 5 */
    (u32)eff08_char_table_006,  /* 6 */
    (u32)eff08_char_table_007,  /* 7 */
    (u32)eff08_char_table_008,  /* 8 */
    (u32)eff08_char_table_009,  /* 9 */
    (u32)eff08_char_table_010,  /* 10 */
    (u32)eff08_char_table_011,  /* 11 */
    (u32)eff08_char_table_012,  /* 12 */
    (u32)eff08_char_table_013,  /* 13 */
    (u32)eff08_char_table_014,  /* 14 */
    (u32)eff08_char_table_015,  /* 15 */
};

extern const u16 eff07_char_table_000[], eff07_char_table_001[], eff07_char_table_002[], eff07_char_table_003[],
                 eff07_char_table_004[], eff07_char_table_005[], eff07_char_table_006[], eff07_char_table_007[],
                 eff07_char_table_008[];

/* eff07_char_table: 9 entries; used by EFF07 */
const u32 eff07_char_table[10] = {
    (u32)eff07_char_table_000,  /* 0 */
    (u32)eff07_char_table_001,  /* 1 */
    (u32)eff07_char_table_002,  /* 2 */
    (u32)eff07_char_table_003,  /* 3 */
    (u32)eff07_char_table_004,  /* 4 */
    (u32)eff07_char_table_005,  /* 5 */
    (u32)eff07_char_table_006,  /* 6 */
    (u32)eff07_char_table_007,  /* 7 */
    (u32)eff07_char_table_008,  /* 8 */
    0
};

/* script: 0 */
const u16 stg05_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_000[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CF0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 stg05_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_001[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C08),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 stg05_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_002[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C09),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 stg05_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_003[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C0A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 stg05_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_004[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C0B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 stg05_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_005[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CF1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 stg05_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_006[44] = {
    L2(84, 0, 0, 0, 0, 0, 0, 0x4C0E),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C0F),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C10),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C11),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C12),
    L2(60, 0, 0, 0, 0, 0, 0, 0x4C13),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C12),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C11),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C10),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C0F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 stg05_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_007[52] = {
    L2(20, 0, 0, 0, 0, 0, 0, 0x4C14),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C15),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C16),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C17),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C18),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C19),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C1A),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C19),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C18),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C17),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C16),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C15),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 stg05_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_008[64] = {
    L2(32, 0, 0, 0, 0, 0, 0, 0x4C1B),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C1C),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C1D),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C1E),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C1F),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C20),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C21),
    L2(32, 0, 0, 0, 0, 0, 0, 0x4C22),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C23),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C24),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C25),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C26),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C27),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C28),
    L2(160, 0, 0, 0, 0, 0, 0, 0x4C29),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 stg05_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_009[60] = {
    L2(42, 0, 0, 0, 0, 0, 0, 0x4C2A),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C2B),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C2C),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C2D),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C2E),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C2F),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C30),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C31),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C32),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C33),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C34),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C35),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C36),
    L2(160, 0, 0, 0, 0, 0, 0, 0x4C37),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 stg05_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_010[64] = {
    L2(26, 0, 0, 0, 0, 0, 0, 0x4C38),
    L2(26, 0, 0, 0, 0, 0, 0, 0x4C39),
    L2(26, 0, 0, 0, 0, 0, 0, 0x4C3A),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C3B),
    L2(20, 0, 0, 0, 0, 0, 0, 0x4C3C),
    L2(20, 0, 0, 0, 0, 0, 0, 0x4C3D),
    L2(20, 0, 0, 0, 0, 0, 0, 0x4C3E),
    L2(20, 0, 0, 0, 0, 0, 0, 0x4C3F),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C40),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C41),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C42),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C43),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C44),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C45),
    L2(160, 0, 0, 0, 0, 0, 0, 0x4C46),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 stg05_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_011[52] = {
    L2(48, 0, 0, 0, 0, 0, 0, 0x4C47),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C48),
    L2(22, 0, 0, 0, 0, 0, 0, 0x4C49),
    L2(20, 0, 0, 0, 0, 0, 0, 0x4C4A),
    L2(20, 0, 0, 0, 0, 0, 0, 0x4C4B),
    L2(20, 0, 0, 0, 0, 0, 0, 0x4C4C),
    L2(20, 0, 0, 0, 0, 0, 0, 0x4C4D),
    L2(18, 0, 0, 0, 0, 0, 0, 0x4C4E),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C4F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C50),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C51),
    L2(160, 0, 0, 0, 0, 0, 0, 0x4C52),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 stg05_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_012[84] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C5E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C5F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C60),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C61),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C62),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C63),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C62),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C61),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C60),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C5F),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C5E),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C5F),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C60),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C61),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C62),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C63),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C62),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C61),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C60),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C5F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 stg05_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_013[124] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C64),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C65),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C66),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C67),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C66),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C65),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C64),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C65),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C66),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C67),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C68),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C69),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C68),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C67),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C68),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C69),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C68),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C67),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C66),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C65),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C64),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C65),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C66),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C67),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C68),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C69),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C68),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C67),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C66),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C65),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 stg05_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_014[44] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C6A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C6B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C6C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C6D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C6E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C6F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C6E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C6D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C6C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C6B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 stg05_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_015[72] = {
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C70),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4C71),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4C72),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4C73),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4C74),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C75),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C76),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C77),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C78),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C79),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C80),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C81),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C82),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C83),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C84),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C85),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4C86),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16 */
const u16 stg05_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_016[96] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C87),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C88),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C89),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C90),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C91),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C92),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C93),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C94),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C95),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C96),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C97),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C98),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C99),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 17 */
const u16 stg05_char_table_017_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg05_char_table_017[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff08_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_000[60] = {
    L2(54, 0, 0, 0, 0, 0, 0, 0x4C53),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C55),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C56),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C57),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4C5B),
    CMD(CM_EXEC, 3, 0, 0),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C57),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4C56),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4C55),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4C54),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4C53),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4C58),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4C53),
    L2(6, 1, 0, 0, 0, 0, 0, 0x4C53),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff08_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_001[32] = {
    L2(12, 0, 0, 0, 0, 0, 0, 0x4C57),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4C56),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4C55),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4C54),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C53),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C58),
    L2(200, 0, 0, 0, 0, 0, 0, 0x4C58),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff08_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_002[44] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C64),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C65),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C66),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C67),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C68),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C69),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C68),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C67),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C66),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4C65),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff08_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_003[44] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C64),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4C65),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4C66),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4C67),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C68),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4C69),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4C68),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4C67),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4C66),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C65),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff08_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_004[112] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF8),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF9),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CFA),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CFB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CFC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CFD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CFF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D00),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D01),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D02),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D03),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D04),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D05),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D06),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D07),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D08),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D09),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D0A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D0B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D0C),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4D0C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 eff08_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_005[8] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D30),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 eff08_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_006[8] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D31),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 eff08_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_007[56] = {
    CMD(CM_EXEC, 3, 1, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4D32),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D33),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D34),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D35),
    CMD(CM_EXEC, 3, 2, 0),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4D36),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4D35),
    CMD(CM_EXEC, 3, 3, 0),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4D34),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D35),
    L2(60, 0, 0, 0, 0, 0, 0, 0x4D36),
    L2(4, 255, 0, 0, 0, 0, 0, 0x4D36),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 eff08_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_008[52] = {
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D3A),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4D3B),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4D3C),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4D3D),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4D3E),
    L2(13, 0, 0, 0, 0, 0, 0, 0x4D3F),
    L2(13, 0, 0, 0, 0, 0, 0, 0x4D40),
    L2(13, 0, 0, 0, 0, 0, 0, 0x4D41),
    L2(13, 0, 0, 0, 0, 0, 0, 0x4D42),
    L2(13, 0, 0, 0, 0, 0, 0, 0x4D43),
    L2(13, 0, 0, 0, 0, 0, 0, 0x4D44),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4D45),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 eff08_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_009[56] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x4D4E),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4D4F),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4D50),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4D51),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4D52),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4D53),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4D54),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4D55),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4D56),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4D57),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4D58),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4D59),
    L2(11, 0, 0, 0, 0, 0, 0, 0x4D5A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 eff08_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_010[20] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D5B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D5C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D5D),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4D5D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 eff08_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_011[28] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D83),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D84),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D85),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D86),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D87),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4D87),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 eff08_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_012[28] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D88),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D89),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D8A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D8B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D8C),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4D8C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 eff08_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_013[24] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D8E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D8F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D90),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D91),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4D91),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 eff08_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_014[36] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D92),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D93),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D94),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D95),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D96),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D97),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D98),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4D98),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 eff08_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff08_char_table_015[84] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DB6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DB7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DB8),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DB9),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DBA),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DBB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DBC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DBD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DBE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DBF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DB6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DB7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DB8),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DB9),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DBA),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DBB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DBC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DBD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DBE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4DBF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff07_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff07_char_table_000[60] = {
    CMD(CM_FOR, 0, 0, 3),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D6E),
    L2(17, 0, 0, 0, 0, 0, 0, 0x4D6F),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D6E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4D70),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4D71),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4D70),
    CMD(CM_NEX, 0, 0, 0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D70),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D6E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D73),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D74),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D75),
    L2(6, 1, 0, 0, 0, 0, 0, 0x4D75),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff07_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff07_char_table_001[136] = {
    L2(21, 0, 0, 0, 0, 0, 0, 0x4D6E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D72),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D73),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D74),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D75),
    CMD(CM_FOR, 0, 0, 3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D77),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D78),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4D77),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D76),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D75),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D76),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D77),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D76),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D75),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D76),
    CMD(CM_NEX, 0, 0, 0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D77),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4D78),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D77),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D76),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D75),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D76),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D77),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D76),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D75),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D76),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D77),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D76),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D75),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D74),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4D73),
    L2(7, 1, 0, 0, 0, 0, 0, 0x4D73),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff07_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff07_char_table_002[52] = {
    L2(16, 0, 0, 0, 0, 0, 0, 0x4D79),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D7A),
    L2(32, 0, 0, 0, 0, 0, 0, 0x4D7B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D7C),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4D7D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4D70),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4D7F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D80),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4D81),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4D80),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4D81),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4D81),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff07_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff07_char_table_003[32] = {
    CMD(CM_FOR, 0, 0, 5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D7F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4D81),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4D80),
    CMD(CM_NEX, 0, 0, 0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4D71),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4D71),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff07_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff07_char_table_004[28] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D78),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4D7C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4D7D),
    L2(16, 0, 0, 0, 0, 0, 0, 0x4D7B),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4D7A),
    L2(12, 1, 0, 0, 0, 0, 0, 0x4D7A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 eff07_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff07_char_table_005[196] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x4C87),
    L2(200, 0, 0, 0, 0, 0, 0, 0x4C87),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C88),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C89),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C90),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C91),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C92),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C93),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C94),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C95),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C96),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C97),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C98),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C99),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9D),
    L2(200, 0, 0, 0, 0, 0, 0, 0x4CCA),
    L2(100, 0, 0, 0, 0, 0, 0, 0x4CCA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD6),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD7),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CE0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 eff07_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff07_char_table_006[192] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x4C87),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C88),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C89),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C90),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C91),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C92),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C93),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C94),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C95),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C96),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C97),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C98),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C99),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9D),
    L2(220, 0, 0, 0, 0, 0, 0, 0x4CCA),
    L2(220, 0, 0, 0, 0, 0, 0, 0x4CCA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD6),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD7),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CE0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 eff07_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff07_char_table_007[200] = {
    L2(80, 0, 0, 0, 0, 0, 0, 0x4C87),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C88),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C89),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C8F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C90),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C91),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C92),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C93),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C94),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C95),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C96),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C97),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C98),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C99),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4C9D),
    L2(240, 0, 0, 0, 0, 0, 0, 0x4CCA),
    L2(240, 0, 0, 0, 0, 0, 0, 0x4CCA),
    L2(100, 0, 0, 0, 0, 0, 0, 0x4CCA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CCF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD6),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD7),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CD9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CDF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4CE0),
    L2(200, 0, 0, 0, 0, 0, 0, 0x4C87),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 eff07_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff07_char_table_008[24] = {
    CMD(CM_EXEC, 3, 1, 0),
    L2(14, 0, 0, 0, 0, 0, 0, 0x4D32),
    CMD(CM_EXEC, 3, 1, 0),
    L2(18, 0, 0, 0, 0, 0, 0, 0x4D32),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4D32),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 stg06_char_table_000[], stg06_char_table_001[], stg06_char_table_002[], stg06_char_table_003[],
                 stg06_char_table_004[], stg06_char_table_005[], stg06_char_table_006[], stg06_char_table_007[],
                 stg06_char_table_008[], stg06_char_table_009[], stg06_char_table_010[], stg06_char_table_011[],
                 stg06_char_table_012[], stg06_char_table_013[], stg06_char_table_014[], stg06_char_table_015[],
                 stg06_char_table_016[], stg06_char_table_017[], stg06_char_table_018[], stg06_char_table_019[],
                 stg06_char_table_020[], stg06_char_table_021[], stg06_char_table_022[], stg06_char_table_023[],
                 stg06_char_table_024[], stg06_char_table_025[], stg06_char_table_026[], stg06_char_table_027[],
                 stg06_char_table_028[], stg06_char_table_029[], stg06_char_table_030[], stg06_char_table_031[],
                 stg06_char_table_032[], stg06_char_table_033[], stg06_char_table_034[], stg06_char_table_035[],
                 stg06_char_table_036[], stg06_char_table_037[];

/* stg06_char_table: 38 entries; debug viewer: GERMANY OBJ; used by EFF63, dbg_work, eff05 */
const u32 stg06_char_table[39] = {
    (u32)stg06_char_table_000,  /* 0 */
    (u32)stg06_char_table_001,  /* 1 */
    (u32)stg06_char_table_002,  /* 2 */
    (u32)stg06_char_table_003,  /* 3 */
    (u32)stg06_char_table_004,  /* 4 */
    (u32)stg06_char_table_005,  /* 5 */
    (u32)stg06_char_table_006,  /* 6 */
    (u32)stg06_char_table_007,  /* 7 */
    (u32)stg06_char_table_008,  /* 8 */
    (u32)stg06_char_table_009,  /* 9 */
    (u32)stg06_char_table_010,  /* 10 */
    (u32)stg06_char_table_011,  /* 11 */
    (u32)stg06_char_table_012,  /* 12 */
    (u32)stg06_char_table_013,  /* 13 */
    (u32)stg06_char_table_014,  /* 14 */
    (u32)stg06_char_table_015,  /* 15 */
    (u32)stg06_char_table_016,  /* 16 */
    (u32)stg06_char_table_017,  /* 17 */
    (u32)stg06_char_table_018,  /* 18 */
    (u32)stg06_char_table_019,  /* 19 */
    (u32)stg06_char_table_020,  /* 20 */
    (u32)stg06_char_table_021,  /* 21 */
    (u32)stg06_char_table_022,  /* 22 */
    (u32)stg06_char_table_023,  /* 23 */
    (u32)stg06_char_table_024,  /* 24 */
    (u32)stg06_char_table_025,  /* 25 */
    (u32)stg06_char_table_026,  /* 26 */
    (u32)stg06_char_table_027,  /* 27 */
    (u32)stg06_char_table_028,  /* 28 */
    (u32)stg06_char_table_029,  /* 29 */
    (u32)stg06_char_table_030,  /* 30 */
    (u32)stg06_char_table_031,  /* 31 */
    (u32)stg06_char_table_032,  /* 32 */
    (u32)stg06_char_table_033,  /* 33 */
    (u32)stg06_char_table_034,  /* 34 */
    (u32)stg06_char_table_035,  /* 35 */
    (u32)stg06_char_table_036,  /* 36 */
    (u32)stg06_char_table_037,  /* 37 */
    0
};

/* script: 0 */
const u16 stg06_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_000[52] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x4DE0),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4DE1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DE2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DE3),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4DE4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DE5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DE6),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4DE7),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DE8),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4DE5),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4DE4),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4DE3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 stg06_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_001[116] = {
    L2(32, 0, 0, 0, 0, 0, 0, 0x4E3A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E3B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E3C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E3D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E3E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E3F),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4E40),
    L2(14, 0, 0, 0, 0, 0, 0, 0x4E41),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E42),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E43),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E44),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E45),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E46),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E47),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E48),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E47),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E46),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E45),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4E44),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E43),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E42),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E41),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4E40),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E3F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E3E),
    L2(12, 0, 0, 0, 0, 0, 0, 0x4E3D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E3C),
    L2(14, 0, 0, 0, 0, 0, 0, 0x4E3B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 stg06_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_002[80] = {
    L2(120, 0, 0, 0, 0, 0, 0, 0x4E58),
    CMD(CM_FOR, 0, 0, 3),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E58),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E55),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E58),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E56),
    CMD(CM_NEX, 0, 0, 0),
    L2(120, 0, 0, 0, 0, 0, 0, 0x4E58),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E59),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E5A),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E57),
    CMD(CM_FOR, 0, 0, 2),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E5A),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E59),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E5A),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E57),
    CMD(CM_NEX, 0, 0, 0),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E5A),
    L2(120, 0, 0, 0, 0, 0, 0, 0x4E58),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 stg06_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_003[176] = {
    CMD(CM_FOR, 0, 0, 3),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E5E),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E5F),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E60),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E5F),
    CMD(CM_NEX, 0, 0, 0),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E61),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E62),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E63),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E64),
    L2(72, 0, 0, 0, 0, 0, 0, 0x4E65),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E66),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E67),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E68),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E69),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E6A),
    CMD(CM_FOR, 0, 0, 2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E64),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E65),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E66),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E67),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E68),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E69),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E6A),
    CMD(CM_NEX, 0, 0, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E6B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E6A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E5B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E5C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4E5D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E62),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E61),
    L2(190, 0, 0, 0, 0, 0, 0, 0x4E5E),
    CMD(CM_FOR, 0, 0, 3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E6C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E6D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E6E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E6F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E70),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E71),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E72),
    CMD(CM_NEX, 0, 0, 0),
    L2(190, 0, 0, 0, 0, 0, 0, 0x4E5E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 stg06_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_004[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E73),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 stg06_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_005[92] = {
    CMD(CM_FOR, 0, 0, 3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DF4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DF5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DF6),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DF5),
    CMD(CM_NEX, 0, 0, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DF7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4DF8),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4DF8),
    L2(180, 0, 0, 0, 0, 0, 0, 0x4DF9),
    CMD(CM_FOR, 0, 0, 3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DF9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DFA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DFB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DFC),
    CMD(CM_NEX, 0, 0, 0),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4DFC),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4DFD),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4DF8),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4DF7),
    L2(5, 1, 0, 0, 0, 0, 0, 0x4DF3),
    L2(186, 1, 0, 0, 0, 0, 0, 0x4DF3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 stg06_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_006[76] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4DFE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4DFF),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E00),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E01),
    CMD(CM_FOR, 0, 0, 3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E02),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E03),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E04),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E05),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E06),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E07),
    CMD(CM_NEX, 0, 0, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E01),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E00),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DFF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DFE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DFE),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4DFE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 stg06_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_007[52] = {
    L2(250, 0, 0, 0, 0, 0, 0, 0x4DE9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DEA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DEB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DEC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DED),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DEE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DEF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DF0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DF1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DF2),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4DE9),
    L2(250, 0, 0, 0, 0, 0, 0, 0x4DE9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 stg06_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_008[84] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x4DE9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DEA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DEB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DEC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DED),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DEE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DEF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DF0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4DF1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DF2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DEA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DEB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DEC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DED),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DEE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DEF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DF0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4DF1),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4DF2),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4DF2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 stg06_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_009[56] = {
    L2(90, 0, 0, 0, 0, 0, 0, 0x4E10),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E0F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E0E),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E0D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E0E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E0F),
    L2(20, 0, 0, 0, 0, 0, 0, 0x4E10),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E0F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E0E),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E0D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E0E),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4E0F),
    L2(1, 1, 0, 0, 0, 0, 0, 0x4E0F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 stg06_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_010[84] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E10),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E11),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E12),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E13),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E14),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E15),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E16),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E17),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E18),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E19),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E1A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E1B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E1C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E1D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E1E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E1F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E20),
    L2(7, 0, 0, 0, 0, 0, 0, 0x4E12),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4E11),
    L2(7, 1, 0, 0, 0, 0, 0, 0x4E11),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 stg06_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_011[104] = {
    L2(20, 0, 0, 0, 0, 0, 0, 0x4E21),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E22),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E23),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E24),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E25),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E26),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E27),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E28),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E29),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E2A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E2B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E2C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E2D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E2C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E2B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E2A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E29),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E28),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E27),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E26),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E25),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E24),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E23),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E22),
    L2(6, 1, 0, 0, 0, 0, 0, 0x4E22),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 stg06_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_012[100] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E21),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E2E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E2F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E30),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E31),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E32),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E33),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E34),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E35),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E36),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E37),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E38),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E39),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E38),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E37),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E36),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E35),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E34),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E33),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E32),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E31),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4E30),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4E2F),
    L2(5, 1, 0, 0, 0, 0, 0, 0x4E2E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 stg06_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_013[100] = {
    L2(20, 0, 0, 0, 0, 0, 0, 0x4E49),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E4A),
    L2(6, 1, 0, 0, 0, 0, 0, 0x4E4A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 stg06_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_014[52] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E49),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E50),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E51),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E52),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E53),
    L2(20, 0, 0, 0, 0, 0, 0, 0x4E54),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E53),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E52),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4E51),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4E50),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E49),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4E49),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 stg06_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_015[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4E08),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16 */
const u16 stg06_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_016[28] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E09),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E0A),
    L2(9, 0, 0, 0, 0, 0, 0, 0x4E0B),
    L2(48, 0, 0, 0, 0, 0, 0, 0x4E0C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4E0A),
    L2(6, 1, 0, 0, 0, 0, 0, 0x4E0A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 17 */
const u16 stg06_char_table_017_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_017[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EA5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 18 */
const u16 stg06_char_table_018_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_018[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EA6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 19 */
const u16 stg06_char_table_019_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_019[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EA7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 20 */
const u16 stg06_char_table_020_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_020[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EA8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 21 */
const u16 stg06_char_table_021_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_021[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EAA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 22 */
const u16 stg06_char_table_022_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_022[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EAB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 23 */
const u16 stg06_char_table_023_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_023[32] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F20),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F24),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F25),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F26),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F27),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F28),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F29),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 24 */
const u16 stg06_char_table_024_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_024[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EAE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 25 */
const u16 stg06_char_table_025_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_025[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F21),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 26 */
const u16 stg06_char_table_026_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_026[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F22),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 27 */
const u16 stg06_char_table_027_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_027[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F23),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 28 */
const u16 stg06_char_table_028_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_028[36] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4EBD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4EBE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4EBF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4EC0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4EC1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4EC2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4EC3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4EC4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 29 */
const u16 stg06_char_table_029_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_029[92] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x4EC5),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4EC6),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4EC7),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4EC8),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4EC9),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ECA),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ECB),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ECC),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ECD),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ECE),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ECF),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ED0),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ECF),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ECE),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ECD),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ECC),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ECB),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4ECA),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4EC9),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4EC8),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4EC7),
    L2(10, 0, 0, 0, 0, 0, 0, 0x4EC6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 30 */
const u16 stg06_char_table_030_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_030[28] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x4EAF),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4EF6),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4EF7),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4EF8),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4EF9),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4EFA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 31 */
const u16 stg06_char_table_031_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_031[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EA9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 32 */
const u16 stg06_char_table_032_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_032[20] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4EA9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ED1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ED2),
    L2(8, 1, 0, 0, 0, 0, 0, 0x4ED2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 33 */
const u16 stg06_char_table_033_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_033[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x4ED2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 34 */
const u16 stg06_char_table_034_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_034[96] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4ED3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4ED4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4ED5),
    L2(4, 2, 0, 0, 0, 0, 0, 0x4ED6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4ED7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4ED8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4ED9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EDA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EDB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EDC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EDB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EDA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4ED9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EDD),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EDE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EDF),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EDD),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4ED9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EDA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EDB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EDA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4ED9),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4ED9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 35 */
const u16 stg06_char_table_035_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_035[68] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EE0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EE1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EE2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EE3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EE4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EE5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EE6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EE7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EE8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EE9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EEA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EEB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EEC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4EED),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4EEE),
    L2(5, 1, 0, 0, 0, 0, 0, 0x4EEE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 36 */
const u16 stg06_char_table_036_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_036[8] = {
    L2(5, 1, 0, 0, 0, 0, 0, 0x4EEF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 37 */
const u16 stg06_char_table_037_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg06_char_table_037[8] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x4ED9),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 stg07_char_table_000[], stg07_char_table_001[], stg07_char_table_002[], stg07_char_table_003[],
                 stg07_char_table_004[], stg07_char_table_005[], stg07_char_table_006[], stg07_char_table_007[],
                 stg07_char_table_008[], stg07_char_table_009[], stg07_char_table_010[];

/* stg07_char_table: 11 entries; debug viewer: FURUDERA OBJ; used by dbg_work, eff05 */
const u32 stg07_char_table[12] = {
    (u32)stg07_char_table_000,  /* 0 */
    (u32)stg07_char_table_001,  /* 1 */
    (u32)stg07_char_table_002,  /* 2 */
    (u32)stg07_char_table_003,  /* 3 */
    (u32)stg07_char_table_004,  /* 4 */
    (u32)stg07_char_table_005,  /* 5 */
    (u32)stg07_char_table_006,  /* 6 */
    (u32)stg07_char_table_007,  /* 7 */
    (u32)stg07_char_table_008,  /* 8 */
    (u32)stg07_char_table_009,  /* 9 */
    (u32)stg07_char_table_010,  /* 10 */
    0
};

/* script: 0 */
const u16 stg07_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg07_char_table_000[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x6510),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 stg07_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg07_char_table_001[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x6511),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 stg07_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg07_char_table_002[76] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x6528),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6529),
    L2(6, 0, 0, 0, 0, 0, 0, 0x652A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6529),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6528),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6529),
    L2(6, 0, 0, 0, 0, 0, 0, 0x652A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6529),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6528),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6529),
    L2(6, 0, 0, 0, 0, 0, 0, 0x652A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x652B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x652A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6529),
    L2(6, 0, 0, 0, 0, 0, 0, 0x652A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x652B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x652A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6529),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 stg07_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg07_char_table_003[40] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x7738),
    L2(5, 0, 0, 0, 0, 0, 0, 0x7739),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7738),
    L2(7, 0, 0, 0, 0, 0, 0, 0x7739),
    L2(4, 0, 0, 0, 0, 0, 0, 0x7738),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7739),
    L2(10, 0, 0, 0, 0, 0, 0, 0x7738),
    L2(12, 0, 0, 0, 0, 0, 0, 0x7739),
    L2(7, 0, 0, 0, 0, 0, 0, 0x773A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 stg07_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg07_char_table_004[40] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x773B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x773C),
    L2(9, 0, 0, 0, 0, 0, 0, 0x773B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x773C),
    L2(5, 0, 0, 0, 0, 0, 0, 0x773B),
    L2(7, 0, 0, 0, 0, 0, 0, 0x773C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x773B),
    L2(11, 0, 0, 0, 0, 0, 0, 0x773C),
    L2(5, 0, 0, 0, 0, 0, 0, 0x773D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 stg07_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg07_char_table_005[60] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x6540),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6541),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6542),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6541),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6540),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6541),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6542),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6541),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6542),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6541),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6540),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6541),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6540),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6541),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 stg07_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg07_char_table_006[56] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6560),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6561),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6562),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6563),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6564),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6565),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6566),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6567),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6568),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6569),
    L2(8, 0, 0, 0, 0, 0, 0, 0x656A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x656B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x656C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 stg07_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg07_char_table_007[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x654C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 stg07_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg07_char_table_008[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x654D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 stg07_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg07_char_table_009[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x654E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 stg07_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 stg07_char_table_010[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x654F),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 eff77_char_table_000[], eff77_char_table_001[], eff77_char_table_002[], eff77_char_table_003[],
                 eff77_char_table_004[], eff77_char_table_005[];

/* eff77_char_table: 6 entries (no closing 0: the next table follows); debug viewer: YUN YAN; used by EFF77, dbg_work */
const u32 eff77_char_table[6] = {
    (u32)eff77_char_table_000,  /* 0 */
    (u32)eff77_char_table_001,  /* 1 */
    (u32)eff77_char_table_002,  /* 2 */
    (u32)eff77_char_table_003,  /* 3 */
    (u32)eff77_char_table_004,  /* 4 */
    (u32)eff77_char_table_005,  /* 5 */
};

extern const u16 eff78_char_table_000[], eff78_char_table_001[], eff78_char_table_002[], eff78_char_table_003[],
                 eff78_char_table_004[];

/* eff78_char_table: 5 entries (no closing 0: the next table follows); used by EFF78 */
const u32 eff78_char_table[5] = {
    (u32)eff78_char_table_000,  /* 0 */
    (u32)eff78_char_table_001,  /* 1 */
    (u32)eff78_char_table_002,  /* 2 */
    (u32)eff78_char_table_003,  /* 3 */
    (u32)eff78_char_table_004,  /* 4 */
};

extern const u16 eff79_char_table_000[], eff79_char_table_001[], eff79_char_table_002[], eff79_char_table_003[],
                 eff79_char_table_004[], eff79_char_table_005[];

/* eff79_char_table: 6 entries (no closing 0: the next table follows); used by EFF79 */
const u32 eff79_char_table[6] = {
    (u32)eff79_char_table_000,  /* 0 */
    (u32)eff79_char_table_001,  /* 1 */
    (u32)eff79_char_table_002,  /* 2 */
    (u32)eff79_char_table_003,  /* 3 */
    (u32)eff79_char_table_004,  /* 4 */
    (u32)eff79_char_table_005,  /* 5 */
};

extern const u16 eff80_char_table_000[], eff80_char_table_001[];

/* eff80_char_table: 4 entries (no closing 0: the next table follows); used by EFF80 */
const u32 eff80_char_table[4] = {
    (u32)eff80_char_table_000,  /* 0 */
    (u32)eff80_char_table_001,  /* 1 */
    (u32)eff80_char_table_001,  /* 2 */
    (u32)eff80_char_table_001,  /* 3 */
};

extern const u16 eff81_char_table_000[], eff81_char_table_001[], eff81_char_table_002[];

/* eff81_char_table: 3 entries; used by EFF81 */
const u32 eff81_char_table[4] = {
    (u32)eff81_char_table_000,  /* 0 */
    (u32)eff81_char_table_001,  /* 1 */
    (u32)eff81_char_table_002,  /* 2 */
    0
};

/* script: 0 */
const u16 eff77_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff77_char_table_000[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x624D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff77_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff77_char_table_001[48] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x624D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6251),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6252),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6253),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6254),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6255),
    L2(18, 0, 0, 0, 0, 0, 0, 0x6254),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6256),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6257),
    L2(60, 0, 0, 0, 0, 0, 0, 0x624D),
    L2(2, 1, 0, 0, 0, 0, 0, 0x624D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff77_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff77_char_table_002[28] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x624D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x624E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x624F),
    L2(2, 1, 0, 0, 0, 0, 0, 0x624F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6250),
    CMD(CM_END, 0, 0, 5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff77_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff77_char_table_003[48] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x62BF),
    L2(3, 9, 0, 0, 0, 0, 0, 0x62C0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x62C1),
    L2(7, 0, 0, 0, 0, 0, 0, 0x62C2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x62C3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x62C4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x62C5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x62C6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62C6),
    L2(200, 255, 0, 0, 0, 0, 0, 0x62C6),
    CMD(CM_END, 0, 0, 10),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff77_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff77_char_table_004[8] = {
    L2(20, 0, 0, 0, 0, 0, 0, 0x62C6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 eff77_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff77_char_table_005[28] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x62C8),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62C9),
    L2(1, 0, 0, 0, 0, 0, 0, 0x62CB),
    L2(30, 0, 0, 0, 0, 0, 0, 0x62CA),
    L2(250, 1, 0, 0, 0, 0, 0, 0x62CA),
    CMD(CM_END, 0, 0, 5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff78_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff78_char_table_000[80] = {
    L2(32, 0, 0, 0, 0, 0, 0, 0x6246),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6247),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6248),
    L2(38, 0, 0, 0, 0, 0, 0, 0x6249),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6248),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6247),
    L2(85, 0, 0, 0, 0, 0, 0, 0x6246),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6247),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6248),
    L2(38, 0, 0, 0, 0, 0, 0, 0x6249),
    L2(2, 0, 0, 0, 0, 0, 0, 0x624A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x624B),
    L2(221, 0, 0, 0, 0, 0, 0, 0x6240),
    L2(2, 0, 0, 0, 0, 0, 0, 0x624B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x624A),
    L2(55, 0, 0, 0, 0, 0, 0, 0x6249),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6248),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6247),
    L2(2, 1, 0, 0, 0, 0, 0, 0x6247),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff78_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff78_char_table_001[32] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x62A6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62A7),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62A8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62A9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62AA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62AB),
    L2(8, 1, 0, 0, 0, 0, 0, 0x62AB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff78_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff78_char_table_002[32] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x6240),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6241),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6242),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6243),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6244),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6245),
    L2(2, 1, 0, 0, 0, 0, 0, 0x6245),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff78_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff78_char_table_003[56] = {
    L2(8, 2, 0, 0, 0, 0, 0, 0x62AC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62AD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62AE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62AF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62B0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62B1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62B3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62B3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62B4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62B5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62B6),
    L2(8, 1, 0, 0, 0, 0, 0, 0x62B6),
    CMD(CM_END, 0, 0, 11),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff78_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff78_char_table_004[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x62B6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff79_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff79_char_table_000[76] = {
    CMD(CM_FOR, 0, 0, 8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6269),
    L2(4, 0, 0, 0, 0, 0, 0, 0x626A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x626B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x626C),
    CMD(CM_NEX, 0, 0, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x626D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x626E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x626F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6270),
    CMD(CM_FOR, 0, 0, 8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6270),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6271),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6272),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6273),
    CMD(CM_NEX, 0, 0, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6274),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6275),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff79_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff79_char_table_001[16] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x6276),
    L2(4, 1, 0, 0, 0, 0, 0, 0x6277),
    CMD(CM_END, 0, 0, 2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff79_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff79_char_table_002[20] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x62FC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62FD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62FE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62FF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff79_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff79_char_table_003[60] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x6300),
    L2(1, 0, 0, 0, 0, 0, 0, 0x6301),
    L2(1, 0, 0, 0, 0, 0, 0, 0x6302),
    L2(1, 0, 0, 0, 0, 0, 0, 0x6303),
    L2(1, 0, 0, 0, 0, 0, 0, 0x6304),
    L2(1, 0, 0, 0, 0, 0, 0, 0x6305),
    L2(1, 0, 0, 0, 0, 0, 0, 0x6306),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6307),
    L2(2, 2, 0, 0, 0, 0, 0, 0x6307),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6308),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6309),
    L2(4, 0, 0, 0, 0, 0, 0, 0x630A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x630B),
    CMD(CM_END, 0, 0, 10),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff79_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff79_char_table_004[72] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x62DD),
    L2(4, 1, 0, 0, 0, 0, 0, 0x62DE),
    L2(4, 1, 0, 0, 0, 0, 0, 0x62DF),
    L2(4, 1, 0, 0, 0, 0, 0, 0x62E0),
    L2(250, 9, 0, 0, 0, 0, 0, 0x62E1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x62E2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x62E3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x62E4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x62E5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x62E6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x62E7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x62E8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x62E9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x62EA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x62EB),
    L2(4, 2, 0, 0, 0, 0, 0, 0x62EB),
    CMD(CM_END, 0, 0, 16),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 eff79_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff79_char_table_005[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x62EB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff80_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff80_char_table_000[56] = {
    L2(11, 0, 0, 0, 0, 0, 0, 0x62EC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62ED),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62EE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62EF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62F0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62F1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62F2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62F3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62F4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62F5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62F6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x62F7),
    L2(250, 1, 0, 0, 0, 0, 0, 0x62F7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1, 2, 3 */
const u16 eff80_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff80_char_table_001[84] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x6330),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6331),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6332),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6333),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6334),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6335),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6336),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6337),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6338),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6339),
    L2(4, 0, 0, 0, 0, 0, 0, 0x633A),
    CMD(CM_PA_Y, 0, -256, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x633B),
    CMD(CM_PA_Y, 0, -256, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x633B),
    CMD(CM_PA_Y, 0, 256, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x633B),
    CMD(CM_PA_Y, 0, 256, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x633B),
    CMD(CM_END, 0, 0, 12),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff81_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff81_char_table_000[68] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x62CC),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62CD),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62CE),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62CF),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62D0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62D1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62D2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62D3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62D4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62D5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62D6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62D7),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62D8),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62D9),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62DA),
    L2(8, 0, 0, 0, 0, 0, 0, 0x62DB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff81_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff81_char_table_001[36] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6340),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6341),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6342),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6343),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6344),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6345),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6346),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6347),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff81_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff81_char_table_002[68] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6348),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6349),
    L2(8, 0, 0, 0, 0, 0, 0, 0x634A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x634B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x634C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x634D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x634E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x634F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6350),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6351),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6352),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6353),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6354),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6355),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6356),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6357),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 eff45_char_table_000[], eff45_char_table_001[], eff45_char_table_002[], eff45_char_table_003[],
                 eff45_char_table_004[], eff45_char_table_005[], eff45_char_table_006[], eff45_char_table_007[],
                 eff45_char_table_008[], eff45_char_table_009[], eff45_char_table_010[], eff45_char_table_011[],
                 eff45_char_table_012[], eff45_char_table_013[], eff45_char_table_014[], eff45_char_table_015[];

/* eff45_char_table: 16 entries (no closing 0: the next table follows); debug viewer: AFRICA 1; used by EFF45, EFFC2, EFFC3, dbg_work, eff05 */
const u32 eff45_char_table[16] = {
    (u32)eff45_char_table_000,  /* 0 */
    (u32)eff45_char_table_001,  /* 1 */
    (u32)eff45_char_table_002,  /* 2 */
    (u32)eff45_char_table_003,  /* 3 */
    (u32)eff45_char_table_004,  /* 4 */
    (u32)eff45_char_table_005,  /* 5 */
    (u32)eff45_char_table_006,  /* 6 */
    (u32)eff45_char_table_007,  /* 7 */
    (u32)eff45_char_table_008,  /* 8 */
    (u32)eff45_char_table_009,  /* 9 */
    (u32)eff45_char_table_010,  /* 10 */
    (u32)eff45_char_table_011,  /* 11 */
    (u32)eff45_char_table_012,  /* 12 */
    (u32)eff45_char_table_013,  /* 13 */
    (u32)eff45_char_table_014,  /* 14 */
    (u32)eff45_char_table_015,  /* 15 */
};

extern const u16 eff56_char_table_000[], eff56_char_table_001[], eff56_char_table_002[], eff56_char_table_003[],
                 eff56_char_table_004[], eff56_char_table_005[];

/* eff56_char_table: 6 entries (no closing 0: the next table follows); used by eff56 */
const u32 eff56_char_table[6] = {
    (u32)eff56_char_table_000,  /* 0 */
    (u32)eff56_char_table_001,  /* 1 */
    (u32)eff56_char_table_002,  /* 2 */
    (u32)eff56_char_table_003,  /* 3 */
    (u32)eff56_char_table_004,  /* 4 */
    (u32)eff56_char_table_005,  /* 5 */
};

extern const u16 eff54_char_table_000[], eff54_char_table_001[], eff54_char_table_002[], eff54_char_table_003[],
                 eff54_char_table_004[];

/* eff54_char_table: 5 entries; used by EFF53, EFF54 */
const u32 eff54_char_table[6] = {
    (u32)eff54_char_table_000,  /* 0 */
    (u32)eff54_char_table_001,  /* 1 */
    (u32)eff54_char_table_002,  /* 2 */
    (u32)eff54_char_table_003,  /* 3 */
    (u32)eff54_char_table_004,  /* 4 */
    0
};

/* script: 0 */
const u16 eff45_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_000[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F60),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff45_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_001[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F61),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff45_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_002[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F62),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff45_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_003[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F63),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff45_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_004[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F64),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 eff45_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_005[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F6F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 eff45_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_006[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F70),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 eff45_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_007[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F71),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 eff45_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_008[44] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F65),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F66),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F67),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F68),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F69),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F6A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F6B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F6C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F6D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4F6E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 eff45_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_009[56] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F72),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F73),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F74),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F75),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F76),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F77),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F78),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F79),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F7A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F7B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F7C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F7D),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4F7D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 eff45_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_010[56] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FD0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FD1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FD2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FD3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FD4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FD5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FD6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FD7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FD8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FD9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FDA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FDB),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4FDB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 eff45_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_011[56] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F8A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F8B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F8C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F8D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F8E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F8F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F90),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F91),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F92),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F93),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F94),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4F95),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4F95),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 eff45_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_012[56] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FDC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FDD),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FDE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FDF),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FE0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FE1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FE2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FE3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FE4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FE5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FE6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4FE7),
    L2(4, 1, 0, 0, 0, 0, 0, 0x4FE7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 eff45_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_013[44] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x4F61),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4FA2),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4FA3),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4FA4),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4FA5),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4FA6),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4FA7),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4FA8),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4FA9),
    L2(5, 0, 0, 0, 0, 0, 0, 0x4FAA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 eff45_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_014[8] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x4FE8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 eff45_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff45_char_table_015[8] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x4FE9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff56_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff56_char_table_000[32] = {
    L2(14, 0, 0, 0, 0, 0, 0, 0x5060),
    L2(14, 0, 0, 0, 0, 0, 0, 0x5061),
    L2(14, 0, 0, 0, 0, 0, 0, 0x5062),
    L2(14, 0, 0, 0, 0, 0, 0, 0x5063),
    L2(14, 0, 0, 0, 0, 0, 0, 0x5064),
    L2(14, 0, 0, 0, 0, 0, 0, 0x5065),
    L2(14, 0, 0, 0, 0, 0, 0, 0x5066),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff56_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff56_char_table_001[32] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x5060),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5061),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5062),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5063),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5064),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5065),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5066),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff56_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff56_char_table_002[32] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x5059),
    L2(8, 0, 0, 0, 0, 0, 0, 0x505A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x505B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x505C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x505D),
    L2(7, 0, 0, 0, 0, 0, 0, 0x505E),
    L2(7, 0, 0, 0, 0, 0, 0, 0x505F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff56_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff56_char_table_003[36] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5052),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5053),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5054),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5055),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5056),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5057),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5058),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5052),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff56_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff56_char_table_004[32] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x504B),
    L2(7, 0, 0, 0, 0, 0, 0, 0x504C),
    L2(7, 0, 0, 0, 0, 0, 0, 0x504D),
    L2(7, 0, 0, 0, 0, 0, 0, 0x504E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x504F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5050),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5051),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 eff56_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff56_char_table_005[52] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x504B),
    L2(7, 0, 0, 0, 0, 0, 0, 0x504C),
    L2(7, 0, 0, 0, 0, 0, 0, 0x504D),
    L2(7, 0, 0, 0, 0, 0, 0, 0x504E),
    L2(7, 0, 0, 0, 0, 0, 0, 0x504F),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5050),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5051),
    L2(7, 0, 0, 0, 0, 0, 0, 0x504B),
    L2(7, 0, 0, 0, 0, 0, 0, 0x504C),
    L2(7, 0, 0, 0, 0, 0, 0, 0x504D),
    L2(7, 0, 0, 0, 0, 0, 0, 0x504E),
    L2(7, 0, 0, 0, 0, 0, 0, 0x504F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff54_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff54_char_table_000[152] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5018),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5019),
    L2(6, 0, 0, 0, 0, 0, 0, 0x501A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x501B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x501C),
    L2(6, 0, 0, 0, 0, 0, 0, 0x501D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x501E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x501F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5020),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5021),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5022),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5023),
    L2(6, 1, 0, 0, 0, 0, 0, 0x5023),
    CMD(CM_EXEC, 4, 0, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5024),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5025),
    L2(1, 2, 0, 0, 0, 0, 0, 0x5025),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5026),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5027),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5028),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5029),
    L2(9, 0, 0, 0, 0, 0, 0, 0x502A),
    L2(9, 0, 0, 0, 0, 0, 0, 0x502B),
    L2(9, 0, 0, 0, 0, 0, 0, 0x502C),
    L2(9, 0, 0, 0, 0, 0, 0, 0x502D),
    L2(9, 0, 0, 0, 0, 0, 0, 0x502E),
    L2(9, 0, 0, 0, 0, 0, 0, 0x502F),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5030),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5031),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5032),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5033),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5034),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5035),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5036),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5037),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5038),
    L2(2, 1, 0, 0, 0, 0, 0, 0x5038),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff54_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff54_char_table_001[32] = {
    L2(9, 0, 0, 0, 0, 0, 0, 0x5039),
    L2(10, 0, 0, 0, 0, 0, 0, 0x503A),
    L2(9, 0, 0, 0, 0, 0, 0, 0x503B),
    L2(10, 0, 0, 0, 0, 0, 0, 0x503C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x503D),
    L2(11, 0, 0, 0, 0, 0, 0, 0x503E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x503F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff54_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff54_char_table_002[16] = {
    L2(16, 0, 0, 0, 0, 0, 0, 0x5048),
    L2(16, 0, 0, 0, 0, 0, 0, 0x5049),
    L2(16, 0, 0, 0, 0, 0, 0, 0x504A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff54_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff54_char_table_003[28] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x5041),
    L2(24, 0, 0, 0, 0, 0, 0, 0x5043),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5044),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5045),
    L2(2, 2, 0, 0, 0, 0, 0, 0x5045),
    L2(250, 1, 0, 0, 0, 0, 0, 0x5045),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff54_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff54_char_table_004[80] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x5039),
    L2(6, 0, 0, 0, 0, 0, 0, 0x503A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x503B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x503C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x503D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x503E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x503F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5040),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5039),
    L2(4, 0, 0, 0, 0, 0, 0, 0x503A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x503B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x503C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x503D),
    L2(5, 0, 0, 0, 0, 0, 0, 0x503E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x503F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5040),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5039),
    L2(5, 0, 0, 0, 0, 0, 0, 0x503A),
    L2(200, 0, 0, 0, 0, 0, 0, 0x503B),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 eff86_char_table_000[], eff86_char_table_001[], eff86_char_table_002[], eff86_char_table_003[],
                 eff86_char_table_004[], eff86_char_table_005[], eff86_char_table_006[], eff86_char_table_007[],
                 eff86_char_table_008[], eff86_char_table_009[], eff86_char_table_010[], eff86_char_table_011[],
                 eff86_char_table_012[], eff86_char_table_013[], eff86_char_table_014[], eff86_char_table_015[],
                 eff86_char_table_016[], eff86_char_table_017[], eff86_char_table_018[], eff86_char_table_019[],
                 eff86_char_table_020[];

/* eff86_char_table: 21 entries; debug viewer: AFRICA 2; used by EFF85, EFF86, dbg_work, eff05 */
const u32 eff86_char_table[22] = {
    (u32)eff86_char_table_000,  /* 0 */
    (u32)eff86_char_table_001,  /* 1 */
    (u32)eff86_char_table_002,  /* 2 */
    (u32)eff86_char_table_003,  /* 3 */
    (u32)eff86_char_table_004,  /* 4 */
    (u32)eff86_char_table_005,  /* 5 */
    (u32)eff86_char_table_006,  /* 6 */
    (u32)eff86_char_table_007,  /* 7 */
    (u32)eff86_char_table_008,  /* 8 */
    (u32)eff86_char_table_009,  /* 9 */
    (u32)eff86_char_table_010,  /* 10 */
    (u32)eff86_char_table_011,  /* 11 */
    (u32)eff86_char_table_012,  /* 12 */
    (u32)eff86_char_table_013,  /* 13 */
    (u32)eff86_char_table_014,  /* 14 */
    (u32)eff86_char_table_015,  /* 15 */
    (u32)eff86_char_table_016,  /* 16 */
    (u32)eff86_char_table_017,  /* 17 */
    (u32)eff86_char_table_018,  /* 18 */
    (u32)eff86_char_table_019,  /* 19 */
    (u32)eff86_char_table_020,  /* 20 */
    0
};

/* script: 0 */
const u16 eff86_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_000[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x50B0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff86_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_001[68] = {
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B1),
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B2),
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B3),
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B4),
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B5),
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B6),
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B7),
    L2(25, 0, 0, 0, 0, 0, 0, 0x50B8),
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B7),
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B6),
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B5),
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B4),
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B3),
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B2),
    L2(7, 0, 0, 0, 0, 0, 0, 0x50B1),
    L2(200, 0, 0, 0, 0, 0, 0, 0x50B1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff86_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_002[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5110),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff86_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_003[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5111),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 18 */
const u16 eff86_char_table_018_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_018[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5129),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff86_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_004[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x50C0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 eff86_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_005[132] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x5112),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5123),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5124),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5125),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5126),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5127),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5128),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5113),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5114),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5115),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5116),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5117),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5118),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5119),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5122),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5119),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5122),
    L2(20, 0, 0, 0, 0, 0, 0, 0x5119),
    L2(20, 0, 0, 0, 0, 0, 0, 0x5118),
    L2(10, 0, 0, 0, 0, 0, 0, 0x511A),
    L2(10, 0, 0, 0, 0, 0, 0, 0x511B),
    L2(10, 0, 0, 0, 0, 0, 0, 0x511C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x511D),
    L2(10, 0, 0, 0, 0, 0, 0, 0x511E),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5128),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5127),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5126),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5128),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5112),
    L2(10, 0, 0, 0, 0, 0, 0, 0x511F),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5120),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5121),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 eff86_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_006[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5150),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 eff86_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_007[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5151),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 eff86_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_008[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5152),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 eff86_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_009[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5153),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 eff86_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_010[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5298),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 eff86_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_011[140] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x5156),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5157),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5158),
    L2(5, 0, 0, 0, 0, 0, 0, 0x5159),
    L2(5, 0, 0, 0, 0, 0, 0, 0x515A),
    L2(5, 0, 0, 0, 0, 0, 0, 0x515B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x515C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x515D),
    CMD(CM_FOR, 0, 0, 3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x515E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x515F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5160),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5161),
    CMD(CM_NEX, 0, 0, 0),
    L2(5, 0, 0, 0, 0, 0, 0, 0x515E),
    L2(5, 0, 0, 0, 0, 0, 0, 0x515D),
    CMD(CM_FOR, 0, 0, 2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5156),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5157),
    L2(5, 0, 0, 0, 0, 0, 0, 0x5158),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5159),
    L2(5, 0, 0, 0, 0, 0, 0, 0x515A),
    L2(5, 0, 0, 0, 0, 0, 0, 0x515B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x515C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x515D),
    CMD(CM_NEX, 0, 0, 0),
    L2(5, 0, 0, 0, 0, 0, 0, 0x515E),
    L2(5, 0, 0, 0, 0, 0, 0, 0x515F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x5160),
    L2(5, 0, 0, 0, 0, 0, 0, 0x515F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x515E),
    L2(5, 0, 0, 0, 0, 0, 0, 0x515F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x5160),
    L2(5, 0, 0, 0, 0, 0, 0, 0x5161),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 eff86_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_012[180] = {
    CMD(CM_FOR2, 0, 0, 2),
    CMD(CM_FOR, 0, 0, 4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5167),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5166),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5165),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5166),
    CMD(CM_NEX, 0, 0, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5166),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5168),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5169),
    L2(5, 0, 0, 0, 0, 0, 0, 0x516A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5169),
    L2(6, 0, 0, 0, 0, 0, 0, 0x516B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x516C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5168),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5169),
    L2(6, 0, 0, 0, 0, 0, 0, 0x516A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5169),
    L2(4, 0, 0, 0, 0, 0, 0, 0x516B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x516C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x516D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x516E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x516F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5170),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5171),
    L2(5, 0, 0, 0, 0, 0, 0, 0x516E),
    L2(5, 0, 0, 0, 0, 0, 0, 0x516D),
    L2(5, 0, 0, 0, 0, 0, 0, 0x516B),
    L2(5, 0, 0, 0, 0, 0, 0, 0x5166),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5167),
    L2(5, 0, 0, 0, 0, 0, 0, 0x5166),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5165),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5166),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5167),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5166),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5165),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5166),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5167),
    CMD(CM_NEX2, 0, 0, 0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5172),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5173),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5174),
    L2(30, 0, 0, 0, 0, 0, 0, 0x5175),
    L2(9, 1, 0, 0, 0, 0, 0, 0x5175),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 eff86_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_013[220] = {
    CMD(CM_FOR2, 0, 0, 2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5178),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5178),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(6, 0, 0, 0, 0, 0, 0, 0x517A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5178),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(6, 0, 0, 0, 0, 0, 0, 0x517A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5180),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5182),
    L2(5, 0, 0, 0, 0, 0, 0, 0x5183),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5184),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5182),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5183),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5184),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5183),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5182),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5181),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5180),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5181),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5182),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5183),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5184),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5183),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5182),
    L2(5, 0, 0, 0, 0, 0, 0, 0x517B),
    L2(5, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(5, 0, 0, 0, 0, 0, 0, 0x517A),
    L2(5, 0, 0, 0, 0, 0, 0, 0x5179),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5181),
    L2(5, 0, 0, 0, 0, 0, 0, 0x517B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x517D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x517E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5181),
    L2(2, 0, 0, 0, 0, 0, 0, 0x517D),
    L2(6, 0, 0, 0, 0, 0, 0, 0x517E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x517F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5181),
    CMD(CM_NEX2, 0, 0, 0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5187),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5186),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5188),
    L2(30, 0, 0, 0, 0, 0, 0, 0x5189),
    L2(9, 1, 0, 0, 0, 0, 0, 0x5189),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 eff86_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_014[220] = {
    L2(48, 0, 0, 0, 0, 0, 0, 0x518B),
    L2(10, 0, 0, 0, 0, 0, 0, 0x518C),
    L2(10, 0, 0, 0, 0, 0, 0, 0x518D),
    L2(10, 0, 0, 0, 0, 0, 0, 0x518E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x518F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5190),
    L2(22, 0, 0, 0, 0, 0, 0, 0x5191),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5190),
    CMD(CM_FOR, 0, 0, 2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x518F),
    L2(7, 0, 0, 0, 0, 0, 0, 0x518E),
    CMD(CM_NEX, 0, 0, 0),
    L2(22, 0, 0, 0, 0, 0, 0, 0x518D),
    L2(7, 0, 0, 0, 0, 0, 0, 0x518C),
    CMD(CM_FOR, 0, 0, 3),
    L2(7, 0, 0, 0, 0, 0, 0, 0x518B),
    L2(7, 0, 0, 0, 0, 0, 0, 0x518C),
    CMD(CM_NEX, 0, 0, 0),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5190),
    L2(21, 0, 0, 0, 0, 0, 0, 0x518E),
    L2(7, 0, 0, 0, 0, 0, 0, 0x518F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5192),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5193),
    L2(67, 0, 0, 0, 0, 0, 0, 0x5194),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5195),
    L2(96, 0, 0, 0, 0, 0, 0, 0x5196),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5193),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5192),
    L2(7, 0, 0, 0, 0, 0, 0, 0x518F),
    L2(21, 0, 0, 0, 0, 0, 0, 0x518E),
    L2(7, 0, 0, 0, 0, 0, 0, 0x518D),
    L2(7, 0, 0, 0, 0, 0, 0, 0x518C),
    L2(31, 0, 0, 0, 0, 0, 0, 0x518B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5197),
    CMD(CM_FOR, 0, 0, 2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5198),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5199),
    CMD(CM_NEX, 0, 0, 0),
    L2(46, 0, 0, 0, 0, 0, 0, 0x519A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x519B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x519A),
    L2(12, 0, 0, 0, 0, 0, 0, 0x519B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5199),
    L2(9, 0, 0, 0, 0, 0, 0, 0x5198),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5199),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5198),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5199),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5198),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5197),
    L2(3, 1, 0, 0, 0, 0, 0, 0x5197),
    CMD(CM_FOR, 0, 0, 2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x518F),
    L2(7, 0, 0, 0, 0, 0, 0, 0x518E),
    CMD(CM_NEX, 0, 0, 0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 eff86_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_015[160] = {
    L2(41, 0, 0, 0, 0, 0, 0, 0x5280),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5281),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5282),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5283),
    L2(32, 0, 0, 0, 0, 0, 0, 0x5285),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5286),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5287),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5288),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5287),
    CMD(CM_FOR, 0, 0, 2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5286),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5285),
    L2(31, 0, 0, 0, 0, 0, 0, 0x5284),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5285),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5286),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5287),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5288),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5287),
    CMD(CM_NEX, 0, 0, 0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5286),
    L2(31, 0, 0, 0, 0, 0, 0, 0x5285),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5284),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5283),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5282),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5281),
    L2(31, 0, 0, 0, 0, 0, 0, 0x5280),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5289),
    L2(3, 0, 0, 0, 0, 0, 0, 0x528A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x528B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x528C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x528D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x528E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x528F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5290),
    L2(53, 0, 0, 0, 0, 0, 0, 0x5291),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5292),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5293),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5294),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5295),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16 */
const u16 eff86_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_016[236] = {
    L2(30, 0, 0, 0, 0, 0, 0, 0x51D4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D1),
    L2(30, 0, 0, 0, 0, 0, 0, 0x51D0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D5),
    L2(30, 0, 0, 0, 0, 0, 0, 0x51D4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D8),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D9),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x51DB),
    L2(8, 0, 0, 0, 0, 0, 0, 0x51E0),
    L2(12, 0, 0, 0, 0, 0, 0, 0x51E1),
    CMD(CM_FOR, 0, 0, 2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x51E0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x51DB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DF),
    CMD(CM_NEX, 0, 0, 0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x51DE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x51DD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51E0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DF),
    CMD(CM_FOR, 0, 0, 2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51E0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x51DF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x51DE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x51DD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51E0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DF),
    CMD(CM_NEX, 0, 0, 0),
    L2(14, 0, 0, 0, 0, 0, 0, 0x51DE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x51DF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51E0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51DA),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D9),
    L2(2, 0, 0, 0, 0, 0, 0, 0x51D8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x51D7),
    L2(7, 0, 0, 0, 0, 0, 0, 0x51D6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x51D1),
    L2(43, 0, 0, 0, 0, 0, 0, 0x51D0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 17 */
const u16 eff86_char_table_017_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_017[452] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x5210),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5211),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5212),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5213),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5214),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5215),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5216),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5217),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5218),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5219),
    L2(3, 0, 0, 0, 0, 0, 0, 0x521A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x521B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x521C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x521D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x521E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x521F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5220),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5221),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5222),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5223),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5224),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5225),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5226),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5227),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5228),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5229),
    L2(3, 0, 0, 0, 0, 0, 0, 0x522A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x522B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x522C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x522D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x522E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x522F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5230),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5231),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5232),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5233),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5234),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5235),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5236),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5237),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5238),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5239),
    L2(3, 0, 0, 0, 0, 0, 0, 0x523A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x523B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x523C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x523D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x523E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x523F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5240),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5241),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5242),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5243),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5244),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5245),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5246),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5247),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5248),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5249),
    L2(3, 0, 0, 0, 0, 0, 0, 0x524A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x524B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x524C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x524D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x524E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x524F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5250),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5251),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5252),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5253),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5254),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5255),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5256),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5257),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5258),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5259),
    L2(3, 0, 0, 0, 0, 0, 0, 0x525A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x525B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x525C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x525D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x525E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x525F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5260),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5261),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5262),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5263),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5264),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5265),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5266),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5267),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5268),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5269),
    L2(3, 0, 0, 0, 0, 0, 0, 0x526A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x526B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x526C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x526D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x526E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x526F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5270),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5271),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5272),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5273),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5274),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5275),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5276),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5277),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5278),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5279),
    L2(3, 0, 0, 0, 0, 0, 0, 0x527A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x527B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x527C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x527D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x527E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x527F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 19 */
const u16 eff86_char_table_019_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_019[24] = {
    L2(30, 0, 0, 0, 0, 0, 0, 0x5175),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5174),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5173),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5172),
    L2(2, 1, 0, 0, 0, 0, 0, 0x5172),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 20 */
const u16 eff86_char_table_020_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff86_char_table_020[24] = {
    L2(30, 0, 0, 0, 0, 0, 0, 0x5189),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5188),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5186),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5187),
    L2(2, 1, 0, 0, 0, 0, 0, 0x5187),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 eff09_char_table_000[], eff09_char_table_001[], eff09_char_table_002[], eff09_char_table_003[],
                 eff09_char_table_004[], eff09_char_table_005[], eff09_char_table_006[];

/* eff09_char_table: 7 entries; used by EFF09 */
const u32 eff09_char_table[8] = {
    (u32)eff09_char_table_000,  /* 0 */
    (u32)eff09_char_table_001,  /* 1 */
    (u32)eff09_char_table_002,  /* 2 */
    (u32)eff09_char_table_003,  /* 3 */
    (u32)eff09_char_table_004,  /* 4 */
    (u32)eff09_char_table_005,  /* 5 */
    (u32)eff09_char_table_006,  /* 6 */
    0
};

/* script: 0 */
const u16 eff09_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff09_char_table_000[112] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF8),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CF9),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CFA),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CFB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CFC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CFD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4CFF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D00),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D01),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D02),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D03),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D04),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D05),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D06),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D07),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D08),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D09),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D0A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D0B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D0C),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4D0C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff09_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff09_char_table_001[28] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D83),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D84),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D85),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D86),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D87),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4D87),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff09_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff09_char_table_002[36] = {
    CMD(CM_FOR, 0, 0, 2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D88),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D89),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D8A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D8B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x4D8C),
    CMD(CM_NEX, 0, 0, 0),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4D8C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff09_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff09_char_table_003[20] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x4D5B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4D5C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x4D5D),
    L2(2, 1, 0, 0, 0, 0, 0, 0x4D5D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 eff09_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff09_char_table_004[36] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x4190),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4191),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4192),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4193),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4194),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4195),
    L2(6, 0, 0, 0, 0, 0, 0, 0x4196),
    CMD(CM_ROA, 0, 0, 0),
    CMD(CM_EXEC, 3, 0, 0),
};

/* script: 5 */
const u16 eff09_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff09_char_table_005[32] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x6D34),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6D35),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6D36),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6D37),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6D38),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6D39),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6D39),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 eff09_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff09_char_table_006[40] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x6D3A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6D3B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6D3C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6D3D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6D3E),
    L2(3, 2, 0, 0, 0, 0, 0, 0x6D3F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6D40),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6D41),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6D41),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 brz_char_table_000[], brz_char_table_001[], brz_char_table_002[], brz_char_table_003[],
                 brz_char_table_004[], brz_char_table_005[], brz_char_table_006[], brz_char_table_007[],
                 brz_char_table_008[], brz_char_table_009[], brz_char_table_010[], brz_char_table_011[],
                 brz_char_table_012[], brz_char_table_013[], brz_char_table_014[], brz_char_table_015[],
                 brz_char_table_016[], brz_char_table_017[], brz_char_table_018[], brz_char_table_019[],
                 brz_char_table_020[], brz_char_table_021[], brz_char_table_022[], brz_char_table_023[],
                 brz_char_table_024[], brz_char_table_025[], brz_char_table_026[], brz_char_table_027[],
                 brz_char_table_028[], brz_char_table_029[], brz_char_table_030[], brz_char_table_031[],
                 brz_char_table_032[], brz_char_table_033[], brz_char_table_034[], brz_char_table_035[],
                 brz_char_table_036[], brz_char_table_037[], brz_char_table_038[], brz_char_table_039[],
                 brz_char_table_040[], brz_char_table_041[], brz_char_table_042[], brz_char_table_043[],
                 brz_char_table_044[], brz_char_table_045[], brz_char_table_046[], brz_char_table_047[],
                 brz_char_table_048[], brz_char_table_049[], brz_char_table_050[], brz_char_table_051[];

/* brz_char_table: 52 entries (no closing 0: the next table follows); debug viewer: BRAZIL; used by EFF55, EFF71, EFF72, EFF74, dbg_work, eff05, eff73 */
const u32 brz_char_table[52] = {
    (u32)brz_char_table_000,  /* 0 */
    (u32)brz_char_table_001,  /* 1 */
    (u32)brz_char_table_002,  /* 2 */
    (u32)brz_char_table_003,  /* 3 */
    (u32)brz_char_table_004,  /* 4 */
    (u32)brz_char_table_005,  /* 5 */
    (u32)brz_char_table_006,  /* 6 */
    (u32)brz_char_table_007,  /* 7 */
    (u32)brz_char_table_008,  /* 8 */
    (u32)brz_char_table_009,  /* 9 */
    (u32)brz_char_table_010,  /* 10 */
    (u32)brz_char_table_011,  /* 11 */
    (u32)brz_char_table_012,  /* 12 */
    (u32)brz_char_table_013,  /* 13 */
    (u32)brz_char_table_014,  /* 14 */
    (u32)brz_char_table_015,  /* 15 */
    (u32)brz_char_table_016,  /* 16 */
    (u32)brz_char_table_017,  /* 17 */
    (u32)brz_char_table_018,  /* 18 */
    (u32)brz_char_table_019,  /* 19 */
    (u32)brz_char_table_020,  /* 20 */
    (u32)brz_char_table_021,  /* 21 */
    (u32)brz_char_table_022,  /* 22 */
    (u32)brz_char_table_023,  /* 23 */
    (u32)brz_char_table_024,  /* 24 */
    (u32)brz_char_table_025,  /* 25 */
    (u32)brz_char_table_026,  /* 26 */
    (u32)brz_char_table_027,  /* 27 */
    (u32)brz_char_table_028,  /* 28 */
    (u32)brz_char_table_029,  /* 29 */
    (u32)brz_char_table_030,  /* 30 */
    (u32)brz_char_table_031,  /* 31 */
    (u32)brz_char_table_032,  /* 32 */
    (u32)brz_char_table_033,  /* 33 */
    (u32)brz_char_table_034,  /* 34 */
    (u32)brz_char_table_035,  /* 35 */
    (u32)brz_char_table_036,  /* 36 */
    (u32)brz_char_table_037,  /* 37 */
    (u32)brz_char_table_038,  /* 38 */
    (u32)brz_char_table_039,  /* 39 */
    (u32)brz_char_table_040,  /* 40 */
    (u32)brz_char_table_041,  /* 41 */
    (u32)brz_char_table_042,  /* 42 */
    (u32)brz_char_table_043,  /* 43 */
    (u32)brz_char_table_044,  /* 44 */
    (u32)brz_char_table_045,  /* 45 */
    (u32)brz_char_table_046,  /* 46 */
    (u32)brz_char_table_047,  /* 47 */
    (u32)brz_char_table_048,  /* 48 */
    (u32)brz_char_table_049,  /* 49 */
    (u32)brz_char_table_050,  /* 50 */
    (u32)brz_char_table_051,  /* 51 */
};

extern const u16 eff90_char_table_000[];

/* eff90_char_table: 1 entries; used by eff90 */
const u32 eff90_char_table[2] = {
    (u32)eff90_char_table_000,  /* 0 */
    0
};

/* script: 0 */
const u16 brz_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_000[68] = {
    CMD(CM_FOR, 0, 0, 3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53C0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53C1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53C2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53C3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53C4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53C5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53C6),
    CMD(CM_NEX, 0, 0, 0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53C7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53C8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53C9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53CA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53CB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53CC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53CD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 brz_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_001[32] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x53C7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53C8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53C9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53CA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53CB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53CC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53CD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 brz_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_002[68] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x53CE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53CF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53D8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53D9),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53DA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53DB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53CE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53CF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53D0),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53D1),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53D2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53D3),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53D4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53D5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53D6),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53D7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 brz_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_003[52] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x53DC),
    L2(5, 0, 0, 0, 0, 0, 0, 0x53DD),
    L2(5, 0, 0, 0, 0, 0, 0, 0x53DE),
    L2(5, 0, 0, 0, 0, 0, 0, 0x53DF),
    L2(5, 0, 0, 0, 0, 0, 0, 0x53E0),
    L2(5, 0, 0, 0, 0, 0, 0, 0x53E1),
    L2(5, 0, 0, 0, 0, 0, 0, 0x53E2),
    L2(5, 0, 0, 0, 0, 0, 0, 0x53E3),
    L2(5, 0, 0, 0, 0, 0, 0, 0x53E4),
    L2(5, 0, 0, 0, 0, 0, 0, 0x53E5),
    L2(5, 0, 0, 0, 0, 0, 0, 0x53E6),
    L2(5, 0, 0, 0, 0, 0, 0, 0x53E7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 brz_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_004[40] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x53E8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53E9),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53EA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53EB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53EC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53ED),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53EE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53EF),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53F0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 brz_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_005[40] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x53F1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53F2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53F3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53F4),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53F5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53F6),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53F7),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53F8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x53F9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 brz_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_006[40] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x53FA),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53FB),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53FC),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53FD),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53FE),
    L2(6, 0, 0, 0, 0, 0, 0, 0x53FF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5400),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5401),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5402),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 brz_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_007[8] = {
    L2(26, 0, 0, 0, 0, 0, 0, 0x5403),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 brz_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_008[48] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x5404),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5405),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5406),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5407),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5408),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5409),
    L2(4, 0, 0, 0, 0, 0, 0, 0x540A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x540B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x540C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x540D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x540E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 brz_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_009[12] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x540F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x5410),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 brz_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_010[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x5411),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 brz_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_011[32] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x5412),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5413),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5414),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5415),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5416),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5417),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5418),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 brz_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_012[188] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x5419),
    L2(8, 0, 0, 0, 0, 0, 0, 0x541A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x541B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x541C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x541D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x541E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x541F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5420),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5421),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5422),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5423),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5424),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5425),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5426),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5427),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5428),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5429),
    L2(8, 0, 0, 0, 0, 0, 0, 0x542A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x542B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x542C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x542D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x542E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x542F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5430),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5431),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5432),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5433),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5434),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5435),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5436),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5437),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5438),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5439),
    L2(8, 0, 0, 0, 0, 0, 0, 0x543A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x543B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x543C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x543D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x543E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x543F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5440),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5441),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5442),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5443),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5444),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5445),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5446),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 brz_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_013[108] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x54E8),
    L2(5, 0, 0, 0, 0, 0, 0, 0x54E9),
    L2(29, 0, 0, 0, 0, 0, 0, 0x54EA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x54E9),
    L2(9, 0, 0, 0, 0, 0, 0, 0x54E8),
    CMD(CM_FOR, 0, 0, 3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x54EB),
    L2(26, 0, 0, 0, 0, 0, 0, 0x54EC),
    CMD(CM_NEX, 0, 0, 0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x54ED),
    L2(3, 0, 0, 0, 0, 0, 0, 0x54EE),
    L2(3, 0, 0, 0, 0, 0, 0, 0x54EF),
    CMD(CM_FOR, 0, 0, 3),
    L2(60, 0, 0, 0, 0, 0, 0, 0x54F0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x54F1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x54F2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x54F1),
    L2(60, 0, 0, 0, 0, 0, 0, 0x54F0),
    CMD(CM_NEX, 0, 0, 0),
    L2(5, 0, 0, 0, 0, 0, 0, 0x54F2),
    L2(6, 0, 0, 0, 0, 0, 0, 0x54F3),
    L2(5, 0, 0, 0, 0, 0, 0, 0x54F4),
    L2(56, 0, 0, 0, 0, 0, 0, 0x54EC),
    L2(136, 0, 0, 0, 0, 0, 0, 0x54EB),
    L2(3, 0, 0, 0, 0, 0, 0, 0x54E8),
    L2(6, 0, 0, 0, 0, 0, 0, 0x54E9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 brz_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_014[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x54F9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 brz_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_015[68] = {
    L2(145, 1, 0, 0, 0, 0, 0, 0x54FA),
    L2(10, 1, 0, 0, 0, 0, 0, 0x54FB),
    L2(11, 1, 0, 0, 0, 0, 0, 0x54FC),
    L2(176, 1, 0, 0, 0, 0, 0, 0x54FD),
    L2(11, 1, 0, 0, 0, 0, 0, 0x54FC),
    L2(10, 1, 0, 0, 0, 0, 0, 0x54FB),
    CMD(CM_FOR, 0, 0, 3),
    L2(12, 1, 0, 0, 0, 0, 0, 0x54FB),
    L2(12, 1, 0, 0, 0, 0, 0, 0x54FC),
    L2(12, 1, 0, 0, 0, 0, 0, 0x54FD),
    CMD(CM_NEX, 0, 0, 0),
    L2(10, 1, 0, 0, 0, 0, 0, 0x54FB),
    L2(11, 1, 0, 0, 0, 0, 0, 0x54FC),
    L2(106, 1, 0, 0, 0, 0, 0, 0x54FD),
    L2(11, 1, 0, 0, 0, 0, 0, 0x54FC),
    L2(10, 1, 0, 0, 0, 0, 0, 0x54FB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16 */
const u16 brz_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_016[16] = {
    L2(24, 0, 0, 0, 0, 0, 0, 0x54FF),
    L2(6, 0, 0, 0, 0, 0, 0, 0x54FE),
    L2(6, 1, 0, 0, 0, 0, 0, 0x54FE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 17 */
const u16 brz_char_table_017_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_017[108] = {
    L2(103, 2, 0, 0, 0, 0, 0, 0x5500),
    L2(10, 2, 0, 0, 0, 0, 0, 0x5501),
    L2(7, 2, 0, 0, 0, 0, 0, 0x5502),
    L2(5, 2, 0, 0, 0, 0, 0, 0x5501),
    L2(7, 2, 0, 0, 0, 0, 0, 0x5502),
    L2(7, 2, 0, 0, 0, 0, 0, 0x5501),
    L2(6, 2, 0, 0, 0, 0, 0, 0x5502),
    L2(7, 2, 0, 0, 0, 0, 0, 0x5501),
    L2(36, 2, 0, 0, 0, 0, 0, 0x5502),
    L2(4, 2, 0, 0, 0, 0, 0, 0x5503),
    L2(5, 2, 0, 0, 0, 0, 0, 0x5504),
    L2(5, 2, 0, 0, 0, 0, 0, 0x5505),
    L2(19, 2, 0, 0, 0, 0, 0, 0x5506),
    L2(23, 0, 0, 0, 0, 0, 0, 0x5507),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5508),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5509),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5507),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5508),
    L2(15, 0, 0, 0, 0, 0, 0, 0x5509),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5507),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5508),
    L2(14, 0, 0, 0, 0, 0, 0, 0x5509),
    L2(10, 0, 0, 0, 0, 0, 0, 0x550A),
    L2(12, 0, 0, 0, 0, 0, 0, 0x550B),
    L2(46, 0, 0, 0, 0, 0, 0, 0x5507),
    CMD(CM_END, 0, 0, 14),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 18 */
const u16 brz_char_table_018_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_018[68] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x550C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x550D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x550E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x550F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x5510),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5511),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5512),
    L2(7, 0, 0, 0, 0, 0, 0, 0x5513),
    L2(39, 0, 0, 0, 0, 0, 0, 0x5514),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5515),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5516),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5515),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5516),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5515),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5516),
    L2(200, 0, 0, 0, 0, 0, 0, 0x5514),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 19 */
const u16 brz_char_table_019_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_019[76] = {
    L2(39, 0, 0, 0, 0, 0, 0, 0x5517),
    CMD(CM_FOR, 0, 0, 2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5518),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5519),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5518),
    L2(18, 0, 0, 0, 0, 0, 0, 0x551A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5517),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5519),
    L2(8, 0, 0, 0, 0, 0, 0, 0x551A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x551B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x551E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x551D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x551E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x551D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x551C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x551B),
    L2(33, 0, 0, 0, 0, 0, 0, 0x5517),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 20 */
const u16 brz_char_table_020_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_020[200] = {
    CMD(CM_FOR, 0, 0, 3),
    L2(80, 0, 0, 0, 0, 0, 0, 0x5525),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5526),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5527),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5528),
    L2(88, 0, 0, 0, 0, 0, 0, 0x5529),
    L2(5, 0, 0, 0, 0, 0, 0, 0x552A),
    L2(5, 0, 0, 0, 0, 0, 0, 0x552B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x552A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x552B),
    L2(18, 0, 0, 0, 0, 0, 0, 0x552A),
    L2(230, 0, 0, 0, 0, 0, 0, 0x5529),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5528),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5527),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5526),
    L2(140, 0, 0, 0, 0, 0, 0, 0x5525),
    L2(4, 0, 0, 0, 0, 0, 0, 0x552E),
    L2(20, 0, 0, 0, 0, 0, 0, 0x552F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x552E),
    L2(92, 0, 0, 0, 0, 0, 0, 0x552F),
    L2(140, 0, 0, 0, 0, 0, 0, 0x5525),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5526),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5527),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5528),
    L2(60, 0, 0, 0, 0, 0, 0, 0x5529),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5528),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5527),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5526),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5527),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5528),
    L2(168, 0, 0, 0, 0, 0, 0, 0x5529),
    L2(7, 0, 0, 0, 0, 0, 0, 0x552A),
    L2(7, 0, 0, 0, 0, 0, 0, 0x552B),
    L2(7, 0, 0, 0, 0, 0, 0, 0x552A),
    L2(7, 0, 0, 0, 0, 0, 0, 0x552B),
    L2(7, 0, 0, 0, 0, 0, 0, 0x552A),
    L2(50, 0, 0, 0, 0, 0, 0, 0x5529),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5528),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5527),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5526),
    L2(178, 0, 0, 0, 0, 0, 0, 0x5525),
    L2(4, 0, 0, 0, 0, 0, 0, 0x552E),
    L2(30, 0, 0, 0, 0, 0, 0, 0x552F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x552E),
    L2(32, 0, 0, 0, 0, 0, 0, 0x552F),
    CMD(CM_NEX, 0, 0, 0),
    L2(5, 0, 0, 0, 0, 0, 0, 0x552C),
    L2(5, 0, 0, 0, 0, 0, 0, 0x552D),
    L2(5, 1, 0, 0, 0, 0, 0, 0x552D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 21 */
const u16 brz_char_table_021_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_021[28] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x551F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5520),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5521),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5522),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5523),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5524),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 22 */
const u16 brz_char_table_022_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_022[24] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x5526),
    L2(2, 0, 0, 0, 0, 0, 0, 0x5527),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5528),
    L2(29, 0, 0, 0, 0, 0, 0, 0x5529),
    L2(29, 1, 0, 0, 0, 0, 0, 0x5529),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 23 */
const u16 brz_char_table_023_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_023[28] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x552A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x552B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x552A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x552B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x552A),
    L2(4, 1, 0, 0, 0, 0, 0, 0x552B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 25 */
const u16 brz_char_table_025_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_025[16] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x552C),
    L2(5, 0, 0, 0, 0, 0, 0, 0x552D),
    L2(5, 1, 0, 0, 0, 0, 0, 0x552D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 24 */
const u16 brz_char_table_024_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_024[24] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x552E),
    L2(20, 0, 0, 0, 0, 0, 0, 0x552F),
    L2(1, 0, 0, 0, 0, 0, 0, 0x552E),
    L2(32, 0, 0, 0, 0, 0, 0, 0x552F),
    L2(32, 1, 0, 0, 0, 0, 0, 0x552F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 26 */
const u16 brz_char_table_026_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_026[40] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x5530),
    L2(4, 0, 0, 0, 0, 0, 0, 0x5531),
    L2(40, 0, 0, 0, 0, 0, 0, 0x5525),
    L2(4, 0, 0, 0, 0, 0, 0, 0x552E),
    L2(20, 0, 0, 0, 0, 0, 0, 0x552F),
    L2(6, 0, 0, 0, 0, 0, 0, 0x552E),
    L2(32, 0, 0, 0, 0, 0, 0, 0x552F),
    L2(3, 1, 0, 0, 0, 0, 0, 0x5525),
    L2(40, 0, 0, 0, 0, 0, 0, 0x5525),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 27 */
const u16 brz_char_table_027_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_027[8] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x5540),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 28 */
const u16 brz_char_table_028_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_028[28] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x5543),
    L2(8, 1, 0, 0, 0, 0, 0, 0x5543),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5544),
    L2(8, 1, 0, 0, 0, 0, 0, 0x5544),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5546),
    L2(8, 1, 0, 0, 0, 0, 0, 0x5546),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 29 */
const u16 brz_char_table_029_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_029[36] = {
    CMD(CM_FOR, 0, 0, 4),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5547),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5548),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5549),
    L2(6, 0, 0, 0, 0, 0, 0, 0x554A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x554B),
    CMD(CM_NEX, 0, 0, 0),
    L2(6, 1, 0, 0, 0, 0, 0, 0x554B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 30 */
const u16 brz_char_table_030_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_030[72] = {
    CMD(CM_FOR, 0, 0, 2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x554C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x554D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x554E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x554F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5550),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5551),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5552),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x554C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x554D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x554E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x554F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5550),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5551),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5552),
    L2(8, 1, 0, 0, 0, 0, 0, 0x5552),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 31 */
const u16 brz_char_table_031_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_031[36] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x554C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x554D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x554E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x554F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5550),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5551),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5552),
    L2(8, 1, 0, 0, 0, 0, 0, 0x5552),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 32 */
const u16 brz_char_table_032_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_032[20] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x5558),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5559),
    L2(3, 0, 0, 0, 0, 0, 0, 0x555A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x555B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 33 */
const u16 brz_char_table_033_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_033[44] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x555C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x555D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x555F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5560),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5561),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5562),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5563),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5564),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5565),
    L2(3, 1, 0, 0, 0, 0, 0, 0x5565),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 34 */
const u16 brz_char_table_034_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_034[20] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5568),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5569),
    L2(6, 0, 0, 0, 0, 0, 0, 0x556A),
    L2(6, 1, 0, 0, 0, 0, 0, 0x556A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 35 */
const u16 brz_char_table_035_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_035[8] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x556B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 36 */
const u16 brz_char_table_036_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_036[20] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x556C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x556D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x556E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x556F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 37 */
const u16 brz_char_table_037_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_037[44] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x5570),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5571),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5572),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5573),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5574),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5575),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5576),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5577),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5578),
    L2(3, 1, 0, 0, 0, 0, 0, 0x5578),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 38 */
const u16 brz_char_table_038_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_038[20] = {
    L2(6, 0, 0, 0, 1, 0, 0, 0x5568),
    L2(6, 0, 0, 0, 1, 0, 0, 0x5569),
    L2(6, 0, 0, 0, 1, 0, 0, 0x556A),
    L2(6, 1, 0, 0, 1, 0, 0, 0x556A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 39 */
const u16 brz_char_table_039_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_039[8] = {
    L2(6, 0, 0, 0, 1, 0, 0, 0x556B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 40 */
const u16 brz_char_table_040_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_040[40] = {
    L2(200, 0, 0, 0, 0, 0, 0, 0x5539),
    CMD(CM_FOR, 0, 0, 2),
    L2(11, 0, 0, 0, 0, 0, 0, 0x553A),
    L2(11, 0, 0, 0, 0, 0, 0, 0x553B),
    L2(11, 0, 0, 0, 0, 0, 0, 0x553C),
    L2(11, 0, 0, 0, 0, 0, 0, 0x553D),
    L2(11, 0, 0, 0, 0, 0, 0, 0x553E),
    CMD(CM_NEX, 0, 0, 0),
    L2(200, 0, 0, 0, 0, 0, 0, 0x5539),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 41 */
const u16 brz_char_table_041_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_041[56] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x5539),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5538),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5537),
    L2(10, 0, 0, 0, 0, 0, 0, 0x5533),
    L2(6, 0, 0, 0, 0, 0, 0, 0x5534),
    L2(24, 0, 0, 0, 0, 0, 0, 0x5535),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5534),
    L2(8, 0, 0, 0, 0, 0, 0, 0x5536),
    L2(18, 0, 0, 0, 0, 0, 0, 0x5533),
    L2(12, 0, 0, 0, 0, 0, 0, 0x5537),
    L2(12, 0, 0, 0, 0, 0, 0, 0x5538),
    L2(12, 0, 0, 0, 0, 0, 0, 0x5539),
    L2(10, 1, 0, 0, 0, 0, 0, 0x5539),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 42 */
const u16 brz_char_table_042_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_042[32] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x5419),
    L2(3, 0, 0, 0, 0, 0, 0, 0x541A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x541B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x541C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x541D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x541E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x541F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 43 */
const u16 brz_char_table_043_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_043[16] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x5420),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5421),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5422),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 44 */
const u16 brz_char_table_044_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_044[28] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x5423),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5424),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5425),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5426),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5427),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5428),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 45 */
const u16 brz_char_table_045_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_045[28] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x5429),
    L2(3, 0, 0, 0, 0, 0, 0, 0x542A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x542B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x542C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x542D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x542E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 46 */
const u16 brz_char_table_046_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_046[24] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x542F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5430),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5431),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5432),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5433),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 47 */
const u16 brz_char_table_047_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_047[28] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x5434),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5435),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5436),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5437),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5438),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5439),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 48 */
const u16 brz_char_table_048_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_048[20] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x543A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x543B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x543C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x543D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 49 */
const u16 brz_char_table_049_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_049[28] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x543E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x543F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5440),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5441),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5442),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5443),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 50 */
const u16 brz_char_table_050_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_050[16] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x5444),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5445),
    L2(3, 0, 0, 0, 0, 0, 0, 0x5446),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 51 */
const u16 brz_char_table_051_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 brz_char_table_051[52] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x54F5),
    L2(5, 0, 0, 0, 0, 0, 0, 0x54F6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x54F7),
    CMD(CM_FOR, 0, 0, 10),
    L2(2, 0, 0, 0, 0, 0, 0, 0x54F8),
    L2(2, 0, 0, 0, 0, 0, 0, 0x54F7),
    CMD(CM_NEX, 0, 0, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x54F8),
    L2(4, 0, 0, 0, 0, 0, 0, 0x54F6),
    L2(5, 0, 0, 0, 0, 0, 0, 0x54F5),
    L2(6, 0, 0, 0, 0, 0, 0, 0x54E9),
    L2(6, 1, 0, 0, 0, 0, 0, 0x54E9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff90_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff90_char_table_000[8] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x409A),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 eff75_char_table_000[], eff75_char_table_001[];

/* eff75_char_table: 2 entries (no closing 0: the next table follows); used by EFF75, EFF76 */
const u32 eff75_char_table[2] = {
    (u32)eff75_char_table_000,  /* 0 */
    (u32)eff75_char_table_001,  /* 1 */
};

extern const u16 eff67_char_table_000[], eff67_char_table_001[], eff67_char_table_002[], eff67_char_table_003[];

/* eff67_char_table: 4 entries; used by EFF67 */
const u32 eff67_char_table[5] = {
    (u32)eff67_char_table_000,  /* 0 */
    (u32)eff67_char_table_001,  /* 1 */
    (u32)eff67_char_table_002,  /* 2 */
    (u32)eff67_char_table_003,  /* 3 */
    0
};

/* script: 0 */
const u16 eff75_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff75_char_table_000[224] = {
    L2(4, 13, 0, 0, 0, 0, 0, 0x6290),
    L2(4, 13, 0, 0, 0, 0, 0, 0x6291),
    L2(4, 13, 0, 0, 0, 0, 0, 0x6292),
    L2(4, 13, 0, 0, 0, 0, 0, 0x6293),
    L2(4, 13, 0, 0, 0, 0, 0, 0x6294),
    L2(4, 13, 0, 0, 0, 0, 0, 0x6295),
    L2(5, 14, 0, 0, 0, 0, 0, 0x6290),
    L2(5, 14, 0, 0, 0, 0, 0, 0x6291),
    L2(5, 14, 0, 0, 0, 0, 0, 0x6292),
    L2(5, 14, 0, 0, 0, 0, 0, 0x6293),
    L2(5, 14, 0, 0, 0, 0, 0, 0x6294),
    L2(5, 14, 0, 0, 0, 0, 0, 0x6295),
    L2(6, 14, 0, 0, 0, 0, 0, 0x6290),
    L2(6, 14, 0, 0, 0, 0, 0, 0x6291),
    L2(6, 15, 0, 0, 0, 0, 0, 0x6292),
    L2(6, 15, 0, 0, 0, 0, 0, 0x6293),
    L2(6, 15, 0, 0, 0, 0, 0, 0x6294),
    L2(6, 16, 0, 0, 0, 0, 0, 0x6295),
    L2(7, 16, 0, 0, 0, 0, 0, 0x6290),
    L2(7, 16, 0, 0, 0, 0, 0, 0x6291),
    L2(7, 17, 0, 0, 0, 0, 0, 0x6292),
    L2(7, 17, 0, 0, 0, 0, 0, 0x6293),
    L2(7, 18, 0, 0, 0, 0, 0, 0x6294),
    L2(8, 18, 0, 0, 0, 0, 0, 0x6295),
    L2(8, 19, 0, 0, 0, 0, 0, 0x6290),
    L2(8, 19, 0, 0, 0, 0, 0, 0x6291),
    L2(8, 19, 0, 0, 0, 0, 0, 0x6292),
    L2(8, 20, 0, 0, 0, 0, 0, 0x6293),
    L2(8, 21, 0, 0, 0, 0, 0, 0x6294),
    L2(9, 22, 0, 0, 0, 0, 0, 0x6295),
    L2(9, 23, 0, 0, 0, 0, 0, 0x6290),
    L2(9, 24, 0, 0, 0, 0, 0, 0x6291),
    L2(9, 25, 0, 0, 0, 0, 0, 0x6292),
    L2(9, 26, 0, 0, 0, 0, 0, 0x6293),
    L2(9, 27, 0, 0, 0, 0, 0, 0x6294),
    L2(10, 28, 0, 0, 0, 0, 0, 0x6295),
    L2(10, 29, 0, 0, 0, 0, 0, 0x6290),
    L2(10, 30, 0, 0, 0, 0, 0, 0x6291),
    L2(10, 31, 0, 0, 0, 0, 0, 0x6292),
    L2(10, 32, 0, 0, 0, 0, 0, 0x6293),
    L2(10, 33, 0, 0, 0, 0, 0, 0x6294),
    L2(11, 34, 0, 0, 0, 0, 0, 0x6295),
    L2(11, 34, 0, 0, 0, 0, 0, 0x6290),
    L2(11, 34, 0, 0, 0, 0, 0, 0x6291),
    L2(11, 34, 0, 0, 0, 0, 0, 0x6292),
    L2(11, 34, 0, 0, 0, 0, 0, 0x6293),
    L2(11, 34, 0, 0, 0, 0, 0, 0x6294),
    L2(11, 34, 0, 0, 0, 0, 0, 0x6295),
    L2(12, 34, 0, 0, 0, 0, 0, 0x6290),
    L2(12, 34, 0, 0, 0, 0, 0, 0x6291),
    L2(12, 34, 0, 0, 0, 0, 0, 0x6292),
    L2(12, 34, 0, 0, 0, 0, 0, 0x6293),
    L2(12, 34, 0, 0, 0, 0, 0, 0x6294),
    L2(12, 34, 0, 0, 0, 0, 0, 0x6295),
    L2(12, 99, 0, 0, 0, 0, 0, 0x6295),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff75_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff75_char_table_001[176] = {
    L2(1, 13, 0, 0, 0, 0, 0, 0x6296),
    L2(1, 13, 0, 0, 0, 0, 0, 0x6297),
    L2(1, 13, 0, 0, 0, 0, 0, 0x6298),
    L2(1, 13, 0, 0, 0, 0, 0, 0x6299),
    L2(2, 13, 0, 0, 0, 0, 0, 0x629A),
    L2(2, 13, 0, 0, 0, 0, 0, 0x629B),
    L2(2, 14, 0, 0, 0, 0, 0, 0x6296),
    L2(2, 14, 0, 0, 0, 0, 0, 0x6297),
    L2(2, 14, 0, 0, 0, 0, 0, 0x6298),
    L2(2, 14, 0, 0, 0, 0, 0, 0x6299),
    L2(2, 14, 0, 0, 0, 0, 0, 0x629A),
    L2(3, 14, 0, 0, 0, 0, 0, 0x629B),
    L2(3, 15, 0, 0, 0, 0, 0, 0x6296),
    L2(4, 15, 0, 0, 0, 0, 0, 0x6297),
    L2(4, 15, 0, 0, 0, 0, 0, 0x6298),
    L2(4, 15, 0, 0, 0, 0, 0, 0x6299),
    L2(4, 16, 0, 0, 0, 0, 0, 0x629A),
    L2(5, 16, 0, 0, 0, 0, 0, 0x629B),
    L2(5, 17, 0, 0, 0, 0, 0, 0x6296),
    L2(5, 17, 0, 0, 0, 0, 0, 0x6297),
    L2(5, 18, 0, 0, 0, 0, 0, 0x6298),
    L2(6, 18, 0, 0, 0, 0, 0, 0x6299),
    L2(6, 19, 0, 0, 0, 0, 0, 0x629A),
    L2(6, 19, 0, 0, 0, 0, 0, 0x629B),
    L2(6, 20, 0, 0, 0, 0, 0, 0x6296),
    L2(7, 20, 0, 0, 0, 0, 0, 0x6297),
    L2(7, 21, 0, 0, 0, 0, 0, 0x6298),
    L2(7, 21, 0, 0, 0, 0, 0, 0x6299),
    L2(7, 22, 0, 0, 0, 0, 0, 0x629A),
    L2(8, 22, 0, 0, 0, 0, 0, 0x629B),
    L2(8, 23, 0, 0, 0, 0, 0, 0x6296),
    L2(8, 24, 0, 0, 0, 0, 0, 0x6297),
    L2(8, 25, 0, 0, 0, 0, 0, 0x6298),
    L2(9, 26, 0, 0, 0, 0, 0, 0x6299),
    L2(9, 27, 0, 0, 0, 0, 0, 0x629A),
    L2(9, 28, 0, 0, 0, 0, 0, 0x629B),
    L2(10, 29, 0, 0, 0, 0, 0, 0x6296),
    L2(10, 30, 0, 0, 0, 0, 0, 0x6297),
    L2(10, 31, 0, 0, 0, 0, 0, 0x6298),
    L2(10, 32, 0, 0, 0, 0, 0, 0x6299),
    L2(10, 33, 0, 0, 0, 0, 0, 0x629A),
    L2(10, 34, 0, 0, 0, 0, 0, 0x629B),
    L2(10, 99, 0, 0, 0, 0, 0, 0x629B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 eff67_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff67_char_table_000[40] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x7738),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7739),
    L2(8, 0, 0, 0, 0, 0, 0, 0x773A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7738),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7739),
    L2(8, 0, 0, 0, 0, 0, 0, 0x773A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7738),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7739),
    L2(8, 0, 0, 0, 0, 0, 0, 0x773A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 eff67_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff67_char_table_001[40] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x773B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x773C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x773D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x773B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x773C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x773D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x773B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x773C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x773D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 eff67_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff67_char_table_002[16] = {
    L2(18, 0, 0, 0, 0, 0, 0, 0x7740),
    L2(18, 0, 0, 0, 0, 0, 0, 0x7741),
    L2(18, 0, 0, 0, 0, 0, 0, 0x7742),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 eff67_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 eff67_char_table_003[16] = {
    L2(18, 0, 0, 0, 0, 0, 0, 0x7743),
    L2(18, 0, 0, 0, 0, 0, 0, 0x7744),
    L2(18, 0, 0, 0, 0, 0, 0, 0x7745),
    CMD(CM_ROA, 0, 0, 0),
};
