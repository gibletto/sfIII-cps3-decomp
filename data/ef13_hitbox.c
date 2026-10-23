/*
 * EF13_HITBOX.C  Effect 13's hit boxes
 *
 * Each of Effect 13's animation frames names a row of ef13_hit_ix_table (a frame line's hit field).
 * The row picks the boxes that frame uses; set_char_base_data (CHARID) points the work at these
 * tables through char_init_data and set_jugde_area (CHARMOVE) at the rows. A box is x, width, y,
 * height from the character's position, x mirrored when facing left; width 0 means no box.
 *
 * hit_ix_table  one row per frame pose; each column picks a row of one box table (0 = none):
 *     boix  body boxes (body_box)
 *     atix  catch and attack boxes (att_box)
 *     cuix  caught box (cau_box)
 *     hoix  push box (hos_box)
 * body_box  five damage boxes: the hit check tests an attack against each in turn; the fifth (an
 *           extended arm or leg) is hit only from the front
 * att_box   three boxes: the first is the reach of a throw (catch_hit_check: the opponent's caught
 *           box must overlap it), the other two are the attack boxes the hit check tests against
 *           the opponent's body boxes
 * cau_box   where this character can be thrown from
 * hos_box   the push box: where two fighters' push boxes overlap they are moved apart; an attack
 *           whose attribute has free4 bit 7 also hits it
 *
 * Row comments: the moves whose frames use the row or box (debug viewer names), and for att_box the
 * rows of ef13_catt_table dealt through it. Row 0 of a box table is no box.
 *
 * Effect 13 is the projectile (shell) work the fighters fire (EFF13.c). Its scripts are
 * ef13_char_table in effect_char.c; the row comments number them (script N).
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

const HIT_IX ef13_hit_ix_table[31] = {
    /* boix  atix  cuix  hoix */
    {    0,    0,    0,    0 },  /* 0: not used by a script */
    {    1,    1,    0,    0 },  /* 1: not used by a script */
    {    2,    2,    0,    0 },  /* 2: not used by a script */
    {    3,    3,    0,    0 },  /* 3: not used by a script */
    {    4,    4,    0,    0 },  /* 4: not used by a script */
    {    5,    5,    0,    0 },  /* 5: not used by a script */
    {    6,    6,    0,    0 },  /* 6: not used by a script */
    {    7,    7,    0,    0 },  /* 7: not used by a script */
    {    8,    8,    0,    0 },  /* 8: not used by a script */
    {    9,    9,    0,    0 },  /* 9: not used by a script */
    {   10,   10,    0,    0 },  /* 10: not used by a script */
    {   11,   11,    0,    0 },  /* 11: not used by a script */
    {   12,   12,    0,    0 },  /* 12: not used by a script */
    {   13,   13,    0,    0 },  /* 13: not used by a script */
    {   14,   14,    0,    0 },  /* 14: not used by a script */
    {   15,   15,    0,    0 },  /* 15: not used by a script */
    {   16,   16,    0,    0 },  /* 16: not used by a script */
    {   17,   17,    0,    0 },  /* 17: not used by a script */
    {   18,   18,    0,    0 },  /* 18: not used by a script */
    {   20,   19,    0,    0 },  /* 19: not used by a script */
    {   19,   20,    0,    0 },  /* 20: not used by a script */
    {   21,   21,    0,    0 },  /* 21: not used by a script */
    {   22,   22,    0,    0 },  /* 22: not used by a script */
    {   23,   23,    0,    0 },  /* 23: not used by a script */
    {   24,   24,    0,    0 },  /* 24: not used by a script */
    {   25,   25,    0,    0 },  /* 25: not used by a script */
    {   26,   26,    0,    0 },  /* 26: not used by a script */
    {   27,   27,    0,    0 },  /* 27: not used by a script */
    {   28,   28,    0,    0 },  /* 28: not used by a script */
    {   29,   29,    0,    0 },  /* 29: not used by a script */
    {   30,   30,    0,    0 },  /* 30: not used by a script */
};

