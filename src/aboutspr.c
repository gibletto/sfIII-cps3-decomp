/*
 * ABOUTSPR.C  Character sprite graphics and display lists
 *
 * Builds character and effect cells, manages graphics slots and queues sprite lists by
 * priority. Prebuilt cell tables supply shadows, hit marks and the seraph effect. Connected
 * works combine several graphics sets; the judge-area display draws hit and hurt boxes.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Sub.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "cps3.h"

#define CHAR_GFX_ROM_BEGIN 0x06480000

CharGfxSlot cg_slot_tbl[384];
CharGfxEntry * cg_data_list;

extern s16 mark_gfx_ofs[128];    /* provisional name */
extern s16 mark_gfx_cells[128];  /* provisional name */
extern s16 mark_gfx_colcd[128];  /* provisional name */
extern const s16 mark_cg_tbl[46];       /* provisional name */
extern const s16 mark_index_tbl[5][9];  /* provisional name */
extern const s16 zoom_down_tbl[64];     /* provisional name */
extern const s16 zoom_up_tbl[64];       /* provisional name */


/* provisional name */
void init_char_gfx_tables(void) {
    s16 i;
    cg_data_list = (CharGfxEntry*)cg_data_tbl;
    for (i = 0; i < 384; i++) {
        cg_slot_tbl[i].addr = cg_slot_tbl[i].handle = 0;
    }
    for (i = 0; i < 64; i++) {
        (&kage_gfx_ofs[0])[i] = kage_gfx_cells[i] = 0;
    }
    for (i = 0; i < 48; i++) {
        (&seraph_gfx_ofs[0])[i] = seraph_gfx_cells[i] = 0;
    }
    for (i = 0; i < 224; i++) {
        hitmark_gfx_ofs[0][i] = hitmark_gfx_ofs[1][i] = 0;
        hitmark_gfx_cells[i] = 0;
    }

}

/* provisional name */
void setup_kage_cells(void) {
    WORK* ewk;
    WORK* handle_wk;
    s16* handles;
    s16 ix;
    s16 i;
    if (kage_gfx_ofs[0]) {
        return;
    }
    if (!load_char_gfx(0x4020, 1)) {
        return;
    }
    if ((ix = pull_effect_work(7)) == -1) {
        purge_char_gfx(0x4020);
        return;
    }
    ewk = (WORK*)frw[ix];
    ewk->my_col_code = 0x2000;
    if ((ix = pull_effect_work(7)) == -1) {
        purge_char_gfx(0x4020);
        push_effect_work(ewk);
        return;
    }
    handle_wk = (WORK*)&frw[ix];
    handles = &handle_wk->routine_no[0];
    for (i = 0; i < 29; i++) {
        ewk->cg_number = 0x4020 + i;
        if (!trans_char_cells(ewk)) {
            goto fail;
        }
        kage_gfx_ofs[i] = ewk->spr.gfx_ofs;
        kage_gfx_cells[i] = ewk->spr.gfx_cells;
        handles[i] = ewk->spr.gfx_blk40[0];
        ewk->spr.gfx_blk40[0] = 0;
    }
    goto done;
fail:
    if (i) {
        i--;
        for (ix = i; ix >= 0; ix--) {
            simmram_block_free_40(handles[ix]);
        }
    }
    purge_char_gfx(0x4020);
done:
    push_effect_work(ewk);
    push_effect_work(handle_wk);
}


/* provisional name */
void setup_seraph_cells(void) {
    WORK* ewk;
    WORK* handle_wk;
    s16* handles;
    s16 ix;
    s16 i;
    if (seraph_gfx_ofs[0]) {
        return;
    }
    if (!load_char_gfx(0x7718, 1)) {
        return;
    }
    if ((ix = pull_effect_work(7)) == -1) {
        purge_char_gfx(0x7718);
        return;
    }
    ewk = (WORK*)frw[ix];
    ewk->my_col_code = 0x2000;
    if ((ix = pull_effect_work(7)) == -1) {
        purge_char_gfx(0x7718);
        push_effect_work(ewk);
        return;
    }
    handle_wk = (WORK*)&frw[ix];
    handles = &handle_wk->routine_no[0];
    for (i = 0; i < 32; i++) {
        ewk->cg_number = 0x7718 + i;
        if (!trans_char_cells(ewk)) {
            goto fail;
        }
        seraph_gfx_ofs[i] = ewk->spr.gfx_ofs;
        seraph_gfx_cells[i] = ewk->spr.gfx_cells;
        handles[i] = ewk->spr.gfx_blk40[0];
        ewk->spr.gfx_blk40[0] = 0;
    }
    goto done;
fail:
    if (i) {
        i--;
        for (ix = i; ix >= 0; ix--) {
            simmram_block_free_40(handles[ix]);
        }
    }
    purge_char_gfx(0x7718);
done:
    push_effect_work(ewk);
    push_effect_work(handle_wk);
}


void setup_GILL_exsa_obj(void) {
    WORK* ewk;
    WORK* handle_wk;
    s16* handles;
    s16 ix;
    s16 i;
    if (seraph_gfx_ofs[32]) {
        return;
    }
    if (!load_char_gfx(0x7738, 1)) {
        return;
    }
    if ((ix = pull_effect_work(7)) == -1) {
        purge_char_gfx(0x7738);
        return;
    }
    ewk = (WORK*)frw[ix];
    ewk->my_col_code = 0x2000;
    if ((ix = pull_effect_work(7)) == -1) {
        purge_char_gfx(0x7738);
        push_effect_work(ewk);
        return;
    }
    handle_wk = (WORK*)&frw[ix];
    handles = &handle_wk->routine_no[0];
    for (i = 32; i < 46; i++) {
        ewk->cg_number = 0x7718 + i;
        if (!trans_char_cells(ewk)) {
            goto fail;
        }
        seraph_gfx_ofs[i] = ewk->spr.gfx_ofs;
        seraph_gfx_cells[i] = ewk->spr.gfx_cells;
        handles[i] = ewk->spr.gfx_blk40[0];
        ewk->spr.gfx_blk40[0] = 0;
    }
    goto done;
fail:
    if (i) {
        i--;
        for (ix = i; ix >= 0; ix--) {
            simmram_block_free_40(handles[ix]);
        }
    }
    purge_char_gfx(0x7738);
done:
    push_effect_work(ewk);
    push_effect_work(handle_wk);
}


