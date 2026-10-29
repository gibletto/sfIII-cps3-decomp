/*
 * END_MAIN_C.C  Ending main control and the helpers the endings share
 *
 * Ending_main runs the ending each frame: it clears the system and starts the character's ending script
 * (end_main_jp[]), switches the screen in, runs the script's scenes (the cut button skips to the end), fades
 * out to the staff roll (staff_roll_main), fades again and lets the winner's name run out before it sets
 * ending_all_end. The prize card messages are shown throughout (card_win_check, card_msg_disp). The shared
 * helpers used by the end_N modules follow: common_end_init00/01 (scroll graphics allocation and BG work
 * setup), plane position and family updates, block attribute writes, the BGM fade and fade-complete checks and
 * the cut button test (Cut_Cut_Cut_t). end_00000 and end_06000 are scripts that end at once.
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
#include "Com_Pl.h"
#include "aboutspr.h"
#include "SYS_sub.h"
#include "bg000.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "fifo.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "effe9.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "sc_trans.h"
#include "end_main_c.h"

/* end_w.r_no_0 in Ending_main */
#define END_INIT        0       /* clear the system and start the character's ending */
#define END_COVER       1       /* after Cover_Timer, set up the screen and wipe in */
#define END_REVIVAL     2       /* finish the wipe */
#define END_PLAY        3       /* the ending, until it ends or is cut */
#define END_TO_STAFF    4       /* fade out to the staff roll */
#define END_STAFF_SETUP 5       /* after the fade, set up the staff roll screen */
#define END_FADE_IN     6       /* fade the staff roll in */
#define END_FADE_WAIT   7       /* until the fade is done */
#define END_STAFF       8       /* the staff roll */
#define END_FADE_OUT    9       /* fade out */
#define END_MUSIC       10      /* after the fade, fade the music (longer when the name entry was cut short) */
#define END_WAIT        11      /* wait end_w.timer, then finished */



extern s32 staff_r_no;
void scrn_attr_set(u16 n, u16 attr, u16 bits);
void scrn_map_set(u16 n, u32 p);
void scrn_map_set_now(u16 n, u32 p);
extern const s8 end_type_tbl[16];




void Ending_init(void) {
    end_w.r_no_0 = 0;
    end_w.r_no_1 = 0;
    end_w.r_no_2 = 0;
    end_w.type = 0;
    end_w.end_flag = 0;
    Game_timer = 0;
    ending_all_end = 0;
    end_fade_timer = 0;
    end_fade_flag = 0;
    end_no_cut = 0;
    end_name_cut = 0;
    staff_r_no = 0;
    end_staff_flag = 0;
}



#pragma inline(end_main_move)
s32 Ending_main(s16 pl_num) {
    Game_timer++;
    switch (end_w.r_no_0) {
    case END_INIT:
        end_w.r_no_0 += 1;
        System_all_clear_Wait();
        load_any_color(0x8D);
        Cover_Timer = 24;
        end_staff_flag_set();
        end_main_jp[pl_num](pl_num);
        card_win_check(1);
        break;
    case END_COVER:
        if (Cover_Timer -= 1) {
            break;
        }
        end_w.r_no_0 += 1;
        end_color_load();
        tilemap_fill_all(0, 32);
        Switch_Screen_Init(0, 1);
        end_staff_flag_set();
        end_main_jp[pl_num](pl_num);
        card_msg_disp();
        break;
    case END_REVIVAL:
        if (Switch_Screen_Revival()) {
            end_w.r_no_0 += 1;
            Ignore_Entry[LOSER] = 0;
            Forbid_Break = -1;
        }
        break;
    case END_PLAY:
        end_main_move(pl_num);
        card_msg_disp();
        if (end_w.end_flag) {
            end_w.r_no_0 += 1;
            end_no_cut = 1;
            Rewrite_End_Message(0);
        } else if (Cut_Cut_Cut_t()) {
            end_w.timer = 0;
            Rewrite_End_Message(0);
            end_main_move(pl_num);
            move_effect_work(4);
            end_fade_flag = 0;
        }
        break;
    case END_TO_STAFF:
        end_staff_flag_set();
        if (end_no_cut == 0) {
            fadeout_to_staff_roll();
            end_w.r_no_0 += 1;
        } else {
            end_w.r_no_0 += 1;
        }
        break;
    case END_STAFF_SETUP:
        end_staff_flag_set();
        if (end_fade_complete()) {
            end_w.r_no_0 += 1;
            end_w.r_no_2 += 1;
            if (end_w.type == 12) {
                Bg_Off_W(1);
            }
            end_no_cut = 1;
        }
        break;
    case END_FADE_IN:
        end_staff_flag_set();
        end_w.r_no_0 += 1;
        if (end_type_tbl[end_w.type]) {
            Request_Fade(57, 0);
        } else {
            Request_Fade(55, 0);
        }
        end_no_cut = 1;
        Forbid_Break = -1;
        break;
    case END_FADE_WAIT:
        end_staff_flag_set();
        if (end_fade_complete()) {
            end_w.r_no_0 += 1;
            end_no_cut = 0;
        }
        break;
    case END_STAFF:
        Forbid_Break = 0;
        if (staff_roll_main(end_staff_flag)) {
            end_w.r_no_0 += 1;
        }
        break;
    case END_FADE_OUT:
        if (end_type_tbl[end_w.type]) {
            Request_Fade(59, 0);
        } else {
            Request_Fade(60, 0);
        }
        end_w.r_no_0 += 1;
        end_no_cut = 1;
        Forbid_Break = 0;
        break;
    case END_MUSIC:
        if (end_fade_complete()) {
            end_w.r_no_0 += 1;
            end_no_cut = 0;
            if (name_wk[WINNER].timer > 0) {
                name_wk[WINNER].timer = 0;
                end_name_cut = 1;
                end_w.timer = 180;
                bgm_fade_out(0xB6);
            } else {
                end_w.timer = 60;
                bgm_fade_out(0x222);
            }
        }
        Forbid_Break = 0;
        break;
    case END_WAIT:
        end_w.timer--;
        if (end_w.timer < 0) {
            ending_all_end = 1;
        }
        Forbid_Break = 0;
        break;
    }
    return ending_all_end;
}



