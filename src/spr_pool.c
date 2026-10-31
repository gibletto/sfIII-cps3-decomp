/*
 * SPR_POOL.C  Sprite entry pools
 *
 * The double-buffered sprite entry pools: sprite_entry_alloc takes an entry of a layer from the pool being
 * filled, sprite_entry_push_prio links it into that pool's priority list, sprite_display_list_build turns the
 * other pool's lists into the sprite display list, and sprite_bank_flip swaps the pools each frame, carrying
 * over the entries of the fixed layers.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "cps3.h"

s32 frame_ready;  /* 0205ED74 */
SPRITE_ENTRY spr_entry_a[512];  /* 0205ED78 */
SPRITE_ENTRY spr_entry_b[512];  /* 02061578 */
SPRITE_ENTRY * spr_prio_a[0x80];  /* 02063D78 */
SPRITE_ENTRY * spr_prio_b[0x80];  /* 02063F78 */
u16 spr_cnt0_a;  /* 02064178 */
u16 spr_cnt0_b;  /* 0206417A */
u16 spr_cnt1_a;  /* 0206417C */
u16 spr_cnt1_b;  /* 0206417E */
u16 spr_cnt2_a;  /* 02064180 */
u16 spr_cnt2_b;  /* 02064182 */
u16 spr_cnt3_a;  /* 02064184 */
u16 spr_cnt3_b;  /* 02064186 */
u16 spr_cnt4_a;  /* 02064188 */
u16 spr_cnt4_b;  /* 0206418A */
u8 spr_bank;  /* 0206418C */
s8 spr_list_ready;  /* 0206418D */


u16 sprite_head_x = 0;  /* 02007384 */
u16 sprite_head_y = 0;  /* 02007386 */
u16 sprite_pad_x = 0;  /* 02007388 */
u16 sprite_pad_y = 0;  /* 0200738A */
u32 spr_pool_busy = 0;  /* 0200738C */


/* provisional name */
void sprite_pools_init(void)
{
    s32 i;
    s32 unused;
    spr_pool_busy = 1;
    spr_cnt0_a = 0;
    spr_cnt0_b = 0;
    spr_cnt1_a = 0;
    spr_cnt1_b = 0;
    spr_cnt2_a = 0;
    spr_cnt2_b = 0;
    spr_cnt3_a = 0;
    spr_cnt3_b = 0;
    spr_cnt4_a = 0;
    spr_cnt4_b = 0;
    spr_list_ready = 0;
    for (i = 0; i < 128; i++) {
        spr_prio_a[i] = 0;
        spr_prio_b[i] = 0;
    }
    for (i = 0; i < 512; i++) {
        spr_entry_a[i].flag = 0;
        spr_entry_b[i].flag = 0;
    }
    spr_pool_busy = 0;
}



/* provisional name */
SPRITE_ENTRY* sprite_entry_alloc(s8 layer) {
    u16 ix;
    SPRITE_ENTRY* e;
    switch (layer) {
    case 0:
        if (spr_bank) {
            ix = spr_cnt0_b;
            if (ix > 255) {
                return 0;
            }
            spr_cnt0_b++;
            break;
        } else {
            ix = spr_cnt0_a;
            if (ix > 255) {
                return 0;
            }
            spr_cnt0_a++;
        }
        break;
    case 1:
        if (spr_bank) {
            ix = spr_cnt1_b;
            if (ix > 63) {
                return 0;
            }
            spr_cnt1_b++;
            ix += 0x100;
            break;
        } else {
            ix = spr_cnt1_a;
            if (ix > 63) {
                return 0;
            }
            spr_cnt1_a++;
            ix += 0x100;
        }
        break;
    case 2:
        if (spr_bank) {
            ix = spr_cnt2_b;
            if (ix > 63) {
                return 0;
            }
            spr_cnt2_b++;
            ix += 0x140;
            break;
        } else {
            ix = spr_cnt2_a;
            if (ix > 63) {
                return 0;
            }
            spr_cnt2_a++;
            ix += 0x140;
        }
        break;
    case 3:
        if (spr_bank) {
            ix = spr_cnt3_b;
            if (ix > 63) {
                return 0;
            }
            spr_cnt3_b++;
            ix += 0x180;
            break;
        } else {
            ix = spr_cnt3_a;
            if (ix > 63) {
                return 0;
            }
            spr_cnt3_a++;
            ix += 0x180;
        }
        break;
    case 4:
        if (spr_bank) {
            ix = spr_cnt4_b;
            if (ix > 63) {
                return 0;
            }
            spr_cnt4_b++;
            ix += 0x1C0;
            break;
        } else {
            ix = spr_cnt4_a;
            if (ix > 63) {
                return 0;
            }
            spr_cnt4_a++;
            ix += 0x1C0;
        }
        break;
    }
    if (spr_bank) {
        e = &spr_entry_b[ix];
    } else {
        e = &spr_entry_a[ix];
    }
    e->flag = 1;
    e->layer = layer;
    return e;
}