/* provisional name */
void setup_hit_mark_cells(void) {
    WORK* ewk;
    WORK* handle_wk;
    s16* handles;
    s16 ix;
    s16 i;
    if (hitmark_gfx_ofs[0][0]) {
        return;
    }
    if (!load_char_gfx(0x7748, 1)) {
        return;
    }
    if ((ix = pull_effect_work(7)) == -1) {
        purge_char_gfx(0x7748);
        return;
    }
    ewk = (WORK*)frw[ix];
    ewk->my_col_code = 0x2000;
    if ((ix = pull_effect_work(7)) == -1) {
        purge_char_gfx(0x7748);
        push_effect_work(ewk);
        return;
    }
    handle_wk = (WORK*)&frw[ix];
    handles = &handle_wk->routine_no[0];
    ewk->rl_flag = 0;
    for (i = 0; i < 215; i++) {
        ewk->cg_number = 0x7748 + i;
        if (!trans_char_cells(ewk)) {
            goto fail;
        }
        hitmark_gfx_ofs[0][i] = ewk->spr.gfx_ofs;
        hitmark_gfx_cells[i] = ewk->spr.gfx_cells;
        handles[i] = ewk->spr.gfx_blk40[0];
        ewk->spr.gfx_blk40[0] = 0;
    }
    ewk->rl_flag = 1;
    for (i = 0; i < 215; i++) {
        ewk->cg_number = 0x7748 + i;
        if (!trans_char_cells(ewk)) {
            goto fail;
        }
        hitmark_gfx_ofs[1][i] = ewk->spr.gfx_ofs;
        handles[215 + i] = ewk->spr.gfx_blk40[0];
        ewk->spr.gfx_blk40[0] = 0;
    }
    goto done;
fail:
    if (i) {
        i--;
        for (ix = i; ix >= 0; ix--) {
            simmram_block_free_40(handles[ix]);
        }
    }
    purge_char_gfx(0x7748);
done:
    push_effect_work(ewk);
    push_effect_work(handle_wk);
}


/* provisional name */
u32 get_cg_slot_no(id)
u16 id;
{
    return cg_data_list[id].set->slot;
}

/* provisional name */
s32 get_cg_slot_addr(id)
u16 id;
{
    return cg_slot_tbl[id].addr;
}


/* provisional name */
s32 load_char_gfx(id, mode)
u16 id;
s8 mode;
{
    CharGfxSet* set = cg_data_list[id].set;
    s32 handle;
    u32 base;
    s16 i;
    CharGfxChunk* chunk;
    s32 err;
    u32 adr;
    if (!check_cg_data(id)) {
        return 0;
    }
    if (!(set->slot & 0x8000)) {
        if (cg_slot_tbl[set->slot].addr != 0) {
            return 1;
        }
        chr_dma_request(set->prep, 0, 0, 3);
        if ((s16)(handle = simmram_block_alloc_10((set->size >> 5) + 1, 1)) == 0) {
            return 0;
        }
        base = simmram_slot_to_offset(handle);
        cg_slot_tbl[set->slot].addr = simmram_slot_to_cg_no(handle);
        cg_slot_tbl[set->slot].handle = handle;
        chunk = set->chunk;
        for (i = 0; i < set->count; i++) {
            adr = base + chunk[i].dst * 16;
            err = chr_dma_request(chunk[i].src, adr, chunk[i].size, mode);
            if (err != 0) {
                cg_slot_tbl[set->slot].addr = cg_slot_tbl[set->slot].handle = 0;
                simmram_block_free_10(handle);
                return 0;
            }
        }
    }
    return 1;
}


/* provisional name */
s32 purge_char_gfx(id)
u16 id;
{
    CharGfxSet* set = cg_data_list[id].set;
    s16 no = set->slot & 0x7FFF;
    if (cg_slot_tbl[no].addr == 0) {
        return 0;
    }
    simmram_block_free_10(cg_slot_tbl[no].handle);
    cg_slot_tbl[no].addr = cg_slot_tbl[no].handle = 0;
    return 1;
}


/* provisional name */
s32 check_cg_data(id)
u16 id;
{
    s8 flag = 0;
    if ((u32)cg_data_list[id].set > CHAR_GFX_ROM_BEGIN && (u32)cg_data_list[id].set < 0x67FFFFF) {
        flag = 1;
    }
    return flag;
}


