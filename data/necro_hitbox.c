/*
 * NECRO_HITBOX.C  Necro's hit boxes
 *
 * Each of Necro's animation frames names a row of necro_hit_ix_table (a frame line's hit field).
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
 * rows of necro_catt_table dealt through it. Row 0 of a box table is no box.
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

const HIT_IX necro_hit_ix_table[179] = {
    /* boix  atix  cuix  hoix */
    {    0,    0,    0,    0 },  /* 0: OKIAGARI, OKIAGARI F, OKIAGARI B +20 */
    {    1,    0,    1,    1 },  /* 1: KAMAE, HURIMUKI, FRONT WALK +97 */
    {    2,    0,    2,    2 },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +17 */
    {    3,    0,    3,    3 },  /* 3: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +1 */
    {    3,    0,    3,    3 },  /* 4: JUMP FRONT, SP JUMP FRONT */
    {    3,    0,    3,    3 },  /* 5: SP JUMP FRONT */
    {    3,    0,    3,    3 },  /* 6: JUMP FRONT, JUMP VERTICAL, S JUMP FRONT +8 */
    {    3,    0,    3,    3 },  /* 7: JUMP FRONT, JUMP VERTICAL, JUMP BACK +3 */
    {    3,    0,    3,    3 },  /* 8: JUMP BACK, SP JUMP BACK, PARING AIR F +1 */
    {    3,    0,    3,    3 },  /* 9: JUMP BACK, SP JUMP BACK */
    {    3,    0,    3,    3 },  /* 10: SP JUMP BACK */
    {    3,    0,    3,    3 },  /* 11: JUMP BACK, SP JUMP BACK */
    {    1,    0,    1,    1 },  /* 12: S PUNCH C */
    {   13,    1,    1,    9 },  /* 13: S PUNCH C */
    {   13,    0,    1,    9 },  /* 14: S PUNCH C */
    {   91,    0,    1,    9 },  /* 15: S PUNCH C */
    {   14,    0,    1,    9 },  /* 16: S PUNCH C */
    {   15,    2,    1,    1 },  /* 17: S PUNCH A */
    {   15,    0,    1,    1 },  /* 18: S PUNCH A */
    {    1,    0,    1,    1 },  /* 19: M PUNCH A, atca 156, UP P GUARD P S +1 */
    {   17,    3,    1,    1 },  /* 20: M PUNCH A, atca 156, UP P GUARD P S +1 */
    {   97,    0,    1,    1 },  /* 21: M PUNCH A, atca 156, UP P GUARD P S +1 */
    {    1,    0,    1,    1 },  /* 22: KAGAMI P C */
    {    1,    0,    1,    1 },  /* 23: KAGAMI P C */
    {    1,    0,    1,    1 },  /* 24: KAGAMI P C */
    {    1,    0,    1,    1 },  /* 25: KAGAMI P C */
    {   22,    4,    1,    1 },  /* 26: not used by a script */
    {   22,    0,    1,    1 },  /* 27: KAGAMI P C */
    {    1,    0,    1,    1 },  /* 28: KAGAMI P C */
    {    1,    0,    1,    1 },  /* 29: KAGAMI P C */
    {    1,    0,    1,    1 },  /* 30: L PUNCH A, atca 157 */
    {    1,    0,    1,    1 },  /* 31: L PUNCH A, atca 157 */
    {    1,    0,    1,    1 },  /* 32: L PUNCH A, atca 157 */
    {   28,    0,    1,    1 },  /* 33: L PUNCH A, atca 157 */
    {   29,    5,    1,    1 },  /* 34: L PUNCH A, atca 157 */
    {   29,    0,    1,    1 },  /* 35: L PUNCH A, atca 157 */
    {   30,    6,    1,    1 },  /* 36: not used by a script */
    {   30,    0,    1,    1 },  /* 37: not used by a script */
    {    1,    0,    1,    1 },  /* 38: S KICK A */
    {   32,    7,    1,    1 },  /* 39: S KICK A */
    {   32,    0,    1,    1 },  /* 40: S KICK A */
    {    1,    0,    1,    1 },  /* 41: M KICK C */
    {   34,    8,    1,    1 },  /* 42: M KICK C */
    {   34,    0,    1,    1 },  /* 43: M KICK C */
    {   35,    9,    1,    1 },  /* 44: M KICK A, UP P GUARD K S, D P GUARD K S */
    {   35,    0,    1,    1 },  /* 45: M KICK A, UP P GUARD K S, D P GUARD K S */
    {    1,    0,    1,    1 },  /* 46: L KICK C */
    {   37,    0,    1,    1 },  /* 47: L KICK C */
    {   38,   10,    1,    1 },  /* 48: L KICK C */
    {   38,    0,    1,    1 },  /* 49: L KICK C */
    {    1,    0,    1,    1 },  /* 50: L KICK A */
    {   40,    0,    1,    1 },  /* 51: L KICK A */
    {   41,    0,    1,    1 },  /* 52: L KICK A */
    {   42,   11,    1,    1 },  /* 53: L KICK A */
    {   42,    0,    1,    1 },  /* 54: L KICK A */
    {   41,    0,    1,    1 },  /* 55: L KICK A */
    {    2,    0,    2,    2 },  /* 56: KAGAMI P A */
    {   46,   12,   13,    2 },  /* 57: KAGAMI P A */
    {   46,    0,   13,    2 },  /* 58: KAGAMI P A */
    {   47,   13,    2,    2 },  /* 59: KAGAMI P A */
    {   47,    0,    2,    2 },  /* 60: KAGAMI P A */
    {    2,    0,    2,    2 },  /* 61: KAGAMI P A */
    {   49,    0,    2,    2 },  /* 62: KAGAMI P A */
    {   50,    0,    2,    2 },  /* 63: KAGAMI P A */
    {   51,    0,    2,    2 },  /* 64: KAGAMI P A */
    {   52,    0,    2,    2 },  /* 65: KAGAMI P A */
    {   53,   14,    9,   18 },  /* 66: KAGAMI P A */
    {   53,    0,    9,   18 },  /* 67: KAGAMI P A */
    {   52,    0,    9,   18 },  /* 68: KAGAMI P A */
    {   54,   15,   13,    2 },  /* 69: KAGAMI K A */
    {   54,    0,   13,    2 },  /* 70: KAGAMI K A */
    {    2,    0,    2,    2 },  /* 71: KAGAMI K A */
    {    2,    0,    2,    2 },  /* 72: KAGAMI K A */
    {    2,    0,    2,    2 },  /* 73: KAGAMI K A */
    {   58,    0,    2,    2 },  /* 74: KAGAMI K A */
    {   58,    0,    2,    2 },  /* 75: KAGAMI K A */
    {    2,    0,    2,    2 },  /* 76: KAGAMI K A */
    {    2,    0,    2,    2 },  /* 77: KAGAMI K A */
    {   61,    0,    2,    2 },  /* 78: not used by a script */
    {   62,   17,    2,    2 },  /* 79: KAGAMI K A */
    {  102,    0,    2,    2 },  /* 80: KAGAMI K A */
    {   63,    0,    2,    2 },  /* 81: KAGAMI K A */
    {   64,    0,    2,    2 },  /* 82: KAGAMI K A */
    {    1,   18,    1,    1 },  /* 83: KAGAMI P C */
    {    3,    0,    3,    3 },  /* 84: ATTACK 6 S (Att_SENPUUKYAKU), ATTACK 6 M (Att_SENPUUKYAKU), ATTACK 6 L (Att_SENPUUKYAKU) */
    {    3,    0,    3,    3 },  /* 85: ATTACK 6 S (Att_SENPUUKYAKU), ATTACK 6 M (Att_SENPUUKYAKU), ATTACK 6 L (Att_SENPUUKYAKU) */
    {   67,   19,    3,    3 },  /* 86: ATTACK 6 S (Att_SENPUUKYAKU), ATTACK 6 M (Att_SENPUUKYAKU), ATTACK 6 L (Att_SENPUUKYAKU) */
    {   67,    0,    3,    3 },  /* 87: ATTACK 6 S (Att_SENPUUKYAKU), ATTACK 6 M (Att_SENPUUKYAKU), ATTACK 6 L (Att_SENPUUKYAKU) */
    {    3,    0,    3,    3 },  /* 88: V JUMP P S A, V JUMP P M A, V JUMP P L A +3 */
    {   69,   20,    3,    3 },  /* 89: V JUMP P S A */
    {   69,    0,    3,    3 },  /* 90: V JUMP P S A */
    {   70,   45,    3,    3 },  /* 91: V JUMP P M A */
    {   70,    0,    3,    3 },  /* 92: V JUMP P M A */
    {   71,   21,    3,    3 },  /* 93: V JUMP P L A, F JUMP P L A */
    {   71,    0,    3,    3 },  /* 94: V JUMP P L A, F JUMP P L A */
    {    3,    0,    3,    3 },  /* 95: V JUMP K S A, V JUMP K M A, V JUMP K L A +4 */
    {  115,   22,    3,    3 },  /* 96: V JUMP K S A, F JUMP K S A */
    {    3,    0,    3,    3 },  /* 97: V JUMP K M A, V JUMP K L A */
    {   74,   23,    3,    6 },  /* 98: V JUMP K M A, V JUMP K L A */
    {   75,   34,    3,    6 },  /* 99: V JUMP K L A */
    {   76,    0,    3,    3 },  /* 100: not used by a script */
    {   77,   24,    3,    3 },  /* 101: F JUMP P S A */
    {   77,    0,    3,    3 },  /* 102: F JUMP P S A */
    {   78,   24,    3,    3 },  /* 103: F JUMP P M A */
    {   78,    0,    3,    3 },  /* 104: F JUMP P M A */
    {   79,    0,    3,    3 },  /* 105: F JUMP K M A, F JUMP K L A */
    {   80,   25,    3,    3 },  /* 106: F JUMP K M A */
    {   80,   26,    3,    3 },  /* 107: F JUMP K M A */
    {   80,    0,    3,    3 },  /* 108: not used by a script */
    {    1,    0,    3,    3 },  /* 109: F JUMP K M A, F JUMP K L A */
    {   82,   25,    3,    3 },  /* 110: F JUMP K L A */
    {   82,   26,    3,    3 },  /* 111: F JUMP K L A */
    {   82,    0,    3,    3 },  /* 112: not used by a script */
    {    1,    0,    1,    1 },  /* 113: GUARD HEAD, GUARD UP */
    {    2,    0,    2,    2 },  /* 114: PARING DOWN, GUARD DOWN */
    {    0,    0,    0,    2 },  /* 115: TATAKI S, KGM TATAKI S, OKIAGARI +15 */
    {   85,    0,    0,    2 },  /* 116: not used by a script */
    {  121,    0,    1,    1 },  /* 117: FUSHIN P S, OKIAGARI P S, super art Att_HADOUKEN (command slot 18) +1 */
    {    1,   27,    1,    1 },  /* 118: FUSHIN P S */
    {  108,   28,    1,    1 },  /* 119: OKIAGARI P S, Att_HADOUKEN (command slot 26) */
    {  109,   29,    1,    1 },  /* 120: OKIAGARI P S, Att_HADOUKEN (command slot 26) */
    {    1,   30,    1,    1 },  /* 121: M PUNCH A, M PUNCH C, M KICK A +3 */
    {    1,    0,    2,    2 },  /* 122: CATCH 5, ATTACK 5 S (Att_HADOUKEN), ATTACK 5 M (Att_HADOUKEN) +1 */
    {    1,    0,    2,    2 },  /* 123: ATTACK 5 S (Att_HADOUKEN), ATTACK 5 M (Att_HADOUKEN), ATTACK 5 L (Att_HADOUKEN) */
    {    1,    0,    2,    2 },  /* 124: CATCH 5, ATTACK 5 S (Att_HADOUKEN), ATTACK 5 M (Att_HADOUKEN) +1 */
    {   90,   31,    2,    2 },  /* 125: ATTACK 5 S (Att_HADOUKEN), ATTACK 5 M (Att_HADOUKEN), ATTACK 5 L (Att_HADOUKEN) */
    {    1,    0,    1,    1 },  /* 126: M PUNCH C */
    {   92,   32,    1,    1 },  /* 127: M PUNCH C */
    {   93,    0,    1,    1 },  /* 128: M PUNCH C */
    {   95,    0,    1,    1 },  /* 129: M PUNCH C */
    {    1,    0,    1,    1 },  /* 130: M PUNCH C */
    {   96,    0,    1,    1 },  /* 131: S PUNCH A, super art Att_HADOUKEN (command slot 18) */
    {   98,    0,   13,    2 },  /* 132: KAGAMI P A */
    {   99,    0,   13,    2 },  /* 133: KAGAMI K A */
    {  103,   33,    2,    2 },  /* 134: KAGAMI K A */
    {  103,    0,    2,    2 },  /* 135: KAGAMI K A */
    {   99,    0,    2,    2 },  /* 136: KAGAMI K A */
    {  100,    0,    3,    3 },  /* 137: V JUMP K M A */
    {  100,    0,    3,    3 },  /* 138: V JUMP K L A */
    {  101,    0,    9,   18 },  /* 139: KAGAMI P A */
    {  104,   35,   15,    1 },  /* 140: ATTACK 2 S (Att_CHOUCHUURENGEKI), ATTACK 2 M (Att_CHOUCHUURENGEKI), ATTACK 2 L (Att_CHOUCHUURENGEKI) */
    {  105,   36,   15,    1 },  /* 141: ATTACK 2 S (Att_CHOUCHUURENGEKI), ATTACK 2 M (Att_CHOUCHUURENGEKI), ATTACK 2 L (Att_CHOUCHUURENGEKI) */
    {  106,   37,    1,    1 },  /* 142: ATTACK 3 L (Att_HADOUKEN) */
    {  106,   38,    1,    1 },  /* 143: ATTACK 3 L (Att_HADOUKEN) */
    {  111,   39,    1,    1 },  /* 144: ATTACK 4 S (Att_HADOUKEN) */
    {  111,   40,    1,    1 },  /* 145: ATTACK 4 S (Att_HADOUKEN) */
    {   68,    0,   14,   22 },  /* 146: DASH HUMIKOMI, DASH TOBINOKI */
    {  107,    0,   12,   23 },  /* 147: AIR S, AIR M, AIR L +37 */
    {    1,   41,    1,    1 },  /* 148: super art Att_HADOUKEN (command slot 18) */
    {  108,    0,    1,    1 },  /* 149: not used by a script */
    {  109,   42,    1,    1 },  /* 150: not used by a script */
    {  113,   43,    1,    1 },  /* 151: not used by a script */
    {    0,    0,    0,   24 },  /* 152: OKIAGARI P S */
    {  110,    0,    2,   24 },  /* 153: OKIAGARI P S, super art Att_HADOUKEN (command slot 18), Att_HADOUKEN (command slot 26) */
    {    0,    0,    0,    1 },  /* 154: ATTACK 1 S (Att_HADOUKEN), ATTACK 4 S (Att_HADOUKEN), super art Att_HADOUKEN (command slot 18) */
    {    1,    0,    1,    1 },  /* 155: not used by a script */
    {  112,    0,    1,    1 },  /* 156: KAGAMI P C */
    {    1,   46,    1,    1 },  /* 157: L PUNCH A, L KICK A, L KICK C */
    {    0,    0,    0,    3 },  /* 158: AIR S, AIR M, AIR L +2 */
    {   62,    0,    2,    2 },  /* 159: KAGAMI K A */
    {  114,   47,    1,    1 },  /* 160: KAGAMI P C */
    {  116,    0,    1,    1 },  /* 161: ATTACK 1 S (Att_HADOUKEN) */
    {  117,   48,    3,    3 },  /* 162: saca 54 */
    {  118,    0,   15,    1 },  /* 163: ATTACK 2 S (Att_CHOUCHUURENGEKI), ATTACK 2 M (Att_CHOUCHUURENGEKI), ATTACK 2 L (Att_CHOUCHUURENGEKI) +1 */
    {  119,    0,    1,    2 },  /* 164: PIYO */
    {   17,    0,    1,    1 },  /* 165: M PUNCH A, atca 156 */
    {   90,   49,    2,    2 },  /* 166: not used by a script */
    {   90,   50,    2,    2 },  /* 167: not used by a script */
    {    0,    0,    0,   24 },  /* 168: NEKOROBI S */
    {  106,   51,    1,    1 },  /* 169: ATTACK 3 S (Att_HADOUKEN) */
    {  106,   51,    1,    1 },  /* 170: not used by a script */
    {  106,   52,    1,    1 },  /* 171: ATTACK 3 M (Att_HADOUKEN) */
    {  106,   52,    1,    1 },  /* 172: not used by a script */
    {  120,    0,    1,    1 },  /* 173: OKIAGARI P S, super art Att_HADOUKEN (command slot 18), Att_HADOUKEN (command slot 26) */
    {    1,    0,    0,    1 },  /* 174: HANASARE */
    {    2,    0,    0,    2 },  /* 175: HANASARE */
    {  106,    0,    1,    1 },  /* 176: ATTACK 3 S (Att_HADOUKEN), ATTACK 3 M (Att_HADOUKEN) */
    {    1,    0,    1,    0 },  /* 177: LOSE SONABA */
    {   90,    0,    2,    2 },  /* 178: CATCH 5, ATTACK 5 S (Att_HADOUKEN), ATTACK 5 M (Att_HADOUKEN) +1 */
};

