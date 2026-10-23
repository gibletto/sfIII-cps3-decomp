/*
 * ORO_HITBOX.C  Oro's hit boxes
 *
 * Each of Oro's animation frames names a row of oro_hit_ix_table (a frame line's hit field). The
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
 * rows of oro_catt_table dealt through it. Row 0 of a box table is no box.
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

const HIT_IX oro_hit_ix_table[175] = {
    /* boix  atix  cuix  hoix */
    {    0,    0,    0,    0 },  /* 0: NAGERARE KAIHI, OKIAGARI, OKIAGARI F +22 */
    {    1,    0,    1,    1 },  /* 1: KAMAE, HURIMUKI, DASH HUMIKOMI +94 */
    {    1,    0,    1,    1 },  /* 2: FRONT WALK, BACK WALK */
    {    3,    0,    1,    1 },  /* 3: DASH HUMIKOMI */
    {   10,    0,    2,    2 },  /* 4: DASH HUMIKOMI */
    {    5,    0,    2,   16 },  /* 5: DASH HUMIKOMI */
    {    1,    0,    1,    1 },  /* 6: DASH HUMIKOMI */
    {    7,    0,    1,    1 },  /* 7: DASH TOBINOKI */
    {    8,    0,    1,    1 },  /* 8: DASH TOBINOKI */
    {   10,    0,    1,    1 },  /* 9: DASH TOBINOKI */
    {   10,    0,    3,    3 },  /* 10: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +18 */
    {   10,    0,    3,    3 },  /* 11: KAGAMI TURN */
    {   12,    0,    4,    4 },  /* 12: JUMP FRONT, JUMP BACK, SP JUMP FRONT +4 */
    {   13,    0,    4,    4 },  /* 13: JUMP FRONT, JUMP BACK, SP JUMP FRONT +4 */
    {   14,    0,    4,    4 },  /* 14: JUMP FRONT, JUMP BACK, S JUMP FRONT +8 */
    {   15,    0,    4,    4 },  /* 15: JUMP JUNBI, SP JUMP JUNBI, JUMP VERTICAL +11 */
    {   16,    1,    1,    1 },  /* 16: S PUNCH A */
    {    1,    0,    1,    1 },  /* 17: S PUNCH A */
    {    1,    0,    1,    1 },  /* 18: S PUNCH A */
    {    1,    0,    1,    1 },  /* 19: S PUNCH B */
    {   19,    2,    1,    1 },  /* 20: S PUNCH B */
    {   19,    0,    1,    1 },  /* 21: S PUNCH B */
    {   20,    0,    1,    1 },  /* 22: not used by a script */
    {   21,    3,    1,    1 },  /* 23: not used by a script */
    {   21,    0,    1,    1 },  /* 24: not used by a script */
    {    1,    0,    1,    1 },  /* 25: M PUNCH B */
    {   23,    4,    1,    1 },  /* 26: not used by a script */
    {   24,    4,    1,    1 },  /* 27: M PUNCH B */
    {   24,    0,    1,    1 },  /* 28: M PUNCH B */
    {   25,    0,    1,    1 },  /* 29: caca 5, M PUNCH B */
    {    1,    6,    1,    1 },  /* 30: not used by a script */
    {   27,    5,    1,    1 },  /* 31: M PUNCH A */
    {   28,    6,    1,    1 },  /* 32: M PUNCH A */
    {   29,    0,    1,    1 },  /* 33: M PUNCH A */
    {   30,    0,    1,    1 },  /* 34: M PUNCH A */
    {    1,    0,    1,    1 },  /* 35: M PUNCH A */
    {   32,    0,    1,    1 },  /* 36: L PUNCH A, UP P GUARD P L */
    {   33,    0,    1,    1 },  /* 37: L PUNCH A, UP P GUARD P L */
    {   34,    0,    1,    1 },  /* 38: L PUNCH A, UP P GUARD P L */
    {   35,    7,    1,    1 },  /* 39: L PUNCH A, UP P GUARD P L */
    {   36,    8,    1,    1 },  /* 40: L PUNCH A, UP P GUARD P L */
    {   36,    0,    1,    1 },  /* 41: L PUNCH A, UP P GUARD P L */
    {   37,    0,    1,    1 },  /* 42: L PUNCH A, UP P GUARD P L */
    {   38,    0,    1,    1 },  /* 43: S KICK A */
    {   40,    9,    1,    1 },  /* 44: S KICK A */
    {   40,    0,    1,    1 },  /* 45: S KICK A */
    {   39,    0,    1,    1 },  /* 46: S KICK A */
    {   41,    0,    1,    1 },  /* 47: S KICK B */
    {   42,   10,    1,    1 },  /* 48: S KICK B */
    {   42,    0,    1,    1 },  /* 49: S KICK B */
    {   43,    0,    1,    1 },  /* 50: S KICK B */
    {   44,    0,    1,    1 },  /* 51: M KICK A */
    {   46,   11,    1,    1 },  /* 52: M KICK A */
    {   46,    0,    1,    1 },  /* 53: M KICK A */
    {   47,    0,    1,    1 },  /* 54: M KICK A */
    {   48,    0,    6,    1 },  /* 55: M KICK B, UP P GUARD K S */
    {   49,   12,    6,    1 },  /* 56: UP P GUARD K S */
    {   50,   51,    6,    1 },  /* 57: M KICK B, UP P GUARD K S */
    {   50,    0,    6,    1 },  /* 58: M KICK B, UP P GUARD K S */
    {   51,    0,    6,    1 },  /* 59: M KICK B, UP P GUARD K S */
    {   52,    0,    1,    1 },  /* 60: M KICK B, UP P GUARD K S */
    {   53,    0,    1,    1 },  /* 61: L KICK A */
    {   54,   13,    1,    1 },  /* 62: L KICK A */
    {   55,   52,    1,    1 },  /* 63: not used by a script */
    {   55,    0,    1,    1 },  /* 64: L KICK A */
    {   57,    0,    1,    1 },  /* 65: L KICK A */
    {   58,    0,   11,    3 },  /* 66: KAGAMI P A */
    {   59,   14,   11,    3 },  /* 67: KAGAMI P A */
    {   59,    0,   11,    3 },  /* 68: KAGAMI P A */
    {   60,    0,    3,    3 },  /* 69: KAGAMI P A */
    {   61,   15,    3,    3 },  /* 70: KAGAMI P A */
    {   62,   16,    3,    3 },  /* 71: KAGAMI P A */
    {   60,    0,    3,    3 },  /* 72: KAGAMI P A */
    {   63,    0,    3,    3 },  /* 73: KAGAMI P A */
    {   64,    0,    3,    3 },  /* 74: TOUKETSU A, KAGAMI P A */
    {   65,    0,    3,    3 },  /* 75: KAGAMI K A */
    {   66,   18,   11,    3 },  /* 76: KAGAMI K A */
    {   66,    0,   11,    3 },  /* 77: KAGAMI K A */
    {   65,    0,   11,    3 },  /* 78: KAGAMI K A */
    {   68,   19,    3,    3 },  /* 79: D P GUARD K S */
    {   68,    0,    3,    3 },  /* 80: KAGAMI K A, D P GUARD K S */
    {   69,   19,    3,    3 },  /* 81: KAGAMI K A, D P GUARD K S */
    {   69,    0,    3,    3 },  /* 82: KAGAMI K A, D P GUARD K S */
    {   70,    0,    3,    3 },  /* 83: KAGAMI K A, D P GUARD K S */
    {   71,    0,    3,    3 },  /* 84: KAGAMI K A, D P GUARD K S */
    {   72,    0,    3,    3 },  /* 85: KAGAMI K A, D P GUARD K S */
    {   73,   20,    4,    4 },  /* 86: V JUMP P S A */
    {   73,    0,    4,    4 },  /* 87: V JUMP P S A */
    {  104,   21,    4,    4 },  /* 88: V JUMP K S A, saca 66 */
    {  104,   22,    4,    4 },  /* 89: V JUMP K M A */
    {   74,   23,    4,    4 },  /* 90: V JUMP K L A */
    {   74,    0,    4,    4 },  /* 91: V JUMP K L A */
    {   75,    0,    4,    4 },  /* 92: F JUMP P S A, F JUMP P M A, F JUMP P L A */
    {   76,    0,    4,    4 },  /* 93: F JUMP P S A, F JUMP P M A */
    {  118,   24,    4,    4 },  /* 94: F JUMP P S A */
    {  105,   25,    4,    4 },  /* 95: F JUMP P M A */
    {   77,    0,    4,    4 },  /* 96: F JUMP P S A, F JUMP P M A */
    {  106,   26,    4,    4 },  /* 97: F JUMP P L A */
    {  107,   27,    4,    4 },  /* 98: F JUMP P L A */
    {   78,    0,    4,    4 },  /* 99: F JUMP K S A, F JUMP K M A */
    {   79,    0,    4,    4 },  /* 100: GUARD AIR, F JUMP K S A, F JUMP K M A */
    {   79,   28,    4,    4 },  /* 101: F JUMP K S A */
    {   79,   29,    4,    4 },  /* 102: F JUMP K M A */
    {   80,    0,    4,    4 },  /* 103: GUARD AIR, F JUMP K S A, F JUMP K M A */
    {   81,   30,    4,    4 },  /* 104: F JUMP K M B, air Att_KUUCHUUJINNCHUUWATARI (command slot 38) */
    {   81,   50,    4,    4 },  /* 105: Att_JINNCHUUWATARI (command slot 25) */
    {   82,    0,    4,    4 },  /* 106: F JUMP K M B, F JUMP K L A */
    {   83,   31,    4,    4 },  /* 107: not used by a script */
    {   83,    0,    4,    4 },  /* 108: F JUMP K L A */
    {   10,    0,    3,    3 },  /* 109: PARING DOWN, GUARD DOWN */
    {   85,   32,    1,    1 },  /* 110: UP P GUARD P S, D P GUARD P S */
    {   85,    0,    1,    1 },  /* 111: UP P GUARD P S, D P GUARD P S */
    {   86,   33,    1,    1 },  /* 112: FUSHIN P S */
    {   86,    0,    1,    1 },  /* 113: FUSHIN P S */
    {    0,    0,    0,    3 },  /* 114: OKIAGARI, UKEMI MOVE F, UKEMI MOVE R +11 */
    {   87,    0,    0,   15 },  /* 115: saca 61 */
    {    0,    0,    0,   12 },  /* 116: not used by a script */
    {   88,    0,    0,   12 },  /* 117: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    {   89,    0,    0,   12 },  /* 118: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    {   90,   34,    1,   12 },  /* 119: ATTACK 3 L (Att_SHOURYUUKEN) */
    {   91,   35,    1,   13 },  /* 120: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    {   92,   36,   10,   14 },  /* 121: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    {   93,    0,   10,   14 },  /* 122: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    {   94,    0,    1,    1 },  /* 123: ATTACK 4 S (Att_HADOUKEN), ATTACK 4 M (Att_HADOUKEN), ATTACK 4 L (Att_HADOUKEN) +1 */
    {   95,    0,    1,    1 },  /* 124: ATTACK 4 S (Att_HADOUKEN), ATTACK 4 M (Att_HADOUKEN), ATTACK 4 L (Att_HADOUKEN) +1 */
    {   96,    0,    1,    1 },  /* 125: ATTACK 4 S (Att_HADOUKEN), ATTACK 4 M (Att_HADOUKEN), ATTACK 4 L (Att_HADOUKEN) +1 */
    {   97,   37,    1,    1 },  /* 126: not used by a script */
    {   97,    0,    1,    1 },  /* 127: ATTACK 4 S (Att_HADOUKEN) */
    {   98,   38,    1,    1 },  /* 128: not used by a script */
    {   98,    0,    1,    1 },  /* 129: ATTACK 4 M (Att_HADOUKEN) */
    {   99,   39,    1,    1 },  /* 130: not used by a script */
    {   99,    0,    1,    1 },  /* 131: ATTACK 4 L (Att_HADOUKEN), ATTACK 4 SP */
    {  100,    0,    4,    4 },  /* 132: ATTACK 5 S (Att_KUUCHUUNICHIRINSHOU), ATTACK 5 M (Att_KUUCHUUNICHIRINSHOU), ATTACK 5 L (Att_KUUCHUUNICHIRINSHOU) +1 */
    {  101,    0,    4,    4 },  /* 133: ATTACK 5 S (Att_KUUCHUUNICHIRINSHOU), ATTACK 5 M (Att_KUUCHUUNICHIRINSHOU), ATTACK 5 L (Att_KUUCHUUNICHIRINSHOU) +1 */
    {  101,    0,    4,    4 },  /* 134: ATTACK 5 S (Att_KUUCHUUNICHIRINSHOU), ATTACK 5 M (Att_KUUCHUUNICHIRINSHOU), ATTACK 5 L (Att_KUUCHUUNICHIRINSHOU) +1 */
    {  109,   41,    1,    1 },  /* 135: ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN), ATTACK 1 L (Att_HADOUKEN) */
    {  102,   42,    3,    3 },  /* 136: KAGAMI P A */
    {  111,   43,    3,    3 },  /* 137: KAGAMI K A */
    {  103,   44,    4,    4 },  /* 138: V JUMP P M A */
    {  103,    0,    4,    4 },  /* 139: V JUMP P M A, V JUMP P L A, atca 157 */
    {  108,    0,    4,    4 },  /* 140: F JUMP P L A */
    {    1,   45,    1,    1 },  /* 141: M PUNCH A, M PUNCH B, M KICK A +3 */
    {  110,    0,    9,   18 },  /* 142: AIR S, AIR M, AIR L +38 */
    {    0,    0,    0,    1 },  /* 143: ATTACK 6 S (Att_HADOUKEN), super art Att_HADOUKEN (command slot 17), super art Att_HADOUKEN (command slot 18) */
    {  113,   57,    1,    1 },  /* 144: atca 156, saca 56 */
    {  113,   46,    1,    1 },  /* 145: atca 159, saca 56 */
    {  113,    0,    1,    1 },  /* 146: atca 156, atca 158, atca 159 +1 */
    {  113,   58,    1,    1 },  /* 147: atca 158, saca 56 */
    {   15,   47,    4,    4 },  /* 148: V JUMP P L A, F JUMP P L A */
    {   93,   48,   10,   14 },  /* 149: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    {   46,   49,    1,    1 },  /* 150: not used by a script */
    {   81,    0,    4,    4 },  /* 151: air Att_KUUCHUUJINNCHUUWATARI (command slot 38), Att_JINNCHUUWATARI (command slot 25) */
    {   45,   42,    3,    3 },  /* 152: not used by a script */
    {   65,   43,    3,    3 },  /* 153: not used by a script */
    {    0,    0,    0,   15 },  /* 154: OKIAGARI F, OKIAGARI B, dmca 90 +1 */
    {  115,   53,    4,    4 },  /* 155: V JUMP P L A */
    {  116,   22,    4,    4 },  /* 156: not used by a script */
    {   15,   23,    4,    4 },  /* 157: not used by a script */
    {   83,   54,    4,    4 },  /* 158: F JUMP K L A */
    {    1,   55,    1,    1 },  /* 159: L PUNCH A, L KICK A */
    {    0,    0,    0,    4 },  /* 160: AIR S, AIR M, AIR L +2 */
    {  122,   56,    4,    4 },  /* 161: atca 157 */
    {  119,    0,    4,    4 },  /* 162: Att_JINNCHUUWATARI (command slot 25) */
    {  120,    0,    1,   19 },  /* 163: PIYO */
    {  121,   59,    4,    4 },  /* 164: not used by a script */
    {  111,    0,    3,    3 },  /* 165: KAGAMI K A */
    {    0,    0,    0,   20 },  /* 166: NEKOROBI S */
    {  123,    0,    1,    1 },  /* 167: ATTACK 6 S (Att_HADOUKEN) */
    {   59,    0,    3,    3 },  /* 168: KAGAMI P A */
    {   58,    0,    3,    3 },  /* 169: KAGAMI P A */
    {    1,    0,    0,    1 },  /* 170: HANASARE */
    {   10,    0,    0,    3 },  /* 171: HANASARE */
    {    1,    0,    1,    0 },  /* 172: LOSE SONABA */
    {  106,    0,    4,    4 },  /* 173: F JUMP P L A */
    {  107,    0,    4,    4 },  /* 174: F JUMP P L A */
};