/* provisional name */
s32 trans_char_cells(WORK* work) {
    WORK* wk = work;
    CharGfxSet* set;
    CHAR_CELL* cells;
    CHAR_SPRITE* dst;
    u32 base;
    u16 no;
    u16 addr;
    s32 blk10;
    s16 blk40;
    s16 i;
    s32 err;
    u32 adr;
    CharGfxChunk* chunk;
    no = wk->cg_number;
    set = cg_data_list[no].set;
    if (set->slot & 0x8000) {
        goto simm;
    }
    if (wk->old_cgnum == wk->cg_number) {
        goto cached;
    }
    if (cg_slot_tbl[set->slot].addr == 0 && !load_char_gfx(no, wk->cgromtype)) {
        return 0;
    }
    addr = cg_slot_tbl[set->slot].addr;
    wk->spr.slot_addr = addr;
    cells = (CHAR_CELL*)set->chunk;
    cells = (CHAR_CELL*)((u8*)cells + set->count * sizeof(CharGfxChunk));
    wk->spr.cells = cells;
    if ((blk40 = simmram_block_alloc_40((set->cells >> 4) + 1, 1)) == 0) {
        return 0;
    }
    dst = (CHAR_SPRITE*)simmram_slot_addr(blk40);
    goto set_sprite;
    simm:
    if (wk->old_cgnum != wk->cg_number) {
        goto reload;
    }
    cached:
    if (wk->spr.done_flip != wk->cg_flip) {
        if (wk->spr.done_rl != wk->rl_flag) {
            goto both;
        }
    } else {
        if (wk->spr.done_rl == wk->rl_flag) {
            return char_cell_flip_none(wk);
        }
        if (!char_cell_flip_x(wk)) {
            return 0;
        }
        wk->spr.done_rl = wk->rl_flag;
        wk->spr.sprite_flip = wk->cg_flip ^ wk->rl_flag;
        return 1;
    }
    if (!char_cell_flip_tbl[wk->spr.done_flip][wk->cg_flip](wk)) {
        return 0;
    }
    wk->spr.done_flip = wk->cg_flip;
    wk->spr.sprite_flip = wk->cg_flip ^ wk->rl_flag;
    return 1;
    both:
    if (!char_cell_flip_tbl[wk->spr.done_flip ^ wk->spr.done_rl][wk->cg_flip ^ wk->rl_flag](wk)) {
        return 0;
    }
    wk->spr.done_flip = wk->cg_flip;
    wk->spr.done_rl = wk->rl_flag;
    wk->spr.sprite_flip = wk->cg_flip ^ wk->rl_flag;
    return 1;
    reload:
    chr_dma_request(set->prep, 0, 0, 3);
    if ((s16)(blk10 = simmram_block_alloc_10((set->size >> 5) + 1, 1)) == 0) {
        return 0;
    }
    base = simmram_slot_to_offset(blk10);
    wk->spr.slot_addr = addr = simmram_slot_to_cg_no(blk10);
    chunk = set->chunk;
    for (i = 0; i < set->count; i++) {
        adr = base + chunk[i].dst * 16;
        err = chr_dma_request(chunk[i].src, adr, chunk[i].size, wk->cgromtype);
        if (err != 0) {
            simmram_block_free_10(blk10);
            return 0;
        }
    }
    cells = (CHAR_CELL*)&chunk[i];
    wk->spr.cells = cells;
    if ((blk40 = simmram_block_alloc_40((set->cells >> 4) + 1, 1)) == 0) {
        simmram_block_free_10(blk10);
        return 0;
    }
    dst = (CHAR_SPRITE*)simmram_slot_addr(blk40);
    if (wk->spr.gfx_blk10[2]) {
        simmram_block_free_10(wk->spr.gfx_blk10[2]);
    }
    wk->spr.gfx_blk10[2] = wk->spr.gfx_blk10[1];
    wk->spr.gfx_blk10[1] = wk->spr.gfx_blk10[0];
    wk->spr.gfx_blk10[0] = blk10;
    set_sprite:
    if (wk->spr.gfx_blk40[2]) {
        simmram_block_free_40(wk->spr.gfx_blk40[2]);
    }
    wk->spr.gfx_blk40[2] = wk->spr.gfx_blk40[1];
    wk->spr.gfx_blk40[1] = wk->spr.gfx_blk40[0];
    wk->spr.gfx_blk40[0] = blk40;
    wk->spr.gfx_ofs = simmram_slot_to_code(blk40);
    wk->spr.gfx_cells = set->cells;
    wk->spr.spr_free0 = cg_data_list[no].cge_free0;
    wk->spr.cg_ofs_x = cg_data_list[no].x;
    wk->spr.cg_ofs_y = -cg_data_list[no].y;
    wk->spr.sprite_flip = wk->cg_flip ^ wk->rl_flag;
    wk->spr.done_flip = wk->cg_flip;
    wk->spr.done_rl = wk->rl_flag;
    wk->spr.old_mr.x = 63;
    wk->spr.old_mr.y = 63;
    wk->spr.disp_colcd = wk->my_col_code;
    if (wk->my_col_code & 0x2000) {
        wk->spr.disp_colcd += cells->col & 0x1FF;
        wk->current_colcd = wk->spr.disp_colcd;
        make_char_cells_tbl[wk->spr.sprite_flip](wk, cells, dst, set->cells, addr, 0);
    } else {
        wk->spr.disp_colcd &= 0x1FF;
        wk->current_colcd = wk->spr.disp_colcd;
        make_char_cells_tbl[wk->spr.sprite_flip](wk, cells, dst, set->cells, addr, wk->spr.disp_colcd);
    }
    wk->old_cgnum = wk->cg_number;
    (void)&((WORK*)cg_data_list)->id;
    return 1;
}


/* provisional name */
void make_char_cells_n(WORK* wk, CHAR_CELL* cell, CHAR_SPRITE* spr, u16 count, s16 x, s16 y) {
    s16 i;

    for (i = 0; i < count; i++) {
        u16 size;
        spr[i].x = cell[i].code + x;
        spr[i].y = cell[i].col + y;
        spr[i].sx = (cell[i].x + wk->spr.cg_ofs_x) & 0x3FF;
        spr[i].sy = (-cell[i].y + wk->spr.cg_ofs_y) & 0x3FF;
        size = *(u8*)&cell[i].y >> 4;
        spr[i].attr = size | 0x300;
        spr[i].size = cell_size_tbl[size];
    }
}


/* provisional name */
void make_char_cells_x(WORK* wk, CHAR_CELL* cell, CHAR_SPRITE* spr, u16 count, s16 x, s16 y) {
    s16 i;

    for (i = 0; i < count; i++) {
        u16 size;
        spr[i].x = cell[i].code + x;
        spr[i].y = cell[i].col + y;
        spr[i].sx = (-cell[i].x - wk->spr.cg_ofs_x) & 0x3FF;
        spr[i].sy = (-cell[i].y + wk->spr.cg_ofs_y) & 0x3FF;
        size = *(u8*)&cell[i].y >> 4;
        spr[i].attr = size | 0x300;
        spr[i].size = cell_size_tbl[size];
    }
}


/* provisional name */
void make_char_cells_y(WORK* wk, CHAR_CELL* cell, CHAR_SPRITE* spr, u16 count, s16 x, s16 y) {
    s16 i;

    for (i = 0; i < count; i++) {
        u16 size;
        spr[i].x = cell[i].code + x;
        spr[i].y = cell[i].col + y;
        spr[i].sx = (cell[i].x + wk->spr.cg_ofs_x) & 0x3FF;
        spr[i].sy = (cell[i].y - wk->spr.cg_ofs_y + wk->spr.spr_free0) & 0x3FF;
        size = *(u8*)&cell[i].y >> 4;
        spr[i].attr = size | 0x300;
        spr[i].size = cell_size_tbl[size];
    }
}


