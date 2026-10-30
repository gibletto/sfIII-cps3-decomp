/*
 * BG000.C  Stage background services
 *
 * bg_initialize loads a stage: picks bg_index from stage and area, transfers its scroll graphics and
 * palette and initialises all seven layer works; bg_etc_write does the same for the special screens.
 * bg_rect_attr_preset and oh_opening_demo patch map cell attributes. The zoom routines follow the
 * players' distance and requests, the move checks scroll the base and follower layers, and
 * capcom_logo_anim steps the CAPCOM logo colours.
 *
 * The stage background subroutines are here too. Bg_Family_Set and its variants load the scroll and
 * family registers, and bg_pos_hosei_* add the screen offset and quake. The zoom routines are
 * zoom_frame_judge, zoom_ud_check and zoom_x_width_check / zoom_y_width_check; the line-scroll
 * routines are suzi_line_clear, suzi_line_calc, suzi_offset_set and suzi_sync_pos_set. The cell
 * writers are blit_*, bg_cell_write*, bg_scr_write and the akebono_* finish-screen routines. The move
 * helpers are bgw_xy_add, bgw_wxy_add, Bg_mv_tw, x_right_check / x_left_check, the base and chase
 * moves (bg_base_x_move_check, bg_chase_move) and bg_x_move_check / bg_y_move_check.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Pl.h"
#include "SYS_sub.h"
#include "fifo.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "ta_sub2.h"
#include "tate00.h"
#include "ta_sub.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
/* bg_sub.h left out */
#include "bg040.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "EFF61.h"
#include "EFF78.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "bg120.h"
#include "eff05.h"
#include "eff06.h"
#include "EFF07.h"
#include "EFF11.h"
#include "eff14.h"
#include "EFF44.h"
#include "aboutspr.h"
#include "bg000.h"
#include "fighter.h"

extern const s16 bg_zoom_rate_tbl[];
extern s16 bg_deff_type;          /* provisional name: 0201D5A4 */
/* provisional names */
extern s16 bg_zoom_d;
extern const HUD_CELL* bg_rewrite_cell_tbl_8[][4];
extern const u32 bg_clear_cell_tbl[14][3];
extern s16 bg_zoom_old_x;
void zoom_center_set(void);
void tilemap_print_string_attr(u16 x, u16 y, u16 attr, const s8* str);
/* provisional names: the frame_deff tables of bg_frame_deff_set */
extern const s16 bg_deff_l_base[21];
extern const s16 bg_deff_l2_tbl[][57];
extern const s16 bg_deff_l_tbl[][57];
extern const s16 bg_deff_r_base[21];
extern const s16 bg_deff_r_tbl[][57];



s32 polygon2d_submit_line();
s32 simmram_block_alloc_10(s32 blocks, s32 kind);
u32 simmram_big_page_alloc_40(s32 kind);
u32 simmram_slot_addr(s16 no);
u32 simmram_slot_to_offset(s16 handle);
s32 sprite_list_setup(s16 slot, s16 owner, const s16* data);
void scrn_attr_set(s16 n, u16 attr, u16 bits);
void scrn_map_set_now(u16 n, u32 p);
void scrn_map_set(u16 n, u32 p);
void bg_frame_deff_set();
#define SUZI_W  ((SUZI_CALC*)suzi_calc_w)
#define SUZI_W0 (&suzi_calc_w[0])



AKE_SCRL ake_scrl_w[3];
BG bg_w;
s16 scr_cg_c_no;
s16 ake_cg_c_no;








/* provisional name */
s32 bg_cell_offset(s16 x, s16 y) {
    return ((((0x400 - (y & 0x300) - (y & 0xF0)) & 0x3F0) << 4) + ((x & 0x3F0) >> 2)) >> 1;
}



void suzi_offset_set(WORK* wk) {
    if (wk->sync_suzi == 1) {
        suzi_offset_set_sub(wk);
    }
}



u32 suzi_offset_set_sub(WORK* wk)
{
    s16 work;
    s16 work2;
    s16 pos = wk->xyz[1].disp.pos;
    u16* adrs;

    work = pos & 0x300;
    work = 0x300 - work;
    work2 = pos & 0xFF;
    work2 = 0x100 - work2;
    work += work2;
    work += work;
    adrs = bg_w.bgw[wk->my_family - 1].suzi_adrs;
    adrs += work;
    wk->suzi_offset = adrs;
    return 0;
}



void suzi_sync_pos_set(WORK_Other* ewk) {
    s16 sub;
    if (ewk->wu.sync_suzi) {
        if (ewk->wu.sync_suzi == 2) {
            suzi_offset_set_sub((WORK*)ewk);
        }
        sub = *ewk->wu.suzi_offset;
        sub -= 0x200;
    } else {
        sub = 0;
    }
    ewk->wu.position_x = (ewk->wu.xyz[0].disp.pos - sub) & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
}



void Bg_Family_Set(void) {
    s32 i;
    s32 x;
    s32 y;
    for (i = 0; i < bg_w.scno; i++) {
        x = bg_w.bgw[i].position_x;
        y = bg_w.bgw[i].position_y;
        Scrn_Move_Set(i, x, y);
        x = -x & 0x3FF;
        y = (768 - (y & 0x3FF)) & 0x3FF;
        Family_Set_W(i + 1, x, y);
    }
}



/* provisional name */
void ake_Family_Set(void) {
    s32 pos_work_x = bg_w.bgw[3].position_x;
    s32 pos_work_y = bg_w.bgw[3].position_y;
    Scrn_Move_Set(3, pos_work_x, pos_work_y);
    pos_work_x = -pos_work_x & 0x3FF;
    pos_work_y = (768 - (pos_work_y & 0x3FF)) & 0x3FF;
    Family_Set_W(4, pos_work_x, pos_work_y);
}



void Bg_Family_Set_2(void) {
    s32 i;
    s32 a, b, x, y;
    for (i = 0; i < bg_w.scno; i++) {
        x = bg_w.bgw[i].position_x;
        y = bg_w.bgw[i].position_y;
        y += 12;
        Scrn_Move_Set(i, x, y);
        a = -x & 0x3FF;
        b = (0x300 - (y & 0x3FF)) & 0x3FF;
        Family_Set_W(i + 1, a, b);
    }
}



/* provisional name */
/* Bg_Family_Set_2 without the 12-dot drop */
void Bg_Family_Set_3(void) {
    s32 i;
    s32 a, b, x, y;
    for (i = 0; i < bg_w.scno; i++) {
        x = bg_w.bgw[i].position_x;
        y = bg_w.bgw[i].position_y;
        Scrn_Move_Set(i, x, y);
        a = -x & 0x3FF;
        b = (0x300 - (y & 0x3FF)) & 0x3FF;
        Family_Set_W(i + 1, a, b);
    }
}



/* provisional name */
s16 bg_frame_deff_get(s32 bg_no) {
    return bg_w.bgw[bg_no].frame_deff;
}



void bg_pos_hosei_sub2(s32 bg_no) {
    u16 pos;
    u16 pos2;
    s16 ofs;
    if (Game_setting.Screen_Mode) {
        ofs = 0xF8;
    } else {
        ofs = bg_w.bgw[bg_no].frame_deff;
    }
    pos2 = bg_w.bgw[bg_no].wxy[0].disp.pos;
    pos = pos2 & 0x3FF;
    pos -= ofs;
    pos &= 0x3FF;
    pos += quake_x_tbl[bg_w.quake_x_index];
    pos2 -= ofs;
    bg_w.bgw[bg_no].position_x = pos & 0x3FF;
    pos2 += quake_x_tbl[bg_w.quake_x_index];
    bg_w.bgw[bg_no].abs_x = pos2;
    pos2 = bg_w.bgw[bg_no].xy[1].disp.pos;
    pos = pos2 & 0x3FF;
    pos += quake_y_tbl[bg_w.quake_y_index];
    pos2 += quake_y_tbl[bg_w.quake_y_index];
    bg_w.bgw[bg_no].position_y = pos & 0x3FF;
    bg_w.bgw[bg_no].abs_y = pos2;
}



void bg_pos_hosei_sub3(s32 bg_no) {
    u16 pos;
    u16 pos2;
    pos2 = bg_w.bgw[bg_no].wxy[0].disp.pos;
    pos = pos2 & 0x3FF;
    pos -= bg_w.pos_offset;
    pos2 -= bg_w.pos_offset;
    pos &= 0x3FF;
    pos += quake_x_tbl[bg_w.quake_x_index];
    pos2 += quake_x_tbl[bg_w.quake_x_index];
    bg_w.bgw[bg_no].position_x = pos & 0x3FF;
    bg_w.bgw[bg_no].abs_x = pos2;
    pos2 = bg_w.bgw[bg_no].xy[1].disp.pos;
    pos = pos2 & 0x3FF;
    pos += quake_y_tbl[bg_w.quake_y_index];
    pos2 += quake_y_tbl[bg_w.quake_y_index];
    bg_w.bgw[bg_no].position_y = pos & 0x3FF;
    bg_w.bgw[bg_no].abs_y = pos2;
}



/* provisional name */
void bg_frame_deff_init(void) {
    BGW* bgw = &bg_w.bgw[1];
    if (!Game_setting.Screen_Mode) {
        bgw->frame_deff = 0xC0;
    } else {
        bgw->frame_deff = 0xF8;
    }
}



