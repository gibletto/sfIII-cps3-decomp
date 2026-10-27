/*
 * CMD_MAIN_TBL_C.C  English configuration values and the debug preview character sets
 *
 * str_NORMAL_2 and str_WIDE (screen), str_1_ROUND .. str_7_ROUNDS (max round) and str_OFF and
 * str_1_MATCH (event) are the value strings of the English configuration page, placed through
 * the screen, round and event lists of GAME_CONFIG_EN.C. debug_charset_tbl gives the character
 * set of each character's block of cg numbers in the debug character preview; read by
 * CMD_MAIN.C, the debug menu.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const char str_NORMAL_2[];
extern const char str_WIDE[];
extern const char str_1_ROUND[];
extern const char str_3_ROUNDS[];
extern const char str_5_ROUNDS[];
extern const char str_7_ROUNDS[];
extern const char str_OFF[];
extern const char str_1_MATCH[];
extern const u8 debug_charset_tbl[];

const char str_NORMAL_2[12] = "NORMAL  \0\x02\x03\x03";

const char str_WIDE[12] = "WIDE    \0\x1E\x1E\x20";

const char str_1_ROUND[12] = "1 ROUND \0\x29\x29\x2A";

const char str_3_ROUNDS[12] = "3 ROUNDS\0\x01\x02\x02";

const char str_5_ROUNDS[12] = "5 ROUNDS\0\x06\x06\x06";

const char str_7_ROUNDS[12] = "7 ROUNDS\0\x07\x37\x38";

const char str_OFF[8] = "OFF    ";

const char str_1_MATCH[8] = "1 MATCH";

const u8 debug_charset_tbl[16] = {
    6, 3, 5, 1, 2, 9, 7, 4, 0xA, 8, 0xC, 0xD, 0xE, 3, 3, 3,
};
