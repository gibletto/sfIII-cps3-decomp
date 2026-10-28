/*
 * MODE_INIT.C  Mode initialisation and screen mode setup
 *
 * mode_init_task initialises the game for the selected mode; region_setup splits the BIOS
 * region byte into country and version, region_group_params_set picks the per-region
 * parameters; mode_init_task also sets the screen mode for normal or wide screen.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Sub.h"
#include "ACTIVE00.h"
#include "active01.h"
#include "active02.h"
#include "active03.h"
#include "active04.h"
#include "active05.h"
#include "active07.h"
#include "active08.h"
#include "active09.h"
#include "active11.h"
#include "active12.h"
#include "FOLLOW01.h"
#include "FOLLOW02.h"
#include "fifo.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "pass00.h"
#include "PASS01.h"
#include "PASS02.h"
#include "PASS03.h"
#include "PASS04.h"
#include "PASS05.h"
#include "PASS07.h"
#include "PASS08.h"
#include "PASS09.h"
#include "PASS11.h"
#include "PASS12.h"
#include "SHELL00.h"
#include "SHELL01.h"
#include "SHELL03.h"
#include "SHELL04.h"
#include "SHELL11.h"
#include "SHELL12.h"
#include "Entry.h"
#include "entry_2.h"
#include "CMD_MAIN.h"
#include "cmd_main_2.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "PLS02.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sc_trans.h"
#include "Manage.h"
#include "manage_2.h"
#include "bg0001.h"
#include "Com_Pl.h"
#include "cps3.h"
#include "fighter.h"
#include "RANKING.h"

#define BOOT_TITLE_ATTR(palette) ((palette) * 2)
#define BOOT_REGION_ATTR(palette) ((palette) << 1)
#define BOOT_NO_CD_ATTR(palette) ((palette) * 2U)




extern const u8 game_cfg_default_tbl_row0[];
extern const u8 game_cfg_default_tbl_row1[];
extern const u8 game_cfg_default_tbl_row2[];
extern const u8 game_cfg_default_tbl_row3[];
extern const u8 game_cfg_default_tbl_row4[];
extern const u8 game_cfg_default_tbl_row5[];
extern const u8 game_cfg_default_tbl_row6[];
extern const u8 game_cfg_default_tbl_row7[];
extern const u8 game_cfg_default_tbl_row8[];
extern const char str_Asian_countries_only[];
extern const char str_Canada_and_the_Federative_Republ[];
extern const char str_Sales_export_or_operation_outsid[];
extern const char str_Sales_export_or_operation_outsid_2[];
extern const char str_This_game_is_for_use_in_japan_on[];
extern const char str_This_game_is_for_use_in_the_Euro[];
extern const char str_This_game_is_for_use_in_the_Fede[];
extern const char str_This_game_is_for_use_in_the_Ocea[];
extern const char str_This_game_is_for_use_in_the_Unit[];
extern const char str_This_game_is_for_use_in_the_West[];
extern const char str_This_game_is_for_use_in_the_sout[];
extern const char str_Violators_are_subject_to_severe_[];
extern const char str_WARNING[];
extern const char str_Parental_Advisory[];
extern const char str_Animated_violence_Mild[];
extern const char str_Contains_scenes_of_violence[];
extern const char str_cartoon_like_characters[];
extern const char str_and_trademark_infringement_and_i[];
extern const char str_and_will_be_prosecuted_to_the_fu[];
extern const char str_blank_2[];
extern const char str_countries_except_the_United_Stat[];
extern const char str_countries_may_be_construed_as_co[];
extern const char str_country_may_be_construed_as_copy[];
extern const char str_country_may_be_construed_as_copy_2[];
extern const char str_of_America_and_Canada_only[];
extern const char str_of_Brazil_only[];
extern const char str_of_the_law[];
extern const char str_only[];
extern const char str_prohibited[];
extern const char str_trademark_infringement_and_is_st[];
extern const u8 sys_cfg_default_0_0[];
extern const u8 sys_cfg_default_0_1[];
extern const u8 sys_cfg_default_1_1[];
extern const u8 sys_cfg_default_1_2[];
extern const u8 sys_cfg_default_1_4[];
extern const u8 sys_cfg_default_1_3[];
extern const u8 sys_cfg_default_1_5[];
extern const u8 sys_cfg_default_1_6[];
extern const u8 sys_cfg_default_1_7[];
extern const u8 sys_cfg_default_1_8[];
extern const u8 sys_cfg_default_2_0[];
extern const u8 sys_cfg_default_2_1[];
extern const u8 sys_cfg_default_0_2[];
extern const u8 sys_cfg_default_2_2[];
extern const u8 sys_cfg_default_2_4[];
extern const u8 sys_cfg_default_2_3[];
extern const u8 sys_cfg_default_2_5[];
extern const u8 sys_cfg_default_2_6[];
extern const u8 sys_cfg_default_2_7[];
extern const u8 sys_cfg_default_2_8[];
extern const u8 sys_cfg_default_0_4[];
extern const u8 sys_cfg_default_0_3[];
extern const u8 sys_cfg_default_0_5[];
extern const u8 sys_cfg_default_0_6[];
extern const u8 sys_cfg_default_0_7[];
extern const u8 sys_cfg_default_0_8[];
extern const u8 sys_cfg_default_1_0[];

/* 0200011C */
TM_STRING warning_mes[8][11] = {
    { { 0x13, 2, 2, (void*)(str_WARNING) }, { 2, 4, 2, (void*)(str_This_game_is_for_use_in_japan_on) }, { 2, 6, 2, (void*)(str_Sales_export_or_operation_outsid) }, { 2, 8, 2, (void*)(str_country_may_be_construed_as_copy) }, { 2, 0xA, 2, (void*)(str_and_trademark_infringement_and_i) }, { 2, 0xC, 2, (void*)(str_prohibited) }, { 2, 0xE, 2, (void*)(str_Violators_are_subject_to_severe_) }, { 2, 0x10, 2, (void*)(str_and_will_be_prosecuted_to_the_fu) }, { 2, 0x12, 2, (void*)(str_of_the_law) }, { 2, 0x14, 2, (void*)(str_blank_2) }, { 2, 0x16, 2, (void*)(str_blank_2) } },
    { { 0x13, 2, 4, (void*)(str_WARNING) }, { 2, 4, 4, (void*)(str_This_game_is_for_use_in_the_sout) }, { 2, 6, 4, (void*)(str_Asian_countries_only) }, { 2, 8, 4, (void*)(str_Sales_export_or_operation_outsid_2) }, { 2, 0xA, 4, (void*)(str_countries_may_be_construed_as_co) }, { 2, 0xC, 4, (void*)(str_trademark_infringement_and_is_st) }, { 2, 0xE, 4, (void*)(str_prohibited) }, { 2, 0x10, 4, (void*)(str_Violators_are_subject_to_severe_) }, { 2, 0x12, 4, (void*)(str_and_will_be_prosecuted_to_the_fu) }, { 2, 0x14, 4, (void*)(str_of_the_law) }, { 2, 0x16, 4, (void*)(str_blank_2) } },
    { { 0x13, 2, 6, (void*)(str_WARNING) }, { 1, 4, 6, (void*)(str_This_game_is_for_use_in_the_Euro) }, { 1, 6, 6, (void*)(str_only) }, { 1, 8, 6, (void*)(str_Sales_export_or_operation_outsid_2) }, { 1, 0xA, 6, (void*)(str_countries_may_be_construed_as_co) }, { 1, 0xC, 6, (void*)(str_trademark_infringement_and_is_st) }, { 1, 0xE, 6, (void*)(str_prohibited) }, { 1, 0x10, 6, (void*)(str_Violators_are_subject_to_severe_) }, { 1, 0x12, 6, (void*)(str_and_will_be_prosecuted_to_the_fu) }, { 1, 0x14, 6, (void*)(str_of_the_law) }, { 1, 0x16, 6, (void*)(str_blank_2) } },
    { { 0x13, 2, 8, (void*)(str_WARNING) }, { 2, 4, 8, (void*)(str_This_game_is_for_use_in_the_Unit) }, { 2, 6, 8, (void*)(str_of_America_and_Canada_only) }, { 2, 8, 8, (void*)(str_Sales_export_or_operation_outsid_2) }, { 2, 0xA, 8, (void*)(str_countries_may_be_construed_as_co) }, { 2, 0xC, 8, (void*)(str_trademark_infringement_and_is_st) }, { 2, 0xE, 8, (void*)(str_prohibited) }, { 2, 0x10, 8, (void*)(str_Violators_are_subject_to_severe_) }, { 2, 0x12, 8, (void*)(str_and_will_be_prosecuted_to_the_fu) }, { 2, 0x14, 8, (void*)(str_of_the_law) }, { 2, 0x16, 8, (void*)(str_blank_2) } },
    { { 0x13, 2, 0xA, (void*)(str_WARNING) }, { 1, 4, 0xA, (void*)(str_This_game_is_for_use_in_the_West) }, { 1, 6, 0xA, (void*)(str_countries_except_the_United_Stat) }, { 1, 8, 0xA, (void*)(str_Canada_and_the_Federative_Republ) }, { 1, 0xA, 0xA, (void*)(str_Sales_export_or_operation_outsid_2) }, { 1, 0xC, 0xA, (void*)(str_countries_may_be_construed_as_co) }, { 1, 0xE, 0xA, (void*)(str_trademark_infringement_and_is_st) }, { 1, 0x10, 0xA, (void*)(str_prohibited) }, { 1, 0x12, 0xA, (void*)(str_Violators_are_subject_to_severe_) }, { 1, 0x14, 0xA, (void*)(str_and_will_be_prosecuted_to_the_fu) }, { 1, 0x16, 0xA, (void*)(str_of_the_law) } },
    { { 0x13, 2, 0xC, (void*)(str_WARNING) }, { 1, 4, 0xC, (void*)(str_This_game_is_for_use_in_the_Fede) }, { 1, 6, 0xC, (void*)(str_of_Brazil_only) }, { 1, 8, 0xC, (void*)(str_Sales_export_or_operation_outsid) }, { 1, 0xA, 0xC, (void*)(str_country_may_be_construed_as_copy_2) }, { 1, 0xC, 0xC, (void*)(str_trademark_infringement_and_is_st) }, { 1, 0xE, 0xC, (void*)(str_prohibited) }, { 1, 0x10, 0xC, (void*)(str_Violators_are_subject_to_severe_) }, { 1, 0x12, 0xC, (void*)(str_and_will_be_prosecuted_to_the_fu) }, { 1, 0x14, 0xC, (void*)(str_of_the_law) }, { 1, 0x16, 0xC, (void*)(str_blank_2) } },
    { { 0x13, 2, 0xE, (void*)(str_WARNING) }, { 1, 4, 0xE, (void*)(str_This_game_is_for_use_in_the_Ocea) }, { 1, 6, 0xE, (void*)(str_only) }, { 1, 8, 0xE, (void*)(str_Sales_export_or_operation_outsid_2) }, { 1, 0xA, 0xE, (void*)(str_countries_may_be_construed_as_co) }, { 1, 0xC, 0xE, (void*)(str_trademark_infringement_and_is_st) }, { 1, 0xE, 0xE, (void*)(str_prohibited) }, { 1, 0x10, 0xE, (void*)(str_Violators_are_subject_to_severe_) }, { 1, 0x12, 0xE, (void*)(str_and_will_be_prosecuted_to_the_fu) }, { 1, 0x14, 0xE, (void*)(str_of_the_law) }, { 1, 0x16, 0xE, (void*)(str_blank_2) } },
    { { 0x13, 2, 4, (void*)(str_WARNING) }, { 2, 4, 4, (void*)(str_This_game_is_for_use_in_the_sout) }, { 2, 6, 4, (void*)(str_Asian_countries_only) }, { 2, 8, 4, (void*)(str_Sales_export_or_operation_outsid_2) }, { 2, 0xA, 4, (void*)(str_countries_may_be_construed_as_co) }, { 2, 0xC, 4, (void*)(str_trademark_infringement_and_is_st) }, { 2, 0xE, 4, (void*)(str_prohibited) }, { 2, 0x10, 4, (void*)(str_Violators_are_subject_to_severe_) }, { 2, 0x12, 4, (void*)(str_and_will_be_prosecuted_to_the_fu) }, { 2, 0x14, 4, (void*)(str_of_the_law) }, { 2, 0x16, 4, (void*)(str_blank_2) } },
};
/* 0200053C */
TM_STRING parental_advisory_msg[4] = {
    { 6, 0x16, 0x12, (void*)(str_Parental_Advisory) },
    { 6, 0x17, 0x12, (void*)(str_Animated_violence_Mild) },
    { 1, 0x19, 0x12, (void*)(str_Contains_scenes_of_violence) },
    { 1, 0x1A, 0x12, (void*)(str_cartoon_like_characters) },
};
/* 0200056C */
/* The default settings rows of each cabinet type (sys_cfg_default_tbl), nine per type. */
const u8* sys_cfg_default_list[3][9] = {
    { sys_cfg_default_0_0, sys_cfg_default_0_1, sys_cfg_default_0_2, sys_cfg_default_0_3, sys_cfg_default_0_4, sys_cfg_default_0_5, sys_cfg_default_0_6, sys_cfg_default_0_7, sys_cfg_default_0_8 },
    { sys_cfg_default_1_0, sys_cfg_default_1_1, sys_cfg_default_1_2, sys_cfg_default_1_3, sys_cfg_default_1_4, sys_cfg_default_1_5, sys_cfg_default_1_6, sys_cfg_default_1_7, sys_cfg_default_1_8 },
    { sys_cfg_default_2_0, sys_cfg_default_2_1, sys_cfg_default_2_2, sys_cfg_default_2_3, sys_cfg_default_2_4, sys_cfg_default_2_5, sys_cfg_default_2_6, sys_cfg_default_2_7, sys_cfg_default_2_8 },
};
/* 020005D8 */
u32 sys_cfg_default_tbl[3] = {
    (u32)sys_cfg_default_list[0], (u32)sys_cfg_default_list[1], (u32)sys_cfg_default_list[2],
};
/* 020005E4 */
u8* game_cfg_default_tbl[9] = {
    (void*)(game_cfg_default_tbl_row0),
    (void*)(game_cfg_default_tbl_row1),
    (void*)(game_cfg_default_tbl_row2),
    (void*)(game_cfg_default_tbl_row3),
    (void*)(game_cfg_default_tbl_row4),
    (void*)(game_cfg_default_tbl_row5),
    (void*)(game_cfg_default_tbl_row6),
    (void*)(game_cfg_default_tbl_row7),
    (void*)(game_cfg_default_tbl_row8),
};
/* Stored after game_cfg_default_tbl. Nothing in the program refers to it by name or address; if it is read,
   it is through an index past the end of game_cfg_default_tbl. */
