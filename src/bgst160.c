/*
 * BGST160.C  Stage background (ta0_move slot 16)
 *
 * BG160 runs three layers: layer 1 (bg1602, the chasing base layer), layer 0 (bg1601)
 * and layer 2 (bg1603), then checks zoom, corrects positions and sets the family.
 * The base layer loads the graphics, palette and scenery effects. The entrance demo
 * uses bg160_demo_check and demo90_base; jijii_win_bg and jijii_win_bg2 scroll the
 * layers during Oro's special win scene.
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
#include "fighter.h"
#include "eff06.h"
#include "EFF71.h"
#include "EFF72.h"
#include "EFF74.h"
#include "eff56.h"

/* bgw r_no_0 of a layer with an entrance demo: its bg*_jmp routine */
#define R0_INIT         0       /* set up the layer */
#define R0_DEMO         1       /* the entrance demo */
#define R0_MOVE         2       /* follow the fight */

/* declarations the headers do not give */
void load_any_color();
s32 effect_18_init();

void bg1601(void);
void bg1601_init00(void);
void bg1602(void);
void bg1602_init00(void);
void bg1603(void);
void bg1603_init00(void);
void bg1603_move(void);
void bg160_demo_check(void);
void demo90_base(void);
void jijii_win_bg(void);
void jijii_win_bg2(void);
static void bg_move_common(void);
static void bg_base_move_common(void);


/* Update the three scroll layers. */
void BG160(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg1602();
    bgw_ptr = &bg_w.bgw[0];
    bg1601();
    bgw_ptr = &bg_w.bgw[2];
    bg1603();
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set();
}



/* Layer 0: initialise, enter, then scroll. */
void bg1601(void) {
    void (*bg1601_jmp[3])() = { bg1601_init00, demo90_base, bg_move_common };
    if (win_sp_flag) {
        jijii_win_bg2();
    } else {
        bg1601_jmp[bgw_ptr->r_no_0]();
    }
}



/* Set the entrance state and horizontal position. */
void bg1601_init00(void) {
    bg160_demo_check();
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
}



/* Move the foreground layer. */
static void bg_move_common(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* Layer 1: initialise, enter, then chase the players. */
void bg1602(void) {
    void (*bg1602_jmp[3])() = { bg1602_init00, demo90_base, bg_base_move_common };
    if (win_sp_flag) {
        jijii_win_bg();
    } else {
        bg1602_jmp[bgw_ptr->r_no_0]();
    }
}



/* Load the stage graphics, palette and effects. */
void bg1602_init00(void) {
    bg160_demo_check();
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
    effect_05_init();
    effect_06_init();
    effect_18_init(4);
    effect_94_entry(1);
    effect_55_init();
    effect_71_init();
    effect_72_init();
    effect_74_init();
    load_any_color(108);
    load_char_gfx(0x53C0, 1);
}



/* Move the base layer and chase the players. */
static void bg_base_move_common(void) {
    bg_base_x_move_check();
    bg_base_y_move_check();
    bg_chase_move();
}



/* provisional name */
void bg1603(void) {
    void (*bg1603_jmp[3])() = { bg1603_init00, demo90_base, bg1603_move };
    if (win_sp_flag) {
        jijii_win_bg2();
    } else {
        bg1603_jmp[bgw_ptr->r_no_0]();
    }
}



/* provisional name */
void bg1603_init00(void) {
    bg160_demo_check();
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
}



/* provisional name */
void bg1603_move(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* Start the entrance drop when Oro is present in the first area. */
void bg160_demo_check(void) {
    if ((plw->player_number != PL_ORO) && (plw[1].player_number != PL_ORO)) {
        bgw_ptr->r_no_0 = R0_MOVE;
    } else if (bg_w.area != 0) {
        bgw_ptr->r_no_0 = R0_MOVE;
    } else {
        bgw_ptr->r_no_0 = R0_DEMO;
        bgw_ptr->xy[1].cal = bgw_ptr->wxy[1].cal = bgw_ptr->speed_y * 200;
    }
}



void demo90_base(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        if (Appear_free) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 1:
        bgw_ptr->xy[1].cal -= bgw_ptr->speed_y * 0xA;
        bgw_ptr->wxy[1].cal -= bgw_ptr->speed_y * 0xA;
        if (bgw_ptr->xy[1].disp.pos <= 0) {
            bgw_ptr->r_no_1++;
            bgw_ptr->xy[1].cal = 0;
            bgw_ptr->wxy[1].cal = 0;
            break;
        }
        break;
    case 2:
        if (Appear_end != 2) {
            break;
        }
        bgw_ptr->r_no_0++;
        bgw_ptr->r_no_1 = 0;
        bgw_ptr->xy[1].cal = 0;
        bgw_ptr->wxy[1].cal = 0;
    }
}



/* Raise the base layer until its height passes 0xC0. */
void jijii_win_bg(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        if (win_sp_flag == 2) {
            bgw_ptr->xy[1].cal += 0xA0000;
            bgw_ptr->wxy[1].cal += 0xA0000;
            if (bgw_ptr->xy[1].disp.pos > 0xC0) {
                bgw_ptr->r_no_1 += 1;
                win_sp_flag = 3;
            }
        }
    case 1:
        break;
    }
}



void jijii_win_bg2(void) {
    s16 zuu_work;
    s32 sp_work;
    switch (bg_w.bgw[1].r_no_1) {
    case 0:
        if (win_sp_flag == 2) {
            zuu_work = 0xA;
            sp_work = bgw_ptr->speed_y * zuu_work;
            bgw_ptr->xy[1].cal += sp_work;
            bgw_ptr->wxy[1].cal += sp_work;
        }
    case 1:
        break;
    }
}
