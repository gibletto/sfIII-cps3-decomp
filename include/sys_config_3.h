#ifndef SYS_CONFIG_3_H
#define SYS_CONFIG_3_H

#include "structs.h"

void dma_src_ack_seq(void);
void sprite_dma_end_wait(void);
void init_render_lists(void);
void render_list_primary_alloc(void);
void sprite_template_chain_init(void);
void sprite_template_pool_init(void);

#endif
