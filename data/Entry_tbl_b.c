/*
 * ENTRY_TBL_B.C  insert-coin messages and region tables
 *
 * str_INSERT_COIN and str_INSERT_COINS .. str_INSERT_COINS_8 are the insert-coin messages, the
 * plural ones carrying the coin count, 2 to 9, as a code between the words; placed through the
 * message lists of ENTRY_2.C, the player entry and credit task. region_type_tbl turns the
 * Country into the area type, region_cc_type_tbl gives the CC type of each country and
 * Difficult_V_Data the two CC values of each CC type; read by MODE_INIT.C.
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
extern const s8 Difficult_V_Data[][2];

const s8 str_INSERT_COIN[12] = "INSERT COIN";

/* Messages whose digits are the font's glyph numbers 0-9 (not ASCII) are written as numbers; the comment
   after each name is the text it shows. */
const s8 str_INSERT_COINS[16] = {  /* "INSERT 2 COINS" */
    73, 78, 83, 69, 82, 84, 32, 2, 32, 67, 79, 73, 78, 83, 0, 10,
};

const s8 str_INSERT_COINS_2[16] = {  /* "INSERT 3 COINS" */
    73, 78, 83, 69, 82, 84, 32, 3, 32, 67, 79, 73, 78, 83, 0, 48,
};

const s8 str_INSERT_COINS_3[16] = {  /* "INSERT 4 COINS" */
    73, 78, 83, 69, 82, 84, 32, 4, 32, 67, 79, 73, 78, 83, 0, 48,
};

const s8 str_INSERT_COINS_4[16] = {  /* "INSERT 5 COINS" */
    73, 78, 83, 69, 82, 84, 32, 5, 32, 67, 79, 73, 78, 83, 0, 48,
};

const s8 str_INSERT_COINS_5[16] = {  /* "INSERT 6 COINS" */
    73, 78, 83, 69, 82, 84, 32, 6, 32, 67, 79, 73, 78, 83, 0, 48,
};

const s8 str_INSERT_COINS_6[16] = {  /* "INSERT 7 COINS" */
    73, 78, 83, 69, 82, 84, 32, 7, 32, 67, 79, 73, 78, 83, 0, 17,
};

const s8 str_INSERT_COINS_7[16] = {  /* "INSERT 8 COINS" */
    73, 78, 83, 69, 82, 84, 32, 8, 32, 67, 79, 73, 78, 83, 0, 0,
};

const s8 str_INSERT_COINS_8[16] = {  /* "INSERT 9 COINS" */
    73, 78, 83, 69, 82, 84, 32, 9, 32, 67, 79, 73, 78, 83, 0, 96,
};

const s8 region_type_tbl[9] = {
    0, 0, 2, 5, 1, 3, 4, 7, 2,
};

const s8 region_cc_type_tbl[8] = {
    0, 2, 1, 1, 1, 1, 1, 2,
};

const s8 Difficult_V_Data[3][2] = {
    { 0, 0 }, { 1, 2 }, { 2, 4 },
};
