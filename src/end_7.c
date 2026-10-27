/*
 * END_7.C  Ending 7 (end_07000)
 *
 * end_07000(pl_num) is the ending script: it runs the common ending inits, loads the ending graphics,
 * writes the BG cells (end_700_cell_set, from end_scrn_data) and requests music 22; then it counts down
 * timer_7_tbl through twelve scenes, running the BG0 handler (end_700_move) and the BG1 handler
 * (end_701_move) each frame, and after the last scene hands over to the staff roll (music 27).
 * end_700_0000 places a layer for its scene, starts the scene's effect E6 objects, shows the ending
 * messages, changes the music to 26 and starts the fades; end_700_5000 and end_701_7000 run the scenes
 * with their own timed effects.
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
#include "end_7.h"



extern const s16 end_7_anm_tbl[8];
extern const PANEL end_700_panel0[16];
extern const PANEL end_700_panel1[14];
extern const u32 end_scrn_data[];



void end_07000(u16 pl_num) {
    switch (end_w.r_no_1) {
    case END1_INIT:
        end_w.r_no_1++;
        end_w.r_no_2 = 0;
        common_end_init00(pl_num);
        load_char_gfx(0x75E8, 1);
        end_w.timer = timer_7_tbl[end_w.r_no_2];
        common_end_init01();
        end_700_cell_set();
        bgm_request(22);
        break;
    case END1_SCENES:
        end_w.timer--;
        if (end_w.timer < 0) {
            end_w.r_no_2++;
            if (end_w.r_no_2 == 12) {
                end_w.r_no_1++;
                end_w.end_flag = 1;
                fadeout_to_staff_roll();
                bgm_request(27);
            } else {
                end_w.timer = timer_7_tbl[end_w.r_no_2];
            }
            bg_w.bgw[0].r_no_1 = 0;
            bg_w.bgw[1].r_no_1 = 0;
        } else {
            end_700_move();
            end_701_move();
        }
    case END1_DONE:
        end_scn_pos_set2();
        end_bg_pos_hosei2();
        end_fam_set2();
        break;
    }
}



void end_700_move(void) {
    void (*end_700_jp[12])() = { end_700_0000, end_700_0000, end_700_0000, end_700_0000, end_X_com01, end_700_5000, end_700_0000, end_X_com01, end_X_com01, end_700_0000, end_700_0000, end_700_0000 };
    bgw_ptr = &bg_w.bgw[0];
    end_700_jp[end_w.r_no_2]();
}



void end_701_move(void) {
    void (*end_701_jp[12])() = { end_X_com01, end_700_0000, end_700_0000, end_700_0000, end_700_0000, end_700_0000, end_X_com01, end_701_7000, end_701_7000, end_700_0000, end_700_0000, end_X_com01 };
    bgw_ptr = &bg_w.bgw[1];
    end_701_jp[end_w.r_no_2]();
}



void end_700_0000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
            Bg_On_W(1 << bgw_ptr->fam_no);
        }
        bgw_ptr->xy[0].disp.pos = end_7_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_7_pos[end_w.r_no_2][1];
        if (bgw_ptr->fam_no == 0) {
            switch (end_w.r_no_2) {
            case 0:
                effect_E6_init(39);
                break;
            case 1:
                effect_E6_init(40);
                break;
            case 2:
                Rewrite_End_Message(2);
                end_fade_flag = 1;
                end_fade_timer = timer_7_tbl[2] - 120;
                break;
            case 3:
                bgm_request(26);
                effect_E6_init(41);
                effect_E6_init(42);
                Rewrite_End_Message(0);
                break;
            case 6:
                effect_E6_init(45);
                Rewrite_End_Message(7);
                break;
            case 9:
                Rewrite_End_Message(9);
                break;
            case 10:
                Rewrite_End_Message(10);
                break;
            case 11:
                end_fade_flag = 1;
                end_fade_timer = timer_7_tbl[11] - 120;
                break;
            }
        }
        break;
    case 1:
        break;
    }
}



void end_700_5000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
            Bg_On_W(1 << bgw_ptr->fam_no);
        }
        bgw_ptr->xy[0].disp.pos = end_7_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_7_pos[end_w.r_no_2][1];
        effect_E6_init(44);
        Rewrite_End_Message(6);
        bgw_ptr->l_limit = 30;
        break;
    case 1:
        bgw_ptr->l_limit--;
        if (bgw_ptr->l_limit < 0) {
            effect_E6_init(43);
            bgw_ptr->r_no_1++;
        }
        break;
    case 2:
        break;
    }
}



void end_701_7000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if (end_w.r_no_2 == 7) {
            if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
                Bg_On_W(1 << bgw_ptr->fam_no);
            }
            bgw_ptr->xy[0].disp.pos = end_7_pos[end_w.r_no_2][0];
            bgw_ptr->xy[1].disp.pos = end_7_pos[end_w.r_no_2][1];
            bgw_ptr->free = 2;
            bgw_ptr->l_limit = 0;
            effect_E6_init(46);
            Rewrite_End_Message(0);
        }
        break;
    case 1:
        bgw_ptr->free--;
        if (bgw_ptr->free < 0) {
            bgw_ptr->free = 2;
            bgw_ptr->l_limit++;
            bgw_ptr->l_limit &= 7;
            bgw_ptr->r_limit = end_7_anm_tbl[bgw_ptr->l_limit];
            end_bg_block_attr_add(1, 0, 32, 0x1000, 16);
        }
        break;
    }
}



void end_700_cell_set(void) {
    s16 i;
    const PANEL* p;
    p = end_700_panel0;
    for (i = 0; i < 16; i++, p++) {
        bg_cell_write(0, p->ofs, p->cell, (u32)end_scrn_data, 0, 0x220);
    }
    p = end_700_panel1;
    for (i = 0; i < 14; i++, p++) {
        bg_cell_write(1, p->ofs, p->cell, (u32)end_scrn_data, 0, 0x220);
    }
    bg_w.bgw[0].r_limit = 65;
    end_bg_block_attr_add(0, 0, 32, 0x1000, 16);
}
