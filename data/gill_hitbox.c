/*
 * GILL_HITBOX.C  Gill's hit boxes
 *
 * Each of Gill's animation frames names a row of gill_hit_ix_table (a frame line's hit field). The
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
 * rows of gill_catt_table dealt through it. Row 0 of a box table is no box.
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

const HIT_IX gill_hit_ix_table[123] = {
    /* boix  atix  cuix  hoix */
    {    0,    0,    0,    0 },  /* 0: TATAKI M, TATAKI L, TATAKI SP +23 */
    {    1,    0,    1,    1 },  /* 1: KAMAE, HURIMUKI, DASH HUMIKOMI +69 */
    {    2,    0,    2,    2 },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +23 */
    {    3,    0,    6,    9 },  /* 3: DASH HUMIKOMI */
    {    4,    0,    6,    9 },  /* 4: DASH HUMIKOMI */
    {    5,    0,    2,    2 },  /* 5: DASH TOBINOKI */
    {    6,    0,    1,    1 },  /* 6: DASH TOBINOKI */
    {    7,    0,    1,    1 },  /* 7: DASH HUMIKOMI, DASH TOBINOKI */
    {    8,    0,    3,    3 },  /* 8: S JUMP FRONT, GUARD AIR, AIR S +55 */
    {    0,    0,    0,    1 },  /* 9: super art Att_RESURRECTION (command slot 16); super art Att_RESURRECTION (command slot 17); super art Att_RESURRECTION (command slot 18) */
    {   10,    0,    3,    3 },  /* 10: not used by a script */
    {   11,    1,    1,    1 },  /* 11: S PUNCH A, UP P GUARD P S, FUSHIN P S */
    {   11,    0,    1,    1 },  /* 12: S PUNCH A, UP P GUARD P S, FUSHIN P S */
    {   12,    0,    1,    1 },  /* 13: M PUNCH C, L PUNCH A */
    {   12,    2,    1,    1 },  /* 14: M PUNCH C */
    {   96,    3,    1,    1 },  /* 15: M PUNCH C, UP P GUARD P M */
    {   13,    0,    1,    1 },  /* 16: M PUNCH C, UP P GUARD P M */
    {   19,    0,    1,    1 },  /* 17: S KICK A */
    {   19,    7,    1,    1 },  /* 18: S KICK A, UP P GUARD P L */
    {   21,    0,    1,    1 },  /* 19: M KICK A */
    {   22,    8,    1,    1 },  /* 20: M KICK A */
    {   22,    9,    1,    1 },  /* 21: M KICK A */
    {   22,    0,    1,    1 },  /* 22: M KICK A */
    {   23,    0,    1,    1 },  /* 23: L KICK A */
    {   24,    0,    1,    1 },  /* 24: L KICK A */
    {   88,   38,    1,    1 },  /* 25: L KICK A */
    {   25,   39,    1,    1 },  /* 26: L KICK A */
    {   26,   40,    1,    1 },  /* 27: L KICK A */
    {   27,    0,    1,    1 },  /* 28: L KICK A, UP P GUARD P L */
    {   31,   13,    2,    2 },  /* 29: KAGAMI P A, UP P GUARD P L */
    {   31,    0,    2,    2 },  /* 30: KAGAMI P A, UP P GUARD P L */
    {   33,    0,    1,    1 },  /* 31: KAGAMI P A, UP P GUARD P L */
    {   34,   15,    2,    2 },  /* 32: KAGAMI K A, UP P GUARD P L */
    {   34,   41,    2,    2 },  /* 33: KAGAMI K A, UP P GUARD P L */
    {   29,    0,    1,    5 },  /* 34: not used by a script */
    {   30,   12,    1,    5 },  /* 35: not used by a script */
    {   30,    0,    1,    5 },  /* 36: not used by a script */
    {   31,   10,    2,    2 },  /* 37: KAGAMI P A */
    {   32,    0,    2,    2 },  /* 38: KAGAMI P A */
    {   32,   14,    2,    2 },  /* 39: KAGAMI P A */
    {   33,   11,    1,    1 },  /* 40: KAGAMI P A */
    {   34,    0,    2,    2 },  /* 41: KAGAMI K A */
    {   35,   42,    2,    2 },  /* 42: KAGAMI K A */
    {   35,    0,    2,    2 },  /* 43: KAGAMI K A */
    {   89,   44,    3,    3 },  /* 44: V JUMP P L A */
    {   89,    0,    3,    3 },  /* 45: V JUMP P L A */
    {   89,   16,    3,    3 },  /* 46: V JUMP P L A */
    {   87,   18,    3,    3 },  /* 47: V JUMP P M A */
    {   86,    0,    3,    3 },  /* 48: V JUMP P M A, V JUMP P L A */
    {   87,   43,    3,    3 },  /* 49: V JUMP P M A */
    {   87,    0,    3,    3 },  /* 50: V JUMP P M A */
    {   49,    0,    3,    3 },  /* 51: V JUMP K S A, V JUMP K M A */
    {   49,   19,    3,    3 },  /* 52: V JUMP K S A */
    {   40,   21,    3,    3 },  /* 53: V JUMP K M A */
    {   40,   22,    3,    3 },  /* 54: V JUMP K M A, ATTACK 4 M */
    {   91,    0,    3,    3 },  /* 55: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +2 */
    {   92,    0,    3,    3 },  /* 56: JUMP FRONT, SP JUMP FRONT, ATTACK 1 M (Att_MOONSALT_KNEE_DROP) +2 */
    {   93,    0,    3,    3 },  /* 57: JUMP FRONT, SP JUMP FRONT, ATTACK 4 M */
    {   94,   45,    3,    3 },  /* 58: ATTACK 4 M, saca 49 */
    {   90,    0,    1,    1 },  /* 59: FRONT WALK, BACK WALK */
    {   47,    0,    3,    3 },  /* 60: V JUMP P S A, V JUMP P M A, V JUMP P L A +4 */
    {   48,   17,    3,    3 },  /* 61: V JUMP P S A */
    {   52,    0,    1,    1 },  /* 62: not used by a script */
    {   53,   25,    1,    1 },  /* 63: exca 13 */
    {   53,    0,    1,    1 },  /* 64: not used by a script */
    {   54,    0,    3,    3 },  /* 65: not used by a script */
    {   55,    0,    3,    3 },  /* 66: not used by a script */
    {   56,    0,    3,    3 },  /* 67: exca 13, HANASARE */
    {   57,    0,    3,    3 },  /* 68: not used by a script */
    {   58,    0,    3,    3 },  /* 69: not used by a script */
    {   59,   26,    3,    3 },  /* 70: not used by a script */
    {    8,   27,    3,    3 },  /* 71: not used by a script */
    {   30,   28,    1,    5 },  /* 72: not used by a script */
    {    1,   29,    1,    1 },  /* 73: M PUNCH A, M PUNCH C, L PUNCH A +3 */
    {    1,   30,    1,    1 },  /* 74: atca 144 */
    {   62,    0,    1,    1 },  /* 75: ATTACK 3 M (Att_HADOUKEN), ATTACK 3 L (Att_HADOUKEN), ATTACK 3 SP (Att_HADOUKEN) */
    {   63,    0,    1,    1 },  /* 76: ATTACK 3 M (Att_HADOUKEN) */
    {   64,    0,    4,    7 },  /* 77: ATTACK 3 M (Att_HADOUKEN) */
    {   65,    0,    4,    7 },  /* 78: ATTACK 3 M (Att_HADOUKEN) */
    {   66,    0,    4,    7 },  /* 79: ATTACK 3 M (Att_HADOUKEN) */
    {   67,    0,    4,    7 },  /* 80: ATTACK 3 L (Att_HADOUKEN) */
    {   68,    0,    4,    7 },  /* 81: ATTACK 3 SP (Att_HADOUKEN) */
    {    0,    0,    0,    2 },  /* 82: TATAKI S, NEKOROBI S, OKIAGARI +10 */
    {    0,    0,    0,    3 },  /* 83: AIR S, AIR M, AIR L +2 */
    {   69,    0,    1,    5 },  /* 84: not used by a script */
    {   70,    0,    1,    1 },  /* 85: PIYO */
    {   71,    0,    1,    1 },  /* 86: PIYO */
    {   72,    0,    1,    8 },  /* 87: ATTACK 1 M (Att_MOONSALT_KNEE_DROP), ATTACK 2 M (Att_ABISEGERI), ATTACK 5 M (Att_SENPUUKYAKU) */
    {   73,    0,    3,    3 },  /* 88: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    {   74,    0,    3,    3 },  /* 89: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    {   75,    0,    3,    3 },  /* 90: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    {   75,   31,    3,    3 },  /* 91: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    {   76,   32,    3,    3 },  /* 92: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    {   76,    0,    3,    3 },  /* 93: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    {   77,    0,    3,    3 },  /* 94: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    {   78,   33,    0,    0 },  /* 95: ATTACK 2 M (Att_ABISEGERI) */
    {   79,    0,    1,    1 },  /* 96: ATTACK 2 M (Att_ABISEGERI) */
    {   80,   34,    1,    1 },  /* 97: ATTACK 2 M (Att_ABISEGERI) */
    {   81,    0,    1,    1 },  /* 98: ATTACK 2 M (Att_ABISEGERI) */
    {   82,    0,    3,    3 },  /* 99: ATTACK 5 M (Att_SENPUUKYAKU) */
    {   83,   35,    3,    3 },  /* 100: ATTACK 5 M (Att_SENPUUKYAKU) */
    {   83,    0,    3,    3 },  /* 101: ATTACK 5 M (Att_SENPUUKYAKU) */
    {   84,    0,    3,    3 },  /* 102: not used by a script */
    {   85,    0,    3,    3 },  /* 103: not used by a script */
    {    1,    0,    0,    1 },  /* 104: HANASARE */
    {    2,    0,    0,    2 },  /* 105: HANASARE */
    {   14,    0,    1,    1 },  /* 106: M PUNCH A */
    {   14,   37,    1,    1 },  /* 107: M PUNCH A */
    {   14,   37,    1,    1 },  /* 108: M PUNCH A */
    {   15,    0,    1,    1 },  /* 109: L PUNCH A */
    {   16,    0,    1,    1 },  /* 110: L PUNCH A */
    {   17,    5,    1,    1 },  /* 111: L PUNCH A */
    {   17,    6,    1,    1 },  /* 112: L PUNCH A */
    {   17,    0,    1,    1 },  /* 113: L PUNCH A */
    {   41,    0,    3,    3 },  /* 114: V JUMP K L A */
    {   42,    0,    3,    3 },  /* 115: V JUMP K L A */
    {   43,   24,    3,    3 },  /* 116: V JUMP K L A */
    {   43,   24,    3,    3 },  /* 117: V JUMP K L A */
    {   43,    0,    3,    3 },  /* 118: V JUMP K L A */
    {   44,    0,    3,    3 },  /* 119: V JUMP K L A */
    {    1,    0,    1,    0 },  /* 120: not used by a script */
    {   78,   33,    0,    1 },  /* 121: ATTACK 2 M (Att_ABISEGERI) */
    {   95,    0,    3,    3 },  /* 122: PARING AIR F, PARING AIR B */
};

