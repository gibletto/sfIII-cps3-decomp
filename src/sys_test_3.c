/*
 * SYS_TEST_3.C  Test mode memory, CD-ROM and SIMM checks
 *
 * Routines: memtest_pattern_word, memtest_pattern_byte_lane, memtest_pattern_masked_word,
 * memtest_work_ram, memtest_sprite_ram, memtest_color_ram, memtest_character_ram, memtest_ss_ram,
 * memtest_eeprom, memtest_sram, cd_check_drive_inquiry, ...
 *
 * The memory test checks the character RAM as one block with memtest_pattern_word and runs the SRAM
 * test too; the CD and SIMM lines sit two rows below the RAM lines.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "eeprom.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "sys_test_3.h"
#include "cps3.h"

/* the CD-ROM drive's SCSI controller (WD33C93): a register number written to CD_SELECT picks the register
   that CD_DATA reads or writes (the number steps on after each access); reading CD_REG gives the auxiliary
   status */
#define CD_SELECT           (*(volatile u16*)CD_REG)
#define CD_AUX_STATUS       (*(volatile u16*)CD_REG)
#define CD_DATA             (*(volatile u16*)(CD_REG + 0x2))

#define AUX_INT             0x80    /* interrupt pending */
#define AUX_BUSY            0x30    /* busy, command in progress */
#define AUX_DBR             0x01    /* data buffer ready */

#define SCSI_OWN_ID         0       /* own ID, here the CDB size */
#define SCSI_CONTROL        1
#define SCSI_CDB1           3       /* the CDB bytes follow */
#define SCSI_TARGET_LUN     15
#define SCSI_COMMAND_PHASE  16
#define SCSI_SYNC_TRANSFER  17
#define SCSI_COUNT_MSB      18      /* transfer count: MSB, 2nd, LSB */
#define SCSI_COUNT_2ND      19
#define SCSI_DEST_ID        21
#define SCSI_STATUS         23
#define SCSI_COMMAND        24
#define SCSI_DATA           25

#define SCSI_SEL_ATN_XFER   8       /* command: select with ATN and transfer */

/* memtest_no: the memory test page step */
#define MEMTEST_INIT    0       /* memtest_menu_init: draw the menu */
#define MEMTEST_SELECT  1       /* memtest_menu_select: choose a test */
#define MEMTEST_RUN     2       /* until memtest_error clears */
#define MEMTEST_WAIT    3       /* wait memtest_wait */
#define MEMTEST_EXIT    4       /* (default) back to the test menu */



extern const char str_ONBOARD[];
extern const char str_SIMM1[];
extern const char str_SIMM2[];
extern const char str_SIMM3[];
extern const char str_SIMM4[];
extern const char str_SIMM5[];
extern const char str_SIMM6[];
extern const char str_SIMM7[];

u32 scsi_sense_key;  /* 0205E2D4 */
u32 scsi_sense_asc;  /* 0205E2D8 */
s8 scsi_sense_buf[22];  /* 0205E2DC */
SCSI_INQUIRY scsi_inquiry_data;  /* 0205E2F2 */
SCSI_CAPACITY scsi_capacity;  /* 0205E318 */
s8 scsi_toc_buf[40];  /* 0205E320 */
s8 cd_sector_buf[2048];  /* 0205E348 */
s32 scsi_error;  /* 0205EB48 */
s16 scsi_cdb_len;  /* 0205EB4C */


/* 02007158 */
const s8* simm_name_tbl[8] = {
    str_ONBOARD,
    str_SIMM1,
    str_SIMM2,
    str_SIMM3,
    str_SIMM4,
    str_SIMM5,
    str_SIMM6,
    str_SIMM7,
};
u8 no_cd_flag = 0;  /* 02007178 */
s16 memtest_error = 0;  /* 0200717A */
s16 memtest_wait = 0;  /* 0200717C */
s16 memtest_cursor = 0;  /* 0200717E */
s16 memtest_no = 0;  /* 02007180 */


/* provisional name */
u32 memtest_pattern_word(volatile u16* addr, u32 size) {
    register u16 got;
    register u16 save;
    register u32 i;
    register volatile u16* p;
    for (p = addr, i = 0; i < size; i += 2) {
        save = *p;
        *p = 0xFFFF;
        got = *p;
        *p = save;
        if (got != 0xFFFF) {
            return (u32)p;
        }
        *p = 0xAAAA;
        got = *p;
        *p = save;
        if (got != 0xAAAA) {
            return (u32)p;
        }
        *p = 0x5555;
        got = *p;
        *p = save;
        if (got != 0x5555) {
            return (u32)p;
        }
        *p = 0;
        got = *p;
        *p = save;
        if (got != 0) {
            return (u32)p;
        }
        p++;
    }
    return 0;
}

