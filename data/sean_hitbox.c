/*
 * SEAN_HITBOX.C  Sean's hit boxes
 *
 * Each of Sean's animation frames names a row of sean_hit_ix_table (a frame line's hit field). The
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
 * rows of sean_catt_table dealt through it. Row 0 of a box table is no box.
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

const HIT_IX sean_hit_ix_table[190] = {
    /* boix  atix  cuix  hoix */
    {    0,    0,    0,    0 },  /* 0: NAGERARE KAIHI, OKIAGARI, OKIAGARI F +16 */
    {    1,    0,    1,    1 },  /* 1: KAMAE, HURIMUKI, FRONT WALK +96 */
    {    2,    0,    2,    2 },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +25 */
    {    0,    0,    0,    1 },  /* 3: OKIAGARI P S */
    {    0,    1,    0,    2 },  /* 4: ATTACK 6 S (Att_SHOURYUUREPPA), saca 56, saca 57 +1 */
    {    0,    2,    0,    1 },  /* 5: ATTACK 6 S (Att_SHOURYUUREPPA), saca 56, saca 57 +1 */
    {    3,    3,    0,   17 },  /* 6: saca 56, saca 57, saca 58 */
    {    3,    0,    3,   17 },  /* 7: ATTACK 6 S (Att_SHOURYUUREPPA), saca 56, saca 57 +2 */
    {    4,    0,    3,   17 },  /* 8: ATTACK 6 S (Att_SHOURYUUREPPA), saca 56, saca 57 +1 */
    {    5,    0,   18,   19 },  /* 9: DASH HUMIKOMI, DASH TOBINOKI */
    {    6,    0,    1,    1 },  /* 10: DASH TOBINOKI */
    {    7,    0,    3,    3 },  /* 11: GUARD AIR, V JUMP P M A, V JUMP K S A +8 */
    {    8,    0,    3,    3 },  /* 12: not used by a script */
    {    9,    0,    3,    3 },  /* 13: not used by a script */
    {   10,    0,    4,    4 },  /* 14: JUMP FRONT, JUMP BACK, SP JUMP FRONT +1 */
    {   11,    0,    4,    4 },  /* 15: JUMP JUNBI, SP JUMP JUNBI, JUMP VERTICAL +6 */
    {   12,    0,    4,    4 },  /* 16: JUMP VERTICAL, S JUMP FRONT, SP JUMP V +1 */
    {   13,    0,    3,    3 },  /* 17: not used by a script */
    {   14,    0,    3,    3 },  /* 18: not used by a script */
    {   15,    0,    3,    3 },  /* 19: not used by a script */
    {  109,    4,    1,    1 },  /* 20: not used by a script */
    {   16,    0,    1,    1 },  /* 21: not used by a script */
    {   17,    5,    1,    1 },  /* 22: S PUNCH A */
    {   17,    0,    1,    1 },  /* 23: S PUNCH A */
    {  110,    6,    1,    1 },  /* 24: M PUNCH A */
    {   18,    0,    1,    1 },  /* 25: M PUNCH B, L PUNCH A, L PUNCH B +4 */
    {   19,    7,    1,    1 },  /* 26: M PUNCH B, UP P GUARD P S */
    {   19,    0,    1,    1 },  /* 27: M PUNCH B, UP P GUARD P S */
    {   20,    0,    1,    1 },  /* 28: M PUNCH B, UP P GUARD P S */
    {   21,    0,    1,    1 },  /* 29: L PUNCH A, L PUNCH B, atca 156 +1 */
    {   22,    8,    1,    1 },  /* 30: L PUNCH A, L PUNCH B, atca 156 +1 */
    {   23,    9,    1,    1 },  /* 31: L PUNCH A, L PUNCH B, atca 156 +1 */
    {   24,    0,    1,    1 },  /* 32: L PUNCH A, L PUNCH B, atca 156 +1 */
    {   25,    0,    1,    1 },  /* 33: not used by a script */
    {   26,   10,    1,    1 },  /* 34: not used by a script */
    {   27,   10,    1,    1 },  /* 35: not used by a script */
    {   27,    0,    1,    1 },  /* 36: not used by a script */
    {   28,    0,    1,    1 },  /* 37: not used by a script */
    {   29,    0,    1,    1 },  /* 38: not used by a script */
    {   31,    0,    8,    1 },  /* 39: S KICK A, M KICK A */
    {   31,   11,    8,    1 },  /* 40: S KICK A */
    {   30,    0,    8,    1 },  /* 41: S KICK A */
    {   32,    0,    1,    1 },  /* 42: not used by a script */
    {   33,    0,    1,    1 },  /* 43: not used by a script */
    {   34,   12,    1,    1 },  /* 44: not used by a script */
    {   34,    0,    1,    1 },  /* 45: not used by a script */
    {   35,    0,    1,    1 },  /* 46: L KICK A */
    {   36,    0,    1,    1 },  /* 47: not used by a script */
    {   31,   13,    1,    1 },  /* 48: M KICK A */
    {   37,    0,    1,    1 },  /* 49: L KICK A */
    {   38,    0,    1,    1 },  /* 50: L KICK A */
    {   39,    0,    1,    1 },  /* 51: not used by a script */
    {   40,   14,    1,    1 },  /* 52: not used by a script */
    {   40,    0,    1,    1 },  /* 53: not used by a script */
    {   41,    0,    1,    1 },  /* 54: not used by a script */
    {   42,    0,    1,    1 },  /* 55: not used by a script */
    {   43,    0,    1,    1 },  /* 56: not used by a script */
    {   44,    0,    1,    1 },  /* 57: not used by a script */
    {   45,    0,    1,    1 },  /* 58: not used by a script */
    {   46,   15,    1,    1 },  /* 59: L KICK A */
    {   47,   16,    1,    1 },  /* 60: not used by a script */
    {   48,   17,    1,    1 },  /* 61: not used by a script */
    {   49,   40,    1,    1 },  /* 62: not used by a script */
    {   50,    0,    1,    1 },  /* 63: not used by a script */
    {   51,    0,    1,    1 },  /* 64: L KICK A */
    {   52,    0,    1,    1 },  /* 65: L KICK B */
    {   53,   18,    1,    1 },  /* 66: not used by a script */
    {   54,   19,    1,    1 },  /* 67: L KICK B */
    {   54,    0,    1,    1 },  /* 68: L KICK B */
    {   55,    0,    1,    1 },  /* 69: L KICK B */
    {   56,    0,    1,    1 },  /* 70: L KICK B */
    {   57,    0,    1,    1 },  /* 71: L KICK B */
    {   58,    0,    1,    1 },  /* 72: L KICK C */
    {   59,    0,    1,    1 },  /* 73: L KICK C */
    {   60,    0,    1,    1 },  /* 74: TOUKETSU A, L KICK C */
    {   61,   20,    1,    1 },  /* 75: L KICK C */
    {   61,    0,    1,    1 },  /* 76: L KICK C */
    {   62,    0,    1,    1 },  /* 77: L KICK C */
    {   63,    0,    1,    1 },  /* 78: L KICK C */
    {   64,   21,    9,    2 },  /* 79: KAGAMI P A */
    {   64,    0,    9,    2 },  /* 80: KAGAMI P A */
    {   65,   22,    2,    2 },  /* 81: KAGAMI P A */
    {   65,    0,    2,    2 },  /* 82: KAGAMI P A */
    {   66,    0,    2,    2 },  /* 83: KAGAMI P A */
    {   67,   23,    2,    2 },  /* 84: KAGAMI P A */
    {   68,   24,    2,    2 },  /* 85: KAGAMI P A */
    {   69,    0,    2,    2 },  /* 86: not used by a script */
    {   68,    0,    2,    2 },  /* 87: KAGAMI P A */
    {   70,    0,    2,    2 },  /* 88: KAGAMI P A */
    {   71,    0,    9,    2 },  /* 89: KAGAMI K A */
    {   72,   25,    9,    2 },  /* 90: KAGAMI K A */
    {   72,    0,    9,    2 },  /* 91: KAGAMI K A */
    {   73,    0,    2,    2 },  /* 92: KAGAMI K A, UP P GUARD K S */
    {   74,   26,    2,    2 },  /* 93: KAGAMI K A, UP P GUARD K S */
    {   74,    0,    2,    2 },  /* 94: UP P GUARD K S */
    {   75,    0,    2,    2 },  /* 95: KAGAMI K A, UP P GUARD K S */
    {   76,    0,    2,    2 },  /* 96: KAGAMI K A */
    {   77,   27,    2,    2 },  /* 97: KAGAMI K A */
    {   77,    0,    2,    2 },  /* 98: KAGAMI K A */
    {   78,    0,    4,    4 },  /* 99: V JUMP P S A, V JUMP P L A, F JUMP P S A */
    {   78,   28,    4,    4 },  /* 100: V JUMP P S A, F JUMP P S A */
    {   79,    0,    4,    4 },  /* 101: V JUMP P L A, V JUMP K M A */
    {   80,   29,    4,    4 },  /* 102: V JUMP P L A */
    {   80,    0,    4,    4 },  /* 103: F JUMP P S A */
    {   81,   30,    4,    4 },  /* 104: V JUMP K M A */
    {   81,    0,    4,    4 },  /* 105: not used by a script */
    {   95,   31,    3,    3 },  /* 106: not used by a script */
    {   96,   32,    3,    3 },  /* 107: V JUMP P M A, F JUMP P M A, F JUMP P L A */
    {   82,   33,    3,    3 },  /* 108: V JUMP K S A, F JUMP K S A */
    {   82,    0,    3,    3 },  /* 109: V JUMP K S A, F JUMP K S A */
    {   83,   34,    3,    3 },  /* 110: F JUMP K M A */
    {   83,    0,    3,    3 },  /* 111: F JUMP K M A, F JUMP K L A */
    {    0,   35,    0,    2 },  /* 112: not used by a script */
    {   79,   36,    3,    3 },  /* 113: not used by a script */
    {   84,   37,    3,    3 },  /* 114: V JUMP K L A */
    {   84,    0,    3,    3 },  /* 115: V JUMP K L A */
    {   85,    0,   15,   23 },  /* 116: not used by a script */
    {   86,    0,   15,   23 },  /* 117: ATTACK 4 S (Att_HADOUKEN) */
    {   87,   38,    0,    1 },  /* 118: exca 17, ATTACK 5 S (Att_SLIDE_and_JUMP) */
    {   88,    0,   12,   18 },  /* 119: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +2 */
    {   89,   39,   12,   18 },  /* 120: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +1 */
    {   89,    0,   12,   18 },  /* 121: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +2 */
    {   90,    0,    0,   18 },  /* 122: not used by a script */
    {    1,    0,    1,    1 },  /* 123: GUARD HEAD */
    {    1,    0,    1,    1 },  /* 124: GUARD UP */
    {    2,    0,    2,    2 },  /* 125: GUARD DOWN */
    {    0,    0,    0,    2 },  /* 126: OKIAGARI, OKIAGARI F, OKIAGARI B +16 */
    {    0,    0,    0,    2 },  /* 127: not used by a script */
    {    1,   41,    1,    1 },  /* 128: M PUNCH A, M PUNCH B, M KICK A +3 */
    {  115,    0,    1,    1 },  /* 129: ATTACK 3 S (Att_ABISEGERI), ATTACK 3 M (Att_ABISEGERI) */
    {  116,    0,    0,    3 },  /* 130: ATTACK 3 S (Att_ABISEGERI), ATTACK 3 M (Att_ABISEGERI), ATTACK 3 L (Att_ABISEGERI) */
    {  117,   46,    0,    3 },  /* 131: not used by a script */
    {  118,   42,    0,    3 },  /* 132: ATTACK 5 S (Att_SLIDE_and_JUMP) */
    {  119,   43,    0,    3 },  /* 133: ATTACK 3 S (Att_ABISEGERI), ATTACK 3 M (Att_ABISEGERI), ATTACK 3 L (Att_ABISEGERI) +1 */
    {  120,    0,    0,    3 },  /* 134: ATTACK 3 S (Att_ABISEGERI), ATTACK 3 M (Att_ABISEGERI), ATTACK 3 L (Att_ABISEGERI) +1 */
    {  118,    0,    0,    1 },  /* 135: not used by a script */
    {  119,    0,    0,    1 },  /* 136: not used by a script */
    {  126,    0,    0,    0 },  /* 137: Att_CHOUCHUURENGEKI (command slot 25) */
    {  121,    0,   13,   20 },  /* 138: AIR S, AIR M, AIR L +39 */
    {    1,   44,    1,    1 },  /* 139: not used by a script */
    {  122,    0,    2,    2 },  /* 140: ATTACK 1 S (Att_CHOUCHUURENGEKI), ATTACK 1 L (Att_CHOUCHUURENGEKI) */
    {  123,    0,    5,   21 },  /* 141: ATTACK 1 S (Att_CHOUCHUURENGEKI), ATTACK 1 M (Att_CHOUCHUURENGEKI), ATTACK 1 L (Att_CHOUCHUURENGEKI) */
    {  124,    0,    5,   21 },  /* 142: ATTACK 1 S (Att_CHOUCHUURENGEKI), ATTACK 1 M (Att_CHOUCHUURENGEKI), ATTACK 1 L (Att_CHOUCHUURENGEKI) +1 */
    {  125,   45,    5,   21 },  /* 143: ATTACK 1 S (Att_CHOUCHUURENGEKI), ATTACK 1 M (Att_CHOUCHUURENGEKI), ATTACK 1 L (Att_CHOUCHUURENGEKI) */
    {    0,    0,    0,    1 },  /* 144: ATTACK 5 S (Att_SLIDE_and_JUMP), ATTACK 6 S (Att_SHOURYUUREPPA) */
    {    0,    0,   19,    0 },  /* 145: not used by a script */
    {  128,    0,   14,   22 },  /* 146: FUSHIN P S */
    {  129,   47,   14,   22 },  /* 147: FUSHIN P S */
    {    5,   48,    1,    1 },  /* 148: ATTACK 5 S (Att_SLIDE_and_JUMP) */
    {  108,    0,    1,    1 },  /* 149: M PUNCH A */
    {    0,    0,    0,   23 },  /* 150: ATTACK 4 S (Att_HADOUKEN) */
    {  130,    0,    0,    2 },  /* 151: not used by a script */
    {  131,    0,    0,    2 },  /* 152: saca 56, saca 57, saca 58 */
    {   83,   49,    3,    3 },  /* 153: F JUMP K L A */
    {   77,    0,    2,    2 },  /* 154: not used by a script */
    {    1,   51,    1,    1 },  /* 155: ATTACK 5 S (Att_SLIDE_and_JUMP) */
    {  132,   46,    0,    1 },  /* 156: not used by a script */
    {    0,   48,    0,    1 },  /* 157: ATTACK 5 S (Att_SLIDE_and_JUMP) */
    {   89,   52,    0,   18 },  /* 158: ATTACK 5 S (Att_SLIDE_and_JUMP) */
    {   74,    0,    2,    2 },  /* 159: KAGAMI K A */
    {   72,    0,    9,    2 },  /* 160: KAGAMI K A */
    {  133,    0,   15,   23 },  /* 161: ATTACK 5 S (Att_SLIDE_and_JUMP) */
    {  118,   53,    0,   20 },  /* 162: ATTACK 5 S (Att_SLIDE_and_JUMP) */
    {    1,   55,    1,    1 },  /* 163: L PUNCH A, L PUNCH B, L KICK A +2 */
    {    0,    0,    0,   18 },  /* 164: AIR S, AIR M, AIR L +2 */
    {  134,    0,    0,   25 },  /* 165: Att_SENPUUKYAKU (command slot 23) */
    {  134,   56,    0,   25 },  /* 166: not used by a script */
    {  134,   57,    0,   25 },  /* 167: not used by a script */
    {  134,   58,    0,   25 },  /* 168: Att_SENPUUKYAKU (command slot 23) */
    {  134,   59,    0,   18 },  /* 169: not used by a script */
    {  135,   60,    3,    3 },  /* 170: saca 60 */
    {  137,    0,    1,    1 },  /* 171: PIYO */
    {  138,    0,    1,    1 },  /* 172: PIYO */
    {  139,    0,   15,    5 },  /* 173: ATTACK 4 S (Att_HADOUKEN) */
    {   84,   61,    3,    3 },  /* 174: ATTACK 2 L (Att_SHOURYUUKEN) */
    {    0,    0,    0,   26 },  /* 175: NEKOROBI S */
    {  140,    0,   16,    2 },  /* 176: OKIAGARI P S */
    {  140,   62,   16,    1 },  /* 177: OKIAGARI P S */
    {  141,   63,   17,    4 },  /* 178: OKIAGARI P S */
    {  142,    0,   17,    4 },  /* 179: OKIAGARI P S */
    {   96,   64,    3,    3 },  /* 180: Att_SENPUUKYAKU (command slot 23) */
    {    2,    1,    1,    2 },  /* 181: ATTACK 6 S (Att_SHOURYUUREPPA), Att_SENPUUKYAKU (command slot 23) */
    {  143,    2,    1,    1 },  /* 182: ATTACK 6 S (Att_SHOURYUUREPPA), Att_SENPUUKYAKU (command slot 23) */
    {    1,    0,    0,    1 },  /* 183: HANASARE */
    {    2,    0,    0,    2 },  /* 184: HANASARE */
    {  144,    0,    1,    1 },  /* 185: ATTACK 3 S (Att_ABISEGERI), ATTACK 3 M (Att_ABISEGERI), ATTACK 3 L (Att_ABISEGERI) */
    {    1,    0,    1,    0 },  /* 186: LOSE SONABA */
    {  145,    0,   20,   32 },  /* 187: PARING AIR F, PARING AIR B */
    {  125,    0,    5,   21 },  /* 188: not used by a script */
    {  146,    0,    5,   21 },  /* 189: ATTACK 1 S (Att_CHOUCHUURENGEKI), ATTACK 1 M (Att_CHOUCHUURENGEKI), ATTACK 1 L (Att_CHOUCHUURENGEKI) */
};

