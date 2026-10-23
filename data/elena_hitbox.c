/*
 * ELENA_HITBOX.C  Elena's hit boxes
 *
 * Each of Elena's animation frames names a row of elena_hit_ix_table (a frame line's hit field).
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
 * rows of elena_catt_table dealt through it. Row 0 of a box table is no box.
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

const HIT_IX elena_hit_ix_table[263] = {
    /* boix  atix  cuix  hoix */
    {    0,    0,    0,    0 },  /* 0: OKIAGARI, OKIAGARI F, OKIAGARI B +9 */
    {    1,    0,    1,    1 },  /* 1: KAMAE, STAND UP, WALK END +54 */
    {    2,    0,    1,    1 },  /* 2: FRONT WALK, BACK WALK */
    {    3,    0,    2,    2 },  /* 3: KAGAMU, KAGAMI KAMAE, PARING DOWN +18 */
    {   11,    0,    1,    1 },  /* 4: TUKAMIKAKARI 1, PIYO, yuca 60 */
    {    4,    0,    3,    3 },  /* 5: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +4 */
    {    5,    0,    3,    3 },  /* 6: JUMP FRONT, S JUMP FRONT, PARING AIR F +16 */
    {    6,    0,    5,    6 },  /* 7: AIR S, AIR M, AIR L +21 */
    {    7,    0,    6,    5 },  /* 8: DASH HUMIKOMI */
    {    8,    0,    6,    5 },  /* 9: DASH HUMIKOMI */
    {    9,    0,    1,    1 },  /* 10: DASH HUMIKOMI, ATTACK 5 S (Att_SHOURYUUREPPA) */
    {   10,    0,    1,    1 },  /* 11: DASH HUMIKOMI */
    {   12,    0,    3,    3 },  /* 12: GUARD AIR */
    {  185,    0,    0,    0 },  /* 13: saca 49, SP APPEAR 1 */
    {   13,    0,    2,    2 },  /* 14: KAGAMI TURN */
    {   14,    0,    2,    2 },  /* 15: KAGAMI TURN */
    {   15,    0,    1,    1 },  /* 16: HURIMUKI */
    {   16,    0,    1,    1 },  /* 17: HURIMUKI */
    {   17,    0,    1,    1 },  /* 18: HURIMUKI */
    {   18,    0,    1,    1 },  /* 19: HURIMUKI */
    {   19,    0,    2,    2 },  /* 20: KAGAMI P A */
    {   21,    0,    7,    2 },  /* 21: KAGAMI P A */
    {   22,    0,    7,    2 },  /* 22: KAGAMI P A */
    {   21,    0,    2,    2 },  /* 23: KAGAMI P A */
    {   22,    0,    2,    2 },  /* 24: KAGAMI P A */
    {   23,    0,    7,    2 },  /* 25: KAGAMI K A */
    {   24,    2,    7,    2 },  /* 26: KAGAMI K A */
    {   24,    0,    7,    2 },  /* 27: KAGAMI K A */
    {   25,    0,    7,    2 },  /* 28: KAGAMI K A */
    {   26,    0,    7,    2 },  /* 29: KAGAMI K A */
    {   27,    3,    2,    2 },  /* 30: not used by a script */
    {   27,    0,    2,    2 },  /* 31: KAGAMI P A */
    {   28,    0,    2,    2 },  /* 32: KAGAMI P A, KAGAMI K A, ATTACK 6 S */
    {   29,    0,    2,    2 },  /* 33: KAGAMI P A, ATTACK 6 S */
    {   30,    0,    2,    2 },  /* 34: KAGAMI P A, ATTACK 6 S */
    {   31,    0,    2,    2 },  /* 35: KAGAMI P A, ATTACK 6 S */
    {   32,    4,    2,    2 },  /* 36: KAGAMI P A, ATTACK 6 S */
    {   32,    0,    2,    2 },  /* 37: KAGAMI P A */
    {   33,    0,    2,    2 },  /* 38: KAGAMI P A, ATTACK 6 S */
    {   34,    0,    2,    2 },  /* 39: KAGAMI K A */
    {   35,    0,    2,    2 },  /* 40: KAGAMI K A */
    {   36,    0,    2,    2 },  /* 41: KAGAMI K A */
    {   37,    5,    2,    2 },  /* 42: not used by a script */
    {   37,    0,    2,    2 },  /* 43: KAGAMI K A */
    {   38,    0,    3,    3 },  /* 44: V JUMP P S A, F JUMP P S A, ATTACK 5 S (Att_SHOURYUUREPPA) +1 */
    {   39,    0,    3,    3 },  /* 45: V JUMP P S A, F JUMP P S A, ATTACK 5 S (Att_SHOURYUUREPPA) +1 */
    {   40,    6,    3,    3 },  /* 46: V JUMP P S A, F JUMP P S A */
    {  107,    0,    3,    3 },  /* 47: V JUMP P S A, V JUMP P M A, V JUMP P L A +10 */
    {  108,    0,    3,    3 },  /* 48: V JUMP P M A, V JUMP P L A, V JUMP K S A +6 */
    {  109,    7,    3,    3 },  /* 49: V JUMP P M A, F JUMP P M A */
    {  109,    0,    3,    3 },  /* 50: V JUMP P M A, F JUMP P M A */
    {  110,    0,    3,    3 },  /* 51: V JUMP P L A, F JUMP P L A */
    {  111,    0,    3,    3 },  /* 52: V JUMP P L A, F JUMP P L A */
    {  112,    8,    3,    3 },  /* 53: V JUMP P L A, F JUMP P L A */
    {  112,    0,    3,    3 },  /* 54: V JUMP P L A, F JUMP P L A */
    {  114,    0,    3,    3 },  /* 55: V JUMP K S A, F JUMP K S A */
    {  114,    9,    3,    3 },  /* 56: V JUMP K S A, F JUMP K S A */
    {  115,   10,    3,    3 },  /* 57: V JUMP K M A, F JUMP K M A, atca 156 */
    {  115,    0,    3,    3 },  /* 58: V JUMP K M A, F JUMP K M A, atca 156 */
    {    0,    0,    1,    1 },  /* 59: ATTACK 5 S (Att_SHOURYUUREPPA) */
    {    0,    0,    0,    6 },  /* 60: AIR S, AIR M, AIR L +2 */
    {    1,    0,    1,    1 },  /* 61: GUARD HEAD, GUARD UP, APPEAR 5 */
    {    1,    0,    1,    1 },  /* 62: GUARD UP, GUARD AIR, HUSHIN HEAD +3 */
    {    0,    0,    0,    1 },  /* 63: FUSHIN P S, ATTACK 4 S (Att_SHOURYUUREPPA), ATTACK 5 S (Att_SHOURYUUREPPA) +2 */
    {    0,    0,    0,    6 },  /* 64: PARING AIR B */
    {   46,    0,    1,    1 },  /* 65: not used by a script */
    {   47,    0,    1,    1 },  /* 66: not used by a script */
    {   48,    0,    1,    1 },  /* 67: HANASARE */
    {   49,    0,    1,    1 },  /* 68: HUSHIN HEAD, HUSHIN DOWN, HANASARE +1 */
    {   50,    0,    5,    6 },  /* 69: PARING AIR F */
    {   51,    0,    5,    6 },  /* 70: not used by a script */
    {   52,    0,    1,    2 },  /* 71: M PUNCH C, ATTACK 6 S */
    {   53,    0,    1,    1 },  /* 72: M PUNCH C, ATTACK 6 S */
    {   54,   26,    1,    1 },  /* 73: M PUNCH C, ATTACK 6 S */
    {   54,    0,    1,    1 },  /* 74: M PUNCH C, OKIAGARI P S */
    {   55,    0,    1,    1 },  /* 75: M PUNCH C, ATTACK 6 S */
    {   56,    0,    1,    2 },  /* 76: M PUNCH A, ATTACK 6 S */
    {   57,    0,    1,    2 },  /* 77: M PUNCH A, ATTACK 6 S */
    {   58,   49,    1,    2 },  /* 78: M PUNCH A */
    {   59,   27,    1,    2 },  /* 79: M PUNCH A, ATTACK 6 S */
    {   59,    0,    1,    2 },  /* 80: M PUNCH A */
    {   60,    0,    1,    2 },  /* 81: M PUNCH A */
    {   61,    0,    1,    2 },  /* 82: M PUNCH A */
    {   62,    0,    1,    1 },  /* 83: L PUNCH A, ATTACK 6 S */
    {   63,    0,    1,    1 },  /* 84: L PUNCH A, ATTACK 6 L, ATTACK 6 SP */
    {   64,    0,    1,    1 },  /* 85: L PUNCH A, ATTACK 6 S */
    {   65,   28,    1,    1 },  /* 86: not used by a script */
    {   65,   41,    1,    1 },  /* 87: L PUNCH A, ATTACK 6 S */
    {   66,    0,    1,    1 },  /* 88: L PUNCH A, ATTACK 6 L, ATTACK 6 SP */
    {   67,    0,    1,    1 },  /* 89: L KICK A, ATTACK 6 S */
    {   68,    0,    1,    1 },  /* 90: L KICK A, ATTACK 6 S */
    {   69,    0,    3,    3 },  /* 91: L KICK A, UP P GUARD P L, ATTACK 6 S */
    {   70,   29,    3,    3 },  /* 92: L KICK A, ATTACK 6 S */
    {   70,    0,    3,    3 },  /* 93: L KICK A, UP P GUARD P L */
    {   71,    0,    3,    3 },  /* 94: UP P GUARD P L */
    {   72,    0,    3,    3 },  /* 95: L KICK A, UP P GUARD P L */
    {   73,    0,    1,    1 },  /* 96: L KICK A, UP P GUARD P L */
    {   74,    0,    1,    1 },  /* 97: S PUNCH A, UP P GUARD P S, ATTACK 5 S (Att_SHOURYUUREPPA) */
    {   75,   30,    1,    1 },  /* 98: S PUNCH A, UP P GUARD P S */
    {   75,    0,    1,    1 },  /* 99: S PUNCH A */
    {   75,    0,    1,    1 },  /* 100: UP P GUARD P S */
    {   76,    0,    1,    1 },  /* 101: S PUNCH A, UP P GUARD P S */
    {   77,    0,    1,    1 },  /* 102: S PUNCH A, UP P GUARD P S */
    {   78,    0,    1,    1 },  /* 103: S KICK A, D P GUARD P S, FUSHIN P S +1 */
    {   79,   32,    1,    1 },  /* 104: S KICK A, D P GUARD P S, FUSHIN P S +1 */
    {   79,    0,    1,    1 },  /* 105: S KICK A, D P GUARD P S */
    {   81,    0,    1,    1 },  /* 106: S KICK A, D P GUARD P S */
    {   82,    0,    2,    2 },  /* 107: L KICK C, KAGAMI K C, D P GUARD P M */
    {   83,    0,    2,    2 },  /* 108: L KICK C, KAGAMI K C, D P GUARD P M */
    {  206,   33,    2,    2 },  /* 109: D P GUARD P M */
    {   84,   33,    2,    2 },  /* 110: L KICK C, KAGAMI K C, D P GUARD P M */
    {   84,    0,    2,    2 },  /* 111: L KICK C, KAGAMI K C, D P GUARD P M */
    {   86,    0,    2,    2 },  /* 112: L KICK C, KAGAMI K C, D P GUARD P M */
    {   87,    0,    2,    2 },  /* 113: L KICK C, KAGAMI K C, D P GUARD P M */
    {   88,    0,    2,    2 },  /* 114: L KICK C, KAGAMI K C, D P GUARD P M */
    {   89,    0,    1,    1 },  /* 115: L KICK C, KAGAMI K C, D P GUARD P M */
    {   90,    0,    1,    1 },  /* 116: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    {   91,    0,    1,    1 },  /* 117: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    {   92,    0,    3,    3 },  /* 118: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    {   93,    0,    3,    3 },  /* 119: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    {   94,    0,    3,    3 },  /* 120: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    {   95,    0,    3,    3 },  /* 121: HANASARE, ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU) +1 */
    {   96,   35,    1,    1 },  /* 122: HANASARE */
    {   97,   36,    1,    1 },  /* 123: HANASARE */
    {   98,    0,    1,    1 },  /* 124: HANASARE */
    {   99,    0,    1,    1 },  /* 125: not used by a script */
    {  100,    0,    1,    2 },  /* 126: M KICK A, UP P GUARD P M, ATTACK 6 S */
    {  101,    0,    1,    2 },  /* 127: M KICK A, UP P GUARD P M, ATTACK 6 S */
    {  102,    0,    1,    2 },  /* 128: M KICK A, UP P GUARD P M, ATTACK 6 S */
    {  103,   37,    1,    2 },  /* 129: M KICK A, UP P GUARD P M, ATTACK 6 S */
    {  104,    0,    1,    2 },  /* 130: M KICK A */
    {  105,    0,    1,    2 },  /* 131: M KICK A, UP P GUARD P M */
    {  106,    0,    1,    1 },  /* 132: M KICK A, UP P GUARD P M */
    {   97,    0,    1,    1 },  /* 133: not used by a script */
    {  116,    0,    3,    3 },  /* 134: V JUMP K L A, F JUMP K L A */
    {  117,    0,    3,    3 },  /* 135: V JUMP K L A, F JUMP K L A */
    {  118,    0,    3,    3 },  /* 136: V JUMP K L A, F JUMP K L A */
    {  119,   11,    3,    3 },  /* 137: V JUMP K L A, F JUMP K L A */
    {  120,    0,    3,    3 },  /* 138: V JUMP K L A, F JUMP K L A */
    {  121,    0,    3,    3 },  /* 139: V JUMP K L A, F JUMP K L A */
    {  122,    0,    3,    3 },  /* 140: V JUMP K L A, F JUMP K L A */
    {  123,    0,    2,    2 },  /* 141: KAGAMI K A, ATTACK 6 S */
    {  124,    0,    2,    2 },  /* 142: KAGAMI K A, ATTACK 6 S */
    {  125,   12,    2,    2 },  /* 143: KAGAMI K A, ATTACK 6 S */
    {  126,    0,    2,    2 },  /* 144: KAGAMI K A */
    {  127,    0,    2,    2 },  /* 145: KAGAMI K A */
    {  128,    0,    2,    2 },  /* 146: KAGAMI K A */
    {  129,    0,    2,    2 },  /* 147: KAGAMI K A */
    {  130,    0,    2,    2 },  /* 148: KAGAMI K A */
    {    0,    0,    0,    4 },  /* 149: TATAKI S, TATAKI V. S, KGM TATAKI S +18 */
    {  131,    0,    2,    4 },  /* 150: OKIAGARI P S */
    {  132,   13,    2,    4 },  /* 151: OKIAGARI P S */
    {  132,    0,    2,    4 },  /* 152: OKIAGARI P S */
    {  133,    0,    2,    4 },  /* 153: OKIAGARI P S */
    {  134,    0,    2,    4 },  /* 154: OKIAGARI P S */
    {  135,    0,    2,    4 },  /* 155: OKIAGARI P S */
    {  136,    0,    2,    4 },  /* 156: OKIAGARI P S */
    {  137,   14,    3,    3 },  /* 157: UP P GUARD P L */
    {  138,   15,    3,    3 },  /* 158: UP P GUARD P L */
    {   80,   48,    1,    1 },  /* 159: not used by a script */
    {  140,    0,    1,    1 },  /* 160: L PUNCH A, ATTACK 6 L, ATTACK 6 SP */
    {  141,    0,    1,    1 },  /* 161: UP P GUARD P L */
    {  142,    0,    1,    1 },  /* 162: UP P GUARD P L */
    {  143,    0,    1,    2 },  /* 163: DASH TOBINOKI */
    {  144,    0,    1,    2 },  /* 164: DASH TOBINOKI */
    {  145,    0,    1,    2 },  /* 165: DASH TOBINOKI */
    {  146,    0,    1,    2 },  /* 166: DASH TOBINOKI */
    {  147,    0,    1,    2 },  /* 167: DASH TOBINOKI */
    {  148,    0,    1,    2 },  /* 168: DASH TOBINOKI */
    {  149,    0,    1,    2 },  /* 169: DASH TOBINOKI */
    {  150,    0,    1,    1 },  /* 170: DASH TOBINOKI */
    {    1,   16,    1,    1 },  /* 171: M PUNCH A, M PUNCH C */
    {  181,   54,    5,    6 },  /* 172: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  182,   38,    5,    6 },  /* 173: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {   98,   25,    1,    1 },  /* 174: HANASARE */
    {  183,   39,    3,    3 },  /* 175: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  184,   40,    3,    3 },  /* 176: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  118,   42,    3,    3 },  /* 177: V JUMP K L A, F JUMP K L A */
    {  156,    0,    0,    6 },  /* 178: ATTACK 1 M (Att_SHOURYUUKEN) */
    {  157,   17,    5,    6 },  /* 179: ATTACK 1 M (Att_SHOURYUUKEN) */
    {  158,   18,    5,    6 },  /* 180: ATTACK 1 M (Att_SHOURYUUKEN) */
    {  159,    0,    5,    6 },  /* 181: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN) */
    {  160,    0,    5,    6 },  /* 182: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN) +1 */
    {  161,    0,    5,    6 },  /* 183: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN) +1 */
    {  162,    0,    5,    6 },  /* 184: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN) +1 */
    {  163,    0,    1,    1 },  /* 185: HANASARE */
    {  164,    0,    1,    1 },  /* 186: S PUNCH C, ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU) +1 */
    {  165,    0,    1,    1 },  /* 187: S PUNCH C, ATTACK 2 L (Att_SENPUUKYAKU) */
    {  166,    0,    1,    1 },  /* 188: S PUNCH C, ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  167,    0,    1,    1 },  /* 189: S PUNCH C, ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  168,    0,    1,    1 },  /* 190: S PUNCH C, ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU) +1 */
    {  169,    0,    1,    1 },  /* 191: S PUNCH C, ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU) +1 */
    {  170,    0,    1,    1 },  /* 192: S PUNCH C, ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU) +1 */
    {  171,    0,    1,    1 },  /* 193: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  172,   20,    3,    3 },  /* 194: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  173,   21,    3,    3 },  /* 195: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  174,   22,    3,    3 },  /* 196: ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  175,    0,    3,    3 },  /* 197: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  176,   23,    3,    3 },  /* 198: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  176,    0,    3,    3 },  /* 199: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  177,    0,    3,    3 },  /* 200: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  178,    0,    5,    6 },  /* 201: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  179,   24,    5,    6 },  /* 202: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  179,    0,    5,    6 },  /* 203: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  180,    0,    1,    1 },  /* 204: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    {  186,    0,    1,    1 },  /* 205: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  187,   43,    1,    1 },  /* 206: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  188,   44,    1,    1 },  /* 207: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  189,   45,    1,    1 },  /* 208: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  190,   46,    1,    1 },  /* 209: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  191,   47,    1,    1 },  /* 210: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  192,    0,    1,    1 },  /* 211: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  193,    0,    1,    1 },  /* 212: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  194,    0,    1,    1 },  /* 213: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  195,    0,    1,    1 },  /* 214: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  196,    0,    1,    1 },  /* 215: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  197,    0,    1,    1 },  /* 216: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  198,    0,    1,    1 },  /* 217: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  199,    0,    1,    1 },  /* 218: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  200,    0,    1,    1 },  /* 219: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  201,    0,    1,    1 },  /* 220: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  202,    0,    1,    1 },  /* 221: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  203,    0,    1,    1 },  /* 222: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  204,    0,    1,    1 },  /* 223: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {    0,   44,    1,    1 },  /* 224: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  223,   31,    1,    1 },  /* 225: ATTACK 5 S (Att_SHOURYUUREPPA) */
    {  119,    0,    3,    3 },  /* 226: V JUMP K L A, F JUMP K L A */
    {   40,   62,    3,    3 },  /* 227: ATTACK 5 S (Att_SHOURYUUREPPA) */
    {  103,    0,    1,    2 },  /* 228: M KICK A */
    {  205,    0,    1,    2 },  /* 229: not used by a script */
    {  209,    1,    7,    2 },  /* 230: KAGAMI P A */
    {   27,    3,    2,    2 },  /* 231: KAGAMI P A */
    {   55,    0,    1,    2 },  /* 232: M PUNCH C */
    {  211,    0,    2,    2 },  /* 233: KAGAMI K A */
    {  211,    5,    2,    2 },  /* 234: KAGAMI K A */
    {  125,    0,    2,    2 },  /* 235: KAGAMI K A */
    {  174,    0,    3,    3 },  /* 236: ATTACK 2 S (Att_SENPUUKYAKU) */
    {  224,    0,    2,    2 },  /* 237: super art Att_PL08_HEALING (command slot 18) */
    {  207,   28,    1,    1 },  /* 238: L PUNCH A */
    {   65,    0,    1,    1 },  /* 239: L PUNCH A, ATTACK 6 L, ATTACK 6 SP */
    {  208,    0,    1,    1 },  /* 240: L PUNCH A, ATTACK 6 L, ATTACK 6 SP */
    {  210,    0,    2,    2 },  /* 241: KAGAMI P A */
    {  212,    0,    1,    2 },  /* 242: M PUNCH A */
    {  213,   50,    3,    3 },  /* 243: L KICK A, ATTACK 6 S */
    {  214,   51,    3,    3 },  /* 244: L KICK A */
    {  215,    0,    1,    2 },  /* 245: M KICK A */
    {  216,    0,    0,    6 },  /* 246: ATTACK 1 S (Att_SHOURYUUKEN) */
    {  217,    0,    5,    6 },  /* 247: ATTACK 1 S (Att_SHOURYUUKEN) */
    {  218,   19,    5,    6 },  /* 248: ATTACK 1 S (Att_SHOURYUUKEN) */
    {  219,    0,    0,    6 },  /* 249: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  219,   54,    5,    6 },  /* 250: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  220,   52,    5,    6 },  /* 251: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  221,   53,    5,    6 },  /* 252: ATTACK 1 L (Att_SHOURYUUKEN) */
    {    1,   58,    1,    1 },  /* 253: L PUNCH A */
    {   40,   59,    3,    3 },  /* 254: not used by a script */
    {  222,   11,    3,    3 },  /* 255: not used by a script */
    {    0,    0,    0,    7 },  /* 256: NEKOROBI S */
    {  210,    0,    7,    2 },  /* 257: KAGAMI P A */
    {    1,    0,    0,    1 },  /* 258: BUTTOBI */
    {    3,    0,    0,    2 },  /* 259: KUNOJI BUTTOBI */
    {   40,   63,    3,    3 },  /* 260: saca 50 */
    {  207,   64,    1,    1 },  /* 261: ATTACK 6 S */
    {    1,    0,    1,    0 },  /* 262: LOSE SONABA */
};

