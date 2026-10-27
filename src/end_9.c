/*
 * END_9.C  Ending 9 (end_09000)
 *
 * end_09000(pl_num) is the ending script: it runs the common ending inits, loads the ending graphics,
 * writes the BG cells (end_900_cell_set) and requests music 21; then it counts down timer_9_tbl through
 * seven scenes, running the BG0 handler (end_900_move) and the BG1 handler (end_901_0000) each frame,
 * and after the last scene hands over to the staff roll (music 27). The BG0 handlers place the layer,
 * start the scene's effects (E6, and G7, G8 and H1) and show the ending messages; the last scene starts
 * the fade.
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
#include "EFFG7.h"
#include "effg8.h"
#include "aboutspr.h"
#include "end_9.h"



void end_09000(u16 pl_num) {
    switch (end_w.r_no_1) {
    case END1_INIT:
        end_w.r_no_1++;
        end_w.r_no_2 = 0;
        common_end_init00(pl_num);
        common_end_init01();
        end_w.timer = timer_9_tbl[end_w.r_no_2];
        load_char_gfx(0x7498, 1);
        end_900_cell_set();
        bgm_request(21);
        break;
    case END1_SCENES:
        end_w.timer--;
        if (end_w.timer < 0) {
            end_w.r_no_2++;
            if (end_w.r_no_2 == 7) {
                end_w.r_no_1++;
                end_w.end_flag = 1;
                bgm_request(27);
                fadeout_to_staff_roll();
            } else {
                end_w.timer = timer_9_tbl[end_w.r_no_2];
            }
            bg_w.bgw[0].r_no_1 = 0;
            bg_w.bgw[1].r_no_1 = 0;
        } else {
            end_900_move();
            end_901_0000();
        }
    case END1_DONE:
        end_scn_pos_set2();
        end_bg_pos_hosei2();
        end_fam_set2();
        break;
    }
}



void end_900_move(void) {
    void (*end_900_jp[7])() = { end_900_0000, end_900_1000, end_900_2000, end_900_2000, end_900_4000, end_900_5000, end_900_6000 };
    bgw_ptr = &bg_w.bgw[0];
    end_900_jp[end_w.r_no_2]();
}



void end_900_0000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        Bg_On_W(1);
        bgw_ptr->abs_x = 0x200;
        bgw_ptr->abs_y = 0;
        bgw_ptr->xy[0].disp.pos = end_9_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_9_pos[end_w.r_no_2][1];
        bgw_ptr->speed_x = -0x4000;
        effect_E6_init(34);
        effect_G7_init(0);
        Rewrite_End_Message(1);
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        break;
    }
}



void end_900_1000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        effect_E6_init(35);
        Rewrite_End_Message(2);
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        break;
    }
}



void end_900_2000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        Rewrite_End_Message(0);
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        break;
    }
}



void end_900_4000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        effect_E6_init(36);
        effect_E6_init(37);
        Rewrite_End_Message(4);
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        break;
    }
}



void end_900_5000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        break;
    }
}



void end_900_6000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->abs_x = bgw_ptr->xy[0].disp.pos = end_9_pos[end_w.r_no_2][0];
        bgw_ptr->abs_y = bgw_ptr->xy[1].disp.pos = end_9_pos[end_w.r_no_2][1];
        bgw_ptr->speed_x = -0xC000;
        bgw_ptr->speed_y = -0x1000;
        effect_G8_init();
        effect_H1_init();
        bgw_ptr->r_limit = 90;
        Rewrite_End_Message(5);
        end_fade_flag = 1;
        end_fade_timer = timer_9_tbl[6] - 120;
        break;
    case 1:
        bgw_ptr->r_limit--;
        if (bgw_ptr->r_limit < 0) {
            bgw_ptr->r_no_1++;
            effect_E6_init(38);
        }
    case 2:
        if (bgw_ptr->xy[0].disp.pos > 0x1A0) {
            bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
            bgw_ptr->abs_x = bgw_ptr->xy[0].disp.pos;
        } else {
            bgw_ptr->xy[0].cal = 0x1A00000;
            bgw_ptr->abs_x = 0x1A0;
        }
        if (bgw_ptr->xy[1].disp.pos > 16) {
            bgw_ptr->xy[1].cal += bgw_ptr->speed_y;
            bgw_ptr->abs_y = bgw_ptr->xy[1].disp.pos;
        } else {
            bgw_ptr->xy[1].cal = 0x100000;
            bgw_ptr->abs_y = 16;
        }
        break;
    }
}



void end_901_0000(void) {
    bgw_ptr = &bg_w.bgw[1];
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->abs_x = bgw_ptr->xy[0].disp.pos = 0x200;
        bgw_ptr->abs_y = bgw_ptr->xy[1].disp.pos = 0;
    case 1:
        end_scn_pos_set(1);
        end_bg_pos_hosei(1);
        end_fam_set(1);
        break;
    }
}



void end_900_cell_set(void) {
    s16 i;
    const PANEL* p;
    p = end_900_bg0_cell_tbl;
    for (i = 0; i < 7; i++, p++) {
        bg_cell_write(0, p->ofs, p->cell, (u32)end_900_scrn_data, 0, 0x220);
    }
    bg_cell_write_xyflip(0, 0x20C0, 3, (u32)end_900_scrn_data, 0, 0x220);
}
