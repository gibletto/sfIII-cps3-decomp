/*
 * WIN_PL_TBL_B.C  tables read by lose_pl.c and win_pl.c: the round winner and loser poses
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 win_2000_tbl[];
extern const s16 Win_3000_tbl[];
extern const s8 Win_3001_tbl[];
extern const s16 Win_4000_voice_tbl[];
extern const s16 lose_type_tbl[];

const s16 win_2000_tbl[17] = {
    1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1,
    0,
};

const s16 Win_3000_tbl[8] = {
    32, 34, 33, 35, 32, 34, 32, 35,
};

const s8 Win_3001_tbl[8] = {
    36, 37, 36, 37, 36, 38, 38, 37,
};

const s16 Win_4000_voice_tbl[5] = {
    532, 373, 530, 531, 0,
};

const s16 lose_type_tbl[14] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
};