const BODY_BOX gill_body_box[97] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {  -18,  24,  102,  18 },  {  -40,  68,   92,  14 },  {  -28,  52,   52,  38 },  {  -26,  62,    0,  50 },  {    0,   0,    0,   0 } } },  /* 1: KAMAE, HURIMUKI, DASH HUMIKOMI +70 */
    { { {  -12,  32,   54,  18 },  {  -32,  70,   44,  14 },  {  -44,  88,   24,  22 },  {  -40,  80,    0,  22 },  {    0,   0,    0,   0 } } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +23 */
    { { {  -50,  22,   92,  18 },  {  -38,  60,   94,  12 },  {  -32,  60,   41,  52 },  {  -32,  72,    0,  40 },  {    0,   0,    0,   0 } } },  /* 3: DASH HUMIKOMI */
    { { {  -34,  22,   86,  18 },  {  -28,  52,   81,  16 },  {  -28,  52,   41,  39 },  {  -32,  72,    0,  40 },  {    0,   0,    0,   0 } } },  /* 4: DASH HUMIKOMI */
    { { {  -16,  22,   74,  18 },  {  -28,  52,   33,  16 },  {  -24,  48,   44,  20 },  {  -32,  72,    0,  44 },  {    0,   0,    0,   0 } } },  /* 5: DASH TOBINOKI */
    { { {   -2,  22,  114,  18 },  {  -20,  68,  104,  12 },  {  -20,  61,   51,  52 },  {  -32,  72,    0,  50 },  {    0,   0,    0,   0 } } },  /* 6: DASH TOBINOKI */
    { { {  -22,  22,   90,  18 },  {  -26,  64,   85,  12 },  {  -26,  66,   41,  42 },  {  -32,  72,    0,  40 },  {    0,   0,    0,   0 } } },  /* 7: DASH HUMIKOMI, DASH TOBINOKI */
    { { {   -8,  24,  118,  18 },  {  -26,  62,  106,  16 },  {  -22,  46,   62,  42 },  {  -12,  44,   28,  36 },  {    0,   0,    0,   0 } } },  /* 8: S JUMP FRONT, GUARD AIR, AIR S +55 */
    { { {  -32,  22,  106,  18 },  {  -28,  56,   92,  24 },  {  -20,  44,   50,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 9: not used by a script */
    { { {  -48,  22,   92,  18 },  {  -28,  56,   88,  28 },  {  -32,  60,   50,  38 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 10: not used by a script */
    { { {  -18,  24,  102,  18 },  {  -40,  68,   92,  14 },  {  -28,  52,   52,  38 },  {  -26,  62,    0,  50 },  {  -88,  48,   70,  28 } } },  /* 11: S PUNCH A, UP P GUARD P S, FUSHIN P S */
    { { {  -22,  24,   94,  18 },  {  -44,  68,   82,  14 },  {  -28,  48,   48,  32 },  {  -34,  68,    0,  46 },  {    0,   0,    0,   0 } } },  /* 12: M PUNCH C, L PUNCH A */
    { { {  -22,  24,   94,  18 },  {  -44,  68,   82,  14 },  {  -28,  48,   48,  32 },  {  -34,  68,    0,  46 },  {  -40,  26,   98,  40 } } },  /* 13: M PUNCH C, UP P GUARD P M */
    { { {  -22,  24,   94,  18 },  {  -44,  68,   82,  14 },  {  -28,  48,   48,  32 },  {  -34,  68,    0,  46 },  {  -82,  52,   76,  28 } } },  /* 14: M PUNCH A */
    { { {   -2,  24,  100,  18 },  {  -32,  76,   92,  14 },  {  -20,  52,   52,  38 },  {  -34,  70,    0,  50 },  {    0,   0,    0,   0 } } },  /* 15: L PUNCH A */
    { { {  -44,  40,  100,  16 },  {  -40,  68,   88,  14 },  {  -32,  52,   48,  38 },  {  -36,  78,    0,  46 },  {    0,   0,    0,   0 } } },  /* 16: L PUNCH A */
    { { {  -34,  50,   80,  22 },  {  -50,  70,   54,  24 },  {  -30,  56,   40,  24 },  {  -40,  92,    0,  40 },  {  -68,  34,   42,  40 } } },  /* 17: L PUNCH A */
    { { {  -10,  22,  102,  18 },  {  -32,  64,   94,  12 },  {  -32,  64,   41,  52 },  {  -32,  72,    0,  40 },  {    0,   0,    0,   0 } } },  /* 18: not used by a script */
    { { {  -34,  24,   98,  18 },  {  -44,  66,   88,  14 },  {  -30,  46,   50,  36 },  {  -52,  60,    0,  48 },  {    0,   0,    0,   0 } } },  /* 19: S KICK A, UP P GUARD P L */
    { { {  -15,  19,  103,  16 },  {  -27,  51,   94,  12 },  {  -20,  30,   41,  52 },  {  -22,  41,    0,  40 },  {  -78,  58,   74,   9 } } },  /* 20: not used by a script */
    { { {   -2,  24,   98,  18 },  {  -40,  68,   88,  14 },  {  -26,  52,   52,  38 },  {  -14,  36,    0,  50 },  {    0,   0,    0,   0 } } },  /* 21: M KICK A */
    { { {   -8,  32,   96,  18 },  {  -58,  92,   70,  24 },  {  -34,  38,   50,  26 },  {  -16,  34,    0,  48 },  { -112,  52,   70,  22 } } },  /* 22: M KICK A */
    { { {  -12,  24,  104,  18 },  {  -24,  68,   92,  14 },  {  -22,  50,   52,  38 },  {  -34,  62,    0,  50 },  {    0,   0,    0,   0 } } },  /* 23: L KICK A */
    { { {   -2,  24,  106,  18 },  {  -26,  68,   94,  14 },  {  -22,  60,   58,  34 },  {   -8,  34,    0,  56 },  {    0,   0,    0,   0 } } },  /* 24: L KICK A */
    { { {   10,  24,   96,  18 },  {  -20,  68,   86,  14 },  {  -44,  76,   56,  30 },  {  -10,  34,    0,  54 },  {  -78,  44,   64,  50 } } },  /* 25: L KICK A */
    { { {   16,  24,   94,  18 },  {   -8,  68,   84,  14 },  {  -28,  78,   60,  24 },  {  -14,  34,    0,  58 },  {  -72,  42,   26,  46 } } },  /* 26: L KICK A */
    { { {   20,  28,   94,  18 },  {  -16,  78,   66,  30 },  {  -44,  58,   36,  32 },  {  -12,  34,    0,  40 },  {    0,   0,    0,   0 } } },  /* 27: L KICK A, UP P GUARD P L */
    { { {   20,  22,   96,  18 },  {  -12,  72,   78,  24 },  {  -36,  80,   41,  36 },  {  -16,  48,    0,  40 },  {    0,   0,    0,   0 } } },  /* 28: not used by a script */
    { { {   -8,  22,  106,  18 },  {  -24,  60,   94,  12 },  {  -24,  60,   41,  52 },  {  -12,  48,    0,  40 },  {    0,   0,    0,   0 } } },  /* 29: not used by a script */
    { { {  -30,  22,  108,  18 },  {  -16,  56,  100,  28 },  {  -24,  64,   48,  52 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 30: not used by a script */
    { { {  -24,  32,   54,  18 },  {  -44,  70,   44,  14 },  {  -32,  76,   24,  22 },  {  -40,  80,    0,  22 },  {  -84,  38,   42,  22 } } },  /* 31: KAGAMI P A, UP P GUARD P L */
    { { {  -20,  26,   70,  18 },  {  -34,  56,   60,  14 },  {  -46,  76,   36,  22 },  {  -44,  88,    0,  34 },  {    0,   0,    0,   0 } } },  /* 32: KAGAMI P A */
    { { {  -16,  24,  100,  18 },  {  -26,  54,   88,  14 },  {  -22,  48,   36,  50 },  {  -38,  82,    0,  34 },  {  -40,  24,   76,  48 } } },  /* 33: KAGAMI P A, UP P GUARD P L */
    { { {  -18,  46,   50,  18 },  {  -36,  74,   44,  14 },  {  -44,  88,   24,  22 },  {  -40,  80,    0,  22 },  {  -92,  50,    0,  30 } } },  /* 34: KAGAMI K A, UP P GUARD P L */
    { { {  -18,  46,   50,  18 },  {  -36,  74,   44,  14 },  {  -44,  88,   24,  22 },  {  -40,  80,    0,  22 },  {  -98,  56,    0,  32 } } },  /* 35: KAGAMI K A */
    { { {  -18,  19,  107,  16 },  {  -24,  46,   88,  21 },  {  -22,  30,   49,  46 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 36: not used by a script */
    { { {  -46,  19,   93,  16 },  {  -27,  46,   88,  21 },  {  -22,  30,   49,  46 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 37: not used by a script */
    { { {  -46,  19,   93,  16 },  {  -27,  46,   88,  21 },  {  -22,  30,   49,  46 },  {    0,   0,    0,   0 },  {  -68,  57,   83,   7 } } },  /* 38: not used by a script */
    { { {  -46,  19,   93,  16 },  {  -27,  46,   88,  21 },  {  -22,  30,   49,  46 },  {    0,   0,    0,   0 },  {  -38,  18,   64,  26 } } },  /* 39: not used by a script */
    { { {   -2,  40,  106,  16 },  {  -18,  60,   88,  22 },  {  -36,  82,   66,  30 },  {   -6,  40,   48,  22 },  { -100,  62,   70,  16 } } },  /* 40: V JUMP K M A, ATTACK 4 M */
    { { {   -2,  24,  110,  18 },  {  -32,  66,  102,  14 },  {  -28,  56,   76,  26 },  {  -24,  56,   42,  32 },  {    0,   0,    0,   0 } } },  /* 41: V JUMP K L A */
    { { {  -12,  24,  110,  18 },  {  -20,  54,  102,  20 },  {  -32,  66,   78,  24 },  {  -40,  76,   58,  24 },  {    0,   0,    0,   0 } } },  /* 42: V JUMP K L A */
    { { {  -34,  24,  108,  18 },  {  -24,  54,  102,  20 },  {  -40,  68,   78,  24 },  {  -52,  90,   60,  26 },  { -100,  46,   58,  24 } } },  /* 43: V JUMP K L A */
    { { {  -30,  28,  112,  18 },  {  -32,  60,  106,  14 },  {  -32,  56,   78,  26 },  {  -50,  62,   58,  28 },  {    0,   0,    0,   0 } } },  /* 44: V JUMP K L A */
    { { {   -8,  19,  115,  16 },  {  -17,  46,   98,  21 },  {  -13,  30,   49,  46 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 45: not used by a script */
    { { {  -32,  16,  106,  16 },  {  -23,  46,   96,  21 },  {  -16,  30,   57,  46 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 46: not used by a script */
    { { {  -20,  24,  118,  18 },  {  -34,  66,  106,  14 },  {  -28,  56,   78,  26 },  {  -32,  64,   50,  26 },  {    0,   0,    0,   0 } } },  /* 47: V JUMP P S A, V JUMP P M A, V JUMP P L A +4 */
    { { {  -40,  24,  108,  18 },  {  -48,  72,   98,  14 },  {  -52,  86,   72,  24 },  {  -32,  60,   48,  26 },  {    0,   0,    0,   0 } } },  /* 48: V JUMP P S A */
    { { {   -2,  40,  106,  16 },  {  -18,  60,   88,  22 },  {  -40,  86,   62,  24 },  {  -18,  50,   50,  18 },  {    0,   0,    0,   0 } } },  /* 49: V JUMP K S A, V JUMP K M A */
    { { {   -8,  19,  115,  16 },  {  -17,  46,   98,  21 },  {  -13,  30,   49,  46 },  {  -45,  29,   72,  12 },  {    0,   0,    0,   0 } } },  /* 50: not used by a script */
    { { {  -46,  19,   93,  16 },  {  -27,  46,   88,  21 },  {  -22,  30,   49,  46 },  {  -50,  28,   66,  24 },  {    0,   0,    0,   0 } } },  /* 51: not used by a script */
    { { {  -32,  19,   86,  16 },  {  -26,  51,   68,  21 },  {  -20,  30,   44,  39 },  {  -22,  41,    0,  44 },  {  -50,  28,   72,  12 } } },  /* 52: not used by a script */
    { { {  -39,  19,   71,  16 },  {  -18,  46,   65,  32 },  {  -20,  30,   44,  39 },  {  -22,  41,    0,  44 },  {    0,   0,    0,   0 } } },  /* 53: exca 13 */
    { { {   13,  11,  129,  16 },  {  -17,  46,  113,  21 },  {  -13,  30,   69,  46 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 54: not used by a script */
    { { {   40,  19,   97,  16 },  {    4,  35,   84,  44 },  {  -21,  30,   69,  46 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 55: not used by a script */
    { { {   11,  19,   55,  16 },  {   -6,  46,   70,  21 },  {  -32,  58,   85,  25 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 56: exca 13, HANASARE */
    { { {   -7,  19,   51,  16 },  {  -24,  46,   66,  21 },  {  -19,  41,   88,  34 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 57: not used by a script */
    { { {  -34,  19,  106,  16 },  {  -23,  28,   75,  36 },  {    6,  41,   85,  20 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 58: not used by a script */
    { { {  -18,  19,  117,  16 },  {  -24,  46,   98,  21 },  {  -20,  30,   59,  46 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 59: not used by a script */
    { { {  -22,  19,   88,  16 },  {  -27,  51,   68,  21 },  {  -22,  32,   40,  39 },  {  -32,  64,    0,  44 },  {    0,   0,    0,   0 } } },  /* 60: not used by a script */
    { { {  -64,  19,   72,  16 },  {  -45,  51,   68,  21 },  {  -32,  32,   40,  39 },  {  -48,  64,    0,  44 },  {  -64,  16,   32,  40 } } },  /* 61: not used by a script */
    { { {   -8,  24,   94,  18 },  {  -32,  68,   90,  14 },  {  -28,  52,   52,  36 },  {  -54,  94,    0,  50 },  {    0,   0,    0,   0 } } },  /* 62: ATTACK 3 M (Att_HADOUKEN), ATTACK 3 L (Att_HADOUKEN), ATTACK 3 SP (Att_HADOUKEN) */
    { { {  -28,  62,   82,  18 },  {  -48,  86,   70,  14 },  {  -24,  60,   42,  28 },  {  -62, 102,    0,  44 },  {    0,   0,    0,   0 } } },  /* 63: ATTACK 3 M (Att_HADOUKEN) */
    { { {   -4,  52,   82,  18 },  {  -12,  58,   70,  14 },  {  -18,  58,   40,  28 },  {  -62, 102,    0,  44 },  {    0,   0,    0,   0 } } },  /* 64: ATTACK 3 M (Att_HADOUKEN) */
    { { {  -42,  68,   82,  18 },  {  -34,  66,   70,  14 },  {  -22,  58,   40,  28 },  {  -62, 102,    0,  44 },  {    0,   0,    0,   0 } } },  /* 65: ATTACK 3 M (Att_HADOUKEN) */
    { { {  -26,  24,   98,  18 },  {  -44,  68,   88,  14 },  {  -32,  52,   52,  38 },  {  -54,  94,    0,  50 },  {    0,   0,    0,   0 } } },  /* 66: ATTACK 3 M (Att_HADOUKEN) */
    { { {  -28,  62,   82,  18 },  {  -44,  82,   78,  14 },  {  -24,  60,   44,  32 },  {  -62, 102,    0,  44 },  {    0,   0,    0,   0 } } },  /* 67: ATTACK 3 L (Att_HADOUKEN) */
    { { {  -28,  62,   82,  18 },  {  -38,  18,   94,  12 },  {  -22,  58,   44,  36 },  {  -62, 102,    0,  44 },  {    0,   0,    0,   0 } } },  /* 68: ATTACK 3 SP (Att_HADOUKEN) */
    { { {  -36,  22,  104,  18 },  {  -28,  56,   82,  28 },  {  -48,  64,   48,  34 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 69: not used by a script */
    { { {  -11,  30,  102,  18 },  {  -30,  68,   94,  12 },  {  -30,  65,   41,  52 },  {  -32,  72,    0,  40 },  {    0,   0,    0,   0 } } },  /* 70: PIYO */
    { { {  -29,  33,  102,  18 },  {  -37,  63,   94,  12 },  {  -37,  65,   41,  52 },  {  -36,  74,    0,  40 },  {    0,   0,    0,   0 } } },  /* 71: PIYO */
    { { {  -26,  22,   84,  18 },  {  -32,  58,   82,  12 },  {  -24,  50,   40,  40 },  {  -36,  72,    0,  40 },  {    0,   0,    0,   0 } } },  /* 72: ATTACK 1 M (Att_MOONSALT_KNEE_DROP), ATTACK 2 M (Att_ABISEGERI), ATTACK 5 M (Att_SENPUUKYAKU) */
    { { {   14,  22,  126,  18 },  {  -18,  58,  122,  12 },  {  -22,  50,   80,  40 },  {   -4,  44,   50,  20 },  {    0,   0,    0,   0 } } },  /* 73: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    { { {    0,   0,    0,   0 },  {  -36,  64,   96,  28 },  {  -36,  64,   64,  28 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 74: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    { { {  -14,  22,  110,  18 },  {  -32,  56,  104,  16 },  {  -20,  42,   72,  30 },  {  -28,  46,   56,  24 },  {    0,   0,    0,   0 } } },  /* 75: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    { { {    0,   0,    0,   0 },  {  -50,  64,   94,  20 },  {  -26,  42,   72,  14 },  {  -46,  60,   56,  24 },  {    0,   0,    0,   0 } } },  /* 76: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    { { {  -38,  22,  106,  18 },  {  -34,  58,   94,  20 },  {  -18,  36,   72,  24 },  {  -38,  50,   50,  28 },  {    0,   0,    0,   0 } } },  /* 77: ATTACK 1 M (Att_MOONSALT_KNEE_DROP) */
    { { {  -44,  22,   92,  18 },  {  -48,  88,   82,  16 },  {  -38,  64,   40,  40 },  {    8,  56,    0,  40 },  {    0,   0,    0,   0 } } },  /* 78: ATTACK 2 M (Att_ABISEGERI) */
    { { {  -30,  22,   88,  18 },  {  -24,  56,   82,  18 },  {  -20,  44,   46,  34 },  {  -36,  78,    0,  46 },  {    0,   0,    0,   0 } } },  /* 79: ATTACK 2 M (Att_ABISEGERI) */
    { { {  -30,  22,   88,  18 },  {  -24,  56,   82,  18 },  {  -20,  44,   46,  34 },  {  -36,  78,    0,  46 },  {  -60,  38,   66,  16 } } },  /* 80: ATTACK 2 M (Att_ABISEGERI) */
    { { {  -40,  22,   70,  18 },  {  -16,  56,   80,  18 },  {  -26,  54,   38,  40 },  {  -34,  82,    0,  36 },  {    0,   0,    0,   0 } } },  /* 81: ATTACK 2 M (Att_ABISEGERI) */
    { { {    8,  22,  104,  18 },  {  -24,  70,   92,  14 },  {  -16,  48,   60,  32 },  {   -4,  50,   32,  26 },  {    0,   0,    0,   0 } } },  /* 82: ATTACK 5 M (Att_SENPUUKYAKU) */
    { { {  -44,  50,   94,  18 },  {  -64,  28,   70,  22 },  {  -38,  54,   68,  24 },  {  -40,  54,   40,  26 },  {    0,   0,    0,   0 } } },  /* 83: ATTACK 5 M (Att_SENPUUKYAKU) */
    { { {  -28,  22,  108,  18 },  {  -34,  60,   98,  20 },  {  -14,  38,   72,  24 },  {  -28,  48,   42,  28 },  {    0,   0,    0,   0 } } },  /* 84: not used by a script */
    { { {   -8,  22,  118,  18 },  {  -24,  56,   98,  20 },  {  -22,  42,   70,  26 },  {  -14,  38,   28,  40 },  {    0,   0,    0,   0 } } },  /* 85: not used by a script */
    { { {  -52,  54,  102,  18 },  {  -60,  72,   88,  18 },  {  -36,  64,   56,  30 },  {   -4,  50,   48,  20 },  {    0,   0,    0,   0 } } },  /* 86: V JUMP P M A, V JUMP P L A */
    { { {  -52,  54,  102,  18 },  {  -60,  72,   88,  18 },  {  -36,  64,   56,  30 },  {   -4,  50,   48,  20 },  {  -90,  44,   80,  28 } } },  /* 87: V JUMP P M A */
    { { {   -2,  24,  106,  18 },  {  -26,  68,   94,  14 },  {  -22,  60,   58,  34 },  {   -8,  34,    0,  56 },  {  -50,  24,   88,  36 } } },  /* 88: L KICK A */
    { { {  -52,  54,  102,  18 },  {  -60,  72,   88,  18 },  {  -36,  64,   56,  30 },  {   -4,  50,   48,  20 },  {  -68,  30,   66,  18 } } },  /* 89: V JUMP P L A */
    { { {  -20,  24,  104,  18 },  {  -36,  68,   92,  14 },  {  -30,  52,   52,  38 },  {  -34,  62,    0,  50 },  {    0,   0,    0,   0 } } },  /* 90: FRONT WALK, BACK WALK */
    { { {   -8,  24,  118,  18 },  {  -24,  60,  108,  14 },  {  -22,  46,   70,  36 },  {  -16,  48,   42,  26 },  {    0,   0,    0,   0 } } },  /* 91: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +2 */
    { { {  -24,  24,  110,  18 },  {  -32,  60,  106,  14 },  {  -16,  44,   70,  36 },  {  -30,  52,   44,  24 },  {    0,   0,    0,   0 } } },  /* 92: JUMP FRONT, SP JUMP FRONT, ATTACK 1 M (Att_MOONSALT_KNEE_DROP) +2 */
    { { {  -46,  24,   94,  18 },  {  -28,  56,  100,  14 },  {  -10,  40,   72,  26 },  {  -36,  60,   50,  26 },  {    0,   0,    0,   0 } } },  /* 93: JUMP FRONT, SP JUMP FRONT, ATTACK 4 M */
    { { {  -44,  42,  108,  18 },  {  -60,  92,   98,  14 },  {  -70, 108,   72,  24 },  {  -44,  72,   48,  26 },  {  -66,  32,   54,  22 } } },  /* 94: ATTACK 4 M, saca 49 */
    { { {  -20,  24,  116,  18 },  {  -44,  72,  108,  14 },  {  -40,  72,   80,  30 },  {  -46,  80,   62,  24 },  {    0,   0,    0,   0 } } },  /* 95: PARING AIR F, PARING AIR B */
    { { {  -22,  24,   94,  18 },  {  -44,  68,   82,  14 },  {  -28,  48,   48,  32 },  {  -34,  68,    0,  46 },  {  -60,  40,   80,  52 } } },  /* 96: M PUNCH C, UP P GUARD P M */
};

const ATTACK_BOX gill_att_box[46] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {    0,   0,    0,   0 },  {  -84,  26,   74,  16 },  {  -66,  26,   82,  12 } } },  /* 1: S PUNCH A, UP P GUARD P S, FUSHIN P S; attack 1 */
    { { {    0,   0,    0,   0 },  {  -72,  22,   72,  18 },  {  -62,  20,   58,  16 } } },  /* 2: M PUNCH C; attack 2 */
    { { {    0,   0,    0,   0 },  {  -74,  22,   92,  20 },  {  -70,  22,  114,  20 } } },  /* 3: M PUNCH C, UP P GUARD P M; attack 3 */
    { { {    0,   0,    0,   0 },  {  -56,  22,  104,  18 },  {    0,   0,    0,   0 } } },  /* 4: not used by a script */
    { { {    0,   0,    0,   0 },  {  -94,  28,   70,  24 },  {  -84,  40,   36,  32 } } },  /* 5: L PUNCH A; attack 5 */
    { { {    0,   0,    0,   0 },  {  -90,  24,   44,  16 },  {    0,   0,    0,   0 } } },  /* 6: L PUNCH A */
    { { {    0,   0,    0,   0 },  {  -72,  32,   10,  14 },  {  -62,  30,   22,  12 } } },  /* 7: S KICK A, UP P GUARD P L; attack 6 */
    { { {    0,   0,    0,   0 },  { -124,  40,   70,  12 },  {  -82,  46,   66,  16 } } },  /* 8: M KICK A; attack 8 */
    { { {    0,   0,    0,   0 },  { -112,  36,   70,  12 },  {  -74,  38,   66,  16 } } },  /* 9: M KICK A; attack 8 */
    { { {    0,   0,    0,   0 },  {  -96,  26,   52,  20 },  {  -74,  24,   40,  18 } } },  /* 10: KAGAMI P A; attack 13 */
    { { {    0,   0,    0,   0 },  {  -50,  22,  108,  22 },  {  -54,  22,   84,  22 } } },  /* 11: KAGAMI P A; attack 14 */
    { { {    0,   0,    0,   0 },  { -104,  54,   50,  18 },  {  -80,  80,   68,  16 } } },  /* 12: not used by a script */
    { { {    0,   0,    0,   0 },  {  -82,  20,   46,  16 },  {  -66,  20,   38,  16 } } },  /* 13: KAGAMI P A, UP P GUARD P L; attack 12 */
    { { {    0,   0,    0,   0 },  {  -54,  28,   62,  20 },  {  -46,  24,   42,  18 } } },  /* 14: KAGAMI P A; attack 28 */
    { { {    0,   0,    0,   0 },  { -100,  72,    0,  12 },  {    0,   0,    0,   0 } } },  /* 15: KAGAMI K A, UP P GUARD P L; attack 15 */
    { { {    0,   0,    0,   0 },  {  -80,  22,   64,  18 },  {  -62,  22,   60,  18 } } },  /* 16: V JUMP P L A */
    { { {    0,   0,    0,   0 },  {  -56,  22,   68,  12 },  {    0,   0,    0,   0 } } },  /* 17: V JUMP P S A; attack 18 */
    { { {    0,   0,    0,   0 },  {  -92,  24,   86,  14 },  {  -74,  24,   80,  14 } } },  /* 18: V JUMP P M A */
    { { {    0,   0,    0,   0 },  {  -48,  20,   58,  16 },  {    0,   0,    0,   0 } } },  /* 19: V JUMP K S A; attack 19, 29 */
    { { {    0,   0,    0,   0 },  {  -50,  24,   71,  17 },  {    0,   0,    0,   0 } } },  /* 20: not used by a script */
    { { {    0,   0,    0,   0 },  { -108,  76,   80,  12 },  {    0,   0,    0,   0 } } },  /* 21: V JUMP K M A; attack 30 */
    { { {    0,   0,    0,   0 },  {  -94,  56,   80,  12 },  {    0,   0,    0,   0 } } },  /* 22: V JUMP K M A, ATTACK 4 M; attack 20 */
    { { {    0,   0,    0,   0 },  { -120,  44,   48,  16 },  {  -82,  52,   58,  16 } } },  /* 23: not used by a script */
    { { {    0,   0,    0,   0 },  { -108,  40,   52,  16 },  {  -74,  44,   60,  16 } } },  /* 24: V JUMP K L A; attack 31 */
    { { {    0,   0,    0,   0 },  {  -89,  56,   55,  24 },  {    0,   0,    0,   0 } } },  /* 25: exca 13 */
    { { {    0,   0,    0,   0 },  {  -30,  56,   54,  16 },  {    0,   0,    0,   0 } } },  /* 26: not used by a script */
    { { {    0,   0,    0,   0 },  {  -36,  56,   40,  16 },  {    0,   0,    0,   0 } } },  /* 27: not used by a script */
    { { {    0,   0,    0,   0 },  { -120,  56,   42,  22 },  {  -84,  84,   64,  18 } } },  /* 28: not used by a script */
    { { {  -31,   6,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 29: M PUNCH A, M PUNCH C, L PUNCH A +3; attack 21 */
    { { {  -35,  10,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 30: atca 144; attack 21 */
    { { {    0,   0,    0,   0 },  {  -38,  44,   46,  20 },  {  -18,  30,   60,  14 } } },  /* 31: ATTACK 1 M (Att_MOONSALT_KNEE_DROP); attack 24 */
    { { {    0,   0,    0,   0 },  {  -54,  28,   62,  22 },  {  -38,  22,   54,  16 } } },  /* 32: ATTACK 1 M (Att_MOONSALT_KNEE_DROP); attack 25 */
    { { {    0,   0,    0,   0 },  {   38,  18,   84,  18 },  {    0,   0,    0,   0 } } },  /* 33: ATTACK 2 M (Att_ABISEGERI); attack 32 */
    { { {    0,   0,    0,   0 },  {  -78,  50,   68,  20 },  {    0,   0,    0,   0 } } },  /* 34: ATTACK 2 M (Att_ABISEGERI); attack 33 */
    { { {    0,   0,    0,   0 },  {  -74,  28,   76,  22 },  {  -64,  24,   92,  20 } } },  /* 35: ATTACK 5 M (Att_SENPUUKYAKU); attack 26 */
    { { {    0,   0,    0,   0 },  { -104,  40,   66,  22 },  {  -70,  42,   78,  20 } } },  /* 36: not used by a script */
    { { {    0,   0,    0,   0 },  {  -94,  30,   72,  16 },  {  -70,  30,   78,  16 } } },  /* 37: M PUNCH A; attack 3 */
    { { {    0,   0,    0,   0 },  {  -58,  34,  122,  24 },  {  -28,  28,  132,  20 } } },  /* 38: L KICK A; attack 9 */
    { { {    0,   0,    0,   0 },  { -112,  60,   64,  48 },  {  -90,  50,   96,  36 } } },  /* 39: L KICK A; attack 10 */
    { { {    0,   0,    0,   0 },  {  -92,  36,   12,  28 },  { -104,  32,   32,  26 } } },  /* 40: L KICK A */
    { { {    0,   0,    0,   0 },  { -108,  80,    0,  14 },  {    0,   0,    0,   0 } } },  /* 41: KAGAMI K A, UP P GUARD P L; attack 16 */
    { { {    0,   0,    0,   0 },  { -124,  94,    0,  16 },  {    0,   0,    0,   0 } } },  /* 42: KAGAMI K A; attack 17 */
    { { {    0,   0,    0,   0 },  { -112,  22,   76,  16 },  {  -88,  48,   80,  14 } } },  /* 43: V JUMP P M A; attack 19 */
    { { {    0,   0,    0,   0 },  {  -96,  28,   70,  24 },  { -100,  26,   90,  22 } } },  /* 44: V JUMP P L A; attack 20 */
    { { {    0,   0,    0,   0 },  {  -48,  34,   58,  18 },  {    0,   0,    0,   0 } } },  /* 45: ATTACK 4 M, saca 49; attack 34 */
};

const CAUGHT_BOX gill_cau_box[7] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -24,   48,    0,   16 } },  /* 1: KAMAE, HURIMUKI, DASH HUMIKOMI +75 */
    { {  -28,   52,    0,    8 } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +25 */
    { {  -24,   48,   54,   60 } },  /* 3: S JUMP FRONT, GUARD AIR, AIR S +66 */
    { {  -24,   48,    0,   16 } },  /* 4: ATTACK 3 M (Att_HADOUKEN), ATTACK 3 L (Att_HADOUKEN), ATTACK 3 SP (Att_HADOUKEN) */
    { {  -28,   52,    0,    8 } },  /* 5: not used by a script */
    { {  -32,   64,    0,   16 } },  /* 6: DASH HUMIKOMI */
};

const HOSEI_BOX gill_hos_box[10] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -24,   48,    0,   94 } },  /* 1: KAMAE, HURIMUKI, DASH HUMIKOMI +74 */
    { {  -24,   48,    0,   56 } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +37 */
    { {  -24,   48,   62,   50 } },  /* 3: S JUMP FRONT, GUARD AIR, AIR S +67 */
    { {   -4,   48,    0,  100 } },  /* 4: not used by a script */
    { {  -11,   48,    0,  100 } },  /* 5: not used by a script */
    { {    7,   48,    0,   56 } },  /* 6: not used by a script */
    { {  -24,   48,    0,  100 } },  /* 7: ATTACK 3 M (Att_HADOUKEN), ATTACK 3 L (Att_HADOUKEN), ATTACK 3 SP (Att_HADOUKEN) */
    { {  -24,   48,    0,   84 } },  /* 8: ATTACK 1 M (Att_MOONSALT_KNEE_DROP), ATTACK 2 M (Att_ABISEGERI), ATTACK 5 M (Att_SENPUUKYAKU) */
    { {  -32,   64,    0,   94 } },  /* 9: DASH HUMIKOMI */
};