/* provisional name: unreferenced; frees the entries of a layer and of every layer after it */
void sprite_layer_free(s8 layer) {
    s32 i;
    switch (layer) {
    case 1:
        if (spr_bank) {
            for (i = 0; i < 63; i++) {
                spr_entry_b[i + 0x100].flag = 0;
            }
        } else {
            for (i = 0; i < 63; i++) {
                spr_entry_a[i + 0x100].flag = 0;
            }
        }
    case 2:
        if (spr_bank) {
            for (i = 0; i < 63; i++) {
                spr_entry_b[i + 0x140].flag = 0;
            }
        } else {
            for (i = 0; i < 63; i++) {
                spr_entry_a[i + 0x140].flag = 0;
            }
        }
    case 3:
        if (spr_bank) {
            for (i = 0; i < 63; i++) {
                spr_entry_b[i + 0x180].flag = 0;
            }
        } else {
            for (i = 0; i < 63; i++) {
                spr_entry_a[i + 0x180].flag = 0;
            }
        }
    case 4:
        if (spr_bank) {
            for (i = 0; i < 63; i++) {
                spr_entry_b[i + 0x1C0].flag = 0;
            }
        } else {
            for (i = 0; i < 63; i++) {
                spr_entry_a[i + 0x1C0].flag = 0;
            }
        }
    }
}



/* provisional name */
void sprite_entry_push_prio(entry, level)
SPRITE_ENTRY* entry;
u16 level;
{
    entry->prio = level;
    if (spr_bank) {
        entry->next = spr_prio_b[level];
        spr_prio_b[level] = entry;
    } else {
        entry->next = spr_prio_a[level];
        spr_prio_a[level] = entry;
    }
}



/* provisional name */
void sprite_display_list_build(void) {
    SPRITE_ENTRY* rec;
    SPRITE_ENTRY* unused_rec;
    u16* dst;
    u16* unused_dst;
    s32 unused_a;
    s32 i;
    s32 unused_b;
    s32 unused_c;
    s32 total;
    s32 count;
    s32 unused_d;
    s32 unused_e;
    if (spr_list_ready) {
        count = 1;
        total = 16;
        spr_list_ready = 0;
        dst = (u16*)SPRITE_RAM;
        *dst = 16;
        dst++;
        *dst = sprite_dummy_code;
        dst++;
        *dst = sprite_head_x;
        dst++;
        *dst = sprite_head_y;
        dst++;
        *dst = 0;
        dst++;
        *dst = 0;
        dst += 3;
        if (spr_bank) {
            for (i = 127; i >= 0; i--) {
                rec = spr_prio_a[i];
                if (rec) {
                    while (rec->flag != 0) {
                        total += (s16)rec->w0 & 0x1FF;
                        *dst = rec->w0;
                        dst++;
                        *dst = rec->w2;
                        dst++;
                        *dst = rec->w4;
                        dst++;
                        *dst = rec->w6;
                        dst++;
                        *dst = rec->w8;
                        dst++;
                        *dst = rec->w10;
                        dst += 3;
                        rec = rec->next;
                        if (++count >= 0x1FF) {
                            *dst = 0x8000;
                            return;
                        }
                    }
                }
            }
        } else {
            for (i = 127; i >= 0; i--) {
                rec = spr_prio_b[i];
                if (rec) {
                    while (rec->flag != 0) {
                        total += (s16)rec->w0 & 0x1FF;
                        *dst = rec->w0;
                        dst++;
                        *dst = rec->w2;
                        dst++;
                        *dst = rec->w4;
                        dst++;
                        *dst = rec->w6;
                        dst++;
                        *dst = rec->w8;
                        dst++;
                        *dst = rec->w10;
                        dst += 3;
                        rec = rec->next;
                        if (++count >= 0x1FF) {
                            *dst = 0x8000;
                            return;
                        }
                    }
                }
            }
        }
        if (total < 350) {
            for (i = 0; i < (350 - total) / 16 + 1; i++) {
                *dst = 16;
                dst++;
                *dst = sprite_dummy_code;
                dst++;
                *dst = sprite_pad_x;
                dst++;
                *dst = sprite_pad_y;
                dst++;
                *dst = 0;
                dst++;
                *dst = 0;
                dst += 3;
            }
            count++;
            if (count >= 0x1FF) {
                *dst = 0x8000;
                return;
            }
        }
        *dst = 0x8000;
    }
}



