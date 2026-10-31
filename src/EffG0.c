/*
 * EFFG0.C  Effect G0: the select flow scene's figures
 *
 * effect_G0_init (from sel_flow.c) sets a work up by type. Types 0-6 are the seven judges
 * (effG0_judge_set / effG0_judge_move): each plays its animation, opens a flashing sign
 * (effG0_flash_init) and waits until all seven have (effg0_judge_count). Type 7 puts up the name
 * signs from effg0_name_tbl (effg0_name_tbl2 in the akebono form, Select_Flow_Akebono) and frees
 * itself; type 8 is a plain sprite from stage 12's character table (effG0_obj_set /
 * effG0_obj_move); type 9 sets the akebono scroll layer up on BG 0 (effG0_akebono_setup) and steps
 * it (effG0_akebono_move).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "fifo.h"
#include "sys_config.h"
#include "sys_test.h"
#include "bg_sub.h"
#include "Com_Pl.h"
#include "end_main.h"
#include "SYS_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "color3rd.h"
#include "EffG0.h"

/* routine_no[0], effG0_judge_move */
#define R0_INIT         0       /* set up on the first frame */
#define R0_MOVE         1       /* play the judge's steps */
#define R0_KILL         2       /* put the work back */

/* routine_no[1] */
#define R1_INIT         0       /* start the first pattern */
#define R1_FIRST        1       /* first pattern, then open the sign */
#define R1_SECOND       2       /* second pattern, then count in */
#define R1_WAIT         3       /* wait for all the judges */

/* routine_no[0], effG0_obj_move */
#define R0_ANIM         1       /* animate the sprite */

/* routine_no[0], effG0_akebono_move */
#define R0_SCROLL       1       /* step the scroll every 8 frames */

extern s8 Select_Flow_Akebono;   /* provisional name (sel_flow.c): the akebono form of the select flow scene */
extern s16 effg0_judge_count;   /* provisional name: initialised work RAM */
extern const u32* effg0_char_tbl[];   /* provisional name: initialised work RAM */
extern const s16 effg0_col_tbl[7];
extern const s16 effg0_pos_tbl[7][3];
extern const s16 effg0_flash_tbl[40][4];
extern const s16 effg0_name_tbl[53][3];
extern const s16 effg0_name_tbl2[][3];   /* provisional name: the names of the akebono version */
void akebono_scrn_move();
void scrn_attr_set();
s32 effG0_flash_init(s16 step, s16 x, s16 y, s16 timer, s16 dir_old, s16 col_ofs, s16 use_ofs, s16 col2_ofs);



/* provisional name */
void effG0_akebono_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.dir_timer = 8;
        ewk->wu.dir_step = 0;
        ewk->wu.routine_no[0]++;
        /* fall through */
    case R0_SCROLL:
        if (!ewk->wu.dir_timer) {
            akebono_scrn_move(ewk->wu.dir_step);
            ewk->wu.dir_timer = 8;
            ewk->wu.dir_step++;
            ewk->wu.dir_step &= 3;
        } else {
            ewk->wu.dir_timer--;
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* provisional name */
void effG0_obj_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R0_ANIM:
        char_move(&ewk->wu);
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* provisional name */
void effG0_names_move(WORK_Other* ewk) {
    const s16* p;
    s16 x;
    s16 no;
    s16 nx;
    s16 ny;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        x = bg_w.bgw[0].xy[0].disp.pos - 0xC0;
        if (Select_Flow_Akebono == 0) {
            p = effg0_name_tbl[0];
        } else {
            p = effg0_name_tbl2[0];
        }
        while (1) {
            if (*p == -1) {
                break;
            }
            no = p[0];
            nx = p[1] + x;
            ny = p[2];
            effG0_flash_init(no, nx, ny, 1, Flash_Rank_Time, 3, 0, -1);
            p += 3;
        }
        ewk->wu.routine_no[0]++;
    }
    push_effect_work(&ewk->wu);
}



