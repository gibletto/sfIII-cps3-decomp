/*
 * BGST170.C  Stage background: ta0_move slots 17 and 18, bgst050's stage with character 10
 *
 * BG170 runs the stage's three layers (1, 0, and 2 in the later areas only). Unless bg170_appear_check says
 * the stage starts in place (a later area, or neither player is character 10, or both are), each layer first
 * drops in from above (bg170_demo: wait, slide down, then wait for Appear_end) before it scrolls normally.
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

/* bgw r_no_1 in bg170_demo */
#define DEMO_WAIT       0       /* until free runs out */
#define DEMO_SCROLL     1       /* scroll the Y down to 0 */
#define DEMO_APPEAR     2       /* until Appear_end is 2, then the next r_no_0 */

void load_any_color();
s32 effect_18_init();
#include "EFF25.h"
#include "EFF29.h"
#include "EFF60.h"
#include "eff87.h"
#include "fighter.h"
void bg170_layer0(void);
void bg170_layer1(void);
void bg170_layer2(void);
void bg170_layer0_init(void);
void bg170_layer1_init(void);
void bg170_layer2_init(void);
void bg170_layer2_move(void);
void bg170_demo(void);
s32 bg170_appear_check(void);
static void bg_move_common(void);
static void bg_base_move_common(void);
#pragma inline(bg170_layer0, bg170_layer1)


void BG170(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg170_layer1();
    bgw_ptr = &bg_w.bgw[0];
    bg170_layer0();
    bgw_ptr = &bg_w.bgw[2];
    bg170_layer2();
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set();
}



/* provisional name */
void bg170_layer0(void) {
    void (*bg1700_jmp[3])() = { bg170_layer0_init, bg170_demo, bg_move_common };
    bg1700_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg170_layer0_init(void) {
    bgw_ptr->r_no_1 = 0;
    bgw_ptr->zuubun = 0;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->hos_xy[0].disp.pos = bgw_ptr->wxy[0].disp.pos - bg_w.pos_offset;
    bgw_ptr->hos_xy[0].disp.low = 0;
    if (bg170_appear_check()) {
        bgw_ptr->r_no_0 = R0_MOVE;
    } else {
        bgw_ptr->r_no_0++;
        if (bg_w.area == 0) {
            bgw_ptr->free = 74;
            bgw_ptr->xy[1].cal = bgw_ptr->wxy[1].cal = 0x960000;
        }
    }
}



/* Each stage file has its own copy. */
static void bg_move_common(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
void bg170_layer1(void) {
    void (*bg1701_jmp[3])() = { bg170_layer1_init, bg170_demo, bg_base_move_common };
    bg1701_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
/* Also loads the area's palette, graphics and effects. */
void bg170_layer1_init(void) {
    bgw_ptr->r_no_1 = 0;
    bgw_ptr->zuubun = 0;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->hos_xy[0].disp.pos = bgw_ptr->wxy[0].disp.pos - bg_w.pos_offset;
    bgw_ptr->hos_xy[0].disp.low = 0;
    if (bg170_appear_check()) {
        bgw_ptr->r_no_0 = R0_MOVE;
    } else {
        bgw_ptr->r_no_0++;
        if (bg_w.area == 0) {
            bgw_ptr->free = 74;
            bgw_ptr->xy[1].cal = bgw_ptr->wxy[1].cal = 0x960000;
        }
    }
    effect_05_init();
    effect_06_init();
    if (bg_w.area) {
        effect_18_init(2);
        effect_87_init(2);
        effect_23_init();
        effect_C1_entry();
        load_any_color(106);
        load_char_gfx(0x4540, 1);
    } else {
        effect_25_init(0);
        effect_25_init(1);
        effect_25_init(2);
        effect_29_init();
        effect_60_init(0);
        load_any_color(107);
        load_char_gfx(0x47C0, 1);
        load_char_gfx(0x4960, 1);
        load_char_gfx(0x4AD0, 1);
    }
}



/* Move the base layer and chase the players; each stage file has its own copy. */
static void bg_base_move_common(void) {
    bg_base_x_move_check();
    bg_base_y_move_check();
    bg_chase_move();
}



/* provisional name */
/* Layer 2 runs in the later areas only. */
void bg170_layer2(void) {
    void (*bg1702_jmp[3])() = { bg170_layer2_init, bg170_demo, bg170_layer2_move };
    if (bg_w.area == 0) {
        return;
    }
    bg1702_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg170_layer2_init(void) {
    bgw_ptr->r_no_1 = 0;
    bgw_ptr->zuubun = 0;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->hos_xy[0].disp.pos = bgw_ptr->wxy[0].disp.pos - bg_w.pos_offset;
    bgw_ptr->hos_xy[0].disp.low = 0;
    if (bg170_appear_check()) {
        bgw_ptr->r_no_0 = R0_MOVE;
    } else {
        bgw_ptr->r_no_0++;
        if (bg_w.area == 0) {
            bgw_ptr->free = 74;
            bgw_ptr->xy[1].cal = bgw_ptr->wxy[1].cal = 0x960000;
        }
    }
}



/* provisional name */
void bg170_layer2_move(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
/* The drop-in: free counts down, then the layer slides down to 0, then waits for Appear_end == 2. */
void bg170_demo(void) {
    switch (bgw_ptr->r_no_1) {
    case DEMO_WAIT:
        bgw_ptr->free--;
        if (bgw_ptr->free < 0) {
            bgw_ptr->r_no_1++;
        }
        break;
    case DEMO_SCROLL:
        bgw_ptr->xy[1].cal -= 0xA8000;
        bgw_ptr->wxy[1].cal -= 0xA8000;
        if (bgw_ptr->xy[1].disp.pos <= 0) {
            bgw_ptr->r_no_1++;
            bgw_ptr->xy[1].cal = 0;
            bgw_ptr->wxy[1].cal = 0;
        }
        break;
    case DEMO_APPEAR:
        if (Appear_end != 2) {
            break;
        }
        bgw_ptr->r_no_0++;
        bgw_ptr->r_no_1 = 0;
        break;
    }
}



/* provisional name */
/* Returns 1 to start in place (a later area, or neither player is Yang), else 0. */
s32 bg170_appear_check(void) {
    s16 p1;
    s16 p2;
    p1 = plw[0].player_number;
    p2 = plw[1].player_number;
    if (bg_w.area == 0) {
        if (p1 == PL_YANG && p2 == PL_YANG) {
            return 0;
        }
        if (p1 != PL_YANG && p2 != PL_YANG) {
            return 1;
        }
        return 0;
    }
    return 1;
}
