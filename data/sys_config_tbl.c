/*
 * SYS_CONFIG_TBL.C  the guide lines of the configuration pages, which config_help_modify_str_tbl and
 * config_help_return_str_tbl (CMD_MAIN_tbl.c) show
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const char str_guide_modify_setting[];
extern const s8 str_1P_SHOT1_or_SHOT2[];
extern const char str_guide_select_option[];
extern const char str_guide_return_config_menu[];
extern const s8 str_1P_SHOT1[];

const char str_guide_modify_setting[36] = "MODIFY SETTING = 1P LEFT or RIGHT \n";

const s8 str_1P_SHOT1_or_SHOT2[36] = "               = 1P SHOT1 or SHOT2\0\x04";

const char str_guide_select_option[36] = "SELECT OPTION  = 1P UP or DOWN    \n";

const char str_guide_return_config_menu[36] = "RETURN TO CONFIGURATION MENU      \n";

const s8 str_1P_SHOT1[36] = "               = 1P SHOT1         \0\x28";