/* provisional name */
/* bg_pos_hosei2 with each layer's frame_deff in place of pos_offset */
/* provisional name */
void bg_pos_hosei_deff(void)
{
    s32 pos;
    s32 pos2;
    s16 i;

    for (i = 0; i < bg_w.scno; i++) {
        bg_frame_deff_set(i);
        if (bg_w.chase_flag & 0xF) {
            pos2 = bg_w.bgw[i].chase_xy[0].disp.pos;
        } else {
            pos2 = bg_w.bgw[i].wxy[0].disp.pos;
        }
        pos = pos2 & 0x3FF;
        pos -= bg_w.bgw[i].frame_deff;
        pos &= 0x3FF;
        pos += quake_x_tbl[bg_w.quake_x_index];
        bg_w.bgw[i].position_x = pos & 0x3FF;
        pos2 -= bg_w.bgw[i].frame_deff;
        pos2 += quake_x_tbl[bg_w.quake_x_index];
        bg_w.bgw[i].abs_x = pos2;
        if (bg_w.chase_flag & 0xF0) {
            pos2 = bg_w.bgw[i].chase_xy[1].disp.pos;
        } else {
            pos2 = bg_w.bgw[i].xy[1].disp.pos;
        }
        pos = pos2 & 0x3FF;
        pos += quake_y_tbl[bg_w.quake_y_index];
        pos2 += quake_y_tbl[bg_w.quake_y_index];
        bg_w.bgw[i].position_y = pos & 0x3FF;
        bg_w.bgw[i].abs_y = pos2;
    }
}



/* provisional name */
void bg_frame_deff_set(s16 bg_no) {
    s16 wx;
    s16 x;
    s16 d;
    s16 deff;
    if (Game_setting.Screen_Mode) {
        bg_w.bgw[bg_no].frame_deff = 56;
    } else {
        wx = bg_w.bgw[bg_no].wxy[0].disp.pos;
        x = bg_w.bgw[bg_no].xy[0].disp.pos;
        if (wx > bg_w.bgw[bg_no].pos_x_work) {
            if (bg_w.bgw[bg_no].zuubun) {
                wx += 0x200;
                x += 0x200;
            }
            d = x - wx;
            deff = bg_deff_r_tbl[bg_w.frame_vol][d];
            deff += bg_deff_r_base[bg_w.frame_vol];
            bg_w.bgw[bg_no].frame_deff = deff + 0xF8;
        } else {
            if (bg_w.bgw[bg_no].zuubun) {
                wx += 0x200;
                x += 0x200;
            }
            d = wx - x;
            if (bg_w.dmm1 == 2) {
                deff = bg_deff_l2_tbl[bg_w.frame_vol][d];
            } else {
                deff = bg_deff_l_tbl[bg_w.frame_vol][d];
            }
            deff += bg_deff_l_base[bg_w.frame_vol];
            bg_w.bgw[bg_no].frame_deff = deff + 0xF8;
        }
    }
}



void bg_pos_hosei2(void)
{
    s32 pos;
    s32 pos2;
    s16 i;
    BGW* bgw;

    for (i = 0; i < bg_w.scno; i++) {
        bgw = &bg_w.bgw[i];
        if (bg_w.chase_flag & 0xF) {
            pos2 = bgw->chase_xy[0].disp.pos;
        } else {
            pos2 = bgw->wxy[0].disp.pos;
        }
        pos = pos2 & 0x3FF;
        pos -= bg_w.pos_offset;
        pos &= 0x3FF;
        pos += quake_x_tbl[bg_w.quake_x_index];
        bg_w.bgw[i].position_x = pos & 0x3FF;
        pos2 -= bg_w.pos_offset;
        pos2 += quake_x_tbl[bg_w.quake_x_index];
        bg_w.bgw[i].abs_x = pos2;
        if (bg_w.chase_flag & 0xF0) {
            pos2 = bg_w.bgw[i].chase_xy[1].disp.pos;
        } else {
            pos2 = bg_w.bgw[i].xy[1].disp.pos;
        }
        pos = pos2 & 0x3FF;
        pos = pos + quake_y_tbl[bg_w.quake_y_index];
        pos2 = pos2 + quake_y_tbl[bg_w.quake_y_index];
        bg_w.bgw[i].position_y = pos & 0x3FF;
        bg_w.bgw[i].abs_y = pos2;
    }
}




/* provisional name */
void bg_frame_deff_set2(s16 bg_no) {
    s16 wx;
    s16 x;
    s16 d;
    s16 deff;
    s16* tbl;
    if (Game_setting.Screen_Mode) {
        bg_w.bgw[bg_no].frame_deff = -56;
    } else {
        wx = bg_w.bgw[bg_no].wxy[0].disp.pos;
        x = bg_w.bgw[bg_no].xy[0].disp.pos;
        if (wx > bg_w.bgw[bg_no].pos_x_work) {
            if (bg_w.bgw[bg_no].zuubun) {
                wx += 0x200;
                x += 0x200;
            }
            d = x - wx;
            switch (bg_deff_type) {
            case 0:
                if (d) {
                    tbl = bg_w.bgw[bg_no].deff_minus1;
                    deff = tbl[d + bg_w.frame_vol * 57];
                } else {
                    deff = 0;
                }
                break;
            case 1:
                if (d) {
                    tbl = bg_w.bgw[bg_no].deff_rl0;
                    deff = tbl[bg_w.frame_vol * 57];
                    tbl = bg_w.bgw[bg_no].deff_plus0;
                    deff += tbl[d + bg_w.frame_vol * 57];
                } else {
                    tbl = bg_w.bgw[bg_no].deff_rl0;
                    deff = tbl[bg_w.frame_vol * 57];
                }
                break;
            case 2:
                tbl = bg_w.bgw[bg_no].deff_rl1;
                deff = tbl[d + bg_w.frame_vol * 57];
                break;
            }
            bg_w.bgw[bg_no].frame_deff = deff;
        } else {
            if (bg_w.bgw[bg_no].zuubun) {
                wx += 0x200;
                x += 0x200;
            }
            d = wx - x;
            switch (bg_deff_type) {
            case 0:
                tbl = bg_w.bgw[bg_no].deff_minus0;
                deff = tbl[d + bg_w.frame_vol * 57];
                break;
            case 1:
                tbl = bg_w.bgw[bg_no].deff_rl0;
                deff = tbl[d + bg_w.frame_vol * 57];
                break;
            case 2:
                if (d) {
                    tbl = bg_w.bgw[bg_no].deff_rl1;
                    deff = tbl[bg_w.frame_vol * 57];
                    tbl = bg_w.bgw[bg_no].deff_plus1;
                    deff += tbl[d + bg_w.frame_vol * 57];
                } else {
                    tbl = bg_w.bgw[bg_no].deff_rl1;
                    deff = tbl[d + bg_w.frame_vol * 57];
                }
                break;
            }
            bg_w.bgw[bg_no].frame_deff = deff;
        }
    }
}



/* provisional name */
void bg_pos_hosei_deff2(void) {
    s32 pos;
    s32 pos2;
    s16 i;

    for (i = 0; i < bg_w.scno; i++) {
        bg_frame_deff_set2(i);
        pos2 = (&bg_w.bgw[i] + 0)->frame_deff +
               (pos = (&bg_w.bgw[i] + 0)->xy[0].disp.pos, pos);
        pos = pos2;
        pos &= 0x3FF;
        pos -= bg_w.pos_offset;
        pos &= 0x3FF;
        pos += quake_x_tbl[bg_w.quake_x_index];
        (&bg_w.bgw[i] + 0)->position_x = pos & 0x3FF;
        pos2 = pos2 - bg_w.pos_offset;
        pos2 += quake_x_tbl[bg_w.quake_x_index];
        bg_w.bgw[i].position_x = pos2;
        if (bg_w.chase_flag & 0xF0) {
            pos2 = bg_w.bgw[i].chase_xy[1].disp.pos;
        } else {
            pos2 = bg_w.bgw[i].xy[1].disp.pos;
        }
        pos = pos2 & 0x3FF;
        pos += quake_y_tbl[bg_w.quake_y_index];
        bg_w.bgw[i].position_y = pos & 0x3FF;
    }
}




/* provisional name */
s32 zoom_frame_judge(void) {
    PLW* p1;
    PLW* p2;
    s16 left;
    s16 right;
    s16 work;
    bg_w.frame_flag = 0;
    if (bg_w.bgw[1].wxy[0].disp.pos <= bg_w.bgw[1].l_limit2 ||
        bg_w.bgw[1].wxy[0].disp.pos >= bg_w.bgw[1].r_limit2) {
        return 2;
    } else {
        p1 = &plw[0];
        p2 = &plw[1];
    }
    if (p1->wu.scr_mv_x < p2->wu.scr_mv_x) {
        left = p1->wu.scr_mv_x;
        right = p2->wu.scr_mv_x;
    } else {
        left = p2->wu.scr_mv_x;
        right = p1->wu.scr_mv_x;
    }
    work = right - left;
    if (work > 368) {
        return 2;
    }
    return 1;
}



