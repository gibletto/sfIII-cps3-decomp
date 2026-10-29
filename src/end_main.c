/*
 * END_MAIN.C  Opening demo
 *
 * opening_demo_tick runs the opening each frame: op_w.r_no_0 picks one of 22 steps from opening_jp (the setup,
 * the logo, the scene runs with their fades and the title), then opening_family_set puts layer 0's position into
 * the families. Each scene step shows a row of op_scrn_tbl (map in eff_bg_adrs, position, frames) through
 * op_scrn_map_set and op_scrn_pos_set; op_w.r_no_1 is the step's own routine number.
 *
 * op_fade_46 and op_fade_45 are steps no table refers to.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Pl.h"
#include "aboutspr.h"
#include "sc_trans.h"
#include "se_3.h"
#include "fifo.h"
#include "color3rd.h"
#include "eff36.h"
#include "EFF58.h"
#include "EFFE1.h"
#include "efff6.h"

void scrn_pos_clear(void);
s32 polygon2d_submit_line();
s32 simmram_block_alloc_10(s32 blocks, s32 kind);
s32 sprite_list_setup(s16 slot, s16 owner, s16* data);
u32 simmram_big_page_alloc_40(s32 kind);
u32 simmram_slot_addr(s16 no);
u32 simmram_slot_to_offset(s16 handle);
void scrn_attr_set(u16 n, u16 attr, u16 bits);
void scrn_map_set(u16 n, u32 p);
void scrn_map_set_now(u16 n, u32 p);
void Scrn_Move_Set(s32 n, s16 x, s16 y);
void debug_bg_tile_put(s16 bg, s32 ofs, s32 page, s32 src);
void oh_opening_demo();
void load_any_color();
s32 effect_F5_init();
s32 Check_Fade_Complete(void);
s32 Request_Fade(u16 fade_code, s8 fade_mode);
void Disp_Capcom_Rights(void);

extern const u16 op_scr_record_data[];
extern const OP_TILE op_tile_tbl[5][8];
extern const OP_SCRN op_scrn_tbl[20];
extern const OP_PRIO op_prio_tbl[10];
extern const u16 op_bg_scrn_data;
extern s8 effE1_end_flag;
extern s8 op_fade_flag;

void opning_init_00000(void);
void opning_init_01000(void);
void op_02_move(void);
void op_03_move(void);
void op_04_move(void);
void op_08_move(void);
void op_09_move(void);
void op_10_move(void);
void op_11_move(void);
void op_fade_46(void);
void op_fade_45(void);
void op_12_move(void);
void op_13_move(void);
void op_14_move(void);
void op_15_move(void);
void op_16_move(void);
void op_17_move(void);
void op_20_move(void);
void op_21_move(void);
void op_scrn_map_set();
void op_scrn_pos_set();
void opening_family_set(void);



void op_w_clear(void) {
    op_w.r_no_0 = 0;
    op_w.r_no_1 = 0;
    op_w.r_no_2 = 0;
    op_w.mv_ctr = 0;
}



s16 opening_demo_tick(void) {
    void (*opening_jp[22])() = {
        opning_init_00000, opning_init_01000, op_02_move, op_03_move, op_04_move, op_03_move,
        op_04_move, op_03_move, op_08_move, op_09_move, op_10_move, op_11_move,
        op_12_move, op_13_move, op_14_move, op_15_move, op_16_move, op_17_move,
        op_14_move, op_15_move, op_20_move, op_21_move,
    };
    opening_jp[op_w.r_no_0]();
    opening_family_set();
    return op_end_flag;
}



/* the setup: scroll graphics and palette, layer 0, five maps in eff_bg_adrs */
void opning_init_00000(void) {
    s16 i;
    BG_ADRS* p;
    op_end_flag = 0;
    bg_vbl_trans_flag = 0;
    Family_Init();
    clear_scroll_layer_state_and_mask();
    scrn_pos_clear();
    Zoomf_Init();
    op_w.r_no_0++;
    scr_cg_c_no = simmram_block_alloc_10(0xCE, 1);
    bg_w.scroll_cg_adr = simmram_slot_to_offset(scr_cg_c_no);
    bg_w.scno = 1;
    load_any_color(0x82);
    polygon2d_submit_line(0x00FB4000, 0, 0, 3);
    polygon2d_submit_line(0x00FB4080, bg_w.scroll_cg_adr, 0xCD5F, 1);
    if (Game_setting.mode) {
        bg_w.pos_offset = 0xF8;
    } else {
        bg_w.pos_offset = 0xC0;
    }
    bg_w.bgw[0].pos_x_work = bg_w.bgw[0].pos_y_work = 0;
    bg_w.bgw[0].rewrite_flag = 0;
    bg_w.bgw[0].fam_no = 0;
    bg_w.bgw[0].zuubun = 0;
    bg_w.bgw[0].xy[0].cal = 0x1000000;
    bg_w.bgw[0].xy[1].cal = 0;
    bg_w.bgw[0].wxy[0].cal = 0x1000000;
    bg_w.bgw[0].wxy[1].cal = 0;
    bg_w.bgw[0].hos_xy[0].cal = 0x1000000;
    bg_w.bgw[0].hos_xy[1].cal = 0;
    bg_w.bgw[0].position_x = 0x100 - bg_w.pos_offset;
    bg_w.bgw[0].position_y = 0;
    for (i = 0; i < 5; i++) {
        (p = &eff_bg_adrs[i])->no = simmram_big_page_alloc_40(1);
        p->adrs = simmram_slot_addr(p->no);
    }
    bg_w.bgw[0].bg_adrs_c_no = eff_bg_adrs[0].no;
    bg_w.bgw[0].bg_address = (u16*)eff_bg_adrs[0].adrs;
    scrn_map_set_now(0, eff_bg_adrs[0].adrs);
    scrn_map_set(0, eff_bg_adrs[0].adrs);
    sprite_list_setup(0, 1, (s16*)op_scr_record_data);
    op_w.r_no_1 = 0;
    op_end_flag = 0;
    load_char_gfx(0x6D00, 1);
    bg_stop = 0;
    bg_stop2 = 0;
    akebono_flag = 0;
    seraph_flag = 0;
    aku_flag = 0;
    sa_pa_flag = 0;
    bg_app = 0;
    bg_w.chase_flag = 0;
}



