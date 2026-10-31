/*
 * CMD_MAIN.C  Debug menu and command input
 *
 * One object (0606DBA0-060766A0, its tables at 06406858-06406A0B): the debug_* screens (OBJECT
 * LOOK/EDIT, the all-character edit, HIT and CATCH JUDGMENT box editors, the character preview, a BG viewer),
 * the move recorder and player snapshots, and the on-screen dumps of player state and cg data.
 * debug_pattern_preview_restart runs straight on into debug_pattern_preview_step.
 *
 * 6 debug tools (the sixth is a BG viewer of etc BG 4), 4 hit box kinds (body 5, attack 3, caught 1, hosei 1 per
 * pattern; HIT_IX of 4 halfwords), cg numbers up to 0x7827, 13 characters (palette rows of 0x400 cgs), 3-digit
 * BCD readouts.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "Com_Pl.h"
#include "aboutspr.h"
#include "SYS_sub.h"
#include "CALDIR.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFF00.h"
#include "EFF02.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "PLS01.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "fifo.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "bg000.h"
#include "HITCHECK.h"
#include "PLCNTDAT.h"
#include "plcntdat_2.h"
#include "cmd_main_2.h"
#include "CMD_MAIN.h"
#include "cps3.h"
#include "fighter.h"

/* Debug_R_No: the debug menu routine (debug_scene_outer_dispatch) */
#define DBG_INIT        0       /* debug_menu_work_init */
#define DBG_GFX         1       /* debug_menu_gfx_load */
#define DBG_PLAYER      2       /* debug_menu_player_setup */
#define DBG_SELECT      3       /* debug_menu_select_dispatch */
#define DBG_RUN         4       /* the debug scene, until exit */

void scrn_attr_set(s16 n, u16 attr, u16 bits);  /* as bg000.c declares them */
void scrn_map_set_now(u16 n, u32 p);
void scrn_map_set(u16 n, u32 p);



/* provisional name */


#pragma inline(debug_menu_select_dispatch)

/* provisional name */
s32 debug_scene_outer_dispatch(void) {
    dbg_p1sw_1 = dbg_p1sw_0;
    dbg_p1sw_0 = p1sw_0;
    dbg_p2sw_1 = dbg_p2sw_0;
    dbg_p2sw_0 = p2sw_0;
    dbg_dipsw_1 = dbg_dipsw_0;
    dbg_dipsw_0 = exsw_1;
    plw[0].wu.old_rno[0] = plw[0].wu.cg_number;
    plw[1].wu.old_rno[0] = plw[1].wu.cg_number;
    switch (Debug_R_No) {
    case DBG_INIT:
        debug_menu_work_init();
        break;
    case DBG_GFX:
        debug_menu_gfx_load();
        break;
    case DBG_PLAYER:
        debug_menu_player_setup();
        break;
    case DBG_SELECT:
        debug_menu_select_dispatch();
        break;
    case DBG_RUN:
        if (!debug_menu_exit_check()) {
            debug_main_dispatch();
            debug_effect_move_all();
        }
        break;
    }
    if ((dbg_p2sw_0 & BUTTON_PUNCHES) == BUTTON_PUNCHES) {
        return 1;
    }
    return 0;
}

/* provisional name */
void debug_effect_move_all(void)
{
    color_trans_dummy();
    move_effect_work(0);
    move_effect_work(1);
    move_effect_work(2);
    move_effect_work(3);
    move_effect_work(4);
    move_effect_work(6);
    move_effect_work(5);
}


/* provisional name */
void debug_menu_work_init(void) {
    s16 i;
    s16 j;
    s16* p;
    Debug_R_No++;
    debug_edit_slots_reset();
    for (i = 0; i < 2; i++) {
        p = (s16*)(dbg_slot_w + i);
        for (j = 0; j < 16; j++) {
            *p++ = 0;
        }
    }
    for (i = 0; i < 2; i++) {
        ((DBG_SLOT*)(dbg_slot_w + i))->sel[1] = 1;
        ((DBG_SLOT*)(dbg_slot_w + i))->sel[2] = 0;
        p = (s16*)(dbg_snap_w + i);
        for (j = 0; j < 12; j++) {
            *p++ = 0;
        }
    }
    work_init_zero((s32*)&plw[0], sizeof(PLW));
    work_init_zero((s32*)&plw[1], sizeof(PLW));
    Game_pause = 0;
    plw[0].zuru_timer = plw[1].zuru_timer = 0;
}

/* provisional name */
void debug_menu_gfx_load(void)
{
    Debug_R_No++;
    tilemap_fill_all(0, 0x20);
    init_char_gfx_tables();
    effect_work_quick_init();
    load_char_gfx(0x4000, 1);
    setup_kage_cells();
    Game_pause = 0;
}


/* provisional name */
void debug_menu_player_setup(void) {
    s16 i;
    s16 j;
    s16 ix;
    WORK_Other* ewk;
    Debug_R_No++;
    tilemap_fill_all(0, 32);
    work_init_zero((s32*)&plw[0], sizeof(PLW));
    work_init_zero((s32*)&plw[1], sizeof(PLW));
    debug_pattern_edit_init_counts();
    debug_edit_slots_reset();
    debug_both_players_reset();
    plw[0].wu.hit_adrs = (u32*)&plw[1];
    plw[1].wu.hit_adrs = (u32*)&plw[0];
    plw[0].wu.dmg_adrs = (u32*)&plw[1];
    plw[1].wu.dmg_adrs = (u32*)&plw[0];
    init_color_trans_req();
    load_any_color(0);
    load_player_color(plw[0].player_number, 0, 0);
    load_player_color(plw[1].player_number, 1, 0);
    effect_00_init(&plw[0].wu);
    effect_00_init(&plw[1].wu);
    effect_01_init(&plw[0].wu, 0);
    effect_01_init(&plw[0].wu, 1);
    effect_01_init(&plw[0].wu, 2);
    effect_01_init(&plw[0].wu, 3);
    effect_01_init(&plw[1].wu, 0);
    effect_01_init(&plw[1].wu, 1);
    effect_01_init(&plw[1].wu, 2);
    effect_01_init(&plw[1].wu, 3);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            if ((ix = pull_effect_work(7)) == -1) {
                return;
            }
            ewk = (WORK_Other*)frw[ix];
            ewk->wu.cgromtype = 1;
            ewk->wu.my_family = 1;
            if (i == 0) {
                ewk->wu.my_col_code = 0x2000;
            } else {
                ewk->wu.my_col_code = 0x2010;
            }
            ewk->wu.my_col_mode = 0x4200;
            ewk->wu.id = i;
            dbg_ghost_ewk[i][j] = ewk;
        }
    }
    dbg_judge_eff_ix = search_effect_index(0, 0, 0);
    Debug_Rec_Frame = 0;
    Debug_Rec_Count = 0;
    Debug_PL_id = 0;
    Debug_Dec_Disp = 0;
    dbg_cmd_panel = 0;
    dbg_hud_mode = 0;
    Game_pause = 0;
    if (Game_setting.Screen_Mode) {
        dbg_hud_x = 8;
    } else {
        dbg_hud_x = 0;
    }
}


/* provisional name */
void debug_menu_select_dispatch(void) {
    void (*Select_Tbl[2])() = { debug_menu_select_init, debug_menu_select_run };
    Select_Tbl[Debug_Select_No]();
}

/* provisional name */
void debug_menu_select_init(void)
{
    Debug_Select_No++;
    tilemap_fill_all(0, 0x20);
    Debug_Menu_No += 4;
    tilemap_print_string(0, 0, 0xFFFF, dbg_menu_str);
    tilemap_print_string_attr(8, Debug_Menu_No, 6, "T");
    Game_pause = 0;
}


/* provisional name */
void debug_menu_select_run(void) {
    u16 sw = ~dbg_p1sw_1 & dbg_p1sw_0;
    if (sw & BUTTON_LP) {
        Debug_Menu_No -= 4;
        Debug_R_No++;
        Debug_Tool_No = 0;
        debug_bg_stage_load();
        return;
    }
    if (sw & LEVER_UP) {
        tilemap_print_string_attr(8, Debug_Menu_No, 6, " ");
        Debug_Menu_No--;
        if (Debug_Menu_No < 4) {
            Debug_Menu_No = 9;
        }
    } else if (sw & LEVER_DOWN) {
        tilemap_print_string_attr(8, Debug_Menu_No, 6, " ");
        Debug_Menu_No++;
        if (Debug_Menu_No > 9) {
            Debug_Menu_No = 4;
        }
    }
    tilemap_print_string_attr(8, Debug_Menu_No, 6, "T");
}


/* provisional name */
void debug_main_dispatch(void) {
    void (*Debug_Tbl[6])() = { debug_object_look_dispatch, debug_object_edit_dispatch, debug_object_edit_all_char_dispatch, debug_hit_judgment_dispatch, debug_char_preview_dispatch, debug_bg_test_dispatch };
    dbg_old_cgd_type = plw[0].wu.cgd_type;
    Debug_Tbl[Debug_Menu_No]();
}


/* provisional name */
void debug_object_look_dispatch(void) {
    void (*Look_Tbl[2])() = { debug_object_look_init, debug_object_look_run };
    dbg_pl = plw;
    dbg_slot = (DBG_SLOT*)dbg_slot_w[0];
    Look_Tbl[Debug_Tool_No]();
    debug_draw_object_info();
    debug_draw_kakusyuku_frame_flags();
    debug_hud_mode_dispatch();
}


/* provisional name */
void debug_object_look_init(void) {
    s16 i;
    Debug_Tool_No++;
    tilemap_fill_all(0, 32);
    tilemap_print_string_attr(15, 1, 14, object_look_msg);
    tilemap_print_string(0, 0, 0xFFFF, dbg_obj_info_str);
    for (i = 0; i < 21; i++) {
        Debug_Rep_Timer[i] = 0;
        Debug_Rep_Count[i] = 0;
    }
    dbg_kakusyuku_mode = 0;
    dbg_look_mode = 0;
    dbg_zoom_x = 19;
    dbg_zoom_y = 19;
    dbg_cmd_panel = 0;
    Debug_Dec_Disp = 0;
    Debug_Snap_Disp = 0;
    Debug_PL_id = 0;
    debug_both_players_reset();
    plw[1].wu.disp_flag = 0;
    plw[1].wu.be_flag = 0;
    dbg_pl = &plw[0];
    dbg_slot = (DBG_SLOT*)dbg_slot_w[0];
    debug_slot_char_load();
    debug_motion_list_count();
    debug_pattern_count();
    debug_pattern_timer_update();
}


/* provisional name */
void debug_object_look_run(void) {
    Debug_Command = 0;
    debug_object_look_input();
    switch (Debug_Command) {
    case 1:
        debug_slot_char_load();
        debug_motion_list_count();
        dbg_pl->wu.meoshi_hit_flag = 1;
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_timer_update();
        debug_pattern_count();
        break;
    case 2:
        dbg_pl->wu.meoshi_hit_flag = 1;
        if (dbg_slot->sel[0] > 0x90) {
            set_char_move_init(&dbg_pl->wu, 0, dbg_slot->sel[1] - 1);
        } else {
            set_char_move_init(&dbg_pl->wu, dbg_slot->row, dbg_slot->sel[1] - 1);
        }
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (dbg_pl->wu.disp_flag == 0) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_timer_update();
        debug_pattern_count();
        break;
    case 4:
        dbg_pl->wu.meoshi_hit_flag = 1;
        char_move(&dbg_pl->wu);
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (dbg_pl->wu.disp_flag == 0) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        debug_pattern_timer_update();
        if (dbg_slot->sel[2] == dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type) {
            break;
        } else {
            Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
            dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
            Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
            dbg_slot->sel[2] = dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type;
        }
        break;
    case 5:
        dbg_pl->wu.meoshi_hit_flag = 1;
        char_move_z(&dbg_pl->wu);
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (dbg_pl->wu.disp_flag == 0) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_timer_update();
        dbg_slot->sel[2] = dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type;
        break;
    case 6:
        dbg_pl->wu.meoshi_hit_flag = 1;
        char_move_cmoa(&dbg_pl->wu);
        debug_pattern_timer_update();
        dbg_slot->sel[2] = dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type;
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
    }
    dbg_pl->wu.position_z = dbg_pl->wu.my_priority;
    sort_push_request(&dbg_pl->wu);
}


const char object_look_msg[12] = "OBJECT LOOK";


/* provisional name */
void debug_object_edit_dispatch(void) {
    void (*Edit_Tbl[2])() = { debug_object_edit_init, debug_object_edit_move };
    dbg_pl = &plw[Debug_PL_id];
    dbg_slot = (DBG_SLOT*)(dbg_slot_w + Debug_PL_id);
    dbg_snap_ptr = &dbg_snap_w[0][Debug_Rec_Frame];
    Edit_Tbl[Debug_Tool_No]();
    debug_draw_object_info();
    debug_draw_record_info();
}


/* provisional name */
void debug_object_edit_init(void) {
    s16 i;
    Debug_Tool_No++;
    tilemap_fill_all(0, 32);
    tilemap_print_string_attr(15, 1, 14, object_edit_msg);
    tilemap_print_string(0, 0, 0xFFFF, dbg_obj_info_str);
    tilemap_print_string(0, 0, 0xFFFF, dbg_obj_rel_str);
    tilemap_print_string(0, 0, 0xFFFF, dbg_edit_num_str);
    for (i = 0; i < 21; i++) {
        Debug_Rep_Timer[i] = 0;
        Debug_Rep_Count[i] = 0;
    }
    debug_both_players_reset();
    dbg_save_mode = 2;
    dbg_rec_menu = 0;
    Debug_Play_Flag = 0;
    Debug_PL_id = 0;
    Debug_Edit_Sub = 0;
    dbg_rec_exist = 0;
    Debug_Snap_Disp = 0;
    dbg_col_ix[0] = 0;
    dbg_col_ix[1] = 0;
    dbg_cmd_panel = 0;
    Debug_Dec_Disp = 0;
    Debug_Dec_Disp = 0;
    for (i = 0; i < 2; i++) {
        dbg_pl = &plw[i];
        dbg_slot = (DBG_SLOT*)(dbg_slot_w + i);
        debug_slot_char_load();
        debug_motion_list_count();
        debug_pattern_count();
        debug_pattern_timer_update();
    }
}


/* provisional name */
void debug_object_edit_move(void) {
    u16 group;
    s16 base;
    Debug_Command = 0;
    dbg_snap_req = 0;
    debug_object_edit_input();
    switch (Debug_Command) {
    case 1:
        debug_slot_char_load();
        debug_motion_list_count();
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_timer_update();
        dbg_snap_ptr->dbg_val[1] = dbg_slot->frames;
        dbg_snap_ptr->dbg_val[0] = dbg_slot->rest;
        debug_pattern_count();
        Debug_Play_Flag = 0;
        break;
    case 2:
        if (dbg_slot->sel[0] > 0x90) {
            set_char_move_init(&dbg_pl->wu, 0, dbg_slot->sel[1] - 1);
        } else {
            set_char_move_init(&dbg_pl->wu, dbg_slot->row, dbg_slot->sel[1] - 1);
        }
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (!dbg_pl->wu.disp_flag) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_timer_update();
        dbg_snap_ptr->dbg_val[1] = dbg_slot->frames;
        dbg_snap_ptr->dbg_val[0] = dbg_slot->rest;
        debug_pattern_count();
        Debug_Play_Flag = 0;
        break;
    case 4:
        char_move(&dbg_pl->wu);
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (dbg_pl->wu.disp_flag == 0) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        debug_pattern_timer_update();
        if (dbg_slot->sel[2] != dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type) {
            Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
            dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
            Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
            dbg_slot->sel[2] = dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type;
        }
        dbg_snap_ptr->dbg_val[1] = dbg_slot->frames;
        dbg_snap_ptr->dbg_val[0] = dbg_slot->rest;
        Debug_Play_Flag = 0;
        break;
    case 5:
        char_move_z(&dbg_pl->wu);
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (dbg_pl->wu.disp_flag == 0) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_timer_update();
        dbg_slot->sel[2]++;
        dbg_slot->sel[2] = dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type;
        dbg_snap_ptr->dbg_val[1] = dbg_slot->frames;
        dbg_snap_ptr->dbg_val[0] = dbg_slot->rest;
        Debug_Play_Flag = 0;
        break;
    case 6:
        if (Debug_Rec_Count) {
            tilemap_print_string_attr(30, 1, 14, no_edit_erase_msg);
        } else {
            tilemap_print_string_attr(30, 1, 6, no_edit_msg);
            break;
        }
        Debug_Play_Flag = dbg_snap_req = 1;
        dbg_rec_exist = 1;
        dbg_snap_ptr->used++;
        if (dbg_snap_ptr->used > dbg_snap_ptr->cg_ctr) {
            dbg_snap_ptr->used = 1;
            Debug_Rec_Frame++;
            if (Debug_Rec_Frame > Debug_Rec_Count) {
                Debug_Rec_Frame = 1;
            }
        }
        break;
    case 7:
        if (Debug_Rec_Count) {
            tilemap_print_string_attr(30, 1, 14, (char *)&no_edit_erase_msg);
        } else {
            tilemap_print_string_attr(30, 1, 6, (char *)&no_edit_msg);
            break;
        }
        Debug_Play_Flag = dbg_snap_req = 1;
        dbg_rec_exist = 1;
        dbg_snap_ptr->used = 1;
        Debug_Rec_Frame++;
        if (Debug_Rec_Frame > Debug_Rec_Count) {
            Debug_Rec_Frame = 1;
        }
        break;
    case 3:
        Debug_Play_Flag = 0;
        break;
    case 8:
        debug_record_frame_save();
        Debug_Play_Flag = 1;
        break;
    default:
        Debug_Play_Flag = 0;
        break;
    }
    debug_object_edit_snapshot_restore();
    debug_draw_record_ghosts();
    group = debug_cg_group_index(dbg_pl->wu.cg_number);
    tilemap_print_string(0, 0, 0xFFFF, &dbg_edit_group_str[group]);
    base = dbg_cg_group_top_tbl[group];
    base = dbg_pl->wu.cg_number - base;
    tilemap_print_hex(7, 25, 2, base, 4, 0);
}


/* provisional name */
void debug_record_frame_save(void) {
    s16 i;
    s16 j;
    switch (dbg_save_mode) {
    case 0:
        dbg_snap_req = 1;
        debug_save_player_snapshot(&dbg_snap_w[0][Debug_Rec_Frame], &plw[0].wu);
        debug_save_player_snapshot(&dbg_snap_w[1][Debug_Rec_Frame], &plw[1].wu);
        if (Debug_Rec_Frame < Debug_Rec_Count) {
            Debug_Rec_Frame++;
        }
        break;
    case 1:
        if (dbg_rec_exist == 0) {
            break;
        } else {
            if (Debug_Rec_Count > 128) {
                i = 127;
            } else {
                i = Debug_Rec_Count;
            }
            for (; i > Debug_Rec_Frame - 1; i--) {
                j = i + 1;
                debug_copy_player_snapshot(&dbg_snap_w[0][i], &dbg_snap_w[0][j]);
                debug_copy_player_snapshot(&dbg_snap_w[1][i], &dbg_snap_w[1][j]);
            }
            debug_save_player_snapshot(&dbg_snap_w[0][Debug_Rec_Frame], &plw[0].wu);
            debug_save_player_snapshot(&dbg_snap_w[1][Debug_Rec_Frame], &plw[1].wu);
            if (Debug_Rec_Count + 1 <= 128) {
                Debug_Rec_Count++;
            }
        }
        break;
    case 2:
        if (dbg_rec_exist == 0) {
            if (Debug_Rec_Frame + 1 > 128) {
                break;
            }
            Debug_Rec_Frame++;
            if (Debug_Rec_Count + 1 > 128) {
                break;
            } else {
                Debug_Rec_Count++;
                debug_save_player_snapshot(&dbg_snap_w[0][Debug_Rec_Frame], &plw[0].wu);
                debug_save_player_snapshot(&dbg_snap_w[1][Debug_Rec_Frame], &plw[1].wu);
            }
        } else {
            if (Debug_Rec_Frame + 1 > 128) {
                break;
            }
            if (Debug_Rec_Count > 128) {
                i = 127;
            } else {
                i = Debug_Rec_Count;
            }
            for (; i > Debug_Rec_Frame; i--) {
                j = i + 1;
                debug_copy_player_snapshot(&dbg_snap_w[0][i], &dbg_snap_w[0][j]);
                debug_copy_player_snapshot(&dbg_snap_w[1][i], &dbg_snap_w[1][j]);
            }
            Debug_Rec_Frame++;
            debug_save_player_snapshot(&dbg_snap_w[0][Debug_Rec_Frame], &plw[0].wu);
            debug_save_player_snapshot(&dbg_snap_w[1][Debug_Rec_Frame], &plw[1].wu);
            if (Debug_Rec_Count + 1 <= 128) {
                Debug_Rec_Count++;
            }
        }
        break;
    }
}


