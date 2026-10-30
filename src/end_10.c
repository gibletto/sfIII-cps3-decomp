/*
 * END_10.C  Ending 10 (end_10000)
 *
 * end_10000(pl_num) is the ending script: it runs the common ending inits, writes the BG cells
 * (end_1000_cell_set, from end_scrn_data) and requests music 24; then it counts down timer_10_tbl
 * through seven scenes, running the scene's handler from end_10_jp for BG0 and again for BG1 each
 * frame, and after the last scene hands over to the staff roll (music 27). The handlers end_1000_0000 to
 * end_1000_6000 place the layers and show the ending messages; the last scene starts the fade.
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
#include "end_10.h"



extern const s16 end_10_anm_tbl[5];
extern void (*end_10_jp[7])();
extern const PANEL* end_10_panel_p[2];



void end_10000(u16 pl_num) {
    switch (end_w.r_no_1) {
    case END1_INIT:
        end_w.r_no_1++;
        end_w.r_no_2 = 0;
        common_end_init00(pl_num);
        common_end_init01();
        end_1000_cell_set();
        BGM_Request(24);
        end_w.timer = timer_10_tbl[end_w.r_no_2];
        break;
    case END1_SCENES:
        end_w.timer--;
        if (end_w.timer < 0) {
            end_w.r_no_2++;
            if (end_w.r_no_2 == 7) {
                end_w.r_no_1++;
                end_w.end_flag = 1;
                BGM_Request(27);
                fadeout_to_staff_roll();
            } else {
                end_w.timer = timer_10_tbl[end_w.r_no_2];
            }
            bg_w.bgw[0].r_no_1 = 0;
            bg_w.bgw[1].r_no_1 = 0;
        } else {
            bgw_ptr = &bg_w.bgw[0];
            end_10_jp[end_w.r_no_2]();
            bgw_ptr = &bg_w.bgw[1];
            end_10_jp[end_w.r_no_2]();
        }
    case END1_DONE:
        end_scn_pos_set2();
        end_bg_pos_hosei2();
        end_fam_set2();
        break;
    }
}



void end_1000_0000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        Bg_On_W(1 << bgw_ptr->fam_no);
        bgw_ptr->xy[0].disp.pos = (*(end_w.r_no_2 + end_10_pos))[0];
        bgw_ptr->xy[1].disp.pos = end_10_pos[end_w.r_no_2][1];
        Rewrite_End_Message(1);
        break;
    case 1:
        break;
    }
}



void end_1000_1000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[0].disp.pos = end_10_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_10_pos[end_w.r_no_2][1];
        if (bgw_ptr->fam_no == 0) {
            bgw_ptr->free = 2;
            bgw_ptr->l_limit = 0;
            Rewrite_End_Message(0);
        } else {
            Bg_Off_W(2);
        }
        break;
    case 1:
        if (bgw_ptr->fam_no == 0) {
            bgw_ptr->free--;
            if (bgw_ptr->free < 0) {
                bgw_ptr->free = 2;
                bgw_ptr->l_limit++;
                bgw_ptr->l_limit &= 3;
                bgw_ptr->r_limit = end_10_anm_tbl[bgw_ptr->l_limit];
                end_bg_block_attr_add(0, 64, 32, 0, 16);
            }
        }
        break;
    }
}



void end_1000_2000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if (bgw_ptr->fam_no == 1) {
            bgw_ptr->free = 10;
            bgw_ptr->r_limit = 6;
            Bg_On_W(2);
        } else {
            Rewrite_End_Message(2);
        }
        bgw_ptr->xy[0].disp.pos = end_10_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_10_pos[end_w.r_no_2][1];
        break;
    case 1:
        if (bgw_ptr->fam_no == 1) {
            bgw_ptr->free--;
            if (bgw_ptr->free < 0) {
                bgw_ptr->free = 10;
                bgw_ptr->r_limit++;
                if (bgw_ptr->r_limit < 11) {
                    end_bg_block_attr_add(1, 0x800, 32, 0, 16);
                } else {
                    bgw_ptr->r_no_1++;
                }
            }
        }
        break;
    case 2:
        break;
    }
}




void end_1000_3000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[0].disp.pos = end_10_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_10_pos[end_w.r_no_2][1];
        if (bgw_ptr->fam_no) {
            bgw_ptr->speed_x = -0x1000;
        } else {
            bgw_ptr->speed_x = 0x2000;
            Rewrite_End_Message(3);
        }
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        break;
    case 2:
        break;
    }
}



void end_1000_4000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[0].disp.pos = end_10_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_10_pos[end_w.r_no_2][1];
        if (bgw_ptr->fam_no == 0) {
            Rewrite_End_Message(0);
        }
        bgw_ptr->speed_y = -0x6000;
        break;
    case 1:
        if (bgw_ptr->xy[1].disp.pos > 0x80) {
            bgw_ptr->xy[1].cal += bgw_ptr->speed_y;
        }
        break;
    case 2:
        break;
    }
}



void end_1000_5000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[1].disp.pos = end_10_pos[end_w.r_no_2][1];
        if (bgw_ptr->fam_no == 0) {
            Rewrite_End_Message(5);
            bgw_ptr->xy[0].disp.pos = 0x2A0;
            bgw_ptr->speed_x = 0x3000;
        } else {
            bgw_ptr->xy[0].disp.pos = 0x2D0;
            bgw_ptr->speed_x = -0x1000;
        }
        break;
    case 1:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        break;
    case 2:
        break;
    }
}



void end_1000_6000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[0].disp.pos = end_10_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_10_pos[end_w.r_no_2][1];
        if (bgw_ptr->fam_no == 0) {
            Rewrite_End_Message(6);
            end_fade_flag = 1;
            end_fade_timer = timer_10_tbl[7] - 120;
        }
        break;
    case 1:
        break;
    }
}



void end_1000_cell_set(void) {
    s16 i;
    s16 j;
    const PANEL* p;
    for (j = 0; j < 2; j++) {
        p = end_10_panel_p[j];
        for (i = 0; i < 16; i++, p++) {
            bg_cell_write(j, p->ofs, p->cell, (u32)end_scrn_data, 0, 0x220);
        }
    }
}
