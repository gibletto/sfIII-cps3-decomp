/*
 * IBUKI_HITBOX.C  Ibuki's hit boxes
 *
 * Each of Ibuki's animation frames names a row of ibuki_hit_ix_table (a frame line's hit field).
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
 * rows of ibuki_catt_table dealt through it. Row 0 of a box table is no box.
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

const HIT_IX ibuki_hit_ix_table[248] = {
    /* boix  atix  cuix  hoix */
    {    0,    0,    0,    0 },  /* 0: NAGERARE KAIHI, OKIAGARI, OKIAGARI F +17 */
    {    1,    0,    1,    1 },  /* 1: KAMAE, HURIMUKI, FRONT WALK +103 */
    {    2,    0,    2,    2 },  /* 2: DASH TOBINOKI, KAGAMU, KAGAMI KAMAE +30 */
    {    3,    0,    1,    1 },  /* 3: S PUNCH A, ATTACK 3 S (Att_CHOUCHUURENGEKI), ATTACK 3 M (Att_CHOUCHUURENGEKI) +1 */
    {    9,    1,    1,    1 },  /* 4: S PUNCH A */
    {    4,    0,    1,    1 },  /* 5: S PUNCH B */
    {    5,    2,    1,    1 },  /* 6: S PUNCH B */
    {    5,    0,    1,    1 },  /* 7: S PUNCH B */
    {    6,    0,    3,    3 },  /* 8: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +10 */
    {    7,    0,    3,    3 },  /* 9: JUMP FRONT, JUMP BACK, SP JUMP FRONT +13 */
    {    8,    0,    3,    3 },  /* 10: JUMP FRONT, JUMP VERTICAL, JUMP BACK +23 */
    {    9,    0,    1,    1 },  /* 11: S PUNCH A */
    {   10,    0,    1,    1 },  /* 12: GUARD HEAD, GUARD UP */
    {   11,    0,    2,    2 },  /* 13: GUARD DOWN */
    {    0,    0,    0,    1 },  /* 14: not used by a script */
    {   13,    0,    4,    4 },  /* 15: DASH HUMIKOMI */
    {   14,    0,    4,    4 },  /* 16: DASH HUMIKOMI */
    {   15,    0,    4,    4 },  /* 17: DASH HUMIKOMI, CATCH 5 */
    {   16,    0,    4,    4 },  /* 18: DASH TOBINOKI */
    {   17,    0,    9,   11 },  /* 19: DASH TOBINOKI, ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2) +1 */
    {   18,    0,    1,    1 },  /* 20: M KICK C, atca 156 */
    {   19,    0,    4,    4 },  /* 21: M KICK C, atca 156 */
    {   20,    0,    3,    3 },  /* 22: M KICK C, atca 156 */
    {   21,    3,    3,    3 },  /* 23: M KICK C, atca 156 */
    {   22,    4,    3,    3 },  /* 24: M KICK C, atca 156 */
    {   22,    0,    4,    4 },  /* 25: M KICK C, atca 156 */
    {   23,    5,    2,    2 },  /* 26: KAGAMI K A, atca 157, UP P GUARD K S */
    {   24,    0,    3,    3 },  /* 27: V JUMP K L A, F JUMP K L A, saca 92 */
    {   25,    0,    3,    3 },  /* 28: V JUMP K L A, F JUMP K L A, saca 92 */
    {   70,    6,    3,    3 },  /* 29: V JUMP K L A, F JUMP K L A */
    {   71,    7,    3,    3 },  /* 30: V JUMP K L A, F JUMP K L A */
    {   72,    8,    3,    3 },  /* 31: not used by a script */
    {   26,    0,    3,    3 },  /* 32: L KICK C */
    {   27,    0,    3,    3 },  /* 33: L KICK C */
    {   28,    9,    3,    3 },  /* 34: L KICK C */
    {  101,    0,    3,    3 },  /* 35: L KICK C */
    {   29,    0,    3,    3 },  /* 36: F JUMP K S A */
    {   73,   10,    3,    3 },  /* 37: F JUMP K S A */
    {   73,   11,    3,    3 },  /* 38: F JUMP K S A */
    {   30,    0,    3,    3 },  /* 39: F JUMP K M A, atca 158, FUSHIN P S */
    {   31,   12,    3,    3 },  /* 40: F JUMP K M A, atca 158, FUSHIN P S */
    {   31,   13,    3,    3 },  /* 41: F JUMP K M A, atca 158, FUSHIN P S */
    {  111,    0,    2,    2 },  /* 42: KAGAMI K A, atca 157, UP P GUARD K S +1 */
    {   32,    0,    1,    1 },  /* 43: M PUNCH A */
    {   32,   14,    1,    1 },  /* 44: M PUNCH A */
    {  124,   15,    1,    1 },  /* 45: M PUNCH A */
    {   33,   16,    1,    1 },  /* 46: M PUNCH A */
    {   33,    0,    1,    1 },  /* 47: M PUNCH A */
    {   34,    0,    1,    1 },  /* 48: M PUNCH B */
    {   35,   17,    1,    1 },  /* 49: M PUNCH B */
    {  105,   18,    1,    1 },  /* 50: M PUNCH B */
    {  105,    0,    1,    1 },  /* 51: M PUNCH B */
    {    1,   19,    1,    1 },  /* 52: L PUNCH A */
    {   36,   20,    1,    1 },  /* 53: L PUNCH A */
    {   36,   21,    1,    1 },  /* 54: L PUNCH A */
    {  106,    0,    1,    1 },  /* 55: L PUNCH A */
    {   37,    0,    1,    1 },  /* 56: S KICK A, saca 84, saca 85 +1 */
    {   38,   22,    1,    1 },  /* 57: not used by a script */
    {   38,   23,    1,    1 },  /* 58: S KICK A, saca 84, saca 85 +1 */
    {   38,    0,    1,    1 },  /* 59: S KICK A */
    {   39,   24,    1,    1 },  /* 60: S KICK B */
    {   39,   25,    1,    1 },  /* 61: S KICK B */
    {  102,    0,    1,    1 },  /* 62: S KICK B */
    {   40,    0,    1,    1 },  /* 63: M KICK A, atca 160, saca 88 */
    {   50,   26,    1,    1 },  /* 64: M KICK A, atca 160 */
    {   41,    0,    1,    1 },  /* 65: M KICK B, ATTACK 5 S (Att_CHOUCHUURENGEKI), ATTACK 5 M (Att_CHOUCHUURENGEKI) +1 */
    {   42,    0,    1,    1 },  /* 66: M KICK B, ATTACK 5 S (Att_CHOUCHUURENGEKI), ATTACK 5 M (Att_CHOUCHUURENGEKI) +1 */
    {  100,   27,    1,    1 },  /* 67: M KICK B */
    {   43,    0,    1,    1 },  /* 68: M KICK B, ATTACK 5 S (Att_CHOUCHUURENGEKI), ATTACK 5 M (Att_CHOUCHUURENGEKI) +7 */
    {   45,   28,    1,    1 },  /* 69: L KICK A */
    {   45,   29,    1,    1 },  /* 70: L KICK A */
    {   45,    0,    1,    1 },  /* 71: L KICK A, ATTACK 6 S, saca 89 +2 */
    {   44,    0,    1,    1 },  /* 72: L KICK A, ATTACK 6 S, saca 89 +2 */
    {   47,    0,    1,    1 },  /* 73: L PUNCH B, saca 84, saca 85 +1 */
    {   48,    0,    1,    1 },  /* 74: TOUKETSU A, L PUNCH B, saca 84 +2 */
    {   49,   30,    1,    1 },  /* 75: L PUNCH B */
    {   49,   31,    1,    1 },  /* 76: L PUNCH B */
    {  107,    0,    1,    1 },  /* 77: L PUNCH B, saca 84, saca 85 +1 */
    {   50,   32,    1,    1 },  /* 78: M KICK A, atca 160, saca 88 */
    {  103,    0,    1,    1 },  /* 79: M KICK A, atca 160, saca 88 */
    {   51,   33,   11,    2 },  /* 80: KAGAMI P A */
    {   51,   34,    2,    2 },  /* 81: KAGAMI P A */
    {   51,    0,    2,    2 },  /* 82: KAGAMI P A */
    {   52,    0,    2,    2 },  /* 83: KAGAMI P A */
    {   53,   35,    2,    2 },  /* 84: KAGAMI P A */
    {   53,   36,    2,    2 },  /* 85: KAGAMI P A */
    {  104,    0,    2,    2 },  /* 86: KAGAMI P A */
    {   54,   37,   11,    2 },  /* 87: KAGAMI K A */
    {   54,   38,   11,    2 },  /* 88: KAGAMI K A */
    {   54,    0,   11,    2 },  /* 89: KAGAMI K A */
    {   55,    0,    3,    3 },  /* 90: V JUMP P S A, V JUMP P M A */
    {  117,   39,    3,    3 },  /* 91: V JUMP P S A */
    {  117,    0,    3,    3 },  /* 92: V JUMP P S A, V JUMP P M A */
    {   56,   40,    3,    3 },  /* 93: V JUMP P S A */
    {   57,    0,    3,    3 },  /* 94: V JUMP P L A */
    {   58,    0,    3,    3 },  /* 95: V JUMP P L A, atca 159 */
    {   59,   41,    3,    3 },  /* 96: V JUMP P L A, atca 159 */
    {   59,   76,    3,    3 },  /* 97: V JUMP P L A, atca 159 */
    {   60,    0,    3,    3 },  /* 98: V JUMP K S A, V JUMP K M A */
    {   61,   42,    3,    3 },  /* 99: V JUMP K S A */
    {   61,   43,    3,    3 },  /* 100: V JUMP K S A, V JUMP K M A */
    {   61,    0,    3,    3 },  /* 101: V JUMP K M A */
    {   62,    0,    3,    3 },  /* 102: V JUMP K M A */
    {   63,    0,    3,    3 },  /* 103: F JUMP P S A, F JUMP P M A, saca 76 */
    {   64,   44,    3,    3 },  /* 104: F JUMP P S A */
    {   64,   45,    3,    3 },  /* 105: F JUMP P S A, F JUMP P M A */
    {   65,    0,    2,    2 },  /* 106: not used by a script */
    {   66,    0,    2,    2 },  /* 107: not used by a script */
    {   67,   46,    2,    2 },  /* 108: not used by a script */
    {   67,    0,    2,    2 },  /* 109: not used by a script */
    {  116,   47,    1,    1 },  /* 110: UP P GUARD P S */
    {    0,    0,    0,    2 },  /* 111: TATAKI S, KGM TATAKI S, OKIAGARI +14 */
    {   68,    0,    1,    1 },  /* 112: not used by a script */
    {   69,   48,    1,    1 },  /* 113: L KICK A */
    {   69,    0,    1,    1 },  /* 114: L KICK A, saca 84, saca 85 +1 */
    {    1,   49,    1,    1 },  /* 115: not used by a script */
    {   74,   50,    3,    3 },  /* 116: not used by a script */
    {  134,    0,    1,    1 },  /* 117: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 6 S */
    {  134,   48,    1,    1 },  /* 118: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 6 S */
    {  134,   51,    3,    1 },  /* 119: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 6 S */
    {  135,   52,    3,    1 },  /* 120: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 6 S */
    {  135,   53,    3,    1 },  /* 121: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 6 S */
    {    1,   55,    1,    1 },  /* 122: M PUNCH A, M PUNCH B, L PUNCH A +2 */
    {   76,    0,    2,    2 },  /* 123: not used by a script */
    {   77,    0,    2,    2 },  /* 124: L KICK B, atca 161, OKIAGARI P S +3 */
    {   78,   56,    2,    2 },  /* 125: L KICK B, atca 161, OKIAGARI P S */
    {  122,   57,    2,    2 },  /* 126: L KICK B, atca 161, OKIAGARI P S */
    {   79,   58,    3,    3 },  /* 127: not used by a script */
    {   80,    0,    1,    5 },  /* 128: L PUNCH B */
    {   81,   59,    1,    5 },  /* 129: L PUNCH B */
    {   82,    0,    5,    6 },  /* 130: ATTACK 3 S (Att_CHOUCHUURENGEKI), ATTACK 3 M (Att_CHOUCHUURENGEKI), ATTACK 3 L (Att_CHOUCHUURENGEKI) +1 */
    {   82,   49,    5,    6 },  /* 131: ATTACK 3 S (Att_CHOUCHUURENGEKI) */
    {   83,   60,    3,    3 },  /* 132: not used by a script */
    {   84,   61,    3,    3 },  /* 133: not used by a script */
    {   85,   62,    3,    3 },  /* 134: not used by a script */
    {   86,   63,    1,    1 },  /* 135: not used by a script */
    {   86,   64,    1,    1 },  /* 136: not used by a script */
    {   87,    0,    6,    7 },  /* 137: AIR S, AIR M, AIR L +47 */
    {   88,    0,    7,    8 },  /* 138: not used by a script */
    {   93,    0,    3,    9 },  /* 139: ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2), ATTACK 2 L (Att_PL07_AT2) */
    {   89,   65,    3,    9 },  /* 140: ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2), ATTACK 2 L (Att_PL07_AT2) */
    {   90,    0,    3,    3 },  /* 141: ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2), ATTACK 2 L (Att_PL07_AT2) */
    {   90,   66,    3,    3 },  /* 142: ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2), ATTACK 2 L (Att_PL07_AT2) */
    {   92,   67,    5,    6 },  /* 143: super art Att_PL07_SA2 (command slot 17) */
    {   91,    0,    5,    6 },  /* 144: super art Att_PL07_SA2 (command slot 17) */
    {   92,    0,    5,    6 },  /* 145: super art Att_PL07_SA2 (command slot 17) */
    {   92,   68,    5,    6 },  /* 146: super art Att_PL07_SA2 (command slot 17) */
    {   92,   69,    5,    6 },  /* 147: super art Att_PL07_SA2 (command slot 17) */
    {   92,   70,    5,    6 },  /* 148: super art Att_PL07_SA2 (command slot 17) */
    {   92,   71,    5,    6 },  /* 149: not used by a script */
    {   92,   72,    5,    6 },  /* 150: not used by a script */
    {   94,    0,    2,    2 },  /* 151: KAGAMI K A, ATTACK 4 S (Att_PL07_AT1), ATTACK 4 M (Att_PL07_AT1) +1 */
    {   94,   73,    2,    2 },  /* 152: not used by a script */
    {   95,   74,    2,    2 },  /* 153: ATTACK 4 S (Att_PL07_AT1), ATTACK 4 M (Att_PL07_AT1), ATTACK 4 L (Att_PL07_AT1) */
    {    0,    0,    0,    3 },  /* 154: AIR S, AIR M, AIR L +2 */
    {  110,   75,    2,    2 },  /* 155: KAGAMI K A */
    {    0,    0,    0,    2 },  /* 156: not used by a script */
    {   97,    0,    8,   10 },  /* 157: air Att_PL07_AT3 (command slot 37), saca 65, saca 66 +7 */
    {   98,    0,    8,   10 },  /* 158: air Att_PL07_AT3 (command slot 37), saca 65, saca 66 +7 */
    {   99,    0,    8,   10 },  /* 159: air Att_PL07_AT3 (command slot 37), air super art Att_PL07_SA3 (command slot 33) */
    {  135,   54,    3,    1 },  /* 160: ATTACK 1 S (Att_SHOURYUUKEN) */
    {  135,   89,    3,    1 },  /* 161: ATTACK 1 S (Att_SHOURYUUKEN) */
    {    0,    0,    0,    8 },  /* 162: not used by a script */
    {    0,    0,    0,    6 },  /* 163: super art Att_PL07_SA2 (command slot 17) */
    {    0,    0,    0,   10 },  /* 164: air super art Att_PL07_SA3 (command slot 33) */
    {   57,   78,    3,    3 },  /* 165: V JUMP P L A */
    {  108,    0,    3,    3 },  /* 166: L KICK C */
    {  109,   79,    2,    2 },  /* 167: KAGAMI P A */
    {  140,   80,    1,    1 },  /* 168: ATTACK 5 S (Att_CHOUCHUURENGEKI), ATTACK 5 M (Att_CHOUCHUURENGEKI), ATTACK 5 L (Att_CHOUCHUURENGEKI) */
    {   23,   81,    2,    2 },  /* 169: ATTACK 5 SP */
    {  112,    0,    8,   10 },  /* 170: air Att_PL07_AT3 (command slot 37), saca 64, saca 74 +1 */
    {  113,    0,    8,   10 },  /* 171: air Att_PL07_AT3 (command slot 37), saca 64, saca 74 +1 */
    {  114,    0,    8,   10 },  /* 172: air Att_PL07_AT3 (command slot 37), saca 74, saca 75 */
    {    0,   49,    0,    6 },  /* 173: super art Att_PL07_SA2 (command slot 17) */
    {  115,   82,    3,    3 },  /* 174: V JUMP K M A */
    {  118,   83,    3,    3 },  /* 175: V JUMP P M A */
    {  119,   84,    3,    3 },  /* 176: V JUMP P M A */
    {  120,    0,    1,    1 },  /* 177: not used by a script */
    {  121,    0,    1,    1 },  /* 178: L KICK B, atca 161, saca 84 +2 */
    {  123,    0,    3,    9 },  /* 179: ATTACK 2 M (Att_PL07_AT2), ATTACK 2 L (Att_PL07_AT2) */
    {   38,   85,    1,    1 },  /* 180: not used by a script */
    {  125,    0,    3,    3 },  /* 181: M KICK C */
    {   23,    0,    2,    2 },  /* 182: KAGAMI K A, atca 157 */
    {  126,   86,    3,    3 },  /* 183: F JUMP P M A */
    {   38,   87,    1,    1 },  /* 184: S KICK A, saca 84, saca 85 +1 */
    {    1,   88,    1,    1 },  /* 185: not used by a script */
    {  135,   90,    3,    1 },  /* 186: ATTACK 1 S (Att_SHOURYUUKEN) */
    {  135,   91,    3,    1 },  /* 187: ATTACK 1 S (Att_SHOURYUUKEN) */
    {  135,   92,    3,    1 },  /* 188: ATTACK 1 S (Att_SHOURYUUKEN) */
    {  135,   93,    3,    1 },  /* 189: ATTACK 1 S (Att_SHOURYUUKEN) */
    {  135,    0,    3,    1 },  /* 190: ATTACK 1 S (Att_SHOURYUUKEN) */
    {   44,    0,    3,    1 },  /* 191: ATTACK 1 S (Att_SHOURYUUKEN) */
    {  132,    0,    1,    1 },  /* 192: ATTACK 1 M (Att_SHOURYUUKEN) */
    {  132,   48,    1,    1 },  /* 193: ATTACK 1 M (Att_SHOURYUUKEN) */
    {  132,   51,    1,    1 },  /* 194: ATTACK 1 M (Att_SHOURYUUKEN) */
    {  137,   52,    3,    1 },  /* 195: ATTACK 1 M (Att_SHOURYUUKEN) */
    {  137,   53,    3,    1 },  /* 196: ATTACK 1 M (Att_SHOURYUUKEN) */
    {  137,   54,    3,    1 },  /* 197: ATTACK 1 M (Att_SHOURYUUKEN) */
    {  137,   94,    3,    1 },  /* 198: ATTACK 1 M (Att_SHOURYUUKEN) */
    {   55,   78,    3,    3 },  /* 199: V JUMP P M A */
    {   63,   99,    3,    3 },  /* 200: F JUMP P M A */
    {  127,    0,   10,   12 },  /* 201: PIYO */
    {    0,    0,    0,    0 },  /* 202: CATCH 5 */
    {  126,  100,    3,    3 },  /* 203: saca 76 */
    {   64,  101,    3,    3 },  /* 204: saca 76 */
    {   70,  102,    3,    3 },  /* 205: saca 92 */
    {   71,  103,    3,    3 },  /* 206: saca 92 */
    {   72,  104,    3,    3 },  /* 207: saca 92 */
    {  128,    0,    2,    2 },  /* 208: ATTACK 4 S (Att_PL07_AT1), ATTACK 4 M (Att_PL07_AT1), ATTACK 4 L (Att_PL07_AT1) */
    {  129,    0,   10,   12 },  /* 209: PIYO */
    {    0,    0,    0,   13 },  /* 210: NEKOROBI S */
    {  130,  105,    1,    1 },  /* 211: saca 84, saca 85, saca 86 */
    {  131,  106,    1,    1 },  /* 212: saca 84, saca 85, saca 86 */
    {   45,   95,    3,    1 },  /* 213: ATTACK 1 M (Att_SHOURYUUKEN) */
    {   45,   96,    3,    1 },  /* 214: ATTACK 1 M (Att_SHOURYUUKEN) */
    {   78,  107,    2,    2 },  /* 215: saca 84, saca 85, saca 86 */
    {  122,  108,    2,    2 },  /* 216: saca 84, saca 85, saca 86 */
    {   50,  109,    1,    1 },  /* 217: saca 88 */
    {   45,  110,    1,    1 },  /* 218: saca 84, saca 85, saca 86 */
    {   45,  111,   12,    1 },  /* 219: saca 84, saca 85, saca 86 */
    {  137,   97,    3,    1 },  /* 220: ATTACK 1 M (Att_SHOURYUUKEN) */
    {  137,   98,    3,    1 },  /* 221: ATTACK 1 M (Att_SHOURYUUKEN) */
    {  137,    0,    3,    1 },  /* 222: ATTACK 1 M (Att_SHOURYUUKEN) */
    {   44,    0,    3,    1 },  /* 223: ATTACK 1 M (Att_SHOURYUUKEN) */
    {  133,    0,    1,    1 },  /* 224: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  133,   48,    1,    1 },  /* 225: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  133,   51,    1,    1 },  /* 226: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  138,  112,    3,    1 },  /* 227: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  138,  113,    3,    1 },  /* 228: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  138,   54,    3,    1 },  /* 229: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  138,   94,    3,    1 },  /* 230: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  138,   95,    3,    1 },  /* 231: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  138,   96,    3,    1 },  /* 232: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  138,   97,    3,    1 },  /* 233: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  138,   98,    3,    1 },  /* 234: ATTACK 1 L (Att_SHOURYUUKEN) */
    {  138,    0,    3,    1 },  /* 235: ATTACK 1 L (Att_SHOURYUUKEN) */
    {   44,    0,    3,    1 },  /* 236: ATTACK 1 L (Att_SHOURYUUKEN) */
    {    0,    0,    0,    1 },  /* 237: saca 84, saca 85, saca 86 */
    {  139,    0,    5,    6 },  /* 238: super art Att_PL07_SA2 (command slot 17) */
    {   51,   34,   11,    2 },  /* 239: KAGAMI P A */
    {   51,    0,   11,    2 },  /* 240: KAGAMI P A */
    {    1,    0,    0,    1 },  /* 241: HANASARE */
    {    2,    0,    0,    2 },  /* 242: HANASARE */
    {   82,  114,    5,    6 },  /* 243: ATTACK 3 M (Att_CHOUCHUURENGEKI) */
    {   82,  115,    5,    6 },  /* 244: ATTACK 3 L (Att_CHOUCHUURENGEKI) */
    {    1,    0,    1,    0 },  /* 245: LOSE SONABA */
    {   45,    0,   12,    1 },  /* 246: saca 89, saca 90, saca 91 */
    {   44,    0,   12,    1 },  /* 247: saca 89, saca 90, saca 91 */
};