/* provisional name */
void debug_object_edit_snapshot_restore(void) {
    WORK* wk;
    if (Debug_Play_Flag) {
        debug_restore_player_snapshot(&dbg_snap_w[0][Debug_Rec_Frame], (WORK*)&plw[0]);
        debug_restore_player_snapshot(&dbg_snap_w[1][Debug_Rec_Frame], &plw[1].wu);
        plw[0].wu.old_cgnum = 0;
        debug_char_disp(&plw[0].wu);
        plw[1].wu.old_cgnum = 0;
        debug_char_disp(&plw[1].wu);
        Debug_Snap_Disp = 1;
    } else if (dbg_snap_req) {
        if (Debug_Rec_Count) {
            debug_restore_player_snapshot(&dbg_snap_w[0][Debug_Rec_Frame], (WORK*)&plw[0]);
            debug_restore_player_snapshot(&dbg_snap_w[1][Debug_Rec_Frame], &plw[1].wu);
            plw[0].wu.old_cgnum = 0;
            debug_char_disp(&plw[0].wu);
            plw[1].wu.old_cgnum = 0;
            debug_char_disp(&plw[1].wu);
            Debug_Snap_Disp = 1;
        } else {
            plw[0].wu.old_cgnum = 0;
            debug_char_disp(&plw[0].wu);
            wk = &plw[1].wu;
            wk->old_cgnum = 0;
            debug_char_disp(wk);
            Debug_Snap_Disp = 1;
        }
    } else {
        plw[0].wu.old_cgnum = 0;
        debug_char_disp(&plw[0].wu);
        wk = &plw[1].wu;
        wk->old_cgnum = 0;
        debug_char_disp(wk);
        Debug_Snap_Disp = 0;
    }
}


const char object_edit_msg[12] = "OBJECT EDIT";


const char no_edit_erase_msg[8] = "       ";


const char no_edit_msg[8] = "NO EDIT";


/* provisional name */
void debug_object_edit_all_char_dispatch(void) {
    void (*All_Tbl[2])() = { debug_object_edit_all_char_init, debug_object_edit_all_char_move };
    dbg_pl = &plw[Debug_PL_id];
    dbg_slot = (DBG_SLOT*)(dbg_slot_w + Debug_PL_id);
    dbg_snap_ptr = &dbg_snap_w[0][Debug_Rec_Frame];
    All_Tbl[Debug_Tool_No]();
    debug_draw_object_info();
    debug_draw_record_info();
}


/* provisional name */
void debug_object_edit_all_char_init(void) {
    s16 i;
    Debug_Tool_No++;
    tilemap_fill_all(0, 32);
    tilemap_print_string_attr(9, 1, 14, object_edit_all_msg);
    tilemap_print_string(0, 0, 0xFFFF, dbg_obj_info_str);
    tilemap_print_string(0, 0, 0xFFFF, dbg_obj_rel_str);
    tilemap_print_string(0, 0, 0xFFFF, dbg_edit_num_str);
    for (i = 0; i < 21; i++) {
        Debug_Rep_Timer[i] = 0;
        Debug_Rep_Count[i] = 0;
    }
    debug_char_slot_init(1);
    debug_both_players_reset();
    dbg_save_mode = 2;
    dbg_rec_menu = 0;
    Debug_Play_Flag = 0;
    Debug_PL_id = 0;
    Debug_Edit_Sub = 0;
    Debug_Dec_Disp = 0;
    Debug_Snap_Disp = 0;
    dbg_rec_exist = 0;
    dbg_col_ix[0] = 0;
    dbg_col_ix[1] = 0;
    dbg_cmd_panel = 0;
    dbg_pl = &plw[0];
    dbg_slot = (DBG_SLOT*)dbg_slot_w[0];
    debug_slot_char_load();
    debug_motion_list_count();
    debug_pattern_count();
    debug_pattern_timer_update();
    dbg_col_char = 0;
    dbg_cmd_panel = 0;
    plw[1].wu.old_cgnum = 0;
    plw[1].wu.cg_number = 1;
}


/* provisional name */
void debug_object_edit_all_char_move(void) {
    u16 group;
    s16 base;
    Debug_Command = 0;
    dbg_snap_req = 0;
    debug_edit_all_char_input();
    switch (Debug_Command) {
    case 1:
        debug_slot_char_load();
        debug_motion_list_count();
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_timer_update();
        dbg_snap_ptr->dbg_val[1] = dbg_slot->frames;
        dbg_snap_ptr->dbg_val[0] = dbg_slot->rest;
        debug_pattern_count();
        Debug_Play_Flag = 0;
        break;
    case 2:
        if (dbg_slot->sel[0] > 0x90) {
            set_char_move_init(&dbg_pl->wu, 0, dbg_slot->sel[1] - 1);
        } else {
            set_char_move_init(&dbg_pl->wu, dbg_slot->row, dbg_slot->sel[1] - 1);
        }
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (!dbg_pl->wu.disp_flag) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_timer_update();
        dbg_snap_ptr->dbg_val[1] = dbg_slot->frames;
        dbg_snap_ptr->dbg_val[0] = dbg_slot->rest;
        debug_pattern_count();
        Debug_Play_Flag = 0;
        break;
    case 4:
        char_move(&dbg_pl->wu);
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (dbg_pl->wu.disp_flag == 0) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        debug_pattern_timer_update();
        if (dbg_slot->sel[2] != dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type) {
            Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
            dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
            Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
            dbg_slot->sel[2] = dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type;
        }
        dbg_snap_ptr->dbg_val[1] = dbg_slot->frames;
        dbg_snap_ptr->dbg_val[0] = dbg_slot->rest;
        Debug_Play_Flag = 0;
        break;
    case 5:
        char_move_z(&dbg_pl->wu);
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (dbg_pl->wu.disp_flag == 0) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_timer_update();
        dbg_slot->sel[2]++;
        dbg_slot->sel[2] = dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type;
        dbg_snap_ptr->dbg_val[1] = dbg_slot->frames;
        dbg_snap_ptr->dbg_val[0] = dbg_slot->rest;
        Debug_Play_Flag = 0;
        break;
    case 6:
        if (Debug_Rec_Count) {
            tilemap_print_string_attr(30, 1, 14, no_edit_erase_msg);
        } else {
            tilemap_print_string_attr(30, 1, 6, no_edit_msg);
            break;
        }
        Debug_Play_Flag = dbg_snap_req = 1;
        dbg_rec_exist = 1;
        dbg_snap_ptr->used++;
        if (dbg_snap_ptr->used > dbg_snap_ptr->cg_ctr) {
            dbg_snap_ptr->used = 1;
            Debug_Rec_Frame++;
            if (Debug_Rec_Frame > Debug_Rec_Count) {
                Debug_Rec_Frame = 1;
            }
        }
        break;
    case 7:
        if (Debug_Rec_Count) {
            tilemap_print_string_attr(30, 1, 14, (char *)&no_edit_erase_msg);
        } else {
            tilemap_print_string_attr(30, 1, 6, (char *)&no_edit_msg);
            break;
        }
        Debug_Play_Flag = dbg_snap_req = 1;
        dbg_rec_exist = 1;
        dbg_snap_ptr->used = 1;
        Debug_Rec_Frame++;
        if (Debug_Rec_Frame > Debug_Rec_Count) {
            Debug_Rec_Frame = 1;
        }
        break;
    case 3:
        Debug_Play_Flag = 0;
        break;
    case 8:
        debug_record_frame_save();
        Debug_Play_Flag = 1;
        break;
    default:
        Debug_Play_Flag = 0;
        break;
    }
    debug_object_edit_snapshot_restore();
    debug_draw_record_ghosts();
    group = debug_cg_group_index(dbg_pl->wu.cg_number);
    tilemap_print_string(0, 0, 0xFFFF, &dbg_edit_group_str[group]);
    base = dbg_cg_group_top_tbl[group];
    base = dbg_pl->wu.cg_number - base;
    tilemap_print_hex(7, 25, 2, base, 4, 0);
}


/* provisional name */
void debug_zoom_out_by_dipsw(void) {
    u16 sw = ~dbg_dipsw_1;
    sw &= dbg_dipsw_0;
    sw &= 0xC0;
    switch (sw) {
    case 0x40:
        Zoomf_Init();
        Frame_Down(0xC0, 0xE0, 8, 8);
        break;
    case 0x80:
        Zoomf_Init();
        Frame_Down(0xC0, 0xE0, 16, 16);
        break;
    case 0xC0:
        Zoomf_Init();
        Frame_Down(0xC0, 0xE0, 24, 24);
        break;
    }
    sw = dbg_dipsw_0;
    sw &= 0xC0;
    if (sw == 0) {
        Zoomf_Init();
    }
}


/* provisional name */
void debug_player_color_next(void) {
    u16 sw;
    if (exsw_1 & 0x100) {
        sw = ~dbg_p1sw_1 & dbg_p1sw_0;
        if (sw & BUTTON_START) {
            dbg_col_ix[dbg_pl->wu.id] += 1;
            dbg_col_ix[dbg_pl->wu.id] &= 0xF;
            dbg_pl->wu.my_col_code = dbg_col_code_tbl[dbg_col_ix[dbg_pl->wu.id]];
            if (dbg_col_ix[dbg_pl->wu.id] < 13) {
                load_any_color(dbg_col_no_tbl[dbg_col_ix[dbg_pl->wu.id]]);
            }
        }
    }
}


/* provisional name */
void debug_ghost_shift_left(WORK* wk) {
    u16 sw = exsw_1 & 3;
    switch (sw) {
    case 0:
        wk->position_x -= 104;
        wk->position_y += 96;
        break;
    case 1:
        wk->position_x -= 136;
        wk->position_y += 112;
        break;
    case 2:
        wk->position_x -= 168;
        wk->position_y += 128;
        break;
    case 3:
        wk->position_x -= 200;
        wk->position_y += 136;
        break;
    }
}


/* provisional name */
void debug_ghost_shift_right(WORK* wk) {
    u16 sw = exsw_1 & 3;
    switch (sw) {
    case 0:
        wk->position_x += 104;
        wk->position_y += 96;
        break;
    case 1:
        wk->position_x += 136;
        wk->position_y += 112;
        break;
    case 2:
        wk->position_x += 168;
        wk->position_y += 128;
        break;
    case 3:
        wk->position_x += 200;
        wk->position_y += 136;
        break;
    }
}


/* provisional name */
void debug_ghost_shift_up(WORK* wk) {
    u16 sw = exsw_1 & 6;
    switch (sw) {
    case 0:
        wk->position_y += 96;
        break;
    case 2:
        wk->position_y += 112;
        break;
    case 4:
        wk->position_y += 128;
        break;
    case 6:
        wk->position_y += 136;
        break;
    }
}


/* provisional name */
void debug_draw_record_ghosts(void) {
    u16 sw = exsw_1 & 1;
    s16 i;
    WORK_Other* ewk;
    if (sw == 0) {
        return;
    }
    if (!Debug_Rec_Count) {
        return;
    } else {
        if (dbg_save_mode) {
            if (Debug_Rec_Frame > 0) {
                for (i = 0; i < 2; i++) {
                    ewk = dbg_ghost_ewk[i][0];
                    debug_snapshot_to_ghost((WORK*)ewk, &dbg_snap_w[i][Debug_Rec_Frame]);
                    ewk->wu.my_priority += 4;
                    ewk->wu.position_z = ewk->wu.my_priority;
                    debug_ghost_shift_left(&ewk->wu);
                    ewk->wu.old_cgnum = 0;
                    debug_char_disp_once(&ewk->wu);
                }
            }
            if (Debug_Rec_Frame < Debug_Rec_Count) {
                for (i = 0; i < 2; i++) {
                    ewk = dbg_ghost_ewk[i][2];
                    debug_snapshot_to_ghost((WORK*)ewk, &dbg_snap_w[i][Debug_Rec_Frame + 1]);
                    ewk->wu.my_priority += 4;
                    ewk->wu.position_z = ewk->wu.my_priority;
                    debug_ghost_shift_right(&ewk->wu);
                    ewk->wu.old_cgnum = 0;
                    debug_char_disp_once(&ewk->wu);
                }
            }
        } else {
            if (Debug_Rec_Frame > 1) {
                for (i = 0; i < 2; i++) {
                    ewk = dbg_ghost_ewk[i][0];
                    debug_snapshot_to_ghost((WORK*)ewk, &dbg_snap_w[i][Debug_Rec_Frame - 1]);
                    ewk->wu.my_priority += 4;
                    ewk->wu.position_z = ewk->wu.my_priority;
                    debug_ghost_shift_left(&ewk->wu);
                    ewk->wu.old_cgnum = 0;
                    debug_char_disp_once(&ewk->wu);
                }
            }
            for (i = 0; i < 2; i++) {
                ewk = dbg_ghost_ewk[i][1];
                debug_snapshot_to_ghost((WORK*)ewk, &dbg_snap_w[i][Debug_Rec_Frame]);
                ewk->wu.my_priority += 2;
                ewk->wu.position_z = ewk->wu.my_priority;
                debug_ghost_shift_up(&ewk->wu);
                ewk->wu.old_cgnum = 0;
                debug_char_disp_once(&ewk->wu);
            }
            if (Debug_Rec_Frame < Debug_Rec_Count) {
                for (i = 0; i < 2; i++) {
                    ewk = dbg_ghost_ewk[i][2];
                    debug_snapshot_to_ghost((WORK*)ewk, &dbg_snap_w[i][Debug_Rec_Frame + 1]);
                    ewk->wu.my_priority += 4;
                    ewk->wu.position_z = ewk->wu.my_priority;
                    debug_ghost_shift_right(&ewk->wu);
                    ewk->wu.old_cgnum = 0;
                    debug_char_disp_once(&ewk->wu);
                }
            }
        }
    }
}


const char object_edit_all_msg[32] = "OBJECT EDIT  -ALL CHAR VERSION-";


/* provisional name */
void debug_hit_judgment_dispatch(void) {
    void (*Hit_Tbl[2])() = { debug_hit_judgment_init, debug_hit_judgment_move };
    dbg_pl = &plw[Debug_PL_id];
    dbg_slot = (DBG_SLOT*)(dbg_slot_w + Debug_PL_id);
    dbg_judge_ewk = (WORK_Other_JUDGE*)&frw[dbg_judge_eff_ix][0];
    Hit_Tbl[Debug_Tool_No]();
}


/* provisional name */
void debug_hit_judgment_init(void) {
    s16 i;
    Debug_Tool_No++;
    tilemap_fill_all(0, 32);
    tilemap_print_string_attr(15, 1, 14, "HIT JUDGMENT");
    tilemap_print_string(0, 0, 0xFFFF, dbg_obj_info_str);
    tilemap_print_string(0, 0, 0xFFFF, dbg_hit_size_str);
    tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_hit_part_str);
    for (i = 0; i < 21; i++) {
        Debug_Rep_Timer[i] = 0;
        Debug_Rep_Count[i] = 0;
    }
    Debug_PL_id = 0;
    Debug_Hit_Sub = 0;
    Debug_Box_Edit = 0;
    dbg_copy_done = 0;
    Debug_Snap_Disp = 0;
    dbg_cmd_panel = 0;
    Debug_Dec_Disp = 0;
    debug_both_players_reset();
    debug_slot_char_load();
    debug_motion_list_count();
    plw[1].wu.rl_flag = 1;
    dbg_look_buf.judge = dbg_look_judge;
    dbg_look_buf.body_adrs = (u8*)dbg_look_body;
    dbg_look_buf.attack_adrs = (u8*)dbg_look_attack;
    dbg_look_buf.caught_adrs = dbg_look_caught;
    dbg_look_buf.hosei_adrs = dbg_look_hosei;
    dbg_copy_buf.judge = dbg_copy_judge;
    dbg_copy_buf.body_adrs = dbg_copy_buf.h_bod = dbg_copy_body;
    dbg_copy_buf.attack_adrs = dbg_copy_buf.h_att = dbg_copy_attack;
    dbg_copy_buf.caught_adrs = dbg_copy_buf.h_cau = dbg_copy_caught;
    dbg_copy_buf.hosei_adrs = dbg_copy_buf.h_hos = dbg_copy_hosei;
    dbg_edit_buf.judge = dbg_edit_judge;
    dbg_edit_buf.body_adrs = dbg_edit_buf.h_bod = dbg_edit_body;
    dbg_edit_buf.attack_adrs = dbg_edit_buf.h_att = dbg_edit_attack;
    dbg_edit_buf.caught_adrs = dbg_edit_buf.h_cau = dbg_edit_caught;
    dbg_edit_buf.hosei_adrs = dbg_edit_buf.h_hos = dbg_edit_hosei;
    debug_set_all_boxes(0);
    debug_pattern_list_build();
    debug_edit_pattern_timer_update();
    dbg_judge_ewk->curr_ja = 0;
    dbg_judge_ewk->look_up_flag = 0;
    dbg_edit_box = (s16*)dbg_look_buf.h_bod;
}


/* provisional name */
void debug_hit_judgment_move(void) {
    WORK* wk;
    Debug_Command = 0;
    debug_hit_judgment_input();
    switch (Debug_Command) {
    case 1:
        debug_slot_char_load();
        debug_motion_list_count();
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_list_build();
        debug_edit_pattern_timer_update();
        debug_set_all_boxes(1);
        break;
    case 2:
        if (dbg_slot->sel[0] > 0x90) {
            set_char_move_init(&dbg_pl->wu, 0, dbg_slot->sel[1] - 1);
        } else {
            set_char_move_init(&dbg_pl->wu, dbg_slot->row, dbg_slot->sel[1] - 1);
        }
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (dbg_pl->wu.disp_flag == 0) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_list_build();
        debug_edit_pattern_timer_update();
        debug_set_all_boxes(1);
        break;
    case 4:
        debug_pattern_preview_step(&dbg_pl->wu);
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (dbg_pl->wu.disp_flag == 0) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        debug_edit_pattern_timer_update();
        debug_set_all_boxes(dbg_slot->sel[2]);
        break;
    case 5:
        wk = &dbg_pl->wu;
        dbg_pl->wu.cg_ctr = 1;
        debug_pattern_preview_step(wk);
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (dbg_pl->wu.disp_flag == 0) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        debug_edit_pattern_timer_update();
        debug_set_all_boxes(dbg_slot->sel[2]);
        break;
    }
    debug_char_disp((WORK*)&plw[0]);
    debug_char_disp((WORK*)&plw[1]);
    debug_draw_object_info();
    debug_draw_hit_edit_info();
}


