/*
 * EFF12.C  Effect 12: animated BG 0 map
 *
 * effect_12_init (from the bgst000, bgst030, bgst090 and bgst160 stages) records BG 0's page in
 * eff_bg_adrs and allocates a second one. On its first frame effect_12_move writes the animation's
 * tiles into the two pages (eff12_tile_put, from bg050_cell_data) and then cycles through the four
 * frames of eff12_frame_tbl, each showing one page at its own Y offset for its time.
 * debug_bg_tile_put, which copies one 16 x 16 tile into a page, is shared with effect 48. The
 * allocated page is freed when the effect ends.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "end_main.h"
#include "sys_config.h"
#include "sys_test.h"

/* routine_no[0] */
#define R0_INIT         0       /* write the tiles into both pages */
#define R0_MOVE         1       /* cycle the four frames */

extern const EFF12_FRAME eff12_frame_tbl[4];
extern const EFF12_ROW eff12_tile_tbl[2];
extern const u16 bg050_cell_data[66][16][32];
void eff12_tile_put(void);
void debug_bg_tile_put(s16 bg, s32 ofs, s32 page, s32 src);

void effect_12_move(WORK_Other* ewk) {
    s16 y;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.cg_ix = 0;
        ewk->wu.cg_ctr = eff12_frame_tbl[0].timer;
        eff12_tile_put();
        scrn_map_set_now(0, eff_bg_adrs[0].adrs);
        y = eff12_frame_tbl[(s8)ewk->wu.cg_ix].y + bg_w.bgw[0].position_y;
        Scrn_Y_Set_R(0, y);
        break;
    case R0_MOVE:
        if (!EXE_flag && !Game_pause) {
            ewk->wu.cg_ctr--;
            if (!ewk->wu.cg_ctr) {
                ewk->wu.cg_ix++;
                ewk->wu.cg_ix &= 3;
                ewk->wu.cg_ctr = eff12_frame_tbl[(s8)ewk->wu.cg_ix].timer;
                scrn_map_set(0, eff_bg_adrs[eff12_frame_tbl[(s8)ewk->wu.cg_ix].page].adrs);
            }
        }
        y = eff12_frame_tbl[(s8)ewk->wu.cg_ix].y;
        y += bg_w.bgw[0].abs_y & 0x3FF;
        Scrn_Y_Set_W(0, y);
        break;
    default:
        simmram_block_free_40(eff_bg_adrs[1].no);
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

s32 effect_12_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 12;
    ewk->wu.work_id = 16;
    ewk->wu.type = 0;
    eff_bg_adrs[0].no = bg_w.bgw[0].bg_adrs_c_no;
    eff_bg_adrs[0].adrs = (u32)bg_w.bgw[0].bg_address;
    eff_bg_adrs[1].no = simmram_big_page_alloc_40(1);
    eff_bg_adrs[1].adrs = simmram_slot_addr(eff_bg_adrs[1].no);
    return 0;
}

void debug_bg_tile_put(s16 bg, s32 ofs, s32 page, s32 src) {
    u16* dst;
    u16* sp;
    s32 x;
    s32 adr;
    adr = eff_bg_adrs[bg].adrs;
    ofs += adr;
    dst = (u16*)ofs;
    x = 0;
    x += bg_w.scroll_cg_adr >> 7;
    page = (page << 10) + src;
    sp = (u16*)page;
    blit_16x16_tile(sp, (u16)x, dst, 0x240);
}

static void eff12_tile_disp(s32 ofs) {}

void eff12_tile_put(void) {
    s16 i;
    s16 j;
    const EFF12_ROW* row;
    const EFF12_TILE* tile;

    for (i = 0; i < 2; i++) {
        row = &eff12_tile_tbl[i] + 0;
        for (j = 0; j < 16; j++) {
            tile = &row->t[j];
            debug_bg_tile_put(i, tile->ofs, tile->page, (s32)bg050_cell_data);
            eff12_tile_disp(tile->ofs);
        }
    }
}
