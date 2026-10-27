/*
 * EFFB6_TBL.C  round number patterns
 *
 * effb9_round_char_tbl gives the pattern of the round number for each round (Round_num). Read
 * by EFFB9.C, the round-call number sprite.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effb9_round_char_tbl[];

const s16 effb9_round_char_tbl[8] = {
    1, 2, 3, 4, 5, 6, 7, 0,
};
