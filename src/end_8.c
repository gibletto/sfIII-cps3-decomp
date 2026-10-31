/*
 * END_8.C  Ending 8 (end_08000)
 *
 * end_08000(pl_num) is the ending script: it runs the common ending inits, loads the ending graphics,
 * writes the BG cells (end_800_cell_set, from end_scrn_data) and requests music 25; then it counts down
 * timer_8_tbl through four scenes, running the handlers of BG0, BG1 and BG2 (end_800_0000,
 * end_801_0000, end_802_0000) each frame, and after the last scene hands over to the staff roll (music
 * 27). The BG0 handler starts each scene's effect E6 objects and the effect F2 flying objects, shows the
 * ending messages and starts the fade in the last scene.
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
#include "end_8.h"



extern const PANEL* end_8_panel_p[2];



void end_08000(u16 pl_num) {
    switch (end_w.r_no_1) {
    case END1_INIT:
        end_w.r_no_1++;
        end_w.r_no_2 = 0;
        common_end_init00(pl_num);
        load_char_gfx(0x73E8, 1);
        common_end_init01();
        end_800_cell_set();
        BGM_Request(25);
        end_w.timer = timer_8_tbl[end_w.r_no_2];
        break;
    case END1_SCENES:
        end_w.timer--;
        if (end_w.timer < 0) {
            end_w.r_no_2++;
            if (end_w.r_no_2 == 4) {
                end_w.r_no_1++;
                end_w.end_flag = 1;
                BGM_Request(27);
                fadeout_to_staff_roll();
            } else {
                end_w.timer = timer_8_tbl[end_w.r_no_2];
                bg_w.bgw[0].r_no_1 = 0;
                bg_w.bgw[1].r_no_1 = 0;
                bg_w.bgw[2].r_no_1 = 0;
            }
        } else {
            end_800_0000();
            end_801_0000();
            end_802_0000();
        }
    case END1_DONE:
        end_scn_pos_set2();
        end_bg_pos_hosei2();
        end_fam_set2();
        break;
    }
}



void end_800_0000(void) {
    bgw_ptr = &bg_w.bgw[0];
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[0].disp.pos = end_8_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_8_pos[end_w.r_no_2][1];
        switch (end_w.r_no_2) {
        case 0:
            Bg_On_W(1);
            effect_E6_init(18);
            effect_E6_init(19);
            effect_E6_init(20);
            effect_E6_init(21);
            Rewrite_End_Message(1);
            break;
        case 1:
            effect_E6_init(22);
            Rewrite_End_Message(2);
            effect_F2_init(0);
            break;
        case 2:
            effect_F2_init(0);
            Rewrite_End_Message(3);
            break;
        case 3:
            end_fade_flag = 1;
            end_fade_timer = timer_8_tbl[3] - 120;
            Rewrite_End_Message(0);
            break;
        }
        break;
    case 1:
        break;
    }
}



void end_801_0000(void) {
    bgw_ptr = &bg_w.bgw[1];
    if (end_w.r_no_2 != 2) {
        switch (bgw_ptr->r_no_1) {
        case 0:
            bgw_ptr->r_no_1++;
            bgw_ptr->xy[0].disp.pos = end_8_pos[end_w.r_no_2][0];
            bgw_ptr->xy[1].disp.pos = end_8_pos[end_w.r_no_2][1];
            if (end_w.r_no_2 == 0) {
                Bg_On_W(2);
            }
            break;
        case 1:
            break;
        }
    } else {
        switch (bgw_ptr->r_no_1) {
        case 0:
            bgw_ptr->r_no_1++;
            bgw_ptr->xy[0].disp.pos = 0x198;
            bgw_ptr->xy[1].disp.pos = 0x200;
            bgw_ptr->speed_x = -0x8000;
            break;
        case 1:
            bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
            break;
        }
    }
}



void end_802_0000(void) {
    if (end_w.r_no_2 == 3) {
        bgw_ptr = &bg_w.bgw[2];
        switch (bgw_ptr->r_no_1) {
        case 0:
            bgw_ptr->r_no_1++;
            bgw_ptr->xy[0].disp.pos = end_8_pos[end_w.r_no_2][0];
            bgw_ptr->xy[1].disp.pos = end_8_pos[end_w.r_no_2][1];
            Bg_On_W(4);
            break;
        case 1:
            break;
        }
    }
}



void end_800_cell_set(void) {
    s16 i;
    s16 j;
    const PANEL* p;
    for (j = 0; j < 2; j++) {
        p = end_8_panel_p[j];
        for (i = 0; i < 8; i++, p++) {
            bg_cell_write(j, p->ofs, p->cell, (u32)end_scrn_data, 0, 0x220);
        }
    }
    bg_cell_write_xyflip(1, 0x1080, 95, (u32)end_scrn_data, 0, 0x220);
    bg_cell_write_xyflip(1, 0x10C0, 94, (u32)end_scrn_data, 0, 0x220);
    bg_w.bgw[1].r_limit = 89;
    end_bg_block_attr_add(1, 0, 32, 0x1800, 16);
    bg_cell_write(2, 0x3080, 46, (u32)end_scrn_data, 0, 0x220);
    bg_cell_write(2, 0x30C0, 47, (u32)end_scrn_data, 0, 0x220);
    bg_w.bgw[2].r_limit = 89;
    end_bg_block_attr_add(2, 64, 32, 0x1800, 16);
}