/* provisional name */
void debug_catch_judgment_dispatch(void) {
    void (*Catch_Tbl[2])() = { debug_catch_judgment_init, debug_catch_judgment_run };
    dbg_pl = &plw[Debug_PL_id];
    dbg_slot = (DBG_SLOT*)(dbg_slot_w + Debug_PL_id);
    Catch_Tbl[Debug_Tool_No]();
    if (!Debug_PL_id) {
        dbg_slot = (DBG_SLOT*)dbg_slot_w[0];
    }
    debug_draw_object_info();
    debug_draw_position_delta();
    debug_draw_edit_side();
    debug_draw_cm_summary();
}


/* provisional name */
void debug_catch_judgment_init(void) {
    s16 i;
    Debug_Tool_No++;
    tilemap_fill_all(0, 32);
    tilemap_print_string_attr(15, 1, 14, dbg_catch_judge_title);
    tilemap_print_string(0, 0, 0xFFFF, dbg_obj_info_str);
    tilemap_print_string(0, 0, 0xFFFF, dbg_obj_rel_str);
    debug_both_players_reset();
    for (i = 0; i < 21; i++) {
        Debug_Rep_Timer[i] = 0;
        Debug_Rep_Count[i] = 0;
    }
    Debug_PL_id = 0;
    dbg_cmd_panel = 0;
    Debug_Snap_Disp = 0;
    Debug_Dec_Disp = 0;
    for (i = 0; i < 2; i++) {
        dbg_pl = &plw[i];
        dbg_slot = (DBG_SLOT*)(dbg_slot_w + i);
        debug_slot_char_load();
        debug_motion_list_count();
        debug_pattern_count();
        debug_pattern_timer_update();
    }
}


/* provisional name */
void debug_catch_judgment_run(void) {
    Debug_Command = 0;
    debug_catch_judgment_input();
    switch (Debug_Command) {
    case 1:
        debug_slot_char_load();
        debug_motion_list_count();
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_timer_update();
        debug_pattern_count();
        break;
    case 2:
        if (dbg_slot->sel[0] > 0x90) {
            set_char_move_init(&dbg_pl->wu, 0, dbg_slot->sel[1] - 1);
        } else {
            set_char_move_init(&dbg_pl->wu, dbg_slot->row, dbg_slot->sel[1] - 1);
        }
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (dbg_pl->wu.disp_flag == 0) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_timer_update();
        debug_pattern_count();
        break;
    case 4:
        char_move(&dbg_pl->wu);
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (dbg_pl->wu.disp_flag == 0) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        if (dbg_slot->sel[2] != dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type) {
            Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
            dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
            Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
            dbg_slot->sel[2] = dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type;
        }
        debug_pattern_timer_update();
        dbg_slot->sel[2] = dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type;
        break;
    case 5:
        char_move_z(&dbg_pl->wu);
        dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
        if (dbg_pl->wu.disp_flag == 0) {
            dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
        }
        Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
        dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
        Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
        debug_pattern_timer_update();
        dbg_slot->sel[2] = dbg_pl->wu.cg_ix / dbg_pl->wu.cgd_type;
        break;
    }
    debug_char_disp((WORK*)&plw[0]);
    debug_char_disp((WORK*)&plw[1]);
}


const char dbg_catch_judge_title[16] = "CATCH JUDJEMENT";


/* provisional name */
void debug_char_preview_dispatch(void) {
    void (*Preview_Tbl[2])() = { debug_char_preview_init, debug_char_preview_run };
    dbg_pl = plw;
    dbg_slot = (DBG_SLOT*)dbg_slot_w[0];
    Preview_Tbl[Debug_Tool_No]();
}


/* provisional name */
void debug_char_preview_init(void) {
    s16 i;
    Debug_Tool_No++;
    tilemap_fill_all(0, 32);
    tilemap_print_string(0, 0, 0xFFFF, dbg_all_char_str);
    debug_char_slot_init(0);
    debug_char_slot_init(1);
    dbg_pl->wu.be_flag = 1;
    dbg_pl->wu.disp_flag = 1;
    dbg_pl->wu.cgromtype = 1;
    dbg_pl->wu.my_family = 1;
    dbg_pl->wu.my_col_code = 0x2000;
    dbg_pl->wu.my_col_mode = 0x4200;
    dbg_pl->wu.position_x = dbg_pl->wu.xyz[0].disp.pos = 0x1B0;
    dbg_pl->wu.my_priority = 62;
    dbg_pl->wu.position_y = dbg_pl->wu.xyz[1].disp.pos = 0;
    dbg_pl->wu.xyz[2].disp.pos = dbg_pl->wu.my_priority;
    dbg_pl->wu.xyz[0].disp.low = 0;
    dbg_pl->wu.xyz[1].disp.low = 0;
    dbg_pl->wu.xyz[2].disp.low = 0;
    dbg_pl->wu.charset_id = debug_charset_tbl[0];
    plw[0].wu.cg_number = plw[1].wu.cg_number = 0;
    plw[0].wu.old_cgnum = 1;
    for (i = 0; i < 21; i++) {
        Debug_Rep_Timer[i] = 0;
        Debug_Rep_Count[i] = 0;
    }
    Debug_PL_id = 0;
    Debug_Snap_Disp = 0;
    Debug_Dec_Disp = 0;
    dbg_col_char = 0;
    dbg_cmd_panel = 0;
    Debug_Flip_Mask[0] = Debug_Flip_Work[0] = Debug_CG_Flip[0] = Debug_RL_Flag[0] = 0;
    Debug_Flip_Mask[1] = Debug_Flip_Work[1] = Debug_CG_Flip[1] = Debug_RL_Flag[1] = 0;
}

#pragma inline(debug_rgb_editor_navigate, debug_rgb_editor_print)

/* provisional name */
static void debug_rgb_editor_navigate(u16 sw) {
    if (dbg_p2sw_0 & BUTTON_LP) {
        Debug_RGB[0]--;
        if (sw & BUTTON_LP) {
            Debug_RGB[0] -= 3;
        }
    }
    if (dbg_p2sw_0 & BUTTON_MP) {
        Debug_RGB[1]--;
        if (sw & BUTTON_MP) {
            Debug_RGB[1] -= 3;
        }
    }
    if (dbg_p2sw_0 & BUTTON_HP) {
        Debug_RGB[2]--;
        if (sw & BUTTON_HP) {
            Debug_RGB[2] -= 3;
        }
    }
    if (dbg_p2sw_0 & BUTTON_LK) {
        Debug_RGB[0]++;
        if (sw & BUTTON_LK) {
            Debug_RGB[0] += 3;
        }
    }
    if (dbg_p2sw_0 & BUTTON_MK) {
        Debug_RGB[1]++;
        if (sw & BUTTON_MK) {
            Debug_RGB[1] += 3;
        }
    }
    if (dbg_p2sw_0 & BUTTON_HK) {
        Debug_RGB[2]++;
        if (sw & BUTTON_HK) {
            Debug_RGB[2] += 3;
        }
    }
    Debug_RGB[0] &= 0x7F;
    Debug_RGB[1] &= 0x7F;
    Debug_RGB[2] &= 0x7F;
}

/* provisional name */
static void debug_rgb_editor_print(s16 print) {
    u16 r, g, b;
    s32 green, blue;
    s32 word;
    s32 part;
    r = Debug_RGB[0] >> 2;
    r &= 0x1F;
    g = Debug_RGB[1] >> 2;
    g &= 0x1F;
    b = Debug_RGB[2] >> 2;
    b &= 0x1F;
    if (print) {
        tilemap_print_hex(13, 12, 2, r, 2, 0);
        tilemap_print_hex(13, 13, 2, green = g, 2, 0);
        tilemap_print_hex(13, 14, 2, blue = b, 2, 0);
    }
    word = blue << 10;
    part = green << 5;
    *(u16*)COLOR_RAM = (word | part | r) & 0x7FFF;
}

/* provisional name */
void debug_char_preview_run(void) {
    u16 group;
    s16 base;
    s16 pal;
    u16 shown;
    u16 code;
    debug_position_by_pad();
    if (debug_lever_repeat(dbg_p1sw_0, dbg_p1sw_1, LEVER_UP, 0)) {
        dbg_pl->wu.cg_number -= 1;
        if (dbg_pl->wu.cg_number > 0x7827) {
            dbg_pl->wu.cg_number = 0x7827;
        }
    }
    if (debug_lever_repeat(dbg_p1sw_0, dbg_p1sw_1, LEVER_DOWN, 1)) {
        dbg_pl->wu.cg_number += 1;
        if (dbg_pl->wu.cg_number > 0x7827) {
            dbg_pl->wu.cg_number = 0;
        }
    }
    if (debug_lever_repeat(dbg_p1sw_0, dbg_p1sw_1, LEVER_LEFT, 2)) {
        dbg_pl->wu.cg_number -= 0x80;
        if (dbg_pl->wu.cg_number > 0x7827) {
            dbg_pl->wu.cg_number = 0x7827;
        }
    }
    if (debug_lever_repeat(dbg_p1sw_0, dbg_p1sw_1, LEVER_RIGHT, 3)) {
        dbg_pl->wu.cg_number += 0x80;
        if (dbg_pl->wu.cg_number > 0x7827) {
            dbg_pl->wu.cg_number = 0;
        }
    }
    if (dbg_pl->wu.cg_number < 0x3C00) {
        pal = dbg_pl->wu.cg_number / 0x400;
        if (pal != dbg_col_char) {
            dbg_col_char = pal;
            load_player_color(dbg_col_char, 0, 0);
        }
    } else {
        if (dbg_pl->wu.cg_number > 0x4000 && dbg_pl->wu.cg_number < 0x4020) {
            dbg_col_char = 20;
        }
        if (dbg_pl->wu.cg_number > 0x4020 && dbg_pl->wu.cg_number < 0x4090) {
            if (dbg_col_char != 21) {
                dbg_col_char = 21;
            }
        }
    }
    tilemap_print_hex(10, 7, 2, dbg_pl->wu.cg_number, 4, 0);
    group = debug_cg_group_index(plw[0].wu.cg_number);
    tilemap_print_string(0, 0, 0xFFFF, &dbg_preview_group_str[group]);
    base = dbg_cg_group_top_tbl[group];
    base = plw[0].wu.cg_number - base;
    tilemap_print_hex(10, 5, 2, base, 4, 0);
    dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
    if (dbg_pl->wu.disp_flag == 0) {
        dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
    }
    shown = get_cg_slot_no(dbg_pl->wu.cg_number);
    if (dbg_pl->zuru_timer != shown) {
        code = dbg_cg_group_top_tbl[(dbg_pl->zuru_timer & 0x7FFF) / 4];
        if (code != 0x4000 && code != 0x4090) {
            purge_char_gfx(code);
        }
        dbg_pl->zuru_timer = shown;
    }
    dbg_pl->wu.cg_olc_ix = dbg_pl->wu.cg_olc_ix = 0;
    debug_char_disp(&dbg_pl->wu);
}


/* provisional names: the sixth debug tool, a BG viewer for etc BG 4 */
void debug_bg_test_dispatch(void) {
    void (*Test_Tbl[2])() = { debug_bg_test_init, debug_bg_test_run };
    dbg_slot = (DBG_SLOT*)dbg_slot_w[0];
    Test_Tbl[Debug_Tool_No]();
}



void debug_bg_test_init(void) {
    const BG_GFX* gfx;
    const s16* ptr;
    s16 i;
    s16 j;
    u8 mode;
    Family_Init();
    clear_scroll_layer_state_and_mask();
    scrn_pos_clear();
    Zoomf_Init();
    Debug_Tool_No++;
    tilemap_fill_all(0, 32);
    scr_cg_c_no = simmram_block_alloc_10(0x400, 1);
    bg_w.scroll_cg_adr = simmram_slot_to_offset(scr_cg_c_no);
    bg_w.scno = use_scr2[4];
    load_any_color(10);
    gfx = &etc_bg_gfx_tbl[4];
    polygon2d_submit_line(gfx->prep, 0, 0, 3);
    mode = gfx->mode;
    polygon2d_submit_line(gfx->src, bg_w.scroll_cg_adr, gfx->size, mode);
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
        ptr = bg_map_tbl2[4][i];
        sprite_list_setup(i, 1, ptr);
        bg_w.bgw[i].r_no_1 = bg_w.bgw[i].r_no_2 = 0;
        bg_w.bgw[i].fam_no = i;
    }
    bg_etc_scr_write(4);
    for (j = 0; j < bg_w.scno; j++) {
        Bg_Off_R(16 << j);
        Bg_On_R(1 << j);
        scrn_attr_set(j, 0, 31);
        scrn_reg_w[j].ctrl &= 0xFE7F;
        bg_w.bgw[j].hos_xy[0].cal = bg_w.bgw[j].wxy[0].cal = bg_w.bgw[j].xy[0].cal = bg_pos_tbl2[4][j][0];
        bg_w.bgw[j].hos_xy[1].cal = bg_w.bgw[j].wxy[1].cal = bg_w.bgw[j].xy[1].cal = bg_pos_tbl2[4][j][1];
        bg_w.bgw[j].old_pos_x = bg_w.bgw[j].pos_x_work = bg_w.bgw[j].xy[0].disp.pos;
        bg_w.bgw[j].pos_y_work = bg_w.bgw[j].xy[1].disp.pos;
        bg_w.bgw[j].speed_x = msp2[4][j][0];
        bg_w.bgw[j].speed_y = msp2[4][j][1];
        bg_w.bgw[j].rewrite_flag = 0;
        bg_w.bgw[j].zuubun = etc_bg_zuubun_tbl[4][j];
        bg_w.bgw[j].xy[1].disp.pos = bg_w.bgw[j].wxy[1].disp.pos = bg_w.bgw[j].pos_y_work = 0;
    }
    ptr = etc_bg_limit_tbl[4];
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
    bg_w.bg_f_x = 9;
    bg_w.old_bg_f_x = 9;
    bg_w.bg_f_y = 9;
    bg_w.old_bg_f_y = 9;
    bg_w.dmm1 = 1;
    bg_w.bg2_sp_x2 = bg_w.bg2_sp_x = 0;
    bg_sp_work = 0;
    bg_zoom_x_pos = 0xC0;
    bg_w.quake_x_index = 0;
    bg_w.quake_y_index = 0;
}


void debug_bg_test_run(void) {
    u16* adrs;
    u16* p;
    u16 cell;
    s16 i;
    s16 j;
    switch (bg_w.bgw[0].r_no_1) {
    case 0:
        bg_w.bgw[0].r_no_1++;
        bg_w.bgw[0].l_limit = 2;
        bg_w.bgw[0].r_limit = 64;
        break;
    case 1:
        bg_w.bgw[0].l_limit--;
        if (bg_w.bgw[0].l_limit >= 0) {
            break;
        } else {
        }
        bg_w.bgw[0].r_limit++;
        bg_w.bgw[0].l_limit = 2;
        if (bg_w.bgw[0].r_limit >= 95) {
            bg_w.bgw[0].r_no_1++;
            bg_w.bgw[0].l_limit = 16;
        }
        adrs = bg_w.bgw[0].bg_address + 0x1820;
        for (i = 0; i < 16; i++) {
            p = adrs;
            for (j = 0; j < 32; j++) {
                cell = *++p;
                cell &= 0xFE00;
                cell |= 0x40;
                cell |= bg_w.bgw[0].r_limit;
                *p = cell;
                p++;
            }
            adrs += 0x80;
        }
        break;
    case 2:
        bg_w.bgw[0].l_limit--;
        if (bg_w.bgw[0].l_limit < 0) {
            bg_w.bgw[0].r_no_1 = 0;
        }
        break;
    }
}


/* provisional name */
/* The first loop writes slot 0 eight times. */
void debug_char_slot_init(id)
s16 id;
{
    PLW* save_wk;
    s16* save_sp;
    PLW* wk;
    s16* sp;
    s16 i;
    s16* p = dbg_slot_w[id];

    for (i = 0; i < 8; i++) {
        p[0] = 1;
    }
    sp = dbg_slot_w[id];
    sp[8] = 0;
    wk = &plw[id];
    wk->player_number = 0;
    wk->wu.charset_id = debug_charset_tbl[0];
    wk->zuru_timer = 0;
    save_wk = dbg_pl;
    dbg_pl = wk;
    save_sp = (s16*)dbg_slot;
    dbg_slot = (DBG_SLOT*)sp;
    dbg_pl->wu.id = id;
    debug_char_init();
    dbg_pl->wu.disp_flag = 0;
    dbg_pl = save_wk;
    dbg_slot = (DBG_SLOT*)save_sp;
}


/* provisional name */
void debug_edit_slots_reset(void) {
    s16 i;
    s16* sp = dbg_slot_w[0];

    for (i = 0; i < 2; i++) {
        s16* p = sp;
        sp[0] = 1;
        p[1] = 1;
        p[2] = 0;
        p[3] = 1;
        p[8] = 0;
        sp += 9;
    }
}


/* provisional name */
s32 debug_slot_all_select(u16 sw)
{
    s16 moved;
    s16 row;
    if (!(dbg_p1sw_0 & BUTTON_START)) {
        return 0;
    }
    if (!(dbg_p1sw_0 & (LEVER_UP | LEVER_DOWN))) {
        return 0;
    }
    moved = 0;
    if (debug_lever_repeat(dbg_p1sw_0, dbg_p1sw_1, LEVER_UP, 0)) {
        dbg_slot->sel[0]--;
        if (dbg_slot->sel[0] < 1) {
            dbg_slot->sel[0] = dbg_slot->sel0_max;
        }
        moved = 1;
    } else if (debug_lever_repeat(dbg_p1sw_0, dbg_p1sw_1, LEVER_DOWN, 1)) {
        dbg_slot->sel[0]++;
        moved = 1;
        if (dbg_slot->sel[0] > dbg_slot->sel0_max) {
            dbg_slot->sel[0] = 1;
        }
    }
    if (dbg_slot->sel[0] <= 0x90) {
        if (dbg_slot->sel[0] < 10) {
            row = dbg_slot->sel[0] - 1;
        } else {
            row = (dbg_slot->sel[0] - 1) % 9;
        }
        if (row >= 8) {
            row++;
        }
        dbg_slot->row = row;
    } else {
        dbg_slot->row = 0;
    }
    if (moved) {
        return 1;
    }
    return 0;
}


/* provisional name */
s32 debug_slot_motion_select(void) {
    if (debug_lever_repeat(dbg_p1sw_0, dbg_p1sw_1, LEVER_RIGHT, 3)) {
        dbg_slot->sel[1]++;
        if (dbg_slot->sel[1] > dbg_slot->sel1_max) {
            dbg_slot->sel[1] = 1;
        }
        return 2;
    } else if (debug_lever_repeat(dbg_p1sw_0, dbg_p1sw_1, LEVER_LEFT, 2)) {
        dbg_slot->sel[1]--;
        if (dbg_slot->sel[1] < 1) {
            dbg_slot->sel[1] = dbg_slot->sel1_max;
        }
        return 2;
    }
    return 0;
}


#pragma inline(debug_check_step, debug_check_rec_step, debug_check_step_z, debug_check_rec_frame)
#pragma inline(debug_pl_id_input, debug_record_sw_check, debug_dec_disp_input)

/* provisional name: command 4 (step one frame) on P1 button 1 */
s32 debug_check_step(void) {
    if (dbg_p1sw_0 & BUTTON_LP) {
        return 4;
    }
    return 0;
}


/* provisional name: command 6 (next recorded frame) on P2 button 1 */
s32 debug_check_rec_step(void) {
    if (Debug_Rec_Count != 0) {
        if (dbg_p2sw_0 & BUTTON_LP) {
            return 6;
        }
    }
    return 0;
}


/* provisional name: command 5 on button 2 */
s32 debug_check_step_z(u16 sw) {
    if (sw & BUTTON_MP) {
        return 5;
    }
    return 0;
}


/* provisional name: command 7 (restart recorded frame) on button 2 */
s32 debug_check_rec_frame(u16 sw) {
    if (Debug_Rec_Count != 0 && (sw & BUTTON_MP) != 0) {
        return 7;
    }
    return 0;
}