const BODY_BOX ibuki_body_box[141] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {  -16,  20,   74,  18 },  {  -36,  56,   66,  15 },  {  -26,  42,   34,  32 },  {  -36,  68,    0,  37 },  {    0,   0,    0,   0 } } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +103 */
    { { {  -19,  20,   45,  18 },  {    0,   0,    0,   0 },  {  -36,  58,    0,  58 },  {  -48,  80,    0,  27 },  {    0,   0,    0,   0 } } },  /* 2: DASH TOBINOKI, KAGAMU, KAGAMI KAMAE +30 */
    { { {  -28,  20,   74,  18 },  {  -44,  56,   66,  15 },  {  -30,  36,   34,  32 },  {  -36,  68,    0,  37 },  {    0,   0,    0,   0 } } },  /* 3: S PUNCH A, ATTACK 3 S (Att_CHOUCHUURENGEKI), ATTACK 3 M (Att_CHOUCHUURENGEKI) +1 */
    { { {  -28,  20,   74,  18 },  {  -36,  48,   66,  15 },  {  -24,  34,   37,  29 },  {  -36,  68,    0,  37 },  {  -63,  35,   61,  25 } } },  /* 4: S PUNCH B */
    { { {  -28,  20,   74,  18 },  {  -36,  48,   66,  15 },  {  -24,  34,   37,  29 },  {  -36,  68,    0,  37 },  {  -78,  50,   61,  25 } } },  /* 5: S PUNCH B */
    { { {  -14,  20,   92,  18 },  {  -28,  46,   86,  12 },  {  -19,  38,   70,  19 },  {  -38,  60,   45,  25 },  {    0,   0,    0,   0 } } },  /* 6: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +10 */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -34,  64,   44,  50 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 7: JUMP FRONT, JUMP BACK, SP JUMP FRONT +13 */
    { { {  -14,  20,   92,  18 },  {  -29,  48,   86,  12 },  {  -23,  43,   67,  19 },  {  -29,  54,   38,  29 },  {    0,   0,    0,   0 } } },  /* 8: JUMP FRONT, JUMP VERTICAL, JUMP BACK +23 */
    { { {  -28,  20,   74,  18 },  {  -35,  44,   62,  16 },  {  -30,  36,   34,  32 },  {  -36,  68,    0,  37 },  {  -58,  30,   63,  21 } } },  /* 9: S PUNCH A */
    { { {   -3,  20,   72,  18 },  {  -22,  54,   66,  15 },  {  -11,  39,   34,  32 },  {  -30,  68,    0,  37 },  {    0,   0,    0,   0 } } },  /* 10: GUARD HEAD, GUARD UP */
    { { {  -15,  20,   45,  18 },  {    0,   0,    0,   0 },  {  -34,  58,    0,  56 },  {  -44,  78,    0,  27 },  {    0,   0,    0,   0 } } },  /* 11: GUARD DOWN */
    { { {  -18,  16,   78,  14 },  {  -24,  40,   74,  12 },  {  -20,  30,   62,  14 },  {  -40,  60,   46,  22 },  {    0,   0,    0,   0 } } },  /* 12: not used by a script */
    { { {  -22,  20,   64,  18 },  {    0,   0,    0,   0 },  {  -32,  52,   25,  48 },  {  -40,  72,    0,  37 },  {    0,   0,    0,   0 } } },  /* 13: DASH HUMIKOMI */
    { { {  -22,  20,   64,  18 },  {    0,   0,    0,   0 },  {  -32,  52,   25,  48 },  {  -40,  72,    0,  37 },  {    0,   0,    0,   0 } } },  /* 14: DASH HUMIKOMI */
    { { {  -22,  20,   64,  18 },  {    0,   0,    0,   0 },  {  -32,  52,   25,  48 },  {  -40,  72,    0,  37 },  {    0,   0,    0,   0 } } },  /* 15: DASH HUMIKOMI, CATCH 5 */
    { { {  -22,  20,   63,  18 },  {    0,   0,    0,   0 },  {  -30,  48,   27,  44 },  {  -40,  72,    0,  37 },  {    0,   0,    0,   0 } } },  /* 16: DASH TOBINOKI */
    { { {  -22,  20,   88,  18 },  {  -45,  59,   80,  14 },  {  -39,  48,   17,  63 },  {  -34,  44,   34,  20 },  {    0,   0,    0,   0 } } },  /* 17: DASH TOBINOKI, ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2) +1 */
    { { {  -20,  20,   62,  18 },  {  -29,  48,   54,  15 },  {  -43,  70,   38,  20 },  {  -36,  68,    0,  37 },  {    0,   0,    0,   0 } } },  /* 18: M KICK C, atca 156 */
    { { {  -16,  20,   82,  18 },  {  -23,  52,   76,  15 },  {  -16,  43,   36,  40 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 19: M KICK C, atca 156 */
    { { {  -16,  20,   92,  18 },  {  -43,  61,   81,  15 },  {  -28,  51,   59,  22 },  {  -11,  34,   44,  16 },  {    0,   0,    0,   0 } } },  /* 20: M KICK C, atca 156 */
    { { {   -8,  20,   88,  18 },  {  -30,  48,   78,  15 },  {  -45,  62,   54,  25 },  {  -27,  44,   36,  19 },  {  -91,  61,   50,  26 } } },  /* 21: M KICK C, atca 156 */
    { { {    2,  20,   84,  18 },  {  -26,  48,   69,  15 },  {  -38,  48,   18,  51 },  {  -64,  46,   29,  31 },  {    0,   0,    0,   0 } } },  /* 22: M KICK C, atca 156 */
    { { {  -18,  20,   48,  18 },  {  -36,  54,   40,  19 },  {    0,   0,    0,   0 },  {  -48,  75,    0,  40 },  {  -86,  38,    0,  19 } } },  /* 23: KAGAMI K A, atca 157, UP P GUARD K S +1 */
    { { {  -14,  20,   84,  18 },  {  -28,  46,   75,  15 },  {  -30,  52,   53,  22 },  {  -27,  45,   21,  32 },  {    0,   0,    0,   0 } } },  /* 24: V JUMP K L A, F JUMP K L A, saca 92 */
    { { {  -14,  20,   84,  18 },  {  -28,  46,   75,  15 },  {  -34,  64,   56,  19 },  {  -18,  45,   21,  36 },  {    0,   0,    0,   0 } } },  /* 25: V JUMP K L A, F JUMP K L A, saca 92 */
    { { {  -16,  20,   86,  18 },  {  -24,  54,   78,  15 },  {  -26,  55,   34,  44 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 26: L KICK C */
    { { {  -16,  20,   90,  18 },  {  -30,  48,   83,  15 },  {  -18,  40,   62,  26 },  {  -10,  39,   27,  44 },  {  -54,  36,   62,  36 } } },  /* 27: L KICK C */
    { { {  -16,  20,   98,  18 },  {  -27,  48,   88,  15 },  {  -39,  74,   63,  26 },  {    0,   0,    0,   0 },  {  -93,  69,   62,  23 } } },  /* 28: L KICK C */
    { { {  -20,  20,   84,  18 },  {  -25,  48,   73,  15 },  {  -32,  43,   64,   9 },  {  -19,  44,   33,  15 },  {    0,   0,    0,   0 } } },  /* 29: F JUMP K S A */
    { { {   -8,  20,   87,  18 },  {  -16,  49,   82,  15 },  {  -39,  65,   58,  24 },  {  -44,  70,   38,  26 },  {    0,   0,    0,   0 } } },  /* 30: F JUMP K M A, atca 158, FUSHIN P S */
    { { {   -8,  20,   87,  18 },  {  -16,  49,   82,  15 },  {  -39,  65,   58,  24 },  {  -41,  80,   41,  18 },  {  -73,  46,   36,  35 } } },  /* 31: F JUMP K M A, atca 158, FUSHIN P S */
    { { {  -26,  20,   67,  18 },  {  -36,  56,   58,  15 },  {  -26,  42,   30,  32 },  {  -36,  68,    0,  37 },  {    0,   0,    0,   0 } } },  /* 32: M PUNCH A */
    { { {  -26,  20,   67,  18 },  {  -36,  56,   58,  15 },  {  -26,  42,   30,  32 },  {  -36,  68,    0,  37 },  {  -63,  37,   75,  33 } } },  /* 33: M PUNCH A */
    { { {  -16,  20,   74,  18 },  {  -36,  56,   66,  15 },  {  -26,  42,   34,  32 },  {  -36,  68,    0,  37 },  {    0,   0,    0,   0 } } },  /* 34: M PUNCH B */
    { { {  -16,  20,   74,  18 },  {  -36,  56,   66,  15 },  {  -26,  42,   34,  32 },  {  -36,  68,    0,  37 },  {  -75,  39,   62,  21 } } },  /* 35: M PUNCH B */
    { { {  -20,  20,   72,  18 },  {  -36,  56,   63,  15 },  {  -26,  42,   34,  32 },  {  -36,  68,    0,  37 },  {  -57,  37,   61,  24 } } },  /* 36: L PUNCH A */
    { { {   -2,  20,   74,  18 },  {  -28,  56,   66,  15 },  {  -26,  42,   34,  32 },  {   -7,  40,    0,  44 },  {    0,   0,    0,   0 } } },  /* 37: S KICK A, saca 84, saca 85 +1 */
    { { {   -2,  20,   74,  18 },  {  -28,  56,   66,  15 },  {  -26,  42,   34,  32 },  {   -7,  40,    0,  44 },  {  -66,  60,   45,  28 } } },  /* 38: S KICK A, saca 84, saca 85 +1 */
    { { {  -16,  20,   70,  18 },  {  -36,  56,   62,  15 },  {  -26,  42,   34,  32 },  {  -38,  46,    0,  38 },  {  -91,  65,   25,  25 } } },  /* 39: S KICK B */
    { { {  -16,  20,   78,  18 },  {  -36,  56,   70,  15 },  {  -26,  42,   38,  32 },  {  -30,  56,    0,  44 },  {    0,   0,    0,   0 } } },  /* 40: M KICK A, atca 160, saca 88 */
    { { {    4,  20,   76,  18 },  {  -28,  54,   67,  15 },  {  -20,  40,   39,  28 },  {  -20,  51,    0,  39 },  {    0,   0,    0,   0 } } },  /* 41: M KICK B, ATTACK 5 S (Att_CHOUCHUURENGEKI), ATTACK 5 M (Att_CHOUCHUURENGEKI) +1 */
    { { {    4,  20,   74,  18 },  {  -27,  52,   63,  19 },  {  -26,  40,   40,  24 },  {  -34,  57,    0,  45 },  {  -75,  48,   58,  22 } } },  /* 42: M KICK B, ATTACK 5 S (Att_CHOUCHUURENGEKI), ATTACK 5 M (Att_CHOUCHUURENGEKI) +1 */
    { { {    4,  20,   72,  18 },  {  -13,  40,   62,  20 },  {  -36,  47,   39,  23 },  {  -20,  51,    0,  39 },  {    0,   0,    0,   0 } } },  /* 43: M KICK B, ATTACK 5 S (Att_CHOUCHUURENGEKI), ATTACK 5 M (Att_CHOUCHUURENGEKI) +7 */
    { { {  -16,  20,   78,  18 },  {  -43,  50,   72,  15 },  {  -39,  51,   46,  24 },  {  -34,  47,    0,  34 },  {    0,   0,    0,   0 } } },  /* 44: L KICK A, ATTACK 6 S, saca 89 +5 */
    { { {  -16,  20,   78,  18 },  {  -36,  52,   70,  12 },  {  -28,  36,   34,  36 },  {  -34,  47,    0,  34 },  {  -52,  42,   58,  68 } } },  /* 45: L KICK A, ATTACK 6 S, saca 89 +6 */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 46: no box */
    { { {  -16,  20,   74,  18 },  {  -30,  46,   65,  15 },  {  -27,  40,   36,  29 },  {  -24,  55,    0,  37 },  {    0,   0,    0,   0 } } },  /* 47: L PUNCH B, saca 84, saca 85 +1 */
    { { {  -16,  20,   74,  18 },  {  -30,  46,   65,  15 },  {  -27,  40,   36,  29 },  {  -48,  76,    0,  34 },  {    0,   0,    0,   0 } } },  /* 48: TOUKETSU A, L PUNCH B, saca 84 +2 */
    { { {  -21,  20,   66,  18 },  {  -27,  46,   54,  15 },  {  -26,  40,   29,  29 },  {  -40,  76,    0,  34 },  {  -56,  35,   49,  30 } } },  /* 49: L PUNCH B */
    { { {  -16,  20,   78,  18 },  {  -36,  56,   70,  15 },  {  -26,  42,   38,  32 },  {  -30,  56,    0,  44 },  {    0,   0,    0,   0 } } },  /* 50: M KICK A, atca 160, saca 88 */
    { { {  -19,  20,   50,  18 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -48,  80,    0,  38 },  {  -78, 106,   38,  19 } } },  /* 51: KAGAMI P A */
    { { {  -25,  20,   62,  18 },  {  -39,  46,   53,  15 },  {  -39,  55,   33,  20 },  {  -40,  78,    0,  33 },  {    0,   0,    0,   0 } } },  /* 52: KAGAMI P A */
    { { {  -19,  20,   66,  18 },  {  -39,  56,   53,  23 },  {  -39,  55,   33,  20 },  {  -40,  78,    0,  34 },  {  -67,  52,   65,  41 } } },  /* 53: KAGAMI P A */
    { { {   -4,  20,   50,  18 },  {  -18,  50,   38,  19 },  {  -26,  63,    0,  38 },  {    0,   0,    0,   0 },  {  -90,  64,    6,  27 } } },  /* 54: KAGAMI K A */
    { { {  -10,  20,   86,  18 },  {  -26,  56,   78,  15 },  {  -19,  46,   60,  18 },  {  -36,  69,   41,  19 },  {    0,   0,    0,   0 } } },  /* 55: V JUMP P S A, V JUMP P M A */
    { { {  -10,  20,   87,  18 },  {  -34,  52,   80,  15 },  {  -19,  36,   60,  20 },  {  -32,  60,   39,  21 },  {  -87,  68,   65,  25 } } },  /* 56: V JUMP P S A */
    { { {  -16,  20,   87,  18 },  {  -34,  44,   76,  15 },  {  -24,  30,   62,  14 },  {  -36,  52,   29,  33 },  {    0,   0,    0,   0 } } },  /* 57: V JUMP P L A */
    { { {  -10,  20,   87,  18 },  {  -22,  44,   77,  15 },  {  -18,  31,   63,  14 },  {  -16,  50,   31,  32 },  {    0,   0,    0,   0 } } },  /* 58: V JUMP P L A, atca 159 */
    { { {  -20,  20,   82,  18 },  {  -30,  42,   72,  15 },  {    0,   0,    0,   0 },  {  -18,  48,   33,  39 },  {  -67,  49,   57,  26 } } },  /* 59: V JUMP P L A, atca 159 */
    { { {  -18,  20,   87,  18 },  {  -26,  42,   77,  15 },  {    0,   0,    0,   0 },  {  -33,  56,   33,  44 },  {    0,   0,    0,   0 } } },  /* 60: V JUMP K S A, V JUMP K M A */
    { { {  -18,  20,   87,  18 },  {  -32,  47,   74,  19 },  {  -23,  42,   52,  22 },  {  -16,  33,   16,  36 },  {  -92,  69,   39,  31 } } },  /* 61: V JUMP K S A, V JUMP K M A */
    { { {  -18,  20,   87,  18 },  {  -26,  44,   78,  15 },  {  -21,  43,   18,  60 },  {  -63,  43,   43,  22 },  {    0,   0,    0,   0 } } },  /* 62: V JUMP K M A */
    { { {  -43,  20,   76,  18 },  {  -46,  50,   70,  15 },  {  -43,  51,   50,  20 },  {  -35,  67,   29,  21 },  {    0,   0,    0,   0 } } },  /* 63: F JUMP P S A, F JUMP P M A, saca 76 */
    { { {  -43,  20,   76,  18 },  {  -47,  58,   73,  15 },  {  -42,  51,   53,  20 },  {  -23,  51,   28,  25 },  {  -76,  43,   36,  34 } } },  /* 64: F JUMP P S A, F JUMP P M A, saca 76 */
    { { {   -8,  16,   51,  14 },  {  -19,  40,   42,  12 },  {  -16,  32,   26,  12 },  {  -32,  62,    0,  26 },  {    0,   0,    0,   0 } } },  /* 65: not used by a script */
    { { {  -25,  16,   51,  14 },  {  -19,  40,   42,  12 },  {  -16,  32,   26,  12 },  {  -32,  62,    0,  26 },  {    0,   0,    0,   0 } } },  /* 66: not used by a script */
    { { {  -25,  16,   51,  14 },  {  -19,  40,   42,  12 },  {  -16,  32,   26,  12 },  {  -32,  62,    0,  26 },  {  -53,  35,   48,   8 } } },  /* 67: not used by a script */
    { { {    0,   0,    0,   0 },  {  -22,  38,   66,  12 },  {  -16,  28,   40,  24 },  {  -30,  54,    0,  38 },  {    0,   0,    0,   0 } } },  /* 68: not used by a script */
    { { {  -16,  20,   78,  18 },  {  -36,  52,   70,  12 },  {  -28,  36,   34,  36 },  {  -34,  47,    0,  34 },  {    0,   0,    0,   0 } } },  /* 69: L KICK A, saca 84, saca 85 +1 */
    { { {  -14,  20,   84,  18 },  {  -26,  48,   66,  24 },  {  -38,  58,   48,  28 },  {  -10,  37,   17,  43 },  {  -50,  36,   59,  59 } } },  /* 70: V JUMP K L A, F JUMP K L A, saca 92 */
    { { {  -14,  20,   84,  18 },  {  -25,  43,   66,  27 },  {  -42,  62,   45,  21 },  {  -10,  40,   14,  43 },  {  -73,  49,   38,  34 } } },  /* 71: V JUMP K L A, F JUMP K L A, saca 92 */
    { { {  -14,  20,   84,  18 },  {  -25,  43,   66,  24 },  {  -37,  56,   43,  23 },  {  -10,  40,   14,  43 },  {  -65,  37,   12,  33 } } },  /* 72: saca 92 */
    { { {  -18,  20,   84,  18 },  {  -23,  48,   76,  15 },  {  -28,  54,   45,  31 },  {    0,   0,    0,   0 },  {  -47,  38,   28,  32 } } },  /* 73: F JUMP K S A */
    { { {   -7,  20,   86,  18 },  {  -19,  44,   80,  15 },  {  -19,  42,   46,  32 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 74: not used by a script */
    { { {  -27,  16,   73,  14 },  {  -32,  38,   64,  13 },  {  -27,  32,   42,  20 },  {  -32,  54,    0,  40 },  {  -44,  11,   53,  25 } } },  /* 75: not used by a script */
    { { {    0,   0,    0,   0 },  {  -22,  44,   33,  18 },  {  -26,  48,   15,  22 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 76: not used by a script */
    { { {   20,  20,   39,  18 },  {    0,   0,    0,   0 },  {  -24,  50,    0,  84 },  {    0,   0,    0,   0 },  {  -78,  54,   48,  29 } } },  /* 77: L KICK B, atca 161, OKIAGARI P S +3 */
    { { {   20,  20,   39,  18 },  {    0,   0,    0,   0 },  {  -28,  56,    0,  68 },  {  -73,  63,   80,  22 },  { -106, 116,   60,  30 } } },  /* 78: L KICK B, atca 161, OKIAGARI P S +3 */
    { { {  -19,  16,   85,  14 },  {  -37,  48,   71,  13 },  {  -23,  30,   51,  22 },  {   -2,  47,    0,  48 },  {    0,   0,    0,   0 } } },  /* 79: not used by a script */
    { { {  -39,  20,   63,  18 },  {  -58,  46,   55,  15 },  {  -45,  28,   34,  21 },  {  -51,  71,    0,  34 },  {  -73,  34,   49,  30 } } },  /* 80: L PUNCH B */
    { { {  -41,  20,   63,  18 },  {  -51,  46,   55,  15 },  {  -42,  42,   34,  21 },  {  -51,  71,    0,  34 },  {  -77,  36,   46,  30 } } },  /* 81: L PUNCH B */
    { { {  -47,  41,   70,  18 },  {  -69,  81,   59,  17 },  {  -54,  68,   36,  24 },  {  -62,  86,    0,  37 },  {    0,   0,    0,   0 } } },  /* 82: ATTACK 3 S (Att_CHOUCHUURENGEKI), ATTACK 3 M (Att_CHOUCHUURENGEKI), ATTACK 3 L (Att_CHOUCHUURENGEKI) +1 */
    { { {  -11,  20,   90,  18 },  {  -22,  43,   83,  15 },  {  -27,  42,   64,  24 },  {  -18,  30,   21,  47 },  {  -49,  38,   81,  22 } } },  /* 83: not used by a script */
    { { {   -6,  20,   87,  18 },  {  -23,  46,   80,  15 },  {  -37,  55,   54,  26 },  {  -21,  33,   16,  38 },  {  -41,  35,   74,  24 } } },  /* 84: not used by a script */
    { { {   -3,  20,   84,  18 },  {  -23,  48,   75,  15 },  {  -18,  34,   50,  25 },  {  -44,  45,   23,  37 },  {  -36,  33,   71,  23 } } },  /* 85: not used by a script */
    { { {   -5,  20,   79,  18 },  {  -19,  56,   70,  15 },  {  -34,  62,   38,  32 },  {  -11,  40,    0,  38 },  {    0,   0,    0,   0 } } },  /* 86: not used by a script */
    { { {  -18,  45,   68,  16 },  {  -24,  56,   55,  17 },  {  -23,  52,   41,  14 },  {  -20,  45,   28,  13 },  {    0,   0,    0,   0 } } },  /* 87: AIR S, AIR M, AIR L +47 */
    { { {  -21,  20,   43,  18 },  {  -24,  39,   37,  15 },  {  -19,  52,   13,  24 },  {  -30,  68,    0,  15 },  {    0,   0,    0,   0 } } },  /* 88: not used by a script */
    { { {  -24,  20,   78,  18 },  {  -33,  48,   73,  15 },  {  -19,  50,   48,  25 },  {  -86, 116,   19,  29 },  {    0,   0,    0,   0 } } },  /* 89: ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2), ATTACK 2 L (Att_PL07_AT2) */
    { { {  -18,  20,   84,  18 },  {  -36,  48,   76,  15 },  {  -39,  68,   53,  23 },  {  -66,  60,   28,  25 },  {    0,   0,    0,   0 } } },  /* 90: ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2), ATTACK 2 L (Att_PL07_AT2) */
    { { {  -41,  20,   74,  18 },  {  -53,  65,   60,  21 },  {  -53,  63,   37,  24 },  {  -62,  81,    0,  37 },  {  -85,  44,   44,  50 } } },  /* 91: super art Att_PL07_SA2 (command slot 17) */
    { { {  -51,  20,   70,  18 },  {  -49,  62,   57,  19 },  {  -55,  48,   37,  19 },  {  -62,  81,    0,  37 },  { -104, 124,   49,  45 } } },  /* 92: super art Att_PL07_SA2 (command slot 17) */
    { { {  -18,  20,   84,  18 },  {  -36,  48,   76,  15 },  {  -39,  54,   51,  25 },  {  -42,  66,    1,  50 },  {    0,   0,    0,   0 } } },  /* 93: ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2), ATTACK 2 L (Att_PL07_AT2) */
    { { {   -2,  20,   30,  18 },  {  -16,  44,   26,  18 },  {  -16,  49,    0,  26 },  {  -45,  29,   26,  16 },  {  -75,  60,    0,  30 } } },  /* 94: KAGAMI K A, ATTACK 4 S (Att_PL07_AT1), ATTACK 4 M (Att_PL07_AT1) +1 */
    { { {   -2,  20,   30,  18 },  {  -16,  44,   26,  18 },  {  -16,  46,    0,  37 },  {  -37,  21,   26,  21 },  {  -52,  49,    0,  26 } } },  /* 95: ATTACK 4 S (Att_PL07_AT1), ATTACK 4 M (Att_PL07_AT1), ATTACK 4 L (Att_PL07_AT1) */
    { { {  -21,  16,   78,  14 },  {  -29,  41,   75,  12 },  {  -30,  47,   33,  48 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 96: not used by a script */
    { { {  -23,  20,   60,  18 },  {  -53, 106,   67,  27 },  {    0,   0,    0,   0 },  {  -38,  70,   90,  66 },  {    0,   0,    0,   0 } } },  /* 97: air Att_PL07_AT3 (command slot 37), saca 65, saca 66 +7 */
    { { {  -30,  20,   63,  18 },  {  -55, 100,   76,  23 },  {  -24,  53,   94,  22 },  {  -21,  75,  116,  31 },  {    0,   0,    0,   0 } } },  /* 98: air Att_PL07_AT3 (command slot 37), saca 65, saca 66 +7 */
    { { {  -19,  20,   58,  18 },  {  -34,  59,   63,  16 },  {  -29,  48,   79,  16 },  {  -43,  69,   95,  38 },  {    0,   0,    0,   0 } } },  /* 99: air Att_PL07_AT3 (command slot 37), air super art Att_PL07_SA3 (command slot 33) */
    { { {    4,  20,   74,  18 },  {  -27,  52,   63,  19 },  {  -26,  40,   40,  24 },  {  -34,  57,    0,  45 },  { -104,  77,   60,  26 } } },  /* 100: M KICK B */
    { { {  -16,  20,   98,  18 },  {  -27,  48,   88,  15 },  {  -39,  74,   63,  26 },  {    0,   0,    0,   0 },  {  -87,  48,   53,  32 } } },  /* 101: L KICK C */
    { { {  -16,  20,   70,  18 },  {  -36,  56,   62,  15 },  {  -26,  42,   34,  32 },  {  -38,  46,    0,  38 },  {  -79,  56,   16,  32 } } },  /* 102: S KICK B */
    { { {  -16,  20,   78,  18 },  {  -36,  56,   70,  15 },  {  -26,  42,   38,  32 },  {  -30,  56,    0,  44 },  {  -54,  38,   34,  56 } } },  /* 103: M KICK A, atca 160, saca 88 */
    { { {  -23,  20,   68,  18 },  {  -39,  47,   53,  22 },  {  -39,  55,   33,  20 },  {  -40,  78,    0,  34 },  {  -59,  34,   61,  42 } } },  /* 104: KAGAMI P A */
    { { {  -16,  20,   74,  18 },  {  -36,  56,   66,  15 },  {  -26,  42,   34,  32 },  {  -36,  68,    0,  37 },  {  -75,  39,   62,  21 } } },  /* 105: M PUNCH B */
    { { {  -20,  20,   72,  18 },  {  -36,  56,   63,  15 },  {  -26,  42,   34,  32 },  {  -36,  68,    0,  37 },  {  -50,  29,   32,  39 } } },  /* 106: L PUNCH A */
    { { {  -21,  20,   66,  18 },  {  -27,  46,   54,  15 },  {  -26,  40,   29,  29 },  {  -40,  76,    0,  34 },  {  -56,  35,   49,  30 } } },  /* 107: L PUNCH B, saca 84, saca 85 +1 */
    { { {  -16,  20,   98,  18 },  {  -44,  82,   94,  13 },  {  -29,  53,   63,  32 },  {  -52,  95,   34,  28 },  {    0,   0,    0,   0 } } },  /* 108: L KICK C */
    { { {  -19,  20,   50,  18 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -48,  80,    0,  38 },  {  -68,  96,   38,  19 } } },  /* 109: KAGAMI P A */
    { { {   -2,  20,   30,  18 },  {  -16,  44,   26,  18 },  {  -16,  49,    0,  26 },  {    0,   0,    0,   0 },  {  -98,  82,    0,  30 } } },  /* 110: KAGAMI K A */
    { { {  -18,  20,   47,  18 },  {    0,   0,    0,   0 },  {  -36,  59,    0,  59 },  {  -68,  97,    0,  27 },  {    0,   0,    0,   0 } } },  /* 111: KAGAMI K A, atca 157, UP P GUARD K S +1 */
    { { {  -39,  20,   59,  18 },  {  -55,  96,   72,  25 },  {    0,   0,    0,   0 },  {  -25,  84,   96,  33 },  {    0,   0,    0,   0 } } },  /* 112: air Att_PL07_AT3 (command slot 37), saca 64, saca 74 +1 */
    { { {  -41,  20,   64,  18 },  {  -21,  72,   62,  29 },  {    0,   0,    0,   0 },  {   -9,  55,   91,  22 },  {    0,   0,    0,   0 } } },  /* 113: air Att_PL07_AT3 (command slot 37), saca 64, saca 74 +1 */
    { { {  -41,  20,   64,  18 },  {  -21,  68,   62,  29 },  {    0,   0,    0,   0 },  {  -41,  34,   62,  40 },  {    0,   0,    0,   0 } } },  /* 114: air Att_PL07_AT3 (command slot 37), saca 74, saca 75 */
    { { {  -18,  20,   87,  18 },  {  -32,  47,   74,  19 },  {  -23,  42,   52,  22 },  {  -16,  33,   16,  36 },  {  -78,  55,   40,  30 } } },  /* 115: V JUMP K M A */
    { { {  -15,  20,   75,  18 },  {  -34,  58,   66,  18 },  {  -26,  42,   34,  32 },  {  -44,  76,    0,  37 },  {    0,   0,    0,   0 } } },  /* 116: UP P GUARD P S */
    { { {  -10,  20,   87,  18 },  {  -34,  52,   80,  15 },  {  -19,  36,   60,  20 },  {  -32,  60,   39,  21 },  {  -68,  49,   69,  23 } } },  /* 117: V JUMP P S A, V JUMP P M A */
    { { {  -10,  20,   87,  18 },  {  -34,  52,   80,  15 },  {  -19,  36,   60,  20 },  {  -32,  60,   39,  21 },  {  -78,  59,   72,  24 } } },  /* 118: V JUMP P M A */
    { { {  -10,  20,   87,  18 },  {  -34,  52,   80,  15 },  {  -19,  36,   60,  20 },  {  -32,  60,   39,  21 },  {  -70,  51,   72,  24 } } },  /* 119: V JUMP P M A */
    { { {   -8,  20,   78,  18 },  {  -22,  46,   70,  15 },  {  -20,  49,   46,  24 },  {  -28,  60,    0,  46 },  {    0,   0,    0,   0 } } },  /* 120: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -34,  63,   28,  52 },  {  -26,  63,    0,  28 },  {    0,   0,    0,   0 } } },  /* 121: L KICK B, atca 161, saca 84 +2 */
    { { {   20,  20,   39,  18 },  {    0,   0,    0,   0 },  {  -28,  56,    0,  68 },  {  -60,  50,   78,  20 },  {  -88,  98,   60,  28 } } },  /* 122: L KICK B, atca 161, OKIAGARI P S +3 */
    { { {  -18,  20,   84,  18 },  {  -36,  48,   76,  15 },  {  -39,  54,   51,  25 },  {  -33,  51,   39,  12 },  {    0,   0,    0,   0 } } },  /* 123: ATTACK 2 M (Att_PL07_AT2), ATTACK 2 L (Att_PL07_AT2) */
    { { {  -26,  20,   67,  18 },  {  -36,  56,   58,  15 },  {  -26,  42,   30,  32 },  {  -36,  68,    0,  37 },  {  -67,  41,   71,  33 } } },  /* 124: M PUNCH A */
    { { {  -16,  20,   92,  18 },  {  -43,  61,   81,  15 },  {  -28,  51,   59,  22 },  {  -11,  34,   44,  16 },  {  -78,  62,   71,  31 } } },  /* 125: M KICK C */
    { { {  -43,  20,   76,  18 },  {  -47,  58,   73,  15 },  {  -42,  51,   53,  20 },  {  -23,  51,   28,  25 },  {  -72,  41,   40,  30 } } },  /* 126: F JUMP P M A, saca 76 */
    { { {  -52,  20,   49,  18 },  {  -44,  62,   58,  19 },  {  -46,  70,   28,  29 },  {  -41,  79,    0,  27 },  {    0,   0,    0,   0 } } },  /* 127: PIYO */
    { { {  -19,  20,   51,  18 },  {    0,   0,    0,   0 },  {  -36,  58,    0,  64 },  {  -48,  80,    0,  27 },  {    0,   0,    0,   0 } } },  /* 128: ATTACK 4 S (Att_PL07_AT1), ATTACK 4 M (Att_PL07_AT1), ATTACK 4 L (Att_PL07_AT1) */
    { { {  -36,  28,   49,  18 },  {  -32,  62,   59,  19 },  {  -33,  68,   31,  28 },  {  -37,  77,    0,  30 },  {    0,   0,    0,   0 } } },  /* 129: PIYO */
    { { {  -21,  20,   68,  18 },  {  -27,  52,   54,  15 },  {  -26,  42,   29,  29 },  {  -38,  78,    0,  34 },  {  -40,  50,   55,  25 } } },  /* 130: saca 84, saca 85, saca 86 */
    { { {  -21,  20,   68,  18 },  {  -27,  52,   54,  15 },  {  -26,  42,   29,  29 },  {  -38,  78,    0,  34 },  {  -48,  52,   48,  31 } } },  /* 131: saca 84, saca 85, saca 86 */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -24,  45,   37,  42 },  {  -30,  44,    0,  37 },  {    0,   0,    0,   0 } } },  /* 132: ATTACK 1 M (Att_SHOURYUUKEN) */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -30,  53,   23,  41 },  {  -38,  70,    0,  23 },  {    0,   0,    0,   0 } } },  /* 133: ATTACK 1 L (Att_SHOURYUUKEN) */
    { { {  -15,  20,   73,  18 },  {  -26,  46,   66,  15 },  {  -18,  34,   34,  32 },  {  -24,  56,    0,  37 },  {    0,   0,    0,   0 } } },  /* 134: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 6 S */
    { { {  -15,  20,   80,  18 },  {  -32,  50,   68,  16 },  {  -26,  36,   34,  34 },  {  -24,  31,   22,  12 },  {  -42,  40,   58,  78 } } },  /* 135: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 6 S */
    { { {  -15,  20,   73,  18 },  {  -26,  46,   66,  15 },  {  -18,  34,   34,  32 },  {  -24,  56,    0,  37 },  {    0,   0,    0,   0 } } },  /* 136: not used by a script */
    { { {  -16,  20,   78,  18 },  {  -36,  52,   70,  12 },  {  -28,  36,   34,  36 },  {  -34,  47,   18,  16 },  {  -49,  39,   58,  63 } } },  /* 137: ATTACK 1 M (Att_SHOURYUUKEN) */
    { { {  -16,  20,   78,  18 },  {  -36,  52,   70,  12 },  {  -28,  36,   34,  36 },  {  -34,  47,   18,  16 },  {  -52,  36,   51,  52 } } },  /* 138: ATTACK 1 L (Att_SHOURYUUKEN) */
    { { {  -49,  20,   70,  18 },  {  -75,  84,   57,  25 },  {  -56,  39,   36,  24 },  {  -62,  81,    0,  37 },  {    0,   0,    0,   0 } } },  /* 139: super art Att_PL07_SA2 (command slot 17) */
    { { {    4,  20,   74,  18 },  {  -27,  52,   63,  19 },  {  -26,  40,   40,  24 },  {  -34,  57,    0,  45 },  { -122,  95,   60,  26 } } },  /* 140: ATTACK 5 S (Att_CHOUCHUURENGEKI), ATTACK 5 M (Att_CHOUCHUURENGEKI), ATTACK 5 L (Att_CHOUCHUURENGEKI) */
};

const ATTACK_BOX ibuki_att_box[116] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {    0,   0,    0,   0 },  {  -54,  24,   64,  10 },  {  -37,  25,   60,   8 } } },  /* 1: S PUNCH A; attack 1 */
    { { {    0,   0,    0,   0 },  {  -85,  12,   63,  16 },  {  -73,  52,   64,  10 } } },  /* 2: S PUNCH B; attack 2 */
    { { {    0,   0,    0,   0 },  {  -87,  23,   41,  24 },  {  -64,  41,   53,  11 } } },  /* 3: M KICK C, atca 156; attack 3 */
    { { {    0,   0,    0,   0 },  {  -62,  18,   14,  16 },  {  -46,  15,   26,  15 } } },  /* 4: M KICK C, atca 156; attack 4 */
    { { {    0,   0,    0,   0 },  {  -95,  38,    0,   7 },  {  -58,  47,    0,  15 } } },  /* 5: KAGAMI K A, atca 157, UP P GUARD K S; attack 5, 126 */
    { { {    0,   0,    0,   0 },  {  -60,  23,   86,  28 },  {  -46,  18,   70,  23 } } },  /* 6: V JUMP K L A, F JUMP K L A; attack 6 */
    { { {    0,   0,    0,   0 },  {  -82,  35,   41,  22 },  {  -47,  31,   44,  16 } } },  /* 7: V JUMP K L A, F JUMP K L A; attack 7 */
    { { {    0,   0,    0,   0 },  {  -62,  24,    9,  22 },  {  -43,  20,   23,  24 } } },  /* 8: not used by a script */
    { { {    0,   0,    0,   0 },  { -106,  28,   44,  25 },  {  -77,  55,   56,  15 } } },  /* 9: L KICK C; attack 9 */
    { { {    0,   0,    0,   0 },  {  -46,  19,   24,  17 },  {  -33,  19,   40,  16 } } },  /* 10: F JUMP K S A; attack 10 */
    { { {    0,   0,    0,   0 },  {  -39,  19,   32,  15 },  {    0,   0,    0,   0 } } },  /* 11: F JUMP K S A */
    { { {    0,   0,    0,   0 },  {  -88,  33,   40,  20 },  {  -55,  68,   42,  13 } } },  /* 12: F JUMP K M A, atca 158, FUSHIN P S; attack 11, 127 */
    { { {    0,   0,    0,   0 },  {  -76,  30,   40,  20 },  {  -46,  61,   45,  12 } } },  /* 13: F JUMP K M A, atca 158, FUSHIN P S; attack 12, 128 */
    { { {    0,   0,    0,   0 },  {  -48,  22,   67,  15 },  {  -38,  14,   54,  13 } } },  /* 14: M PUNCH A; attack 13 */
    { { {    0,   0,    0,   0 },  {  -62,  25,   90,  21 },  {  -48,  21,   74,  23 } } },  /* 15: M PUNCH A; attack 14 */
    { { {    0,   0,    0,   0 },  {  -50,  14,   88,  16 },  {    0,   0,    0,   0 } } },  /* 16: M PUNCH A; attack 15 */
    { { {    0,   0,    0,   0 },  {  -84,  22,   60,  14 },  {  -60,  22,   64,  14 } } },  /* 17: M PUNCH B; attack 16 */
    { { {    0,   0,    0,   0 },  {  -70,  41,   61,  12 },  {    0,   0,    0,   0 } } },  /* 18: M PUNCH B; attack 17 */
    { { {    0,   0,    0,   0 },  {  -43,  21,   71,  16 },  {  -34,  16,   80,  14 } } },  /* 19: L PUNCH A; attack 18 */
    { { {    0,   0,    0,   0 },  {  -55,  21,   55,  17 },  {  -48,  27,   67,   9 } } },  /* 20: L PUNCH A; attack 19 */
    { { {    0,   0,    0,   0 },  {  -47,  25,   34,  24 },  {  -43,  13,   53,  19 } } },  /* 21: L PUNCH A; attack 20 */
    { { {    0,   0,    0,   0 },  { -102,  40,   50,   8 },  {  -70,  40,   46,   8 } } },  /* 22: not used by a script */
    { { {    0,   0,    0,   0 },  {  -72,  14,   45,  22 },  {  -58,  48,   49,   7 } } },  /* 23: S KICK A, saca 84, saca 85 +1; attack 21, 134 */
    { { {    0,   0,    0,   0 },  {  -84,  20,   11,  24 },  {  -75,  32,   28,  11 } } },  /* 24: S KICK B; attack 23, 113 */
    { { {    0,   0,    0,   0 },  {  -74,  20,   11,  24 },  {  -63,  26,   28,  11 } } },  /* 25: S KICK B; attack 24, 114 */
    { { {    0,   0,    0,   0 },  {  -42,  22,   68,  20 },  {  -34,  18,   56,  16 } } },  /* 26: M KICK A, atca 160; attack 25, 140 */
    { { {    0,   0,    0,   0 },  {  -94,  84,   60,  12 },  {    0,   0,    0,   0 } } },  /* 27: M KICK B; attack 26 */
    { { {    0,   0,    0,   0 },  {  -46,  18,   84,  52 },  {  -60,  18,   70,  36 } } },  /* 28: L KICK A; attack 27 */
    { { {    0,   0,    0,   0 },  {  -34,  16,  102,  20 },  {    0,   0,    0,   0 } } },  /* 29: L KICK A; attack 28 */
    { { {    0,   0,    0,   0 },  {  -66,  28,   50,  14 },  {  -48,  28,   56,  14 } } },  /* 30: L PUNCH B; attack 29 */
    { { {    0,   0,    0,   0 },  {  -49,  22,   50,  12 },  {    0,   0,    0,   0 } } },  /* 31: L PUNCH B; attack 30 */
    { { {    0,   0,    0,   0 },  {  -46,  18,   64,  14 },  {    0,   0,    0,   0 } } },  /* 32: M KICK A, atca 160, saca 88 */
    { { {    0,   0,    0,   0 },  {  -76,  32,   36,   6 },  {  -50,  32,   33,   6 } } },  /* 33: KAGAMI P A; attack 32 */
    { { {    0,   0,    0,   0 },  {  -60,  32,   36,   8 },  {    0,   0,    0,   0 } } },  /* 34: KAGAMI P A */
    { { {    0,   0,    0,   0 },  {  -59,  21,   80,  29 },  {  -45,  17,   67,  26 } } },  /* 35: KAGAMI P A; attack 33 */
    { { {    0,   0,    0,   0 },  {  -52,  14,   86,  14 },  {  -44,  14,   78,  14 } } },  /* 36: KAGAMI P A; attack 34 */
    { { {    0,   0,    0,   0 },  {  -85,  50,    8,   8 },  {  -64,  50,   12,   7 } } },  /* 37: KAGAMI K A; attack 35 */
    { { {    0,   0,    0,   0 },  {  -70,  54,   10,   8 },  {    0,   0,    0,   0 } } },  /* 38: KAGAMI K A */
    { { {    0,   0,    0,   0 },  {  -60,  50,   74,  11 },  {    0,   0,    0,   0 } } },  /* 39: V JUMP P S A */
    { { {    0,   0,    0,   0 },  {  -81,  39,   69,  14 },  {  -42,  32,   73,  12 } } },  /* 40: V JUMP P S A; attack 36 */
    { { {    0,   0,    0,   0 },  {  -75,  30,   46,  24 },  {  -45,  23,   61,  14 } } },  /* 41: V JUMP P L A, atca 159; attack 39, 133 */
    { { {    0,   0,    0,   0 },  {  -88,  32,   45,  17 },  {  -56,  43,   48,  11 } } },  /* 42: V JUMP K S A; attack 43 */
    { { {    0,   0,    0,   0 },  {  -74,  24,   48,  15 },  {  -51,  29,   48,  10 } } },  /* 43: V JUMP K S A, V JUMP K M A; attack 43, 107 */
    { { {    0,   0,    0,   0 },  {  -72,  17,   28,  20 },  {  -55,  17,   46,  21 } } },  /* 44: F JUMP P S A; attack 40 */
    { { {    0,   0,    0,   0 },  {  -64,  16,   41,  13 },  {    0,   0,    0,   0 } } },  /* 45: F JUMP P S A, F JUMP P M A; attack 38 */
    { { {    0,   0,    0,   0 },  {  -76,  26,   48,   9 },  {  -49,  26,   51,   5 } } },  /* 46: not used by a script */
    { { {    0,   0,    0,   0 },  {  -87,  30,   78,  22 },  {  -58,  23,   69,  17 } } },  /* 47: UP P GUARD P S; attack 48 */
    { { {    0,   0,    0,   0 },  {  -52,  22,   42,  18 },  {  -40,  20,   34,  16 } } },  /* 48: L KICK A, ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 6 S +2; attack 49, 58, 63, 66 ... */
    { { {  -56,  44,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 49: ATTACK 3 S (Att_CHOUCHUURENGEKI), super art Att_PL07_SA2 (command slot 17); attack 50, 52 */
    { { {    0,   0,    0,   0 },  {  -61,  46,   60,  37 },  {  -60,  24,   97,  10 } } },  /* 50: not used by a script */
    { { {    0,   0,    0,   0 },  {  -64,  12,   42,  39 },  {  -49,  18,   67,   9 } } },  /* 51: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 6 S, ATTACK 1 M (Att_SHOURYUUKEN) +1; attack 59, 95 */
    { { {    0,   0,    0,   0 },  {  -36,  20,   88,  45 },  {  -57,  18,   53,  60 } } },  /* 52: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 6 S, ATTACK 1 M (Att_SHOURYUUKEN); attack 61, 64, 96 */
    { { {    0,   0,    0,   0 },  {  -35,  17,   74,  46 },  {  -55,  20,   63,  50 } } },  /* 53: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 6 S, ATTACK 1 M (Att_SHOURYUUKEN); attack 61, 64, 68, 97 */
    { { {    0,   0,    0,   0 },  {  -60,  18,   34,  48 },  {    0,   0,    0,   0 } } },  /* 54: ATTACK 1 S (Att_SHOURYUUKEN), ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN); attack 62, 65, 68 */
    { { {  -34,   6,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 55: M PUNCH A, M PUNCH B, L PUNCH A +2; attack 70 */
    { { {    0,   0,    0,   0 },  { -100,  34,   70,  28 },  {  -67,  53,   61,  11 } } },  /* 56: L KICK B, atca 161, OKIAGARI P S; attack 72, 141 */
    { { {    0,   0,    0,   0 },  {  -72,  23,   73,  20 },  {  -52,  36,   62,  13 } } },  /* 57: L KICK B, atca 161, OKIAGARI P S; attack 72 */
    { { { -110,  95,   36,  62 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 58: not used by a script */
    { { {    0,   0,    0,   0 },  {  -84,  13,   69,  16 },  {  -75,  31,   58,  11 } } },  /* 59: L PUNCH B; attack 75 */
    { { {    0,   0,    0,   0 },  {  -83,  23,   55,  40 },  {  -60,  50,   65,  14 } } },  /* 60: not used by a script */
    { { {    0,   0,    0,   0 },  {  -93,  31,   28,  35 },  {  -62,  48,   42,  20 } } },  /* 61: not used by a script */
    { { {    0,   0,    0,   0 },  {  -73,  47,    6,  22 },  {  -47,  29,   28,  15 } } },  /* 62: not used by a script */
    { { {    0,   0,    0,   0 },  {  -58,  44,   45,  45 },  {  -59,  33,   37,  17 } } },  /* 63: not used by a script */
    { { {    0,   0,    0,   0 },  {  -59,  36,   52,  33 },  {    0,   0,    0,   0 } } },  /* 64: not used by a script */
    { { {    0,   0,    0,   0 },  {  -92,  40,   12,  26 },  {  -60,  35,   28,  21 } } },  /* 65: ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2), ATTACK 2 L (Att_PL07_AT2); attack 81 */
    { { {    0,   0,    0,   0 },  {  -82,  42,   13,  29 },  {  -59,  33,   29,  25 } } },  /* 66: ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2), ATTACK 2 L (Att_PL07_AT2); attack 82, 89, 90 */
    { { {    0,   0,    0,   0 },  { -166,  86,   21,  72 },  {  -81,  56,   48,  18 } } },  /* 67: super art Att_PL07_SA2 (command slot 17); attack 83, 84, 85, 86 ... */
    { { {    0,   0,    0,   0 },  { -174,  88,   47,  28 },  {    0,   0,    0,   0 } } },  /* 68: super art Att_PL07_SA2 (command slot 17); attack 88 */
    { { {    0,   0,    0,   0 },  { -182,  31,   47,  25 },  { -105,  27,   48,  34 } } },  /* 69: super art Att_PL07_SA2 (command slot 17); attack 88 */
    { { {    0,   0,    0,   0 },  { -187,  31,   48,  24 },  { -103,  24,   48,  32 } } },  /* 70: super art Att_PL07_SA2 (command slot 17); attack 88 */
    { { {    0,   0,    0,   0 },  { -202,  22,   52,  12 },  { -101,  21,   48,  22 } } },  /* 71: not used by a script */
    { { {    0,   0,    0,   0 },  { -206,  16,   52,  10 },  {  -99,  18,   48,  18 } } },  /* 72: not used by a script */
    { { {    0,   0,    0,   0 },  {  -73,  44,    0,   6 },  {    0,   0,    0,   0 } } },  /* 73: not used by a script */
    { { {  -40,  40,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 74: ATTACK 4 S (Att_PL07_AT1), ATTACK 4 M (Att_PL07_AT1), ATTACK 4 L (Att_PL07_AT1); attack 98, 99, 101 */
    { { {    0,   0,    0,   0 },  {  -84,  70,    0,  13 },  {  -47,  33,   13,   8 } } },  /* 75: KAGAMI K A; attack 103 */
    { { {    0,   0,    0,   0 },  {  -60,  17,   53,  16 },  {  -42,  30,   64,  12 } } },  /* 76: V JUMP P L A, atca 159 */
    { { {    0,   0,    0,   0 },  {  -52,  14,   61,  31 },  {  -17,  24,   52,  30 } } },  /* 77: not used by a script */
    { { {  -32,  24,   50,  38 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 78: V JUMP P L A, V JUMP P M A; attack 70 */
    { { {    0,   0,    0,   0 },  {  -81,  19,   34,  17 },  {  -62,  43,   37,   8 } } },  /* 79: KAGAMI P A; attack 108 */
    { { {    0,   0,    0,   0 },  {  -88,  80,   58,  12 },  { -114,  27,   55,  23 } } },  /* 80: ATTACK 5 S (Att_CHOUCHUURENGEKI), ATTACK 5 M (Att_CHOUCHUURENGEKI), ATTACK 5 L (Att_CHOUCHUURENGEKI); attack 77, 78, 79, 80 ... */
    { { {    0,   0,    0,   0 },  { -108,  44,    0,   8 },  {  -64,  50,    0,  15 } } },  /* 81: ATTACK 5 SP; attack 112 */
    { { {    0,   0,    0,   0 },  {  -90,  32,   44,  18 },  {  -58,  42,   47,  12 } } },  /* 82: V JUMP K M A; attack 106 */
    { { {    0,   0,    0,   0 },  {  -83,  24,   71,  18 },  {  -59,  44,   72,   9 } } },  /* 83: V JUMP P M A; attack 37 */
    { { {    0,   0,    0,   0 },  {  -67,  25,   71,  18 },  {  -42,  28,   74,   9 } } },  /* 84: V JUMP P M A; attack 38 */
    { { {    0,   0,    0,   0 },  {  -80,  28,   43,  25 },  {  -52,  50,   45,  14 } } },  /* 85: not used by a script */
    { { {    0,   0,    0,   0 },  {  -75,  21,   29,  20 },  {  -58,  23,   46,  19 } } },  /* 86: F JUMP P M A; attack 37 */
    { { {    0,   0,    0,   0 },  {  -58,  14,   45,  18 },  {  -44,  34,   49,   7 } } },  /* 87: S KICK A, saca 84, saca 85 +1; attack 22, 134 */
    { { {  -38,  10,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 88: not used by a script */
    { { {    0,   0,    0,   0 },  {  -66,  18,   36,  48 },  {    0,   0,    0,   0 } } },  /* 89: ATTACK 1 S (Att_SHOURYUUKEN); attack 62 */
    { { {    0,   0,    0,   0 },  {  -71,  18,   37,  48 },  {    0,   0,    0,   0 } } },  /* 90: ATTACK 1 S (Att_SHOURYUUKEN); attack 62 */
    { { {    0,   0,    0,   0 },  {  -78,  18,   38,  48 },  {    0,   0,    0,   0 } } },  /* 91: ATTACK 1 S (Att_SHOURYUUKEN); attack 62 */
    { { {    0,   0,    0,   0 },  {  -84,  18,   40,  48 },  {    0,   0,    0,   0 } } },  /* 92: ATTACK 1 S (Att_SHOURYUUKEN); attack 62 */
    { { {    0,   0,    0,   0 },  {  -91,  18,   42,  48 },  {    0,   0,    0,   0 } } },  /* 93: ATTACK 1 S (Att_SHOURYUUKEN); attack 62 */
    { { {    0,   0,    0,   0 },  {  -60,  18,   37,  48 },  {    0,   0,    0,   0 } } },  /* 94: ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN); attack 65, 68 */
    { { {    0,   0,    0,   0 },  {  -63,  18,   38,  48 },  {    0,   0,    0,   0 } } },  /* 95: ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN); attack 65, 68 */
    { { {    0,   0,    0,   0 },  {  -68,  18,   40,  48 },  {    0,   0,    0,   0 } } },  /* 96: ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN); attack 65, 68 */
    { { {    0,   0,    0,   0 },  {  -74,  18,   43,  48 },  {    0,   0,    0,   0 } } },  /* 97: ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN); attack 65, 68 */
    { { {    0,   0,    0,   0 },  {  -80,  18,   48,  48 },  {    0,   0,    0,   0 } } },  /* 98: ATTACK 1 M (Att_SHOURYUUKEN), ATTACK 1 L (Att_SHOURYUUKEN); attack 65, 68 */
    { { {  -53,  28,   41,  52 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 99: F JUMP P M A; attack 70 */
    { { {    0,   0,    0,   0 },  {  -66,  22,   24,  20 },  {  -56,  23,   39,  19 } } },  /* 100: saca 76; attack 115 */
    { { {    0,   0,    0,   0 },  {  -62,  16,   38,  13 },  {    0,   0,    0,   0 } } },  /* 101: saca 76; attack 116 */
    { { {    0,   0,    0,   0 },  {  -49,  19,   77,  28 },  {  -42,  18,   61,  23 } } },  /* 102: saca 92; attack 117 */
    { { {    0,   0,    0,   0 },  {  -71,  30,   36,  26 },  {  -46,  31,   42,  16 } } },  /* 103: saca 92; attack 118 */
    { { {    0,   0,    0,   0 },  {  -54,  24,    8,  22 },  {  -37,  20,   23,  24 } } },  /* 104: saca 92; attack 119 */
    { { {    0,   0,    0,   0 },  {  -65,  33,   37,  30 },  {  -50,  37,   52,  19 } } },  /* 105: saca 84, saca 85, saca 86; attack 120 */
    { { {    0,   0,    0,   0 },  {  -60,  47,   38,  27 },  {    0,   0,    0,   0 } } },  /* 106: saca 84, saca 85, saca 86; attack 120 */
    { { {    0,   0,    0,   0 },  { -100,  34,   59,  35 },  {  -72,  55,   51,  18 } } },  /* 107: saca 84, saca 85, saca 86; attack 121 */
    { { {    0,   0,    0,   0 },  {  -80,  23,   66,  28 },  {  -57,  41,   55,  21 } } },  /* 108: saca 84, saca 85, saca 86; attack 121 */
    { { {    0,   0,    0,   0 },  {  -49,  24,   60,  20 },  {  -42,  18,   43,  17 } } },  /* 109: saca 88; attack 122 */
    { { {    0,   0,    0,   0 },  {  -44,  24,   62,  50 },  {  -57,  36,   48,  37 } } },  /* 110: saca 84, saca 85, saca 86; attack 124 */
    { { {    0,   0,    0,   0 },  {  -47,  26,   62,  44 },  {    0,   0,    0,   0 } } },  /* 111: saca 84, saca 85, saca 86; attack 125 */
    { { {    0,   0,    0,   0 },  {  -36,  22,   79,  40 },  {  -57,  21,   64,  55 } } },  /* 112: ATTACK 1 L (Att_SHOURYUUKEN); attack 60 */
    { { {    0,   0,    0,   0 },  {  -36,  22,   79,  36 },  {  -55,  19,   64,  51 } } },  /* 113: ATTACK 1 L (Att_SHOURYUUKEN); attack 67 */
    { { {  -58,  46,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 114: ATTACK 3 M (Att_CHOUCHUURENGEKI); attack 50 */
    { { {  -60,  48,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 115: ATTACK 3 L (Att_CHOUCHUURENGEKI); attack 50 */
};

const CAUGHT_BOX ibuki_cau_box[13] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -28,   56,    0,   16 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +113 */
    { {  -32,   60,    0,    8 } },  /* 2: DASH TOBINOKI, KAGAMU, KAGAMI KAMAE +35 */
    { {  -25,   48,   44,   48 } },  /* 3: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +42 */
    { {  -30,   60,    0,   16 } },  /* 4: DASH HUMIKOMI, CATCH 5, DASH TOBINOKI +2 */
    { {  -38,   38,    0,   16 } },  /* 5: ATTACK 3 S (Att_CHOUCHUURENGEKI), ATTACK 3 M (Att_CHOUCHUURENGEKI), ATTACK 3 L (Att_CHOUCHUURENGEKI) +1 */
    { {  -15,   40,   66,   17 } },  /* 6: AIR S, AIR M, AIR L +47 */
    { {  -28,   28,    0,    8 } },  /* 7: not used by a script */
    { {  -25,   48,   64,   48 } },  /* 8: air Att_PL07_AT3 (command slot 37), saca 65, saca 66 +11 */
    { {  -36,   44,   64,   22 } },  /* 9: DASH TOBINOKI, ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2) +1 */
    { {  -30,   60,    0,   16 } },  /* 10: PIYO */
    { {  -36,   64,    0,    8 } },  /* 11: KAGAMI P A, KAGAMI K A */
    { {  -46,   58,    0,   16 } },  /* 12: saca 84, saca 85, saca 86 +3 */
};

const HOSEI_BOX ibuki_hos_box[14] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -28,   56,    0,   80 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +113 */
    { {  -28,   56,    0,   58 } },  /* 2: DASH TOBINOKI, KAGAMU, KAGAMI KAMAE +49 */
    { {  -24,   48,   44,   48 } },  /* 3: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +43 */
    { {  -30,   60,    0,   76 } },  /* 4: DASH HUMIKOMI, CATCH 5, DASH TOBINOKI +2 */
    { {  -22,   44,   28,   36 } },  /* 5: L PUNCH B */
    { {  -32,   64,    0,   80 } },  /* 6: ATTACK 3 S (Att_CHOUCHUURENGEKI), ATTACK 3 M (Att_CHOUCHUURENGEKI), ATTACK 3 L (Att_CHOUCHUURENGEKI) +1 */
    { {  -15,   40,   66,   17 } },  /* 7: AIR S, AIR M, AIR L +47 */
    { {  -28,   56,    0,   56 } },  /* 8: not used by a script */
    { {  -32,   61,   21,   58 } },  /* 9: ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2), ATTACK 2 L (Att_PL07_AT2) */
    { {  -25,   48,   64,   53 } },  /* 10: air Att_PL07_AT3 (command slot 37), saca 65, saca 66 +11 */
    { {  -32,   64,   14,   82 } },  /* 11: DASH TOBINOKI, ATTACK 2 S (Att_PL07_AT2), ATTACK 2 M (Att_PL07_AT2) +1 */
    { {  -30,   60,    0,   62 } },  /* 12: PIYO */
    { {  -28,   56,    0,   30 } },  /* 13: NEKOROBI S */
};
