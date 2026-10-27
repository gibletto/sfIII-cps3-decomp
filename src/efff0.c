/*
 * EFFF0.C  Effect F0: alternate background controller
 *
 * effect_F0_init (from tate00.c) creates the controller and clears another_bg. While either player's
 * another_bg request is set, effect_F0_move turns the stage layers off and BG 3 on, lowers sound
 * register 0's level and runs BG 3's wave line scroll from effF0_line_tbl (effF0_line_scroll), with
 * BG 3 and family 4 placed from BG 1 (effF0_scroll_set); seraph_flag tells other effects it is up.
 * When the requests end it restores the layers (effF0_scroll_reset; not while the super art flash
 * holds them). It ends for the finish screen (akebono_flag).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "fifo.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "meta_col_mem.h"

/* routine_no[0] */
#define R0_INIT         0       /* clear BG 3's line scroll */
#define R0_WAIT         1       /* wait for an another-BG request */
#define R0_MOVE         2       /* wave BG 3 while it is requested */
#define R0_OFF          3       /* put the stage layers back */
#define R0_KILL         99      /* (default) put the work back */

extern s16 ls_rate0;
extern s16 line_scroll_mode;
extern s16 ls_cnt1;
extern s16 ls_cnt2;
extern const s32 effF0_line_tbl[256];
void Scrn_Move_Set(s32 n, s16 x, s16 y);
void effF0_line_scroll(WORK_Other* ewk);
void effF0_scroll_reset(WORK_Other* ewk);
void effF0_scroll_set(WORK_Other* ewk);

void effect_F0_move(WORK_Other* ewk) {
    s16 i;
    if (akebono_flag) {
        ewk->wu.routine_no[0] = R0_KILL;
        seraph_flag = 0;
        Bg_Off_R(0x80);
    }
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        scrn_map_set_now(3, ake_scrl_w[0].adrs);
        memset(bg_w.bgw[3].suzi_adrs, 0, 0x1000);
        /* fall through */
    case R0_WAIT:
        if (!another_bg[0] && !another_bg[1]) {
            break;
        }
        ewk->wu.routine_no[0]++;
        Bg_On_W(0x80);
        ls_rate0 = 96;
        ls_cnt1 = 0;
        ls_cnt2 = 16;
        ewk->wu.old_rno[0] = 0;
        ewk->wu.old_rno[1] = 0;
        if (!(scrn_reg_w[3].ctrl & 0x8000)) {
            Bg_On_W(8);
        }
        for (i = 0; i < bg_w.scno; i++) {
            if (scrn_reg_w[i].ctrl & 0x8000) {
                Bg_Off_W(1 << i);
            }
        }
        sound_reg_level_set(0, 0xF0);
        /* fall through */
    case R0_MOVE:
        if (another_bg[0] || another_bg[1]) {
            seraph_flag = 1;
            scrn_map_set(3, ake_scrl_w[0].adrs);
            effF0_line_scroll(ewk);
line_done:;
        } else {
            scrn_map_set(3, ake_scrl_w[0].adrs);
            effF0_line_scroll(ewk);
            effF0_scroll_set(ewk);
            ewk->wu.routine_no[0] = R0_OFF;
            ewk->wu.old_rno[0] = 2;
            seraph_flag = 0;
            sound_reg_level_set(0, 0);
            return;
        }
        goto scroll_set;
    case R0_OFF:
        effF0_line_scroll(ewk);
scroll_set:;
        effF0_scroll_set(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

void effF0_line_scroll(WORK_Other* ewk) {
    s16* line = (s16*)bg_w.bgw[3].suzi_adrs + 0x400;
    u16 i;
    u16 ix;
    XY work;
    switch (ewk->wu.old_rno[0]) {
    case 0:
        ewk->wu.old_rno[0] = 1;
        ls_rate0 = 96;
        ls_cnt1 = 0;
        ls_cnt2 = 16;
        break;
    case 2:
        effF0_scroll_reset(ewk);
        break;
    case 1:
        if (aku_flag) {
            break;
        }
        if (EXE_flag) {
            break;
        } else if (Game_pause) {
            break;
        }
        line_scroll_mode = 0x108;
        for (i = 0; i < 512; i++) {
            ix = (ls_cnt1 + i * 2) & 0xFF;
            work.cal = effF0_line_tbl[ix];
            *line = work.disp.pos;
            line += 2;
        }
        ls_cnt1 = (ls_cnt1 + 2) & 0x1FF;
        break;
    }
}

void effF0_scroll_reset(WORK_Other* ewk) {
    s16 i;
    seraph_flag = 0;
    ewk->wu.routine_no[0] = R0_WAIT;
    if (!sa_pa_flag) {
        if (scrn_reg_w[3].ctrl & 0x8000) {
            Bg_Off_W(8);
        }
        for (i = 0; i < bg_w.scno; i++) {
            if (!(scrn_reg_w[i].ctrl & 0x8000)) {
                Bg_On_W(1 << i);
            }
        }
    }
    Bg_Off_W(0x80);
}

void effF0_scroll_set(WORK_Other* ewk) {
    s32 x;
    s16 pos_y;
    s32 y;
    ake_scrl_w[0].xy[1].cal = bg_w.bgw[1].wxy[1].cal;
    ake_scrl_w[0].pos_x = bg_w.bgw[1].wxy[0].disp.pos;
    if (bg_w.bgw[1].zuubun) {
        ake_scrl_w[0].pos_x += 0x200;
    }
    ake_scrl_w[0].pos_x -= bg_w.pos_offset;
    x = ake_scrl_w[0].pos_x;
    pos_y = ake_scrl_w[0].pos_y = bg_w.bgw[1].position_y;
    Scrn_Move_Set(3, x, pos_y);
    y = ake_scrl_w[0].pos_y;
    x = -x & 0x3FF;
    y = 0x300 - (y & 0x3FF);
    y &= 0x3FF;
    Family_Set_W(4, x, y);
}

s32 effect_F0_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.id = 150;
    another_bg[0] = another_bg[1] = 0;
    return 0;
}