/* provisional name */
s32 debug_flip_cycle(u16 sw) {
    if (sw & BUTTON_LK) {
        dbg_pl->wu.cg_flip++;
        dbg_pl->wu.cg_flip &= 3;
        Debug_Flip_Mask[dbg_pl->wu.id]++;
        Debug_Flip_Mask[dbg_pl->wu.id] &= 3;
        return 3;
    }
    return 0;
}


/* provisional name */
s32 debug_priority_swap(u16 sw) {
    if (sw & BUTTON_HP) {
        if (plw[0].wu.my_priority == 50) {
            plw[0].wu.my_priority = 51;
            plw[1].wu.my_priority = 50;
        } else {
            plw[0].wu.my_priority = 50;
            plw[1].wu.my_priority = 51;
        }
        return 3;
    }
    if ((plw[0].wu.my_priority == 50 && plw[1].wu.my_priority == 51)
        || (plw[1].wu.my_priority == 50 && plw[0].wu.my_priority == 51)) {
        return 0;
    }
    if (plw[0].wu.my_priority <= plw[1].wu.my_priority) {
        plw[0].wu.my_priority = 50;
        plw[1].wu.my_priority = 51;
    } else {
        plw[0].wu.my_priority = 51;
        plw[1].wu.my_priority = 50;
    }
    return 0;
}


/* provisional name */
void debug_move_record_start(u16 sw) {
    s16 n;
    if (sw & BUTTON_MK) {
        if (Debug_Rec_Count != 0) {
            dbg_rec_menu = 15;
        } else {
            dbg_rec_menu = 0;
            n = debug_catch_move_record(dbg_snap_w[0], dbg_snap_w[1]);
            if (n != 0) {
                dbg_rec_exist = 1;
                Debug_Rec_Frame = 1;
            } else {
                Debug_Rec_Count = 0;
                Debug_Rec_Frame = 0;
            }
            dbg_snap_req = 1;
            Debug_Play_Flag = 1;
        }
    }
}


/* provisional name */
void debug_pl_id_input(u16 sw) {
    if (sw & BUTTON_HP) {
        Debug_PL_id ^= 1;
    }
}


/* provisional name */
s32 debug_record_sw_check(u16 sw) {
    if (sw & BUTTON_LK) {
        return 8;
    }
    return 0;
}


/* provisional name */
void debug_record_frame_adjust(u16 sw) {
    if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, BUTTON_MK, 19)) {
        dbg_snap_ptr->cg_ctr++;
    }
    if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, BUTTON_HK, 20)) {
        dbg_snap_ptr->cg_ctr--;
        if (dbg_snap_ptr->cg_ctr < 0) {
            dbg_snap_ptr->cg_ctr = 0;
        }
    }
}

/* provisional name */
void debug_move_record_menu(void)
{
    u16 sw;
    s16 i;
    s16 next;

    if (Debug_Rec_Count) {
        tilemap_print_string(0, 0, 0xFFFF, dbg_rec_menu_str);
    } else {
        tilemap_print_string(0, 0, 0xFFFF, dbg_rec_nodata_str);
    }
    sw = ~dbg_p1sw_1 & dbg_p1sw_0;
    if (sw & BUTTON_LK) {
        /* clear all recorded frames */
        tilemap_print_string(0, 0, 0xFFFF, dbg_rec_clear_str);
        Debug_Rec_Frame = 0;
        Debug_Rec_Count = 0;
        dbg_save_mode = 2;
        dbg_snap_req = 0;
        dbg_rec_menu = 0;
        dbg_rec_exist = 0;
        Debug_Play_Flag = 0;
    }
    if (sw & BUTTON_MK) {
        /* delete the current frame: pull the following snapshots down one slot */
        tilemap_print_string(0, 0, 0xFFFF, dbg_rec_clear_str);
        for (i = Debug_Rec_Frame; i < Debug_Rec_Count; i++) {
            next = i + 1;
            debug_copy_player_snapshot(&dbg_snap_w[0][next], &dbg_snap_w[0][i]);
            debug_copy_player_snapshot(&dbg_snap_w[1][next], &dbg_snap_w[1][i]);
        }
        Debug_Rec_Count--;
        dbg_rec_menu = 0;
        dbg_snap_req = 1;
        Debug_Play_Flag = 1;
    }
    if (sw & BUTTON_HK) {
        tilemap_print_string(0, 0, 0xFFFF, dbg_rec_clear_str);
        dbg_rec_menu = 0;
    }
}

/* provisional name */
void debug_playback_mode_cycle(u16 sw) {
    if ((sw & BUTTON_HK) != 0) {
        if (Debug_Rec_Count != 0) {
            dbg_rec_exist = 1;
            dbg_save_mode++;
            if (dbg_save_mode > 2) {
                dbg_save_mode = 0;
            }
        }
    }
}


/* provisional name */
void debug_position_by_pad(void) {
    if (!(dbg_p1sw_0 & BUTTON_START)) {
        if (dbg_p1sw_0 & LEVER_DOWN) {
            debug_bg_scroll_by_pad();
            return;
        }
        if ((dbg_p1sw_0 & LEVER_UP) && (dbg_p2sw_0 & LEVER_ALL)) {
            debug_bg_position_reset();
        }
    }
    if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, LEVER_UP, 4)) {
        dbg_pl->wu.xyz[1].disp.pos++;
    }
    if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, LEVER_DOWN, 5)) {
        dbg_pl->wu.xyz[1].disp.pos--;
    }
    if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, LEVER_LEFT, 6)) {
        dbg_pl->wu.xyz[0].disp.pos--;
    }
    if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, LEVER_RIGHT, 7)) {
        dbg_pl->wu.xyz[0].disp.pos++;
    }
}


/* provisional name: debug_bg_scroll_by_pad for BG layer 0 only, unreferenced */
void debug_bg0_scroll_by_pad(void) {
    if (p2sw_0 & LEVER_LEFT) {
        bg_w.bgw[0].position_x--;
        bg_w.bgw[0].xy[0].disp.pos--;
    }
    if (p2sw_0 & LEVER_RIGHT) {
        bg_w.bgw[0].position_x++;
        bg_w.bgw[0].xy[0].disp.pos++;
    }
    if (p2sw_0 & LEVER_UP) {
        bg_w.bgw[0].position_y++;
        bg_w.bgw[0].xy[1].disp.pos++;
    }
    if (p2sw_0 & LEVER_DOWN) {
        bg_w.bgw[0].position_y--;
        bg_w.bgw[0].xy[1].disp.pos--;
    }
    Bg_Family_Set();
}


/* provisional name */
void debug_bg_position_reset(void) {
    s16 i;
    i = 0;
    while (i < bg_w.scno) {
        bg_w.bgw[i].xy[0].disp.pos = 0x100;
        bg_w.bgw[i].xy[1].disp.pos = 0;
        bg_w.bgw[i].xy[0].disp.low = 0;
        bg_w.bgw[i].xy[1].disp.low = 0;
        bg_w.bgw[i].position_x = 0x100;
        bg_w.bgw[i].position_y = 0;
        i++;
    }
    Bg_Family_Set();
}


#pragma inline(bg_pos_disp)
static void bg_pos_disp(s16 pos, s16 position_x) {}

/* provisional name */
void debug_bg_scroll_by_pad(void) {
    s16 i;
    if (p2sw_0 & LEVER_LEFT) {
        for (i = 0; i < bg_w.scno; i++) {
            bg_w.bgw[i].position_x--;
            bg_w.bgw[i].xy[0].disp.pos--;
        }
    }
    if (p2sw_0 & LEVER_RIGHT) {
        for (i = 0; i < bg_w.scno; i++) {
            bg_w.bgw[i].position_x++;
            bg_w.bgw[i].xy[0].disp.pos++;
        }
    }
    if (p2sw_0 & LEVER_UP) {
        for (i = 0; i < bg_w.scno; i++) {
            bg_w.bgw[i].position_y++;
            bg_w.bgw[i].xy[1].disp.pos++;
        }
    }
    if (p2sw_0 & LEVER_DOWN) {
        for (i = 0; i < bg_w.scno; i++) {
            bg_w.bgw[i].position_y--;
            bg_w.bgw[i].xy[1].disp.pos--;
        }
    }
    if (!bg_w.stage) {
        bg_w.bgw[4].hos_xy[0].cal = bg_w.bgw[4].xy[0].cal = bg_w.bgw[0].xy[0].cal;
        bg_w.bgw[4].hos_xy[0].cal = bg_w.bgw[4].xy[1].cal = bg_w.bgw[0].xy[1].cal;
        bg_pos_disp(bg_w.bgw[4].xy[0].disp.pos, bg_w.bgw[4].position_x);
    }
    Bg_Family_Set();
}


/* provisional name */
void debug_hit_box_edit(void) {
    u8* body;
    u8* attack;
    s16* box;
    u16 pad;
    pad = ~dbg_p2sw_1 & dbg_p2sw_0;
    if (pad & BUTTON_MP) {
        dbg_judge_ewk->look_up_flag ^= 1;
    }
    if (Debug_Box_Edit) {
        body = dbg_copy_buf.h_bod;
        attack = dbg_copy_buf.h_att;
        switch (dbg_judge_ewk->curr_ja) {
        case 0:
            box = (s16*)body;
            break;
        case 1:
            box = (s16*)(body + 8);
            break;
        case 2:
            box = (s16*)(body + 16);
            break;
        case 3:
            box = (s16*)(body + 24);
            break;
        case 4:
            box = (s16*)(body + 32);
            break;
        case 5:
            box = (s16*)attack;
            break;
        case 6:
            box = (s16*)(attack + 8);
            break;
        case 7:
            box = (s16*)(attack + 16);
            break;
        case 8:
            box = (s16*)dbg_copy_buf.h_cau;
            break;
        case 9:
            box = (s16*)dbg_copy_buf.h_hos;
            break;
        }
        dbg_edit_box = box;
    } else if (dbg_judge_ewk->look_up_flag) {
        pad = dbg_p2sw_0;
        body = dbg_look_buf.h_bod;
        attack = dbg_look_buf.h_att;
        switch (dbg_judge_ewk->curr_ja) {
        case 0:
            box = (s16*)body;
            break;
        case 1:
            box = (s16*)(body + 8);
            break;
        case 2:
            box = (s16*)(body + 16);
            break;
        case 3:
            box = (s16*)(body + 24);
            break;
        case 4:
            box = (s16*)(body + 32);
            break;
        case 5:
            box = (s16*)attack;
            break;
        case 6:
            box = (s16*)(attack + 8);
            break;
        case 7:
            box = (s16*)(attack + 16);
            break;
        case 8:
            box = (s16*)dbg_look_buf.h_cau;
            break;
        case 9:
            box = (s16*)dbg_look_buf.h_hos;
            break;
        }
        dbg_edit_box = box;
        if (!Debug_Box_Edit) {
            if (pad & BUTTON_LP) {
                if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, LEVER_UP, 4)) {
                    box[3] = box[3] + 1;
                }
                if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, LEVER_DOWN, 5)) {
                    box[3]--;
                    if (box[3] < 0) {
                        box[3] = 0;
                    }
                }
                if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, LEVER_RIGHT, 7)) {
                    box[1]++;
                }
                if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, LEVER_LEFT, 6)) {
                    box[1]--;
                    if (box[1] < 0) {
                        box[1] = 0;
                    }
                }
            } else {
                if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, LEVER_UP, 4)) {
                    box[2]++;
                }
                if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, LEVER_DOWN, 5)) {
                    box[2]--;
                }
                if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, LEVER_LEFT, 6)) {
                    box[0] = box[0] - 1;
                }
                if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, LEVER_RIGHT, 7)) {
                    box[0]++;
                }
            }
        }
    } else {
        body = dbg_edit_buf.h_bod;
        attack = dbg_edit_buf.h_att;
        switch (dbg_judge_ewk->curr_ja) {
        case 0:
            box = (s16*)body;
            break;
        case 1:
            box = (s16*)(body + 8);
            break;
        case 2:
            box = (s16*)(body + 16);
            break;
        case 3:
            box = (s16*)(body + 24);
            break;
        case 4:
            box = (s16*)(body + 32);
            break;
        case 5:
            box = (s16*)attack;
            break;
        case 6:
            box = (s16*)(attack + 8);
            break;
        case 7:
            box = (s16*)(attack + 16);
            break;
        case 8:
            box = (s16*)dbg_edit_buf.h_cau;
            break;
        case 9:
            box = (s16*)dbg_edit_buf.h_hos;
            break;
        }
        dbg_edit_box = box;
    }
}


/* provisional name */
void debug_set_dummy_box(void) {
}


/* provisional name */
void debug_set_body_box(s16 n) {
    dbg_look_buf.h_bod = dbg_look_buf.body_adrs + n * 40;
    dbg_edit_buf.h_bod = dbg_edit_buf.body_adrs + n * 40;
}


/* provisional name */
void debug_set_attack_box(s16 n) {
    dbg_look_buf.h_att = dbg_look_buf.attack_adrs + n * 24;
    dbg_edit_buf.h_att = dbg_edit_buf.attack_adrs + n * 24;
}


/* provisional name */
void debug_set_caught_box(s16 n) {
    dbg_look_buf.h_cau = dbg_look_buf.caught_adrs + n * 8;
    dbg_edit_buf.h_cau = dbg_edit_buf.caught_adrs + n * 8;
}


/* provisional name */
void debug_set_hosei_box(s16 n) {
    dbg_look_buf.h_hos = dbg_look_buf.hosei_adrs + n * 8;
    dbg_edit_buf.h_hos = dbg_edit_buf.hosei_adrs + n * 8;
}


/* Point every hit-box cursor of the look and edit buffers at box number n. */
/* provisional name */
void debug_set_all_boxes(n)
s16 n;
{
    debug_set_dummy_box();
    debug_set_body_box(n);
    debug_set_attack_box(n);
    debug_set_caught_box(n);
    debug_set_hosei_box(n);
}


/* provisional name */
void debug_hit_box_cursor(void) {
    u16 now;
    u16 sw;
    now = dbg_p2sw_0;
    sw = ~dbg_p2sw_1 & dbg_p2sw_0;
    if (now & 0x240) {
        tilemap_rect_fill(dbg_hud_x + 36, (s8)((WORK_Other*)dbg_judge_ewk)->refrected + 16, 8, 1, 2, 0xFFFF);
        if (sw & BUTTON_HP) {
            ((WORK_Other*)dbg_judge_ewk)->refrected--;
            if ((s8)((WORK_Other*)dbg_judge_ewk)->refrected < 0) {
                ((WORK_Other*)dbg_judge_ewk)->refrected = 9;
            }
        }
        if (sw & BUTTON_HK) {
            ((WORK_Other*)dbg_judge_ewk)->refrected++;
            if ((s8)((WORK_Other*)dbg_judge_ewk)->refrected > 9) {
                ((WORK_Other*)dbg_judge_ewk)->refrected = 0;
            }
        }
    }
}


/* provisional name */
void debug_memcpy_u16(u16* src, u16* dst, s16 n) {
    s16 i;
    for (i = 0; i < n; i++) {
        *dst++ = *src++;
    }
}


/* provisional name */
void debug_hit_box_copy(void) {
    u16 sw;
    sw = ~dbg_p2sw_1 & dbg_p2sw_0;
    if (sw & BUTTON_MK) {
        Debug_Box_Edit ^= 1;
        if (Debug_Box_Edit) {
            if (dbg_judge_ewk->look_up_flag) {
                debug_memcpy_u16((u16*)dbg_look_buf.h_bod, (u16*)dbg_copy_buf.h_bod, 20);
                debug_memcpy_u16((u16*)dbg_look_buf.h_att, (u16*)dbg_copy_buf.h_att, 12);
                debug_memcpy_u16((u16*)dbg_look_buf.h_cau, (u16*)dbg_copy_buf.h_cau, 4);
                debug_memcpy_u16((u16*)dbg_look_buf.h_hos, (u16*)dbg_copy_buf.h_hos, 4);
            } else {
                debug_memcpy_u16((u16*)dbg_pl->wu.h_bod, (u16*)dbg_copy_buf.h_bod, 20);
                debug_memcpy_u16((u16*)dbg_pl->wu.h_att, (u16*)dbg_copy_buf.h_att, 12);
                debug_memcpy_u16((u16*)dbg_pl->wu.h_cau, (u16*)dbg_copy_buf.h_cau, 4);
                debug_memcpy_u16((u16*)dbg_pl->wu.h_hos, (u16*)dbg_copy_buf.h_hos, 4);
            }
        } else {
            dbg_copy_done = 0;
        }
    }
    if (sw & BUTTON_LK) {
        if (Debug_Box_Edit) {
            dbg_copy_done = 1;
            dbg_copy_pat = dbg_slot->sel[2];
            dbg_copy_char = dbg_pl->wu.char_index;
            debug_set_body_box(dbg_slot->sel[2]);
            debug_memcpy_u16((u16*)dbg_copy_buf.h_bod, (u16*)dbg_look_buf.h_bod, 20);
            debug_set_attack_box(dbg_slot->sel[2]);
            debug_memcpy_u16((u16*)dbg_copy_buf.h_att, (u16*)dbg_look_buf.h_att, 12);
            debug_set_caught_box(dbg_slot->sel[2]);
            debug_memcpy_u16((u16*)dbg_copy_buf.h_cau, (u16*)dbg_look_buf.h_cau, 4);
            debug_set_hosei_box(dbg_slot->sel[2]);
            debug_memcpy_u16((u16*)dbg_copy_buf.h_hos, (u16*)dbg_look_buf.h_hos, 4);
        }
    }
}


/* provisional name */
void debug_hit_box_show_select(void) {
    u16 sw = exsw_1;
    dbg_judge_ewk->ja_disp_bit = 0;
    dbg_judge_ewk->wu.spr.gfx_cells = 0;
    if (sw & 0x100) {
        dbg_judge_ewk->ja_disp_bit |= 0x120;
        dbg_judge_ewk->wu.spr.gfx_cells += 8;
    }
    if (sw & 0x200) {
        dbg_judge_ewk->ja_disp_bit |= 0x200;
        dbg_judge_ewk->wu.spr.gfx_cells += 4;
    }
    if (sw & 0x400) {
        dbg_judge_ewk->ja_disp_bit |= 0xC0;
        dbg_judge_ewk->wu.spr.gfx_cells += 8;
    }
    if (sw & 0x800) {
        dbg_judge_ewk->ja_disp_bit |= 0x1F;
        dbg_judge_ewk->wu.spr.gfx_cells += 20;
    }
    if (sw & 0x1000) {
        dbg_judge_ewk->ja_disp_bit |= 0x400;
        dbg_judge_ewk->wu.spr.gfx_cells += 2;
    }
}


