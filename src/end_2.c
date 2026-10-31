/*
 * END_2.C  Ending 2 (end_02000)
 *
 * end_02000(pl_num) is the ending script: it runs the common ending inits, loads the ending graphics,
 * writes the first BG0 and BG1 cells, starts three effect H5 objects and issues sound 25; then it counts
 * down timer_2_tbl through four scenes, running the BG0 handler (end_200_move) and the BG1 handler
 * (end_201_move) each frame, and after the last scene hands over to the staff roll.
 * In scenes 0 and 3 both layers scroll left; in scene 3 the cells of BG0 and BG1 are rewritten in turn
 * (end_2_bg0_step, end_2_bg1_step) for a tile animation. end_202_0000 and end_200_cell_set are not called.
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
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "end_main.h"
#include "effh5.h"
#include "textsound_2.h"
#include "aboutspr.h"
#include "end_2.h"
void bg_cell_write(s16 bg, s32 ofs, s32 cell, u32 src, u16 u5, s16 attr);
void bg_cell_write_xyflip(u16 bg, s32 ofs, s32 cell, u32 src, s32 u5, s16 attr);



extern s32 end_2_bg0_step;
extern s32 end_2_bg1_step;
extern s32 end_2_timer;

#pragma inline(end_200_move, end_201_move)



void end_02000(u16 pl_num) {
    switch (end_w.r_no_1) {
    case END1_INIT:
        end_w.r_no_1++;
        end_w.r_no_2 = 0;
        common_end_init00(pl_num);
        load_char_gfx(0x7458, 1);
        end_w.timer = timer_2_tbl[end_w.r_no_2];
        common_end_init01();
        bg_cell_write(0, 0, 4, (u32)end_200_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x40, 5, (u32)end_200_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x80, 6, (u32)end_200_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x1000, 8, (u32)end_200_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x1040, 9, (u32)end_200_scrn_data, 0, 0x220);
        bg_cell_write(1, 0, 1, (u32)end_200_scrn_data, 0, 0x220);
        bg_cell_write(1, 0x40, 2, (u32)end_200_scrn_data, 0, 0x220);
        bg_cell_write(1, 0x80, 3, (u32)end_200_scrn_data, 0, 0x220);
        effect_H5_init(0);
        effect_H5_init(1);
        effect_H5_init(2);
        sound_request(25);
        break;
    case END1_SCENES:
        end_w.timer = end_w.timer - 1;
        if (end_w.timer < 0) {
            end_w.r_no_2 = end_w.r_no_2 + 1;
            if (end_w.r_no_2 == 4) {
                end_w.r_no_1++;
                end_w.end_flag = 1;
                fadeout_to_staff_roll();
            } else {
                end_w.timer = timer_2_tbl[end_w.r_no_2];
            }
            bg_w.bgw[0].r_no_1 = 0;
            bg_w.bgw[1].r_no_1 = 0;
        } else {
            end_200_move();
            end_201_move();
        }
        end_scn_pos_set2();
        end_bg_pos_hosei2();
        end_fam_set2();
        break;
    case END1_DONE:
        break;
    }
}



void end_200_move(void) {
    void (*end_200_jp[4])() = { end_200_0000, end_200_1000, end_200_2000, end_200_3000 };
    end_200_jp[end_w.r_no_2]();
}



void end_200_0000(void) {
    s32 pos;

    bgw_ptr = &bg_w.bgw[0];
    switch (bgw_ptr->r_no_1) {
    case 0:
        Bg_On_W(1);
        bgw_ptr->r_no_1++;
        bgw_ptr->abs_x = 0x200;
        bgw_ptr->abs_y = 0;
        bgw_ptr->xy[0].disp.pos = 0x200;
        bgw_ptr->xy[1].disp.pos = 0x300;
        bgw_ptr->speed_x = -0x10000;
        Rewrite_End_Message(1);
        break;
    case 1:
        bgw_ptr->r_no_1++;
        break;
    case 2:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        bgw_ptr->abs_x = bgw_ptr->xy[0].disp.pos;
        pos = bgw_ptr->xy[0].disp.pos;
        if (pos <= 0x1A0) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 3:
        break;
    }
}



void end_200_1000(void) {
    bgw_ptr = &bg_w.bgw[0];
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->abs_x = 0x200;
        bgw_ptr->xy[0].disp.pos = 0xC0;
        bgw_ptr->xy[1].disp.pos = 0x200;
        effect_H5_init(3);
        effect_H5_init(4);
        effect_H5_init(5);
        Rewrite_End_Message(2);
        end_fade_flag = 1;
        end_fade_timer = timer_2_tbl[1] - 120;
        break;
    case 1:
        break;
    }
}



void end_200_2000(void) {
    bgw_ptr = &bg_w.bgw[0];
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->abs_x = 0x200;
        bgw_ptr->xy[0].disp.pos = 0x1A0;
        bgw_ptr->xy[1].disp.pos = 0x300;
        effect_H5_init(6);
        effect_H5_init(7);
        effect_H5_init(8);
        sound_request(23);
        break;
    case 1:
        break;
    }
}



void end_200_3000(void) {
    s32 work;

    bgw_ptr = &bg_w.bgw[0];
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[0].disp.pos = 10;
        bgw_ptr->xy[1].disp.pos = 0x300;
        bgw_ptr->abs_x = bgw_ptr->xy[0].disp.pos;
        bgw_ptr->speed_x = 0xA0000;
        bg_cell_write(0, 0, 13, (u32)end_200_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x40, 14, (u32)end_200_scrn_data, 0, 0x220);
        bg_cell_write(0, 0x80, 15, (u32)end_200_scrn_data, 0, 0x220);
        bg_cell_write(0, 0xC0, 15, (u32)end_200_scrn_data, 0, 0x220);
        end_2_bg0_step = 8;
        end_2_timer = 420;
        effect_H5_init(9);
        effect_H5_init(10);
        Rewrite_End_Message(3);
        break;
    case 1:
        end_2_timer--;
        if (end_2_timer < 0) {
            bgw_ptr->r_no_1++;
            Rewrite_End_Message(4);
        }
        break;
    case 2:
        bgw_ptr->abs_x = bgw_ptr->xy[0].disp.pos;
        work = bgw_ptr->xy[0].disp.pos;
        work = work & 0x200;
        if (work == 0x200) {
            bgw_ptr->r_no_1++;
        }
        /* fall through */
    case 3:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        work = bgw_ptr->xy[0].disp.pos;
        work &= 0xFF;
        if (work < 10) {
            work = end_2_bg0_step;
            end_2_bg0_step = work + 1;
            switch (work) {
            case 0:
                bg_cell_write(0, 0, 14, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 1:
                bg_cell_write(0, 0x40, 15, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 2:
                bg_cell_write(0, 0x80, 15, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 3:
                bg_cell_write(0, 0xC0, 15, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 4:
                bg_cell_write(0, 0, 14, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 5:
                bg_cell_write(0, 0x40, 0, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 6:
                bg_cell_write(0, 0x80, 0, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 7:
                bg_cell_write(0, 0xC0, 0, (u32)end_200_scrn_data, 0, 0x220);
                end_2_bg0_step = 0;
                break;
            case 8:
                bg_cell_write(0, 0xC0, 15, (u32)end_200_scrn_data, 0, 0x220);
                end_2_bg0_step = 0;
                break;
            }
        }
        break;
    }
}



void end_201_move(void) {
    void (*end_201_jp[4])() = { end_201_0000, end_X_com01, end_201_2000, end_201_3000 };
    end_201_jp[end_w.r_no_2]();
}



void end_201_0000(void) {
    s32 pos;

    bgw_ptr = &bg_w.bgw[1];
    switch (bgw_ptr->r_no_1) {
    case 0:
        Bg_On_W(2);
        bgw_ptr->r_no_1++;
        bgw_ptr->abs_x = 0x200;
        bgw_ptr->abs_y = 0;
        bgw_ptr->xy[0].disp.pos = 0x200;
        bgw_ptr->xy[1].disp.pos = 0x300;
        bgw_ptr->speed_x = -0x10000;
        break;
    case 1:
        bgw_ptr->r_no_1++;
        break;
    case 2:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        pos = bgw_ptr->xy[0].disp.pos;
        if (pos <= 0x1A0) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 3:
        break;
    }
}



void end_201_2000(void) {
    bgw_ptr = &bg_w.bgw[1];
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[0].disp.pos = 0x1A0;
        bgw_ptr->xy[1].disp.pos = 0x300;
        break;
    case 1:
        break;
    }
}



void end_201_3000(void) {
    s32 work;

    bgw_ptr = &bg_w.bgw[1];
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->abs_x = 0x200;
        bgw_ptr->xy[0].disp.pos = 0xC0;
        bgw_ptr->xy[1].disp.pos = 0x200;
        bgw_ptr->speed_x = 0x10000;
        bg_cell_write(1, 0x1000, 10, (u32)end_200_scrn_data, 0, 0x220);
        bg_cell_write(1, 0x1040, 11, (u32)end_200_scrn_data, 0, 0x220);
        bg_cell_write(1, 0x1080, 12, (u32)end_200_scrn_data, 0, 0x220);
        bg_cell_write(1, 0x10C0, 10, (u32)end_200_scrn_data, 0, 0x220);
        end_2_bg1_step = 3;
        break;
    case 1:
        if (bg_w.bgw[0].r_no_1 == 2) {
            bgw_ptr->r_no_1++;
        }
        break;
    case 2:
        bgw_ptr->xy[0].cal += bgw_ptr->speed_x;
        work = bgw_ptr->xy[0].disp.pos;
        work &= 0xFF;
        if (work == 0) {
            work = end_2_bg1_step;
            end_2_bg1_step++;
            switch (work) {
            case 0:
                bg_cell_write(1, 0x1000, 10, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 1:
                bg_cell_write(1, 0x1040, 11, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 2:
                bg_cell_write(1, 0x1080, 12, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 3:
                bg_cell_write(1, 0x10C0, 10, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 4:
                bg_cell_write(1, 0x1000, 11, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 5:
                bg_cell_write(1, 0x1040, 12, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 6:
                bg_cell_write(1, 0x1080, 10, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 7:
                bg_cell_write(1, 0x10C0, 11, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 8:
                bg_cell_write(1, 0x1000, 12, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 9:
                bg_cell_write(1, 0x1040, 10, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 10:
                bg_cell_write(1, 0x1080, 11, (u32)end_200_scrn_data, 0, 0x220);
                break;
            case 11:
                bg_cell_write(1, 0x10C0, 12, (u32)end_200_scrn_data, 0, 0x220);
                end_2_bg1_step = 0;
                break;
            }
        }
        break;
    }
}



void end_202_0000(void) {
    bgw_ptr = &bg_w.bgw[2];
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->abs_x = bgw_ptr->xy[0].disp.pos = 0x200;
        bgw_ptr->abs_y = bgw_ptr->xy[1].disp.pos = 0;
        /* fall through */
    case 1:
        end_scn_pos_set(2);
        end_bg_pos_hosei(2);
        end_fam_set(2);
        break;
    }
}



void end_200_cell_set(void) {
    s16 i;
    const PANEL* p;
    for (p = end_200_panel0, i = 0; i < 8; i++, p++) {
        bg_cell_write(0, p->ofs, p->cell, (u32)end_200_scrn_data, 0, 0x220);
    }
    bg_cell_write(0, 0x2000, 9, (u32)end_200_scrn_data, 0, 0x220);
    bg_cell_write_xyflip(0, 0x2040, 9, (u32)end_200_scrn_data, 0, 0x220);
    bg_cell_write(0, 0x2080, 9, (u32)end_200_scrn_data, 0, 0x220);
    bg_cell_write_xyflip(0, 0x20C0, 9, (u32)end_200_scrn_data, 0, 0x220);
    bg_cell_write(1, 0, 1, (u32)end_200_scrn_data, 0, 0x220);
    bg_cell_write(1, 0x40, 2, (u32)end_200_scrn_data, 0, 0x220);
    bg_cell_write(1, 0x80, 1, (u32)end_200_scrn_data, 0, 0x220);
    bg_cell_write(1, 0xC0, 2, (u32)end_200_scrn_data, 0, 0x220);
}
