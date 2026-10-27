/*
 * EFF11.C  Effect 11: animated background map of stage 07 (bg070)
 *
 * effect_11_init (from bg070) takes BG 0's map as page 0 of eff_bg_adrs and allocates three more
 * map pages. effect_11_move fills the four pages from bg070_cell_data once, then flips BG 0
 * between them: eff11_anime_tbl gives each animation its repeat count and frame set, and
 * eff11_frame_tbl each frame's page, Y offset and duration. The object's last state releases the
 * extra pages.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "end_main.h"
#include "sys_config.h"
#include "sys_test.h"
#include "EFF11.h"

/* routine_no[0] */
#define R0_INIT         0       /* fill the map pages, show the first */
#define R0_MOVE         1       /* flip BG 0 between the pages */




extern const EFF11_ROW eff11_tile_tbl[4];
extern const EFF11_FRAME eff11_frame_tbl[8][4];
extern const EFF11_ANIME eff11_anime_tbl[14];
extern const u16 bg070_cell_data[155][16][32];

void debug_bg_tile_put(s16 bg, s32 ofs, s32 page, s32 src);



static void eff11_tile_disp(s32 ofs) {}

void effect_11_move(WORK_Other* ewk) {
    s16 i;
    s16 j;
    void (*put)(s16, s32, s32, s32);
    s16 y;
    s16 page;
    const EFF11_ROW* row;
    const EFF11_TILE* tile;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0] += 1;
        ewk->wu.cg_ix = 0;
        ewk->wu.char_index = 0;
        ewk->wu.now_koc = eff11_anime_tbl[ewk->wu.char_index].count;
        ewk->wu.pat_status = eff11_anime_tbl[ewk->wu.char_index].frames;
        ewk->wu.cg_ctr = eff11_frame_tbl[ewk->wu.pat_status][ewk->wu.cg_ix].timer;
        put = debug_bg_tile_put;
        for (i = 0; i < 4; i++) {
            row = (const EFF11_ROW*)&eff11_tile_tbl[i].t[0];
            for (j = 0; j < 16; j++) {
                tile = &row->t[j];
                put(i, tile->ofs, tile->page, (s32)bg070_cell_data);
                eff11_tile_disp(tile->ofs);
            }
        }
        (void)&((WORK*)put)->id;
        scrn_map_set_now(0, (u32)bg_w.bgw[0].bg_address);
        Scrn_Y_Set_R(0, eff11_frame_tbl[ewk->wu.pat_status][ewk->wu.cg_ix].y);
        break;
    case R0_MOVE:
        if (!EXE_flag && !Game_pause) {
            ewk->wu.cg_ctr--;
            if (!ewk->wu.cg_ctr) {
                ewk->wu.cg_ix++;
                if (ewk->wu.cg_ix > 3) {
                    ewk->wu.cg_ix = 0;
                    ewk->wu.now_koc--;
                    if (!ewk->wu.now_koc) {
                        ewk->wu.char_index++;
                        if (ewk->wu.char_index > 13) {
                            ewk->wu.char_index = 0;
                        }
                        ewk->wu.now_koc = eff11_anime_tbl[ewk->wu.char_index].count;
                        ewk->wu.pat_status = eff11_anime_tbl[ewk->wu.char_index].frames;
                    }
                }
                ewk->wu.cg_ctr = eff11_frame_tbl[ewk->wu.pat_status][ewk->wu.cg_ix].timer;
                page = eff11_frame_tbl[ewk->wu.pat_status][ewk->wu.cg_ix].page;
                scrn_map_set_now(0, eff_bg_adrs[page].adrs);
            }
        }
        y = eff11_frame_tbl[ewk->wu.pat_status][ewk->wu.cg_ix].y;
        y += bg_w.bgw[0].abs_y & 0x3FF;
        Scrn_Y_Set_R(0, y);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        for (i = 1; i < 4; i++) {
            simmram_block_free_40(eff_bg_adrs[i].no);
        }
        break;
    }
}



static void bg_adrs_disp(s16 no) {}

s32 effect_11_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    BG_ADRS* adrs;
    BG* bg;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 11;
    bg_adrs_disp(eff_bg_adrs->no);
    bg = &bg_w;
    ewk->wu.work_id = 16;
    eff_bg_adrs[0].no = bg->bgw[0].bg_adrs_c_no;
    eff_bg_adrs[0].adrs = (u32)bg->bgw[0].bg_address;
    for (i = 1; i < 4; i++) {
        (adrs = &eff_bg_adrs[i] + 0)->no = simmram_big_page_alloc_40(1);
        adrs->adrs = simmram_slot_addr(adrs->no);
    }
    return 0;
}
