/*
 * EFFECT_CHAR.C  Player effect scripts
 *
 * Each *_char_table is an index of animation scripts followed by the scripts, in the format of the
 * fighters' tables: an effect's work takes the table as its char_table and set_char_move_init
 * starts its scripts. See charscr.h for the line layouts. The comment of each index table names the
 * modules that use it.
 *
 * Index tables here: plef_char_table, ef01_char_table, ef13_char_table, ag_char_table_0,
 * ag_char_table_1, ag_char_table_2, ag_char_table_3, ag_char_table_4, ag_char_table_5,
 * ag_char_table_6, ag_face_panel_table, effD4_char_table, effh0_char_table.
 */

#include "types.h"
#include "structs.h"
#include "charscr.h"

#pragma section CHR

extern const u16 plef_char_table_000[], plef_char_table_001[], plef_char_table_002[], plef_char_table_003[],
                 plef_char_table_004[], plef_char_table_005[], plef_char_table_006[], plef_char_table_007[],
                 plef_char_table_008[], plef_char_table_009[], plef_char_table_010[], plef_char_table_011[],
                 plef_char_table_012[], plef_char_table_013[], plef_char_table_014[], plef_char_table_015[],
                 plef_char_table_016[], plef_char_table_017[], plef_char_table_018[], plef_char_table_019[],
                 plef_char_table_020[], plef_char_table_021[], plef_char_table_022[], plef_char_table_023[],
                 plef_char_table_024[], plef_char_table_025[], plef_char_table_026[], plef_char_table_027[],
                 plef_char_table_028[], plef_char_table_029[], plef_char_table_030[], plef_char_table_031[],
                 plef_char_table_032[], plef_char_table_033[], plef_char_table_034[], plef_char_table_035[],
                 plef_char_table_036[], plef_char_table_037[], plef_char_table_038[], plef_char_table_039[],
                 plef_char_table_040[], plef_char_table_041[], plef_char_table_042[], plef_char_table_043[],
                 plef_char_table_044[], plef_char_table_045[], plef_char_table_046[], plef_char_table_047[],
                 plef_char_table_048[], plef_char_table_049[], plef_char_table_050[], plef_char_table_051[],
                 plef_char_table_052[], plef_char_table_053[], plef_char_table_054[], plef_char_table_055[],
                 plef_char_table_056[], plef_char_table_057[], plef_char_table_058[], plef_char_table_059[],
                 plef_char_table_060[], plef_char_table_061[], plef_char_table_062[], plef_char_table_063[],
                 plef_char_table_064[], plef_char_table_065[], plef_char_table_066[], plef_char_table_067[],
                 plef_char_table_068[], plef_char_table_069[], plef_char_table_070[], plef_char_table_071[],
                 plef_char_table_072[], plef_char_table_073[], plef_char_table_074[], plef_char_table_075[],
                 plef_char_table_076[], plef_char_table_077[], plef_char_table_078[], plef_char_table_090[],
                 plef_char_table_091[], plef_char_table_092[], plef_char_table_093[], plef_char_table_094[],
                 plef_char_table_095[], plef_char_table_096[], plef_char_table_097[], plef_char_table_098[],
                 plef_char_table_099[], plef_char_table_100[], plef_char_table_101[], plef_char_table_102[],
                 plef_char_table_103[], plef_char_table_104[], plef_char_table_105[], plef_char_table_106[],
                 plef_char_table_122[], plef_char_table_123[], plef_char_table_155[], plef_char_table_156[],
                 plef_char_table_157[], plef_char_table_158[], plef_char_table_159[], plef_char_table_160[],
                 plef_char_table_161[], plef_char_table_162[], plef_char_table_163[], plef_char_table_164[],
                 plef_char_table_165[];

/* plef_char_table: 166 entries; used by EFF03, EFF41, EFFC0, EFFE2, EFFG2, EFFG4, EFFG5, EFFG9, EFFH9, dbg_work */
const u32 plef_char_table[167] = {
    (u32)plef_char_table_000,  /* 0 */
    (u32)plef_char_table_001,  /* 1 */
    (u32)plef_char_table_002,  /* 2 */
    (u32)plef_char_table_003,  /* 3 */
    (u32)plef_char_table_004,  /* 4 */
    (u32)plef_char_table_005,  /* 5 */
    (u32)plef_char_table_006,  /* 6 */
    (u32)plef_char_table_007,  /* 7 */
    (u32)plef_char_table_008,  /* 8 */
    (u32)plef_char_table_009,  /* 9 */
    (u32)plef_char_table_010,  /* 10 */
    (u32)plef_char_table_011,  /* 11 */
    (u32)plef_char_table_012,  /* 12 */
    (u32)plef_char_table_013,  /* 13 */
    (u32)plef_char_table_014,  /* 14 */
    (u32)plef_char_table_015,  /* 15 */
    (u32)plef_char_table_016,  /* 16 */
    (u32)plef_char_table_017,  /* 17 */
    (u32)plef_char_table_018,  /* 18 */
    (u32)plef_char_table_019,  /* 19 */
    (u32)plef_char_table_020,  /* 20 */
    (u32)plef_char_table_021,  /* 21 */
    (u32)plef_char_table_022,  /* 22 */
    (u32)plef_char_table_023,  /* 23 */
    (u32)plef_char_table_024,  /* 24 */
    (u32)plef_char_table_025,  /* 25 */
    (u32)plef_char_table_026,  /* 26 */
    (u32)plef_char_table_027,  /* 27 */
    (u32)plef_char_table_028,  /* 28 */
    (u32)plef_char_table_029,  /* 29 */
    (u32)plef_char_table_030,  /* 30 */
    (u32)plef_char_table_031,  /* 31 */
    (u32)plef_char_table_032,  /* 32 */
    (u32)plef_char_table_033,  /* 33 */
    (u32)plef_char_table_034,  /* 34 */
    (u32)plef_char_table_035,  /* 35 */
    (u32)plef_char_table_036,  /* 36 */
    (u32)plef_char_table_037,  /* 37 */
    (u32)plef_char_table_038,  /* 38 */
    (u32)plef_char_table_039,  /* 39 */
    (u32)plef_char_table_040,  /* 40 */
    (u32)plef_char_table_041,  /* 41 */
    (u32)plef_char_table_042,  /* 42 */
    (u32)plef_char_table_043,  /* 43 */
    (u32)plef_char_table_044,  /* 44 */
    (u32)plef_char_table_045,  /* 45 */
    (u32)plef_char_table_046,  /* 46 */
    (u32)plef_char_table_047,  /* 47 */
    (u32)plef_char_table_048,  /* 48 */
    (u32)plef_char_table_049,  /* 49 */
    (u32)plef_char_table_050,  /* 50 */
    (u32)plef_char_table_051,  /* 51 */
    (u32)plef_char_table_052,  /* 52 */
    (u32)plef_char_table_053,  /* 53 */
    (u32)plef_char_table_054,  /* 54 */
    (u32)plef_char_table_055,  /* 55 */
    (u32)plef_char_table_056,  /* 56 */
    (u32)plef_char_table_057,  /* 57 */
    (u32)plef_char_table_058,  /* 58 */
    (u32)plef_char_table_059,  /* 59 */
    (u32)plef_char_table_060,  /* 60 */
    (u32)plef_char_table_061,  /* 61 */
    (u32)plef_char_table_062,  /* 62 */
    (u32)plef_char_table_063,  /* 63 */
    (u32)plef_char_table_064,  /* 64 */
    (u32)plef_char_table_065,  /* 65 */
    (u32)plef_char_table_066,  /* 66 */
    (u32)plef_char_table_067,  /* 67 */
    (u32)plef_char_table_068,  /* 68 */
    (u32)plef_char_table_069,  /* 69 */
    (u32)plef_char_table_070,  /* 70 */
    (u32)plef_char_table_071,  /* 71 */
    (u32)plef_char_table_072,  /* 72 */
    (u32)plef_char_table_073,  /* 73 */
    (u32)plef_char_table_074,  /* 74 */
    (u32)plef_char_table_075,  /* 75 */
    (u32)plef_char_table_076,  /* 76 */
    (u32)plef_char_table_077,  /* 77 */
    (u32)plef_char_table_078,  /* 78 */
    (u32)plef_char_table_078,  /* 79 */
    (u32)plef_char_table_078,  /* 80 */
    (u32)plef_char_table_078,  /* 81 */
    (u32)plef_char_table_078,  /* 82 */
    (u32)plef_char_table_078,  /* 83 */
    (u32)plef_char_table_078,  /* 84 */
    (u32)plef_char_table_078,  /* 85 */
    (u32)plef_char_table_078,  /* 86 */
    (u32)plef_char_table_078,  /* 87 */
    (u32)plef_char_table_078,  /* 88 */
    (u32)plef_char_table_078,  /* 89 */
    (u32)plef_char_table_090,  /* 90 */
    (u32)plef_char_table_091,  /* 91 */
    (u32)plef_char_table_092,  /* 92 */
    (u32)plef_char_table_093,  /* 93 */
    (u32)plef_char_table_094,  /* 94 */
    (u32)plef_char_table_095,  /* 95 */
    (u32)plef_char_table_096,  /* 96 */
    (u32)plef_char_table_097,  /* 97 */
    (u32)plef_char_table_098,  /* 98 */
    (u32)plef_char_table_099,  /* 99 */
    (u32)plef_char_table_100,  /* 100 */
    (u32)plef_char_table_101,  /* 101 */
    (u32)plef_char_table_102,  /* 102 */
    (u32)plef_char_table_103,  /* 103 */
    (u32)plef_char_table_104,  /* 104 */
    (u32)plef_char_table_105,  /* 105 */
    (u32)plef_char_table_106,  /* 106 */
    (u32)plef_char_table_106,  /* 107 */
    (u32)plef_char_table_106,  /* 108 */
    (u32)plef_char_table_106,  /* 109 */
    (u32)plef_char_table_106,  /* 110 */
    (u32)plef_char_table_106,  /* 111 */
    (u32)plef_char_table_106,  /* 112 */
    (u32)plef_char_table_106,  /* 113 */
    (u32)plef_char_table_106,  /* 114 */
    (u32)plef_char_table_106,  /* 115 */
    (u32)plef_char_table_106,  /* 116 */
    (u32)plef_char_table_106,  /* 117 */
    (u32)plef_char_table_106,  /* 118 */
    (u32)plef_char_table_106,  /* 119 */
    (u32)plef_char_table_106,  /* 120 */
    (u32)plef_char_table_106,  /* 121 */
    (u32)plef_char_table_122,  /* 122 */
    (u32)plef_char_table_123,  /* 123 */
    (u32)plef_char_table_123,  /* 124 */
    (u32)plef_char_table_123,  /* 125 */
    (u32)plef_char_table_123,  /* 126 */
    (u32)plef_char_table_123,  /* 127 */
    (u32)plef_char_table_123,  /* 128 */
    (u32)plef_char_table_123,  /* 129 */
    (u32)plef_char_table_123,  /* 130 */
    (u32)plef_char_table_123,  /* 131 */
    (u32)plef_char_table_123,  /* 132 */
    (u32)plef_char_table_123,  /* 133 */
    (u32)plef_char_table_123,  /* 134 */
    (u32)plef_char_table_123,  /* 135 */
    (u32)plef_char_table_123,  /* 136 */
    (u32)plef_char_table_123,  /* 137 */
    (u32)plef_char_table_123,  /* 138 */
    (u32)plef_char_table_123,  /* 139 */
    (u32)plef_char_table_123,  /* 140 */
    (u32)plef_char_table_123,  /* 141 */
    (u32)plef_char_table_123,  /* 142 */
    (u32)plef_char_table_123,  /* 143 */
    (u32)plef_char_table_123,  /* 144 */
    (u32)plef_char_table_123,  /* 145 */
    (u32)plef_char_table_123,  /* 146 */
    (u32)plef_char_table_123,  /* 147 */
    (u32)plef_char_table_123,  /* 148 */
    (u32)plef_char_table_123,  /* 149 */
    (u32)plef_char_table_123,  /* 150 */
    (u32)plef_char_table_123,  /* 151 */
    (u32)plef_char_table_123,  /* 152 */
    (u32)plef_char_table_123,  /* 153 */
    (u32)plef_char_table_123,  /* 154 */
    (u32)plef_char_table_155,  /* 155 */
    (u32)plef_char_table_156,  /* 156 */
    (u32)plef_char_table_157,  /* 157 */
    (u32)plef_char_table_158,  /* 158 */
    (u32)plef_char_table_159,  /* 159 */
    (u32)plef_char_table_160,  /* 160 */
    (u32)plef_char_table_161,  /* 161 */
    (u32)plef_char_table_162,  /* 162 */
    (u32)plef_char_table_163,  /* 163 */
    (u32)plef_char_table_164,  /* 164 */
    (u32)plef_char_table_165,  /* 165 */
    0
};

/* script: 0 */
const u16 plef_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_000[24] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x1CC4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1CC5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1CC6),
    L2(3, 1, 0, 0, 0, 0, 0, 0x1CC6),
    L2(250, 255, 0, 0, 0, 0, 0, 0x1CC6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 plef_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_001[52] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x130B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x130C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x130D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x130E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x130F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1310),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1311),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1312),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1313),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1314),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1315),
    L2(250, 255, 0, 0, 0, 0, 0, 0x1315),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 plef_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_002[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F52),
    L2(4, 0, 303, 0, 0, 0, 0, 0x6F53),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F54),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F55),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F56),
    L2(4, 0, 303, 0, 0, 0, 0, 0x6F57),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F58),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F59),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 plef_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_003[28] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x6F5A),
    L2(5, 0, 303, 0, 0, 0, 0, 0x6F5B),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6F5C),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6F5D),
    L2(5, 0, 303, 0, 0, 0, 0, 0x6F5E),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6F5F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 plef_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_004[24] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x6F60),
    L2(5, 0, 316, 0, 0, 0, 0, 0x6F61),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6F62),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6F63),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6F64),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 plef_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_005[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F66),
    L2(4, 0, 315, 0, 0, 0, 0, 0x6F67),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F68),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F69),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F6A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F6B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F6C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F6D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6 */
const u16 plef_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_006[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F93),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F94),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F95),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F96),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F97),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F98),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F99),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6F99),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 7 */
const u16 plef_char_table_007_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_007[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F9A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F9B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F9C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F9D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F9E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6F9F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6FA0),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6FA0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 plef_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_008[32] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x77F7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77F8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77F9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77FA),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77FB),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77FC),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77FC),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 plef_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_009[32] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x77FD),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77FE),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77FF),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7800),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7801),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7802),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7802),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 plef_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_010[36] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x6ED3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6ED4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6ED5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6ED6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6ED7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6ED8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6ED9),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6ED9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 plef_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_011[36] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EDA),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EDB),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EDC),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EDD),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EDE),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EDF),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EE0),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6EE0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 plef_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_012[36] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EE1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EE2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EE3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EE4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EE5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EE6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6EE7),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6EE7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 plef_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_013[56] = {
    L2(250, 131, 0, 0, 0, 0, 0, 0x778F),
    CMD(CM_IXBW, 0, 0, 1),
    L2(3, 1, 0, 0, 0, 0, 0, 0x7790),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7791),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7792),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7793),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7794),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7795),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7796),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7797),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7798),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7799),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7799),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 plef_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_014[56] = {
    L2(250, 131, 0, 0, 0, 0, 0, 0x779A),
    CMD(CM_IXBW, 0, 0, 1),
    L2(3, 1, 0, 0, 0, 0, 0, 0x779B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x779C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x779D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x779E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x779F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A4),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77A4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 plef_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_015[56] = {
    L2(250, 131, 0, 0, 0, 0, 0, 0x77A5),
    CMD(CM_IXBW, 0, 0, 1),
    L2(3, 1, 0, 0, 0, 0, 0, 0x77A6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77AA),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77AB),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77AC),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77AD),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77AE),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77AF),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77AF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16 */
