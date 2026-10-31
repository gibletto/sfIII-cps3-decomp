/*
 * END_5.C  Ending 5 (end_05000)
 *
 * end_05000(pl_num) is the ending script: it runs the common ending inits, loads the ending graphics
 * and colours, writes the BG cells (end_500_cell_set) and requests music 22, and fades in (fade 53);
 * then it counts down timer_5_tbl through six scenes, running the BG0 handler (end_500_move) and the
 * BG1 handler (end_501_move) each frame, and after the last scene hands over to the staff roll. Each
 * scene places the layers, starts its effect E6 objects and shows its ending message; scene 3 waits
 * for end_etc_flag from its effect, scene 4 starts the fade and scene 5 changes the music to 23.
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
#include "end_5.h"

/* end_w.r_no_1 in end_05000 */
#define E5_INIT         0       /* set up the ending */
#define E5_FADE         1       /* request the fade */
#define E5_FADE_WAIT    2       /* until the fade is done */
#define E5_SCENES       3       /* each scene for its timer, then the staff roll */
#define E5_DONE         4       /* hold the last screen */







void end_05000(u16 pl_num) {
    switch (end_w.r_no_1) {
    case E5_INIT:
        end_w.r_no_1++;
        end_w.r_no_2 = 0;
        common_end_init00(pl_num);
        load_char_gfx(0x7668, 1);
        end_w.timer = timer_5_tbl[end_w.r_no_2];
        common_end_init01();
        end_500_cell_set();
        load_any_color(0x91);
        BGM_Request(22);
        break;
    case E5_FADE:
        if (Request_Fade(53, 0) == 0) {
            break;
        }
        end_w.r_no_1++;
        break;
    case E5_FADE_WAIT:
        if (end_fade_complete() == 0) {
            break;
        }
        end_w.r_no_1++;
    case E5_SCENES:
        end_w.timer--;
        if (end_w.timer < 0) {
            end_w.r_no_2++;
            if (end_w.r_no_2 == 6) {
                end_w.r_no_1++;
                end_w.end_flag = 1;
                fadeout_to_staff_roll();
            } else {
                end_w.timer = timer_5_tbl[end_w.r_no_2];
            }
            bg_w.bgw[0].r_no_1 = 0;
            bg_w.bgw[1].r_no_1 = 0;
        } else {
            end_500_move();
            end_501_move();
        }
    case E5_DONE:
        end_scn_pos_set2();
        end_bg_pos_hosei2();
        end_fam_set2();
        break;
    }
}



void end_500_move(void) {
    void (*end_500_jp[6])() = { end_500_0000, end_500_1000, end_500_2000, end_500_3000, end_500_4000, end_500_5000 };
    bgw_ptr = &bg_w.bgw[0];
    end_500_jp[end_w.r_no_2]();
}



/* The background steps of end_500_1000: frames to wait, then the value it keeps in r_limit. */
const s16 end_5_anm_tbl[4][2] = {
    { 240, 21 }, { 8, 22 }, { 8, 23 }, { 8, 24 },
};



void end_500_1000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
            Bg_On_W(1 << bgw_ptr->fam_no);
        }
        bgw_ptr->xy[0].disp.pos = end_5_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_5_pos[end_w.r_no_2][1];
        Rewrite_End_Message(2);
        effect_E6_init(60);
        effect_E6_init(61);
        bgw_ptr->free = 90;
        break;
    case 1:
        bgw_ptr->free--;
        if (bgw_ptr->free < 0) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 2:
        bgw_ptr->r_no_1++;
        bgw_ptr->free = end_5_anm_tbl[0][0];
        bgw_ptr->l_limit = 0;
    case 3:
        bgw_ptr->free--;
        if (bgw_ptr->free < 0) {
            bgw_ptr->l_limit++;
            if (bgw_ptr->l_limit == 3) {
                bgw_ptr->r_no_1++;
            }
            bgw_ptr->free = end_5_anm_tbl[bgw_ptr->l_limit][0];
            bgw_ptr->r_limit = end_5_anm_tbl[bgw_ptr->l_limit][1];
            end_bg_block_attr_add(0, 64, 32, 0, 16);
        }
        break;
    case 4:
        break;
    }
}



void end_500_2000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        Rewrite_End_Message(3);
        effect_E6_init(64);
        bgw_ptr->xy[0].disp.pos = end_5_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_5_pos[end_w.r_no_2][1];
        break;
    case 1:
        if (Request_Fade(52, 0) == 0) {
            break;
        }
        bgw_ptr->r_no_1++;
        end_no_cut = 1;
        break;
    case 2:
        if (end_fade_complete()) {
            bgw_ptr->r_no_1++;
            end_no_cut = 0;
        }
        break;
    case 3:
        break;
    }
}



