/*
 * GILL_ATTR.C  Gill's attack attributes
 *
 * gill_catt_table has one attack attribute per row, written with ATTR (charscr.h): reaction,
 * attribute and chip damage class, guard type, knock-back, blow-away type, damage (pow), stun
 * (piyo), super art gain, hit stop and marks. A frame line's att picks the row (negative: a new
 * hit); set_new_attnum (CHARMOVE) copies it into the work. Each row names the moves using it.
 */

#include "types.h"
#include "structs.h"
#include "charscr.h"

#pragma section CHR

const ATTACK_ATTR gill_catt_table[35] = {
    /*   rea zu  att kez mkh dip zur fr4 dir vs  grd nd  but pow imp piy art ng  hsm hsy hit dmg */
    ATTR(  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0),  /* 0: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,  0, 11,  3, 10,  0,  0, 15, 32,  2,  1,  0,  7, -7, 13, 72),  /* 1: S PUNCH A, UP P GUARD P S, FUSHIN P S */
    ATTR( 32,  0,  0,  1,  0, 15,  0,  0, 15,  3, 11,  0,  0, 36, 33,  6,  4,  0,  8, -8, 18, 72),  /* 2: M PUNCH C */
    ATTR( 32,  0,  0,  1,  0, 15,  0,  0, 12,  3, 11,  0,  0, 33, 34,  6,  4,  0,  8, -8, 18, 72),  /* 3: M PUNCH A, UP P GUARD P M */
    ATTR( 32,  0,  1,  1,  0, 15,  0,  0, 12,  3, 12,  0,  0, 21, 35,  8,  7,  0,  9, -9, 23, 73),  /* 4: not used by a script */
    ATTR( 36,  0,  1,  2,  0, 15,  0, 16, 10,  3, 12,  0,  9, 51, 35,  8,  7,  0,  9, -9, 23, 73),  /* 5: L PUNCH A */
    ATTR( 32,  0,  0,  0,  0, 15,  0,  0, 11,  3, 10,  0,  0, 18, 32,  3,  1,  0,  7, -7, 29, 72),  /* 6: S KICK A */
    ATTR( 32,  0,  0,  0,  0, 15,  0,  0, 12,  3, 10,  0,  0, 21, 32,  4,  1,  0,  7, -7, 29,  0),  /* 7: not used by a script */
    ATTR( 32,  0,  0,  1,  0, 15,  0,  0, 13,  3, 11,  0,  0, 30, 34,  6,  4,  0,  8, -8, 34, 72),  /* 8: M KICK A */
    ATTR( 32,  0,  1,  2,  0, 14,  0, 16, 11,  3, 12,  0,  9, 21, 35,  2,  8,  0,  9, -9, 39, 73),  /* 9: L KICK A, UP P GUARD P L */
    ATTR( 36,  0,  1,  2,  0, 14,  0, 16,  9,  3, 12,  0,  9, 33, 35,  8,  1,  0,  9, -9, 39, 73),  /* 10: L KICK A, UP P GUARD P L */
    ATTR( 32,  0,  0,  2,  0, 15,  0,  0, 11,  3, 12,  0,  0, 51, 36,  8,  7,  0,  9, -9, 39,  0),  /* 11: not used by a script */
    ATTR( 32,  0,  0,  0,  0, 15,  0,  0, 13,  3, 10,  0,  0,  9, 32,  2,  1,  0,  7, -7, 13, 72),  /* 12: KAGAMI P A */
    ATTR( 32,  0,  0,  1,  0, 15,  0,  0, 14,  3, 11,  0,  0, 21, 34,  6,  4,  0,  8, -8, 18, 72),  /* 13: KAGAMI P A */
    ATTR( 95,  0,  3,  3,  0, 15,  0, 16, 15,  3, 12,  0,  8, 21, 35,  4,  1,  0,  9, -9, 23, 73),  /* 14: KAGAMI P A */
    ATTR( 32,  0,  0,  0,  0, 13,  0,  0, 11,  3, 10,  0,  0,  9, 32,  1,  1,  0,  7, -7, 29, 72),  /* 15: KAGAMI K A */
    ATTR( 32,  0,  0,  1,  0, 13,  0,  0, 12,  3, 11,  0,  0, 27, 34,  3,  4,  0,  8, -8, 34, 72),  /* 16: KAGAMI K A */
    ATTR( 89,  0,  1,  0,  0, 13,  0, 16, 13,  3, 12,  0,  1, 39, 36,  4,  7,  0,  9, -9, 39, 73),  /* 17: KAGAMI K A */
    ATTR( 32,  0,  0,  0,  0, 14,  0,  0,  9,  3, 10,  0,  0, 21, 37,  4,  1,  0,  6, -6, 13, 72),  /* 18: V JUMP P S A */
    ATTR( 32,  0,  0,  1,  0, 14,  0,  0, 11,  3, 11,  0,  0, 33, 38,  6,  4,  0,  7, -7, 18, 72),  /* 19: V JUMP P M A, V JUMP K S A */
    ATTR( 32,  0,  3,  2,  0, 14,  0, 16, 10,  3, 12,  0,  0, 45, 39,  8,  7,  0,  8, -8, 23, 73),  /* 20: V JUMP P L A, ATTACK 4 M */
    ATTR( 32,  0,  0,  1,  0,  8,  0,  0, 11,  3, 14,  0,  0,254, 34,  0,  0,  1,  8, -8,  0, 73),  /* 21: M PUNCH A, M PUNCH C, L PUNCH A +3 */
    ATTR( 32,  0,  0,  1, 54, 15,  0,  0, 10,  3, 14,  0,  2, 81, 38,  9, 13,  0, 10,-10, 55, 73),  /* 22: CATCH 1 */
    ATTR( 32,  0,  0,  2, 38, 15,  0,  0,  6,  3, 14,  0,  4, 12, 36,  2,  1,  0, 12,-12, 71, 72),  /* 23: CATCH 2 */
    ATTR( 36,  0,  0,  2,  0, 14,  0, 72, 10,  3, 14,  0,  5, 15, 36,  4,  4,  0,  8, -8, 44, 73),  /* 24: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    ATTR( 35,  0,  0,  2,  0, 14,  0, 72, 13,  3, 14,  0,  6, 39, 36,  6,  1,  0, 16,-16, 44, 73),  /* 25: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    ATTR( 32,  0,  0,  2,  0, 14,  1, 72, 13,  3, 14,  0, 12, 45, 36,  9,  4,  0, 12,-12, 96, 73),  /* 26: ATTACK 5 M (Att_SENPUUKYAKU) */
    ATTR( 32,  0,  0,  1,  0, 15,  0, 16, 12,  3,  0,  0,  6,  6, 36,  2,  1,  0, 12,-12, 28, 73),  /* 27: not used by a script */
    ATTR( 38,  0,  3,  2,  0, 15,  0, 16, 13,  3, 12,  0,  7, 27, 35,  4,  8,  0,  9, -9, 23, 73),  /* 28: KAGAMI P A */
    ATTR( 32,  0,  0,  0,  0, 14,  0,  0, 12,  3, 10,  0,  0, 21, 37,  4,  1,  0,  6, -6, 29, 72),  /* 29: V JUMP K S A */
    ATTR( 32,  0,  0,  1,  0, 14,  0,  0, 13,  3, 11,  0,  0, 33, 38,  6,  4,  0,  7, -7, 34, 72),  /* 30: V JUMP K M A */
    ATTR( 32,  0,  3,  2,  0, 14,  0, 16, 11,  3, 12,  0,  0, 45, 39,  8,  7,  0,  8, -8, 39, 73),  /* 31: V JUMP K L A */
    ATTR(110,  1,  0,  1, 53, 15,  0,  8,  2,  3, 12,  0, 10, 69, 39,  2,  7,  0, 16,-16, 28, 60),  /* 32: ATTACK 2 M (Att_ABISEGERI) */
    ATTR( 33,  0,  1,  2,  0, 15,  0,  8, 11,  3, 12,  0, 11, 45, 39,  8,  1,  0, 12,-12, 28, 72),  /* 33: ATTACK 2 M (Att_ABISEGERI) */
    ATTR( 32,  0,  0,  1,  0, 14,  0,  0,  9,  3, 10,  0,  0, 21, 37,  4,  4,  0,  7, -7, 13, 72),  /* 34: saca 49 */
};
