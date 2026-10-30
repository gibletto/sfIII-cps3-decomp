/*
 * EFFA6.C  Effect A6: BG 0 scroll to the battle country
 *
 * effect_A6_init (from sel_pl.c) takes the target from effA6_x_tbl by Battle_Country (effA6_x_tbl_wide
 * when Game_setting.Screen_Mode is set) and the direction (effA6_set_target). A frame later effect_A6_move
 * scrolls BG 0 toward it, accelerating up to 8 dots a frame (faster with the cut button,
 * Cut_Cut_Sub), stops on the target and sets Next_Step. It waits while Break_Into is set.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "EFFECT.h"
#include "effect_2.h"

/* routine_no[0] */
#define R0_WAIT         0       /* wait a frame */
#define R0_SCROLL       1       /* scroll BG 0 to the target */

void effA6_set_target(WORK_Other* ewk);

extern const s16 effA6_x_tbl[];   /* provisional name: 3 per country */
extern const SCROLL_TARGET effA6_x_tbl_wide[];   /* provisional name: 3 per country */



void effect_A6_move(WORK_Other* ewk) {
    u16 sp;
    u16 acc;
    sp = Cut_Cut_Sub(3);
    acc = Cut_Cut_Sub(5);
    if (Break_Into) {
        return;
    }
    switch (ewk->wu.routine_no[0]) {
    case R0_WAIT:
        if (--ewk->wu.dir_timer == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case R0_SCROLL:
        bg_w.bgw[0].xy[0].cal += ewk->wu.mvxy.a[0].sp * sp;
        ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp * acc;
        if (ewk->wu.mvxy.a[0].sp > 0) {
            if (ewk->wu.hit_quake < bg_w.bgw[0].xy[0].disp.pos) {
                ewk->wu.routine_no[0]++;
                bg_w.bgw[0].xy[0].disp.pos = ewk->wu.hit_quake;
                Next_Step = 1;
                break;
            }
            if (ewk->wu.mvxy.a[0].sp > 0x80000) {
                ewk->wu.mvxy.a[0].sp = 0x80000;
            }
        } else {
            if (ewk->wu.hit_quake > bg_w.bgw[0].xy[0].disp.pos) {
                ewk->wu.routine_no[0]++;
                bg_w.bgw[0].xy[0].disp.pos = ewk->wu.hit_quake;
                Next_Step = 1;
                break;
            }
            if (ewk->wu.mvxy.a[0].sp < -0x80000) {
                ewk->wu.mvxy.a[0].sp = -0x80000;
            }
        }
        break;
    }
}



s32 effect_A6_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 106;
    ewk->wu.dir_timer = 1;
    effA6_set_target(ewk);
    return 0;
}



/* provisional name */
void effA6_set_target(WORK_Other* ewk) {
    ewk->wu.hit_quake = effA6_x_tbl[Battle_Country * 3 + 2];
    if (Game_setting.Screen_Mode) {
        ewk->wu.hit_quake = effA6_x_tbl_wide[Battle_Country * 3].x;
    } else {
        ewk->wu.hit_quake = effA6_x_tbl[Battle_Country * 3 + 2];
    }
    if (ewk->wu.hit_quake < bg_w.bgw[0].xy[0].disp.pos) {
        ewk->wu.mvxy.a[0].sp = -0x40000;
        ewk->wu.mvxy.d[0].sp = -0x3800;
    } else {
        ewk->wu.mvxy.a[0].sp = 0x40000;
        ewk->wu.mvxy.d[0].sp = 0x3800;
    }
}
