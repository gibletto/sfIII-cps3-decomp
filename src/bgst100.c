/*
 * BGST100.C  Stage background (ta0_move slot 10)
 *
 * BG100 runs the stage's two layers: layer 1 (the line-scroll base layer; bg1001_move also runs the map
 * animation, sixteen frames of four cells that the test switch starts) and layer 0 (the stage graphics, effects
 * and palette), then the zoom check, position correction and family set.
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
#include "eff05.h"
#include "color3rd.h"
#include "eff06.h"
#include "EFF63.h"

/* declarations the headers do not give */
void zoom_ud_check(void);
void bg_x_move_check(void);
void bg_y_move_check(void);
void bg_base_y_move_check(void);
void load_any_color();
/* provisional names */
extern const u32 bg100_scrn_data[];
extern s16 bg100_cnt;
extern s16 bg100_timer;
s32 effect_18_init();
s32 effect_87_init();
void bg1000(void);
void bg1001(void);
void bg1000_init00(void);
void bg1000_move(void);
void bg1001_init00(void);
void bg1001_move(void);
#pragma inline(bg1000, bg1001)


/* provisional name */
/* the four cells of each animation frame */
const s32 bg100_cell_tbl[16][4] = {
    { 0x02, 0x03, 0x0A, 0x0B },
    { 0x10, 0x11, 0x18, 0x19 },
    { 0x12, 0x13, 0x1A, 0x1B },
    { 0x14, 0x15, 0x1C, 0x1D },
    { 0x16, 0x17, 0x1E, 0x1F },
    { 0x20, 0x21, 0x28, 0x29 },
    { 0x22, 0x23, 0x2A, 0x2B },
    { 0x24, 0x25, 0x2C, 0x2D },
    { 0x26, 0x27, 0x2E, 0x2F },
    { 0x30, 0x31, 0x28, 0x39 },
    { 0x32, 0x33, 0x2A, 0x3B },
    { 0x34, 0x35, 0x2C, 0x3D },
    { 0x36, 0x37, 0x3E, 0x3F },
    { 0x40, 0x41, 0x48, 0x49 },
    { 0x42, 0x43, 0x4A, 0x4B },
    { 0x44, 0x45, 0x4C, 0x4D },
};


void BG100(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg1001();
    bgw_ptr = &bg_w.bgw[0];
    bg1000();
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set();
}



/* provisional name */
void bg1000(void) {
    void (*bg1000_jmp[2])() = { bg1000_init00, bg1000_move };
    bg1000_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg1000_init00(void) {
    bgw_ptr->r_no_0++;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
    effect_05_init();
    effect_06_init();
    effect_63_init();
    if (bg_w.area == 0) {
        effect_87_init(3);
        effect_18_init(3);
    }
    load_char_gfx(0x4DE0, 1);
    load_any_color(96);
}



/* provisional name */
void bg1000_move(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
void bg1001(void) {
    void (*bg1001_jmp[2])() = { bg1001_init00, bg1001_move };
    bg1001_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg1001_init00(void) {
    bgw_ptr->r_no_0++;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->suzi_c_no = simmram_small_page_alloc_40(1);
    bgw_ptr->suzi_adrs = (u16*)simmram_slot_addr(bgw_ptr->suzi_c_no);
    scrn_linescroll_set_now(1, bgw_ptr->suzi_adrs);
    memset(bgw_ptr->suzi_adrs, 0, 0x1000);
    Bg_On_R(32);
    suzi_line_clear(1);
    bgw_ptr->zuubun = 0x124;
    bgw_ptr->no_suzi_line = 0x3B0;
    bgw_ptr->u_line = 40;
    bgw_ptr->d_line = 40;
    bgw_ptr->start_suzi = bgw_ptr->suzi_adrs + 0x760;
}



/* provisional name */
/* the base layer move, with the map animation the test switch starts */
void bg1001_move(void) {
    const s32* p;
    s16 sw;
    switch (bgw_ptr->r_no_1) {
    case 0:
        if (exsw_0 & 0x8000) {
            sw = ~p1sw_1 & p1sw_0;
            if (sw & 0x80) {
                bgw_ptr->r_no_1++;
                bg100_timer = 8;
                bg100_cnt = 0;
            }
        }
        break;
    case 1:
        bg100_timer--;
        if (bg100_timer < 0) {
            bg100_timer = 8;
            bg100_cnt++;
            if (bg100_cnt > 15) {
                bgw_ptr->r_no_1++;
            } else {
                p = bg100_cell_tbl[bg100_cnt];
                bg_cell_write(1, 0x2040, *p, (u32)bg100_scrn_data, 0, 0x240);
                p++;
                bg_cell_write(1, 0x2080, *p, (u32)bg100_scrn_data, 0, 0x240);
                p++;
                bg_cell_write(1, 0x3040, *p, (u32)bg100_scrn_data, 0, 0x240);
                p++;
                bg_cell_write(1, 0x3080, *p, (u32)bg100_scrn_data, 0, 0x240);
            }
        }
        break;
    case 2:
        break;
    default:
        break;
    }
    bg_base_x_move_check();
    bg_base_y_move_check();
    bg_chase_move();
    suzi_line_calc(1);
}
