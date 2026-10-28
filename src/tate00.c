/*
 * TATE00.C  Stage background control task
 *
 * TATE00 is the per-frame stage BG entry used during fights (and by the debug fight setups):
 * ta0_init00 sets a random compel_flag and runs bg_initialize; ta0_move then calls the stage's
 * own handler (from a local table of the 19 stage handlers) every frame and counts down the screen quake timers. The file ends with debug
 * helpers that step through the stages, scroll the layers and switch them off, and free the
 * stage work blocks.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "bg000.h"
#include "PLS02.h"
#include "tate00.h"
#include "Com_Pl.h"
#include "SYS_sub.h"
#include "fifo.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "ta_sub2.h"
#include "ta_sub.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "bg_sub.h"
#include "bg040.h"
#include "BG050.h"
#include "bg090.h"
#include "BG100.h"
#include "bg120.h"
#include "bg140.h"
#include "bg150.h"
#include "bg160.h"
#include "effe3.h"



void TATE00(void) {
    void (*jump_tbl[2])() = { ta0_init00, ta0_move };
    jump_tbl[bg_w.bg_routine]();
}



void ta0_init00(void) {
    bg_w.bg_routine++;
    bg_w.compel_flag = random_16_com();
    bg_w.compel_flag &= 3;
    bg_initialize();
    effect_F0_init();
    effect_E3_init();
}



/* the handler table is local; the BGnn0 names are the table slots (the stage numbers) */
void BG170(void);

void ta0_move(void) {
    void (*move_tbl[19])() = {
        BG000,
        BG010,
        BG020,
        BG030,
        BG040,
        BG050,
        BG050,
        BG070,
        BG070,
        BG090,
        BG100,
        BG110,
        BG110,
        BG110,
        BG140,
        BG150,
        BG160,
        BG170,
        BG170,
    };
    move_tbl[bg_w.bg_index]();
    if (bg_w.quake_x_index > 0) {
        bg_w.quake_x_index--;
    }
    if (bg_w.quake_y_index > 0) {
        bg_w.quake_y_index--;
    }
}



/* provisional name */
void bg_free_work_blocks(void) {
    s16 i;
    simmram_block_free_10(scr_cg_c_no);
    for (i = 0; i < bg_w.scno; i++) {
        simmram_block_free_40(bg_w.bgw[i].bg_adrs_c_no);
        sprite_list_clear(i);
        if (bg_w.bgw[i].zuubun != 0) {
            simmram_block_free_40(bg_w.bgw[i].suzi_c_no);
        }
    }
}



/* provisional name */
/* layers 0-5, then bg_pos_hosei2 and Bg_Family_Set once */
void bg_debug_scroll_layers(void) {
    BGW* bgw;
    s32 dx;
    s32 dy;
    s16 i;
    for (i = 0; i < 6; i++) {
        bgw = &bg_w.bgw[i];
        if (p1sw_0 & BUTTON_LP) {
            dx = bgw->speed_x * 2;
            dy = bgw->speed_y * 2;
        } else {
            dx = bgw->speed_x;
            dy = bgw->speed_y;
        }
        if (p1sw_0 & LEVER_LEFT) {
            Bg_mv_tw_appoint(i, -dx, 0);
            bgw->hos_xy[0].cal = bgw->xy[0].cal;
        }
        if (p1sw_0 & LEVER_RIGHT) {
            Bg_mv_tw_appoint(i, dx, 0);
            bgw->hos_xy[0].cal = bgw->xy[0].cal;
        }
        if (p1sw_0 & LEVER_UP) {
            Bg_mv_tw_appoint(i, 0, dy);
            bgw->hos_xy[0].cal = bgw->xy[0].cal;
        }
        if (p1sw_0 & LEVER_DOWN) {
            Bg_mv_tw_appoint(i, 0, -dy);
            bgw->hos_xy[0].cal = bgw->xy[0].cal;
        }
    }
    bg_pos_hosei2();
    Bg_Family_Set();
}



/* provisional name */
void bg_test_stage_select(void) {
    u16 sw;
    s16 changed;
    s8 save_27;
    s8 save_entry;
    changed = 0;
    sw = ~p1sw_1 & p1sw_0;
    if (sw & BUTTON_LK) {
        bg_select_no++;
        if (bg_select_no > 16) {
            bg_select_no = 0;
        }
        bg_w.stage = bg_test_stage_tbl[bg_select_no][0];
        bg_w.area = bg_test_stage_tbl[bg_select_no][1];
        changed = 1;
    }
    if (sw & BUTTON_MK) {
        bg_select_no--;
        if (bg_select_no < 0) {
            bg_select_no = 16;
        }
        bg_w.stage = bg_test_stage_tbl[bg_select_no][0];
        bg_w.area = bg_test_stage_tbl[bg_select_no][1];
        changed = 1;
    }
    if (changed) {
        System_all_clear_Wait();
        pcon_rno[0] = pcon_rno[1] = pcon_rno[2] = pcon_rno[3] = 0;
        save_27 = bg_test_flag;
        save_entry = bg_select_no;
        bg_work_clear();
        bg_select_no = save_entry;
        bg_test_flag = save_27;
    }
}



/* provisional name */
void bg_layers_off(void) {
    s16 i;

    for (i = 0; i < bg_w.scno; i++) {
        if ((scrn_reg_w[i].ctrl & 0x8000) == 0) {
            continue;
        }
        Bg_Off_W(1 << i);
    }
    if ((scrn_reg_w[3].ctrl & 0x8000) != 0) {
        Bg_Off_W(8);
    }
}