void end_main_move(s16 pl_num) {
    end_main_jp[pl_num](pl_num);
    end_fade_bgm();
}



void end_00000(void) {
    end_w.end_flag = 1;
    ending_all_end = 1;
}



/* provisional name: the end_main_jp slot of a character who is not in the game */
void end_06000(void) {
    end_w.end_flag = 1;
    ending_all_end = 1;
}



void end_color_load(void) {
    if (end_type_tbl[end_w.type]) {
        load_any_color(0x92);
    } else {
        load_any_color(0x85);
    }
}



void fadeout_to_staff_roll(void) {
    if (end_type_tbl[end_w.type]) {
        Request_Fade(58, 0);
    } else {
        Request_Fade(56, 0);
    }
    end_no_cut = 1;
    Forbid_Break = -1;
}



void common_end_init00(s16 pl_num) {
    s16 i;
    s32 n;
    u32 blocks;
    const END_BG_GFX* gfx;
    Family_Init();
    clear_scroll_layer_state_and_mask();
    scrn_pos_clear();
    Zoomf_Init();
    end_cont_coin = Continue_Coin[WINNER];
    end_w.type = pl_num;
    bg_w.bg_index = end_bg_index_tbl[end_w.type];
    bg_w.scno = end_scno_tbl[end_w.type];
    n = ((end_bg_gfx_tbl[bg_w.bg_index].size << 4) + 0xFFF) / 0x1000;
    blocks = n;
    scr_cg_c_no = simmram_block_alloc_10(blocks, 1);
    bg_w.scroll_cg_adr = simmram_slot_to_offset(scr_cg_c_no);
    gfx = &end_bg_gfx_tbl[bg_w.bg_index];
    polygon2d_submit_line(gfx->prep, 0, 0, 3);
    polygon2d_submit_line(gfx->src, bg_w.scroll_cg_adr, gfx->size, 1);
    if (Game_setting.mode) {
        bg_w.pos_offset = 0xF8;
    } else {
        bg_w.pos_offset = 0xC0;
    }
    base_y_pos = 40;
    for (i = 0; i < 7; i++) {
        bg_w.bgw[i].r_no_0 = 0;
        bg_w.bgw[i].r_no_1 = 0;
        bg_w.bgw[i].r_no_2 = 0;
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
        sprite_list_setup(i, 1, (s16*)end_map_tbl[i]);
        bg_w.bgw[i].r_no_1 = bg_w.bgw[i].r_no_2 = 0;
        bg_w.bgw[i].fam_no = i;
    }
}



void common_end_init01(void) {
    s16 i;
    for (i = 0; i < bg_w.scno; i++) {
        scrn_attr_set(i, 0, 31);
        scrn_reg_w[i].ctrl &= 0xFE7F;
    }
    bg_w.scr_stop = 0;
    bg_w.frame_flag = 0;
    bg_w.dmm0[0] = 0;
    bg_w.bg_f_x = 9;
    bg_w.old_bg_f_x = 9;
    bg_w.bg_f_y = 9;
    bg_w.old_bg_f_y = 9;
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
    bg_ofs_work[0] = bg_ofs_work[1] = bg_ofs_work[2] = 0;
    end_etc_flag = 0;
    end_reset_etc();
    bg_w.bgw[3].wxy[0].cal = bg_w.bgw[3].xy[0].cal = 0x2000000;
    bg_w.bgw[3].xy[1].cal = 0;
    bg_w.bgw[3].position_x = 512 - bg_w.pos_offset;
    bg_w.bgw[3].position_y = 0;
    end_fam_set(3);
    effect_E9_init();
    load_any_color(0x8E);
    load_char_gfx(0x7448, 1);
    effect_F9_init(end_w.type);
}



