/*
 * END_4.C  Ending 4 (end_04000)
 *
 * end_04000(pl_num) is the ending script: it runs the common ending inits, loads the ending graphics,
 * writes the BG0 and BG1 cells (end_400_cell_set, from end_scrn_data) and requests music 22; then it
 * counts down timer_4_tbl through five scenes, running the BG0 handler (end_400_move) and the BG1
 * handler (end_401_move) each frame, and after the last scene hands over to the staff roll. Each scene
 * places the layers, starts its effect E6 objects and shows its ending message: scene 2 starts the
 * fade, scene 3 changes the music to 23, and scene 4's message waits for end_etc_flag from its effect.
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
#include "end_4.h"



extern const PANEL* end_4_panel_p[2];



void end_04000(u16 pl_num) {
    switch (end_w.r_no_1) {
    case END1_INIT:
        end_w.r_no_1++;
        end_w.r_no_2 = 0;
        common_end_init00(pl_num);
        common_end_init01();
        end_w.timer = timer_4_tbl[end_w.r_no_2];
        load_char_gfx(0x7518, 1);
        end_400_cell_set();
        BGM_Request(22);
        break;
    case END1_SCENES:
        end_w.timer--;
        if (end_w.timer < 0) {
            end_w.r_no_2++;
            if (end_w.r_no_2 == 5) {
                end_w.r_no_1++;
                end_w.end_flag = 1;
                fadeout_to_staff_roll();
            } else {
                end_w.timer = timer_4_tbl[end_w.r_no_2];
            }
            bg_w.bgw[0].r_no_1 = 0;
            bg_w.bgw[1].r_no_1 = 0;
        } else {
            end_400_move();
            end_401_move();
        }
        /* fall through */
    case END1_DONE:
        end_scn_pos_set2();
        end_bg_pos_hosei2();
        end_fam_set2();
        break;
    }
}



void end_400_move(void) {
    void (*end_400_jp[5])() = { end_400_0000, end_400_1000, end_400_0000, end_400_3000, end_400_4000 };
    bgw_ptr = &bg_w.bgw[0];
    end_400_jp[end_w.r_no_2]();
}



void end_400_1000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        effect_E6_init(31);
        Rewrite_End_Message(2);
        bgw_ptr->xy[0].disp.pos = end_4_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_4_pos[end_w.r_no_2][1];
        bgw_ptr->speed_x = 0x10000;
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        bgw_ptr->abs_x = bgw_ptr->xy[0].disp.pos;
        if (bgw_ptr->xy[0].disp.pos > 0x1B0) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 2:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        if (bgw_ptr->xy[0].disp.pos > 0x300) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 3:
        break;
    }
}



void end_400_3000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        Bg_On_W(1 << bgw_ptr->fam_no);
        bgw_ptr->abs_x = 0x200;
        bgw_ptr->abs_y = 0;
        bgw_ptr->xy[0].disp.pos = end_4_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_4_pos[end_w.r_no_2][1];
        BGM_Request(23);
        Rewrite_End_Message(4);
        effect_E6_init(30);
        effect_E6_init(32);
        bgw_ptr->r_limit = 20;
        break;
    case 1:
        bgw_ptr->r_limit--;
        if (bgw_ptr->r_limit < 0) {
            bgw_ptr->r_no_1++;
            bgw_ptr->r_limit = 50;
            effect_E6_init(68);
        }
        break;
    case 2:
        bgw_ptr->r_limit--;
        if (bgw_ptr->r_limit < 0) {
            bgw_ptr->r_no_1++;
            effect_E6_init(32);
        }
        break;
    case 3:
        break;
    }
}



void end_400_4000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        end_etc_flag = 0;
        effect_E6_init(33);
        break;
    case 1:
        if (end_etc_flag == 1) {
            Rewrite_End_Message(5);
            end_etc_flag = 0;
            bgw_ptr->r_no_1++;
        }
        break;
    case 2:
        break;
    }
}



void end_401_move(void) {
    void (*end_401_jp[5])() = { end_400_0000, end_400_0000, end_400_0000, end_X_com01, end_X_com01 };
    bgw_ptr = &bg_w.bgw[1];
    end_401_jp[end_w.r_no_2]();
}



void end_400_0000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        Bg_On_W(1 << bgw_ptr->fam_no);
        bgw_ptr->abs_x = 0x200;
        bgw_ptr->abs_y = 0;
        bgw_ptr->xy[0].disp.pos = end_4_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_4_pos[end_w.r_no_2][1];
        if (bgw_ptr->fam_no == 0) {
            switch (end_w.r_no_2) {
            case 0:
                Rewrite_End_Message(1);
                break;
            case 2:
                effect_E6_init(29);
                Rewrite_End_Message(3);
                end_fade_flag = 1;
                end_fade_timer = timer_4_tbl[2] - 120;
                break;
            }
        }
        break;
    case 1:
        break;
    }
}



void end_400_cell_set(void) {
    s16 i;
    s16 j;
    const PANEL* p;
    for (j = 0; j < 2; j++) {
        p = end_4_panel_p[j];
        for (i = 0; i < 10; i++, p++) {
            bg_cell_write(j, p->ofs, p->cell, (u32)end_scrn_data, 0, 0x220);
        }
    }
}
