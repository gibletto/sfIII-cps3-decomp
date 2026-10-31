/*
 * EEPROM.C  EEPROM access and bookkeeping counters
 *
 * Low-level serial EEPROM routines: eeprom_read and eeprom_write transfer words with the
 * command sequence and ready polling (eeprom_wait_ready), eeprom_test saves the 64 words,
 * writes and verifies test patterns (eeprom_fill_verify) and restores them.
 * The bookkeeping counters kept in EEPROM (coins, service credits, free-play games,
 * dispensed cards) are incremented by bookkeep_*_count, flushed from pending counts by
 * bookkeep_flush and cleared by bookkeep_clear_all; a write error halts with an error screen.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "eeprom.h"
#include "cps3.h"

/* the EEPROM interface (EEP_ROM_WRITE and EEP_ROM_READ, the word windows, are in cps3.h) */
#define EEP_ROM_OPEN        (*(volatile u16*)(EEP_ROM + 0x60))      /* read three times before a transfer */
#define EEP_ROM_CLOSE       (*(volatile u16*)EEP_ROM)               /* read three times after it */
#define EEP_ROM_STATUS      (*(volatile u16*)(EEP_ROM + 0x200))     /* bit 0 set while busy */
#define EEP_ROM_DATA        (*(volatile u16*)(EEP_ROM + 0x202))     /* the word a load from EEP_ROM_READ fetched */



u32 book_coin_count;  /* 0205EC2C */
u32 book_service_count;  /* 0205EC30 */
u32 book_free_count;  /* 0205EC34 */
u32 book_card_count;  /* 0205EC38 */
u16 eep_dummy;  /* 0205EC3C */
u16 eep_strobe_0;  /* 0205EC3E */
u16 eep_strobe_1;  /* 0205EC40 */
u16 eep_strobe_2;  /* 0205EC42 */
u16 eeprom_test_save[64];  /* 0205EC44 */


/* 020071E8 */
u32 bookkeep_add0 = 0;
u32 bookkeep_add1 = 0;
u32 bookkeep_add2 = 0;
u32 bookkeep_add3 = 0;


/* provisional name */
s8 eeprom_test(u16* buf) {
    register s16 i;
    u16* p;
    u16* q;
    if (eeprom_read(64, (volatile u16*)EEP_ROM_READ, buf)) {
        return 1;
    }
    for (p = buf, q = eeprom_test_save, i = 0; i < 64; i++) {
        *q = *p;
        p++;
        q++;
    }
    if (eeprom_fill_verify(0xFFFF, buf)) {
        return 1;
    }
    if (eeprom_fill_verify(0xAAAA, buf)) {
        return 1;
    }
    if (eeprom_fill_verify(0x5555, buf)) {
        return 1;
    }
    if (eeprom_fill_verify(0, buf)) {
        return 1;
    }
    for (p = buf, q = eeprom_test_save, i = 0; i < 64; i++) {
        *p = *q;
        p++;
        q++;
    }
    if (eeprom_write(64, (volatile u16*)EEP_ROM_WRITE, buf)) {
        return 1;
    }
    return 0;
}



/* provisional name */
s8 eeprom_fill_verify(u16 fill, u16* buf) {
    register s16 i;
    register u16* p;
    for (p = buf, i = 0; i < 64; i++) {
        *p = fill;
        p++;
    }
    if (eeprom_write(64, (volatile u16*)EEP_ROM_WRITE, buf)) {
        return 1;
    }
    if (eeprom_read(64, (volatile u16*)EEP_ROM_READ, buf)) {
        return 1;
    }
    for (p = buf, i = 0; i < 64; i++) {
        if (*p != fill) {
            return 1;
        }
        p++;
    }
    return 0;
}



/* provisional name */
s8 eeprom_read(s16 n, volatile u16* rom, u16* buf) {
    register s16 i;
    eep_strobe_0 = EEP_ROM_OPEN;
    eep_strobe_1 = EEP_ROM_OPEN;
    eep_strobe_2 = EEP_ROM_OPEN;
    delay_cycles(161);
    eep_dummy = *rom;
    delay_cycles(161);
    if (eeprom_wait_ready()) {
        return 1;
    }
    eep_dummy = EEP_ROM_DATA;
    delay_cycles(161);
    if (eeprom_wait_ready()) {
        return 1;
    }
    for (i = 0; i < n; i++) {
        eep_dummy = *rom;
        delay_cycles(161);
        if (eeprom_wait_ready()) {
            return 1;
        }
        *buf = EEP_ROM_DATA;
        delay_cycles(161);
        if (eeprom_wait_ready()) {
            return 1;
        }
        rom++;
        buf++;
    }
    eep_strobe_0 = EEP_ROM_CLOSE;
    eep_strobe_1 = EEP_ROM_CLOSE;
    eep_strobe_2 = EEP_ROM_CLOSE;
    delay_cycles(3);
    return 0;
}



