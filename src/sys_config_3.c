/*
 * SYS_CONFIG_3.C  Render list setup and the sprite DMA handshake
 *
 * Display management: init_render_lists sets up the sprite pools (SPR_POOL.C), the SIMM RAM free
 * lists (simmram.src), the polygon transfer queue (POLY_QUE.C), the fixed sprite lists (SPR_LIST.C) and the
 * sprite templates; dma_src_ack_seq and sprite_dma_end_wait drive the sprite DMA handshake.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CMD_MAIN.h"
#include "cmd_main_2.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "eeprom.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "cram_bank.h"
#include "game_config_main.h"
#include "sys_config.h"
#include "sys_config_3.h"
#include "cps3.h"



u16 sprite_dummy_code = 0;  /* 02007380 */


/* provisional name */
void init_render_lists(void) {
    s32 unused;
    sprite_template_pool_init();
    cram_bank_init();
    sprite_pools_init();
    simmram_freelist_init();
    simmram_freelist_init_10();
    render_list_primary_alloc();
    poly_queue_init(simmram_slot_to_offset(simmram_block_alloc_10(2, 0)));
    sprite_template_chain_init();
    sprite_list_clear(0);
    sprite_list_clear(1);
    sprite_list_clear(2);
    sprite_list_clear(3);
}



/* provisional name */
void render_list_primary_alloc(void) {
    u16* p;
    s32 i;
    p = (u16*)(simmram_slot_to_offset(simmram_block_alloc_10(1, 0)) + CHARACTER_RAM);
    for (i = 0; i < 0x800; i++) {
        *p = 0;
        p++;
    }
}



/* provisional name */
void sprite_template_pool_init(void) {
    s32 unused;
    s32 i;
    u16* p;
    p = (u16*)SPRITE_RAM;
    *p = 16;
    p++;
    *p = sprite_dummy_code;
    p++;
    *p = sprite_head_x;
    p++;
    *p = sprite_head_y;
    p++;
    *p = 0;
    p++;
    *p = 0;
    p += 3;
    for (i = 0; i < 22; i++) {
        *p = 16;
        p++;
        *p = sprite_dummy_code;
        p++;
        *p = sprite_pad_x;
        p++;
        *p = sprite_pad_y;
        p++;
        *p = 0;
        p++;
        *p = 0;
        p += 3;
    }
    *p = 0x8000;
    dma_src_ack_seq();
    sprite_dma_end_wait();
}



/* provisional name */
void sprite_template_chain_init(void) {
    s32 i;
    u16 slot;
    u16 link;
    u16* p;
    slot = simmram_block_alloc_40(1, 0);
    if (slot == 0) {
        return;
    }
    sprite_dummy_code = simmram_slot_to_code(slot);
    p = (u16*)simmram_slot_addr(slot);
    link = 0x3FF;
    for (i = 0; i < 16; i++) {
        p[0] = 0;
        p[1] = 0x1FF;
        p[2] = 0x200;
        p[3] = link;
        p[4] = 0x0F0F;
        p[5] = 5;
        link = (link + 0xFFF0) & 0x3FF;
        p += 8;
    }
}

/* provisional name */
void dma_src_ack_seq(void) {
    s32 unused;
    *(volatile u16 *)DMA_CTRL_REG = 8;
    *(volatile u16 *)DMA_CTRL_REG = 9;
    *(volatile u16 *)DMA_CTRL_REG = 8;
    *(volatile u16 *)DMA_CTRL_REG = 9;
    *(volatile u16 *)DMA_CTRL_REG = 8;
    *(volatile u16 *)DMA_CTRL_REG = 9;
    *(volatile u16 *)DMA_CTRL_REG = 8;
    *(volatile u16 *)DMA_CTRL_REG = 9;
}

/* Called from the vertical blank interrupt: wait until the sprite DMA has
   finished, then clear the DMA control register. */
/* provisional name */
void sprite_dma_end_wait(void) {
    while (*(volatile u16 *)DMA_STATUS_REG & 1) {
    }
    *(volatile u16 *)DMA_CTRL_REG = 0;
}