/* provisional name */
void debug_edit_common_input(void)
{
    u16 sw;

    if (Debug_Menu_No != 3) {
        debug_position_by_pad();
    }
    sw = ~dbg_p1sw_1 & dbg_p1sw_0;
    if ((Debug_Command = debug_slot_all_select(sw)) != 0) {
        return;
    }
    if ((Debug_Command = debug_slot_motion_select()) != 0) {
        return;
    }
    if ((Debug_Command = debug_check_step_z(sw)) != 0) {
        return;
    }
    if ((Debug_Command = debug_check_step()) != 0) {
        return;
    }
    Debug_Command = debug_flip_cycle(sw);
    if (sw & 0x800) {
        dbg_cmd_panel ^= 1;
        if (dbg_cmd_panel) {
            tilemap_print_string_attr(0x14, 3, 2, "1P S1 UJA ");
            tilemap_print_string_attr(0x14, 4, 2, "   S2 UJA2");
            tilemap_print_string_attr(0x14, 5, 2, "   S3 UJA3");
            tilemap_print_string_attr(0x14, 6, 2, "   S4 UJA4");
            tilemap_print_string_attr(0x14, 7, 2, "   S5  -  ");
            tilemap_print_string_attr(0x14, 8, 2, "   S6  -  ");
            tilemap_print_string_attr(0x21, 3, 2, "2P S1 ROA ");
            tilemap_print_string_attr(0x21, 4, 2, "   S2 WCA ");
            tilemap_print_string_attr(0x21, 5, 2, "   S3 UMJA");
            tilemap_print_string_attr(0x21, 6, 2, "   S4  -  ");
            tilemap_print_string_attr(0x21, 7, 2, "   S5  -  ");
            tilemap_print_string_attr(0x21, 8, 2, "   S6  -  ");
        } else {
            tilemap_print_string_attr(0x14, 3, 2, "          ");
            tilemap_print_string_attr(0x14, 4, 2, "          ");
            tilemap_print_string_attr(0x14, 5, 2, "          ");
            tilemap_print_string_attr(0x14, 6, 2, "          ");
            tilemap_print_string_attr(0x14, 7, 2, "          ");
            tilemap_print_string_attr(0x14, 8, 2, "          ");
            tilemap_print_string_attr(0x21, 3, 2, "          ");
            tilemap_print_string_attr(0x21, 4, 2, "          ");
            tilemap_print_string_attr(0x21, 5, 2, "          ");
            tilemap_print_string_attr(0x21, 6, 2, "          ");
            tilemap_print_string_attr(0x21, 7, 2, "          ");
            tilemap_print_string_attr(0x21, 8, 2, "          ");
        }
    }
}


/* provisional name */
void debug_kakusyuku_mode_cycle(u16 sw) {
    if (sw & BUTTON_HK) {
        dbg_kakusyuku_mode++;
        dbg_kakusyuku_mode &= 3;
        switch (dbg_kakusyuku_mode) {
        case 0:
            dbg_pl->wu.my_mr_flag = 0;
            dbg_pl->wu.my_mr.size.x = 63;
            dbg_pl->wu.my_mr.size.y = 63;
            dbg_zoom_x = 19;
            dbg_zoom_y = 19;
            Zoomf_Init();
            break;
        case 1:
            dbg_zoom_x = 19;
            dbg_zoom_y = 19;
            dbg_pl->wu.my_mr_flag = 0;
            break;
        case 2:
            dbg_pl->wu.my_mr_flag = 1;
            dbg_pl->wu.my_mr.size.x = 63;
            dbg_pl->wu.my_mr.size.y = 63;
            dbg_zoom_x = 19;
            dbg_zoom_y = 19;
            Zoomf_Init();
            break;
        case 3:
            Zoomf_Init();
            dbg_pl->wu.my_mr.size.x = 63;
            dbg_pl->wu.my_mr.size.y = 63;
            dbg_zoom_x = 19;
            dbg_zoom_y = 19;
            dbg_pl->wu.my_mr_flag = 1;
            break;
        }
    }
}


/* provisional name */
void debug_screen_zoom_by_pad(void) {
    if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, BUTTON_HP, 16)) {
        dbg_zoom_x--;
        dbg_zoom_y--;
        if (dbg_zoom_x > 0) {
            Frame_Down(0xC0, 0xE0, 1, 1);
        } else {
            dbg_zoom_x = 0;
            dbg_zoom_y = 0;
        }
    }
    if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, BUTTON_HK, 19)) {
        dbg_zoom_x++;
        dbg_zoom_y++;
        if (dbg_zoom_x < 38) {
            Frame_Up(0xC0, 0xE0, 1, 1);
        } else {
            dbg_zoom_x = 38;
            dbg_zoom_y = 38;
        }
    }
}


/* provisional name */
void debug_char_scale_by_pad(void) {
    if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, BUTTON_LP, 14)) {
        if (dbg_pl->wu.my_mr.size.x != 0) {
            dbg_pl->wu.my_mr.size.x--;
        }
    }
    if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, BUTTON_MP, 15)) {
        if (dbg_pl->wu.my_mr.size.y != 0) {
            dbg_pl->wu.my_mr.size.y--;
        }
    }
    if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, BUTTON_LK, 17)) {
        dbg_pl->wu.my_mr.size.x++;
        if (dbg_pl->wu.my_mr.size.x > 127) {
            dbg_pl->wu.my_mr.size.x = 127;
        }
    }
    if (debug_lever_repeat(dbg_p2sw_0, dbg_p2sw_1, BUTTON_MK, 18)) {
        dbg_pl->wu.my_mr.size.y++;
        if (dbg_pl->wu.my_mr.size.y > 127) {
            dbg_pl->wu.my_mr.size.y = 127;
        }
    }
}


/* provisional name */
void debug_kakusyuku_input(void) {
    switch (dbg_kakusyuku_mode) {
    case 1:
        debug_screen_zoom_by_pad();
        break;
    case 2:
        debug_char_scale_by_pad();
        break;
    case 3:
        debug_screen_zoom_by_pad();
        debug_char_scale_by_pad();
        break;
    }
}


/* provisional name */
void debug_dec_disp_input(u16 sw) {
    if (sw & BUTTON_START) {
        Debug_Dec_Disp ^= 1;
    }
}


/* provisional name */
void debug_cmd_panel_run(void) {
    WORK* wk;
    u16 trg = ~dbg_p1sw_1 & dbg_p1sw_0;
    u16 sel = ~dbg_p2sw_1 & dbg_p2sw_0 & BUTTON_SHOTS;
    sel = sel * 16 + (0x3F0 & trg) / 16;
    if (dbg_cmd_panel != 0) {
        wk = &dbg_pl->wu;
        switch (sel) {
        case 1:
            char_move_cmja(wk);
            break;
        case 2:
            char_move_cmj2(wk);
            break;
        case 4:
            char_move_cmj3(wk);
            break;
        case 8:
            char_move_cmj4(wk);
            break;
        case 0x100:
            char_move_cmoa(wk);
            break;
        case 0x200:
            if (wk->cg_wca_ix != -1) {
                char_move_wca(wk);
            } else {
                tilemap_print_string_attr(20, 2, 2, "NO WCA ");
            }
            break;
        case 0x400:
            if (wk->cmja.pat) {
                char_move_cmja(wk);
            } else {
                tilemap_print_string_attr(20, 2, 2, "NO CMJA");
            }
            break;
        default:
            if (trg & 0x800) {
                dbg_cmd_panel ^= 1;
            }
            goto draw;
            break;
        }
    }
    dbg_cmd_panel = 0;
    task_sleep(4);
draw:
    if (dbg_cmd_panel) {
        tilemap_print_string_attr(20, 3, 2, "1P S1 UJA ");
        tilemap_print_string_attr(20, 4, 2, "   S2 UJA2");
        tilemap_print_string_attr(20, 5, 2, "   S3 UJA3");
        tilemap_print_string_attr(20, 6, 2, "   S4 UJA4");
        tilemap_print_string_attr(20, 7, 2, "   S5  -  ");
        tilemap_print_string_attr(20, 8, 2, "   S6  -  ");
        tilemap_print_string_attr(33, 3, 2, "2P S1 ROA ");
        tilemap_print_string_attr(33, 4, 2, "   S2 WCA ");
        tilemap_print_string_attr(33, 5, 2, "   S3 UMJA");
        tilemap_print_string_attr(33, 6, 2, "   S4  -  ");
        tilemap_print_string_attr(33, 7, 2, "   S5  -  ");
        tilemap_print_string_attr(33, 8, 2, "   S6  -  ");
    } else {
        tilemap_print_string_attr(20, 2, 2, "          ");
        tilemap_print_string_attr(20, 3, 2, "          ");
        tilemap_print_string_attr(20, 4, 2, "          ");
        tilemap_print_string_attr(20, 5, 2, "          ");
        tilemap_print_string_attr(20, 6, 2, "          ");
        tilemap_print_string_attr(20, 7, 2, "          ");
        tilemap_print_string_attr(20, 8, 2, "          ");
        tilemap_print_string_attr(33, 3, 2, "          ");
        tilemap_print_string_attr(33, 4, 2, "          ");
        tilemap_print_string_attr(33, 5, 2, "          ");
        tilemap_print_string_attr(33, 6, 2, "          ");
        tilemap_print_string_attr(33, 7, 2, "          ");
        tilemap_print_string_attr(33, 8, 2, "          ");
    }
}


/* provisional name */
void debug_cg_number_browse(void) {
    s16 ix;
    u16 group;
    debug_position_by_pad();
    debug_flip_cycle(~dbg_p1sw_1 & dbg_p1sw_0);
    if (dbg_p1sw_0 & BUTTON_START) {
        if (debug_lever_repeat_fast(dbg_p1sw_0, dbg_p1sw_1, LEVER_UP, 0)) {
            dbg_pl->wu.cg_number--;
            if (dbg_pl->wu.cg_number > 0x7827) {
                dbg_pl->wu.cg_number = 0x7827;
            }
        }
        if (debug_lever_repeat_fast(dbg_p1sw_0, dbg_p1sw_1, LEVER_DOWN, 1)) {
            dbg_pl->wu.cg_number++;
            if (dbg_pl->wu.cg_number > 0x7827) {
                dbg_pl->wu.cg_number = 0;
            }
        }
        if (debug_lever_repeat_fast(dbg_p1sw_0, dbg_p1sw_1, LEVER_LEFT, 2)) {
            dbg_pl->wu.cg_number -= 0x80;
            if (dbg_pl->wu.cg_number > 0x7827) {
                dbg_pl->wu.cg_number = 0x7827;
            }
        }
        if (debug_lever_repeat_fast(dbg_p1sw_0, dbg_p1sw_1, LEVER_RIGHT, 3)) {
            dbg_pl->wu.cg_number += 0x80;
            if (dbg_pl->wu.cg_number > 0x7827) {
                dbg_pl->wu.cg_number = 0;
            }
        }
        if (dbg_pl->wu.cg_number < 0x3C00) {
            ix = dbg_pl->wu.cg_number / 0x400;
            if (ix != dbg_col_char) {
                dbg_col_char = ix;
                if (dbg_col_char != 6) {
                    load_player_color(dbg_col_char, 1, 0);
                }
                dbg_pl->wu.charset_id = debug_charset_tbl[dbg_col_char];
                dbg_pl->wu.my_col_mode = 0x4200;
                debug_char_table_load();
                set_char_base_data_init(&dbg_pl->wu);
                dbg_pl->wu.my_col_code = 0x2010;
            }
            dbg_pl->player_number = ix;
        } else {
            if (dbg_pl->wu.cg_number > 0x4000 && dbg_pl->wu.cg_number < 0x4020) {
                dbg_col_char = 20;
            }
            if (dbg_pl->wu.cg_number > 0x4020 && dbg_pl->wu.cg_number < 0x4090) {
                if (dbg_col_char != 21) {
                    dbg_col_char = 21;
                }
            }
        }
    }
    dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
    if (dbg_pl->wu.disp_flag == 0) {
        dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
    }
    group = get_cg_slot_no(dbg_pl->wu.cg_number);
    if (dbg_pl->zuru_timer != group) {
        purge_char_gfx(dbg_cg_group_top_tbl[(dbg_pl->zuru_timer & 0x7FFF) / 4]);
        dbg_pl->zuru_timer = group;
    }
}


/* provisional name */
void debug_object_look_input(void) {
    u16 sw;
    if (dbg_cmd_panel) {
        debug_cmd_panel_run();
        return;
    }
    debug_edit_common_input();
    if (Debug_Command) {
        return;
    }
    sw = ~dbg_p1sw_1 & dbg_p1sw_0;
    if (sw & BUTTON_HP) {
        Debug_Command = 6;
        return;
    }
    debug_kakusyuku_mode_cycle(sw);
    debug_kakusyuku_input();
}

/* provisional name */
void debug_object_edit_input(void)
{
    u16 sw;

    if (dbg_cmd_panel) {
        debug_cmd_panel_run();
        return;
    }
    if (dbg_rec_menu) {
        debug_move_record_menu();
        return;
    }
    debug_edit_common_input();
    if (Debug_Command) {
        return;
    }
    sw = ~dbg_p1sw_1 & dbg_p1sw_0;
    if ((Debug_Command = debug_priority_swap(sw)) != 0) {
        return;
    }
    debug_move_record_start(sw);
    debug_playback_mode_cycle(sw);
    sw = ~dbg_p2sw_1 & dbg_p2sw_0;
    if ((Debug_Command = debug_check_rec_frame(sw)) != 0) {
        return;
    }
    if ((Debug_Command = debug_check_rec_step()) != 0) {
        return;
    }
    if ((Debug_Command = debug_record_sw_check(sw)) != 0) {
        return;
    }
    debug_dec_disp_input(sw);
    debug_record_frame_adjust(sw);
    debug_pl_id_input(sw);
    debug_zoom_out_by_dipsw();
    debug_player_color_next();
}


/* provisional name */
void debug_edit_all_char_input(void) {
    u16 sw;
    if (dbg_cmd_panel) {
        debug_cmd_panel_run();
        return;
    }
    if (dbg_rec_menu) {
        debug_move_record_menu();
        return;
    }
    if (!dbg_pl->wu.id) {
        debug_edit_common_input();
    } else {
        debug_cg_number_browse();
    }
    if (Debug_Command) {
        return;
    }
    sw = ~dbg_p1sw_1 & dbg_p1sw_0;
    if ((Debug_Command = debug_priority_swap(sw))) {
        return;
    }
    debug_move_record_start(sw);
    debug_playback_mode_cycle(sw);
    sw = ~dbg_p2sw_1 & dbg_p2sw_0;
    if ((Debug_Command = debug_check_rec_frame(sw))) {
        return;
    }
    if ((Debug_Command = debug_check_rec_step())) {
        return;
    }
    if ((Debug_Command = debug_record_sw_check(sw))) {
        return;
    }
    debug_record_frame_adjust(sw);
    debug_pl_id_input(sw);
    debug_dec_disp_input(sw);
    debug_zoom_out_by_dipsw();
    debug_player_color_next();
}


/* provisional name */
void debug_hit_judgment_input(void) {
    s16 sw;
    if (dbg_cmd_panel) {
        debug_cmd_panel_run();
        return;
    }
    debug_edit_common_input();
    debug_hit_box_edit();
    debug_hit_box_cursor();
    debug_hit_box_copy();
    if (!dbg_judge_ewk->look_up_flag) {
        debug_position_by_pad();
    }
    sw = ~dbg_p2sw_1 & dbg_p2sw_0;
    if (sw & BUTTON_START) {
        Debug_PL_id = Debug_PL_id ^ 1;
    }
}


/* provisional name */
void debug_catch_judgment_input(void) {
    s16 sw;
    if (dbg_cmd_panel) {
        debug_cmd_panel_run();
        return;
    }
    debug_edit_common_input();
    if (Debug_Command) {
        return;
    }
    sw = ~dbg_p2sw_1 & dbg_p2sw_0;
    debug_pl_id_input(sw);
    debug_dec_disp_input(sw);
}


/* provisional name */
s32 debug_lever_repeat(sw, old, mask, ix)
u16 sw;
u16 old;
u16 mask;
s16 ix;
{
    if (sw & mask) {
        if (Debug_Menu_No == 4) {
            if (sw & BUTTON_LP) {
                return 1;
            }
        }
        Debug_Rep_Timer[ix]++;
        if (~old & sw & mask) {
            Debug_Rep_Timer[ix] = 0;
            Debug_Rep_Count[ix] = 0;
            return 1;
        }
        if (ix > 3) {
            if (Debug_Rep_Timer[ix] > 14) {
                Debug_Rep_Count[ix]++;
                return 1;
            }
            return 0;
        } else {
            if (Debug_Rep_Timer[ix] > 16) {
                Debug_Rep_Count[ix]++;
                if (Debug_Rep_Count[ix] > 6) {
                    Debug_Rep_Count[ix] = 0;
                    return 1;
                }
            }
            return 0;
        }
    }
    Debug_Rep_Timer[ix] = 0;
    Debug_Rep_Count[ix] = 0;
    return 0;
}


/* provisional name */
s32 debug_lever_repeat_fast(sw, old, mask, ix)
u16 sw;
u16 old;
u16 mask;
s16 ix;
{
    if (sw & mask) {
        if (sw & BUTTON_LP) {
            return 1;
        }
        Debug_Rep_Timer[ix]++;
        if (~old & sw & mask) {
            Debug_Rep_Timer[ix] = 0;
            Debug_Rep_Count[ix] = 0;
            return 1;
        }
        if (ix > 3) {
            if (Debug_Rep_Timer[ix] > 14) {
                Debug_Rep_Count[ix]++;
                return 1;
            }
            return 0;
        } else {
            if (Debug_Rep_Timer[ix] > 16) {
                Debug_Rep_Count[ix]++;
                if (Debug_Rep_Count[ix] > 6) {
                    Debug_Rep_Count[ix] = 0;
                    return 1;
                }
            }
            return 0;
        }
    }
    Debug_Rep_Timer[ix] = 0;
    Debug_Rep_Count[ix] = 0;
    return 0;
}

/* provisional name */
void debug_pattern_timer_update(void) {
    u32* p = dbg_pl->wu.set_char_ad + dbg_pl->wu.cg_ix;

    dbg_slot->frames = *(s8*)p;
    dbg_slot->rest = dbg_slot->frames - dbg_pl->wu.cg_ctr + 1;
}


/* provisional name */
void debug_edit_pattern_timer_update(void) {
    dbg_slot->frames = dbg_edit_buf.rec[dbg_slot->sel[2]].u.frames;
    dbg_slot->rest = dbg_slot->frames + 1 - dbg_pl->wu.cg_ctr;
}


/* provisional name */
void debug_char_table_load(void) {
    dbg_pl->wu.char_table[0] = dbg_pl_char_tbl[dbg_pl->player_number][0];
    dbg_pl->wu.char_table[1] = dbg_pl_char_tbl[dbg_pl->player_number][1];
    dbg_pl->wu.char_table[2] = dbg_pl_char_tbl[dbg_pl->player_number][2];
    dbg_pl->wu.char_table[3] = dbg_pl_char_tbl[dbg_pl->player_number][3];
    dbg_pl->wu.char_table[4] = dbg_pl_char_tbl[dbg_pl->player_number][4];
    dbg_pl->wu.char_table[5] = dbg_pl_char_tbl[dbg_pl->player_number][5];
    dbg_pl->wu.char_table[6] = dbg_pl_char_tbl[dbg_pl->player_number][6];
    dbg_pl->wu.char_table[7] = dbg_pl_char_tbl[dbg_pl->player_number][7];
    dbg_pl->wu.char_table[8] = dbg_pl_char_tbl[dbg_pl->player_number][8];
    dbg_pl->wu.char_table[9] = dbg_pl_char_tbl[dbg_pl->player_number][8];
}


