#ifndef SYS_CONFIG_H
#define SYS_CONFIG_H

#include "structs.h"

void eeprom_config_reset(void);
s8 config_bytes_equal(u8* a, u8* b, s32 n);
void eeprom_config_save(void);
void eeprom_config_default(void);
void eeprom_config_verify(void);
void eeprom_config_load(void);
void eeprom_config_apply();
u16 simmram_slot_to_code(s16 n);
void sprite_list_shift_x(SPR16* dst, SPR16* src, s16 dx, s32 n);
u16 simmram_slot_to_cg_no(s16 n);
s32 polygon2d_queue_quad(u32 a, u32 b, u32 c, u16 lo, u16 hi, s16 pri);
u32 simmram_small_page_alloc_40(s32 kind);
void poly_queue_init(s32 offset);
void poly_bank_flip(void);
void sprite_bank_flip(void);
u32 simmram_slot_to_page_offset(s16 slot);
u32 simmram_freelist_init_10(void);
s32 polygon2d_submit_line();
s32 polygon2d_submit_quad();
s32 simmram_block_alloc_10(s32 blocks, s32 kind);
s16 simmram_block_alloc_40(s32 blocks, s32 kind);
void simmram_block_free_10(s32 blk);
void simmram_block_free_40(s32 blk);
u32 simmram_big_page_alloc_40(s32 kind);
u32 simmram_freelist_init(void);
u32 simmram_slot_addr(s16 no);
u32 simmram_slot_to_offset(s16 handle);
void sprite_display_list_build(void);
SPRITE_ENTRY* sprite_entry_alloc(s8 layer);
void sprite_layer_free(s8 layer);
void sprite_entry_push_prio();
s32 sprite_list_clear(s16 list);
s32 sprite_list_submit(s16 slot);
void sprite_poly_queue_drain_try(void);
void sprite_poly_queue_drain_wait(void);
void sprite_polygon_flush_queue(s32 kind);
void sprite_list_init(s32 list);
void sprite_pools_init(void);
s32 sprite_list_setup(s16 slot, s16 owner, s16* data);

#endif