/* draws the five maps, then waits 8 frames with the music started */
void opning_init_01000(void) {
    s16 i;
    s16 j;
    const OP_TILE* t;
    const OP_TILE* q;
    switch (op_w.r_no_1) {
    case 0:
        op_w.r_no_1++;
        for (i = 0; i < 5; i = i + 1) {
            t = &op_tile_tbl[i][0];
            for (j = 0; j < 8; j++) {
                q = t;
                q += j;
                debug_bg_tile_put(i, q->ofs, q->cell, (u32)&op_bg_scrn_data);
            }
        }
        Bg_On_R(1);
        Bg_On_W(1);
        Bg_Off_R(0xFE);
        Bg_Off_W(0xFE);
        scrn_attr_set(0, 0, 31);
        scrn_reg_w[0].ctrl &= 0xFE7F;
        op_w.free_work = 8;
        bgm_request(1);
        break;
    case 1:
        op_w.free_work = op_w.free_work - 1;
        if (op_w.free_work < 0) {
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
            ToneDown(0);
        }
        break;
    }
    Scrn_Move_Set(0, 0x100 - bg_w.pos_offset, 0x200);
}



/* the first scene: ten priority steps of map 0, then the frame zooms in until the scene's time runs out */
void op_02_move(void) {
    const OP_PRIO* p;
    switch (op_w.r_no_1) {
    case 0:
        op_w.r_no_1++;
        op_w.r_no_2 = 0;
        op_w.index = op_scrn_tbl[op_w.r_no_2].time;
        op_w.free_work = 0;
        op_w.mv_ctr = 0;
        bg_w.bgw[0].l_limit = 1;
        debug_bg_tile_put(0, 0, 16, (u32)&op_bg_scrn_data);
        debug_bg_tile_put(0, 0, 17, (u32)&op_bg_scrn_data);
        p = op_prio_tbl;
        oh_opening_demo(eff_bg_adrs[0].adrs, 0, 32, 0x800, 16, 0x240, op_prio_tbl[0].prio);
        op_scrn_map_set(op_w.r_no_2);
        bg_w.bgw[0].r_limit = p->time;
        break;
    case 1:
        op_w.index--;
        bg_w.bgw[0].r_limit--;
        if (bg_w.bgw[0].r_limit < 0) {
            bg_w.bgw[0].l_limit++;
            if (bg_w.bgw[0].l_limit > 9) {
                op_w.r_no_1++;
            } else {
                bg_w.bgw[0].r_limit = op_prio_tbl[bg_w.bgw[0].l_limit].time;
                oh_opening_demo(eff_bg_adrs[0].adrs, 0, 32, 0x800, 16, 0x240,
                                op_prio_tbl[bg_w.bgw[0].l_limit].prio);
            }
        }
        break;
    case 2:
        op_w.index--;
        if (op_w.index < 0) {
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
        } else {
            op_w.free_work++;
            op_w.free_work &= 3;
            if (op_w.free_work == 0) {
                op_w.mv_ctr++;
                Frame_Up(0xC0, 0xE0, 1, 1);
            }
        }
        break;
    }
    op_scrn_pos_set(op_w.r_no_2);
}