/* provisional name */
void debug_slot_char_load(void) {
    s16 ix;
    s16 n;
    s16 row;
    s16 col;
    u16 group;
    if (dbg_slot->sel[0] <= 0x90) {
        dbg_pl->wu.operator = 0;
        if (dbg_slot->sel[0] < 10) {
            ix = 0;
        } else {
            ix = (dbg_slot->sel[0] - 1) / 9;
        }
        if (dbg_pl->player_number != ix) {
            dbg_pl->player_number = ix;
            dbg_pl->wu.charset_id = debug_charset_tbl[dbg_pl->player_number];
            dbg_pl->wu.my_col_mode = 0x4200;
            debug_char_table_load();
            set_char_base_data_init(&dbg_pl->wu);
            if (dbg_pl->wu.id) {
                dbg_pl->wu.my_col_code = 0x2010;
            } else {
                dbg_pl->wu.my_col_code = 0x2000;
            }
            if (dbg_pl->player_number != PL_HUGO) {
                load_player_color(dbg_pl->player_number, dbg_pl->wu.id, 0);
            }
            set_player_shadow(dbg_pl);
        }
        set_char_move_init(&dbg_pl->wu, dbg_slot->row, 0);
    } else {
        dbg_pl->wu.my_col_mode = 0x4200;
        dbg_pl->wu.my_col_code = 0x4040;
        if (dbg_slot->sel[0] == 0x91) {
            load_player_color(1, 0, 0);
            dbg_pl->wu.my_col_code = 0x4007;
        }
        if (dbg_slot->sel[0] == 0x92) {
            dbg_pl->wu.hit_ix_table = (HIT_IX*)ef13_hit_ix_table;
            dbg_pl->wu.body_adrs = (BODY_BOX*)ef13_body_box;
            dbg_pl->wu.attack_adrs = (ATTACK_BOX*)ef13_att_box;
            dbg_pl->wu.caught_adrs = (CAUGHT_BOX*)ef13_cau_box;
            dbg_pl->wu.hosei_adrs = (HOSEI_BOX*)ef13_hos_box;
            dbg_pl->wu.att_ix_table = (ATTACK_ATTR*)ef13_catt_table;
            load_any_color(dbg_obj_color_tbl[dbg_slot->sel[0] - 0x92]);
            dbg_pl->wu.my_col_code = 0x4020;
        }
        dbg_pl->player_number = 0x99;
        dbg_pl->wu.operator = 1;
        n = dbg_slot->sel[0] - 0x90;
        if (n < 10) {
            col = n - 1;
            row = 0;
        } else {
            col = (n - 1) % 9;
            row = (n - 1) / 9;
        }
        row += 16;
        dbg_pl->wu.char_table[0] = dbg_pl_char_tbl[row][col];
        set_char_move_init(&dbg_pl->wu, 0, 0);
    }
    Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip;
    dbg_pl->wu.cg_flip ^= Debug_Flip_Mask[dbg_pl->wu.id];
    Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag;
    dbg_pl->wu.disp_flag = check_cg_data(dbg_pl->wu.cg_number);
    if (dbg_pl->wu.disp_flag == 0) {
        dbg_pl->wu.old_cgnum = dbg_pl->wu.cg_number;
    }
    group = get_cg_slot_no(dbg_pl->wu.cg_number);
    if (group & 0x8000) {
        if (!(dbg_pl->zuru_timer & 0)) {
            purge_char_gfx(dbg_pl->wu.old_rno[0]);
            dbg_pl->zuru_timer = group;
        }
    } else if (!get_cg_slot_addr(group)) {
        if (!(dbg_pl->zuru_timer & 0x8000)) {
            purge_char_gfx(dbg_pl->wu.old_rno[0]);
        }
        dbg_pl->zuru_timer = group;
    }
}


/* provisional name */
void debug_char_disp(WORK* wk) {
    wk->position_x = wk->xyz[0].disp.pos;
    wk->position_y = wk->xyz[1].disp.pos;
    wk->position_z = wk->my_priority;
    sort_push_request(wk);
}


/* provisional name */
void debug_char_disp_sort(WORK* wk) {
    wk->position_z = wk->my_priority;
    sort_push_request(wk);
}


/* provisional name */
void debug_char_disp_once(WORK* wk) {
    wk->be_flag = 1;
    wk->disp_flag = 1;
    wk->position_z = wk->my_priority;
    sort_push_request(wk);
    wk->be_flag = 0;
    wk->disp_flag = 0;
}


/* provisional name */
void debug_pattern_edit_init_counts(void) {
    const u32** pat;
    ((DBG_SLOT*)&dbg_slot_w[0])->sel[0] = 1;
    ((DBG_SLOT*)&dbg_slot_w[1])->sel[0] = 1;
    ((DBG_SLOT*)&dbg_slot_w[0])->sel0_max = 0;
    ((DBG_SLOT*)&dbg_slot_w[1])->sel0_max = 0;
    for (pat = dbg_pl_char_tbl[0]; *pat; pat++) {
        ((DBG_SLOT*)&dbg_slot_w[0])->sel0_max++;
        ((DBG_SLOT*)&dbg_slot_w[1])->sel0_max++;
    }
}


/* provisional name */
void debug_motion_list_count(void) {
    const u32* p;
    dbg_slot->sel[1] = 1;
    if (dbg_slot->sel[0] > 0x90) {
        p = dbg_pl->wu.char_table[0];
    } else {
        switch (dbg_slot->row) {
        case 0:
            p = dbg_pl->wu.char_table[0];
            break;
        case 1:
            p = dbg_pl->wu.char_table[1];
            break;
        case 2:
            p = dbg_pl->wu.char_table[2];
            break;
        case 3:
            p = dbg_pl->wu.char_table[3];
            break;
        case 4:
            p = dbg_pl->wu.char_table[4];
            break;
        case 5:
            p = dbg_pl->wu.char_table[5];
            break;
        case 6:
            p = dbg_pl->wu.char_table[6];
            break;
        case 7:
            p = dbg_pl->wu.char_table[7];
            break;
        case 8:
        case 9:
            p = dbg_pl->wu.char_table[9];
            break;
        default:
            break;
        }
    }
    dbg_slot->sel1_max = 0;
    while (*p) {
        p++;
        dbg_slot->sel1_max++;
    }
}


/* provisional name */
void debug_pattern_count(void) {
    u32* p;
    dbg_slot->sel[2] = 0;
    p = dbg_pl->wu.set_char_ad;
    dbg_slot->rec_count = 0;
    while (1) {
        u32* q = p;
        if (*(u16*)q == 1) {
            break;
        }
        if (*(u16*)q >= 0x100) {
            dbg_slot->rec_count++;
        }
        p += dbg_pl->wu.cgd_type;
    }
}


/* provisional name */
void debug_pattern_entry_copy_dual(s16 n, u16* q, s16 box) {
    u16* src;
    u16* look;
    u16* edit;
    s16 i;
    const HIT_IX* ix;
    src = (u16*)&dbg_pl->wu.hit_ix_table[box];
    look = (u16*)((u8*)dbg_look_buf.hit_ix + n * 8);
    edit = (u16*)((u8*)dbg_edit_buf.hit_ix + n * 8);
    for (i = 0; i < 4; i++) {
        *look++ = *src;
        *edit++ = *src++;
    }
    ix = &dbg_pl->wu.hit_ix_table[box];
    src = (u16*)&dbg_pl->wu.body_adrs[ix->boix];
    look = (u16*)(dbg_look_buf.body_adrs + n * 40);
    edit = (u16*)(dbg_edit_buf.body_adrs + n * 40);
    for (i = 0; i < 20; i++) {
        *look++ = *src;
        *edit++ = *src++;
    }
    src = (u16*)&dbg_pl->wu.attack_adrs[ix->atix];
    look = (u16*)(dbg_look_buf.attack_adrs + n * 24);
    edit = (u16*)(dbg_edit_buf.attack_adrs + n * 24);
    for (i = 0; i < 12; i++) {
        *look++ = *src;
        *edit++ = *src++;
    }
    src = (u16*)&dbg_pl->wu.caught_adrs[ix->cuix];
    look = (u16*)(dbg_look_buf.caught_adrs + n * 8);
    edit = (u16*)(dbg_edit_buf.caught_adrs + n * 8);
    for (i = 0; i < 4; i++) {
        *look++ = *src;
        *edit++ = *src++;
    }
    src = (u16*)&dbg_pl->wu.hosei_adrs[ix->hoix];
    look = (u16*)(dbg_look_buf.hosei_adrs + n * 8);
    edit = (u16*)(dbg_edit_buf.hosei_adrs + n * 8);
    for (i = 0; i < 4; i++) {
        *look++ = *src;
        *edit++ = *src++;
    }
}


/* provisional name */
void debug_pattern_list_build(void) {
    s16 n;
    u32* p;
    u16* q;
    PATTERN_REC* r;
    dbg_slot->sel[2] = 1;
    dbg_slot->rec_count = 0;
    n = 0;
    p = dbg_pl->wu.set_char_ad;
    while (1) {
        q = (u16*)p;
        if (*q == 1) {
            break;
        }
        if (*q >= 0x100) {
            n++;
            dbg_slot->rec_count++;
            q = (u16*)p;
            r = &dbg_look_buf.rec[dbg_slot->rec_count];
            r->u.code = q[0];
            r = &dbg_edit_buf.rec[dbg_slot->rec_count];
            r->u.code = q[0];
            dbg_look_buf.rec[dbg_slot->rec_count].type = dbg_pl->wu.cgd_type;
            dbg_look_buf.rec[dbg_slot->rec_count].param = q[3];
            dbg_look_buf.rec[dbg_slot->rec_count].box = q[5];
            dbg_edit_buf.rec[dbg_slot->rec_count].type = dbg_pl->wu.cgd_type;
            dbg_edit_buf.rec[dbg_slot->rec_count].param = q[3];
            dbg_edit_buf.rec[dbg_slot->rec_count].box = q[5];
            debug_pattern_entry_copy_dual(n, (u16*)p, dbg_look_buf.rec[dbg_slot->rec_count].box);
        }
        p += dbg_pl->wu.cgd_type;
    }
}

/* provisional name */
void debug_pattern_preview_restart(WORK* wk) {
    dbg_pl->wu.cg_ctr = 1;
    debug_pattern_preview_step(wk);
}


/* provisional name */
void debug_pattern_preview_step(WORK* wk)
{
    if (--dbg_pl->wu.cg_ctr != 0) {
        return;
    }
    dbg_slot->sel[2]++;
    if (dbg_slot->sel[2] > dbg_slot->rec_count) {
        dbg_slot->sel[2] = 1;
    }
    wk->cg_olc = wk->olc_ix_table[wk->cg_olc_ix];
    if (dbg_judge_ewk->look_up_flag) {
        wk->cgd_type = dbg_look_buf.rec[dbg_slot->sel[2]].type;
        wk->cg_ctr = dbg_look_buf.rec[dbg_slot->sel[2]].u.frames;
        wk->cg_number = dbg_look_buf.rec[dbg_slot->sel[2]].param;
        wk->cg_hit_ix = dbg_look_buf.rec[dbg_slot->sel[2]].box;
        if (wk->cg_att_ix) {
            set_new_attnum(wk);
        }
        wk->cg_ja = wk->hit_ix_table[wk->cg_hit_ix];
        wk->h_bod = wk->body_adrs + dbg_look_buf.hit_ix[dbg_slot->sel[2]][0];
        wk->h_att = wk->attack_adrs + dbg_look_buf.hit_ix[dbg_slot->sel[2]][1];
        wk->h_cau = wk->caught_adrs + dbg_look_buf.hit_ix[dbg_slot->sel[2]][2];
        wk->h_hos = wk->hosei_adrs + dbg_look_buf.hit_ix[dbg_slot->sel[2]][3];
    } else {
        wk->cgd_type = dbg_edit_buf.rec[dbg_slot->sel[2]].type;
        wk->cg_ctr = dbg_edit_buf.rec[dbg_slot->sel[2]].u.frames;
        wk->cg_number = dbg_edit_buf.rec[dbg_slot->sel[2]].param;
        wk->cg_hit_ix = dbg_edit_buf.rec[dbg_slot->sel[2]].box;
        wk->h_bod = wk->body_adrs + dbg_edit_buf.hit_ix[dbg_slot->sel[2]][0];
        wk->h_att = wk->attack_adrs + dbg_edit_buf.hit_ix[dbg_slot->sel[2]][1];
        wk->h_cau = wk->caught_adrs + dbg_edit_buf.hit_ix[dbg_slot->sel[2]][2];
        wk->h_hos = wk->hosei_adrs + dbg_edit_buf.hit_ix[dbg_slot->sel[2]][3];
    }
    if (wk->cg_type == 0xFF) {
        return;
    }
    if (!(wk->cg_type & 0x80)) {
        return;
    }
    wk->cg_wca_ix = wk->cg_type & 0x7F;
    wk->cg_type = 0;
}


/* provisional name */
void debug_save_player_snapshot(SNAPSHOT* rec, WORK* wk) {
    rec->pos_x = wk->xyz[0].disp.pos;
    rec->pos_y = wk->xyz[1].disp.pos;
    rec->priority = wk->my_priority;
    rec->cg_number = wk->cg_number;
    rec->dbg_rl_flag = Debug_RL_Flag[wk->id];
    rec->dbg_cg_flip = Debug_CG_Flip[wk->id];
    rec->used = 1;
    rec->col_mode = wk->my_col_mode;
    rec->col_code = wk->my_col_code;
    rec->olc_ix = wk->cg_olc_ix;
    rec->rl_flag = wk->rl_flag;
    rec->cg_flip = wk->cg_flip;
    if (dbg_save_mode) {
        rec->cg_ctr = wk->cg_ctr;
    }
}


/* provisional name */
void debug_copy_player_snapshot(SNAPSHOT* src, SNAPSHOT* dst) {
    dst->pos_x = src->pos_x;
    dst->pos_y = src->pos_y;
    dst->priority = src->priority;
    dst->cg_number = src->cg_number;
    dst->dbg_rl_flag = src->dbg_rl_flag;
    dst->dbg_cg_flip = src->dbg_cg_flip;
    dst->used = 1;
    dst->cg_ctr = src->cg_ctr;
    dst->col_mode = src->col_mode;
    dst->col_code = src->col_code;
    dst->olc_ix = src->olc_ix;
    dst->rl_flag = src->rl_flag;
    dst->cg_flip = src->cg_flip;
}


/* provisional name */
void debug_restore_player_snapshot(SNAPSHOT* rec, WORK* wk) {
    wk->xyz[0].disp.pos = rec->pos_x;
    wk->xyz[1].disp.pos = rec->pos_y;
    wk->my_priority = rec->priority;
    wk->cg_number = rec->cg_number;
    wk->my_col_mode = rec->col_mode;
    wk->my_col_code = rec->col_code;
    wk->cg_olc_ix = rec->olc_ix;
    wk->rl_flag = rec->rl_flag;
    wk->cg_flip = rec->cg_flip;
    set_char_olc_data(wk);
}


/* provisional name */
void debug_snapshot_to_ghost(WORK* wk, SNAPSHOT* rec) {
    wk->position_x = rec->pos_x;
    wk->position_y = rec->pos_y;
    wk->my_priority = rec->priority;
    wk->cg_number = rec->cg_number;
    wk->my_col_mode = rec->col_mode;
    wk->my_col_code = rec->col_code;
    wk->cg_olc_ix = rec->olc_ix;
    wk->rl_flag = rec->rl_flag;
    wk->cg_flip = rec->cg_flip;
}


/* provisional name */
s32 debug_hex4_to_bcd(s16 x) {
    s16 digit[3];
    s16 i;
    s32 n;
    s16 div = 100;
    s32 bcd;
    s32 tens;
    for (i = 0; i < 3; i++) {
        n = 0;
        while (1) {
            x -= div;
            if (x < 0) {
                break;
            }
            n++;
        }
        digit[i] = n;
        x = x + div;
        div /= 10;
    }
    bcd = digit[0] << 8;
    bcd &= 0xF00;
    tens = digit[1] << 4;
    tens &= 0xF0;
    bcd |= tens;
    bcd |= digit[2];
    return (s16)bcd;
}


/* provisional name */
void debug_draw_object_info(void) {
    s16 num;
    s16 pat;
    const TM_STRING* p;
    num = debug_hex4_to_bcd(dbg_slot->sel[0]);
    tilemap_print_hex(10, 4, 2, num, 3, 0);
    num = debug_hex4_to_bcd(dbg_slot->sel0_max);
    tilemap_print_hex(14, 4, 2, num, 3, 0);
    if (DEBUG_DISP) {
        num = debug_hex4_to_bcd(dbg_slot->rec_count);
        tilemap_print_hex(18, 4, 2, num, 3, 0);
    }
    num = debug_hex4_to_bcd(dbg_slot->sel[1]);
    tilemap_print_hex(10, 6, 2, num, 3, 0);
    num = debug_hex4_to_bcd(dbg_slot->sel1_max);
    tilemap_print_hex(14, 6, 2, num, 3, 0);
    if (Debug_Menu_No == 3) {
        pat = debug_hex4_to_bcd(dbg_slot->sel[2]);
    } else {
        pat = debug_hex4_to_bcd(dbg_slot->sel[2] + 1);
    }
    tilemap_print_hex(11, 8, 2, pat, 2, 0);
    num = debug_hex4_to_bcd(dbg_slot->rec_count);
    tilemap_print_hex(14, 8, 2, num, 2, 0);
    num = debug_hex4_to_bcd(dbg_slot->rest);
    tilemap_print_hex(11, 9, 2, num, 2, 0);
    num = debug_hex4_to_bcd(dbg_slot->frames);
    tilemap_print_hex(14, 9, 2, num, 2, 0);
    tilemap_print_hex(11, 10, 2, dbg_pl->wu.cg_number, 4, 0);
    switch (Debug_CG_Flip[dbg_pl->wu.id]) {
    case 0:
        tilemap_print_string_attr(11, 11, 2, "NO");
        break;
    case 1:
        tilemap_print_string_attr(11, 11, 2, "H ");
        break;
    case 2:
        tilemap_print_string_attr(11, 11, 2, "V ");
        break;
    case 3:
        tilemap_print_string_attr(11, 11, 2, "HV");
        break;
    }
    if (Debug_RL_Flag[dbg_pl->wu.id]) {
        tilemap_print_string_attr(13, 11, 2, "[1]");
    } else {
        tilemap_print_string_attr(13, 11, 2, "[0]");
    }
    switch (dbg_pl->wu.cg_flip) {
    case 0:
        tilemap_print_string_attr(11, 12, 2, "NO");
        break;
    case 1:
        tilemap_print_string_attr(11, 12, 2, "H ");
        break;
    case 2:
        tilemap_print_string_attr(11, 12, 2, "V ");
        break;
    case 3:
        tilemap_print_string_attr(11, 12, 2, "HV");
        break;
    }
    if (dbg_pl->wu.rl_flag) {
        tilemap_print_string_attr(13, 12, 2, "[1]");
    } else {
        tilemap_print_string_attr(13, 12, 2, "[0]");
    }
    tilemap_print_hex(11, 13, 2, dbg_pl->wu.position_x, 4, 0);
    tilemap_print_hex(11, 14, 2, dbg_pl->wu.position_y, 4, 0);
    if (dbg_slot->sel[0] <= 144) {
        tilemap_print_string(0, 0, 0xFFFF, &dbg_act_kind_str[dbg_slot->row]);
        p = dbg_act_name_tbl[dbg_slot->row];
        p = &p[dbg_slot->sel[1] - 1];
        tilemap_print_string(0, 0, 0xFFFF, p);
        tilemap_print_string(0, 0, 0xFFFF, &dbg_char_name_str[dbg_pl->player_number]);
    } else {
        tilemap_print_string(0, 0, 0xFFFF, &dbg_act_kind_str[9]);
        p = dbg_act_name_tbl[9];
        p = &p[dbg_slot->sel[0] - 145];
        tilemap_print_string(0, 0, 0xFFFF, p);
        tilemap_print_string(0, 0, 0xFFFF, &dbg_char_name_str[16]);
    }
}


/* provisional name */
void debug_draw_kakusyuku_frame_flags(void) {
    switch (dbg_kakusyuku_mode) {
    case 0:
        tilemap_print_string_attr(1, 16, 2, "KAKUSYUKU  OFF");
        tilemap_print_string_attr(1, 17, 2, "FRAME      OFF");
        break;
    case 1:
        tilemap_print_string_attr(1, 17, 2, "FRAME      ON ");
        break;
    case 2:
        tilemap_print_string_attr(1, 16, 2, "KAKUSYUKU  ON ");
        tilemap_print_string_attr(1, 17, 2, "FRAME      OFF");
        break;
    case 3:
        tilemap_print_string_attr(1, 17, 2, "FRAME      ON ");
        break;
    }
}


