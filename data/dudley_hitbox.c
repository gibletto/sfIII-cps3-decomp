/*
 * DUDLEY_HITBOX.C  Dudley's hit boxes
 *
 * Each of Dudley's animation frames names a row of dudley_hit_ix_table (a frame line's hit field).
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
 * rows of dudley_catt_table dealt through it. Row 0 of a box table is no box.
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

const HIT_IX dudley_hit_ix_table[142] = {
    /* boix  atix  cuix  hoix */
    {    0,    0,    0,    0 },  /* 0: OKIAGARI, OKIAGARI F, OKIAGARI B +19 */
    {    1,    0,    1,    1 },  /* 1: KAMAE, HURIMUKI, FRONT WALK +99 */
    {    2,    0,    2,    1 },  /* 2: HANASARE, Att_HADOUKEN (command slot 24) */
    {    0,    0,    0,    0 },  /* 3: not used by a script */
    {    3,    0,    3,   20 },  /* 4: DASH HUMIKOMI, ATTACK 3 S (Att_HADOUKEN2), Att_CHOUCHUURENGEKI (command slot 26) */
    {    5,    0,    1,    1 },  /* 5: L KICK C */
    {   12,   35,    1,    1 },  /* 6: L KICK C */
    {    4,   36,    1,    1 },  /* 7: L KICK C */
    {   77,   57,    8,    5 },  /* 8: V JUMP K L A */
    {    8,    0,    6,    3 },  /* 9: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +29 */
    {    0,    0,    0,    5 },  /* 10: AIR S, AIR M, AIR L +9 */
    {   10,    0,    8,    5 },  /* 11: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +24 */
    {    7,   33,    0,    0 },  /* 12: saca 69, saca 70, saca 71 */
    {    6,    0,    1,   11 },  /* 13: saca 69 */
    {    9,    0,    1,   11 },  /* 14: saca 69 */
    {   14,    1,    1,    1 },  /* 15: S PUNCH A, atca 163, saca 61 +1 */
    {   15,    2,    1,    1 },  /* 16: M PUNCH A, atca 160, atca 163 +5 */
    {   16,    3,    1,    1 },  /* 17: S KICK A */
    {   16,    0,    1,    1 },  /* 18: S KICK A */
    {   17,    0,    1,    1 },  /* 19: M KICK A, atca 156, atca 157 +4 */
    {   18,    4,    1,    1 },  /* 20: M KICK A, atca 156, atca 157 +4 */
    {   68,    5,    1,    1 },  /* 21: M KICK A, atca 156, atca 157 +4 */
    {   68,    0,    1,    1 },  /* 22: M KICK A, atca 156, atca 157 +4 */
    {   19,    0,   10,    1 },  /* 23: S PUNCH C */
    {   20,    6,   10,    1 },  /* 24: S PUNCH C */
    {   15,    0,    1,    1 },  /* 25: M PUNCH A, atca 160, atca 163 +3 */
    {   22,    0,    1,    1 },  /* 26: L PUNCH A, L PUNCH C, M KICK C +9 */
    {   23,    7,    1,    4 },  /* 27: M KICK C */
    {   23,    0,    1,    4 },  /* 28: M KICK C */
    {   24,    8,    1,    1 },  /* 29: L KICK A, atca 162, atca 165 */
    {   25,    9,    1,    1 },  /* 30: L KICK A, atca 162, atca 165 +1 */
    {   26,   10,    1,    1 },  /* 31: L KICK A, atca 162, atca 165 +4 */
    {   26,    0,    1,    1 },  /* 32: L KICK A, atca 162, atca 165 +4 */
    {   27,   11,    1,    1 },  /* 33: L PUNCH A, L PUNCH C, atca 158 +2 */
    {   27,    0,    1,    1 },  /* 34: L PUNCH A, L PUNCH C, atca 158 +2 */
    {   28,   12,    7,    3 },  /* 35: KAGAMI P A */
    {   29,    0,    6,    3 },  /* 36: KAGAMI P A */
    {   30,   13,    6,    3 },  /* 37: KAGAMI P A */
    {   30,    0,    6,    3 },  /* 38: KAGAMI P A */
    {   31,    0,    6,    1 },  /* 39: KAGAMI P A, atca 166, ATTACK 3 S (Att_HADOUKEN2) +1 */
    {   32,   14,    6,    1 },  /* 40: KAGAMI P A, atca 166, ATTACK 3 S (Att_HADOUKEN2) +1 */
    {   33,   15,    6,    1 },  /* 41: KAGAMI P A, atca 166, ATTACK 3 S (Att_HADOUKEN2) +1 */
    {   34,    0,    6,    1 },  /* 42: KAGAMI P A, atca 166, ATTACK 3 S (Att_HADOUKEN2) +1 */
    {   35,    0,    6,    1 },  /* 43: KAGAMI P A, atca 166, ATTACK 3 S (Att_HADOUKEN2) +2 */
    {   36,   16,    7,    3 },  /* 44: KAGAMI K A */
    {   36,    0,    7,    3 },  /* 45: KAGAMI K A */
    {   37,    0,    6,    3 },  /* 46: KAGAMI K A, UP P GUARD K S */
    {   38,   17,    6,    3 },  /* 47: KAGAMI K A, UP P GUARD K S */
    {   38,    0,    6,    3 },  /* 48: KAGAMI K A, UP P GUARD K S */
    {   44,    0,    6,    3 },  /* 49: ATTACK 1 M (Att_SENPUUKYAKU) */
    {   40,    0,    6,    3 },  /* 50: KAGAMI K A */
    {   41,    0,   13,    3 },  /* 51: KAGAMI K A */
    {    5,    0,    1,    1 },  /* 52: L KICK C */
    {   43,   18,   13,    3 },  /* 53: KAGAMI K A */
    {   43,    0,   13,    3 },  /* 54: KAGAMI K A */
    {   83,   64,    8,    5 },  /* 55: saca 79 */
    {   45,   19,    8,    5 },  /* 56: V JUMP P S A, F JUMP P S A, atca 168 */
    {   45,    0,    8,    5 },  /* 57: V JUMP P S A, F JUMP P S A, atca 168 */
    {   46,   20,    8,    5 },  /* 58: V JUMP P M A, F JUMP P M A */
    {   46,    0,    8,    5 },  /* 59: V JUMP P M A, F JUMP P M A */
    {   47,    0,   14,    5 },  /* 60: V JUMP P L A, F JUMP P L A */
    {   48,   21,    8,    5 },  /* 61: V JUMP P L A, F JUMP P L A */
    {   48,    0,    8,    5 },  /* 62: V JUMP P L A, F JUMP P L A */
    {   75,   22,    8,    5 },  /* 63: V JUMP K S A, F JUMP K S A */
    {   49,    0,    8,    5 },  /* 64: V JUMP K L A, F JUMP K L A */
    {   50,   23,    8,    5 },  /* 65: F JUMP K L A */
    {   50,    0,    8,    5 },  /* 66: V JUMP K L A, F JUMP K L A */
    {    1,   34,    1,    1 },  /* 67: ATTACK 1 L (Att_SENPUUKYAKU) */
    {   11,    0,    8,    5 },  /* 68: not used by a script */
    {    0,    0,    0,    3 },  /* 69: TATAKI S, OKIAGARI, OKIAGARI F +16 */
    {   53,    0,    6,    3 },  /* 70: not used by a script */
    {   54,    0,    0,    0 },  /* 71: not used by a script */
    {   55,    0,   16,   15 },  /* 72: FUSHIN P S */
    {   55,   24,   16,   15 },  /* 73: FUSHIN P S */
    {   56,    0,   17,   16 },  /* 74: TOUKETSU A, OKIAGARI P S */
    {   57,    0,   18,   17 },  /* 75: not used by a script */
    {   58,   25,   18,   17 },  /* 76: OKIAGARI P S */
    {    1,   26,    1,    1 },  /* 77: M PUNCH A, atca 144, atca 146 */
    {   21,   28,    6,    3 },  /* 78: ATTACK 1 S (Att_SENPUUKYAKU) */
    {   13,   27,    8,    5 },  /* 79: ATTACK 1 S (Att_SENPUUKYAKU), ATTACK 1 M (Att_SENPUUKYAKU), ATTACK 1 L (Att_SENPUUKYAKU) */
    {   39,   29,   22,    1 },  /* 80: ATTACK 1 M (Att_SENPUUKYAKU), super art Att_SHOURYUUREPPA (command slot 16) */
    {   11,   30,    8,    5 },  /* 81: ATTACK 1 M (Att_SENPUUKYAKU) */
    {    1,   31,   22,    1 },  /* 82: ATTACK 1 L (Att_SENPUUKYAKU) */
    {   11,   32,    8,    5 },  /* 83: ATTACK 1 L (Att_SENPUUKYAKU) */
    {   10,    0,    8,    5 },  /* 84: ATTACK 1 S (Att_SENPUUKYAKU), ATTACK 1 M (Att_SENPUUKYAKU), ATTACK 1 L (Att_SENPUUKYAKU) +1 */
    {   10,   34,    1,    1 },  /* 85: not used by a script */
    {   59,    0,    1,   25 },  /* 86: ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    {   60,    0,    1,   27 },  /* 87: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    {   61,   37,    1,    1 },  /* 88: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    {   61,   38,    1,    1 },  /* 89: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    {   61,   39,    1,    1 },  /* 90: ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    {   61,   40,    1,    1 },  /* 91: ATTACK 5 L (Att_SENPUUKYAKU) */
    {   61,   41,    1,    1 },  /* 92: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    {   61,   42,    1,    1 },  /* 93: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    {   62,    0,    1,    1 },  /* 94: not used by a script */
    {   63,    0,    1,    1 },  /* 95: not used by a script */
    {   64,    0,    1,    1 },  /* 96: not used by a script */
    {    0,   43,    1,    3 },  /* 97: ATTACK 2 S (Att_CHOUCHUURENGEKI) */
    {   66,   44,    1,    3 },  /* 98: ATTACK 2 S (Att_CHOUCHUURENGEKI) */
    {   66,   45,    1,    3 },  /* 99: ATTACK 2 S (Att_CHOUCHUURENGEKI) */
    {   66,   46,    1,    3 },  /* 100: ATTACK 2 S (Att_CHOUCHUURENGEKI) */
    {   85,   47,    1,    3 },  /* 101: ATTACK 2 S (Att_CHOUCHUURENGEKI) */
    {   85,    0,    1,    3 },  /* 102: ATTACK 2 S (Att_CHOUCHUURENGEKI) */
    {   67,    0,   20,   19 },  /* 103: ATTACK 3 S (Att_HADOUKEN2), Att_CHOUCHUURENGEKI (command slot 26), saca 74 +10 */
    {   67,    0,   19,   13 },  /* 104: ATTACK 3 S (Att_HADOUKEN2) */
    {   67,   48,   19,   13 },  /* 105: ATTACK 3 S (Att_HADOUKEN2) */
    {   69,   49,    1,   13 },  /* 106: ATTACK 3 S (Att_HADOUKEN2) */
    {   70,   50,    1,   13 },  /* 107: ATTACK 3 S (Att_HADOUKEN2) */
    {   70,   51,    1,   13 },  /* 108: not used by a script */
    {   70,    0,    1,   13 },  /* 109: ATTACK 3 S (Att_HADOUKEN2) */
    {   71,    0,   19,   13 },  /* 110: ATTACK 3 S (Att_HADOUKEN2) */
    {   72,    0,   19,   13 },  /* 111: ATTACK 3 S (Att_HADOUKEN2) */
    {   72,   52,   19,   13 },  /* 112: ATTACK 3 S (Att_HADOUKEN2) */
    {   73,   53,    1,   13 },  /* 113: ATTACK 3 S (Att_HADOUKEN2) */
    {   73,   54,    1,   13 },  /* 114: not used by a script */
    {   73,    0,    1,   13 },  /* 115: ATTACK 3 S (Att_HADOUKEN2) */
    {    1,   55,    6,   12 },  /* 116: super art Att_SHOURYUUREPPA (command slot 16) */
    {   10,   56,    8,    5 },  /* 117: super art Att_SHOURYUUREPPA (command slot 16) */
    {    1,    0,    1,   21 },  /* 118: not used by a script */
    {   10,   58,    0,    1 },  /* 119: super art Att_SHOURYUUREPPA (command slot 16) */
    {   74,    0,   21,   24 },  /* 120: AIR S, AIR M, AIR L +39 */
    {   76,   59,    8,    5 },  /* 121: V JUMP K M A, F JUMP K M A */
    {    0,    0,    0,    1 },  /* 122: ATTACK 2 S (Att_CHOUCHUURENGEKI), ATTACK 3 S (Att_HADOUKEN2), super art Att_SHOURYUUREPPA (command slot 16) */
    {    0,    0,    0,    5 },  /* 123: not used by a script */
    {    0,    0,    0,    1 },  /* 124: not used by a script */
    {    0,   56,    8,    5 },  /* 125: super art Att_SHOURYUUREPPA (command slot 16) */
    {    0,   29,    0,    1 },  /* 126: super art Att_SHOURYUUREPPA (command slot 16) */
    {    1,   60,    1,    1 },  /* 127: L PUNCH A, L PUNCH C */
    {   78,   61,    1,    1 },  /* 128: saca 73 */
    {   78,    0,    1,    1 },  /* 129: saca 73 */
    {   79,   62,    1,    1 },  /* 130: saca 74 */
    {   80,   63,    1,    1 },  /* 131: saca 74 */
    {   80,    0,    1,    1 },  /* 132: saca 74 */
    {   81,    0,    1,   10 },  /* 133: PIYO */
    {   82,    0,    1,   10 },  /* 134: PIYO */
    {   42,   65,    8,    5 },  /* 135: super art Att_SHOURYUUREPPA (command slot 16) */
    {    0,    0,    0,   26 },  /* 136: NEKOROBI S */
    {   84,    0,    9,   14 },  /* 137: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    {    8,    0,    7,    3 },  /* 138: KAGAMI P A, KAGAMI K A */
    {    1,    0,    0,    1 },  /* 139: HANASARE */
    {    8,    0,    0,    3 },  /* 140: HANASARE */
    {    1,    0,    1,    0 },  /* 141: LOSE SONABA */
};