/* steps 4 and 6: one scene row while the frame zooms in */
void op_04_move(void) {
    switch (op_w.r_no_1) {
    case 0:
        op_w.r_no_1++;
        switch (op_w.r_no_0) {
        case 4:
            op_w.r_no_2 = 6;
            break;
        case 6:
            op_w.r_no_2 = 12;
            break;
        }
        op_w.index = op_scrn_tbl[op_w.r_no_2].time;
        op_w.free_work = 0;
        op_w.mv_ctr = 0;
        op_scrn_map_set(op_w.r_no_2);
        break;
    case 1:
        op_w.index--;
        if (op_w.index < 0) {
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
        } else {
            op_w.free_work++;
            op_w.free_work &= 3;
            if (op_w.free_work == 0) {
                op_w.mv_ctr++;
                Frame_Up(0xC0, 0xE0, 1, 1);
            }
        }
        break;
    }
    op_scrn_pos_set(op_w.r_no_2);
}



/* steps 3, 5 and 7: the scene rows fade from one to the next until free_work, then effect 36 */
void op_03_move(void) {
    switch (op_w.r_no_1) {
    case 0:
        Zoomf_Init();
        op_w.r_no_1++;
        switch (op_w.r_no_0) {
        case 3:
            op_w.r_no_2 = 1;
            break;
        case 5:
            op_w.r_no_2 = 7;
            break;
        case 7:
            op_w.r_no_2 = 13;
            break;
        }
        op_fade_flag = 1;
        op_w.free_work = op_w.r_no_2 + 3;
        goto time_set;
    case 1:
        op_w.index--;
        if (op_w.index == 8) {
            if (op_w.r_no_2 != 16) {
                Request_Fade(62, 0);
                op_fade_flag = 0;
            } else {
                op_fade_flag = 1;
            }
            break;
        }
        if (op_w.index <= 0) {
            op_w.r_no_2++;
            Request_Fade(61, 0);
            op_fade_flag = 0;
            if (op_w.r_no_2 > op_w.free_work) {
                op_w.r_no_1++;
                op_obj_disp = 1;
                switch (op_w.r_no_0) {
                case 3:
                    effect_36_init(1);
                    break;
                case 5:
                    effect_36_init(2);
                    break;
                case 7:
                    effect_36_init(0);
                    break;
                }
            }
        time_set:
            op_w.index = op_scrn_tbl[op_w.r_no_2].time;
            op_scrn_map_set(op_w.r_no_2);
            break;
        }
        if (!op_fade_flag) {
            op_fade_flag = Check_Fade_Complete();
        }
        break;
    case 2:
        Request_Fade(61, 0);
        op_w.r_no_1++;
        op_w.index--;
        op_fade_flag = 0;
        break;
    case 3:
        op_w.index--;
        if (op_w.index <= 0) {
            op_w.r_no_1++;
            op_obj_disp = 0;
        }
        if (!op_fade_flag) {
            op_fade_flag = Check_Fade_Complete();
        }
        break;
    case 4:
        op_w.r_no_0++;
        op_w.r_no_1 = 0;
        break;
    }
    op_scrn_pos_set(op_w.r_no_2);
}



