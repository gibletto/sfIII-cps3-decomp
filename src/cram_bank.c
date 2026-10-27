/*
 * CRAM_BANK.C  Character RAM bank switching
 *
 * The character RAM is reached through a window at CHARACTER_RAM selected by the bank register
 * at CRAM_BANK_REG. cram_bank_init resets it to bank 0; cram_bank_set selects a bank and
 * remembers the previous one; cram_bank_restore swaps back to the previous bank.
 * cram_bank_addr selects the 1 MB bank holding a linear offset and returns its address in
 * the window, and cram_bank_slot_offset does the same for a 4 KB slot number.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "cram_bank.h"
#include "cps3.h"



#define CRAM_BANK_BYTES     0x100000    /* one bank: the window's size */
#define CRAM_WINDOW_MASK    0xFFFFF
#define CRAM_BANK_MASK      15          /* sixteen banks */
#define CRAM_SLOTS_PER_BANK 256         /* 4 KB slots, numbered from 1 */
#define CRAM_SLOT_SHIFT     12

s16 cram_bank_old;  /* 02079C94 */
s16 cram_bank_now;  /* 02079C96 */


/* provisional name */
void cram_bank_init(void) {
    *(volatile s16*)CRAM_BANK_REG = 0;
    cram_bank_old = 0;
    cram_bank_now = 0;
}



/* provisional name */
s16 cram_bank_set(s16 bank) {
    if (cram_bank_now == bank) {
        return cram_bank_now;
    }
    cram_bank_old = cram_bank_now;
    cram_bank_now = bank;
    *(volatile u16*)CRAM_BANK_REG = bank & CRAM_BANK_MASK;
    return cram_bank_old;
}



/* provisional name */
s16 cram_bank_restore(void) {
    s16 prev;
    if (cram_bank_old == cram_bank_now) {
        return cram_bank_now;
    }
    prev = cram_bank_now;
    cram_bank_now = cram_bank_old;
    *(volatile u16*)CRAM_BANK_REG = cram_bank_now & CRAM_BANK_MASK;
    cram_bank_old = prev;
    return prev;
}



/* provisional name */
u32 cram_bank_addr(s32 offset) {
    s16 bank;
    bank = (offset / CRAM_BANK_BYTES) & CRAM_BANK_MASK;
    if (cram_bank_now != bank) {
        cram_bank_old = cram_bank_now;
        cram_bank_now = bank;
        *(volatile u16*)CRAM_BANK_REG = bank & CRAM_BANK_MASK;
    }
    return (offset & CRAM_WINDOW_MASK) + CHARACTER_RAM;
}



/* provisional name */
u32 cram_bank_slot_offset(s16 slot) {
    s16 bank;
    bank = ((slot - 1) / CRAM_SLOTS_PER_BANK) & CRAM_BANK_MASK;
    if (cram_bank_now != bank) {
        cram_bank_old = cram_bank_now;
        cram_bank_now = bank;
        *(volatile u16*)CRAM_BANK_REG = bank & CRAM_BANK_MASK;
    }
    return ((slot - 1) << CRAM_SLOT_SHIFT) & CRAM_WINDOW_MASK;
}


/* provisional name */
s16 cram_bank_now_get(void) {
    return cram_bank_now;
}


/* provisional name */
s16 cram_bank_old_get(void) {
    return cram_bank_old;
}
