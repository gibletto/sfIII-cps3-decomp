/*
 * BGST020.C  Stage background (ta0_move slot 2)
 *
 * BG020 runs the stage's four layers: layer 1 (bg0201_ctrl, the chasing base layer: stage graphics, palette and
 * effects, some by compel_flag), layer 0 (bg0200) and two synced layers (2 and 4, bg020_layer; speed from
 * bg_sync_speed_tbl), then the zoom check, position correction and family set. In the first area every layer
 * starts low and scrolls up into place (bg0200_demo, faster while the cut button is held).
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
#include "ta_sub2.h"
#include "aboutspr.h"
#include "eff05.h"

/* bgw r_no_0 of a layer with an entrance demo: its bg*_jmp routine */
#define R0_INIT         0       /* set up the layer */
#define R0_DEMO         1       /* the entrance demo */
#define R0_MOVE         2       /* follow the fight */

void zoom_ud_check(void);
void bg_x_move_check(void);
void bg_y_move_check(void);
void bg_base_y_move_check(void);
s32 effect_06_init();
s32 effect_25_init();
s32 effect_44_init();
s32 effect_61_init();
s32 effect_64_init();
s32 effect_87_init();
s32 effect_88_init();
void bg0200(void);
void bg0201_ctrl(void);
void bg0200_init00(void);
void bg0201_init00(void);
void bg0200_demo(void);
static void bg_move_common(void);
static void bg_base_move_common(void);
void bg020_layer(s16 n);
#pragma inline(bg0201_ctrl, bg0200)


/* provisional name */
/* the synced layers' speeds: speed_x, speed_y */
const s32 bg_sync_speed_tbl[4][2] = {
    { 0xE800, 0x10000 }, { 0xCE00, 0x10000 }, { 0xB400, 0x10000 }, { 0xB000, 0x10000 },
};


void BG020(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg0201_ctrl();
    bgw_ptr = &bg_w.bgw[0];
    bg0200();
    bgw_ptr = &bg_w.bgw[2];
    bg020_layer(0);
    bgw_ptr = &bg_w.bgw[4];
    bg020_layer(1);
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set();
}



void bg0200(void) {
    void (*bg0200_jmp[3])() = { bg0200_init00, bg0200_demo, bg_move_common };
    bg0200_jmp[bgw_ptr->r_no_0]();
}



void bg0200_init00(void) {
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



void bg0201_ctrl(void) {
    void (*bg0201_jmp[3])() = { bg0201_init00, bg0200_demo, bg_base_move_common };
    bg0201_jmp[bgw_ptr->r_no_0]();
}



void bg0201_init00(void) {
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
    effect_44_init();
    load_char_gfx(0x5860, 2);
    effect_87_init(1);
    effect_88_init(2);
    switch (bg_w.compel_flag) {
    case 0:
        effect_61_init();
        break;
    case 1:
    case 2:
        effect_64_init(0);
        break;
    case 3:
        effect_25_init(3);
        break;
    }
    effect_64_init(1);
    effect_64_init(2);
    effect_25_init(4);
    load_char_gfx(0x5D30, 1);
    load_any_color(105);
}



static void bg_base_move_common(void) {
    bg_base_x_move_check();
    bg_base_y_move_check();
    bg_chase_move();
}



/* provisional name */
void bg020_layer(s16 n) {
    switch (bgw_ptr->r_no_0) {
    case R0_INIT:
        bgw_ptr->r_no_0++;
        bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
        bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
        bgw_ptr->xy[1].disp.pos = bgw_ptr->pos_y_work = 0;
        bgw_ptr->zuubun = 0;
        if (n) {
            bgw_ptr->fam_no = 4;
        } else {
            bgw_ptr->fam_no = 2;
        }
        bgw_ptr->xy[0].disp.low = bgw_ptr->xy[1].disp.low = 0;
        bgw_ptr->y_limit = bgw_ptr->y_limit2 = 0x100;
        bgw_ptr->speed_x = bg_sync_speed_tbl[n][0];
        bgw_ptr->speed_y = bg_sync_speed_tbl[n][1];
        if (bg_w.area == 0) {
            bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 0x10A;
            bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
        } else {
            bgw_ptr->r_no_0++;
        }
        sync_fam_set3(bgw_ptr->fam_no);
        break;
    case R0_DEMO:
        bg0200_demo();
        sync_fam_set3(bgw_ptr->fam_no);
        break;
    case R0_MOVE:
        bg_x_move_check();
        bg_y_move_check();
        sync_fam_set3(bgw_ptr->fam_no);
        break;
    }
}



/* provisional name */
/* the first area's layers scroll up into place: faster while the cut button is held */
void bg0200_demo(void) {
    if (Cut_Cut_Cut()) {
        bgw_ptr->xy[1].cal -= bgw_ptr->speed_y * 6;
    } else {
        bgw_ptr->xy[1].cal -= bgw_ptr->speed_y * 4;
    }
    if (bgw_ptr->xy[1].cal < 0) {
        bgw_ptr->xy[1].cal = 0;
        bgw_ptr->r_no_0++;
        bg_app = 0;
    }
}
