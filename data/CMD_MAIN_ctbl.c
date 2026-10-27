/*
 * CMD_MAIN_CTBL.C  debug screen sign strings
 *
 * dbg_minus_str is the minus sign printed before a negative value on the debug screens, and
 * dbg_space2_str the two blanks printed in place of a value. Read by CMD_MAIN.C, the debug
 * menu.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const char dbg_minus_str[];
extern const char dbg_space2_str[];

const char dbg_minus_str[4] = "-\0\x26\x26";

const char dbg_space2_str[4] = "  \0\x28";
