/*
 * EF13_ATTR.C  Effect 13's attack attributes
 *
 * ef13_catt_table has one attack attribute per row, written with ATTR (charscr.h): reaction,
 * attribute and chip damage class, guard type, knock-back, blow-away type, damage (pow), stun
 * (piyo), super art gain, hit stop and marks. A frame line's att picks the row (negative: a new
 * hit); set_new_attnum (CHARMOVE) copies it into the work. Each row names the moves using it.
 *
 * Effect 13 is the projectile (shell) work the fighters fire (EFF13.c). Its scripts are
 * ef13_char_table in effect_char.c; the row comments number them (script N).
 */

#include "types.h"
#include "structs.h"
#include "charscr.h"

#pragma section CHR

const ATTACK_ATTR ef13_catt_table[35] = {
    /*   rea zu  att kez mkh dip zur fr4 dir vs  grd nd  but pow imp piy art ng  hsm hsy hit dmg */
    ATTR(  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0),  /* 0: not used by a script */
    ATTR( 32,  1,  0,  1,  0, 15,  3, 80, 12,  7, 10,  0, 11, 15, 26,  1,  2,  0, 10,-14, 67, 80),  /* 1: not used by a script */
    ATTR( 37,  0,  0,  1,  0, 15,  7,208, 12,  7, 10,  0, 12, 15, 17,  0,  0,  0,  2, -8, 68, 80),  /* 2: not used by a script */
    ATTR( 91,  0,  0,  1,  0, 15,  7,208, 12,  7, 10,  0, 12, 15, 17,  0,  0,  0,  6, -6, 68, 80),  /* 3: not used by a script */
    ATTR( 37,  0,  2,  1,  0,  8,  0,208, 12,  7, 10,  0, 13,  9, 16, 10,  0,  0,  6, -6, 69, 80),  /* 4: not used by a script */
    ATTR( 37,  0,  2,  1,  0,  8,  0,208, 12,  7, 10,  0, 13, 15, 16,  8,  0,  0,  6, -6, 69, 80),  /* 5: not used by a script */
    ATTR( 37,  0,  2,  1,  0, 13,  0,208, 13,  7, 10,  0, 14, 24, 16,  2,  0,  0, 12,-12,  0, 80),  /* 6: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,208, 14,  7, 10,  0,  0,  3, 16,  0,  0,  0,  6, -6, 34, 80),  /* 7: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,208,  2,  7, 10,  0,  0,  9, 16,  0,  0,  0,  8, -8, 39, 80),  /* 8: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,208,  0,  7, 10,  0,  0,  3, 16,  0,  0,  0,  6, -6, 18, 80),  /* 9: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,208, 15,  7, 10,  0,  0,  3, 16,  0,  0,  0,  6, -6, 34, 80),  /* 10: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,208,  1,  7, 10,  0,  0,  9, 16,  0,  0,  0,  8, -8, 39, 80),  /* 11: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,208,  1,  7, 10,  0,  0,  3, 16,  0,  0,  0,  6, -6, 39, 80),  /* 12: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,208,  1,  7, 10,  0,  0,  3, 16,  0,  0,  0,  6, -6, 39, 80),  /* 13: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,208,  1,  7, 10,  0,  0,  3, 16,  0,  0,  0,  6, -6, 39, 80),  /* 14: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,208,  1,  7, 10,  0,  0,  9, 16,  0,  0,  0,  8, -8, 39, 80),  /* 15: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,208,  1,  7, 10,  0,  0,  3, 16,  0,  0,  0,  6, -6, 39, 80),  /* 16: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,208,  1,  7, 10,  0,  0,  3, 16,  0,  0,  0,  6, -6, 39, 80),  /* 17: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,208,  1,  7, 10,  0,  0,  3, 16,  0,  0,  0,  6, -6, 39, 80),  /* 18: not used by a script */
    ATTR( 32,  0,  0,  1,  0, 15,  0,208,  0,  7, 10,  0, 10, 12, 16,  1,  0,  0,  6, -6, 69, 80),  /* 19: not used by a script */
    ATTR( 32,  0,  0,  1,  0, 15,  0, 80, 12,  7, 10,  0, 11,  9, 20,  1,  1,  0,  8, -8, 67, 80),  /* 20: not used by a script */
    ATTR( 32,  0,  0,  1,  0, 15,  0, 80, 13,  7, 10,  0, 11,  9, 20,  1,  1,  0,  8, -8, 67, 80),  /* 21: not used by a script */
    ATTR( 32,  0,  0,  1,  0, 15,  0, 80, 14,  7, 10,  0, 11,  9, 20,  1,  1,  0,  8, -8, 67, 80),  /* 22: not used by a script */
    ATTR( 32,  0,  0,  1,  0, 15,  0, 80, 15,  7, 10,  0, 11, 15, 20,  1,  1,  0,  8, -8, 67, 80),  /* 23: not used by a script */
    ATTR( 36,  0,  0,  1,  0, 15,  0, 80, 10,  7, 10,  0, 11,  9, 20,  1,  4,  0,  8, -8, 67, 80),  /* 24: not used by a script */
    ATTR( 32,  1,  0,  1,  0, 15,  3, 80, 12,  7, 10,  0, 18, 15, 26,  1,  2,  0, 10,-14, 67, 80),  /* 25: not used by a script */
    ATTR( 93,  0,  0,  2,  0, 15,  7,208, 12,  7, 14,  0, 10, 57, 26,  4,  0,  0,  8,-16, 68, 78),  /* 26: not used by a script */
    ATTR( 93,  0,  0,  2,  0, 15,  7,208, 12,  7, 14,  0, 10, 57, 26,  4,  0,  0,  8, 16, 68, 78),  /* 27: not used by a script */
    ATTR( 32,  0,  0,  1,  0, 15,  7, 16, 11,  7, 10,  0,  0, 15,  0,  1,  2,  0,  6, -6, 86, 80),  /* 28: not used by a script */
    ATTR( 32,  0,  0,  1,  0, 15,  7,  4,  9,  7, 10,  0, 19,  6,  1,  0,  0,  0,  0, -3, 86, 80),  /* 29: not used by a script */
    ATTR( 36,  0,  0,  2,  0, 15,  7,  0,  9,  7, 10,  0, 19,  6,  1,  0,  0,  0,  0, -4, 86, 80),  /* 30: not used by a script */
    ATTR( 32,  0,  0,  2,  0, 15,  3, 80, 12,  7, 10,  0, 11, 18, 20,  1,  2,  0,  4,-16, 67, 80),  /* 31: not used by a script */
    ATTR( 37,  0,  1,  1,  0, 15,  0, 80, 14,  7, 10,  0,  3, 21, 20,  1,  1,  0,  6, -8, 68, 80),  /* 32: not used by a script */
    ATTR( 37,  0,  3,  1,  0, 15,  0, 80, 14,  7, 10,  0,  3, 21, 20,  1,  1,  0,  8, -8, 68, 80),  /* 33: not used by a script */
    ATTR( 91,  0,  2,  2,  0, 13,  0,208, 13,  7, 10,  0, 14, 24, 16,  2,  0,  0, 12,-12,  0, 80),  /* 34: not used by a script */
};
