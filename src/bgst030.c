/*
 * BGST030.C  Stage background (ta0_move slot 3)
 *
 * BG030 runs the stage's three scroll layers: layer 1 (bg0302: the line-scroll base layer, with the
 * stage's effects), layer 0 (bg0301) and layer 2 (bg0303), then the zoom check, position correction and
 * family set. In the first area every layer starts low and scrolls up into place (bg030_appear, faster while
 * the cut button is held) before it moves with the base layer.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "bg_sub.h"
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
#include "eff14.h"

s32 effect_18_init();
s32 effect_34_init();
void setup_seraph_cells(void);
void bg0301(void);
void bg0302(void);
void bg0303(void);
void bg0301_init00(void);
void bg0302_init00(void);
void bg0302_move(void);
void bg0303_init00(void);
void bg0303_move(void);
void bg030_appear(void);
static void bg_move_common(void);
#pragma inline(bg0301, bg0302, bg0303)


void BG030(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg0302();
    bgw_ptr = &bg_w.bgw[0];
    bg0301();
    bgw_ptr = &bg_w.bgw[2];
    bg0303();
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set();
}



void bg0301(void) {
    void (*bg0301_jmp[3])() = { bg0301_init00, bg030_appear, bg_move_common };
    bg0301_jmp[bgw_ptr->r_no_0]();
}



void bg0301_init00(void) {
    bgw_ptr->r_no_0++;
    if (bg_w.area == 0) {
        bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 176;
        bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
    } else {
        bgw_ptr->r_no_0++;
    }
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
}



static void bg_move_common(void) {
    bg_x_move_check();
    bg_y_move_check();
}



void bg0302(void) {
    void (*bg0302_jmp[3])() = { bg0302_init00, bg030_appear, bg0302_move };
    bg0302_jmp[bgw_ptr->r_no_0]();
}



void bg0302_init00(void) {
    bgw_ptr->r_no_0++;
    if (bg_w.area == 0) {
        bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 176;
        bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
        bg_app = 1;
    } else {
        bgw_ptr->r_no_0++;
    }
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->suzi_c_no = simmram_small_page_alloc_40(1);
    bgw_ptr->suzi_adrs = (u16*)simmram_slot_addr(bgw_ptr->suzi_c_no);
    scrn_linescroll_set_now(1, bgw_ptr->suzi_adrs);
    memset(bgw_ptr->suzi_adrs, 0, 0x1000);
    Bg_On_R(32);
    bgw_ptr->zuubun = 0xCC;
    bgw_ptr->no_suzi_line = 967;
    bgw_ptr->u_line = 16;
    bgw_ptr->d_line = 40;
    bgw_ptr->start_suzi = bgw_ptr->suzi_adrs + 1934;
    suzi_line_clear(1);
    load_any_color(102);
    load_char_gfx(0x41C0, 1);
    setup_seraph_cells();
    effect_05_init();
    effect_06_init();
    effect_18_init(0);
    effect_14_init(1);
    effect_14_init(2);
    effect_14_init(3);
    effect_34_init();
}



/* provisional name */
/* base layer move and its line scroll */
void bg0302_move(void) {
    bg_base_x_move_check();
    bg_base_y_move_check();
    bg_chase_move();
    suzi_line_calc(1);
}



/* provisional name */
/* layer 2 */
void bg0303(void) {
    void (*bg0303_jmp[3])() = { bg0303_init00, bg030_appear, bg0303_move };
    bg0303_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg0303_init00(void) {
    bgw_ptr->r_no_0++;
    if (bg_w.area == 0) {
        bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 176;
        bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
    } else {
        bgw_ptr->r_no_0++;
    }
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
}



/* provisional name */
void bg0303_move(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
/* the first area's layers scroll up into place: twice as fast while the cut button is held */
void bg030_appear(void) {
    if (Cut_Cut_Cut()) {
        bgw_ptr->xy[1].cal -= bgw_ptr->speed_y * 4;
    } else {
        bgw_ptr->xy[1].cal -= bgw_ptr->speed_y * 2;
    }
    if (bgw_ptr->xy[1].cal < 0) {
        bgw_ptr->xy[1].cal = 0;
        bgw_ptr->r_no_0++;
        bg_app = 0;
    }
}