void op_08_move(void) {
    const OP_SCRN* p;
    switch (op_w.r_no_1) {
    case 0:
        op_w.r_no_1++;
        op_w.free_work = 54;
        op_w.index = op_scrn_tbl[18].time;
        p = &op_scrn_tbl[18];
        op_w.r_no_2 = 18;
        scrn_map_set_now(0, eff_bg_adrs[p->bg].adrs);
        op_scrn_map_set(18);
        oh_opening_demo(eff_bg_adrs[4].adrs, 64, 32, 0x1800, 16, 0x240, 13);
        break;
    case 1:
        op_w.free_work--;
        if (op_w.free_work < 0) {
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
        }
        break;
    }
    op_scrn_pos_set(18);
}



void op_09_move(void) {
    switch (op_w.r_no_1) {
    case 0:
        op_w.r_no_1++;
        op_w.free_work = 0;
        effect_F5_init(0);
        op_w.r_no_2 = 19;
        op_scrn_map_set(op_w.r_no_2);
        break;
    case 1:
        if (op_w.free_work) {
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
        }
        break;
    }
    op_scrn_pos_set(op_w.r_no_2);
}



void op_10_move(void) {
    switch (op_w.r_no_1) {
    case 0:
        op_w.r_no_1++;
        op_w.free_work = 0;
        effect_F6_init();
        Sound_SE(122);
        break;
    case 1:
        if (op_w.free_work) {
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
        }
        break;
    }
    op_scrn_map_set(op_w.r_no_2);
    op_scrn_pos_set(op_w.r_no_2);
}



void op_11_move(void) {
    switch (op_w.r_no_1) {
    case 0:
        op_w.r_no_1++;
        op_w.free_work = 0;
        effect_F5_init(0);
        effect_F5_init(1);
        effect_F5_init(6);
        effect_F5_init(7);
        break;
    case 1:
        if (op_w.free_work) {
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
        }
        break;
    }
    op_scrn_map_set(op_w.r_no_2);
    op_scrn_pos_set(op_w.r_no_2);
}



/* (no step refers to it) */
void op_fade_46(void) {
    switch (op_w.r_no_1) {
    case 0:
        if (Request_Fade(46, 0)) {
            op_w.r_no_1++;
        }
        break;
    case 1:
        if (Check_Fade_Complete()) {
            op_w.r_no_1++;
            op_w.free_work = 8;
        }
        break;
    case 2:
        op_w.free_work--;
        if (op_w.free_work < 0) {
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
        }
        break;
    }
    op_scrn_map_set(op_w.r_no_2);
    op_scrn_pos_set(op_w.r_no_2);
}



/* (no step refers to it) */
void op_fade_45(void) {
    switch (op_w.r_no_1) {
    case 0:
        if (op_w.r_no_0 == 20) {
            if (!Request_Fade(47, 0)) {
                break;
            }
        } else {
            if (!Request_Fade(45, 0)) {
                break;
            }
        }
        op_w.r_no_1++;
        if (op_w.r_no_0 == 15) {
            effect_E1_init(0, 1, 0);
        }
        break;
    case 1:
        if (Check_Fade_Complete()) {
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
        }
        break;
    }
    op_scrn_map_set(op_w.r_no_2);
    op_scrn_pos_set(op_w.r_no_2);
}



void op_12_move(void) {
    switch (op_w.r_no_1) {
    case 0:
        op_w.r_no_1++;
        effect_F5_init(10);
        effect_F5_init(11);
        effect_F5_init(12);
        effect_F5_init(13);
        effect_F5_init(2);
        op_w.free_work = 30;
        Sound_SE(123);
        break;
    case 1:
        op_w.free_work--;
        if (op_w.free_work < 0) {
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
        }
        break;
    }
    op_scrn_map_set(op_w.r_no_2);
    op_scrn_pos_set(op_w.r_no_2);
}