/* provisional name */
void effG0_judge_move(WORK_Other* ewk) {
    s16 x;
    s16 no;
    s16 nx;
    s16 ny;
    s16 nt;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.routine_no[1] = R1_INIT;
        ewk->wu.disp_flag = 1;
        x = bg_w.bgw[1].xy[0].disp.pos - 0xC0;
        ewk->wu.xyz[0].disp.pos = x + effg0_pos_tbl[ewk->wu.type][0];
        ewk->wu.xyz[1].disp.pos = effg0_pos_tbl[ewk->wu.type][1] + 40;
        ewk->wu.xyz[2].disp.pos = effg0_pos_tbl[ewk->wu.type][2] + 32;
        ewk->wu.kage_flag = 0;
        set_char_move_init(&ewk->wu, 0, 0);
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos;
        ewk->wu.position_z = ewk->wu.xyz[2].disp.pos;
        ewk->wu.old_pos[1] = 0;
        sort_push_request(&ewk->wu);
        break;
    case R0_MOVE:
        char_move(&ewk->wu);
        switch (ewk->wu.routine_no[1]) {
        case R1_INIT:
            set_char_move_init(&ewk->wu, 0, 1);
            ewk->wu.routine_no[1]++;
            break;
        case R1_FIRST:
            if (ewk->wu.cg_type == 0xFF) {
                set_char_move_init(&ewk->wu, 0, 2);
                nx = ewk->wu.position_x + effg0_flash_tbl[ewk->wu.type][0];
                ny = ewk->wu.position_y + effg0_flash_tbl[ewk->wu.type][1];
                no = effg0_flash_tbl[ewk->wu.type][2];
                nt = effg0_flash_tbl[ewk->wu.type][3];
                effG0_flash_init(no, nx, ny, nt, Flash_Rank_Time, 3, 1, -1);
                ewk->wu.routine_no[1]++;
            }
            break;
        case R1_SECOND:
            if (ewk->wu.cg_type == 0xFF) {
                effg0_judge_count++;
                ewk->wu.routine_no[1]++;
            }
            break;
        case R1_WAIT:
            if (effg0_judge_count > 7) {
                ewk->wu.routine_no[1]++;
            }
            break;
        }
        sort_push_request(&ewk->wu);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



void effect_G0_move(WORK_Other* ewk) {
    if (ewk->wu.type < 7) {
        effG0_judge_move(ewk);
    } else if (ewk->wu.type == 7) {
        effG0_names_move(ewk);
    } else if (ewk->wu.type == 8) {
        effG0_obj_move(ewk);
    } else if (ewk->wu.type == 9) {
        effG0_akebono_move(ewk);
    }
}



/* provisional name: effect_51_init without the 120-frame lead */
s32 effG0_flash_init(s16 step, s16 x, s16 y, s16 timer, s16 dir_old, s16 col_ofs, s16 use_ofs, s16 col2_ofs) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    Flash_Sign[0]++;
    Flash_Sign[1]++;
    ewk->wu.be_flag = 1;
    ewk->wu.id = 51;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 1;
    ewk->wu.position_z = 10;
    ewk->wu.dir_timer = timer;
    ewk->wu.dir_step = dir_old;
    ewk->wu.char_table[0] = sel_pl_char_table;
    ewk->wu.char_index = 26;
    ewk->wu.my_mr_flag = 1;
    ewk->wu.my_mr.size.x = 127;
    ewk->wu.my_mr.size.y = 127;
    ewk->wu.dir_step = step;
    ewk->wu.xyz[0].disp.pos = x;
    ewk->wu.xyz[1].disp.pos = y;
    if (use_ofs == 0) {
        ewk->wu.my_col_code = 0x2043;
    } else {
        ewk->wu.my_col_code = col_ofs + 0x2043;
    }
    if (dir_old) {
        ewk->wu.routine_no[2] = 1;
        ewk->wu.routine_no[3] = 1;
        ewk->wu.routine_no[4] = 0;
        ewk->wu.vitality = 0;
        ewk->wu.vital_new = col2_ofs + 0x2043;
        ewk->wu.vital_old = ewk->wu.my_col_code;
    }
    return 0;
}



/* provisional name */
void effG0_judge_set(wk, kind)
WORK* wk;
u8 kind;
{
    if (kind == 6) {
        wk->rl_flag = 1;
    } else {
        wk->rl_flag = 0;
    }
    wk->cgromtype = 1;
    wk->my_family = 2;
    wk->my_col_mode = 0x4200;
    wk->my_col_code = effg0_col_tbl[wk->charset_id];
    wk->char_table[0] = effg0_char_tbl[wk->charset_id];
}



/* provisional name */
void effG0_obj_set(WORK* wk) {
    wk->my_col_mode = 0x4200;
    wk->dead_f = 0;
    wk->my_family = 2;
    wk->my_col_code = 0x2058;
    wk->xyz[0].disp.pos = bg_w.bgw[1].xy[0].disp.pos + 48;
    wk->xyz[1].disp.pos = 48;
    wk->my_priority = wk->position_z = 79;
    wk->char_index = 5;
    wk->hit_stop = 1;
    wk->sync_suzi = 0;
    wk->char_table[0] = char_add[12][0];
}



/* provisional name */
void effG0_akebono_setup(void) {
    clear_scroll_layer_state_and_mask();
    scrn_pos_clear();
    Zoomf_Init();
    ake_cg_c_no = simmram_block_alloc_10(104, 1);
    bg_w.ake_cg_adr = simmram_slot_to_offset(ake_cg_c_no);
    load_any_color(0x8C);
    polygon2d_submit_line(0x013554A0, 0, 0, 3);
    polygon2d_submit_line(0x01355520, bg_w.ake_cg_adr, 0x671F, 1);
    ake_scrl_w[1].handle = simmram_big_page_alloc_40(1);
    ake_scrl_w[1].adrs = simmram_slot_addr(ake_scrl_w[1].handle);
    bg_w.bgw[0].bg_adrs_c_no = ake_scrl_w[1].handle;
    bg_w.bgw[0].bg_address = (u16*)ake_scrl_w[1].adrs;
    scrn_map_set_now(0, ake_scrl_w[1].adrs);
    scrn_map_set(0, ake_scrl_w[1].adrs);
    ake_scrl_w[0].pos_x = 0x200 - bg_w.pos_offset;
    ake_scrl_w[0].pos_y = 0;
    ake_scrl_w[0].xy[0].cal = 0x2000000;
    ake_scrl_w[0].xy[1].cal = 0;
    sprite_list_setup(0, 1, bg_scr_record_data);
    akebono_cell_fill();
    Bg_On_R(1);
    scrn_reg_w[0].ctrl &= 0xFE7F;
    scrn_attr_set(0, 0, 31);
    akebono_scrn_move(0);
}



s32 effect_G0_init(WORK* wk, u8 type) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 160;
    ewk->wu.work_id = 16;
    ewk->wu.type = type;
    ewk->wu.charset_id = type;
    effg0_judge_count = 0;
    if (type < 7) {
        effG0_judge_set(&ewk->wu, type);
    } else if (type == 8) {
        effG0_obj_set(&ewk->wu);
    } else if (type == 9) {
        effG0_akebono_setup();
    }
    return 0;
}