const BODY_BOX oro_body_box[124] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {  -20,  29,   65,  23 },  {  -32,  56,   58,  23 },  {  -32,  58,   28,  29 },  {  -35,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 1: KAMAE, HURIMUKI, DASH HUMIKOMI +96 */
    { { {  -19,  21,   67,  21 },  {  -28,  49,   52,  16 },  {  -28,  50,   28,  22 },  {  -35,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 2: not used by a script */
    { { {   -5,  21,   53,  23 },  {  -26,  47,   42,  15 },  {  -25,  44,   24,  17 },  {  -37,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 3: DASH HUMIKOMI */
    { { {  -24,  21,   33,  23 },  {  -42,  47,   30,  15 },  {  -46,  55,   21,  13 },  {  -50,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 4: not used by a script */
    { { {  -50,  21,   36,  23 },  {  -42,  47,   34,  15 },  {  -38,  55,   23,  13 },  {  -53,  90,    0,  27 },  {    0,   0,    0,   0 } } },  /* 5: DASH HUMIKOMI */
    { { {  -39,  21,   57,  23 },  {  -42,  47,   34,  15 },  {  -38,  55,   23,  13 },  {  -53,  90,    0,  27 },  {    0,   0,    0,   0 } } },  /* 6: not used by a script */
    { { {  -22,  21,   53,  23 },  {  -28,  49,   52,  12 },  {  -26,  42,   28,  22 },  {  -35,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 7: DASH TOBINOKI */
    { { {  -33,  21,   46,  23 },  {  -28,  49,   52,  12 },  {  -26,  42,   28,  22 },  {  -35,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 8: DASH TOBINOKI */
    { { {  -30,  21,   34,  23 },  {  -25,  49,   40,  12 },  {  -26,  42,   28,  22 },  {  -35,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 9: not used by a script */
    { { {  -29,  31,   41,  23 },  {  -29,  58,   30,  23 },  {  -29,  59,   16,  14 },  {  -42,  76,    0,  14 },  {    0,   0,    0,   0 } } },  /* 10: DASH HUMIKOMI, DASH TOBINOKI, KAGAMU +22 */
    { { {   -6,  21,   39,  23 },  {  -22,  49,   32,  12 },  {  -20,  46,   18,  16 },  {  -34,  64,    0,  14 },  {    0,   0,    0,   0 } } },  /* 11: not used by a script */
    { { {  -45,  21,   81,  23 },  {  -27,  55,   74,  20 },  {  -20,  43,   29,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 12: JUMP FRONT, JUMP BACK, SP JUMP FRONT +4 */
    { { {  -51,  21,   70,  23 },  {  -27,  55,   74,  20 },  {  -20,  43,   29,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 13: JUMP FRONT, JUMP BACK, SP JUMP FRONT +4 */
    { { {  -51,  21,   63,  23 },  {  -27,  55,   74,  20 },  {  -20,  43,   29,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 14: JUMP FRONT, JUMP BACK, S JUMP FRONT +8 */
    { { {  -10,  21,   95,  23 },  {  -27,  55,   74,  20 },  {  -20,  43,   29,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 15: JUMP JUNBI, SP JUMP JUNBI, JUMP VERTICAL +12 */
    { { {  -18,  21,   65,  23 },  {  -32,  56,   58,  23 },  {  -32,  58,   28,  29 },  {  -35,  64,    0,  27 },  {  -62,  39,   64,  36 } } },  /* 16: S PUNCH A */
    { { {  -13,  21,   62,  23 },  {  -28,  49,   52,  12 },  {  -26,  42,   28,  22 },  {  -35,  64,    0,  27 },  {  -38,  17,   57,  15 } } },  /* 17: not used by a script */
    { { {  -22,  21,   64,  23 },  {  -28,  49,   52,  12 },  {  -26,  42,   28,  22 },  {  -35,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 18: not used by a script */
    { { {  -22,  21,   62,  23 },  {  -32,  56,   58,  23 },  {  -32,  58,   28,  29 },  {  -35,  64,    0,  27 },  { -100,  67,   49,  20 } } },  /* 19: S PUNCH B */
    { { {  -22,  21,   69,  23 },  {  -33,  49,   54,  12 },  {  -26,  42,   28,  22 },  {  -35,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 20: not used by a script */
    { { {  -22,  21,   69,  23 },  {  -33,  49,   54,  12 },  {  -26,  42,   28,  22 },  {  -35,  64,    0,  27 },  {  -72,  40,   48,  12 } } },  /* 21: not used by a script */
    { { {  -10,  21,   74,  23 },  {  -22,  49,   61,  12 },  {  -19,  42,   32,  27 },  {  -30,  64,    0,  30 },  {    0,   0,    0,   0 } } },  /* 22: not used by a script */
    { { {  -18,  21,   85,  23 },  {  -27,  44,   70,  15 },  {  -25,  42,   42,  26 },  {  -30,  64,    0,  39 },  {  -81,  60,   62,  29 } } },  /* 23: not used by a script */
    { { {  -18,  21,   85,  23 },  {  -27,  44,   70,  15 },  {  -25,  42,   42,  26 },  {  -30,  64,    0,  39 },  {  -86,  68,   68,  24 } } },  /* 24: M PUNCH B */
    { { {  -18,  21,   85,  23 },  {  -27,  44,   70,  15 },  {  -25,  42,   42,  26 },  {  -30,  64,    0,  39 },  {    0,   0,    0,   0 } } },  /* 25: caca 5, M PUNCH B */
    { { {  -13,  21,   62,  23 },  {  -28,  49,   52,  12 },  {  -15,  42,   27,  22 },  {  -35,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 26: not used by a script */
    { { {  -20,  29,   65,  23 },  {  -32,  56,   58,  23 },  {  -32,  58,   28,  29 },  {  -35,  64,    0,  27 },  {  -54,  36,   38,  23 } } },  /* 27: M PUNCH A */
    { { {  -18,  21,   65,  23 },  {  -32,  56,   58,  23 },  {  -32,  58,   28,  29 },  {  -35,  64,    0,  27 },  {  -39,  28,   73,  56 } } },  /* 28: M PUNCH A */
    { { {  -18,  21,   65,  23 },  {  -32,  56,   58,  23 },  {  -32,  58,   28,  29 },  {  -35,  64,    0,  27 },  {  -37,  25,   78,  48 } } },  /* 29: M PUNCH A */
    { { {  -18,  21,   65,  23 },  {  -32,  56,   58,  23 },  {  -32,  58,   28,  29 },  {  -35,  64,    0,  27 },  {  -39,  34,   67,  15 } } },  /* 30: M PUNCH A */
    { { {   -4,  21,   66,  23 },  {  -28,  49,   52,  12 },  {  -15,  42,   27,  22 },  {  -24,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 31: not used by a script */
    { { {   -5,  21,   72,  23 },  {  -20,  52,   59,  12 },  {  -35,  62,   34,  25 },  {  -15,  52,    0,  34 },  {    0,   0,    0,   0 } } },  /* 32: L PUNCH A, UP P GUARD P L */
    { { {   -5,  21,   72,  23 },  {  -17,  49,   59,  12 },  {  -18,  42,   35,  22 },  {  -33,  74,    0,  33 },  {    0,   0,    0,   0 } } },  /* 33: L PUNCH A, UP P GUARD P L */
    { { {  -16,  21,   62,  23 },  {  -22,  49,   52,  12 },  {  -15,  42,   28,  22 },  {  -33,  74,    0,  33 },  {    0,   0,    0,   0 } } },  /* 34: L PUNCH A, UP P GUARD P L */
    { { {  -16,  21,   56,  23 },  {  -24,  49,   47,  12 },  {  -15,  42,   28,  22 },  {  -30,  74,    0,  27 },  {  -56,  29,   54,  36 } } },  /* 35: L PUNCH A, UP P GUARD P L */
    { { {  -16,  21,   56,  23 },  {  -34,  58,   47,  12 },  {  -15,  42,   28,  22 },  {  -22,  74,    0,  27 },  {  -71,  54,   25,  22 } } },  /* 36: L PUNCH A, UP P GUARD P L */
    { { {   -3,  21,   69,  23 },  {  -25,  57,   56,  12 },  {  -28,  60,   33,  23 },  {  -38,  76,    0,  33 },  {    0,   0,    0,   0 } } },  /* 37: L PUNCH A, UP P GUARD P L */
    { { {   14,  21,   77,  23 },  {   -3,  49,   59,  16 },  {  -18,  42,   37,  22 },  {  -31,  54,    0,  40 },  {    0,   0,    0,   0 } } },  /* 38: S KICK A */
    { { {   14,  21,   77,  23 },  {   -3,  49,   59,  16 },  {  -18,  42,   37,  22 },  {   -2,  26,    0,  40 },  {    0,   0,    0,   0 } } },  /* 39: S KICK A */
    { { {   14,  21,   77,  23 },  {   -3,  49,   59,  16 },  {  -18,  42,   37,  22 },  {   -2,  26,    0,  40 },  {  -48,  44,   42,  48 } } },  /* 40: S KICK A */
    { { {   16,  21,   79,  23 },  {  -18,  60,   67,  12 },  {  -31,  69,   42,  26 },  {   -2,  34,    0,  42 },  {    0,   0,    0,   0 } } },  /* 41: S KICK B */
    { { {   27,  21,   78,  23 },  {  -18,  60,   67,  12 },  {  -15,  42,   42,  26 },  {   -2,  34,    0,  42 },  {  -82,  69,   40,  26 } } },  /* 42: S KICK B */
    { { {   27,  21,   78,  23 },  {  -18,  60,   67,  12 },  {  -31,  69,   42,  26 },  {   -2,  34,    0,  42 },  {    0,   0,    0,   0 } } },  /* 43: S KICK B */
    { { {    1,  21,   75,  23 },  {  -14,  49,   62,  12 },  {  -16,  42,   35,  25 },  {  -17,  64,    0,  33 },  {    0,   0,    0,   0 } } },  /* 44: M KICK A */
    { { {  -30,  21,   45,  23 },  {  -29,  58,   28,  23 },  {  -29,  59,   16,  14 },  {  -42,  76,    0,  14 },  {  -71,  54,   28,  27 } } },  /* 45: not used by a script */
    { { {    1,  21,   75,  23 },  {  -14,  49,   62,  12 },  {  -16,  42,   35,  25 },  {  -17,  39,    0,  33 },  {  -44,  29,   34,  53 } } },  /* 46: M KICK A */
    { { {  -16,  21,   75,  23 },  {  -14,  49,   62,  12 },  {  -16,  42,   35,  25 },  {  -17,  39,    0,  33 },  {  -36,  21,   49,  22 } } },  /* 47: M KICK A */
    { { {    2,  21,   93,  23 },  {   -9,  49,   75,  17 },  {  -15,  42,   45,  29 },  {  -10,  34,    0,  44 },  {    0,   0,    0,   0 } } },  /* 48: M KICK B, UP P GUARD K S */
    { { {    2,  21,   93,  23 },  {   -9,  49,   75,  17 },  {  -15,  42,   45,  29 },  {  -10,  34,    0,  44 },  {  -68,  43,   55,  25 } } },  /* 49: UP P GUARD K S */
    { { {   -5,  21,   87,  23 },  {   -9,  49,   75,  17 },  {  -15,  42,   45,  29 },  {  -10,  34,    0,  44 },  {  -83,  74,   53,  27 } } },  /* 50: M KICK B, UP P GUARD K S */
    { { {   -5,  21,   79,  23 },  {  -11,  49,   64,  17 },  {  -15,  42,   39,  29 },  {  -10,  34,    0,  37 },  {  -83,  74,   38,  25 } } },  /* 51: M KICK B, UP P GUARD K S */
    { { {  -13,  21,   76,  23 },  {  -28,  49,   62,  28 },  {  -26,  42,   30,  29 },  {  -35,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 52: M KICK B, UP P GUARD K S */
    { { {  -11,  21,   82,  23 },  {  -16,  49,   66,  20 },  {  -26,  42,   38,  28 },  {  -29,  34,    0,  36 },  {    0,   0,    0,   0 } } },  /* 53: L KICK A */
    { { {    5,  21,   82,  23 },  {  -36,  72,   66,  26 },  {  -18,  42,   38,  28 },  {  -29,  34,    0,  36 },  {  -89,  70,   55,  32 } } },  /* 54: L KICK A */
    { { {    5,  21,   82,  23 },  {  -36,  72,   66,  26 },  {  -18,  42,   38,  28 },  {  -29,  34,    0,  36 },  {  -82,  65,   55,  24 } } },  /* 55: L KICK A */
    { { {   -8,  21,   81,  23 },  {  -16,  49,   66,  20 },  {  -18,  42,   38,  28 },  {  -29,  34,    0,  36 },  {    0,   0,    0,   0 } } },  /* 56: not used by a script */
    { { {  -16,  21,   81,  23 },  {  -28,  49,   64,  20 },  {  -25,  42,   38,  28 },  {  -25,  34,    0,  36 },  {    0,   0,    0,   0 } } },  /* 57: L KICK A */
    { { {  -30,  21,   45,  23 },  {  -29,  58,   28,  23 },  {  -29,  59,   16,  14 },  {  -42,  76,    0,  14 },  {    0,   0,    0,   0 } } },  /* 58: KAGAMI P A */
    { { {  -22,  21,   53,  23 },  {  -30,  58,   38,  23 },  {  -43,  72,   16,  20 },  {  -59,  90,    0,  14 },  { -108,  85,   29,  23 } } },  /* 59: KAGAMI P A */
    { { {   -8,  21,   52,  28 },  {  -33,  62,   40,  23 },  {  -42,  70,   21,  17 },  {  -51,  80,    0,  19 },  {    0,   0,    0,   0 } } },  /* 60: KAGAMI P A */
    { { {   -8,  21,   52,  28 },  {  -33,  62,   40,  23 },  {  -42,  70,   21,  17 },  {  -51,  80,    0,  19 },  {  -79,  51,   36,  25 } } },  /* 61: KAGAMI P A */
    { { {   -8,  21,   52,  28 },  {  -33,  62,   40,  23 },  {  -42,  70,   21,  17 },  {  -51,  80,    0,  19 },  {  -69,  59,   44,  25 } } },  /* 62: KAGAMI P A */
    { { {   -8,  21,   52,  28 },  {  -33,  62,   40,  23 },  {  -42,  70,   21,  17 },  {  -51,  80,    0,  19 },  {    0,   0,    0,   0 } } },  /* 63: KAGAMI P A */
    { { {  -22,  21,   55,  23 },  {  -29,  58,   28,  23 },  {  -29,  59,   16,  14 },  {  -42,  76,    0,  14 },  {    0,   0,    0,   0 } } },  /* 64: TOUKETSU A, KAGAMI P A */
    { { {    2,  21,   55,  23 },  {  -14,  55,   43,  15 },  {  -27,  67,   19,  23 },  {  -46,  85,    0,  19 },  {    0,   0,    0,   0 } } },  /* 65: KAGAMI K A */
    { { {    2,  21,   55,  23 },  {  -14,  55,   43,  15 },  {  -27,  67,   19,  23 },  {  -57,  93,    0,  32 },  {  -91,  49,    0,  22 } } },  /* 66: KAGAMI K A */
    { { {   30,  21,   39,  23 },  {  -15,  49,   41,  12 },  {  -26,  42,   28,  22 },  {  -35,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 67: not used by a script */
    { { {    3,  21,   47,  23 },  {  -27,  61,   41,  17 },  {  -46,  78,   28,  22 },  {  -58,  91,    0,  27 },  {  -72,  41,    0,  36 } } },  /* 68: D P GUARD K S, KAGAMI K A */
    { { {    3,  21,   47,  23 },  {  -27,  61,   41,  17 },  {  -46,  78,   28,  22 },  {  -58,  91,    0,  27 },  {  -98,  66,    0,  36 } } },  /* 69: KAGAMI K A, D P GUARD K S */
    { { {    3,  21,   47,  23 },  {  -27,  61,   41,  17 },  {  -46,  78,   28,  22 },  {  -58,  91,    0,  27 },  {    0,   0,    0,   0 } } },  /* 70: KAGAMI K A, D P GUARD K S */
    { { {    3,  21,   47,  23 },  {  -27,  61,   41,  17 },  {  -46,  78,   28,  22 },  {  -58,  91,    0,  27 },  {    0,   0,    0,   0 } } },  /* 71: KAGAMI K A, D P GUARD K S */
    { { {  -28,  21,   47,  23 },  {  -15,  49,   41,  12 },  {  -26,  42,   28,  22 },  {  -35,  64,    0,  27 },  {    0,   0,    0,   0 } } },  /* 72: KAGAMI K A, D P GUARD K S */
    { { {  -33,  26,   92,  23 },  {  -73,  98,   61,  30 },  {  -32,  58,   26,  51 },  {    0,   0,    0,   0 },  {  -93,  60,   48,  29 } } },  /* 73: V JUMP P S A */
    { { {  -10,  21,   95,  23 },  {  -24,  49,   74,  20 },  {  -17,  39,   27,  48 },  {    0,   0,    0,   0 },  {  -84,  62,   43,  30 } } },  /* 74: V JUMP K L A */
    { { {  -46,  21,   66,  23 },  {  -28,  49,   72,  12 },  {  -20,  43,   26,  48 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 75: F JUMP P S A, F JUMP P M A, F JUMP P L A */
    { { {  -46,  21,   66,  23 },  {  -28,  49,   78,  12 },  {  -29,  48,   41,  38 },  {    0,   0,    0,   0 },  {  -53,  26,   43,  20 } } },  /* 76: F JUMP P S A, F JUMP P M A */
    { { {  -51,  21,   63,  23 },  {  -28,  49,   78,  12 },  {  -20,  43,   26,  48 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 77: F JUMP P S A, F JUMP P M A */
    { { {  -28,  21,   81,  23 },  {  -28,  49,   72,  12 },  {  -20,  43,   26,  48 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 78: F JUMP K S A, F JUMP K M A */
    { { {    5,  21,   81,  23 },  {  -28,  49,   72,  12 },  {  -20,  43,   26,  48 },  {    0,   0,    0,   0 },  {  -46,  46,   12,  30 } } },  /* 79: GUARD AIR, F JUMP K S A, F JUMP K M A */
    { { {  -45,  21,   81,  23 },  {  -28,  49,   72,  12 },  {  -66,  53,   36,  39 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 80: GUARD AIR, F JUMP K S A, F JUMP K M A */
    { { {  -47,  21,   62,  23 },  {  -30,  49,   78,  12 },  {  -26,  42,   32,  44 },  {  -35,  47,    5,  27 },  {    0,   0,    0,   0 } } },  /* 81: F JUMP K M B, air Att_KUUCHUUJINNCHUUWATARI (command slot 38), Att_JINNCHUUWATARI (command slot 25) */
    { { {  -51,  21,   63,  23 },  {  -28,  49,   72,  12 },  {  -57,  36,   38,  30 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 82: F JUMP K M B, F JUMP K L A */
    { { {  -51,  21,   63,  23 },  {  -28,  49,   72,  12 },  {  -50,  71,   26,  48 },  {    0,   0,    0,   0 },  {  -92,  70,   32,  27 } } },  /* 83: F JUMP K L A */
    { { {   -5,  21,   39,  23 },  {  -16,  49,   28,  12 },  {  -12,  46,   12,  16 },  {  -29,  64,    0,  14 },  {    0,   0,    0,   0 } } },  /* 84: not used by a script */
    { { {  -13,  21,   62,  23 },  {  -32,  56,   58,  23 },  {  -32,  58,   28,  29 },  {  -35,  64,    0,  27 },  {  -69,  43,   52,   7 } } },  /* 85: UP P GUARD P S, D P GUARD P S */
    { { {  -13,  21,   62,  23 },  {  -28,  49,   52,  12 },  {  -26,  42,   28,  22 },  {  -35,  64,    0,  27 },  {  -36,  49,   60,  10 } } },  /* 86: FUSHIN P S */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -29,  53,    0,  21 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 87: saca 61 */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -24,  42,   28,  18 },  {  -30,  64,    0,  26 },  {    0,   0,    0,   0 } } },  /* 88: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -34,  42,   26,  18 },  {  -36,  64,    0,  26 },  {    0,   0,    0,   0 } } },  /* 89: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    { { {  -33,  42,   52,  18 },  {    0,   0,    0,   0 },  {  -28,  42,   30,  18 },  {  -24,  62,    0,  30 },  {  -40,  18,   25,  31 } } },  /* 90: ATTACK 3 L (Att_SHOURYUUKEN) */
    { { {    0,   0,    0,   0 },  {  -28,  38,   66,  16 },  {  -27,  40,   38,  27 },  {  -14,  50,    0,  38 },  {  -46,  17,   47,  33 } } },  /* 91: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    { { {  -10,  16,   96,  16 },  {  -20,  26,   78,  16 },  {  -26,  38,   52,  24 },  {  -20,  34,   26,  24 },  {    0,   0,    0,   0 } } },  /* 92: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    { { {  -10,  18,  100,  16 },  {  -20,  38,   80,  16 },  {  -24,  48,   52,  24 },  {  -18,  36,    0,  51 },  {    0,   0,    0,   0 } } },  /* 93: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    { { {  -30,  18,   50,  20 },  {  -30,  42,   44,  18 },  {  -24,  40,   28,  20 },  {  -40,  68,    0,  26 },  {    0,   0,    0,   0 } } },  /* 94: ATTACK 4 S (Att_HADOUKEN), ATTACK 4 M (Att_HADOUKEN), ATTACK 4 L (Att_HADOUKEN) +1 */
    { { {  -16,  18,   76,  20 },  {  -24,  34,   58,  16 },  {  -26,  32,   34,  22 },  {  -46,  66,    0,  32 },  {    0,   0,    0,   0 } } },  /* 95: ATTACK 4 S (Att_HADOUKEN), ATTACK 4 M (Att_HADOUKEN), ATTACK 4 L (Att_HADOUKEN) +1 */
    { { {  -34,  18,   70,  20 },  {  -38,  44,   54,  14 },  {  -34,  36,   34,  18 },  {  -52,  82,    0,  33 },  {    0,   0,    0,   0 } } },  /* 96: ATTACK 4 S (Att_HADOUKEN), ATTACK 4 M (Att_HADOUKEN), ATTACK 4 L (Att_HADOUKEN) +1 */
    { { {  -34,  18,   70,  20 },  {  -38,  44,   54,  14 },  {  -34,  36,   34,  18 },  {  -52,  82,    0,  33 },  { -108,  68,   60,  12 } } },  /* 97: ATTACK 4 S (Att_HADOUKEN) */
    { { {  -34,  18,   70,  20 },  {  -38,  44,   54,  14 },  {  -34,  36,   34,  18 },  {  -47,  81,    0,  34 },  {  -85,  55,   59,  35 } } },  /* 98: ATTACK 4 M (Att_HADOUKEN) */
    { { {  -34,  18,   70,  20 },  {  -38,  44,   54,  14 },  {  -34,  36,   34,  18 },  {  -52,  82,    0,  34 },  {  -65,  28,   63,  49 } } },  /* 99: ATTACK 4 L (Att_HADOUKEN), ATTACK 4 SP */
    { { {   -6,  18,   98,  22 },  {  -12,  48,   84,  12 },  {  -18,  46,   62,  20 },  {  -24,  42,   36,  24 },  {    0,   0,    0,   0 } } },  /* 100: ATTACK 5 S (Att_KUUCHUUNICHIRINSHOU), ATTACK 5 M (Att_KUUCHUUNICHIRINSHOU), ATTACK 5 L (Att_KUUCHUUNICHIRINSHOU) +1 */
    { { {  -28,  18,   96,  22 },  {  -32,  48,   84,  12 },  {  -22,  46,   62,  20 },  {  -24,  42,   36,  24 },  {  -98,  40,   64,  18 } } },  /* 101: ATTACK 5 S (Att_KUUCHUUNICHIRINSHOU), ATTACK 5 M (Att_KUUCHUUNICHIRINSHOU), ATTACK 5 L (Att_KUUCHUUNICHIRINSHOU) +1 */
    { { {  -22,  21,   53,  23 },  {  -30,  58,   38,  23 },  {  -43,  72,   16,  20 },  {  -59,  90,    0,  14 },  {  -99,  68,   31,  19 } } },  /* 102: KAGAMI P A */
    { { {  -33,  26,   92,  23 },  {  -64,  94,   61,  30 },  {  -36,  63,   36,  34 },  {    0,   0,    0,   0 },  {  -96,  64,   54,  23 } } },  /* 103: V JUMP P M A, V JUMP P L A, atca 157 */
    { { {  -25,  21,   81,  23 },  {  -24,  49,   74,  20 },  {  -20,  43,   26,  48 },  {    0,   0,    0,   0 },  {  -62,  41,   48,  29 } } },  /* 104: V JUMP K S A, saca 66, V JUMP K M A */
    { { {  -51,  21,   63,  23 },  {  -28,  49,   78,  12 },  {  -20,  43,   26,  48 },  {    0,   0,    0,   0 },  {  -80,  54,   40,  28 } } },  /* 105: F JUMP P M A */
    { { {  -72,  44,   50,  37 },  {  -28,  49,   78,  12 },  {  -29,  48,   41,  38 },  {    0,   0,    0,   0 },  {  -58,  35,    9,  68 } } },  /* 106: F JUMP P L A */
    { { {  -72,  44,   50,  37 },  {  -28,  49,   78,  12 },  {  -29,  48,   41,  38 },  {    0,   0,    0,   0 },  {  -53,  34,   69,  57 } } },  /* 107: F JUMP P L A */
    { { {  -72,  44,   50,  37 },  {  -28,  49,   78,  12 },  {  -29,  48,   41,  38 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 108: F JUMP P L A */
    { { {  -23,  21,   71,  23 },  {  -32,  56,   58,  23 },  {  -32,  58,   28,  29 },  {  -54,  86,    0,  33 },  {  -82,  48,   59,  15 } } },  /* 109: ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN), ATTACK 1 L (Att_HADOUKEN) */
    { { {  -21,  43,   56,  14 },  {  -27,  54,   50,  18 },  {  -27,  55,   35,  15 },  {  -27,  55,   21,  14 },  {    0,   0,    0,   0 } } },  /* 110: AIR S, AIR M, AIR L +38 */
    { { {    2,  21,   55,  23 },  {  -14,  55,   43,  15 },  {  -27,  67,   19,  23 },  {  -46,  85,    0,  19 },  {  -83,  56,    0,  32 } } },  /* 111: KAGAMI K A */
    { { {  -18,  18,   74,  18 },  {  -24,  34,   56,  16 },  {  -26,  38,   32,  22 },  {  -34,  60,    0,  30 },  {    0,   0,    0,   0 } } },  /* 112: not used by a script */
    { { {  -20,  18,   72,  18 },  {  -48,  58,   58,  14 },  {  -26,  38,   32,  24 },  {  -34,  60,    0,  30 },  {  -80,  34,   60,  10 } } },  /* 113: atca 156, saca 56, atca 159 +1 */
    { { {  -20,  18,   72,  18 },  {  -48,  58,   58,  14 },  {  -26,  38,   32,  24 },  {  -34,  60,    0,  30 },  {    0,   0,    0,   0 } } },  /* 114: not used by a script */
    { { {  -10,  21,   95,  23 },  {  -24,  49,   74,  20 },  {  -20,  43,   26,  51 },  {    0,   0,    0,   0 },  { -104,  78,   74,  19 } } },  /* 115: V JUMP P L A */
    { { {  -25,  21,   81,  23 },  {  -24,  49,   74,  20 },  {  -20,  43,   26,  48 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 116: not used by a script */
    { { {  -51,  21,   63,  23 },  {  -28,  49,   72,  12 },  {  -50,  71,   26,  48 },  {    0,   0,    0,   0 },  { -102,  83,   32,  27 } } },  /* 117: not used by a script */
    { { {  -46,  21,   66,  23 },  {  -28,  49,   78,  12 },  {  -29,  48,   41,  38 },  {    0,   0,    0,   0 },  {  -77,  53,   37,  25 } } },  /* 118: F JUMP P S A */
    { { {  -10,  21,   79,  13 },  {  -27,  55,   74,  20 },  {  -20,  43,   29,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 119: Att_JINNCHUUWATARI (command slot 25) */
    { { {  -20,  29,   57,  23 },  {  -29,  59,   45,  25 },  {  -32,  64,   28,  29 },  {  -35,  68,    0,  27 },  {    0,   0,    0,   0 } } },  /* 120: PIYO */
    { { {  -68,  42,   66,  25 },  {  -28,  49,   78,  12 },  {  -29,  48,   41,  38 },  {    0,   0,    0,   0 },  {  -68,  40,   31,  37 } } },  /* 121: not used by a script */
    { { {  -10,  21,   95,  23 },  {  -24,  49,   74,  20 },  {  -20,  43,   26,  51 },  {    0,   0,    0,   0 },  {  -98,  75,   62,  37 } } },  /* 122: atca 157 */
    { { {  -11,  23,   84,  27 },  {  -34,  70,   70,  19 },  {  -32,  66,   42,  28 },  {  -29,  59,    0,  42 },  {    0,   0,    0,   0 } } },  /* 123: ATTACK 6 S (Att_HADOUKEN) */
};

const ATTACK_BOX oro_att_box[60] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {    0,   0,    0,   0 },  {  -61,  22,   82,  14 },  {  -49,  28,   48,  33 } } },  /* 1: S PUNCH A; attack 1 */
    { { {    0,   0,    0,   0 },  {  -97,  16,   51,  13 },  {  -80,  50,   54,   9 } } },  /* 2: S PUNCH B; attack 2 */
    { { {    0,   0,    0,   0 },  { -103,  48,   48,  12 },  {  -53,  18,   53,  14 } } },  /* 3: not used by a script */
    { { {    0,   0,    0,   0 },  {  -91,  34,   71,  15 },  {  -56,  41,   72,  15 } } },  /* 4: M PUNCH B; attack 4 */
    { { {    0,   0,    0,   0 },  {  -53,  21,   50,  14 },  {  -36,  21,   43,   8 } } },  /* 5: M PUNCH A; attack 3 */
    { { {    0,   0,    0,   0 },  {  -30,  17,   99,  33 },  {  -24,  14,   70,  28 } } },  /* 6: M PUNCH A; attack 6 */
    { { {    0,   0,    0,   0 },  {  -50,  15,   59,  22 },  {  -40,  14,   56,  12 } } },  /* 7: L PUNCH A, UP P GUARD P L; attack 7 */
    { { {    0,   0,    0,   0 },  {  -74,  40,   12,  27 },  {  -33,  12,   29,  18 } } },  /* 8: L PUNCH A, UP P GUARD P L; attack 8 */
    { { {    0,   0,    0,   0 },  {  -46,  14,   42,  34 },  {  -35,  19,   57,  36 } } },  /* 9: S KICK A; attack 9 */
    { { {    0,   0,    0,   0 },  {  -78,  10,   44,  18 },  {  -74,  57,   44,  12 } } },  /* 10: S KICK B; attack 10 */
    { { {    0,   0,    0,   0 },  {  -42,  26,   37,  49 },  {    0,   0,    0,   0 } } },  /* 11: M KICK A; attack 11 */
    { { {    0,   0,    0,   0 },  {  -90,  71,   57,  22 },  {    0,   0,    0,   0 } } },  /* 12: UP P GUARD K S; attack 12 */
    { { {    0,   0,    0,   0 },  {  -82,  21,   62,  20 },  {  -60,  41,   62,  19 } } },  /* 13: L KICK A; attack 13 */
    { { {    0,   0,    0,   0 },  {  -96,  10,   29,  13 },  {  -85,  60,   29,  13 } } },  /* 14: KAGAMI P A; attack 15 */
    { { {    0,   0,    0,   0 },  {  -88,  29,   47,  19 },  {  -67,  37,   37,  21 } } },  /* 15: KAGAMI P A; attack 16 */
    { { {    0,   0,    0,   0 },  {  -76,  33,   56,  16 },  {  -43,  35,   45,  19 } } },  /* 16: KAGAMI P A */
    { { {    0,   0,    0,   0 },  {  -47,  18,   74,  14 },  {  -30,  19,   62,  15 } } },  /* 17: not used by a script */
    { { {    0,   0,    0,   0 },  {  -80,  28,    0,  10 },  {  -54,  37,    8,   9 } } },  /* 18: KAGAMI K A; attack 19 */
    { { {    0,   0,    0,   0 },  {  -98,  67,    0,  26 },  {    0,   0,    0,   0 } } },  /* 19: D P GUARD K S, KAGAMI K A; attack 34, 53 */
    { { {    0,   0,    0,   0 },  {  -84,  20,   54,  14 },  {  -65,  28,   65,  13 } } },  /* 20: V JUMP P S A; attack 21 */
    { { {    0,   0,    0,   0 },  {  -54,  16,   55,  16 },  {  -38,  14,   41,  30 } } },  /* 21: V JUMP K S A, saca 66; attack 22, 69 */
    { { {    0,   0,    0,   0 },  {  -65,  25,   56,  23 },  {  -44,  20,   45,  26 } } },  /* 22: V JUMP K M A; attack 23 */
    { { {    0,   0,    0,   0 },  {  -91,  14,   49,  17 },  {  -75,  54,   49,  17 } } },  /* 23: V JUMP K L A; attack 24 */
    { { {    0,   0,    0,   0 },  {  -69,  14,   42,  13 },  {  -54,  31,   47,  14 } } },  /* 24: F JUMP P S A; attack 25 */
    { { {    0,   0,    0,   0 },  {  -69,  13,   35,  26 },  {  -56,  28,   42,  15 } } },  /* 25: F JUMP P M A; attack 26 */
    { { {    0,   0,    0,   0 },  {  -44,  18,   14,  45 },  {    0,   0,    0,   0 } } },  /* 26: F JUMP P L A; attack 27 */
    { { {    0,   0,    0,   0 },  {  -45,  19,   85,  45 },  {    0,   0,    0,   0 } } },  /* 27: F JUMP P L A; attack 28 */
    { { {    0,   0,    0,   0 },  {  -42,  13,   24,  15 },  {    0,   0,    0,   0 } } },  /* 28: F JUMP K S A; attack 29 */
    { { {    0,   0,    0,   0 },  {  -39,  24,   15,  19 },  {  -23,  28,   23,  24 } } },  /* 29: F JUMP K M A; attack 30 */
    { { {    0,   0,    0,   0 },  {  -20,  14,    0,   9 },  {    0,   0,    0,   0 } } },  /* 30: F JUMP K M B, air Att_KUUCHUUJINNCHUUWATARI (command slot 38); attack 31, 61 */
    { { {    0,   0,    0,   0 },  {  -92,  24,   44,  12 },  {  -71,  47,   44,  12 } } },  /* 31: not used by a script */
    { { {    0,   0,    0,   0 },  { -107,  42,   50,  12 },  {  -67,  43,   52,   7 } } },  /* 32: UP P GUARD P S, D P GUARD P S; attack 33 */
    { { {    0,   0,    0,   0 },  {  -89,  42,   61,  12 },  {  -60,  43,   63,   7 } } },  /* 33: FUSHIN P S; attack 33 */
    { { {    0,   0,    0,   0 },  {  -62,  50,   26,  37 },  {  -54,  42,   12,  14 } } },  /* 34: ATTACK 3 L (Att_SHOURYUUKEN); attack 39 */
    { { {    0,   0,    0,   0 },  {  -61,  60,   58,  35 },  {  -54,  28,   38,  22 } } },  /* 35: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1; attack 35, 37, 40, 71 */
    { { {    0,   0,    0,   0 },  {  -29,  23,  108,  28 },  {  -44,  31,   82,  30 } } },  /* 36: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1; attack 36, 38, 40, 71 */
    { { {    0,   0,    0,   0 },  {  -76,  32,   60,   8 },  {  -65,  36,   60,   8 } } },  /* 37: not used by a script */
    { { {    0,   0,    0,   0 },  {  -60,  12,   70,   8 },  {  -48,  11,   62,   9 } } },  /* 38: not used by a script */
    { { {    0,   0,    0,   0 },  {  -56,  10,   88,   8 },  {  -46,  10,   71,  16 } } },  /* 39: not used by a script */
    { { {    0,   0,    0,   0 },  {  -88,  13,   66,   7 },  {  -77,  14,   70,   8 } } },  /* 40: not used by a script */
    { { { -103,  71,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 41: ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN), ATTACK 1 L (Att_HADOUKEN); attack 50 */
    { { {    0,   0,    0,   0 },  { -102,  20,   27,  18 },  {  -82,  61,   27,  18 } } },  /* 42: KAGAMI P A; attack 52 */
    { { {    0,   0,    0,   0 },  {  -90,  43,    0,  10 },  {  -54,  45,    8,  15 } } },  /* 43: KAGAMI K A; attack 20 */
    { { {    0,   0,    0,   0 },  {  -96,  27,   48,  19 },  {  -79,  31,   58,  17 } } },  /* 44: V JUMP P M A; attack 54 */
    { { {  -35,   6,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 45: M PUNCH A, M PUNCH B, M KICK A +3; attack 46, 50, 66 */
    { { {  -92,  56,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 46: atca 159, saca 56; attack 58 */
    { { {  -29,  24,   60,  38 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 47: V JUMP P L A, F JUMP P L A; attack 65 */
    { { {    0,   0,    0,   0 },  {  -29,  46,   99,  31 },  {    0,   0,    0,   0 } } },  /* 48: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1; attack 41, 71 */
    { { {    0,   0,    0,   0 },  {  -51,  33,   31,  57 },  {    0,   0,    0,   0 } } },  /* 49: not used by a script */
    { { {    0,   0,    0,   0 },  {  -41,  40,    0,   9 },  {    0,   0,    0,   0 } } },  /* 50: Att_JINNCHUUWATARI (command slot 25); attack 67, 68, 72, 73 ... */
    { { {    0,   0,    0,   0 },  {  -89,  73,   59,  16 },  {    0,   0,    0,   0 } } },  /* 51: M KICK B, UP P GUARD K S; attack 12 */
    { { {    0,   0,    0,   0 },  {  -83,  21,   65,  20 },  {  -60,  47,   68,  15 } } },  /* 52: not used by a script */
    { { {    0,   0,    0,   0 },  { -100,  38,   70,  15 },  {  -60,  35,   77,   8 } } },  /* 53: V JUMP P L A; attack 55 */
    { { {    0,   0,    0,   0 },  {  -88,  14,   40,  14 },  {  -73,  49,   39,  17 } } },  /* 54: F JUMP K L A; attack 32 */
    { { {  -39,  10,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 55: L PUNCH A, L KICK A; attack 46, 66 */
    { { {  -65,  42,   72,  22 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 56: atca 157; attack 62 */
    { { {  -57,  21,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 57: atca 156, saca 56; attack 58 */
    { { {  -66,  35,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 58: atca 158, saca 56; attack 58 */
    { { {    0,   0,    0,   0 },  {  -50,  27,    0,  29 },  {  -55,  27,   27,  15 } } },  /* 59: not used by a script */
};

const CAUGHT_BOX oro_cau_box[12] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -29,   59,    0,   16 } },  /* 1: KAMAE, HURIMUKI, DASH HUMIKOMI +101 */
    { {  -43,   50,    0,   16 } },  /* 2: DASH HUMIKOMI */
    { {  -33,   63,    0,    8 } },  /* 3: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +21 */
    { {  -23,   46,   39,   47 } },  /* 4: JUMP FRONT, JUMP BACK, SP JUMP FRONT +31 */
    { {  -25,   50,   31,   58 } },  /* 5: not used by a script */
    { {  -29,   59,    0,   16 } },  /* 6: M KICK B, UP P GUARD K S */
    { {  -23,   46,   39,   47 } },  /* 7: not used by a script */
    { {  -25,   50,   31,   58 } },  /* 8: not used by a script */
    { {  -21,   49,   22,   45 } },  /* 9: AIR S, AIR M, AIR L +38 */
    { {  -24,   48,   28,   51 } },  /* 10: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    { {  -37,   67,    0,    8 } },  /* 11: KAGAMI P A, KAGAMI K A */
};

const HOSEI_BOX oro_hos_box[21] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -29,   59,    0,   79 } },  /* 1: KAMAE, HURIMUKI, DASH HUMIKOMI +97 */
    { {  -43,   50,    0,   64 } },  /* 2: DASH HUMIKOMI */
    { {  -29,   59,    0,   44 } },  /* 3: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +33 */
    { {  -23,   46,   39,   47 } },  /* 4: JUMP FRONT, JUMP BACK, SP JUMP FRONT +36 */
    { {  -25,   50,   31,   58 } },  /* 5: not used by a script */
    { {  -14,   50,   28,   40 } },  /* 6: not used by a script */
    { {  -16,   50,   28,   60 } },  /* 7: not used by a script */
    { {  -28,   50,   28,   60 } },  /* 8: not used by a script */
    { {  -16,   50,   22,   34 } },  /* 9: not used by a script */
    { {  -28,   50,   31,   47 } },  /* 10: not used by a script */
    { {  -28,   50,   51,   47 } },  /* 11: not used by a script */
    { {  -24,   48,    0,   57 } },  /* 12: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    { {  -28,   56,    0,   65 } },  /* 13: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    { {  -24,   48,   28,   51 } },  /* 14: OKIAGARI P S, ATTACK 3 S (Att_SHOURYUUKEN), ATTACK 3 M (Att_SHOURYUUKEN) +1 */
    { {  -26,   44,    0,   25 } },  /* 15: saca 61, OKIAGARI F, OKIAGARI B +2 */
    { {  -43,   64,    0,   55 } },  /* 16: DASH HUMIKOMI */
    { {  -43,   79,   20,   34 } },  /* 17: not used by a script */
    { {  -21,   49,   22,   45 } },  /* 18: AIR S, AIR M, AIR L +38 */
    { {  -29,   59,    0,   60 } },  /* 19: PIYO */
    { {  -29,   59,    0,   30 } },  /* 20: NEKOROBI S */
};