void op_13_move(void) {
    switch (op_w.r_no_1) {
    case 0:
        op_w.r_no_1++;
        op_w.free_work = 70;
        effE1_end_flag = 0;
        effect_58_init(6, 50, 0xA1);
        effect_E1_init(1, 30, 0);
        effect_E1_init(2, 30, 0);
        break;
    case 1:
        op_w.free_work--;
        if (op_w.free_work < 0) {
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
        }
        break;
    }
    op_scrn_map_set(op_w.r_no_2);
    op_scrn_pos_set(op_w.r_no_2);
}



/* steps 15 and 19: fade 47; in step 15 scene row 5 and effect E1 */
void op_15_move(void) {
    switch (op_w.r_no_1) {
    case 0:
        if (Request_Fade(47, 0)) {
            op_w.r_no_1++;
            if (op_w.r_no_0 == 15) {
                op_w.r_no_2 = 5;
                effect_E1_init(0, 1, 0);
            }
        }
        break;
    case 1:
        if (Check_Fade_Complete()) {
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
        }
        break;
    }
    op_scrn_map_set(op_w.r_no_2);
    op_scrn_pos_set(op_w.r_no_2);
}



void op_16_move(void) {
    op_w.r_no_0++;
    op_scrn_map_set(5);
    op_scrn_pos_set(5);
}



void op_17_move(void) {
    op_w.r_no_2 = 5;
    switch (op_w.r_no_1) {
    case 0:
        if (effE1_end_flag != 0) {
            op_w.r_no_1++;
            op_w.free_work = 0;
            effect_F5_init(3);
        }
        break;
    case 1:
        if (op_w.free_work) {
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
        }
        break;
    }
    op_scrn_map_set(op_w.r_no_2);
    op_scrn_pos_set(op_w.r_no_2);
}



/* steps 14 and 18: fade 48; in step 18 the title map, its effects and the last scene row */
void op_14_move(void) {
    switch (op_w.r_no_1) {
    case 0:
        if (Request_Fade(48, 0)) {
            if (op_w.r_no_0 == 18) {
                effect_58_init(6, 4, 125);
            }
            op_w.r_no_1++;
        }
        break;
    case 1:
        if (Check_Fade_Complete()) {
            if (op_w.r_no_0 == 18) {
                op_w.r_no_2 = 19;
                debug_bg_tile_put(4, 0x3000, 30, (u32)&op_bg_scrn_data);
                debug_bg_tile_put(4, 0x3040, 31, (u32)&op_bg_scrn_data);
                debug_bg_tile_put(4, 0x3080, 30, (u32)&op_bg_scrn_data);
                debug_bg_tile_put(4, 0x30C0, 31, (u32)&op_bg_scrn_data);
                effect_F5_init(8);
                effect_58_init(6, 72, 0xA2);
                if (Country != 1) {
                    effect_F5_init(9);
                }
            }
            op_w.r_no_0++;
            op_w.r_no_1 = 0;
        }
        break;
    }
    op_scrn_map_set(op_w.r_no_2);
    op_scrn_pos_set(op_w.r_no_2);
}



/* the title: copyright, 180 frames, then op_end_flag */
void op_20_move(void) {
    switch (op_w.r_no_1) {
    case 0:
        op_w.r_no_1++;
        Disp_Capcom_Rights();
        op_w.free_work = 180;
        op_w.index = op_scrn_tbl[19].time;
        break;
    case 1:
        op_w.free_work--;
        if (op_w.free_work < 0) {
            op_end_flag = 1;
        }
        break;
    }
    op_scrn_map_set(op_w.r_no_2);
    op_scrn_pos_set(op_w.r_no_2);
}



