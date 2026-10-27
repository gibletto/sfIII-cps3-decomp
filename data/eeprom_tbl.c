/*
 * EEPROM_TBL.C  EEPROM error message
 *
 * eeprom_error_str is the "EEPROM  ERROR" line printed by EEPROM.C when it halts on a failed
 * EEPROM.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s8 eeprom_error_str[];

const s8 eeprom_error_str[16] = "EEPROM  ERROR";