/* provisional name */
void make_char_cells_xy(WORK* wk, CHAR_CELL* cell, CHAR_SPRITE* spr, u16 count, s16 x, s16 y) {
    s16 i;

    for (i = 0; i < count; i++) {
        u16 size;
        spr[i].x = cell[i].code + x;
        spr[i].y = cell[i].col + y;
        spr[i].sx = (-cell[i].x - wk->spr.cg_ofs_x) & 0x3FF;
        spr[i].sy = (cell[i].y - wk->spr.cg_ofs_y + wk->spr.spr_free0) & 0x3FF;
        size = *(u8*)&cell[i].y >> 4;
        spr[i].attr = size | 0x300;
        spr[i].size = cell_size_tbl[size];
    }
}


/* provisional name */
s32 char_cell_flip_none(WORK* wk) {
    if (wk->spr.gfx_blk10[2]) {
        simmram_block_free_10(wk->spr.gfx_blk10[2]);
    }
    wk->spr.gfx_blk10[2] = wk->spr.gfx_blk10[1];
    wk->spr.gfx_blk10[1] = 0;
    if (wk->spr.gfx_blk40[2]) {
        simmram_block_free_40(wk->spr.gfx_blk40[2]);
    }
    wk->spr.gfx_blk40[2] = wk->spr.gfx_blk40[1];
    wk->spr.gfx_blk40[1] = 0;
    return 1;
}


/* provisional name */
s32 char_cell_push_block(wk, handle)
WORK* wk;
s16 handle;
{
    if (wk->spr.gfx_blk10[2]) {
        simmram_block_free_10(wk->spr.gfx_blk10[2]);
    }
    wk->spr.gfx_blk10[2] = wk->spr.gfx_blk10[1];
    wk->spr.gfx_blk10[1] = 0;
    if (wk->spr.gfx_blk40[2]) {
        simmram_block_free_40(wk->spr.gfx_blk40[2]);
    }
    wk->spr.gfx_blk40[2] = wk->spr.gfx_blk40[1];
    wk->spr.gfx_blk40[1] = wk->spr.gfx_blk40[0];
    wk->spr.gfx_blk40[0] = handle;
    wk->spr.gfx_ofs = simmram_slot_to_code(handle);
    return 1;
}


/* provisional name */
s32 char_cell_flip_x(WORK* wk) {
    CharSpriteK* dst;
    s16 handle;
    CharSpriteK* src;
    s16 i;
    if ((handle = simmram_block_alloc_40((wk->spr.gfx_cells >> 4) + 1, 1)) == 0) {
        return 0;
    }
    dst = (CharSpriteK*)simmram_slot_addr(handle);
    src = (CharSpriteK*)(SPRITE_RAM + wk->spr.gfx_ofs * 16);
    for (i = 0; i < wk->spr.gfx_cells; i++) {
        dst[i] = src[i];
        dst[i].x = -dst[i].x & 0x3FF;
    }
    return char_cell_push_block(wk, handle);
}


/* provisional name */
s32 char_cell_flip_y(WORK* wk) {
    CharSpriteK* dst;
    s16 handle;
    CharSpriteK* src;
    s16 i;
    if ((handle = simmram_block_alloc_40((wk->spr.gfx_cells >> 4) + 1, 1)) == 0) {
        return 0;
    }
    dst = (CharSpriteK*)simmram_slot_addr(handle);
    src = (CharSpriteK*)(SPRITE_RAM + wk->spr.gfx_ofs * 16);
    for (i = 0; i < wk->spr.gfx_cells; i++) {
        dst[i] = src[i];
        dst[i].y = (-dst[i].y + wk->spr.spr_free0) & 0x3FF;
    }
    return char_cell_push_block(wk, handle);
}


/* provisional name */
s32 char_cell_unflip_y(WORK* wk) {
    CharSpriteK* dst;
    s16 handle;
    CharSpriteK* src;
    s16 i;
    if ((handle = simmram_block_alloc_40((wk->spr.gfx_cells >> 4) + 1, 1)) == 0) {
        return 0;
    }
    dst = (CharSpriteK*)simmram_slot_addr(handle);
    src = (CharSpriteK*)(SPRITE_RAM + wk->spr.gfx_ofs * 16);
    for (i = 0; i < wk->spr.gfx_cells; i++) {
        dst[i] = src[i];
        dst[i].y = (-dst[i].y + wk->spr.spr_free0) & 0x3FF;
    }
    return char_cell_push_block(wk, handle);
}


/* provisional name */
s32 char_cell_flip_xy(WORK* wk) {
    CHAR_SPRITE* dst;
    s16 handle;
    CHAR_SPRITE* src;
    s16 i;
    if ((handle = simmram_block_alloc_40((wk->spr.gfx_cells >> 4) + 1, 1)) == 0) {
        return 0;
    }
    dst = (CHAR_SPRITE*)simmram_slot_addr(handle);
    src = (CHAR_SPRITE*)(SPRITE_RAM + wk->spr.gfx_ofs * 16);
    for (i = 0; i < wk->spr.gfx_cells; i++) {
        dst[i] = src[i];
        dst[i].sx = -dst[i].sx & 0x3FF;
        dst[i].sy = (-dst[i].sy + wk->spr.spr_free0) & 0x3FF;
    }
    return char_cell_push_block(wk, handle);
}


/* provisional name */
s32 char_cell_unflip_xy(WORK* wk) {
    CHAR_SPRITE* dst;
    s16 handle;
    CHAR_SPRITE* src;
    s16 i;
    if ((handle = simmram_block_alloc_40((wk->spr.gfx_cells >> 4) + 1, 1)) == 0) {
        return 0;
    }
    dst = (CHAR_SPRITE*)simmram_slot_addr(handle);
    src = (CHAR_SPRITE*)(SPRITE_RAM + wk->spr.gfx_ofs * 16);
    for (i = 0; i < wk->spr.gfx_cells; i++) {
        dst[i] = src[i];
        dst[i].sx = -dst[i].sx & 0x3FF;
        dst[i].sy = (-dst[i].sy + wk->spr.spr_free0) & 0x3FF;
    }
    return char_cell_push_block(wk, handle);
}