/* provisional name */
void debug_draw_position_delta(void) {
    s16 d;
    s16 bcd;
    d = plw[1].wu.xyz[0].disp.pos;
    d -= plw[0].wu.xyz[0].disp.pos;
    if (d < 0) {
        tilemap_print_string_attr(10, 15, 2, dbg_minus_str);
        d = -d;
    } else {
        tilemap_print_string_attr(10, 15, 2, " ");
    }
    if (Debug_Dec_Disp) {
        bcd = debug_hex4_to_bcd(d);
        tilemap_print_hex(11, 15, 2, bcd, 4, 0);
        tilemap_print_string_attr(15, 15, 2, dbg_space2_str);
    } else {
        tilemap_print_hex(11, 15, 2, d, 4, 0);
        tilemap_print_string_attr(15, 15, 2, dbg_hex_mark_str);
    }
    d = plw[1].wu.xyz[1].disp.pos;
    d -= plw[0].wu.xyz[1].disp.pos;
    if (d < 0) {
        tilemap_print_string_attr(10, 16, 2, dbg_minus_str);
        d = -d;
    } else {
        tilemap_print_string_attr(10, 16, 2, " ");
    }
    if (Debug_Dec_Disp) {
        bcd = debug_hex4_to_bcd(d);
        tilemap_print_hex(11, 16, 2, bcd, 4, 0);
        tilemap_print_string_attr(15, 16, 2, dbg_space2_str);
    } else {
        tilemap_print_hex(11, 16, 2, d, 4, 0);
        tilemap_print_string_attr(15, 16, 2, dbg_hex_mark_str);
    }
}


/* provisional name */
void debug_draw_edit_side(void) {
    if (Debug_PL_id) {
        tilemap_print_string_attr(11, 17, 2, dbg_2p_str);
    } else {
        tilemap_print_string_attr(11, 17, 2, dbg_1p_str);
    }
}


/* provisional name */
void debug_draw_hit_edit_info(void)
{
    s16 i;
    s16 num;
    s16* p;
    u16 x;

    tilemap_rect_fill(dbg_hud_x + 36, dbg_judge_ewk->curr_ja + 16, 8, 1, 6, 0xFFFF);
    if (Debug_Box_Edit) {
        tilemap_print_string_attr(dbg_hud_x + 36, 12, 6, dbg_hold_str);
    } else {
        tilemap_print_string_attr(dbg_hud_x + 36, 12, 14, dbg_free_str);
    }
    if (DEBUG_DISP) {
        tilemap_print_string_attr(dbg_hud_x + 36, 13, 6, dbg_copy_str);
    }
    if (dbg_copy_done) {
        if (dbg_copy_pat == dbg_slot->sel[2] && dbg_pl->wu.char_index == dbg_copy_char) {
            tilemap_print_string_attr(dbg_hud_x + 36, 13, 6, dbg_copy_str);
        } else {
            tilemap_print_string_attr(dbg_hud_x + 36, 13, 14, dbg_copy_str);
        }
    } else {
        tilemap_print_string_attr(dbg_hud_x + 36, 13, 14, dbg_copy_str);
    }
    if (dbg_judge_ewk->look_up_flag) {
        tilemap_print_string_attr(dbg_hud_x + 36, 14, 2, dbg_user_str);
    } else {
        tilemap_print_string_attr(dbg_hud_x + 36, 14, 2, dbg_define_str);
    }

    /* the four edit-box values, signed */
    for (i = 0; i < 4; i++) {
        num = dbg_edit_box[i];
        if (num < 0) {
            tilemap_print_string_attr(10, i + 15, 2, dbg_minus_str);
            num = -num;
        } else {
            tilemap_print_string_attr(10, i + 15, 2, " ");
        }
        tilemap_print_hex(11, i + 15, 2, num, 4, 0);
    }

    /* hit-index row of the current pattern */
    num = debug_hex4_to_bcd(dbg_edit_buf.rec[dbg_slot->sel[2]].box);
    tilemap_print_hex(11, 20, 2, num, 4, 0);
    p = (s16*)&dbg_pl->wu.hit_ix_table[dbg_edit_buf.rec[dbg_slot->sel[2]].box];
    for (i = 0; i < 4; i++) {
        tilemap_print_hex(11, i + 21, 2, *p, 3, 0);
        p++;
    }

    x = dbg_hud_x + 11;
    tilemap_print_string_attr(x, 25, 2, Debug_PL_id ? dbg_2p_str : dbg_1p_str);
}


/* provisional name */
void debug_draw_cm_summary(void) {
    s16 num;
    tilemap_print_string_attr(5, 25, 10, dbg_lp_str);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmlp.code);
    tilemap_print_hex(8, 25, 10, num, 3, 0);
    tilemap_print_string(0, 0, 0xFFFF, &dbg_koc_cmlp_str[dbg_pl->wu.cmlp.koc]);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmlp.ix);
    tilemap_print_hex(15, 25, 10, num, 3, 0);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmlp.pat);
    tilemap_print_string_attr(19, 25, 10, dbg_nix_str);
    tilemap_print_hex(22, 25, 10, num, 2, 0);
    tilemap_print_string_attr(5, 26, 10, dbg_l2_str);
    num = debug_hex4_to_bcd(dbg_pl->wu.cml2.code);
    tilemap_print_hex(8, 26, 10, num, 3, 0);
    tilemap_print_string(0, 0, 0xFFFF, &dbg_koc_cml2_str[dbg_pl->wu.cml2.koc]);
    num = debug_hex4_to_bcd(dbg_pl->wu.cml2.ix);
    tilemap_print_hex(15, 26, 10, num, 3, 0);
    num = debug_hex4_to_bcd(dbg_pl->wu.cml2.pat);
    tilemap_print_string_attr(19, 26, 10, dbg_nix_str);
    tilemap_print_hex(22, 26, 10, num, 2, 0);
    tilemap_print_string_attr(5, 27, 10, dbg_sw_str);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmsw.code);
    tilemap_print_hex(8, 27, 10, num, 3, 0);
    tilemap_print_string(0, 0, 0xFFFF, &dbg_koc_cmsw_str[dbg_pl->wu.cmsw.koc]);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmsw.ix);
    tilemap_print_hex(15, 27, 10, num, 3, 0);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmsw.pat);
    tilemap_print_string_attr(19, 27, 10, dbg_nix_str);
    tilemap_print_hex(22, 27, 10, num, 2, 0);
    tilemap_print_string_attr(25, 25, 10, dbg_ja_str);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmja.code);
    tilemap_print_hex(28, 25, 10, num, 3, 0);
    tilemap_print_string(0, 0, 0xFFFF, &dbg_koc_cmja_str[dbg_pl->wu.cmja.koc]);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmja.ix);
    tilemap_print_hex(35, 25, 10, num, 3, 0);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmja.pat);
    tilemap_print_string_attr(39, 25, 10, dbg_nix_str);
    tilemap_print_hex(42, 25, 10, num, 2, 0);
    tilemap_print_string_attr(25, 26, 10, dbg_j2_str);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmj2.code);
    tilemap_print_hex(28, 26, 10, num, 3, 0);
    tilemap_print_string(0, 0, 0xFFFF, &dbg_koc_cmja_str[dbg_pl->wu.cmj2.koc]);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmj2.ix);
    tilemap_print_hex(35, 26, 10, num, 3, 0);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmj2.pat);
    tilemap_print_string_attr(39, 26, 10, dbg_nix_str);
    tilemap_print_hex(42, 26, 10, num, 2, 0);
    tilemap_print_string_attr(25, 27, 10, dbg_oa_str);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmoa.code);
    tilemap_print_hex(28, 27, 10, num, 3, 0);
    tilemap_print_string(0, 0, 0xFFFF, &dbg_koc_cmoa_str[dbg_pl->wu.cmoa.koc]);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmoa.ix);
    tilemap_print_hex(35, 27, 10, num, 3, 0);
    num = debug_hex4_to_bcd(dbg_pl->wu.cmoa.pat);
    tilemap_print_string_attr(39, 27, 10, dbg_nix_str);
    tilemap_print_hex(42, 27, 10, num, 2, 0);
}


/* provisional name */
void debug_draw_cm_data(void)
{
    s16 bcd;

    tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_koc_str[dbg_pl->wu.cmoa.koc]);
    tilemap_print_string(dbg_hud_x, 1, 0xFFFF, &dbg_koc_str[dbg_pl->wu.cmsw.koc]);
    tilemap_print_string(dbg_hud_x, 2, 0xFFFF, &dbg_koc_str[dbg_pl->wu.cmlp.koc]);
    tilemap_print_string(dbg_hud_x, 3, 0xFFFF, &dbg_koc_str[dbg_pl->wu.cml2.koc]);
    tilemap_print_string(dbg_hud_x, 4, 0xFFFF, &dbg_koc_str[dbg_pl->wu.cmja.koc]);
    tilemap_print_string(dbg_hud_x, 5, 0xFFFF, &dbg_koc_str[dbg_pl->wu.cmj2.koc]);
    tilemap_print_string(dbg_hud_x, 6, 0xFFFF, &dbg_koc_str[dbg_pl->wu.cmj3.koc]);
    tilemap_print_string(dbg_hud_x, 7, 0xFFFF, &dbg_koc_str[dbg_pl->wu.cmj4.koc]);
    tilemap_print_string(dbg_hud_x, 8, 0xFFFF, &dbg_koc_str[dbg_pl->wu.cmms.koc]);
    tilemap_print_hex(dbg_hud_x + 32, 11, 10, dbg_pl->wu.cmmd.koc, 2, 0);
    tilemap_print_hex(dbg_hud_x + 32, 12, 10, dbg_pl->wu.cmyd.koc, 2, 0);
    tilemap_print_string(dbg_hud_x, 11, 0xFFFF, &dbg_koc_str[dbg_pl->wu.cmcf.koc]);
    tilemap_print_string(dbg_hud_x, 12, 0xFFFF, &dbg_koc_str[dbg_pl->wu.cmcr.koc]);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmoa.ix);
    tilemap_print_hex(dbg_hud_x + 35, 2, 10, bcd, 3, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmoa.pat);
    tilemap_print_string_attr(dbg_hud_x + 39, 2, 10, dbg_nix_str);
    tilemap_print_hex(dbg_hud_x + 42, 2, 10, bcd, 2, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmsw.ix);
    tilemap_print_hex(dbg_hud_x + 35, 3, 10, bcd, 3, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmsw.pat);
    tilemap_print_string_attr(dbg_hud_x + 39, 3, 10, dbg_nix_str);
    tilemap_print_hex(dbg_hud_x + 42, 3, 10, bcd, 2, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmlp.ix);
    tilemap_print_hex(dbg_hud_x + 35, 4, 10, bcd, 3, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmlp.pat);
    tilemap_print_string_attr(dbg_hud_x + 39, 4, 10, dbg_nix_str);
    tilemap_print_hex(dbg_hud_x + 42, 4, 10, bcd, 2, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cml2.ix);
    tilemap_print_hex(dbg_hud_x + 35, 5, 10, bcd, 3, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cml2.pat);
    tilemap_print_string_attr(dbg_hud_x + 39, 5, 10, dbg_nix_str);
    tilemap_print_hex(dbg_hud_x + 42, 5, 10, bcd, 2, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmja.ix);
    tilemap_print_hex(dbg_hud_x + 35, 6, 10, bcd, 3, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmja.pat);
    tilemap_print_string_attr(dbg_hud_x + 39, 6, 10, dbg_nix_str);
    tilemap_print_hex(dbg_hud_x + 42, 6, 10, bcd, 2, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmj2.ix);
    tilemap_print_hex(dbg_hud_x + 35, 7, 10, bcd, 3, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmj2.pat);
    tilemap_print_string_attr(dbg_hud_x + 39, 7, 10, dbg_nix_str);
    tilemap_print_hex(dbg_hud_x + 42, 7, 10, bcd, 2, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmj3.ix);
    tilemap_print_hex(dbg_hud_x + 35, 8, 10, bcd, 3, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmj3.pat);
    tilemap_print_string_attr(dbg_hud_x + 39, 8, 10, dbg_nix_str);
    tilemap_print_hex(dbg_hud_x + 42, 8, 10, bcd, 2, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmj4.ix);
    tilemap_print_hex(dbg_hud_x + 35, 9, 10, bcd, 3, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmj4.pat);
    tilemap_print_string_attr(dbg_hud_x + 39, 9, 10, dbg_nix_str);
    tilemap_print_hex(dbg_hud_x + 42, 9, 10, bcd, 2, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmms.ix);
    tilemap_print_hex(dbg_hud_x + 35, 10, 10, bcd, 3, 0);
    bcd = debug_hex4_to_bcd(dbg_pl->wu.cmms.pat);
    tilemap_print_string_attr(dbg_hud_x + 39, 10, 10, dbg_nix_str);
    tilemap_print_hex(dbg_hud_x + 42, 10, 10, bcd, 2, 0);
    tilemap_print_hex(dbg_hud_x + 35, 11, 10, dbg_pl->wu.cmmd.ix, 3, 0);
    tilemap_print_hex(dbg_hud_x + 41, 11, 10, dbg_pl->wu.cmmd.pat, 3, 0);
    tilemap_print_hex(dbg_hud_x + 35, 12, 10, dbg_pl->wu.cmyd.ix, 3, 0);
    tilemap_print_hex(dbg_hud_x + 41, 12, 10, dbg_pl->wu.cmyd.pat, 3, 0);
    tilemap_print_hex(dbg_hud_x + 35, 13, 10, dbg_pl->wu.cmcf.ix, 3, 0);
    tilemap_print_hex(dbg_hud_x + 41, 13, 10, dbg_pl->wu.cmcf.pat, 3, 0);
    tilemap_print_hex(dbg_hud_x + 35, 14, 10, dbg_pl->wu.cmcr.ix, 3, 0);
    tilemap_print_hex(dbg_hud_x + 41, 14, 10, dbg_pl->wu.cmcr.pat, 3, 0);
}


/* provisional name */
void debug_draw_delta_and_side(void)
{
    debug_draw_position_delta();
    debug_draw_edit_side();
}


/* provisional name */
void debug_draw_record_info(void) {
    s16 bcd;
    debug_draw_position_delta();
    debug_draw_edit_side();
    bcd = debug_hex4_to_bcd(Debug_Rec_Count);
    tilemap_print_hex(11, 19, 2, bcd, 4, 0);
    bcd = debug_hex4_to_bcd(Debug_Rec_Frame);
    tilemap_print_hex(11, 18, 2, bcd, 4, 0);
    bcd = debug_hex4_to_bcd(dbg_snap_ptr->used);
    tilemap_print_hex(11, 20, 2, bcd, 4, 0);
    bcd = debug_hex4_to_bcd(dbg_snap_ptr->cg_ctr);
    tilemap_print_hex(11, 21, 2, bcd, 4, 0);
    switch (dbg_save_mode) {
    case 0:
        tilemap_print_string_attr(1, 23, 6, dbg_over_write_str);
        break;
    case 1:
        tilemap_print_string_attr(1, 23, 6, dbg_insert_str);
        break;
    case 2:
        tilemap_print_string_attr(1, 23, 6, dbg_addition_str);
        break;
    }
}


/* provisional name */
void debug_char_init(void) {
    s16 x;
    if (Game_setting.Screen_Mode) {
        x = 32;
    } else {
        x = 0;
    }
    dbg_pl->wu.be_flag = 1;
    dbg_pl->wu.disp_flag = 1;
    dbg_pl->wu.cgromtype = 1;
    dbg_pl->wu.my_family = 1;
    dbg_pl->wu.my_col_mode = 0x4200;
    dbg_pl->wu.work_id = 1;
    if (dbg_pl->wu.id) {
        dbg_pl->wu.position_x = dbg_pl->wu.xyz[0].disp.pos = x + 0x200;
        dbg_pl->wu.my_priority = 64;
        dbg_pl->wu.target_adrs = (u32*)&plw[0];
    } else {
        dbg_pl->wu.position_x = dbg_pl->wu.xyz[0].disp.pos = x + 0x1B0;
        dbg_pl->wu.my_priority = 62;
        dbg_pl->wu.target_adrs = (u32*)&plw[1];
    }
    dbg_pl->wu.position_y = dbg_pl->wu.xyz[1].disp.pos = 0;
    dbg_pl->wu.xyz[2].disp.pos = dbg_pl->wu.my_priority;
    dbg_pl->wu.xyz[0].disp.low = 0;
    dbg_pl->wu.xyz[1].disp.low = 0;
    dbg_pl->wu.xyz[2].disp.low = 0;
    dbg_pl->wu.charset_id = debug_charset_tbl[dbg_pl->player_number];
    debug_char_table_load();
    set_char_base_data_init(&dbg_pl->wu);
    set_char_move_init(&dbg_pl->wu, dbg_slot->row, dbg_slot->sel[1] - 1);
    Debug_Flip_Work[dbg_pl->wu.id] = Debug_RL_Flag[dbg_pl->wu.id] = dbg_pl->wu.rl_flag = 0;
    Debug_Flip_Mask[dbg_pl->wu.id] = Debug_CG_Flip[dbg_pl->wu.id] = dbg_pl->wu.cg_flip = 0;
    if (dbg_pl->wu.id) {
        dbg_pl->wu.my_col_code = 0x2010;
    } else {
        dbg_pl->wu.my_col_code = 0x2000;
    }
}


/* provisional name */
void debug_char_color_load(PLW* pl) {
    polygon2d_submit_quad(dbg_char_color_tbl[pl->player_number], 0, 0x80, 0, 0, 0);
}


/* provisional name */
void debug_p1_reset(void) {
    dbg_pl = &plw[0];
    dbg_slot = (DBG_SLOT*)dbg_slot_w[0];
    dbg_pl->wu.id = 0;
    debug_char_init();
}


/* provisional name */
void debug_both_players_reset(void) {
    dbg_pl = &plw[0];
    dbg_slot = (DBG_SLOT*)dbg_slot_w[0];
    dbg_pl->wu.id = 0;
    debug_char_init();
    dbg_pl->wu.id = 0;
    dbg_pl = &plw[1];
    dbg_pl->wu.id = 1;
    debug_char_init();
    dbg_pl->wu.id = 1;
}


/* provisional name */
s32 debug_menu_exit_check(void) {
    if ((dbg_p1sw_0 & BUTTON_START) && (dbg_p2sw_0 & BUTTON_START)) {
        Debug_R_No = DBG_PLAYER;
        Debug_Select_No = 0;
        Debug_Tool_No = 0;
        Scr_all_clear_Wait();
        work_init_zero((s32*)&plw[0], sizeof(PLW));
        work_init_zero((s32*)&plw[1], sizeof(PLW));
        dbg_hud_mode = 0;
        tilemap_print_string(0, 0, 0xFFFF, dbg_hud_clr_str);
        return 1;
    }
    return 0;
}


/* provisional name */
void debug_bg_stage_load(void)
{
    s16 i;
    u16 sw;

    sw = exsw_0;
    if (sw & 0x4000) {
        switch (sw & 0x3000) {
        case 0x1000:
            bg_w.area = 1;
            break;
        case 0x2000:
            bg_w.area = 2;
            break;
        case 0:
        default:
            bg_w.area = 0;
            break;
        }
        sw &= 0xF00;
        switch (sw) {
        case 0x100:
            bg_w.stage = 1;
            break;
        case 0x200:
            bg_w.stage = 2;
            break;
        case 0x300:
            bg_w.stage = 3;
            break;
        case 0x400:
            bg_w.stage = 4;
            break;
        case 0x500:
            bg_w.stage = 5;
            break;
        case 0x600:
            bg_w.stage = 6;
            break;
        case 0x700:
            bg_w.stage = 7;
            break;
        case 0x800:
            bg_w.stage = 8;
            break;
        case 0x900:
            bg_w.stage = 9;
            break;
        case 0xA00:
            bg_w.stage = 10;
            break;
        case 0xB00:
            bg_w.stage = 11;
            break;
        case 0xC00:
            bg_w.stage = 12;
            break;
        case 0:
        default:
            bg_w.stage = 0;
            break;
        }
    }
    if (Debug_Menu_No != 5) {
        bg_initialize();
        for (i = 0; i < bg_w.scno; i++) {
            bg_w.bgw[i].xy[0].disp.pos = 0x100;
            bg_w.bgw[i].xy[1].disp.pos = 0;
            bg_w.bgw[i].xy[0].disp.low = 0;
            bg_w.bgw[i].xy[1].disp.low = 0;
            bg_w.bgw[i].position_x = 0x100;
            bg_w.bgw[i].position_y = 0;
        }
        Bg_Family_Set();
    }
}


