#ifndef EEPROM_H
#define EEPROM_H

#include "structs.h"

s8 eeprom_fill_verify(u16 fill, u16* buf);
s8 eeprom_read(s16 n, volatile u16* rom, u16* buf);
s8 eeprom_write();
s8 eeprom_wait_ready(void);
void eeprom_error_halt(void);
void bookkeep_coin_count(void);
void bookkeep_service_count(void);
void bookkeep_freeplay_count(void);
void bookkeep_card_count(void);
void bookkeep_clear_all(void);
s32 bookkeep_flush(void);
s8 eeprom_test(u16* buf);

#endif