s32 set_judge_area_sprite(WORK_Other_JUDGE* wk) {
    GFX_CELL* base;
    const u16* flip;
    s16 blk;
    s16 base_code;
    CharGfxSet* set;
    s16 cell;
    s16 y_ofs;
    s16 i;
    s16 j;
    s16 k;
    s32 n;
    s32 t;
    if (wk->wu.spr.gfx_cells == 0) {
        return 0;
    }
    set = cg_data_list[wk->wu.cg_number].set;
    base_code = cg_slot_tbl[set->slot].addr;
    if ((blk = simmram_block_alloc_40(wk->wu.spr.gfx_cells / 16 + 1, 1)) == 0) {
        return 0;
    }
    base = (GFX_CELL *)simmram_slot_addr(blk);
    if (wk->wu.spr.gfx_blk40[2]) {
        simmram_block_free_40(wk->wu.spr.gfx_blk40[2]);
    }
    wk->wu.spr.gfx_blk40[2] = wk->wu.spr.gfx_blk40[1];
    wk->wu.spr.gfx_blk40[1] = wk->wu.spr.gfx_blk40[0];
    wk->wu.spr.gfx_blk40[0] = blk;
    wk->wu.spr.gfx_ofs = simmram_slot_to_code(blk);
    wk->wu.spr.done_rl = 0;
    cell = 0;
    for (i = 0; i < 10; i++) {
        if (!(wk->ja_disp_bit & (1 << i))) {
            continue;
        }
        y_ofs = 0;
        if (wk->curr_ja == i) {
            y_ofs = wk->fade_cja.w * 2;
        }
        for (k = 0, n = i * 16, flip = flip_attr_tbl; k < 4; n = n + 4, flip = flip + 1) {
            base[cell].w[0] = judge_area_code_tbl[i] + base_code + y_ofs;
            base[cell].w[1] = *flip;
            base[cell].w[2] = *(s16*)((u32)wk->ja + (t = n)) & 0x3FF;
            base[cell].w[3] = *(s16*)((u32)wk->ja + t + 2) & 0x3FF;
            base[cell].w[5] = 0x305;
            base[cell].w[4] = cell_size_tbl[5];
            cell++;
            k++;
        }
    }
    if (wk->ja_disp_bit & 0x400) {
        for (j = 0; j < 2; j++) {
            base[cell].w[0] = (&judge_area_code_tbl[10])[j] + base_code;
            base[cell].w[1] = flip_attr_tbl[0];
            base[cell].w[2] = wk->ja[40 + j][0] & 0x3FF;
            base[cell].w[3] = wk->ja[40 + j][1] & 0x3FF;
            base[cell].w[5] = 0x305;
            base[cell].w[4] = cell_size_tbl[5];
            cell++;
        }
    }
    if (wk->wu.spr.gfx_cells != cell) {
        return 2;
    }
    return 1;
}


s32 set_conn_sprite(WORK_Other_CONN* wk) {
    s16 handle;
    CharSpriteK* dst;
    CharSpriteK* s;
    CHAR_CELL* cells;
    CharGfxSet* set;
    s16 base;
    s16 chr;
    u16 cg_index;
    s16 i;
    s16 j;
    s16 n;
    u16 size;
    if (wk->wu.old_cgnum == wk->wu.cg_number) {
        return 1;
    }
    count_conn_cells(wk);
    if (wk->wu.spr.gfx_cells == 0) {
        return 0;
    }
    if ((handle = simmram_block_alloc_40(wk->wu.spr.gfx_cells / 16 + 1, 1)) == 0) {
        return 0;
    }
    dst = (CharSpriteK*)simmram_slot_addr(handle);
    if (wk->wu.spr.gfx_blk40[2]) {
        simmram_block_free_40(wk->wu.spr.gfx_blk40[2]);
    }
    wk->wu.spr.gfx_blk40[2] = wk->wu.spr.gfx_blk40[1];
    wk->wu.spr.gfx_blk40[1] = wk->wu.spr.gfx_blk40[0];
    wk->wu.spr.gfx_blk40[0] = handle;
    wk->wu.spr.gfx_ofs = simmram_slot_to_code(handle);
    wk->wu.spr.done_rl = 0;
    if (wk->wu.my_col_code & 0x2000) {
        wk->wu.spr.disp_colcd = 0;
        n = 0;
    } else {
        wk->wu.spr.disp_colcd = wk->wu.my_col_code & 0x1FF;
        n = 0;
    }
    for (i = 0; i < wk->num_of_conn; i++) {
        chr = wk->conn[i].chr;
        cg_index = chr;
        set = cg_data_list[cg_index].set;
        base = cg_slot_tbl[set->slot].addr;
        cells = (CHAR_CELL*)set->chunk;
        cells += set->count;
        for (j = 0; j < set->cells; j++) {
            s = &dst[n];
            s->code = base + cells[j].code;
            s->pal = cells[j].col + wk->wu.spr.disp_colcd + wk->conn[i].col;
            s->x = (cells[j].x + wk->conn[i].nx + cg_data_list[cg_index].x) & 0x3FF;
            s->y = (wk->conn[i].ny - cells[j].y - cg_data_list[cg_index].y) & 0x3FF;
            size = *(u8*)&cells[j].y >> 4;
            s->attr = size | 0x300;
            s->zoom = cell_size_tbl[size];
            n++;
        }
    }
    return 1;
}


/* provisional name */
void count_conn_cells(WORK_Other_CONN* ewk) {
    s16 i;
    ewk->wu.spr.gfx_cells = 0;
    for (i = 0; i < ewk->num_of_conn; i++) {
        if (ewk->conn[i].chr == 0) {
            continue;
        }
        ewk->wu.spr.gfx_cells += cg_data_list[ewk->conn[i].chr].set->cells;
    }
}


