/*
 * CMD_MAIN_TBL_B.C  the text of the English game configuration page: its title, its lines and a guide line, which
 * config_title_str_tbl (CMD_MAIN_tbl.c) shows
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s8 gcfg_line_title_en[];
extern const s8 str_1_GAME_DIFFICULTY_EASY_HARD[];
extern const s8 str_2_DAMAGE_LEVEL_LOW_HIGH[];
extern const s8 str_3_TIME_COUNT_SPEED_SLOW_FAST[];
extern const s8 str_4_MAX_ROUND_3_ROUND[];
extern const s8 str_5_EVENT_OFF[];
extern const s8 str_6_EXIT[];
extern const s8 gcfg_help_select2_en[];

/* provisional name */
const s8 gcfg_line_title_en[44] = "7-2. G A M E   C O N F I G U R A T I O N\n\0\x08\x08";

const s8 str_1_GAME_DIFFICULTY_EASY_HARD[44] = "1. GAME DIFFICULTY   EASY[********]HARD\n\0\x03\x03\x04";

const s8 str_2_DAMAGE_LEVEL_LOW_HIGH[40] = "2. DAMAGE LEVEL      LOW [****] HIGH\n\0\x20\x20";

const s8 str_3_TIME_COUNT_SPEED_SLOW_FAST[40] = "3. TIME COUNT SPEED  SLOW[****]FAST\n\0\x26\x27\x28";

const s8 str_4_MAX_ROUND_3_ROUND[32] = "4. MAX ROUND         3 ROUND\n\0\x29\x29";

const s8 str_5_EVENT_OFF[28] = "5. EVENT             OFF\n\0\x27\x28";

const s8 str_6_EXIT[12] = "6. EXIT\n\0\x01\x01\x01";

/* provisional name */
const s8 gcfg_help_select2_en[32] = "SELECT OPTION  = 1P UP or DOWN\0\x01";
