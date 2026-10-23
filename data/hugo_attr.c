/*
 * HUGO_ATTR.C  Hugo's attack attributes
 *
 * hugo_catt_table has one attack attribute per row, written with ATTR (charscr.h): reaction,
 * attribute and chip damage class, guard type, knock-back, blow-away type, damage (pow), stun
 * (piyo), super art gain, hit stop and marks. A frame line's att picks the row (negative: a new
 * hit); set_new_attnum (CHARMOVE) copies it into the work. Each row names the moves using it.
 */

#include "types.h"
#include "structs.h"
#include "charscr.h"

#pragma section CHR

const ATTACK_ATTR hugo_catt_table[2] = {
    /*   rea zu  att kez mkh dip zur fr4 dir vs  grd nd  but pow imp piy art ng  hsm hsy hit dmg */
    ATTR(  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0),  /* 0: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,  0, 12,  3, 10,  0,  0,  9,  0,  4,  1,  0,  7, -7, 13, 72),  /* 1: not used by a script */
};