const u16 plef_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_016[56] = {
    L2(250, 131, 0, 0, 0, 0, 0, 0x77B0),
    CMD(CM_IXBW, 0, 0, 1),
    L2(3, 1, 0, 0, 0, 0, 0, 0x77B1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77BA),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77BA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 17 */
const u16 plef_char_table_017_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_017[72] = {
    CMD(CM_FOR, 0, 0, 1),
    L2(3, 139, 0, 0, 0, 0, 0, 0x77BB),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77BC),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77BD),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77BE),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77BF),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C2),
    CMD(CM_NEX, 0, 0, 0),
    L2(3, 1, 0, 0, 0, 0, 0, 0x77C3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C8),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77C8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 18 */
const u16 plef_char_table_018_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_018[72] = {
    CMD(CM_FOR, 0, 0, 1),
    L2(3, 139, 0, 0, 0, 0, 0, 0x77C9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77CA),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77CB),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77CC),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77CD),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77CE),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77CF),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D0),
    CMD(CM_NEX, 0, 0, 0),
    L2(3, 1, 0, 0, 0, 0, 0, 0x77D1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D6),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77D6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 19 */
const u16 plef_char_table_019_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_019[32] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C8),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77C8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 20 */
const u16 plef_char_table_020_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_020[32] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D6),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77D6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 21 */
const u16 plef_char_table_021_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_021[44] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x77EE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77EF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77F0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77F1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77F2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77F3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77F4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77F5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77F6),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77F6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 22 */
const u16 plef_char_table_022_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_022[44] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x77E5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77E6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77E7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77E8),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77E9),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77EA),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77EB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77EC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77ED),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77ED),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 23 */
const u16 plef_char_table_023_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_023[60] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x77D8),
    L2(4, 0, 283, 0, 0, 0, 0, 0x77D9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77DA),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77DB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77DC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77DD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77DE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77DF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77E0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77E1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77E2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77E3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x77E4),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77E4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 24 */
const u16 plef_char_table_024_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_024[92] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F3E),
    CMD(CM_ROA, 0, 0, 0),
    L2(2, 0, 317, 0, 0, 0, 0, 0x6F3E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F3F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F40),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F41),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F42),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F43),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F44),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F45),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F46),
    CMD(CM_EXEC, 9, 0, 0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F47),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F48),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F49),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F4A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F4B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F4C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F4D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F4E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F4F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6F50),
    CMD(CM_RET, 0, 0, 0),
};

/* script: 25 */
const u16 plef_char_table_025_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_025[28] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x1F0B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1F0C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x1F0D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x1F0E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x1F0F),
    L2(250, 255, 0, 0, 0, 0, 0, 0x1F0F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 26 */
const u16 plef_char_table_026_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_026[52] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x1760),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1761),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1762),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1763),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1764),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1765),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1766),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1767),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1768),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1769),
    L2(3, 0, 0, 0, 0, 0, 0, 0x176A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x176B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 27 */
const u16 plef_char_table_027_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_027[52] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x176C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x176D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x176E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x176F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1770),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1771),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1772),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1773),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1774),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1775),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1776),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1777),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 28 */
const u16 plef_char_table_028_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_028[32] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x7771),
    L2(4, 0, 0, 0, 0, 0, 0, 0x7772),
    L2(5, 0, 0, 0, 0, 0, 0, 0x7773),
    L2(5, 0, 0, 0, 0, 0, 0, 0x7774),
    L2(6, 0, 0, 0, 0, 0, 0, 0x7775),
    L2(6, 0, 0, 0, 0, 0, 0, 0x7776),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7776),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 29 */
const u16 plef_char_table_029_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_029[32] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x7777),
    L2(4, 0, 0, 0, 0, 0, 0, 0x7778),
    L2(5, 0, 0, 0, 0, 0, 0, 0x7779),
    L2(5, 0, 0, 0, 0, 0, 0, 0x777A),
    L2(6, 0, 0, 0, 0, 0, 0, 0x777B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x777C),
    L2(250, 255, 0, 0, 0, 0, 0, 0x777C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 30 */
const u16 plef_char_table_030_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_030[44] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x7786),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7787),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7788),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7789),
    L2(2, 0, 0, 0, 0, 0, 0, 0x778A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x778B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x778C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x778D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x778E),
    L2(250, 255, 0, 0, 0, 0, 0, 0x778E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 31 */
const u16 plef_char_table_031_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_031[44] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x777D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x777E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x777F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7780),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7781),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7782),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7783),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7784),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7785),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7785),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 32 */
const u16 plef_char_table_032_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_032[60] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FA1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FA2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FA3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FA4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FA5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FA6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FA7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FA8),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FA9),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FAA),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FAB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FAC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FAD),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6FAD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 33 */
const u16 plef_char_table_033_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_033[88] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F7D),
    CMD(CM_PAXY, 0, 320, 256),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F7E),
    CMD(CM_PAXY, 0, 384, 288),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F7F),
    CMD(CM_PAXY, 0, 448, 320),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F80),
    CMD(CM_PAXY, 0, 512, 352),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F81),
    CMD(CM_PAXY, 0, 576, 384),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F82),
    CMD(CM_PAXY, 0, 640, 416),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F83),
    CMD(CM_PAXY, 0, 704, 448),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F84),
    CMD(CM_PAXY, 0, 768, 480),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F85),
    CMD(CM_PAXY, 0, 832, 512),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F86),
    CMD(CM_PAXY, 0, 896, 544),
    L2(250, 255, 0, 0, 0, 0, 0, 0x1F86),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 34 */
const u16 plef_char_table_034_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_034[48] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F8D),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F8E),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F8F),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F90),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F91),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F92),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F93),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F94),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F95),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F96),
    L2(250, 255, 0, 0, 0, 0, 0, 0x1F96),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 35 */
const u16 plef_char_table_035_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_035[32] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F87),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1F88),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1F89),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1F8A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x1F8B),
    L2(6, 0, 0, 0, 0, 0, 0, 0x1F8C),
    L2(250, 255, 0, 0, 0, 0, 0, 0x1F8C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 36 */
const u16 plef_char_table_036_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_036[68] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x7568),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7569),
    L2(8, 0, 0, 0, 0, 0, 0, 0x756A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x756B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x756C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x756D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x756E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x756F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7570),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7571),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7572),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7573),
    L2(8, 1, 0, 0, 0, 0, 0, 0x7574),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7575),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7576),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7577),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 37 */
const u16 plef_char_table_037_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_037[36] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x75C8),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75C9),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75CA),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75CB),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75CC),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75CD),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75CE),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75CF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 38 */
const u16 plef_char_table_038_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_038[68] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x7578),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7579),
    L2(8, 0, 0, 0, 0, 0, 0, 0x757A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x757B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x757C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x757D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x757E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x757F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7580),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7581),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7582),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7583),
    L2(8, 1, 0, 0, 0, 0, 0, 0x7584),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7585),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7586),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7587),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 39 */
const u16 plef_char_table_039_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_039[48] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x75A8),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75A9),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75AA),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75AB),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75AC),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75AD),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75AE),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75AF),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75B0),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75B1),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75B2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 40 */
const u16 plef_char_table_040_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_040[68] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x7588),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7589),
    L2(8, 0, 0, 0, 0, 0, 0, 0x758A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x758B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x758C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x758D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x758E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x758F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7590),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7591),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7592),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7593),
    L2(8, 1, 0, 0, 0, 0, 0, 0x7594),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7595),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7596),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7597),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 41 */
const u16 plef_char_table_041_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_041[48] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x75B8),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75B9),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75BA),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75BB),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75BC),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75BD),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75BE),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75BF),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75C0),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75C1),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75C2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 42 */
const u16 plef_char_table_042_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_042[68] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x7598),
    L2(8, 0, 0, 0, 0, 0, 0, 0x7599),
    L2(8, 0, 0, 0, 0, 0, 0, 0x759A),
    L2(8, 0, 0, 0, 0, 0, 0, 0x759B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x759C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x759D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x759E),
    L2(8, 0, 0, 0, 0, 0, 0, 0x759F),
    L2(8, 0, 0, 0, 0, 0, 0, 0x75A0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x75A1),
    L2(8, 0, 0, 0, 0, 0, 0, 0x75A2),
    L2(8, 0, 0, 0, 0, 0, 0, 0x75A3),
    L2(8, 1, 0, 0, 0, 0, 0, 0x75A4),
    L2(8, 0, 0, 0, 0, 0, 0, 0x75A5),
    L2(8, 0, 0, 0, 0, 0, 0, 0x75A6),
    L2(8, 0, 0, 0, 0, 0, 0, 0x75A7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 43 */
const u16 plef_char_table_043_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_043[48] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x75D8),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75D9),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75DA),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75DB),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75DC),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75DD),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75DE),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75DF),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75E0),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75E1),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75E2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 44 */
const u16 plef_char_table_044_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_044[32] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x1795),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1796),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1797),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1798),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1799),
    L2(3, 0, 0, 0, 0, 0, 0, 0x179A),
    L2(250, 255, 0, 0, 0, 0, 0, 0x179A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 45 */
const u16 plef_char_table_045_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_045[20] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x17AA),
    L2(3, 0, 0, 0, 0, 0, 0, 0x17AB),
    L2(3, 0, 0, 0, 0, 0, 0, 0x17AC),
    L2(250, 255, 0, 0, 0, 0, 0, 0x17AC),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 46 */
const u16 plef_char_table_046_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_046[8] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x17AA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 47 */
const u16 plef_char_table_047_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_047[60] = {
    L2(1, 0, 0, 0, 1, 0, 0, 0x6FA1),
    L2(1, 0, 0, 0, 1, 0, 0, 0x6FA2),
    L2(1, 0, 0, 0, 1, 0, 0, 0x6FA3),
    L2(2, 0, 0, 0, 1, 0, 0, 0x6FA4),
    L2(2, 0, 0, 0, 1, 0, 0, 0x6FA5),
    L2(2, 0, 0, 0, 1, 0, 0, 0x6FA6),
    L2(3, 0, 0, 0, 1, 0, 0, 0x6FA7),
    L2(3, 0, 0, 0, 1, 0, 0, 0x6FA8),
    L2(4, 0, 0, 0, 1, 0, 0, 0x6FA9),
    L2(4, 0, 0, 0, 1, 0, 0, 0x6FAA),
    L2(4, 0, 0, 0, 1, 0, 0, 0x6FAB),
    L2(5, 0, 0, 0, 1, 0, 0, 0x6FAC),
    L2(5, 0, 0, 0, 1, 0, 0, 0x6FAD),
    L2(250, 255, 0, 0, 1, 0, 0, 0x6FAD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 48 */
const u16 plef_char_table_048_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_048[48] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x729E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x729F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x72A0),
    L2(4, 0, 0, 0, 0, 0, 0, 0x72A1),
    L2(4, 0, 0, 0, 0, 0, 0, 0x72A2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x72A3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x72A4),
    L2(5, 0, 0, 0, 0, 0, 0, 0x72A5),
    L2(5, 0, 0, 0, 0, 0, 0, 0x72A6),
    L2(6, 0, 0, 0, 0, 0, 0, 0x72A7),
    L2(250, 255, 0, 0, 0, 0, 0, 0x72A7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 49 */
const u16 plef_char_table_049_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_049[32] = {
    CMD(CM_FOR, 0, 0, 2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FCB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6E80),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FCC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6E80),
    CMD(CM_NEX, 0, 0, 0),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E80),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 50 */
const u16 plef_char_table_050_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_050[32] = {
    CMD(CM_FOR, 0, 0, 2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FCD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6E80),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FCE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6E80),
    CMD(CM_NEX, 0, 0, 0),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E80),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 51 */
const u16 plef_char_table_051_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_051[32] = {
    CMD(CM_FOR, 0, 0, 2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FCF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6E80),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FD0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6E80),
    CMD(CM_NEX, 0, 0, 0),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E80),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 52 */
const u16 plef_char_table_052_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_052[28] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x7011),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7012),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7013),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7014),
    L2(4, 0, 0, 0, 0, 0, 0, 0x7015),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7015),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 53 */
const u16 plef_char_table_053_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_053[64] = {
    L2(4, 133, 0, 0, 0, 0, 0, 0x778F),
    L2(1, 0, 323, 0, 0, 0, 0, 0x778F),
    L2(250, 0, 0, 0, 0, 0, 0, 0x778F),
    CMD(CM_IXBW, 0, 0, 1),
    L2(3, 1, 0, 0, 0, 0, 0, 0x7790),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7791),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7792),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7793),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7794),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7795),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7796),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7797),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7798),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7799),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7799),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 54 */
const u16 plef_char_table_054_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_054[64] = {
    L2(4, 133, 0, 0, 0, 0, 0, 0x779A),
    L2(1, 0, 323, 0, 0, 0, 0, 0x779A),
    L2(250, 0, 0, 0, 0, 0, 0, 0x779A),
    CMD(CM_IXBW, 0, 0, 1),
    L2(3, 1, 0, 0, 0, 0, 0, 0x779B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x779C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x779D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x779E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x779F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A4),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77A4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 55 */
const u16 plef_char_table_055_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_055[64] = {
    L2(4, 133, 0, 0, 0, 0, 0, 0x77A5),
    L2(1, 0, 323, 0, 0, 0, 0, 0x77A5),
    L2(250, 0, 0, 0, 0, 0, 0, 0x77A5),
    CMD(CM_IXBW, 0, 0, 1),
    L2(3, 1, 0, 0, 0, 0, 0, 0x77A6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77A9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77AA),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77AB),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77AC),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77AD),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77AE),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77AF),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77AF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 56 */
const u16 plef_char_table_056_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_056[64] = {
    L2(4, 133, 0, 0, 0, 0, 0, 0x77B0),
    L2(1, 0, 323, 0, 0, 0, 0, 0x77B0),
    L2(250, 0, 0, 0, 0, 0, 0, 0x77B0),
    CMD(CM_IXBW, 0, 0, 1),
    L2(3, 1, 0, 0, 0, 0, 0, 0x77B1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77B9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77BA),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77BA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 57 */
const u16 plef_char_table_057_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_057[96] = {
    L2(2, 145, 0, 0, 0, 0, 0, 0x77BB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77BC),
    L2(2, 0, 314, 0, 0, 0, 0, 0x77BD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77BE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77BF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77C0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77C1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77C2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77BB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77BC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77BD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77BE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77BF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77C0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77C1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77C2),
    L2(2, 1, 0, 0, 0, 0, 0, 0x77C3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77C4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77C8),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77C8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 58 */
const u16 plef_char_table_058_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_058[96] = {
    L2(2, 145, 0, 0, 0, 0, 0, 0x77C9),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77CA),
    L2(2, 0, 314, 0, 0, 0, 0, 0x77CB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77CC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77CD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77CE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77CF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77D0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77C9),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77CA),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77CB),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77CC),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77CD),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77CE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77CF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77D0),
    L2(2, 1, 0, 0, 0, 0, 0, 0x77D1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x77D2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x77D6),
    L2(250, 255, 0, 0, 0, 0, 0, 0x77D6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 59 */
const u16 plef_char_table_059_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_059[28] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x1D71),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1D83),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1E01),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1E4C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1E4D),
    L2(250, 255, 0, 0, 0, 0, 0, 0x1E4E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 60 */
const u16 plef_char_table_060_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_060[72] = {
    L2(2, 0, 0, 0, 1, 0, 0, 0x731C),
    L2(2, 0, 0, 0, 1, 0, 0, 0x731D),
    L2(2, 0, 0, 0, 1, 0, 0, 0x731E),
    L2(2, 0, 0, 0, 1, 0, 0, 0x731F),
    L2(2, 0, 0, 0, 1, 0, 0, 0x7320),
    L2(2, 0, 0, 0, 1, 0, 0, 0x7321),
    L2(2, 0, 0, 0, 1, 0, 0, 0x7322),
    L2(2, 0, 0, 0, 1, 0, 0, 0x7323),
    L2(2, 0, 0, 0, 1, 0, 0, 0x7324),
    L2(2, 0, 0, 0, 1, 0, 0, 0x7325),
    L2(2, 0, 0, 0, 1, 0, 0, 0x7326),
    L2(2, 0, 0, 0, 1, 0, 0, 0x7327),
    L2(2, 0, 0, 0, 1, 0, 0, 0x7328),
    L2(2, 0, 0, 0, 1, 0, 0, 0x7329),
    L2(1, 0, 0, 0, 1, 0, 0, 0x732A),
    L2(1, 0, 0, 0, 1, 0, 0, 0x732B),
    L2(250, 255, 0, 0, 1, 0, 0, 0x732B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 61 */
const u16 plef_char_table_061_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_061[56] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x7026),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7027),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7028),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7029),
    L2(3, 0, 0, 0, 0, 0, 0, 0x702A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x702B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x702C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x702D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x702E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x702F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7030),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7031),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7031),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 62 */
