/*
 * EFFD9_TBL.C  palette change tables and the flames of a standing player
 *
 * color_table_index has five entries { end-condition flags, timer, 1P table, 2P table },
 * picked by the entry number effect D9 is started with; the coltbl_NNN_1P and coltbl_NNN_2P
 * tables are the colour steps, { frames, colour } pairs ending with 0, that the effect cycles
 * the player's extra colour through. Read by EFFD9.C, the palette change controller.
 * flames_stand gives, per character, the four flame pieces { body box, x, y, pattern } placed
 * on a standing player hit by a fire attack; read by EFFE2.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 coltbl_000_1P[];
extern const s16 coltbl_000_2P[];
extern const s16 coltbl_001_1P[];
extern const s16 coltbl_001_2P[];
extern const s16 coltbl_002_1P[];
extern const s16 coltbl_002_2P[];
extern const s16 coltbl_003_1P[];
extern const s16 coltbl_003_2P[];
extern const s16 coltbl_004_1P[];
extern const s16 coltbl_004_2P[];
extern const ColorTableIndex color_table_index[];
extern const s16 flames_stand[][4][4];

const s16 coltbl_000_1P[10] = {
    1, 8192, 2, 8193, 1, 8195, 1, 8198, 0, 0,
};

const s16 coltbl_000_2P[10] = {
    1, 8208, 2, 8209, 1, 8211, 1, 8214, 0, 0,
};

const s16 coltbl_001_1P[6] = {
    2, 8192, 2, 8194, 0, 0,
};

const s16 coltbl_001_2P[6] = {
    2, 8208, 2, 8210, 0, 0,
};

const s16 coltbl_002_1P[4] = {
    999, 8195, 0, 0,
};

const s16 coltbl_002_2P[4] = {
    999, 8211, 0, 0,
};

const s16 coltbl_003_1P[6] = {
    2, 8192, 2, 8193, 0, 0,
};

const s16 coltbl_003_2P[6] = {
    2, 8208, 2, 8209, 0, 0,
};

const s16 coltbl_004_1P[6] = {
    2, 8192, 2, 8196, 0, 0,
};

const s16 coltbl_004_2P[6] = {
    2, 8208, 2, 8212, 0, 0,
};

const ColorTableIndex color_table_index[5] = {
    { 8, 0, coltbl_000_1P, coltbl_000_2P },
    { 7, 24, coltbl_003_1P, coltbl_003_2P },
    { 7, 30, coltbl_001_1P, coltbl_001_2P },
    { 5, 0, coltbl_002_1P, coltbl_002_2P },
    { 7, 18, coltbl_004_1P, coltbl_004_2P },
};

const s16 flames_stand[16][4][4] = {
    { { 1, -32, -16, 18 }, { 1, 16, -16, 57 }, { 3, 16, 24, 18 }, { 3, -16, 16, 18 } },  /* Gill */
    { { 1, 32, -16, 57 }, { 2, 0, 0, 18 }, { 3, 32, 8, 18 }, { 3, -16, 16, 18 } },  /* Alex */
    { { 1, 16, -16, 57 }, { 0, 0, 0, 0 }, { 3, 24, 12, 18 }, { 3, -16, 8, 18 } },  /* Ryu */
    { { 1, 16, -16, 57 }, { 0, 0, 0, 0 }, { 3, 16, 8, 18 }, { 3, -16, 16, 18 } },  /* Yun */
    { { 1, 32, -16, 57 }, { 0, 0, 0, 0 }, { 3, 24, 8, 18 }, { 3, -16, 20, 18 } },  /* Dudley */
    { { 1, 0, -16, 57 }, { 3, -32, 24, 18 }, { 3, -16, 16, 18 }, { 3, 16, 8, 18 } },  /* Necro */
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },  /* Hugo */
    { { 1, 16, -16, 57 }, { 0, 0, 0, 0 }, { 3, 24, 12, 18 }, { 3, -16, 16, 18 } },  /* Ibuki */
    { { 1, 16, -16, 57 }, { 0, 0, 0, 0 }, { 3, -20, 16, 18 }, { 3, 16, 8, 18 } },  /* Elena */
    { { 1, 16, -16, 57 }, { 0, 0, 0, 0 }, { 3, -16, 8, 18 }, { 3, 24, 12, 18 } },  /* Oro */
    { { 1, 16, -16, 57 }, { 0, 0, 0, 0 }, { 3, 16, 8, 18 }, { 3, -16, 16, 18 } },  /* Yang */
    { { 1, 16, -16, 57 }, { 0, 0, 0, 0 }, { 3, 24, 12, 18 }, { 3, -16, 8, 18 } },  /* Ken */
    { { 1, 16, -16, 57 }, { 0, 0, 0, 0 }, { 3, 24, 12, 18 }, { 3, -16, 8, 18 } },  /* Sean */
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },  /* 13 */
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },  /* 14 */
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },  /* 15 */
};