void zoom_ud_check(void) {
    s16 work;
    s16 rate;
    s16 work2;
    s16 pos_w;
    if (bg_app) {
        return;
    }
    work2 = zoom_request_flag & 0xFF;
    bg_w.frame_deff = 64 - zoom_request_level;
    work = 0xFF & (~zoom_req_flag_old & zoom_request_flag);
    if (work && !bg_w.frame_flag) {
        Zoomf_Init();
        bg_w.frame_flag = 1;
        bg_w.old_frame_flag = 1;
        bg_w.center_y = 224 - scr_req_y;
        if (scr_req_x < bg_w.bgw[1].l_limit2) {
            if (bg_w.bgw[1].zuubun != 0) {
                bg_w.center_x = scr_req_x + 512;
                pos_w = bg_w.bgw[1].wxy[0].disp.pos + 512;
            } else {
                bg_w.center_x = scr_req_x;
                pos_w = bg_w.bgw[1].wxy[0].disp.pos;
            }
            pos_w -= bg_w.pos_offset;
            bg_w.center_x -= pos_w;
            goto zoom_check;
        }
        if (bg_w.bgw[1].r_limit2 < scr_req_x) {
            if (bg_w.bgw[1].zuubun != 0) {
                bg_w.center_x = scr_req_x + 512;
                pos_w = bg_w.bgw[1].wxy[0].disp.pos + 512;
            } else {
                bg_w.center_x = scr_req_x;
                pos_w = bg_w.bgw[1].wxy[0].disp.pos;
            }
            pos_w -= bg_w.pos_offset;
            bg_w.center_x -= pos_w;
            goto zoom_check;
        }
        bg_w.center_x = 192;
        bg_w.center_y = 224;
    }
zoom_check:
    if (work2) {
        if (bg_w.bg_f_x > bg_w.frame_deff) {
            rate = bg_zoom_rate_tbl[bg_w.bg_f_x];
            Frame_Up(bg_w.center_x, bg_w.center_y, rate, rate);
            bg_w.bg_f_x--;
            bg_w.bg_f_y--;
            return;
        } else if (bg_w.bg_f_x < bg_w.frame_deff) {
            rate = bg_zoom_rate_tbl[bg_w.bg_f_x];
            Frame_Down(bg_w.center_x, bg_w.center_y, rate, rate);
            bg_w.bg_f_x++;
            bg_w.bg_f_y++;
            if (bg_w.bg_f_x == 64) {
                bg_w.frame_flag = 0;
            }
        }
    } else if (bg_w.bg_f_x < 64) {
        rate = bg_zoom_rate_tbl[bg_w.bg_f_x];
        Frame_Down(bg_w.center_x, bg_w.center_y, rate, rate);
        bg_w.bg_f_x++;
        bg_w.bg_f_y++;
        if (bg_w.bg_f_x == 64) {
            bg_w.frame_flag = 0;
        }
    }
}



/* provisional name */
/* An earlier frame judgement on the two players' distance alone. */
/* called with bg_f_x, which it does not use */
s32 zoom_frame_judge_dist(s16 f) {
    s16 right;
    s32 left;
    bg_w.frame_flag = 0;
    if (plw[0].wu.scr_mv_x < plw[1].wu.scr_mv_x) {
        left = plw[0].wu.scr_mv_x;
        right = plw[1].wu.scr_mv_x;
    } else {
        left = plw[1].wu.scr_mv_x;
        right = plw[0].wu.scr_mv_x;
    }
    right -= left;
    if (right > 304) {
        return 2;
    }
    if (right < 272) {
        return 1;
    }
    return 0;
}



/* provisional name */
/* the message while test switch bit 8 is held, otherwise blank */
#define ZOOM_MSG(msg)                                           \
    if (exsw_2 & 0x100) {                                       \
        tilemap_print_string_attr(3, 12, 18, msg);              \
    } else {                                                    \
        tilemap_print_string_attr(3, 12, 18, "          ");   \
    }


/* provisional name */
/* the zoom test: zooms the frame one step by the players' distance and shows FRAME UP / FRAME DOWN while
   test switch bit 8 is held */
void zoom_width_test(void) {
    s32 f;
    if (Game_setting.Screen_Mode) {
        return;
    }
    if (bg_stop) {
        return;
    }
    bg_w.old_frame_flag = bg_w.frame_flag;
    bg_w.frame_flag = zoom_frame_judge_dist(bg_w.bg_f_x);
    bg_w.frame_vol = 9 - bg_w.bg_f_x;
    f = bg_w.bg_f_x;
    switch (bg_w.frame_flag) {
    case 1:
        if (f < 9) {
            bg_w.dmm1 = 1;
            bg_w.bg_f_x++;
            bg_w.bg_f_y++;
            if (bg_w.old_frame_flag == 1) {
                bg_w.old_bg_f_x++;
                bg_w.old_bg_f_y++;
                Frame_Up(bg_zoom_x_pos, bg_w.center_y, 1, 1);
                ZOOM_MSG("FRAME UP  ");
            } else {
                ZOOM_MSG("          ");
            }
        } else {
            ZOOM_MSG("          ");
        }
        break;
    case 2:
        if (f > 0) {
            bg_w.dmm1 = 2;
            bg_w.bg_f_x--;
            bg_w.bg_f_y--;
            if (bg_w.old_frame_flag == 2) {
                bg_w.old_bg_f_x--;
                bg_w.old_bg_f_y--;
                Frame_Down(bg_zoom_x_pos, bg_w.center_y, 1, 1);
                ZOOM_MSG("FRAME DOWN");
            } else {
                zoom_center_set();
                bg_zoom_x_pos = bg_w.center_x;
                ZOOM_MSG("          ");
            }
        } else {
            ZOOM_MSG("          ");
        }
        break;
    default:
        tilemap_print_string_attr(3, 12, 18, "          ");
        break;
    }
}



/* provisional name */
/* the zoom centre from layer 1's offset: bg_deff_type 0 (none), 1 (right) or 2 (left) */
void zoom_center_set(void) {
    s16 d;
    bg_zoom_old_x = bg_w.bgw[1].xy[0].disp.pos;
    d = bg_w.bgw[1].wxy[0].disp.pos - bg_w.bgw[1].xy[0].disp.pos;
    bg_zoom_d = d;
    if (!d) {
        bg_w.center_x = 0xBF;
        bg_deff_type = 0;
    } else if (d < 0) {
        bg_deff_type = 2;
        bg_w.center_x = 0x17F;
        d = -d;
    } else {
        bg_deff_type = 1;
        bg_w.center_x = 0;
    }
    bg_sp_work = d;
    bg_w.center_y = 0xE0;
}



void zoom_x_width_check(void) {
    s32 f;
    if (Game_setting.Screen_Mode) {
        return;
    }
    if (bg_stop) {
        return;
    }
    bg_w.frame_flag = zoom_frame_judge();
    f = bg_w.bg_f_x;
    switch (bg_w.frame_flag) {
    case 1:
        if (f < 9) {
            bg_w.bg_f_x++;
            if (bg_w.old_frame_flag == 1) {
                Frame_Up(192, 224, 1, 0);
            }
        }
        break;
    case 2:
        if (f > 0) {
            bg_w.bg_f_x--;
            if (bg_w.old_frame_flag == 2) {
                Frame_Down(192, 224, 1, 0);
            }
        }
        break;
    case 3:
        if (f != 9) {
            Zoomf_Init_X();
        }
        break;
    }
}



/* provisional name */
void zoom_y_width_check(void) {
    s32 f;
    if (Game_setting.Screen_Mode) {
        return;
    }
    /* previous bg_f_y, kept in the unnamed word at bg_w+0x34 */
    bg_w.old_bg_f_y = bg_w.bg_f_y;
    bg_w.frame_flag = zoom_frame_judge();
    f = bg_w.bg_f_y;
    switch (bg_w.frame_flag) {
    case 1:
        if (f < 9) {
            bg_w.bg_f_y++;
            if (bg_w.old_frame_flag == 1) {
                Frame_Up(192, 224, 0, 1);
            }
        }
        break;
    case 2:
        if (f > 0) {
            bg_w.bg_f_y--;
            if (bg_w.old_frame_flag == 2) {
                Frame_Down(192, 224, 0, 1);
            }
        }
        break;
    case 3:
        if (f != 9) {
            Zoomf_Init_Y();
        }
        break;
    }
}



s16 get_center_position(void) {
    return bg_w.bgw[1].wxy[0].disp.pos;
}



s32 get_height_position(void) {
    return bg_w.bgw[1].xy[1].disp.pos;
}



/* provisional name */
/* an empty routine (unreferenced) */
void bg_position_dummy(void) {}



/* provisional name */
void bg_quake_x_index_set(s16 ix) {
    bg_w.quake_x_index = ix;
}



/* provisional name */
void bg_quake_y_index_set(s16 ix) {
    bg_w.quake_y_index = ix;
}



/* provisional name */
void suzi_line_clear(s16 bg_num) {
    u16* dst;
    s16 i;
    dst = bg_w.bgw[bg_num].suzi_adrs;
    for (i = 0; i < 0x400; i++) {
        *dst++ = 0x200;
        *dst++ = 0;
    }
    dst = suzi_line_buf;
    for (i = 0; i < 0x400; i++) {
        *dst++ = 0x200;
        *dst++ = 0;
    }
}



/* provisional name */
void suzi_line_calc(s16 bg_num) {
    s32* line;
    u16* dst;
    u16 top;
    s16 pos;
    s16 dist;
    s16 i;
    if (bg_w.chase_flag & 0xF) {
        pos = bg_w.bgw[bg_num].chase_xy[0].disp.pos;
    } else {
        pos = bg_w.bgw[bg_num].wxy[0].disp.pos;
    }
    if (bg_w.bgw[bg_num].old_pos_x == pos) {
        return;
    }
    dist = pos;
    dist -= bg_w.bgw[bg_num].old_pos_x;
    if (dist < 0) {
        dist = -dist;
        suzi_calc_w->step = bg_w.bgw[bg_num].zuubun * dist;
        dst = bg_w.bgw[bg_num].start_suzi;
        SUZI_W0->ofs = SUZI_W0->step * bg_w.bgw[bg_num].u_line;
        line = (s32*)suzi_line_buf;
        for (i = 0; i < bg_w.bgw[bg_num].u_line; i++) {
            *line += suzi_calc_w->ofs;
            SUZI_W->ofs -= SUZI_W->step;
            *dst = *(u16*)line;
            line++;
            dst = dst + 2;
        }
        suzi_calc_w->ofs = 0;
        for (i = 0; i < bg_w.bgw[bg_num].d_line; i++) {
            *line -= suzi_calc_w->ofs;
            SUZI_W->ofs += SUZI_W->step;
            *dst = *(u16*)line;
            line++;
            dst = dst + 2;
        }
    } else {
        suzi_calc_w->step = bg_w.bgw[bg_num].zuubun * dist;
        dst = bg_w.bgw[bg_num].start_suzi;
        SUZI_W0->ofs = SUZI_W0->step * bg_w.bgw[bg_num].u_line;
        line = (s32*)suzi_line_buf;
        for (i = 0; i < bg_w.bgw[bg_num].u_line; i++) {
            *line -= suzi_calc_w->ofs;
            SUZI_W->ofs -= SUZI_W->step;
            *dst = *(u16*)line;
            line++;
            dst = dst + 2;
        }
        suzi_calc_w->ofs = 0;
        for (i = 0; i < bg_w.bgw[bg_num].d_line; i++) {
            *line += suzi_calc_w->ofs;
            SUZI_W->ofs += SUZI_W->step;
            *dst = *(u16*)line;
            line++;
            dst = dst + 2;
        }
    }
    top = suzi_line_buf[0];
    dst = bg_w.bgw[bg_num].suzi_adrs + 1024;
    for (i = 0; i < bg_w.bgw[bg_num].no_suzi_line - 512; i++) {
        *dst++ = top;
        dst++;
    }
}



