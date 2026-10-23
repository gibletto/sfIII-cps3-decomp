/*
 * RYU_HITBOX.C  Ryu's hit boxes
 *
 * Each of Ryu's animation frames names a row of ryu_hit_ix_table (a frame line's hit field). The
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
 * rows of ryu_catt_table dealt through it. Row 0 of a box table is no box.
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

const HIT_IX ryu_hit_ix_table[188] = {
    /* boix  atix  cuix  hoix */
    {    0,    0,    0,    0 },  /* 0: NAGERARE KAIHI, OKIAGARI, OKIAGARI F +18 */
    {    1,    0,    1,    1 },  /* 1: KAMAE, HURIMUKI, FRONT WALK +94 */
    {    2,    0,    2,    2 },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +18 */
    {  122,    0,    0,    2 },  /* 3: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +1 */
    {  122,    1,    0,    2 },  /* 4: ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 6 S (Att_SHINSHOURYUUKEN) */
    {    0,    1,    0,    4 },  /* 5: ATTACK 6 S (Att_SHINSHOURYUUKEN) */
    {    3,    2,    0,    4 },  /* 6: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +1 */
    {    3,    0,    3,    4 },  /* 7: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) */
    {    4,    0,    3,    4 },  /* 8: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +1 */
    {    5,    0,   22,   21 },  /* 9: DASH HUMIKOMI, DASH TOBINOKI */
    {    6,    0,    1,    1 },  /* 10: DASH TOBINOKI */
    {    7,    0,    3,    3 },  /* 11: GUARD AIR, V JUMP P M A, V JUMP K S A +10 */
    {    8,    0,    3,    3 },  /* 12: not used by a script */
    {    9,    0,    3,    3 },  /* 13: not used by a script */
    {   10,    0,    4,    4 },  /* 14: JUMP FRONT, JUMP BACK, SP JUMP FRONT +3 */
    {   11,    0,    4,    4 },  /* 15: JUMP JUNBI, SP JUMP JUNBI, JUMP VERTICAL +9 */
    {   12,    0,    4,    4 },  /* 16: JUMP VERTICAL, S JUMP FRONT, SP JUMP V +1 */
    {   13,    0,    3,    3 },  /* 17: not used by a script */
    {   14,    0,    3,    3 },  /* 18: not used by a script */
    {   15,    0,    3,    3 },  /* 19: not used by a script */
    {  109,    4,    1,    1 },  /* 20: S PUNCH A */
    {   16,    0,    1,    1 },  /* 21: S PUNCH A */
    {   17,    5,    1,    1 },  /* 22: S PUNCH B */
    {   17,    0,    1,    1 },  /* 23: S PUNCH B */
    {  110,    6,    1,    1 },  /* 24: M PUNCH A, UP P GUARD P M */
    {   18,    0,    1,    1 },  /* 25: L PUNCH A, V JUMP P S A, atca 108 +2 */
    {   19,    7,    1,    1 },  /* 26: M PUNCH B, UP P GUARD P S */
    {   19,    0,    1,    1 },  /* 27: M PUNCH B, UP P GUARD P S */
    {   20,    0,    1,    1 },  /* 28: M PUNCH B, UP P GUARD P S */
    {   21,    0,    1,    1 },  /* 29: atca 156 */
    {   22,    8,    1,    1 },  /* 30: L PUNCH A, atca 156 */
    {   23,    9,    1,    1 },  /* 31: L PUNCH A, atca 156 */
    {   24,    0,    1,    1 },  /* 32: L PUNCH A, atca 156 */
    {   25,    0,    1,    1 },  /* 33: L PUNCH B, UP P GUARD P L */
    {   26,   10,    1,    1 },  /* 34: UP P GUARD P L */
    {   27,   10,    1,    1 },  /* 35: L PUNCH B, UP P GUARD P L */
    {   27,    0,    1,    1 },  /* 36: not used by a script */
    {   28,    0,    1,    1 },  /* 37: L PUNCH B, atca 157, UP P GUARD P L */
    {   29,    0,    1,    1 },  /* 38: L PUNCH B, UP P GUARD P L */
    {   30,    0,    9,    1 },  /* 39: S KICK A */
    {   31,   11,    9,    1 },  /* 40: S KICK A */
    {   31,    0,    9,    1 },  /* 41: S KICK A */
    {   32,    0,    1,    1 },  /* 42: not used by a script */
    {   33,    0,    1,    1 },  /* 43: not used by a script */
    {   34,   12,    1,    1 },  /* 44: not used by a script */
    {   34,    0,    1,    1 },  /* 45: not used by a script */
    {   35,    0,    1,    1 },  /* 46: M KICK A */
    {   36,    0,    1,    1 },  /* 47: not used by a script */
    {   37,   13,    1,    1 },  /* 48: M KICK A */
    {   37,    0,    1,    1 },  /* 49: not used by a script */
    {   38,    0,    1,    1 },  /* 50: not used by a script */
    {   39,    0,    1,    1 },  /* 51: not used by a script */
    {   40,   14,    1,    1 },  /* 52: M KICK B, UP P GUARD K S */
    {   40,   57,    1,    1 },  /* 53: M KICK B, UP P GUARD K S */
    {   41,    0,    1,    1 },  /* 54: M KICK B, UP P GUARD K S */
    {   42,    0,    1,    1 },  /* 55: not used by a script */
    {   43,    0,    1,    1 },  /* 56: not used by a script */
    {   44,    0,    1,    1 },  /* 57: not used by a script */
    {   45,    0,    1,    1 },  /* 58: not used by a script */
    {   46,   15,    1,    1 },  /* 59: not used by a script */
    {   47,   16,    1,    1 },  /* 60: not used by a script */
    {   48,   17,    1,    1 },  /* 61: not used by a script */
    {   49,   40,    1,    1 },  /* 62: not used by a script */
    {   50,    0,    1,    1 },  /* 63: not used by a script */
    {   51,    0,    1,    1 },  /* 64: not used by a script */
    {   52,    0,    1,    1 },  /* 65: L KICK A, atca 157 */
    {   53,    0,    1,    1 },  /* 66: L KICK A, atca 157 */
    {   54,    0,    1,    1 },  /* 67: L KICK A, atca 157 */
    {   54,   18,    1,    1 },  /* 68: not used by a script */
    {   55,   19,    1,    1 },  /* 69: L KICK A, atca 157 */
    {   56,    0,    1,    1 },  /* 70: L KICK A, atca 157 */
    {   57,    0,    1,    1 },  /* 71: L KICK A, atca 157 */
    {   58,    0,    1,    1 },  /* 72: not used by a script */
    {   59,    0,    1,   19 },  /* 73: not used by a script */
    {   60,    0,    1,   10 },  /* 74: TOUKETSU A */
    {   61,   20,    1,   11 },  /* 75: not used by a script */
    {   61,    0,    1,   11 },  /* 76: not used by a script */
    {   62,    0,    1,   11 },  /* 77: not used by a script */
    {   63,    0,    1,   11 },  /* 78: not used by a script */
    {   64,   21,    8,    2 },  /* 79: KAGAMI P A */
    {   64,    0,    8,    2 },  /* 80: KAGAMI P A */
    {   65,   22,    2,    2 },  /* 81: KAGAMI P A */
    {   65,    0,    2,    2 },  /* 82: KAGAMI P A */
    {   66,    0,    2,    2 },  /* 83: KAGAMI P A */
    {   67,   23,    2,    2 },  /* 84: KAGAMI P A */
    {   68,   24,    2,    2 },  /* 85: KAGAMI P A */
    {   69,    0,    2,    2 },  /* 86: KAGAMI P A */
    {   68,    0,    2,    2 },  /* 87: not used by a script */
    {   70,    0,    2,    2 },  /* 88: KAGAMI P A */
    {   71,    0,    8,    2 },  /* 89: KAGAMI K A */
    {   72,   25,    8,    2 },  /* 90: KAGAMI K A */
    {   72,    0,    8,    2 },  /* 91: not used by a script */
    {   73,    0,    2,    2 },  /* 92: KAGAMI K A */
    {   74,   26,    2,    2 },  /* 93: KAGAMI K A */
    {   74,    0,    2,    2 },  /* 94: not used by a script */
    {   75,    0,    2,    2 },  /* 95: not used by a script */
    {   76,    0,    2,    2 },  /* 96: KAGAMI K A */
    {   77,   27,    2,    2 },  /* 97: KAGAMI K A */
    {   77,    0,    2,    2 },  /* 98: KAGAMI K A */
    {   78,    0,    4,    4 },  /* 99: V JUMP P S A, F JUMP P S A, atca 108 */
    {   78,   28,    4,   16 },  /* 100: V JUMP P S A, F JUMP P S A, atca 108 */
    {    7,    0,    4,    4 },  /* 101: V JUMP K M A, F JUMP P M A, atca 110 +1 */
    {   96,   51,    4,    4 },  /* 102: V JUMP P M A */
    {   96,   58,    4,    4 },  /* 103: not used by a script */
    {   81,   30,    4,    4 },  /* 104: V JUMP K M A, atca 116 */
    {   81,    0,    4,    4 },  /* 105: V JUMP K M A, atca 116 */
    {   77,   56,   10,    2 },  /* 106: not used by a script */
    {   96,   51,    3,    3 },  /* 107: F JUMP P L A */
    {   82,   33,    3,    3 },  /* 108: V JUMP K S A, F JUMP K S A, atca 114 */
    {   82,    0,    3,    3 },  /* 109: V JUMP K S A, F JUMP K S A, atca 114 */
    {   83,   34,    3,    3 },  /* 110: F JUMP K M A */
    {   83,    0,    3,    3 },  /* 111: F JUMP K M A, F JUMP K L A, atca 118 */
    {    0,   35,    0,    2 },  /* 112: not used by a script */
    {  121,   36,    4,    3 },  /* 113: F JUMP P M A, atca 110 */
    {   84,   37,    4,    4 },  /* 114: V JUMP K L A */
    {   84,    0,    4,    4 },  /* 115: V JUMP K L A */
    {   85,    0,   16,   19 },  /* 116: HANASARE, ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN) +3 */
    {   86,    0,   16,   19 },  /* 117: HANASARE, ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN) +7 */
    {    0,    0,    1,   20 },  /* 118: exca 17, saca 48 */
    {   88,    0,    1,    1 },  /* 119: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +1 */
    {   89,    0,    1,    1 },  /* 120: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +1 */
    {   90,    0,   12,   18 },  /* 121: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +4 */
    {   97,   38,   12,   18 },  /* 122: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +4 */
    {    1,    0,    1,    1 },  /* 123: GUARD HEAD */
    {    1,    0,    1,    1 },  /* 124: GUARD UP */
    {    2,    0,    2,    2 },  /* 125: GUARD DOWN */
    {    0,    0,    0,    2 },  /* 126: OKIAGARI, OKIAGARI F, OKIAGARI B +17 */
    {    0,    0,    0,    2 },  /* 127: not used by a script */
    {    1,   41,    1,    1 },  /* 128: M PUNCH A, M PUNCH B, M PUNCH C +4 */
    {  107,   42,    1,    1 },  /* 129: M PUNCH C */
    {  112,   43,    1,    1 },  /* 130: M PUNCH C */
    {    7,   44,    4,   16 },  /* 131: F JUMP P M A, atca 110 */
    {   97,    0,   12,   18 },  /* 132: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +3 */
    {   98,   39,   12,   18 },  /* 133: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +3 */
    {   98,    0,   12,   18 },  /* 134: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +3 */
    {   99,    0,    1,    1 },  /* 135: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    {  100,    0,   20,    6 },  /* 136: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    {  101,    0,   20,    6 },  /* 137: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    {  102,    0,    1,    1 },  /* 138: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    {  103,   46,    1,    1 },  /* 139: UP P GUARD K L */
    {  103,   47,    1,    1 },  /* 140: UP P GUARD K L */
    {  103,    0,    1,    1 },  /* 141: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    {  104,    0,    1,    1 },  /* 142: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    {  105,    0,    1,    1 },  /* 143: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    {    1,    0,    1,    1 },  /* 144: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    {  111,   48,    3,    3 },  /* 145: F JUMP K L A, atca 118 */
    {  108,    0,    1,    1 },  /* 146: M PUNCH A, UP P GUARD P M */
    {  106,    0,    1,    1 },  /* 147: M PUNCH C */
    {   54,   49,    1,    1 },  /* 148: atca 157 */
    {  116,    0,   14,   23 },  /* 149: FUSHIN P S */
    {  117,   50,   14,   23 },  /* 150: FUSHIN P S */
    {    7,    0,   13,   22 },  /* 151: AIR S, AIR M, AIR L +33 */
    {   96,   51,    3,    3 },  /* 152: not used by a script */
    {    0,   52,    0,    1 },  /* 153: ATTACK 6 S (Att_SHINSHOURYUUKEN) */
    {    0,   53,    0,    1 },  /* 154: ATTACK 6 S (Att_SHINSHOURYUUKEN) */
    {    0,   54,    0,   17 },  /* 155: ATTACK 6 S (Att_SHINSHOURYUUKEN) */
    {    0,    0,    0,    1 },  /* 156: not used by a script */
    {    0,   55,    0,   17 },  /* 157: ATTACK 6 S (Att_SHINSHOURYUUKEN) */
    {    7,    0,    4,    4 },  /* 158: not used by a script */
    {  118,    0,    4,    4 },  /* 159: V JUMP P L A, atca 112 */
    {  119,   29,    4,    4 },  /* 160: V JUMP P L A, atca 112 */
    {  120,   60,    4,    4 },  /* 161: V JUMP K M A, atca 116 */
    {    0,    0,    0,    4 },  /* 162: AIR S, AIR M, AIR L +2 */
    {    0,    0,    1,    1 },  /* 163: not used by a script */
    {    0,    0,    0,   19 },  /* 164: not used by a script */
    {    0,    0,    0,   15 },  /* 165: ATTACK 4 S (Att_HADOUKEN), ATTACK 4 M (Att_HADOUKEN), ATTACK 4 L (Att_HADOUKEN) +2 */
    {   74,    0,    2,    2 },  /* 166: KAGAMI K A */
    {   72,    0,    8,    2 },  /* 167: KAGAMI K A */
    {    1,   61,    1,    1 },  /* 168: L PUNCH A, L PUNCH B, L KICK A */
    {  122,    0,    0,    1 },  /* 169: not used by a script */
    {  123,   62,    3,    3 },  /* 170: saca 56 */
    {  124,    0,    1,    1 },  /* 171: PIYO */
    {  125,    0,    1,    1 },  /* 172: PIYO */
    {   22,   63,    1,    1 },  /* 173: L PUNCH A */
    {    0,    0,    0,   25 },  /* 174: NEKOROBI S */
    {  126,    0,   20,    2 },  /* 175: OKIAGARI P S */
    {  126,   64,   20,    1 },  /* 176: OKIAGARI P S */
    {  127,   65,   21,    4 },  /* 177: OKIAGARI P S */
    {  128,    0,   21,    4 },  /* 178: OKIAGARI P S */
    {  129,    1,    0,    2 },  /* 179: ATTACK 2 L (Att_SHOURYUUKEN) */
    {    1,    0,    0,    1 },  /* 180: HANASARE */
    {    2,    0,    0,    2 },  /* 181: HANASARE */
    {   98,   66,   12,   18 },  /* 182: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    {    1,    0,    1,    0 },  /* 183: LOSE SONABA */
    {  103,   47,    1,    1 },  /* 184: Att_HADOUKEN2 (command slot 25) */
    {  103,   67,    1,    1 },  /* 185: Att_HADOUKEN2 (command slot 25) */
    {  103,   46,    1,    1 },  /* 186: Att_HADOUKEN2 (command slot 25) */
    {  130,    1,    0,    2 },  /* 187: ATTACK 2 S (Att_SHOURYUUKEN) */
};