/* provisional name */
u16* memtest_pattern_byte_lane(u16* start, u32 size) {
    register u16 r;
    register u16 save;
    register u32 i;
    register u16* p;
    i = 0;
    p = start;
    for (;;) {
        save = *p;
        *p = 0xFFFF;
        r = *p;
        *p = save;
        if (((u32)r % 256) != 0xFF) {
            return p;
        }
        *p = 0xAAAA;
        r = *p;
        *p = save;
        if (((u32)r % 256) != 0xAA && r != 0xAAAA) {
            return p;
        }
        *p = 0x5555;
        r = *p;
        *p = save;
        if (((u32)r % 256) != 0x55) {
            return p;
        }
        *p = 0;
        r = *p;
        *p = save;
        if ((u32)r % 256) {
            return p;
        }
        i++;
        p++;
        if (i >= size >> 1) {
            break;
        }
    }
    return 0;
}



/* provisional name */
u32 memtest_pattern_masked_word(volatile u16* addr, u32 size) {
    register u16 got;
    register u16 save;
    register u32 i;
    register volatile u16* p;
    i = 0;
    p = addr;
    while (1) {
        save = *p;
        *p = 0xFFFF;
        got = *p;
        *p = save;
        if ((got & 0x7FFF) != 0x7FFF) {
            return (u32)p;
        }
        *p = 0xAAAA;
        got = *p;
        *p = save;
        if ((got & 0x7FFF) != 0x2AAA) {
            if (got != 0xAAAA) {
                return (u32)p;
            }
        }
        *p = 0x5555;
        got = *p;
        *p = save;
        if ((got & 0x7FFF) != 0x5555) {
            return (u32)p;
        }
        *p = 0;
        got = *p;
        *p = save;
        if (got & 0x7FFF) {
            return (u32)p;
        }
        i++;
        p++;
        if (i >= size >> 1) {
            break;
        }
    }
    return 0;
}



/* provisional name */
void memtest_work_ram(void) {
    register s32 err;
    tilemap_print_string_attr(30, 3, 2, memtest_checking_str);
    _builtin_set_imask(15);
    err = memtest_pattern_word((volatile u16*)WORK_RAM, 0x80000);
    _builtin_set_imask(1);
    if (err) {
        tilemap_print_string_attr(30, 3, 8, memtest_ng_str);
        tilemap_print_hex_block(33, 3, 2, err, 8, 0);
        memtest_error = 1;
    } else {
        tilemap_print_string_attr(30, 3, 2, memtest_ok_str);
    }
}



/* provisional name */
void memtest_sprite_ram(void) {
    register s32 err;
    tilemap_print_string_attr(30, 5, 2, memtest_checking_str);
    _builtin_set_imask(15);
    err = memtest_pattern_word((volatile u16*)SPRITE_RAM, 0x7E000);
    _builtin_set_imask(1);
    if (err) {
        tilemap_print_string_attr(30, 5, 8, memtest_ng_str);
        tilemap_print_hex_block(33, 5, 2, err, 8, 0);
        memtest_error = 1;
    } else {
        tilemap_print_string_attr(30, 5, 2, memtest_ok_str);
    }
}



/* provisional name */
void memtest_color_ram(void) {
    register s32 err;
    tilemap_print_string_attr(30, 7, 2, memtest_checking_str);
    _builtin_set_imask(15);
    err = memtest_pattern_masked_word((volatile u16*)COLOR_RAM, 0x40000);
    _builtin_set_imask(1);
    if (err) {
        tilemap_print_string_attr(30, 7, 8, memtest_ng_str);
        tilemap_print_hex_block(33, 7, 2, err, 8, 0);
        memtest_error = 1;
    } else {
        tilemap_print_string_attr(30, 7, 2, memtest_ok_str);
    }
}



/* provisional name */
void memtest_character_ram(void) {
    register u32 err;
    tilemap_print_string_attr(30, 9, 2, memtest_checking_str);
    _builtin_set_imask(15);
    err = memtest_pattern_word((volatile u16*)CHARACTER_RAM, 0x100000);
    _builtin_set_imask(1);
    if (err) {
        tilemap_print_string_attr(30, 9, 8, memtest_ng_str);
        tilemap_print_hex_block(33, 9, 2, err, 8, 0);
        memtest_error = 1;
    } else {
        tilemap_print_string_attr(30, 9, 2, memtest_ok_str);
    }
}



