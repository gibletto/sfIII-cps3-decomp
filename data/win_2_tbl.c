/*
 * WIN_2_TBL.C  win screen text positions
 *
 * Entry_Screen_X_Pairs gives the column of each text of the entry and win screens by row, side
 * and screen mode: rows 0-5 the entry messages (ENTRY_2.C, CONTINUE.C, GAME_MAIN.C), rows 6-7 the
 * scores (Score_X_Pos_Data: POW_POW.C, damage and score, and MANAGE_2.C) and rows 8-10 the
 * win record and loser texts (Loser_X_Pos_Data: MANAGE_2.C and ENTRY_2.C); EFFA3_Area_Data
 * the text rectangle effect A3 clears, by area and screen mode, read by EFFA3.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u16 Entry_Screen_X_Pairs[][2][2];
extern const s16 EFFA3_Area_Data[][2][4];

/* provisional name */
const u16 Entry_Screen_X_Pairs[11][2][2] = {
    { { 6, 6 }, { 0x1F, 0x28 } }, { { 5, 5 }, { 0x1E, 0x27 } },
    { { 2, 2 }, { 0x1B, 0x24 } }, { { 2, 6 }, { 0x1B, 0x28 } },
    { { 7, 7 }, { 0x20, 0x29 } }, { { 7, 7 }, { 0x20, 0x29 } },
    /* the scores */
    { { 17, 23 }, { 37, 46 } }, { { 6, 6 }, { 31, 40 } },
    /* the win record, the loser texts */
    { { 5, 12 }, { 42, 51 } }, { { 8, 15 }, { 31, 40 } }, { { 7, 7 }, { 32, 41 } },
};

/*
 * Indexed by area (kage_hx) and screen mode: the text rectangle effect A3 clears, as left,
 * top, right and bottom cells (rows counted from Text_Page_Y).
 */
const s16 EFFA3_Area_Data[2][2][4] = {
    { { 0, 9, 48, 10 }, { 8, 9, 62, 10 } }, { { 0, 15, 48, 16 }, { 8, 15, 62, 16 } },
};
