/*
 * WIN_2_TBL.C  win screen text positions
 *
 * Score_X_Pos_Data gives the score column of each side by screen mode, read by POW_POW.C
 * (damage and score) and MANAGE_2.C; Loser_X_Pos_Data the loser's text column by screen mode,
 * read by MANAGE_2.C (round and match management); EFFA3_Area_Data the text rectangle effect
 * A3 clears, by area and screen mode, read by EFFA3.C. Entry_Screen_X_Pairs, column pairs by
 * screen mode, is not referred to.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u16 Entry_Screen_X_Pairs[][2][2];
extern const u16 Score_X_Pos_Data[][2];
extern const s16 Loser_X_Pos_Data[][2];
extern const s16 EFFA3_Area_Data[][2][4];

/* provisional name */
const u16 Entry_Screen_X_Pairs[6][2][2] = {
    { { 6, 6 }, { 0x1F, 0x28 } }, { { 5, 5 }, { 0x1E, 0x27 } },
    { { 2, 2 }, { 0x1B, 0x24 } }, { { 2, 6 }, { 0x1B, 0x28 } },
    { { 7, 7 }, { 0x20, 0x29 } }, { { 7, 7 }, { 0x20, 0x29 } },
};

const u16 Score_X_Pos_Data[4][2] = {
    { 17, 23 }, { 37, 46 }, { 6, 6 }, { 31, 40 },
};

const s16 Loser_X_Pos_Data[6][2] = {
    { 5, 12 }, { 42, 51 }, { 8, 15 }, { 31, 40 }, { 7, 7 }, { 32, 41 },
};

/*
 * Indexed by area (kage_hx) and screen mode: the text rectangle effect A3 clears, as left,
 * top, right and bottom cells (rows counted from Text_Page_Y).
 */
const s16 EFFA3_Area_Data[2][2][4] = {
    { { 0, 9, 48, 10 }, { 8, 9, 62, 10 } }, { { 0, 15, 48, 16 }, { 8, 15, 62, 16 } },
};
