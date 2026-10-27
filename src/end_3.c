/*
 * END_3.C  Ending 3 (end_03000)
 *
 * end_03000(pl_num) is the ending script: it runs the common ending inits, loads the ending graphics,
 * writes the BG cells (end_300_cell_set, from end_scrn_data) and requests music 21; then it counts down
 * timer_3_tbl through nine scenes, running the BG0 handler (end_300_move) and the BG1 handler
 * (end_301_move) each frame, and after the last scene hands over to the staff roll
 * (fadeout_to_staff_roll, music 27). The BG0 handlers place the layer for each scene from end_3_pos
 * (drifting it in scenes 0, 1, 5 and 6, the direction by end_w.type), start the scene's effect E6
 * objects and show the ending messages; the last scene starts the fade. The BG1 handlers only turn
 * their layer on.
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
#include "end_3.h"



extern const PANEL end_300_panel[8];

#pragma inline(end_300_move, end_301_move)



void end_03000(u16 pl_num) {
    switch (end_w.r_no_1) {
    case END1_INIT:
        end_w.r_no_1++;
        end_w.r_no_2 = 0;
        common_end_init00(pl_num);
        load_char_gfx(0x7398, 1);
        end_w.timer = timer_3_tbl[end_w.r_no_2];
        common_end_init01();
        end_300_cell_set();
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
                end_w.timer = timer_3_tbl[end_w.r_no_2];
            }
            bg_w.bgw[0].r_no_1 = 0;
            bg_w.bgw[1].r_no_1 = 0;
        } else {
            end_300_move();
            end_301_move();
        }
    case END1_DONE:
        end_scn_pos_set2();
        end_bg_pos_hosei2();
        end_fam_set2();
        break;
    }
}



void end_300_move(void) {
    void (*end_300_jp[9])() = { end_300_0000, end_300_1000, end_300_2000, end_300_3000, end_300_2000, end_300_0000, end_300_1000, end_300_2000, end_300_2000 };
    end_300_jp[end_w.r_no_2]();
}



void end_300_0000(void) {
    bgw_ptr = &bg_w.bgw[0];
    switch (bgw_ptr->r_no_1) {
    case 0:
        Bg_On_W(1);
        bgw_ptr->r_no_1++;
        bgw_ptr->abs_x = 0x200;
        bgw_ptr->abs_y = 0;
        if (end_w.type == 3) {
            bgw_ptr->xy[0].disp.pos = end_3_pos[0][0];
            bgw_ptr->xy[1].disp.pos = end_3_pos[0][1];
            bgw_ptr->speed_x = 0x8000;
            bgw_ptr->speed_y = -0x3000;
        } else {
            bgw_ptr->xy[0].disp.pos = end_3_pos[1][0];
            bgw_ptr->xy[1].disp.pos = end_3_pos[1][1];
            bgw_ptr->speed_x = 0x8000;
            bgw_ptr->speed_y = 0x3000;
        }
        if (end_w.r_no_2 != 0) {
            Rewrite_End_Message(6);
        } else {
            Rewrite_End_Message(1);
        }
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        bgw_ptr->xy[1].cal += bgw_ptr->speed_y;
        break;
    }
}



void end_300_1000(void) {
    bgw_ptr = &bg_w.bgw[0];
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if (end_w.r_no_2 != 1) {
            Rewrite_End_Message(7);
        } else {
            Rewrite_End_Message(2);
        }
        if (end_w.type == 3) {
            bgw_ptr->xy[0].disp.pos = end_3_pos[1][0];
            bgw_ptr->xy[1].disp.pos = end_3_pos[1][1];
            bgw_ptr->speed_x = 0x8000;
            bgw_ptr->speed_y = 0x3000;
        } else {
            bgw_ptr->xy[0].disp.pos = end_3_pos[0][0];
            bgw_ptr->xy[1].disp.pos = end_3_pos[0][1];
            bgw_ptr->speed_x = 0x8000;
            bgw_ptr->speed_y = -0x3000;
        }
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        bgw_ptr->xy[1].cal += bgw_ptr->speed_y;
        break;
    }
}



void end_300_2000(void) {
    bgw_ptr = &bg_w.bgw[0];
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[0].disp.pos = end_3_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_3_pos[end_w.r_no_2][1];
        switch (end_w.r_no_2) {
        case 2:
            effect_E6_init(0);
            effect_E6_init(1);
            Rewrite_End_Message(3);
            break;
        case 4:
            effect_E6_init(6);
            effect_E6_init(7);
            Rewrite_End_Message(5);
            break;
        case 7:
            effect_E6_init(10);
            effect_E6_init(11);
            if (end_w.type == 3) {
                effect_E6_init(8);
                effect_E6_init(9);
            } else {
                effect_E6_init(16);
                effect_E6_init(17);
            }
            Rewrite_End_Message(8);
            break;
        case 8:
            end_fade_flag = 1;
            end_fade_timer = timer_3_tbl[8] - 120;
            Rewrite_End_Message(9);
            if (end_w.type == 3) {
                effect_E6_init(12);
                effect_E6_init(13);
            } else {
                effect_E6_init(14);
                effect_E6_init(15);
            }
            break;
        }
        break;
    case 1:
        break;
    }
}



void end_300_3000(void) {
    bgw_ptr = &bg_w.bgw[0];
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[0].disp.pos = end_3_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_3_pos[end_w.r_no_2][1];
        bgw_ptr->speed_x = -0x180000;
        if (end_w.type == 3) {
            effect_E6_init(2);
            effect_E6_init(3);
        } else {
            effect_E6_init(4);
            effect_E6_init(5);
        }
        Rewrite_End_Message(4);
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        break;
    }
}



void end_301_move(void) {
    void (*end_301_jp[9])() = { end_301_0000, end_301_1000, end_X_com01, end_X_com01, end_X_com01, end_301_0000, end_301_1000, end_X_com01, end_X_com01 };
    end_301_jp[end_w.r_no_2]();
}



void end_301_0000(void) {
    bgw_ptr = &bg_w.bgw[1];
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        Bg_On_W(2);
        bgw_ptr->abs_x = 0x200;
        bgw_ptr->abs_y = 0;
        if (end_w.type == 3) {
            bgw_ptr->xy[0].disp.pos = 0x110;
            bgw_ptr->xy[1].disp.pos = 0x300;
            bgw_ptr->speed_x = -0x1000;
            bgw_ptr->speed_y = 0;
        } else {
            bgw_ptr->xy[0].disp.pos = 0x110;
            bgw_ptr->xy[1].disp.pos = 0x300;
            bgw_ptr->speed_x = -0x1000;
            bgw_ptr->speed_y = 0;
        }
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        bgw_ptr->xy[1].cal += bgw_ptr->speed_y;
        break;
    }
}





void end_301_1000(void) {
    bgw_ptr = &bg_w.bgw[1];
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if (end_w.type == 3) {
            bgw_ptr->xy[0].disp.pos = 0x330;
            bgw_ptr->xy[1].disp.pos = 0x300;
            bgw_ptr->speed_x = -0x1000;
            bgw_ptr->speed_y = 0;
        } else {
            bgw_ptr->xy[0].disp.pos = 0x330;
            bgw_ptr->xy[1].disp.pos = 0x300;
            bgw_ptr->speed_x = -0x1000;
            bgw_ptr->speed_y = 0;
        }
        Bg_On_W(2);
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        bgw_ptr->xy[1].cal += bgw_ptr->speed_y;
        break;
    }
}



void end_300_cell_set(void) {
    s16 i;
    const PANEL* p;
    p = end_300_panel;
    for (i = 0; i < 8; i++, p++) {
        bg_cell_write(0, p->ofs, p->cell, (u32)end_scrn_data, 0, 0x220);
    }
    bg_cell_write(0, 0x2000, 9, (u32)end_scrn_data, 0, 0x220);
    bg_cell_write_xyflip(0, 0x2040, 9, (u32)end_scrn_data, 0, 0x220);
    bg_cell_write(0, 0x2080, 9, (u32)end_scrn_data, 0, 0x220);
    bg_cell_write_xyflip(0, 0x20C0, 9, (u32)end_scrn_data, 0, 0x220);
    bg_cell_write(1, 0, 1, (u32)end_scrn_data, 0, 0x220);
    bg_cell_write(1, 64, 2, (u32)end_scrn_data, 0, 0x220);
    bg_cell_write(1, 128, 1, (u32)end_scrn_data, 0, 0x220);
    bg_cell_write(1, 0xC0, 2, (u32)end_scrn_data, 0, 0x220);
}