void end_500_3000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
            Bg_On_W(1 << bgw_ptr->fam_no);
        }
        bgw_ptr->xy[0].disp.pos = end_5_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_5_pos[end_w.r_no_2][1];
        bgw_ptr->l_limit = 500;
        Rewrite_End_Message(4);
        break;
    case 1:
        bgw_ptr->l_limit--;
        if (bgw_ptr->l_limit < 0) {
            bgw_ptr->r_no_1++;
            end_etc_flag = 0;
            effect_E6_init(62);
        }
        break;
    case 2:
        if (end_etc_flag == 0) {
            break;
        }
        if (Request_Fade(50, 0) == 0) {
            break;
        }
        end_no_cut = 1;
        bgw_ptr->r_no_1++;
    case 3:
        if (end_fade_complete()) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 4:
        break;
    }
}



void end_500_4000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        end_fade_flag = 1;
        end_fade_timer = timer_5_tbl[4] - 120;
        if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
            Bg_On_W(1 << bgw_ptr->fam_no);
        }
        bg_w.quake_y_index = 0;
        break;
    case 1:
        if (Request_Fade(49, 0) == 0) {
            break;
        }
        end_no_cut = 1;
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[0].disp.pos = end_5_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_5_pos[end_w.r_no_2][1];
        break;
    case 2:
        if (end_fade_complete()) {
            bgw_ptr->r_no_1++;
            end_no_cut = 0;
        }
        break;
    case 3:
    case 4:
        break;
    }
    bg_w.quake_y_index ^= 1;
    if (bg_w.quake_y_index) {
        bgw_ptr->xy[1].disp.pos += quake_y_tbl[11];
    } else {
        bgw_ptr->xy[1].disp.pos += quake_y_tbl[12];
    }
}



void end_500_5000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        BGM_Request(23);
        if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
            Bg_On_W(1 << bgw_ptr->fam_no);
        }
        bgw_ptr->xy[0].disp.pos = end_5_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_5_pos[end_w.r_no_2][1];
        effect_E6_init(63);
        effect_E6_init(67);
        Rewrite_End_Message(6);
        break;
    case 1:
        bgw_ptr->xy[0].cal -= 0xC0000;
        break;
    }
}



void end_501_move(void) {
    void (*end_501_jp[6])() = { end_X_com01, end_501_1000, end_501_2000, end_X_com01, end_500_0000, end_501_5000 };
    bgw_ptr = &bg_w.bgw[1];
    end_501_jp[end_w.r_no_2]();
}



void end_501_1000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
            Bg_On_W(1 << bgw_ptr->fam_no);
        }
        bgw_ptr->xy[0].disp.pos = end_5_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_5_pos[end_w.r_no_2][1];
        break;
    case 1:
        break;
    }
}



void end_501_2000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
            Bg_On_W(1 << bgw_ptr->fam_no);
        }
        bgw_ptr->xy[0].disp.pos = end_5_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_5_pos[end_w.r_no_2][1];
        break;
    case 1:
        break;
    }
}



void end_501_5000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
            Bg_On_W(1 << bgw_ptr->fam_no);
        }
        bgw_ptr->xy[0].disp.pos = end_5_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_5_pos[end_w.r_no_2][1];
        bgw_ptr->free = 4;
        bgw_ptr->r_limit = 12;
        break;
    case 1:
        bgw_ptr->free--;
        if (bgw_ptr->free < 0) {
            bgw_ptr->free = 4;
            bgw_ptr->r_limit++;
            if (bgw_ptr->r_limit < 16) {
                end_bg_block_attr_add(1, 0, 32, 0x1800, 16);
            } else {
                bgw_ptr->r_limit = 12;
            }
        }
        break;
    }
}



void end_500_0000(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        if ((scrn_reg_w[bgw_ptr->fam_no].ctrl & 0x8000) == 0) {
            Bg_On_W(1 << bgw_ptr->fam_no);
        }
        bgw_ptr->xy[0].disp.pos = end_5_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_5_pos[end_w.r_no_2][1];
        if (bgw_ptr->fam_no == 0 && end_w.r_no_2 == 0) {
            Rewrite_End_Message(1);
        }
        break;
    case 1:
        break;
    }
}



void end_500_cell_set(void) {
    s16 i;
    const PANEL* p;
    p = end_500_bg0_cell_tbl;
    for (i = 0; i < 12; i++, p++) {
        bg_cell_write(0, p->ofs, p->cell, (u32)end_500_scrn_data, 0, 0x220);
    }
    p = end_500_bg1_cell_tbl;
    for (i = 0; i < 8; i++, p++) {
        bg_cell_write(1, p->ofs, p->cell, (u32)end_500_scrn_data, 0, 0x220);
    }
    bg_cell_write(0, 0x1000, 17, (u32)end_500_scrn_data, 0, 0x202);
    bg_cell_write(0, 0x1040, 18, (u32)end_500_scrn_data, 0, 0x202);
    bg_w.bgw[1].r_limit = 10;
    end_bg_block_attr_add(1, 0, 32, 0x1000, 16);
}
