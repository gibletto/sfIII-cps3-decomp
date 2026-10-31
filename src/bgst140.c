/*
 * BGST140.C  Stage background (ta0_move slot 14)
 *
 * BG140 runs the stage's three layers: layer 1 (the chasing base layer), layer 0 (the line-scroll layer with the
 * stage graphics, effects and palette) and layer 2 (a synced layer), then the zoom check, position correction and
 * Bg_Family_Set_2. In the first area all three start raised (speed_y * 176) and come down together
 * (bg140_demo). Once C_No0 reaches 8, with Round_num below twice Game_setting.Battle_Number or the winner's PL_Wins below
 * set4 + 1, layer 1 drops away: bg_land_flag is set, Sound_SE(118), the screen quakes and zooms out while
 * bg_etc_flag counts down, then the layer falls out of sight (bg140_fall0..4).
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
#include "Com_Pl.h"
#include "color3rd.h"
#include "se_3.h"
#include "eff05.h"
#include "eff06.h"
#include "eff14.h"
#include "EFF53.h"
#include "eff56.h"
#include "EFFC2.h"
#include "EFF45.h"
#include "fighter.h"

/* bgw r_no_0 of a layer with an entrance demo: its bg*_jmp routine */
#define R0_INIT         0       /* set up the layer */
#define R0_DEMO         1       /* the entrance demo */
#define R0_MOVE         2       /* follow the fight */

/* declarations the headers do not give */
void suzi_line_fix_set(void);
s32 effect_C3_init();
void load_any_color();
extern s16 bg080_quake_sw;

void bg140_layer0(void);
void bg140_layer0_init(void);
void bg140_layer1(void);
void bg140_layer1_init(void);
void bg140_layer1_move(void);
void bg140_layer1_fall(void);
void bg140_quake(void);
void bg140_fall0(void);
void bg140_fall1(void);
void bg140_fall2(void);
void bg140_fall3(void);
void bg140_fall4(void);
void bg140_layer2(void);
void bg140_demo(void);
static void bg_move_common(void);
#pragma inline(bg140_layer1, bg140_quake)


void BG140(void) {
    bgw_ptr = &bg_w.bgw[1];
    bg140_layer1();
    bgw_ptr = &bg_w.bgw[0];
    bg140_layer0();
    bgw_ptr = &bg_w.bgw[2];
    bg140_layer2();
    zoom_ud_check();
    bg_pos_hosei2();
    Bg_Family_Set_2();
}



/* provisional name */
void bg140_layer0(void) {
    void (*bg1400_jmp[3])() = { bg140_layer0_init, bg140_demo, bg_move_common };
    bg1400_jmp[bgw_ptr->r_no_0]();
    suzi_line_fix_set();
}



/* provisional name */
void bg140_layer0_init(void) {
    bgw_ptr->r_no_0++;
    if (bg_w.area == 0) {
        bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 176;
        bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
    } else {
        bgw_ptr->r_no_0++;
    }
    bgw_ptr->r_no_1 = 0;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 16;
    bgw_ptr->suzi_c_no = simmram_small_page_alloc_40(1);
    bgw_ptr->suzi_adrs = (u16*)simmram_slot_addr(bgw_ptr->suzi_c_no);
    scrn_linescroll_set_now(0, bgw_ptr->suzi_adrs);
    memset(bgw_ptr->suzi_adrs, 0, 0x1000);
    Bg_On_R(16);
    suzi_line_clear(0);
    bgw_ptr->no_suzi_line = 0x200;
    bgw_ptr->u_line = 0x200;
    bgw_ptr->d_line = 96;
    bgw_ptr->start_suzi = bgw_ptr->suzi_adrs + 0x400;
    load_char_gfx(0x4F60, 1);
    load_any_color(98);
    effect_45_init(0);
    effect_53_init();
    effect_56_init();
    effect_C2_init();
    effect_C3_init(0);
    effect_05_init();
    effect_06_init();
}



static void bg_move_common(void) {
    bg_x_move_check();
    bg_y_move_check();
}



/* provisional name */
void bg140_layer1(void) {
    void (*bg1401_jmp[4])() = { bg140_layer1_init, bg140_demo, bg140_layer1_move, bg140_layer1_fall };
    bg1401_jmp[bgw_ptr->r_no_0]();
}



/* provisional name */
void bg140_layer1_init(void) {
    bgw_ptr->r_no_0++;
    if (bg_w.area == 0) {
        bg_app = 1;
        bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 176;
        bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
    } else {
        bgw_ptr->r_no_0++;
    }
    bg_land_flag = 0;
    bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
    bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
    bgw_ptr->zuubun = 0;
}



