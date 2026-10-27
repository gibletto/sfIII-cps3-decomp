/*
 * EFFB0.C  Effect B0: scene changes of an ending
 *
 * effect_B0_init clears BG0 and BG3, puts
 * their cells (end_ake_cell_put) and starts effect B1. effect_B0_move runs three scenes in turn
 * (effB0_0000, effB0_1000, effB0_2000), each fading out (Request_Fade 43) and back in, starting
 * the effect D2 wipes and B1, and checks every frame whether the player cut the scene short
 * (Cut_Cut_Cut in dir_timer); then it fades the BGM and sets END_OF_B0 to 2.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "SYS_sub.h"
#include "sys_test.h"
#include "sys_config.h"
#include "color3rd.h"
#include "end_main.h"
#include "fifo.h"
#include "textsound_2.h"
#include "EFFB1_INIT.h"
#include "effd2.h"
#include "EFFB0.h"

/* routine_no[0] */
#define R0_SCENE1       0       /* first scene */
#define R0_SCENE2       1       /* second scene */
#define R0_SCENE3       2       /* third scene */
#define R0_BGM_OUT      3       /* fade the BGM out if cut short */
#define R0_WAIT         4       /* count down, then flag the end */
#define R0_DONE         5       /* finished */

/* routine_no[1]: step of a scene */
#define R1_FADE_OUT     0       /* start the fade out */
#define R1_BG_ON        1       /* at black, switch the BGs on */
#define R1_FADE_IN      2       /* start the fade in */
#define R1_WIPE         3       /* faded in: start the wipe */
#define R1_HOLD         4       /* count down, then end the scene */

/* routine_no[1], effB0_1000 and effB0_2000 */
#define R1_BLACK        1       /* at black, start the fade in */
#define R1_FADING_IN    2       /* wait for the fade in */
#define R1_COUNT        3       /* count down, then end the scene */

extern s16 END_OF_B0;
extern s8 Forbid_Break;
extern const u16 effb0_scrn_data[10][16][32]; /* provisional name */
extern const s16 effb0_scr_record_data[];    /* provisional name */

s32 effB0_0000(WORK_Other* ewk);
s32 effB0_1000(WORK_Other* ewk);
s32 effB0_2000(WORK_Other* ewk);
void effB0_check(WORK_Other* ewk);
void effB0_cut_check(WORK_Other* ewk);
void end_ake_cell_put(s16 map, s32 ofs, s32 cell, u32 src);

#pragma inline(effB0_cut_check)



/* Run the ending scene sequence. */
void effect_B0_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_SCENE1:
        if (effB0_0000(ewk)) {
            break;
        }
        ewk->wu.routine_no[0]++;
        effB0_check(ewk);
        break;
    case R0_SCENE2:
        if (effB0_1000(ewk)) {
            break;
        }
        ewk->wu.routine_no[0]++;
        effB0_check(ewk);
        break;
    case R0_SCENE3:
        if (effB0_2000(ewk)) {
            break;
        }
        ewk->wu.routine_no[0] = R0_BGM_OUT;
        ewk->wu.dir_old = 8;
        effect_D2_init(ewk);
        break;
    case R0_BGM_OUT:
        ewk->wu.routine_no[0]++;
        if (ewk->wu.dir_timer) {
            bgm_fade_out(0x222);
        }
        /* fall through */
    case R0_WAIT:
        ewk->wu.dir_old--;
        if (ewk->wu.dir_old < 0) {
            ewk->wu.routine_no[0]++;
            END_OF_B0 = 2;
        }
        break;
    case R0_DONE:
        break;
    }
}



/* cut short: go to the BGM fade */
/* provisional name */
void effB0_check(WORK_Other* ewk) {
    if (ewk->wu.dir_timer) {
        ewk->wu.routine_no[0] = R0_BGM_OUT;
        ewk->wu.dir_old = 8;
    }
}



/* Read the request to cut the scene short. */
/* provisional name */
void effB0_cut_check(WORK_Other* ewk) {
    ewk->wu.dir_timer = Cut_Cut_Cut();
}



/* scene 1 */
/* provisional name */
s32 effB0_0000(WORK_Other* ewk) {
    effB0_cut_check(ewk);
    switch (ewk->wu.routine_no[1]) {
    case R1_FADE_OUT:
        if (!Request_Fade(43, 0)) {
            break;
        }
        ewk->wu.routine_no[1]++;
        break;
    case R1_BG_ON:
        if (Check_Fade_Complete()) {
            ewk->wu.routine_no[1]++;
            Bg_On_R(1);
            Bg_On_R(8);
        }
        Forbid_Break = 0;
        break;
    case R1_FADE_IN:
        if (!Request_Fade(39, 0)) {
            break;
        }
        ewk->wu.routine_no[1]++;
        break;
    case R1_WIPE:
        if (Check_Fade_Complete()) {
            ewk->wu.routine_no[1]++;
            ewk->wu.dir_old = 4;
            effect_D2_init(ewk);
        }
        Forbid_Break = 0;
        break;
    case R1_HOLD:
        ewk->wu.dir_old--;
        if (ewk->wu.dir_old < 0) {
            ewk->wu.routine_no[1] = R1_FADE_OUT;
            ewk->wu.dir_step = 1;
            effect_B1_init((PLW*)ewk);
            effect_D2_init2(ewk);
            return 0;
        }
        break;
    }
    return 1;
}