const BODY_BOX dudley_body_box[86] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {  -21,  31,   88,  17 },  {  -29,  60,   85,  12 },  {  -29,  60,   40,  45 },  {  -33,  68,    0,  40 },  {    0,   0,    0,   0 } } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +99 */
    { { {  -32,  61,   67,  39 },  {  -26,  55,   57,  10 },  {  -26,  55,   38,  19 },  {  -32,  70,    0,  38 },  {    0,   0,    0,   0 } } },  /* 2: HANASARE, Att_HADOUKEN (command slot 24) */
    { { {  -52,  19,   56,  26 },  {  -31,  54,   56,  26 },  {  -33,  69,   33,  21 },  {  -33,  68,    0,  32 },  {    0,   0,    0,   0 } } },  /* 3: DASH HUMIKOMI, ATTACK 3 S (Att_HADOUKEN2), Att_CHOUCHUURENGEKI (command slot 26) */
    { { {  -33,  51,   80,  15 },  {  -52,  74,   59,  19 },  {  -40,  62,   36,  21 },  {  -40,  85,    0,  34 },  {  -65,  23,   20,  38 } } },  /* 4: L KICK C */
    { { {  -24,  39,   81,  15 },  {  -34,  55,   59,  20 },  {  -34,  55,   37,  20 },  {  -40,  81,    0,  34 },  {    0,   0,    0,   0 } } },  /* 5: L KICK C */
    { { {  -30,  30,   82,  18 },  {  -52,  66,   62,  28 },  {  -38,  60,   40,  30 },  {  -50,  90,    0,  38 },  {    0,   0,    0,   0 } } },  /* 6: saca 69 */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -38,  60,   40,  34 },  {  -50,  90,    0,  38 },  {    0,   0,    0,   0 } } },  /* 7: saca 69, saca 70, saca 71 */
    { { {  -21,  31,   59,  17 },  {  -39,  75,   49,  20 },  {  -38,  71,   29,  20 },  {  -43,  84,    0,  29 },  {    0,   0,    0,   0 } } },  /* 8: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +29 */
    { { {  -28,  30,   84,  18 },  {  -44,  70,   62,  26 },  {  -32,  64,   36,  24 },  {  -48,  92,    0,  36 },  {    0,   0,    0,   0 } } },  /* 9: saca 69 */
    { { {  -23,  42,   96,  16 },  {  -32,  64,   84,  23 },  {  -30,  59,   64,  18 },  {  -30,  60,   41,  21 },  {    0,   0,    0,   0 } } },  /* 10: JUMP JUNBI, SP JUMP JUNBI, JUMP FRONT +28 */
    { { {  -21,  33,  107,  41 },  {  -32,  61,   84,  24 },  {  -31,  59,   64,  20 },  {  -31,  59,   41,  23 },  {    0,   0,    0,   0 } } },  /* 11: ATTACK 1 M (Att_SENPUUKYAKU), ATTACK 1 L (Att_SENPUUKYAKU) */
    { { {  -35,  49,   81,  19 },  {  -45,  70,   59,  32 },  {  -40,  65,   34,  25 },  {  -40,  81,    0,  34 },  {    0,   0,    0,   0 } } },  /* 12: L KICK C */
    { { {   -8,  29,  100,  17 },  {  -24,  54,   84,  22 },  {  -33,  61,   64,  20 },  {  -36,  64,   41,  23 },  {    0,   0,    0,   0 } } },  /* 13: ATTACK 1 S (Att_SENPUUKYAKU), ATTACK 1 M (Att_SENPUUKYAKU), ATTACK 1 L (Att_SENPUUKYAKU) */
    { { {  -24,  26,   91,  16 },  {  -24,  52,   76,  23 },  {  -27,  54,   45,  29 },  {  -33,  68,    0,  43 },  {  -88,  63,   78,  21 } } },  /* 14: S PUNCH A, atca 163, saca 61 +1 */
    { { {  -24,  26,   91,  16 },  {  -29,  45,   73,  21 },  {  -33,  49,   41,  30 },  {  -39,  74,    0,  40 },  {  -94,  66,   74,  20 } } },  /* 15: M PUNCH A, atca 160, atca 163 +6 */
    { { {  -18,  34,   92,  17 },  {  -23,  48,   73,  18 },  {  -55,  80,   53,  20 },  {  -35,  71,    0,  53 },  {  -65,  43,   69,  27 } } },  /* 16: S KICK A */
    { { {  -40,  16,   80,  16 },  {  -43,  48,   72,  12 },  {  -32,  40,   40,  32 },  {  -36,  64,    0,  40 },  {    0,   0,    0,   0 } } },  /* 17: M KICK A, atca 156, atca 157 +4 */
    { { {  -50,  50,   96,  16 },  {  -56,  71,   83,  17 },  {  -59,  88,   48,  35 },  {  -36,  74,    0,  48 },  {  -81,  22,   65,  18 } } },  /* 18: M KICK A, atca 156, atca 157 +4 */
    { { {  -34,  37,   79,  13 },  {  -34,  52,   61,  19 },  {  -34,  61,   37,  22 },  {  -34,  81,    0,  35 },  {    0,   0,    0,   0 } } },  /* 19: S PUNCH C */
    { { {  -28,  40,   83,  13 },  {  -27,  56,   62,  22 },  {  -28,  69,   38,  22 },  {  -33,  86,    0,  37 },  {  -90,  63,   62,  22 } } },  /* 20: S PUNCH C */
    { { {  -66,  55,   59,  18 },  {  -65,  68,   45,  14 },  {  -64,  73,   25,  20 },  {  -62,  96,    0,  25 },  {    0,   0,    0,   0 } } },  /* 21: ATTACK 1 S (Att_SENPUUKYAKU) */
    { { {  -17,  35,   76,  16 },  {  -32,  68,   61,  22 },  {  -32,  68,   38,  21 },  {  -42,  88,    0,  37 },  {    0,   0,    0,   0 } } },  /* 22: L PUNCH A, L PUNCH C, M KICK C +9 */
    { { {  -35,  39,   81,  16 },  {  -24,  45,   65,  15 },  {  -53,  74,   46,  19 },  {  -40,  75,    0,  47 },  {  -72,  46,   63,  20 } } },  /* 23: M KICK C */
    { { {  -31,  39,   77,  22 },  {  -37,  67,   61,  21 },  {  -43,  73,   39,  22 },  {  -37,  77,    0,  39 },  {    0,   0,    0,   0 } } },  /* 24: L KICK A, atca 162, atca 165 */
    { { {  -31,  43,   81,  18 },  {  -25,  51,   64,  15 },  {  -53,  83,   46,  18 },  {  -37,  72,    0,  46 },  {  -72,  46,   65,  13 } } },  /* 25: L KICK A, atca 162, atca 165 +1 */
    { { {  -24,  34,   84,  18 },  {  -73, 103,   64,  20 },  {  -36,  67,   41,  23 },  {  -36,  72,    0,  40 },  {  -74,  50,   84,  21 } } },  /* 26: L KICK A, atca 162, atca 165 +4 */
    { { {  -30,  42,   83,  16 },  {  -80, 106,   52,  39 },  {  -24,  50,   38,  14 },  {  -36,  72,    0,  38 },  {  -91,  11,   61,  30 } } },  /* 27: L PUNCH A, L PUNCH C, atca 158 +2 */
    { { {  -29,  31,   69,  17 },  {  -40,  68,   53,  23 },  {  -37,  61,   33,  20 },  {  -42,  87,    0,  33 },  {  -83,  44,   39,  31 } } },  /* 28: KAGAMI P A */
    { { {  -29,  31,   69,  17 },  {  -40,  68,   53,  23 },  {  -37,  61,   33,  20 },  {  -42,  87,    0,  33 },  {    0,   0,    0,   0 } } },  /* 29: KAGAMI P A */
    { { {  -29,  31,   69,  17 },  {  -40,  68,   53,  23 },  {  -37,  61,   33,  20 },  {  -42,  87,    0,  33 },  {  -83,  44,   52,  27 } } },  /* 30: KAGAMI P A */
    { { {  -46,  31,   72,  17 },  {  -54,  68,   53,  23 },  {  -37,  61,   33,  20 },  {  -42,  87,    0,  33 },  {    0,   0,    0,   0 } } },  /* 31: KAGAMI P A, atca 166, ATTACK 3 S (Att_HADOUKEN2) +1 */
    { { {  -35,  31,   82,  17 },  {  -49,  67,   60,  26 },  {  -37,  61,   33,  27 },  {  -42,  87,    0,  33 },  {  -83,  46,   57,  29 } } },  /* 32: KAGAMI P A, atca 166, ATTACK 3 S (Att_HADOUKEN2) +1 */
    { { {  -30,  31,   89,  17 },  {  -45,  63,   60,  30 },  {  -37,  61,   33,  27 },  {  -42,  87,    0,  33 },  {  -79,  48,   76,  38 } } },  /* 33: KAGAMI P A, atca 166, ATTACK 3 S (Att_HADOUKEN2) +1 */
    { { {  -30,  31,   89,  17 },  {  -45,  63,   60,  30 },  {  -37,  61,   33,  27 },  {  -42,  87,    0,  33 },  {  -79,  48,   76,  38 } } },  /* 34: KAGAMI P A, atca 166, ATTACK 3 S (Att_HADOUKEN2) +1 */
    { { {  -30,  31,   89,  17 },  {  -45,  63,   60,  30 },  {  -37,  61,   33,  27 },  {  -42,  87,    0,  33 },  {    0,   0,    0,   0 } } },  /* 35: KAGAMI P A, atca 166, ATTACK 3 S (Att_HADOUKEN2) +2 */
    { { {  -21,  31,   67,  17 },  {  -39,  75,   49,  27 },  {  -38,  71,   29,  20 },  {  -43,  84,    0,  29 },  {  -88,  52,   17,  42 } } },  /* 36: KAGAMI K A */
    { { {  -22,  16,   56,  16 },  {  -40,  64,   50,  13 },  {  -35,  56,   32,  15 },  {  -38,  68,    0,  28 },  {    0,   0,    0,   0 } } },  /* 37: KAGAMI K A, UP P GUARD K S */
    { { {  -46,  31,   61,  17 },  {  -54,  76,   49,  22 },  {  -66,  99,   29,  28 },  {  -55,  96,    0,  29 },  {  -80,  37,   19,  25 } } },  /* 38: KAGAMI K A, UP P GUARD K S */
    { { {  -33,  42,   90,  18 },  {  -60,  90,   78,  24 },  {   -8,  48,   31,  47 },  {    0,  51,    0,  31 },  {    0,   0,    0,   0 } } },  /* 39: ATTACK 1 M (Att_SENPUUKYAKU), super art Att_SHOURYUUREPPA (command slot 16) */
    { { {  -32,  31,   67,  17 },  {  -39,  76,   49,  28 },  {  -39,  68,   29,  20 },  {  -40,  87,    0,  29 },  {    0,   0,    0,   0 } } },  /* 40: KAGAMI K A */
    { { {  -55,  31,   67,  17 },  {  -50,  66,   53,  24 },  {  -48,  80,   29,  24 },  {  -45,  87,    0,  29 },  {    0,   0,    0,   0 } } },  /* 41: KAGAMI K A */
    { { {  -24,  43,   99,  16 },  {  -32,  58,   84,  25 },  {  -30,  56,   64,  20 },  {  -29,  55,   41,  23 },  {    0,   0,    0,   0 } } },  /* 42: super art Att_SHOURYUUREPPA (command slot 16) */
    { { {  -61,  33,   30,  29 },  {  -40,  48,   35,  31 },  {  -75, 109,   23,  24 },  {  -48, 104,    0,  28 },  {  -87,  39,   16,  19 } } },  /* 43: KAGAMI K A */
    { { {  -31,  41,   80,  22 },  {  -28,  60,   60,  20 },  {  -12,  66,   29,  31 },  {   -4,  67,    0,  29 },  {    0,   0,    0,   0 } } },  /* 44: ATTACK 1 M (Att_SENPUUKYAKU) */
    { { {  -19,  28,  107,  16 },  {    0,   0,    0,   0 },  {  -29,  58,   79,  32 },  {  -26,  52,   50,  29 },  {  -80,  54,   82,  27 } } },  /* 45: V JUMP P S A, F JUMP P S A, atca 168 */
    { { {  -35,  43,  104,  16 },  {    0,   0,    0,   0 },  {  -31,  61,   79,  34 },  {  -28,  56,   42,  37 },  {  -86,  62,   83,  24 } } },  /* 46: V JUMP P M A, F JUMP P M A */
    { { {    8,  16,  104,  16 },  {    0,   0,    0,   0 },  {  -24,  48,   80,  32 },  {  -16,  32,   56,  56 },  {    0,   0,    0,   0 } } },  /* 47: V JUMP P L A, F JUMP P L A */
    { { {  -18,  37,  105,  15 },  {  -85, 114,   90,  17 },  {  -84, 113,   66,  24 },  {  -28,  56,   52,  14 },  {    0,   0,    0,   0 } } },  /* 48: V JUMP P L A, F JUMP P L A */
    { { {  -45,  42,   96,  16 },  {  -37,  71,   84,  23 },  {  -35,  79,   64,  18 },  {  -26,  78,   48,  16 },  {    0,   0,    0,   0 } } },  /* 49: V JUMP K L A, F JUMP K L A */
    { { {  -76,  50,   78,  15 },  {  -76,  72,   47,  31 },  {  -26,  79,   78,  27 },  {   -4,  57,   47,  31 },  {    0,   0,    0,   0 } } },  /* 50: F JUMP K L A, V JUMP K L A */
    { { {   -1,  16,   91,  16 },  {  -17,  56,   80,  12 },  {   -7,  40,   40,  40 },  {  -24,  53,    0,  38 },  {    0,   0,    0,   0 } } },  /* 51: not used by a script */
    { { {  -16,  16,   56,  16 },  {  -32,  64,   50,  13 },  {  -20,  39,   32,  15 },  {  -32,  68,    0,  28 },  {    0,   0,    0,   0 } } },  /* 52: not used by a script */
    { { {  -48,  16,   55,  16 },  {  -39,  45,   50,  22 },  {  -28,  56,   32,  15 },  {  -32,  68,    0,  28 },  {    0,   0,    0,   0 } } },  /* 53: not used by a script */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {  -25,  34,    0,  52 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 54: not used by a script */
    { { {   -1,  16,   99,  16 },  {  -19,  61,   82,  20 },  {  -12,  47,   56,  24 },  {  -17,  53,   12,  42 },  {    0,   0,    0,   0 } } },  /* 55: FUSHIN P S */
    { { {  -11,  16,   71,  16 },  {  -22,  56,   60,  16 },  {  -20,  50,   38,  20 },  {  -20,  53,    0,  36 },  {    0,   0,    0,   0 } } },  /* 56: TOUKETSU A, OKIAGARI P S */
    { { {  -63,  16,   67,  16 },  {  -78,  56,   63,  12 },  {  -75,  40,   33,  40 },  {  -75,  53,    0,  40 },  {    0,   0,    0,   0 } } },  /* 57: not used by a script */
    { { {  -43,  16,   57,  16 },  {  -55,  56,   59,  12 },  {  -37,  53,   33,  22 },  {  -23,  53,    0,  40 },  {    0,   0,    0,   0 } } },  /* 58: OKIAGARI P S */
    { { {  -33,  33,   71,  22 },  {  -42,  73,   65,  17 },  {  -42,  62,   50,  15 },  {  -42,  70,   35,  15 },  {    0,   0,    0,   0 } } },  /* 59: ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    { { {  -38,  34,   86,  17 },  {  -42,  62,   78,  14 },  {  -42,  74,   58,  20 },  {  -42,  78,    0,  58 },  {    0,   0,    0,   0 } } },  /* 60: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    { { {  -22,  16,   90,  16 },  {  -28,  50,   71,  20 },  {  -27,  46,   47,  24 },  {  -29,  52,    0,  47 },  {  -43,  14,   70,  23 } } },  /* 61: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    { { {    4,  16,   88,  14 },  {  -20,  46,   74,  16 },  {  -22,  36,   40,  32 },  {  -32,  60,    0,  38 },  {    0,   0,    0,   0 } } },  /* 62: not used by a script */
    { { {   -4,  16,   90,  14 },  {  -22,  48,   74,  16 },  {  -24,  36,   40,  32 },  {  -36,  62,    0,  38 },  {    0,   0,    0,   0 } } },  /* 63: not used by a script */
    { { {  -10,  16,   76,  14 },  {  -30,  50,   68,  16 },  {  -26,  36,   40,  26 },  {  -36,  62,    0,  38 },  {    0,   0,    0,   0 } } },  /* 64: not used by a script */
    { { {  -26,  16,   74,  14 },  {  -42,  56,   60,  14 },  {  -20,  34,   38,  20 },  {  -36,  72,    0,  36 },  {    0,   0,    0,   0 } } },  /* 65: not used by a script */
    { { {  -33,  36,   74,  17 },  {  -42,  74,   60,  14 },  {  -40,  75,   38,  22 },  {  -40,  79,    0,  38 },  {    0,   0,    0,   0 } } },  /* 66: ATTACK 2 S (Att_CHOUCHUURENGEKI) */
    { { {  -61,  26,   22,  20 },  {  -35,  19,   22,  20 },  {  -16,  36,   22,  20 },  {  -55, 102,    0,  22 },  {    0,   0,    0,   0 } } },  /* 67: ATTACK 3 S (Att_HADOUKEN2), Att_CHOUCHUURENGEKI (command slot 26), saca 74 +10 */
    { { {  -50,  50,   96,  16 },  {  -80,  95,   83,  16 },  {  -45,  74,   48,  35 },  {  -45,  85,    0,  48 },  {  -80,  46,   99,  25 } } },  /* 68: M KICK A, atca 156, atca 157 +4 */
    { { {   -9,  16,   71,  16 },  {  -30,  64,   62,  16 },  {  -19,  49,   41,  20 },  {  -25,  53,    0,  39 },  {    0,   0,    0,   0 } } },  /* 69: ATTACK 3 S (Att_HADOUKEN2) */
    { { {    8,  16,   79,  16 },  {  -20,  53,   69,  16 },  {  -17,  39,   36,  31 },  {  -30,  56,    0,  34 },  {    0,   0,    0,   0 } } },  /* 70: ATTACK 3 S (Att_HADOUKEN2) */
    { { {   12,  16,   59,  16 },  {  -18,  53,   55,  15 },  {  -17,  41,   38,  15 },  {  -35,  53,    0,  36 },  {    0,   0,    0,   0 } } },  /* 71: ATTACK 3 S (Att_HADOUKEN2) */
    { { {  -42,  16,   44,  16 },  {  -36,  54,   47,  19 },  {  -30,  48,   32,  13 },  {  -31,  57,    0,  30 },  {    0,   0,    0,   0 } } },  /* 72: ATTACK 3 S (Att_HADOUKEN2) */
    { { {  -30,  16,   74,  16 },  {  -37,  51,   65,  19 },  {  -24,  39,   41,  22 },  {  -32,  50,    0,  40 },  {    0,   0,    0,   0 } } },  /* 73: ATTACK 3 S (Att_HADOUKEN2) */
    { { {  -18,  47,   72,  17 },  {  -22,  55,   62,  18 },  {  -22,  55,   43,  17 },  {  -19,  49,   34,  14 },  {    0,   0,    0,   0 } } },  /* 74: AIR S, AIR M, AIR L +39 */
    { { {  -34,  42,  104,  16 },  {  -28,  57,   80,  32 },  {  -29,  58,   41,  39 },  {    0,   0,    0,   0 },  {  -56,  44,   75,  41 } } },  /* 75: V JUMP K S A, F JUMP K S A */
    { { {  -34,  42,  104,  16 },  {  -28,  57,   80,  32 },  {  -29,  58,   41,  39 },  {    0,   0,    0,   0 },  {  -49,  36,   62,  49 } } },  /* 76: V JUMP K M A, F JUMP K M A */
    { { {  -60,  34,   78,  15 },  {  -62,  58,   32,  46 },  {  -26,  79,   78,  27 },  {   -4,  57,   47,  31 },  {    0,   0,    0,   0 } } },  /* 77: V JUMP K L A */
    { { {  -22,  32,   83,  16 },  {  -45,  71,   52,  36 },  {  -49,  75,   38,  14 },  {  -65, 110,    0,  38 },  {  -88,  66,   62,  33 } } },  /* 78: saca 73 */
    { { {  -34,  33,   82,  17 },  {  -47,  67,   60,  29 },  {  -28,  61,   33,  27 },  {  -12,  68,    0,  33 },  {  -87,  55,   51,  32 } } },  /* 79: saca 74 */
    { { {  -30,  35,   89,  17 },  {  -50,  68,   60,  30 },  {  -50,  74,   33,  27 },  {  -50,  95,    0,  33 },  {  -81,  50,   72,  40 } } },  /* 80: saca 74 */
    { { {  -55,  31,   42,  18 },  {  -50,  64,   49,  31 },  {  -40,  67,   29,  24 },  {  -40,  85,    0,  29 },  {    0,   0,    0,   0 } } },  /* 81: PIYO */
    { { {  -55,  31,   50,  18 },  {  -50,  64,   57,  30 },  {  -40,  65,   29,  37 },  {  -40,  83,    0,  29 },  {    0,   0,    0,   0 } } },  /* 82: PIYO */
    { { {  -34,  42,  104,  16 },  {  -70,  96,   85,  27 },  {  -68,  94,   60,  25 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 83: saca 79 */
    { { {  -21,  31,   94,  17 },  {  -43,  74,   85,  14 },  {  -43,  74,   40,  45 },  {  -43,  74,    0,  40 },  {    0,   0,    0,   0 } } },  /* 84: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    { { {  -33,  36,   74,  17 },  {  -42,  74,   60,  14 },  {  -40,  75,   38,  22 },  {  -40,  79,    0,  38 },  {  -72,  28,   60,  14 } } },  /* 85: ATTACK 2 S (Att_CHOUCHUURENGEKI) */
};

const ATTACK_BOX dudley_att_box[66] = {
    /*     x    w     y    h          x    w     y    h          x    w     y    h */
    { { {    0,   0,    0,   0 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 0: no box */
    { { {    0,   0,    0,   0 },  {  -92,  20,   80,  17 },  {  -72,  47,   80,  17 } } },  /* 1: S PUNCH A, atca 163, saca 61 +1; attack 1, 65 */
    { { {    0,   0,    0,   0 },  { -106,  22,   76,  16 },  {  -84,  56,   76,  16 } } },  /* 2: M PUNCH A, atca 160, atca 163 +5; attack 4, 66, 80, 84 */
    { { {    0,   0,    0,   0 },  {  -70,  47,   72,  19 },  {  -52,  29,   56,  16 } } },  /* 3: S KICK A; attack 3 */
    { { {    0,   0,    0,   0 },  {  -75,  30,   70,  18 },  {  -62,  37,   44,  26 } } },  /* 4: M KICK A, atca 156, atca 157 +4; attack 5, 55, 67, 73 ... */
    { { {    0,   0,    0,   0 },  {  -56,  16,  112,  16 },  {  -72,  22,   88,  24 } } },  /* 5: M KICK A, atca 156, atca 157 +4; attack 55, 67 */
    { { {    0,   0,    0,   0 },  {  -94,  25,   60,  22 },  {  -69,  51,   60,  22 } } },  /* 6: S PUNCH C; attack 7 */
    { { {    0,   0,    0,   0 },  {  -84,  60,   63,  16 },  {  -65,  41,   48,  15 } } },  /* 7: M KICK C; attack 8 */
    { { {    0,   0,    0,   0 },  {  -59,  33,   39,  20 },  {    0,   0,    0,   0 } } },  /* 8: L KICK A, atca 162, atca 165; attack 9, 83, 86 */
    { { {    0,   0,    0,   0 },  {  -87,  61,   65,  21 },  {  -69,  43,   47,  18 } } },  /* 9: L KICK A, atca 162, atca 165 +1; attack 56 */
    { { {    0,   0,    0,   0 },  {  -70,  22,   66,  36 },  {  -46,  20,   66,  17 } } },  /* 10: L KICK A, atca 162, atca 165 +4; attack 49 */
    { { {    0,   0,    0,   0 },  { -108,  28,   64,  21 },  {  -80,  54,   55,  30 } } },  /* 11: L PUNCH A, L PUNCH C, atca 158 +2; attack 11, 75, 82 */
    { { {    0,   0,    0,   0 },  {  -74,  22,   45,  19 },  {  -52,  28,   45,  12 } } },  /* 12: KAGAMI P A; attack 12 */
    { { {    0,   0,    0,   0 },  {  -87,  19,   51,  22 },  {  -68,  48,   52,  10 } } },  /* 13: KAGAMI P A; attack 13 */
    { { {    0,   0,    0,   0 },  {  -76,  34,   49,  24 },  {  -60,  32,   33,  25 } } },  /* 14: KAGAMI P A, atca 166, ATTACK 3 S (Att_HADOUKEN2) +1; attack 14, 57, 71, 87 */
    { { {    0,   0,    0,   0 },  {  -69,  29,   94,  25 },  {  -74,  19,   84,  17 } } },  /* 15: KAGAMI P A, atca 166, ATTACK 3 S (Att_HADOUKEN2) +1; attack 15, 57, 72, 88 */
    { { {    0,   0,    0,   0 },  {  -77,  23,   24,  18 },  {  -58,  32,   33,  16 } } },  /* 16: KAGAMI K A; attack 16 */
    { { {    0,   0,    0,   0 },  {  -70,  23,    0,  23 },  {  -52,  22,   19,  17 } } },  /* 17: KAGAMI K A, UP P GUARD K S; attack 17 */
    { { {    0,   0,    0,   0 },  {  -70,  22,    0,  21 },  {  -52,  18,   16,  14 } } },  /* 18: KAGAMI K A; attack 18 */
    { { {    0,   0,    0,   0 },  {  -69,  43,   91,  14 },  {    0,   0,    0,   0 } } },  /* 19: V JUMP P S A, F JUMP P S A, atca 168; attack 19, 93 */
    { { {    0,   0,    0,   0 },  {  -80,  58,   90,  21 },  {    0,   0,    0,   0 } } },  /* 20: V JUMP P M A, F JUMP P M A; attack 20 */
    { { {    0,   0,    0,   0 },  {  -84,  32,   67,  22 },  {  -52,  26,   80,  19 } } },  /* 21: V JUMP P L A, F JUMP P L A; attack 21 */
    { { {    0,   0,    0,   0 },  {  -47,  34,   78,  36 },  {    0,   0,    0,   0 } } },  /* 22: V JUMP K S A, F JUMP K S A; attack 22 */
    { { {    0,   0,    0,   0 },  {  -63,  37,   43,  31 },  {    0,   0,    0,   0 } } },  /* 23: F JUMP K L A; attack 24 */
    { { {    0,   0,    0,   0 },  {  -52,  26,   73,  12 },  {  -26,  13,   74,  17 } } },  /* 24: FUSHIN P S; attack 25 */
    { { {    0,   0,    0,   0 },  {  -60,  19,   52,  20 },  {  -51,  18,   37,  16 } } },  /* 25: OKIAGARI P S; attack 26 */
    { { {  -34,   6,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 26: M PUNCH A, atca 144, atca 146; attack 27 */
    { { {    0,   0,    0,   0 },  {  -32,  39,  107,  54 },  {    0,   0,    0,   0 } } },  /* 27: ATTACK 1 S (Att_SENPUUKYAKU), ATTACK 1 M (Att_SENPUUKYAKU), ATTACK 1 L (Att_SENPUUKYAKU); attack 31, 33, 35 */
    { { {    0,   0,    0,   0 },  {  -41,  30,   65,  31 },  {    0,   0,    0,   0 } } },  /* 28: ATTACK 1 S (Att_SENPUUKYAKU); attack 30 */
    { { {    0,   0,    0,   0 },  {  -68,  60,   49,  32 },  {  -50,  42,   31,  18 } } },  /* 29: ATTACK 1 M (Att_SENPUUKYAKU), super art Att_SHOURYUUREPPA (command slot 16); attack 32, 50, 59 */
    { { {    0,   0,    0,   0 },  {  -28,  39,   68,  86 },  {    0,   0,    0,   0 } } },  /* 30: ATTACK 1 M (Att_SENPUUKYAKU); attack 33 */
    { { {    0,   0,    0,   0 },  {  -60,  44,   33,  48 },  {    0,   0,    0,   0 } } },  /* 31: ATTACK 1 L (Att_SENPUUKYAKU); attack 34 */
    { { {    0,   0,    0,   0 },  {  -33,  39,   66,  88 },  {    0,   0,    0,   0 } } },  /* 32: ATTACK 1 L (Att_SENPUUKYAKU); attack 35 */
    { { {    0,   0,    0,   0 },  { -112,  88,   72,  18 },  {  -66, 128,   68,  28 } } },  /* 33: saca 69, saca 70, saca 71; attack 76, 77, 78 */
    { { {    0,   0,    0,   0 },  {  -50,  40,   31,  26 },  {    0,   0,    0,   0 } } },  /* 34: ATTACK 1 L (Att_SENPUUKYAKU); attack 37 */
    { { {    0,   0,    0,   0 },  {  -42,  16,   64,  21 },  {    0,   0,    0,   0 } } },  /* 35: L KICK C; attack 6 */
    { { {    0,   0,    0,   0 },  {  -86,  60,   19,  20 },  {  -74,  48,   41,  17 } } },  /* 36: L KICK C; attack 6 */
    { { {    0,   0,    0,   0 },  {  -96,  21,   61,  23 },  {  -75,  48,   61,  29 } } },  /* 37: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU); attack 43 */
    { { {    0,   0,    0,   0 },  {  -87,  22,   69,  18 },  {  -83,  57,   88,  11 } } },  /* 38: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU); attack 44 */
    { { {    0,   0,    0,   0 },  {  -99,  32,   86,  19 },  {  -65,  39,   86,  14 } } },  /* 39: ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU); attack 45 */
    { { {    0,   0,    0,   0 },  {  -92,  33,   54,  22 },  {  -58,  28,   69,  18 } } },  /* 40: ATTACK 5 L (Att_SENPUUKYAKU); attack 46, 47 */
    { { {    0,   0,    0,   0 },  {  -78,  20,   61,  25 },  {  -58,  18,   50,  21 } } },  /* 41: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU); attack 48 */
    { { {    0,   0,    0,   0 },  {  -67,  21,   83,  25 },  {  -83,  16,   70,  19 } } },  /* 42: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU); attack 49 */
    { { {    0,   0,    0,   0 },  {  -80,  36,   56,  22 },  {  -56,  28,   48,  38 } } },  /* 43: ATTACK 2 S (Att_CHOUCHUURENGEKI); attack 38 */
    { { {    0,   0,    0,   0 },  {  -88,  40,   58,  18 },  {  -60,  30,   52,  30 } } },  /* 44: ATTACK 2 S (Att_CHOUCHUURENGEKI); attack 39 */
    { { {    0,   0,    0,   0 },  {  -92,  42,   60,  14 },  {  -64,  32,   54,  26 } } },  /* 45: ATTACK 2 S (Att_CHOUCHUURENGEKI); attack 40 */
    { { {    0,   0,    0,   0 },  {  -96,  44,   62,  10 },  {  -68,  34,   56,  22 } } },  /* 46: ATTACK 2 S (Att_CHOUCHUURENGEKI); attack 41 */
    { { {    0,   0,    0,   0 },  {  -96,  48,   62,  10 },  {    0,   0,    0,   0 } } },  /* 47: ATTACK 2 S (Att_CHOUCHUURENGEKI); attack 42 */
    { { {    0,   0,    0,   0 },  {  -56,  34,   37,  16 },  {  -43,  64,   29,  13 } } },  /* 48: ATTACK 3 S (Att_HADOUKEN2); attack 52 */
    { { {    0,   0,    0,   0 },  {  -64,  19,   43,  24 },  {  -48,  17,   31,  23 } } },  /* 49: ATTACK 3 S (Att_HADOUKEN2); attack 53 */
    { { {    0,   0,    0,   0 },  {  -50,  79,   70,  14 },  {  -63,  25,   54,  14 } } },  /* 50: ATTACK 3 S (Att_HADOUKEN2) */
    { { {    0,   0,    0,   0 },  {   -6,  37,   79,  14 },  {  -39,  31,   70,  14 } } },  /* 51: not used by a script */
    { { {    0,   0,    0,   0 },  {  -82,  19,   32,  38 },  {  -62,  29,   23,  19 } } },  /* 52: ATTACK 3 S (Att_HADOUKEN2); attack 54 */
    { { {    0,   0,    0,   0 },  {  -69,  29,   54,  25 },  {  -89,  18,   35,  35 } } },  /* 53: ATTACK 3 S (Att_HADOUKEN2) */
    { { {    0,   0,    0,   0 },  {  -39,  39,   65,  16 },  {  -59,  19,   57,  16 } } },  /* 54: not used by a script */
    { { {    0,   0,    0,   0 },  {  -70,  63,   33,  51 },  {    0,   0,    0,   0 } } },  /* 55: super art Att_SHOURYUUREPPA (command slot 16); attack 61 */
    { { {    0,   0,    0,   0 },  {  -27,  38,  110,  42 },  {  -53,  26,   68,  53 } } },  /* 56: super art Att_SHOURYUUREPPA (command slot 16); attack 51, 60 */
    { { {    0,   0,    0,   0 },  {  -65,  37,   42,  31 },  {    0,   0,    0,   0 } } },  /* 57: V JUMP K L A; attack 24 */
    { { {    0,   0,    0,   0 },  {  -42,  73,  116,  38 },  {  -53,  26,   68,  48 } } },  /* 58: super art Att_SHOURYUUREPPA (command slot 16); attack 36, 62 */
    { { {    0,   0,    0,   0 },  {  -53,  35,   70,  33 },  {    0,   0,    0,   0 } } },  /* 59: V JUMP K M A, F JUMP K M A; attack 23 */
    { { {  -38,  10,    0,  16 },  {    0,   0,    0,   0 },  {    0,   0,    0,   0 } } },  /* 60: L PUNCH A, L PUNCH C; attack 27 */
    { { {    0,   0,    0,   0 },  {  -98,  20,   75,  11 },  {  -78,  51,   74,  12 } } },  /* 61: saca 73; attack 58 */
    { { {    0,   0,    0,   0 },  {  -68,  40,   42,  36 },  {  -57,  43,   21,  28 } } },  /* 62: saca 74; attack 63 */
    { { {    0,   0,    0,   0 },  {  -60,  32,   98,  22 },  {  -68,  21,   79,  19 } } },  /* 63: saca 74; attack 64 */
    { { {    0,   0,    0,   0 },  {  -50,  35,   49,  36 },  {    0,   0,    0,   0 } } },  /* 64: saca 79; attack 91 */
    { { {    0,   0,    0,   0 },  {  -25,  57,  115,  29 },  {   19,  31,   75,  40 } } },  /* 65: super art Att_SHOURYUUREPPA (command slot 16); attack 92 */
};

const CAUGHT_BOX dudley_cau_box[23] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -28,   57,    0,   16 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +101 */
    { {  -52,  104,    0,   16 } },  /* 2: HANASARE, Att_HADOUKEN (command slot 24) */
    { {  -32,   64,    0,   16 } },  /* 3: DASH HUMIKOMI, ATTACK 3 S (Att_HADOUKEN2), Att_CHOUCHUURENGEKI (command slot 26) */
    { {  -24,   40,    0,   16 } },  /* 4: not used by a script */
    { {  -24,   48,    0,   16 } },  /* 5: not used by a script */
    { {  -32,   61,    0,    8 } },  /* 6: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +30 */
    { {  -36,   65,    0,    8 } },  /* 7: KAGAMI P A, KAGAMI K A */
    { {  -26,   52,   44,   61 } },  /* 8: V JUMP K L A, JUMP JUNBI, SP JUMP JUNBI +28 */
    { {  -42,   71,    0,   16 } },  /* 9: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    { {  -34,   63,    0,   16 } },  /* 10: S PUNCH C */
    { {  -24,   48,    0,   16 } },  /* 11: not used by a script */
    { {  -18,   40,    0,   16 } },  /* 12: not used by a script */
    { {  -48,   77,    0,    8 } },  /* 13: KAGAMI K A */
    { {  -16,   43,   86,   21 } },  /* 14: V JUMP P L A, F JUMP P L A */
    { {  -42,   28,   56,   35 } },  /* 15: not used by a script */
    { {  -11,   40,    8,   96 } },  /* 16: FUSHIN P S */
    { {  -15,   40,    0,   16 } },  /* 17: TOUKETSU A, OKIAGARI P S */
    { {  -29,   40,    0,   16 } },  /* 18: OKIAGARI P S */
    { {  -55,  102,    0,    8 } },  /* 19: ATTACK 3 S (Att_HADOUKEN2) */
    { {  -55,  102,    0,    8 } },  /* 20: ATTACK 3 S (Att_HADOUKEN2), Att_CHOUCHUURENGEKI (command slot 26), saca 74 +10 */
    { {  -20,   51,   40,   44 } },  /* 21: AIR S, AIR M, AIR L +39 */
    { {  -29,   47,    0,   16 } },  /* 22: ATTACK 1 M (Att_SENPUUKYAKU), super art Att_SHOURYUUREPPA (command slot 16), ATTACK 1 L (Att_SENPUUKYAKU) */
};

const HOSEI_BOX dudley_hos_box[28] = {
    /*    x     w     y     h */
    { {    0,    0,    0,    0 } },  /* 0: no box */
    { {  -28,   57,    0,   96 } },  /* 1: KAMAE, HURIMUKI, FRONT WALK +103 */
    { {  -24,   48,    0,   91 } },  /* 2: not used by a script */
    { {  -28,   57,    0,   66 } },  /* 3: KAGAMU, KAGAMI KAMAE, KAGAMI TURN +49 */
    { {  -20,   57,    0,   96 } },  /* 4: M KICK C */
    { {  -26,   52,   44,   61 } },  /* 5: V JUMP K L A, AIR S, AIR M +40 */
    { {  -12,   57,    0,   96 } },  /* 6: not used by a script */
    { {   -4,   57,    0,   96 } },  /* 7: not used by a script */
    { {  -24,   57,    0,   96 } },  /* 8: not used by a script */
    { {    4,   57,    0,   96 } },  /* 9: not used by a script */
    { {  -28,   57,    0,   73 } },  /* 10: PIYO */
    { {  -28,   57,    0,   40 } },  /* 11: saca 69 */
    { {  -28,   57,    0,   50 } },  /* 12: super art Att_SHOURYUUREPPA (command slot 16) */
    { {  -12,   57,    0,   58 } },  /* 13: ATTACK 3 S (Att_HADOUKEN2) */
    { {  -42,   71,    0,   96 } },  /* 14: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    { {  -17,   47,    6,   96 } },  /* 15: FUSHIN P S */
    { {  -18,   48,   27,   48 } },  /* 16: TOUKETSU A, OKIAGARI P S */
    { {  -32,   48,   27,   48 } },  /* 17: OKIAGARI P S */
    { {  -29,   48,   19,   44 } },  /* 18: not used by a script */
    { {  -55,   93,   19,   44 } },  /* 19: ATTACK 3 S (Att_HADOUKEN2), Att_CHOUCHUURENGEKI (command slot 26), saca 74 +10 */
    { {  -32,   64,    0,   80 } },  /* 20: DASH HUMIKOMI, ATTACK 3 S (Att_HADOUKEN2), Att_CHOUCHUURENGEKI (command slot 26) */
    { {  -33,   57,    0,   91 } },  /* 21: not used by a script */
    { {  -53,   81,   41,   37 } },  /* 22: not used by a script */
    { {  -49,   94,   19,   44 } },  /* 23: not used by a script */
    { {  -20,   51,   40,   44 } },  /* 24: AIR S, AIR M, AIR L +39 */
    { {  -39,   74,    0,   79 } },  /* 25: ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
    { {  -28,   57,    0,   30 } },  /* 26: NEKOROBI S */
    { {  -38,   67,    0,   96 } },  /* 27: ATTACK 5 S (Att_SENPUUKYAKU), ATTACK 5 M (Att_SENPUUKYAKU), ATTACK 5 L (Att_SENPUUKYAKU) */
};