void end_fam_set(s16 i) {
    BGW* l = &bg_w.bgw[i];
    s32 a, b, m;
    a = l->position_x;
    b = l->position_y;
    a = -a;
    m = 0x3FF;
    a &= m;
    b &= m;
    b = (0x300 - b) & m;
    Family_Set_R(i + 1, a, b);
}



void end_fam_set2(void) {
    s16 i;
    s32 pos_work_x;
    s32 pos_work_y;
    for (i = 0; i < bg_w.scno; i++) {
        pos_work_x = bg_w.bgw[i].position_x;
        pos_work_y = bg_w.bgw[i].position_y;
        pos_work_x = -pos_work_x & 0x3FF;
        pos_work_y = (0x300 - (pos_work_y & 0x3FF)) & 0x3FF;
        Family_Set_R(i + 1, pos_work_x, pos_work_y);
    }
}



void end_bg_pos_hosei(s16 bg_no) {
    s16 pos_work = bg_w.bgw[bg_no].abs_x & 0x3FF;
    pos_work -= bg_w.pos_offset;
    bg_w.bgw[bg_no].position_x = pos_work & 0x3FF;
    pos_work = bg_w.bgw[bg_no].abs_y & 0x3FF;
    bg_w.bgw[bg_no].position_y = pos_work;
}



void end_bg_pos_hosei2(void) {
    s16 bg_no;
    u16 pos_work;
    for (bg_no = 0; bg_no < bg_w.scno; bg_no++) {
        pos_work = bg_w.bgw[bg_no].abs_x & 0x3FF;
        pos_work -= bg_w.pos_offset;
        bg_w.bgw[bg_no].position_x = pos_work & 0x3FF;
        pos_work = bg_w.bgw[bg_no].abs_y & 0x3FF;
        bg_w.bgw[bg_no].position_y = pos_work;
    }
}



void end_scn_pos_set(u16 bg_no) {
    Scrn_Move_Set_R(bg_w.bgw[bg_no].fam_no, (bg_w.bgw[bg_no].xy[0].disp.pos & 0x3FF) - bg_w.pos_offset,
                    bg_w.bgw[bg_no].xy[1].disp.pos);
    bg_w.bgw[bg_no].wxy[0].cal = bg_w.bgw[bg_no].xy[0].cal;
}



void end_scn_pos_set2(void) {
    s16 bg_no;
    for (bg_no = 0; bg_no < bg_w.scno; bg_no++) {
        Scrn_Move_Set_R(bg_w.bgw[bg_no].fam_no,
                        (bg_w.bgw[bg_no].xy[0].disp.pos & 0x3FF) - bg_w.pos_offset,
                        bg_w.bgw[bg_no].xy[1].disp.pos);
        bg_w.bgw[bg_no].wxy[0].cal = bg_w.bgw[bg_no].xy[0].cal;
    }
}


void end_bg_block_attr_add(s16 bg, s32 ofs, s16 w, s32 cell, s16 h) {
    BGW* bgw;
    u16* adrs;
    adrs = (bgw = &bg_w.bgw[bg])->bg_address;
    oh_opening_demo(adrs, ofs, w, cell, h, 0x220, bgw->r_limit);
}



void end_reset_etc(void) {
    s16 i;
    for (i = 0; i < bg_w.scno; i++) {
        bg_w.bgw[i].r_no_1 = 0;
        bg_w.bgw[i].abs_x = bg_w.bgw[i].xy[0].disp.pos = 0x200;
        bg_w.bgw[i].abs_y = bg_w.bgw[i].xy[1].disp.pos = 0;
    }
}



void end_X_com01(void) {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        Bg_Off_W(1 << bgw_ptr->fam_no);
        break;
    case 1:
        break;
    }
}



void end_fade_bgm(void) {
    if (end_fade_flag != 0) {
        end_fade_timer -= 1;
        if (end_fade_timer < 0) {
            end_fade_flag = 0;
            bgm_fade_out(0x111);
        }
    }
}



s16 end_fade_complete(void) {
    if (Check_Fade_Complete()) {
        Forbid_Break = -1;
        Text_Page_Y = 32;
        commit_name_entry_row_both_players(32);
        return 1;
    }
    return 0;
}



s32 Cut_Cut_Cut_t(void) {
    u16 sw_w;
    if (end_no_cut == 0) {
        if (WINNER) {
            sw_w = p2sw_0 & ~p2sw_1;
        } else {
            sw_w = p1sw_0 & ~p1sw_1;
        }
        if (sw_w & 0x7F0) {
            return 1;
        }
    }
    return 0;
}


/* provisional name */
void end_staff_flag_set(void) {
    u16 sw_w;
    if (WINNER) {
        sw_w = p2sw_0;
    } else {
        sw_w = p1sw_0;
    }
    if (sw_w == 0x1080) {
        end_cont_coin = 0;
    }
    end_staff_flag = end_cont_coin;
}
