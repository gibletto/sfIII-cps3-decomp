/*
 * ENTRY_TBL_B.C  tables read by entry_2.c and mode_init.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s8 str_INSERT_COIN[];
extern const s8 str_INSERT_COINS[];
extern const s8 str_INSERT_COINS_2[];
extern const s8 str_INSERT_COINS_3[];
extern const s8 str_INSERT_COINS_4[];
extern const s8 str_INSERT_COINS_5[];
extern const s8 str_INSERT_COINS_6[];
extern const s8 str_INSERT_COINS_7[];
extern const s8 str_INSERT_COINS_8[];
extern const s8 region_type_tbl[];
extern const s8 region_cc_type_tbl[];
extern const s8 region_param_tbl[][2];

const s8 str_INSERT_COIN[12] = "INSERT COIN";

const s8 str_INSERT_COINS[16] = {
    73, 78, 83, 69, 82, 84, 32, 2, 32, 67, 79, 73, 78, 83, 0, 10,
};

const s8 str_INSERT_COINS_2[16] = {
    73, 78, 83, 69, 82, 84, 32, 3, 32, 67, 79, 73, 78, 83, 0, 48,
};

const s8 str_INSERT_COINS_3[16] = {
    73, 78, 83, 69, 82, 84, 32, 4, 32, 67, 79, 73, 78, 83, 0, 48,
};

const s8 str_INSERT_COINS_4[16] = {
    73, 78, 83, 69, 82, 84, 32, 5, 32, 67, 79, 73, 78, 83, 0, 48,
};

const s8 str_INSERT_COINS_5[16] = {
    73, 78, 83, 69, 82, 84, 32, 6, 32, 67, 79, 73, 78, 83, 0, 48,
};

const s8 str_INSERT_COINS_6[16] = {
    73, 78, 83, 69, 82, 84, 32, 7, 32, 67, 79, 73, 78, 83, 0, 17,
};

const s8 str_INSERT_COINS_7[16] = {
    73, 78, 83, 69, 82, 84, 32, 8, 32, 67, 79, 73, 78, 83, 0, 0,
};

const s8 str_INSERT_COINS_8[16] = {
    73, 78, 83, 69, 82, 84, 32, 9, 32, 67, 79, 73, 78, 83, 0, 96,
};

const s8 region_type_tbl[9] = {
    0, 0, 2, 5, 1, 3, 4, 7, 2,
};

const s8 region_cc_type_tbl[8] = {
    0, 2, 1, 1, 1, 1, 1, 2,
};

const s8 region_param_tbl[3][2] = {
    { 0, 0 }, { 1, 2 }, { 2, 4 },
};
