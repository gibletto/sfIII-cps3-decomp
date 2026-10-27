/*
 * N_INPUT_TBL.C  ranking name entry tables
 *
 * slang_tbl lists the 17 three-letter names refused at entry, name_code_tbl converts a
 * position in the entry character set to the letter code stored in the ranking, and
 * thank_you_str and for_playing_str are the closing message. Read by N_INPUT.C, the ranking
 * name entry.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 slang_tbl[][3];
extern const s8 name_code_tbl[];
extern const char thank_you_str[];
extern const char for_playing_str[];

const s16 slang_tbl[17][3] = {
    { 0, 7, 14 }, { 18, 4, 23 }, { 7, 8, 21 }, { 5, 20, 2 },
    { 5, 20, 10 }, { 0, 18, 18 }, { 44, 44, 44 }, { 39, 39, 39 },
    { 0, 20, 12 }, { 3, 8, 4 }, { 4, 19, 0 }, { 8, 17, 0 },
    { 10, 10, 10 }, { 14, 18, 8 }, { 15, 4, 4 }, { 15, 8, 18 },
    { 15, 11, 14 },
};

const s8 name_code_tbl[50] = {
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 71, 37, 38, 39, 40,
    41, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 42, 46, 43, 44, 0,
    0, 0,
};

const char thank_you_str[12] = "THANK YOU";

const char for_playing_str[12] = "FOR PLAYING";