const u16 plef_char_table_062_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_062[72] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x7016),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7017),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7018),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7019),
    L2(3, 0, 0, 0, 0, 0, 0, 0x701A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x701B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x701C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x701D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x701E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x701F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7020),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7021),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7022),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7023),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7024),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7025),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7025),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 63 */
const u16 plef_char_table_063_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_063[72] = {
    L2(3, 0, 0, 0, 1, 0, 0, 0x7016),
    L2(3, 0, 0, 0, 1, 0, 0, 0x7017),
    L2(3, 0, 0, 0, 1, 0, 0, 0x7018),
    L2(3, 0, 0, 0, 1, 0, 0, 0x7019),
    L2(3, 0, 0, 0, 1, 0, 0, 0x701A),
    L2(3, 0, 0, 0, 1, 0, 0, 0x701B),
    L2(3, 0, 0, 0, 1, 0, 0, 0x701C),
    L2(3, 0, 0, 0, 1, 0, 0, 0x701D),
    L2(3, 0, 0, 0, 1, 0, 0, 0x701E),
    L2(3, 0, 0, 0, 1, 0, 0, 0x701F),
    L2(3, 0, 0, 0, 1, 0, 0, 0x7020),
    L2(3, 0, 0, 0, 1, 0, 0, 0x7021),
    L2(3, 0, 0, 0, 1, 0, 0, 0x7022),
    L2(3, 0, 0, 0, 1, 0, 0, 0x7023),
    L2(3, 0, 0, 0, 1, 0, 0, 0x7024),
    L2(3, 0, 0, 0, 1, 0, 0, 0x7025),
    L2(250, 255, 0, 0, 1, 0, 0, 0x7025),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 64 */
const u16 plef_char_table_064_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_064[72] = {
    L2(2, 0, 0, 0, 2, 0, 0, 0x731C),
    L2(2, 0, 0, 0, 2, 0, 0, 0x731D),
    L2(2, 0, 0, 0, 2, 0, 0, 0x731E),
    L2(2, 0, 0, 0, 2, 0, 0, 0x731F),
    L2(2, 0, 0, 0, 2, 0, 0, 0x7320),
    L2(2, 0, 0, 0, 2, 0, 0, 0x7321),
    L2(2, 0, 0, 0, 2, 0, 0, 0x7322),
    L2(2, 0, 0, 0, 2, 0, 0, 0x7323),
    L2(2, 0, 0, 0, 2, 0, 0, 0x7324),
    L2(2, 0, 0, 0, 2, 0, 0, 0x7325),
    L2(2, 0, 0, 0, 2, 0, 0, 0x7326),
    L2(2, 0, 0, 0, 2, 0, 0, 0x7327),
    L2(2, 0, 0, 0, 2, 0, 0, 0x7328),
    L2(2, 0, 0, 0, 2, 0, 0, 0x7329),
    L2(1, 0, 0, 0, 2, 0, 0, 0x732A),
    L2(1, 0, 0, 0, 2, 0, 0, 0x732B),
    L2(250, 255, 0, 0, 2, 0, 0, 0x732B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 65 */
const u16 plef_char_table_065_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_065[12] = {
    L2(16, 0, 0, 0, 0, 0, 0, 0x1FDD),
    L2(250, 255, 0, 0, 0, 0, 0, 0x1FDD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 66 */
const u16 plef_char_table_066_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_066[40] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x701E),
    L2(1, 0, 0, 0, 0, 0, 0, 0x701F),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7020),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7021),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7022),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7023),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7024),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7025),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7025),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 67 */
const u16 plef_char_table_067_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_067[40] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x701E),
    L2(1, 0, 0, 0, 0, 0, 0, 0x701F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7020),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7021),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7022),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7023),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7024),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7025),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7025),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 68 */
const u16 plef_char_table_068_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_068[40] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x701E),
    L2(1, 0, 0, 0, 0, 0, 0, 0x701F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7020),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7021),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7022),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7023),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7024),
    L2(4, 0, 0, 0, 0, 0, 0, 0x7025),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7025),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 69 */
const u16 plef_char_table_069_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_069[104] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x7016),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7017),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7018),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7019),
    CMD(CM_FOR, 0, 0, 4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x701A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x701B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x701C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x701D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x701E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x701F),
    CMD(CM_NEX, 0, 0, 0),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7026),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7027),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7028),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7029),
    L2(2, 0, 0, 0, 0, 0, 0, 0x702A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x702B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x702C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x702D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x702E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x702F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x7030),
    L2(4, 0, 0, 0, 0, 0, 0, 0x7031),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7031),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 70 */
const u16 plef_char_table_070_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_070[36] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x6FF6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FF7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FF8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6FF9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6FFA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6FFB),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6FFC),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6FFC),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 71 */
const u16 plef_char_table_071_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_071[24] = {
    CMD(CM_FOR, 0, 0, 28),
    L2(1, 0, 0, 0, 0, 0, 0, 0x0F6A),
    CMD(CM_PA_X, 0, 768, 0),
    CMD(CM_NEX, 0, 0, 0),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0F6A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 72 */
const u16 plef_char_table_072_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_072[24] = {
    CMD(CM_FOR, 0, 0, 28),
    L2(1, 0, 0, 0, 0, 0, 0, 0x0F6A),
    CMD(CM_PA_X, 0, -768, 0),
    CMD(CM_NEX, 0, 0, 0),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0F6A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 73 */
const u16 plef_char_table_073_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_073[72] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x731C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x731D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x731E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x731F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7320),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7321),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7322),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7323),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7324),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7325),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7326),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7327),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7328),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7329),
    L2(1, 0, 0, 0, 0, 0, 0, 0x732A),
    L2(1, 0, 0, 0, 0, 0, 0, 0x732B),
    L2(250, 255, 0, 0, 0, 0, 0, 0x732B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 74 */
const u16 plef_char_table_074_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_074[68] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x7568),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7569),
    L2(3, 0, 0, 0, 0, 0, 0, 0x756A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x756B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x756C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x756D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x756E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x756F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7570),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7571),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7572),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7573),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7574),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7575),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7576),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7577),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 75 */
const u16 plef_char_table_075_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_075[68] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x7578),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7579),
    L2(3, 0, 0, 0, 0, 0, 0, 0x757A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x757B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x757C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x757D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x757E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x757F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7580),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7581),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7582),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7583),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7584),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7585),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7586),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7587),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 76 */
const u16 plef_char_table_076_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_076[68] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x7588),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7589),
    L2(3, 0, 0, 0, 0, 0, 0, 0x758A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x758B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x758C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x758D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x758E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x758F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7590),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7591),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7592),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7593),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7594),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7595),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7596),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7597),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 77 */
const u16 plef_char_table_077_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_077[68] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x7598),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7599),
    L2(3, 0, 0, 0, 0, 0, 0, 0x759A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x759B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x759C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x759D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x759E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x759F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75A0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75A1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75A2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75A3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75A4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75A5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75A6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75A7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 78, 79, 80, 81 ... */
const u16 plef_char_table_078_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_078[12] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x0001),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0001),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 90 */
const u16 plef_char_table_090_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_090[24] = {
    CMD(CM_FOR, 0, 0, 28),
    L2(1, 0, 0, 0, 0, 0, 0, 0x2B66),
    CMD(CM_PA_X, 0, 768, 0),
    CMD(CM_NEX, 0, 0, 0),
    L2(250, 255, 0, 0, 0, 0, 0, 0x2B66),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 91 */
const u16 plef_char_table_091_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_091[24] = {
    CMD(CM_FOR, 0, 0, 28),
    L2(1, 0, 0, 0, 0, 0, 0, 0x2B66),
    CMD(CM_PA_X, 0, -768, 0),
    CMD(CM_NEX, 0, 0, 0),
    L2(250, 255, 0, 0, 0, 0, 0, 0x2B66),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 92 */
const u16 plef_char_table_092_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_092[24] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x0366),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0367),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0368),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0369),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0369),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 93 */
const u16 plef_char_table_093_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_093[20] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x036D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x036E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x036F),
    L2(250, 255, 0, 0, 0, 0, 0, 0x036F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 94 */
const u16 plef_char_table_094_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_094[20] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x0377),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0378),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0379),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0379),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 95 */
const u16 plef_char_table_095_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_095[20] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x037D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x037E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x037F),
    L2(250, 255, 0, 0, 0, 0, 0, 0x037F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 96 */
const u16 plef_char_table_096_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_096[20] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x038C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x038D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x038E),
    L2(250, 255, 0, 0, 0, 0, 0, 0x038E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 97 */
const u16 plef_char_table_097_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_097[24] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x0385),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0386),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0387),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0388),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0388),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 98 */
const u16 plef_char_table_098_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_098[28] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x039A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x039B),
    L2(3, 0, 0, 0, 0, 0, 0, 0x039C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x039D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x039E),
    L2(250, 255, 0, 0, 0, 0, 0, 0x039E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 99 */
const u16 plef_char_table_099_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_099[24] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x0394),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0395),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0396),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0397),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0397),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 100 */
const u16 plef_char_table_100_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_100[24] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x03A5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x03A6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x03A7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x03A8),
    L2(250, 255, 0, 0, 0, 0, 0, 0x03A8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 101 */
const u16 plef_char_table_101_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_101[20] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x03AC),
    L2(3, 0, 0, 0, 0, 0, 0, 0x03AD),
    L2(3, 0, 0, 0, 0, 0, 0, 0x03AE),
    L2(250, 255, 0, 0, 0, 0, 0, 0x03AE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 102 */
const u16 plef_char_table_102_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_102[24] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x03BB),
    L2(3, 0, 0, 0, 0, 0, 0, 0x03BC),
    L2(3, 0, 0, 0, 0, 0, 0, 0x03BD),
    L2(3, 0, 0, 0, 0, 0, 0, 0x03BE),
    L2(250, 255, 0, 0, 0, 0, 0, 0x03BE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 103 */
const u16 plef_char_table_103_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_103[24] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x03B5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x03B6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x03B7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x03B8),
    L2(250, 255, 0, 0, 0, 0, 0, 0x03B8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 104 */
const u16 plef_char_table_104_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_104[20] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x038C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x038D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x038E),
    L2(250, 255, 0, 0, 0, 0, 0, 0x038E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 105 */
const u16 plef_char_table_105_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_105[24] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x0385),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0386),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0387),
    L2(3, 0, 0, 0, 0, 0, 0, 0x0388),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0388),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 106, 107, 108, 109 ... */
const u16 plef_char_table_106_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_106[12] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x0401),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0401),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 122 */
const u16 plef_char_table_122_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_122[88] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F7D),
    CMD(CM_PAXY, 0, 384, 128),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F7E),
    CMD(CM_PAXY, 0, 464, 128),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F7F),
    CMD(CM_PAXY, 0, 544, 128),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F80),
    CMD(CM_PAXY, 0, 624, 128),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F81),
    CMD(CM_PAXY, 0, 704, 128),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F82),
    CMD(CM_PAXY, 0, 784, 128),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F83),
    CMD(CM_PAXY, 0, 864, 128),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F84),
    CMD(CM_PAXY, 0, 944, 128),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F85),
    CMD(CM_PAXY, 0, 1024, 128),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1F86),
    CMD(CM_PAXY, 0, 1120, 128),
    L2(250, 255, 0, 0, 0, 0, 0, 0x1F86),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 123, 124, 125, 126 ... */
const u16 plef_char_table_123_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_123[12] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x0001),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0001),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 155 */
const u16 plef_char_table_155_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_155[72] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x7016),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7017),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7018),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7019),
    L2(1, 0, 0, 0, 0, 0, 0, 0x701A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x701B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x701C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x701D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x701E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x701F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7020),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7021),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7022),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7023),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7024),
    L2(4, 0, 0, 0, 0, 0, 0, 0x7025),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7025),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 156 */
const u16 plef_char_table_156_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_156[12] = {
    CMD(CM_JSR, 0, 24, 3),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0000),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 157 */
const u16 plef_char_table_157_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_157[16] = {
    CMD(CM_JSR, 0, 24, 3),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0000),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0000),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 158 */
const u16 plef_char_table_158_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_158[16] = {
    CMD(CM_JSR, 0, 24, 3),
    L2(16, 0, 0, 0, 0, 0, 0, 0x0000),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0000),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 159 */
const u16 plef_char_table_159_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_159[44] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x75CF),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75D0),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75D1),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75D2),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75D3),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75D4),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75D5),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75D6),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75D7),
    L2(250, 255, 0, 0, 0, 0, 0, 0x75D7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 160 */
const u16 plef_char_table_160_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_160[52] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x75AD),
    L2(4, 0, 0, 0, 0, 0, 0, 0x75AE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x75AF),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75B0),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75B1),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75B2),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75B3),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75B4),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75B5),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75B6),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75B7),
    L2(250, 255, 0, 0, 0, 0, 0, 0x75B7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 161 */
const u16 plef_char_table_161_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_161[72] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x75B8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75B9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75BA),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75BB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x75BC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x75BD),
    L2(4, 0, 0, 0, 0, 0, 0, 0x75BE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x75BF),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75C0),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75C1),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75C2),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75C3),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75C4),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75C5),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75C6),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75C7),
    L2(250, 255, 0, 0, 0, 0, 0, 0x75C7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 162 */
const u16 plef_char_table_162_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_162[72] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x75D8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75D9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75DA),
    L2(3, 0, 0, 0, 0, 0, 0, 0x75DB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x75DC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x75DD),
    L2(4, 0, 0, 0, 0, 0, 0, 0x75DE),
    L2(4, 0, 0, 0, 0, 0, 0, 0x75DF),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75E0),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75E1),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75E2),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75E3),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75E4),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75E5),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75E6),
    L2(5, 0, 0, 0, 0, 0, 0, 0x75E7),
    L2(250, 255, 0, 0, 0, 0, 0, 0x75E7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 163 */
const u16 plef_char_table_163_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_163[128] = {
    L2(4, 0, 0, 0, 1, 0, 0, 0x03C0),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03C1),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03C2),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03C3),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03C4),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03C5),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03C6),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03C7),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03C8),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03C9),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03CA),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03CB),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03CC),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03CD),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03CE),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03CF),
    L2(4, 0, 0, 0, 1, 0, 0, 0x03D0),
    L2(3, 0, 0, 0, 1, 0, 0, 0x03D1),
    L2(3, 0, 0, 0, 1, 0, 0, 0x03D2),
    L2(3, 0, 0, 0, 1, 0, 0, 0x03D3),
    L2(3, 0, 0, 0, 1, 0, 0, 0x03D4),
    L2(3, 0, 0, 0, 1, 0, 0, 0x03D5),
    L2(3, 0, 0, 0, 1, 0, 0, 0x03D6),
    L2(3, 0, 0, 0, 1, 0, 0, 0x03D7),
    L2(3, 0, 0, 0, 1, 0, 0, 0x03D8),
    L2(3, 0, 0, 0, 1, 0, 0, 0x03D9),
    L2(3, 0, 0, 0, 1, 0, 0, 0x03DA),
    L2(3, 0, 0, 0, 1, 0, 0, 0x03DB),
    L2(3, 0, 0, 0, 1, 0, 0, 0x03DC),
    L2(3, 0, 0, 0, 1, 0, 0, 0x03DD),
    L2(250, 255, 0, 0, 1, 0, 0, 0x03DD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 164 */
const u16 plef_char_table_164_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_164[64] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x02E0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02E1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02E2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02E3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02E4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02E5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02E6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02E7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02E8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02E9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02EA),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02EB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x02EC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x02ED),
    L2(250, 255, 0, 0, 0, 0, 0, 0x02ED),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 165 */
