/*
 * YANG_HITBOX.C  Yang's hit boxes
 *
 * Each of Yang's animation frames names a row of yang_hit_ix_table (a frame line's hit field). The
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
 * rows of yang_catt_table dealt through it. Row 0 of a box table is no box.
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

const HIT_IX yang_hit_ix_table[220] = {
    /* boix  atix  cuix  hoix */
    {    0,    0,    0,    0 },  /* 0: OKIAGARI, OKIAGARI F, OKIAGARI B +17 */
    {    1,    0,    1,    1 },  /* 1: KAMAE, HURIMUKI, FRONT WALK +129 */
    {    2,    0,    2,    2 },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +34 */
    {    3,    0,    3,    3 },  /* 3: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +15 */
    {    4,    0,    3,    3 },  /* 4: JUMP FRONT, JUMP VERTICAL, JUMP BACK +11 */
    {    1,    0,    1,    1 },  /* 5: not used by a script */
    {    1,    0,    1,    1 },  /* 6: GUARD AIR */
    {    2,    0,    2,    2 },  /* 7: not used by a script */
    {    3,    0,    3,    3 },  /* 8: GUARD AIR */
    {    9,    0,    1,    1 },  /* 9: not used by a script */
    {   14,    0,    1,    1 },  /* 10: M KICK A, atca 212 */
    {   10,    1,    1,    1 },  /* 11: not used by a script */
    {   11,    2,    1,    1 },  /* 12: M KICK A, atca 212 */
    {   11,   48,    1,    1 },  /* 13: M KICK A, atca 212 */
    {   11,    0,    1,    1 },  /* 14: M KICK A, atca 212 */
    {   12,    0,    1,    1 },  /* 15: M KICK A, atca 212 */
    {   15,    0,    1,    1 },  /* 16: saca 52 */
    {   16,    0,    1,    1 },  /* 17: UP P GUARD P S, UP P GUARD P M, saca 52 */
    {   17,    3,    1,    1 },  /* 18: UP P GUARD P S, saca 52 */
    {   17,    4,    1,    1 },  /* 19: UP P GUARD P S, UP P GUARD P M, saca 52 */
    {   17,    0,    1,    1 },  /* 20: UP P GUARD P S, UP P GUARD P M, saca 52 */
    {   18,    0,    1,    1 },  /* 21: not used by a script */
    {   19,    0,    1,    1 },  /* 22: not used by a script */
    {   20,    0,    1,    1 },  /* 23: not used by a script */
    {   21,   60,    1,    1 },  /* 24: UP P GUARD P L, saca 52 */
    {   21,   61,    1,    1 },  /* 25: UP P GUARD P L, saca 52 */
    {   21,    0,    1,    1 },  /* 26: UP P GUARD P L, saca 52 */
    {   23,    0,    1,    1 },  /* 27: S PUNCH A, atca 200 */
    {   24,    6,    1,    1 },  /* 28: S PUNCH A, atca 200 */
    {   24,   39,    1,    1 },  /* 29: S PUNCH A, atca 200 */
    {   25,    0,    1,    1 },  /* 30: M PUNCH B, atca 204, super art Att_SLIDE_and_JUMP (command slot 17) */
    {   26,    7,    1,    1 },  /* 31: M PUNCH B, atca 204 */
    {   26,    0,    1,    1 },  /* 32: not used by a script */
    {   27,    0,    1,    1 },  /* 33: M PUNCH A, atca 203, super art Att_SLIDE_and_JUMP (command slot 17) */
    {   28,    8,    1,    1 },  /* 34: M PUNCH A, atca 203 */
    {   28,   40,    1,    1 },  /* 35: M PUNCH A, atca 203 */
    {   28,    0,    1,    1 },  /* 36: M PUNCH A, atca 203 */
    {   31,    0,    1,    1 },  /* 37: L PUNCH A, atca 206 */
    {   31,    9,    1,    1 },  /* 38: L PUNCH A, atca 206 */
    {   32,   42,    1,    1 },  /* 39: L PUNCH A, atca 206 */
    {   33,   43,    1,    1 },  /* 40: L PUNCH A, atca 206 */
    {   33,    0,    1,    1 },  /* 41: L PUNCH A, atca 206 */
    {   34,    0,    1,    1 },  /* 42: L PUNCH B, atca 208 */
    {   35,    0,    1,    1 },  /* 43: not used by a script */
    {   36,   10,    1,    1 },  /* 44: L PUNCH B, atca 208 */
    {   36,   44,    1,    1 },  /* 45: L PUNCH B, atca 208 */
    {   36,    0,    1,    1 },  /* 46: L PUNCH B, atca 208 */
    {   37,    0,    1,    1 },  /* 47: L PUNCH B, atca 158, atca 208 */
    {   38,    0,    1,    1 },  /* 48: atca 158 */
    {   39,   11,    1,    1 },  /* 49: atca 158 */
    {   39,   45,    1,    1 },  /* 50: atca 158 */
    {   39,    0,    1,    1 },  /* 51: atca 158 */
    {   40,    0,    1,    1 },  /* 52: S KICK A, atca 209 */
    {   41,   12,    1,    1 },  /* 53: not used by a script */
    {   41,   13,    1,    1 },  /* 54: not used by a script */
    {   41,    0,    1,    1 },  /* 55: not used by a script */
    {   41,   46,    1,    1 },  /* 56: S KICK A, atca 209 */
    {   41,   47,    1,    1 },  /* 57: S KICK A, atca 209 */
    {   24,    0,    1,    1 },  /* 58: S PUNCH A, atca 200 */
    {   13,    0,    1,    1 },  /* 59: M KICK A, atca 212 */
    {   46,    0,    2,    2 },  /* 60: KAGAMI P A, atca 218, atca 221 */
    {   47,   14,    2,    2 },  /* 61: atca 218 */
    {   47,   19,    2,    2 },  /* 62: atca 218 */
    {   47,    0,    2,    2 },  /* 63: KAGAMI P A, atca 218, atca 221 */
    {   48,    0,    2,    2 },  /* 64: KAGAMI P A, atca 224 */
    {   48,   56,    2,    2 },  /* 65: KAGAMI P A, atca 224 */
    {   49,    0,    2,    2 },  /* 66: KAGAMI P A, atca 224 */
    {   59,    0,    2,    2 },  /* 67: KAGAMI K A, atca 227, atca 230 */
    {   54,   17,    2,    2 },  /* 68: KAGAMI K A, atca 227, atca 230 */
    {   54,    0,    2,    2 },  /* 69: KAGAMI K A, atca 227, atca 230 */
    {   54,   57,    2,    2 },  /* 70: KAGAMI K A, atca 230 */
    {   56,    0,    2,    8 },  /* 71: KAGAMI K A, atca 233 */
    {   57,    0,    2,    8 },  /* 72: atca 233 */
    {   58,   18,    2,    8 },  /* 73: not used by a script */
    {   58,   58,    2,    8 },  /* 74: KAGAMI K A, atca 233 */
    {   58,    0,    2,    8 },  /* 75: KAGAMI K A, atca 233 */
    {   55,    0,    1,    1 },  /* 76: UP P GUARD P S, UP P GUARD P M */
    {   17,    5,    1,    1 },  /* 77: UP P GUARD P M */
    {   22,    0,    1,    1 },  /* 78: UP P GUARD P L, saca 52 */
    {   50,    0,    1,    1 },  /* 79: UP P GUARD P L, saca 52 */
    {  100,    0,    5,    1 },  /* 80: ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI) +1 */
    {   53,    0,    5,    1 },  /* 81: OKIAGARI P S, ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI) +5 */
    {   51,    0,    3,    1 },  /* 82: ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI) +4 */
    {   52,    0,    3,    1 },  /* 83: ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI) +3 */
    {   61,    0,    1,    1 },  /* 84: OKIAGARI P S */
    {   62,    0,    1,    1 },  /* 85: not used by a script */
    {    1,    0,    1,    1 },  /* 86: GUARD HEAD */
    {    1,    0,    1,    1 },  /* 87: GUARD UP */
    {    2,    0,    2,    2 },  /* 88: GUARD DOWN */
    {   72,    0,    1,    1 },  /* 89: DASH HUMIKOMI */
    {   73,    0,    1,    1 },  /* 90: DASH HUMIKOMI */
    {    0,    0,    0,    2 },  /* 91: TATAKI S, OKIAGARI, OKIAGARI F +16 */
    {   74,    0,    0,    0 },  /* 92: not used by a script */
    {   47,   54,    2,    2 },  /* 93: KAGAMI P A, atca 221 */
    {   47,   55,    2,    2 },  /* 94: KAGAMI P A, atca 221 */
    {   49,   15,    2,    2 },  /* 95: KAGAMI P A, atca 224 */
    {   49,   16,    2,    2 },  /* 96: KAGAMI P A, atca 224 */
    {  107,    0,    1,    1 },  /* 97: HANASARE, exca 86, exca 87 */
    {   79,    0,    1,    1 },  /* 98: M KICK C, atca 214 */
    {   80,    0,    1,    1 },  /* 99: M KICK C, atca 214 */
    {   81,    0,    4,    4 },  /* 100: M KICK C, atca 214 */
    {   82,    0,    4,    4 },  /* 101: M KICK C, atca 214 */
    {   42,    0,    4,    4 },  /* 102: M KICK C, atca 214 */
    {   43,   20,    1,    1 },  /* 103: M KICK C, atca 214, exca 13 */
    {   83,    0,   17,   18 },  /* 104: not used by a script */
    {   83,   22,   17,   18 },  /* 105: not used by a script */
    {   84,   23,   17,   18 },  /* 106: not used by a script */
    {   84,    0,   17,   18 },  /* 107: not used by a script */
    {   85,    0,    1,    1 },  /* 108: ATTACK 4 S (Att_SENPUUKYAKU), ATTACK 4 M (Att_SENPUUKYAKU), ATTACK 4 L (Att_SENPUUKYAKU) +1 */
    {   86,    0,    1,    1 },  /* 109: ATTACK 4 S (Att_SENPUUKYAKU), ATTACK 4 M (Att_SENPUUKYAKU), ATTACK 4 L (Att_SENPUUKYAKU) +1 */
    {   87,   24,    1,    1 },  /* 110: ATTACK 4 S (Att_SENPUUKYAKU), ATTACK 4 M (Att_SENPUUKYAKU), ATTACK 4 L (Att_SENPUUKYAKU) +1 */
    {   88,   25,    1,    1 },  /* 111: saca 69 */
    {   89,    0,    1,    1 },  /* 112: ATTACK 4 S (Att_SENPUUKYAKU), ATTACK 4 M (Att_SENPUUKYAKU), ATTACK 4 L (Att_SENPUUKYAKU) +1 */
    {   90,   26,    1,    1 },  /* 113: ATTACK 2 S (Att_HADOUKEN), saca 65 */
    {   90,   27,    1,    1 },  /* 114: ATTACK 2 S (Att_HADOUKEN), saca 65 */
    {  138,   27,    1,    1 },  /* 115: ATTACK 2 S (Att_HADOUKEN), saca 65 */
    {   93,    0,    4,    4 },  /* 116: atca 156, atca 260, ATTACK 5 S +2 */
    {   91,    0,    4,    4 },  /* 117: atca 156, atca 260, ATTACK 5 S +1 */
    {   91,   29,    4,    4 },  /* 118: atca 156, atca 260, ATTACK 5 S +1 */
    {   92,    0,    4,    4 },  /* 119: atca 156, atca 260, ATTACK 5 S +1 */
    {   93,   30,    3,    3 },  /* 120: ATTACK 5 S, saca 75 */
    {   94,   31,    4,    4 },  /* 121: ATTACK 5 S */
    {   94,    0,    3,    3 },  /* 122: ATTACK 5 S, saca 75 */
    {   95,    0,    4,    4 },  /* 123: ATTACK 5 S, saca 52, saca 75 */
    {   96,    0,    2,    2 },  /* 124: ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI), saca 67 +1 */
    {   97,    0,    2,    2 },  /* 125: OKIAGARI P S, ATTACK 3 S (Att_TENSHINSENKYUUTAI), saca 66 */
    {   97,    0,    2,    2 },  /* 126: OKIAGARI P S, ATTACK 3 S (Att_TENSHINSENKYUUTAI), saca 66 */
    {   97,   32,    2,    2 },  /* 127: ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI) +3 */
    {   99,   33,    2,    2 },  /* 128: OKIAGARI P S, ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI) +4 */
    {  100,   34,    5,    1 },  /* 129: ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI) +4 */
    {  100,   64,    5,    1 },  /* 130: OKIAGARI P S, ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI) +4 */
    {  103,    0,    3,    3 },  /* 131: V JUMP P M A, F JUMP P M A, F JUMP P L A +5 */
    {  104,    0,    3,    3 },  /* 132: V JUMP P M A, F JUMP P M A, atca 238 +1 */
    {  105,   37,    3,    3 },  /* 133: V JUMP P M A, F JUMP P M A, atca 238 +1 */
    {  105,   38,    3,    3 },  /* 134: not used by a script */
    {  106,    0,    3,    3 },  /* 135: V JUMP P M A, F JUMP P M A, F JUMP P L A +5 */
    {   29,   41,    1,    1 },  /* 136: M PUNCH B, atca 204 */
    {   29,    0,    1,    1 },  /* 137: M PUNCH B, atca 204, super art Att_SLIDE_and_JUMP (command slot 17) +1 */
    {   30,    0,    1,    1 },  /* 138: M PUNCH B, atca 204, super art Att_SLIDE_and_JUMP (command slot 17) */
    {  101,    0,    3,    3 },  /* 139: V JUMP P S A, F JUMP P S A, atca 236 +1 */
    {  102,   35,    3,    3 },  /* 140: F JUMP P S A, atca 248 */
    {  102,   36,    3,    3 },  /* 141: V JUMP P S A, atca 236 */
    {  105,   49,    3,    3 },  /* 142: F JUMP P L A, atca 252 */
    {  105,   50,    3,    3 },  /* 143: F JUMP P L A, atca 252 */
    {  105,    0,    3,    3 },  /* 144: V JUMP P M A, F JUMP P M A, atca 238 +1 */
    {   44,   21,    1,    1 },  /* 145: M KICK C, atca 214 */
    {   45,    0,    1,    1 },  /* 146: M KICK C, atca 214, exca 75 +1 */
    {    1,   53,    1,    1 },  /* 147: M PUNCH A, M PUNCH B, L PUNCH A +5 */
    {  110,    0,    1,    1 },  /* 148: FUSHIN P S */
    {  111,    0,    1,    1 },  /* 149: FUSHIN P S */
    {  112,    0,    1,    1 },  /* 150: FUSHIN P S */
    {  113,   62,    1,    1 },  /* 151: FUSHIN P S */
    {  113,   63,    1,    1 },  /* 152: FUSHIN P S */
    {  113,    0,    1,    1 },  /* 153: FUSHIN P S */
    {  114,    0,    1,    1 },  /* 154: exca 63, exca 64, exca 73 +2 */
    {  115,    0,    1,    1 },  /* 155: exca 63, exca 64, exca 73 +2 */
    {   63,   65,    2,    2 },  /* 156: ATTACK 6 S (Att_TENSHINSENKYUUTAI), saca 75 */
    {   98,   66,    2,    2 },  /* 157: not used by a script */
    {   64,    0,    3,    3 },  /* 158: V JUMP P L A, atca 240 */
    {   65,    0,    3,    3 },  /* 159: V JUMP P L A, atca 240 */
    {   66,   67,    3,    3 },  /* 160: not used by a script */
    {   66,   68,    3,    3 },  /* 161: not used by a script */
    {   66,   69,    3,    3 },  /* 162: V JUMP P L A, atca 240 */
    {   66,   70,    3,    3 },  /* 163: not used by a script */
    {   66,   71,    3,    3 },  /* 164: not used by a script */
    {   66,   72,    3,    3 },  /* 165: V JUMP P L A, atca 240 */
    {   66,   73,    3,    3 },  /* 166: V JUMP P L A, atca 240 */
    {   67,    0,    3,    3 },  /* 167: V JUMP K L A, F JUMP K L A, atca 246 +3 */
    {   68,   74,    3,    3 },  /* 168: V JUMP K L A, F JUMP K L A, atca 246 +2 */
    {   68,   75,    3,    3 },  /* 169: V JUMP K L A, F JUMP K L A, atca 246 +2 */
    {   68,    0,    3,    3 },  /* 170: V JUMP K L A, F JUMP K L A, atca 246 +1 */
    {  118,    0,    3,    3 },  /* 171: V JUMP K S A, V JUMP K M A, F JUMP K S A +6 */
    {  116,    0,    3,    3 },  /* 172: V JUMP K S A, V JUMP K M A, F JUMP K S A +5 */
    {  117,    0,    3,    3 },  /* 173: V JUMP K S A, V JUMP K M A, F JUMP K S A +5 */
    {  118,   78,    3,    3 },  /* 174: V JUMP K S A, F JUMP K S A, atca 242 +1 */
    {  118,   79,    3,    3 },  /* 175: V JUMP K S A, F JUMP K S A, atca 242 +1 */
    {  118,   80,    3,    3 },  /* 176: V JUMP K M A, F JUMP K M A, atca 244 +1 */
    {  118,   81,    3,    3 },  /* 177: V JUMP K M A, F JUMP K M A, atca 244 +1 */
    {  119,    0,    3,    3 },  /* 178: F JUMP K S B, F JUMP K M B, F JUMP K L B +3 */
    {  120,    0,    3,    3 },  /* 179: F JUMP K S B, F JUMP K M B, F JUMP K L B +3 */
    {  121,   82,    3,    3 },  /* 180: F JUMP K S B, F JUMP K M B, F JUMP K L B +3 */
    {  121,   83,    3,    3 },  /* 181: F JUMP K S B, F JUMP K M B, F JUMP K L B +3 */
    {  122,    0,    1,    1 },  /* 182: exca 65, exca 66 */
    {  123,    0,    1,    1 },  /* 183: exca 51, exca 52 */
    {  124,    0,    1,    1 },  /* 184: exca 53, exca 54 */
    {  125,    0,    1,    1 },  /* 185: exca 53, exca 54 */
    {  126,   84,    1,    1 },  /* 186: Att_HADOUKEN (command slot 22), saca 74 */
    {  127,    0,    1,    1 },  /* 187: Att_HADOUKEN (command slot 22), saca 74 */
    {  128,    0,   17,   19 },  /* 188: AIR S, AIR M, AIR L +36 */
    {    0,    0,    0,    1 },  /* 189: ATTACK 5 S, ATTACK 6 S (Att_TENSHINSENKYUUTAI), super art Att_SLIDE_and_JUMP (command slot 17) +1 */
    {    0,   51,    0,    1 },  /* 190: super art Att_SLIDE_and_JUMP (command slot 17) */
    {   29,   52,    1,    1 },  /* 191: super art Att_SLIDE_and_JUMP (command slot 17) */
    {    0,    0,    0,    3 },  /* 192: AIR S, AIR M, AIR L +2 */
    {  131,    0,    1,    1 },  /* 193: Att_HADOUKEN (command slot 22), saca 74 */
    {  132,    0,    1,    2 },  /* 194: ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI), saca 67 +1 */
    {  133,   85,    1,    1 },  /* 195: L KICK A, atca 215 */
    {  133,   86,    1,    1 },  /* 196: L KICK A, atca 215 */
    {  134,    0,    1,    1 },  /* 197: L KICK A, atca 215 */
    {   98,   87,    2,    2 },  /* 198: saca 75 */
    {   99,   88,    1,    2 },  /* 199: saca 75 */
    {   17,   89,    1,    1 },  /* 200: not used by a script */
    {    1,   90,    1,    1 },  /* 201: L KICK A */
    {  136,    0,    1,    1 },  /* 202: ATTACK 2 S (Att_HADOUKEN), ATTACK 2 SP (Att_HADOUKEN) */
    {  137,   91,    3,    3 },  /* 203: saca 70, saca 76 */
    {    0,    0,    0,   21 },  /* 204: NEKOROBI S */
    {  133,    0,    1,    1 },  /* 205: L KICK A */
    {   46,    0,   18,    2 },  /* 206: KAGAMI P A */
    {   47,   14,   18,    2 },  /* 207: KAGAMI P A */
    {   47,   19,   18,    2 },  /* 208: KAGAMI P A */
    {   47,    0,   18,    2 },  /* 209: KAGAMI P A */
    {   59,    0,   18,    2 },  /* 210: KAGAMI K A */
    {   54,   17,   18,    2 },  /* 211: KAGAMI K A */
    {   54,    0,   18,    2 },  /* 212: KAGAMI K A */
    {  100,   92,    5,    1 },  /* 213: saca 75 */
    {  107,    0,    1,    1 },  /* 214: exca 84, exca 85 */
    {   66,    0,    3,    3 },  /* 215: V JUMP P L A, atca 240 */
    {    1,    0,    1,    0 },  /* 216: LOSE SONABA */
    {  132,   65,    1,    2 },  /* 217: saca 67, saca 68 */
    {  138,    0,    1,    1 },  /* 218: atca 159, ATTACK 2 S (Att_HADOUKEN) */
    {  138,   26,    1,    1 },  /* 219: atca 159 */
};