/* provisional name */
s32 debug_cg_group_index(code)
s16 code;
{
    u16 i;
    for (i = 0; i < 89; i++) {
        if (code < dbg_cg_group_top_tbl[i + 1]) {
            break;
        }
    }
    return i;
}


/* provisional name */
void debug_draw_att_data(void)
{
    s16 bcd;

    if (plw[0].wu.meoshi_hit_flag != 1) {
        tilemap_print_string_attr(dbg_hud_x + 36, 2, 10, dbg_minus_str);
    } else {
        tilemap_print_string_attr(dbg_hud_x + 36, 2, 14, " ");
    }
    bcd = debug_hex4_to_bcd(plw[0].wu.cg_att_ix);
    tilemap_print_hex(dbg_hud_x + 37, 2, 10, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 3, 10, plw[0].wu.att.reaction, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.att.reaction);
    tilemap_print_hex(dbg_hud_x + 42, 3, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 4, 10, plw[0].wu.att.mkh_ix, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.att.mkh_ix);
    tilemap_print_hex(dbg_hud_x + 42, 4, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 5, 10, plw[0].wu.att.dipsw, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.att.dipsw);
    tilemap_print_hex(dbg_hud_x + 42, 5, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 6, 10, plw[0].wu.att.at_free4, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.att.at_free4);
    tilemap_print_hex(dbg_hud_x + 42, 6, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 7, 10, plw[0].wu.att.dir, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.att.dir);
    tilemap_print_hex(dbg_hud_x + 42, 7, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 8, 10, plw[0].wu.att.guard, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.att.guard);
    tilemap_print_hex(dbg_hud_x + 42, 8, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 9, 10, plw[0].wu.att.pow, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.att.pow);
    tilemap_print_hex(dbg_hud_x + 42, 9, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 10, 10, plw[0].wu.att.impact, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.att.impact);
    tilemap_print_hex(dbg_hud_x + 42, 10, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 11, 10, plw[0].wu.att.piyo, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.att.piyo);
    tilemap_print_hex(dbg_hud_x + 42, 11, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 12, 10, plw[0].wu.att.hs_me, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.att.hs_me);
    tilemap_print_hex(dbg_hud_x + 42, 12, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 13, 10, plw[0].wu.att.hs_you, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.att.hs_you);
    tilemap_print_hex(dbg_hud_x + 42, 13, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 14, 10, plw[0].wu.att.ng_type, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.att.ng_type);
    tilemap_print_hex(dbg_hud_x + 42, 14, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 15, 10, plw[0].wu.zu_flag, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.zu_flag);
    tilemap_print_hex(dbg_hud_x + 42, 15, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 16, 10, plw[0].wu.at_attribute, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.at_attribute);
    tilemap_print_hex(dbg_hud_x + 42, 16, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 17, 10, plw[0].wu.kezuri_pow, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.kezuri_pow);
    tilemap_print_hex(dbg_hud_x + 42, 17, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 18, 10, plw[0].wu.add_arts_point, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.add_arts_point);
    tilemap_print_hex(dbg_hud_x + 42, 18, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 19, 10, plw[0].wu.buttobi_type, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.buttobi_type);
    tilemap_print_hex(dbg_hud_x + 42, 19, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 21, 10, plw[0].wu.dir_atthit, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.dir_atthit);
    tilemap_print_hex(dbg_hud_x + 42, 21, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 22, 10, plw[0].wu.vs_id, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.vs_id);
    tilemap_print_hex(dbg_hud_x + 42, 22, 2, bcd, 4, 0);
}


/* provisional name */
void debug_draw_cg_data(void) {
    s16 bcd;
    s16 n;
    s16 i;
    s16 bit;
    u16 group;
    s16 base;
    if (dbg_old_cgd_type != plw[0].wu.cgd_type) {
        switch (plw[0].wu.cgd_type) {
        case 2:
            tilemap_print_string(0, 0, 0xFFFF, dbg_hud_clr_mid_str);
        case 4:
            tilemap_print_string(0, 0, 0xFFFF, dbg_hud_clr_low_str);
            break;
        }
    }
    switch (plw[0].wu.cgd_type) {
    case 6:
        tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_cg_rival_str);
        tilemap_print_hex(dbg_hud_x + 37, 16, 10, plw[0].wu.cg_rival, 4, 0);
        bcd = debug_hex4_to_bcd(plw[0].wu.cg_rival);
        tilemap_print_hex(dbg_hud_x + 42, 16, 2, bcd, 4, 0);
        tilemap_print_hex(dbg_hud_x + 37, 17, 10, plw[0].wu.cg_add_xy, 4, 0);
        bcd = debug_hex4_to_bcd(plw[0].wu.cg_add_xy);
        tilemap_print_hex(dbg_hud_x + 42, 17, 2, bcd, 4, 0);
        tilemap_print_string_attr(dbg_hud_x + 37, 18, 10, dbg_nix_str);
        tilemap_print_hex(dbg_hud_x + 40, 18, 10, plw[0].wu.cg_next_ix, 2, 0);
        bcd = debug_hex4_to_bcd(plw[0].wu.cg_status);
        tilemap_print_hex(dbg_hud_x + 37, 19, 10, bcd, 4, 0);
    case 4:
        tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_cg_att_str);
        if (plw[0].wu.cg_att_ix < 0) {
            tilemap_print_string_attr(dbg_hud_x + 37, 14, 2, dbg_minus_str);
            n = -plw[0].wu.cg_att_ix;
            tilemap_print_string_attr(dbg_hud_x + 42, 14, 2, dbg_minus_str);
        } else {
            tilemap_print_string_attr(dbg_hud_x + 37, 14, 2, " ");
            tilemap_print_string_attr(dbg_hud_x + 42, 14, 2, " ");
            n = plw[0].wu.cg_att_ix;
        }
        tilemap_print_hex(dbg_hud_x + 38, 10, 10, plw[0].wu.cg_att_ix, 3, 0);
        bcd = debug_hex4_to_bcd(n);
        tilemap_print_hex(dbg_hud_x + 43, 10, 2, bcd, 3, 0);
        tilemap_print_hex(dbg_hud_x + 37, 11, 10, plw[0].wu.cg_hit_ix, 4, 0);
        bcd = debug_hex4_to_bcd(plw[0].wu.cg_hit_ix);
        tilemap_print_hex(dbg_hud_x + 42, 11, 2, bcd, 4, 0);
        if (plw[0].wu.cg_extdat) {
            bcd = plw[0].wu.cg_extdat & 0xC0;
            bcd = bcd >> 6;
            tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_extdat_str[bcd]);
            bcd = debug_hex4_to_bcd(plw[0].wu.cg_extdat & 0x3F);
            tilemap_print_hex(dbg_hud_x + 39, 12, 10, bcd, 2, 0);
        } else {
            tilemap_print_string_attr(dbg_hud_x + 37, 12, 10, dbg_no_extdat_str);
        }
        bit = 1;
        for (i = 0; i < 8; i++) {
            if (plw[0].wu.cg_cancel & bit) {
                tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_cancel_on_str[i]);
            } else {
                tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_cancel_off_str[i]);
            }
            bit = bit << 1;
        }
        if (plw[0].wu.cg_cancel & 8) {
            n = plw[0].wu.cg_eftype & 0xF;
            if (n > 8) {
                tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_eftype_names[8]);
            } else {
                tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_eftype_names[n]);
            }
            n = plw[0].wu.cg_eftype >> 8;
            n &= 7;
            tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_eftype_s_str[n]);
            if (plw[0].wu.cg_eftype & 0x80) {
                tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_eftype_usemj_str[1]);
            } else {
                tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_eftype_usemj_str[0]);
            }
        } else if (plw[0].wu.cg_eftype) {
            tilemap_print_string_attr(dbg_hud_x + 37, 15, 10, dbg_eftype_str);
            bcd = debug_hex4_to_bcd(plw[0].wu.cg_eftype);
            tilemap_print_hex(dbg_hud_x + 40, 15, 10, bcd, 2, 0);
        } else {
            tilemap_print_string_attr(dbg_hud_x + 37, 15, 10, debug_blank6_msg);
        }
        tilemap_print_hex(dbg_hud_x + 37, 14, 10, plw[0].wu.cg_effect, 4, 0);
        bcd = debug_hex4_to_bcd(plw[0].wu.cg_effect);
        tilemap_print_hex(dbg_hud_x + 42, 14, 2, bcd, 4, 0);
    case 2:
        tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_cgd_type_str[plw[0].wu.cgd_type / 2]);
        tilemap_print_hex(dbg_hud_x + 37, 3, 10, plw[0].wu.cg_ctr, 4, 0);
        bcd = debug_hex4_to_bcd(plw[0].wu.cg_ctr);
        tilemap_print_hex(dbg_hud_x + 42, 3, 2, bcd, 4, 0);
        tilemap_print_hex(dbg_hud_x + 37, 4, 10, plw[0].wu.cg_type, 4, 0);
        bcd = debug_hex4_to_bcd(plw[0].wu.cg_type);
        tilemap_print_hex(dbg_hud_x + 42, 4, 2, bcd, 4, 0);
        tilemap_print_hex(dbg_hud_x + 37, 5, 10, (s16)plw[0].wu.cg_se, 4, 0);
        bcd = debug_hex4_to_bcd(plw[0].wu.cg_se);
        tilemap_print_hex(dbg_hud_x + 42, 5, 2, bcd, 4, 0);
        tilemap_print_hex(dbg_hud_x + 37, 6, 10, plw[0].wu.cg_flip, 4, 0);
        bcd = debug_hex4_to_bcd(plw[0].wu.cg_flip);
        tilemap_print_hex(dbg_hud_x + 42, 6, 2, bcd, 4, 0);
        tilemap_print_hex(dbg_hud_x + 37, 7, 10, plw[0].wu.cg_olc_ix, 4, 0);
        bcd = debug_hex4_to_bcd(plw[0].wu.cg_olc_ix);
        tilemap_print_hex(dbg_hud_x + 42, 7, 2, bcd, 4, 0);
        group = debug_cg_group_index((s16)plw[0].wu.cg_number);
        tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_cg_group_str[group]);
        base = dbg_cg_group_top_tbl[group];
        base = plw[0].wu.cg_number - base;
        tilemap_print_hex(dbg_hud_x + 43, 8, 10, base, 4, 0);
        break;
    }
}


/* provisional name */
void debug_draw_cgd_info(void) {
    s16 bcd;
    tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_pat_status_str[plw[0].wu.pat_status / 2]);
    tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_cgd_type_str[plw[0].wu.cgd_type / 2]);
    bcd = plw[0].wu.kind_of_waza;
    bcd = bcd >> 4;
    tilemap_print_string(dbg_hud_x, 0, 0xFFFF, &dbg_waza_kind_str[bcd]);
    if (plw[0].wu.kind_of_waza & 1) {
        tilemap_print_string_attr(dbg_hud_x + 40, 4, 10, dbg_waza_k_str);
    } else {
        tilemap_print_string_attr(dbg_hud_x + 40, 4, 10, dbg_waza_p_str);
    }
    if (plw[0].wu.kind_of_waza & 2) {
        tilemap_print_string_attr(dbg_hud_x + 41, 4, 10, dbg_digit0_str);
    }
    if (plw[0].wu.kind_of_waza & 4) {
        tilemap_print_string_attr(dbg_hud_x + 41, 4, 10, dbg_digit1_str);
    }
    if (plw[0].wu.kind_of_waza & 6) {
        tilemap_print_string_attr(dbg_hud_x + 41, 4, 10, dbg_digit2_str);
    }
    tilemap_print_hex(dbg_hud_x + 37, 5, 10, plw[0].wu.hit_range, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 6, 10, plw[0].wu.total_paring, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.total_paring);
    tilemap_print_hex(dbg_hud_x + 42, 6, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 7, 10, plw[0].wu.total_att_set, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.total_att_set);
    tilemap_print_hex(dbg_hud_x + 42, 7, 2, bcd, 4, 0);
    tilemap_print_hex(dbg_hud_x + 37, 8, 10, plw[0].wu.sp_tech_id, 4, 0);
    bcd = debug_hex4_to_bcd(plw[0].wu.sp_tech_id);
    tilemap_print_hex(dbg_hud_x + 42, 8, 2, bcd, 4, 0);
    if (plw[0].wu.cg_wca_ix) {
        tilemap_print_string_attr(dbg_hud_x + 37, 9, 10, dbg_wca_str);
        bcd = debug_hex4_to_bcd(plw[0].wu.cg_wca_ix);
        tilemap_print_hex(dbg_hud_x + 40, 9, 10, bcd, 2, 0);
    } else {
        tilemap_print_string_attr(dbg_hud_x + 37, 9, 10, debug_blank6_msg);
    }
}


/* provisional name */
void debug_hud_mode_dispatch(void) {
    u16 trg = ~dbg_p2sw_1 & dbg_p2sw_0;
    if (trg & BUTTON_START) {
        dbg_hud_mode++;
        if (dbg_hud_mode > 4) {
            dbg_hud_mode = 0;
        }
        switch (dbg_hud_mode) {
        case 0:
            tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_hud_clr_str);
            tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_hud_clr_bottom_str);
            break;
        case 1:
            tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_hud_clr_bottom_str);
            tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_cg_head_str);
            break;
        case 2:
            tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_hud_clr_bottom_str);
            switch (plw[0].wu.cgd_type) {
            case 6:
                tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_hud_clr_low_str);
            case 4:
                tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_hud_clr_mid_str);
            case 2:
                tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_hud_clr_str);
                break;
            }
            tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_att_data_str);
            break;
        case 3:
            tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_hud_clr_str);
            tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_cm_label_str);
            break;
        case 4:
            tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_hud_clr_str);
            tilemap_print_string(dbg_hud_x, 0, 0xFFFF, dbg_cgd_info_str);
            break;
        }
    }
    switch (dbg_hud_mode) {
    case 1:
        debug_draw_cg_data();
        break;
    case 2:
        debug_draw_att_data();
        break;
    case 3:
        debug_draw_cm_data();
        break;
    case 4:
        debug_draw_cgd_info();
        break;
    }
}


/* provisional name */
s16 debug_catch_move_record(SNAPSHOT* p1, SNAPSHOT* p2) {
    SNAPSHOT* s1;
    SNAPSHOT* s2;
    if (plw[0].wu.now_koc != 2) {
        return 0;
    }
    plw[0].tsukami_num = plw[1].player_number;
    set_char_move_init(&plw[0].wu, 2, plw[0].wu.char_index);
    set_char_move_init(&plw[1].wu, 3, plw[0].wu.cmyd.ix);
    if (plw[0].wu.cmyd.pat == 0) {
        return 0;
    }
    Debug_CG_Flip[0] = plw[0].wu.cg_flip;
    Debug_Flip_Mask[0] = 0;
    Debug_RL_Flag[0] = plw[0].wu.rl_flag;
    Debug_CG_Flip[1] = plw[1].wu.cg_flip;
    Debug_Flip_Mask[1] = 0;
    Debug_RL_Flag[1] = plw[1].wu.rl_flag;
    Debug_Rec_Count = 0;
    if (plw[0].wu.cmyd.pat == 1) {
        while (1) {
            Debug_Rec_Count++;
            s1 = &p1[Debug_Rec_Count];
            s2 = &p2[Debug_Rec_Count];
            if (plw[0].wu.cg_rival) {
                char_move_index(&plw[1].wu, plw[0].wu.curr_rca->catch_nix);
                plw[1].wu.rl_flag = plw[0].wu.rl_flag ^ plw[0].wu.curr_rca->catch_flip;
                if (plw[0].wu.rl_flag) {
                    plw[1].wu.xyz[0].disp.pos = plw[0].wu.xyz[0].disp.pos - plw[0].wu.curr_rca->catch_hos_x;
                } else {
                    plw[1].wu.xyz[0].disp.pos = plw[0].wu.xyz[0].disp.pos + plw[0].wu.curr_rca->catch_hos_x;
                }
                plw[1].wu.xyz[1].disp.pos = plw[0].wu.xyz[1].disp.pos + plw[0].wu.curr_rca->catch_hos_y;
                if (plw[0].wu.curr_rca->catch_prio == 2) {
                    plw[1].wu.next_z = plw[0].wu.xyz[2].disp.pos - 1;
                } else {
                    plw[1].wu.next_z = plw[0].wu.xyz[2].disp.pos + 1;
                }
            }
            debug_move_snapshot_frame(s1, &plw[0].wu, plw[0].wu.xyz[2].disp.pos);
            debug_move_snapshot_frame(s2, &plw[1].wu, plw[1].wu.next_z);
            char_move_z(&plw[0].wu);
            Debug_CG_Flip[0] = plw[0].wu.cg_flip;
            Debug_Flip_Mask[0] = 0;
            Debug_RL_Flag[0] = plw[0].wu.rl_flag;
            if (plw[0].wu.cg_type == 0xFF) {
                break;
            }
        }
    } else {
        while (1) {
            Debug_Rec_Count++;
            s1 = &p1[Debug_Rec_Count];
            s2 = &p2[Debug_Rec_Count];
            if (plw[0].wu.cg_rival) {
                char_move_index(&plw[1].wu, plw[0].wu.curr_rca->catch_nix);
                plw[1].wu.rl_flag = plw[0].wu.rl_flag ^ plw[0].wu.curr_rca->catch_flip;
                if (plw[0].wu.rl_flag) {
                    plw[0].wu.xyz[0].disp.pos = plw[1].wu.xyz[0].disp.pos + plw[0].wu.curr_rca->catch_hos_x;
                } else {
                    plw[0].wu.xyz[0].disp.pos = plw[1].wu.xyz[0].disp.pos - plw[0].wu.curr_rca->catch_hos_x;
                }
                plw[0].wu.xyz[1].disp.pos = plw[1].wu.xyz[1].disp.pos - plw[0].wu.curr_rca->catch_hos_y;
                if (plw[0].wu.curr_rca->catch_prio == 2) {
                    plw[1].wu.next_z = plw[0].wu.xyz[2].disp.pos - 1;
                } else {
                    plw[1].wu.next_z = plw[0].wu.xyz[2].disp.pos + 1;
                }
            }
            debug_move_snapshot_frame(s1, &plw[0].wu, plw[0].wu.xyz[2].disp.pos);
            debug_move_snapshot_frame(s2, &plw[1].wu, plw[1].wu.next_z);
            char_move_z(&plw[0].wu);
            Debug_CG_Flip[0] = plw[0].wu.cg_flip;
            Debug_Flip_Mask[0] = 0;
            Debug_RL_Flag[0] = plw[0].wu.rl_flag;
            if (plw[0].wu.cg_type == 0xFF) {
                break;
            }
        }
    }
    return 1;
}


/* provisional name */
void debug_move_snapshot_frame(SNAPSHOT* rec, WORK* wk, s16 priority) {
    rec->pos_x = wk->xyz[0].disp.pos;
    rec->pos_y = wk->xyz[1].disp.pos;
    rec->priority = priority;
    rec->cg_number = wk->cg_number;
    rec->dbg_rl_flag = wk->rl_flag;
    rec->dbg_cg_flip = wk->cg_flip;
    rec->used = 1;
    rec->cg_ctr = wk->cg_ctr;
    rec->col_mode = wk->my_col_mode;
    rec->col_code = wk->my_col_code;
    rec->olc_ix = wk->cg_olc_ix;
    rec->rl_flag = wk->rl_flag;
    rec->cg_flip = wk->cg_flip;
}


/* provisional name */
