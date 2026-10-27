/*
 * EFF41_TBL.C  super art sign tables and select-screen zoom positions
 *
 * sa_sign_data has one row per super art sign: x offset from the player (mirrored by facing),
 * y offset and animation number; read by EFF41.C, the super art sign. eff40_pos_x_tbl gives
 * the x position of the select-screen zoom object for each direction; read by EFF40.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff40_pos_x_tbl[];
extern const s16 sa_sign_data[][3];

const s16 eff40_pos_x_tbl[8] = {
    128, 144, 160, 176, 208, 224, 240, 256,
};

/*
 * One row per super art sign (effect_41_init's data): x offset from the player
 * (mirrored by rl_flag), y offset and animation number.
 */
const s16 sa_sign_data[33][3] = {
    { 28, 70, 156 }, { -41, 37, 156 }, { 12, 56, 156 }, { -46, 52, 156 },
    { -14, 48, 156 }, { -28, 56, 156 }, { -12, 56, 156 }, { -20, 84, 156 },
    { -38, 44, 156 }, { 48, 92, 156 }, { -43, 52, 156 }, { -51, 55, 156 },
    { -34, 114, 156 }, { 0, 33, 156 }, { -32, 42, 156 }, { 0, 72, 156 },
    { 14, 65, 156 }, { -28, 44, 156 }, { -58, 60, 156 }, { -20, 64, 156 },
    { -22, 66, 156 }, { 22, 66, 156 }, { 0, 48, 156 }, { -22, 74, 156 },
    { -36, 52, 156 }, { -32, 48, 156 }, { -12, 40, 156 }, { -24, 68, 156 },
    { -3, 72, 156 }, { -14, 92, 156 }, { -74, 64, 156 }, { 0, 72, 156 },
    { 28, 10, 156 },
};