const BODY_BOX yang_body_box[139] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {  -10,  22,   71,  21 },  {  -29,  53,   70,   7 },  {  -29,  53,   34,  35 },  {  -34,  58,    0,  32 },  {    0,   0,    0,   0 } } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +129 */
    { { {  -12,  27,   46,  20 },  {  -32,  62,   41,  17 },  {    0,   0,    0,   0 },  {  -44,  82,    0,  42 },  {    0,   0,    0,   0 } } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +35 */
    { { {   -7,  19,   98,  20 },  {  -21,  50,   88,  14 },  {  -16,  44,   70,  20 },  {  -24,  48,   32,  36 },  {    0,   0,    0,   0 } } },  /* 3: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +16 */
    { { {   -7,  19,   98,  20 },  {  -21,  50,   88,  14 },  {  -16,  44,   70,  20 },  {  -24,  48,   32,  36 },  {    0,   0,    0,   0 } } },  /* 4: JUMP FRONT, JUMP VERTICAL, JUMP BACK +11 */
    { { {    6,  22,   74,  14 },  {   -8,  44,   60,  14 },  {   -2,  38,   36,  22 },  {  -26,  54,    0,  34 },  {    0,   0,    0,   0 } } },  /* 5: not used by a script */
    { { {   -4,  18,   74,  14 },  {  -18,  46,   62,  14 },  {   -6,  36,   36,  26 },  {  -28,  56,    0,  34 },  {    0,   0,    0,   0 } } },  /* 6: not used by a script */
    { { {   -4,  18,   46,  14 },  {    0,   0,    0,   0 },  {  -20,  48,   34,  18 },  {  -26,  54,    0,  32 },  {    0,   0,    0,   0 } } },  /* 7: not used by a script */
    { { {  -18,  18,   68,  14 },  {  -30,  48,   58,  14 },  {  -24,  42,   36,  22 },  {  -24,  40,   14,  20 },  {    0,   0,    0,   0 } } },  /* 8: not used by a script */
    { { {    0,  25,   79,  20 },  {  -16,  53,   67,  16 },  {  -32,  63,   21,  47 },  {  -21,  48,    0,  34 },  {    0,   0,    0,   0 } } },  /* 9: not used by a script */
    { { {   18,  26,   68,  21 },  {  -11,  53,   57,  24 },  {  -36,  69,   44,  22 },  {  -20,  49,    0,  56 },  {    0,   0,    0,   0 } } },  /* 10: not used by a script */
    { { {   13,  40,   70,  16 },  {   -2,  44,   60,  16 },  {  -46,  53,   40,  50 },  {  -40,  65,    0,  56 },  {  -64,  46,   82,  29 } } },  /* 11: M KICK A, atca 212 */
    { { {   16,  29,   70,  19 },  {  -19,  63,   65,  16 },  {  -64, 104,   42,  24 },  {  -32,  61,    0,  36 },  {    0,   0,    0,   0 } } },  /* 12: M KICK A, atca 212 */
    { { {    6,  28,   70,  21 },  {  -35,  72,   58,  16 },  {  -58,  94,   27,  31 },  {  -32,  58,    0,  34 },  {    0,   0,    0,   0 } } },  /* 13: M KICK A, atca 212 */
    { { {    5,  27,   74,  21 },  {  -17,  60,   64,  16 },  {  -31,  76,   38,  28 },  {  -32,  61,    0,  36 },  {    0,   0,    0,   0 } } },  /* 14: M KICK A, atca 212 */
    { { {  -10,  16,   74,  14 },  {  -26,  46,   62,  14 },  {  -16,  34,   34,  26 },  {  -38,  60,    0,  32 },  {    0,   0,    0,   0 } } },  /* 15: saca 52 */
    { { {  -18,  16,   68,  14 },  {  -24,  44,   58,  12 },  {   -8,  30,   36,  22 },  {  -30,  54,    0,  34 },  {    0,   0,    0,   0 } } },  /* 16: UP P GUARD P S, UP P GUARD P M, saca 52 */
    { { {  -28,  16,   68,  14 },  {  -32,  44,   58,  12 },  {  -16,  30,   36,  22 },  {  -30,  54,    0,  34 },  {  -66,  32,   60,  12 } } },  /* 17: UP P GUARD P S, saca 52, UP P GUARD P M */
    { { {   -6,  16,   70,  14 },  {  -20,  46,   58,  12 },  {  -20,  46,   36,  22 },  {  -22,  50,    0,  34 },  {    0,   0,    0,   0 } } },  /* 18: not used by a script */
    { { {   -6,  16,   70,  14 },  {  -20,  46,   58,  12 },  {  -20,  46,   36,  22 },  {  -22,  50,    0,  34 },  {    0,   0,    0,   0 } } },  /* 19: not used by a script */
    { { {  -20,  16,   60,  14 },  {  -22,  40,   54,  14 },  {  -12,  34,   36,  22 },  {  -30,  54,    0,  34 },  {    0,   0,    0,   0 } } },  /* 20: not used by a script */
    { { {  -26,  16,   64,  14 },  {  -34,  46,   56,  12 },  {  -24,  30,   36,  22 },  {  -40,  74,    0,  34 },  {  -64,  28,   58,  12 } } },  /* 21: UP P GUARD P L, saca 52 */
    { { {  -20,  16,   68,  14 },  {  -28,  46,   58,  12 },  {  -22,  30,   36,  22 },  {  -40,  66,    0,  34 },  {  -58,  28,   62,  10 } } },  /* 22: UP P GUARD P L, saca 52 */
    { { {  -23,  20,   70,  16 },  {  -37,  61,   54,  18 },  {  -28,  44,   34,  22 },  {  -40,  63,    0,  32 },  {    0,   0,    0,   0 } } },  /* 23: S PUNCH A, atca 200 */
    { { {  -23,  20,   70,  16 },  {  -37,  61,   54,  18 },  {  -28,  44,   34,  22 },  {  -40,  63,    0,  32 },  {  -80,  66,   57,  23 } } },  /* 24: S PUNCH A, atca 200 */
    { { {  -23,  37,   69,  16 },  {  -37,  66,   54,  18 },  {  -37,  64,   34,  22 },  {  -57,  87,    0,  32 },  {    0,   0,    0,   0 } } },  /* 25: M PUNCH B, atca 204, super art Att_SLIDE_and_JUMP (command slot 17) */
    { { {  -30,  29,   67,  16 },  {  -37,  66,   54,  18 },  {  -31,  57,   34,  22 },  {  -46,  87,    0,  32 },  {  -68,  55,   45,  31 } } },  /* 26: M PUNCH B, atca 204 */
    { { {  -18,  20,   70,  16 },  {  -31,  54,   54,  18 },  {  -26,  44,   34,  22 },  {  -42,  66,    0,  32 },  {    0,   0,    0,   0 } } },  /* 27: M PUNCH A, atca 203, super art Att_SLIDE_and_JUMP (command slot 17) */
    { { {  -18,  21,   70,  18 },  {  -37,  66,   54,  18 },  {  -31,  57,   34,  22 },  {  -55,  98,    0,  32 },  {  -61,  40,   51,  34 } } },  /* 28: M PUNCH A, atca 203 */
    { { {  -24,  16,   66,  14 },  {  -30,  60,   58,  10 },  {  -37,  66,   34,  22 },  {  -52,  87,    0,  32 },  {  -63,  53,   49,  31 } } },  /* 29: M PUNCH B, atca 204, super art Att_SLIDE_and_JUMP (command slot 17) +1 */
    { { {  -30,  29,   67,  16 },  {  -37,  66,   54,  18 },  {  -31,  57,   34,  22 },  {  -46,  87,    0,  32 },  {  -43,  22,   50,  26 } } },  /* 30: M PUNCH B, atca 204, super art Att_SLIDE_and_JUMP (command slot 17) */
    { { {  -23,  31,   70,  20 },  {  -39,  66,   55,  16 },  {  -32,  54,   36,  22 },  {  -45,  76,    0,  34 },  {    0,   0,    0,   0 } } },  /* 31: L PUNCH A, atca 206 */
    { { {  -23,  31,   70,  20 },  {  -39,  66,   55,  16 },  {  -32,  54,   36,  22 },  {  -45,  76,    0,  34 },  {  -57,  46,   53,  47 } } },  /* 32: L PUNCH A, atca 206 */
    { { {  -23,  31,   70,  20 },  {  -39,  66,   55,  16 },  {  -32,  54,   36,  22 },  {  -45,  76,    0,  34 },  {  -57,  46,   53,  47 } } },  /* 33: L PUNCH A, atca 206 */
    { { {  -30,  26,   68,  21 },  {  -60,  88,   62,  17 },  {  -42,  69,   34,  35 },  {  -34,  58,    0,  32 },  {    0,   0,    0,   0 } } },  /* 34: L PUNCH B, atca 208 */
    { { {  -28,  16,   66,  14 },  {  -30,  46,   60,  12 },  {  -16,  36,   34,  24 },  {  -38,  68,    0,  34 },  {    0,   0,    0,   0 } } },  /* 35: not used by a script */
    { { {  -32,  30,   64,  20 },  {  -38,  67,   59,  12 },  {  -40,  65,   36,  22 },  {  -56,  95,    0,  34 },  {  -70,  54,   43,  33 } } },  /* 36: L PUNCH B, atca 208 */
    { { {  -23,  28,   66,  21 },  {  -61,  89,   56,  14 },  {  -36,  57,   36,  20 },  {  -55,  88,    0,  34 },  {    0,   0,    0,   0 } } },  /* 37: L PUNCH B, atca 158, atca 208 */
    { { {  -28,  16,   66,  14 },  {  -30,  46,   60,  12 },  {  -16,  36,   34,  24 },  {  -38,  68,    0,  34 },  {    0,   0,    0,   0 } } },  /* 38: atca 158 */
    { { {  -26,  16,   64,  14 },  {  -38,  56,   56,  12 },  {  -24,  36,   36,  20 },  {  -38,  68,    0,  34 },  {  -66,  24,   60,  12 } } },  /* 39: atca 158 */
    { { {  -14,  16,   78,  14 },  {  -28,  46,   68,  12 },  {  -16,  30,   38,  28 },  {  -30,  54,    0,  36 },  {    0,   0,    0,   0 } } },  /* 40: S KICK A, atca 209 */
    { { {  -12,  23,   79,  19 },  {  -30,  54,   68,  16 },  {  -40,  72,   40,  30 },  {  -37,  61,    0,  41 },  {  -66,  42,    0,  52 } } },  /* 41: S KICK A, atca 209 */
    { { {  -20,  36,   86,  19 },  {  -51,  86,   76,  12 },  {  -43,  60,   23,  54 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 42: M KICK C, atca 214 */
    { { {  -17,  26,   87,  19 },  {  -48,  89,   78,  12 },  {  -37,  66,   44,  35 },  {  -36,  60,    0,  42 },  {  -80,  62,   53,  28 } } },  /* 43: M KICK C, atca 214, exca 13 */
    { { {  -17,  26,   81,  19 },  {  -48,  80,   73,  12 },  {  -37,  66,   44,  35 },  {  -36,  60,    0,  42 },  {  -80,  62,   41,  28 } } },  /* 44: M KICK C, atca 214 */
    { { {  -17,  26,   76,  19 },  {  -48,  94,   67,  12 },  {  -37,  66,   44,  25 },  {  -36,  60,    0,  42 },  {  -67,  62,   30,  28 } } },  /* 45: M KICK C, atca 214, exca 75 +1 */
    { { {  -24,  34,   47,  20 },  {  -41,  69,   36,  16 },  {    0,   0,    0,   0 },  {  -39,  78,    0,  36 },  {    0,   0,    0,   0 } } },  /* 46: KAGAMI P A, atca 218, atca 221 */
    { { {  -31,  49,   51,  20 },  {  -41,  69,   40,  16 },  {    0,   0,    0,   0 },  {  -46,  79,    0,  40 },  {  -82,  60,   45,  16 } } },  /* 47: atca 218, KAGAMI P A, atca 221 */
    { { {  -26,  34,   55,  20 },  {  -55,  81,   36,  30 },  {    0,   0,    0,   0 },  {  -52,  83,    0,  36 },  {    0,   0,    0,   0 } } },  /* 48: KAGAMI P A, atca 224 */
    { { {  -26,  41,   55,  20 },  {  -54,  89,   36,  20 },  {    0,   0,    0,   0 },  {  -55,  89,    0,  36 },  {  -71,  45,   45,  19 } } },  /* 49: KAGAMI P A, atca 224 */
    { { {  -28,  16,   68,  14 },  {  -32,  46,   58,  14 },  {  -22,  34,   34,  26 },  {  -36,  64,    0,  32 },  {    0,   0,    0,   0 } } },  /* 50: UP P GUARD P L, saca 52 */
    { { {    2,  16,   80,  14 },  {  -16,  44,   70,  14 },  {  -38,  64,   54,  16 },  {  -26,  50,   34,  18 },  {    0,   0,    0,   0 } } },  /* 51: ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI) +4 */
    { { {  -12,  16,   82,  14 },  {  -22,  44,   72,  14 },  {  -12,  30,   46,  24 },  {  -26,  42,    8,  36 },  {    0,   0,    0,   0 } } },  /* 52: ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI) +3 */
    { { {  -36,  22,   64,  28 },  {  -28,  56,   52,  14 },  {  -30,  64,   40,  14 },  {   14,  16,   22,  24 },  {    0,   0,    0,   0 } } },  /* 53: OKIAGARI P S, ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI) +5 */
    { { {    3,  30,   48,  23 },  {  -34,  69,   39,  19 },  {  -35,  69,   16,  23 },  {  -36,  70,    0,  16 },  {  -82,  65,    0,  19 } } },  /* 54: KAGAMI K A, atca 227, atca 230 */
    { { {  -28,  16,   68,  14 },  {  -32,  44,   58,  12 },  {  -16,  30,   36,  22 },  {  -30,  54,    0,  34 },  {    0,   0,    0,   0 } } },  /* 55: UP P GUARD P S, UP P GUARD P M */
    { { {   -3,  32,   52,  21 },  {  -36,  78,   39,  18 },  {  -43,  90,    0,  41 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 56: KAGAMI K A, atca 233 */
    { { {   -4,  24,   56,  14 },  {  -34,  71,   40,  18 },  {  -55,  99,    0,  41 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 57: atca 233 */
    { { {  -12,  35,   56,  15 },  {  -42,  69,   33,  26 },  {  -52,  87,    0,  34 },  {  -48,  80,    0,  18 },  {  -77,  27,    0,  25 } } },  /* 58: KAGAMI K A, atca 233 */
    { { {    3,  30,   48,  23 },  {  -34,  69,   39,  19 },  {  -35,  69,   16,  23 },  {  -36,  70,    0,  16 },  {    0,   0,    0,   0 } } },  /* 59: KAGAMI K A, atca 227, atca 230 */
    { { {  -36,  22,   64,  28 },  {  -28,  56,   52,  14 },  {  -30,  64,   40,  14 },  {   14,  16,   22,  24 },  {    0,   0,    0,   0 } } },  /* 60: not used by a script */
    { { {    2,  16,   72,  14 },  {  -16,  44,   62,  14 },  {  -38,  64,   46,  16 },  {  -26,  50,   26,  18 },  {    0,   0,    0,   0 } } },  /* 61: OKIAGARI P S */
    { { {   -4,  16,   68,  14 },  {  -16,  44,   56,  14 },  {  -24,  52,   38,  16 },  {  -32,  50,    8,  28 },  {    0,   0,    0,   0 } } },  /* 62: not used by a script */
    { { {  -16,  36,   20,  10 },  {    0,   0,    0,   0 },  {  -18,  40,    0,  18 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 63: ATTACK 6 S (Att_TENSHINSENKYUUTAI), saca 75 */
    { { {  -16,  16,   96,  14 },  {  -28,  44,   86,  14 },  {  -12,  32,   62,  22 },  {  -30,  46,   46,  26 },  {    0,   0,    0,   0 } } },  /* 64: V JUMP P L A, atca 240 */
    { { {  -26,  16,   96,  14 },  {  -34,  46,   84,  14 },  {  -12,  40,   60,  22 },  {  -24,  46,   40,  22 },  {    0,   0,    0,   0 } } },  /* 65: V JUMP P L A, atca 240 */
    { { {  -34,  16,   96,  14 },  {  -40,  52,   86,  14 },  {  -20,  56,   62,  22 },  {  -16,  32,   28,  32 },  {  -79,  60,   81,  16 } } },  /* 66: V JUMP P L A, atca 240 */
    { { {  -16,  16,   96,  14 },  {  -28,  44,   86,  14 },  {  -12,  32,   62,  22 },  {  -36,  46,   46,  26 },  {    0,   0,    6,   0 } } },  /* 67: V JUMP K L A, F JUMP K L A, atca 246 +3 */
    { { {  -20,  16,   96,  14 },  {  -28,  42,   86,  14 },  {  -28,  46,   68,  16 },  {  -20,  36,   32,  36 },  {  -54,  44,   60,  39 } } },  /* 68: V JUMP K L A, F JUMP K L A, atca 246 +2 */
    { { {    6,  22,   74,  14 },  {    1,  34,   60,  14 },  {   -2,  38,   36,  22 },  {  -26,  54,    0,  34 },  {    0,   0,    0,   0 } } },  /* 69: not used by a script */
    { { {   -4,  18,   74,  14 },  {  -18,  46,   62,  14 },  {    2,  22,   36,  26 },  {  -21,  49,    0,  34 },  {    0,   0,    0,   0 } } },  /* 70: not used by a script */
    { { {   -4,  18,   47,  14 },  {    0,   0,    0,   0 },  {  -20,  48,   35,  14 },  {  -20,  50,    0,  30 },  {    0,   0,    0,   0 } } },  /* 71: not used by a script */
    { { {  -11,  16,   61,  14 },  {  -15,  39,   49,  14 },  {  -12,  34,   36,  22 },  {  -30,  54,    0,  34 },  {    0,   0,    0,   0 } } },  /* 72: DASH HUMIKOMI */
    { { {  -31,  16,   76,  14 },  {  -32,  39,   65,  14 },  {  -18,  34,   42,  22 },  {  -36,  64,   10,  34 },  {    0,   0,    0,   0 } } },  /* 73: DASH HUMIKOMI */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -23,  35,    0,  47 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 74: not used by a script */
    { { {    1,  16,   77,  14 },  {  -11,  46,   62,  14 },  {   -1,  34,   36,  22 },  {  -17,  54,    0,  34 },  {    0,   0,    0,   0 } } },  /* 75: not used by a script */
    { { {   13,  16,   83,  14 },  {    5,  35,   65,  16 },  {   11,  28,   36,  29 },  {   -4,  42,    0,  34 },  {    0,   0,    0,   0 } } },  /* 76: not used by a script */
    { { {   13,  16,   98,  14 },  {    5,  35,   82,  16 },  {    2,  28,   44,  36 },  {  -17,  40,   69,  25 },  {    0,   0,    0,   0 } } },  /* 77: not used by a script */
    { { {   13,  16,   98,  14 },  {    5,  35,   82,  16 },  {    2,  28,   44,  36 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 78: not used by a script */
    { { {   -8,  29,   79,  15 },  {  -24,  45,   66,  12 },  {  -32,  63,   34,  31 },  {  -25,  65,    0,  34 },  {    0,   0,    0,   0 } } },  /* 79: M KICK C, atca 214 */
    { { {  -12,  28,   79,  22 },  {  -28,  53,   71,  12 },  {  -32,  63,   34,  36 },  {  -21,  57,    0,  34 },  {    0,   0,    0,   0 } } },  /* 80: M KICK C, atca 214 */
    { { {  -19,  32,   82,  18 },  {  -29,  72,   74,  13 },  {  -28,  60,   27,  49 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 81: M KICK C, atca 214 */
    { { {  -16,  29,   87,  19 },  {  -38,  93,   77,  15 },  {  -48,  74,   24,  52 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 82: M KICK C, atca 214 */
    { { {   -4,  16,   85,  14 },  {  -20,  31,   66,  19 },  {  -11,  36,   28,  37 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 83: not used by a script */
    { { {   -4,  16,   85,  14 },  {  -20,  31,   66,  19 },  {  -11,  36,   28,  37 },  {  -42,  35,   55,  17 },  {    0,   0,    0,   0 } } },  /* 84: not used by a script */
    { { {  -20,  16,   64,  14 },  {  -28,  46,   56,  12 },  {  -12,  34,   36,  22 },  {  -30,  54,    0,  34 },  {    0,   0,    0,   0 } } },  /* 85: ATTACK 4 S (Att_SENPUUKYAKU), ATTACK 4 M (Att_SENPUUKYAKU), ATTACK 4 L (Att_SENPUUKYAKU) +1 */
    { { {  -24,  16,   58,  14 },  {  -28,  46,   50,  12 },  {  -12,  34,   32,  22 },  {  -18,  50,    0,  32 },  {    0,   0,    0,   0 } } },  /* 86: ATTACK 4 S (Att_SENPUUKYAKU), ATTACK 4 M (Att_SENPUUKYAKU), ATTACK 4 L (Att_SENPUUKYAKU) +1 */
    { { {  -28,  16,   66,  14 },  {  -28,  46,   56,  14 },  {  -32,  57,   36,  22 },  {  -77, 135,    7,  29 },  {  -40,  29,   36,  48 } } },  /* 87: ATTACK 4 S (Att_SENPUUKYAKU), ATTACK 4 M (Att_SENPUUKYAKU), ATTACK 4 L (Att_SENPUUKYAKU) +1 */
    { { {  -28,  16,   66,  14 },  {  -28,  46,   56,  14 },  {  -16,  34,   36,  22 },  {  -77, 135,    7,  29 },  {    0,   0,    0,   0 } } },  /* 88: saca 69 */
    { { {  -28,  16,   68,  14 },  {  -28,  46,   58,  14 },  {  -16,  34,   36,  22 },  {  -71, 124,    5,  30 },  {  -62,  32,   64,   8 } } },  /* 89: ATTACK 4 S (Att_SENPUUKYAKU), ATTACK 4 M (Att_SENPUUKYAKU), ATTACK 4 L (Att_SENPUUKYAKU) +1 */
    { { {  -24,  16,   68,  14 },  {  -22,  32,   58,  12 },  {  -10,  30,   36,  22 },  {  -30,  54,    0,  36 },  {    0,   0,    0,   0 } } },  /* 90: ATTACK 2 S (Att_HADOUKEN), saca 65 */
    { { {  -11,  23,   81,  18 },  {  -20,  46,   71,  15 },  {  -37,  58,   32,  39 },  {    0,   0,    0,   0 },  {  -83,  62,   51,  28 } } },  /* 91: atca 156, atca 260, ATTACK 5 S +1 */
    { { {    6,  16,   86,  14 },  {  -10,  42,   72,  14 },  {  -22,  42,   46,  20 },  {   -8,  28,   16,  36 },  {    0,   0,    0,   0 } } },  /* 92: atca 156, atca 260, ATTACK 5 S +1 */
    { { {   -4,  16,   92,  14 },  {  -12,  40,   80,  14 },  {  -14,  30,   56,  22 },  {  -14,  22,   18,  40 },  {    0,   0,    0,   0 } } },  /* 93: atca 156, atca 260, ATTACK 5 S +2 */
    { { {   -4,  16,   92,  14 },  {  -12,  40,   80,  14 },  {  -14,  30,   56,  22 },  {  -14,  22,   18,  40 },  {  -46,  24,   68,  32 } } },  /* 94: ATTACK 5 S, saca 75 */
    { { {  -10,  16,   84,  14 },  {  -20,  40,   74,  12 },  {  -10,  30,   50,  22 },  {  -22,  32,   18,  34 },  {    0,   0,    0,   0 } } },  /* 95: ATTACK 5 S, saca 52, saca 75 */
    { { {  -28,  16,   46,  14 },  {  -12,  36,   48,  12 },  {    0,   0,    0,   0 },  {  -18,  54,    0,  32 },  {    0,   0,    0,   0 } } },  /* 96: ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI), saca 67 +1 */
    { { {  -30,  53,   48,  12 },  {    0,   0,    0,   0 },  {  -50,  72,    0,  47 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 97: OKIAGARI P S, ATTACK 3 S (Att_TENSHINSENKYUUTAI), saca 66 +4 */
    { { {  -26,  50,   36,  10 },  {    0,   0,    0,   0 },  {  -43,  73,   13,  35 },  {   14,  18,    0,  16 },  {    0,   0,    0,   0 } } },  /* 98: saca 75 */
    { { {  -26,  26,   48,  22 },  {  -30,  54,   40,  14 },  {  -43,  76,   22,  37 },  {   16,  20,    0,  24 },  {    0,   0,    0,   0 } } },  /* 99: OKIAGARI P S, ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI) +5 */
    { { {  -44,  37,   36,  73 },  {  -32,  58,   52,  14 },  {  -36,  70,   34,  16 },  {   10,  16,    0,  36 },  {    0,   0,    0,   0 } } },  /* 100: ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI) +5 */
    { { {  -20,  16,   96,  14 },  {  -26,  42,   88,  14 },  {  -12,  30,   74,  16 },  {  -26,  44,   52,  20 },  {    0,   0,    0,   0 } } },  /* 101: V JUMP P S A, F JUMP P S A, atca 236 +1 */
    { { {  -24,  16,   96,  14 },  {  -34,  46,   88,  14 },  {  -16,  48,   72,  14 },  {  -25,  54,   44,  34 },  {  -46,  26,   61,  41 } } },  /* 102: F JUMP P S A, atca 248, V JUMP P S A +1 */
    { { {  -20,  16,   96,  14 },  {  -26,  42,   86,  14 },  {  -10,  28,   72,  16 },  {  -30,  48,   54,  20 },  {    0,   0,    0,   0 } } },  /* 103: V JUMP P M A, F JUMP P M A, F JUMP P L A +5 */
    { { {  -26,  16,   92,  14 },  {  -20,  36,   84,  14 },  {   -8,  28,   72,  16 },  {  -28,  56,   56,  20 },  {    0,   0,    0,   0 } } },  /* 104: V JUMP P M A, F JUMP P M A, atca 238 +1 */
    { { {  -26,  36,   90,  14 },  {  -34,  48,   76,  12 },  {  -42,  14,   68,  12 },  {  -24,  62,   56,  20 },  {  -58,  36,   56,  41 } } },  /* 105: V JUMP P M A, F JUMP P M A, atca 238 +3 */
    { { {  -22,  16,   92,  14 },  {  -20,  36,   86,  14 },  {  -12,  30,   72,  16 },  {  -28,  56,   56,  20 },  {  -52,  30,   76,  10 } } },  /* 106: V JUMP P M A, F JUMP P M A, F JUMP P L A +5 */
    { { {  -10,  16,   86,  14 },  {   -4,  28,   64,  28 },  {  -20,  44,   38,  24 },  {   -4,  28,    0,  36 },  {    0,   0,    0,   0 } } },  /* 107: HANASARE, exca 86, exca 87 +2 */
    { { {  -33,  16,   96,  14 },  {  -20,  40,   90,  14 },  {   -4,  28,   72,  20 },  {  -20,  42,   54,  20 },  {  -36,  17,   70,  23 } } },  /* 108: not used by a script */
    { { {  -33,  16,   96,  14 },  {  -20,  40,   90,  14 },  {   -4,  28,   72,  20 },  {  -20,  42,   54,  20 },  {  -36,  15,   71,  22 } } },  /* 109: not used by a script */
    { { {  -18,  16,   74,  14 },  {  -26,  44,   68,  12 },  {   -6,  28,   38,  28 },  {  -26,  32,   16,  26 },  {    0,   0,    0,   0 } } },  /* 110: FUSHIN P S */
    { { {  -10,  16,   76,  14 },  {  -26,  44,   68,  12 },  {  -10,  30,   44,  22 },  {  -26,  34,   30,  26 },  {    0,   0,    0,   0 } } },  /* 111: FUSHIN P S */
    { { {    2,  16,   78,  14 },  {  -12,  42,   72,  12 },  {  -28,  44,   50,  20 },  {  -12,  28,   16,  32 },  {    0,   0,    0,   0 } } },  /* 112: FUSHIN P S */
    { { {   12,  16,   78,  14 },  {   -4,  36,   62,  22 },  {  -30,  46,   52,  20 },  {  -10,  28,   16,  34 },  {  -68,  36,   58,  16 } } },  /* 113: FUSHIN P S */
    { { {   -2,  16,   80,  14 },  {  -12,  38,   62,  22 },  {  -30,  48,   52,  20 },  {   -8,  28,    0,  50 },  {  -56,  28,   48,  18 } } },  /* 114: exca 63, exca 64, exca 73 +2 */
    { { {   -8,  16,   74,  14 },  {  -20,  46,   58,  18 },  {  -22,  44,   24,  32 },  {   -6,  28,    0,  22 },  {  -46,  22,   24,  20 } } },  /* 115: exca 63, exca 64, exca 73 +2 */
    { { {   -2,  16,   96,  14 },  {  -18,  44,   86,  14 },  {   -8,  30,   66,  22 },  {  -26,  38,   48,  26 },  {    0,   0,    0,   0 } } },  /* 116: V JUMP K S A, V JUMP K M A, F JUMP K S A +5 */
    { { {    8,  16,   94,  14 },  {   -8,  42,   86,  14 },  {  -24,  44,   68,  20 },  {   -8,  28,   36,  30 },  {    0,   0,    0,   0 } } },  /* 117: V JUMP K S A, V JUMP K M A, F JUMP K S A +5 */
    { { {    9,  25,   94,  20 },  {  -50,  89,   90,  16 },  {  -18,  61,   70,  20 },  {  -32,  61,   42,  27 },  {  -83,  65,   67,  30 } } },  /* 118: V JUMP K S A, V JUMP K M A, F JUMP K S A +6 */
    { { {  -12,  16,   98,  14 },  {  -10,  30,   86,  16 },  {   -4,  28,   68,  20 },  {  -24,  36,   48,  28 },  {    0,   0,    0,   0 } } },  /* 119: F JUMP K S B, F JUMP K M B, F JUMP K L B +3 */
    { { {  -10,  16,   98,  14 },  {   -4,  30,   90,  16 },  {  -20,  42,   62,  26 },  {  -16,  28,   38,  22 },  {    0,   0,    0,   0 } } },  /* 120: F JUMP K S B, F JUMP K M B, F JUMP K L B +3 */
    { { {  -10,  44,   98,  19 },  {  -15,  54,   92,   8 },  {  -20,  58,   62,  31 },  {    0,   0,    0,   0 },  {  -20,  49,   20,  50 } } },  /* 121: F JUMP K S B, F JUMP K M B, F JUMP K L B +3 */
    { { {  -10,  16,   78,  14 },  {   -6,  32,   60,  24 },  {  -30,  52,   32,  26 },  {  -16,  26,    0,  32 },  {    0,   0,    0,   0 } } },  /* 122: exca 65, exca 66 */
    { { {  -18,  16,   84,  14 },  {  -24,  46,   70,  16 },  {  -10,  32,   32,  36 },  {  -20,  24,    0,  44 },  {    0,   0,    0,   0 } } },  /* 123: exca 51, exca 52 */
    { { {   -6,  16,   92,  14 },  {  -12,  32,   78,  18 },  {  -36,  54,   56,  20 },  {   -6,  24,    0,  54 },  {    0,   0,    0,   0 } } },  /* 124: exca 53, exca 54 */
    { { {   -6,  16,   84,  14 },  {  -12,  30,   60,  28 },  {  -38,  54,   30,  28 },  {   -4,  24,    0,  28 },  {    0,   0,    0,   0 } } },  /* 125: exca 53, exca 54 */
    { { {  -19,  16,   74,  14 },  {  -29,  41,   65,  12 },  {  -12,  30,   36,  22 },  {  -30,  54,    0,  34 },  {    0,   0,    0,   0 } } },  /* 126: Att_HADOUKEN (command slot 22), saca 74 */
    { { {  -13,  16,   72,  14 },  {  -21,  41,   60,  12 },  {  -12,  30,   36,  22 },  {  -30,  54,    0,  34 },  {  -46,  32,   56,  15 } } },  /* 127: Att_HADOUKEN (command slot 22), saca 74 */
    { { {  -13,  33,   59,  14 },  {  -19,  46,   52,  15 },  {  -19,  46,   34,  16 },  {  -13,  33,   26,  14 },  {    0,   0,    0,   0 } } },  /* 128: AIR S, AIR M, AIR L +36 */
    { { {  -68,  30,   70,  16 },  {  -82,  73,   52,  18 },  {  -59,  54,   34,  22 },  {  -65,  91,    0,  32 },  {    0,   0,    0,   0 } } },  /* 129: not used by a script */
    { { {  -86,  36,   59,  20 },  {  -95,  73,   42,  18 },  {  -59,  54,   34,  22 },  {  -65,  91,    0,  32 },  {    0,   0,    0,   0 } } },  /* 130: not used by a script */
    { { {  -88,  21,   62,  18 },  { -102,  63,   54,  19 },  {  -90,  68,   36,  22 },  {  -69,  95,    0,  34 },  {    0,   0,    0,   0 } } },  /* 131: Att_HADOUKEN (command slot 22), saca 74 */
    { { {  -49,  81,    0,  47 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 132: ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI), saca 67 +1 */
    { { {  -64,  98,   73,  22 },  {  -63,  98,   70,   7 },  {  -67, 101,   34,  35 },  {  -48,  82,    0,  32 },  {  -85,  21,   43,  47 } } },  /* 133: L KICK A, atca 215 */
    { { {  -10,  39,   71,  21 },  {  -28,  69,   70,   7 },  {  -67, 110,   34,  35 },  {  -31,  74,    0,  32 },  {    0,   0,    0,   0 } } },  /* 134: L KICK A, atca 215 */
    { { {   -9,  26,   85,  22 },  {  -25,  48,   54,  35 },  {  -54,  74,   30,  43 },  {    0,   0,    0,   0 },  {  -84,  73,   44,  25 } } },  /* 135: not used by a script */
    { { {  -10,  22,   71,  21 },  {  -16,  39,   70,   7 },  {  -15,  38,   34,  35 },  {  -16,  41,    0,  32 },  {    0,   0,    0,   0 } } },  /* 136: ATTACK 2 S (Att_HADOUKEN), ATTACK 2 SP (Att_HADOUKEN) */
    { { {  -10,  22,   71,  21 },  {  -16,  39,   70,   7 },  {  -62,  93,   47,  57 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 137: saca 70, saca 76 */
    { { {  -24,  16,   68,  14 },  {  -22,  32,   58,  12 },  {  -10,  30,   36,  22 },  {  -30,  54,    0,  36 },  {  -56,  46,   42,  37 } } },  /* 138: ATTACK 2 S (Att_HADOUKEN), saca 65, atca 159 */
};

const ATTACK_BOX yang_att_box[93] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {    0,   0,    0,   0 },  {  -39,  32,   50,  16 },  {  -31,  40,   22,  27 } } },  /* 1: not used by a script */
    { { {    0,   0,    0,   0 },  {  -55,  31,   98,  19 },  {  -40,  28,   57,  40 } } },  /* 2: M KICK A, atca 212; attack 2, 106 */
    { { {    0,   0,    0,   0 },  {  -80,  22,   54,  22 },  {  -56,  22,   51,  20 } } },  /* 3: UP P GUARD P S, saca 52; attack 3, 39 */
    { { {    0,   0,    0,   0 },  {  -76,  26,   54,  19 },  {    0,   0,    0,   0 } } },  /* 4: UP P GUARD P S, UP P GUARD P M, saca 52 */
    { { {    0,   0,    0,   0 },  {  -84,  26,   62,  12 },  {  -56,  26,   58,  12 } } },  /* 5: UP P GUARD P M; attack 4 */
    { { {    0,   0,    0,   0 },  {  -76,  64,   66,  10 },  {  -38,  21,   51,  17 } } },  /* 6: S PUNCH A, atca 200; attack 6, 99 */
    { { {    0,   0,    0,   0 },  {  -63,  46,   53,  30 },  {    0,   0,    0,   0 } } },  /* 7: M PUNCH B, atca 204; attack 7, 101 */
    { { {    0,   0,    0,   0 },  {  -53,  35,   57,  23 },  {    0,   0,    0,   0 } } },  /* 8: M PUNCH A, atca 203; attack 8, 100 */
    { { {    0,   0,    0,   0 },  {  -42,  34,   30,  39 },  {    0,   0,    0,   0 } } },  /* 9: L PUNCH A, atca 206; attack 9, 102 */
    { { {    0,   0,    0,   0 },  {  -83,  68,   57,  13 },  {  -60,  32,   50,  12 } } },  /* 10: L PUNCH B, atca 208; attack 10, 104 */
    { { {    0,   0,    0,   0 },  {  -86,  32,   66,  12 },  {  -60,  32,   60,  12 } } },  /* 11: atca 158; attack 11 */
    { { {    0,   0,    0,   0 },  {  -84,  40,   18,  12 },  {  -60,  40,   30,  12 } } },  /* 12: not used by a script */
    { { {    0,   0,    0,   0 },  {  -76,  36,   20,  12 },  {    0,   0,    0,   0 } } },  /* 13: not used by a script */
    { { {    0,   0,    0,   0 },  {  -76,  54,   50,   8 },  {    0,   0,    0,   0 } } },  /* 14: atca 218, KAGAMI P A; attack 14, 109 */
    { { {    0,   0,    0,   0 },  {  -88,  65,   47,  14 },  {    0,   0,    0,   0 } } },  /* 15: KAGAMI P A, atca 224; attack 47, 112 */
    { { {    0,   0,    0,   0 },  {  -74,  36,   50,  10 },  {    0,   0,    0,   0 } } },  /* 16: KAGAMI P A, atca 224 */
    { { {    0,   0,    0,   0 },  {  -63,  44,    0,   8 },  {    0,   0,    0,   0 } } },  /* 17: KAGAMI K A, atca 227, atca 230; attack 15, 113 */
    { { {    0,   0,    0,   0 },  {  -84,  50,    0,   8 },  {    0,   0,    0,   0 } } },  /* 18: not used by a script */
    { { {    0,   0,    0,   0 },  {  -60,  36,   49,   9 },  {    0,   0,    0,   0 } } },  /* 19: atca 218, KAGAMI P A */
    { { {    0,   0,    0,   0 },  {  -70,  53,   46,  19 },  {    0,   0,    0,   0 } } },  /* 20: M KICK C, atca 214, exca 13; attack 18, 107 */
    { { {    0,   0,    0,   0 },  {  -68,  49,   40,  17 },  {    0,   0,    0,   0 } } },  /* 21: M KICK C, atca 214 */
    { { {    0,   0,    0,   0 },  {  -42,  14,   80,  29 },  {  -30,  15,   62,  30 } } },  /* 22: not used by a script */
    { { {    0,   0,    0,   0 },  {  -83,  38,   53,  14 },  {  -49,  35,   56,  14 } } },  /* 23: not used by a script */
    { { {    0,   0,    0,   0 },  {  -61,  44,   58,  11 },  {    0,   0,    0,   0 } } },  /* 24: ATTACK 4 S (Att_SENPUUKYAKU), ATTACK 4 M (Att_SENPUUKYAKU), ATTACK 4 L (Att_SENPUUKYAKU) +1; attack 20, 21, 87, 88 ... */
    { { {    0,   0,    0,   0 },  {  -76,  49,   68,  10 },  {  -24,  16,   41,  29 } } },  /* 25: saca 69; attack 97 */
    { { {    0,   0,    0,   0 },  {  -64,  53,   46,  32 },  {    0,   0,    0,   0 } } },  /* 26: ATTACK 2 S (Att_HADOUKEN), saca 65, atca 159; attack 22, 76, 80 */
    { { {    0,   0,    0,   0 },  {  -71,  25,   53,  17 },  {    0,   0,    0,   0 } } },  /* 27: ATTACK 2 S (Att_HADOUKEN), saca 65; attack 23, 80 */
    { { {    0,   0,    0,   0 },  { -105,  88,   53,  34 },  {  -63,  70,   25,  37 } } },  /* 28: not used by a script */
    { { {    0,   0,    0,   0 },  {  -96,  73,   52,  28 },  {  -57,  39,   42,  21 } } },  /* 29: atca 156, atca 260, ATTACK 5 S +1; attack 25, 73, 82, 83 ... */
    { { {    0,   0,    0,   0 },  {  -69,  34,   44,  80 },  {  -64,  80,    9,  73 } } },  /* 30: ATTACK 5 S, saca 75; attack 26, 27, 75 */
    { { {    0,   0,    0,   0 },  {  -52,  18,   84,  32 },  {  -36,  18,   68,  32 } } },  /* 31: ATTACK 5 S; attack 27 */
    { { {    0,   0,    0,   0 },  {  -57,  52,   16,  53 },  {    0,   0,    0,   0 } } },  /* 32: ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI) +3; attack 28, 57, 60, 81 */
    { { {    0,   0,    0,   0 },  {  -47,  43,    0,  78 },  {    0,   0,    0,   0 } } },  /* 33: OKIAGARI P S, ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI) +4; attack 81, 95 */
    { { {    0,   0,    0,   0 },  {  -58,  33,  112,  17 },  {  -42,  32,   60,  52 } } },  /* 34: ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI) +4; attack 29, 56, 58, 61 ... */
    { { {    0,   0,    0,   0 },  {  -35,  14,   69,  15 },  {    0,   0,    0,   0 } } },  /* 35: F JUMP P S A, atca 248; attack 65, 122 */
    { { {    0,   0,    0,   0 },  {  -37,  23,   70,  23 },  {    0,   0,    0,   0 } } },  /* 36: V JUMP P S A, atca 236; attack 31, 116 */
    { { {    0,   0,    0,   0 },  {  -50,  29,   60,  18 },  {    0,   0,    0,   0 } } },  /* 37: V JUMP P M A, F JUMP P M A, atca 238 +1; attack 32, 66, 117, 123 */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -48,  14,   62,  12 } } },  /* 38: not used by a script */
    { { {    0,   0,    0,   0 },  {  -74,  32,   70,   6 },  {    0,   0,    0,   0 } } },  /* 39: S PUNCH A, atca 200 */
    { { {    0,   0,    0,   0 },  {  -48,  29,   57,  17 },  {    0,   0,    0,   0 } } },  /* 40: M PUNCH A, atca 203 */
    { { {    0,   0,    0,   0 },  {  -54,  24,   66,  12 },  {    0,   0,    0,   0 } } },  /* 41: M PUNCH B, atca 204; attack 7 */
    { { {    0,   0,    0,   0 },  {  -62,  41,   91,  16 },  {  -47,  27,   60,  31 } } },  /* 42: L PUNCH A, atca 206; attack 41, 103 */
    { { {    0,   0,    0,   0 },  {  -57,  21,   85,  16 },  {  -47,  39,   66,  19 } } },  /* 43: L PUNCH A, atca 206; attack 9 */
    { { {    0,   0,    0,   0 },  {  -75,  59,   56,  13 },  {    0,   0,    0,   0 } } },  /* 44: L PUNCH B, atca 208 */
    { { {    0,   0,    0,   0 },  {  -78,  32,   64,  12 },  {    0,   0,    0,   0 } } },  /* 45: atca 158 */
    { { {    0,   0,    0,   0 },  {  -52,  33,    0,  42 },  {    0,   0,    0,   0 } } },  /* 46: S KICK A, atca 209; attack 12, 105 */
    { { {    0,   0,    0,   0 },  {  -52,  33,    8,  28 },  {    0,   0,    0,   0 } } },  /* 47: S KICK A, atca 209; attack 12 */
    { { {    0,   0,    0,   0 },  {  -54,  18,   89,  19 },  {  -37,  17,   65,  26 } } },  /* 48: M KICK A, atca 212; attack 2 */
    { { {    0,   0,    0,   0 },  {  -64,  20,   48,  16 },  {  -52,  20,   58,  16 } } },  /* 49: F JUMP P L A, atca 252; attack 67, 124 */
    { { {    0,   0,    0,   0 },  {  -60,  18,   52,  14 },  {  -50,  18,   60,  14 } } },  /* 50: F JUMP P L A, atca 252 */
    { { {    0,   0,    0,   0 },  {  -54,  40,   56,  29 },  {  -45,  34,    0,  57 } } },  /* 51: super art Att_SLIDE_and_JUMP (command slot 17); attack 37 */
    { { {    0,   0,    0,   0 },  {  -64,  59,   58,  25 },  {  -54,  31,    0,  77 } } },  /* 52: super art Att_SLIDE_and_JUMP (command slot 17); attack 38 */
    { { {  -27,   6,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 53: M PUNCH A, M PUNCH B, L PUNCH A +5; attack 63, 64 */
    { { {    0,   0,    0,   0 },  {  -78,  57,   48,  11 },  {    0,   0,    0,   0 } } },  /* 54: KAGAMI P A, atca 221; attack 45, 110 */
    { { {    0,   0,    0,   0 },  {  -65,  44,   49,  10 },  {    0,   0,    0,   0 } } },  /* 55: KAGAMI P A, atca 221 */
    { { {    0,   0,    0,   0 },  {  -51,  27,   38,  19 },  {    0,   0,    0,   0 } } },  /* 56: KAGAMI P A, atca 224; attack 46, 111 */
    { { {    0,   0,    0,   0 },  {  -80,  62,    0,  11 },  {    0,   0,    0,   0 } } },  /* 57: KAGAMI K A, atca 230; attack 48, 114 */
    { { {    0,   0,    0,   0 },  {  -88,  65,    0,  19 },  {    0,   0,    0,   0 } } },  /* 58: KAGAMI K A, atca 233; attack 50, 115 */
    { { {    0,   0,    0,   0 },  {  -76,  53,    6,  10 },  {    0,   0,    0,   0 } } },  /* 59: not used by a script */
    { { {    0,   0,    0,   0 },  {  -86,  22,   53,  28 },  {  -62,  30,   51,  21 } } },  /* 60: UP P GUARD P L, saca 52; attack 5, 40 */
    { { {    0,   0,    0,   0 },  {  -76,  25,   53,  28 },  {    0,   0,    0,   0 } } },  /* 61: UP P GUARD P L, saca 52 */
    { { {    0,   0,    0,   0 },  {  -84,  40,   64,  12 },  {  -60,  40,   58,  12 } } },  /* 62: FUSHIN P S; attack 16 */
    { { {    0,   0,    0,   0 },  {  -72,  32,   62,  12 },  {    0,   0,    0,   0 } } },  /* 63: FUSHIN P S; attack 16 */
    { { {    0,   0,    0,   0 },  {  -44,  20,   90,  30 },  {    0,   0,    0,   0 } } },  /* 64: OKIAGARI P S, ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI) +4; attack 30, 59, 62, 81 */
    { { {    0,   0,    0,   0 },  {  -26,  35,    0,  48 },  {    0,   0,    0,   0 } } },  /* 65: ATTACK 6 S (Att_TENSHINSENKYUUTAI), saca 75, saca 67 +1; attack 96 */
    { { {    0,   0,    0,   0 },  {  -32,  22,   42,  18 },  {  -24,  20,   32,  16 } } },  /* 66: not used by a script */
    { { {    0,   0,    0,   0 },  {  -86,  65,   86,   8 },  {  -52,  34,   78,   8 } } },  /* 67: not used by a script */
    { { {    0,   0,    0,   0 },  {  -82,  40,   86,   8 },  {    0,   0,    0,   0 } } },  /* 68: not used by a script */
    { { {    0,   0,    0,   0 },  {  -71,  51,   86,   8 },  {    0,   0,    0,   0 } } },  /* 69: V JUMP P L A, atca 240 */
    { { {    0,   0,    0,   0 },  {  -81,  67,   87,  12 },  {    0,   0,    0,   0 } } },  /* 70: not used by a script */
    { { {    0,   0,    0,   0 },  {  -82,  40,   86,   8 },  {    0,   0,    0,   0 } } },  /* 71: not used by a script */
    { { {    0,   0,    0,   0 },  {  -89,  77,   79,  13 },  {    0,   0,    0,   0 } } },  /* 72: V JUMP P L A, atca 240; attack 33, 118 */
    { { {    0,   0,    0,   0 },  {  -86,  44,   84,  10 },  {    0,   0,    0,   0 } } },  /* 73: V JUMP P L A, atca 240 */
    { { {    0,   0,    0,   0 },  {  -67,  20,   92,  18 },  {  -56,  38,   73,  23 } } },  /* 74: V JUMP K L A, F JUMP K L A, atca 246 +2; attack 36, 72, 121, 127 */
    { { {    0,   0,    0,   0 },  {  -56,  32,   77,  19 },  {    0,   0,    0,   0 } } },  /* 75: V JUMP K L A, F JUMP K L A, atca 246 +2; attack 72 */
    { { {    0,   0,    0,   0 },  {  -53,  39,   83,  19 },  {  -34,  14,   53,  35 } } },  /* 76: not used by a script */
    { { {    0,   0,    0,   0 },  {  -67,  20,   92,  18 },  {  -56,  38,   62,  33 } } },  /* 77: not used by a script */
    { { {    0,   0,    0,   0 },  {  -71,  51,   82,  12 },  {    0,   0,    0,   0 } } },  /* 78: V JUMP K S A, F JUMP K S A, atca 242 +1; attack 34, 68, 119, 125 */
    { { {    0,   0,    0,   0 },  {  -64,  46,   84,   9 },  {    0,   0,    0,   0 } } },  /* 79: V JUMP K S A, F JUMP K S A, atca 242 +1 */
    { { {    0,   0,    0,   0 },  {  -80,  59,   71,  15 },  {    0,   0,    0,   0 } } },  /* 80: V JUMP K M A, F JUMP K M A, atca 244 +1; attack 35, 69, 120, 126 */
    { { {    0,   0,    0,   0 },  {  -74,  53,   76,  11 },  {    0,   0,    0,   0 } } },  /* 81: V JUMP K M A, F JUMP K M A, atca 244 +1 */
    { { {    0,   0,    0,   0 },  {  -16,  20,   22,   7 },  {    0,   0,    0,   0 } } },  /* 82: F JUMP K S B, F JUMP K M B, F JUMP K L B +3; attack 71, 128 */
    { { {    0,   0,    0,   0 },  {  -16,  20,   22,   7 },  {    0,   0,    0,   0 } } },  /* 83: F JUMP K S B, F JUMP K M B, F JUMP K L B +3 */
    { { {  -52,  32,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 84: Att_HADOUKEN (command slot 22), saca 74; attack 43 */
    { { {    0,   0,    0,   0 },  {  -99,  77,   45,  29 },  {  -46,  27,   32,  23 } } },  /* 85: L KICK A, atca 215; attack 42, 108 */
    { { {    0,   0,    0,   0 },  {  -80,  56,   59,  10 },  {    0,   0,    0,   0 } } },  /* 86: L KICK A, atca 215 */
    { { {    0,   0,    0,   0 },  {  -43,  51,    0,  57 },  {    0,   0,    0,   0 } } },  /* 87: saca 75; attack 54 */
    { { {    0,   0,    0,   0 },  {  -57,  68,    0,  82 },  {    0,   0,    0,   0 } } },  /* 88: saca 75; attack 55 */
    { { {    0,   0,    0,   0 },  {  -79,  53,   41,  33 },  {    0,   0,    0,   0 } } },  /* 89: not used by a script */
    { { {  -31,  10,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 90: L KICK A; attack 63 */
    { { {    0,   0,    0,   0 },  {  -39,  20,   26,  49 },  {    0,   0,    0,   0 } } },  /* 91: saca 70, saca 76; attack 67, 131 */
    { { {    0,   0,    0,   0 },  {  -85,  88,   86,  38 },  {  -71,  74,   14,  71 } } },  /* 92: saca 75; attack 56 */
};

const CAUGHT_BOX yang_cau_box[19] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -21,   42,    0,   16 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +138 */
    { {  -25,   46,    0,    8 } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +44 */
    { {  -20,   40,   51,   44 } },  /* 3: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +52 */
    { {  -21,   42,   41,   37 } },  /* 4: M KICK C, atca 214, atca 156 +4 */
    { {  -21,   42,   34,   36 } },  /* 5: ATTACK 3 S (Att_TENSHINSENKYUUTAI), ATTACK 3 M (Att_TENSHINSENKYUUTAI), ATTACK 3 L (Att_TENSHINSENKYUUTAI) +5 */
    { {  -46,   48,    0,   74 } },  /* 6: not used by a script */
    { {  -42,   48,    0,   74 } },  /* 7: not used by a script */
    { {  -14,   46,   94,   28 } },  /* 8: not used by a script */
    { {    0,    0,    0,    0 } },  /* 9: no box */
    { {    0,    0,    0,    0 } },  /* 10: no box */
    { {   -4,   48,    0,   74 } },  /* 11: not used by a script */
    { {   -4,   48,   31,   74 } },  /* 12: not used by a script */
    { {  -32,   48,   16,   74 } },  /* 13: not used by a script */
    { {  -19,   48,   16,   74 } },  /* 14: not used by a script */
    { {   -6,   48,   16,   74 } },  /* 15: not used by a script */
    { {  -17,   48,   15,   74 } },  /* 16: not used by a script */
    { {  -17,   42,   35,   32 } },  /* 17: AIR S, AIR M, AIR L +36 */
    { {  -29,   50,    0,    8 } },  /* 18: KAGAMI P A, KAGAMI K A */
};

const HOSEI_BOX yang_hos_box[22] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -21,   42,    0,   70 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +141 */
    { {  -21,   42,    0,   55 } },  /* 2: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +61 */
    { {  -20,   40,   51,   44 } },  /* 3: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +51 */
    { {  -21,   42,   41,   37 } },  /* 4: M KICK C, atca 214, atca 156 +4 */
    { {  -32,   46,   36,   36 } },  /* 5: not used by a script */
    { {  -44,   46,   36,   36 } },  /* 6: not used by a script */
    { {  -41,   46,   36,   36 } },  /* 7: not used by a script */
    { {  -21,   60,    0,   55 } },  /* 8: KAGAMI K A, atca 233 */
    { {    0,    0,    0,    0 } },  /* 9: no box */
    { {    0,    0,    0,    0 } },  /* 10: no box */
    { {  -10,   46,   36,   36 } },  /* 11: not used by a script */
    { {    6,   36,   43,   36 } },  /* 12: not used by a script */
    { {    0,   36,   62,   36 } },  /* 13: not used by a script */
    { {    0,    0,    0,    0 } },  /* 14: no box */
    { {  -27,   32,   47,   36 } },  /* 15: not used by a script */
    { {   -4,   32,   52,   36 } },  /* 16: not used by a script */
    { {   10,   32,   52,   36 } },  /* 17: not used by a script */
    { {  -15,   38,   36,   45 } },  /* 18: not used by a script */
    { {  -17,   42,   35,   32 } },  /* 19: AIR S, AIR M, AIR L +36 */
    { {  -20,   40,   60,   24 } },  /* 20: not used by a script */
    { {  -21,   42,    0,   30 } },  /* 21: NEKOROBI S */
};
