/*
 * KEN_HITBOX.C  Ken's hit boxes
 *
 * Each of Ken's animation frames names a row of ken_hit_ix_table (a frame line's hit field). The
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
 * rows of ken_catt_table dealt through it. Row 0 of a box table is no box.
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

const HIT_IX ken_hit_ix_table[218] = {
    /* boix  atix  cuix  hoix */
    {    0,    0,    0,    0 },  /* 0: NAGERARE KAIHI, OKIAGARI, OKIAGARI F +19 */
    {    1,    0,    1,    1 },  /* 1: KAMAE, HURIMUKI, FRONT WALK +91 */
    {    2,    0,    2,    2 },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +20 */
    {  123,    0,    0,    2 },  /* 3: OKIAGARI P S, ATTACK 2 S (Att_SHOURYUUKEN) */
    {  123,    1,    0,    1 },  /* 4: not used by a script */
    {  131,    1,    0,    4 },  /* 5: ATTACK 5 S (Att_SHOURYUUREPPA) */
    {    3,    2,    0,    4 },  /* 6: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +2 */
    {    3,    0,    3,    4 },  /* 7: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +2 */
    {    4,    0,    3,    4 },  /* 8: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +2 */
    {    5,    0,   18,   21 },  /* 9: DASH HUMIKOMI, DASH TOBINOKI */
    {    6,    0,    1,    1 },  /* 10: DASH TOBINOKI */
    {    7,    0,    3,    3 },  /* 11: GUARD AIR, V JUMP P M A, V JUMP K S A +7 */
    {    8,    0,    3,    3 },  /* 12: not used by a script */
    {    9,    0,    3,    3 },  /* 13: not used by a script */
    {   10,    0,    4,    4 },  /* 14: JUMP FRONT, JUMP BACK, SP JUMP FRONT +1 */
    {   11,    0,    4,    4 },  /* 15: JUMP JUNBI, SP JUMP JUNBI, JUMP VERTICAL +7 */
    {   12,    0,    4,    4 },  /* 16: JUMP VERTICAL, S JUMP FRONT, SP JUMP V +2 */
    {   13,    0,    3,    3 },  /* 17: not used by a script */
    {   14,    0,    3,    3 },  /* 18: not used by a script */
    {   15,    0,    3,    3 },  /* 19: not used by a script */
    {  109,    4,    1,    1 },  /* 20: S PUNCH A */
    {   16,    0,    1,    1 },  /* 21: S PUNCH A */
    {   17,    5,    1,    1 },  /* 22: S PUNCH B */
    {   17,    0,    1,    1 },  /* 23: S PUNCH B */
    {  110,    6,    1,    1 },  /* 24: M PUNCH A, UP P GUARD P M */
    {   18,    0,    1,    1 },  /* 25: L PUNCH A, V JUMP P S A, atca 157 +1 */
    {   19,    7,    1,    1 },  /* 26: M PUNCH B, UP P GUARD P S */
    {   19,    0,    1,    1 },  /* 27: M PUNCH B, UP P GUARD P S */
    {   20,    0,    1,    1 },  /* 28: M PUNCH B, UP P GUARD P S */
    {   21,    0,    1,    1 },  /* 29: atca 157 */
    {   22,    8,    1,    1 },  /* 30: L PUNCH A, atca 157 */
    {   23,    9,    1,    1 },  /* 31: L PUNCH A, atca 157 */
    {   24,    0,    1,    1 },  /* 32: L PUNCH A, atca 157 */
    {   25,    0,    1,    1 },  /* 33: L PUNCH B, UP P GUARD P L */
    {   26,   10,    1,    1 },  /* 34: UP P GUARD P L */
    {   27,   10,    1,    1 },  /* 35: L PUNCH B, UP P GUARD P L */
    {   27,    0,    1,    1 },  /* 36: not used by a script */
    {   28,    0,    1,    1 },  /* 37: L PUNCH B, UP P GUARD P L */
    {   29,    0,    1,    1 },  /* 38: L PUNCH B, UP P GUARD P L */
    {   30,    0,    8,    1 },  /* 39: S KICK A */
    {   31,   11,    8,    1 },  /* 40: S KICK A */
    {   31,    0,    8,    1 },  /* 41: S KICK A */
    {   32,    0,    5,    5 },  /* 42: not used by a script */
    {   33,    0,    5,    5 },  /* 43: not used by a script */
    {   34,   12,    5,    5 },  /* 44: not used by a script */
    {   34,    0,    5,    5 },  /* 45: not used by a script */
    {   35,    0,    6,    1 },  /* 46: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   36,    0,    6,    1 },  /* 47: not used by a script */
    {   37,   13,    7,    1 },  /* 48: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   37,    0,    7,    1 },  /* 49: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   38,    0,    7,    1 },  /* 50: not used by a script */
    {   39,    0,    1,    1 },  /* 51: UP P GUARD K M, ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   40,   57,    1,    1 },  /* 52: UP P GUARD K M */
    {   40,   58,    1,    1 },  /* 53: M KICK A, M KICK C, UP P GUARD K M */
    {   41,    0,    1,    1 },  /* 54: M KICK A, UP P GUARD K M, ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   42,    0,    1,    1 },  /* 55: not used by a script */
    {   43,    0,    1,    1 },  /* 56: M KICK C */
    {   44,    0,    1,    1 },  /* 57: M KICK C, atca 156 */
    {   45,    0,    1,    1 },  /* 58: not used by a script */
    {   45,   14,    1,    1 },  /* 59: M KICK C, atca 156 */
    {   46,   15,    1,    1 },  /* 60: M KICK C, atca 156 */
    {   47,   16,    1,    1 },  /* 61: M KICK C, atca 156 */
    {   49,   17,    1,    1 },  /* 62: M KICK C, atca 156 */
    {   49,   18,    1,    1 },  /* 63: not used by a script */
    {   50,    0,    1,    1 },  /* 64: not used by a script */
    {   52,    0,    1,    1 },  /* 65: L KICK A, UP P GUARD K L */
    {   53,   68,    1,    1 },  /* 66: UP P GUARD K L */
    {   54,   19,    1,    1 },  /* 67: L KICK A, UP P GUARD K L */
    {   54,   19,    1,    1 },  /* 68: UP P GUARD K L */
    {   55,    0,    1,    1 },  /* 69: L KICK A, UP P GUARD K L, ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   56,    0,    1,    1 },  /* 70: not used by a script */
    {   57,    0,    1,    1 },  /* 71: L KICK A, UP P GUARD K L, FUSHIN P S +1 */
    {   58,    0,    1,    1 },  /* 72: not used by a script */
    {   59,    0,    1,   19 },  /* 73: not used by a script */
    {   60,    0,    1,   10 },  /* 74: TOUKETSU A */
    {   61,   20,    1,   11 },  /* 75: not used by a script */
    {   61,    0,    1,   11 },  /* 76: not used by a script */
    {   62,    0,    1,   11 },  /* 77: not used by a script */
    {   63,    0,    1,   11 },  /* 78: not used by a script */
    {   64,   21,    9,    2 },  /* 79: KAGAMI P A */
    {   64,    0,    9,    2 },  /* 80: KAGAMI P A */
    {   65,   22,    2,    2 },  /* 81: KAGAMI P A */
    {   65,    0,    2,    2 },  /* 82: KAGAMI P A */
    {   66,    0,    2,    2 },  /* 83: KAGAMI P A */
    {   67,   23,    2,    2 },  /* 84: KAGAMI P A */
    {   68,   24,    2,    2 },  /* 85: KAGAMI P A */
    {   69,    0,    2,    2 },  /* 86: KAGAMI P A */
    {   68,    0,    2,    2 },  /* 87: atca 156 */
    {   70,    0,    2,    2 },  /* 88: KAGAMI P A */
    {   71,    0,    9,    2 },  /* 89: KAGAMI K A */
    {   72,   25,    9,    2 },  /* 90: KAGAMI K A */
    {   72,    0,    9,    2 },  /* 91: not used by a script */
    {   73,    0,    2,    2 },  /* 92: KAGAMI K A, UP P GUARD K S */
    {   74,   26,    2,    2 },  /* 93: KAGAMI K A, UP P GUARD K S */
    {   74,    0,    2,    2 },  /* 94: UP P GUARD K S */
    {   75,    0,    2,    2 },  /* 95: KAGAMI K A, UP P GUARD K S */
    {   76,    0,    2,    2 },  /* 96: KAGAMI K A */
    {   77,   27,    2,    2 },  /* 97: KAGAMI K A */
    {   77,    0,    2,    2 },  /* 98: KAGAMI K A */
    {   78,    0,    4,    4 },  /* 99: V JUMP P S A, F JUMP P S A */
    {   78,   28,    4,   16 },  /* 100: V JUMP P S A, F JUMP P S A */
    {    7,    0,    4,    4 },  /* 101: V JUMP K M A */
    {   80,   29,    4,    4 },  /* 102: not used by a script */
    {   11,    0,    4,    4 },  /* 103: not used by a script */
    {   81,   30,    4,    4 },  /* 104: V JUMP K M A */
    {   81,    0,    4,    4 },  /* 105: V JUMP K M A */
    {   77,   66,    2,    2 },  /* 106: not used by a script */
    {   96,   32,    3,    3 },  /* 107: V JUMP P M A, F JUMP P M A, F JUMP P L A */
    {   82,   33,    3,    3 },  /* 108: V JUMP K S A, F JUMP K S A */
    {   82,    0,    3,    3 },  /* 109: V JUMP K S A, F JUMP K S A */
    {   83,   34,    3,    3 },  /* 110: F JUMP K M A */
    {   83,    0,    3,    3 },  /* 111: F JUMP K M A, F JUMP K L A */
    {  123,   35,    0,    2 },  /* 112: not used by a script */
    {    7,   36,    4,    3 },  /* 113: not used by a script */
    {   84,   37,    4,    4 },  /* 114: V JUMP K L A */
    {   84,    0,    4,    4 },  /* 115: V JUMP K L A */
    {   85,    0,   15,   19 },  /* 116: ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN), ATTACK 1 L (Att_HADOUKEN) */
    {   86,    0,   15,   19 },  /* 117: ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN), ATTACK 1 L (Att_HADOUKEN) */
    {   87,    0,    1,   20 },  /* 118: exca 17, HANASARE, ATTACK 3 S (Att_SENPUUKYAKU) +2 */
    {   88,    0,    1,    1 },  /* 119: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    {   89,   45,    1,    1 },  /* 120: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    {   90,    0,   12,   18 },  /* 121: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +4 */
    {   97,   38,   12,   18 },  /* 122: ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU), saca 48 +2 */
    {    1,    0,    1,    1 },  /* 123: GUARD HEAD */
    {    1,    0,    1,    1 },  /* 124: GUARD UP */
    {    2,    0,    2,    2 },  /* 125: GUARD DOWN */
    {    0,    0,    0,    2 },  /* 126: OKIAGARI, OKIAGARI F, OKIAGARI B +16 */
    {    0,    0,    0,    2 },  /* 127: not used by a script */
    {    1,   41,    1,    1 },  /* 128: M PUNCH A, M PUNCH B, M KICK A +4 */
    {  107,   42,    1,    1 },  /* 129: not used by a script */
    {  112,   43,    1,    1 },  /* 130: not used by a script */
    {    7,   44,    4,    3 },  /* 131: not used by a script */
    {   97,    0,   12,   18 },  /* 132: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +3 */
    {   98,   39,   12,   18 },  /* 133: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +3 */
    {   98,    0,   12,   18 },  /* 134: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +3 */
    {   99,    0,    1,    1 },  /* 135: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    {  100,    0,    1,   10 },  /* 136: not used by a script */
    {  101,    0,    1,   10 },  /* 137: not used by a script */
    {  102,    0,    1,   10 },  /* 138: not used by a script */
    {  103,   46,    1,   11 },  /* 139: not used by a script */
    {  103,   47,    1,   11 },  /* 140: not used by a script */
    {  103,    0,    1,   11 },  /* 141: not used by a script */
    {  104,    0,    1,   11 },  /* 142: not used by a script */
    {  105,    0,    1,    1 },  /* 143: not used by a script */
    {    1,    0,    1,   10 },  /* 144: not used by a script */
    {  111,   48,    3,    3 },  /* 145: F JUMP K L A */
    {  108,    0,    1,    1 },  /* 146: M PUNCH A, UP P GUARD P M */
    {  106,    0,    1,    1 },  /* 147: not used by a script */
    {   54,   49,    1,    9 },  /* 148: not used by a script */
    {  113,    0,    1,    1 },  /* 149: FUSHIN P S */
    {  114,   50,    1,    1 },  /* 150: FUSHIN P S */
    {    0,   51,    0,    1 },  /* 151: ATTACK 5 S (Att_SHOURYUUREPPA) */
    {    0,   52,    0,    0 },  /* 152: ATTACK 5 S (Att_SHOURYUUREPPA) */
    {    0,   52,    0,    0 },  /* 153: ATTACK 5 S (Att_SHOURYUUREPPA) */
    {    0,   52,    0,    0 },  /* 154: ATTACK 5 S (Att_SHOURYUUREPPA) */
    {    0,   52,    0,    0 },  /* 155: ATTACK 5 S (Att_SHOURYUUREPPA) */
    {    0,   52,    0,    0 },  /* 156: ATTACK 5 S (Att_SHOURYUUREPPA) */
    {  117,    0,    1,    0 },  /* 157: Att_CHOUCHUURENGEKI (command slot 25), saca 56 */
    {   90,    0,   12,    4 },  /* 158: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   97,   38,   12,    0 },  /* 159: not used by a script */
    {   97,    0,   12,    4 },  /* 160: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   98,   39,   12,    0 },  /* 161: not used by a script */
    {  115,    0,   13,   22 },  /* 162: AIR S, AIR M, AIR L +39 */
    {  116,   59,    3,    3 },  /* 163: not used by a script */
    {    0,    0,    0,    1 },  /* 164: ATTACK 4 S (Att_SHOURYUUREPPA), ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {    0,   60,    0,    1 },  /* 165: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   54,   60,    1,    1 },  /* 166: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   40,   61,    0,    1 },  /* 167: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   97,   62,    0,    4 },  /* 168: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   98,   63,    0,    4 },  /* 169: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   31,   60,    0,    1 },  /* 170: not used by a script */
    {   37,   60,    0,    1 },  /* 171: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {    0,   67,    0,    2 },  /* 172: ATTACK 5 S (Att_SHOURYUUREPPA) */
    {   52,   68,    1,    1 },  /* 173: not used by a script */
    {  118,    1,    0,   25 },  /* 174: not used by a script */
    {    0,   69,    0,   25 },  /* 175: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {    0,   70,    0,   25 },  /* 176: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {    0,    2,    0,   25 },  /* 177: not used by a script */
    {    3,    0,    0,   25 },  /* 178: not used by a script */
    {    7,    0,    4,    4 },  /* 179: not used by a script */
    {  119,    0,    4,    4 },  /* 180: V JUMP P L A */
    {  120,   29,    4,    4 },  /* 181: V JUMP P L A */
    {  121,   72,    4,    4 },  /* 182: V JUMP K M A */
    {    0,    0,    0,    4 },  /* 183: AIR S, AIR M, AIR L +2 */
    {    1,    1,    0,   25 },  /* 184: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {    1,    2,    0,   25 },  /* 185: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {    0,    0,    0,   25 },  /* 186: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {    0,    0,    0,    3 },  /* 187: not used by a script */
    {    0,   73,    0,    1 },  /* 188: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    {   74,    0,    2,    2 },  /* 189: not used by a script */
    {   72,    0,    9,    2 },  /* 190: KAGAMI K A */
    {    1,   74,    1,    1 },  /* 191: L PUNCH A, L PUNCH B, L KICK A */
    {    0,    0,    0,    2 },  /* 192: ATTACK 5 S (Att_SHOURYUUREPPA) */
    {  124,   75,    3,    3 },  /* 193: not used by a script */
    {  125,    0,    1,    1 },  /* 194: PIYO */
    {  126,    0,    1,    1 },  /* 195: PIYO */
    {   22,   76,    1,    1 },  /* 196: L PUNCH A */
    {  127,   77,    3,    3 },  /* 197: saca 57 */
    {    0,    0,    0,   27 },  /* 198: NEKOROBI S */
    {  128,    0,   16,    2 },  /* 199: OKIAGARI P S */
    {  128,   78,   16,    1 },  /* 200: OKIAGARI P S */
    {  129,   79,   17,    4 },  /* 201: OKIAGARI P S */
    {  130,    0,   17,    4 },  /* 202: OKIAGARI P S */
    {    0,    0,    1,    2 },  /* 203: not used by a script */
    {    2,   69,    0,   25 },  /* 204: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {    1,   70,    0,   25 },  /* 205: ATTACK 4 S (Att_SHOURYUUREPPA) */
    {  123,    0,    0,    2 },  /* 206: ATTACK 2 L (Att_SHOURYUUKEN) */
    {  123,   35,    0,    2 },  /* 207: ATTACK 2 L (Att_SHOURYUUKEN) */
    {  123,    1,    1,    2 },  /* 208: ATTACK 2 L (Att_SHOURYUUKEN) */
    {    1,    0,    0,    1 },  /* 209: HANASARE */
    {    2,    0,    0,    2 },  /* 210: HANASARE */
    {  131,    0,    0,    2 },  /* 211: ATTACK 2 M (Att_SHOURYUUKEN) */
    {  131,    1,    0,    2 },  /* 212: ATTACK 2 M (Att_SHOURYUUKEN) */
    {  131,    2,    1,    1 },  /* 213: ATTACK 2 M (Att_SHOURYUUKEN) */
    {   97,   81,   12,   18 },  /* 214: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    {    1,    0,    1,    0 },  /* 215: LOSE SONABA */
    {  132,    0,   19,   28 },  /* 216: PARING AIR F, PARING AIR B */
    {  134,    1,    0,    2 },  /* 217: ATTACK 2 S (Att_SHOURYUUKEN) */
};