const BODY_BOX necro_body_box[122] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {  -16,  24,   76,  18 },  {  -29,  64,   72,  16 },  {  -29,  64,   40,  31 },  {  -30,  65,    0,  38 },  {    0,   0,    0,   0 } } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +106 */
    { { {  -33,  21,   47,  18 },  {  -14,  52,   50,  16 },  {  -33,  71,   25,  26 },  {  -39,  78,    0,  28 },  {    0,   0,    0,   0 } } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +19 */
    { { {  -17,  21,  103,  16 },  {  -29,  61,   91,  27 },  {  -26,  52,   53,  36 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 3: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +22 */
    { { {  -47,  25,   79,  17 },  {  -40,  48,   83,  18 },  {  -32,  46,   73,  41 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 4: not used by a script */
    { { {    0,   0,    0,   0 },  {  -40,  48,   83,  18 },  {  -32,  46,   55,  41 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 5: not used by a script */
    { { {  -15,  25,   95,  17 },  {  -23,  48,   89,  18 },  {  -23,  46,   48,  41 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 6: not used by a script */
    { { {  -16,  21,   99,  14 },  {  -29,  47,   91,  18 },  {  -26,  41,   71,  23 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 7: not used by a script */
    { { {    4,  25,  100,  17 },  {   -7,  48,   95,  18 },  {  -15,  33,   69,  41 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 8: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -33,  44,   73,  52 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 9: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -29,  46,   59,  41 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 10: not used by a script */
    { { {  -19,  25,  100,  17 },  {  -28,  48,   88,  18 },  {  -27,  46,   50,  41 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 11: not used by a script */
    { { {  -16,  24,   76,  18 },  {  -30,  58,   60,  26 },  {  -20,  44,   40,  24 },  {  -20,  54,    0,  38 },  {    0,   0,    0,   0 } } },  /* 12: not used by a script */
    { { {    0,   0,    0,   0 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  {  -92,  72,   42,  37 } } },  /* 13: S PUNCH C */
    { { {  -16,  24,   76,  18 },  {  -30,  58,   60,  26 },  {  -20,  44,   40,  24 },  {  -20,  54,    0,  38 },  {    0,   0,    0,   0 } } },  /* 14: S PUNCH C */
    { { {  -16,  24,   76,  18 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  { -128, 102,   57,  29 } } },  /* 15: S PUNCH A */
    { { {  -31,  25,   71,  17 },  {  -21,  48,   65,  18 },  {  -19,  46,   41,  24 },  {  -19,  44,    0,  39 },  {    0,   0,    0,   0 } } },  /* 16: not used by a script */
    { { {  -16,  24,   76,  18 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  { -102,  79,   73,  23 } } },  /* 17: M PUNCH A, atca 156, UP P GUARD P S +1 */
    { { {    2,  25,   76,  17 },  {   -2,  48,   67,  18 },  {    6,  46,   41,  24 },  {  -19,  44,    0,  39 },  {    0,   0,    0,   0 } } },  /* 18: not used by a script */
    { { {   16,  25,   48,  17 },  {  -20,  48,   43,  18 },  {  -39,  46,   24,  24 },  {  -38,  44,    0,  23 },  {    0,   0,    0,   0 } } },  /* 19: not used by a script */
    { { {   -6,  25,   60,  17 },  {  -20,  48,   43,  18 },  {  -39,  46,   24,  24 },  {  -38,  44,    0,  23 },  {    0,   0,    0,   0 } } },  /* 20: not used by a script */
    { { {  -11,  25,   66,  17 },  {  -27,  48,   53,  18 },  {  -38,  46,   29,  24 },  {  -38,  44,    0,  29 },  {    0,   0,    0,   0 } } },  /* 21: not used by a script */
    { { {  -36,  26,   96,  31 },  {  -40,  57,   84,  18 },  {  -40,  63,   45,  38 },  {  -25,  67,    0,  45 },  {   -3,  29,   97,  47 } } },  /* 22: KAGAMI P C */
    { { {    0,  25,   81,  17 },  {   -9,  48,   70,  18 },  {   -9,  46,   33,  38 },  {  -10,  44,    0,  45 },  {    0,   0,    0,   0 } } },  /* 23: not used by a script */
    { { {  -21,  25,   81,  17 },  {  -24,  48,   70,  18 },  {  -22,  46,   33,  38 },  {  -24,  44,    0,  45 },  {    0,   0,    0,   0 } } },  /* 24: not used by a script */
    { { {  -16,  24,   76,  18 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  {    0,   0,    0,   0 } } },  /* 25: not used by a script */
    { { {  -16,  24,   65,  17 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  {    0,   0,    0,   0 } } },  /* 26: not used by a script */
    { { {  -59,  25,   57,  17 },  {  -34,  48,   57,  18 },  {  -19,  46,   37,  22 },  {  -19,  44,    0,  39 },  {    0,   0,    0,   0 } } },  /* 27: not used by a script */
    { { {  -16,  24,   76,  18 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  {  -99,  72,   50,  34 } } },  /* 28: L PUNCH A, atca 157 */
    { { {  -16,  24,   76,  18 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  { -148, 128,   50,  34 } } },  /* 29: L PUNCH A, atca 157 */
    { { {  -31,  25,   71,  17 },  {  -21,  48,   65,  18 },  {  -19,  46,   41,  24 },  {  -51,  75,    0,  39 },  {    0,   0,    0,   0 } } },  /* 30: not used by a script */
    { { {    1,  25,   71,  17 },  {   10,  48,   65,  18 },  {  -19,  46,   41,  24 },  {  -19,  44,    0,  39 },  {    0,   0,    0,   0 } } },  /* 31: not used by a script */
    { { {    0,   0,    0,   0 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  {  -92,  71,   33,  35 } } },  /* 32: S KICK A */
    { { {  -19,  25,   89,  17 },  {  -21,  48,   79,  18 },  {  -19,  46,   41,  36 },  {  -19,  44,    0,  39 },  {    0,   0,    0,   0 } } },  /* 33: not used by a script */
    { { {  -19,  25,   89,  17 },  {  -21,  48,   79,  18 },  {  -66,  92,   54,  24 },  {  -30,  65,    0,  38 },  {    0,   0,    0,   0 } } },  /* 34: M KICK C */
    { { {  -31,  25,   71,  17 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  { -132, 106,   23,  25 } } },  /* 35: M KICK A, UP P GUARD K S, D P GUARD K S */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -19,  46,   41,  24 },  {  -19,  44,    0,  39 },  {    0,   0,    0,   0 } } },  /* 36: not used by a script */
    { { {   10,  25,   95,  17 },  {  -22,  74,   73,  29 },  {  -19,  46,   41,  45 },  {  -19,  44,    0,  39 },  {    0,   0,    0,   0 } } },  /* 37: L KICK C */
    { { {   10,  25,   95,  17 },  {  -44,  91,   73,  29 },  {  -19,  46,   41,  45 },  {  -19,  44,    0,  39 },  {  -63,  39,   67,  59 } } },  /* 38: L KICK C */
    { { {  -11,  25,   83,  17 },  {  -21,  48,   65,  18 },  {  -19,  46,   41,  24 },  {  -19,  44,    0,  39 },  {    0,   0,    0,   0 } } },  /* 39: not used by a script */
    { { {    9,  25,   88,  21 },  {   -4,  75,   79,  18 },  {  -19,  46,   55,  24 },  {  -19,  44,    0,  53 },  {    0,   0,    0,   0 } } },  /* 40: L KICK A */
    { { {    9,  25,   88,  21 },  {  -18,  75,   79,  20 },  {  -91, 118,   52,  33 },  {  -19,  44,    0,  53 },  {    0,   0,    0,   0 } } },  /* 41: L KICK A */
    { { {    9,  25,   88,  21 },  {  -18,  75,   79,  18 },  {  -23,  49,   55,  24 },  {  -19,  44,    0,  53 },  { -126, 122,   52,  34 } } },  /* 42: L KICK A */
    { { {    1,  25,   87,  17 },  {  -18,  75,   79,  18 },  {  -23,  49,   55,  24 },  {  -19,  44,    0,  53 },  { -116, 102,   64,  19 } } },  /* 43: not used by a script */
    { { {  -31,  25,   87,  17 },  {  -21,  48,   79,  18 },  {  -19,  45,   55,  24 },  {  -18,  44,    0,  53 },  {    0,   0,    0,   0 } } },  /* 44: not used by a script */
    { { {  -16,  25,   55,  17 },  {  -21,  48,   45,  18 },  {  -19,  46,   26,  24 },  {  -19,  44,    0,  26 },  {    0,   0,    0,   0 } } },  /* 45: not used by a script */
    { { {  -28,  40,   60,  18 },  {  -47,  88,   44,  27 },  {  -24,  60,   24,  20 },  {  -49,  90,    0,  28 },  { -121,  96,   29,  22 } } },  /* 46: KAGAMI P A */
    { { {  -61,  45,   49,  36 },  {  -31,  67,   44,  36 },  {  -41,  80,   24,  22 },  {  -49,  92,    0,  28 },  { -103,  41,   85,  35 } } },  /* 47: KAGAMI P A */
    { { {  -16,  25,   55,  17 },  {  -38,  68,   45,  18 },  {  -19,  46,   26,  24 },  {  -19,  44,    0,  26 },  {    0,   0,    0,   0 } } },  /* 48: not used by a script */
    { { {   -9,  37,   64,  19 },  {  -27,  79,   45,  25 },  {  -40,  71,   26,  24 },  {  -50,  87,    0,  26 },  {    0,   0,    0,   0 } } },  /* 49: KAGAMI P A */
    { { {   -9,  37,   64,  19 },  {  -27,  79,   45,  25 },  {  -40,  71,   26,  24 },  {  -50,  87,    0,  26 },  {    0,   0,    0,   0 } } },  /* 50: KAGAMI P A */
    { { {  -25,  37,   61,  19 },  {  -52,  77,   45,  28 },  {  -56,  69,   26,  24 },  {  -55,  77,    0,  26 },  {    0,   0,    0,   0 } } },  /* 51: KAGAMI P A */
    { { {  -25,  37,   61,  19 },  {  -52,  77,   45,  28 },  {  -56,  69,   26,  24 },  {  -55,  77,    0,  26 },  {    0,   0,    0,   0 } } },  /* 52: KAGAMI P A */
    { { {  -54,  25,   68,  18 },  {  -84,  74,   52,  29 },  {  -84,  74,   26,  24 },  {  -84, 112,    0,  26 },  { -110,  48,   64,  25 } } },  /* 53: KAGAMI P A */
    { { {  -41,  28,   42,  24 },  {  -13,  52,   44,  27 },  {  -67, 106,   24,  26 },  {  -28,  67,    0,  28 },  { -115,  91,    0,  33 } } },  /* 54: KAGAMI K A */
    { { {    0,   0,    0,   0 },  {  -21,  48,   45,  18 },  {  -19,  46,   26,  24 },  {  -19,  44,    0,  26 },  {    0,   0,    0,   0 } } },  /* 55: not used by a script */
    { { {   26,  25,   35,  17 },  {  -21,  48,   45,  18 },  {  -19,  46,   26,  24 },  {  -19,  44,    0,  26 },  {    0,   0,    0,   0 } } },  /* 56: not used by a script */
    { { {  -63,  25,   33,  17 },  {  -60,  48,   45,  18 },  {  -36,  46,   26,  24 },  {  -19,  44,    0,  26 },  {    0,   0,    0,   0 } } },  /* 57: not used by a script */
    { { {  -81,  65,   33,  19 },  {  -60,  52,   42,  28 },  {  -36,  71,   26,  34 },  {  -39, 138,    0,  34 },  {    0,   0,    0,   0 } } },  /* 58: KAGAMI K A */
    { { {  -51,  25,   24,  17 },  {  -45,  48,   34,  18 },  {  -23,  46,   24,  24 },  {  -19,  44,    0,  26 },  {    0,   0,    0,   0 } } },  /* 59: not used by a script */
    { { {    0,   0,    0,   0 },  {  -17,  48,   34,  18 },  {  -23,  46,   24,  24 },  {  -19,  44,    0,  26 },  {    0,   0,    0,   0 } } },  /* 60: not used by a script */
    { { {    6,  25,   34,  17 },  {    2,  48,   25,  18 },  {  -24,  46,   17,  24 },  {  -19,  44,    0,  26 },  {    0,   0,    0,   0 } } },  /* 61: not used by a script */
    { { {   26,  25,   51,  22 },  {   20,  75,   44,  22 },  {  -16,  80,    0,  42 },  {  -16,  43,    0,  42 },  { -108,  95,    0,  51 } } },  /* 62: KAGAMI K A */
    { { {    6,  25,   64,  22 },  {  -20,  75,   57,  22 },  {  -17,  70,   38,  24 },  {  -20,  77,    0,  42 },  {    0,   0,    0,   0 } } },  /* 63: KAGAMI K A */
    { { {    6,  25,   64,  22 },  {  -20,  75,   57,  22 },  {  -17,  70,   38,  24 },  {  -20,  77,    0,  42 },  {    0,   0,    0,   0 } } },  /* 64: KAGAMI K A */
    { { {  -31,  25,  104,  17 },  {  -35,  41,   90,  18 },  {  -17,  28,   55,  34 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 65: not used by a script */
    { { {  -48,  25,   91,  17 },  {  -35,  41,   90,  18 },  {  -17,  28,   55,  34 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 66: not used by a script */
    { { {  -48,  25,   91,  17 },  {  -35,  41,   90,  18 },  {  -80,  87,   55,  34 },  {    0,   0,    0,   0 },  {  -96,  65,   20,  36 } } },  /* 67: ATTACK 6 S (Att_SENPUUKYAKU), ATTACK 6 M (Att_SENPUUKYAKU), ATTACK 6 L (Att_SENPUUKYAKU) */
    { { {  -16,  24,   76,  18 },  {  -29,  64,   72,  16 },  {  -29,  64,   40,  31 },  {  -30,  65,   -8,  49 },  {    0,   0,    0,   0 } } },  /* 68: DASH HUMIKOMI, DASH TOBINOKI */
    { { {  -17,  21,  103,  16 },  {  -29,  61,   91,  27 },  {  -26,  52,   53,  36 },  {    0,   0,    0,   0 },  { -119,  92,   99,  17 } } },  /* 69: V JUMP P S A */
    { { {  -17,  21,  103,  16 },  {  -29,  61,   91,  27 },  {  -26,  52,   53,  36 },  {    0,   0,    0,   0 },  { -127,  98,   96,  25 } } },  /* 70: V JUMP P M A */
    { { { -108,  80,   70,  27 },  {  -42,  48,   75,  18 },  {  -12,  44,   73,  25 },  {    0,   0,    0,   0 },  { -140,  82,   46,  37 } } },  /* 71: V JUMP P L A, F JUMP P L A */
    { { {  -13,  25,   94,  17 },  {  -21,  48,   83,  18 },  {  -19,  46,   62,  29 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 72: not used by a script */
    { { {  -45,  25,   87,  17 },  {  -30,  48,   83,  18 },  {  -19,  46,   62,  29 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 73: not used by a script */
    { { {  -17,  21,  103,  16 },  {  -29,  61,   91,  27 },  {  -26,  52,   53,  36 },  {    0,   0,    0,   0 },  { -118,  93,   56,  33 } } },  /* 74: V JUMP K M A, V JUMP K L A */
    { { {  -17,  21,  103,  16 },  {  -29,  61,   91,  27 },  {  -26,  52,   53,  36 },  {    0,   0,    0,   0 },  { -130, 103,   54,  39 } } },  /* 75: V JUMP K L A */
    { { {  -38,  25,   74,  17 },  {  -31,  48,   87,  18 },  {  -19,  46,   62,  29 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 76: not used by a script */
    { { {  -17,  21,  103,  16 },  {  -29,  61,   91,  27 },  {  -26,  52,   53,  36 },  {    0,   0,    0,   0 },  {  -75,  58,   30,  45 } } },  /* 77: F JUMP P S A */
    { { {  -17,  21,  103,  16 },  {  -29,  61,   91,  27 },  {  -26,  52,   53,  36 },  {    0,   0,    0,   0 },  {  -88,  67,   29,  33 } } },  /* 78: F JUMP P M A */
    { { {   16,  29,   94,  25 },  {  -25,  61,   56,  51 },  {  -55,  54,   37,  51 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 79: F JUMP K M A, F JUMP K L A */
    { { {   15,  25,   94,  17 },  {  -37,  79,   82,  33 },  {  -57,  55,   63,  25 },  {  -68,  46,   27,  42 },  {    0,   0,    0,   0 } } },  /* 80: F JUMP K M A */
    { { {  -10,  25,   94,  17 },  {  -37,  79,   82,  33 },  {  -57,  55,   63,  25 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 81: not used by a script */
    { { {   15,  25,   94,  17 },  {  -37,  79,   82,  33 },  {  -57,  55,   63,  25 },  {  -65,  47,   36,  30 },  {    0,   0,    0,   0 } } },  /* 82: F JUMP K L A */
    { { {  -14,  25,   77,  17 },  {  -21,  48,   65,  18 },  {   -9,  27,   41,  24 },  {  -19,  44,    0,  39 },  {    0,   0,    0,   0 } } },  /* 83: not used by a script */
    { { {  -18,  25,   59,  17 },  {  -29,  48,   48,  18 },  {  -22,  36,   26,  24 },  {  -28,  44,    0,  26 },  {    0,   0,    0,   0 } } },  /* 84: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -17,  39,    0,  35 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 85: not used by a script */
    { { {  -13,  25,   83,  17 },  {  -21,  48,   65,  18 },  {  -19,  46,   41,  24 },  {  -19,  44,    0,  39 },  {    0,   0,    0,   0 } } },  /* 86: not used by a script */
    { { {  -20,  25,   55,  17 },  {  -21,  48,   45,  18 },  {  -19,  46,   26,  24 },  {  -19,  44,    0,  26 },  {    0,   0,    0,   0 } } },  /* 87: not used by a script */
    { { {   -7,  25,   61,  17 },  {  -21,  48,   45,  18 },  {  -19,  46,   26,  24 },  {  -19,  44,    0,  26 },  {    0,   0,    0,   0 } } },  /* 88: not used by a script */
    { { {  -37,  25,   58,  17 },  {  -21,  48,   45,  18 },  {  -19,  46,   26,  24 },  {  -19,  44,    0,  26 },  {    0,   0,    0,   0 } } },  /* 89: not used by a script */
    { { {  -37,  25,   45,  17 },  {  -14,  52,   44,  22 },  {  -24,  60,   24,  20 },  {  -28,  67,    0,  28 },  {  -94,  54,   20,  26 } } },  /* 90: ATTACK 5 S (Att_HADOUKEN), ATTACK 5 M (Att_HADOUKEN), ATTACK 5 L (Att_HADOUKEN) +1 */
    { { {  -64,  44,   58,  20 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  {    0,   0,    0,   0 } } },  /* 91: S PUNCH C */
    { { {    0,   0,    0,   0 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  {  -86,  62,   42,  38 } } },  /* 92: M PUNCH C */
    { { {    0,   0,    0,   0 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  {  -96,  74,   60,  16 } } },  /* 93: M PUNCH C */
    { { {  -16,  24,   76,  18 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  {    0,   0,    0,   0 } } },  /* 94: not used by a script */
    { { {  -64,  44,   58,  20 },  {  -30,  58,   60,  26 },  {  -20,  44,   40,  24 },  {  -20,  54,    0,  38 },  {    0,   0,    0,   0 } } },  /* 95: M PUNCH C */
    { { {  -16,  24,   76,  18 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  {  -86,  64,   60,  24 } } },  /* 96: S PUNCH A, super art Att_HADOUKEN (command slot 18) */
    { { {  -16,  24,   76,  18 },  {  -35,  72,   60,  29 },  {  -29,  64,   40,  24 },  {  -30,  65,    0,  38 },  {  -68,  48,   73,  16 } } },  /* 97: M PUNCH A, atca 156, UP P GUARD P S +1 */
    { { {  -16,  25,   55,  17 },  {  -14,  52,   44,  22 },  {  -24,  60,   24,  20 },  {  -28,  67,    0,  28 },  {  -72,  48,   28,  16 } } },  /* 98: KAGAMI P A */
    { { {  -41,  28,   42,  24 },  {  -13,  52,   44,  27 },  {  -67, 106,   24,  26 },  {  -84, 112,    0,  28 },  {    0,   0,    0,   0 } } },  /* 99: KAGAMI K A */
    { { {  -17,  21,  103,  16 },  {  -29,  61,   91,  27 },  {  -26,  52,   53,  36 },  {    0,   0,    0,   0 },  { -118,  93,   56,  33 } } },  /* 100: V JUMP K M A, V JUMP K L A */
    { { {  -54,  25,   68,  18 },  {  -84,  74,   52,  29 },  {  -84,  74,   26,  24 },  {  -84, 112,    0,  26 },  {  -88,  29,   54,  32 } } },  /* 101: KAGAMI P A */
    { { {   26,  25,   51,  22 },  {   20,  75,   44,  22 },  {  -16,  80,    0,  42 },  {  -16,  43,    0,  42 },  { -104, 105,    0,  41 } } },  /* 102: KAGAMI K A */
    { { {  -41,  28,   42,  24 },  {  -13,  52,   44,  27 },  {  -67, 106,   24,  26 },  {  -28,  67,    0,  28 },  { -113,  90,    0,  37 } } },  /* 103: KAGAMI K A */
    { { {  -31,  25,   71,  17 },  {  -61,  86,   65,  18 },  {  -19,  46,   41,  24 },  {  -65,  91,    0,  39 },  {  -66,  51,   43,  29 } } },  /* 104: ATTACK 2 S (Att_CHOUCHUURENGEKI), ATTACK 2 M (Att_CHOUCHUURENGEKI), ATTACK 2 L (Att_CHOUCHUURENGEKI) */
    { { {  -74,  64,   57,  20 },  {  -21,  48,   65,  18 },  {  -54,  83,   41,  24 },  {  -55,  84,    0,  39 },  {  -95,  85,   73,  20 } } },  /* 105: ATTACK 2 S (Att_CHOUCHUURENGEKI), ATTACK 2 M (Att_CHOUCHUURENGEKI), ATTACK 2 L (Att_CHOUCHUURENGEKI) */
    { { {  -36,  25,   62,  28 },  {  -21,  48,   65,  18 },  {  -33,  60,   41,  24 },  {  -50, 104,    0,  44 },  {    0,   0,    0,   0 } } },  /* 106: ATTACK 3 L (Att_HADOUKEN), ATTACK 3 S (Att_HADOUKEN), ATTACK 3 M (Att_HADOUKEN) */
    { { {  -24,  47,   72,  17 },  {  -27,  55,   62,  18 },  {  -27,  55,   34,  27 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 107: AIR S, AIR M, AIR L +37 */
    { { {  -47,  44,   87,  23 },  {  -29,  64,   72,  16 },  {  -29,  64,   40,  31 },  {  -30,  65,    0,  38 },  {  -84,  37,  101,  25 } } },  /* 108: OKIAGARI P S, Att_HADOUKEN (command slot 26) */
    { { {  -33,  33,   80,  19 },  {  -29,  64,   72,  16 },  {  -85, 121,   40,  31 },  {  -30,  65,    0,  38 },  { -106,  44,   21,  30 } } },  /* 109: OKIAGARI P S, Att_HADOUKEN (command slot 26) */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {   18,  52,    0,  62 },  {  -29,  54,    0,  29 },  {    0,   0,    0,   0 } } },  /* 110: OKIAGARI P S, super art Att_HADOUKEN (command slot 18), Att_HADOUKEN (command slot 26) */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -19,  46,   41,  24 },  {  -42,  86,    0,  39 },  {    0,   0,    0,   0 } } },  /* 111: ATTACK 4 S (Att_HADOUKEN) */
    { { {  -13,  25,   96,  17 },  {  -40,  57,   84,  18 },  {  -40,  63,   45,  38 },  {  -25,  67,    0,  45 },  {  -16,  29,   93,  68 } } },  /* 112: KAGAMI P C */
    { { {   10,  25,   95,  17 },  {  -44,  91,   73,  29 },  {  -19,  46,   41,  45 },  {  -19,  44,    0,  39 },  {    0,   0,    0,   0 } } },  /* 113: not used by a script */
    { { {  -26,  30,   96,  38 },  {  -40,  57,   84,  18 },  {  -40,  63,   45,  38 },  {  -25,  67,    0,  45 },  {    5,  20,   96,  64 } } },  /* 114: KAGAMI P C */
    { { {  -17,  21,  103,  16 },  {  -29,  61,   91,  27 },  {  -26,  52,   53,  36 },  {    0,   0,    0,   0 },  {  -54,  45,   37,  43 } } },  /* 115: V JUMP K S A, F JUMP K S A */
    { { {  -28,  24,   40,  30 },  {    4,  33,   71,  16 },  {  -10,  64,   40,  31 },  {  -24,  79,    0,  38 },  {  -68,  39,    0,  41 } } },  /* 116: ATTACK 1 S (Att_HADOUKEN) */
    { { {  -17,  21,  103,  16 },  {  -69,  94,   91,  27 },  {  -70,  96,   53,  36 },  {    0,   0,    0,   0 },  {  -88,  67,   36,  31 } } },  /* 117: saca 54 */
    { { {  -16,  24,   76,  18 },  {  -42,  89,   72,  16 },  {  -42,  88,   40,  31 },  {  -43,  89,    0,  38 },  {    0,   0,    0,   0 } } },  /* 118: ATTACK 2 S (Att_CHOUCHUURENGEKI), ATTACK 2 M (Att_CHOUCHUURENGEKI), ATTACK 2 L (Att_CHOUCHUURENGEKI) +1 */
    { { {  -33,  24,   48,  23 },  {  -29,  62,   60,  18 },  {  -29,  64,   40,  31 },  {  -30,  65,    0,  38 },  {    0,   0,    0,   0 } } },  /* 119: PIYO */
    { { {    0,   0,    0,   0 },  {   32,  44,   63,  30 },  {  -26,  81,   31,  32 },  {  -29,  83,    0,  29 },  {    0,   0,    0,   0 } } },  /* 120: OKIAGARI P S, super art Att_HADOUKEN (command slot 18), Att_HADOUKEN (command slot 26) */
    { { {  -25,  24,   87,  18 },  {  -16,  42,   72,  49 },  {  -29,  64,   40,  31 },  {  -30,  65,    0,  38 },  {    0,   0,    0,   0 } } },  /* 121: FUSHIN P S, OKIAGARI P S, super art Att_HADOUKEN (command slot 18) +1 */
};

const ATTACK_BOX necro_att_box[53] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {    0,   0,    0,   0 },  {  -90,  23,   48,  17 },  {  -67,  46,   48,  17 } } },  /* 1: S PUNCH C; attack 1 */
    { { {    0,   0,    0,   0 },  { -119,  24,   63,  12 },  {  -94,  65,   63,  12 } } },  /* 2: S PUNCH A; attack 2 */
    { { {    0,   0,    0,   0 },  { -109,  31,   67,  18 },  {  -76,  54,   67,  18 } } },  /* 3: M PUNCH A, atca 156, UP P GUARD P S +1; attack 3, 4, 76 */
    { { {    0,   0,    0,   0 },  {   -4,  33,  125,  46 },  {  -41,  24,   72,  59 } } },  /* 4: not used by a script */
    { { {    0,   0,    0,   0 },  { -147,  21,   56,  21 },  { -125, 104,   56,  21 } } },  /* 5: L PUNCH A, atca 157; attack 5, 77 */
    { { {    0,   0,    0,   0 },  {  -95,  21,   38,  21 },  {  -71,  44,   37,  17 } } },  /* 6: not used by a script */
    { { {    0,   0,    0,   0 },  {  -87,  11,   39,  24 },  {  -75,  53,   40,  15 } } },  /* 7: S KICK A; attack 7 */
    { { {    0,   0,    0,   0 },  {  -73,  17,   70,  13 },  {  -60,  35,   40,  41 } } },  /* 8: M KICK C; attack 8 */
    { { {    0,   0,    0,   0 },  { -124,  38,   28,  14 },  {  -84,  60,   28,  14 } } },  /* 9: M KICK A, UP P GUARD K S, D P GUARD K S; attack 9 */
    { { {    0,   0,    0,   0 },  {  -71,  21,   86,  47 },  {  -49,  26,   42,  80 } } },  /* 10: L KICK C; attack 10 */
    { { {    0,   0,    0,   0 },  { -128,  37,   58,  33 },  {  -92,  82,   52,  22 } } },  /* 11: L KICK A; attack 11 */
    { { {    0,   0,    0,   0 },  { -113,  15,   32,  11 },  {  -98,  74,   32,  11 } } },  /* 12: KAGAMI P A; attack 12 */
    { { {    0,   0,    0,   0 },  { -110,  35,   98,  27 },  {  -74,  33,   73,  25 } } },  /* 13: KAGAMI P A; attack 13 */
    { { {    0,   0,    0,   0 },  { -117,  28,   74,  21 },  { -100,  42,   48,  31 } } },  /* 14: KAGAMI P A; attack 14 */
    { { {    0,   0,    0,   0 },  { -105,  77,    0,  20 },  {    0,   0,    0,   0 } } },  /* 15: KAGAMI K A; attack 15 */
    { { {    0,   0,    0,   0 },  {   36,  68,    8,  24 },  {    0,   0,    0,   0 } } },  /* 16: not used by a script */
    { { {    0,   0,    0,   0 },  { -116,  22,    0,  24 },  {  -93,  78,    0,  24 } } },  /* 17: KAGAMI K A; attack 17 */
    { { {    0,   0,    0,   0 },  {  -53,  26,   47,  24 },  {    0,   0,    0,   0 } } },  /* 18: KAGAMI P C; attack 4 */
    { { {    0,   0,    0,   0 },  {  -86,  34,   24,  20 },  {  -73,  28,   42,  14 } } },  /* 19: ATTACK 6 S (Att_SENPUUKYAKU), ATTACK 6 M (Att_SENPUUKYAKU), ATTACK 6 L (Att_SENPUUKYAKU); attack 18, 63, 64 */
    { { {    0,   0,    0,   0 },  { -128,  31,  113,   7 },  { -101,  67,  104,   7 } } },  /* 20: V JUMP P S A; attack 19 */
    { { {    0,   0,    0,   0 },  { -135,  40,   55,  24 },  {  -93,  32,   57,  23 } } },  /* 21: V JUMP P L A, F JUMP P L A; attack 21 */
    { { {    0,   0,    0,   0 },  {  -47,  15,   43,  21 },  {  -32,  16,   52,  24 } } },  /* 22: V JUMP K S A, F JUMP K S A; attack 22 */
    { { {    0,   0,    0,   0 },  { -121,  12,   66,  27 },  { -107,  78,   66,  18 } } },  /* 23: V JUMP K M A, V JUMP K L A; attack 23, 24 */
    { { {    0,   0,    0,   0 },  {  -68,  17,   36,  17 },  {  -59,  37,   48,  11 } } },  /* 24: F JUMP P S A, F JUMP P M A; attack 25, 26 */
    { { {    0,   0,    0,   0 },  {  -60,  27,   33,  17 },  {  -53,  20,   48,  28 } } },  /* 25: F JUMP K M A, F JUMP K L A; attack 27, 28, 29, 30 */
    { { {    0,   0,    0,   0 },  {  -60,  27,   33,  17 },  {  -33,  20,   48,  28 } } },  /* 26: F JUMP K M A, F JUMP K L A; attack 28, 30 */
    { { {    0,   0,    0,   0 },  {  -78,  21,   86,  14 },  {  -62,  49,   79,  10 } } },  /* 27: FUSHIN P S; attack 31 */
    { { {    0,   0,    0,   0 },  {  -82,  30,   83,  18 },  {  -49,  25,   71,  26 } } },  /* 28: OKIAGARI P S, Att_HADOUKEN (command slot 26); attack 32, 71, 72 */
    { { {    0,   0,    0,   0 },  {  -97,  36,    0,  48 },  {  -59,  32,   42,  17 } } },  /* 29: OKIAGARI P S, Att_HADOUKEN (command slot 26); attack 32, 71, 72 */
    { { {  -33,   6,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 30: M PUNCH A, M PUNCH C, M KICK A +3; attack 33, 47 */
    { { { -131,  56,    4,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 31: ATTACK 5 S (Att_HADOUKEN), ATTACK 5 M (Att_HADOUKEN), ATTACK 5 L (Att_HADOUKEN); attack 37 */
    { { {    0,   0,    0,   0 },  {  -92,  18,   48,  21 },  {  -73,  61,   48,  21 } } },  /* 32: M PUNCH C; attack 54 */
    { { {    0,   0,    0,   0 },  { -114,  88,    0,  20 },  {    0,   0,    0,   0 } } },  /* 33: KAGAMI K A; attack 53 */
    { { {    0,   0,    0,   0 },  { -136,  32,   62,  23 },  { -104,  72,   62,  23 } } },  /* 34: V JUMP K L A; attack 24 */
    { { {    0,   0,    0,   0 },  {  -59,   9,   47,  20 },  {  -50,  29,   47,  20 } } },  /* 35: ATTACK 2 S (Att_CHOUCHUURENGEKI), ATTACK 2 M (Att_CHOUCHUURENGEKI), ATTACK 2 L (Att_CHOUCHUURENGEKI); attack 39, 57, 60, 65 */
    { { {    0,   0,    0,   0 },  {  -84,  28,   63,  16 },  {  -55,  39,   52,  27 } } },  /* 36: ATTACK 2 S (Att_CHOUCHUURENGEKI), ATTACK 2 M (Att_CHOUCHUURENGEKI), ATTACK 2 L (Att_CHOUCHUURENGEKI); attack 40, 41, 58, 59 ... */
    { { {    0,   0,    0,   0 },  {  -50, 102,   63,  27 },  {  -24,  53,   52,  46 } } },  /* 37: ATTACK 3 L (Att_HADOUKEN); attack 42, 43, 67 */
    { { {    0,   0,    0,   0 },  {  -37,  75,   63,  27 },  {  -24,  53,   48,  54 } } },  /* 38: ATTACK 3 L (Att_HADOUKEN); attack 43, 67 */
    { { {    0,   0,    0,   0 },  {  -63, 116,    7,  84 },  {  -24,  53,   52,  52 } } },  /* 39: ATTACK 4 S (Att_HADOUKEN); attack 44, 45, 56, 73 ... */
    { { {    0,   0,    0,   0 },  {  -52, 105,    7,  84 },  {  -26,  54,   53,  59 } } },  /* 40: ATTACK 4 S (Att_HADOUKEN) */
    { { {  -86,  61,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 41: super art Att_HADOUKEN (command slot 18); attack 52 */
    { { {    0,   0,    0,   0 },  {  -77,  26,    0,  20 },  {  -53,  33,   13,  24 } } },  /* 42: not used by a script */
    { { {    0,   0,    0,   0 },  {  -89,  32,  114,  32 },  {  -66,  51,   50,  73 } } },  /* 43: not used by a script */
    { { {    0,   0,    0,   0 },  {  -97,  90,   51,  31 },  {    0,   0,    0,   0 } } },  /* 44: not used by a script */
    { { {    0,   0,    0,   0 },  { -135,  35,  105,   9 },  { -100,  69,  104,   6 } } },  /* 45: V JUMP P M A; attack 20 */
    { { {  -37,  10,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 46: L PUNCH A, L KICK A, L KICK C; attack 33, 47 */
    { { {    0,   0,    0,   0 },  {   -1,  26,  125,  46 },  {  -19,  24,   98,  41 } } },  /* 47: KAGAMI P C */
    { { {    0,   0,    0,   0 },  {  -57,  33,    0,  30 },  {  -77,  30,   27,  19 } } },  /* 48: saca 54; attack 25 */
    { { { -127,  40,    4,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 49: not used by a script */
    { { { -123,  40,    4,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 50: not used by a script */
    { { {    0,   0,    0,   0 },  {  -39,  79,   63,  27 },  {  -24,  53,   58,  38 } } },  /* 51: ATTACK 3 S (Att_HADOUKEN); attack 42, 43 */
    { { {    0,   0,    0,   0 },  {  -44,  89,   63,  27 },  {  -24,  53,   54,  43 } } },  /* 52: ATTACK 3 M (Att_HADOUKEN); attack 42, 43, 67 */
};

const CAUGHT_BOX necro_cau_box[16] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -27,   54,    0,   16 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +100 */
    { {  -31,   58,    0,    8 } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +22 */
    { {  -25,   50,   68,   48 } },  /* 3: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +24 */
    { {  -34,   48,   80,   28 } },  /* 4: not used by a script */
    { {  -24,   48,   83,   28 } },  /* 5: not used by a script */
    { {  -31,   48,   84,   28 } },  /* 6: not used by a script */
    { {   -7,   48,   84,   28 } },  /* 7: not used by a script */
    { {  -32,   48,   83,   28 } },  /* 8: not used by a script */
    { {  -55,   48,    0,    8 } },  /* 9: KAGAMI P A */
    { {  -28,   35,   56,   58 } },  /* 10: not used by a script */
    { {  -24,   48,   44,   64 } },  /* 11: not used by a script */
    { {  -22,   48,   42,   37 } },  /* 12: AIR S, AIR M, AIR L +37 */
    { {  -35,   62,    0,    8 } },  /* 13: KAGAMI P A, KAGAMI K A */
    { {  -27,   54,   -8,   24 } },  /* 14: DASH HUMIKOMI, DASH TOBINOKI */
    { {  -35,   74,    0,   16 } },  /* 15: ATTACK 2 S (Att_CHOUCHUURENGEKI), ATTACK 2 M (Att_CHOUCHUURENGEKI), ATTACK 2 L (Att_CHOUCHUURENGEKI) +1 */
};

const HOSEI_BOX necro_hos_box[25] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -27,   54,    0,   82 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +100 */
    { {  -27,   54,    0,   61 } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +39 */
    { {  -25,   50,   68,   48 } },  /* 3: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +29 */
    { {  -35,   48,   72,   40 } },  /* 4: not used by a script */
    { {  -24,   48,   67,   40 } },  /* 5: not used by a script */
    { {  -31,   48,   70,   40 } },  /* 6: V JUMP K M A, V JUMP K L A */
    { {  -22,   48,   70,   40 } },  /* 7: not used by a script */
    { {  -32,   48,   73,   40 } },  /* 8: not used by a script */
    { {  -21,   48,   30,   40 } },  /* 9: S PUNCH C */
    { {   -1,   48,   37,   40 } },  /* 10: not used by a script */
    { {  -19,   48,   27,   40 } },  /* 11: not used by a script */
    { {  -32,   48,   31,   40 } },  /* 12: not used by a script */
    { {  -28,   48,   46,   56 } },  /* 13: not used by a script */
    { {  -11,   48,   32,   56 } },  /* 14: not used by a script */
    { {  -25,   48,   32,   56 } },  /* 15: not used by a script */
    { {   -4,   48,   58,   40 } },  /* 16: not used by a script */
    { {  -21,   48,   58,   40 } },  /* 17: not used by a script */
    { {  -55,   48,    0,   54 } },  /* 18: KAGAMI P A */
    { {  -72,   97,   22,   40 } },  /* 19: not used by a script */
    { {  -21,   27,   59,   43 } },  /* 20: not used by a script */
    { {  -43,   63,   61,   39 } },  /* 21: not used by a script */
    { {  -37,   64,    0,   79 } },  /* 22: DASH HUMIKOMI, DASH TOBINOKI */
    { {  -22,   48,   42,   37 } },  /* 23: AIR S, AIR M, AIR L +37 */
    { {  -27,   54,    0,   30 } },  /* 24: OKIAGARI P S, super art Att_HADOUKEN (command slot 18), Att_HADOUKEN (command slot 26) +1 */
};