/* scene 2 */
/* provisional name */
s32 effB0_1000(WORK_Other* ewk) {
    effB0_cut_check(ewk);
    switch (ewk->wu.routine_no[1]) {
    case R1_FADE_OUT:
        if (!Request_Fade(43, 0)) {
            break;
        }
        Forbid_Break = 0;
        ewk->wu.routine_no[1]++;
        break;
    case R1_BLACK:
        if (Check_Fade_Complete()) {
            if (Request_Fade(44, 0) == 0) {
                break;
            }
            ewk->wu.routine_no[1]++;
        }
        Forbid_Break = 0;
        break;
    case R1_FADING_IN:
        if (Check_Fade_Complete()) {
            ewk->wu.routine_no[1]++;
            ewk->wu.dir_old = 1;
        }
        Forbid_Break = 0;
        break;
    case R1_COUNT:
        ewk->wu.dir_old--;
        if (ewk->wu.dir_old < 0) {
            ewk->wu.dir_step = 2;
            effect_B1_init((PLW*)ewk);
            ewk->wu.routine_no[1] = R1_FADE_OUT;
            return 0;
        }
        break;
    }
    return 1;
}



/* scene 3 */
/* provisional name */
s32 effB0_2000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_FADE_OUT:
        if (!Request_Fade(43, 0)) {
            break;
        }
        Forbid_Break = 0;
        ewk->wu.routine_no[1]++;
        break;
    case R1_BLACK:
        if (Check_Fade_Complete()) {
            if (Request_Fade(39, 0) == 0) {
                break;
            }
            ewk->wu.routine_no[1]++;
        }
        Forbid_Break = 0;
        break;
    case R1_FADING_IN:
        if (Check_Fade_Complete()) {
            ewk->wu.routine_no[1]++;
            ewk->wu.dir_old = 2;
            effect_D2_init2(ewk);
        }
        Forbid_Break = 0;
        break;
    case R1_COUNT:
        ewk->wu.dir_old--;
        if (ewk->wu.dir_old < 0) {
            ewk->wu.routine_no[1] = R1_FADE_OUT;
            return 0;
        }
        break;
    }
    return 1;
}



/* Create the ending scene controller. */
s32 effect_B0_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    s16 n;
    s32 x;
    s32 y;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    END_OF_B0 = 0;
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.id = 110;
    ewk->wu.dir_step = 0;
    ewk->wu.dir_timer = 0;
    ewk->wu.direction = 0;
    load_any_color_fade(9, 0, 0, 0);
    Bg_Off_R(16);
    (void)&((WORK*)2)->id;
    bg_w.bgw[0].zuubun = 0;
    bg_w.quake_x_index = 0;
    bg_w.quake_y_index = 0;
    for (i = 0; i < 2; i = i + 1) {
        if (i) {
            n = 3;
        } else {
            n = 0;
        }
        bg_w.bgw[n].r_no_1 = bg_w.bgw[n].r_no_2 = 0;
        bg_w.bgw[n].pos_x_work = 0x200;
        bg_w.bgw[n].pos_y_work = 0;
        bg_w.bgw[n].hos_xy[0].cal = bg_w.bgw[n].wxy[0].cal = bg_w.bgw[n].xy[0].cal = 0x2000000;
        bg_w.bgw[n].hos_xy[1].cal = bg_w.bgw[n].wxy[1].cal = bg_w.bgw[n].xy[1].cal = 0;
        bg_w.bgw[n].position_x = (0x200 - bg_w.pos_offset) & 0x3FF;
        bg_w.bgw[n].position_y = 0;
    }
    (void)&((WORK*)0x200)->id;
    scrn_reg_w[0].ctrl &= 0xFE7F;
    (void)&((WORK*)0x2000000)->id;
    
    end_ake_cell_put(0, 0x3040, 6, (u32)effb0_scrn_data);
    end_ake_cell_put(0, 0x3080, 7, (u32)effb0_scrn_data);
    Bg_Off_R(1);
    scrn_map_set_now(0, (u32)bg_w.bgw[0].bg_address);
    x = bg_w.bgw[0].position_x;
    y = bg_w.bgw[0].position_y;
    Scrn_Move_Set(0, x, y);
    x = -x & 0x3FF;
    y = (768 - (y & 0x3FF)) & 0x3FF;
    Family_Set_W(1, x, y);
    bg_w.bgw[3].bg_adrs_c_no = simmram_big_page_alloc_40(1);
    bg_w.bgw[3].bg_address = (u16*)simmram_slot_addr(bg_w.bgw[3].bg_adrs_c_no);
    scrn_attr_set(3, 0, 31);
    scrn_reg_w[3].ctrl &= 0xFE7F;
    sprite_list_setup(3, 1, (s16*)effb0_scr_record_data);
    end_ake_cell_put(3, 0x3040, 8, (u32)effb0_scrn_data);
    end_ake_cell_put(3, 0x3080, 9, (u32)effb0_scrn_data);
    Bg_Off_R(8);
    scrn_map_set_now(3, (u32)bg_w.bgw[3].bg_address);
    x = bg_w.bgw[3].position_x;
    y = bg_w.bgw[3].position_y;
    Scrn_Move_Set(3, x, y);
    x = -x & 0x3FF;
    y = (768 - (y & 0x3FF)) & 0x3FF;
    Family_Set_W(4, x, y);
    return effect_B1_init((PLW*)ewk);
}



/* Write into the background's map using its scroll character base. */
void end_ake_cell_put(s16 map, s32 ofs, s32 cell, u32 src) {
    register u16* s;
    s32 x;
    u16* dst;
    u32 adrs;
    adrs = (u32)bg_w.bgw[map].bg_address;
    ofs += adrs;
    x = 0;
    cell = (cell << 10) + src;
    dst = (u16*)ofs;
    s = (u16*)cell;
    x += bg_w.scroll_cg_adr >> 7;
    blit_16x16_tile(s, (u16)x, dst, 0x27F);
}