const BODY_BOX ken_body_box[135] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {  -14,  21,   84,  18 },  {  -29,  59,   81,   7 },  {  -29,  59,   32,  49 },  {  -35,  72,    0,  31 },  {    0,   0,    0,   0 } } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +95 */
    { { {  -15,  21,   50,  18 },  {  -30,  58,   43,  13 },  {  -29,  58,   26,  20 },  {  -42,  82,    0,  31 },  {    0,   0,    0,   0 } } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +21 */
    { { {   -1,  18,   96,  16 },  {  -20,  44,   81,  14 },  {  -16,  32,   63,  18 },  {  -22,  42,   37,  27 },  {  -21,  17,   97,  26 } } },  /* 3: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +2 */
    { { {   -4,  18,  102,  16 },  {  -24,  44,   90,  14 },  {  -24,  46,   61,  31 },  {  -18,  42,   -3,  73 },  {    0,   0,    0,   0 } } },  /* 4: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +2 */
    { { {  -16,  23,   78,  16 },  {  -25,  53,   62,  20 },  {  -24,  40,   37,  29 },  {  -38,  66,    0,  35 },  {    0,   0,    0,   0 } } },  /* 5: DASH HUMIKOMI, DASH TOBINOKI */
    { { {   -5,  23,   78,  16 },  {  -25,  53,   67,  20 },  {  -18,  43,   36,  29 },  {  -33,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 6: DASH TOBINOKI */
    { { {  -19,  39,   92,  16 },  {  -32,  64,   78,  15 },  {  -30,  59,   42,  37 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 7: GUARD AIR, V JUMP P M A, V JUMP K S A +8 */
    { { {  -28,  54,   39,  40 },  {  -23,  53,   75,  20 },  {  -28,  54,   39,  40 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 8: not used by a script */
    { { {  -42,  31,   52,  21 },  {  -33,  60,   75,  20 },  {  -25,  52,   36,  37 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 9: not used by a script */
    { { {    0,   0,    0,   0 },  {  -34,  69,   42,  53 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 10: JUMP FRONT, JUMP BACK, SP JUMP FRONT +1 */
    { { {  -11,  23,  106,  16 },  {  -23,  53,   90,  20 },  {  -19,  43,   45,  49 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 11: JUMP JUNBI, SP JUMP JUNBI, JUMP VERTICAL +7 */
    { { {  -18,  23,   99,  16 },  {  -23,  53,   90,  20 },  {  -31,  63,   44,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 12: JUMP VERTICAL, S JUMP FRONT, SP JUMP V +2 */
    { { {  -13,  27,   93,  17 },  {  -22,  57,   76,  20 },  {  -29,  57,   40,  38 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 13: not used by a script */
    { { {  -11,  49,   81,  19 },  {  -39,  79,   42,  52 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 14: not used by a script */
    { { {  -22,  57,   76,  20 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 15: not used by a script */
    { { {  -23,  23,   78,  16 },  {  -31,  53,   63,  20 },  {  -18,  43,   36,  29 },  {  -25,  55,    0,  35 },  {  -42,  12,   70,  20 } } },  /* 16: S PUNCH A */
    { { {  -14,  21,   84,  18 },  {  -28,  58,   69,  22 },  {  -21,  49,   38,  31 },  {  -28,  63,    0,  38 },  {  -73,  51,   66,  30 } } },  /* 17: S PUNCH B */
    { { {  -30,  23,   82,  16 },  {  -36,  53,   66,  20 },  {  -32,  43,   36,  29 },  {  -32,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 18: L PUNCH A, V JUMP P S A, atca 157 +1 */
    { { {  -27,  23,   79,  16 },  {  -45,  69,   63,  21 },  {  -32,  52,   36,  29 },  {  -42,  74,    0,  41 },  {  -70,  59,   64,  18 } } },  /* 19: M PUNCH B, UP P GUARD P S */
    { { {  -20,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -32,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 20: M PUNCH B, UP P GUARD P S */
    { { {  -20,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -32,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 21: atca 157 */
    { { {  -29,  34,   83,  16 },  {  -32,  54,   67,  20 },  {  -26,  43,   36,  29 },  {  -33,  62,    0,  35 },  {  -50,  32,   46,  29 } } },  /* 22: L PUNCH A, atca 157 */
    { { {  -29,  34,   83,  16 },  {  -32,  54,   67,  20 },  {  -26,  43,   36,  29 },  {  -33,  62,    0,  35 },  {  -50,  32,   46,  29 } } },  /* 23: L PUNCH A, atca 157 */
    { { {  -29,  34,   83,  16 },  {  -32,  54,   67,  20 },  {  -26,  43,   36,  29 },  {  -33,  62,    0,  35 },  {  -49,  46,   57,  54 } } },  /* 24: L PUNCH A, atca 157 */
    { { {  -21,  38,   83,  16 },  {  -29,  55,   67,  20 },  {  -21,  44,   47,  22 },  {  -35,  61,    0,  47 },  {    0,   0,    0,   0 } } },  /* 25: L PUNCH B, UP P GUARD P L */
    { { {  -20,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -35,  61,    0,  35 },  {  -57,  33,   74,  14 } } },  /* 26: UP P GUARD P L */
    { { {   -6,  26,   82,  16 },  {  -25,  49,   67,  20 },  {  -20,  43,   36,  29 },  {  -36,  80,    0,  35 },  {  -68,  45,   60,  40 } } },  /* 27: L PUNCH B, UP P GUARD P L */
    { { {    0,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -35,  61,    0,  35 },  {    0,   0,    0,   0 } } },  /* 28: L PUNCH B, UP P GUARD P L */
    { { {  -14,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -35,  61,    0,  35 },  {    0,   0,    0,   0 } } },  /* 29: L PUNCH B, UP P GUARD P L */
    { { {  -14,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -25,  28,    0,  35 },  {    0,   0,    0,   0 } } },  /* 30: S KICK A */
    { { {  -24,  31,   84,  16 },  {  -32,  51,   67,  20 },  {  -35,  56,   36,  29 },  {  -44,  56,    0,  35 },  {  -71,  47,   11,  44 } } },  /* 31: S KICK A */
    { { {    7,  23,   83,  16 },  {   -5,  53,   67,  20 },  {   -6,  43,   36,  29 },  {   10,  26,    0,  35 },  {    0,   0,    0,   0 } } },  /* 32: not used by a script */
    { { {   21,  23,   83,  16 },  {    6,  53,   67,  20 },  {   -6,  43,   36,  29 },  {   10,  26,    0,  35 },  {    0,   0,    0,   0 } } },  /* 33: not used by a script */
    { { {   21,  23,   83,  16 },  {    6,  53,   67,  20 },  {   -6,  43,   36,  29 },  {   10,  26,    0,  35 },  {  -49,  50,   60,  12 } } },  /* 34: not used by a script */
    { { {  -33,  23,   86,  15 },  {  -41,  52,   72,  14 },  {  -56,  63,   41,  30 },  {  -47,  55,    0,  42 },  {    0,   0,    0,   0 } } },  /* 35: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    { { {  -33,  23,   83,  16 },  {  -31,  43,   67,  20 },  {  -19,  29,   36,  30 },  {  -47,  55,    0,  42 },  {    0,   0,    0,   0 } } },  /* 36: not used by a script */
    { { {  -39,  31,   89,  16 },  {  -48,  53,   73,  20 },  {  -33,  38,   43,  31 },  {  -47,  55,    0,  42 },  {  -68,  38,   14,  53 } } },  /* 37: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    { { {  -26,  23,   83,  16 },  {  -33,  43,   68,  20 },  {  -25,  29,   35,  30 },  {  -33,  28,    0,  35 },  {    0,   0,    0,   0 } } },  /* 38: not used by a script */
    { { {   -2,  23,   87,  16 },  {  -12,  53,   67,  20 },  {  -13,  43,   36,  29 },  {   -9,  33,    0,  37 },  {    0,   0,    0,   0 } } },  /* 39: UP P GUARD K M, ATTACK 6 S (Att_SLIDE_and_JUMP) */
    { { {    3,  23,   82,  16 },  {  -11,  47,   67,  20 },  {  -35,  61,   48,  24 },  {  -33,  54,    0,  48 },  {  -78,  53,   55,  33 } } },  /* 40: UP P GUARD K M, M KICK A, M KICK C +1 */
    { { {   -5,  23,   82,  16 },  {  -16,  47,   67,  20 },  {  -25,  43,   37,  29 },  {  -20,  33,    0,  37 },  {  -59,  42,   45,  22 } } },  /* 41: M KICK A, UP P GUARD K M, ATTACK 6 S (Att_SLIDE_and_JUMP) */
    { { {   -5,  23,   82,  16 },  {  -16,  47,   67,  20 },  {  -25,  43,   37,  29 },  {  -20,  33,    0,  37 },  {    0,   0,    0,   0 } } },  /* 42: not used by a script */
    { { {  -20,  23,   88,  16 },  {  -34,  51,   70,  20 },  {  -31,  43,   42,  29 },  {  -36,  49,    0,  43 },  {    0,   0,    0,   0 } } },  /* 43: M KICK C */
    { { {  -24,  24,   84,  16 },  {  -36,  52,   69,  16 },  {  -40,  48,   36,  32 },  {  -40,  40,    0,  36 },  {    0,   0,    0,   0 } } },  /* 44: M KICK C, atca 156 */
    { { {  -24,  24,   84,  16 },  {  -36,  52,   69,  16 },  {  -40,  48,   36,  32 },  {  -40,  40,    0,  36 },  {  -70,  51,   61,  60 } } },  /* 45: M KICK C, atca 156 */
    { { {  -24,  24,   84,  16 },  {  -36,  52,   69,  16 },  {  -40,  48,   36,  32 },  {  -40,  40,    0,  36 },  { -107,  74,   41,  61 } } },  /* 46: M KICK C, atca 156 */
    { { {  -24,  24,   84,  16 },  {  -36,  52,   69,  16 },  {  -40,  48,   36,  32 },  {  -40,  40,    0,  36 },  { -107,  74,   41,  61 } } },  /* 47: M KICK C, atca 156 */
    { { {  -24,  24,   84,  16 },  {  -36,  52,   69,  16 },  {  -40,  48,   36,  32 },  {  -40,  40,    0,  36 },  {  -61,  21,    9,  36 } } },  /* 48: not used by a script */
    { { {  -31,  23,   78,  16 },  {  -39,  46,   59,  20 },  {  -47,  39,   39,  23 },  {  -65,  43,    0,  48 },  {    0,   0,    0,   0 } } },  /* 49: M KICK C, atca 156 */
    { { {  -25,  21,   80,  17 },  {  -28,  52,   59,  23 },  {  -33,  40,   35,  30 },  {  -37,  40,    1,  36 },  {    0,   0,    0,   0 } } },  /* 50: not used by a script */
    { { {  -31,  23,   88,  16 },  {  -44,  46,   67,  20 },  {  -39,  43,   36,  29 },  {  -43,  50,    0,  35 },  {    0,   0,    0,   0 } } },  /* 51: not used by a script */
    { { {   -5,  23,   77,  16 },  {  -25,  53,   67,  20 },  {  -18,  43,   36,  29 },  {  -25,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 52: L KICK A, UP P GUARD K L */
    { { {   -5,  23,   77,  16 },  {  -25,  53,   67,  20 },  {  -33,  61,   41,  24 },  {  -17,  39,    1,  39 },  {  -57,  33,   44,  17 } } },  /* 53: UP P GUARD K L */
    { { {   -5,  23,   81,  16 },  {  -25,  53,   67,  20 },  {  -33,  61,   41,  24 },  {  -17,  39,    0,  39 },  {  -90,  63,   35,  38 } } },  /* 54: L KICK A, UP P GUARD K L, ATTACK 6 S (Att_SLIDE_and_JUMP) */
    { { {    0,  23,   78,  16 },  {  -17,  52,   64,  16 },  {  -26,  43,   39,  29 },  {  -17,  33,    0,  35 },  {  -81,  55,   40,  18 } } },  /* 55: L KICK A, UP P GUARD K L, ATTACK 6 S (Att_SLIDE_and_JUMP) */
    { { {    7,  23,   77,  16 },  {  -30,  63,   61,  20 },  {  -30,  43,   36,  29 },  {  -31,  53,    0,  35 },  {  -68,  27,   72,  23 } } },  /* 56: not used by a script */
    { { {   -8,  23,   83,  16 },  {  -21,  51,   68,  18 },  {  -24,  43,   39,  29 },  {  -15,  33,    0,  35 },  {    0,   0,    0,   0 } } },  /* 57: L KICK A, UP P GUARD K L, FUSHIN P S +1 */
    { { {   -2,  23,   81,  16 },  {  -19,  44,   70,  18 },  {  -24,  43,   38,  29 },  {  -15,  36,    0,  35 },  {    0,   0,    0,   0 } } },  /* 58: not used by a script */
    { { {   -4,  23,   90,  16 },  {  -25,  53,   67,  20 },  {  -18,  43,   36,  29 },  {  -25,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 59: not used by a script */
    { { {   20,  23,   77,  16 },  {  -14,  53,   67,  20 },  {  -18,  43,   36,  29 },  {  -25,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 60: TOUKETSU A */
    { { {   37,  23,   65,  16 },  {    4,  53,   54,  20 },  {  -14,  43,   36,  29 },  {  -15,  36,    0,  35 },  {  -32,  38,   65,  11 } } },  /* 61: not used by a script */
    { { {   37,  23,   65,  16 },  {    4,  53,   54,  20 },  {  -14,  43,   36,  29 },  {  -15,  36,    0,  35 },  {    0,   0,    0,   0 } } },  /* 62: not used by a script */
    { { {   32,  23,   78,  16 },  {    4,  53,   64,  20 },  {  -14,  43,   36,  29 },  {  -15,  36,    0,  35 },  {    0,   0,    0,   0 } } },  /* 63: not used by a script */
    { { {  -23,  26,   48,  18 },  {  -30,  58,   43,  18 },  {  -18,  43,   20,  26 },  {  -42,  70,    0,  58 },  {  -72,  52,   34,  22 } } },  /* 64: KAGAMI P A */
    { { {  -14,  23,   50,  16 },  {  -21,  43,   37,  18 },  {  -18,  43,   20,  26 },  {  -42,  70,    0,  58 },  {  -63,  41,   37,  19 } } },  /* 65: KAGAMI P A */
    { { {  -14,  23,   50,  16 },  {  -21,  43,   37,  18 },  {  -18,  43,   20,  26 },  {  -42,  70,    0,  58 },  {    0,   0,    0,   0 } } },  /* 66: KAGAMI P A */
    { { {  -24,  25,   70,  19 },  {  -37,  63,   61,  18 },  {    0,   0,    0,   0 },  {  -47,  74,    0,  60 },  {  -52,  24,   27,  33 } } },  /* 67: KAGAMI P A */
    { { {   -5,  23,   80,  16 },  {  -26,  62,   66,  18 },  {  -18,  43,   37,  29 },  {  -48,  78,    0,  52 },  {  -43,  43,   40,  76 } } },  /* 68: KAGAMI P A, atca 156 */
    { { {   -7,  23,   75,  16 },  {  -18,  44,   60,  18 },  {  -19,  43,   37,  29 },  {  -42,  70,    0,  58 },  {  -35,  33,   51,  59 } } },  /* 69: KAGAMI P A */
    { { {   -8,  23,   69,  16 },  {  -17,  36,   53,  18 },  {  -21,  43,   31,  29 },  {  -42,  70,    0,  58 },  {    0,   0,    0,   0 } } },  /* 70: KAGAMI P A */
    { { {  -15,  21,   50,  18 },  {  -30,  58,   43,  13 },  {  -29,  58,   26,  20 },  {  -38,  72,    0,  30 },  {    0,   0,    0,   0 } } },  /* 71: KAGAMI K A */
    { { {   -4,  34,   43,  18 },  {  -35,  63,   34,  18 },  {  -54,  93,   21,  28 },  {  -85, 128,    0,  21 },  {  -72,  48,    0,  41 } } },  /* 72: KAGAMI K A */
    { { {   -4,  25,   44,  17 },  {  -44,  77,   28,  23 },  {  -23,  65,   20,  26 },  {  -59, 103,    0,  28 },  {    0,   0,    0,   0 } } },  /* 73: KAGAMI K A, UP P GUARD K S */
    { { {   -4,  25,   44,  17 },  {  -44,  77,   28,  23 },  {  -66, 111,   21,  26 },  {  -54, 114,    0,  23 },  {  -88,  62,    0,  28 } } },  /* 74: KAGAMI K A, UP P GUARD K S */
    { { {   -6,  24,   58,  19 },  {  -36,  80,   43,  21 },  {  -31,  84,   20,  26 },  {  -64, 122,    0,  32 },  {    0,   0,    0,   0 } } },  /* 75: KAGAMI K A, UP P GUARD K S */
    { { {  -31,  45,   58,  18 },  {  -54,  89,   43,  18 },  {    0,   0,    0,   0 },  {  -55,  92,    0,  43 },  {    0,   0,    0,   0 } } },  /* 76: KAGAMI K A */
    { { {  -29,  49,   57,  20 },  {  -58,  96,   39,  22 },  {  -24,  43,   20,  26 },  {  -92, 130,    0,  24 },  {  -73,  65,   17,  27 } } },  /* 77: KAGAMI K A */
    { { {  -39,  23,   91,  21 },  {  -41,  75,   83,  23 },  {  -43,  79,   39,  47 },  {  -53,  16,   41,  51 },  {    0,   0,    0,   0 } } },  /* 78: V JUMP P S A, F JUMP P S A */
    { { {  -18,  23,  107,  16 },  {  -25,  53,   74,  20 },  {  -17,  43,   47,  35 },  {    0,   0,    0,   0 },  {  -74,  54,   68,  49 } } },  /* 79: not used by a script */
    { { {  -18,  23,  107,  16 },  {  -25,  53,   74,  20 },  {  -17,  43,   47,  35 },  {    0,   0,    0,   0 },  {  -80,  64,   95,  15 } } },  /* 80: not used by a script */
    { { {   -6,  23,  100,  16 },  {  -25,  53,   86,  20 },  {  -33,  69,   37,  52 },  {    0,   0,    0,   0 },  {  -91,  64,   45,  31 } } },  /* 81: V JUMP K M A */
    { { {  -20,  23,   92,  16 },  {  -23,  53,   75,  20 },  {  -33,  53,   36,  37 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 82: V JUMP K S A, F JUMP K S A */
    { { {  -19,  20,   92,  14 },  {  -32,  61,   80,  14 },  {  -27,  48,   48,  32 },  {    0,   0,    0,   0 },  {  -66,  47,   42,  43 } } },  /* 83: F JUMP K M A, F JUMP K L A */
    { { {  -11,  23,  106,  16 },  {  -23,  53,   90,  20 },  {  -29,  57,   43,  40 },  {    0,   0,    0,   0 },  {  -76,  71,   70,  20 } } },  /* 84: V JUMP K L A */
    { { {  -28,  38,   74,  16 },  {  -37,  65,   56,  20 },  {  -19,  43,   36,  29 },  {  -46,  80,    0,  35 },  {    0,   0,    0,   0 } } },  /* 85: ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN), ATTACK 1 L (Att_HADOUKEN) */
    { { {  -31,  29,   70,  16 },  {  -42,  77,   55,  23 },  {  -19,  43,   36,  29 },  {  -46,  80,    0,  35 },  {    0,   0,    0,   0 } } },  /* 86: ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN), ATTACK 1 L (Att_HADOUKEN) */
    { { {  -12,  18,   72,  14 },  {  -24,  52,   62,  14 },  {  -14,  40,   38,  22 },  {  -24,  56,    0,  36 },  {    0,   0,    0,   0 } } },  /* 87: exca 17, HANASARE, ATTACK 3 S (Att_SENPUUKYAKU) +2 */
    { { {  -10,  18,   84,  14 },  {  -18,  44,   74,  14 },  {  -12,  36,   42,  14 },  {  -16,  56,    0,  40 },  {    0,   0,    0,   0 } } },  /* 88: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    { { {   -8,  18,   84,  14 },  {  -24,  46,   72,  14 },  {  -18,  30,   46,  24 },  {  -16,  24,    0,  44 },  {  -38,  16,   46,  18 } } },  /* 89: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    { { {  -10,  18,   98,  14 },  {  -24,  48,   88,  14 },  {  -29,  60,   49,  43 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 90: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +4 */
    { { {   -3,  23,   83,  16 },  {  -17,  43,   72,  20 },  {   -8,  37,   40,  29 },  {  -20,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 91: not used by a script */
    { { {   -6,  23,   83,  16 },  {  -20,  53,   67,  20 },  {  -12,  38,   36,  29 },  {  -22,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 92: not used by a script */
    { { {   -6,  23,   49,  16 },  {  -16,  42,   37,  18 },  {  -18,  44,   20,  26 },  {  -28,  55,    0,  31 },  {    0,   0,    0,   0 } } },  /* 93: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -27,  36,    0,  53 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 94: not used by a script */
    { { {  -20,  23,   89,  16 },  {  -25,  53,   74,  20 },  {  -17,  43,   47,  35 },  {    0,   0,    0,   0 },  {  -40,  25,   69,  19 } } },  /* 95: not used by a script */
    { { {  -32,  27,   89,  24 },  {  -34,  66,   79,  27 },  {  -25,  69,   50,  35 },  {    0,   0,    0,   0 },  {  -77,  59,   62,  19 } } },  /* 96: V JUMP P M A, F JUMP P M A, F JUMP P L A */
    { { {  -13,  22,  100,  17 },  {  -34,  65,   88,  14 },  {  -29,  60,   49,  43 },  {    0,   0,    0,   0 },  {  -60,  50,   53,  16 } } },  /* 97: ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU), saca 48 +4 */
    { { {  -13,  22,  100,  17 },  {  -34,  65,   88,  14 },  {  -29,  60,   49,  43 },  {    0,   0,    0,   0 },  {  -16,  56,   53,  16 } } },  /* 98: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +4 */
    { { {  -12,  18,   90,  14 },  {  -26,  50,   80,  14 },  {  -20,  34,   50,  28 },  {  -30,  54,   10,  38 },  {    0,   0,    0,   0 } } },  /* 99: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    { { {  -10,  18,   84,  14 },  {  -24,  52,   74,  14 },  {  -24,  40,   40,  30 },  {  -10,  36,    0,  38 },  {    0,   0,    0,   0 } } },  /* 100: not used by a script */
    { { {   -2,  18,   84,  14 },  {  -24,  52,   76,  14 },  {  -18,  36,   38,  34 },  {  -28,  50,    0,  36 },  {    0,   0,    0,   0 } } },  /* 101: not used by a script */
    { { {   14,  18,   78,  14 },  {  -18,  52,   70,  14 },  {  -28,  48,   38,  30 },  {  -24,  26,    0,  36 },  {    0,   0,    0,   0 } } },  /* 102: not used by a script */
    { { {   36,  18,   66,  14 },  {   12,  24,   50,  28 },  {  -30,  40,   44,  30 },  {  -20,  28,    0,  42 },  {  -64,  32,   64,  16 } } },  /* 103: not used by a script */
    { { {   34,  18,   68,  14 },  {   12,  24,   48,  30 },  {  -30,  40,   44,  28 },  {  -18,  28,    0,  42 },  {  -60,  28,   46,  16 } } },  /* 104: not used by a script */
    { { {   20,  18,   78,  14 },  {  -12,  52,   64,  20 },  {  -24,  48,   30,  32 },  {   -8,  30,    0,  30 },  {    0,   0,    0,   0 } } },  /* 105: not used by a script */
    { { {  -23,  18,   86,  14 },  {  -30,  52,   73,  14 },  {  -19,  37,   41,  30 },  {  -38,  72,    2,  36 },  {    0,   0,    0,   0 } } },  /* 106: not used by a script */
    { { {  -31,  23,   79,  16 },  {  -34,  53,   63,  20 },  {  -28,  43,   36,  29 },  {  -33,  55,    0,  35 },  {  -50,  26,   63,  26 } } },  /* 107: not used by a script */
    { { {  -14,  21,   84,  18 },  {  -28,  58,   69,  22 },  {  -21,  49,   38,  31 },  {  -28,  63,    0,  38 },  {  -33,  21,   54,  19 } } },  /* 108: M PUNCH A, UP P GUARD P M */
    { { {  -23,  18,   81,  14 },  {  -34,  52,   67,  14 },  {  -25,  40,   38,  30 },  {  -28,  56,    0,  36 },  {  -46,  16,   74,  18 } } },  /* 109: S PUNCH A */
    { { {  -18,  23,   81,  16 },  {  -30,  61,   70,  15 },  {  -46,  72,   38,  30 },  {  -33,  65,    0,  36 },  {    0,   0,    0,   0 } } },  /* 110: M PUNCH A, UP P GUARD P M */
    { { {  -28,  46,   89,  16 },  {  -35,  60,   69,  26 },  {  -72, 100,   49,  22 },  {  -85, 102,   46,  16 },  {  -72,  41,   71,  15 } } },  /* 111: F JUMP K L A */
    { { {  -24,  23,   79,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -32,  55,    0,  35 },  {  -52,  18,   51,  26 } } },  /* 112: not used by a script */
    { { {  -24,  18,   90,  14 },  {  -17,  52,   79,  14 },  {   -9,  40,   47,  30 },  {  -24,  56,    0,  36 },  {    0,   0,    0,   0 } } },  /* 113: FUSHIN P S */
    { { {  -24,  18,   90,  14 },  {  -17,  52,   79,  14 },  {   -9,  40,   47,  30 },  {  -24,  56,    0,  36 },  {  -59,  41,   78,  10 } } },  /* 114: FUSHIN P S */
    { { {  -17,  37,   77,  14 },  {  -24,  52,   66,  17 },  {  -24,  53,   47,  17 },  {  -17,  40,   37,  15 },  {    0,   0,    0,   0 } } },  /* 115: AIR S, AIR M, AIR L +39 */
    { { {  -20,  23,   89,  16 },  {  -25,  53,   74,  20 },  {  -17,  43,   47,  35 },  {    0,   0,    0,   0 },  {  -52,  39,   71,  17 } } },  /* 116: not used by a script */
    { { {    0,   0,    0,   0 },  {  -23,  50,   22,  18 },  {  -18,  43,    9,  26 },  {  -28,  55,    0,  23 },  {    0,   0,    0,   0 } } },  /* 117: Att_CHOUCHUURENGEKI (command slot 25), saca 56 */
    { { {  -37,  30,   68,  21 },  {  -33,  51,   62,  14 },  {  -34,  52,   46,  20 },  {  -30,  58,    0,  46 },  {    0,   0,    0,   0 } } },  /* 118: not used by a script */
    { { {  -17,  28,  108,  16 },  {  -29,  54,   95,  15 },  {  -31,  69,   47,  49 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 119: V JUMP P L A */
    { { {  -17,  28,  108,  16 },  {  -29,  54,   95,  15 },  {  -31,  69,   47,  49 },  {    0,   0,    0,   0 },  {  -86,  66,   80,  12 } } },  /* 120: V JUMP P L A */
    { { {   -6,  23,  100,  16 },  {  -25,  53,   86,  20 },  {  -33,  69,   37,  52 },  {    0,   0,    0,   0 },  {  -87,  69,   46,  16 } } },  /* 121: V JUMP K M A */
    { { {  -19,  39,   92,  16 },  {  -32,  64,   78,  15 },  {  -30,  59,   42,  37 },  {    0,   0,    0,   0 },  {  -58,  38,   59,  24 } } },  /* 122: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -35,  59,    0,  48 },  {    0,   0,    0,   0 } } },  /* 123: OKIAGARI P S, ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) */
    { { {  -32,  27,   89,  24 },  {  -65,  96,   79,  27 },  {  -72, 104,   49,  33 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 124: not used by a script */
    { { {   -9,  21,   84,  18 },  {  -11,  54,   81,   7 },  {  -11,  52,   41,  40 },  {  -28,  63,    0,  38 },  {    0,   0,    0,   0 } } },  /* 125: PIYO */
    { { {  -34,  21,   80,  18 },  {  -43,  68,   69,  17 },  {  -28,  52,   38,  30 },  {  -29,  63,    0,  38 },  {    0,   0,    0,   0 } } },  /* 126: PIYO */
    { { {  -32,  27,   89,  24 },  {  -65,  96,   79,  27 },  {  -72, 104,   49,  33 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 127: saca 57 */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -41,  81,    0,  24 },  {    0,   0,    0,   0 } } },  /* 128: OKIAGARI P S */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -41,  82,    0,  61 },  {    0,   0,    0,   0 } } },  /* 129: OKIAGARI P S */
    { { {  -20,  41,   96,  27 },  {  -29,  58,   82,  14 },  {  -29,  58,   64,  18 },  {  -33,  66,    0,  64 },  {    0,   0,    0,   0 } } },  /* 130: OKIAGARI P S */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -34,  59,    0,  32 },  {    0,   0,    0,   0 } } },  /* 131: ATTACK 5 S (Att_SHOURYUUREPPA), ATTACK 2 M (Att_SHOURYUUKEN) */
    { { {    0,   0,    0,   0 },  {  -31,  63,   22,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 132: PARING AIR F, PARING AIR B */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -35,  59,    0,  48 },  {    0,   0,    0,   0 } } },  /* 133: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -35,  59,    0,  60 },  {    0,   0,    0,   0 } } },  /* 134: ATTACK 2 S (Att_SHOURYUUKEN) */
};

const ATTACK_BOX ken_att_box[82] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {    0,   0,    0,   0 },  {  -66,  40,   36,  22 },  {    0,   0,    0,   0 } } },  /* 1: ATTACK 5 S (Att_SHOURYUUREPPA), ATTACK 4 S (Att_SHOURYUUREPPA), ATTACK 2 L (Att_SHOURYUUKEN) +2; attack 2, 43, 53, 57 ... */
    { { {    0,   0,    0,   0 },  {  -31,  26,  101,  39 },  {  -46,  24,   48,  29 } } },  /* 2: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +2; attack 1, 2, 44, 46 ... */
    { { {    0,   0,    0,   0 },  {  -40,  18,   58,  16 },  {  -26,  14,  122,  20 } } },  /* 3: not used by a script */
    { { {    0,   0,    0,   0 },  {  -53,  43,   75,  21 },  {  -39,  28,   57,  21 } } },  /* 4: S PUNCH A; attack 3 */
    { { {    0,   0,    0,   0 },  {  -69,  62,   71,  15 },  {    0,   0,    0,   0 } } },  /* 5: S PUNCH B; attack 4 */
    { { {    0,   0,    0,   0 },  {  -52,  26,   39,  26 },  {    0,   0,    0,   0 } } },  /* 6: M PUNCH A, UP P GUARD P M; attack 5 */
    { { {    0,   0,    0,   0 },  {  -86,  71,   67,  12 },  {    0,   0,    0,   0 } } },  /* 7: M PUNCH B, UP P GUARD P S; attack 6 */
    { { {    0,   0,    0,   0 },  {  -63,  47,   61,  25 },  {    0,   0,    0,   0 } } },  /* 8: L PUNCH A, atca 157; attack 7, 8 */
    { { {    0,   0,    0,   0 },  {  -52,  40,   83,  32 },  {    0,   0,    0,   0 } } },  /* 9: L PUNCH A, atca 157; attack 8 */
    { { {    0,   0,    0,   0 },  {  -75,  50,   70,  22 },  {    0,   0,    0,   0 } } },  /* 10: UP P GUARD P L, L PUNCH B; attack 9 */
    { { {    0,   0,    0,   0 },  {  -76,  54,   10,  18 },  {    0,   0,    0,   0 } } },  /* 11: S KICK A; attack 10 */
    { { {    0,   0,    0,   0 },  {  -75,  46,   65,  15 },  {  -35,  35,   59,  13 } } },  /* 12: not used by a script */
    { { {    0,   0,    0,   0 },  {  -80,  35,   57,  15 },  {  -74,  28,   45,  10 } } },  /* 13: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    { { {    0,   0,    0,   0 },  {  -53,  22,   68,  34 },  {    0,   0,    0,   0 } } },  /* 14: M KICK C, atca 156; attack 50 */
    { { {    0,   0,    0,   0 },  {  -87,  59,   49,  21 },  {  -77,  30,   69,  17 } } },  /* 15: M KICK C, atca 156; attack 50 */
    { { {    0,   0,    0,   0 },  { -104,  25,   33,  16 },  {  -89,  47,   41,  20 } } },  /* 16: M KICK C, atca 156; attack 51 */
    { { {    0,   0,    0,   0 },  {  -68,  23,    6,  13 },  {  -89,  40,   21,  14 } } },  /* 17: M KICK C, atca 156 */
    { { {    0,   0,    0,   0 },  {  -80,  33,   73,  17 },  {  -72,  45,   30,  29 } } },  /* 18: not used by a script */
    { { {    0,   0,    0,   0 },  {  -89,  15,   41,  12 },  {  -83,  59,   46,  12 } } },  /* 19: L KICK A, UP P GUARD K L; attack 17 */
    { { {    0,   0,    0,   0 },  {  -78,  42,   74, 231 },  {  -50,  39,   63,  12 } } },  /* 20: not used by a script */
    { { {    0,   0,    0,   0 },  {  -64,  45,   37,  15 },  {    0,   0,    0,   0 } } },  /* 21: KAGAMI P A; attack 19 */
    { { {    0,   0,    0,   0 },  {  -69,  52,   43,  10 },  {    0,   0,    0,   0 } } },  /* 22: KAGAMI P A; attack 20 */
    { { {    0,   0,    0,   0 },  {  -60,  36,   30,  35 },  {    0,   0,    0,   0 } } },  /* 23: KAGAMI P A; attack 21 */
    { { {    0,   0,    0,   0 },  {  -23,  20,   89,  33 },  {  -38,  23,   61,  28 } } },  /* 24: KAGAMI P A; attack 22 */
    { { {    0,   0,    0,   0 },  {  -80,  54,    0,   5 },  {    0,   0,    0,   0 } } },  /* 25: KAGAMI K A; attack 23 */
    { { {    0,   0,    0,   0 },  {  -86,  76,    0,   5 },  {    0,   0,    0,   0 } } },  /* 26: KAGAMI K A, UP P GUARD K S; attack 24 */
    { { {    0,   0,    0,   0 },  {  -96,  75,    0,   6 },  {  -57,  45,    2,  21 } } },  /* 27: KAGAMI K A; attack 25 */
    { { {    0,   0,    0,   0 },  {  -42,  28,   63,  18 },  {    0,   0,    0,   0 } } },  /* 28: V JUMP P S A, F JUMP P S A; attack 26, 32 */
    { { {    0,   0,    0,   0 },  {  -90,  64,   91,  10 },  {    0,   0,    0,   0 } } },  /* 29: V JUMP P L A; attack 34 */
    { { {    0,   0,    0,   0 },  {  -72,  66,   60,  14 },  {    0,   0,    0,   0 } } },  /* 30: V JUMP K M A; attack 30 */
    { { {    0,   0,    0,   0 },  {  -55,  16,   91,  25 },  {  -46,  20,   74,  20 } } },  /* 31: not used by a script */
    { { {    0,   0,    0,   0 },  {  -71,  44,   50,  23 },  {    0,   0,    0,   0 } } },  /* 32: V JUMP P M A, F JUMP P M A, F JUMP P L A; attack 27, 34, 52 */
    { { {    0,   0,    0,   0 },  {  -32,  24,   48,  19 },  {    0,   0,    0,   0 } } },  /* 33: V JUMP K S A, F JUMP K S A; attack 35 */
    { { {    0,   0,    0,   0 },  {  -79,  19,   38,  24 },  {  -63,  77,   52,  22 } } },  /* 34: F JUMP K M A; attack 36 */
    { { {    0,   0,    0,   0 },  {  -52,  24,   18,  28 },  {  -36,  24,    4,  28 } } },  /* 35: ATTACK 2 L (Att_SHOURYUUKEN); attack 73 */
    { { {    0,   0,    0,   0 },  {  -55,  16,   93,  19 },  {  -45,  20,   81,  14 } } },  /* 36: not used by a script */
    { { {    0,   0,    0,   0 },  {  -66,  61,   77,  21 },  {  -81,  25,   93,  22 } } },  /* 37: V JUMP K L A; attack 31 */
    { { {    0,   0,    0,   0 },  {  -78,  18,   63,  20 },  {  -56,  38,   63,  14 } } },  /* 38: ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU), saca 48 +2; attack 39 */
    { { {    0,   0,    0,   0 },  {   18,  35,   66,  16 },  {    0,   0,    0,   0 } } },  /* 39: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +3; attack 39, 40 */
    { { {    0,   0,    0,   0 },  {   -2,  33,   55,  20 },  {    0,   0,    0,   0 } } },  /* 40: not used by a script */
    { { {  -31,   6,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 41: M PUNCH A, M PUNCH B, M KICK A +4; attack 48 */
    { { {    0,   0,    0,   0 },  {  -61,  15,   58,  19 },  {  -55,  25,   79,   9 } } },  /* 42: not used by a script */
    { { {    0,   0,    0,   0 },  {  -61,  13,   32,  28 },  {  -47,  13,   49,  24 } } },  /* 43: not used by a script */
    { { {    0,   0,    0,   0 },  {  -42,  21,   58,  18 },  {    0,   0,    0,   0 } } },  /* 44: not used by a script */
    { { {    0,   0,    0,   0 },  {  -52,  22,   56,  18 },  {  -40,  20,   48,  16 } } },  /* 45: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU); attack 38, 75 */
    { { {    0,   0,    0,   0 },  {  -98,  26,   70,  22 },  {  -70,  26,   62,  22 } } },  /* 46: not used by a script */
    { { {    0,   0,    0,   0 },  {  -78,  28,   70,  14 },  {    0,   0,    0,   0 } } },  /* 47: not used by a script */
    { { {    0,   0,    0,   0 },  {  -77,  18,   55,  13 },  {  -67,  58,   54,  19 } } },  /* 48: F JUMP K L A; attack 37 */
    { { {    0,   0,    0,   0 },  {  -85,  34,   84,  24 },  {  -67,  27,   65,  31 } } },  /* 49: not used by a script */
    { { {    0,   0,    0,   0 },  {  -74,  61,   78,  10 },  {    0,   0,    0,   0 } } },  /* 50: FUSHIN P S; attack 69 */
    { { {    0,   0,    0,   0 },  {  -71,  95,   50,  23 },  {  -62,  95,    0,  50 } } },  /* 51: ATTACK 5 S (Att_SHOURYUUREPPA); attack 56 */
    { { {    0,   0,    0,   0 },  {  -46,  98,   22, 113 },  {    0,   0,    0,   0 } } },  /* 52: ATTACK 5 S (Att_SHOURYUUREPPA); attack 57, 58, 59 */
    { { {    0,   0,    0,   0 },  {  -16,  27,  101,  34 },  {  -40,  28,   40,  38 } } },  /* 53: not used by a script */
    { { {    0,   0,    0,   0 },  {   -5,  28,   99,  30 },  {   -6,  25,   35,  46 } } },  /* 54: not used by a script */
    { { {    0,   0,    0,   0 },  {   -1,  30,   92,  43 },  {  -16,  25,   35,  38 } } },  /* 55: not used by a script */
    { { {    0,   0,    0,   0 },  {  -11,  26,   93,  37 },  {  -17,  35,   39,  36 } } },  /* 56: not used by a script */
    { { {    0,   0,    0,   0 },  {  -73,  21,   75,  17 },  {  -50,  27,   46,  31 } } },  /* 57: UP P GUARD K M; attack 13 */
    { { {    0,   0,    0,   0 },  {  -71,  29,   76,  18 },  {  -42,  23,   58,  19 } } },  /* 58: M KICK A, M KICK C, UP P GUARD K M; attack 13 */
    { { {    0,   0,    0,   0 },  {  -76,  18,   59,  11 },  {  -56,  17,   69,  11 } } },  /* 59: not used by a script */
    { { {    0,   0,    0,   0 },  {  -94,  48,   22,  51 },  {  -60,  53,    0,  81 } } },  /* 60: ATTACK 6 S (Att_SLIDE_and_JUMP); attack 64, 67, 71 */
    { { {    0,   0,    0,   0 },  {  -89,  46,   58,  50 },  {  -59,  53,    0,  85 } } },  /* 61: ATTACK 6 S (Att_SLIDE_and_JUMP); attack 63, 64 */
    { { {    0,   0,    0,   0 },  { -101, 124,   33,  70 },  {    0,   0,    0,   0 } } },  /* 62: ATTACK 6 S (Att_SLIDE_and_JUMP); attack 65, 68 */
    { { {    0,   0,    0,   0 },  {  -24, 115,   27,  82 },  {    0,   0,    0,   0 } } },  /* 63: ATTACK 6 S (Att_SLIDE_and_JUMP); attack 66, 68 */
    { { {    0,   0,    0,   0 },  {  -97,  53,    0,  34 },  {  -64,  64,    0,  58 } } },  /* 64: not used by a script */
    { { {    0,   0,    0,   0 },  {  -93,  49,   45,  42 },  {  -74,  44,    0,  74 } } },  /* 65: not used by a script */
    { { {    0,   0,    0,   0 },  { -100,  37,    0,  19 },  {  -57,  45,    2,  21 } } },  /* 66: not used by a script */
    { { {    0,   0,    0,   0 },  {  -95, 155,    0,  64 },  {    0,   0,    0,   0 } } },  /* 67: ATTACK 5 S (Att_SHOURYUUREPPA); attack 56 */
    { { {    0,   0,    0,   0 },  {  -78,  68,   43,  17 },  {  -40,  45,   31,  19 } } },  /* 68: UP P GUARD K L; attack 17 */
    { { {    0,   0,    0,   0 },  {  -69,  63,   19,  53 },  {    0,   0,    0,   0 } } },  /* 69: ATTACK 4 S (Att_SHOURYUUREPPA); attack 41, 45, 46 */
    { { {    0,   0,    0,   0 },  {  -42,  33,   61,  69 },  {  -61,  51,    0,  78 } } },  /* 70: ATTACK 4 S (Att_SHOURYUUREPPA); attack 42, 46 */
    { { {    0,   0,    0,   0 },  {  -72,  25,   39,  22 },  {  -47,  28,   49,  29 } } },  /* 71: not used by a script */
    { { {    0,   0,    0,   0 },  {  -87,  70,   55,  21 },  {    0,   0,    0,   0 } } },  /* 72: V JUMP K M A; attack 30 */
    { { {    0,   0,    0,   0 },  {  -92,  64,   36,  14 },  {  -66,  64,   24,  14 } } },  /* 73: ATTACK 6 S (Att_SLIDE_and_JUMP); attack 72 */
    { { {  -35,  10,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 74: L PUNCH A, L PUNCH B, L KICK A; attack 48 */
    { { {    0,   0,    0,   0 },  {  -49,  26,   29,  49 },  {    0,   0,    0,   0 } } },  /* 75: not used by a script */
    { { {    0,   0,    0,   0 },  {  -63,  47,   48,  39 },  {    0,   0,    0,   0 } } },  /* 76: L PUNCH A; attack 7 */
    { { {    0,   0,    0,   0 },  {  -49,  26,   29,  49 },  {    0,   0,    0,   0 } } },  /* 77: saca 57; attack 74 */
    { { {    0,   0,    0,   0 },  {  -41,  81,    0,  24 },  {    0,   0,    0,   0 } } },  /* 78: OKIAGARI P S; attack 76 */
    { { {    0,   0,    0,   0 },  {  -42,  27,   42,  33 },  {  -30,  26,  100,  39 } } },  /* 79: OKIAGARI P S; attack 2, 76 */
    { { {    0,   0,    0,   0 },  {  -52,  27,   42,  47 },  {  -39,  30,  102,  39 } } },  /* 80: not used by a script */
    { { {    0,   0,    0,   0 },  {  -64,  39,   70,  12 },  {    0,   0,    0,   0 } } },  /* 81: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU); attack 40, 81, 82 */
};

const CAUGHT_BOX ken_cau_box[20] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -25,   50,    0,   16 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +102 */
    { {  -29,   54,    0,    8 } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +22 */
    { {  -18,   45,   52,   40 } },  /* 3: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +12 */
    { {  -31,   63,   44,   44 } },  /* 4: JUMP FRONT, JUMP BACK, SP JUMP FRONT +13 */
    { {   -1,   48,    0,   90 } },  /* 5: not used by a script */
    { {  -21,   36,    0,   90 } },  /* 6: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    { {  -36,   36,    0,   90 } },  /* 7: ATTACK 6 S (Att_SLIDE_and_JUMP) */
    { {  -29,   54,    0,   16 } },  /* 8: S KICK A */
    { {  -33,   58,    0,    8 } },  /* 9: KAGAMI P A, KAGAMI K A */
    { {  -28,   48,    0,   58 } },  /* 10: not used by a script */
    { {  -28,   45,   46,   61 } },  /* 11: not used by a script */
    { {  -24,   46,   80,   20 } },  /* 12: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +4 */
    { {  -21,   45,   45,   44 } },  /* 13: AIR S, AIR M, AIR L +39 */
    { {  -22,   48,    0,   82 } },  /* 14: not used by a script */
    { {  -46,   80,    0,   16 } },  /* 15: ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN), ATTACK 1 L (Att_HADOUKEN) */
    { {  -41,   81,    0,   16 } },  /* 16: OKIAGARI P S */
    { {  -36,   73,   46,   49 } },  /* 17: OKIAGARI P S */
    { {  -38,   63,    0,   16 } },  /* 18: DASH HUMIKOMI, DASH TOBINOKI */
    { {  -31,   63,   22,   44 } },  /* 19: PARING AIR F, PARING AIR B */
};

const HOSEI_BOX ken_hos_box[29] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -25,   50,    0,   86 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +101 */
    { {  -25,   50,    0,   54 } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +44 */
    { {  -18,   45,   52,   40 } },  /* 3: GUARD AIR, V JUMP P M A, V JUMP K S A +7 */
    { {  -31,   63,   44,   44 } },  /* 4: ATTACK 5 S (Att_SHOURYUUREPPA), ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN) +24 */
    { {    1,   47,   35,   54 } },  /* 5: not used by a script */
    { {  -20,   37,   35,   54 } },  /* 6: not used by a script */
    { {  -37,   37,   35,   54 } },  /* 7: not used by a script */
    { {    6,   47,   35,   54 } },  /* 8: not used by a script */
    { {  -14,   62,   49,   33 } },  /* 9: not used by a script */
    { {  -28,   53,   36,   44 } },  /* 10: TOUKETSU A */
    { {  -20,   49,   36,   36 } },  /* 11: not used by a script */
    { {   -4,   56,   35,   48 } },  /* 12: not used by a script */
    { {  -16,   47,   23,   37 } },  /* 13: not used by a script */
    { {  -16,   47,   13,   37 } },  /* 14: not used by a script */
    { {  -24,   47,   23,   37 } },  /* 15: not used by a script */
    { {  -31,   63,   57,   36 } },  /* 16: V JUMP P S A, F JUMP P S A */
    { {  -22,   69,   40,   61 } },  /* 17: not used by a script */
    { {  -24,   44,   47,   57 } },  /* 18: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +4 */
    { {  -46,   80,    0,   70 } },  /* 19: ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN), ATTACK 1 L (Att_HADOUKEN) */
    { {  -24,   57,   27,   63 } },  /* 20: exca 17, HANASARE, ATTACK 3 S (Att_SENPUUKYAKU) +2 */
    { {  -38,   63,    0,   80 } },  /* 21: DASH HUMIKOMI, DASH TOBINOKI */
    { {  -21,   45,   45,   44 } },  /* 22: AIR S, AIR M, AIR L +39 */
    { {  -20,   47,   36,   44 } },  /* 23: not used by a script */
    { {  -20,   71,    0,   56 } },  /* 24: not used by a script */
    { {  -18,   44,  -20,   87 } },  /* 25: ATTACK 4 S (Att_SHOURYUUREPPA) */
    { {  -22,   49,   12,   82 } },  /* 26: not used by a script */
    { {  -25,   50,    0,   30 } },  /* 27: NEKOROBI S */
    { {  -31,   63,   22,   44 } },  /* 28: PARING AIR F, PARING AIR B */
};