/* provisional name */
void memtest_ss_ram(void) {
    register u16* bad;
    tilemap_print_string_attr(30, 11, 2, memtest_checking_str);
    _builtin_set_imask(15);
    bad = memtest_pattern_byte_lane((u16*)SS_RAM, 0xC800);
    _builtin_set_imask(1);
    if (bad) {
        tilemap_print_string_attr(30, 11, 8, memtest_ng_str);
        tilemap_print_hex_block(33, 11, 2, (u32)bad, 8, 0);
        memtest_error = 1;
    } else {
        tilemap_print_string_attr(30, 11, 2, memtest_ok_str);
    }
}



/* provisional name */
void memtest_eeprom(void) {
    register s32 err;
    tilemap_print_string_attr(30, 13, 2, memtest_checking_str);
    _builtin_set_imask(15);
    err = eeprom_test((u16*)eeprom_w);
    _builtin_set_imask(1);
    if (err) {
        tilemap_print_string_attr(30, 13, 8, memtest_ng_str);
        tilemap_print_hex_block(33, 13, 2, err, 8, 0);
        memtest_error = 1;
    } else {
        tilemap_print_string_attr(30, 13, 2, memtest_ok_str);
    }
}



/* provisional name */
void memtest_sram(void) {
    u8 got;
    u8 save;
    s32 i;
    tilemap_print_string_attr(30, 15, 2, memtest_checking_str);
    _builtin_set_imask(15);
    for (i = 0; i < 0x200; i++) {
        save = sram_read_byte(i);
        sram_write_byte(i, 0xFF);
        got = sram_read_byte(i);
        sram_write_byte(i, save);
        if (got != 0xFF) {
            break;
        }
        sram_write_byte(i, 0xAA);
        got = sram_read_byte(i);
        sram_write_byte(i, save);
        if (got != 0xAA) {
            break;
        }
        sram_write_byte(i, 0x55);
        got = sram_read_byte(i);
        sram_write_byte(i, save);
        if (got != 0x55) {
            break;
        }
        sram_write_byte(i, 0);
        got = sram_read_byte(i);
        sram_write_byte(i, save);
        if (got != 0) {
            break;
        }
    }
    _builtin_set_imask(1);
    if (i < 0x200) {
        tilemap_print_string_attr(30, 15, 8, memtest_ng_str);
        tilemap_print_hex_block(33, 15, 2, i * 2 + SRAM, 8, 0);
        memtest_error = 1;
    } else {
        tilemap_print_string_attr(30, 15, 2, memtest_ok_str);
    }
}



/* provisional name */
s32 cd_check_drive_inquiry(void) {
    s32 rc;
    if (no_cd_flag) {
        return 0;
    }
    while (1) {
        rc = scsi_test_unit_ready(1);
        if ((rc = scsi_decode_sense_key(rc)) == -1) {
            return -1;
        }
        if (rc == 0) {
            break;
        }
    }
    while (1) {
        rc = scsi_inquiry(36, 1, (u8*)&scsi_inquiry_data);
        if ((rc = scsi_decode_sense_key(rc)) == -1) {
            return -1;
        }
        if (rc == 0) {
            break;
        }
    }
    if (scsi_inquiry_data.device_type != 5) {
        return -1;
    }
    return 0;
}



#define CD_VOLUME_ID ((s8*)0x067FFFE0)

