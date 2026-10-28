/*
 * BGST000.C  Stage background (ta0_move slot 0)
 *
 * BG000 runs the stage's three layers: layer 1 (the chasing base layer), layer 0 (the stage graphics and
 * effects) and layer 4 (a synced layer), then the zoom check, position correction and family set.
 * In the first area every layer starts raised (speed_y * 256) with the screen zoomed in (Frame_Up), and
 * bg000_demo brings them down: a short wait, then the screen zooms back out while the layers come down;
 * pressing a shot button three times cuts the drop short.
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
#include "Com_Pl.h"
#include "eff05.h"
#include "eff06.h"
#include "EFF47.h"
#include "eff12.h"

/* bgw r_no_0 of a layer with an entrance demo: its bg*_jmp routine */
#define R0_INIT         0       /* set up the layer */
#define R0_DEMO         1       /* the entrance demo */
#define R0_MOVE         2       /* follow the fight */

/* declarations the headers do not give */
void zoom_ud_check(void);
void bg_x_move_check(void);
void bg_y_move_check(void);
void bg_base_x_move_check(void);
void bg_base_y_move_check(void);
void setup_mark_cells();
void effect_94_entry();
/* provisional names */
extern s8 bg_demo_shot;
extern s8 bg_demo_cnt;

void bg000_layer1(void);
void bg000_layer1_init(void);
void bg000_layer0(void);
void bg000_layer0_init(void);
void bg000_layer4(void);
void bg000_demo(void);
static void bg_base_move_common(void);
static void bg_move_common(void);
#pragma inline(bg000_layer1, bg000_layer0)


void BG000(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg000_layer1();
    bgw_ptr = &bg_w.bgw[0];
    bg000_layer0();
    bgw_ptr = &bg_w.bgw[4];
    bg000_layer4();
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set();
}



/* provisional name */
void bg000_layer1(void) {
    void (*bg0001_jmp[3])() = { bg000_layer1_init, bg000_demo, bg_base_move_common };
    bg0001_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg000_layer1_init(void) {
    bgw_ptr->r_no_0++;
    if (bg_w.area == 0) {
        bg_app = 1;
        bg_demo_shot = 0;
        bg_demo_cnt = 10;
        bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 256;
        bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
        bg_w.bg_f_x = bg_w.bg_f_y = 24;
        Frame_Up(16, 0xD0, 40, 40);
    } else {
        bgw_ptr->r_no_0++;
    }
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
    effect_05_init();
    effect_06_init();
    effect_94_entry(0);
}



static void bg_base_move_common(void) {
    bg_base_x_move_check();
    bg_base_y_move_check();
    bg_chase_move();
}



/* provisional name */
void bg000_layer0(void) {
    void (*bg0000_jmp[3])() = { bg000_layer0_init, bg000_demo, bg_move_common };
    bg0000_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg000_layer0_init(void) {
    bgw_ptr->r_no_0++;
    if (bg_w.area == 0) {
        bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 256;
        bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
    } else {
        bgw_ptr->r_no_0++;
    }
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
    effect_12_init();
    effect_47_init();
    load_char_gfx(0x6000, 1);
    load_char_gfx(0x6390, 1);
    setup_mark_cells();
}



static void bg_move_common(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
void bg000_layer4(void) {
    switch (bgw_ptr->r_no_0) {
    case R0_INIT:
        bgw_ptr->r_no_0++;
        bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
        bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
        bgw_ptr->pos_y_work = 0;
        bgw_ptr->zuubun = 0;
        bgw_ptr->fam_no = 4;
        bgw_ptr->xy[0].disp.low = 0;
        bgw_ptr->xy[1].disp.pos = 0;
        bgw_ptr->xy[1].disp.low = 0;
        bgw_ptr->speed_x = 0xC000;
        bgw_ptr->speed_y = 0xF000;
        if (bg_w.area == 0) {
            bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 256;
            bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
        } else {
            bgw_ptr->r_no_0++;
        }
        break;
    case R0_DEMO:
        bg000_demo();
        sync_fam_set3(4);
        break;
    case R0_MOVE:
        bg_x_move_check();
        bg_y_move_check();
        sync_fam_set3(4);
        break;
    }
}



/* provisional name */
/* the drop-in: wait bg_demo_cnt frames, then zoom out and come down; three shot presses end it at once */
void bg000_demo(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        if (bgw_ptr->fam_no == 1) {
            bg_demo_cnt--;
        }
        if (bg_demo_cnt == 0) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 1:
        if (bgw_ptr->fam_no == 1) {
            if (pl_shot_trg_check()) {
                bg_demo_shot++;
            }
            if (bg_w.bg_f_x != 64) {
                bg_w.bg_f_x++;
                bg_w.bg_f_y++;
                if (bg_w.bg_f_x < 64) {
                    Frame_Down(16, 0xD0, 1, 1);
                } else {
                    bg_w.bg_f_x = bg_w.bg_f_y = 64;
                    Zoomf_Init();
                }
            }
        }
        if (bg_demo_shot > 2) {
            bgw_ptr->xy[1].cal = bgw_ptr->pos_y_work;
            bgw_ptr->r_no_0++;
            bg_app = 0;
            bgw_ptr->r_no_1 = 0;
            Zoomf_Init();
            bg_w.bg_f_x = bg_w.bg_f_y = 64;
            return;
        }
        if (Cut_Cut_Cut()) {
            bgw_ptr->xy[1].cal -= bgw_ptr->speed_y * 4;
        } else {
            bgw_ptr->xy[1].cal -= bgw_ptr->speed_y * 2;
        }
        if (bgw_ptr->xy[1].cal < bgw_ptr->pos_y_work) {
            Zoomf_Init();
            bgw_ptr->xy[1].cal = bgw_ptr->pos_y_work;
            bgw_ptr->r_no_0++;
            bgw_ptr->r_no_1 = 0;
            bg_app = 0;
        }
        break;
    }
}
