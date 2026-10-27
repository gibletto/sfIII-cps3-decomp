/*
 * BGST050.C  Stage background (ta0_move slots 5 and 6)
 *
 * BG050 runs the stage's three layers (1, 0, and 2 in the first area only). Unless bg050_appear_check says
 * the stage starts in place (a later area, or neither player is character 3, or both are), each layer first
 * drops in from above (bg050_demo: wait, slide down, then wait for Appear_end) before it scrolls normally.
 * Layer 1's init loads the area's palette, graphics and effects.
 */
#include "structs.h"
#include "EFFC1.h"
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
#include "EFF23.h"

/* bgw r_no_0 of a layer with an entrance demo: its bg*_jmp routine */
#define R0_INIT         0       /* set up the layer */
#define R0_DEMO         1       /* the entrance demo */
#define R0_MOVE         2       /* follow the fight */

void load_any_color();
s32 effect_18_init();
s32 effect_25_init();
s32 effect_29_init();
s32 effect_60_init();
s32 effect_87_init();
void bg050_layer0(void);
void bg050_layer1(void);
void bg050_layer2(void);
void bg050_layer0_init(void);
void bg050_layer1_init(void);
void bg050_layer2_init(void);
void bg050_layer2_move(void);
void bg050_demo(void);
s32 bg050_appear_check(void);
static void bg_move_common(void);
static void bg_base_move_common(void);
#pragma inline(bg050_layer0, bg050_layer1)


void BG050(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg050_layer1();
    bgw_ptr = &bg_w.bgw[0];
    bg050_layer0();
    bgw_ptr = &bg_w.bgw[2];
    bg050_layer2();
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set();
}



/* provisional name */
void bg050_layer0(void) {
    void (*bg0500_jmp[3])() = { bg050_layer0_init, bg050_demo, bg_move_common };
    bg0500_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg050_layer0_init(void) {
    bgw_ptr->r_no_1 = 0;
    bgw_ptr->zuubun = 0;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->hos_xy[0].disp.pos = bgw_ptr->wxy[0].disp.pos - bg_w.pos_offset;
    bgw_ptr->hos_xy[0].disp.low = 0;
    if (bg050_appear_check()) {
        bgw_ptr->r_no_0 = R0_MOVE;
    } else {
        bgw_ptr->r_no_0++;
        if (bg_w.area == 0) {
            bgw_ptr->free = 52;
            bgw_ptr->xy[1].cal = bgw_ptr->wxy[1].cal = 0xC40000;
        }
    }
}



static void bg_move_common(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
void bg050_layer1(void) {
    void (*bg0501_jmp[3])() = { bg050_layer1_init, bg050_demo, bg_base_move_common };
    bg0501_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
/* also the area's palette, graphics and effects */
void bg050_layer1_init(void) {
    bgw_ptr->r_no_1 = 0;
    bgw_ptr->zuubun = 0;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->hos_xy[0].disp.pos = bgw_ptr->wxy[0].disp.pos - bg_w.pos_offset;
    bgw_ptr->hos_xy[0].disp.low = 0;
    if (bg050_appear_check()) {
        bgw_ptr->r_no_0 = R0_MOVE;
    } else {
        bgw_ptr->r_no_0++;
        if (bg_w.area == 0) {
            bgw_ptr->free = 52;
            bgw_ptr->xy[1].cal = bgw_ptr->wxy[1].cal = 0xC40000;
        }
    }
    effect_05_init();
    effect_06_init();
    if (bg_w.area) {
        effect_25_init(0);
        effect_25_init(1);
        effect_25_init(2);
        effect_29_init();
        effect_60_init(0);
        load_any_color(107);
        load_char_gfx(0x47C0, 1);
        load_char_gfx(0x4960, 1);
        load_char_gfx(0x4AD0, 1);
    } else {
        effect_18_init(2);
        effect_87_init(2);
        effect_23_init();
        effect_C1_entry();
        load_any_color(106);
        load_char_gfx(0x4540, 1);
    }
}



static void bg_base_move_common(void) {
    bg_base_x_move_check();
    bg_base_y_move_check();
    bg_chase_move();
}



/* provisional name */
/* layer 2 runs in the first area only */
void bg050_layer2(void) {
    void (*bg0502_jmp[3])() = { bg050_layer2_init, bg050_demo, bg050_layer2_move };
    if (bg_w.area) {
        return;
    }
    bg0502_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg050_layer2_init(void) {
    bgw_ptr->r_no_1 = 0;
    bgw_ptr->zuubun = 0;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->hos_xy[0].disp.pos = bgw_ptr->wxy[0].disp.pos - bg_w.pos_offset;
    bgw_ptr->hos_xy[0].disp.low = 0;
    if (bg050_appear_check()) {
        bgw_ptr->r_no_0 = R0_MOVE;
    } else {
        bgw_ptr->r_no_0++;
        if (bg_w.area == 0) {
            bgw_ptr->free = 52;
            bgw_ptr->xy[1].cal = bgw_ptr->wxy[1].cal = 0xC40000;
        }
    }
}



/* provisional name */
void bg050_layer2_move(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
/* the drop-in: free counts down, then the layer slides down to 0, then waits for Appear_end == 2 */
void bg050_demo(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->free--;
        if (bgw_ptr->free < 0) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 1:
        bgw_ptr->xy[1].cal -= 0xA8000;
        bgw_ptr->wxy[1].cal -= 0xA8000;
        if (bgw_ptr->xy[1].disp.pos <= 0) {
            bgw_ptr->r_no_1++;
            bgw_ptr->xy[1].cal = 0;
            bgw_ptr->wxy[1].cal = 0;
        }
        break;
    case 2:
        if (Appear_end != 2) {
            break;
        }
        bgw_ptr->r_no_0++;
        bgw_ptr->r_no_1 = 0;
        break;
    }
}



/* provisional name */
/* 1 = start in place: a later area, or neither player is character 3 */
s32 bg050_appear_check(void) {
    s16 p1;
    s16 p2;
    p1 = plw[0].player_number;
    p2 = plw[1].player_number;
    if (bg_w.area > 1) {
        return 1;
    }
    if (bg_w.area == 0) {
        if (p1 == 3 && p2 == 3) {
            return 0;
        }
        if (p1 != 3 && p2 != 3) {
            return 1;
        }
        return 0;
    }
    return 1;
}
