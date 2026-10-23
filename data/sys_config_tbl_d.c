/*
 * SYS_CONFIG_TBL_D.C  text of the configuration saving message, which sys_config_tbl_c's screens point at
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const char str_saving_configuration[];
extern const char str_IN_EEPROM[];

const char str_saving_configuration[36] = "NOW  SAVING  NEW  CONFIGURATION\n";

const char str_IN_EEPROM[40] = "                         IN  EEPROM...";
