/*
 * EFF93.C  Effect 93: face-select BG slide
 *
 * effect_93 (from sel_pl): moves BG1 on the face-select screen, hiding and re-enabling the cursor.
 * Eff93_SLIDE_UP raises it after a delay; Eff93_SLIDE_DOWN slides it sideways with an
 * accelerating speed, to the left when Last_Arts_PL is 1, else to DE_X[5] + 0x300.
 * Bg_Family_Set_Ex sets up a BG family for sel_pl and Win.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sc_trans.h"
#include "fifo.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "Eff93.h"
#include "cps3.h"

/* routine_no[1], Eff93_SLIDE_UP */
#define R1_WAIT         0       /* count the delay down */
#define R1_RAISE        1       /* (default) raise BG1 12 dots a frame */

/* routine_no[1], Eff93_SLIDE_DOWN */
#define R1_START        0       /* pick the direction and speed */
#define R1_SLIDE        1       /* (default) slide BG1 sideways */



/* 0617A08C */
const Eff93_Jmp_Tbl_t Eff93_Jmp_Tbl[2] = {
    Eff93_SLIDE_UP,
    Eff93_SLIDE_DOWN,
};



void effect_93_move(WORK_Other* ewk) {
    Eff93_Jmp_Tbl[ewk->wu.routine_no[0]](ewk);
}



/* provisional name */
void Eff93_SLIDE_UP(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_WAIT:
        if (--ewk->wu.dir_timer == 0) {
            ewk->wu.routine_no[1]++;
            Face_Status = 1;
        }
        break;
    default:
        if ((bg_w.bgw[1].xy[1].disp.pos -= 12) <= 64) {
            bg_w.bgw[1].xy[1].disp.pos = 68;
            Appear_Cursor = 1;
            Face_Move = 0;
            push_effect_work(&ewk->wu);
        }
        Bg_Family_Set_Ex(1);
        break;
    }
}



/* provisional name */
void Eff93_SLIDE_DOWN(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_START:
        ewk->wu.routine_no[1]++;
        if (Last_Arts_PL == 1) {
            ewk->wu.dir_step = -0x100;
            ewk->wu.mvxy.a[0].sp = -0xA0000;
            ewk->wu.mvxy.d[0].sp = -0x8000;
        } else {
            ewk->wu.dir_step = DE_X[5] + 0x300;
            ewk->wu.mvxy.a[0].sp = 0xA0000;
            ewk->wu.mvxy.d[0].sp = 0x8000;
        }
        break;
    default:
        bg_w.bgw[1].xy[0].cal += ewk->wu.mvxy.a[0].sp;
        ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp;
        if (ewk->wu.mvxy.a[0].sp < 0) {
            if (ewk->wu.dir_step >= bg_w.bgw[1].xy[0].disp.pos) {
                push_effect_work(&ewk->wu);
            }
        } else if (ewk->wu.dir_step <= bg_w.bgw[1].xy[0].disp.pos) {
            push_effect_work(&ewk->wu);
        }
        Bg_Family_Set_Ex(1);
        break;
    }
}



void Bg_Family_Set_Ex(s16 xx) {
    s16 pos_work_x;
    s16 pos_work_y;
    bg_w.bgw[xx].position_x = bg_w.bgw[xx].xy[0].disp.pos & 0x3FF;
    pos_work_x = bg_w.bgw[xx].position_x;
    bg_w.bgw[xx].position_y = bg_w.bgw[xx].xy[1].disp.pos & 0x3FF;
    pos_work_y = bg_w.bgw[xx].position_y;
    Scrn_Move_Set(xx, pos_work_x, pos_work_y);
    pos_work_x = -pos_work_x & 0x3FF;
    pos_work_y = (0x300 - (pos_work_y & 0x3FF)) & 0x3FF;
    Family_Set_W(xx + 1, pos_work_x, pos_work_y);
}



/* provisional name: Bg_Family_Set_Ex with the screen's pos_offset taken off the X position */
void Bg_Family_Set_Ex_Offset(s16 xx) {
    s16 pos_work_x;
    s16 pos_work_y;
    bg_w.bgw[xx].position_x = bg_w.bgw[xx].xy[0].disp.pos & 0x3FF;
    bg_w.bgw[xx].position_x -= bg_w.pos_offset;
    bg_w.bgw[xx].position_x &= 0x3FF;
    pos_work_x = bg_w.bgw[xx].position_x;
    bg_w.bgw[xx].position_y = bg_w.bgw[xx].xy[1].disp.pos & 0x3FF;
    pos_work_y = bg_w.bgw[xx].position_y;
    Scrn_Move_Set(xx, pos_work_x, pos_work_y);
    pos_work_x = -pos_work_x & 0x3FF;
    pos_work_y = (0x300 - (pos_work_y & 0x3FF)) & 0x3FF;
    Family_Set_W(xx + 1, pos_work_x, pos_work_y);
}



s32 effect_93_init(s8 Move_Type, s16 Time) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 93;
    ewk->wu.routine_no[0] = Move_Type - 1;
    ewk->wu.dir_timer = Time;
    Appear_Cursor = 0;
    return 0;
}
