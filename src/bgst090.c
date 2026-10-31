/*
 * BGST090.C  Stage background (ta0_move slot 9)
 *
 * BG090 runs the stage's three layers: layer 1 (bg0902, the chasing base layer), layer 0 (bg0901: the stage
 * graphics and effects; bg090_check picks the start position and bg090_demo scrolls it to 0x200) and layer 2
 * (bg0903, scrolled left with layer 1's movement, plus the stage's sound effect).
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
#include "EFF11.h"
#include "sys_config.h"
#include "sys_test.h"
#include "meta_col_mem.h"
#include "color3rd.h"
#include "eff06.h"
#include "SE.h"
#include "EFF07.h"
#include "fighter.h"

/* declarations the headers do not give */
void load_any_color();
void Bg_Family_Set_3(void);
s32 effect_18_init();
void bg0901(void);
void bg0902(void);
void bg0903(void);
void bg0901_init01(void);
void bg0902_init01(void);
void bg0903_init01(void);
void bg0903_move(void);
void bg090_init00(void);
s32 bg090_check(void);
void bg090_demo(void);
static void bg_move_common(void);
static void bg_base_move_common(void);
#pragma inline(bg0901, bg0902, bg0903)


void BG090(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg0902();
    bgw_ptr = &bg_w.bgw[0];
    bg0901();
    bgw_ptr = &bg_w.bgw[2];
    bg0903();
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set_3();
}



void bg0901(void) {
    void (*bg0901_jmp[4])() = { bg090_init00, bg0901_init01, bg090_demo, bg_move_common };
    bg0901_jmp[bgw_ptr->r_no_0]();
}



void bg0901_init01(void) {
    bgw_ptr->r_no_0++;
    if (bg_w.area == 0) {
        bg_app = 1;
        if (bg090_check()) {
            bg_w.dmm0[0] = 1;
            bgw_ptr->xy[0].disp.pos = 250;
            bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
        } else {
            bg_w.dmm0[0] = 0;
            bgw_ptr->xy[0].disp.pos = 776;
            bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
        }
    } else {
        bgw_ptr->r_no_0++;
    }
    bgw_ptr->zuubun = 0;
    effect_05_init();
    effect_06_init();
    effect_07_init();
    effect_18_init(5);
    load_char_gfx(0x4DE0, 1);
    load_any_color(97);
}



/* Each stage file has its own copy. */
static void bg_move_common(void) {
    bg_x_move_check();
    bg_y_move_check();
}



void bg0902(void) {
    void (*bg0902_jmp[4])() = { bg090_init00, bg0902_init01, bg090_demo, bg_base_move_common };
    bg0902_jmp[bgw_ptr->r_no_0]();
}



void bg0902_init01(void) {
    bgw_ptr->r_no_0++;
    if (bg_w.area == 0) {
        if (bg090_check()) {
            bgw_ptr->xy[0].disp.pos = 250;
            bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
        } else {
            bgw_ptr->xy[0].disp.pos = 776;
            bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
        }
    } else {
        bgw_ptr->r_no_0++;
    }
    bgw_ptr->zuubun = 0;
}



/* Move the base layer and chase the players; each stage file has its own copy. */
static void bg_base_move_common(void) {
    bg_base_x_move_check();
    bg_base_y_move_check();
    bg_chase_move();
}



void bg0903(void) {
    void (*bg0903_jmp[3])() = { bg090_init00, bg0903_init01, bg0903_move };
    bg0903_jmp[bgw_ptr->r_no_0]();
}



void bg0903_init01(void) {
    bgw_ptr->r_no_0++;
    Sound_SE(110);
}



void bg0903_move(void) {
    s16 d;
    if (EXE_flag == 0 && Game_pause == 0) {
        d = bg_w.bgw[1].wxy[0].disp.pos - bg_w.bgw[1].old_pos_x;
        if (d < 0) {
            bgw_ptr->xy[0].disp.pos += d;
            bgw_ptr->wxy[0].disp.pos += d;
        }
        bgw_ptr->xy[0].disp.pos -= 5;
        bgw_ptr->wxy[0].disp.pos -= 5;
    }
    bg_y_move_check();
}



void bg090_init00(void) {
    bgw_ptr->r_no_0++;
    bgw_ptr->xy[0].disp.pos = bgw_ptr->old_pos_x = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
}



s32 bg090_check(void) {
    if (plw[0].player_number == PL_NECRO && plw[1].player_number == PL_NECRO) {
        if (Appear_hv[0]) {
            return 0;
        }
        return 1;
    }
    if (plw[0].player_number != PL_NECRO && plw[1].player_number == PL_NECRO) {
        return 0;
    }
    return 1;
}



void bg090_demo(void) {
    s32 (*fp)(void);
    if (bg_w.dmm0[0]) {
        if ((fp = Cut_Cut_Cut)()) {
            bgw_ptr->wxy[0].cal += bgw_ptr->speed_x * 4;
        } else {
            bgw_ptr->wxy[0].cal += bgw_ptr->speed_x * 4;
        }
        if (bgw_ptr->wxy[0].disp.pos > 0x200) {
            bgw_ptr->xy[0].cal = bgw_ptr->wxy[0].cal = 0x2000000;
            bgw_ptr->r_no_0++;
            bg_app = 0;
        }
    } else {
        if (Cut_Cut_Cut()) {
            bgw_ptr->wxy[0].cal -= bgw_ptr->speed_x * 4;
        } else {
            bgw_ptr->wxy[0].cal -= bgw_ptr->speed_x * 4;
        }
        if (bgw_ptr->wxy[0].disp.pos < 0x200) {
            bgw_ptr->xy[0].cal = bgw_ptr->wxy[0].cal = 0x2000000;
            bgw_ptr->r_no_0++;
            bg_app = 0;
        }
    }
}