const u16 plef_char_table_165_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 plef_char_table_165[52] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x02F0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02F1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02F2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02F3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02F4),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02F5),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02F6),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02F7),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02F8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02F9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02FA),
    L2(250, 255, 0, 0, 0, 0, 0, 0x02FA),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 ef01_char_table_000[], ef01_char_table_001[], ef01_char_table_002[], ef01_char_table_003[],
                 ef01_char_table_004[], ef01_char_table_005[], ef01_char_table_006[], ef01_char_table_008[],
                 ef01_char_table_009[], ef01_char_table_010[], ef01_char_table_011[], ef01_char_table_012[],
                 ef01_char_table_013[], ef01_char_table_014[], ef01_char_table_015[], ef01_char_table_016[],
                 ef01_char_table_017[], ef01_char_table_018[], ef01_char_table_019[], ef01_char_table_020[],
                 ef01_char_table_021[], ef01_char_table_022[], ef01_char_table_023[];

/* ef01_char_table: 24 entries; debug viewer: EFF01 CHAR; used by EFF02, EFF15, EFFA7, EFFC7, dbg_work */
const u32 ef01_char_table[25] = {
    (u32)ef01_char_table_000,  /* 0 */
    (u32)ef01_char_table_001,  /* 1 */
    (u32)ef01_char_table_002,  /* 2 */
    (u32)ef01_char_table_003,  /* 3 */
    (u32)ef01_char_table_004,  /* 4 */
    (u32)ef01_char_table_005,  /* 5 */
    (u32)ef01_char_table_006,  /* 6 */
    (u32)ef01_char_table_006,  /* 7 */
    (u32)ef01_char_table_008,  /* 8 */
    (u32)ef01_char_table_009,  /* 9 */
    (u32)ef01_char_table_010,  /* 10 */
    (u32)ef01_char_table_011,  /* 11 */
    (u32)ef01_char_table_012,  /* 12 */
    (u32)ef01_char_table_013,  /* 13 */
    (u32)ef01_char_table_014,  /* 14 */
    (u32)ef01_char_table_015,  /* 15 */
    (u32)ef01_char_table_016,  /* 16 */
    (u32)ef01_char_table_017,  /* 17 */
    (u32)ef01_char_table_018,  /* 18 */
    (u32)ef01_char_table_019,  /* 19 */
    (u32)ef01_char_table_020,  /* 20 */
    (u32)ef01_char_table_021,  /* 21 */
    (u32)ef01_char_table_022,  /* 22 */
    (u32)ef01_char_table_023,  /* 23 */
    0
};

/* script: 0 */
const u16 ef01_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_000[44] = {
    L2(2, 0, 265, 0, 0, 0, 0, 0x774F),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7750),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7751),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7752),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7753),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7754),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7755),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7756),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7757),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7757),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 ef01_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_001[36] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x7748),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7749),
    L2(2, 0, 0, 0, 0, 0, 0, 0x774A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x774B),
    L2(1, 0, 0, 0, 0, 0, 0, 0x774C),
    L2(1, 0, 0, 0, 0, 0, 0, 0x774D),
    L2(1, 0, 0, 0, 0, 0, 0, 0x774E),
    L2(250, 255, 0, 0, 0, 0, 0, 0x774E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 ef01_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_002[36] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x7803),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7804),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7805),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7806),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7807),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7808),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7809),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7809),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 ef01_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_003[40] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x6E91),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6E92),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6E93),
    L2(1, 0, 0, 0, 0, 0, 0, 0x6E94),
    L2(1, 0, 0, 0, 0, 0, 0, 0x6E95),
    L2(1, 0, 0, 0, 0, 0, 0, 0x6E96),
    L2(1, 0, 0, 0, 0, 0, 0, 0x6E97),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6E98),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E98),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 ef01_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_004[32] = {
    CMD(CM_EXEC, 29, 0, 0),
    L2(3, 1, 0, 0, 0, 0, 0, 0x7759),
    L2(1, 0, 0, 0, 0, 0, 0, 0x775A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x775B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x775C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x775D),
    L2(250, 255, 0, 0, 0, 0, 0, 0x775D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 ef01_char_table_005_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_005[32] = {
    CMD(CM_EXEC, 29, 1, 0),
    L2(3, 1, 0, 0, 0, 0, 0, 0x775F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7760),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7761),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7762),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7763),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7763),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 6, 7 */
const u16 ef01_char_table_006_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_006[32] = {
    CMD(CM_EXEC, 29, 2, 0),
    L2(3, 1, 0, 0, 0, 0, 0, 0x7765),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7766),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7767),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7768),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7769),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7769),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 8 */
const u16 ef01_char_table_008_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_008[28] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x776B),
    L2(1, 0, 0, 0, 0, 0, 0, 0x776A),
    L2(1, 0, 0, 0, 0, 0, 0, 0x776B),
    CMD(CM_EXEC, 1, 2, 0),
    CMD(CM_EXEC, 1, 3, 0),
    CMD(CM_JMP, 0, 10, 6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 9 */
const u16 ef01_char_table_009_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_009[28] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x776B),
    L2(1, 0, 0, 0, 0, 0, 0, 0x776A),
    L2(1, 0, 0, 0, 0, 0, 0, 0x776B),
    CMD(CM_EXEC, 1, 4, 0),
    CMD(CM_EXEC, 1, 5, 0),
    CMD(CM_JMP, 0, 10, 6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 10 */
const u16 ef01_char_table_010_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_010[48] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x776B),
    L2(1, 0, 0, 0, 0, 0, 0, 0x776A),
    L2(1, 0, 0, 0, 0, 0, 0, 0x776B),
    CMD(CM_EXEC, 1, 6, 0),
    CMD(CM_EXEC, 1, 7, 0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x776C),
    L2(3, 0, 0, 0, 0, 0, 0, 0x776D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x776E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x776F),
    L2(3, 0, 0, 0, 0, 0, 0, 0x7770),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7770),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 11 */
const u16 ef01_char_table_011_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_011[28] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x776B),
    L2(1, 0, 0, 0, 0, 0, 0, 0x776A),
    L2(1, 0, 0, 0, 0, 0, 0, 0x776B),
    CMD(CM_EXEC, 1, 8, 0),
    CMD(CM_EXEC, 1, 9, 0),
    CMD(CM_JMP, 0, 10, 6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 12 */
const u16 ef01_char_table_012_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_012[40] = {
    L2(1, 0, 0, 0, 0, 0, 0, 0x6FAE),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FAF),
    L2(2, 0, 0, 0, 0, 0, 0, 0x6FB0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6FB1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6FB2),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6FB3),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6FB4),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6FB5),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6FB5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 ef01_char_table_013_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_013[92] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x780A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x780B),
    L2(1, 0, 0, 0, 0, 0, 0, 0x780C),
    L2(1, 0, 0, 0, 0, 0, 0, 0x780D),
    L2(1, 0, 0, 0, 0, 0, 0, 0x780E),
    L2(1, 0, 0, 0, 0, 0, 0, 0x780F),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7810),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7811),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7812),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7813),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7814),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7815),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7816),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7817),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7818),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7819),
    L2(2, 0, 0, 0, 0, 0, 0, 0x781A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x781B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x781C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x781D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x781E),
    L2(250, 255, 0, 0, 0, 0, 0, 0x781E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 ef01_char_table_014_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_014[20] = {
    CMD(CM_EXEC, 1, 2, 0),
    CMD(CM_EXEC, 1, 3, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0000),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0000),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 ef01_char_table_015_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_015[20] = {
    CMD(CM_EXEC, 1, 4, 0),
    CMD(CM_EXEC, 1, 5, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0000),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0000),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 16 */
const u16 ef01_char_table_016_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_016[20] = {
    CMD(CM_EXEC, 1, 6, 0),
    CMD(CM_EXEC, 1, 7, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0000),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0000),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 17 */
const u16 ef01_char_table_017_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_017[20] = {
    CMD(CM_EXEC, 1, 8, 0),
    CMD(CM_EXEC, 1, 9, 0),
    L2(8, 0, 0, 0, 0, 0, 0, 0x0000),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0000),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 18 */
const u16 ef01_char_table_018_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_018[40] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x776B),
    L2(1, 0, 0, 0, 0, 0, 0, 0x776A),
    L2(1, 0, 0, 0, 0, 0, 0, 0x776B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x776C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x776D),
    L2(3, 0, 0, 0, 0, 0, 0, 0x776E),
    L2(3, 0, 0, 0, 0, 0, 0, 0x776F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x7770),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7770),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 19 */
const u16 ef01_char_table_019_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_019[28] = {
    L2(2, 0, 0, 0, 1, 0, 0, 0x7036),
    L2(1, 0, 0, 0, 1, 0, 0, 0x7032),
    L2(2, 0, 0, 0, 1, 0, 0, 0x7033),
    L2(3, 0, 0, 0, 1, 0, 0, 0x7034),
    L2(4, 0, 0, 0, 1, 0, 0, 0x7035),
    L2(250, 255, 0, 0, 1, 0, 0, 0x7035),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 20 */
const u16 ef01_char_table_020_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_020[76] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x03E5),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03DE),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03DF),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03E0),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03E1),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03E2),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03E3),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03E4),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03E5),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03E6),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03E7),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03E8),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03E9),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03EA),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03EB),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03EC),
    L2(1, 0, 0, 0, 0, 0, 0, 0x03ED),
    L2(250, 255, 0, 0, 0, 0, 0, 0x03ED),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 21 */
const u16 ef01_char_table_021_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_021[184] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x4020),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4021),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4022),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4023),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4024),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4025),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4026),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4027),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4028),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4029),
    L2(4, 0, 0, 0, 0, 0, 0, 0x402A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x402B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x402C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x402D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x402E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x402F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4030),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4031),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4032),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4033),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4034),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4035),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4036),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4037),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4038),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4039),
    L2(4, 0, 0, 0, 0, 0, 0, 0x403A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x403B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x403C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x403D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x403E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x403F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4040),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4041),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4042),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4043),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4044),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4045),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4046),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4047),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4048),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4049),
    L2(4, 0, 0, 0, 0, 0, 0, 0x404A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x404B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x404C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 22 */
const u16 ef01_char_table_022_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_022[108] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x404D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x404E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x404F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4050),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4051),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4052),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4053),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4054),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4055),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4056),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4057),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4058),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4059),
    L2(4, 0, 0, 0, 0, 0, 0, 0x405A),
    L2(4, 0, 0, 0, 0, 0, 0, 0x405B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x405C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x405D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x405E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x405F),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4060),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4061),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4062),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4063),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4064),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4065),
    L2(4, 0, 0, 0, 0, 0, 0, 0x4066),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 23 */
const u16 ef01_char_table_023_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef01_char_table_023[12] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x6FE5),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6FE5),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 ef13_char_table_000[], ef13_char_table_001[], ef13_char_table_002[], ef13_char_table_003[],
                 ef13_char_table_004[], ef13_char_table_005[], ef13_char_table_006[], ef13_char_table_007[],
                 ef13_char_table_008[], ef13_char_table_010[], ef13_char_table_011[], ef13_char_table_013[],
                 ef13_char_table_014[], ef13_char_table_015[], ef13_char_table_016[], ef13_char_table_017[],
                 ef13_char_table_018[], ef13_char_table_019[], ef13_char_table_020[], ef13_char_table_021[],
                 ef13_char_table_022[], ef13_char_table_023[], ef13_char_table_024[], ef13_char_table_025[],
                 ef13_char_table_026[], ef13_char_table_027[], ef13_char_table_028[], ef13_char_table_029[],
                 ef13_char_table_030[], ef13_char_table_031[], ef13_char_table_032[], ef13_char_table_033[],
                 ef13_char_table_034[], ef13_char_table_035[], ef13_char_table_036[], ef13_char_table_037[],
                 ef13_char_table_038[], ef13_char_table_039[], ef13_char_table_040[], ef13_char_table_041[],
                 ef13_char_table_042[], ef13_char_table_043[], ef13_char_table_044[], ef13_char_table_045[],
                 ef13_char_table_046[], ef13_char_table_047[], ef13_char_table_048[], ef13_char_table_049[],
                 ef13_char_table_050[], ef13_char_table_051[], ef13_char_table_052[], ef13_char_table_053[],
                 ef13_char_table_056[], ef13_char_table_057[], ef13_char_table_058[], ef13_char_table_059[],
                 ef13_char_table_060[], ef13_char_table_061[], ef13_char_table_062[], ef13_char_table_063[],
                 ef13_char_table_064[], ef13_char_table_065[], ef13_char_table_066[], ef13_char_table_067[],
                 ef13_char_table_068[], ef13_char_table_069[], ef13_char_table_070[], ef13_char_table_071[],
                 ef13_char_table_072[], ef13_char_table_073[], ef13_char_table_074[], ef13_char_table_075[],
                 ef13_char_table_076[], ef13_char_table_077[], ef13_char_table_078[], ef13_char_table_079[],
                 ef13_char_table_080[], ef13_char_table_081[], ef13_char_table_082[], ef13_char_table_083[],
                 ef13_char_table_084[], ef13_char_table_085[], ef13_char_table_086[], ef13_char_table_087[],
                 ef13_char_table_088[], ef13_char_table_089[], ef13_char_table_090[], ef13_char_table_091[],
                 ef13_char_table_092[], ef13_char_table_093[], ef13_char_table_094[], ef13_char_table_095[],
                 ef13_char_table_096[], ef13_char_table_097[], ef13_char_table_098[], ef13_char_table_099[],
                 ef13_char_table_100[], ef13_char_table_101[], ef13_char_table_102[], ef13_char_table_103[],
                 ef13_char_table_104[], ef13_char_table_105[], ef13_char_table_106[], ef13_char_table_107[],
                 ef13_char_table_108[], ef13_char_table_109[], ef13_char_table_110[], ef13_char_table_111[],
                 ef13_char_table_112[], ef13_char_table_113[], ef13_char_table_114[], ef13_char_table_115[],
                 ef13_char_table_116[], ef13_char_table_117[], ef13_char_table_118[], ef13_char_table_119[],
                 ef13_char_table_120[], ef13_char_table_121[], ef13_char_table_122[], ef13_char_table_123[],
                 ef13_char_table_124[], ef13_char_table_125[], ef13_char_table_126[], ef13_char_table_127[],
                 ef13_char_table_128[], ef13_char_table_129[], ef13_char_table_130[], ef13_char_table_131[],
                 ef13_char_table_132[], ef13_char_table_133[], ef13_char_table_134[], ef13_char_table_135[],
                 ef13_char_table_136[], ef13_char_table_137[], ef13_char_table_138[], ef13_char_table_139[],
                 ef13_char_table_140[], ef13_char_table_141[], ef13_char_table_142[], ef13_char_table_143[],
                 ef13_char_table_144[], ef13_char_table_145[], ef13_char_table_146[], ef13_char_table_147[],
                 ef13_char_table_148[], ef13_char_table_149[], ef13_char_table_150[], ef13_char_table_151[],
                 ef13_char_table_152[], ef13_char_table_153[], ef13_char_table_154[], ef13_char_table_155[],
                 ef13_char_table_156[], ef13_char_table_157[], ef13_char_table_158[], ef13_char_table_159[],
                 ef13_char_table_160[], ef13_char_table_161[], ef13_char_table_162[], ef13_char_table_163[],
                 ef13_char_table_164[], ef13_char_table_165[], ef13_char_table_166[], ef13_char_table_167[],
                 ef13_char_table_168[], ef13_char_table_169[], ef13_char_table_170[], ef13_char_table_171[],
                 ef13_char_table_172[], ef13_char_table_173[], ef13_char_table_174[], ef13_char_table_175[],
                 ef13_char_table_176[], ef13_char_table_177[], ef13_char_table_178[], ef13_char_table_179[],
                 ef13_char_table_180[], ef13_char_table_181[], ef13_char_table_182[], ef13_char_table_183[],
                 ef13_char_table_184[], ef13_char_table_185[], ef13_char_table_186[], ef13_char_table_187[],
                 ef13_char_table_188[], ef13_char_table_189[], ef13_char_table_190[], ef13_char_table_191[],
                 ef13_char_table_192[], ef13_char_table_193[], ef13_char_table_194[];

