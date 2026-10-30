/*
 * SEL_DATA.C  character select screen position tables
 *
 * Face_Cursor_Data is the face grid of the select screen (character per cell, a second grid
 * with Yang in Yun's cell) and EM_Cursor_Data the grid cell of each character for the computer
 * opponent's cursor; both are read by SEL_PL.C. Face_Pos_Data is the x, y of each face, read
 * by EFFD5.C (face plates) and EFFD8.C (face cursor). effA6_x_tbl holds three BG 0 scroll
 * targets per battle country, read by EFFA6.C, and eff52_pos_tbl the x, y of the stage marker
 * per battle country, read by EFF52.C. sel_digit_tbl is not read.
 */

#include "types.h"
#include "structs.h"
#include "fighter.h"

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
    { { PL_RYU, PL_DUDLEY, PL_ALEX, PL_YUN, PL_KEN }, { PL_IBUKI, PL_NECRO, PL_SEAN, PL_ORO, PL_ELENA } },
    { { PL_RYU, PL_DUDLEY, PL_ALEX, PL_YANG, PL_KEN }, { PL_IBUKI, PL_NECRO, PL_SEAN, PL_ORO, PL_ELENA } },
};

/* x, y of each face on the character select screen. */
const s16 Face_Pos_Data[13][2] = {
    { 0, 0 },  /* Gill */
    { 0, 20 },  /* Alex */
    { -72, 20 },  /* Ryu */
    { 40, 20 },  /* Yun */
    { -40, 20 },  /* Dudley */
    { -32, 57 },  /* Necro */
    { 0, 0 },  /* Hugo */
    { -71, 57 },  /* Ibuki */
    { 72, 57 },  /* Elena */
    { 32, 57 },  /* Oro */
    { 40, 20 },  /* Yang */
    { 72, 20 },  /* Ken */
    { 0, 57 },  /* Sean */
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