/* provisional name */
s32 make_conn_cells(WORK_Other_CONN* ewk) {
    s16 handle;
    CharSpriteK* dst;
    CharSpriteK* s;
    CHAR_CELL* cells;
    CharGfxSet* set;
    s16 base;
    u16 chr;
    s16 i;
    s16 j;
    s16 n;
    u16 size;
    if (ewk->wu.old_cgnum == ewk->wu.cg_number) {
        return 1;
    }
    count_conn_cells(ewk);
    if (ewk->wu.spr.gfx_cells == 0) {
        return 0;
    }
    if ((handle = simmram_block_alloc_40(ewk->wu.spr.gfx_cells / 16 + 1, 1)) == 0) {
        return 0;
    }
    dst = (CharSpriteK*)simmram_slot_addr(handle);
    if (ewk->wu.spr.gfx_blk40[2]) {
        simmram_block_free_40(ewk->wu.spr.gfx_blk40[2]);
    }
    ewk->wu.spr.gfx_blk40[2] = ewk->wu.spr.gfx_blk40[1];
    ewk->wu.spr.gfx_blk40[1] = ewk->wu.spr.gfx_blk40[0];
    ewk->wu.spr.gfx_blk40[0] = handle;
    ewk->wu.spr.gfx_ofs = simmram_slot_to_code(handle);
    ewk->wu.spr.done_rl = 0;
    if (ewk->wu.my_col_code & 0x2000) {
        ewk->wu.spr.disp_colcd = 0;
    } else {
        ewk->wu.spr.disp_colcd = ewk->wu.my_col_code & 0x1FF;
    }
    n = 0;
    for (i = 0; i < ewk->num_of_conn; i++) {
        chr = ewk->conn[i].chr;
        set = cg_data_list[chr].set;
        base = cg_slot_tbl[set->slot].addr;
        cells = (CHAR_CELL*)set->chunk;
        cells += set->count;
        for (j = 0; j < set->cells; j++) {
            (s = &dst[n])->code = base + cells[j].code;
            s->pal = cells[j].col + ewk->wu.spr.disp_colcd + ewk->conn[i].col;
            s->x = (cells[j].x + ewk->conn[i].nx + cg_data_list[chr].x) & 0x3FF;
            n++;
            s->y = (ewk->conn[i].ny - cells[j].y - cg_data_list[chr].y) & 0x3FF;
            size = *(u8*)&cells[j].y >> 4;
            s->attr = size | 0x300;
            s->zoom = 0x3F3F;
        }
    }
    return 1;
}


void all_cgps_put_back(WORK* wk) {
    s16 i;
    for (i = 0; i < 3; i++) {
        if (wk->spr.gfx_blk10[i]) {
            simmram_block_free_10(wk->spr.gfx_blk10[i]);
        }
        wk->spr.gfx_blk10[i] = 0;
        if (wk->spr.gfx_blk40[i]) {
            simmram_block_free_40(wk->spr.gfx_blk40[i]);
        }
        wk->spr.gfx_blk40[i] = 0;
    }
    wk->old_cgnum = wk->cg_number = 0;
}


/* provisional name */
void release_char_cell_blocks(WORK* wk) {
    s16 i;
    for (i = 0; i < 3; i++) {
        if (wk->spr.gfx_blk40[i]) {
            simmram_block_free_40(wk->spr.gfx_blk40[i]);
        }
        wk->spr.gfx_blk40[i] = 0;
    }
    wk->cg_number = 0;
    wk->old_cgnum = 0;
}

s32 sort_push_request(WORK* wk) {
    SPRITE_ENTRY* spr;
    u32 flip_mask;
    if (wk->disp_flag == 0 || wk->cg_number == 0) {
        return 1;
    }
    if (wk->disp_flag == 2 && ((wk->blink_timing + Game_timer) & 1)) {
        return 1;
    }
    if (!trans_char_cells(wk)) {
        return 0;
    }
    if ((spr = sprite_entry_alloc(0)) == 0) {
        return 0;
    }
    wk->spr.disp_colcd = wk->current_colcd;
    if (wk->extra_col_2) {
        wk->spr.disp_colcd = wk->extra_col_2;
    }
    if (wk->extra_col) {
        wk->spr.disp_colcd = wk->extra_col;
    }
    push_char_sprite(wk, spr, base_y_pos);
    if (wk->my_mr_flag && *(u32*)&wk->spr.old_mr != *(u32*)&wk->my_mr) {
        char_sprite_zoom_cells(wk);
    }
    flip_mask = 1;
    if (wk->work_id == 1 && (wk->spr.sprite_flip & flip_mask)) {
        spr->w8 |= 8;
    }
    if (wk->work_id == 0x20 && wk->my_col_code == ((WORK*)((WORK_Other*)wk)->my_master)->my_col_code &&
        (wk->spr.sprite_flip & flip_mask)) {
        spr->w8 |= 8;
    }
    if (wk->kage_flag) {
        shadow_drawing(wk, base_y_pos);
    }
    return 2;
}


s32 sort_push_request2(WORK_Other* wk) {
    SPRITE_ENTRY* spr;
    s16 i;
    CHAR_SPRITE* cell;

    if (wk->wu.disp_flag == 0) {
        return 1;
    }
    if (!set_judge_area_sprite((WORK_Other_JUDGE*)wk)) {
        return 0;
    }
    if ((spr = sprite_entry_alloc(0)) == 0) {
        return 0;
    }
    push_char_sprite(&wk->wu, spr, base_y_pos);
    if (wk->wu.spr.done_rl != wk->wu.rl_flag) {
        wk->wu.spr.done_rl = wk->wu.rl_flag;
        spr->w8 ^= 0x1000;
        cell = (CHAR_SPRITE*)SPRITE_RAM + wk->wu.spr.gfx_ofs;
        for (i = 0; i < wk->wu.spr.gfx_cells; i++) {
            cell[i].sx = -cell[i].sx & 0x3FF;
        }
    } else if (wk->wu.spr.done_rl) {
        spr->w8 ^= 0x1000;
    }
    if (wk->wu.kage_flag) {
        shadow_drawing(&wk->wu, base_y_pos);
    }
    return 2;
}


s32 sort_push_request3(WORK* wk) {
    SPRITE_ENTRY* spr;
    s16 i;
    CHAR_SPRITE* cell;

    if (wk->disp_flag == 0) {
        return 1;
    }
    if (wk->disp_flag == 2 && ((wk->blink_timing + Game_timer) & 1)) {
        return 1;
    }
    if (!set_conn_sprite((WORK_Other_CONN*)wk)) {
        return 0;
    }
    wk->old_cgnum = wk->cg_number;
    if ((spr = sprite_entry_alloc(0)) == 0) {
        return 0;
    }
    push_char_sprite(wk, spr, base_y_pos);
    if (wk->spr.done_rl != wk->rl_flag) {
        wk->spr.done_rl = wk->rl_flag;
        spr->w8 ^= 0x1000;
        cell = (CHAR_SPRITE*)SPRITE_RAM + wk->spr.gfx_ofs;
        for (i = 0; i < wk->spr.gfx_cells; i++) {
            cell[i].sx = -cell[i].sx & 0x3FF;
        }
    } else if (wk->spr.done_rl) {
        spr->w8 |= 0x1000;
    }
    if (wk->kage_flag) {
        shadow_drawing(wk, base_y_pos);
    }
    return 2;
}