u32 game_cfg_default_tbl_tail[1] = {
    0x10000,
};


/* Start-up task, created by boot_task (and again by the test menu when it
   returns to the game).  Sets up the region, the video and sound work, the
   coin and switch work and the settings from EEPROM, clears the game state,
   starts test_mode_task, then shows the title with the region name and the
   region's warning screen (each can be cut short with a button), and finally
   starts the per-frame tasks and ends itself. */
/* provisional name */
void mode_init_task(void) {
    s16 wait;
    u8 region;
    s32 color;
    s16* title_x;

    region_setup();
    CC_Type = region_cc_type_tbl[Country - 1];
    region_group_params_set();
    init_render_lists();
    init_color_trans_req();
    init_char_gfx_tables();
    clear_scroll_layer_state_and_mask();
    Scrn_Pos_Init();
    Family_Init();
    coin_work_init();
    palette_bank_set(0x3FC00);
    palette_write(0, sys_palette, 256);
    tilemap_chunk_copy_16b((s16*)(SS_RAM + 0x8000), (char*)sys_font_cg, 140);
    switch_work_clear(Cabinet_Type);
    dispenser_init();
    eeprom_config_load();
    task_sleep(60);
    Win_Point_Split = 1;
    tilemap_fill_all(0, 32);
    task_sleep(1);

    test_flag = 0;
    Cd_Error_Flag = 0;
    Break_Into = 0;
    Forbid_Break = 0;
    Fade_Half_Flag = 0;
    Demo_Flag = 0;
    Random_ix16_com = 0;
    Random_ix32_com = 0;
    unused_flag_a = 0;
    judge_disp_all = 0;
    unused_flag_b = 0;
    unused_flag_c = 0;
    test_sw_lock = 0;
    PB_Music_Off = 0;
    No_Death = 0;
    Request_Break[0] = Request_Break[1] = 0;
    G_No0 = G_No1 = G_No2 = G_No3 = 0;
    E_No0 = E_No1 = E_No2 = E_No3 = 0;
    S_No = S_Sub_No = S_Sub2_No = S_Sub3_No = 0;
    Fade_R_No0 = Fade_R_No1 = 0;
    Fade_Flag = 0;
    if (Free_Play) {
        credit_1p = 9;
        credit_2p = 9;
    }
    /* the screen mode and the column table */
    if (Game_setting.mode) {
        set_screen_mode(7);
        DE_X[0] = 8;
        DE_X[1] = 16;
        DE_X[2] = 6;
        DE_X[3] = 7;
        DE_X[4] = 9;
        DE_X[5] = 112;
        DE_X[6] = 4;
        DE_X[7] = 11;
        DE_X[8] = 2;
        DE_X[9] = 12;
        DE_X[10] = 56;
        DE_X[11] = 0x100;
        DE_X[12] = 13;
        DE_X[13] = 1;
        DE_X[14] = 32;
        DE_X[15] = 16;
    } else {
        set_screen_mode(3);
        DE_X[0] = 0;
        DE_X[1] = 0;
        DE_X[2] = 0;
        DE_X[3] = 0;
        DE_X[4] = 0;
        DE_X[5] = 0;
        DE_X[6] = 0;
        DE_X[7] = 0;
        DE_X[8] = 0;
        DE_X[9] = 0;
        DE_X[10] = 0;
        DE_X[11] = 0xC0;
        DE_X[12] = 0;
        DE_X[13] = 0;
        DE_X[14] = 0;
        DE_X[15] = 0;
    }
    effect_work_init();
    task_sleep(1);
    while (create_task((void (*)())test_mode_task, 0, &task_tbl[4], 2, 0) == 0) {
    }

    /* title and region name, in the region's colour */
    region = bios_region_code;
    region &= 0xF;
    if (region >= 8) {
        region = 8;
    } else {
        region &= 7;
    }
    if (region >= 8) {
        color = 2;
    } else if (region & 7) {
        color = region & 7;
    } else {
        color = 1;
    }
    tilemap_print_string(*(title_x = &DE_X[3]), 0, BOOT_TITLE_ATTR(color), boot_title_str);
    tilemap_print_string(*title_x, 0, BOOT_REGION_ATTR(color), &boot_region_str[region]);
    task_sleep(6);
    for (wait = 166; --wait > 0; ) {
        if ((p1sw_0 | p2sw_0) & 0x7F0) {
            wait = 0;
        }
        task_sleep(1);
    }

    /* warning screen for this country */
    tilemap_fill_all(0, 32);
    load_char_gfx(0x4000, 1);
    load_char_gfx(0x4090, 1);
    setup_kage_cells();
    tilemap_print_string(DE_X[3], 0, 0xFFFF, warning_mes[Country - 1]);
    task_sleep(16);
    for (wait = 100; --wait > 0; ) {
        if ((p1sw_0 | p2sw_0) & 0x7F0) {
            wait = 0;
        }
        task_sleep(1);
    }

    tilemap_fill_all(0, 32);
    Setup_Com_Max_Range();
    load_any_color(2);
    ToneDown(0);
    Ranking_Init();
    while (create_task((void (*)())game_frame_task, 0, &task_tbl[3], 3, 0) == 0) {
    }
    while (create_task((void (*)())entry_task, 0, &task_tbl[2], 3, 0) == 0) {
    }
    cd_ready_flag = 0;
    if (Version_Type == 0 && Country != 2) {
        no_cd_flag = 0;
    } else {
        no_cd_flag = 1;
    }
    destroy_current_task();
}



/* provisional name */
void region_setup(void) {
    Country = bios_region_code & 0xF;
    Version_Type = bios_region_code & 0xF0;
    Version_Type >>= 4;
    if (Version_Type >= 8) {
        Version_Type = 7;
    }
    Area_Type = region_type_tbl[Country];
}


/* provisional name */
void region_cc_type_set(void) {
    CC_Type = region_cc_type_tbl[Country - 1];
}



/* provisional name */
void region_group_params_set(void) {
    CC_Value[0] = region_param_tbl[CC_Type][0];
    CC_Value[1] = region_param_tbl[CC_Type][1];
}