/* ef13_char_table: 195 entries; debug viewer: EFF13 CHAR; used by EFF96, dbg_work */
const u32 ef13_char_table[196] = {
    (u32)ef13_char_table_000,  /* 0 */
    (u32)ef13_char_table_001,  /* 1 */
    (u32)ef13_char_table_002,  /* 2 */
    (u32)ef13_char_table_003,  /* 3 */
    (u32)ef13_char_table_004,  /* 4 */
    (u32)ef13_char_table_005,  /* 5 */
    (u32)ef13_char_table_006,  /* 6 */
    (u32)ef13_char_table_007,  /* 7 */
    (u32)ef13_char_table_008,  /* 8 */
    (u32)ef13_char_table_006,  /* 9 */
    (u32)ef13_char_table_010,  /* 10 */
    (u32)ef13_char_table_011,  /* 11 */
    (u32)ef13_char_table_011,  /* 12 */
    (u32)ef13_char_table_013,  /* 13 */
    (u32)ef13_char_table_014,  /* 14 */
    (u32)ef13_char_table_015,  /* 15 */
    (u32)ef13_char_table_016,  /* 16 */
    (u32)ef13_char_table_017,  /* 17 */
    (u32)ef13_char_table_018,  /* 18 */
    (u32)ef13_char_table_019,  /* 19 */
    (u32)ef13_char_table_020,  /* 20 */
    (u32)ef13_char_table_021,  /* 21 */
    (u32)ef13_char_table_022,  /* 22 */
    (u32)ef13_char_table_023,  /* 23 */
    (u32)ef13_char_table_024,  /* 24 */
    (u32)ef13_char_table_025,  /* 25 */
    (u32)ef13_char_table_026,  /* 26 */
    (u32)ef13_char_table_027,  /* 27 */
    (u32)ef13_char_table_028,  /* 28 */
    (u32)ef13_char_table_029,  /* 29 */
    (u32)ef13_char_table_030,  /* 30 */
    (u32)ef13_char_table_031,  /* 31 */
    (u32)ef13_char_table_032,  /* 32 */
    (u32)ef13_char_table_033,  /* 33 */
    (u32)ef13_char_table_034,  /* 34 */
    (u32)ef13_char_table_035,  /* 35 */
    (u32)ef13_char_table_036,  /* 36 */
    (u32)ef13_char_table_037,  /* 37 */
    (u32)ef13_char_table_038,  /* 38 */
    (u32)ef13_char_table_039,  /* 39 */
    (u32)ef13_char_table_040,  /* 40 */
    (u32)ef13_char_table_041,  /* 41 */
    (u32)ef13_char_table_042,  /* 42 */
    (u32)ef13_char_table_043,  /* 43 */
    (u32)ef13_char_table_044,  /* 44 */
    (u32)ef13_char_table_045,  /* 45 */
    (u32)ef13_char_table_046,  /* 46 */
    (u32)ef13_char_table_047,  /* 47 */
    (u32)ef13_char_table_048,  /* 48 */
    (u32)ef13_char_table_049,  /* 49 */
    (u32)ef13_char_table_050,  /* 50 */
    (u32)ef13_char_table_051,  /* 51 */
    (u32)ef13_char_table_052,  /* 52 */
    (u32)ef13_char_table_053,  /* 53 */
    (u32)ef13_char_table_053,  /* 54 */
    (u32)ef13_char_table_053,  /* 55 */
    (u32)ef13_char_table_056,  /* 56 */
    (u32)ef13_char_table_057,  /* 57 */
    (u32)ef13_char_table_058,  /* 58 */
    (u32)ef13_char_table_059,  /* 59 */
    (u32)ef13_char_table_060,  /* 60 */
    (u32)ef13_char_table_061,  /* 61 */
    (u32)ef13_char_table_062,  /* 62 */
    (u32)ef13_char_table_063,  /* 63 */
    (u32)ef13_char_table_064,  /* 64 */
    (u32)ef13_char_table_065,  /* 65 */
    (u32)ef13_char_table_066,  /* 66 */
    (u32)ef13_char_table_067,  /* 67 */
    (u32)ef13_char_table_068,  /* 68 */
    (u32)ef13_char_table_069,  /* 69 */
    (u32)ef13_char_table_070,  /* 70 */
    (u32)ef13_char_table_071,  /* 71 */
    (u32)ef13_char_table_072,  /* 72 */
    (u32)ef13_char_table_073,  /* 73 */
    (u32)ef13_char_table_074,  /* 74 */
    (u32)ef13_char_table_075,  /* 75 */
    (u32)ef13_char_table_076,  /* 76 */
    (u32)ef13_char_table_077,  /* 77 */
    (u32)ef13_char_table_078,  /* 78 */
    (u32)ef13_char_table_079,  /* 79 */
    (u32)ef13_char_table_080,  /* 80 */
    (u32)ef13_char_table_081,  /* 81 */
    (u32)ef13_char_table_082,  /* 82 */
    (u32)ef13_char_table_083,  /* 83 */
    (u32)ef13_char_table_084,  /* 84 */
    (u32)ef13_char_table_085,  /* 85 */
    (u32)ef13_char_table_086,  /* 86 */
    (u32)ef13_char_table_087,  /* 87 */
    (u32)ef13_char_table_088,  /* 88 */
    (u32)ef13_char_table_089,  /* 89 */
    (u32)ef13_char_table_090,  /* 90 */
    (u32)ef13_char_table_091,  /* 91 */
    (u32)ef13_char_table_092,  /* 92 */
    (u32)ef13_char_table_093,  /* 93 */
    (u32)ef13_char_table_094,  /* 94 */
    (u32)ef13_char_table_095,  /* 95 */
    (u32)ef13_char_table_096,  /* 96 */
    (u32)ef13_char_table_097,  /* 97 */
    (u32)ef13_char_table_098,  /* 98 */
    (u32)ef13_char_table_099,  /* 99 */
    (u32)ef13_char_table_100,  /* 100 */
    (u32)ef13_char_table_101,  /* 101 */
    (u32)ef13_char_table_102,  /* 102 */
    (u32)ef13_char_table_103,  /* 103 */
    (u32)ef13_char_table_104,  /* 104 */
    (u32)ef13_char_table_105,  /* 105 */
    (u32)ef13_char_table_106,  /* 106 */
    (u32)ef13_char_table_107,  /* 107 */
    (u32)ef13_char_table_108,  /* 108 */
    (u32)ef13_char_table_109,  /* 109 */
    (u32)ef13_char_table_110,  /* 110 */
    (u32)ef13_char_table_111,  /* 111 */
    (u32)ef13_char_table_112,  /* 112 */
    (u32)ef13_char_table_113,  /* 113 */
    (u32)ef13_char_table_114,  /* 114 */
    (u32)ef13_char_table_115,  /* 115 */
    (u32)ef13_char_table_116,  /* 116 */
    (u32)ef13_char_table_117,  /* 117 */
    (u32)ef13_char_table_118,  /* 118 */
    (u32)ef13_char_table_119,  /* 119 */
    (u32)ef13_char_table_120,  /* 120 */
    (u32)ef13_char_table_121,  /* 121 */
    (u32)ef13_char_table_122,  /* 122 */
    (u32)ef13_char_table_123,  /* 123 */
    (u32)ef13_char_table_124,  /* 124 */
    (u32)ef13_char_table_125,  /* 125 */
    (u32)ef13_char_table_126,  /* 126 */
    (u32)ef13_char_table_127,  /* 127 */
    (u32)ef13_char_table_128,  /* 128 */
    (u32)ef13_char_table_129,  /* 129 */
    (u32)ef13_char_table_130,  /* 130 */
    (u32)ef13_char_table_131,  /* 131 */
    (u32)ef13_char_table_132,  /* 132 */
    (u32)ef13_char_table_133,  /* 133 */
    (u32)ef13_char_table_134,  /* 134 */
    (u32)ef13_char_table_135,  /* 135 */
    (u32)ef13_char_table_136,  /* 136 */
    (u32)ef13_char_table_137,  /* 137 */
    (u32)ef13_char_table_138,  /* 138 */
    (u32)ef13_char_table_139,  /* 139 */
    (u32)ef13_char_table_140,  /* 140 */
    (u32)ef13_char_table_141,  /* 141 */
    (u32)ef13_char_table_142,  /* 142 */
    (u32)ef13_char_table_143,  /* 143 */
    (u32)ef13_char_table_144,  /* 144 */
    (u32)ef13_char_table_145,  /* 145 */
    (u32)ef13_char_table_146,  /* 146 */
    (u32)ef13_char_table_147,  /* 147 */
    (u32)ef13_char_table_148,  /* 148 */
    (u32)ef13_char_table_149,  /* 149 */
    (u32)ef13_char_table_150,  /* 150 */
    (u32)ef13_char_table_151,  /* 151 */
    (u32)ef13_char_table_152,  /* 152 */
    (u32)ef13_char_table_153,  /* 153 */
    (u32)ef13_char_table_154,  /* 154 */
    (u32)ef13_char_table_155,  /* 155 */
    (u32)ef13_char_table_156,  /* 156 */
    (u32)ef13_char_table_157,  /* 157 */
    (u32)ef13_char_table_158,  /* 158 */
    (u32)ef13_char_table_159,  /* 159 */
    (u32)ef13_char_table_160,  /* 160 */
    (u32)ef13_char_table_161,  /* 161 */
    (u32)ef13_char_table_162,  /* 162 */
    (u32)ef13_char_table_163,  /* 163 */
    (u32)ef13_char_table_164,  /* 164 */
    (u32)ef13_char_table_165,  /* 165 */
    (u32)ef13_char_table_166,  /* 166 */
    (u32)ef13_char_table_167,  /* 167 */
    (u32)ef13_char_table_168,  /* 168 */
    (u32)ef13_char_table_169,  /* 169 */
    (u32)ef13_char_table_170,  /* 170 */
    (u32)ef13_char_table_171,  /* 171 */
    (u32)ef13_char_table_172,  /* 172 */
    (u32)ef13_char_table_173,  /* 173 */
    (u32)ef13_char_table_174,  /* 174 */
    (u32)ef13_char_table_175,  /* 175 */
    (u32)ef13_char_table_176,  /* 176 */
    (u32)ef13_char_table_177,  /* 177 */
    (u32)ef13_char_table_178,  /* 178 */
    (u32)ef13_char_table_179,  /* 179 */
    (u32)ef13_char_table_180,  /* 180 */
    (u32)ef13_char_table_181,  /* 181 */
    (u32)ef13_char_table_182,  /* 182 */
    (u32)ef13_char_table_183,  /* 183 */
    (u32)ef13_char_table_184,  /* 184 */
    (u32)ef13_char_table_185,  /* 185 */
    (u32)ef13_char_table_186,  /* 186 */
    (u32)ef13_char_table_187,  /* 187 */
    (u32)ef13_char_table_188,  /* 188 */
    (u32)ef13_char_table_189,  /* 189 */
    (u32)ef13_char_table_190,  /* 190 */
    (u32)ef13_char_table_191,  /* 191 */
    (u32)ef13_char_table_192,  /* 192 */
    (u32)ef13_char_table_193,  /* 193 */
    (u32)ef13_char_table_194,  /* 194 */
    0
};