/* provisional name */
void bg140_layer1_move(void) {
    if (C_No0 >= C0_NEXT) {
        if (Round_num < Game_setting.Battle_Number * 2 || PL_Wins[Winner_id] < Game_setting.Battle_Number + 1) {
            bg_land_flag = 1;
            bgw_ptr->r_no_0++;
            bg_etc_flag = 0x7000;
            bg080_quake_sw = 0;
            Sound_SE(118);
        }
    }
    bg_base_x_move_check();
    bg_base_y_move_check();
    bg_chase_move();
}



/* provisional name */
void bg140_layer1_fall(void) {
    void (*bg1401_fall_jmp[5])() = { bg140_fall0, bg140_fall1, bg140_fall2, bg140_fall3, bg140_fall4 };
    bg1401_fall_jmp[bgw_ptr->r_no_1]();
}



/* provisional name */
void bg140_quake(void) {
    bg080_quake_sw ^= 1;
    if (bg080_quake_sw) {
        bg_w.quake_y_index = 17;
    } else {
        bg_w.quake_y_index = 18;
    }
}



/* provisional name */
void bg140_fall0(void) {
    bg_etc_flag--;
    if (bg_etc_flag < 0) {
        bg_etc_flag = 56;
        bgw_ptr->r_no_1++;
    } else {
        bg140_quake();
        if (bgw_ptr->xy[0].disp.pos > bgw_ptr->pos_x_work - 56 && bgw_ptr->xy[0].disp.pos < bgw_ptr->pos_x_work + 56) {
            if (Game_setting.Screen_Mode == 0) {
                bg_w.bg_f_x++;
                bg_w.bg_f_y++;
                if (bg_w.bg_f_x < 84) {
                    Frame_Down(192, 224, 1, 1);
                }
            }
        }
    }
}



/* provisional name */
void bg140_fall1(void) {
    bg_etc_flag--;
    if (bg_etc_flag > 0) {
        bgw_ptr->xy[1].cal -= 0xB000;
        bgw_ptr->wxy[1].cal -= 0xB000;
    } else {
        bgw_ptr->r_no_1++;
    }
}



/* provisional name */
void bg140_fall2(void) {
    if (bgw_ptr->wxy[1].cal > -0x1100000) {
        bgw_ptr->xy[1].cal -= 0xB0000;
        bgw_ptr->wxy[1].cal -= 0xB0000;
    } else {
        bgw_ptr->r_no_1++;
        bg_etc_flag = 60;
    }
}



/* provisional name */
void bg140_fall3(void) {
    bg_etc_flag--;
    if (bg_etc_flag < 0) {
        bgw_ptr->r_no_1++;
    }
}



/* provisional name */
void bg140_fall4(void) {
    suzi_line_fix_set();
}



/* provisional name */
void bg140_layer2(void) {
    switch (bgw_ptr->r_no_0) {
    case R0_INIT:
        bgw_ptr->r_no_0++;
        bgw_ptr->old_pos_x = bgw_ptr->xy[0].disp.pos = bgw_ptr->pos_x_work = 0x200;
        bgw_ptr->hos_xy[0].cal = bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal;
        bgw_ptr->zuubun = 0;
        bgw_ptr->fam_no = 2;
        bgw_ptr->xy[1].disp.pos = bgw_ptr->pos_y_work = 0;
        bgw_ptr->y_limit = bgw_ptr->y_limit2 = 96;
        bgw_ptr->speed_x = 0xC000;
        bgw_ptr->speed_y = 0xC000;
        if (bg_w.area == 0) {
            bgw_ptr->xy[1].cal = bgw_ptr->speed_y * 176;
            bgw_ptr->hos_xy[1].disp.pos = bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
        } else {
            bgw_ptr->r_no_0++;
        }
        sync_fam_set3(2);
        break;
    case R0_DEMO:
        bg140_demo();
        sync_fam_set3(2);
        break;
    case R0_MOVE:
        bg_x_move_check();
        bg_y_move_check();
        sync_fam_set3(2);
        break;
    }
}



/* provisional name */
void bg140_demo(void) {
    if (plw[0].player_number == PL_ELENA && plw[1].player_number == PL_ELENA) {
        bgw_ptr->xy[1].cal -= bgw_ptr->speed_y * 4;
    } else if (Cut_Cut_Cut()) {
        bgw_ptr->xy[1].cal -= bgw_ptr->speed_y * 4;
    } else {
        bgw_ptr->xy[1].cal -= bgw_ptr->speed_y * 2;
    }
    if (bgw_ptr->xy[1].cal < bgw_ptr->pos_y_work) {
        bgw_ptr->xy[1].cal = bgw_ptr->pos_y_work;
        bgw_ptr->r_no_0++;
        bg_app = 0;
    }
}
