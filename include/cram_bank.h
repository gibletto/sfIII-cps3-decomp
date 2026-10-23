#ifndef CRAM_BANK_H
#define CRAM_BANK_H

#include "structs.h"

u32 cram_bank_addr(s32 offset);
u32 cram_bank_slot_offset(s16 slot);
void cram_bank_init(void);
s16 cram_bank_set(s16 bank);
s16 cram_bank_restore(void);

#endif
