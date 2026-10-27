/*
 * BGST110.C  Stage background: ta0_move slots 11-13
 *
 * BG110 runs the stage's four layers: layer 1 (bg1102, the base layer that chases the players: graphics,
 * palette and effects by area; in the first area against a human Gill the frame first zooms in, bg1102_zoom_in),
 * layer 0 (bg1101), layer 2 (bg1103) and layer 4 (bg110_sync_common, a synced layer), then the zoom check,
 * position correction and family set.
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
#include "Com_Pl.h"
#include "eff14.h"
#include "eff05.h"
#include "eff06.h"
#include "eff20.h"
#include "EFF82.h"
#include "EFF83.h"
#include "aboutspr.h"
#include "fighter.h"

/* declarations the headers do not give */
void zoom_ud_check(void);
void bg_x_move_check(void);
void bg_y_move_check(void);
void bg_base_x_move_check(void);
void bg_base_y_move_check(void);
void effect_94_entry(s16 sw);
s32 effect_48_init();
s32 effect_75_init();

void bg1101(void);
void bg1101_init00(void);
void bg1101_move(void);
void bg1102(void);
void bg1102_init00(void);
void bg1102_zoom_in(void);
void bg1102_move(void);
void bg1103(void);
void bg1103_init00(void);
void bg1103_move(void);
void bg110_sync_common(void);
void bg110_sync_init(void);
void bg110_sync_move(void);
#pragma inline(bg1101, bg1102, bg1103, bg110_sync_common)


void BG110(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg1102();
    bgw_ptr = &bg_w.bgw[0];
    bg1101();
    bgw_ptr = &bg_w.bgw[2];
    bg1103();
    bgw_ptr = &bg_w.bgw[4];
    bg110_sync_common();
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set();
}



void bg1101(void) {
    void (*bg1101_jmp[2])() = { bg1101_init00, bg1101_move };
    bg1101_jmp[bgw_ptr->r_no_0]();
}



void bg1101_init00(void) {
    bgw_ptr->r_no_0++;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
}



void bg1101_move(void) {
    bg_x_move_check();
    bg_y_move_check();
}



void bg1102(void) {
    void (*bg1102_jmp[3])() = { bg1102_init00, bg1102_zoom_in, bg1102_move };
    bg1102_jmp[bgw_ptr->r_no_0]();
}



void bg1102_init00(void) {
    bgw_ptr->r_no_0++;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
    effect_05_init();
    effect_06_init();
    effect_48_init(0);
    effect_48_init(1);
    load_char_gfx(0x6240, 1);
    load_char_gfx(0x6510, 1);
    setup_GILL_exsa_obj();
    switch (bg_w.area) {
    case 0:
        effect_82_init();
        if ((plw[0].player_number == PL_IBUKI && plw[0].wu.operator == 0)
            || (plw[1].player_number == PL_IBUKI && plw[1].wu.operator == 0)) {
            if (Game_setting.mode == 0) {
                bg_w.bg_f_x = bg_w.bg_f_y = 80;
                Frame_Down(192, 224, 16, 16);
            }
        } else {
            bgw_ptr->r_no_0++;
        }
        load_any_color(109);
        break;
    case 1:
        bgw_ptr->r_no_0++;
        load_any_color(110);
        effect_82_init();
        effect_48_init(1);
        effect_75_init();
        effect_83_init();
        effect_94_entry(0);
        break;
    case 2:
        bgw_ptr->r_no_0++;
        effect_94_entry(1);
        load_any_color(111);
        effect_83_init();
        effect_20_init();
        break;
    }
    effect_14_init(9);
    effect_14_init(10);
    effect_14_init(4);
    effect_14_init(5);
    effect_14_init(6);
    effect_14_init(7);
    effect_14_init(8);
}



/* provisional name */
/* zooms the frame in to bg_f_x 64, then Zoomf_Init */
void bg1102_zoom_in(void) {
    if (C_No1 > 3 || Allow_a_battle_f) {
        if (Game_setting.mode == 0) {
            bg_w.bg_f_x--;
            bg_w.bg_f_y--;
            if (bg_w.bg_f_x > 64) {
                Frame_Up(192, 224, 1, 1);
            } else {
                bgw_ptr->r_no_0++;
                Zoomf_Init();
                bg_w.bg_f_x = bg_w.bg_f_y = 64;
            }
        } else {
            bgw_ptr->r_no_0++;
        }
    }
}



void bg1102_move(void) {
    bg_base_x_move_check();
    bg_base_y_move_check();
    bg_chase_move();
}



/* provisional name */
void bg1103(void) {
    void (*bg1103_jmp[2])() = { bg1103_init00, bg1103_move };
    bg1103_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg1103_init00(void) {
    bgw_ptr->r_no_0++;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
}



/* provisional name */
void bg1103_move(void) {
    bg_x_move_check();
    bg_y_move_check();
}



void bg110_sync_common(void) {
    void (*bg110_sync_jmp[2])() = { bg110_sync_init, bg110_sync_move };
    bg110_sync_jmp[bgw_ptr->r_no_0]();
}



void bg110_sync_init(void) {
    bgw_ptr->r_no_0++;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
    bgw_ptr->fam_no = 4;
    bgw_ptr->y_limit = bgw_ptr->y_limit2 = 160;
    bgw_ptr->pos_y_work = 0;
    bgw_ptr->xy[1].disp.pos = 0;
    bgw_ptr->speed_x = 0xE000;
    bgw_ptr->speed_y = 0x10000;
    sync_fam_set3(4);
}



void bg110_sync_move(void) {
    bg_x_move_check();
    bg_y_move_check();
    sync_fam_set3(4);
}
