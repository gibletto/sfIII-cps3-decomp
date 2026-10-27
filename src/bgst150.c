/*
 * BGST150.C  Stage background (ta0_move slot 15)
 *
 * BG150 runs the stage's three layers: layer 1 (bg150_layer1, the chasing base layer; in area 1 it starts
 * effect C3 and draws its own map into eff_bg_adrs[0], then waits for bg_land_flag to switch back to its
 * map with a quake and Sound_SE(119)), layer 0 (gfx, palette and effects) and layer 2 (bg150_layer2, a synced
 * layer), then the zoom check, position correction and Bg_Family_Set_2.
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
#include "se_3.h"
#include "eff05.h"
#include "eff06.h"
#include "eff14.h"
#include "EFF85.h"
#include "eff87.h"
#include "eff88.h"

/* bgw r_no_0 of a layer that follows the camera */
#define SYNC_INIT       0       /* set up the layer */
#define SYNC_MOVE       1       /* follow the camera (bg_x_move_check, bg_y_move_check) */

/* declarations the headers do not give */
void zoom_ud_check(void);
void bg_x_move_check(void);
void bg_y_move_check(void);
void bg_base_x_move_check(void);
void bg_base_y_move_check(void);
void Bg_Family_Set_2(void);
void load_any_color();
void debug_bg_tile_put();
s32 effect_C3_init();
/* provisional name */
extern const u16 bg150_scrn_data[][16][32];

void bg150_layer0(void);
void bg150_layer0_init(void);
void bg150_layer1(void);
void bg150_layer1_init(void);
void bg150_layer2(void);
static void bg_move_common(void);
static void bg_base_move_common(void);
#pragma inline(bg150_layer0, bg150_layer1)


void BG150(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg150_layer1();
    bgw_ptr = &bg_w.bgw[0];
    bg150_layer0();
    bgw_ptr = &bg_w.bgw[2];
    bg150_layer2();
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set_2();
}



/* provisional name */
void bg150_layer0(void) {
    void (*bg1500_jmp[2])() = { bg150_layer0_init, bg_move_common };
    bg1500_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg150_layer0_init(void) {
    bgw_ptr->r_no_0++;
    bgw_ptr->r_no_1 = 0;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
    load_char_gfx(0x50B0, 1);
    load_any_color(99);
    effect_14_init(0);
    effect_87_init(4);
    effect_88_init(1);
    if (bg_w.compel_flag == 3) {
        effect_85_init();
    }
    effect_05_init();
    effect_06_init();
}



static void bg_move_common(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
void bg150_layer1(void) {
    void (*bg1501_jmp[2])() = { bg150_layer1_init, bg_base_move_common };
    bg1501_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg150_layer1_init(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bg_land_flag = 0;
        bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
        bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
        bgw_ptr->position_y = bgw_ptr->wxy[1].disp.pos = bgw_ptr->xy[1].disp.pos = 0;
        bgw_ptr->zuubun = 0;
        if (bg_w.area != 1) {
            bgw_ptr->r_no_0++;
            break;
        }
        effect_C3_init(1);
        eff_bg_adrs[0].no = simmram_big_page_alloc_40(1);
        eff_bg_adrs[0].adrs = simmram_slot_addr(eff_bg_adrs[0].no);
        debug_bg_tile_put(0, 0x2020, 3, (u32)bg150_scrn_data);
        debug_bg_tile_put(0, 0x2060, 4, (u32)bg150_scrn_data);
        debug_bg_tile_put(0, 0x20A0, 5, (u32)bg150_scrn_data);
        debug_bg_tile_put(0, 0x3020, 11, (u32)bg150_scrn_data);
        debug_bg_tile_put(0, 0x3060, 12, (u32)bg150_scrn_data);
        debug_bg_tile_put(0, 0x30A0, 13, (u32)bg150_scrn_data);
        scrn_map_set_now(1, eff_bg_adrs[0].adrs);
        break;
    case 1:
        if (bg_land_flag) {
            bgw_ptr->r_no_1++;
            scrn_map_set_now(1, (u32)bg_w.bgw[1].bg_address);
            bg_w.quake_y_index = 32;
            Sound_SE(119);
        }
        break;
    case 2:
        if (bg_w.quake_y_index == 0) {
            bgw_ptr->r_no_0++;
        }
        break;
    }
}



static void bg_base_move_common(void) {
    bg_base_x_move_check();
    bg_base_y_move_check();
    bg_chase_move();
}



/* provisional name */
void bg150_layer2(void) {
    switch (bgw_ptr->r_no_0) {
    case SYNC_INIT:
        bgw_ptr->r_no_0++;
        bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
        bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
        bgw_ptr->zuubun = 0;
        bgw_ptr->fam_no = 2;
        bgw_ptr->xy[1].disp.pos = bgw_ptr->pos_y_work = 0;
        bgw_ptr->speed_x = 0xC000;
        bgw_ptr->speed_y = 0xC000;
        bgw_ptr->y_limit = bgw_ptr->y_limit2 = 0xF0;
        sync_fam_set3(2);
        break;
    case SYNC_MOVE:
        bg_x_move_check();
        bg_y_move_check();
        sync_fam_set3(2);
        break;
    }
}
