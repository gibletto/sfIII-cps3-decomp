/*
 * SC_TRANS_TBL2.C  round win mark, stun mark and combo window tables
 *
 * vmark_tbl places the two cells of each round win mark; smark_pos_tbl gives the stun mark
 * position per character, side and screen mode and smark_kind_tbl its kind per character;
 * combo_mtbl gives each combo message's characters and size, combo_mpos_tbl and
 * combo_mclr_pos_tbl its column and the column cleared beside it per side, combo_hitpos_tbl
 * the column of the hit count, and combo_erase_pos_tbl and combo_erase_len_tbl where and how
 * far the combo window is erased; sa_number_attr_tbl is the attribute of each super art
 * number. Read by SC_TRANS.C, the text layer transfer and put routines.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 vmark_tbl[];
extern const s16 smark_pos_tbl[][2][2];
extern const u16 smark_kind_tbl[];
extern const CMB_FRAME combo_mtbl[];
extern const s16 combo_mpos_tbl[][2];
extern const s16 combo_mclr_pos_tbl[][2];
extern const s16 combo_hitpos_tbl[][2];
extern const u16 combo_erase_pos_tbl[][8][2];
extern const u16 combo_erase_len_tbl[];
extern const u16 sa_number_attr_tbl[];

const s16 vmark_tbl[48] = {
    19, 4, 16, 20, 4, 17, 17, 4, 18, 18, 4, 19, 15, 4, 20, 16,
    4, 21, 13, 4, 22, 14, 4, 23, 27, 4, 24, 28, 4, 25, 29, 4,
    26, 30, 4, 27, 31, 4, 28, 32, 4, 29, 33, 4, 30, 34, 4, 31,
};

const s16 smark_pos_tbl[13][2][2] = {
    { { 12, 19 }, { 29, 36 } },  /* Gill */
    { { 13, 20 }, { 29, 36 } },  /* Alex */
    { { 14, 21 }, { 28, 35 } },  /* Ryu */
    { { 14, 21 }, { 28, 35 } },  /* Yun */
    { { 13, 20 }, { 28, 35 } },  /* Dudley */
    { { 14, 21 }, { 28, 35 } },  /* Necro */
    { { 12, 19 }, { 29, 36 } },  /* Hugo */
    { { 14, 21 }, { 28, 35 } },  /* Ibuki */
    { { 14, 21 }, { 28, 35 } },  /* Elena */
    { { 13, 20 }, { 28, 35 } },  /* Oro */
    { { 14, 21 }, { 28, 35 } },  /* Yang */
    { { 14, 21 }, { 28, 35 } },  /* Ken */
    { { 14, 21 }, { 28, 35 } },  /* Sean */
};

const u16 smark_kind_tbl[13] = {
    1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0,
};

const CMB_FRAME combo_mtbl[7] = {
    { { 0xB06, 8, 2 } }, { { 0xB20, 0xC, 2 } }, { { 0xB40, 0x10, 2 } }, { { 0xB60, 0xF, 2 } },
    { { 0xB80, 0xB, 2 } }, { { 0xBA0, 9, 2 } }, { { 0x6C0, 0xB, 2 } },
};

const s16 combo_mpos_tbl[7][2] = {
    { 3, 12 }, { 3, 8 }, { 3, 4 }, { 0, 5 }, { 0, 9 }, { 0, 11 }, { 0, 9 },
};

const s16 combo_mclr_pos_tbl[7][2] = {
    { 11, 8 }, { 15, 4 }, { 19, 0 }, { 15, 4 }, { 11, 8 }, { 9, 10 }, { 11, 8 },
};

const s16 combo_hitpos_tbl[3][2] = {
    { 0, 9 }, { 0, 5 }, { 0, 1 },
};

const u16 combo_erase_pos_tbl[2][8][2] = {
    { { 0x24, 1 }, { 0x1F, 1 }, { 0x1C, 1 }, { 0x20, 1 }, { 0x24, 1 }, { 0x26, 1 }, { 0x24, 1 }, { 0x24, 1 } },
    { { 0x32, 1 }, { 0x2D, 1 }, { 0x2A, 1 }, { 0x2E, 1 }, { 0x32, 1 }, { 0x34, 1 }, { 0x32, 1 }, { 0x30, 1 } },
};

const u16 combo_erase_len_tbl[8] = {
    0xB, 0x10, 0x13, 0xF, 0xB, 9, 0xB, 0xB,
};

const u16 sa_number_attr_tbl[4] = {
    0x22, 0x22, 0x24, 0xFFEC,
};
