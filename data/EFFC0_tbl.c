/*
 * EFFC0_TBL.C  damage state 25 effect and player companion tables
 *
 * plhos_data gives, for each character, the x offset in front of the player, the y offset and
 * the animation of the effect, and hok_table_ef the extra animation steps per frame by how
 * hard the player mashes; read by EFFC0.C, the animation attached to a player in damage state
 * 25. effC1_position_tbl gives, for each player side, the x bounds of the five zones that pick
 * the companion's pattern step, and effC1_reverse_tbl the step used for each zone when it
 * faces the other way; read by EFFC1.C, the player companions.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 hok_table_ef[];
extern const s16 plhos_data[][3];
extern const s16 effC1_reverse_tbl[];
extern const s16 effC1_position_tbl[][5];

const s16 hok_table_ef[8] = {
    1, 1, 2, 2, 3, 3, 3, 3,
};

/*
 * One row per character (player_number): x offset in front of the player (mirrored by
 * rl_flag), y offset and animation number.
 */
const s16 plhos_data[16][3] = {
    { 2, 136, 4 },  /* Gill */
    { 40, 92, 3 },  /* Alex */
    { -4, 104, 2 },  /* Ryu */
    { 2, 92, 5 },  /* Yun */
    { 40, 88, 5 },  /* Dudley */
    { 8, 94, 2 },  /* Necro */
    { 0, 0, 2 },  /* Hugo */
    { 20, 78, 2 },  /* Ibuki */
    { 30, 96, 2 },  /* Elena */
    { 10, 88, 3 },  /* Oro */
    { 2, 92, 5 },  /* Yang */
    { -4, 104, 2 },  /* Ken */
    { -4, 104, 5 },  /* Sean */
    { 0, 0, 0 },  /* 13 */
    { 0, 0, 0 },  /* 14 */
    { 0, 0, 0 },  /* 15 */
};

const s16 effC1_reverse_tbl[5] = {
    4, 3, 2, 1, 0,
};

const s16 effC1_position_tbl[2][5] = {
    { 224, 384, 544, 672, 768 }, { 429, 528, 624, 704, 768 },
};
