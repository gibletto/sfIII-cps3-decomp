/*
 * HUGO_MOVE.C  Hugo's steps and movement data
 *
 * hugo_stepxy_table  x, y position steps: a frame line's add_xy field and the CM_ASXY command name
 *                    the offset in the table (in 1/256 pixel)
 * hugo_movexy_table  movement records set up by setup_mvxy_data: x speed, x acceleration, x mode, y
 *                    speed, y acceleration, y mode (speeds and accelerations in 1/256 pixel)
 * hugo_parabora_data  the arcs of opponents blown away by Hugo's attacks (parabora_own_table,
 *                     setup_butt_own_data): one record per blow-away type (the attack attribute's
 *                     buttobi), a movement record (as movexy_table's) for each of the opponent's
 *                     four weight levels
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

const s16 hugo_stepxy_table[5][2] = {
    /*   x      y          offset */
    {     0,     0 },  /* 0 */
    {  4096,     0 },  /* 2 */
    {  2048,     0 },  /* 4 */
    { -4096,     0 },  /* 6 */
    { -2048,     0 },  /* 8 */
};

const s16 hugo_movexy_table[34][6] = {
    /*  x spd  x acc  x mode   y spd  y acc  y mode */
    {    320,      0,     0,       0,      0,     0 },  /* 0 */
    {   -288,      0,     0,       0,      0,     0 },  /* 1 */
    {   1024,      0,     0,    1024,    -96,     0 },  /* 2 */
    {  -1024,      0,     0,     768,    -96,     0 },  /* 3 */
    {      0,      0,     0,       0,      0,     0 },  /* 4 */
    {      0,      0,     0,       0,      0,     0 },  /* 5 */
    {    768,      0,     0,    1600,    -92,     0 },  /* 6 */
    {      0,      0,     0,    1600,    -92,     0 },  /* 7 */
    {   -640,      0,     0,    1600,    -92,     0 },  /* 8 */
    {    768,      0,     0,    1600,    -92,     0 },  /* 9 */
    {      0,      0,     0,    1600,    -92,     0 },  /* 10 */
    {   -640,      0,     0,    1600,    -92,     0 },  /* 11 */
    {    896,      0,     0,    2176,    -96,     0 },  /* 12 */
    {      0,      0,     0,    2176,    -96,     0 },  /* 13 */
    {   -832,      0,     0,    2176,    -96,     0 },  /* 14 */
    {   1024,      0,     0,       0,      0,     0 },  /* 15 */
    {  -1024,      0,     0,       0,      0,     0 },  /* 16 */
    {  -2560,    160,     1,     512,    -64,     0 },  /* 17 */
    {  -2048,     96,     1,    1024,    -96,     0 },  /* 18 */
    {   1024,      0,     0,       0,      0,     0 },  /* 19 */
    {  -1024,      0,     0,       0,      0,     0 },  /* 20 */
    {  -1920,      0,     0,    1024,    -96,     0 },  /* 21 */
    {   1536,      0,     0,       0,      0,     0 },  /* 22 */
    {      0,      0,     0,       0,      0,     0 },  /* 23 */
    {      0,      0,     0,       0,      0,     0 },  /* 24 */
    {      0,      0,     0,       0,      0,     0 },  /* 25 */
    {      0,      0,     0,       0,      0,     0 },  /* 26 */
    {      0,      0,     0,       0,      0,     0 },  /* 27 */
    {      0,      0,     0,       0,      0,     0 },  /* 28 */
    {      0,      0,     0,       0,      0,     0 },  /* 29 */
    {      0,      0,     0,       0,      0,     0 },  /* 30 */
    {      0,      0,     0,       0,      0,     0 },  /* 31 */
    {    768,    -16,     1,     768,    -80,     0 },  /* 32 */
    {   1024,    -24,     1,    1280,    -88,     0 },  /* 33 */
};

const PARABORA_DATA hugo_parabora_data[1] = {
    /*      x spd  x acc  x mode   y spd  y acc  y mode */
    { { {      0,      0,     1,       0,      0,     0 },  /* buttobi 0: weight 0 */
        {      0,      0,     1,       0,      0,     0 },  /* weight 1 */
        {      0,      0,     1,       0,      0,     0 },  /* weight 2 */
        {      0,      0,     1,       0,      0,     0 } } },  /* weight 3 */
};
