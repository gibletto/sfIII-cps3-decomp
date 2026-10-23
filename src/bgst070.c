/*
 * BGST070.C  Stage background
 *
 * BG070 runs the stage's three layers: layer 1 (bg0701: the line-scroll base layer; its init blits two
 * cells into the map, the second by area), layer 0 (bg0700: graphics, palette and effects by area) and, in the
 * first area only, layer 2 (bg0702), then the zoom check, position correction and family set.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
/* bg_sub.h left out: blit_8x16_tile is called here without a prototype */
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "SYS_sub.h"
#include "aboutspr.h"
#include "eff05.h"
#include "EFF11.h"
#include "color3rd.h"
#include "eff06.h"
#include "eff65.h"

/* declarations the headers do not give */
void zoom_ud_check(void);
void bg_x_move_check(void);
void bg_y_move_check(void);
void bg_base_y_move_check(void);
void load_any_color();
void effect_94_entry(s16 sw);
void blit_8x16_tile();
s32 effect_66_init();
s32 effect_68_init();
/* provisional name */
extern const u16 bg070_cell_data[];
void bg0700(void);
void bg0701(void);
void bg0700_init00(void);
void bg0700_move(void);
void bg0701_init00(void);
void bg0701_move(void);
void bg0702(void);
void bg0702_init00(void);
void bg0702_move(void);
void bg0701_cell_set(void);
#pragma inline(bg0700, bg0701)


void BG070(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg0701();
    bgw_ptr = &bg_w.bgw[0];
    bg0700();
    bgw_ptr = &bg_w.bgw[2];
    bg0702();
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set();
}



/* provisional name */
void bg0700(void) {
    void (*bg0700_jmp[2])() = { bg0700_init00, bg0700_move };
    bg0700_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg0700_init00(void) {
    bgw_ptr->r_no_0++;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
    if (bg_w.area) {
        load_any_color(101);
        effect_94_entry(1);
        effect_66_init(0);
        effect_68_init();
    } else {
        load_any_color(100);
        effect_11_init();
        effect_65_init();
        effect_94_entry(0);
        Sound_SE(109);
    }
    effect_05_init();
    effect_06_init();
    load_char_gfx(0x52D0, 1);
}



/* provisional name */
void bg0700_move(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
void bg0701(void) {
    void (*bg0701_jmp[2])() = { bg0701_init00, bg0701_move };
    bg0701_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg0701_init00(void) {
    bgw_ptr->r_no_0++;
    bg0701_cell_set();
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->suzi_c_no = simmram_small_page_alloc_40(1);
    bgw_ptr->suzi_adrs = (u16*)simmram_slot_addr(bgw_ptr->suzi_c_no);
    scrn_linescroll_set_now(1, bgw_ptr->suzi_adrs);
    memset(bgw_ptr->suzi_adrs, 0, 0x1000);
    Bg_On_R(32);
    suzi_line_clear(1);
    bgw_ptr->zuubun = 0x100;
    bgw_ptr->no_suzi_line = 0x3D0;
    bgw_ptr->u_line = 8;
    bgw_ptr->d_line = 40;
    bgw_ptr->start_suzi = bgw_ptr->suzi_adrs + 0x7A0;
}



/* provisional name */
void bg0701_move(void) {
    bg_base_x_move_check();
    bg_base_y_move_check();
    bg_chase_move();
    suzi_line_calc(1);
}



/* provisional name */
/* layer 2 runs in the first area only */
void bg0702(void) {
    void (*bg0702_jmp[2])() = { bg0702_init00, bg0702_move };
    if (bg_w.area) {
        return;
    }
    bg0702_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg0702_init00(void) {
    bgw_ptr->r_no_0++;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
}



/* provisional name */
void bg0702_move(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
/* two 8x16 cells of the stage's scroll graphics into layer 1's map; the second by area */
void bg0701_cell_set(void) {
    u16 code;
    u32 base;
    u32 ofs;
    u32 cell;
    base = (u32)bg_w.bgw[1].bg_address;
    ofs = 0x3000;
    ofs += base;
    code = bg_w.scroll_cg_adr >> 7;
    cell = 0x420;
    cell += (u32)bg070_cell_data;
    blit_8x16_tile(cell, code, ofs, 0x240);
    if (bg_w.area) {
        cell = 0x1400;
    } else {
        cell = 0x13800;
    }
    base = (u32)bg_w.bgw[1].bg_address;
    ofs = 0x30E0;
    ofs += base;
    code = bg_w.scroll_cg_adr >> 7;
    cell += (u32)bg070_cell_data;
    blit_8x16_tile(cell, code, ofs, 0x240);
}



/* provisional name */
s32 bg070_check(void) {
    if (bg_w.area) {
        return 1;
    }
    if (plw[0].player_number != 4 && plw[1].player_number != 4) {
        return 1;
    }
    if (plw[0].player_number == 4 && plw[1].player_number == 4) {
        return 1;
    }
    return 0;
}
