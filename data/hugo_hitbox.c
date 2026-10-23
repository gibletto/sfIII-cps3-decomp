/*
 * HUGO_HITBOX.C  Hugo's hit boxes
 *
 * Each of Hugo's animation frames names a row of hugo_hit_ix_table (a frame line's hit field). The
 * row picks the boxes that frame uses; set_char_base_data (CHARID) points the work at these tables
 * through char_init_data and set_jugde_area (CHARMOVE) at the rows. A box is x, width, y, height
 * from the character's position, x mirrored when facing left; width 0 means no box.
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
 * rows of hugo_catt_table dealt through it. Row 0 of a box table is no box.
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

const HIT_IX hugo_hit_ix_table[5] = {
    /* boix  atix  cuix  hoix */
    {    0,    0,    0,    0 },  /* 0: NM DM */
    {    1,    0,    1,    1 },  /* 1: KAMAE, HURIMUKI, FRONT WALK +100 */
    {    2,    0,    2,    2 },  /* 2: DASH TOBINOKI, KAGAMU, KAGAMI KAMAE +9 */
    {    3,    0,    3,    3 },  /* 3: JUMP FRONT, SP JUMP FRONT */
    {    4,    0,    3,    3 },  /* 4: JUMP FRONT, S JUMP FRONT, SP JUMP FRONT +12 */
};

const BODY_BOX hugo_body_box[5] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {  -16,  20,  108,  16 },  {  -24,  52,   82,  24 },  {  -18,  44,   50,  30 },  {  -32,  62,    0,  48 },  {    0,   0,    0,   0 } } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +100 */
    { { {  -24,  20,   66,  16 },  {  -22,  44,   42,  28 },  {  -12,  40,   20,  28 },  {  -36,  68,    0,  18 },  {    0,   0,    0,   0 } } },  /* 2: DASH TOBINOKI, KAGAMU, KAGAMI KAMAE +9 */
    { { {  -22,  28,  116,  16 },  {  -22,  46,   88,  30 },  {  -12,  38,   56,  34 },  {  -18,  46,   16,  44 },  {    0,   0,    0,   0 } } },  /* 3: JUMP FRONT, SP JUMP FRONT */
    { { {  -22,  28,  114,  16 },  {  -22,  48,   86,  30 },  {  -12,  38,   64,  26 },  {  -30,  56,   40,  28 },  {    0,   0,    0,   0 } } },  /* 4: JUMP FRONT, S JUMP FRONT, SP JUMP FRONT +12 */
};

const ATTACK_BOX hugo_att_box[2] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {    0,   0,    0,   0 },  {  -80,  48,   64,  16 },  {  -64,  32,   56,  32 } } },  /* 1: not used by a script */
};

const CAUGHT_BOX hugo_cau_box[4] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -22,   48,   48,   48 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +100 */
    { {  -26,   48,   12,   48 } },  /* 2: DASH TOBINOKI, KAGAMU, KAGAMI KAMAE +9 */
    { {  -22,   48,   82,   28 } },  /* 3: JUMP FRONT, SP JUMP FRONT, S JUMP FRONT +12 */
};

const HOSEI_BOX hugo_hos_box[4] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -24,   52,   46,   52 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +100 */
    { {  -24,   54,    0,   58 } },  /* 2: DASH TOBINOKI, KAGAMU, KAGAMI KAMAE +9 */
    { {  -24,   52,   58,   36 } },  /* 3: JUMP FRONT, SP JUMP FRONT, S JUMP FRONT +12 */
};
