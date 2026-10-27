/*
 * SYS_CONFIG_TBL_D.C  configuration saving message text
 *
 * str_saving_configuration and str_IN_EEPROM are the two lines of the "NOW SAVING NEW
 * CONFIGURATION IN EEPROM..." message, reached through config_saving_scr in
 * SYS_CONFIG_TBL_C.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const char str_saving_configuration[];
extern const char str_IN_EEPROM[];

const char str_saving_configuration[36] = "NOW  SAVING  NEW  CONFIGURATION\n";

const char str_IN_EEPROM[40] = "                         IN  EEPROM...";
