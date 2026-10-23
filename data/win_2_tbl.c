/*
 * WIN_2_TBL.C  tables read by EFFA3.c, Game_Main.c, manage_2.c and pow_pow.c: positions of the win screen's texts
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
    { 0x11, 0x17 }, { 0x25, 0x2E }, { 6, 6 }, { 0x1F, 0x28 },
};

const s16 Loser_X_Pos_Data[6][2] = {
    { 5, 12 }, { 42, 51 }, { 8, 15 }, { 31, 40 }, { 7, 7 }, { 32, 41 },
};

const s16 EFFA3_Area_Data[2][2][4] = {
    { { 0, 9, 48, 10 }, { 8, 9, 62, 10 } }, { { 0, 15, 48, 16 }, { 8, 15, 62, 16 } },
};