/* provisional name */
void sprite_bank_flip(void) {
    s32 i;
    SPRITE_ENTRY* src;
    SPRITE_ENTRY* rec;
    s32 unused;
    if (spr_bank) {
        spr_bank = 0;
    } else {
        spr_bank = 1;
    }
    if (spr_bank) {
        for (i = 0; i < 0x200; i++) {
            spr_entry_b[i].flag = 0;
        }
        spr_cnt0_b = 0;
        spr_cnt1_b = 0;
        spr_cnt2_b = 0;
        spr_cnt3_b = 0;
        spr_cnt4_b = 0;
        for (i = 0; i < 0x80; i++) {
            spr_prio_b[i] = 0;
        }
        sprite_list_submit(0);
        sprite_list_submit(1);
        sprite_list_submit(2);
        sprite_list_submit(3);
        for (i = 0; i < 63; i++) {
            src = &spr_entry_a[i + 320];
            if (src->flag) {
                rec = sprite_entry_alloc(2);
                rec->w0 = src->w0;
                rec->w2 = src->w2;
                rec->w4 = src->w4;
                rec->w6 = src->w6;
                rec->w8 = src->w8;
                rec->w10 = src->w10;
                sprite_entry_push_prio(rec, (s16)src->prio);
            }
        }
        for (i = 0; i < 63; i++) {
            src = &spr_entry_a[i + 384];
            if (src->flag) {
                rec = sprite_entry_alloc(3);
                rec->w0 = src->w0;
                rec->w2 = src->w2;
                rec->w4 = src->w4;
                rec->w6 = src->w6;
                rec->w8 = src->w8;
                rec->w10 = src->w10;
                sprite_entry_push_prio(rec, (s16)src->prio);
            }
        }
        for (i = 0; i < 63; i++) {
            src = &spr_entry_a[i + 448];
            if (src->flag) {
                rec = sprite_entry_alloc(4);
                rec->w0 = src->w0;
                rec->w2 = src->w2;
                rec->w4 = src->w4;
                rec->w6 = src->w6;
                rec->w8 = src->w8;
                rec->w10 = src->w10;
                sprite_entry_push_prio(rec, (s16)src->prio);
            }
        }
    } else {
        for (i = 0; i < 0x200; i++) {
            spr_entry_a[i].flag = 0;
        }
        spr_cnt0_a = 0;
        spr_cnt1_a = 0;
        spr_cnt2_a = 0;
        spr_cnt3_a = 0;
        spr_cnt4_a = 0;
        for (i = 0; i < 0x80; i++) {
            spr_prio_a[i] = 0;
        }
        sprite_list_submit(0);
        sprite_list_submit(1);
        sprite_list_submit(2);
        sprite_list_submit(3);
        for (i = 0; i < 63; i++) {
            src = &spr_entry_b[i + 320];
            if (src->flag) {
                rec = sprite_entry_alloc(2);
                rec->w0 = src->w0;
                rec->w2 = src->w2;
                rec->w4 = src->w4;
                rec->w6 = src->w6;
                rec->w8 = src->w8;
                rec->w10 = src->w10;
                sprite_entry_push_prio(rec, (s16)src->prio);
            }
        }
        for (i = 0; i < 63; i++) {
            src = &spr_entry_b[i + 384];
            if (src->flag) {
                rec = sprite_entry_alloc(3);
                rec->w0 = src->w0;
                rec->w2 = src->w2;
                rec->w4 = src->w4;
                rec->w6 = src->w6;
                rec->w8 = src->w8;
                rec->w10 = src->w10;
                sprite_entry_push_prio(rec, (s16)src->prio);
            }
        }
        for (i = 0; i < 63; i++) {
            src = &spr_entry_b[i + 448];
            if (src->flag) {
                rec = sprite_entry_alloc(4);
                rec->w0 = src->w0;
                rec->w2 = src->w2;
                rec->w4 = src->w4;
                rec->w6 = src->w6;
                rec->w8 = src->w8;
                rec->w10 = src->w10;
                sprite_entry_push_prio(rec, (s16)src->prio);
            }
        }
    }
    spr_list_ready = 1;
}