/* Writes n words from src to the EEPROM at dst; returns 1 when the EEPROM does not come ready. */
/* provisional name */
s8 eeprom_write(n, dst, src)
s16 n;
u16* dst;
u16* src;
{
    register s16 i;
    eep_strobe_0 = EEP_ROM_OPEN;
    eep_strobe_1 = EEP_ROM_OPEN;
    eep_strobe_2 = EEP_ROM_OPEN;
    delay_cycles(0xA1);
    for (i = 0; i < n; i++) {
        *(u16*)((u8*)dst + 0x100) = 0;
        delay_cycles(0xA1);
        if (eeprom_wait_ready()) {
            return 1;
        }
        *dst = *src;
        delay_cycles(0xA1);
        if (eeprom_wait_ready()) {
            return 1;
        }
        dst += 1;
        src += 1;
    }
    eep_strobe_0 = EEP_ROM_CLOSE;
    eep_strobe_1 = EEP_ROM_CLOSE;
    eep_strobe_2 = EEP_ROM_CLOSE;
    delay_cycles(0xA1);
    return 0;
}



/* provisional name */
s8 eeprom_wait_ready(void) {
    s32 i;
    for (i = 0; i < 0x30000; i++) {
        if ((EEP_ROM_STATUS & 1) == 0) {
            return 0;
        }
    }
    return 1;
}

/* Shows EEPROM ERROR on a cleared text layer and stops there for good. */
/* provisional name */
void eeprom_error_halt(void)
{
    tilemap_fill_all(0, 0x20);
    tilemap_print_string_attr(15, 8, 12, eeprom_error_str);    /* "EEPROM  ERROR" */
    while (1) {
        task_sleep(1);
    }
}



/* provisional name */
void bookkeep_coin_count(void) {
    book_coin_count++;
    if (eeprom_write(2, (u16*)(EEP_ROM_WRITE + EEP_BOOK_COIN), (u16*)&book_coin_count)) {
        eeprom_error_halt();
    }
}



/* provisional name */
void bookkeep_service_count(void) {
    book_service_count++;
    if (eeprom_write(2, (u16*)(EEP_ROM_WRITE + EEP_BOOK_SERVICE), (u16*)&book_service_count)) {
        eeprom_error_halt();
    }
}



/* provisional name */
void bookkeep_freeplay_count(void) {
    book_free_count++;
    if (eeprom_write(2, (u16*)(EEP_ROM_WRITE + EEP_BOOK_FREE), (u16*)&book_free_count)) {
        eeprom_error_halt();
    }
}



/* provisional name */
void bookkeep_card_count(void) {
    book_card_count++;
    if (eeprom_write(2, (u16*)(EEP_ROM_WRITE + EEP_BOOK_CARD), (u16*)&book_card_count)) {
        eeprom_error_halt();
    }
}



/* provisional name */
void bookkeep_clear_all(void) {
    u32 buf[4];
    buf[0] = book_coin_count = 0;
    buf[1] = book_service_count = 0;
    buf[2] = book_free_count = 0;
    buf[3] = book_card_count = 0;
    if (eeprom_write(8, (u16*)(EEP_ROM_WRITE + EEP_BOOK_COIN), (u16*)buf)) {
        eeprom_error_halt();
    }
}



/* provisional name */
/* Nothing is returned (no caller reads the result). */
s32 bookkeep_flush(void) {
    if (bookkeep_add0 > 0) {
        book_coin_count += bookkeep_add0;
        if (eeprom_write(2, (u16*)(EEP_ROM_WRITE + EEP_BOOK_COIN), (u16*)&book_coin_count)) {
            eeprom_error_halt();
        }
        bookkeep_add0 = 0;
    }
    if (bookkeep_add1 > 0) {
        book_service_count += bookkeep_add1;
        if (eeprom_write(2, (u16*)(EEP_ROM_WRITE + EEP_BOOK_SERVICE), (u16*)&book_service_count)) {
            eeprom_error_halt();
        }
        bookkeep_add1 = 0;
    }
    if (bookkeep_add2 > 0) {
        book_free_count += bookkeep_add2;
        if (eeprom_write(2, (u16*)(EEP_ROM_WRITE + EEP_BOOK_FREE), (u16*)&book_free_count)) {
            eeprom_error_halt();
        }
        bookkeep_add2 = 0;
    }
    if (bookkeep_add3 > 0) {
        book_card_count += bookkeep_add3;
        if (eeprom_write(2, (u16*)(EEP_ROM_WRITE + EEP_BOOK_CARD), (u16*)&book_card_count)) {
            eeprom_error_halt();
        }
        bookkeep_add3 = 0;
    }
}