/* script: 0 */
const u16 ef13_char_table_000_head[4] = { HEAD(4, 0, 8, 10, 0, 6, 0) };
const u16 ef13_char_table_000[84] = {
    L4(2, 0, 0, 0, 0, 0, 0, 0x706E, -1, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70EC, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70F0, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70ED, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70F1, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70EE, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70F2, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70EF, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70F3, 0, 2, 0, 0, 0, 0),
    CMD(CM_IXBW, 0, 0, 8), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 1 */
const u16 ef13_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_001[32] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x6E81),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6E82),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6E83),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6E84),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6E85),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6E86),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E86),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 ef13_char_table_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_002[32] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x7043),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7044),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7045),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7046),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7047),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7047),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7047),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 3 */
const u16 ef13_char_table_003_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_003[12] = {
    L2(2, 0, 267, 0, 0, 0, 0, 0x70F3),
    CMD(CM_JMP, 0, 2, 2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 4 */
const u16 ef13_char_table_004_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_004[12] = {
    L2(2, 0, 266, 0, 0, 0, 0, 0x70F3),
    CMD(CM_JMP, 0, 2, 2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 5 */
const u16 ef13_char_table_005_head[4] = { HEAD(4, 0, 48, 10, 0, 10, 4) };
const u16 ef13_char_table_005[172] = {
    L4(1, 0, 0, 0, 0, 0, 0, 0x706E, -2, 1, 80, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7130, 2, 2, 80, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x70F1, 2, 2, 80, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7131, 2, 2, 80, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x70F2, 2, 2, 80, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7132, 2, 2, 80, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x70F3, 2, 2, 80, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7114, 2, 2, 80, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x70F1, 2, 2, 80, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7115, 2, 2, 80, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x70F2, 2, 2, 80, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7116, 2, 2, 80, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x70F3, 2, 2, 80, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7117, 2, 2, 80, 0, 0, 0),
    CMD(CM_IXBW, 0, 0, 13), 0, 0, 0, 0,
    L4(1, 0, 0, 0, 0, 0, 0, 0x70F0, -2, 2, 83, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7130, 2, 2, 83, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x70F0, 2, 2, 83, 0, 0, 0),
    CMD(CM_WCLT, 16399, 4, -32765), 0, 0, 0, 0,
    L4(1, 0, 0, 0, 0, 0, 0, 0x7130, -3, 1, 0, 0, 0, 0),
    CMD(CM_IXBW, 0, 0, 1), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 6, 9 */
const u16 ef13_char_table_006_head[4] = { HEAD(4, 0, 32, 10, 0, 10, 5) };
const u16 ef13_char_table_006[164] = {
    L4(1, 0, 0, 0, 0, 0, 0, 0x7138, -4, 1, 75, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7138, -4, 2, 75, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7134, 4, 2, 75, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7139, 0, 2, 75, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7135, 0, 2, 75, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x713A, 0, 2, 75, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7136, 0, 2, 75, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x713B, 0, 2, 75, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7137, 0, 2, 75, 0, 0, 0),
    CMD(CM_IXBW, 0, 0, 8), 0, 0, 0, 0,
    L4(1, 0, 0, 0, 0, 0, 0, 0x7138, -5, 2, 66, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7138, -5, 2, 66, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7134, 0, 2, 66, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7139, 0, 2, 66, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7135, 0, 2, 66, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x713A, 0, 2, 66, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7136, 0, 2, 66, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x713B, 0, 2, 66, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7137, 0, 2, 66, 0, 0, 0),
    CMD(CM_IXBW, 0, 0, 8), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 7 */
const u16 ef13_char_table_007_head[4] = { HEAD(4, 0, 8, 10, 0, 6, 0) };
const u16 ef13_char_table_007[84] = {
    L4(2, 0, 0, 0, 0, 0, 0, 0x706E, -25, 1, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70EC, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70F0, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70ED, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70F1, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70EE, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70F2, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70EF, 0, 2, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70F3, 0, 2, 0, 0, 0, 0),
    CMD(CM_END, 0, 0, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 8 */
const u16 ef13_char_table_008_head[4] = { HEAD(4, 0, 48, 10, 0, 10, 4) };
const u16 ef13_char_table_008[180] = {
    L4(1, 0, 0, 0, 0, 0, 0, 0x7100, -26, 1, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7101, 27, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7102, 26, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7103, 27, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7104, 26, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7105, 27, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7106, 26, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7107, 27, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7108, 27, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7109, 27, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x710A, 27, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x710B, 27, 2, 74, 0, 0, 0),
    CMD(CM_IXBW, 0, 0, 12), 0, 0, 0, 0,
    L4(1, 0, 0, 0, 0, 0, 0, 0x7100, -26, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7104, 27, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7101, 26, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7105, 27, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7102, 26, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7106, 27, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7103, 26, 2, 74, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7107, 27, 2, 74, 0, 0, 0),
    CMD(CM_IXBW, 0, 0, 8), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 10 */
const u16 ef13_char_table_010_head[4] = { HEAD(4, 0, 48, 10, 0, 10, 5) };
const u16 ef13_char_table_010[148] = {
    L4(1, 0, 0, 0, 0, 0, 0, 0x1793, -6, 22, 0, 0, 0, 0),
    CMD(CM_FOR, 0, 0, 3), 0, 0, 0, 0,
    L4(2, 0, 0, 0, 0, 0, 0, 0x1794, 0, 22, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x1794, 0, 22, 0, 0, 1, 33),
    CMD(CM_PA_X, 0, 28672, 0), 0, 0, 0, 0,
    L4(2, 0, 0, 0, 0, 0, 0, 0x179B, 0, 23, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x179C, 0, 24, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x179D, 0, 25, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x179E, 0, 22, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x179F, 0, 22, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x179F, 0, 22, 0, 0, 1, 33),
    CMD(CM_PA_X, 0, 28672, 0), 0, 0, 0, 0,
    L4(2, 0, 0, 0, 0, 0, 0, 0x1790, 0, 23, 0, 0, 0, 0),
    L4(3, 0, 0, 0, 0, 0, 0, 0x1791, 0, 24, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x1792, 0, 25, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x1793, 0, 22, 0, 0, 0, 0),
    CMD(CM_NEX, 0, 0, 0), 0, 0, 0, 0,
    CMD(CM_JMP, 0, 11, 1), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 11, 12 */
const u16 ef13_char_table_011_head[4] = { HEAD(2, 0, 48, 10, 0, 10, 5) };
const u16 ef13_char_table_011[32] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x1795),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1796),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1797),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1798),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1799),
    L2(3, 0, 0, 0, 0, 0, 0, 0x179A),
    L2(250, 255, 0, 0, 0, 0, 0, 0x179A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 13 */
const u16 ef13_char_table_013_head[4] = { HEAD(2, 0, 48, 10, 0, 10, 5) };
const u16 ef13_char_table_013[12] = {
    L2(3, 0, 267, 0, 0, 0, 0, 0x1795),
    CMD(CM_JMP, 0, 11, 2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 14 */
const u16 ef13_char_table_014_head[4] = { HEAD(2, 0, 48, 10, 0, 10, 5) };
const u16 ef13_char_table_014[12] = {
    L2(3, 0, 266, 0, 0, 0, 0, 0x1795),
    CMD(CM_JMP, 0, 11, 2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 15 */
const u16 ef13_char_table_015_head[4] = { HEAD(4, 0, 32, 10, 0, 6, 0) };
const u16 ef13_char_table_015[100] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x7080, 7, 3, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7081, 7, 3, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7082, 7, 3, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7083, 7, 3, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7084, 7, 3, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7085, 7, 3, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7086, 7, 3, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7087, 7, 3, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7088, 7, 3, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7089, 7, 3, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x708A, 7, 3, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x708B, 7, 3, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 16 */
const u16 ef13_char_table_016_head[4] = { HEAD(4, 0, 32, 10, 0, 6, 0) };
const u16 ef13_char_table_016[100] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x714C, 8, 4, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x714D, 8, 4, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x714E, 8, 4, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x714F, 8, 4, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7150, 8, 4, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7151, 8, 4, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7152, 8, 4, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7153, 8, 4, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7154, 8, 4, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7155, 8, 4, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7156, 8, 4, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7157, 8, 4, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 17 */
const u16 ef13_char_table_017_head[4] = { HEAD(4, 0, 32, 10, 0, 6, 0) };
const u16 ef13_char_table_017[100] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x7158, 9, 5, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7159, 9, 5, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x715A, 9, 5, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x715B, 9, 5, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x715C, 9, 5, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x715D, 9, 5, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x715E, 9, 5, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x715F, 9, 5, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7160, 9, 5, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7161, 9, 5, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7162, 9, 5, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7163, 9, 5, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 18 */
const u16 ef13_char_table_018_head[4] = { HEAD(4, 0, 32, 10, 0, 6, 0) };
const u16 ef13_char_table_018[100] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x7164, 10, 6, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7165, 10, 6, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7166, 10, 6, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7167, 10, 6, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7168, 10, 6, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7169, 10, 6, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x716A, 10, 6, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x716B, 10, 6, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x716C, 10, 6, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x716D, 10, 6, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x716E, 10, 6, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x716F, 10, 6, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 19 */
const u16 ef13_char_table_019_head[4] = { HEAD(4, 0, 32, 10, 0, 6, 0) };
const u16 ef13_char_table_019[100] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x7170, 11, 7, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7171, 11, 7, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7172, 11, 7, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7173, 11, 7, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7174, 11, 7, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7175, 11, 7, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7176, 11, 7, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7177, 11, 7, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7178, 11, 7, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7179, 11, 7, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x717A, 11, 7, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x717B, 11, 7, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 20 */
const u16 ef13_char_table_020_head[4] = { HEAD(4, 0, 32, 10, 0, 6, 0) };
const u16 ef13_char_table_020[68] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x717C, 12, 9, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x717D, 12, 9, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x717E, 12, 9, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x717F, 12, 9, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7180, 12, 9, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7181, 12, 9, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7182, 12, 9, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7183, 12, 9, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 21 */
const u16 ef13_char_table_021_head[4] = { HEAD(4, 0, 32, 10, 0, 6, 0) };
const u16 ef13_char_table_021[68] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x7184, 13, 10, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7185, 13, 10, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7186, 13, 10, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7187, 13, 10, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7188, 13, 10, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7189, 13, 10, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x718A, 13, 10, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x718B, 13, 10, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 22 */
const u16 ef13_char_table_022_head[4] = { HEAD(4, 0, 32, 10, 0, 6, 0) };
const u16 ef13_char_table_022[100] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x718C, 14, 11, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x718D, 14, 11, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x718E, 14, 11, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x718F, 14, 11, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7190, 14, 11, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7191, 14, 11, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7192, 14, 11, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7193, 14, 11, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7194, 14, 11, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7195, 14, 11, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7196, 14, 11, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7197, 14, 11, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 23 */
const u16 ef13_char_table_023_head[4] = { HEAD(4, 0, 32, 10, 0, 6, 0) };
const u16 ef13_char_table_023[100] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x7198, 15, 12, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x7199, 15, 12, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x719A, 15, 12, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x719B, 15, 12, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x719C, 15, 12, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x719D, 15, 12, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x719E, 15, 12, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x719F, 15, 12, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71A0, 15, 12, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71A1, 15, 12, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71A2, 15, 12, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71A3, 15, 12, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 24 */
const u16 ef13_char_table_024_head[4] = { HEAD(4, 0, 32, 10, 0, 6, 0) };
const u16 ef13_char_table_024[100] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x71A4, 16, 13, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71A5, 16, 13, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71A6, 16, 13, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71A7, 16, 13, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71A8, 16, 13, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71A9, 16, 13, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71AA, 16, 13, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71AB, 16, 13, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71AC, 16, 13, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71AD, 16, 13, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71AE, 16, 13, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71AF, 16, 13, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 25 */
const u16 ef13_char_table_025_head[4] = { HEAD(4, 0, 32, 10, 0, 6, 0) };
const u16 ef13_char_table_025[100] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x71B0, 17, 14, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71B1, 17, 14, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71B2, 17, 14, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71B3, 17, 14, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71B4, 17, 14, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71B5, 17, 14, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71B6, 17, 14, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71B7, 17, 14, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71B8, 17, 14, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71B9, 17, 14, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71BA, 17, 14, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71BB, 17, 14, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 26 */
const u16 ef13_char_table_026_head[4] = { HEAD(4, 0, 32, 10, 0, 6, 0) };
const u16 ef13_char_table_026[100] = {
    L4(4, 0, 0, 0, 0, 0, 0, 0x71BC, 18, 15, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71BD, 18, 15, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71BE, 18, 15, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71BF, 18, 15, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71C0, 18, 15, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71C1, 18, 15, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71C2, 18, 15, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71C3, 18, 15, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71C4, 18, 15, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71C5, 18, 15, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71C6, 18, 15, 0, 0, 0, 0),
    L4(4, 0, 0, 0, 0, 0, 0, 0x71C7, 18, 15, 0, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 27 */
const u16 ef13_char_table_027_head[4] = { HEAD(4, 0, 8, 10, 0, 6, 0) };
const u16 ef13_char_table_027[148] = {
    L4(2, 0, 0, 0, 0, 0, 0, 0x708C, -20, 27, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x708C, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x708D, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x708E, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0000, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x708F, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7090, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7091, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7092, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7093, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7094, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7095, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0000, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7096, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7097, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7098, 0, 20, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7099, 0, 20, 0, 0, 0, 0),
    CMD(CM_END, 0, 0, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 28 */
const u16 ef13_char_table_028_head[4] = { HEAD(2, 0, 8, 0, 0, 0, 0) };
const u16 ef13_char_table_028[64] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x709A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A7),
    L2(250, 255, 0, 0, 0, 0, 0, 0x70A7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 29 */
const u16 ef13_char_table_029_head[4] = { HEAD(2, 0, 8, 0, 0, 0, 0) };
const u16 ef13_char_table_029[64] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x709A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A7),
    L2(250, 255, 0, 0, 0, 0, 0, 0x70A7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 30 */
const u16 ef13_char_table_030_head[4] = { HEAD(2, 0, 8, 0, 0, 0, 0) };
const u16 ef13_char_table_030[64] = {
    L2(2, 0, 267, 0, 0, 0, 0, 0x709A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A7),
    L2(250, 255, 0, 0, 0, 0, 0, 0x70A7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 31 */
const u16 ef13_char_table_031_head[4] = { HEAD(2, 0, 8, 0, 0, 0, 0) };
const u16 ef13_char_table_031[64] = {
    L2(2, 0, 266, 0, 0, 0, 0, 0x709A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x709F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x70A7),
    L2(250, 255, 0, 0, 0, 0, 0, 0x70A7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 32 */
const u16 ef13_char_table_032_head[4] = { HEAD(4, 0, 48, 10, 0, 10, 4) };
const u16 ef13_char_table_032[140] = {
    CMD(CM_IXFW, 0, 0, 2), 0, 0, 0, 0,
    L4(2, 0, 0, 0, 0, 0, 1, 0x70CF, 0, 17, 66, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 1, 0x70C4, -19, 17, 66, 0, 0, 0),
    L4(2, 0, 335, 0, 0, 0, 1, 0x70C5, 0, 17, 66, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 1, 0x70C6, 0, 17, 66, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 1, 0x70C7, 0, 17, 66, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 1, 0x70C8, 0, 17, 66, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 1, 0x70C9, 0, 17, 66, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 1, 0x70CA, 0, 17, 66, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 1, 0x70CB, 0, 17, 66, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 1, 0x70CC, 0, 17, 66, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 1, 0x70CD, 0, 17, 66, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 1, 0x70CE, 0, 17, 66, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 1, 0x70CF, 0, 17, 66, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 1, 0x70C4, 0, 17, 66, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 1, 0x70C5, 0, 17, 66, 0, 0, 0),
    CMD(CM_END, 0, 0, 5), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 33 */
const u16 ef13_char_table_033_head[4] = { HEAD(2, 0, 48, 10, 0, 10, 4) };
const u16 ef13_char_table_033[28] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x70D0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D4),
    L2(250, 255, 0, 0, 0, 0, 0, 0x70D4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 34 */
const u16 ef13_char_table_034_head[4] = { HEAD(2, 0, 48, 10, 0, 10, 4) };
const u16 ef13_char_table_034[28] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x70D0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D4),
    L2(250, 255, 0, 0, 0, 0, 0, 0x70D4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 35 */
const u16 ef13_char_table_035_head[4] = { HEAD(2, 0, 48, 10, 0, 10, 4) };
const u16 ef13_char_table_035[28] = {
    L2(2, 0, 267, 0, 0, 0, 0, 0x70D0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D4),
    L2(250, 255, 0, 0, 0, 0, 0, 0x70D4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 36 */
const u16 ef13_char_table_036_head[4] = { HEAD(2, 0, 48, 10, 0, 10, 4) };
const u16 ef13_char_table_036[28] = {
    L2(2, 0, 266, 0, 0, 0, 0, 0x70D0),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x70D4),
    L2(250, 255, 0, 0, 0, 0, 0, 0x70D4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 37 */
const u16 ef13_char_table_037_head[4] = { HEAD(4, 0, 8, 10, 0, 6, 0) };
const u16 ef13_char_table_037[148] = {
    L4(2, 0, 0, 0, 0, 0, 0, 0x708C, -21, 28, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x708C, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x708D, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x708E, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0000, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x708F, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7090, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7091, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7092, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7093, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7094, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7095, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0000, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7096, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7097, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7098, 0, 30, 0, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7099, 0, 30, 0, 0, 0, 0),
    CMD(CM_END, 0, 0, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 38 */
const u16 ef13_char_table_038_head[4] = { HEAD(4, 0, 8, 10, 0, 6, 0) };
const u16 ef13_char_table_038[20] = {
    L4(2, 0, 0, 0, 0, 0, 0, 0x708C, -22, 29, 0, 0, 0, 0),
    CMD(CM_JMP, 0, 37, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 39 */
const u16 ef13_char_table_039_head[4] = { HEAD(4, 0, 8, 10, 0, 6, 0) };
const u16 ef13_char_table_039[20] = {
    L4(2, 0, 0, 0, 0, 0, 0, 0x708C, -23, 29, 0, 0, 0, 0),
    CMD(CM_JMP, 0, 27, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 40 */
const u16 ef13_char_table_040_head[4] = { HEAD(4, 0, 8, 10, 0, 6, 0) };
const u16 ef13_char_table_040[20] = {
    L4(2, 0, 0, 0, 0, 0, 0, 0x708C, -24, 16, 0, 0, 0, 0),
    CMD(CM_JMP, 0, 37, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 41 */
const u16 ef13_char_table_041_head[4] = { HEAD(4, 0, 8, 10, 0, 10, 0) };
const u16 ef13_char_table_041[84] = {
    L4(1, 0, 0, 0, 0, 0, 0, 0x7233, -28, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7233, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7234, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7235, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7236, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7237, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7238, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7239, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x723A, 0, 18, 0, 0, 0, 0),
    CMD(CM_END, 0, 0, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 42 */
const u16 ef13_char_table_042_head[4] = { HEAD(4, 0, 8, 10, 0, 10, 0) };
const u16 ef13_char_table_042[84] = {
    L4(1, 0, 0, 0, 0, 0, 0, 0x722B, -28, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x722B, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x722C, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x722D, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x722E, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x722F, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7230, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7231, 0, 18, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7232, 0, 18, 0, 0, 0, 0),
    CMD(CM_END, 0, 0, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 43 */
const u16 ef13_char_table_043_head[4] = { HEAD(4, 0, 8, 10, 0, 10, 0) };
const u16 ef13_char_table_043[84] = {
    L4(1, 0, 0, 0, 0, 0, 0, 0x7223, -28, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7223, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7224, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7225, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7226, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7227, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7228, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7229, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x722A, 0, 19, 0, 0, 0, 0),
    CMD(CM_END, 0, 0, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 44 */
const u16 ef13_char_table_044_head[4] = { HEAD(4, 0, 8, 10, 0, 10, 0) };
const u16 ef13_char_table_044[84] = {
    L4(1, 0, 0, 0, 0, 0, 0, 0x721B, -28, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x721B, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x721C, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x721D, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x721E, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x721F, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7220, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7221, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7222, 0, 19, 0, 0, 0, 0),
    CMD(CM_END, 0, 0, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 45 */
const u16 ef13_char_table_045_head[4] = { HEAD(4, 0, 8, 10, 0, 10, 0) };
const u16 ef13_char_table_045[84] = {
    L4(1, 0, 0, 0, 0, 0, 0, 0x7213, -28, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7213, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7214, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7215, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7216, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7217, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7218, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x7219, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x721A, 0, 19, 0, 0, 0, 0),
    CMD(CM_END, 0, 0, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 46 */
const u16 ef13_char_table_046_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_046[12] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x7236),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7236),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 47 */
const u16 ef13_char_table_047_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_047[12] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x722E),
    L2(250, 255, 0, 0, 0, 0, 0, 0x722E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 48 */
const u16 ef13_char_table_048_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_048[12] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x7226),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7226),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 49 */
const u16 ef13_char_table_049_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_049[12] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x721E),
    L2(250, 255, 0, 0, 0, 0, 0, 0x721E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 50 */
const u16 ef13_char_table_050_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_050[12] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x7216),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7216),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 51 */
const u16 ef13_char_table_051_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_051[104] = {
    L2(1, 0, 267, 0, 0, 0, 0, 0x723C),
    L2(1, 0, 0, 0, 0, 0, 0, 0x723D),
    L2(1, 0, 340, 0, 0, 0, 0, 0x723E),
    L2(1, 0, 0, 0, 0, 0, 0, 0x723F),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7240),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7241),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7242),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7243),
    L2(1, 0, 0, 0, 0, 0, 0, 0x723C),
    L2(1, 0, 0, 0, 0, 0, 0, 0x723D),
    L2(1, 0, 0, 0, 0, 0, 0, 0x723E),
    L2(1, 0, 0, 0, 0, 0, 0, 0x723F),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7240),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7241),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7242),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7243),
    L2(1, 0, 0, 0, 0, 0, 0, 0x723C),
    L2(1, 0, 0, 0, 0, 0, 0, 0x723D),
    L2(1, 0, 0, 0, 0, 0, 0, 0x723E),
    L2(1, 0, 0, 0, 0, 0, 0, 0x723F),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7240),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7241),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7242),
    L2(1, 0, 0, 0, 0, 0, 0, 0x7243),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7243),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 52 */
const u16 ef13_char_table_052_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_052[40] = {
    L2(1, 0, 340, 0, 0, 0, 0, 0x723C),
    L2(1, 0, 0, 0, 0, 0, 0, 0x723D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x723E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x723F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7240),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7241),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7242),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7243),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7243),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 53, 54, 55 */
const u16 ef13_char_table_053_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_053[52] = {
    L2(1, 0, 341, 0, 0, 0, 0, 0x1E99),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1E9B),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1E9C),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1E9D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1E9E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1E9F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1EA0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1EA1),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1EA2),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1F10),
    L2(4, 0, 0, 0, 0, 0, 0, 0x1F11),
    L2(250, 255, 0, 0, 0, 0, 0, 0x1F11),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 56 */
const u16 ef13_char_table_056_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_056[52] = {
    L2(1, 0, 341, 0, 0, 0, 0, 0x1F12),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F13),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F14),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1F15),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1F16),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1F17),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1F18),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1F19),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1F1A),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1F1B),
    L2(4, 0, 0, 0, 0, 0, 0, 0x1F1C),
    L2(250, 255, 0, 0, 0, 0, 0, 0x1F1C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 57 */
const u16 ef13_char_table_057_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_057[52] = {
    L2(1, 0, 331, 0, 0, 0, 0, 0x1FD1),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1FD2),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1FD3),
    L2(1, 0, 0, 0, 0, 0, 0, 0x1FD4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1FD5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1FD6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1FD7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1FD8),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1FD9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x1FDA),
    L2(4, 0, 0, 0, 0, 0, 0, 0x1FDB),
    L2(250, 255, 0, 0, 0, 0, 0, 0x1FDB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 58 */
const u16 ef13_char_table_058_head[4] = { HEAD(4, 0, 32, 10, 0, 10, 4) };
const u16 ef13_char_table_058[52] = {
    L4(1, 0, 0, 0, 1, 0, 0, 0x71F3, 0, 0, 0, 0, 0, 0),
    L4(1, 0, 268, 0, 0, 0, 0, 0x71EE, -29, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x71EF, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x71F0, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x71F1, 0, 19, 0, 0, 0, 0),
    CMD(CM_END, 0, 0, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 59 */
const u16 ef13_char_table_059_head[4] = { HEAD(4, 0, 32, 10, 0, 10, 4) };
const u16 ef13_char_table_059[52] = {
    L4(1, 0, 0, 0, 1, 0, 0, 0x71F3, 0, 0, 0, 0, 0, 0),
    L4(1, 0, 268, 0, 0, 0, 0, 0x71EE, -30, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x71EF, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x71F0, 0, 19, 0, 0, 0, 0),
    L4(1, 0, 0, 0, 0, 0, 0, 0x71F1, 0, 19, 0, 0, 0, 0),
    CMD(CM_END, 0, 0, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 60 */
const u16 ef13_char_table_060_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_060[12] = {
    L2(10, 0, 0, 0, 0, 0, 0, 0x1FDD),
    L2(250, 255, 0, 0, 0, 0, 0, 0x1FDD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 61 */
const u16 ef13_char_table_061_head[4] = { HEAD(4, 0, 8, 10, 0, 6, 0) };
const u16 ef13_char_table_061[276] = {
    L4(2, 0, 322, 0, 0, 0, 0, 0x0320, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 487, 0, 0, 0, 0, 0x0321, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0322, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0323, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0324, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0325, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0326, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0327, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0328, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0329, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x032A, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x032B, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x032C, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x032D, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x032E, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x032F, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0330, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0331, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0332, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0333, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0334, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0335, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0336, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0337, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0338, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0339, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x033A, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x033B, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x033C, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x033D, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x033E, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x033F, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0320, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0321, -32, 21, 64, 0, 3, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 62 */
const u16 ef13_char_table_062_head[4] = { HEAD(4, 0, 8, 10, 0, 6, 0) };
const u16 ef13_char_table_062[276] = {
    L4(2, 0, 322, 0, 0, 0, 0, 0x0340, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 486, 0, 0, 0, 0, 0x0341, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0342, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0343, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0344, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0345, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0346, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0347, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0348, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0349, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x034A, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x034B, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x034C, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x034D, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x034E, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x034F, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0350, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0351, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0352, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0353, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0354, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0355, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0356, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0357, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0358, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0359, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x035A, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x035B, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x035C, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x035D, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x035E, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x035F, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0340, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0341, -33, 21, 64, 0, 0, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 63 */
const u16 ef13_char_table_063_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_063[32] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x02E8),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02E9),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02EA),
    L2(3, 0, 0, 0, 0, 0, 0, 0x02EB),
    L2(4, 0, 0, 0, 0, 0, 0, 0x02EC),
    L2(4, 0, 0, 0, 0, 0, 0, 0x02ED),
    L2(250, 255, 0, 0, 0, 0, 0, 0x02ED),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 64 */
const u16 ef13_char_table_064_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_064[44] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x02F1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02F2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02F3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02F4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02F5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02F6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02F7),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02F8),
    L2(2, 0, 0, 0, 0, 0, 0, 0x02F9),
    L2(250, 255, 0, 0, 0, 0, 0, 0x02F9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 65 */
const u16 ef13_char_table_065_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_065[8] = {
    CMD(CM_JMP, 0, 63, 1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 66 */
const u16 ef13_char_table_066_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_066[8] = {
    CMD(CM_JMP, 0, 64, 1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 67 */
const u16 ef13_char_table_067_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_067[12] = {
    L2(2, 0, 267, 0, 0, 0, 0, 0x02E8),
    CMD(CM_JMP, 0, 63, 2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 68 */
const u16 ef13_char_table_068_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_068[12] = {
    L2(2, 0, 267, 0, 0, 0, 0, 0x02F1),
    CMD(CM_JMP, 0, 64, 2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 69 */
const u16 ef13_char_table_069_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_069[12] = {
    L2(2, 0, 266, 0, 0, 0, 0, 0x02E8),
    CMD(CM_JMP, 0, 63, 2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 70 */
const u16 ef13_char_table_070_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_070[12] = {
    L2(2, 0, 266, 0, 0, 0, 0, 0x02F1),
    CMD(CM_JMP, 0, 64, 2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 71 */
const u16 ef13_char_table_071_head[4] = { HEAD(4, 0, 48, 10, 0, 10, 5) };
const u16 ef13_char_table_071[20] = {
    L4(1, 0, 0, 0, 0, 0, 0, 0x1793, -34, 22, 0, 0, 0, 0),
    CMD(CM_JPSS, 0, 10, 2), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 72 */
const u16 ef13_char_table_072_head[4] = { HEAD(4, 0, 8, 10, 0, 6, 0) };
const u16 ef13_char_table_072[276] = {
    L4(2, 0, 322, 0, 0, 0, 0, 0x0320, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 487, 0, 0, 0, 0, 0x0321, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0322, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0323, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0324, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0325, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0326, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0327, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0328, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0329, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x032A, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x032B, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x032C, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x032D, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x032E, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x032F, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0330, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0331, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0332, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0333, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0334, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0335, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0336, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0337, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0338, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0339, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x033A, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x033B, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x033C, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x033D, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x033E, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x033F, -32, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0320, -32, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0321, -32, 21, 64, 0, 3, 0),
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 73 */
const u16 ef13_char_table_073_head[4] = { HEAD(4, 0, 8, 10, 0, 6, 0) };
const u16 ef13_char_table_073[436] = {
    L4(2, 0, 322, 0, 0, 0, 0, 0x0340, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 486, 0, 0, 0, 0, 0x0341, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0342, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0343, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0344, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0345, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0346, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0347, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0348, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0349, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x034A, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x034B, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x034C, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x034D, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x034E, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x034F, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0350, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0351, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0352, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0353, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0354, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0355, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0356, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0357, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0358, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0359, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x035A, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x035B, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x035C, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x035D, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x035E, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x035F, -33, 26, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0340, -33, 21, 64, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x0341, -33, 21, 64, 0, 0, 0),
    CMD(CM_ROA, 0, 0, 0), 0x0004, 0x0020, 0x0A00, 0x0A05,
    L4(2, 0, 0, 0, 0, 0, 0, 0x7104, -4, 1, 69, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7100, 0, 1, 69, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7105, 0, 1, 69, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7101, 0, 1, 69, 0, 0, 0),
    CMD(CM_END, 0, 0, 1), 0, 0, 0, 0,
    L4(2, 0, 0, 0, 0, 0, 0, 0x70EC, -5, 2, 65, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70F0, 0, 2, 65, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70EC, 0, 2, 65, 0, 0, 0),
    CMD(CM_END, 0, 0, 6), 0, 0, 0, 0,
    CMD(CM_ROA, 0, 0, 0), 0x0004, 0x0020, 0x0A00, 0x0A05,
    L4(2, 0, 0, 0, 0, 0, 0, 0x7104, -4, 1, 69, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7100, 0, 1, 69, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7105, 0, 1, 69, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x7101, 0, 1, 69, 0, 0, 0),
    CMD(CM_END, 0, 0, 1), 0, 0, 0, 0,
    L4(2, 0, 0, 0, 0, 0, 0, 0x70EC, -5, 2, 65, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70F0, 0, 2, 65, 0, 0, 0),
    L4(2, 0, 0, 0, 0, 0, 0, 0x70EC, 0, 2, 65, 0, 0, 0),
    CMD(CM_END, 0, 0, 6), 0, 0, 0, 0,
    0x0001, 0x0000, 0x0000, 0x0000,
};

/* script: 74 */
const u16 ef13_char_table_074_head[4] = { HEAD(2, 0, 8, 0, 0, 0, 0) };
const u16 ef13_char_table_074[108] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x16F2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x16F3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x16F4),
    L2(2, 0, 0, 0, 0, 0, 0, 0x16F5),
    L2(2, 0, 0, 0, 0, 0, 0, 0x16F6),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1795),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1796),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1797),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1798),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1799),
    L2(2, 0, 0, 0, 0, 0, 0, 0x179A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1790),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1791),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1792),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1793),
    L2(2, 0, 0, 0, 0, 0, 0, 0x1794),
    L2(2, 0, 0, 0, 0, 0, 0, 0x179B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x179C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x179D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x179E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x179F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x17A0),
    L2(2, 0, 0, 0, 0, 0, 0, 0x17A1),
    L2(2, 0, 0, 0, 0, 0, 0, 0x17A2),
    L2(2, 0, 0, 0, 0, 0, 0, 0x17A3),
    L2(2, 0, 0, 0, 0, 0, 0, 0x17A4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 75 */
const u16 ef13_char_table_075_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_075[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6880),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 76 */
const u16 ef13_char_table_076_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_076[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6881),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 77 */
const u16 ef13_char_table_077_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_077[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6882),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 78 */
const u16 ef13_char_table_078_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_078[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6883),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 79 */
const u16 ef13_char_table_079_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_079[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6884),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 80 */
const u16 ef13_char_table_080_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_080[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6885),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 81 */
const u16 ef13_char_table_081_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_081[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6886),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 82 */
const u16 ef13_char_table_082_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_082[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6887),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 83 */
const u16 ef13_char_table_083_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_083[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6888),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 84 */
const u16 ef13_char_table_084_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_084[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6889),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 85 */
const u16 ef13_char_table_085_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_085[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x688A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 86 */
const u16 ef13_char_table_086_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_086[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x688B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 87 */
const u16 ef13_char_table_087_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_087[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x688C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 88 */
const u16 ef13_char_table_088_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_088[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x688D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 89 */
const u16 ef13_char_table_089_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_089[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x688E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 90 */
const u16 ef13_char_table_090_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_090[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x688F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 91 */
const u16 ef13_char_table_091_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_091[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6890),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 92 */
const u16 ef13_char_table_092_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_092[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6891),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 93 */
const u16 ef13_char_table_093_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_093[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6892),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 94 */
const u16 ef13_char_table_094_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_094[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6893),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 95 */
const u16 ef13_char_table_095_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_095[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6894),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 96 */
const u16 ef13_char_table_096_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_096[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6895),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 97 */
const u16 ef13_char_table_097_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_097[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6896),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 98 */
const u16 ef13_char_table_098_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_098[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6897),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 99 */
const u16 ef13_char_table_099_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_099[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6898),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 100 */
const u16 ef13_char_table_100_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_100[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6899),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 101 */
const u16 ef13_char_table_101_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_101[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x689A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 102 */
const u16 ef13_char_table_102_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_102[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x689B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 103 */
const u16 ef13_char_table_103_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_103[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x689C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 104 */
const u16 ef13_char_table_104_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_104[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x689D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 105 */
const u16 ef13_char_table_105_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_105[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x689E),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 106 */
const u16 ef13_char_table_106_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_106[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x689F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 107 */
const u16 ef13_char_table_107_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_107[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68A0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 108 */
const u16 ef13_char_table_108_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_108[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68A1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 109 */
const u16 ef13_char_table_109_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_109[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68A2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 110 */
const u16 ef13_char_table_110_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_110[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68A3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 111 */
const u16 ef13_char_table_111_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_111[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68A4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 112 */
const u16 ef13_char_table_112_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_112[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68A5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 113 */
const u16 ef13_char_table_113_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_113[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68A6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 114 */
const u16 ef13_char_table_114_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_114[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68A7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 115 */
const u16 ef13_char_table_115_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_115[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68A8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 116 */
const u16 ef13_char_table_116_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_116[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68A9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 117 */
const u16 ef13_char_table_117_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_117[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68AA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 118 */
const u16 ef13_char_table_118_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_118[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68AB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 119 */
const u16 ef13_char_table_119_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_119[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68AC),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 120 */
const u16 ef13_char_table_120_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_120[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68AD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 121 */
const u16 ef13_char_table_121_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_121[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68AE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 122 */
const u16 ef13_char_table_122_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_122[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68AF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 123 */
const u16 ef13_char_table_123_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_123[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68B0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 124 */
const u16 ef13_char_table_124_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_124[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68B1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 125 */
const u16 ef13_char_table_125_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_125[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68B2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 126 */
const u16 ef13_char_table_126_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_126[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68B3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 127 */
const u16 ef13_char_table_127_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_127[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68B4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 128 */
const u16 ef13_char_table_128_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_128[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68B5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 129 */
const u16 ef13_char_table_129_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_129[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68B6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 130 */
const u16 ef13_char_table_130_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_130[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68B7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 131 */
const u16 ef13_char_table_131_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_131[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68B8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 132 */
const u16 ef13_char_table_132_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_132[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68B9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 133 */
const u16 ef13_char_table_133_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_133[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68BA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 134 */
const u16 ef13_char_table_134_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_134[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68BB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 135 */
const u16 ef13_char_table_135_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_135[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68BC),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 136 */
const u16 ef13_char_table_136_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_136[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68BD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 137 */
const u16 ef13_char_table_137_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_137[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68BE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 138 */
const u16 ef13_char_table_138_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_138[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68BF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 139 */
const u16 ef13_char_table_139_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_139[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68C0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 140 */
const u16 ef13_char_table_140_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_140[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68C1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 141 */
const u16 ef13_char_table_141_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_141[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68C2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 142 */
const u16 ef13_char_table_142_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_142[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68C3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 143 */
const u16 ef13_char_table_143_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_143[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68C4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 144 */
const u16 ef13_char_table_144_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_144[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68C5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 145 */
const u16 ef13_char_table_145_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_145[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68C6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 146 */
const u16 ef13_char_table_146_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_146[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68C7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 147 */
const u16 ef13_char_table_147_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_147[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68C8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 148 */
const u16 ef13_char_table_148_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_148[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68C9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 149 */
const u16 ef13_char_table_149_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_149[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68CA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 150 */
const u16 ef13_char_table_150_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_150[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68CB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 151 */
const u16 ef13_char_table_151_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_151[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68CC),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 152 */
const u16 ef13_char_table_152_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_152[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68CD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 153 */
const u16 ef13_char_table_153_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_153[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68CE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 154 */
const u16 ef13_char_table_154_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_154[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68CF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 155 */
const u16 ef13_char_table_155_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_155[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68D0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 156 */
const u16 ef13_char_table_156_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_156[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68D1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 157 */
const u16 ef13_char_table_157_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_157[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68D2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 158 */
const u16 ef13_char_table_158_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_158[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68D3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 159 */
const u16 ef13_char_table_159_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_159[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68D4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 160 */
const u16 ef13_char_table_160_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_160[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68D5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 161 */
const u16 ef13_char_table_161_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_161[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68D6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 162 */
const u16 ef13_char_table_162_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_162[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68D7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 163 */
const u16 ef13_char_table_163_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_163[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68D8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 164 */
const u16 ef13_char_table_164_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_164[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68D9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 165 */
const u16 ef13_char_table_165_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_165[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68DA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 166 */
const u16 ef13_char_table_166_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_166[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68DB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 167 */
const u16 ef13_char_table_167_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_167[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68DC),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 168 */
const u16 ef13_char_table_168_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_168[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68DD),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 169 */
const u16 ef13_char_table_169_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_169[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68DE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 170 */
const u16 ef13_char_table_170_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_170[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68DF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 171 */
const u16 ef13_char_table_171_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_171[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68E0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 172 */
const u16 ef13_char_table_172_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_172[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68E1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 173 */
const u16 ef13_char_table_173_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_173[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68E2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 174 */
const u16 ef13_char_table_174_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_174[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68E3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 175 */
const u16 ef13_char_table_175_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_175[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68E4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 176 */
const u16 ef13_char_table_176_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_176[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68E5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 177 */
const u16 ef13_char_table_177_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_177[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68E6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 178 */
const u16 ef13_char_table_178_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_178[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68E7),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 179 */
const u16 ef13_char_table_179_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_179[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68E8),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 180 */
const u16 ef13_char_table_180_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_180[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68E9),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 181 */
const u16 ef13_char_table_181_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_181[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68EA),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 182 */
const u16 ef13_char_table_182_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_182[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68EB),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 183 */
const u16 ef13_char_table_183_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_183[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68EC),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 184 */
const u16 ef13_char_table_184_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_184[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68ED),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 185 */
const u16 ef13_char_table_185_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_185[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68EE),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 186 */
const u16 ef13_char_table_186_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_186[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68EF),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 187 */
const u16 ef13_char_table_187_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_187[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68F0),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 188 */
const u16 ef13_char_table_188_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_188[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68F1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 189 */
const u16 ef13_char_table_189_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_189[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68F2),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 190 */
const u16 ef13_char_table_190_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_190[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68F3),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 191 */
const u16 ef13_char_table_191_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_191[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68F4),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 192 */
const u16 ef13_char_table_192_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_192[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68F5),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 193 */
const u16 ef13_char_table_193_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_193[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68F6),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 194 */
const u16 ef13_char_table_194_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ef13_char_table_194[8] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x68F7),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 ag_char_table_0_000[], ag_char_table_0_001[], ag_char_table_0_002[];

/* ag_char_table_0: 3 entries; debug viewer: PLEF; used by EFFC9, dbg_work, effg0_work */
/* provisional name */
const u32 ag_char_table_0[4] = {
    (u32)ag_char_table_0_000,  /* 0 */
    (u32)ag_char_table_0_001,  /* 1 */
    (u32)ag_char_table_0_002,  /* 2 */
    0
};

extern const u16 ag_char_table_1_000[], ag_char_table_1_001[], ag_char_table_1_002[];

/* ag_char_table_1: 3 entries; used by EFFC9, dbg_work, effg0_work */
/* provisional name */
const u32 ag_char_table_1[4] = {
    (u32)ag_char_table_1_000,  /* 0 */
    (u32)ag_char_table_1_001,  /* 1 */
    (u32)ag_char_table_1_002,  /* 2 */
    0
};

extern const u16 ag_char_table_2_000[], ag_char_table_2_001[], ag_char_table_2_002[];

/* ag_char_table_2: 3 entries; used by EFFC9, dbg_work, effg0_work */
/* provisional name */
const u32 ag_char_table_2[4] = {
    (u32)ag_char_table_2_000,  /* 0 */
    (u32)ag_char_table_2_001,  /* 1 */
    (u32)ag_char_table_2_002,  /* 2 */
    0
};

extern const u16 ag_char_table_3_000[], ag_char_table_3_001[], ag_char_table_3_002[];

/* ag_char_table_3: 3 entries; used by EFFC9, dbg_work, effg0_work */
/* provisional name */
const u32 ag_char_table_3[4] = {
    (u32)ag_char_table_3_000,  /* 0 */
    (u32)ag_char_table_3_001,  /* 1 */
    (u32)ag_char_table_3_002,  /* 2 */
    0
};

extern const u16 ag_char_table_4_000[], ag_char_table_4_001[], ag_char_table_4_002[];

/* ag_char_table_4: 3 entries; used by EFFC9, dbg_work, effg0_work */
/* provisional name */
const u32 ag_char_table_4[4] = {
    (u32)ag_char_table_4_000,  /* 0 */
    (u32)ag_char_table_4_001,  /* 1 */
    (u32)ag_char_table_4_002,  /* 2 */
    0
};

extern const u16 ag_char_table_5_000[], ag_char_table_5_001[], ag_char_table_5_002[];

/* ag_char_table_5: 3 entries; used by EFFC9, dbg_work, effg0_work */
/* provisional name */
const u32 ag_char_table_5[4] = {
    (u32)ag_char_table_5_000,  /* 0 */
    (u32)ag_char_table_5_001,  /* 1 */
    (u32)ag_char_table_5_002,  /* 2 */
    0
};

extern const u16 ag_char_table_6_000[], ag_char_table_6_001[], ag_char_table_6_002[];

/* ag_char_table_6: 3 entries; used by EFFC9, dbg_work, effg0_work */
/* provisional name */
const u32 ag_char_table_6[4] = {
    (u32)ag_char_table_6_000,  /* 0 */
    (u32)ag_char_table_6_001,  /* 1 */
    (u32)ag_char_table_6_002,  /* 2 */
    0
};

extern const u16 ag_face_panel_table_000[];

/* ag_face_panel_table: 1 entries; used by EFF37, EFFH2, dbg_work */
const u32 ag_face_panel_table[2] = {
    (u32)ag_face_panel_table_000,  /* 0 */
    0
};

/* script: 0 */
const u16 ag_char_table_0_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_0_000[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E00),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 ag_char_table_0_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_0_001[20] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E01),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6E02),
    L2(90, 0, 0, 0, 0, 0, 0, 0x6E03),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E03),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 ag_char_table_0_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_0_002[36] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E04),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E05),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E06),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E07),
    L2(3, 1, 0, 0, 0, 0, 0, 0x6E08),
    L2(30, 2, 0, 0, 0, 0, 0, 0x6E09),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E09),
    CMD(CM_IXBW, 0, 0, 1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 ag_char_table_1_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_1_000[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E0A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 ag_char_table_1_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_1_001[48] = {
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E0B),
    L2(7, 0, 0, 0, 0, 0, 0, 0x6E0C),
    L2(32, 0, 0, 0, 0, 0, 0, 0x6E0D),
    CMD(CM_FOR, 0, 0, 3),
    L2(3, 0, 0, 0, 0, 0, 0, 0x6E0E),
    L2(16, 0, 0, 0, 0, 0, 0, 0x6E0F),
    L2(10, 0, 0, 0, 0, 0, 0, 0x6E10),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E0E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6E0D),
    CMD(CM_NEX, 0, 0, 0),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E0D),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 ag_char_table_1_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_1_002[72] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E11),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E12),
    L2(32, 0, 0, 0, 0, 0, 0, 0x6E13),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E14),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E15),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E16),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E17),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E18),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E19),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6E1A),
    L2(7, 0, 0, 0, 0, 0, 0, 0x6E1B),
    L2(4, 1, 0, 0, 0, 0, 0, 0x6E1C),
    L2(6, 2, 0, 0, 0, 0, 0, 0x6E1D),
    L2(6, 2, 0, 0, 0, 0, 0, 0x6E1E),
    L2(20, 2, 0, 0, 0, 0, 0, 0x6E1F),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E1F),
    CMD(CM_IXBW, 0, 0, 1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 ag_char_table_2_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_2_000[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E24),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 ag_char_table_2_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_2_001[32] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E22),
    L2(58, 0, 0, 0, 0, 0, 0, 0x6E23),
    L2(7, 0, 0, 0, 0, 0, 0, 0x6E22),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E21),
    L2(58, 0, 0, 0, 0, 0, 0, 0x6E20),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E21),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E21),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 ag_char_table_2_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_2_002[36] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E25),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E26),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E27),
    L2(7, 0, 0, 0, 0, 0, 0, 0x6E28),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6E29),
    L2(20, 1, 0, 0, 0, 0, 0, 0x6E2A),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E2A),
    CMD(CM_IXBW, 0, 0, 1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 ag_char_table_3_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_3_000[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E2F),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 ag_char_table_3_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_3_001[32] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E2D),
    L2(58, 0, 0, 0, 0, 0, 0, 0x6E2E),
    L2(7, 0, 0, 0, 0, 0, 0, 0x6E2D),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E2C),
    L2(58, 0, 0, 0, 0, 0, 0, 0x6E2B),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E2C),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E2C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 ag_char_table_3_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_3_002[36] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E30),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E31),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E32),
    L2(7, 0, 0, 0, 0, 0, 0, 0x6E33),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6E34),
    L2(20, 1, 0, 0, 0, 0, 0, 0x6E35),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E35),
    CMD(CM_IXBW, 0, 0, 1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 ag_char_table_4_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_4_000[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E3A),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 ag_char_table_4_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_4_001[32] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E38),
    L2(58, 0, 0, 0, 0, 0, 0, 0x6E39),
    L2(7, 0, 0, 0, 0, 0, 0, 0x6E38),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E37),
    L2(58, 0, 0, 0, 0, 0, 0, 0x6E36),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E37),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E37),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 ag_char_table_4_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_4_002[36] = {
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E3B),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E3C),
    L2(8, 0, 0, 0, 0, 0, 0, 0x6E3D),
    L2(7, 0, 0, 0, 0, 0, 0, 0x6E3E),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6E3F),
    L2(20, 1, 0, 0, 0, 0, 0, 0x6E40),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E40),
    CMD(CM_IXBW, 0, 0, 1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 ag_char_table_5_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_5_000[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E41),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 ag_char_table_5_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_5_001[68] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E42),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E43),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E44),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6E45),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E46),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E47),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E48),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6E49),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E42),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E43),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E44),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E45),
    L2(6, 0, 0, 0, 0, 0, 0, 0x6E43),
    L2(7, 0, 0, 0, 0, 0, 0, 0x6E4A),
    L2(32, 0, 0, 0, 0, 0, 0, 0x6E4B),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E4B),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 ag_char_table_5_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_5_002[36] = {
    L2(6, 0, 0, 0, 0, 0, 0, 0x6E4C),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E4D),
    L2(4, 1, 0, 0, 0, 0, 0, 0x6E4E),
    L2(4, 2, 0, 0, 0, 0, 0, 0x6E4F),
    L2(4, 2, 0, 0, 0, 0, 0, 0x6E50),
    L2(20, 2, 0, 0, 0, 0, 0, 0x6E51),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E51),
    CMD(CM_IXBW, 0, 0, 1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 ag_char_table_6_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_6_000[8] = {
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E52),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 ag_char_table_6_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_6_001[48] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E53),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E54),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E55),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E56),
    L2(32, 0, 0, 0, 0, 0, 0, 0x6E57),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E58),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E59),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E5A),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E5B),
    L2(32, 0, 0, 0, 0, 0, 0, 0x6E5C),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E5C),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 2 */
const u16 ag_char_table_6_002_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_char_table_6_002[68] = {
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E5D),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E5E),
    L2(4, 0, 0, 0, 0, 0, 0, 0x6E5F),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E60),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E61),
    L2(5, 0, 0, 0, 0, 0, 0, 0x6E62),
    L2(5, 1, 0, 0, 0, 0, 0, 0x6E63),
    L2(5, 1, 0, 0, 0, 0, 0, 0x6E64),
    L2(5, 1, 0, 0, 0, 0, 0, 0x6E65),
    L2(5, 1, 0, 0, 0, 0, 0, 0x6E66),
    L2(5, 1, 0, 0, 0, 0, 0, 0x6E67),
    L2(5, 1, 0, 0, 0, 0, 0, 0x6E68),
    L2(5, 1, 0, 0, 0, 0, 0, 0x6E69),
    L2(5, 1, 0, 0, 0, 0, 0, 0x6E6A),
    L2(250, 255, 0, 0, 0, 0, 0, 0x6E6A),
    CMD(CM_IXBW, 0, 0, 1),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 0 */
const u16 ag_face_panel_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 ag_face_panel_table_000[76] = {
    L2(250, 0, 0, 0, 0, 0, 0, 0x76A8),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76A9),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76AA),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76AB),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76AC),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76AD),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76AE),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76AF),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76B0),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76B1),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76B2),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76B3),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76B4),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76B5),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76B6),
    L2(250, 0, 0, 0, 0, 0, 0, 0x76B7),
    L2(250, 0, 0, 0, 0, 0, 0, 0x59BD),
    L2(250, 0, 0, 0, 0, 0, 0, 0x59BE),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 effD4_char_table_000[], effD4_char_table_001[];

/* effD4_char_table: 2 entries; used by EFFG3 */
const u32 effD4_char_table[3] = {
    (u32)effD4_char_table_000,  /* 0 */
    (u32)effD4_char_table_001,  /* 1 */
    0
};

/* script: 0 */
const u16 effD4_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 effD4_char_table_000[12] = {
    L2(3, 0, 0, 0, 0, 0, 0, 0x7026),
    L2(3, 255, 0, 0, 0, 0, 0, 0x7027),
    CMD(CM_ROA, 0, 0, 0),
};

/* script: 1 */
const u16 effD4_char_table_001_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 effD4_char_table_001[48] = {
    L2(2, 0, 0, 0, 0, 0, 0, 0x7028),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7029),
    L2(2, 0, 0, 0, 0, 0, 0, 0x702A),
    L2(2, 0, 0, 0, 0, 0, 0, 0x702B),
    L2(2, 0, 0, 0, 0, 0, 0, 0x702C),
    L2(2, 0, 0, 0, 0, 0, 0, 0x702D),
    L2(2, 0, 0, 0, 0, 0, 0, 0x702E),
    L2(2, 0, 0, 0, 0, 0, 0, 0x702F),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7030),
    L2(2, 0, 0, 0, 0, 0, 0, 0x7031),
    L2(250, 255, 0, 0, 0, 0, 0, 0x7031),
    CMD(CM_ROA, 0, 0, 0),
};

extern const u16 effh0_char_table_000[];

/* effh0_char_table: 1 entries; used by EFFH0 */
const u32 effh0_char_table[2] = {
    (u32)effh0_char_table_000,  /* 0 */
    0
};

/* script: 0 */
const u16 effh0_char_table_000_head[4] = { HEAD(2, 0, 0, 0, 0, 0, 0) };
const u16 effh0_char_table_000[20] = {
    CMD(CM_EXEC, 1, 65, 0),
    CMD(CM_PAXY, 0, 8192, 0),
    CMD(CM_EXEC, 1, 66, 0),
    L2(250, 255, 0, 0, 0, 0, 0, 0x0000),
    CMD(CM_ROA, 0, 0, 0),
};
