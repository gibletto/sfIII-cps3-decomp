/*
 * SC_TRANS_TBL2.C  tables read by sc_trans.c
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
    { { 12, 19 }, { 29, 36 } }, { { 13, 20 }, { 29, 36 } }, { { 14, 21 }, { 28, 35 } }, { { 14, 21 }, { 28, 35 } },
    { { 13, 20 }, { 28, 35 } }, { { 14, 21 }, { 28, 35 } }, { { 12, 19 }, { 29, 36 } }, { { 14, 21 }, { 28, 35 } },
    { { 14, 21 }, { 28, 35 } }, { { 13, 20 }, { 28, 35 } }, { { 14, 21 }, { 28, 35 } }, { { 14, 21 }, { 28, 35 } },
    { { 14, 21 }, { 28, 35 } },
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