const BODY_BOX ryu_body_box[131] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {  -14,  21,   84,  18 },  {  -29,  59,   81,   7 },  {  -29,  59,   32,  49 },  {  -35,  72,    0,  31 },  {    0,   0,    0,   0 } } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +96 */
    { { {  -15,  21,   50,  18 },  {  -30,  58,   43,  13 },  {  -29,  58,   26,  20 },  {  -38,  72,    0,  30 },  {    0,   0,    0,   0 } } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +19 */
    { { {   -1,  18,   96,  16 },  {  -20,  44,   81,  14 },  {  -16,  32,   63,  18 },  {  -22,  42,   37,  27 },  {  -21,  17,   97,  26 } } },  /* 3: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +1 */
    { { {   -4,  18,  102,  16 },  {  -24,  44,   90,  14 },  {  -24,  46,   61,  31 },  {  -18,  42,   -3,  73 },  {    0,   0,    0,   0 } } },  /* 4: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +1 */
    { { {  -16,  23,   78,  16 },  {  -25,  53,   62,  20 },  {  -24,  40,   37,  29 },  {  -38,  66,    0,  35 },  {    0,   0,    0,   0 } } },  /* 5: DASH HUMIKOMI, DASH TOBINOKI */
    { { {   -5,  23,   78,  16 },  {  -25,  53,   67,  20 },  {  -18,  43,   36,  29 },  {  -33,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 6: DASH TOBINOKI */
    { { {  -19,  39,   92,  16 },  {  -32,  64,   78,  15 },  {  -30,  59,   42,  37 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 7: GUARD AIR, V JUMP P M A, V JUMP K S A +48 */
    { { {  -28,  54,   39,  40 },  {  -23,  53,   75,  20 },  {  -28,  54,   39,  40 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 8: not used by a script */
    { { {  -42,  31,   52,  21 },  {  -33,  60,   75,  20 },  {  -25,  52,   36,  37 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 9: not used by a script */
    { { {    0,   0,    0,   0 },  {  -34,  69,   42,  53 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 10: JUMP FRONT, JUMP BACK, SP JUMP FRONT +3 */
    { { {  -11,  23,  106,  16 },  {  -23,  53,   90,  20 },  {  -19,  43,   45,  49 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 11: JUMP JUNBI, SP JUMP JUNBI, JUMP VERTICAL +9 */
    { { {  -18,  23,   99,  16 },  {  -23,  53,   90,  20 },  {  -31,  63,   44,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 12: JUMP VERTICAL, S JUMP FRONT, SP JUMP V +1 */
    { { {  -13,  27,   93,  17 },  {  -22,  57,   76,  20 },  {  -29,  57,   40,  38 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 13: not used by a script */
    { { {  -11,  49,   81,  19 },  {  -39,  79,   42,  52 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 14: not used by a script */
    { { {  -22,  57,   76,  20 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 15: not used by a script */
    { { {  -23,  23,   78,  16 },  {  -31,  53,   63,  20 },  {  -18,  43,   36,  29 },  {  -25,  55,    0,  35 },  {  -42,  12,   70,  20 } } },  /* 16: S PUNCH A */
    { { {  -14,  21,   84,  18 },  {  -28,  58,   69,  22 },  {  -21,  49,   38,  31 },  {  -28,  63,    0,  38 },  {  -73,  51,   66,  30 } } },  /* 17: S PUNCH B */
    { { {  -30,  23,   82,  16 },  {  -36,  53,   66,  20 },  {  -32,  43,   36,  29 },  {  -32,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 18: L PUNCH A, V JUMP P S A, atca 108 +2 */
    { { {  -27,  23,   79,  16 },  {  -45,  69,   63,  21 },  {  -32,  52,   36,  29 },  {  -42,  74,    0,  41 },  {  -70,  59,   64,  18 } } },  /* 19: M PUNCH B, UP P GUARD P S */
    { { {  -20,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -32,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 20: M PUNCH B, UP P GUARD P S */
    { { {  -20,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -32,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 21: atca 156 */
    { { {  -29,  34,   83,  16 },  {  -32,  54,   67,  20 },  {  -26,  43,   36,  29 },  {  -33,  62,    0,  35 },  {  -50,  32,   46,  29 } } },  /* 22: L PUNCH A, atca 156 */
    { { {  -29,  34,   83,  16 },  {  -32,  54,   67,  20 },  {  -26,  43,   36,  29 },  {  -33,  62,    0,  35 },  {  -50,  32,   46,  51 } } },  /* 23: L PUNCH A, atca 156 */
    { { {  -29,  34,   83,  16 },  {  -32,  54,   67,  20 },  {  -26,  43,   36,  29 },  {  -33,  62,    0,  35 },  {  -49,  46,   57,  54 } } },  /* 24: L PUNCH A, atca 156 */
    { { {  -21,  38,   83,  16 },  {  -29,  55,   67,  20 },  {  -21,  44,   47,  22 },  {  -35,  61,    0,  47 },  {    0,   0,    0,   0 } } },  /* 25: L PUNCH B, UP P GUARD P L */
    { { {  -20,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -35,  61,    0,  35 },  {  -57,  33,   74,  14 } } },  /* 26: UP P GUARD P L */
    { { {   -6,  26,   82,  16 },  {  -25,  49,   67,  20 },  {  -20,  43,   36,  29 },  {  -36,  80,    0,  35 },  {  -68,  45,   60,  40 } } },  /* 27: L PUNCH B, UP P GUARD P L */
    { { {    0,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -35,  61,    0,  35 },  {    0,   0,    0,   0 } } },  /* 28: L PUNCH B, atca 157, UP P GUARD P L */
    { { {  -14,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -35,  61,    0,  35 },  {    0,   0,    0,   0 } } },  /* 29: L PUNCH B, UP P GUARD P L */
    { { {  -14,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -25,  28,    0,  35 },  {    0,   0,    0,   0 } } },  /* 30: S KICK A */
    { { {  -24,  31,   84,  16 },  {  -32,  51,   67,  20 },  {  -35,  56,   36,  29 },  {  -44,  56,    0,  35 },  {  -71,  47,   11,  44 } } },  /* 31: S KICK A */
    { { {    7,  23,   83,  16 },  {   -5,  53,   67,  20 },  {   -6,  43,   36,  29 },  {   10,  26,    0,  35 },  {    0,   0,    0,   0 } } },  /* 32: not used by a script */
    { { {   21,  23,   83,  16 },  {    6,  53,   67,  20 },  {   -6,  43,   36,  29 },  {   10,  26,    0,  35 },  {    0,   0,    0,   0 } } },  /* 33: not used by a script */
    { { {   21,  23,   83,  16 },  {    6,  53,   67,  20 },  {   -6,  43,   36,  29 },  {   10,  26,    0,  35 },  {  -49,  50,   60,  12 } } },  /* 34: not used by a script */
    { { {  -33,  23,   86,  15 },  {  -41,  52,   72,  14 },  {  -56,  63,   41,  30 },  {  -47,  55,    0,  42 },  {    0,   0,    0,   0 } } },  /* 35: M KICK A */
    { { {  -33,  23,   83,  16 },  {  -31,  43,   67,  20 },  {  -19,  29,   36,  30 },  {  -47,  55,    0,  42 },  {    0,   0,    0,   0 } } },  /* 36: not used by a script */
    { { {  -39,  31,   89,  16 },  {  -48,  53,   73,  20 },  {  -33,  38,   43,  31 },  {  -47,  55,    0,  42 },  {  -68,  38,   14,  53 } } },  /* 37: M KICK A */
    { { {  -26,  23,   83,  16 },  {  -33,  43,   68,  20 },  {  -25,  29,   35,  30 },  {  -33,  28,    0,  35 },  {    0,   0,    0,   0 } } },  /* 38: not used by a script */
    { { {   -2,  23,   87,  16 },  {  -12,  53,   67,  20 },  {  -13,  43,   36,  29 },  {   -9,  33,    0,  37 },  {    0,   0,    0,   0 } } },  /* 39: not used by a script */
    { { {    7,  31,   82,  16 },  {  -16,  77,   59,  25 },  {  -39,  67,   46,  18 },  {  -28,  63,    0,  38 },  {  -98,  82,   55,  19 } } },  /* 40: M KICK B, UP P GUARD K S */
    { { {   -5,  23,   82,  16 },  {  -16,  47,   67,  20 },  {  -25,  43,   37,  29 },  {  -20,  33,    0,  37 },  {  -59,  42,   45,  22 } } },  /* 41: M KICK B, UP P GUARD K S */
    { { {   14,  23,   82,  16 },  {    3,  53,   67,  20 },  {   -8,  43,   36,  29 },  {    8,  33,    0,  37 },  {    0,   0,    0,   0 } } },  /* 42: not used by a script */
    { { {  -32,  23,   82,  16 },  {  -46,  53,   67,  20 },  {  -39,  43,   36,  29 },  {  -43,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 43: not used by a script */
    { { {  -35,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {    0,   0,    0,   0 } } },  /* 44: not used by a script */
    { { {  -35,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {   50,  19,   75,  27 } } },  /* 45: not used by a script */
    { { {  -35,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {  -55,  19,   57,  27 } } },  /* 46: not used by a script */
    { { {  -35,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {  -64,  19,   62,  27 } } },  /* 47: not used by a script */
    { { {  -35,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {  -85,  48,   63,  19 } } },  /* 48: not used by a script */
    { { {  -20,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {  -85,  48,   51,  19 } } },  /* 49: not used by a script */
    { { {  -20,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {    0,   0,    0,   0 } } },  /* 50: not used by a script */
    { { {  -31,  23,   88,  16 },  {  -44,  46,   67,  20 },  {  -39,  43,   36,  29 },  {  -43,  50,    0,  35 },  {    0,   0,    0,   0 } } },  /* 51: not used by a script */
    { { {   -5,  23,   77,  16 },  {  -25,  53,   67,  20 },  {  -29,  45,   36,  29 },  {  -25,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 52: L KICK A, atca 157 */
    { { {    2,  23,   77,  16 },  {  -27,  60,   61,  20 },  {  -35,  60,   39,  29 },  {  -25,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 53: L KICK A, atca 157 */
    { { {    2,  23,   77,  16 },  {  -27,  60,   61,  20 },  {  -35,  54,   39,  29 },  {  -26,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 54: L KICK A, atca 157 */
    { { {    7,  23,   77,  16 },  {  -30,  63,   61,  20 },  {  -45,  73,   35,  26 },  {  -46,  72,    0,  35 },  {  -72,  30,   54,  57 } } },  /* 55: L KICK A, atca 157 */
    { { {   -1,  23,   77,  16 },  {  -14,  36,   57,  20 },  {  -45,  73,   35,  26 },  {  -46,  72,    0,  35 },  {  -87,  61,   58,  21 } } },  /* 56: L KICK A, atca 157 */
    { { {  -11,  23,   78,  16 },  {  -35,  60,   61,  21 },  {  -34,  59,   34,  29 },  {  -33,  58,    0,  46 },  {  -54,  37,   26,  37 } } },  /* 57: L KICK A, atca 157 */
    { { {   -4,  23,   90,  16 },  {  -25,  53,   67,  20 },  {  -18,  43,   36,  29 },  {  -25,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 58: not used by a script */
    { { {    6,  23,   86,  16 },  {  -14,  53,   67,  20 },  {  -18,  43,   36,  29 },  {  -25,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 59: not used by a script */
    { { {   20,  23,   77,  16 },  {  -14,  53,   67,  20 },  {  -18,  43,   36,  29 },  {  -25,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 60: TOUKETSU A */
    { { {   37,  23,   65,  16 },  {    4,  53,   54,  20 },  {  -14,  43,   36,  29 },  {  -15,  36,    0,  35 },  {  -32,  38,   65,  11 } } },  /* 61: not used by a script */
    { { {   37,  23,   65,  16 },  {    4,  53,   54,  20 },  {  -14,  43,   36,  29 },  {  -15,  36,    0,  35 },  {    0,   0,    0,   0 } } },  /* 62: not used by a script */
    { { {   32,  23,   78,  16 },  {    4,  53,   64,  20 },  {  -14,  43,   36,  29 },  {  -15,  36,    0,  35 },  {    0,   0,    0,   0 } } },  /* 63: not used by a script */
    { { {  -23,  26,   48,  18 },  {  -30,  58,   43,  18 },  {  -18,  43,   20,  26 },  {  -42,  70,    0,  58 },  {  -72,  52,   34,  22 } } },  /* 64: KAGAMI P A */
    { { {  -14,  23,   50,  16 },  {  -21,  43,   37,  18 },  {  -18,  43,   20,  26 },  {  -42,  70,    0,  58 },  {  -63,  41,   37,  19 } } },  /* 65: KAGAMI P A */
    { { {  -14,  23,   50,  16 },  {  -21,  43,   37,  18 },  {  -18,  43,   20,  26 },  {  -42,  70,    0,  58 },  {    0,   0,    0,   0 } } },  /* 66: KAGAMI P A */
    { { {  -24,  25,   70,  19 },  {  -37,  63,   61,  18 },  {    0,   0,    0,   0 },  {  -47,  74,    0,  60 },  {  -52,  24,   27,  33 } } },  /* 67: KAGAMI P A */
    { { {   -5,  23,   80,  16 },  {  -26,  62,   66,  18 },  {  -18,  43,   37,  29 },  {  -48,  78,    0,  52 },  {  -43,  43,   40,  76 } } },  /* 68: KAGAMI P A */
    { { {   -7,  23,   75,  16 },  {  -18,  44,   60,  18 },  {  -19,  43,   37,  29 },  {  -42,  70,    0,  58 },  {  -35,  33,   51,  59 } } },  /* 69: KAGAMI P A */
    { { {   -8,  23,   69,  16 },  {  -17,  36,   53,  18 },  {  -21,  43,   31,  29 },  {  -42,  70,    0,  58 },  {    0,   0,    0,   0 } } },  /* 70: KAGAMI P A */
    { { {  -15,  21,   50,  18 },  {  -30,  58,   43,  13 },  {  -29,  58,   26,  20 },  {  -38,  72,    0,  30 },  {    0,   0,    0,   0 } } },  /* 71: KAGAMI K A */
    { { {   -4,  34,   43,  18 },  {  -35,  63,   34,  18 },  {  -54,  93,   21,  28 },  {  -85, 128,    0,  21 },  {  -72,  48,    0,  41 } } },  /* 72: KAGAMI K A */
    { { {   -4,  25,   44,  17 },  {  -44,  77,   28,  23 },  {  -23,  65,   20,  26 },  {  -59, 103,    0,  28 },  {    0,   0,    0,   0 } } },  /* 73: KAGAMI K A */
    { { {   -4,  25,   44,  17 },  {  -44,  77,   28,  23 },  {  -66, 111,   21,  26 },  {  -54, 114,    0,  23 },  {  -88,  62,    0,  28 } } },  /* 74: KAGAMI K A */
    { { {   -6,  24,   58,  19 },  {  -36,  80,   43,  21 },  {  -31,  84,   20,  26 },  {  -64, 122,    0,  32 },  {    0,   0,    0,   0 } } },  /* 75: not used by a script */
    { { {  -31,  45,   58,  18 },  {  -54,  89,   43,  18 },  {    0,   0,    0,   0 },  {  -55,  92,    0,  43 },  {    0,   0,    0,   0 } } },  /* 76: KAGAMI K A */
    { { {  -29,  49,   57,  20 },  {  -58,  96,   39,  22 },  {  -24,  43,   20,  26 },  {  -92, 130,    0,  24 },  {  -73,  65,   17,  27 } } },  /* 77: KAGAMI K A */
    { { {  -39,  23,   91,  21 },  {  -41,  75,   83,  23 },  {  -43,  79,   39,  47 },  {  -53,  16,   41,  51 },  {    0,   0,    0,   0 } } },  /* 78: V JUMP P S A, F JUMP P S A, atca 108 */
    { { {  -18,  23,  107,  16 },  {  -25,  53,   74,  20 },  {  -17,  43,   47,  35 },  {    0,   0,    0,   0 },  {  -74,  54,   68,  49 } } },  /* 79: not used by a script */
    { { {  -18,  23,  107,  16 },  {  -25,  53,   74,  20 },  {  -17,  43,   47,  35 },  {    0,   0,    0,   0 },  {  -80,  64,   95,  15 } } },  /* 80: not used by a script */
    { { {   -6,  23,  100,  16 },  {  -25,  53,   86,  20 },  {  -33,  69,   37,  52 },  {    0,   0,    0,   0 },  {  -91,  64,   45,  31 } } },  /* 81: V JUMP K M A, atca 116 */
    { { {  -20,  23,   92,  16 },  {  -23,  53,   75,  20 },  {  -33,  53,   36,  37 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 82: V JUMP K S A, F JUMP K S A, atca 114 */
    { { {  -19,  20,   92,  14 },  {  -32,  61,   80,  14 },  {  -27,  48,   48,  32 },  {    0,   0,    0,   0 },  {  -66,  47,   42,  43 } } },  /* 83: F JUMP K M A, F JUMP K L A, atca 118 */
    { { {  -11,  23,  106,  16 },  {  -23,  53,   90,  20 },  {  -29,  57,   43,  40 },  {    0,   0,    0,   0 },  {  -76,  71,   70,  20 } } },  /* 84: V JUMP K L A */
    { { {  -28,  38,   74,  16 },  {  -37,  65,   56,  20 },  {  -19,  43,   36,  29 },  {  -46,  80,    0,  35 },  {    0,   0,    0,   0 } } },  /* 85: HANASARE, ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN) +3 */
    { { {  -31,  29,   70,  16 },  {  -42,  77,   55,  23 },  {  -19,  43,   36,  29 },  {  -46,  80,    0,  35 },  {    0,   0,    0,   0 } } },  /* 86: HANASARE, ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN) +7 */
    { { {  -12,  18,   72,  14 },  {  -24,  52,   62,  14 },  {  -14,  40,   38,  22 },  {  -24,  56,    0,  36 },  {    0,   0,    0,   0 } } },  /* 87: not used by a script */
    { { {  -10,  18,   84,  14 },  {  -18,  44,   74,  14 },  {  -12,  36,   42,  14 },  {  -16,  56,    0,  40 },  {    0,   0,    0,   0 } } },  /* 88: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +1 */
    { { {   -8,  18,   84,  14 },  {  -24,  46,   72,  14 },  {  -18,  30,   46,  24 },  {  -16,  24,    0,  44 },  {  -38,  16,   46,  18 } } },  /* 89: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +1 */
    { { {  -10,  18,   98,  14 },  {  -24,  48,   88,  14 },  {  -29,  60,   49,  43 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 90: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +4 */
    { { {   -3,  23,   83,  16 },  {  -17,  43,   72,  20 },  {   -8,  37,   40,  29 },  {  -20,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 91: not used by a script */
    { { {   -6,  23,   83,  16 },  {  -20,  53,   67,  20 },  {  -12,  38,   36,  29 },  {  -22,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 92: not used by a script */
    { { {   -6,  23,   49,  16 },  {  -16,  42,   37,  18 },  {  -18,  44,   20,  26 },  {  -28,  55,    0,  31 },  {    0,   0,    0,   0 } } },  /* 93: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -27,  36,    0,  53 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 94: not used by a script */
    { { {  -20,  23,   89,  16 },  {  -25,  53,   74,  20 },  {  -17,  43,   47,  35 },  {    0,   0,    0,   0 },  {  -40,  25,   69,  19 } } },  /* 95: not used by a script */
    { { {  -32,  27,   89,  24 },  {  -34,  66,   79,  27 },  {  -25,  69,   50,  35 },  {    0,   0,    0,   0 },  {  -77,  59,   62,  19 } } },  /* 96: V JUMP P M A, F JUMP P L A */
    { { {  -13,  22,  100,  17 },  {  -34,  65,   88,  14 },  {  -29,  60,   49,  43 },  {    0,   0,    0,   0 },  {  -57,  56,   56,  16 } } },  /* 97: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +4 */
    { { {  -13,  22,  100,  17 },  {  -34,  65,   88,  14 },  {  -29,  60,   49,  43 },  {    0,   0,    0,   0 },  {  -16,  56,   53,  16 } } },  /* 98: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +3 */
    { { {  -12,  18,   90,  14 },  {  -26,  50,   80,  14 },  {  -20,  34,   50,  28 },  {  -30,  54,   10,  38 },  {    0,   0,    0,   0 } } },  /* 99: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) */
    { { {  -13,  22,   84,  21 },  {  -31,  64,   74,  16 },  {  -26,  51,   40,  30 },  {  -10,  36,    0,  38 },  {    0,   0,    0,   0 } } },  /* 100: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    { { {  -14,  26,   89,  17 },  {  -39,  81,   76,  14 },  {  -27,  54,   38,  41 },  {  -40,  67,    0,  48 },  {    0,   0,    0,   0 } } },  /* 101: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    { { {    0,  27,   81,  16 },  {  -27,  66,   70,  14 },  {  -28,  64,   38,  30 },  {  -40,  67,    0,  48 },  {    0,   0,    0,   0 } } },  /* 102: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    { { {   26,  26,   65,  22 },  {   10,  24,   39,  44 },  {  -40,  52,   44,  30 },  {  -40,  67,    0,  48 },  {  -80,  69,   58,  34 } } },  /* 103: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    { { {   31,  24,   66,  20 },  {   12,  28,   43,  40 },  {  -30,  40,   44,  41 },  {  -40,  67,    0,  48 },  {  -78,  50,   45,  22 } } },  /* 104: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    { { {   19,  27,   75,  17 },  {   -2,  47,   61,  29 },  {  -21,  71,   34,  32 },  {  -40,  90,    0,  45 },  {  -23,  31,   59,  31 } } },  /* 105: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    { { {  -23,  22,   86,  15 },  {  -33,  67,   73,  14 },  {  -26,  52,   48,  23 },  {  -37,  72,    0,  45 },  {    0,   0,    0,   0 } } },  /* 106: M PUNCH C */
    { { {  -28,  27,   81,  16 },  {  -34,  60,   64,  20 },  {  -28,  45,   36,  29 },  {  -35,  71,    0,  35 },  {  -66,  45,   43,  49 } } },  /* 107: M PUNCH C */
    { { {  -14,  21,   84,  18 },  {  -28,  58,   69,  22 },  {  -21,  49,   38,  31 },  {  -28,  63,    0,  38 },  {  -33,  21,   54,  19 } } },  /* 108: M PUNCH A, UP P GUARD P M */
    { { {  -23,  18,   81,  14 },  {  -34,  52,   67,  14 },  {  -25,  40,   38,  30 },  {  -28,  56,    0,  36 },  {  -46,  16,   74,  18 } } },  /* 109: S PUNCH A */
    { { {  -18,  23,   81,  16 },  {  -30,  61,   70,  15 },  {  -46,  72,   38,  30 },  {  -33,  65,    0,  36 },  {    0,   0,    0,   0 } } },  /* 110: M PUNCH A, UP P GUARD P M */
    { { {  -28,  46,   89,  16 },  {  -35,  60,   69,  26 },  {  -72, 100,   49,  22 },  {  -85, 102,   46,  16 },  {  -72,  41,   71,  15 } } },  /* 111: F JUMP K L A, atca 118 */
    { { {  -32,  32,   79,  17 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -32,  55,    0,  35 },  {  -75,  48,   15,  79 } } },  /* 112: M PUNCH C */
    { { {  -24,  18,   90,  14 },  {  -17,  52,   79,  14 },  {   -9,  40,   47,  30 },  {  -24,  56,    0,  36 },  {    0,   0,    0,   0 } } },  /* 113: not used by a script */
    { { {  -24,  18,   90,  14 },  {  -17,  52,   79,  14 },  {   -9,  40,   47,  30 },  {  -24,  56,    0,  36 },  {  -59,  41,   78,  10 } } },  /* 114: not used by a script */
    { { {  -17,  37,   77,  14 },  {  -24,  52,   66,  17 },  {  -24,  53,   47,  17 },  {  -17,  40,   37,  15 },  {    0,   0,    0,   0 } } },  /* 115: not used by a script */
    { { {    0,  16,   85,  16 },  {   -8,  48,   72,  16 },  {   -4,  40,   48,  24 },  {   -8,  40,   48,  24 },  {    0,   0,    0,   0 } } },  /* 116: FUSHIN P S */
    { { {    0,  16,   85,  16 },  {   -8,  48,   72,  16 },  {   -4,  40,   48,  24 },  {   -8,  40,   48,  24 },  {  -48,  40,   72,  16 } } },  /* 117: FUSHIN P S */
    { { {  -17,  28,  108,  16 },  {  -29,  54,   95,  15 },  {  -31,  69,   47,  49 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 118: V JUMP P L A, atca 112 */
    { { {  -17,  28,  108,  16 },  {  -29,  54,   95,  15 },  {  -31,  69,   47,  49 },  {    0,   0,    0,   0 },  {  -86,  66,   80,  12 } } },  /* 119: V JUMP P L A, atca 112 */
    { { {   -6,  23,  100,  16 },  {  -25,  53,   86,  20 },  {  -33,  69,   37,  52 },  {    0,   0,    0,   0 },  {  -87,  69,   46,  16 } } },  /* 120: V JUMP K M A, atca 116 */
    { { {  -19,  39,   92,  16 },  {  -32,  64,   78,  15 },  {  -30,  59,   42,  37 },  {    0,   0,    0,   0 },  {  -58,  38,   59,  24 } } },  /* 121: F JUMP P M A, atca 110 */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -34,  59,    0,  32 },  {    0,   0,    0,   0 } } },  /* 122: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +1 */
    { { {  -32,  27,   89,  24 },  {  -65,  96,   79,  27 },  {  -72, 104,   49,  33 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 123: saca 56 */
    { { {   -9,  21,   84,  18 },  {  -11,  54,   81,   7 },  {  -11,  52,   41,  40 },  {  -28,  63,    0,  38 },  {    0,   0,    0,   0 } } },  /* 124: PIYO */
    { { {  -34,  21,   80,  18 },  {  -43,  68,   69,  17 },  {  -28,  52,   38,  30 },  {  -29,  63,    0,  38 },  {    0,   0,    0,   0 } } },  /* 125: PIYO */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -41,  81,    0,  24 },  {    0,   0,    0,   0 } } },  /* 126: OKIAGARI P S */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -41,  82,    0,  61 },  {    0,   0,    0,   0 } } },  /* 127: OKIAGARI P S */
    { { {  -20,  41,   96,  27 },  {  -29,  58,   82,  14 },  {  -29,  58,   64,  18 },  {  -33,  66,    0,  64 },  {    0,   0,    0,   0 } } },  /* 128: OKIAGARI P S */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -35,  59,    0,  48 },  {    0,   0,    0,   0 } } },  /* 129: ATTACK 2 L (Att_SHOURYUUKEN) */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -35,  59,    0,  60 },  {    0,   0,    0,   0 } } },  /* 130: ATTACK 2 S (Att_SHOURYUUKEN) */
};

const ATTACK_BOX ryu_att_box[68] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {    0,   0,    0,   0 },  {  -56,  24,   38,  30 },  {    0,   0,    0,   0 } } },  /* 1: ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 6 S (Att_SHINSHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +1; attack 1, 53, 54, 56 */
    { { {    0,   0,    0,   0 },  {  -31,  26,  101,  39 },  {  -46,  24,   48,  29 } } },  /* 2: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +1; attack 2, 56, 61, 62 */
    { { {    0,   0,    0,   0 },  {  -40,  18,   58,  16 },  {  -26,  14,  122,  20 } } },  /* 3: not used by a script */
    { { {    0,   0,    0,   0 },  {  -53,  43,   75,  21 },  {  -39,  28,   57,  21 } } },  /* 4: S PUNCH A; attack 3 */
    { { {    0,   0,    0,   0 },  {  -69,  62,   71,  15 },  {    0,   0,    0,   0 } } },  /* 5: S PUNCH B; attack 4 */
    { { {    0,   0,    0,   0 },  {  -52,  26,   39,  26 },  {    0,   0,    0,   0 } } },  /* 6: M PUNCH A, UP P GUARD P M; attack 5 */
    { { {    0,   0,    0,   0 },  {  -86,  71,   67,  12 },  {    0,   0,    0,   0 } } },  /* 7: M PUNCH B, UP P GUARD P S; attack 6 */
    { { {    0,   0,    0,   0 },  {  -63,  47,   61,  25 },  {    0,   0,    0,   0 } } },  /* 8: L PUNCH A, atca 156; attack 8 */
    { { {    0,   0,    0,   0 },  {  -52,  40,   83,  32 },  {    0,   0,    0,   0 } } },  /* 9: L PUNCH A, atca 156; attack 8 */
    { { {    0,   0,    0,   0 },  {  -75,  50,   70,  22 },  {    0,   0,    0,   0 } } },  /* 10: UP P GUARD P L, L PUNCH B; attack 9 */
    { { {    0,   0,    0,   0 },  {  -76,  54,   10,  18 },  {    0,   0,    0,   0 } } },  /* 11: S KICK A; attack 10 */
    { { {    0,   0,    0,   0 },  {  -75,  46,   65,  15 },  {  -35,  35,   59,  13 } } },  /* 12: not used by a script */
    { { {    0,   0,    0,   0 },  {  -77,  58,   35,  43 },  {    0,   0,    0,   0 } } },  /* 13: M KICK A; attack 12 */
    { { {    0,   0,    0,   0 },  {  -82,  76,   41,  16 },  {    0,   0,    0,   0 } } },  /* 14: M KICK B, UP P GUARD K S; attack 13 */
    { { {    0,   0,    0,   0 },  {  -70,  17,   90,  32 },  {  -60,  19,   63,  26 } } },  /* 15: not used by a script */
    { { {    0,   0,    0,   0 },  {  -85,  17,   90,  32 },  {  -69,  19,   68,  26 } } },  /* 16: not used by a script */
    { { {    0,   0,    0,   0 },  { -115,  37,   72,  18 },  {  -77,  41,   64,  19 } } },  /* 17: not used by a script */
    { { {    0,   0,    0,   0 },  {  -80,  26,   78,  36 },  {  -67,  28,   63,  36 } } },  /* 18: not used by a script */
    { { {    0,   0,    0,   0 },  {  -91,  28,   81,  14 },  {  -62,  35,   60,  26 } } },  /* 19: L KICK A, atca 157; attack 17, 60 */
    { { {    0,   0,    0,   0 },  {  -78,  42,   74,  14 },  {  -50,  39,   63,  12 } } },  /* 20: not used by a script */
    { { {    0,   0,    0,   0 },  {  -64,  45,   37,  15 },  {    0,   0,    0,   0 } } },  /* 21: KAGAMI P A; attack 19 */
    { { {    0,   0,    0,   0 },  {  -69,  52,   43,  10 },  {    0,   0,    0,   0 } } },  /* 22: KAGAMI P A; attack 20 */
    { { {    0,   0,    0,   0 },  {  -60,  36,   30,  35 },  {    0,   0,    0,   0 } } },  /* 23: KAGAMI P A; attack 21 */
    { { {    0,   0,    0,   0 },  {  -23,  20,   89,  33 },  {  -38,  23,   61,  28 } } },  /* 24: KAGAMI P A; attack 22 */
    { { {    0,   0,    0,   0 },  {  -80,  54,    0,   5 },  {    0,   0,    0,   0 } } },  /* 25: KAGAMI K A; attack 23 */
    { { {    0,   0,    0,   0 },  {  -86,  76,    0,   5 },  {    0,   0,    0,   0 } } },  /* 26: KAGAMI K A; attack 24 */
    { { {    0,   0,    0,   0 },  {  -96,  75,    0,   6 },  {  -57,  45,    2,  21 } } },  /* 27: KAGAMI K A; attack 25 */
    { { {    0,   0,    0,   0 },  {  -42,  28,   63,  18 },  {    0,   0,    0,   0 } } },  /* 28: V JUMP P S A, F JUMP P S A, atca 108; attack 26, 32 */
    { { {    0,   0,    0,   0 },  {  -90,  64,   91,  10 },  {    0,   0,    0,   0 } } },  /* 29: V JUMP P L A, atca 112; attack 28 */
    { { {    0,   0,    0,   0 },  {  -72,  66,   60,  14 },  {    0,   0,    0,   0 } } },  /* 30: V JUMP K M A, atca 116; attack 30 */
    { { {    0,   0,    0,   0 },  {  -55,  16,   91,  25 },  {  -46,  20,   74,  20 } } },  /* 31: not used by a script */
    { { {    0,   0,    0,   0 },  {  -76,  18,   59,  11 },  {  -56,  17,   69,  11 } } },  /* 32: not used by a script */
    { { {    0,   0,    0,   0 },  {  -32,  24,   48,  19 },  {    0,   0,    0,   0 } } },  /* 33: V JUMP K S A, F JUMP K S A, atca 114; attack 29, 35 */
    { { {    0,   0,    0,   0 },  {  -79,  19,   38,  24 },  {  -63,  77,   52,  22 } } },  /* 34: F JUMP K M A; attack 36 */
    { { {    0,   0,    0,   0 },  {  -52,  24,   18,  28 },  {  -36,  24,    4,  28 } } },  /* 35: not used by a script */
    { { {    0,   0,    0,   0 },  {  -58,  19,   95,  20 },  {  -45,  27,   66,  28 } } },  /* 36: F JUMP P M A, atca 110; attack 33 */
    { { {    0,   0,    0,   0 },  {  -66,  61,   77,  21 },  {  -81,  25,   93,  22 } } },  /* 37: V JUMP K L A; attack 31 */
    { { {    0,   0,    0,   0 },  {  -78,  18,   63,  20 },  {  -56,  38,   63,  14 } } },  /* 38: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +4; attack 38, 39, 66 */
    { { {    0,   0,    0,   0 },  {   18,  35,   66,  16 },  {    0,   0,    0,   0 } } },  /* 39: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +3; attack 39, 40, 64, 67 */
    { { {    0,   0,    0,   0 },  { -108,  39,   52,  13 },  {  -72,  32,   55,  13 } } },  /* 40: not used by a script */
    { { {  -31,   6,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 41: M PUNCH A, M PUNCH B, M PUNCH C +4; attack 48 */
    { { {    0,   0,    0,   0 },  {  -57,  31,   53,  28 },  {    0,   0,    0,   0 } } },  /* 42: M PUNCH C; attack 50 */
    { { {    0,   0,    0,   0 },  {  -68,  41,   18,  32 },  {    0,   0,    0,   0 } } },  /* 43: M PUNCH C; attack 51 */
    { { {    0,   0,    0,   0 },  {  -45,  40,   54,  29 },  {    0,   0,    0,   0 } } },  /* 44: F JUMP P M A, atca 110; attack 52 */
    { { {    0,   0,    0,   0 },  {  -52,  22,   56,  18 },  {  -40,  20,   48,  16 } } },  /* 45: not used by a script */
    { { {    0,   0,    0,   0 },  {  -80,  49,   58,  12 },  {  -31,  14,   42,  28 } } },  /* 46: UP P GUARD K L, Att_HADOUKEN2 (command slot 25); attack 18, 73 */
    { { {    0,   0,    0,   0 },  {  -83,  57,   74,  14 },  {  -34,  10,   60,  13 } } },  /* 47: UP P GUARD K L, Att_HADOUKEN2 (command slot 25); attack 71 */
    { { {    0,   0,    0,   0 },  {  -77,  18,   55,  13 },  {  -67,  58,   54,  19 } } },  /* 48: F JUMP K L A, atca 118; attack 37 */
    { { {    0,   0,    0,   0 },  {  -85,  34,   84,  24 },  {  -67,  27,   65,  31 } } },  /* 49: atca 157; attack 60 */
    { { {    0,   0,    0,   0 },  {  -66,  18,   72,  16 },  {  -48,  40,   75,  10 } } },  /* 50: FUSHIN P S; attack 58 */
    { { {    0,   0,    0,   0 },  {  -71,  44,   50,  23 },  {    0,   0,    0,   0 } } },  /* 51: V JUMP P M A, F JUMP P L A; attack 27, 34 */
    { { {    0,   0,    0,   0 },  {  -66,  89,   24,  43 },  {    0,   0,    0,   0 } } },  /* 52: ATTACK 6 S (Att_SHINSHOURYUUKEN); attack 55 */
    { { {    0,   0,    0,   0 },  {  -72,  59,    0,  84 },  {    0,   0,    0,   0 } } },  /* 53: ATTACK 6 S (Att_SHINSHOURYUUKEN); attack 57 */
    { { {    0,   0,    0,   0 },  {  -34,  34,  103,  37 },  {    0,   0,    0,   0 } } },  /* 54: ATTACK 6 S (Att_SHINSHOURYUUKEN); attack 57 */
    { { {    0,   0,    0,   0 },  {  -62,  52,   48,  37 },  {    0,   0,    0,   0 } } },  /* 55: ATTACK 6 S (Att_SHINSHOURYUUKEN); attack 59 */
    { { {    0,   0,    0,   0 },  { -100,  37,    0,  19 },  {  -57,  45,    2,  21 } } },  /* 56: not used by a script */
    { { {    0,   0,    0,   0 },  {  -76,  85,   43,  21 },  {    0,   0,    0,   0 } } },  /* 57: M KICK B, UP P GUARD K S; attack 13 */
    { { {    0,   0,    0,   0 },  {  -72,  25,   47,  22 },  {  -47,  28,   51,  25 } } },  /* 58: not used by a script */
    { { {    0,   0,    0,   0 },  {  -90,  32,   98,  10 },  {  -56,  35,   99,  10 } } },  /* 59: not used by a script */
    { { {    0,   0,    0,   0 },  {  -87,  70,   55,  21 },  {    0,   0,    0,   0 } } },  /* 60: V JUMP K M A, atca 116; attack 30 */
    { { {  -35,  10,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 61: L PUNCH A, L PUNCH B, L KICK A; attack 48 */
    { { {    0,   0,    0,   0 },  {  -49,  26,   29,  49 },  {    0,   0,    0,   0 } } },  /* 62: saca 56; attack 69 */
    { { {    0,   0,    0,   0 },  {  -63,  47,   48,  39 },  {    0,   0,    0,   0 } } },  /* 63: L PUNCH A; attack 7 */
    { { {    0,   0,    0,   0 },  {  -41,  81,    0,  24 },  {    0,   0,    0,   0 } } },  /* 64: OKIAGARI P S; attack 70 */
    { { {    0,   0,    0,   0 },  {  -42,  27,   42,  33 },  {  -30,  26,  100,  39 } } },  /* 65: OKIAGARI P S; attack 70 */
    { { {    0,   0,    0,   0 },  {  -64,  39,   70,  12 },  {    0,   0,    0,   0 } } },  /* 66: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU); attack 40, 65, 68 */
    { { {    0,   0,    0,   0 },  {  -81,  57,   72,   8 },  {  -28,   9,   45,  35 } } },  /* 67: Att_HADOUKEN2 (command slot 25); attack 72 */
};

const CAUGHT_BOX ryu_cau_box[21] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -25,   50,    0,   16 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +100 */
    { {  -29,   54,    0,    8 } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +19 */
    { {  -18,   45,   52,   40 } },  /* 3: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +14 */
    { {  -31,   63,   44,   44 } },  /* 4: JUMP FRONT, JUMP BACK, SP JUMP FRONT +20 */
    { {   -1,   48,    0,   90 } },  /* 5: not used by a script */
    { {  -21,   36,    0,   90 } },  /* 6: not used by a script */
    { {  -36,   36,    0,   90 } },  /* 7: not used by a script */
    { {  -33,   58,    0,    8 } },  /* 8: KAGAMI P A, KAGAMI K A */
    { {  -29,   54,    0,   16 } },  /* 9: S KICK A */
    { {  -28,   48,    0,   58 } },  /* 10: not used by a script */
    { {  -28,   45,   46,   61 } },  /* 11: not used by a script */
    { {  -21,   34,   80,   29 } },  /* 12: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +4 */
    { {  -21,   45,   45,   44 } },  /* 13: AIR S, AIR M, AIR L +33 */
    { {   -8,   40,   66,   25 } },  /* 14: FUSHIN P S */
    { {  -16,   48,    0,   82 } },  /* 15: not used by a script */
    { {  -46,   80,    0,   16 } },  /* 16: HANASARE, ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN) +8 */
    { {  -41,   81,    0,   16 } },  /* 17: not used by a script */
    { {  -36,   73,   46,   49 } },  /* 18: not used by a script */
    { {  -38,   63,    0,   16 } },  /* 19: not used by a script */
    { {  -25,   71,    0,   16 } },  /* 20: UP P GUARD K L, Att_HADOUKEN2 (command slot 25), OKIAGARI P S */
};

const HOSEI_BOX ryu_hos_box[26] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -25,   50,    0,   86 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +100 */
    { {  -25,   50,    0,   54 } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +41 */
    { {  -18,   45,   52,   40 } },  /* 3: GUARD AIR, V JUMP P M A, V JUMP K S A +10 */
    { {  -31,   63,   44,   44 } },  /* 4: ATTACK 6 S (Att_SHINSHOURYUUKEN), ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN) +30 */
    { {  -72,   99,    0,   70 } },  /* 5: not used by a script */
    { {  -26,   72,    0,   89 } },  /* 6: UP P GUARD K L, Att_HADOUKEN2 (command slot 25) */
    { {  -37,   37,   35,   54 } },  /* 7: not used by a script */
    { {    6,   47,   35,   54 } },  /* 8: not used by a script */
    { {   -5,   53,   35,   51 } },  /* 9: not used by a script */
    { {  -28,   53,   36,   44 } },  /* 10: TOUKETSU A */
    { {  -20,   49,   36,   36 } },  /* 11: not used by a script */
    { {   -4,   56,   35,   48 } },  /* 12: not used by a script */
    { {  -16,   47,   23,   37 } },  /* 13: not used by a script */
    { {  -16,   47,   13,   37 } },  /* 14: not used by a script */
    { {  -73,  105,    0,   70 } },  /* 15: ATTACK 4 S (Att_HADOUKEN), ATTACK 4 M (Att_HADOUKEN), ATTACK 4 L (Att_HADOUKEN) +2 */
    { {  -31,   63,   57,   36 } },  /* 16: V JUMP P S A, F JUMP P S A, atca 108 +2 */
    { {  -22,   49,   58,   32 } },  /* 17: ATTACK 6 S (Att_SHINSHOURYUUKEN) */
    { {  -24,   44,   54,   52 } },  /* 18: ATTACK 3 S (Att_SENPUUKYAKU), ATTACK 3 M (Att_SENPUUKYAKU), ATTACK 3 L (Att_SENPUUKYAKU) +4 */
    { {  -46,   80,    0,   70 } },  /* 19: HANASARE, ATTACK 1 S (Att_HADOUKEN), ATTACK 1 M (Att_HADOUKEN) +8 */
    { {  -24,   57,   47,   57 } },  /* 20: exca 17, saca 48 */
    { {  -38,   63,    0,   80 } },  /* 21: DASH HUMIKOMI, DASH TOBINOKI */
    { {  -21,   45,   45,   44 } },  /* 22: AIR S, AIR M, AIR L +33 */
    { {   -8,   53,   48,   32 } },  /* 23: FUSHIN P S */
    { {  -22,   49,   18,   57 } },  /* 24: not used by a script */
    { {  -25,   50,    0,   30 } },  /* 25: NEKOROBI S */
};