/* provisional name */
void suzi_line_calc_fill(s16 bg_num) {
    s32* line;
    u16* dst;
    u16 top;
    s16 pos;
    s16 dist;
    s16 count;
    s16 i;
    if (bg_w.chase_flag & 0xF) {
        pos = bg_w.bgw[bg_num].chase_xy[0].disp.pos;
    } else {
        pos = bg_w.bgw[bg_num].wxy[0].disp.pos;
    }
    if (bg_w.bgw[bg_num].old_pos_x == pos) {
        return;
    }
    dist = pos;
    dist -= bg_w.bgw[bg_num].old_pos_x;
    if (dist < 0) {
        dist = -dist;
        suzi_calc_w->step = bg_w.bgw[bg_num].zuubun * dist;
        dst = bg_w.bgw[bg_num].start_suzi;
        SUZI_W0->ofs = SUZI_W0->step * bg_w.bgw[bg_num].u_line;
        line = (s32*)suzi_line_buf;
        for (i = 0; i < bg_w.bgw[bg_num].u_line; i++) {
            *line += suzi_calc_w->ofs;
            SUZI_W->ofs -= SUZI_W->step;
            *dst = *(u16*)line;
            line++;
            dst = dst + 2;
        }
        suzi_calc_w->ofs = 0;
        for (i = 0; i < bg_w.bgw[bg_num].d_line; i++) {
            *line -= suzi_calc_w->ofs;
            SUZI_W->ofs += SUZI_W->step;
            *dst = *(u16*)line;
            line++;
            dst = dst + 2;
        }
        line--;
        count = 41 - bg_w.bgw[bg_num].d_line;
        i = 0;
        if (count <= 0) {
            goto fill_top;
        }
        do {
            *dst = *(u16*)line;
            dst = dst + 2;
            i++;
        } while (i < count);
    } else {
        suzi_calc_w->step = bg_w.bgw[bg_num].zuubun * dist;
        dst = bg_w.bgw[bg_num].start_suzi;
        SUZI_W0->ofs = SUZI_W0->step * bg_w.bgw[bg_num].u_line;
        line = (s32*)suzi_line_buf;
        for (i = 0; i < bg_w.bgw[bg_num].u_line; i++) {
            *line -= suzi_calc_w->ofs;
            SUZI_W->ofs -= SUZI_W->step;
            *dst = *(u16*)line;
            line++;
            dst = dst + 2;
        }
        suzi_calc_w->ofs = 0;
        for (i = 0; i < bg_w.bgw[bg_num].d_line; i++) {
            *line += suzi_calc_w->ofs;
            SUZI_W->ofs += SUZI_W->step;
            *dst = *(u16*)line;
            line++;
            dst += 2;
        }
        line--;
        count = 41 - bg_w.bgw[bg_num].d_line;
        i = 0;
        if (count <= 0) {
            goto fill_top;
        }
        do {
            *dst = *(u16*)line;
            dst += 2;
            i++;
        } while (i < count);
    }
fill_top:
    top = suzi_line_buf[0];
    dst = bg_w.bgw[bg_num].suzi_adrs + 1024;
    for (i = 0; i < bg_w.bgw[bg_num].no_suzi_line - 512; i++) {
        *dst++ = top;
        dst++;
    }
}



/* provisional name */
/* fixed line scroll for layer 0 (bgst140) */
void suzi_line_fix_set(void) {
    s32* line;
    u16* dst;
    u16 top;
    s16 i;
    dst = bg_w.bgw[0].start_suzi;
    line = (s32*)suzi_line_buf;
    suzi_calc_w->step = 0x5000;
    for (i = 0; i < 280; i++) {
        *line += suzi_calc_w->step;
        *dst = *(u16*)line;
        line++;
        dst += 2;
    }
    suzi_calc_w->step = 0x3000;
    for (i = 0; i < 43; i++) {
        *line += suzi_calc_w->step;
        *dst = *(u16*)line;
        line++;
        dst += 2;
    }
    suzi_calc_w->step = 0x1000;
    for (i = 0; i < 20; i++) {
        *line += suzi_calc_w->step;
        *dst = *(u16*)line;
        line++;
        dst += 2;
    }
    top = suzi_line_buf[0];
    dst = bg_w.bgw[0].suzi_adrs;
    for (i = 0; i < 681; i++) {
        *dst++ = top;
        dst++;
    }
}



/* provisional name */
void blit_16x16_tile(u16* src, s16 code, u16* dst, s16 attr) {
    u16 i;
    u16 j;
    u16* d;
    for (i = 0; i < 16; i++) {
        d = dst;
        for (j = 0; j < 16; j++) {
            *d++ = *src++ + code;
            *d++ = *src++ + attr;
        }
        dst += 0x80;
    }
}



/* provisional name */
void blit_8x16_tile(u16* src, s16 code, u16* dst, s16 attr) {
    u16 i;
    u16 j;
    u16* d;
    u16* s;
    for (i = 0; i < 16; i++) {
        d = dst;
        s = src;
        for (j = 0; j < 8; j++) {
            *d++ = *s++ + code;
            *d++ = *s++ + attr;
        }
        dst += 0x80;
        src += 0x20;
    }
}



/* provisional name */
void bg_cell_write(s16 bg, s32 ofs, s32 cell, u32 src, u16 u5, s16 attr) {
    u16* dst;
    u32 base;
    u16 code;
    u16* s;
    base = (u32)bg_w.bgw[bg].bg_address;
    ofs += base;
    dst = (u16*)ofs;
    code = 0;
    code += bg_w.scroll_cg_adr >> 7;
    cell = (cell << 10) + src;
    s = (u16*)cell;
    blit_16x16_tile(s, code, dst, attr);
}



/* provisional name */
void blit_16x16_xflip(u16* src, s16 code, u16* dst, s16 attr) {
    u16 i;
    u16 j;
    register u16* s;
    u16* d;
    u16* p;
    p = src;
    i = 0;
    do {
        d = dst;
        for (j = 0; j < 16; j++) {
            s = p + 30 - j * 2;
            *d++ = *s++ + code;
            *d = *s + attr;
            *d++ |= 0x1000;
        }
        dst = dst + 0x80;
        p += 0x20;
    } while (++i < 16);
}



/* provisional name */
void bg_cell_write_xyflip(s16 bg, s32 ofs, s32 cell, u32 src, s16 u5, s16 attr) {
    u16* dst;
    u32 base;
    u16 code;
    u16* s;
    base = (u32)bg_w.bgw[bg].bg_address;
    ofs += base;
    dst = (u16*)ofs;
    code = 0;
    code += bg_w.scroll_cg_adr >> 7;
    cell = (cell << 10) + src;
    s = (u16*)cell;
    blit_16x16_xflip(s, code, dst, attr);
}



/* the eight base cells of a layer */
#define BG_CELL_FILL(bg, attr)                                                  \
    bg_cell_write(bg, 0, 0, bg_cg_src_tbl[bg_w.bg_index], 0, attr);             \
    bg_cell_write(bg, 0x40, 0, bg_cg_src_tbl[bg_w.bg_index], 0, attr);          \
    bg_cell_write(bg, 0x80, 0, bg_cg_src_tbl[bg_w.bg_index], 0, attr);          \
    bg_cell_write(bg, 0xC0, 0, bg_cg_src_tbl[bg_w.bg_index], 0, attr);          \
    bg_cell_write(bg, 0x1000, 0, bg_cg_src_tbl[bg_w.bg_index], 0, attr);        \
    bg_cell_write(bg, 0x1040, 0, bg_cg_src_tbl[bg_w.bg_index], 0, attr);        \
    bg_cell_write(bg, 0x1080, 0, bg_cg_src_tbl[bg_w.bg_index], 0, attr);        \
    bg_cell_write(bg, 0x10C0, 0, bg_cg_src_tbl[bg_w.bg_index], 0, attr)



/* provisional name */
void bg_scr_write(void) {
    s32 attr;
    const HUD_CELL* c;
    s16 i;
    s16 j;
    attr = bg_attr_tbl[bg_w.bg_index];
    if (bg_w.stage != 13) {
        if ((u16)attr != 0x200) {
            attr += 16;
        } else {
            attr += 64;
        }
    } else {
        attr += 125;
    }
    for (i = 0; i < bg_w.scno; i++) {
        for (j = 0; j < bg_cell_cnt_tbl[bg_w.bg_index][i]; j++) {
            if (Country != 8) {
                c = bg_rewrite_cell_tbl[bg_w.bg_index][i];
            } else {
                c = bg_rewrite_cell_tbl_8[bg_w.bg_index][i];
            }
            c += j;
            bg_cell_write(i, c->ofs, c->cell, bg_cg_src_tbl[bg_w.bg_index], 0, attr);
        }
    }
}



