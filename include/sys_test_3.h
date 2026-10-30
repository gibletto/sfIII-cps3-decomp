#ifndef SYS_TEST_3_H
#define SYS_TEST_3_H

#include "structs.h"

void memtest_sram(void);
s32 cd_check_disc_id(void);
void simm_check_run(void);
void memtest_menu_init(void);
void memtest_menu_select(void);
s32 memtest_page(void);
u8 sram_read_byte(u32 addr);
void sram_write_byte(u32 addr, u8 v);
void sram_bus_slow(void);
void sram_bus_normal(void);
u32 simm_full_checksum(s32 rom, s32 wide);
s32 simm_bank_checksum(s32 slot, s32 count);
void memtest_work_ram(void);
void memtest_memory_check(void);
void memtest_sprite_ram(void);
void memtest_character_ram(void);
void memtest_simm_quick(void);
s32 simm_quick_checksum(s32 slot, s32 mode);
void memtest_ss_ram(void);
void memtest_color_ram(void);
void memtest_eeprom(void);
void memtest_cdrom(void);
s32 cd_check_drive_inquiry(void);
u32 memtest_pattern_word(volatile u16* addr, u32 size);
u16 * memtest_pattern_byte_lane(u16 *start, u32 size);
u32 memtest_pattern_masked_word(volatile u16* addr, u32 size);
s32 scsi_decode_sense_key(s32 status);
s32 scsi_inquiry(s32 len, s32 lun, u8* buf);
s32 scsi_prevent_allow_medium_removal(s32 prevent, s32 lun);
s32 scsi_read_10(s32 lba, s32 count, s32 blk, s32 unused, void* buf);
s32 scsi_read_capacity(s32 len, void* buf);
s32 scsi_request_sense(s32 len, s32 lun, u8* buf);
s32 scsi_send_cdb_and_read(s32 lba, u8* buf);
s32 scsi_send_cdb_bytes(s32 n, const s8* cdb);
s32 scsi_start_stop_unit(s32 start, s32 immed);
s32 scsi_test_unit_ready(s32 lun);

#endif
