/*
 * EFFG6_TBL.C  trail particle emitter data and drifting ending objects
 *
 * effg6_data has a row per emitter type: end flags, life, x and y offset, particle x and y
 * speed, emit mask and display flag, and particle pattern (the columns are described beside
 * the table); read by EFFG6.C, which spawns G9 particles from it. effg7_data_tbl gives the x,
 * y, priority, pattern and first state of the ten ending objects, and effg7_speed_tbl the five
 * drift speeds, two objects to each; read by EFFG7.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effg6_data[][8];
extern const s16 effg7_data_tbl[][5];
extern const s32 effg7_speed_tbl[];

/*
 * One row per trail emitter (effect_G6_init's data): end flags (1 the work's height
 * changed, 2 hidden, 4 hit again, 8 state changed, 0x10 life over, 0x20 stopped), life,
 * x offset (mirrored by rl_flag), y offset, particle x and y speed, emit mask (low byte:
 * emit on frames whose count masks to 0) and display flag (high byte), particle pattern.
 */
const s16 effg6_data[44][8] = {
    { 46, 0, 0, 0, -32, 32, 515, 31 }, { 46, 0, 0, 0, -64, 40, 513, 31 },
    { 46, 0, 0, 0, -128, 48, 513, 30 }, { 46, 0, 0, 0, -192, 64, 513, 30 },
    { 14, 0, 8, 18, -64, 384, 519, 21 }, { 14, 0, 6, 14, -64, 384, 515, 22 },
    { 15, 0, 0, 0, 64, 32, 513, 31 }, { 47, 0, 48, 0, 192, 16, 519, 30 },
    { 47, 0, -28, 0, 192, 16, 515, 30 }, { 47, 0, -72, 0, -64, 64, 519, 30 },
    { 47, 0, -12, 0, 32, 32, 515, 31 }, { 47, 0, 22, 0, 32, 16, 515, 30 },
    { 47, 0, 51, 2, 32, 32, 519, 31 }, { 31, 26, 0, 0, 0, 0, 515, 31 },
    { 31, 40, 40, 0, -32, 32, 519, 30 }, { 31, 36, -32, 0, -32, 32, 519, 30 },
    { 47, 0, -48, 3, -64, 64, 513, 30 }, { 47, 0, 52, 5, 32, 32, 515, 31 },
    { 31, 26, 57, 0, 48, 32, 515, 31 }, { 47, 0, -36, 8, -64, 64, 519, 30 },
    { 47, 0, 24, 0, -32, 32, 515, 31 }, { 47, 0, 0, 0, 96, 64, 513, 30 },
    { 47, 0, 0, 0, 128, 32, 513, 30 }, { 30, 8, 85, 2, 16, 32, 513, 31 },
    { 31, 16, -56, 0, -32, 48, 515, 30 }, { 31, 16, 0, 0, -64, 32, 515, 30 },
    { 31, 10, 0, 0, -32, 32, 515, 30 }, { 31, 5, 0, 0, -64, 64, 513, 30 },
    { 15, 0, 0, 0, 64, 32, 513, 30 }, { 31, 26, -23, -4, 0, 0, 515, 31 },
    { 31, 26, -1, -7, 0, 0, 515, 31 }, { 31, 24, -33, -3, 0, 0, 515, 31 },
    { 31, 28, 36, -5, 0, 0, 515, 31 }, { 31, 26, -60, 2, 0, 0, 513, 31 },
    { 31, 26, 38, -1, 0, 0, 513, 31 }, { 31, 26, 29, 2, 0, 0, 515, 31 },
    { 30, 8, 54, -3, 0, 0, 513, 31 }, { 15, 0, 0, 0, 64, 32, 512, 31 },
    { 30, 3, 26, -12, 0, 0, 513, 31 }, { 30, 26, -6, -4, 0, 0, 513, 31 },
    { 30, 26, 8, -3, 0, 0, 515, 31 }, { 30, 5, -30, -2, 0, 0, 515, 31 },
    { 30, 6, 22, -4, 0, 0, 515, 31 }, { 31, 26, -29, -2, 0, 0, 513, 31 },
};

const s16 effg7_data_tbl[10][5] = {
    { 256, 60, 72, 1, 0 }, { 192, 64, 72, 1, 0 }, { 256, 88, 76, 2, 0 }, { 192, 96, 76, 2, 0 },
    { 256, 112, 78, 3, 0 }, { 192, 116, 78, 3, 0 }, { 256, 120, 80, 4, 0 }, { 192, 124, 80, 4, 0 },
    { 256, 128, 82, 5, 0 }, { 192, 128, 82, 5, 0 },
};

const s32 effg7_speed_tbl[5] = {
    0xA0000, 0x80000, 0x60000, 0x40000, 0x20000,
};