/* provisional name */
void ake_cell_write(s8 map, s32 ofs, s32 cell, u32 src) {
    u16* dst;
    u32 base;
    u16 code;
    u16* s;
    base = ake_scrl_w[map].adrs;
    ofs += base;
    dst = (u16*)ofs;
    code = 0;
    code += bg_w.ake_cg_adr >> 7;
    cell = (cell << 10) + src;
    s = (u16*)cell;
    blit_16x16_tile(s, code, dst, 0x290);
}



/* provisional name */
void akebono_cell_fill(void) {
    ake_cell_write(1, 0x2000, 1, (u32)ake_scrn_data);
    ake_cell_write(1, 0x2040, 2, (u32)ake_scrn_data);
    ake_cell_write(1, 0x2080, 3, (u32)ake_scrn_data);
    ake_cell_write(1, 0x20C0, 4, (u32)ake_scrn_data);
    ake_cell_write(1, 0x3000, 5, (u32)ake_scrn_data);
    ake_cell_write(1, 0x3040, 6, (u32)ake_scrn_data);
    ake_cell_write(1, 0x3080, 7, (u32)ake_scrn_data);
    ake_cell_write(1, 0x30C0, 8, (u32)ake_scrn_data);
}



/* provisional name */
void akebono_scrn_move(s16 ix) {
    s32 x = akebono_scrn_pos_tbl[ix][0] - bg_w.pos_offset;
    s32 y = akebono_scrn_pos_tbl[ix][1];
    Scrn_Move_Set(0, x, y);
}



/* provisional name */
void akebono_scr_write(void)
{
    const PANEL *cell;
    s16 i;

    cell = ake_cell1_data;
    for (i = 0; i < 8; i++) {
        ake_cell_write(1, cell->ofs, cell->cell, (u32)ake_scrn_data);
        cell++;
    }
    cell = ake_cell0_data;
    for (i = 0; i < 8; i++) {
        ake_cell_write(0, cell->ofs, cell->cell, (u32)ake_scrn_data);
        cell++;
    }
    cell = ake_cell2_data;
    for (i = 0; i < 8; i++) {
        ake_cell_write(2, cell->ofs, cell->cell, (u32)ake_scrn_data);
        cell++;
    }
}



/* provisional name */
void bg_etc_scr_write(s16 n) {
    s16 i;
    s16 j;
    const TILEREQ* t;
    s32 attr;

    attr = etc_bg_attr_tbl[n];
    t = bg_etc_cell_tbl[n][0];
    attr += t->attr;
    for (i = 0; i < bg_w.scno; i++) {
        j = 0;
        while (j < etc_bg_cell_cnt_tbl[n][i]) {
            t = bg_etc_cell_tbl[n][i];
            t += j;
            bg_cell_write(i, t->ofs, t->cell, etc_bg_cg_src_tbl[n], 0, attr);
            j++;
        }
    }
}



/* provisional name */
void bg_scr_clear_all(void) {
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < bg_w.scno; i++) {
        for (j = 0; j < bg_w.scno; j++) {
            s32 dst = (s32)bg_w.bgw[i].bg_address;
            dst += j << 12;

            for (k = 0; k < 4; k++) {
                u8* addr;
                u16* target = (u16*)(dst + k * 0x40);
                s16 code = bg_w.scroll_cg_adr >> 7;
                addr = (u8*)((bg_clear_cell_tbl[bg_w.stage][bg_w.area] << 10) + bg_cg_src_tbl[bg_w.bg_index]);
                blit_16x16_tile((u16*)addr, code, target, 0);
            }
        }
    }
}



void bg_work_clear(void) {
    s16 i;
    bg_w.bg_routine = 0;
    bg_w.bg_r_1 = 0;
    bg_w.bg_r_2 = 0;
    bg_w.compel_on = 0;
    win_sp_flag = 0;
    bg_stop = 0;
    bg_stop2 = 0;
    akebono_flag = 0;
    seraph_flag = 0;
    aku_flag = 0;
    sa_pa_flag = 0;
    bg_app = 0;
    for (i = 0; i < 7; i++) {
        bg_w.bgw[i].r_no_0 = 0;
        bg_w.bgw[i].r_no_1 = 0;
        bg_w.bgw[i].r_no_2 = 0;
    }
}



/* provisional name */
void bg_work_clear_dummy(void) {}



/* provisional name */
void bgw_xy_add(s32 x, s32 y) {
    bgw_ptr->xy[0].cal += x;
    bgw_ptr->xy[1].cal += y;
}



/* provisional name */
void bgw_wxy_add(s32 x, s32 y) {
    bgw_ptr->wxy[0].cal += x;
    bgw_ptr->wxy[1].cal += y;
}



void Bg_mv_tw(s32 value_x, s32 value_y) {
    bgw_ptr->xy[0].cal += value_x;
    bgw_ptr->xy[1].cal += value_y;
    bgw_ptr->wxy[0].cal += value_x;
    bgw_ptr->wxy[1].cal += value_y;
}



/* provisional name */
void Bg_mv_tw_appoint(bg_num, dx, dy)
s16 bg_num;
s32 dx;
s32 dy;
{
    bg_w.bgw[bg_num].xy[0].cal += dx;
    bg_w.bgw[bg_num].xy[1].cal += dy;
    bg_w.bgw[bg_num].wxy[0].cal += dx;
    bg_w.bgw[bg_num].wxy[1].cal += dy;
}



/* moves the base layer right by d steps (at most max_x), stopping at r_limit2 */
void x_right_check(s16 d) {
    s32 speed_w;
    bg_w.scr_stop &= 0xFFFC;
    if (d > bg_w.max_x) {
        d = bg_w.max_x;
    }
    speed_w = bgw_ptr->speed_x * d;
    Bg_mv_tw(speed_w, 0);
    if (bgw_ptr->wxy[0].disp.pos > bgw_ptr->r_limit2) {
        bgw_ptr->xy[0].disp.pos = bgw_ptr->r_limit2;
        bgw_ptr->xy[0].disp.low = 0;
        bgw_ptr->wxy[0].disp.pos = bgw_ptr->r_limit2;
        bgw_ptr->wxy[0].disp.low = 0;
    }
}



/* moves the base layer left by -d steps (at most max_x), stopping at l_limit2 */
void x_left_check(s16 d) {
    s32 speed_w;
    bg_w.scr_stop &= 0xFFFC;
    if (d < -bg_w.max_x) {
        d = -bg_w.max_x;
    }
    speed_w = bgw_ptr->speed_x * d;
    Bg_mv_tw(speed_w, 0);
    if (bgw_ptr->wxy[0].disp.pos < bgw_ptr->l_limit2) {
        bgw_ptr->xy[0].disp.pos = bgw_ptr->l_limit2;
        bgw_ptr->xy[0].disp.low = 0;
        bgw_ptr->wxy[0].disp.pos = bgw_ptr->l_limit2;
        bgw_ptr->wxy[0].disp.low = 0;
    }
}



/* follows the players: far apart, the layer centres on them; otherwise it scrolls when one comes within
   68 dots of a screen edge */
void bg_base_x_move_sub(void) {
    s16 work;
    s16 left;
    s16 right;
    s16 lim;
    s16 bgx;
    PLW* lp;
    PLW* rp;
    bg_w.bg2_sp_x2 = bg_w.bg2_sp_x = 0;
    if (plw[0].wu.scr_mv_x > plw[1].wu.scr_mv_x) {
        left = plw[1].wu.scr_mv_x;
        lp = &plw[1];
        right = plw[0].wu.scr_mv_x;
        rp = &plw[0];
    } else {
        left = plw[0].wu.scr_mv_x;
        lp = &plw[0];
        right = plw[1].wu.scr_mv_x;
        rp = &plw[1];
    }
    work = right - left;
    if (Game_setting.Screen_Mode) {
        lim = 0x168;
    } else {
        lim = 0xF8;
    }
    if (work >= lim) {
        left += right;
        left >>= 1;
        bgx = bgw_ptr->wxy[0].disp.pos - bg_w.pos_offset;
        left -= bgx;
        left -= bg_w.pos_offset;
        if (left < 0) {
            if (rp->micchaku_flag != 1) {
                x_left_check(left);
            }
        } else {
            if (lp->micchaku_flag != 2) {
                x_right_check(left);
            }
        }
    } else {
        bgx = bgw_ptr->wxy[0].disp.pos - bg_w.pos_offset;
        right -= bgx;
        right -= bg_w.pos_offset * 2 - 68;
        if (right > 0) {
            x_right_check(right);
        } else {
            left -= bgx;
            left -= 68;
            if (left < 0) {
                x_left_check(left);
            }
        }
    }
    bg_w.bg2_sp_x = bgw_ptr->xy[0].disp.pos - bgw_ptr->pos_x_work;
    bg_w.bg2_sp_x2 = bgw_ptr->wxy[0].disp.pos - bgw_ptr->pos_x_work;
}



void bg_base_x_move_check(void) {
    if (bg_w.chase_flag & 0xF) {
        bgw_ptr->old_pos_x = bgw_ptr->chase_xy[0].disp.pos;
    } else {
        bgw_ptr->old_pos_x = bgw_ptr->wxy[0].disp.pos;
    }
    if (bg_stop) {
        return;
    }
    bg_base_x_move_sub();
}



/* turn the players' positions into a camera request and, while the background is chasing, apply it */
void bg_chase_move(void)
{
    chase_start_check();
    if (bg_w.chase_flag) {
        chase_xy_move();
    }
}