s32 sort_push_request4(WORK* wk) {
    SPRITE_ENTRY* spr;
    if (wk->disp_flag == 0 || wk->cg_number == 0) {
        return 1;
    }
    if (wk->disp_flag == 2 && ((wk->blink_timing + Game_timer) & 1)) {
        return 1;
    }
    if (trans_char_cells(wk) == 0) {
        return 0;
    }
    if ((spr = sprite_entry_alloc(0)) == 0) {
        return 0;
    }
    wk->spr.disp_colcd = wk->current_colcd;
    if (wk->extra_col_2) {
        wk->spr.disp_colcd = wk->extra_col_2;
    }
    if (wk->extra_col) {
        wk->spr.disp_colcd = wk->extra_col;
    }
    push_char_sprite(wk, spr, 0);
    if (wk->my_mr_flag && *(u32*)&wk->spr.old_mr != *(u32*)&wk->my_mr) {
        char_sprite_zoom_cells(wk);
    }
    if (wk->kage_flag) {
        shadow_drawing(wk, 0);
    }
    return 2;
}


/* provisional name */
void push_char_sprite(WORK* wk, SPRITE_ENTRY* spr, s16 y_ofs) {
    spr->w0 = wk->spr.gfx_cells;
    spr->w0 |= wk->my_family << 12;
    spr->w2 = wk->spr.gfx_ofs;
    spr->w4 = wk->position_x;
    spr->w6 = wk->position_y + y_ofs;
    spr->prio = wk->position_z;
    spr->w8 = wk->spr.disp_colcd | wk->my_col_mode | flip_attr_tbl[wk->spr.sprite_flip];
    spr->w10 = wk->my_ext_pri;
    sprite_entry_push_prio(spr, wk->position_z);
}


/* provisional name */
s32 disp_seraph_cells(WORK* wk) {
    SPRITE_ENTRY* spr;
    u16 ix;
    if (wk->disp_flag == 0 || wk->cg_number == 0) {
        return 1;
    }
    if (cg_slot_tbl[cg_data_list[wk->cg_number].set->slot].addr == 0) {
        return;
    }
    if ((spr = sprite_entry_alloc(0)) == 0) {
        return 0;
    }
    ix = wk->cg_number - 0x7718;
    spr->w0 = seraph_gfx_cells[ix];
    spr->w0 |= wk->my_family << 12;
    spr->w2 = seraph_gfx_ofs[ix];
    spr->w4 = wk->position_x;
    spr->w6 = wk->position_y;
    spr->prio = wk->position_z;
    spr->w8 = wk->my_col_code | wk->my_col_mode;
    spr->w10 = 0;
    sprite_entry_push_prio(spr, wk->position_z);
    return 2;
}


s32 sort_push_request8(WORK* wk) {
    u16 no;
    SPRITE_ENTRY* spr;
    u16 ix;
    if (wk->disp_flag == 0 || wk->cg_number == 0) {
        return 1;
    }
    if (wk->disp_flag == 2 && ((wk->blink_timing + Game_timer) & 1)) {
        return 1;
    }
    no = cg_data_list[wk->cg_number].set->slot & 0x7FFF;
    if (no != 0x130) {
        return sort_push_request(wk);
    }
    if (cg_slot_tbl[no].addr == 0) {
        return;
    }
    if ((spr = sprite_entry_alloc(0)) == 0) {
        return 0;
    }
    ix = wk->cg_number - 0x7748;
    spr->w0 = (u16)hitmark_gfx_cells[ix];
    spr->w0 |= wk->my_family << 12;
    spr->w2 = (u16)hitmark_gfx_ofs[wk->rl_flag][ix];
    spr->w4 = wk->position_x;
    spr->w6 = wk->position_y + base_y_pos;
    spr->prio = wk->position_z;
    spr->w8 = wk->my_col_code | wk->my_col_mode | flip_attr_tbl[wk->rl_flag];
    spr->w10 = 0;
    sprite_entry_push_prio(spr, wk->position_z);
    return 2;
}


void shadow_drawing(WORK* wk, s16 y_ofs) {
    SPRITE_ENTRY* spr;
    s16 size;
    if (cg_slot_tbl[cg_data_list[0x4020].set->slot].addr == 0) {
        return;
    }
    if ((spr = sprite_entry_alloc(0)) == 0) {
        return;
    }
    size = wk->kage_char - get_kage_width(wk->xyz[1].disp.pos - wk->kage_hy);
    if (size >= 29) {
        size = 28;
    } else if (size < 0) {
        size = 0;
    }
    spr->w0 = kage_gfx_cells[size];
    spr->w0 |= wk->my_family << 12;
    spr->w2 = kage_gfx_ofs[size];
    spr->w4 = wk->position_x + (s16)(wk->kage_hx * (1 - (wk->rl_flag != 0) * 2));
    spr->w6 = wk->kage_hy + y_ofs;
    spr->prio = wk->kage_prio;
    spr->w8 = 0x6400;
    spr->w10 = 0;
    sprite_entry_push_prio(spr, wk->kage_prio);
}


s16 get_kage_width(v)
s16 v;
{
    if (v <= 0) {
        return 0;
    }
    v /= 4;
    if (v >= 64) {
        return 16;
    }
    return gkw_table[v];
}


/* provisional name: 45 cg 0x6390 patterns made once into sprite lists */
void setup_mark_cells(void) {
    WORK* ewk;
    s16* handles;
    s16 ix;
    s16 i;
    if ((ix = pull_effect_work(7)) == -1) {
        return;
    }
    ewk = (WORK*)frw[ix];
    handles = &ewk->waku_work_index;
    ewk->my_col_code = 64;
    ewk->my_col_mode = 0x4200;
    for (i = 0; i < 45; i++) {
        ewk->cg_number = mark_cg_tbl[i] + 0x6390;
        if (!trans_char_cells(ewk)) {
            goto fail;
        }
        mark_gfx_ofs[i] = ewk->spr.gfx_ofs;
        mark_gfx_cells[i] = ewk->spr.gfx_cells;
        mark_gfx_colcd[i] = ewk->spr.disp_colcd;
        handles[i] = ewk->spr.gfx_blk40[0];
        ewk->spr.gfx_blk40[0] = 0;
    }
    goto done;
fail:
    if (i) {
        i--;
        for (ix = i; ix >= 0; ix--) {
            simmram_block_free_40(handles[ix]);
        }
    }
done:
    push_effect_work(ewk);
}


