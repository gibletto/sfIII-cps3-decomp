/*
 * END_11.C  Ending 11 (end_11000)
 *
 * end_11000(pl_num) is the ending script: it runs the common ending inits, loads the ending graphics,
 * gives BG0 a line-scroll page and requests music 21; then it counts down end_11_timer_tbl through nine
 * scenes, running the handlers of BG0, BG1 and BG2 (end_1100_move, end_1101_move, end_1102_move) each
 * frame, and after the last scene hands over to the staff roll (music 27). The BG0 handlers place the
 * layer, run the scene fades (Request_Fade), start the scene's effect E6 objects and show the ending
 * messages; end_1100_3000 also waves BG0 through its line scroll. end_1100_6000 is not called.
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
#include "SYS_sub.h"
#include "efff7.h"
#include "efff8_code.h"
#include "EFFF9.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "end_main.h"
#include "effe6.h"
#include "aboutspr.h"
#include "end_11.h"

extern const u32 end_1100_scrn_data[];
extern const s32* end_11_cell_ptr0[9];
extern const s32* end_11_cell_ptr1[9];
extern s16 ls_rate0;
extern s16 ls_cnt2;

const s32 end_11_cell_tbl[2][2] = { { 0x3040, 3 }, { 0x3080, 4 } };

const s16 end_11_timer_tbl[10] = { 300, 412, 290, 180, 300, 240, 180, 120, 300, 0 };

void end_11000(u16 pl_num) {
    switch (end_w.r_no_1) {
    case END1_INIT:
        end_w.r_no_1++;
        end_w.r_no_2 = 0;
        common_end_init00(pl_num);
        common_end_init01();
        end_w.timer = end_11_timer_tbl[end_w.r_no_2];
        load_char_gfx(0x74D8, 1);
        bg_w.bgw[0].suzi_c_no = simmram_small_page_alloc_40(1);
        bg_w.bgw[0].suzi_adrs = (u16*)simmram_slot_addr(bg_w.bgw[0].suzi_c_no);
        scrn_linescroll_set_now(0, bg_w.bgw[0].suzi_adrs);
        memset(bg_w.bgw[0].suzi_adrs, 0, 0x1000);
        bgm_request(21);
        break;
    case END1_SCENES:
        end_w.timer--;
        if (end_w.timer < 0) {
            end_w.r_no_2++;
            if (end_w.r_no_2 == 9) {
                end_w.r_no_1++;
                end_w.end_flag = 1;
                bgm_request(27);
                fadeout_to_staff_roll();
            } else {
                end_w.timer = end_11_timer_tbl[end_w.r_no_2];
            }
            bg_w.bgw[0].r_no_1 = 0;
            bg_w.bgw[1].r_no_1 = 0;
            bg_w.bgw[2].r_no_1 = 0;
        } else {
            end_1100_move();
            end_1101_move();
            end_1102_move();
        }
    case END1_DONE:
        end_scn_pos_set2();
        end_bg_pos_hosei2();
        end_fam_set2();
        break;
    }
}

void end_1100_move(void) {
    void (*end_1100_jp[9])() = { end_1100_0000, end_1100_1000, end_1100_2000, end_1100_3000, end_1100_0000, end_1100_5000, end_1100_3000, end_1100_7000, end_1100_0000 };
    bgw_ptr = &bg_w.bgw[0];
    end_1100_jp[end_w.r_no_2]();
}

void end_1100_0000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        Bg_Off_W(16);
        if (end_w.r_no_2 != 8) {
            Rewrite_End_Message(1);
        } else {
            Rewrite_End_Message(5);
            end_fade_flag = 1;
            end_fade_timer = end_11_timer_tbl[8] - 120;
        }
        bg_cell_write(0, 0x1040, 19, (u32)end_1100_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x1080, 19, (u32)end_1100_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x2040, 15, (u32)end_1100_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x2080, 16, (u32)end_1100_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x3040, 17, (u32)end_1100_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x3080, 18, (u32)end_1100_scrn_data, 0, 0x220);
        Bg_On_W(1);
        bgw_ptr->abs_x = bgw_ptr->xy[0].disp.pos = 0x200;
        bgw_ptr->abs_y = bgw_ptr->xy[1].disp.pos = 0;
        bgw_ptr->speed_y = 0x18000;
        if (end_w.r_no_2 != 8) {
            effect_E6_init(23);
        } else {
            effect_E6_init(65);
        }
        break;
    case 1:
        bgw_ptr->xy[1].cal += bgw_ptr->speed_y;
        if (bgw_ptr->xy[1].disp.pos > 0x200) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 2:
        break;
    }
}


void end_1100_1000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        Rewrite_End_Message(2);
        end_11_cell_set(0, end_w.r_no_2);
        bgw_ptr->xy[0].disp.pos = 0x200;
        bgw_ptr->xy[1].disp.pos = 0;
        effect_E6_init(24);
        break;
    case 1:
        break;
    }
}

const s16 end_11_scroll_tbl[19] = { 0, -1, 0, 1, 0, -2, 0, 2, 0, -2, 0, 2, 0, -2, 0, 2, 0, -2, 0 };

const u8 end_11_blink_tbl[62] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0 };

void end_1100_2000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        end_11_cell_set(0, end_w.r_no_2);
        bgw_ptr->xy[0].disp.pos = 0x200;
        bgw_ptr->xy[1].disp.pos = 0;
        effect_E6_init(25);
        bgw_ptr->r_limit = 0;
        break;
    case 1:
        bgw_ptr->r_limit++;
        if (bgw_ptr->r_limit > 60) {
            bgw_ptr->r_no_1++;
            bgw_ptr->disp_flag = 1;
            bgw_ptr->r_limit = 200;
        } else {
            bgw_ptr->disp_flag = end_11_blink_tbl[bgw_ptr->r_limit];
        }
        if (bgw_ptr->disp_flag) {
            Bg_On_W(1);
        } else {
            Bg_Off_W(1);
        }
        break;
    case 2:
        bgw_ptr->r_limit--;
        if (bgw_ptr->r_limit < 0) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 3:
        if (Request_Fade(51, 0) == 0) {
            break;
        }
        end_no_cut = 1;
        bgw_ptr->r_no_1++;
        Rewrite_End_Message(0);
        break;
    case 4:
        if (end_fade_complete()) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 5:
        break;
    }
}


void end_1100_3000(void) {
    s16* line;
    u16 i;
    u16 ix;
    XY work;
    switch (bgw_ptr->r_no_1) {
    case 0:
        if (Request_Fade(54, 0) == 0) {
            break;
        }
        bgw_ptr->r_no_1++;
        Rewrite_End_Message(0);
        end_no_cut = 1;
        end_11_cell_set(0, end_w.r_no_2);
        bgw_ptr->xy[0].disp.pos = 0x200;
        bgw_ptr->xy[1].disp.pos = 0;
        effect_E6_init(26);
        Bg_On_W(16);
        Bg_On_W(1);
        ls_rate0 = 96;
        ls_cnt1 = 0;
        ls_cnt2 = 16;
        break;
    case 1:
        if (end_fade_complete()) {
            bgw_ptr->r_no_1++;
            end_no_cut = 0;
        }
    case 2:
        ls_rate1 = 0x108;
        line = (s16*)bg_w.bgw[0].suzi_adrs + 0x400;
        for (i = 0; i < 512; i++) {
            ix = (ls_cnt1 + i * 4) & 0xFF;
            work.cal = (rate_256_table[ix][RATE_X] * ls_rate1) >> 4;
            *line = work.disp.pos;
            line += 2;
        }
        ls_cnt1 = (ls_cnt1 + 2) & 0x1FF;
        break;
    }
}

void end_1100_5000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        end_11_cell_set(0, end_w.r_no_2);
        bgw_ptr->xy[0].disp.pos = 0x200;
        bgw_ptr->xy[1].disp.pos = 0;
        effect_E6_init(27);
        Rewrite_End_Message(3);
        break;
    case 1:
        if (end_w.timer > 32) {
            break;
        }
        bgw_ptr->r_no_1++;
        Rewrite_End_Message(0);
    case 2:
        if (Request_Fade(51, 0) == 0) {
            break;
        }
        bgw_ptr->r_no_1++;
        end_no_cut = 1;
        break;
    case 3:
        if (end_fade_complete()) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 4:
        break;
    }
}


void end_1100_6000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        Bg_Off_W(16);
        bg_cell_write(0, 0x2040, 15, (u32)end_1100_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x2080, 16, (u32)end_1100_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x3040, 17, (u32)end_1100_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x3080, 18, (u32)end_1100_scrn_data, 0, 0x220);
        Rewrite_End_Message(0);
        Bg_On_W(1);
        bgw_ptr->abs_x = bgw_ptr->xy[0].disp.pos = 0x200;
        bgw_ptr->abs_y = bgw_ptr->xy[1].disp.pos = 0;
        bgw_ptr->speed_y = 0x10000;
        effect_E6_init(23);
        break;
    case 1:
        bgw_ptr->xy[1].cal += bgw_ptr->speed_y;
        if (bgw_ptr->xy[1].disp.pos > 0x100) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 2:
        if (Request_Fade(50, 0) == 0) {
            break;
        }
        bgw_ptr->r_no_1++;
        end_no_cut = 1;
    case 3:
        if (end_fade_complete()) {
            bgw_ptr->r_no_1++;
            end_no_cut = 0;
        }
        break;
    case 4:
        break;
    }
}







void end_1100_7000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        if (Request_Fade(49, 0) == 0) {
            break;
        }
        bgw_ptr->r_no_1++;
        end_no_cut = 1;
        Rewrite_End_Message(4);
        Bg_On_W(1);
        Bg_Off_W(16);
        end_11_cell_set(0, end_w.r_no_2);
        bgw_ptr->xy[0].disp.pos = 0x200;
        bgw_ptr->xy[1].disp.pos = 0;
        effect_E6_init(28);
        bgw_ptr->speed_x = 0x2000;
        bgw_ptr->r_limit = 48;
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        bgw_ptr->r_limit--;
        if (bgw_ptr->r_limit < 0) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 2:
        if (end_fade_complete()) {
            bgw_ptr->r_no_1++;
            end_no_cut = 0;
        }
        break;
    case 3:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        break;
    }
}


void end_1101_move(void) {
    void (*end_1101_jp[9])() = { end_1101_0000, end_1101_0000, end_1101_0000, end_X_com01, end_1101_0000, end_X_com01, end_X_com01, end_X_com01, end_1101_0000 };
    bgw_ptr = &bg_w.bgw[1];
    end_1101_jp[end_w.r_no_2]();
}

void end_1102_move(void) {
    void (*end_1102_jp[9])() = { end_1101_0000, end_X_com01, end_X_com01, end_X_com01, end_1101_0000, end_X_com01, end_X_com01, end_X_com01, end_1101_0000 };
    bgw_ptr = &bg_w.bgw[2];
    end_1102_jp[end_w.r_no_2]();
}

void end_1101_0000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        end_11_cell_set(bgw_ptr->fam_no, end_w.r_no_2);
        Bg_On_W(1 << bgw_ptr->fam_no);
        bgw_ptr->abs_x = bgw_ptr->xy[0].disp.pos = 0x200;
        bgw_ptr->abs_y = bgw_ptr->xy[1].disp.pos = 0;
        break;
    case 1:
        break;
    }
}


void end_11_cell_set(bg, n)
s16 bg;
s16 n;
{
    const s32* p;
    s16 i;
    switch (bg) {
    case 0:
        p = end_11_cell_ptr0[n];
        break;
        break;
    case 1:
        p = end_11_cell_ptr1[n];
        break;
    case 2:
        p = end_11_cell_tbl[0];
        break;
    }
    for (i = 0; i < 2; i++) {
        bg_cell_write(bg, p[0], p[1], (u32)end_1100_scrn_data, 0, 0x220);
        p += 2;
    }
}