void chase_start_check(void) {
    s16 work;
    s16 work2;
    if (zoom_request_flag & 0xF00) {
        if (chase_x != scr_req_x) {
            chase_x = scr_req_x;
            if (bgw_ptr->zuubun) {
                bgw_ptr->chase_xy[0].disp.pos = bgw_ptr->abs_x + bg_w.pos_offset;
            } else {
                bgw_ptr->chase_xy[0].disp.pos = bgw_ptr->position_x + bg_w.pos_offset;
            }
            chase_time_x = 6;
            cal_bg_speed_data_x(bgw_ptr->fam_no, chase_time_x, chase_x);
            bg_w.chase_flag |= 1;
            bg_w.chase_flag &= 0xFFFD;
            bg_w.old_chase_flag = 1;
        }
    } else {
        work = zoom_req_flag_old & 0xF00;
        work2 = ~(zoom_request_flag & 0xF00);
        work &= work2;
        if (work) {
            bg_w.chase_flag |= 2;
            bg_w.chase_flag &= 0xFFFE;
            chase_x = bgw_ptr->xy[0].disp.pos;
            chase_time_x = 6;
            cal_bg_speed_data_x(bgw_ptr->fam_no, chase_time_x, chase_x);
        }
    }
    if (zoom_request_flag & 0xF000) {
        bg_w.chase_flag |= 0x10;
        bg_w.chase_flag &= 0xFFDF;
        bg_w.old_chase_flag |= 0x10;
        bg_w.old_chase_flag &= 0xFFDF;
        if (chase_y != scr_req_y) {
            chase_y = scr_req_y;
            if (bgw_ptr->abs_y < 0) {
                bgw_ptr->chase_xy[1].disp.pos = 0;
            } else {
                bgw_ptr->chase_xy[1].disp.pos = bgw_ptr->abs_y;
            }
            chase_time_y = 6;
            cal_bg_speed_data_y(bgw_ptr->fam_no, chase_time_y, chase_y);
        }
    } else {
        work = zoom_req_flag_old & 0xF000;
        work2 = ~(zoom_request_flag & 0xF000);
        work &= work2;
        if (work) {
            bg_w.chase_flag |= 0x20;
            bg_w.chase_flag &= 0xFFEF;
            chase_y = bgw_ptr->xy[1].disp.pos;
            chase_time_y = 6;
            cal_bg_speed_data_y(bgw_ptr->fam_no, chase_time_y, chase_y);
        }
    }
}



s32 chase_xy_move(void) {
    if (bg_w.chase_flag & 0xF) {
        bg_w.bg2_sp_x2 = bg_w.bg2_sp_x = 0;
        if (bg_w.chase_flag & 1) {
            chase_time_x -= 1;
            if (chase_time_x > 0) {
                bg_mvxy.a[0].sp += bg_mvxy.d[0].sp;
                bgw_ptr->chase_xy[0].cal += bg_mvxy.a[0].sp;
            }
        }
        if (bg_w.chase_flag & 2) {
            chase_time_x -= 1;
            if (chase_time_x > 0) {
                bg_mvxy.a[0].sp += bg_mvxy.d[0].sp;
                bgw_ptr->chase_xy[0].cal += bg_mvxy.a[0].sp;
            } else {
                bg_w.chase_flag &= 0xFFF0;
                bg_w.old_chase_flag &= 0xFFF0;
                bgw_ptr->chase_xy[0].disp.pos = chase_x;
            }
        }
        if (bgw_ptr->chase_xy[0].disp.pos > bgw_ptr->r_limit2) {
            bgw_ptr->chase_xy[0].disp.pos = bgw_ptr->r_limit2;
            bgw_ptr->chase_xy[0].disp.low = 0;
        }
        if (bgw_ptr->chase_xy[0].disp.pos < bgw_ptr->l_limit2) {
            bgw_ptr->chase_xy[0].disp.pos = bgw_ptr->l_limit2;
            bgw_ptr->chase_xy[0].disp.low = 0;
        }
        bg_w.bg2_sp_x = bg_w.bg2_sp_x2 = bgw_ptr->chase_xy[0].disp.pos - bgw_ptr->pos_x_work;
    }
    if (bg_w.chase_flag & 0xF0) {
        if (bg_w.chase_flag & 0x10) {
            chase_time_y -= 1;
            if (chase_time_y > 0) {
                bg_mvxy.a[1].sp += bg_mvxy.d[1].sp;
                bgw_ptr->chase_xy[1].cal += bg_mvxy.a[1].sp;
            }
        }
        if (bg_w.chase_flag & 0x20) {
            chase_time_y -= 1;
            if (chase_time_y > 0) {
                bg_mvxy.a[1].sp += bg_mvxy.d[1].sp;
                bgw_ptr->chase_xy[1].cal += bg_mvxy.a[1].sp;
            } else {
                bg_w.chase_flag &= 0xFF0F;
                bg_w.old_chase_flag &= 0xFF0F;
                bgw_ptr->chase_xy[1].disp.pos = chase_y;
            }
        }
        if (bgw_ptr->chase_xy[1].disp.pos > bgw_ptr->y_limit2) {
            bgw_ptr->chase_xy[1].disp.pos = bgw_ptr->y_limit2;
            bgw_ptr->chase_xy[1].disp.low = 0;
        }
        bg_w.bg2_sp_y = bgw_ptr->chase_xy[1].disp.pos - bgw_ptr->pos_y_work;
    }
}



/* provisional name */
void bg_base_y_move_check(void) {
    s32 pos_w;
    s32 kake;
    s16 hi_pos;
    if (bg_stop) {
        return;
    }
    if (plw[0].wu.scr_mv_y > plw[1].wu.scr_mv_y) {
        hi_pos = plw[0].wu.scr_mv_y;
    } else {
        hi_pos = plw[1].wu.scr_mv_y;
    }
    hi_pos -= 0x54;
    if (hi_pos <= 0) {
        bgw_ptr->xy[1].cal = bgw_ptr->wxy[1].cal = 0;
    } else {
        kake = 0x14000;
        pos_w = kake * hi_pos;
        bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal = 0;
        bgw_ptr->xy[1].cal += pos_w;
        bgw_ptr->wxy[1].cal += pos_w;
        if (bgw_ptr->xy[1].disp.pos > bgw_ptr->y_limit2) {
            bgw_ptr->xy[1].disp.pos = bgw_ptr->y_limit2;
            bgw_ptr->xy[1].disp.low = 0;
            bgw_ptr->wxy[1].disp.pos = bgw_ptr->y_limit2;
            bgw_ptr->wxy[1].disp.low = 0;
            bg_w.scr_stop &= 0x7FFF;
        }
    }
    bg_w.bg2_sp_y = bgw_ptr->xy[1].disp.pos - bgw_ptr->pos_y_work;
}



void bg_x_move_check(void) {
    if (bg_w.chase_flag & 0xF) {
        bgw_ptr->old_pos_x = bgw_ptr->chase_xy[0].disp.pos;
    } else {
        bgw_ptr->old_pos_x = bgw_ptr->wxy[0].disp.pos;
    }
    if (bg_stop) {
        return;
    }
    if (bg_w.chase_flag & 0xF) {
        bgw_ptr->chase_xy[0].cal = bgw_ptr->speed_x * bg_w.bg2_sp_x2;
        bgw_ptr->chase_xy[0].disp.pos += bgw_ptr->pos_x_work;
    } else {
        bgw_ptr->wxy[0].cal = bgw_ptr->xy[0].cal = bgw_ptr->speed_x * bg_w.bg2_sp_x2;
        bgw_ptr->xy[0].disp.pos += bgw_ptr->pos_x_work;
        bgw_ptr->wxy[0].disp.pos = bgw_ptr->xy[0].disp.pos;
    }
}



void bg_y_move_check(void) {
    BGW* l;
    s32 k;
    if (bg_stop) {
        return;
    }
    if (l = bgw_ptr, k = bg_w.bg2_sp_y, (s8)bg_w.chase_flag & 0xF0) {
        l->chase_xy[1].cal = l->speed_y * k;
        if (bgw_ptr->y_limit2 < bgw_ptr->chase_xy[1].disp.pos) {
            bgw_ptr->chase_xy[1].disp.pos = bgw_ptr->y_limit2, bgw_ptr->chase_xy[1].disp.low = 0;
        }
        bgw_ptr->chase_xy[1].disp.pos += bgw_ptr->pos_y_work;
    } else {
        l->xy[1].cal = l->speed_y * k;
        if (bgw_ptr->y_limit2 < bgw_ptr->xy[1].disp.pos) {
            bgw_ptr->xy[1].disp.pos = bgw_ptr->y_limit2, bgw_ptr->xy[1].disp.low = 0;
        }
        bgw_ptr->xy[1].disp.pos += bgw_ptr->pos_y_work;
        bgw_ptr->wxy[1].cal = bgw_ptr->xy[1].cal;
    }
}