/* the title screen set up directly (op_end_flag already set) */
void op_21_move(void) {
    Zoomf_Init();
    bg_vbl_trans_flag = 0;
    scr_cg_c_no = simmram_block_alloc_10(0xCE, 1);
    bg_w.scroll_cg_adr = simmram_slot_to_offset(scr_cg_c_no);
    bg_w.scno = 1;
    polygon2d_submit_line(0x00FB4000, 0, 0, 3);
    polygon2d_submit_line(0x00FB4080, bg_w.scroll_cg_adr, 0xCD5F, 1);
    if (Game_setting.mode) {
        bg_w.pos_offset = 0xF8;
    } else {
        bg_w.pos_offset = 0xC0;
    }
    bg_w.bgw[0].pos_x_work = bg_w.bgw[0].pos_y_work = 0;
    bg_w.bgw[0].rewrite_flag = 0;
    bg_w.bgw[0].fam_no = 0;
    bg_w.bgw[0].zuubun = 0;
    bg_w.bgw[0].xy[0].cal = 0x1000000;
    bg_w.bgw[0].xy[1].cal = 0;
    bg_w.bgw[0].wxy[0].cal = 0x1000000;
    bg_w.bgw[0].wxy[1].cal = 0;
    bg_w.bgw[0].hos_xy[0].cal = 0x1000000;
    bg_w.bgw[0].hos_xy[1].cal = 0;
    bg_w.bgw[0].position_x = 0x100 - bg_w.pos_offset;
    bg_w.bgw[0].position_y = 0;
    eff_bg_adrs[0].no = simmram_big_page_alloc_40(1);
    eff_bg_adrs[0].adrs = simmram_slot_addr(eff_bg_adrs[0].no);
    bg_w.bgw[0].bg_adrs_c_no = eff_bg_adrs[0].no;
    bg_w.bgw[0].bg_address = (u16*)eff_bg_adrs[0].adrs;
    scrn_map_set_now(0, eff_bg_adrs[0].adrs);
    scrn_map_set(0, eff_bg_adrs[0].adrs);
    sprite_list_setup(0, 1, (s16*)op_scr_record_data);
    effect_E1_init(0, 24, 1);
    effect_E1_init(1, 24, 1);
    effect_E1_init(2, 24, 1);
    effect_F5_init(8);
    Disp_Capcom_Rights();
    debug_bg_tile_put(0, 0x3000, 30, (u32)&op_bg_scrn_data);
    debug_bg_tile_put(0, 0x3040, 31, (u32)&op_bg_scrn_data);
    Bg_On_R(1);
    Bg_On_W(1);
    Bg_Off_R(0xFE);
    Bg_Off_W(0xFE);
    scrn_attr_set(0, 0, 31);
    scrn_reg_w[0].ctrl &= 0xFE7F;
    Scrn_Move_Set(0, 0x100 - bg_w.pos_offset, 0);
    load_char_gfx(0x6D00, 1);
    op_end_flag = 1;
    bg_stop = 0;
    bg_stop2 = 0;
    akebono_flag = 0;
    seraph_flag = 0;
    aku_flag = 0;
    sa_pa_flag = 0;
    bg_app = 0;
    bg_w.chase_flag = 0;
}



void op_scrn_map_set(ix)
s16 ix;
{
    scrn_map_set(0, eff_bg_adrs[op_scrn_tbl[ix].bg].adrs);
}



void op_scrn_pos_set(ix)
s16 ix;
{
    Scrn_Move_Set(0, op_scrn_tbl[ix].x - bg_w.pos_offset, op_scrn_tbl[ix].y);
}



void opening_family_set(void) {
    s32 pos_work_x;
    s32 pos_work_y;
    bg_w.bgw[0].position_y = bg_w.bgw[0].xy[1].disp.pos & 0x3FF;
    pos_work_x = -bg_w.bgw[0].position_x & 0x3FF;
    /* Y work is left uninitialized. */
    pos_work_y = (768 - (pos_work_y & 0x3FF)) & 0x3FF;
    Family_Set_W(1, pos_work_x, pos_work_y);
    pos_work_x = (s16)-(0x200 - bg_w.pos_offset) & 0x3FF;
    Family_Set_W(2, pos_work_x, 768);
}
