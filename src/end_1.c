/*
 * END_1.C  Ending 1 (end_01000)
 *
 * end_01000(pl_num) is the ending script: it runs the common ending inits, loads the ending graphics,
 * writes the first BG cells (end_100_cell_set) and issues sound 20; then it counts down timer_1_tbl through
 * eight scenes, running the BG0 handler (end_100_move) and the BG1 handler (end_101_move) each frame, and
 * after the last scene hands over to the staff roll (fadeout_to_staff_roll, sound 27).
 * The BG0 handlers end_100_0000 (scenes 0-2, 5-7), end_100_0003 and end_100_0004 place the layer, request
 * fades, start effect E6 objects and show the ending messages; the BG1 handlers only place the layer.
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
#include "end_1.h"



void end_01000(u16 pl_num) {
    switch (end_w.r_no_1) {
    case 0:
        end_w.r_no_1++;
        end_w.r_no_2 = 0;
        common_end_init00(pl_num);
        load_char_gfx(0x7628, 1);
        end_w.timer = timer_1_tbl[end_w.r_no_2];
        common_end_init01();
        end_100_cell_set();
        bgm_request(20);
        break;
    case 1:
        end_w.timer--;
        if (end_w.timer < 0) {
            end_w.r_no_2++;
            if (end_w.r_no_2 == 8) {
                end_w.r_no_1++;
                end_w.end_flag = 1;
                fadeout_to_staff_roll();
                bgm_request(27);
            } else {
                end_w.timer = timer_1_tbl[end_w.r_no_2];
            }
            bg_w.bgw[0].r_no_1 = 0;
            bg_w.bgw[1].r_no_1 = 0;
        } else {
            end_100_move();
            end_101_move();
        }
    case 2:
        end_scn_pos_set2();
        end_bg_pos_hosei2();
        end_fam_set2();
        break;
    }
}



void end_100_move(void) {
    void (*end_100_jp[8])() = { end_100_0000, end_100_0000, end_100_0000, end_100_0003, end_100_0004, end_100_0000, end_100_0000, end_100_0000 };
    bgw_ptr = &bg_w.bgw[0];
    end_100_jp[end_w.r_no_2]();
}



void end_100_0000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
            Bg_On_W(1 << bgw_ptr->fam_no);
        }
        bgw_ptr->xy[0].disp.pos = end_1_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_1_pos[end_w.r_no_2][1];
        switch (end_w.r_no_2) {
        case 0:
            effect_E6_init(47);
            effect_E6_init(48);
            effect_E6_init(49);
            Rewrite_End_Message(1);
            break;
        case 1:
            effect_E6_init(50);
            effect_E6_init(51);
            Rewrite_End_Message(2);
            break;
        case 2:
            effect_E6_init(52);
            effect_E6_init(53);
            Rewrite_End_Message(3);
            end_fade_flag = 1;
            end_fade_timer = timer_1_tbl[2] - 120;
            break;
        case 5:
            bgm_request(31);
            break;
        case 6:
            effect_E6_init(57);
            Rewrite_End_Message(6);
            break;
        case 7:
            end_fade_flag = 1;
            end_fade_timer = timer_1_tbl[7] - 120;
            Rewrite_End_Message(8);
            break;
        }
        break;
    case 1:
        break;
    }
}



void end_100_0003(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        if (Request_Fade(50, 0) == 0) {
            break;
        }
        bgw_ptr->r_no_1++;
        end_no_cut = 1;
        break;
    case 1:
        if (end_fade_complete()) {
            bgw_ptr->r_no_1++;
            bgw_ptr->r_limit = 60;
        }
        break;
    case 2:
        bgw_ptr->r_limit--;
        if (bgw_ptr->r_limit < 0) {
            bgw_ptr->r_no_1++;
            end_w.timer = 0;
        }
        break;
    }
}



void end_100_0004(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        if (Request_Fade(49, 1) == 0) {
            break;
        }
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[0].disp.pos = end_1_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_1_pos[end_w.r_no_2][1];
        effect_E6_init(54);
        effect_E6_init(55);
        effect_E6_init(56);
        bg_w.bgw[1].r_no_1 = 1;
        Rewrite_End_Message(5);
        break;
    case 1:
        if (end_fade_complete()) {
            end_w.timer = 0;
            end_no_cut = 0;
        }
        break;
    }
}



void end_101_move(void) {
    void (*end_101_jp[8])() = { end_X_com01, end_X_com01, end_X_com01, end_101_0003, end_101_0004, end_101_0003, end_X_com01, end_101_0003 };
    bgw_ptr = &bg_w.bgw[1];
    end_101_jp[end_w.r_no_2]();
}



void end_101_0004(void) {
    if (bgw_ptr->r_no_1) {
        if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
            Bg_On_W(1 << bgw_ptr->fam_no);
        }
        bgw_ptr->xy[0].disp.pos = end_1_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_1_pos[end_w.r_no_2][1];
    }
}



void end_101_0003(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
            Bg_On_W(1 << bgw_ptr->fam_no);
        }
        bgw_ptr->xy[0].disp.pos = end_1_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_1_pos[end_w.r_no_2][1];
        break;
    case 1:
        break;
    }
}



void end_100_cell_set(void) {
    s16 i;
    const PANEL* p;
    p = end_100_panel0;
    for (i = 0; i < 8; i++, p++) {
        bg_cell_write(0, p->ofs, p->cell, (u32)end_100_scrn_data, 0, 0x220);
    }
    p = end_100_panel1;
    for (i = 0; i < 4; i++, p++) {
        bg_cell_write(1, p->ofs, p->cell, (u32)end_100_scrn_data, 0, 0x220);
    }
}