const BODY_BOX sean_body_box[147] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {  -14,  21,   84,  18 },  {  -29,  59,   81,   7 },  {  -29,  59,   32,  49 },  {  -35,  72,    0,  31 },  {    0,   0,    0,   0 } } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +99 */
    { { {  -15,  21,   50,  18 },  {  -30,  58,   43,  13 },  {  -29,  58,   26,  20 },  {  -42,  82,    0,  31 },  {    0,   0,    0,   0 } } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +26 */
    { { {   -1,  18,   96,  16 },  {  -20,  44,   81,  14 },  {  -16,  32,   63,  18 },  {  -26,  42,    0,  64 },  {   -6,  17,  106,  26 } } },  /* 3: saca 56, saca 57, saca 58 +2 */
    { { {   -4,  18,  102,  16 },  {  -24,  44,   90,  14 },  {  -24,  46,   61,  31 },  {  -18,  42,   -3,  73 },  {    0,   0,    0,   0 } } },  /* 4: ATTACK 6 S (Att_SHOURYUUREPPA), saca 56, saca 57 +1 */
    { { {  -16,  23,   78,  16 },  {  -25,  53,   62,  20 },  {  -24,  40,   37,  29 },  {  -38,  66,    0,  35 },  {    0,   0,    0,   0 } } },  /* 5: DASH HUMIKOMI, DASH TOBINOKI, ATTACK 5 S (Att_SLIDE_and_JUMP) */
    { { {   -5,  23,   78,  16 },  {  -25,  53,   67,  20 },  {  -18,  43,   36,  29 },  {  -33,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 6: DASH TOBINOKI */
    { { {  -19,  39,   92,  16 },  {  -32,  64,   78,  15 },  {  -30,  59,   42,  37 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 7: GUARD AIR, V JUMP P M A, V JUMP K S A +8 */
    { { {  -28,  54,   39,  40 },  {  -23,  53,   75,  20 },  {  -28,  54,   39,  40 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 8: not used by a script */
    { { {  -42,  31,   52,  21 },  {  -33,  60,   75,  20 },  {  -25,  52,   36,  37 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 9: not used by a script */
    { { {    0,   0,    0,   0 },  {  -34,  69,   42,  53 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 10: JUMP FRONT, JUMP BACK, SP JUMP FRONT +1 */
    { { {  -11,  23,  106,  16 },  {  -23,  53,   90,  20 },  {  -19,  43,   45,  49 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 11: JUMP JUNBI, SP JUMP JUNBI, JUMP VERTICAL +6 */
    { { {  -18,  23,   99,  16 },  {  -23,  53,   90,  20 },  {  -31,  63,   44,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 12: JUMP VERTICAL, S JUMP FRONT, SP JUMP V +1 */
    { { {  -13,  27,   93,  17 },  {  -22,  57,   76,  20 },  {  -29,  57,   40,  38 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 13: not used by a script */
    { { {  -11,  49,   81,  19 },  {  -39,  79,   42,  52 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 14: not used by a script */
    { { {  -22,  57,   76,  20 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 15: not used by a script */
    { { {  -23,  23,   78,  16 },  {  -31,  53,   63,  20 },  {  -18,  43,   36,  29 },  {  -25,  55,    0,  35 },  {  -42,  12,   70,  20 } } },  /* 16: not used by a script */
    { { {  -14,  21,   84,  18 },  {  -28,  58,   69,  22 },  {  -21,  49,   38,  31 },  {  -28,  63,    0,  38 },  {  -64,  51,   67,  22 } } },  /* 17: S PUNCH A */
    { { {  -30,  23,   82,  16 },  {  -36,  53,   66,  20 },  {  -32,  43,   36,  29 },  {  -32,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 18: M PUNCH B, L PUNCH A, L PUNCH B +4 */
    { { {  -27,  23,   79,  16 },  {  -45,  69,   63,  21 },  {  -32,  52,   36,  29 },  {  -42,  74,    0,  41 },  {  -70,  59,   64,  18 } } },  /* 19: M PUNCH B, UP P GUARD P S */
    { { {  -20,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -32,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 20: M PUNCH B, UP P GUARD P S */
    { { {  -20,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -32,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 21: L PUNCH A, L PUNCH B, atca 156 +1 */
    { { {  -29,  34,   83,  16 },  {  -32,  54,   67,  20 },  {  -26,  43,   36,  29 },  {  -33,  62,    0,  35 },  {  -59,  32,   38,  57 } } },  /* 22: L PUNCH A, L PUNCH B, atca 156 +1 */
    { { {  -29,  34,   83,  16 },  {  -32,  54,   67,  20 },  {  -26,  43,   36,  29 },  {  -33,  62,    0,  35 },  {  -64,  39,   41,  56 } } },  /* 23: L PUNCH A, L PUNCH B, atca 156 +1 */
    { { {  -29,  34,   83,  16 },  {  -32,  54,   67,  20 },  {  -26,  43,   36,  29 },  {  -33,  62,    0,  35 },  {  -49,  46,   57,  54 } } },  /* 24: L PUNCH A, L PUNCH B, atca 156 +1 */
    { { {  -21,  38,   83,  16 },  {  -29,  55,   67,  20 },  {  -21,  44,   47,  22 },  {  -35,  61,    0,  47 },  {    0,   0,    0,   0 } } },  /* 25: not used by a script */
    { { {  -20,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -35,  61,    0,  35 },  {  -57,  33,   74,  14 } } },  /* 26: not used by a script */
    { { {   -6,  26,   82,  16 },  {  -25,  49,   67,  20 },  {  -20,  43,   36,  29 },  {  -36,  80,    0,  35 },  {  -42,  62,   63,  33 } } },  /* 27: not used by a script */
    { { {    0,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -35,  61,    0,  35 },  {    0,   0,    0,   0 } } },  /* 28: not used by a script */
    { { {  -14,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -35,  61,    0,  35 },  {    0,   0,    0,   0 } } },  /* 29: not used by a script */
    { { {  -14,  23,   83,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -25,  28,    0,  35 },  {    0,   0,    0,   0 } } },  /* 30: S KICK A */
    { { {  -24,  31,   84,  16 },  {  -32,  51,   67,  20 },  {  -35,  56,   36,  29 },  {  -44,  56,    0,  35 },  {  -71,  47,   11,  44 } } },  /* 31: S KICK A, M KICK A */
    { { {    7,  23,   83,  16 },  {   -5,  53,   67,  20 },  {   -6,  43,   36,  29 },  {   10,  26,    0,  35 },  {    0,   0,    0,   0 } } },  /* 32: not used by a script */
    { { {   21,  23,   83,  16 },  {    6,  53,   67,  20 },  {   -6,  43,   36,  29 },  {   10,  26,    0,  35 },  {    0,   0,    0,   0 } } },  /* 33: not used by a script */
    { { {   21,  23,   83,  16 },  {    6,  53,   67,  20 },  {   -6,  43,   36,  29 },  {   10,  26,    0,  35 },  {  -49,  50,   60,  12 } } },  /* 34: not used by a script */
    { { {  -33,  23,   86,  15 },  {  -41,  52,   72,  14 },  {  -56,  63,   41,  30 },  {  -47,  55,    0,  42 },  {    0,   0,    0,   0 } } },  /* 35: L KICK A */
    { { {  -33,  23,   83,  16 },  {  -31,  43,   67,  20 },  {  -19,  29,   36,  30 },  {  -47,  55,    0,  42 },  {    0,   0,    0,   0 } } },  /* 36: not used by a script */
    { { {  -39,  31,   89,  16 },  {  -48,  53,   73,  20 },  {  -33,  38,   43,  31 },  {  -47,  55,    0,  42 },  {  -68,  38,   14,  53 } } },  /* 37: L KICK A */
    { { {  -26,  23,   83,  16 },  {  -33,  43,   68,  20 },  {  -25,  29,   35,  30 },  {  -33,  28,    0,  35 },  {    0,   0,    0,   0 } } },  /* 38: L KICK A */
    { { {   -2,  23,   87,  16 },  {  -12,  53,   67,  20 },  {  -13,  43,   36,  29 },  {   -9,  33,    0,  37 },  {    0,   0,    0,   0 } } },  /* 39: not used by a script */
    { { {    7,  31,   82,  16 },  {  -16,  77,   59,  25 },  {  -39,  67,   46,  18 },  {  -28,  63,    0,  38 },  {  -82,  82,   55,  19 } } },  /* 40: not used by a script */
    { { {   16,  24,   82,  19 },  {    3,  53,   67,  20 },  {  -16,  48,   32,  32 },  {  -28,  63,    0,  38 },  {  -51,  45,   42,  22 } } },  /* 41: not used by a script */
    { { {   14,  23,   82,  16 },  {    3,  53,   67,  20 },  {   -8,  43,   36,  29 },  {    8,  33,    0,  37 },  {    0,   0,    0,   0 } } },  /* 42: not used by a script */
    { { {  -32,  23,   82,  16 },  {  -46,  53,   67,  20 },  {  -39,  43,   36,  29 },  {  -43,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 43: not used by a script */
    { { {  -35,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {    0,   0,    0,   0 } } },  /* 44: not used by a script */
    { { {  -35,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {   50,  19,   75,  27 } } },  /* 45: not used by a script */
    { { {  -35,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {  -55,  19,   57,  27 } } },  /* 46: L KICK A */
    { { {  -35,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {  -64,  19,   62,  27 } } },  /* 47: not used by a script */
    { { {  -35,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {  -85,  48,   63,  19 } } },  /* 48: not used by a script */
    { { {  -20,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {  -85,  48,   51,  19 } } },  /* 49: not used by a script */
    { { {  -20,  23,   88,  16 },  {  -46,  46,   67,  20 },  {  -52,  43,   36,  29 },  {  -43,  34,    0,  35 },  {    0,   0,    0,   0 } } },  /* 50: not used by a script */
    { { {  -31,  23,   88,  16 },  {  -44,  46,   67,  20 },  {  -39,  43,   36,  29 },  {  -43,  50,    0,  35 },  {    0,   0,    0,   0 } } },  /* 51: L KICK A */
    { { {  -14,  31,   86,  16 },  {  -25,  53,   67,  20 },  {  -29,  45,   36,  29 },  {  -25,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 52: L KICK B */
    { { {    2,  23,   86,  16 },  {  -27,  60,   74,  20 },  {  -50,  82,   39,  42 },  {  -32,  64,    0,  39 },  {  -77,  52,   64,  33 } } },  /* 53: not used by a script */
    { { {    2,  23,   86,  16 },  {  -27,  60,   74,  20 },  {  -35,  60,   39,  42 },  {  -26,  55,    0,  35 },  {  -57,  45,    0,  76 } } },  /* 54: L KICK B */
    { { {    2,  23,   86,  16 },  {  -27,  60,   74,  20 },  {  -35,  60,   39,  42 },  {  -26,  55,    0,  35 },  {  -57,  45,    0,  76 } } },  /* 55: L KICK B */
    { { {    2,  23,   86,  16 },  {  -27,  60,   74,  20 },  {  -35,  60,   39,  42 },  {  -26,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 56: L KICK B */
    { { {    2,  23,   86,  16 },  {  -27,  60,   74,  20 },  {  -35,  60,   39,  42 },  {  -26,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 57: L KICK B */
    { { {   -4,  23,   90,  16 },  {  -25,  53,   67,  20 },  {  -18,  43,   36,  29 },  {  -25,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 58: L KICK C */
    { { {    6,  23,   86,  16 },  {  -14,  53,   67,  20 },  {  -18,  43,   36,  29 },  {  -25,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 59: L KICK C */
    { { {   20,  23,   77,  16 },  {  -14,  53,   67,  20 },  {  -18,  43,   36,  29 },  {  -25,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 60: TOUKETSU A, L KICK C */
    { { {   37,  23,   65,  16 },  {    4,  53,   54,  20 },  {  -14,  43,   36,  29 },  {  -15,  36,    0,  35 },  {  -32,  38,   65,  11 } } },  /* 61: L KICK C */
    { { {   37,  23,   65,  16 },  {    4,  53,   54,  20 },  {  -14,  43,   36,  29 },  {  -15,  36,    0,  35 },  {    0,   0,    0,   0 } } },  /* 62: L KICK C */
    { { {   32,  23,   78,  16 },  {    4,  53,   64,  20 },  {  -14,  43,   36,  29 },  {  -15,  36,    0,  35 },  {    0,   0,    0,   0 } } },  /* 63: L KICK C */
    { { {  -23,  26,   48,  18 },  {  -30,  58,   43,  18 },  {  -18,  43,   20,  26 },  {  -42,  70,    0,  58 },  {  -61,  52,   43,   9 } } },  /* 64: KAGAMI P A */
    { { {  -14,  23,   50,  16 },  {  -21,  43,   37,  18 },  {  -18,  43,   20,  26 },  {  -42,  70,    0,  58 },  {  -57,  45,   38,  17 } } },  /* 65: KAGAMI P A */
    { { {  -14,  23,   50,  16 },  {  -21,  43,   37,  18 },  {  -18,  43,   20,  26 },  {  -42,  70,    0,  58 },  {    0,   0,    0,   0 } } },  /* 66: KAGAMI P A */
    { { {  -24,  25,   70,  19 },  {  -37,  63,   61,  18 },  {    0,   0,    0,   0 },  {  -47,  74,    0,  60 },  {  -52,  24,   27,  33 } } },  /* 67: KAGAMI P A */
    { { {   -5,  23,   80,  16 },  {  -26,  62,   66,  18 },  {  -18,  43,   37,  29 },  {  -48,  78,    0,  52 },  {  -43,  43,   40,  76 } } },  /* 68: KAGAMI P A */
    { { {   -7,  23,   75,  16 },  {  -18,  44,   60,  18 },  {  -19,  43,   37,  29 },  {  -42,  70,    0,  58 },  {  -35,  33,   51,  59 } } },  /* 69: not used by a script */
    { { {   -8,  23,   69,  16 },  {  -17,  36,   53,  18 },  {  -21,  43,   31,  29 },  {  -42,  70,    0,  58 },  {    0,   0,    0,   0 } } },  /* 70: KAGAMI P A */
    { { {  -15,  21,   50,  18 },  {  -30,  58,   43,  13 },  {  -29,  58,   26,  20 },  {  -38,  72,    0,  30 },  {    0,   0,    0,   0 } } },  /* 71: KAGAMI K A */
    { { {  -16,  34,   58,  18 },  {  -35,  63,   46,  18 },  {  -54,  93,   21,  28 },  {  -85, 128,    0,  21 },  {  -72,  48,    0,  41 } } },  /* 72: KAGAMI K A */
    { { {   -8,  25,   57,  17 },  {  -44,  77,   39,  23 },  {  -23,  65,   20,  26 },  {  -59, 103,    0,  28 },  {    0,   0,    0,   0 } } },  /* 73: KAGAMI K A, UP P GUARD K S */
    { { {   -6,  32,   51,  24 },  {  -33,  87,   41,  26 },  {  -66, 111,   21,  26 },  {  -54, 114,    0,  23 },  {  -88,  62,    0,  28 } } },  /* 74: KAGAMI K A, UP P GUARD K S */
    { { {   -6,  24,   58,  19 },  {  -36,  80,   43,  21 },  {  -31,  84,   20,  26 },  {  -64, 122,    0,  32 },  {    0,   0,    0,   0 } } },  /* 75: KAGAMI K A, UP P GUARD K S */
    { { {  -31,  45,   58,  18 },  {  -54,  89,   43,  18 },  {    0,   0,    0,   0 },  {  -55,  92,    0,  43 },  {    0,   0,    0,   0 } } },  /* 76: KAGAMI K A */
    { { {  -29,  49,   57,  20 },  {  -58,  96,   39,  22 },  {  -24,  43,   20,  26 },  {  -92, 130,    0,  24 },  {  -73,  65,   17,  27 } } },  /* 77: KAGAMI K A */
    { { {  -39,  23,   91,  21 },  {  -41,  75,   83,  23 },  {  -43,  79,   39,  47 },  {  -53,  16,   41,  51 },  {    0,   0,    0,   0 } } },  /* 78: V JUMP P S A, V JUMP P L A, F JUMP P S A */
    { { {  -18,  23,  107,  16 },  {  -25,  53,   74,  20 },  {  -17,  43,   47,  35 },  {    0,   0,    0,   0 },  {  -74,  54,   68,  49 } } },  /* 79: V JUMP P L A, V JUMP K M A */
    { { {  -18,  23,  107,  16 },  {  -25,  53,   74,  20 },  {  -17,  43,   47,  35 },  {    0,   0,    0,   0 },  {  -80,  64,   95,  15 } } },  /* 80: V JUMP P L A, F JUMP P S A */
    { { {   -6,  23,  100,  16 },  {  -25,  53,   86,  20 },  {  -33,  69,   37,  52 },  {    0,   0,    0,   0 },  {  -79,  64,   53,  25 } } },  /* 81: V JUMP K M A */
    { { {  -20,  23,   92,  16 },  {  -23,  53,   75,  20 },  {  -33,  53,   36,  37 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 82: V JUMP K S A, F JUMP K S A */
    { { {  -19,  20,   92,  14 },  {  -32,  61,   80,  14 },  {  -27,  48,   48,  32 },  {    0,   0,    0,   0 },  {  -66,  47,   42,  43 } } },  /* 83: F JUMP K M A, F JUMP K L A */
    { { {  -11,  23,  106,  16 },  {  -23,  53,   90,  20 },  {  -29,  57,   43,  40 },  {    0,   0,    0,   0 },  {  -76,  71,   70,  20 } } },  /* 84: V JUMP K L A, ATTACK 2 L (Att_SHOURYUUKEN) */
    { { {  -28,  38,   74,  16 },  {  -37,  65,   56,  20 },  {  -19,  43,   36,  29 },  {  -46,  80,    0,  35 },  {    0,   0,    0,   0 } } },  /* 85: not used by a script */
    { { {  -31,  29,   70,  16 },  {  -42,  77,   55,  23 },  {  -19,  43,   36,  29 },  {  -46,  80,    0,  35 },  {    0,   0,    0,   0 } } },  /* 86: ATTACK 4 S (Att_HADOUKEN) */
    { { {  -12,  18,   86,  14 },  {  -24,  52,   76,  14 },  {  -26,  53,   57,  22 },  {  -24,  56,    0,  62 },  {    0,   0,    0,   0 } } },  /* 87: exca 17, ATTACK 5 S (Att_SLIDE_and_JUMP) */
    { { {  -12,  20,  102,  15 },  {  -29,  50,   88,  14 },  {  -26,  45,   53,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 88: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +2 */
    { { {  -12,  20,  102,  15 },  {  -29,  50,   88,  14 },  {  -26,  45,   41,  59 },  {    0,   0,    0,   0 },  {  -72, 101,   48,  38 } } },  /* 89: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +2 */
    { { {  -10,  18,   98,  14 },  {  -24,  48,   88,  14 },  {  -31,  60,   30,  62 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 90: not used by a script */
    { { {   -3,  23,   83,  16 },  {  -17,  43,   72,  20 },  {   -8,  37,   40,  29 },  {  -20,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 91: not used by a script */
    { { {   -6,  23,   83,  16 },  {  -20,  53,   67,  20 },  {  -12,  38,   36,  29 },  {  -22,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 92: not used by a script */
    { { {   -6,  23,   49,  16 },  {  -16,  42,   37,  18 },  {  -18,  44,   20,  26 },  {  -28,  55,    0,  31 },  {    0,   0,    0,   0 } } },  /* 93: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -27,  36,    0,  53 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 94: not used by a script */
    { { {  -20,  23,   89,  16 },  {  -25,  53,   74,  20 },  {  -17,  43,   47,  35 },  {    0,   0,    0,   0 },  {  -40,  25,   69,  19 } } },  /* 95: not used by a script */
    { { {  -32,  27,   89,  24 },  {  -34,  66,   79,  27 },  {  -25,  69,   50,  35 },  {    0,   0,    0,   0 },  {  -77,  59,   60,  44 } } },  /* 96: V JUMP P M A, F JUMP P M A, F JUMP P L A +1 */
    { { {  -13,  22,  100,  17 },  {  -34,  65,   88,  14 },  {  -29,  60,   38,  53 },  {    0,   0,    0,   0 },  {  -57,  56,   56,  16 } } },  /* 97: not used by a script */
    { { {  -13,  22,  100,  17 },  {  -34,  65,   88,  14 },  {  -29,  60,   38,  53 },  {    0,   0,    0,   0 },  {  -13,  56,   55,  16 } } },  /* 98: not used by a script */
    { { {  -12,  18,   90,  14 },  {  -26,  50,   80,  14 },  {  -20,  34,   50,  28 },  {  -30,  54,   10,  38 },  {    0,   0,    0,   0 } } },  /* 99: not used by a script */
    { { {  -10,  18,   84,  14 },  {  -24,  52,   74,  14 },  {  -24,  40,   40,  30 },  {  -10,  36,    0,  38 },  {    0,   0,    0,   0 } } },  /* 100: not used by a script */
    { { {   -2,  18,   84,  14 },  {  -24,  52,   76,  14 },  {  -18,  36,   38,  34 },  {  -28,  50,    0,  36 },  {    0,   0,    0,   0 } } },  /* 101: not used by a script */
    { { {   14,  18,   78,  14 },  {  -18,  52,   70,  14 },  {  -28,  48,   38,  30 },  {  -24,  26,    0,  36 },  {    0,   0,    0,   0 } } },  /* 102: not used by a script */
    { { {   36,  18,   66,  14 },  {   12,  24,   50,  28 },  {  -30,  40,   44,  30 },  {  -20,  28,    0,  42 },  {  -64,  32,   64,  16 } } },  /* 103: not used by a script */
    { { {   34,  18,   68,  14 },  {   12,  24,   48,  30 },  {  -30,  40,   44,  28 },  {  -18,  28,    0,  42 },  {  -60,  28,   46,  16 } } },  /* 104: not used by a script */
    { { {   20,  18,   78,  14 },  {  -12,  52,   64,  20 },  {  -24,  48,   30,  32 },  {   -8,  30,    0,  30 },  {    0,   0,    0,   0 } } },  /* 105: not used by a script */
    { { {  -23,  18,   86,  14 },  {  -30,  52,   73,  14 },  {  -19,  37,   41,  30 },  {  -38,  72,    2,  36 },  {    0,   0,    0,   0 } } },  /* 106: not used by a script */
    { { {  -31,  23,   79,  16 },  {  -34,  53,   63,  20 },  {  -28,  43,   36,  29 },  {  -33,  55,    0,  35 },  {  -50,  26,   63,  26 } } },  /* 107: not used by a script */
    { { {  -14,  21,   84,  18 },  {  -28,  58,   69,  22 },  {  -21,  49,   38,  31 },  {  -28,  63,    0,  38 },  {  -33,  21,   54,  19 } } },  /* 108: M PUNCH A */
    { { {  -23,  18,   81,  14 },  {  -34,  52,   67,  14 },  {  -25,  40,   38,  30 },  {  -28,  56,    0,  36 },  {  -46,  16,   74,  18 } } },  /* 109: not used by a script */
    { { {  -18,  23,   81,  16 },  {  -30,  61,   70,  15 },  {  -46,  72,   38,  30 },  {  -33,  65,    0,  36 },  {    0,   0,    0,   0 } } },  /* 110: M PUNCH A */
    { { {  -28,  46,   89,  16 },  {  -35,  60,   69,  26 },  {  -72, 100,   49,  22 },  {  -85, 102,   46,  16 },  {  -72,  41,   71,  15 } } },  /* 111: not used by a script */
    { { {  -24,  23,   79,  16 },  {  -25,  44,   67,  20 },  {  -18,  43,   36,  29 },  {  -32,  55,    0,  35 },  {  -52,  18,   51,  26 } } },  /* 112: not used by a script */
    { { {  -24,  18,   90,  14 },  {  -17,  52,   79,  14 },  {   -9,  40,   47,  30 },  {  -24,  56,    0,  36 },  {    0,   0,    0,   0 } } },  /* 113: not used by a script */
    { { {  -24,  18,   90,  14 },  {  -17,  52,   79,  14 },  {   -9,  40,   47,  30 },  {  -24,  56,    0,  36 },  {  -59,  41,   78,  10 } } },  /* 114: not used by a script */
    { { {    2,  23,   64,  16 },  {  -15,  33,   53,  20 },  {  -18,  43,   36,  29 },  {  -25,  61,    0,  35 },  {    0,   0,    0,   0 } } },  /* 115: ATTACK 3 S (Att_ABISEGERI), ATTACK 3 M (Att_ABISEGERI) */
    { { {    2,  23,   64,  16 },  {  -20,  39,   52,  19 },  {  -36,  83,   46,  54 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 116: ATTACK 3 S (Att_ABISEGERI), ATTACK 3 M (Att_ABISEGERI), ATTACK 3 L (Att_ABISEGERI) */
    { { {    4,  23,   64,  16 },  {  -38, 113,   56,  31 },  {  -37,  98,   52,  47 },  {  -22,  65,   68,  21 },  {    0,   0,    0,   0 } } },  /* 117: not used by a script */
    { { {    6,  38,   72,  16 },  {  -22,  72,   50,  20 },  {  -45,  96,   49,  47 },  {    0,   0,    0,   0 },  {  -45,  51,   71,  53 } } },  /* 118: ATTACK 5 S (Att_SLIDE_and_JUMP) */
    { { {  -28,  55,   71,  26 },  {  -47,  84,   36,  48 },  {  -28,  84,   48,  28 },  {    0,   0,    0,   0 },  {  -89,  71,   35,  43 } } },  /* 119: ATTACK 3 S (Att_ABISEGERI), ATTACK 3 M (Att_ABISEGERI), ATTACK 3 L (Att_ABISEGERI) +1 */
    { { {   -8,  36,   65,  28 },  {  -35,  91,   55,  20 },  {  -73, 115,   18,  40 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 120: ATTACK 3 S (Att_ABISEGERI), ATTACK 3 M (Att_ABISEGERI), ATTACK 3 L (Att_ABISEGERI) +1 */
    { { {  -17,  37,   77,  14 },  {  -24,  52,   66,  17 },  {  -24,  53,   47,  17 },  {  -17,  40,   37,  15 },  {    0,   0,    0,   0 } } },  /* 121: AIR S, AIR M, AIR L +39 */
    { { {  -20,  23,   68,  16 },  {  -23,  50,   55,  14 },  {  -20,  43,   38,  15 },  {  -25,  55,    0,  35 },  {    0,   0,    0,   0 } } },  /* 122: ATTACK 1 S (Att_CHOUCHUURENGEKI), ATTACK 1 L (Att_CHOUCHUURENGEKI) */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -44,  66,   33,  16 },  {  -59,  94,    0,  34 },  {    0,   0,    0,   0 } } },  /* 123: ATTACK 1 S (Att_CHOUCHUURENGEKI), ATTACK 1 M (Att_CHOUCHUURENGEKI), ATTACK 1 L (Att_CHOUCHUURENGEKI) */
    { { {  -54,  22,   36,  16 },  {  -49,  53,   36,  17 },  {  -39,  43,   31,  11 },  {  -56,  94,    0,  32 },  {    0,   0,    0,   0 } } },  /* 124: ATTACK 1 S (Att_CHOUCHUURENGEKI), ATTACK 1 M (Att_CHOUCHUURENGEKI), ATTACK 1 L (Att_CHOUCHUURENGEKI) +1 */
    { { {  -75,  23,   30,  16 },  {  -67,  53,   37,  13 },  {  -54,  43,   25,  16 },  {  -60, 101,    0,  25 },  {    0,   0,    0,   0 } } },  /* 125: ATTACK 1 S (Att_CHOUCHUURENGEKI), ATTACK 1 M (Att_CHOUCHUURENGEKI), ATTACK 1 L (Att_CHOUCHUURENGEKI) */
    { { {    0,   0,    0,   0 },  {  -23,  50,   22,  18 },  {  -18,  43,    9,  26 },  {  -28,  55,    0,  23 },  {    0,   0,    0,   0 } } },  /* 126: Att_CHOUCHUURENGEKI (command slot 25) */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -28,  55,    0,  23 },  {    0,   0,    0,   0 } } },  /* 127: not used by a script */
    { { {    0,  16,   85,  16 },  {   -8,  48,   72,  16 },  {   -4,  40,   48,  24 },  {   -8,  40,   48,  24 },  {    0,   0,    0,   0 } } },  /* 128: FUSHIN P S */
    { { {    0,  16,   85,  16 },  {   -8,  48,   72,  16 },  {   -4,  40,   48,  24 },  {   -8,  40,   48,  24 },  {  -48,  40,   72,  16 } } },  /* 129: FUSHIN P S */
    { { {  -34,  26,   73,  16 },  {  -27,  48,   61,  14 },  {  -25,  46,   38,  24 },  {  -38,  67,    0,  36 },  {    0,   0,    0,   0 } } },  /* 130: not used by a script */
    { { {  -34,  26,   49,  16 },  {  -27,  48,   46,  14 },  {  -27,  46,   30,  24 },  {  -38,  67,    0,  36 },  {    0,   0,    0,   0 } } },  /* 131: saca 56, saca 57, saca 58 */
    { { {  -28,  57,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 132: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -87,  99,   30,  50 },  {  -86,  98,    0,  36 },  {    0,   0,    0,   0 } } },  /* 133: ATTACK 5 S (Att_SLIDE_and_JUMP) */
    { { {  -23,  21,   96,  18 },  {    0,   0,    0,   0 },  {  -50,  69,   40,  65 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 134: Att_SENPUUKYAKU (command slot 23) */
    { { {  -32,  27,   89,  24 },  {  -65,  96,   79,  27 },  {  -72, 104,   49,  33 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 135: saca 60 */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -28,  56,   28,  78 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 136: not used by a script */
    { { {   -9,  21,   84,  18 },  {  -11,  54,   81,   7 },  {  -11,  52,   41,  40 },  {  -28,  63,    0,  38 },  {    0,   0,    0,   0 } } },  /* 137: PIYO */
    { { {  -34,  21,   80,  18 },  {  -43,  68,   69,  17 },  {  -28,  52,   38,  30 },  {  -29,  63,    0,  38 },  {    0,   0,    0,   0 } } },  /* 138: PIYO */
    { { {  -19,  23,   70,  16 },  {  -68,  95,   55,  23 },  {  -19,  43,   36,  29 },  {  -26,  58,    0,  35 },  {    0,   0,    0,   0 } } },  /* 139: ATTACK 4 S (Att_HADOUKEN) */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -41,  81,    0,  24 },  {    0,   0,    0,   0 } } },  /* 140: OKIAGARI P S */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -41,  82,    0,  61 },  {    0,   0,    0,   0 } } },  /* 141: OKIAGARI P S */
    { { {  -20,  41,   96,  27 },  {  -29,  58,   82,  14 },  {  -29,  58,   64,  18 },  {  -33,  66,    0,  64 },  {    0,   0,    0,   0 } } },  /* 142: OKIAGARI P S */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -25,  51,   34,  61 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 143: ATTACK 6 S (Att_SHOURYUUREPPA), Att_SENPUUKYAKU (command slot 23) */
    { { {  -29,  30,   84,  18 },  {  -40,  66,   78,   8 },  {  -39,  68,   38,  40 },  {  -52,  82,    0,  38 },  {    0,   0,    0,   0 } } },  /* 144: ATTACK 3 S (Att_ABISEGERI), ATTACK 3 M (Att_ABISEGERI), ATTACK 3 L (Att_ABISEGERI) */
    { { {    0,   0,    0,   0 },  {  -31,  63,   22,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 145: PARING AIR F, PARING AIR B */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -44,  66,   33,  32 },  {  -59,  94,    0,  34 },  {    0,   0,    0,   0 } } },  /* 146: ATTACK 1 S (Att_CHOUCHUURENGEKI), ATTACK 1 M (Att_CHOUCHUURENGEKI), ATTACK 1 L (Att_CHOUCHUURENGEKI) */
};

const ATTACK_BOX sean_att_box[65] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {    0,   0,    0,   0 },  {  -54,  26,   28,  30 },  {    0,   0,    0,   0 } } },  /* 1: ATTACK 6 S (Att_SHOURYUUREPPA), saca 56, saca 57 +2; attack 1, 41, 42, 69 ... */
    { { {    0,   0,    0,   0 },  {  -29,  29,   34,  77 },  {  -46,  24,   48,  29 } } },  /* 2: ATTACK 6 S (Att_SHOURYUUREPPA), saca 56, saca 57 +2; attack 2, 42, 46, 74 ... */
    { { {    0,   0,    0,   0 },  {  -40,  18,   58,  16 },  {  -26,  14,  122,  20 } } },  /* 3: saca 56, saca 57, saca 58 */
    { { {    0,   0,    0,   0 },  {  -52,  11,   78,  18 },  {  -38,  12,   68,  20 } } },  /* 4: not used by a script */
    { { {    0,   0,    0,   0 },  {  -70,  52,   74,  12 },  {    0,   0,    0,   0 } } },  /* 5: S PUNCH A; attack 4 */
    { { {    0,   0,    0,   0 },  {  -60,  38,   44,  27 },  {    0,   0,    0,   0 } } },  /* 6: M PUNCH A; attack 5 */
    { { {    0,   0,    0,   0 },  {  -86,  65,   64,  18 },  {    0,   0,    0,   0 } } },  /* 7: M PUNCH B, UP P GUARD P S; attack 6 */
    { { {    0,   0,    0,   0 },  {  -69,  44,   49,  33 },  {    0,   0,    0,   0 } } },  /* 8: L PUNCH A, L PUNCH B, atca 156 +1; attack 7, 8 */
    { { {    0,   0,    0,   0 },  {  -48,  31,   80,  33 },  {    0,   0,    0,   0 } } },  /* 9: L PUNCH A, L PUNCH B, atca 156 +1; attack 7, 8 */
    { { {    0,   0,    0,   0 },  {  -74,  28,   78,  16 },  {  -47,  25,   77,  13 } } },  /* 10: not used by a script */
    { { {    0,   0,    0,   0 },  {  -59,  34,   11,  48 },  {    0,   0,    0,   0 } } },  /* 11: S KICK A; attack 10 */
    { { {    0,   0,    0,   0 },  {  -75,  46,   65,  15 },  {  -35,  35,   59,  13 } } },  /* 12: not used by a script */
    { { {    0,   0,    0,   0 },  {  -87,  32,   12,  20 },  {  -64,  42,   34,  18 } } },  /* 13: M KICK A; attack 12 */
    { { {    0,   0,    0,   0 },  {  -88,  63,    7,  14 },  {    0,   0,    0,   0 } } },  /* 14: not used by a script */
    { { {    0,   0,    0,   0 },  {  -78,  44,   48,  24 },  {    0,   0,    0,   0 } } },  /* 15: L KICK A; attack 17 */
    { { {    0,   0,    0,   0 },  {  -85,  17,   90,  32 },  {  -69,  19,   68,  26 } } },  /* 16: not used by a script */
    { { {    0,   0,    0,   0 },  { -115,  37,   72,  18 },  {  -77,  41,   64,  19 } } },  /* 17: not used by a script */
    { { {    0,   0,    0,   0 },  {  -83,  36,   70,  17 },  {  -47,  36,   52,  29 } } },  /* 18: not used by a script */
    { { {    0,   0,    0,   0 },  {  -85,  33,   74,  10 },  {  -52,  37,   63,  15 } } },  /* 19: L KICK B; attack 17 */
    { { {    0,   0,    0,   0 },  {  -78,  42,   74,  14 },  {  -50,  39,   63,  12 } } },  /* 20: L KICK C; attack 18 */
    { { {    0,   0,    0,   0 },  {  -60,  52,   41,  13 },  {    0,   0,    0,   0 } } },  /* 21: KAGAMI P A; attack 19 */
    { { {    0,   0,    0,   0 },  {  -72,  52,   40,  14 },  {    0,   0,    0,   0 } } },  /* 22: KAGAMI P A; attack 20 */
    { { {    0,   0,    0,   0 },  {  -60,  36,   30,  35 },  {    0,   0,    0,   0 } } },  /* 23: KAGAMI P A; attack 21 */
    { { {    0,   0,    0,   0 },  {  -23,  20,   89,  33 },  {  -38,  23,   61,  28 } } },  /* 24: KAGAMI P A; attack 22 */
    { { {    0,   0,    0,   0 },  {  -80,  54,    0,   5 },  {    0,   0,    0,   0 } } },  /* 25: KAGAMI K A; attack 23 */
    { { {    0,   0,    0,   0 },  {  -86,  76,    0,   5 },  {    0,   0,    0,   0 } } },  /* 26: KAGAMI K A, UP P GUARD K S; attack 24 */
    { { {    0,   0,    0,   0 },  {  -96,  75,    0,   6 },  {  -57,  45,    2,  21 } } },  /* 27: KAGAMI K A; attack 25 */
    { { {    0,   0,    0,   0 },  {  -49,  43,   53,  24 },  {    0,   0,    0,   0 } } },  /* 28: V JUMP P S A, F JUMP P S A; attack 26, 32 */
    { { {    0,   0,    0,   0 },  {  -90,  32,   91,  10 },  {    0,   0,    0,   0 } } },  /* 29: V JUMP P L A; attack 34 */
    { { {    0,   0,    0,   0 },  {  -87,  70,   55,  21 },  {    0,   0,    0,   0 } } },  /* 30: V JUMP K M A; attack 30 */
    { { {    0,   0,    0,   0 },  {  -55,  16,   91,  25 },  {  -46,  20,   74,  20 } } },  /* 31: not used by a script */
    { { {    0,   0,    0,   0 },  {  -76,  25,   44,  20 },  {  -56,  36,   58,  20 } } },  /* 32: V JUMP P M A, F JUMP P M A, F JUMP P L A; attack 27, 33, 34 */
    { { {    0,   0,    0,   0 },  {  -32,  24,   48,  19 },  {    0,   0,    0,   0 } } },  /* 33: V JUMP K S A, F JUMP K S A; attack 35 */
    { { {    0,   0,    0,   0 },  {  -72,  10,   61,  15 },  {  -62,  85,   54,   8 } } },  /* 34: F JUMP K M A; attack 36 */
    { { {    0,   0,    0,   0 },  {  -52,  24,   18,  28 },  {  -36,  24,    4,  28 } } },  /* 35: not used by a script */
    { { {    0,   0,    0,   0 },  {  -55,  16,   91,  25 },  {  -46,  20,   74,  20 } } },  /* 36: not used by a script */
    { { {    0,   0,    0,   0 },  {  -95,  45,   93,  13 },  {  -57,  42,   79,  14 } } },  /* 37: V JUMP K L A; attack 31 */
    { { {    0,   0,    0,   0 },  {  -47,  40,   25,  48 },  {    0,   0,    0,   0 } } },  /* 38: exca 17, ATTACK 5 S (Att_SLIDE_and_JUMP); attack 60 */
    { { {    0,   0,    0,   0 },  {  -75,  55,   56,  14 },  {    0,   0,    0,   0 } } },  /* 39: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +1; attack 56, 57, 58, 84 */
    { { {    0,   0,    0,   0 },  { -108,  39,   52,  13 },  {  -72,  32,   55,  13 } } },  /* 40: not used by a script */
    { { {  -31,   6,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 41: M PUNCH A, M PUNCH B, M KICK A +3; attack 48 */
    { { {    0,   0,    0,   0 },  {  -26,  30,   90,  29 },  {    0,   0,    0,   0 } } },  /* 42: ATTACK 5 S (Att_SLIDE_and_JUMP) */
    { { {    0,   0,    0,   0 },  {  -68,  47,   50,  11 },  {    0,   0,    0,   0 } } },  /* 43: ATTACK 3 S (Att_ABISEGERI), ATTACK 3 M (Att_ABISEGERI), ATTACK 3 L (Att_ABISEGERI) +1; attack 49, 50 */
    { { {    0,   0,    0,   0 },  {  -54,  31,   15,  69 },  {    0,   0,    0,   0 } } },  /* 44: not used by a script */
    { { {  -77,  33,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 45: ATTACK 1 S (Att_CHOUCHUURENGEKI), ATTACK 1 M (Att_CHOUCHUURENGEKI), ATTACK 1 L (Att_CHOUCHUURENGEKI); attack 52 */
    { { {    0,   0,    0,   0 },  {   23,  31,   85,  10 },  {    9,  27,   75,  15 } } },  /* 46: not used by a script */
    { { {    0,   0,    0,   0 },  {  -66,  18,   72,  16 },  {  -48,  40,   75,  10 } } },  /* 47: FUSHIN P S; attack 63 */
    { { {    0,   0,    0,   0 },  {  -79,  21,   31,  30 },  {  -58,  30,    0,  64 } } },  /* 48: ATTACK 5 S (Att_SLIDE_and_JUMP); attack 64, 73 */
    { { {    0,   0,    0,   0 },  {  -71,  11,   43,  14 },  {  -69,  58,   57,   7 } } },  /* 49: F JUMP K L A; attack 37 */
    { { {    0,   0,    0,   0 },  { -100,  37,    0,  19 },  {  -57,  45,    2,  21 } } },  /* 50: not used by a script */
    { { {    0,   0,    0,   0 },  {  -79,  58,   24,  72 },  {    0,   0,    0,   0 } } },  /* 51: ATTACK 5 S (Att_SLIDE_and_JUMP); attack 71, 72 */
    { { {    0,   0,    0,   0 },  {  -96, 109,   30,  51 },  {    0,   0,    0,   0 } } },  /* 52: ATTACK 5 S (Att_SLIDE_and_JUMP); attack 61, 62 */
    { { {    0,   0,    0,   0 },  {  -51,  55,   41,  85 },  {    0,   0,    0,   0 } } },  /* 53: ATTACK 5 S (Att_SLIDE_and_JUMP); attack 49 */
    { { {    0,   0,    0,   0 },  {  -92,  83,   34,  73 },  {    0,   0,    0,   0 } } },  /* 54: not used by a script */
    { { {  -35,  10,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 55: L PUNCH A, L PUNCH B, L KICK A +2; attack 48 */
    { { {    0,   0,    0,   0 },  {    2,  34,   80,  41 },  {    0,   0,    0,   0 } } },  /* 56: not used by a script */
    { { {    0,   0,    0,   0 },  {  -44,  42,  106,  24 },  {    0,   0,    0,   0 } } },  /* 57: not used by a script */
    { { {    0,   0,    0,   0 },  {  -66,  58,   91,  29 },  {    0,   0,    0,   0 } } },  /* 58: Att_SENPUUKYAKU (command slot 23); attack 78 */
    { { {    0,   0,    0,   0 },  {  -65,  90,   88,  29 },  {    0,   0,    0,   0 } } },  /* 59: not used by a script */
    { { {    0,   0,    0,   0 },  {  -49,  26,   29,  49 },  {    0,   0,    0,   0 } } },  /* 60: saca 60; attack 77 */
    { { {    0,   0,    0,   0 },  {  -71,  35,   87,  16 },  {  -34,  15,   66,  31 } } },  /* 61: ATTACK 2 L (Att_SHOURYUUKEN); attack 85 */
    { { {    0,   0,    0,   0 },  {  -41,  81,    0,  24 },  {    0,   0,    0,   0 } } },  /* 62: OKIAGARI P S; attack 76 */
    { { {    0,   0,    0,   0 },  {  -42,  27,   42,  33 },  {  -30,  26,  100,  39 } } },  /* 63: OKIAGARI P S; attack 2, 76 */
    { { {    0,   0,    0,   0 },  {  -66,  47,   74,  17 },  {    0,   0,    0,   0 } } },  /* 64: Att_SENPUUKYAKU (command slot 23); attack 78, 83 */
};

const CAUGHT_BOX sean_cau_box[21] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -25,   50,    0,   16 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +100 */
    { {  -29,   54,    0,    8 } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +26 */
    { {  -18,   45,   52,   40 } },  /* 3: ATTACK 6 S (Att_SHOURYUUREPPA), saca 56, saca 57 +15 */
    { {  -31,   63,   44,   44 } },  /* 4: JUMP FRONT, JUMP BACK, SP JUMP FRONT +12 */
    { {  -42,   42,    0,   16 } },  /* 5: ATTACK 1 S (Att_CHOUCHUURENGEKI), ATTACK 1 M (Att_CHOUCHUURENGEKI), ATTACK 1 L (Att_CHOUCHUURENGEKI) +1 */
    { {  -21,   36,    0,   90 } },  /* 6: not used by a script */
    { {  -36,   36,    0,   90 } },  /* 7: not used by a script */
    { {  -29,   54,    0,   16 } },  /* 8: S KICK A, M KICK A */
    { {  -33,   58,    0,    8 } },  /* 9: KAGAMI P A, KAGAMI K A */
    { {  -28,   48,    0,   58 } },  /* 10: not used by a script */
    { {  -28,   45,   46,   61 } },  /* 11: not used by a script */
    { {  -27,   47,   52,   45 } },  /* 12: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +2 */
    { {  -21,   45,   45,   44 } },  /* 13: AIR S, AIR M, AIR L +39 */
    { {   -8,   40,   66,   25 } },  /* 14: FUSHIN P S */
    { {  -46,   80,    0,   16 } },  /* 15: ATTACK 4 S (Att_HADOUKEN), ATTACK 5 S (Att_SLIDE_and_JUMP) */
    { {  -41,   81,    0,   16 } },  /* 16: OKIAGARI P S */
    { {  -36,   73,   46,   49 } },  /* 17: OKIAGARI P S */
    { {  -38,   63,    0,   16 } },  /* 18: DASH HUMIKOMI, DASH TOBINOKI */
    { {  -35,   70,    0,   16 } },  /* 19: not used by a script */
    { {  -31,   63,   22,   44 } },  /* 20: PARING AIR F, PARING AIR B */
};

const HOSEI_BOX sean_hos_box[28] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -25,   50,    0,   86 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +104 */
    { {  -25,   50,    0,   54 } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +47 */
    { {  -18,   45,   52,   40 } },  /* 3: GUARD AIR, V JUMP P M A, V JUMP K S A +15 */
    { {  -31,   63,   44,   44 } },  /* 4: JUMP FRONT, JUMP BACK, SP JUMP FRONT +13 */
    { {  -46,   80,    0,   70 } },  /* 5: ATTACK 4 S (Att_HADOUKEN) */
    { {  -20,   37,   35,   54 } },  /* 6: not used by a script */
    { {  -37,   37,   35,   54 } },  /* 7: not used by a script */
    { {    6,   47,   35,   54 } },  /* 8: not used by a script */
    { {  -14,   62,   49,   33 } },  /* 9: not used by a script */
    { {   -4,   51,   35,   54 } },  /* 10: not used by a script */
    { {   -4,   56,   35,   48 } },  /* 11: not used by a script */
    { {   -4,   56,   35,   48 } },  /* 12: not used by a script */
    { {  -16,   47,   23,   37 } },  /* 13: not used by a script */
    { {  -16,   47,   13,   37 } },  /* 14: not used by a script */
    { {  -24,   47,   23,   37 } },  /* 15: not used by a script */
    { {  -20,   51,   45,   49 } },  /* 16: not used by a script */
    { {  -22,   59,   31,   61 } },  /* 17: saca 56, saca 57, saca 58 +2 */
    { {  -27,   47,   52,   45 } },  /* 18: ATTACK 2 S (Att_SHOURYUUKEN), ATTACK 2 M (Att_SHOURYUUKEN), ATTACK 2 L (Att_SHOURYUUKEN) +7 */
    { {  -38,   63,    0,   80 } },  /* 19: DASH HUMIKOMI, DASH TOBINOKI */
    { {  -21,   45,   45,   44 } },  /* 20: AIR S, AIR M, AIR L +40 */
    { {  -43,   42,    9,   48 } },  /* 21: ATTACK 1 S (Att_CHOUCHUURENGEKI), ATTACK 1 M (Att_CHOUCHUURENGEKI), ATTACK 1 L (Att_CHOUCHUURENGEKI) +1 */
    { {   -8,   48,   48,   32 } },  /* 22: FUSHIN P S */
    { {  -46,   63,   22,   54 } },  /* 23: ATTACK 4 S (Att_HADOUKEN), ATTACK 5 S (Att_SLIDE_and_JUMP) */
    { {  -20,   71,    0,   56 } },  /* 24: not used by a script */
    { {  -34,   48,   48,   54 } },  /* 25: Att_SENPUUKYAKU (command slot 23) */
    { {  -25,   50,    0,   30 } },  /* 26: NEKOROBI S */
    { {  -31,   63,   22,   44 } },  /* 27: not used by a script */
};
