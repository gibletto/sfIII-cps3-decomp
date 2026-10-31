/*
 * EFFH4_TBL.C  ending object tables for effects H4 and H5
 *
 * effH4_data_tbl gives the pattern, x, y and priority of each of the four H4 objects and
 * effH4_sp_tbl their x speed while growing, x speed change once full size, and y speed; read
 * by EFFH4.C. effH5_data_tbl has a row per H5 object: family, colour, pattern, x, y, priority,
 * first frame and behaviour; read by EFFH5.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effH4_data_tbl[][4];
extern const s32 effH4_sp_tbl[][3];
extern const s16 effH5_data_tbl[][8];

/* provisional name */
const s16 effH4_data_tbl[4][4] = {
    { 9, 592, 128, 72 }, { 10, 576, 96, 70 }, { 12, 432, 128, 72 }, { 11, 448, 96, 70 },
};

/*
 * One row per object (type): x speed while it grows, x speed change once it is full size,
 * and y speed.
 */
const s32 effH4_sp_tbl[4][3] = {
    { 0xA8000, 0x38000, -0x10000 }, { 0x88000, 0x38000, -0x10000 },
    { -0xA8000, -0x38000, -0x10000 }, { -0x88000, -0x38000, -0x10000 },
};

const s16 effH5_data_tbl[11][8] = {
    { 1, 32, 27, 324, 120, 80, 1, 0 }, { 1, 32, 27, 360, 136, 82, 2, 0 },
    { 1, 32, 27, 616, 80, 82, 3, 0 }, { 1, 32, 28, 408, 56, 82, 1, 1 },
    { 1, 32, 29, 592, 120, 82, 1, 1 }, { 1, 32, 27, 624, 56, 82, 4, 0 },
    { 1, 32, 27, 428, 120, 80, 1, 0 }, { 1, 32, 31, 432, 120, 82, 1, 2 },
    { 1, 32, 30, 464, 136, 82, 1, 4 }, { 2, 32, 32, 512, 48, 80, 1, 3 },
    { 1, 32, 27, 143, 56, 81, 5, 0 },
};
