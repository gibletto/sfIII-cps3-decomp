/*
 * BGST010.C  Stage background, task slot 1
 *
 * BG010 runs the stage's four layers: layer 1 (the chasing base layer, with the stage graphics, palette and
 * effects), layer 0, layer 2 and layer 4 (a synced layer), then the zoom check, position correction and
 * family set. In the first area every layer starts raised (speed_y * 0x10A) and bg010_demo brings it down.
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
#include "ta_sub.h"
#include "aboutspr.h"
#include "color3rd.h"
#include "eff05.h"
#include "eff06.h"
#include "eff64.h"

/* declarations the headers do not give */
void zoom_ud_check(void);
void bg_x_move_check(void);
void bg_y_move_check(void);
void bg_base_x_move_check(void);
void bg_base_y_move_check(void);
void load_any_color();
void effect_94_entry();
s32 effect_69_init();

void bg010_layer0(void);
void bg010_layer0_init(void);
void bg010_layer1(void);
void bg010_layer1_init(void);
void bg010_layer2(void);
void bg010_layer2_init(void);
void bg010_layer2_move(void);
void bg010_layer4(void);
void bg010_demo(void);
static void bg_move_common(void);
static void bg_base_move_common(void);
#pragma inline(bg010_layer0, bg010_layer1, bg010_layer2)


void BG010(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg010_layer1();
    bgw_ptr = &bg_w.bgw[0];
    bg010_layer0();
    bgw_ptr = &bg_w.bgw[2];
    bg010_layer2();
    bg010_layer4();
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set();
}



/* provisional name */
void bg010_layer0(void) {
    void (*bg0100_jmp[3])() = { bg010_layer0_init, bg010_demo, bg_move_common };
    bg0100_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg010_layer0_init(void) {
    bgw_ptr->r_no_0++;
    if (bg_w.area == 0) {
        bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 0x10A;
        bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
    } else {
        bgw_ptr->r_no_0++;
    }
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].disp.pos = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
}



static void bg_move_common(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
void bg010_layer1(void) {
    void (*bg0101_jmp[3])() = { bg010_layer1_init, bg010_demo, bg_base_move_common };
    bg0101_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
/* also the stage graphics, palette and effects */
void bg010_layer1_init(void) {
    bgw_ptr->r_no_0++;
    if (bg_w.area == 0) {
        bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 0x10A;
        bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
        bg_app = 1;
    } else {
        bgw_ptr->r_no_0++;
    }
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
    effect_05_init();
    effect_06_init();
    effect_69_init();
    effect_64_init(3);
    effect_64_init(4);
    effect_94_entry(1);
    load_char_gfx(0x5620, 1);
    load_any_color(104);
}



static void bg_base_move_common(void) {
    bg_base_x_move_check();
    bg_base_y_move_check();
    bg_chase_move();
}



/* provisional name */
void bg010_layer2(void) {
    void (*bg0102_jmp[3])() = { bg010_layer2_init, bg010_demo, bg010_layer2_move };
    bg0102_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg010_layer2_init(void) {
    bgw_ptr->r_no_0++;
    if (bg_w.area == 0) {
        bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 0x10A;
        bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
    } else {
        bgw_ptr->r_no_0++;
    }
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
}



/* provisional name */
void bg010_layer2_move(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
/* the synced layer sets bgw_ptr itself */
void bg010_layer4(void) {
    bgw_ptr = &bg_w.bgw[4];
    switch (bgw_ptr->r_no_0) {
    case 0:
        bgw_ptr->r_no_0++;
        bgw_ptr->speed_x = 0x8000;
        bgw_ptr->speed_y = 0xA000;
        bgw_ptr->fam_no = 3;
        bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
        bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
        bgw_ptr->zuubun = 0;
        bgw_ptr->xy[0].disp.low = 0;
        if (bg_w.area == 0) {
            bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 0x10A;
            bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
        } else {
            bgw_ptr->xy[1].disp.pos = bgw_ptr->pos_y_work = 0;
        }
        break;
    case 1:
        bg010_demo();
        break;
    case 2:
        bg_x_move_check();
        bg_y_move_check();
        sync_fam_set3(4);
        break;
    }
}



/* provisional name */
/* the drop-in: each layer comes down to 0 */
void bg010_demo(void) {
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