/* provisional name */
void bg_initialize(void) {
    const s16* ptr;
    const BG_GFX* gfx;
    s32 n;
    u32 blocks;
    s16 i;
    Family_Init();
    clear_scroll_layer_state_and_mask();
    scrn_pos_clear();
    Zoomf_Init();
    bg_w.bg_index = bg_index_tbl[bg_w.stage][bg_w.area];
    bg_w.scno = bg_scno_tbl[bg_w.bg_index];
    n = bg_gfx_tbl[bg_w.bg_index].size << 4;
    blocks = (n + 0xFFF) / 0x1000;
    scr_cg_c_no = simmram_block_alloc_10(blocks, 1);
    bg_w.scroll_cg_adr = simmram_slot_to_offset(scr_cg_c_no);
    gfx = &bg_gfx_tbl[bg_w.bg_index];
    load_any_color(bg_palette_no_tbl[bg_w.bg_index]);
    if (bg_w.stage != 13) {
        load_any_color(bg_color2_tbl[bg_w.bg_index]);
    }
    polygon2d_submit_line(gfx->prep, 0, 0, 3);
    polygon2d_submit_line(gfx->src, bg_w.scroll_cg_adr, gfx->size, gfx->mode);
    if (Game_setting.Screen_Mode) {
        bg_w.pos_offset = 0xF8;
    } else {
        bg_w.pos_offset = 0xC0;
    }
    for (i = 0; i < 7; i++) {
        bg_w.bgw[i].pos_x_work = bg_w.bgw[i].pos_y_work = 0;
        bg_w.bgw[i].zuubun = 0;
        bg_w.bgw[i].xy[0].cal = 0;
        bg_w.bgw[i].xy[1].cal = 0;
        bg_w.bgw[i].wxy[0].cal = 0;
        bg_w.bgw[i].wxy[1].cal = 0;
        bg_w.bgw[i].hos_xy[0].cal = 0;
        bg_w.bgw[i].hos_xy[1].cal = 0;
        bg_w.bgw[i].rewrite_flag = 0;
    }
    for (i = 0; i < bg_w.scno; i++) {
        bg_w.bgw[i].bg_adrs_c_no = simmram_big_page_alloc_40(1);
        bg_w.bgw[i].bg_address = (u16 *)simmram_slot_addr(bg_w.bgw[i].bg_adrs_c_no);
        scrn_map_set_now(i, (u32)bg_w.bgw[i].bg_address);
        scrn_map_set(i, (u32)bg_w.bgw[i].bg_address);
        sprite_list_setup(i, 1, bg_map_tbl[bg_w.bg_index][i]);
        bg_w.bgw[i].r_no_1 = bg_w.bgw[i].r_no_2 = 0;
        bg_w.bgw[i].fam_no = i;
    }
    bg_scr_write();
    for (i = 0; i < bg_w.scno; i++) {
        Bg_On_R(1 << i);
        Bg_Off_R(16 << i);
        scrn_attr_set(i, 0, 31);
        scrn_reg_w[i].ctrl &= 0xFE7F;
        bg_w.bgw[i].speed_x = bg_speed_tbl[bg_w.bg_index][i][0];
        bg_w.bgw[i].speed_y = bg_speed_tbl[bg_w.bg_index][i][1];
        bg_w.bgw[i].rewrite_flag = 0;
        bg_w.bgw[i].xy[1].disp.pos = bg_w.bgw[i].wxy[1].disp.pos = bg_w.bgw[i].pos_y_work = 0;
        ptr = bg_limit_tbl[bg_w.bg_index][i];
        bg_w.bgw[i].l_limit = *ptr++;
        bg_w.bgw[i].r_limit = *ptr++;
        bg_w.bgw[i].l_limit2 = *ptr++;
        bg_w.bgw[i].r_limit2 = *ptr++;
        bg_w.bgw[i].y_limit = *ptr++;
        bg_w.bgw[i].y_limit2 = *ptr;
        if (!Game_setting.Screen_Mode) {
            bg_w.bgw[i].r_limit2 = bg_w.bgw[i].r_limit;
            bg_w.bgw[i].l_limit2 = bg_w.bgw[i].l_limit;
        }
        bg_w.bgw[i].frame_deff = bg_w.bgw[i].frame_deff2 = 0;
    }
    if (bg_w.stage != 8) {
        base_y_pos = 40;
    } else {
        base_y_pos = 52;
    }
    bg_pos_hosei2();
    Bg_Family_Set();
    bg_w.scr_stop = 0;
    bg_w.frame_flag = 0;
    bg_w.dmm0[0] = 0;
    bg_w.bg_f_x = 64;
    bg_w.old_bg_f_x = 64;
    bg_w.bg_f_y = 64;
    bg_w.old_bg_f_y = 64;
    bg_w.dmm1 = 1;
    bg_w.bg2_sp_x2 = bg_w.bg2_sp_x = 0;
    bg_sp_work = 0;
    bg_land_flag = 0;
    bg_etc_flag = 0;
    bg_stop2 = 0;
    bg_w.max_x = 6;
    bg_w.old_chase_flag = bg_w.chase_flag = 0;
    bg_zoom_x_pos = 0xC0;
    bg_w.quake_x_index = 0;
    bg_w.quake_y_index = 0;
    bg_w.frame_deff = 64;
    bg_ofs_work[0] = bg_ofs_work[1] = bg_ofs_work[2] = 0;
    ake_cg_c_no = simmram_block_alloc_10(104, 1);
    bg_w.ake_cg_adr = simmram_slot_to_offset(ake_cg_c_no);
    load_any_color(140);
    load_any_color(143);
    polygon2d_submit_line(0x013554A0, 0, 0, 3);
    polygon2d_submit_line(0x01355520, bg_w.ake_cg_adr, 0x671F, 1);
    ake_scrl_w[1].handle = simmram_big_page_alloc_40(1);
    ake_scrl_w[1].adrs = simmram_slot_addr(ake_scrl_w[1].handle);
    bg_w.bgw[3].suzi_c_no = simmram_small_page_alloc_40(1);
    bg_w.bgw[3].suzi_adrs = (u16*)simmram_slot_addr(bg_w.bgw[3].suzi_c_no);
    scrn_linescroll_set_now(3, bg_w.bgw[3].suzi_adrs);
    memset(bg_w.bgw[3].suzi_adrs, 0, 0x1000);
    ake_scrl_w[0].handle = simmram_big_page_alloc_40(1);
    ake_scrl_w[0].adrs = simmram_slot_addr(ake_scrl_w[0].handle);
    ake_scrl_w[2].handle = simmram_big_page_alloc_40(1);
    ake_scrl_w[2].adrs = simmram_slot_addr(ake_scrl_w[2].handle);
    bg_w.bgw[3].bg_adrs_c_no = ake_scrl_w[2].handle;
    bg_w.bgw[3].bg_address = (u16 *)ake_scrl_w[2].adrs;
    scrn_map_set_now(3, (u32)bg_w.bgw[3].bg_address);
    scrn_map_set(3, (u32)bg_w.bgw[3].bg_address);
    bg_w.bgw[3].xy[0].cal = bg_w.bgw[3].wxy[0].cal = 0x100000;
    bg_w.bgw[3].xy[1].cal = bg_w.bgw[3].wxy[1].cal = 0;
    bg_w.bgw[3].position_x = 256 - bg_w.pos_offset;
    bg_w.bgw[3].position_y = 0;
    ake_scrl_w[0].pos_x = 512 - bg_w.pos_offset;
    ake_scrl_w[0].pos_y = 0;
    ake_scrl_w[0].xy[0].cal = 0x2000000;
    ake_scrl_w[0].xy[1].cal = 0;
    sprite_list_setup(3, 1, (s16*)ake_scr_record_data);
    bg_w.bgw[3].r_no_1 = bg_w.bgw[3].r_no_2 = 0;
    bg_w.bgw[3].fam_no = 3;
    akebono_scr_write();
    Bg_On_R(8);
    scrn_reg_w[3].ctrl &= 0xFE7F;
    scrn_attr_set(3, 0, 31);
    Bg_Off_R(8);
}





/* provisional name */
void compel_bg_init_position(void) {
    s16 i;
    bg_w.compel_on = 1;
    Zoomf_Init();
    bg_w.bg_f_x = 64;
    bg_w.old_bg_f_x = 64;
    bg_w.bg_f_y = 64;
    bg_w.old_bg_f_y = 64;
    bg_w.scr_stop = 0;
    bg_w.frame_flag = 0;
    bg_w.dmm0[0] = 0;
    bg_w.bg2_sp_x2 = bg_w.bg2_sp_x = 0;
    for (i = 0; i < 7; i++) {
        bg_w.bgw[i].xy[0].disp.pos = bg_w.bgw[i].wxy[0].disp.pos = bg_w.bgw[i].pos_x_work;
        bg_w.bgw[i].xy[1].disp.pos = bg_w.bgw[i].wxy[1].disp.pos = bg_w.bgw[i].pos_y_work;
        bg_w.bgw[i].xy[0].disp.low = bg_w.bgw[i].wxy[0].disp.low = 0;
        bg_w.bgw[i].xy[0].disp.low = bg_w.bgw[i].wxy[0].disp.low = 0;
        if (bg_w.bgw[i].zuubun) {
            suzi_line_clear(i);
        }
    }
}



