#ifndef SYS_CONFIG_3_H
#define SYS_CONFIG_3_H

#include "structs.h"

void sprite_dma_start(void);
void sprite_dma_end_wait(void);
void init_render_lists(void);
void cram_blank_slot_alloc(void);
void sprite_template_chain_init(void);
void sprite_template_pool_init(void);

#endif