/* provisional name */
void disp_mark_cells(WORK* wk, s16 no) {
    SPRITE_ENTRY* spr;
    s16 ix;
    if (wk->disp_flag == 0) {
        return;
    }
    if (cg_slot_tbl[cg_data_list[0x6390].set->slot].addr == 0) {
        return;
    }
    if ((spr = sprite_entry_alloc(0)) == 0) {
        return;
    }
    ix = mark_index_tbl[wk->type][no];
    spr->w0 = mark_gfx_cells[ix];
    spr->w0 |= wk->my_family << 12;
    spr->w2 = mark_gfx_ofs[ix];
    spr->w4 = wk->position_x;
    spr->w6 = wk->position_y;
    spr->prio = wk->my_priority;
    spr->w8 = mark_gfx_colcd[ix] | 0x4200;
    spr->w10 = 0;
    sprite_entry_push_prio(spr, wk->my_priority);
}


/* provisional name */
void char_sprite_zoom_cells(WORK* wk) {
    CharSpriteK* spr;
    XY16K pos;
    struct {
        s16 mul_x;
        s16 div_x;
        s16 mul_y;
        s16 div_y;
    } m;
    s32 base_x;
    s32 base_y;
    s16 i;
    s16* p;
    s16* q;
    s16* r;
    spr = (CharSpriteK*)(SPRITE_RAM + wk->spr.gfx_ofs * 16);
    *(u32*)&wk->spr.old_mr = *(u32*)&wk->my_mr;
    p = &m.div_x;
    m.mul_x = wk->my_mr.size.x;
    *p = wk->my_mr.size.x - 63;
    if (*p > 0) {
        p = &m.div_x;
        (*p)--;
        *p = zoom_up_tbl[*p] + 63;
    } else {
        m.mul_x = wk->my_mr.size.x;
        p = &m.div_x;
        *p = -*p;
        *p = zoom_down_tbl[*p] + 63;
    }
    m.mul_y = wk->my_mr.size.y;
    p = &m.div_y;
    *p = wk->my_mr.size.y - 63;
    r = &m.div_y;
    q = r;
    if (*p > 0) {
        (*q)--;
        *q = zoom_up_tbl[*q] + 63;
    } else {
        *q = -*q;
        *q = zoom_down_tbl[*q] + 63;
    }
    pos.l = zoom_cell_position((s16*)&m, (u16)wk->spr.cg_ofs_x, wk->spr.cg_ofs_y);
    p = &pos.s.x;
    base_x = p[0];
    base_y = p[1];
    switch (wk->spr.sprite_flip) {
    case 0:
        i = 0;
        p = (s16*)&m;
        for (; i < wk->spr.gfx_cells; i = i + 1) {
            pos.l = zoom_cell_position(p, (u16)wk->spr.cells[i].x, (u16)wk->spr.cells[i].y);
            spr[i].x = (pos.s.x + base_x) & 0x3FF;
            spr[i].y = (-pos.s.y + base_y) & 0x3FF;
            spr[i].zoom = get_cell_zoom(wk->my_mr.size.x, wk->my_mr.size.y, (u16)spr[i].attr);
        }
        break;
    case 1:
        i = 0;
        p = (s16*)&m;
        for (; i < wk->spr.gfx_cells; i++) {
            pos.l = zoom_cell_position(p, (u16)wk->spr.cells[i].x, (u16)wk->spr.cells[i].y);
            spr[i].x = (-pos.s.x - base_x) & 0x3FF;
            spr[i].y = (-pos.s.y + base_y) & 0x3FF;
            spr[i].zoom = get_cell_zoom(wk->my_mr.size.x, wk->my_mr.size.y, (u16)spr[i].attr);
        }
        break;
    case 2:
        i = 0;
        p = (s16*)&m;
        for (; i < wk->spr.gfx_cells; i++) {
            pos.l = zoom_cell_position(p, (u16)wk->spr.cells[i].x, (u16)wk->spr.cells[i].y);
            spr[i].x = (pos.s.x + base_x) & 0x3FF;
            spr[i].y = (pos.s.y - base_y) & 0x3FF;
            spr[i].zoom = get_cell_zoom(wk->my_mr.size.x, wk->my_mr.size.y, (u16)spr[i].attr);
        }
        break;
    default:
        i = 0;
        p = (s16*)&m;
        for (; i < wk->spr.gfx_cells; i++) {
            pos.l = zoom_cell_position(p, (u16)wk->spr.cells[i].x, (u16)wk->spr.cells[i].y);
            spr[i].x = (-pos.s.x - base_x) & 0x3FF;
            spr[i].y = (pos.s.y - base_y) & 0x3FF;
            spr[i].zoom = get_cell_zoom(wk->my_mr.size.x, wk->my_mr.size.y, (u16)spr[i].attr);
        }
        break;
    }
}


/* provisional name */
s32 zoom_cell_position(m, x, y)
s16 *m;
u16 x;
u16 y;
{
    XY16 pos;

    if ((s16)x & 0x200) {
        x |= 0xFC00;
    } else {
        x &= 0x3FF;
    }
    if ((s16)y & 0x200) {
        y |= 0xFC00;
    } else {
        y &= 0x3FF;
    }
    pos.s.x = m[0] * (s16)x / m[1];
    pos.s.y = m[2] * (s16)y / m[3];
    return pos.l;
}


/* provisional name */
s32 get_cell_zoom(lo, hi, rows)
register u16 lo;
u16 hi;
register u16 rows;
{
    s16 lo_row;
    s16 hi_row;
    s32 value;

    lo_row = rows & 3;
    hi_row = (s32)(rows & 12) >> 2;
    value = cell_zoom_tbl[hi_row][hi] << 8;
    if (lo < 4) {
        lo = 4;
    }
    value |= cell_zoom_tbl[lo_row][lo];
    return (s16)value;
}
