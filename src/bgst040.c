/*
 * BGST040.C  Stage background (ta0_move slot 4)
 *
 * BG040 runs the stage's three layers: layer 1 (bg0402: the line-scroll base layer with the stage's effects;
 * bg0402_cell_set rewrites two map columns as the layer scrolls past either edge), layer 0 (bg0401) and layer 2
 * (bg0403), then the zoom check, position correction and family set.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
/* bg_sub.h left out: its bg_cell_write takes an s32 u5 */
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "SYS_sub.h"
#include "aboutspr.h"
#include "sys_config.h"
#include "sys_test.h"
#include "meta_col_mem.h"
#include "color3rd.h"
#include "eff05.h"
#include "eff06.h"
#include "eff88.h"

s32 effect_18_init();
void bg_cell_write(s16 bg, s32 ofs, s32 cell, u32 src, u16 u5, s16 attr);
/* provisional name: the stage map data the code passes by address */
extern const u16 bg040_scrn_data[][16][32];
void bg0401(void);
void bg0402(void);
void bg0403(void);
void bg0401_init00(void);
void bg0401_move(void);
void bg0402_init00(void);
void bg0402_move(void);
void bg0403_init00(void);
void bg0403_move(void);
void bg0402_cell_set(void);
#pragma inline(bg0401, bg0402, bg0403)


void BG040(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg0402();
    bgw_ptr = &bg_w.bgw[0];
    bg0401();
    bgw_ptr = &bg_w.bgw[2];
    bg0403();
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set();
}



void bg0401(void) {
    void (*bg0401_jmp[2])() = { bg0401_init00, bg0401_move };
    bg0401_jmp[bgw_ptr->r_no_0]();
}



void bg0401_init00(void) {
    bgw_ptr->r_no_0++;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
}



void bg0401_move(void) {
    bg_x_move_check();
    bg_y_move_check();
}



void bg0402(void) {
    void (*bg0402_jmp[2])() = { bg0402_init00, bg0402_move };
    bg0402_jmp[bgw_ptr->r_no_0]();
}



void bg0402_init00(void) {
    bgw_ptr->r_no_0++;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->suzi_c_no = simmram_small_page_alloc_40(1);
    bgw_ptr->suzi_adrs = (u16*)simmram_slot_addr(bgw_ptr->suzi_c_no);
    scrn_linescroll_set_now(1, bgw_ptr->suzi_adrs);
    memset(bgw_ptr->suzi_adrs, 0, 0x1000);
    Bg_On_R(32);
    bgw_ptr->zuubun = 0x1C7;
    bgw_ptr->no_suzi_line = 967;
    bgw_ptr->u_line = 17;
    bgw_ptr->d_line = 16;
    bgw_ptr->start_suzi = bgw_ptr->suzi_adrs + 1932;
    suzi_line_clear(1);
    load_any_color(103);
    load_char_gfx(0x43A0, 1);
    effect_05_init();
    effect_06_init();
    effect_18_init(1);
    if (Country == 8) {
        effect_88_init(4);
    }
}



void bg0402_move(void) {
    bg_base_x_move_check();
    bg0402_cell_set();
    bg_base_y_move_check();
    bg_chase_move();
    suzi_line_calc_fill(1);
}



void bg0403(void) {
    void (*bg0403_jmp[2])() = { bg0403_init00, bg0403_move };
    bg0403_jmp[bgw_ptr->r_no_0]();
}



void bg0403_init00(void) {
    bgw_ptr->r_no_0++;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
}



void bg0403_move(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
/* Past 0x90 to either side the base layer's map gets the far columns, and back again on return. */
void bg0402_cell_set(void) {
    switch (bg_w.bgw[1].rewrite_flag) {
    case 0:
        if (bg_w.bgw[1].xy[0].disp.pos > 0x90) {
            bg_cell_write(1, 0x2000, 5, (u32)&bg040_scrn_data, 0, 0x240);
            bg_cell_write(1, 0x3000, 11, (u32)&bg040_scrn_data, 0, 0x240);
            bg_w.bgw[1].rewrite_flag = 2;
        } else if (bg_w.bgw[1].xy[0].disp.pos < -0x90) {
            bg_cell_write(1, 0x20C0, 0, (u32)&bg040_scrn_data, 0, 0x240);
            bg_cell_write(1, 0x30C0, 6, (u32)&bg040_scrn_data, 0, 0x240);
            bg_w.bgw[1].rewrite_flag = 1;
        } else {
            bg_w.bgw[1].rewrite_flag = 0;
        }
        break;
    case 1:
        if (bg_w.bgw[1].xy[0].disp.pos > -0x90) {
            bg_cell_write(1, 0x20C0, 4, (u32)&bg040_scrn_data, 0, 0x240);
            bg_cell_write(1, 0x30C0, 10, (u32)&bg040_scrn_data, 0, 0x240);
            bg_w.bgw[1].rewrite_flag = 0;
        }
        break;
    case 2:
        if (bg_w.bgw[1].xy[0].disp.pos < 0x90) {
            bg_cell_write(1, 0x2000, 1, (u32)&bg040_scrn_data, 0, 0x240);
            bg_cell_write(1, 0x3000, 7, (u32)&bg040_scrn_data, 0, 0x240);
            bg_w.bgw[1].rewrite_flag = 0;
        }
        break;
    }
}