/* provisional name */
s32 cd_check_disc_id(void) {
    s32 rc;
    u32 blen;
    s32 last;
    if (no_cd_flag) {
        return 0;
    }
    while (1) {
        rc = scsi_test_unit_ready(1);
        if ((rc = scsi_decode_sense_key(rc)) == -1) {
            return -1;
        }
        if (rc == 0) {
            break;
        }
    }
    while (1) {
        rc = scsi_read_capacity(8, &scsi_capacity);
        if ((rc = scsi_decode_sense_key(rc)) == -1) {
            return -1;
        }
        if (rc == 0) {
            break;
        }
    }
    blen = scsi_capacity.block_len;
    last = (blen >> 8) - 1;
    while (1) {
        scsi_send_cdb_bytes(10, cdb_read_toc);
        rc = scsi_send_cdb_and_read(12, (u8*)scsi_toc_buf);
        if ((rc = scsi_decode_sense_key(rc)) == -1) {
            return -1;
        }
        if (rc == 0) {
            break;
        }
    }
    if ((scsi_toc_buf[5] & 0xF) == 4) {
        while (1) {
            rc = scsi_read_10(16, 1, last, 1, cd_sector_buf);
            if ((rc = scsi_decode_sense_key(rc)) == -1) {
                return -1;
            }
            if (rc == 0) {
                break;
            }
        }
        if (cd_sector_buf[1] == 'C' && cd_sector_buf[2] == 'D' && cd_sector_buf[3] == '0' &&
            cd_sector_buf[4] == '0' && cd_sector_buf[5] == '1') {
            if (cd_sector_buf[0x28] == CD_VOLUME_ID[0] && cd_sector_buf[0x29] == CD_VOLUME_ID[1] &&
                cd_sector_buf[0x2A] == CD_VOLUME_ID[2] && cd_sector_buf[0x2B] == CD_VOLUME_ID[3] &&
                cd_sector_buf[0x2C] == CD_VOLUME_ID[4] && cd_sector_buf[0x2D] == CD_VOLUME_ID[5] &&
                cd_sector_buf[0x2E] == CD_VOLUME_ID[6] && cd_sector_buf[0x2F] == CD_VOLUME_ID[7] &&
                cd_sector_buf[0x30] == CD_VOLUME_ID[8] && cd_sector_buf[0x31] == CD_VOLUME_ID[9] &&
                cd_sector_buf[0x32] == CD_VOLUME_ID[10]) {
                return 0;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}



/* provisional name */
void memtest_cdrom(void) {
    if (!no_cd_flag) {
        tilemap_print_string_attr(30, 17, 2, memtest_checking_str);
        if (cd_check_drive_inquiry() == 0) {
            tilemap_print_string_attr(30, 17, 2, memtest_ok_str);
        } else {
            tilemap_print_string_attr(30, 17, 8, memtest_ng_str);
            memtest_error = 1;
        }
    } else {
        tilemap_print_string_attr(30, 17, 2, memtest_skip_str);
    }
}



/* provisional name */
void memtest_simm_quick(void) {
    s32 slot;
    s32 j;
    u32 sum;
    u32 p = 0x1FED4;
    u32 q;
    for (slot = 1; slot < 8; slot++) {
        if (*(u8*)p != 0) {
            tilemap_print_string_attr(30, slot + 18, 2, memtest_checking_str);
            _builtin_set_imask(15);
            if (*(u8*)p == 1) {
                sum = simm_quick_checksum(slot, 0);
            } else {
                sum = simm_quick_checksum(slot, 1);
            }
            if (sum % 256 != *(u8*)(p + 2)) {
                memtest_error = 1;
                q = 0x1FED4;
                for (j = 1; j < 8; j++) {
                    if (*(u8*)q != 0 && sum % 256 == *(u8*)(q + 2)) {
                        break;
                    }
                    q += 4;
                }
                if (j == 8) {
                    tilemap_print_string_attr(30, slot + 18, 8, memtest_ng_str);
                } else {
                    tilemap_print_string_attr(30, slot + 18, 8, simm_name_tbl[j]);
                }
            } else {
                tilemap_print_string_attr(30, slot + 18, 2, memtest_ok_str);
            }
        } else {
            tilemap_print_string_attr(30, slot + 18, 2, memtest_skip_str);
        }
        p += 4;
    }
}



/* provisional name */
void memtest_memory_check(void) {
    tilemap_fill_all(0, 32);
    tilemap_print_string(0, 0, 0xFFFF, memtest_ram_scr);
    memtest_work_ram();
    memtest_sprite_ram();
    memtest_color_ram();
    memtest_character_ram();
    memtest_ss_ram();
    memtest_eeprom();
    memtest_sram();
    memtest_cdrom();
    memtest_simm_quick();
}



/* provisional name */
void simm_check_run(void) {
    s32 slot;
    u32 sum;
    u32 p = 0x1FED4;
    tilemap_fill_all(0, 32);
    tilemap_print_string(0, 0, 0xFFFF, memtest_simm_scr);
    for (slot = 1; slot < 8; slot++) {
        if (*(u8*)p != 0) {
            tilemap_print_string_attr(30, slot * 2 + 3, 2, memtest_checking_str);
            _builtin_set_imask(15);
            if (*(u8*)p == 1) {
                sum = simm_full_checksum(slot, 0);
            } else {
                sum = simm_full_checksum(slot, 1);
            }
            if (sum % 256 != *(u8*)(p + 1)) {
                memtest_error = 1;
                tilemap_print_string_attr(30, slot * 2 + 3, 8, memtest_ng_str);
            } else {
                tilemap_print_string_attr(30, slot * 2 + 3, 2, memtest_ok_str);
            }
        } else {
            tilemap_print_string_attr(30, slot * 2 + 3, 2, memtest_skip_str);
        }
        p += 4;
    }
}



/* provisional name */
void memtest_menu_init(void) {
    memtest_cursor = 0;
    memtest_error = 0;
    tilemap_fill_all(0, 32);
    tilemap_print_string(0, 0, 0xFFFF, memtest_menu_scr);
    tilemap_put_block(15, 9, 2, 62);
    memtest_no++;
}



/* provisional name */
void memtest_menu_select(void) {
    s32 unused;
    if ((p1sw_0 & LEVER_UP) == LEVER_UP && (p1sw_1 & LEVER_UP) != LEVER_UP) {
        tilemap_put_block(15, memtest_cursor * 2 + 9, 2, 32);
        if (--memtest_cursor < 0) {
            memtest_cursor = 2;
        }
        tilemap_put_block(15, memtest_cursor * 2 + 9, 2, 62);
    } else if ((p1sw_0 & LEVER_DOWN) == LEVER_DOWN && (p1sw_1 & LEVER_DOWN) != LEVER_DOWN) {
        tilemap_put_block(15, memtest_cursor * 2 + 9, 2, 32);
        if (++memtest_cursor > 2) {
            memtest_cursor = 0;
        }
        tilemap_put_block(15, memtest_cursor * 2 + 9, 2, 62);
    }
    if ((p1sw_0 & BUTTON_LP) == BUTTON_LP && (p1sw_1 & BUTTON_LP) != BUTTON_LP) {
        switch (memtest_cursor) {
        case 0:
            memtest_memory_check();
            memtest_no++;
            break;
        case 1:
            simm_check_run();
            memtest_no++;
            break;
        default:
            memtest_no = MEMTEST_EXIT;
            break;
        }
    }
}



/* provisional name */
s32 memtest_page(void) {
    register s32 rc;
    rc = 0;
    switch (memtest_no) {
    case MEMTEST_INIT:
        memtest_menu_init();
        break;
    case MEMTEST_SELECT:
        memtest_menu_select();
        break;
    case MEMTEST_RUN:
        if (memtest_error == 0) {
            memtest_no++;
            memtest_wait = 60;
        }
        break;
    case MEMTEST_WAIT:
        if (memtest_wait == 0) {
            memtest_no++;
        } else {
            memtest_wait--;
        }
        break;
    default:
        rc = -1;
        memtest_no = MEMTEST_INIT;
        break;
    }
    return rc;
}



/* The SRAM byte is read as a halfword (the low byte is the data). */
u8 sram_read_byte(u32 addr) {
    u16* p;
    s8 c;
    if (addr >= 0x200) {
        p = (u16*)(SRAM + 0x3FE);
    } else {
        p = (u16*)(addr * 2 + SRAM);
    }
    sram_bus_slow();
    c = *p;
    delay_cycles(2);
    sram_bus_normal();
    return c;
}



/* provisional name */
void sram_write_byte(u32 addr, u8 v) {
    volatile u16* p;
    if (addr >= 0x200) {
        p = (volatile u16*)(SRAM + 0x3FE);
    } else {
        p = (volatile u16*)(addr * 2 + SRAM);
    }
    sram_bus_slow();
    *p = v;
    delay_cycles(2);
    sram_bus_normal();
}



/* provisional name */
void sram_bus_slow(void) {
    *(volatile u8*)SH2_CCR = 0x10;
    *(volatile u32*)SH2_BCR1 = 0xA55A00E0;
    *(volatile u32*)SH2_WCR = 0xA55AAA5F;
    *(volatile u8*)SH2_CCR = 0x11;
}



/* provisional name */
void sram_bus_normal(void) {
    *(volatile u8*)SH2_CCR = 0x10;
    *(volatile u32*)SH2_BCR1 = 0xA55A0020;
    *(volatile u32*)SH2_WCR = 0xA55AAA57;
    *(volatile u8*)SH2_CCR = 0x11;
}



/* provisional name */
u32 simm_full_checksum(s32 rom, s32 wide) {
    s32 mode;
    s32 bank;
    u32 port;
    s32 addr;
    s32 count;
    s32 chip;
    u32 sum;
    u8 a;
    u8 b;
    u8 c;
    u8 d;
    u8* p;
    if (rom == 0) {
        chip = 0;
        mode = 0;
    } else if (rom > 2) {
        chip = rom - 2;
        mode = 0;
    } else {
        chip = rom - 1;
        mode = 1;
    }
    if (mode == 0) {
        if (chip == 0 || wide != 0) {
            count = 0x400000;
        } else {
            count = 0x1000000;
        }
        sum = 0;
        for (addr = 0; count > 0; addr++, count--) {
            bank = (chip - 1) * 8 + ((addr >> 21) & 0x3F) + 2;
            port = (addr & 0x1FFFFF) + SIMM_WINDOW;
            *(volatile u16*)SIMM_BANK_REG = bank;
            while (1) {
                a = *(volatile u8*)port;
                b = *(volatile u8*)port;
                c = *(volatile u8*)port;
                d = *(volatile u8*)port;
                if (a == b && c == d) {
                    break;
                }
            }
            sum += a;
        }
    } else {
        count = 0x800000;
        sum = 0;
        addr = (chip << 23) + 0x26000000;
        p = (u8*)((u32)&a + CACHE_THRU);
        for (; count > 0; addr++, count--) {
            dma0_transfer_wait(addr, (u32)p, 1, 0);
            sum += *p;
        }
    }
    return sum;
}



/* provisional name: unreferenced; sums one byte of each half of the given graphics SIMM banks */
s32 simm_bank_checksum(s32 slot, s32 count) {
    volatile u8* p;
    s32 i;
    s32 start;
    u32 sum;
    u8 a;
    u8 b;
    u8 c;
    u8 d;
    if (slot == 0) {
        start = 0;
    } else if (slot > 2) {
        start = (slot - 3) * 8 + 2;
    } else {
        return -1;
    }
    sum = 0;
    for (i = start; i < start + count; i++) {
        *(volatile u16*)SIMM_BANK_REG = i;
        p = (volatile u8*)SIMM_WINDOW;
        while (1) {
            a = *p;
            b = *p;
            c = *p;
            d = *p;
            if (a == b && c == d) {
                break;
            }
        }
        sum += a;
        p = (volatile u8*)(SIMM_WINDOW + 0x100000);
        while (1) {
            a = *p;
            b = *p;
            c = *p;
            d = *p;
            if (a == b && c == d) {
                break;
            }
        }
        sum += a;
    }
    return sum % 256;
}



/* provisional name */
s32 simm_quick_checksum(s32 slot, s32 mode) {
    s32 i;
    s32 flash;
    s32 bank;
    s32 start;
    s32 count;
    u32 base;
    s32 sum;
    u8 b;
    u8* p;
    if (slot == 0) {
        bank = 0;
        flash = 0;
    } else if (slot > 2) {
        bank = slot - 2;
        flash = 0;
    } else {
        bank = slot - 1;
        flash = 1;
    }
    if (flash == 0) {
        if (slot == 0) {
            start = 0;
        } else {
            start = (slot - 3) * 8 + 2;
        }
        if (bank == 0 || mode != 0) {
            count = 2;
        } else {
            count = 8;
        }
        sum = 0;
        for (i = start; i < start + count; i++) {
            *(volatile u16*)SIMM_BANK_REG = i;
            sum += *(u8*)(simm_sum_offset_tbl[0] + SIMM_WINDOW);
            sum += *(u8*)(simm_sum_offset_tbl[1] + SIMM_WINDOW);
            sum += *(u8*)(simm_sum_offset_tbl[2] + SIMM_WINDOW);
            sum += *(u8*)(simm_sum_offset_tbl[3] + SIMM_WINDOW);
        }
    } else {
        base = bank * 0x800000 + 0x26000000;
        sum = 0;
        p = (u8*)((u32)&b + CACHE_THRU);
        for (i = 0; i < 16; i++) {
            dma0_transfer_wait(simm_sum_offset_tbl[i] + base, (u32)p, 1, 0);
            sum += *p;
        }
    }
    return sum;
}



/* provisional name */
s32 scsi_test_unit_ready(s32 lun) {
    scsi_send_cdb_bytes(6, cdb_test_unit_ready);
    return scsi_send_cdb_and_read(0, 0);
}



/* provisional name */
s32 scsi_inquiry(s32 len, s32 lun, u8* buf) {
    scsi_send_cdb_bytes(6, cdb_inquiry);
    return scsi_send_cdb_and_read(len, buf);
}



/* provisional name */
s32 scsi_read_capacity(s32 len, void* buf) {
    scsi_send_cdb_bytes(10, cdb_read_capacity);
    return scsi_send_cdb_and_read(len, buf);
}



/* provisional name */
s32 scsi_request_sense(s32 len, s32 lun, u8* buf) {
    scsi_send_cdb_bytes(6, cdb_request_sense);
    return scsi_send_cdb_and_read(len, buf);
}



/* provisional name */
s32 scsi_start_stop_unit(s32 op, s32 lun) {
    s8 cdb[12];
    if (no_cd_flag) {
        return 0;
    }
    cdb[0] = 0x1B;
    cdb[1] = 0;
    cdb[2] = 0;
    cdb[3] = 0;
    cdb[4] = op & 3;
    cdb[5] = 0;
    scsi_send_cdb_bytes(6, cdb);
    return scsi_send_cdb_and_read(0, 0);
}



/* provisional name */
s32 scsi_prevent_allow_medium_removal(s32 prevent, s32 lun) {
    s8 cdb[12];
    cdb[0] = 0x1E;
    cdb[1] = 0;
    cdb[2] = 0;
    cdb[3] = 0;
    cdb[4] = prevent & 1;
    cdb[5] = 0;
    scsi_send_cdb_bytes(6, cdb);
    return scsi_send_cdb_and_read(0, 0);
}



/* provisional name */
s32 scsi_read_10(s32 lba, s32 count, s32 blk, s32 unused, void* buf) {
    s8 cdb[10];
    cdb[0] = 0x28;
    cdb[1] = 0;
    cdb[2] = (lba & 0xFF000000) >> 24;
    cdb[3] = (lba & 0xFF0000) >> 16;
    cdb[4] = (lba & 0xFF00) >> 8;
    cdb[5] = lba;
    cdb[6] = 0;
    cdb[7] = (count & 0xFF00) >> 8;
    cdb[8] = count;
    cdb[9] = 0;
    scsi_send_cdb_bytes(10, cdb);
    return scsi_send_cdb_and_read((blk + 1) * count << 8, buf);
}



/* provisional name */
s32 scsi_send_cdb_bytes(s32 n, const s8* cdb) {
    s32 i;
    const s8* p;
    p = cdb;
    scsi_cdb_len = n;
    CD_SELECT = SCSI_CDB1;
    delay_cycles(17);
    for (i = 0; i < n; i++, p++) {
        CD_DATA = *p;
        delay_cycles(17);
    }
    return 0;
}



/* provisional name */
s32 scsi_send_cdb_and_read(s32 lba, u8* buf) {
    s32 count;
    u8* dst;
    u8 cmd;
    u16 phase;
    u16 w14;
    u16 msg;
    u32 addr;
    s32 tries;
    u16 result;
    dst = buf;
    cmd = 33;
    tries = 0;
    scsi_error = 0;
    CD_SELECT = SCSI_OWN_ID;
    delay_cycles(17);
    CD_DATA = scsi_cdb_len;
    delay_cycles(17);
    cmd |= 0x40;
    CD_SELECT = SCSI_TARGET_LUN;
    delay_cycles(17);
    CD_DATA = 0;
    delay_cycles(17);
    CD_DATA = 0;
    delay_cycles(17);
    CD_DATA = 32;
    delay_cycles(17);
    CD_DATA = (s16)((lba & 0xFF0000) >> 16);
    delay_cycles(17);
    CD_DATA = (lba & 0xFF00) >> 8;
    delay_cycles(17);
    CD_DATA = lba & 0xFF;
    delay_cycles(17);
    CD_SELECT = SCSI_DEST_ID;
    delay_cycles(17);
    CD_DATA = cmd;
    delay_cycles(17);
    while (1) {
        tries++;
        for (count = 255; count > 0; count--) {
            if ((CD_AUX_STATUS & AUX_BUSY) == 0) {
                break;
            }
        }
        if (count == 0) {
            scsi_error = 2;
            return -1;
        }
        while (1) {
            if ((CD_AUX_STATUS & AUX_INT) == 0) {
                break;
            }
            CD_SELECT = SCSI_STATUS;
            delay_cycles(17);
            w14 = CD_DATA;
        }
        CD_SELECT = SCSI_COMMAND;
        delay_cycles(17);
        CD_DATA = SCSI_SEL_ATN_XFER;
        delay_cycles(17);
        count = 0;
        while (1) {
            if (CD_AUX_STATUS & AUX_DBR) {
                count = 0;
                CD_SELECT = SCSI_DATA;
                delay_cycles(17);
                *dst = CD_DATA;
                dst++;
            } else {
                count++;
            }
            if (CD_AUX_STATUS & AUX_INT) {
                break;
            }
            if (count == 0xFFFF0) {
                scsi_error = 2;
                return -1;
            }
        }
        CD_SELECT = SCSI_STATUS;
        delay_cycles(17);
        phase = CD_DATA & 0xFF;
        if (phase == 22) {
            break;
        }
        CD_SELECT = SCSI_COUNT_2ND;
        delay_cycles(17);
        addr = (CD_DATA & 0xFF) << 16;
        addr |= (CD_DATA & 0xFF) << 8;
        addr |= CD_DATA & 0xFF;
        CD_SELECT = SCSI_COMMAND_PHASE;
        delay_cycles(17);
        msg = CD_DATA & 0xFF;
        switch (phase) {
        case 75:
            CD_SELECT = SCSI_COMMAND_PHASE;
            delay_cycles(17);
            CD_DATA = 70;
            delay_cycles(17);
            CD_SELECT = SCSI_COUNT_MSB;
            delay_cycles(17);
            CD_DATA = 0;
            delay_cycles(17);
            CD_DATA = 0;
            delay_cycles(17);
            CD_DATA = 0;
            delay_cycles(17);
            break;
        case 133:
            if (msg != 67) {
                scsi_error = 1;
                return -1;
            }
            while ((CD_AUX_STATUS & AUX_INT) == 0) {
            }
            phase = CD_DATA & 0xFF;
            if (phase == 128) {
                CD_SELECT = SCSI_COMMAND_PHASE;
                delay_cycles(17);
                CD_DATA = 68;
                delay_cycles(17);
            } else if (phase == 129) {
                CD_SELECT = SCSI_DATA;
                delay_cycles(17);
                w14 = CD_DATA;
                CD_SELECT = SCSI_COMMAND_PHASE;
                delay_cycles(17);
                CD_DATA = 69;
                delay_cycles(17);
            } else {
                scsi_error = 1;
                return -1;
            }
            CD_SELECT = SCSI_SYNC_TRANSFER;
            delay_cycles(17);
            CD_DATA = 32;
            delay_cycles(17);
            CD_DATA = (addr & 0xFF0000) >> 16;
            delay_cycles(17);
            CD_DATA = (addr & 0xFF00) >> 8;
            delay_cycles(17);
            CD_DATA = addr & 0xFF;
            delay_cycles(17);
            break;
        default:
            scsi_error = 1;
            return -1;
        }
    }
    CD_SELECT = SCSI_CONTROL;
    delay_cycles(17);
    w14 = CD_DATA;
    if ((w14 & 8) == 0) {
        while (1) {
            if (CD_AUX_STATUS & AUX_INT) {
                break;
            }
        }
        CD_SELECT = SCSI_STATUS;
        delay_cycles(17);
        phase = CD_DATA & 0xFF;
        if (phase != 133) {
            CD_SELECT = SCSI_TARGET_LUN;
            delay_cycles(17);
            result = CD_DATA & 0x1F;
            scsi_error = 1;
            return -1;
        }
    }
    CD_SELECT = SCSI_TARGET_LUN;
    delay_cycles(17);
    result = CD_DATA & 0x1F;
    return result;
}



/* provisional name */
s32 scsi_decode_sense_key(s32 status) {
    switch (status) {
    case -1:
        if (scsi_error == 2) {
            return -1;
        } else {
            return 1;
        }
        break;
    case 0:
        return 0;
    case 8:
        return 1;
    case 24:
        return -1;
    case 2:
    default:
        if (scsi_request_sense(22, 1, (u8*)scsi_sense_buf)) {
            return -1;
        }
        break;
    }
    scsi_sense_key = scsi_sense_buf[2];
    scsi_sense_asc = scsi_sense_buf[12];
    switch (scsi_sense_key) {
    case 0:
    case 1:
        scsi_error = 0;
        return 0;
        break;
    case 2:
        switch (scsi_sense_asc) {
        case 4:
            return 1;
        case 58:
        default:
            return -1;
        }
    case 7:
        return -1;
    case 5:
        return -1;
    case 3:
    case 4:
    case 6:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    default:
        return 1;
    }
}