const BODY_BOX ef13_body_box[31] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {    0,   0,    0,   0 },  {  -18,  80,  -14,  26 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 1: not used by a script */
    { { {    0,   0,    0,   0 },  {  -11,   8,  -13,  23 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 2: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -12,  24,   -6,  12 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 3: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -18,  36,   -8,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 4: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -14,  28,   -6,  12 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 5: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -12,  24,   -8,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 6: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -12,  24,   -8,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 7: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -12,  24,    0,  24 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 8: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {   -8,  18,    4,  14 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 9: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -10,  20,   -8,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 10: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {   -8,  16,   -6,  12 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 11: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -32,  64,   -8,  14 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 12: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -14,  28,   -8,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 13: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -20,  34,  -10,  20 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 14: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -22,  44,   -8,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 15: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {   -6,  12,   -3,  11 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 16: not used by a script */
    { { {    0,   0,    0,   0 },  {  -30,  60,  -14,  28 },  {  -22,  44,  -22,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 17: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -12,  24,  -10,  20 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 18: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {   -7,   8,  -14,  26 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 19: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -10,  20,  -11,  22 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 20: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -16,  32,  -20,  34 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 21: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -56,  24,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 22: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {   32,  28,    0,  20 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 23: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -36,  72,   12,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 24: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -48,  24,    6,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 25: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -12,  24,  -10,  20 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 26: not used by a script */
    { { {    0,   0,    0,   0 },  {  -12,  30,  -14,  26 },  {   18,  30,  -14,  26 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 27: not used by a script */
    { { {    0,   0,    0,   0 },  {  -12,  24,  -10,  20 },  {   12,  24,  -20,  20 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 28: not used by a script */
    { { {    0,   0,    0,   0 },  {  -12,  24,  -10,  20 },  {    2,  24,  -24,  20 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 29: not used by a script */
    { { {    0,   0,    0,   0 },  {  -10,  20,   -8,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 30: not used by a script */
};

const ATTACK_BOX ef13_att_box[31] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {    0,   0,    0,   0 },  {  -18,  80,  -14,  26 },  {    0,   0,    0,   0 } } },  /* 1: not used by a script */
    { { {    0,   0,    0,   0 },  {  -11,   8,  -13,  23 },  {    0,   0,    0,   0 } } },  /* 2: not used by a script */
    { { {    0,   0,    0,   0 },  {  -12,  24,   -6,  12 },  {    0,   0,    0,   0 } } },  /* 3: not used by a script */
    { { {    0,   0,    0,   0 },  {  -18,  36,   -8,  16 },  {    0,   0,    0,   0 } } },  /* 4: not used by a script */
    { { {    0,   0,    0,   0 },  {  -14,  28,   -6,  12 },  {    0,   0,    0,   0 } } },  /* 5: not used by a script */
    { { {    0,   0,    0,   0 },  {  -12,  24,   -8,  16 },  {    0,   0,    0,   0 } } },  /* 6: not used by a script */
    { { {    0,   0,    0,   0 },  {  -12,  24,   -8,  16 },  {    0,   0,    0,   0 } } },  /* 7: not used by a script */
    { { {    0,   0,    0,   0 },  {  -12,  24,    0,  24 },  {    0,   0,    0,   0 } } },  /* 8: not used by a script */
    { { {    0,   0,    0,   0 },  {   -8,  18,    4,  14 },  {    0,   0,    0,   0 } } },  /* 9: not used by a script */
    { { {    0,   0,    0,   0 },  {  -10,  20,   -8,  16 },  {    0,   0,    0,   0 } } },  /* 10: not used by a script */
    { { {    0,   0,    0,   0 },  {   -8,  16,   -6,  12 },  {    0,   0,    0,   0 } } },  /* 11: not used by a script */
    { { {    0,   0,    0,   0 },  {  -32,  64,   -8,  14 },  {    0,   0,    0,   0 } } },  /* 12: not used by a script */
    { { {    0,   0,    0,   0 },  {  -14,  28,   -8,  16 },  {    0,   0,    0,   0 } } },  /* 13: not used by a script */
    { { {    0,   0,    0,   0 },  {  -20,  34,  -10,  20 },  {    0,   0,    0,   0 } } },  /* 14: not used by a script */
    { { {    0,   0,    0,   0 },  {  -22,  44,   -8,  16 },  {    0,   0,    0,   0 } } },  /* 15: not used by a script */
    { { {    0,   0,    0,   0 },  {   -6,  12,   -3,  11 },  {    0,   0,    0,   0 } } },  /* 16: not used by a script */
    { { {    0,   0,    0,   0 },  {  -30,  60,  -14,  28 },  {  -22,  44,  -22,  44 } } },  /* 17: not used by a script */
    { { {    0,   0,    0,   0 },  {   -8,  16,   -7,  14 },  {    0,   0,    0,   0 } } },  /* 18: not used by a script */
    { { {    0,   0,    0,   0 },  {   -9,  18,   -9,  18 },  {    0,   0,    0,   0 } } },  /* 19: not used by a script */
    { { {    0,   0,    0,   0 },  {   -7,   8,  -14,  26 },  {    0,   0,    0,   0 } } },  /* 20: not used by a script */
    { { {    0,   0,    0,   0 },  {  -16,  32,  -20,  34 },  {    0,   0,    0,   0 } } },  /* 21: not used by a script */
    { { {    0,   0,    0,   0 },  {  -56,  24,    0,  16 },  {    0,   0,    0,   0 } } },  /* 22: not used by a script */
    { { {    0,   0,    0,   0 },  {   32,  28,    0,  20 },  {    0,   0,    0,   0 } } },  /* 23: not used by a script */
    { { {    0,   0,    0,   0 },  {  -36,  72,   12,  16 },  {    0,   0,    0,   0 } } },  /* 24: not used by a script */
    { { {    0,   0,    0,   0 },  {  -48,  24,    6,  16 },  {    0,   0,    0,   0 } } },  /* 25: not used by a script */
    { { {    0,   0,    0,   0 },  {  -12,  24,  -10,  20 },  {    0,   0,    0,   0 } } },  /* 26: not used by a script */
    { { {    0,   0,    0,   0 },  {  -12,  24,  -14,  26 },  {   12,  24,  -14,  26 } } },  /* 27: not used by a script */
    { { {    0,   0,    0,   0 },  {  -12,  24,  -10,  20 },  {   12,  24,  -20,  20 } } },  /* 28: not used by a script */
    { { {    0,   0,    0,   0 },  {  -12,  24,  -10,  20 },  {    2,  24,  -24,  20 } } },  /* 29: not used by a script */
    { { {    0,   0,    0,   0 },  {  -10,  20,   -8,  16 },  {    0,   0,    0,   0 } } },  /* 30: not used by a script */
};

const CAUGHT_BOX ef13_cau_box[1] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
};

const HOSEI_BOX ef13_hos_box[1] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
};
