/*
 * CMD_MAIN_TBL_E.C  configuration menu guide text
 *
 * The guide lines at the foot of the system configuration screens: MODIFY SETTING = 1P LEFT or
 * RIGHT with = 1P SHOT1 or SHOT2, and RETURN TO CONFIGURATION MENU with = 1P SHOT1. Reached
 * through the sysconfig_modify_guide and sysconfig_return_guide lists of SYS_CONFIG_TBL_C.C,
 * which SYS_CONFIG_2.C, the test-mode configuration menu, prints.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s8 gcfg_help_modify_en[];
extern const s8 str_1P_SHOT1_or_SHOT2_2[];
extern const s8 gcfg_help_return_en[];
extern const s8 str_1P_SHOT1_2[];

/* provisional name */
const s8 gcfg_help_modify_en[36] = "MODIFY SETTING = 1P LEFT or RIGHT \n";

const s8 str_1P_SHOT1_or_SHOT2_2[36] = "               = 1P SHOT1 or SHOT2";

/* provisional name */
const s8 gcfg_help_return_en[36] = "RETURN TO CONFIGURATION MENU      \n";

const s8 str_1P_SHOT1_2[36] = "               = 1P SHOT1         ";
