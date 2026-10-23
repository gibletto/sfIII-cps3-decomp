/*
 * SPR_LIST.C  Fixed sprite lists
 *
 * sprite_list_setup / _submit / _clear keep the four fixed sprite lists in SIMM RAM and add them to the
 * sprite entry pools.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "cps3.h"

SPRITE_LIST sprite_list_w[4];  /* 02078A40 */


/* provisional name: unreferenced; clears every sprite list (0) or list n-1 */
void sprite_list_init(s32 list) {
    s32 j;
    s32 i;
    if (list == 0) {
        for (j = 0; j < 4; j++) {
            for (i = 0; i < 8; i++) {
                sprite_list_w[j].rec[i].flag = 0;
            }
            sprite_list_w[j].pad0 = 0;
            sprite_list_w[j].count = 0;
            sprite_list_w[j].slot = 0;
        }
    } else {
        for (i = 0; i < 8; i++) {
            sprite_list_w[list - 1].rec[i].flag = 0;
        }
        sprite_list_w[list - 1].pad0 = 0;
        sprite_list_w[list - 1].count = 0;
        sprite_list_w[list - 1].slot = 0;
    }
}



/* provisional name */
s32 sprite_list_setup(s16 slot, s16 owner, s16* data) {
    s16 n_grp;
    s16 n_ent;
    s16* p;
    SPRITE_ENTRY* g;
    SPRENTRY* e;
    n_grp = 0;
    n_ent = 0;
    p = data;
    while (*p != -1) {
        p += 2;
        n_grp++;
        while (*p != -1) {
            n_ent++;
            p += 3;
        }
        p++;
    }
    if ((sprite_list_w[slot].count = n_grp) == 0) {
        return 0;
    }
    if (n_ent == 0) {
        return 0;
    }
    if ((sprite_list_w[slot].slot = simmram_block_alloc_40(n_ent / 16 + 1, owner)) == 0) {
        return 0;
    }
    e = (SPRENTRY*)simmram_slot_addr(sprite_list_w[slot].slot);
    n_grp = 0;
    while (*data != -1) {
        g = &sprite_list_w[slot].rec[n_grp];
        g->w0 = (*data & 7) << 12;
        data++;
        g->prio = *data;
        data++;
        g->w4 = 0;
        g->w6 = 0;
        g->w2 = ((s32)e - SPRITE_RAM) / 16;
        g->flag = 1;
        n_grp++;
        while (*data != -1) {
            g->w0++;
            e->w0 = 0;
            e->w2 = 0;
            e->w4 = 0;
            e->code = *data;
            data++;
            e->pos = *data;
            data++;
            e->attr = (slot & 3) * 16 | (*data & 0xF);
            data++;
            e++;
        }
        data++;
    }
    if (sprite_list_submit(slot) == 0) {
        return 0;
    }
    return 1;
}



/* provisional name */
s32 sprite_list_submit(s16 list) {
    s16 j;
    SPRITE_ENTRY* rec;
    SPRITE_ENTRY* e;
    if (sprite_list_w[list].count == 0) {
        return 0;
    }
    for (j = 0; j < sprite_list_w[list].count; j++) {
        rec = &sprite_list_w[list].rec[j];
        if (rec->flag == 1) {
            e = sprite_entry_alloc(1);
            if (e == 0) {
                return 0;
            }
        }
        e->w0 = rec->w0;
        e->w4 = rec->w4;
        e->w6 = rec->w6;
        e->w2 = rec->w2;
        sprite_entry_push_prio(e, (s16)rec->prio);
    }
    return 1;
}



/* provisional name */
s32 sprite_list_clear(s16 list) {
    s16 j;
    s16 unused;
    unused = 0;
    if (sprite_list_w[list].count == 0) {
        return 0;
    }
    sprite_list_w[list].count = 0;
    for (j = 0; j < sprite_list_w[list].count; j++) {
        sprite_list_w[list].rec[j].flag = 0;
    }
    simmram_block_free_40(sprite_list_w[list].slot);
    return 1;
}
