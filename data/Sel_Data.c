/*
 * SEL_DATA.C  tables read by Eff52.c, EFFA6.c and sel_pl.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u8 sel_digit_tbl[];
extern const s8 Face_Cursor_Data[][2][5];
extern const s16 Face_Pos_Data[][2];
extern const s8 EM_Cursor_Data[][2];
extern const s16 effA6_x_tbl[];
extern const s16 eff52_pos_tbl[];

/* nothing in the program reads it (provisional name) */
const u8 sel_digit_tbl[13] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9,
};

/* the face grid; the second grid has Yang in Yun's cell */
const s8 Face_Cursor_Data[2][2][5] = {
    { { 2, 4, 1, 3, 11 }, { 7, 5, 12, 9, 8 } },
    { { 2, 4, 1, 10, 11 }, { 7, 5, 12, 9, 8 } },
};

const s16 Face_Pos_Data[13][2] = {
    { 0, 0 }, { 0, 20 }, { -72, 20 }, { 40, 20 }, { -40, 20 }, { -32, 57 }, { 0, 0 }, { -71, 57 },
    { 72, 57 }, { 32, 57 }, { 40, 20 }, { 72, 20 }, { 0, 57 },
};

/* provisional name */
const s8 EM_Cursor_Data[13][2] = {
    { -1, -1 }, { 2, 0 }, { 0, 0 }, { 3, 0 }, { 1, 0 }, { 1, 1 }, { -1, -1 }, { 0, 1 },
    { 4, 1 }, { 3, 1 }, { 3, 0 }, { 4, 0 }, { 2, 1 },
};

/* provisional name */
const s16 effA6_x_tbl[39] = {
    -192, -120, -218, 128, 200, 192, -48, 24, -19, -64, -8, -48, -192, -160, -244, -208,
    -136, -184, -176, -136, -195, -48, 24, -19, -178, -112, -184, 112, 176, 200, -64, -8,
    -48, -48, 24, -19, 128, 200, 192,
};

/* provisional name */
const s16 eff52_pos_tbl[27] = {
    -256, 144, 228, 152, -28, 142, -58, 128, -288, 164, -212, 164, -268, 168, -28, 142,
    -242, 100, 262, 96, -58, 128, -28, 142, 228, 152, 771,
};
