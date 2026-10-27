/*
 * WIN_PL_TBL_B.C  round winner and loser pose tables
 *
 * win_2000_tbl marks, per stage background, where Dudley's final-win pose may play;
 * Win_3000_tbl and Win_3001_tbl are Ibuki's pose choices for an ordinary and a final win;
 * Win_4000_voice_tbl is Elena's win voice choices. These are read by WIN_PL.C, the round
 * winner poses. lose_type_tbl selects, by character, which loser routine (Lose_00000 or
 * Lose_10000) plays; read by LOSE_PL.C, the lose poses after a round.
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