void bg_etc_write(kind)
s16 kind;
{
    s16 type = kind;
    const BG_GFX* gfx;
    s32 n;
    u32 blocks;
    const s16* ptr;
    s16 i;
    s16 j;
    Family_Init();
    clear_scroll_layer_state_and_mask();
    scrn_pos_clear();
    Zoomf_Init();
    n = etc_bg_gfx_tbl[type].size << 4;
    blocks = (n + 0xFFF) / 0x1000;
    scr_cg_c_no = simmram_block_alloc_10(blocks, 1);
    bg_w.scroll_cg_adr = simmram_slot_to_offset(scr_cg_c_no);
    bg_w.scno = etc_bg_scno_tbl[type];
    load_any_color(etc_bg_color_tbl[type]);
    gfx = &etc_bg_gfx_tbl[type];
    polygon2d_submit_line(gfx->prep, 0, 0, 3);
    polygon2d_submit_line(gfx->src, bg_w.scroll_cg_adr, gfx->size, gfx->mode);
    if (Game_setting.Screen_Mode) {
        bg_w.pos_offset = 0xF8;
    } else {
        bg_w.pos_offset = 0xC0;
    }
    for (i = 0; i < 7; i++) {
        bg_w.bgw[i].pos_x_work = 0;
        bg_w.bgw[i].pos_y_work = 0;
        bg_w.bgw[i].zuubun = 0;
        bg_w.bgw[i].xy[0].cal = 0;
        bg_w.bgw[i].xy[1].cal = 0;
        bg_w.bgw[i].wxy[0].cal = 0;
        bg_w.bgw[i].wxy[1].cal = 0;
        bg_w.bgw[i].hos_xy[0].cal = 0;
        bg_w.bgw[i].hos_xy[1].cal = 0;
        bg_w.bgw[i].rewrite_flag = 0;
    }
    for (i = 0; i < bg_w.scno; i++) {
        bg_w.bgw[i].bg_adrs_c_no = simmram_big_page_alloc_40(1);
        bg_w.bgw[i].bg_address = (u16 *)simmram_slot_addr(bg_w.bgw[i].bg_adrs_c_no);
        scrn_map_set_now(i, (u32)bg_w.bgw[i].bg_address);
        scrn_map_set(i, (u32)bg_w.bgw[i].bg_address);
        sprite_list_setup(i, 1, bg_map_tbl2[type][i]);
        bg_w.bgw[i].r_no_1 = bg_w.bgw[i].r_no_2 = 0;
        bg_w.bgw[i].fam_no = i;
    }
    bg_etc_scr_write(type);
    if (DEBUG_DISP) {
        scrn_map_set_now(0, (u32)bg_w.bgw[0].bg_address);
    }
    for (j = 0; j < bg_w.scno; j++) {
        Bg_Off_R(16 << j);
        Bg_On_R(1 << j);
        scrn_attr_set(j, 0, 31);
        scrn_reg_w[j].ctrl &= 0xFE7F;
        bg_w.bgw[j].hos_xy[0].cal = bg_w.bgw[j].wxy[0].cal = bg_w.bgw[j].xy[0].cal = etc_bg_pos_tbl[type][j][0];
        bg_w.bgw[j].hos_xy[1].cal = bg_w.bgw[j].wxy[1].cal = bg_w.bgw[j].xy[1].cal = etc_bg_pos_tbl[type][j][1];
        bg_w.bgw[j].old_pos_x = bg_w.bgw[j].pos_x_work = bg_w.bgw[j].xy[0].disp.pos;
        bg_w.bgw[j].pos_y_work = bg_w.bgw[j].xy[1].disp.pos;
        bg_w.bgw[j].speed_x = etc_bg_speed_tbl[type][j][0];
        bg_w.bgw[j].speed_y = etc_bg_speed_tbl[type][j][1];
        bg_w.bgw[j].rewrite_flag = 0;
        bg_w.bgw[j].zuubun = etc_bg_zuubun_tbl[type][j];
        bg_w.bgw[j].xy[1].disp.pos = bg_w.bgw[j].wxy[1].disp.pos = bg_w.bgw[j].pos_y_work = 0;
        bg_w.bgw[j].frame_deff = bg_w.bgw[j].frame_deff2 = 64;
    }
    ptr = etc_bg_limit_tbl[type];
    bg_w.l_limit = *ptr++;
    bg_w.r_limit = *ptr++;
    bg_w.l_limit2 = *ptr++;
    bg_w.r_limit2 = *ptr++;
    bg_w.y_limit = *ptr++;
    bg_w.y_limit2 = *ptr;
    bg_w.scr_stop = 0;
    bg_w.frame_flag = 0;
    bg_w.dmm0[0] = 0;
    bg_land_flag = 0;
    bg_etc_flag = 0;
    bg_w.old_chase_flag = bg_w.chase_flag = 0;
    bg_w.bg_f_x = 64;
    bg_w.old_bg_f_x = 64;
    bg_w.bg_f_y = 64;
    bg_w.old_bg_f_y = 64;
    bg_w.dmm1 = 1;
    bg_w.bg2_sp_x2 = bg_w.bg2_sp_x = 0;
    bg_sp_work = 0;
    bg_stop2 = 0;
    bg_w.max_x = 6;
    bg_zoom_x_pos = 0xC0;
    bg_w.quake_y_index = bg_w.quake_x_index = 0;
}



/* provisional name */
void bg_rect_attr_preset(void) {
    u16* p = scrn_map_ptr[0].ptr2;
    oh_opening_demo(p, 0x20, 0x20, 0x1800, 0x10, 0x40, 0x24);
}



void oh_opening_demo(adrs, x, w, y, h, attr, prio)
u16* adrs;
s32 x;
s16 w;
s32 y;
s16 h;
s16 attr;
s16 prio;
{
    s16 i;
    u16 cell;
    s16 j;
    u16* p;
    adrs += x;
    adrs += y;
    i = 0;
    while (i < h) {
        p = adrs;
        for (j = 0; j < w; j++) {
            cell = *++p;
            cell &= 0xFE00;
            cell |= attr;
            cell |= prio;
            *p = cell;
            p++;
        }
        adrs += 0x80;
        i++;
    }
}



/* provisional name */
/* the CAPCOM logo colour steps on layer 0 */
s16 capcom_logo_anim(void) {
    s16 ret = 0;
    switch (bg_w.bgw[0].r_no_1) {
    case 0:
        bg_w.bgw[0].r_no_1++;
        bg_w.bgw[0].l_limit = 2;
        bg_w.bgw[0].r_limit = 64;
        bg_vbl_trans_flag = 0;
        if (Demo_Sound != 0 || PB_Music_Off != 0) {
            Sound_SE(30);
        }
        break;
    case 1:
        bg_w.bgw[0].l_limit--;
        if (bg_w.bgw[0].l_limit < 0) {
            bg_w.bgw[0].r_limit++;
            bg_w.bgw[0].l_limit = 1;
            if (bg_w.bgw[0].r_limit >= 95) {
                bg_w.bgw[0].r_no_1++;
                bg_w.bgw[0].l_limit = 256;
            }
            bg_vbl_trans_flag = 1;
        } else {
            bg_vbl_trans_flag = 0;
        }
        break;
    case 2:
        bg_w.bgw[0].l_limit--;
        if (bg_w.bgw[0].l_limit < 0) {
            bg_vbl_trans_flag = 0;
            ret = 1;
        }
        break;
    }
    return ret;
}




/* provisional name */
void check_cg_zoom(void) {
    s16 i;
    s16 zoom_wk;
    WORK* wk;
    zoom_req_flag_old = zoom_request_flag;
    zoom_request_flag = 0;
    for (i = 0; i < 2; i++) {
        if (plw[i].scr_pos_set_flag) {
            plw[i].wu.scr_mv_x = plw[i].wu.xyz[0].disp.pos;
            wk = (WORK*)&plw[i];
            wk->scr_mv_y = wk->xyz[1].disp.pos;
        }
    }
    zoom_wk = plw[1].wu.cg_zoom & 0xE200;
    switch (plw[0].wu.cg_zoom & 0xE200) {
    case 0x4000:
        break;
    case 0x2000:
        switch (zoom_wk) {
        case 0x4000:
            zoom_request_flag = 0x100;
            scr_req_x = plw[0].wu.xyz[0].disp.pos;
            break;
        case 0x2000:
            zoom_request_flag = 0x100;
            scr_req_x = (plw[0].wu.xyz[0].disp.pos + plw[1].wu.xyz[0].disp.pos) >> 1;
            break;
        case 0x200:
        case 0x0:
            zoom_request_flag = 0x100;
            scr_req_x = plw[1].wu.xyz[0].disp.pos;
            break;
        }
        break;
    case 0x200:
        switch (zoom_wk) {
        case 0x2000:
        case 0x0:
        case 0x4000:
            zoom_request_flag = 0x100;
            scr_req_x = plw[0].wu.xyz[0].disp.pos;
            break;
        case 0x200:
            zoom_request_flag = 0x100;
            scr_req_x = (plw[0].wu.xyz[0].disp.pos + plw[1].wu.xyz[0].disp.pos) >> 1;
            break;
        }
        break;
    case 0x0:
        switch (zoom_wk) {
        case 0x2000:
        case 0x4000:
            zoom_request_flag = 0x100;
            scr_req_x = plw[0].wu.xyz[0].disp.pos;
            break;
        case 0x200:
            zoom_request_flag = 0x100;
            scr_req_x = plw[1].wu.xyz[0].disp.pos;
            break;
        case 0x0:
            break;
        }
        break;
    }
    zoom_wk = plw[1].wu.cg_zoom & 0xD100;
    switch (plw[0].wu.cg_zoom & 0xD100) {
    case 0x4000:
        zoom_request_flag |= 0x1000;
        scr_req_y = 0;
        break;
    case 0x1000:
        switch (zoom_wk) {
        case 0x1000:
            zoom_request_flag |= 0x1000;
            scr_req_y = (plw[0].wu.xyz[1].disp.pos + plw[1].wu.xyz[1].disp.pos) >> 1;
            break;
        case 0x100:
        case 0x0:
            zoom_request_flag |= 0x1000;
            scr_req_y = plw[1].wu.xyz[1].disp.pos;
            break;
        case 0x4000:
            zoom_request_flag |= 0x1000;
            scr_req_y = 0;
            break;
        }
        break;
    case 0x100:
        switch (zoom_wk) {
        case 0x1000:
        case 0x0:
            zoom_request_flag |= 0x1000;
            scr_req_y = plw[0].wu.xyz[1].disp.pos;
            break;
        case 0x100:
            zoom_request_flag |= 0x1000;
            scr_req_y = (plw[0].wu.xyz[1].disp.pos + plw[1].wu.xyz[1].disp.pos) >> 1;
            break;
        case 0x4000:
            zoom_request_flag |= 0x1000;
            scr_req_y = 0;
            break;
        }
        break;
    case 0x0:
        switch (zoom_wk) {
        case 0x1000:
            zoom_request_flag |= 0x1000;
            scr_req_y = plw[0].wu.xyz[1].disp.pos;
            break;
        case 0x100:
            zoom_request_flag |= 0x1000;
            scr_req_y = plw[1].wu.xyz[1].disp.pos;
            break;
        case 0x0:
            break;
        case 0x4000:
            zoom_request_flag |= 0x1000;
            scr_req_y = 0;
            break;
        }
        break;
    }
    zoom_request_level = plw[0].wu.cg_zoom & 0xFF;
    if (zoom_request_level < (plw[1].wu.cg_zoom & 0xFF)) {
        zoom_request_level = plw[1].wu.cg_zoom & 0xFF;
    }
    if (zoom_request_level) {
        zoom_request_flag |= 1;
    }
}
