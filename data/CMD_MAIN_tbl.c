/*
 * CMD_MAIN_TBL.C  English game configuration page layout
 *
 * config_title_str_tbl places the title and item lines of the English GAME CONFIGURATION page,
 * config_help_modify_str_tbl and config_help_return_str_tbl the guide lines at the foot of the
 * page; the text itself is in CMD_MAIN_TBL_B.C and SYS_CONFIG_TBL.C. gcfg_gauge_chr_en gives
 * the character put at the star gauge's new position for each setting and
 * gcfg_gauge_clr_chr_en the one that clears the old position. Read by GAME_CONFIG_EN.C, the
 * English configuration page.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const TM_STRING config_title_str_tbl[];
extern const TM_STRING config_help_modify_str_tbl[];
extern const TM_STRING config_help_return_str_tbl[];
extern const s16 gcfg_gauge_clr_chr_en;
extern const s16 gcfg_gauge_chr_en[];
extern const char str_1P_SHOT1[];
extern const char str_1P_SHOT1_or_SHOT2[];
extern const char str_1_GAME_DIFFICULTY_EASY_HARD[];
extern const char str_2_DAMAGE_LEVEL_LOW_HIGH[];
extern const char str_3_TIME_COUNT_SPEED_SLOW_FAST[];
extern const char str_4_MAX_ROUND_3_ROUND[];
extern const char str_5_EVENT_OFF[];
extern const char str_6_EXIT[];
extern const u16 str_guide_modify_setting[];
extern const u16 str_guide_return_config_menu[];
extern const u16 str_guide_select_option[];
extern const u8 gcfg_help_select2_en[];
extern const u8 gcfg_line_title_en[];

const TM_STRING config_title_str_tbl[8] = {
    { 1, 1, 2, (const s8 *)gcfg_line_title_en },
    { 3, 4, 2, (const s8 *)str_1_GAME_DIFFICULTY_EASY_HARD },
    { 3, 6, 2, (const s8 *)str_2_DAMAGE_LEVEL_LOW_HIGH },
    { 3, 8, 2, (const s8 *)str_3_TIME_COUNT_SPEED_SLOW_FAST },
    { 3, 0xA, 2, (const s8 *)str_4_MAX_ROUND_3_ROUND },
    { 3, 0xC, 2, (const s8 *)str_5_EVENT_OFF },
    { 3, 0xE, 2, (const s8 *)str_6_EXIT },
    { 7, 0x19, 2, (const s8 *)gcfg_help_select2_en },
};

const TM_STRING config_help_modify_str_tbl[2] = {
    { 7, 0x1A, 2, (const s8 *)str_guide_modify_setting },
    { 7, 0x1B, 2, (const s8 *)str_1P_SHOT1_or_SHOT2 },
};

const TM_STRING config_help_return_str_tbl[3] = {
    { 7, 0x19, 2, (const s8 *)str_guide_select_option },
    { 7, 0x1A, 2, (const s8 *)str_guide_return_config_menu },
    { 7, 0x1B, 2, (const s8 *)str_1P_SHOT1 },
};

const s16 gcfg_gauge_clr_chr_en = 42;

const s16 gcfg_gauge_chr_en[9] = {
    49, 50, 51, 52, 53, 54, 55, 56, 8224,
};
