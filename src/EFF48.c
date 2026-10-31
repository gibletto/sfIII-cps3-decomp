/*
 * EFF48.C  Effect 48: animated background pages
 *
 * effect_48_init (from bgst110's stage) creates the animator for BG 0 (type 0) or BG 1 (type 1);
 * for type 1 it records the two layers' pages in eff_bg_adrs and allocates four more. On its first
 * frame effect_48_move writes the animation's tiles into the pages (eff48_page0_write /
 * eff48_page1_write; Country 8 has its own type 1 tiles). It then steps through the 20 frames of
 * eff48_frame_tbl0 / 1, each showing one page at its own Y offset for its time, two or three frames
 * shorter in the later areas (eff48_set_wait). The allocated page is freed when the effect ends.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "sys_config.h"
#include "sys_test.h"
#include "end_main.h"
#include "EFF48.h"

/* routine_no[0] */
#define R0_INIT         0       /* write the pages, show the first frame */
#define R0_MOVE         1       /* step through the animation frames */



extern const EFF48_FRAME eff48_frame_tbl0[20];
extern const EFF48_FRAME eff48_frame_tbl1[20];
extern const EFF48_TILE eff48_tile_tbl0[2][12];
extern const EFF48_TILE eff48_tile_tbl1[4][8];
extern const EFF48_TILE eff48_tile_jp_tbl1[4][8];
extern const u16 eff48_scrn_data[46][16][32];
void debug_bg_tile_put(s16 bg, s32 ofs, s32 page, s32 src);

void effect_48_move(WORK_Other* ewk) {
    s16 y;
    register s16 ty;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.cg_ix = 0;
        if (ewk->wu.type) {
            ewk->wu.cg_ctr = eff48_frame_tbl1[0].timer;
            eff48_set_wait(ewk);
            eff48_page1_write();
            scrn_map_set_now(1, eff_bg_adrs[2].adrs);
            y = eff48_frame_tbl1[(s8)ewk->wu.cg_ix].y + bg_w.bgw[1].position_y;
            Scrn_Y_Set_R(1, y);
        } else {
            ewk->wu.cg_ctr = eff48_frame_tbl0[0].timer;
            eff48_set_wait(ewk);
            eff48_page0_write();
            scrn_map_set_now(0, eff_bg_adrs[0].adrs);
            y = eff48_frame_tbl0[(s8)ewk->wu.cg_ix].y + bg_w.bgw[0].position_y;
            Scrn_Y_Set_R(0, y);
        }
        break;
    case R0_MOVE:
        if (!EXE_flag && !Game_pause) {
            ewk->wu.cg_ctr--;
            if (!ewk->wu.cg_ctr) {
                ewk->wu.cg_ix++;
                if (ewk->wu.cg_ix > 19) {
                    ewk->wu.cg_ix = 0;
                }
                if (ewk->wu.type) {
                    ewk->wu.cg_ctr = eff48_frame_tbl1[(s8)ewk->wu.cg_ix].timer;
                    eff48_set_wait(ewk);
                    scrn_map_set(1, eff_bg_adrs[eff48_frame_tbl1[(s8)ewk->wu.cg_ix].slot].adrs);
                } else {
                    ewk->wu.cg_ctr = eff48_frame_tbl0[(s8)ewk->wu.cg_ix].timer;
                    eff48_set_wait(ewk);
                    scrn_map_set(0, eff_bg_adrs[eff48_frame_tbl0[(s8)ewk->wu.cg_ix].slot].adrs);
                }
            }
        }
        if (ewk->wu.type) {
            ty = eff48_frame_tbl1[(s8)ewk->wu.cg_ix].y;
            ty += bg_w.bgw[1].abs_y & 0x3FF;
            Scrn_Y_Set_W(1, ty);
        } else {
            ty = eff48_frame_tbl0[(s8)ewk->wu.cg_ix].y;
            ty += bg_w.bgw[0].abs_y & 0x3FF;
            Scrn_Y_Set_W(0, ty);
        }
        break;
    default:
        if (ewk->wu.type) {
            simmram_block_free_40(eff_bg_adrs[3].no);
        } else {
            simmram_block_free_40(eff_bg_adrs[2].no);
        }
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

s32 effect_48_init(s16 type) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    BG_ADRS* adrs;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 48;
    ewk->wu.work_id = 16;
    ewk->wu.type = type;
    if (type) {
        eff_bg_adrs[0].no = bg_w.bgw[0].bg_adrs_c_no;
        eff_bg_adrs[0].adrs = (u32)bg_w.bgw[0].bg_address;
        eff_bg_adrs[1].no = simmram_big_page_alloc_40(1);
        eff_bg_adrs[1].adrs = simmram_slot_addr(eff_bg_adrs[1].no);
        eff_bg_adrs[2].no = bg_w.bgw[1].bg_adrs_c_no;
        eff_bg_adrs[2].adrs = (u32)bg_w.bgw[1].bg_address;
        for (i = 3; i < 6; i++) {
            (adrs = &eff_bg_adrs[i])->no = simmram_big_page_alloc_40(1);
            adrs->adrs = simmram_slot_addr(adrs->no);
        }
    }
    return 0;
}

void eff48_set_wait(WORK_Other* ewk) {
    switch (bg_w.area) {
    case 1:
        ewk->wu.cg_ctr -= 2;
        break;
    case 2:
        ewk->wu.cg_ctr -= 3;
        break;
    }
}

void eff48_page0_write(void) {
    const EFF48_TILE* data;
    const EFF48_TILE* tile;
    s16 i;
    s16 j;
    for (i = 0; i < 2; i++) {
        data = &eff48_tile_tbl0[i][0];
        for (j = 0; j < 12; j++) {
            tile = data;
            tile += j;
            debug_bg_tile_put(i, tile->ofs, tile->page, (s32)eff48_scrn_data);
        }
    }
}

void eff48_page1_write(void) {
    const EFF48_TILE* data;
    const EFF48_TILE* tile;
    s16 i;
    s16 j;
    for (i = 2; i < 6; i++) {
        if (Country == 8) {
            data = &eff48_tile_jp_tbl1[i - 2][0];
        } else {
            data = &eff48_tile_tbl1[i - 2][0];
        }
        for (j = 0; j < 8; j++) {
            tile = data;
            tile += j;
            debug_bg_tile_put(i, tile->ofs, tile->page, (s32)eff48_scrn_data);
        }
    }
}