const BODY_BOX elena_body_box[225] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {  -32,  22,   72,  19 },  {  -33,  57,   71,  10 },  {  -33,  57,   37,  33 },  {  -33,  64,    0,  36 },  {    0,   0,    0,   0 } } },  /* 1: KAMAE, STAND UP, WALK END +59 */
    { { {  -23,  21,   84,  18 },  {  -28,  52,   72,  18 },  {  -29,  55,   40,  32 },  {  -31,  61,    0,  40 },  {    0,   0,    0,   0 } } },  /* 2: FRONT WALK, BACK WALK */
    { { {  -32,  31,   41,  19 },  {  -16,  44,   41,  13 },  {  -36,  68,   23,  20 },  {  -42,  82,    0,  22 },  {    0,   0,    0,   0 } } },  /* 3: KAGAMU, KAGAMI KAMAE, PARING DOWN +18 */
    { { {  -29,  45,   56,  60 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 4: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +4 */
    { { {  -39,  53,   56,  60 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 5: JUMP FRONT, S JUMP FRONT, PARING AIR F +16 */
    { { {  -14,  33,   59,  16 },  {  -19,  43,   51,  16 },  {  -19,  43,   32,  17 },  {  -14,  33,   25,  16 },  {    0,   0,    0,   0 } } },  /* 6: AIR S, AIR M, AIR L +21 */
    { { {  -46,  16,   62,  16 },  {  -30,  32,   54,  18 },  {  -16,  36,   36,  22 },  {  -12,  48,    0,  32 },  {    0,   0,    0,   0 } } },  /* 7: DASH HUMIKOMI */
    { { {  -46,  16,   62,  16 },  {  -30,  32,   54,  18 },  {  -16,  36,   32,  22 },  {  -22,  66,    0,  32 },  {    0,   0,    0,   0 } } },  /* 8: DASH HUMIKOMI */
    { { {  -36,  16,   66,  16 },  {  -28,  32,   56,  18 },  {  -20,  40,   36,  22 },  {  -30,  68,    0,  36 },  {    0,   0,    0,   0 } } },  /* 9: DASH HUMIKOMI, ATTACK 5 S (Att_SHOURYUUREPPA) */
    { { {  -32,  16,   72,  16 },  {  -20,  32,   60,  18 },  {  -22,  46,   36,  24 },  {  -28,  66,    0,  36 },  {    0,   0,    0,   0 } } },  /* 10: DASH HUMIKOMI */
    { { {  -54,  22,   64,  19 },  {  -36,  48,   68,  10 },  {  -38,  56,   37,  30 },  {  -36,  68,    0,  36 },  {    0,   0,    0,   0 } } },  /* 11: TUKAMIKAKARI 1, PIYO, yuca 60 */
    { { {  -32,  16,   80,  16 },  {  -16,  32,   72,  22 },  {  -28,  50,   46,  26 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 12: GUARD AIR */
    { { {   18,  16,   44,  16 },  {  -16,  32,   30,  18 },  {  -22,  48,   14,  24 },  {  -28,  56,    0,  22 },  {    0,   0,    0,   0 } } },  /* 13: KAGAMI TURN */
    { { {  -14,  16,   48,  16 },  {  -22,  36,   36,  14 },  {  -26,  48,   22,  14 },  {  -28,  56,    0,  22 },  {    0,   0,    0,   0 } } },  /* 14: KAGAMI TURN */
    { { {   18,  16,   53,  15 },  {   -8,  30,   45,  17 },  {  -21,  42,   35,  22 },  {  -16,  39,    0,  33 },  {    0,   0,    0,   0 } } },  /* 15: HURIMUKI */
    { { {  -26,  16,   86,  15 },  {  -24,  30,   73,  17 },  {  -16,  27,   43,  30 },  {   -6,  29,    0,  45 },  {    0,   0,    0,   0 } } },  /* 16: HURIMUKI */
    { { {  -36,  16,   76,  15 },  {  -25,  30,   64,  17 },  {  -21,  27,   33,  30 },  {  -18,  29,    0,  45 },  {    0,   0,    0,   0 } } },  /* 17: HURIMUKI */
    { { {  -40,  16,   60,  15 },  {  -24,  30,   54,  17 },  {   -8,  27,   29,  30 },  {  -26,  29,    0,  45 },  {    0,   0,    0,   0 } } },  /* 18: HURIMUKI */
    { { {  -38,  16,   44,  20 },  {  -28,  40,   36,  24 },  {  -22,  44,   18,  24 },  {  -40,  68,    0,  28 },  {    0,   0,    0,   0 } } },  /* 19: KAGAMI P A */
    { { {  -38,  16,   40,  16 },  {  -28,  44,   28,  32 },  {  -68,  48,    0,  34 },  {  -20,  40,    0,  28 },  { -108,  84,   32,  18 } } },  /* 20: not used by a script */
    { { {  -43,  20,   42,  22 },  {  -22,  34,   40,  23 },  {  -44,  56,   18,  24 },  {  -48,  64,    0,  24 },  {    0,   0,    0,   0 } } },  /* 21: KAGAMI P A */
    { { {  -48,  16,   42,  18 },  {  -36,  44,   36,  22 },  {  -44,  60,   22,  17 },  {  -40,  64,    0,  24 },  {    0,   0,    0,   0 } } },  /* 22: KAGAMI P A */
    { { {   30,  16,   44,  16 },  {    4,  48,   24,  32 },  {  -28,  32,   24,  22 },  {  -36,  88,    0,  24 },  {    0,   0,    0,   0 } } },  /* 23: KAGAMI K A */
    { { {   44,  17,   32,  20 },  {  -11,  55,   24,  32 },  {  -45,  33,   25,  13 },  {  -36,  91,    0,  24 },  {  -92,  56,    0,  24 } } },  /* 24: KAGAMI K A */
    { { {   44,  17,   32,  20 },  {   14,  34,   24,  32 },  {  -28,  42,   24,  26 },  {  -40,  92,    0,  24 },  {    0,   0,    0,   0 } } },  /* 25: KAGAMI K A */
    { { {   -6,  41,   42,  18 },  {    4,  44,   24,  28 },  {  -28,  32,   24,  24 },  {  -36,  88,    0,  24 },  {    0,   0,    0,   0 } } },  /* 26: KAGAMI K A */
    { { {  -43,  20,   40,  22 },  {  -22,  41,   25,  36 },  {  -64,  44,    0,  32 },  {  -20,  40,    0,  24 },  { -100,  82,   32,  22 } } },  /* 27: KAGAMI P A */
    { { {   -4,  16,   44,  16 },  {  -24,  48,   36,  20 },  {  -32,  66,   24,  12 },  {  -36,  80,    0,  24 },  {    0,   0,    0,   0 } } },  /* 28: KAGAMI P A, KAGAMI K A, ATTACK 6 S */
    { { {    0,   0,    0,   0 },  {  -20,  48,   38,  20 },  {  -32,  72,   24,  16 },  {  -36,  88,    0,  24 },  {    0,   0,    0,   0 } } },  /* 29: KAGAMI P A, ATTACK 6 S */
    { { {    0,   0,    0,   0 },  {  -24,  60,   44,  20 },  {  -32,  72,   24,  20 },  {  -36,  88,    0,  24 },  {    0,   0,    0,   0 } } },  /* 30: KAGAMI P A, ATTACK 6 S */
    { { {    0,   0,    0,   0 },  {  -48,  83,   44,  24 },  {  -44,  90,   24,  20 },  {  -45,  97,    0,  24 },  {    0,   0,    0,   0 } } },  /* 31: KAGAMI P A, ATTACK 6 S */
    { { {    0,   0,    0,   0 },  {  -34,  71,   28,  34 },  {  -51,  57,   52,  39 },  {  -50,  99,    0,  33 },  {  -79,  49,   76,  30 } } },  /* 32: KAGAMI P A, ATTACK 6 S */
    { { {    0,   0,    0,   0 },  {  -36,  64,   44,  26 },  {  -24,  68,   24,  20 },  {  -36,  88,    0,  24 },  {  -68,  35,   58,  21 } } },  /* 33: KAGAMI P A, ATTACK 6 S */
    { { {    8,  16,   40,  16 },  {   -2,  44,   24,  26 },  {  -30,  32,   24,  24 },  {  -40,  88,    0,  24 },  {    0,   0,    0,   0 } } },  /* 34: KAGAMI K A */
    { { {   22,  16,   38,  16 },  {   -2,  40,   24,  28 },  {  -30,  32,   24,  24 },  {  -40,  88,    0,  24 },  {    0,   0,    0,   0 } } },  /* 35: KAGAMI K A */
    { { {   40,  16,   32,  16 },  {    8,  36,   24,  34 },  {  -32,  40,   24,  24 },  {  -40,  88,    0,  24 },  {    0,   0,    0,   0 } } },  /* 36: KAGAMI K A */
    { { {   44,  16,   32,  16 },  {    8,  40,   24,  36 },  {  -40,  48,   24,  28 },  {  -40,  88,    0,  24 },  {  -90,  52,   34,  18 } } },  /* 37: KAGAMI K A */
    { { {  -30,  16,   88,  16 },  {  -24,  48,   72,  24 },  {  -36,  58,   52,  24 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 38: V JUMP P S A, F JUMP P S A, ATTACK 5 S (Att_SHOURYUUREPPA) +1 */
    { { {   -2,  16,   92,  16 },  {  -36,  70,   72,  24 },  {  -49,  82,   43,  29 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 39: V JUMP P S A, F JUMP P S A, ATTACK 5 S (Att_SHOURYUUREPPA) +1 */
    { { {   -2,  16,   92,  16 },  {  -36,  70,   72,  24 },  {  -49,  82,   43,  29 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 40: V JUMP P S A, F JUMP P S A, ATTACK 5 S (Att_SHOURYUUREPPA) +1 */
    { { {   -2,  16,   79,  15 },  {    0,  32,   64,  17 },  {   -6,  36,   42,  22 },  {  -28,  54,    0,  42 },  {    0,   0,    0,   0 } } },  /* 41: not used by a script */
    { { {  -11,  16,   79,  15 },  {  -14,  34,   66,  18 },  {   -6,  34,   38,  28 },  {  -12,  40,    0,  38 },  {    0,   0,    0,   0 } } },  /* 42: not used by a script */
    { { {  -28,  16,  100,  16 },  {  -16,  28,   76,  32 },  {  -36,  44,   58,  26 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 43: not used by a script */
    { { {  -30,  16,  100,  16 },  {  -26,  40,   84,  22 },  {  -26,  36,   44,  40 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 44: not used by a script */
    { { {  -28,  16,   98,  16 },  {  -36,  48,   76,  24 },  {  -36,  44,   36,  40 },  {  -36,  54,    0,  36 },  {    0,   0,    0,   0 } } },  /* 45: not used by a script */
    { { {  -28,  16,   80,  16 },  {  -18,  32,   68,  18 },  {  -16,  34,   36,  32 },  {  -30,  54,    0,  36 },  {    0,   0,    0,   0 } } },  /* 46: not used by a script */
    { { {  -38,  16,   64,  16 },  {  -20,  32,   62,  18 },  {  -20,  32,   36,  26 },  {  -32,  54,    0,  36 },  {    0,   0,    0,   0 } } },  /* 47: not used by a script */
    { { {  -38,  16,   46,  16 },  {  -22,  40,   46,  18 },  {  -24,  52,   24,  22 },  {  -36,  68,    0,  24 },  {    0,   0,    0,   0 } } },  /* 48: HANASARE */
    { { {  -34,  16,   66,  16 },  {  -26,  40,   62,  18 },  {  -22,  44,   36,  24 },  {  -28,  52,    0,  36 },  {    0,   0,    0,   0 } } },  /* 49: HUSHIN HEAD, HUSHIN DOWN, HANASARE +1 */
    { { {  -38,  16,   64,  16 },  {  -22,  36,   64,  18 },  {  -24,  40,   32,  32 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 50: PARING AIR F */
    { { {  -30,  16,   72,  16 },  {  -18,  36,   66,  18 },  {  -28,  50,   29,  36 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 51: not used by a script */
    { { {    0,   0,    0,   0 },  {  -44,  72,   24,  22 },  {  -16,  66,   46,  24 },  {  -48,  80,    0,  24 },  {    0,   0,    0,   0 } } },  /* 52: M PUNCH C, ATTACK 6 S */
    { { {    0,   0,    0,   0 },  {  -32,  54,   24,  22 },  {  -16,  48,   46,  43 },  {  -36,  72,    0,  24 },  {    0,   0,    0,   0 } } },  /* 53: M PUNCH C, ATTACK 6 S */
    { { {    0,   0,    0,   0 },  {  -12,  52,   24,  22 },  {  -24,  64,   46,  43 },  {  -18,  72,    0,  24 },  {  -84,  72,   51,  30 } } },  /* 54: M PUNCH C, ATTACK 6 S, OKIAGARI P S */
    { { {  -46,  16,   60,  16 },  {  -36,  56,   50,  22 },  {  -32,  60,   30,  24 },  {  -32,  68,    0,  30 },  {    0,   0,    0,   0 } } },  /* 55: M PUNCH C, ATTACK 6 S */
    { { {  -16,  16,   56,  16 },  {  -30,  52,   44,  18 },  {  -30,  52,   28,  16 },  {  -36,  64,    0,  28 },  {    0,   0,    0,   0 } } },  /* 56: M PUNCH A, ATTACK 6 S */
    { { {   24,  16,   52,  16 },  {  -20,  44,   52,  18 },  {  -28,  60,   32,  20 },  {  -28,  74,    0,  32 },  {    0,   0,    0,   0 } } },  /* 57: M PUNCH A, ATTACK 6 S */
    { { {   32,  23,   36,  18 },  {    8,  28,   32,  32 },  {  -29,  50,   32,  40 },  {  -31,  75,    0,  36 },  {  -38,  37,   59,  29 } } },  /* 58: M PUNCH A */
    { { {   32,  21,   36,  17 },  {   -8,  40,   32,  31 },  {  -39,  31,   32,  57 },  {  -41,  83,    0,  32 },  {  -61,  31,   84,  21 } } },  /* 59: M PUNCH A, ATTACK 6 S */
    { { {   18,  16,   48,  16 },  {  -28,  52,   42,  22 },  {  -30,  56,   24,  18 },  {  -40,  80,    0,  24 },  {    0,   0,    0,   0 } } },  /* 60: M PUNCH A */
    { { {  -16,  16,   60,  16 },  {  -28,  52,   42,  22 },  {  -30,  56,   24,  18 },  {  -40,  80,    0,  24 },  {    0,   0,    0,   0 } } },  /* 61: M PUNCH A */
    { { {   -4,  16,   88,  16 },  {  -18,  48,   66,  22 },  {  -18,  50,   40,  26 },  {  -20,  52,    0,  40 },  {    0,   0,    0,   0 } } },  /* 62: L PUNCH A, ATTACK 6 S */
    { { {   -2,  16,   94,  16 },  {  -20,  52,   74,  20 },  {  -24,  48,   40,  34 },  {  -28,  52,    0,  40 },  {    0,   0,    0,   0 } } },  /* 63: L PUNCH A, ATTACK 6 L, ATTACK 6 SP */
    { { {   -2,  16,   96,  16 },  {  -16,  44,   76,  20 },  {  -24,  44,   44,  32 },  {  -32,  44,    0,  44 },  {    0,   0,    0,   0 } } },  /* 64: L PUNCH A, ATTACK 6 S */
    { { {   -2,  16,   96,  16 },  {  -16,  44,   76,  20 },  {  -24,  44,   44,  32 },  {  -32,  44,    0,  44 },  {  -74,  56,   78,  21 } } },  /* 65: L PUNCH A, ATTACK 6 S, ATTACK 6 L +1 */
    { { {    8,  16,   84,  16 },  {  -16,  48,   68,  22 },  {  -20,  48,   40,  28 },  {  -26,  64,    0,  40 },  {    0,   0,    0,   0 } } },  /* 66: L PUNCH A, ATTACK 6 L, ATTACK 6 SP */
    { { {  -24,  16,   80,  16 },  {  -28,  52,   62,  18 },  {  -20,  56,   36,  26 },  {  -16,  56,    0,  36 },  {    0,   0,    0,   0 } } },  /* 67: L KICK A, ATTACK 6 S */
    { { {  -12,  16,   96,  16 },  {  -20,  48,   80,  20 },  {  -14,  46,   44,  36 },  {   -8,  52,    0,  44 },  {    0,   0,    0,   0 } } },  /* 68: L KICK A, ATTACK 6 S */
    { { {   -8,  16,   96,  16 },  {  -20,  48,   84,  18 },  {  -16,  40,   46,  38 },  {    0,  24,    3,  43 },  {    0,   0,    0,   0 } } },  /* 69: L KICK A, UP P GUARD P L, ATTACK 6 S */
    { { {   -8,  16,   88,  16 },  {  -20,  48,   76,  18 },  {  -16,  40,   38,  38 },  {    0,   0,    0,   0 },  {  -63,  62,   57,  23 } } },  /* 70: L KICK A, ATTACK 6 S, UP P GUARD P L */
    { { {  -22,  16,   84,  16 },  {  -14,  40,   78,  20 },  {  -36,  60,   50,  28 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 71: UP P GUARD P L */
    { { {  -36,  16,   84,  16 },  {  -28,  44,   70,  22 },  {  -26,  52,   34,  36 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 72: L KICK A, UP P GUARD P L */
    { { {  -44,  16,   80,  16 },  {  -34,  48,   70,  18 },  {  -36,  60,   40,  30 },  {  -36,  80,    0,  40 },  {    0,   0,    0,   0 } } },  /* 73: L KICK A, UP P GUARD P L */
    { { {    4,  16,   82,  16 },  {  -12,  44,   60,  22 },  {  -14,  48,   36,  24 },  {  -22,  68,    0,  36 },  {    0,   0,    0,   0 } } },  /* 74: S PUNCH A, UP P GUARD P S, ATTACK 5 S (Att_SHOURYUUREPPA) */
    { { {   -2,  16,   88,  16 },  {  -25,  58,   72,  21 },  {  -23,  57,   36,  40 },  {  -21,  56,    0,  36 },  {  -67,  41,   77,  21 } } },  /* 75: S PUNCH A, UP P GUARD P S */
    { { {   -2,  16,   84,  16 },  {  -14,  48,   64,  18 },  {  -14,  48,   36,  28 },  {  -22,  60,    0,  36 },  {    0,   0,    0,   0 } } },  /* 76: S PUNCH A, UP P GUARD P S */
    { { {   -6,  16,   80,  16 },  {  -14,  48,   60,  22 },  {  -14,  48,   32,  28 },  {  -22,  60,    0,  32 },  {    0,   0,    0,   0 } } },  /* 77: S PUNCH A, UP P GUARD P S */
    { { {  -24,  16,   90,  16 },  {  -20,  40,   72,  22 },  {  -16,  40,   44,  32 },  {  -32,  64,    0,  44 },  {    0,   0,    0,   0 } } },  /* 78: S KICK A, D P GUARD P S, FUSHIN P S +1 */
    { { {  -28,  16,   86,  16 },  {  -22,  42,   68,  24 },  {  -28,  56,   40,  32 },  {  -32,  60,    0,  40 },  {  -60,  28,    0,  40 } } },  /* 79: S KICK A, D P GUARD P S, FUSHIN P S +1 */
    { { {  -28,  16,   88,  16 },  {  -22,  44,   70,  22 },  {  -24,  52,   40,  32 },  {  -36,  64,    0,  40 },  {    0,   0,    0,   0 } } },  /* 80: not used by a script */
    { { {  -38,  16,   80,  16 },  {  -22,  40,   64,  24 },  {  -26,  52,   40,  28 },  {  -30,  60,    0,  40 },  {    0,   0,    0,   0 } } },  /* 81: S KICK A, D P GUARD P S */
    { { {   -8,  16,   64,  16 },  {  -18,  48,   46,  18 },  {  -26,  68,   30,  16 },  {  -44,  88,    0,  30 },  {    0,   0,    0,   0 } } },  /* 82: L KICK C, KAGAMI K C, D P GUARD P M */
    { { {    4,  16,   50,  16 },  {  -18,  52,   38,  18 },  {  -28,  72,   26,  12 },  {  -44,  96,    0,  26 },  {    0,   0,    0,   0 } } },  /* 83: L KICK C, KAGAMI K C, D P GUARD P M */
    { { {    8,  16,   42,  16 },  {   -2,  40,   24,  28 },  {  -28,  26,   24,  24 },  {  -50,  21,   25,  13 },  {  -88, 142,    0,  29 } } },  /* 84: L KICK C, KAGAMI K C, D P GUARD P M */
    { { {   32,  16,   30,  16 },  {    6,  26,   28,  34 },  {  -32,  38,   28,  26 },  {  -24,  72,    0,  28 },  {  -48,  24,    0,  36 } } },  /* 85: not used by a script */
    { { {   36,  16,   28,  16 },  {   12,  24,   28,  32 },  {  -20,  32,   28,  30 },  {  -40,  88,    0,  28 },  {    0,   0,    0,   0 } } },  /* 86: L KICK C, KAGAMI K C, D P GUARD P M */
    { { {    0,   0,    0,   0 },  {   12,  40,   28,  26 },  {  -24,  36,   28,  32 },  {  -36,  88,    0,  28 },  {    0,   0,    0,   0 } } },  /* 87: L KICK C, KAGAMI K C, D P GUARD P M */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -32,  64,   32,  28 },  {  -40,  88,    0,  32 },  {    0,   0,    0,   0 } } },  /* 88: L KICK C, KAGAMI K C, D P GUARD P M */
    { { {  -50,  16,   56,  16 },  {  -34,  40,   50,  18 },  {  -32,  44,   28,  22 },  {  -36,  62,    0,  28 },  {    0,   0,    0,   0 } } },  /* 89: L KICK C, KAGAMI K C, D P GUARD P M */
    { { {  -58,  16,   46,  16 },  {  -42,  30,   40,  36 },  {  -12,  30,   40,  32 },  {  -38,  84,    0,  40 },  {    0,   0,    0,   0 } } },  /* 90: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    { { {    0,   0,    0,   0 },  {  -54,  32,   42,  40 },  {  -22,  40,   42,  46 },  {  -26,  40,    0,  42 },  {    0,   0,    0,   0 } } },  /* 91: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    { { {    0,   0,    0,   0 },  {  -40,  56,   56,  14 },  {  -32,  50,   70,  24 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 92: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    { { {    0,   0,    0,   0 },  {  -30,  46,   58,  14 },  {  -36,  56,   70,  24 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 93: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    { { {    0,   0,    0,   0 },  {  -16,  40,   58,  24 },  {  -36,  20,   58,  24 },  {    0,   0,    0,   0 },  {  -20,  20,   80,  24 } } },  /* 94: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    { { {    0,   0,    0,   0 },  {  -32,  40,   50,  32 },  {   -8,  24,   50,  32 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 95: HANASARE, ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU) +1 */
    { { {  -39,  19,   49,  25 },  {  -20,  28,   42,  40 },  {    8,  32,   42,  44 },  {   -8,  40,    0,  42 },  {   40,  40,   86,  12 } } },  /* 96: HANASARE */
    { { {  -39,  18,   48,  22 },  {  -20,  28,   42,  40 },  {    8,  32,   42,  44 },  {   -8,  40,    0,  42 },  {   40,  48,   56,  16 } } },  /* 97: HANASARE */
    { { {  -38,  16,   54,  22 },  {  -20,  52,   60,  18 },  {  -18,  56,   36,  24 },  {  -16,  60,    0,  36 },  {   36,  49,   46,  21 } } },  /* 98: HANASARE */
    { { {  -26,  30,   71,  16 },  {  -20,  55,   60,  18 },  {  -18,  60,   36,  24 },  {  -16,  80,    0,  36 },  {    0,   0,    0,   0 } } },  /* 99: not used by a script */
    { { {  -36,  16,   52,  16 },  {  -20,  40,   46,  18 },  {  -24,  52,   28,  18 },  {  -28,  68,    0,  28 },  {    0,   0,    0,   0 } } },  /* 100: M KICK A, UP P GUARD P M, ATTACK 6 S */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -28,  56,   32,  28 },  {  -40,  80,    0,  32 },  {    0,   0,    0,   0 } } },  /* 101: M KICK A, UP P GUARD P M, ATTACK 6 S */
    { { {    0,   0,    0,   0 },  {    2,  34,   28,  30 },  {  -34,  36,   28,  32 },  {  -66, 110,    0,  28 },  {    0,   0,    0,   0 } } },  /* 102: M KICK A, UP P GUARD P M, ATTACK 6 S */
    { { {   20,  16,   28,  16 },  {   -8,  28,   28,  36 },  {  -54,  45,   28,  38 },  {  -66, 110,    0,  28 },  {  -97,  41,   49,  24 } } },  /* 103: M KICK A, UP P GUARD P M, ATTACK 6 S */
    { { {    4,  16,   40,  16 },  {  -14,  36,   28,  24 },  {  -58,  43,   28,  31 },  {  -66, 110,    0,  28 },  {  -95,  54,   52,  17 } } },  /* 104: M KICK A */
    { { {   -4,  16,   50,  16 },  {  -24,  48,   34,  22 },  {  -36,  62,   26,  18 },  {  -66, 110,    0,  26 },  {    0,   0,    0,   0 } } },  /* 105: M KICK A, UP P GUARD P M */
    { { {  -14,  16,   70,  16 },  {  -24,  56,   50,  21 },  {  -33,  73,   26,  24 },  {  -53,  97,    0,  26 },  {    0,   0,    0,   0 } } },  /* 106: M KICK A, UP P GUARD P M */
    { { {  -24,  16,   98,  16 },  {  -33,  50,   80,  22 },  {  -44,  62,   48,  31 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 107: V JUMP P S A, V JUMP P M A, V JUMP P L A +10 */
    { { {  -12,  16,   94,  16 },  {  -42,  70,   76,  20 },  {  -47,  70,   48,  29 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 108: V JUMP P M A, V JUMP P L A, V JUMP K S A +6 */
    { { {    2,  26,   94,  16 },  {  -24,  59,   78,  18 },  {  -40,  76,   46,  31 },  {    0,   0,    0,   0 },  {  -94,  68,   65,  21 } } },  /* 109: V JUMP P M A, F JUMP P M A */
    { { {  -14,  16,   96,  16 },  {  -28,  56,   76,  22 },  {  -40,  72,   48,  28 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 110: V JUMP P L A, F JUMP P L A */
    { { {   -6,  16,   94,  16 },  {  -20,  60,   76,  20 },  {  -24,  72,   48,  28 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 111: V JUMP P L A, F JUMP P L A */
    { { {   -8,  16,   96,  16 },  {  -28,  56,   76,  22 },  {  -28,  72,   48,  28 },  {    0,   0,    0,   0 },  {  -84,  55,   47,  25 } } },  /* 112: V JUMP P L A, F JUMP P L A */
    { { {   -4,  16,   94,  16 },  {  -28,  64,   76,  22 },  {  -40,  72,   48,  28 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 113: not used by a script */
    { { {   -4,  16,   94,  16 },  {  -28,  64,   76,  22 },  {  -75, 111,   45,  30 },  {    0,   0,    0,   0 },  { -101,  60,   41,  26 } } },  /* 114: V JUMP K S A, F JUMP K S A */
    { { {   10,  16,   94,  16 },  {  -34,  77,   76,  21 },  {  -64,  94,   50,  30 },  {    0,   0,    0,   0 },  {  -87,  42,   46,  24 } } },  /* 115: V JUMP K M A, F JUMP K M A, atca 156 */
    { { {  -54,  16,   64,  16 },  {  -38,  32,   50,  44 },  {   -8,  56,   46,  40 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 116: V JUMP K L A, F JUMP K L A */
    { { {    0,   0,    0,   0 },  {  -34,  32,   34,  56 },  {   -2,  56,   52,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 117: V JUMP K L A, F JUMP K L A */
    { { {    0,   0,    0,   0 },  {  -24,  56,   34,  32 },  {  -40,  72,   66,  32 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 118: V JUMP K L A, F JUMP K L A */
    { { {    0,   0,    0,   0 },  {  -27,  65,   34,  40 },  {  -33,  44,   69,  52 },  {    0,   0,    0,   0 },  {  -80,  62,   45,  34 } } },  /* 119: V JUMP K L A, F JUMP K L A */
    { { {    0,   0,    0,   0 },  {  -51,  85,   34,  40 },  {  -22,  48,   72,  33 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 120: V JUMP K L A, F JUMP K L A */
    { { {   32,  16,   52,  16 },  {    8,  24,   44,  42 },  {  -45,  52,   30,  56 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 121: V JUMP K L A, F JUMP K L A */
    { { {   -6,  16,   74,  16 },  {  -28,  60,   62,  18 },  {  -32,  72,   38,  24 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 122: V JUMP K L A, F JUMP K L A */
    { { {   14,  16,   40,  16 },  {  -24,  48,   38,  14 },  {  -32,  72,   24,  14 },  {  -40,  88,    0,  24 },  {    0,   0,    0,   0 } } },  /* 123: KAGAMI K A, ATTACK 6 S */
    { { {   40,  16,   30,  16 },  {    8,  32,   28,  28 },  {  -28,  36,   28,  28 },  {  -40,  88,    0,  28 },  {    0,   0,    0,   0 } } },  /* 124: KAGAMI K A, ATTACK 6 S */
    { { {   44,  16,   18,  16 },  {   12,  32,    0,  36 },  {   -8,  20,    0,  40 },  {    0,   0,    0,   0 },  {  -90,  82,    0,  41 } } },  /* 125: KAGAMI K A, ATTACK 6 S */
    { { {   44,  16,   10,  16 },  {   12,  32,    0,  32 },  {   -8,  20,    0,  36 },  {  -92,  83,    0,  33 },  {    0,   0,    0,   0 } } },  /* 126: KAGAMI K A */
    { { {    0,   0,    0,   0 },  {    4,  32,   24,  26 },  {  -36,  38,   24,  30 },  {  -85, 138,    0,  24 },  {    0,   0,    0,   0 } } },  /* 127: KAGAMI K A */
    { { {    0,   0,    0,   0 },  {    8,  36,   24,  28 },  {  -32,  40,   24,  32 },  {  -69, 123,    0,  29 },  {    0,   0,    0,   0 } } },  /* 128: KAGAMI K A */
    { { {    0,   0,    0,   0 },  {    8,  36,   24,  24 },  {  -32,  40,   24,  28 },  {  -36,  88,    0,  24 },  {    0,   0,    0,   0 } } },  /* 129: KAGAMI K A */
    { { {   26,  16,   40,  16 },  {    8,  36,   24,  24 },  {  -24,  32,   24,  28 },  {  -32,  84,    0,  24 },  {    0,   0,    0,   0 } } },  /* 130: KAGAMI K A */
    { { {   52,  16,    0,  16 },  {   24,  28,    0,  30 },  {  -24,  48,    0,  36 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 131: OKIAGARI P S */
    { { {   52,  16,    0,  16 },  {   24,  28,    0,  30 },  {  -24,  48,    0,  36 },  {    0,   0,    0,   0 },  {  -24,  24,   36,  48 } } },  /* 132: OKIAGARI P S */
    { { {   48,  16,    8,  16 },  {   24,  24,    0,  36 },  {  -24,  48,   24,  32 },  {  -24,  48,    0,  24 },  {    0,   0,    0,   0 } } },  /* 133: OKIAGARI P S */
    { { {   36,  16,   16,  16 },  {    8,  28,   28,  22 },  {  -24,  32,   28,  22 },  {  -32,  56,    0,  24 },  {    0,   0,    0,   0 } } },  /* 134: OKIAGARI P S */
    { { {   44,  16,   34,  16 },  {   16,  28,   28,  32 },  {  -16,  32,   28,  32 },  {  -32,  56,    0,  28 },  {    0,   0,    0,   0 } } },  /* 135: OKIAGARI P S */
    { { {   30,  16,   40,  16 },  {   -2,  32,   28,  36 },  {  -30,  28,   28,  32 },  {  -32,  56,    0,  28 },  {    0,   0,    0,   0 } } },  /* 136: OKIAGARI P S */
    { { {  -12,  16,  104,  16 },  {  -26,  40,   92,  18 },  {  -20,  34,   54,  38 },  {    0,   0,    0,   0 },  {  -48,  22,   94,  40 } } },  /* 137: UP P GUARD P L */
    { { {  -12,  16,  104,  16 },  {  -22,  40,   92,  18 },  {  -16,  34,   54,  38 },  {    0,   0,    0,   0 },  {  -82,  58,   72,  40 } } },  /* 138: UP P GUARD P L */
    { { {  -22,  16,   42,  16 },  {  -16,  40,   34,  20 },  {   -8,  40,   12,  24 },  {  -30,  56,    0,  22 },  {    0,   0,    0,   0 } } },  /* 139: not used by a script */
    { { {  -20,  16,   86,  16 },  {  -24,  42,   66,  24 },  {  -26,  48,   40,  26 },  {  -30,  64,    0,  40 },  {    0,   0,    0,   0 } } },  /* 140: L PUNCH A, ATTACK 6 L, ATTACK 6 SP */
    { { {  -26,  16,   80,  16 },  {  -22,  40,   62,  18 },  {  -18,  44,   36,  26 },  {  -18,  52,    0,  36 },  {    0,   0,    0,   0 } } },  /* 141: UP P GUARD P L */
    { { {  -12,  16,   94,  16 },  {  -18,  40,   80,  16 },  {  -14,  44,   44,  36 },  {   -8,  52,    0,  44 },  {    0,   0,    0,   0 } } },  /* 142: UP P GUARD P L */
    { { {  -22,  16,   52,  16 },  {  -24,  32,   40,  18 },  {  -24,  44,   24,  16 },  {  -32,  56,    0,  24 },  {    0,   0,    0,   0 } } },  /* 143: DASH TOBINOKI */
    { { {    6,  16,   48,  16 },  {  -14,  32,   36,  18 },  {  -20,  44,   24,  16 },  {  -40,  56,    0,  24 },  {    0,   0,    0,   0 } } },  /* 144: DASH TOBINOKI */
    { { {   28,  16,   22,  16 },  {    4,  24,   24,  24 },  {  -40,  44,   24,  20 },  {  -44,  64,    0,  24 },  {    0,   0,    0,   0 } } },  /* 145: DASH TOBINOKI */
    { { {    0,   0,    0,   0 },  {  -22,  64,   24,  20 },  {  -52,  71,   27,  37 },  {  -22,  56,    0,  24 },  {    0,   0,    0,   0 } } },  /* 146: DASH TOBINOKI */
    { { {    0,   0,    0,   0 },  {  -22,  48,   24,  20 },  {  -33,  52,   44,  30 },  {  -22,  56,    0,  24 },  {    0,   0,    0,   0 } } },  /* 147: DASH TOBINOKI */
    { { {    0,   0,    0,   0 },  {  -26,  52,   24,  20 },  {  -16,  47,   44,  33 },  {  -30,  60,    0,  24 },  {    0,   0,    0,   0 } } },  /* 148: DASH TOBINOKI */
    { { {    0,   0,    0,   0 },  {  -30,  24,   24,  28 },  {   -6,  34,   24,  38 },  {  -40,  72,    0,  24 },  {    0,   0,    0,   0 } } },  /* 149: DASH TOBINOKI */
    { { {  -48,  16,   56,  16 },  {  -32,  40,   50,  16 },  {  -22,  42,   28,  26 },  {  -26,  58,    0,  28 },  {    0,   0,    0,   0 } } },  /* 150: DASH TOBINOKI */
    { { {  -18,  16,   80,  16 },  {  -22,  40,   60,  18 },  {  -18,  44,   36,  24 },  {  -24,  52,    0,  36 },  {    0,   0,    0,   0 } } },  /* 151: not used by a script */
    { { {   20,  16,   68,  16 },  {  -12,  40,   60,  18 },  {  -20,  44,   36,  24 },  {  -24,  52,    0,  36 },  {    0,   0,    0,   0 } } },  /* 152: not used by a script */
    { { {   28,  16,   54,  16 },  {  -12,  40,   60,  18 },  {  -20,  44,   36,  24 },  {  -28,  56,    0,  36 },  {    0,   0,    0,   0 } } },  /* 153: not used by a script */
    { { {   28,  16,   54,  16 },  {    2,  26,   36,  36 },  {  -24,  26,   36,  36 },  {  -36,  56,    0,  36 },  {    0,   0,    0,   0 } } },  /* 154: not used by a script */
    { { {   28,  16,   54,  16 },  {    2,  26,   36,  36 },  {  -36,  38,   36,  36 },  {  -36,  56,    0,  36 },  {  -72,  36,   36,  28 } } },  /* 155: not used by a script */
    { { {    2,  16,   72,  16 },  {   -8,  36,   56,  18 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 156: ATTACK 1 M (Att_SHOURYUUKEN) */
    { { {    6,  16,   72,  16 },  {  -22,  50,   56,  25 },  {  -22,  40,   30,  26 },  {    0,   0,    0,   0 },  {  -51,  27,   30,  51 } } },  /* 157: ATTACK 1 M (Att_SHOURYUUKEN) */
    { { {    0,  30,   86,  16 },  {  -66,  95,   41,  48 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -80,  63,   76,  19 } } },  /* 158: ATTACK 1 M (Att_SHOURYUUKEN) */
    { { {   28,  16,   82,  16 },  {  -14,  48,   68,  22 },  {  -28,  54,   32,  36 },  {    0,   0,    0,   0 },  {  -24,  48,   84,  16 } } },  /* 159: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN) */
    { { {   36,  16,   50,  16 },  {    8,  28,   54,  32 },  {  -20,  28,   42,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 160: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN) +1 */
    { { {    0,   0,    0,   0 },  {  -26,  50,   40,  24 },  {  -26,  50,   64,  24 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 161: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN) +1 */
    { { {  -46,  16,   46,  16 },  {  -40,  28,   54,  24 },  {  -12,  28,   40,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 162: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN) +1 */
    { { {  -64,  16,   50,  16 },  {  -48,  32,   40,  40 },  {  -16,  32,   40,  48 },  {  -28,  40,    0,  40 },  {    0,   0,    0,   0 } } },  /* 163: HANASARE */
    { { {    4,  16,   82,  16 },  {  -12,  40,   68,  18 },  {  -16,  38,   36,  32 },  {  -24,  52,    0,  36 },  {    0,   0,    0,   0 } } },  /* 164: S PUNCH C, ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU) +1 */
    { { {    6,  16,   82,  16 },  {   -4,  36,   66,  18 },  {  -16,  38,   36,  32 },  {  -24,  52,    0,  36 },  {    0,   0,    0,   0 } } },  /* 165: S PUNCH C, ATTACK 2 L (Att_SENPUUKYAKU) */
    { { {   12,  16,   78,  16 },  {    2,  32,   64,  18 },  {  -16,  38,   36,  32 },  {  -24,  52,    0,  36 },  {    0,   0,    0,   0 } } },  /* 166: S PUNCH C, ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    { { {   16,  16,   74,  16 },  {    2,  32,   60,  18 },  {  -16,  38,   36,  32 },  {  -24,  52,    0,  36 },  {    0,   0,    0,   0 } } },  /* 167: S PUNCH C, ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    { { {  -10,  16,   82,  16 },  {  -18,  40,   68,  18 },  {  -16,  38,   36,  32 },  {  -24,  52,    0,  36 },  {    0,   0,    0,   0 } } },  /* 168: S PUNCH C, ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU) +1 */
    { { {  -20,  16,   84,  16 },  {  -22,  36,   68,  18 },  {  -16,  38,   36,  32 },  {  -24,  52,    0,  36 },  {    0,   0,    0,   0 } } },  /* 169: S PUNCH C, ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU) +1 */
    { { {  -16,  16,   88,  16 },  {  -22,  36,   72,  18 },  {  -18,  38,   36,  36 },  {  -24,  52,    0,  36 },  {    0,   0,    0,   0 } } },  /* 170: S PUNCH C, ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU) +1 */
    { { {   -8,  16,   86,  16 },  {  -18,  34,   72,  18 },  {  -18,  38,   36,  36 },  {  -24,  52,    0,  36 },  {    0,   0,    0,   0 } } },  /* 171: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    { { {   -2,  16,   92,  16 },  {  -14,  40,   80,  18 },  {  -14,  36,   52,  28 },  {    0,   0,    0,   0 },  {  -28,  14,   80,  48 } } },  /* 172: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    { { {   -2,  16,   92,  16 },  {  -14,  40,   80,  18 },  {  -14,  36,   52,  28 },  {    0,   0,    0,   0 },  {  -67,  53,   73,  39 } } },  /* 173: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    { { {   -2,  16,   92,  16 },  {  -18,  40,   84,  18 },  {  -48,  64,   68,  16 },  {    0,   0,    0,   0 },  {  -84,  63,   74,  30 } } },  /* 174: ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU), ATTACK 2 S (Att_SENPUUKYAKU) */
    { { {   10,  16,   88,  16 },  {  -18,  40,   84,  18 },  {  -83, 103,   70,  21 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 175: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    { { {   18,  16,   84,  16 },  {   -2,  24,   66,  28 },  {  -85, 106,   62,  20 },  {    0,   0,    0,   0 },  {  -30,  26,   85,  57 } } },  /* 176: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    { { {   28,  16,   70,  16 },  {    2,  26,   64,  28 },  {  -51,  50,   50,  53 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 177: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    { { {   32,  16,   56,  16 },  {    4,  28,   40,  40 },  {  -35,  38,   41,  47 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 178: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    { { {   32,  16,   56,  16 },  {  -34,  67,   25,  58 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -96,  76,   58,  31 } } },  /* 179: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    { { {   24,  23,   46,  22 },  {  -10,  34,   18,  50 },  {  -71,  60,   31,  37 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 180: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU) */
    { { {  -11,  36,   72,  16 },  {  -23,  47,   56,  18 },  {  -34,  59,   11,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 181: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {    6,  16,   72,  16 },  {  -22,  50,   56,  18 },  {  -22,  40,   30,  26 },  {    0,   0,    0,   0 },  {  -34,  12,   30,  32 } } },  /* 182: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {   14,  16,   86,  16 },  {  -22,  50,   68,  22 },  {  -18,  40,   32,  36 },  {    0,   0,    0,   0 },  {  -66,  44,   64,  20 } } },  /* 183: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {   28,  16,   82,  16 },  {  -14,  48,   68,  22 },  {  -28,  54,   32,  36 },  {    0,   0,    0,   0 },  {  -42,  67,   85,  22 } } },  /* 184: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -24,  50,    0,  28 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 185: saca 49, SP APPEAR 1 */
    { { {   38,  16,   46,  16 },  {    8,  30,   40,  36 },  {  -22,  30,   40,  32 },  {   -8,  48,    0,  40 },  {  -38,  33,    0,  46 } } },  /* 186: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {   38,  16,   46,  16 },  {    8,  30,   40,  36 },  {  -22,  30,   40,  32 },  {   -8,  48,    0,  40 },  {  -38,  33,    0,  46 } } },  /* 187: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {   38,  16,   46,  16 },  {   24,  30,   40,  36 },  {  -14,  30,   40,  32 },  {   -8,  48,    0,  40 },  {  -50,  37,   49,  13 } } },  /* 188: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {   38,  16,   46,  16 },  {   24,  30,   40,  36 },  {  -14,  30,   40,  32 },  {   -8,  48,    0,  40 },  {  -53,  39,   59,  12 } } },  /* 189: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {    0,   0,    0,   0 },  {   20,  32,   40,  40 },  {  -12,  32,   40,  46 },  {    0,   0,    0,   0 },  {  -63,  52,   77,  13 } } },  /* 190: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {    0,   0,    0,   0 },  {   -8,  56,   56,  14 },  {   -6,  50,   70,  24 },  {    0,   0,    0,   0 },  {  -44,  39,   89,  21 } } },  /* 191: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {    0,   0,    0,   0 },  {   -8,  56,   56,  14 },  {   -6,  50,   70,  24 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 192: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {    0,   0,    0,   0 },  {   -8,  56,   56,  14 },  {   -6,  50,   70,  24 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 193: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {    0,   0,    0,   0 },  {   -8,  56,   56,  14 },  {   -6,  50,   70,  24 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 194: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {    0,   0,    0,   0 },  {   -8,  56,   56,  14 },  {   -6,  50,   70,  24 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 195: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {    0,   0,    0,   0 },  {  -28,  40,   48,  35 },  {   12,  20,   44,  35 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 196: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {    0,   0,    0,   0 },  {  -28,  40,   48,  35 },  {   12,  20,   44,  35 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 197: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {  -40,  16,   50,  16 },  {  -26,  28,   42,  36 },  {    2,  28,   42,  40 },  {  -10,  40,    0,  42 },  {    0,   0,    0,   0 } } },  /* 198: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {  -40,  16,   50,  16 },  {  -26,  28,   42,  36 },  {    2,  28,   42,  40 },  {  -10,  40,    0,  42 },  {    0,   0,    0,   0 } } },  /* 199: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {  -40,  16,   50,  16 },  {  -26,  28,   42,  36 },  {    2,  28,   42,  40 },  {  -10,  40,    0,  42 },  {    0,   0,    0,   0 } } },  /* 200: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {  -40,  16,   50,  16 },  {  -26,  28,   42,  36 },  {    2,  28,   42,  40 },  {  -10,  40,    0,  42 },  {    0,   0,    0,   0 } } },  /* 201: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {  -30,  16,   66,  16 },  {  -20,  40,   54,  18 },  {  -16,  48,   36,  24 },  {  -16,  56,    0,  36 },  {    0,   0,    0,   0 } } },  /* 202: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {  -30,  16,   66,  16 },  {  -20,  40,   54,  18 },  {  -16,  48,   36,  24 },  {  -16,  56,    0,  36 },  {    0,   0,    0,   0 } } },  /* 203: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {    6,  16,   80,  16 },  {  -14,  40,   62,  18 },  {  -18,  48,   36,  26 },  {  -28,  56,    0,  36 },  {    0,   0,    0,   0 } } },  /* 204: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {   32,  21,   36,  17 },  {   -8,  40,   32,  31 },  {  -39,  31,   32,  57 },  {  -41,  83,    0,  32 },  {    0,   0,    0,   0 } } },  /* 205: not used by a script */
    { { {   44,  16,   18,  16 },  {   12,  32,    0,  36 },  {   -8,  20,    0,  40 },  {  -32,  24,    0,  24 },  {    0,   0,    0,   0 } } },  /* 206: D P GUARD P M */
    { { {   -2,  16,   96,  16 },  {  -16,  44,   76,  20 },  {  -24,  44,   44,  32 },  {  -32,  44,    0,  44 },  {  -79,  53,   68,  18 } } },  /* 207: L PUNCH A, ATTACK 6 S */
    { { {   -2,  16,   96,  16 },  {  -16,  44,   76,  20 },  {  -24,  44,   44,  32 },  {  -32,  44,    0,  44 },  {  -47,  35,   91,  15 } } },  /* 208: L PUNCH A, ATTACK 6 L, ATTACK 6 SP */
    { { {  -43,  20,   42,  22 },  {  -22,  34,   40,  23 },  {  -44,  56,   18,  24 },  {  -48,  64,    0,  24 },  { -101,  64,   27,  25 } } },  /* 209: KAGAMI P A */
    { { {  -43,  20,   40,  22 },  {  -22,  41,   25,  36 },  {  -79,  56,    0,  39 },  {  -20,  40,    0,  24 },  {    0,   0,    0,   0 } } },  /* 210: KAGAMI P A */
    { { {   44,  16,   32,  16 },  {    8,  40,   24,  36 },  {  -40,  48,   24,  28 },  {  -40,  88,    0,  24 },  { -108,  68,   23,  32 } } },  /* 211: KAGAMI K A */
    { { {   32,  21,   36,  17 },  {   -8,  40,   32,  31 },  {  -39,  31,   32,  57 },  {  -41,  83,    0,  32 },  {  -73,  33,   68,  21 } } },  /* 212: M PUNCH A */
    { { {  -22,  16,   84,  16 },  {  -44,  67,   78,  20 },  {  -41,  65,   50,  28 },  {    0,   0,    0,   0 },  {  -76,  48,   40,  23 } } },  /* 213: L KICK A, ATTACK 6 S */
    { { {  -22,  16,   84,  16 },  {  -44,  67,   78,  20 },  {  -41,  65,   50,  28 },  {    0,   0,    0,   0 },  {  -51,  27,   39,  23 } } },  /* 214: L KICK A */
    { { {    4,  16,   40,  16 },  {  -14,  36,   28,  24 },  {  -56,  42,   28,  26 },  {  -66, 110,    0,  28 },  {  -85,  42,   41,  17 } } },  /* 215: M KICK A */
    { { {   -2,  16,   72,  16 },  {   -8,  36,   56,  18 },  {  -44,  68,   14,  41 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 216: ATTACK 1 S (Att_SHOURYUUKEN) */
    { { {    6,  16,   72,  16 },  {  -22,  50,   56,  18 },  {  -36,  49,    0,  56 },  {    0,   0,    0,   0 },  {  -41,  18,   29,  38 } } },  /* 217: ATTACK 1 S (Att_SHOURYUUKEN) */
    { { {   13,  16,   85,  11 },  {  -34,  63,   68,  17 },  {  -34,  58,   32,  36 },  {    0,   0,    0,   0 },  {  -74,  55,   49,  32 } } },  /* 218: ATTACK 1 S (Att_SHOURYUUKEN) */
    { { {  -11,  36,   72,  16 },  {  -23,  47,   56,  18 },  {  -36,  61,   11,  50 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 219: ATTACK 1 L (Att_SHOURYUUKEN) */
    { { {    6,  16,   72,  16 },  {  -22,  50,   56,  18 },  {  -22,  40,   30,  26 },  {    0,   0,    0,   0 },  {  -52,  31,   32,  40 } } },  /* 220: ATTACK 1 L (Att_SHOURYUUKEN) */
    { { {   14,  16,   86,  16 },  {  -22,  50,   68,  22 },  {  -18,  40,   32,  36 },  {    0,   0,    0,   0 },  {  -77,  53,   55,  36 } } },  /* 221: ATTACK 1 L (Att_SHOURYUUKEN) */
    { { {    0,   0,    0,   0 },  {  -27,  65,   34,  40 },  {  -32,  44,   68,  56 },  {    0,   0,    0,   0 },  {  -92,  68,   48,  36 } } },  /* 222: not used by a script */
    { { {   -2,  16,   88,  16 },  {  -25,  58,   72,  21 },  {  -43,  74,   53,  26 },  {  -21,  49,    0,  54 },  {  -67,  41,   74,  24 } } },  /* 223: ATTACK 5 S (Att_SHOURYUUREPPA) */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -44,  84,    0,  59 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 224: super art Att_PL08_HEALING (command slot 18) */
};

const ATTACK_BOX elena_att_box[65] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {    0,   0,    0,   0 },  {  -96,  71,   30,  14 },  {    0,   0,    0,   0 } } },  /* 1: KAGAMI P A; attack 13 */
    { { {    0,   0,    0,   0 },  {  -88,  34,    0,  14 },  {  -54,  52,   11,  14 } } },  /* 2: KAGAMI K A; attack 16 */
    { { {    0,   0,    0,   0 },  { -104,  89,   34,  16 },  {    0,   0,    0,   0 } } },  /* 3: KAGAMI P A; attack 14 */
    { { {    0,   0,    0,   0 },  {  -64,  23,   81,  22 },  {  -42,  31,   52,  31 } } },  /* 4: KAGAMI P A, ATTACK 6 S; attack 15, 46 */
    { { {    0,   0,    0,   0 },  {  -98,  88,   28,  18 },  {    0,   0,    0,   0 } } },  /* 5: KAGAMI K A; attack 17 */
    { { {    0,   0,    0,   0 },  {  -41,  24,   53,  15 },  {    0,   0,    0,   0 } } },  /* 6: V JUMP P S A, F JUMP P S A; attack 19 */
    { { {    0,   0,    0,   0 },  {  -75,  56,   74,  16 },  {  -97,  22,   78,  16 } } },  /* 7: V JUMP P M A, F JUMP P M A; attack 20 */
    { { {    0,   0,    0,   0 },  {  -88,  23,   45,  16 },  {  -80,  57,   54,  12 } } },  /* 8: V JUMP P L A, F JUMP P L A; attack 21 */
    { { {    0,   0,    0,   0 },  {  -56,  26,   55,  11 },  {  -87,  35,   50,  10 } } },  /* 9: V JUMP K S A, F JUMP K S A; attack 22 */
    { { {    0,   0,    0,   0 },  {  -59,  72,   55,  15 },  {  -91,  32,   51,  13 } } },  /* 10: V JUMP K M A, F JUMP K M A, atca 156; attack 23, 72 */
    { { {    0,   0,    0,   0 },  {  -83,  15,   42,  25 },  {  -72,  54,   53,  19 } } },  /* 11: V JUMP K L A, F JUMP K L A; attack 25 */
    { { {    0,   0,    0,   0 },  {  -88,  67,   12,  19 },  {  -94,  30,    0,  30 } } },  /* 12: KAGAMI K A, ATTACK 6 S; attack 18, 45 */
    { { {    0,   0,    0,   0 },  {  -32,  18,   64,  28 },  {  -20,  20,   40,  48 } } },  /* 13: OKIAGARI P S; attack 12 */
    { { {    0,   0,    0,   0 },  {  -62,  20,  112,  26 },  {    0,   0,    0,   0 } } },  /* 14: UP P GUARD P L; attack 61 */
    { { {    0,   0,    0,   0 },  {  -92,  28,   68,  40 },  {  -68,  48,   76,  44 } } },  /* 15: UP P GUARD P L; attack 62 */
    { { {  -31,   6,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 16: M PUNCH A, M PUNCH C; attack 10 */
    { { {    0,   0,    0,   0 },  {  -61,  20,   20,  56 },  {  -60,  30,   60,  16 } } },  /* 17: ATTACK 1 M (Att_SHOURYUUKEN); attack 28 */
    { { {    0,   0,    0,   0 },  {  -63,  46,   60,  24 },  {  -80,  24,   31,  51 } } },  /* 18: ATTACK 1 M (Att_SHOURYUUKEN); attack 29 */
    { { {    0,   0,    0,   0 },  {  -83,  64,   73,  17 },  {  -57,  38,   52,  20 } } },  /* 19: ATTACK 1 S (Att_SHOURYUUKEN); attack 27 */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -32,  18,   68,  56 } } },  /* 20: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU); attack 32 */
    { { {    0,   0,    0,   0 },  {  -74,  26,  101,  19 },  {  -53,  40,   72,  36 } } },  /* 21: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU); attack 33 */
    { { {    0,   0,    0,   0 },  {  -82,  28,   96,  14 },  {  -70,  52,   76,  24 } } },  /* 22: ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU); attack 34 */
    { { {    0,   0,    0,   0 },  {  -22,  16,   92,  56 },  {    0,   0,    0,   0 } } },  /* 23: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU); attack 35 */
    { { {    0,   0,    0,   0 },  { -108,  44,   62,  27 },  {  -64,  45,   56,  24 } } },  /* 24: ATTACK 2 S (Att_SENPUUKYAKU), ATTACK 2 M (Att_SENPUUKYAKU), ATTACK 2 L (Att_SENPUUKYAKU); attack 36, 37, 38 */
    { { {    0,   0,    0,   0 },  {   39,  56,   40,  22 },  {    0,   0,    0,   0 } } },  /* 25: HANASARE; attack 65 */
    { { {    0,   0,    0,   0 },  {  -88,  74,   52,  16 },  {    0,   0,    0,   0 } } },  /* 26: M PUNCH C, ATTACK 6 S; attack 1, 44 */
    { { {    0,   0,    0,   0 },  {  -71,  35,   87,  11 },  {  -48,  40,   54,  32 } } },  /* 27: M PUNCH A, ATTACK 6 S; attack 2, 42 */
    { { {    0,   0,    0,   0 },  {  -60,  47,   64,  24 },  { -100,  48,   78,  16 } } },  /* 28: L PUNCH A; attack 3 */
    { { {    0,   0,    0,   0 },  {  -75,  63,   49,  27 },  {    0,   0,    0,   0 } } },  /* 29: L KICK A, ATTACK 6 S; attack 4, 47 */
    { { {    0,   0,    0,   0 },  {  -71,  30,   79,  13 },  {  -46,  37,   64,  18 } } },  /* 30: S PUNCH A, UP P GUARD P S; attack 5, 59 */
    { { {    0,   0,    0,   0 },  {  -71,  32,   73,  19 },  {  -49,  42,   50,  33 } } },  /* 31: ATTACK 5 S (Att_SHOURYUUREPPA); attack 40 */
    { { {    0,   0,    0,   0 },  {  -56,  43,   12,  24 },  {  -59,  16,    0,  32 } } },  /* 32: S KICK A, D P GUARD P S, FUSHIN P S +1; attack 7, 40, 63 */
    { { {    0,   0,    0,   0 },  {  -56,  35,    0,  19 },  {  -76,  19,    0,  13 } } },  /* 33: D P GUARD P M, L KICK C, KAGAMI K C; attack 8, 64 */
    { { {    0,   0,    0,   0 },  {   -8,  18,   84,  48 },  {    0,   0,    0,   0 } } },  /* 34: not used by a script */
    { { {    0,   0,    0,   0 },  {   42,  60,   90,  18 },  {   22,  48,   80,  12 } } },  /* 35: HANASARE; attack 53, 54, 55 */
    { { {    0,   0,    0,   0 },  {   84,  18,   62,  22 },  {   44,  40,   54,  12 } } },  /* 36: HANASARE; attack 56, 57, 58 */
    { { {    0,   0,    0,   0 },  { -100,  38,   56,  12 },  {  -62,  44,   46,  14 } } },  /* 37: M KICK A, UP P GUARD P M, ATTACK 6 S; attack 9, 41, 60 */
    { { {    0,   0,    0,   0 },  {  -64,  24,   12,  64 },  {  -52,  32,   56,  26 } } },  /* 38: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {    0,   0,    0,   0 },  {  -90,  26,   48,  48 },  {  -76,  64,   70,  32 } } },  /* 39: ATTACK 4 S (Att_SHOURYUUREPPA); attack 52 */
    { { {    0,   0,    0,   0 },  {  -72,  88,   82,  45 },  {    8,  56,  102,  32 } } },  /* 40: ATTACK 4 S (Att_SHOURYUUREPPA); attack 52 */
    { { {    0,   0,    0,   0 },  {  -60,  44,   72,  16 },  {  -84,  28,   88,  23 } } },  /* 41: L PUNCH A, ATTACK 6 S */
    { { {    0,   0,    0,   0 },  {  -46,  18,   74,  40 },  {    0,   0,    0,   0 } } },  /* 42: V JUMP K L A, F JUMP K L A; attack 24 */
    { { {    0,   0,    0,   0 },  {  -76,  24,    0,  36 },  {  -56,  48,   32,  28 } } },  /* 43: ATTACK 4 S (Att_SHOURYUUREPPA); attack 70 */
    { { {    0,   0,    0,   0 },  {  -80,  20,   24,  32 },  {  -64,  59,   48,  28 } } },  /* 44: ATTACK 4 S (Att_SHOURYUUREPPA); attack 70 */
    { { {    0,   0,    0,   0 },  {  -80,  20,   64,  24 },  {  -60,  57,   62,  20 } } },  /* 45: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {    0,   0,    0,   0 },  {  -86,  54,   70,  36 },  {  -54,  49,   65,  30 } } },  /* 46: ATTACK 4 S (Att_SHOURYUUREPPA); attack 50 */
    { { {    0,   0,    0,   0 },  {  -76,  52,   97,  28 },  {  -54,  49,   82,  29 } } },  /* 47: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { { {  -68,  68,    0,  32 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 48: not used by a script */
    { { {    0,   0,    0,   0 },  {  -44,  27,   65,  12 },  {  -26,  20,   40,  29 } } },  /* 49: M PUNCH A; attack 68 */
    { { {    0,   0,    0,   0 },  {  -66,  32,   32,  26 },  {  -53,  41,   58,  12 } } },  /* 50: L KICK A, ATTACK 6 S; attack 4 */
    { { {    0,   0,    0,   0 },  {  -47,  29,   21,  31 },  {    0,   0,    0,   0 } } },  /* 51: L KICK A; attack 4 */
    { { {    0,   0,    0,   0 },  {  -59,  24,   20,  49 },  {  -52,  32,   61,  14 } } },  /* 52: ATTACK 1 L (Att_SHOURYUUKEN); attack 30 */
    { { {    0,   0,    0,   0 },  {  -76,  54,   73,  24 },  {  -85,  24,   48,  43 } } },  /* 53: ATTACK 1 L (Att_SHOURYUUKEN); attack 31 */
    { { {    0,   0,    0,   0 },  {  -52,  38,   12,  42 },  {    0,   0,    0,   0 } } },  /* 54: ATTACK 4 S (Att_SHOURYUUREPPA), ATTACK 1 L (Att_SHOURYUUKEN); attack 51, 69 */
    { { {    0,   0,    0,   0 },  {  -64,  24,   20,  56 },  {  -52,  32,   64,  18 } } },  /* 55: not used by a script */
    { { {    0,   0,    0,   0 },  {  -76,  54,   78,  24 },  {  -90,  24,   48,  48 } } },  /* 56: not used by a script */
    { { {    0,   0,    0,   0 },  {  -72,  72,   92,  20 },  {    8,  56,  102,  32 } } },  /* 57: not used by a script */
    { { {  -35,  10,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 58: L PUNCH A; attack 10 */
    { { {    0,   0,    0,  16 },  {  -48,  48,   42,  20 },  {  -24,  48,   24,  20 } } },  /* 59: not used by a script */
    { { {    0,   0,    0,  16 },  {  -48,  48,   42,  20 },  {  -24,  48,   24,  20 } } },  /* 60: not used by a script */
    { { {    0,   0,    0,  16 },  {  -84,  36,   24,  36 },  {  -72,  48,    8,  22 } } },  /* 61: not used by a script */
    { { {    0,   0,    0,   0 },  {  -54,  26,   40,  28 },  {    0,   0,    0,   0 } } },  /* 62: ATTACK 5 S (Att_SHOURYUUREPPA); attack 39 */
    { { {    0,   0,    0,   0 },  {  -44,  21,   33,  31 },  {    0,   0,    0,   0 } } },  /* 63: saca 50; attack 71 */
    { { {    0,   0,    0,   0 },  {  -65,  56,   57,  31 },  { -100,  48,   70,  24 } } },  /* 64: ATTACK 6 S; attack 67 */
};

const CAUGHT_BOX elena_cau_box[8] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -25,   50,    0,   16 } },  /* 1: KAMAE, STAND UP, WALK END +83 */
    { {  -29,   54,    0,    8 } },  /* 2: KAGAMU, KAGAMI KAMAE, PARING DOWN +26 */
    { {  -25,   50,   56,   56 } },  /* 3: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +33 */
    { {  -25,   50,    0,    8 } },  /* 4: not used by a script */
    { {  -25,   50,   24,   56 } },  /* 5: AIR S, AIR M, AIR L +29 */
    { {  -31,   62,    0,   16 } },  /* 6: DASH HUMIKOMI */
    { {  -33,   58,    0,    8 } },  /* 7: KAGAMI P A, KAGAMI K A */
};

const HOSEI_BOX elena_hos_box[8] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -25,   50,    0,   79 } },  /* 1: KAMAE, STAND UP, WALK END +83 */
    { {  -25,   50,    0,   49 } },  /* 2: KAGAMU, KAGAMI KAMAE, PARING DOWN +30 */
    { {  -25,   50,   56,   56 } },  /* 3: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +33 */
    { {  -25,   50,    0,   36 } },  /* 4: TATAKI S, TATAKI V. S, KGM TATAKI S +18 */
    { {  -31,   62,    0,   79 } },  /* 5: DASH HUMIKOMI */
    { {  -25,   50,   24,   56 } },  /* 6: AIR S, AIR M, AIR L +31 */
    { {  -25,   50,    0,   30 } },  /* 7: NEKOROBI S */
};
