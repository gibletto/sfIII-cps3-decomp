/*
 * TEST_MENU_SCR.C  test menu screens
 *
 * The screen scripts of the test menu and the system configuration pages (sys_config_2.c, test_mode.c): initialised
 * work RAM (section D).
 */

#include "types.h"
#include "structs.h"

extern TM_STRING test_menu_str[];
extern TM_STRING test_menu_str_asia[];
extern TMSCRIPT test_menu_scr_jp[];
extern TMSCRIPT config_top_scr_jp[];
extern TMSCRIPT sys_cfg_page_scr_jp[];
extern TMSCRIPT sys_cfg_exit_guide_jp[];
extern TMSCRIPT sys_cfg_item_guide_jp[];
extern TMSCRIPT cfg_top_guide_jp[];
extern TMSCRIPT cfg_top_reset_guide_jp[];
extern TMSCRIPT * sys_cfg_coin_scr_jp[];
extern TMSCRIPT * sys_cfg_chute_scr_jp[];
extern TMSCRIPT * sys_cfg_continue_scr_jp[];
extern TMSCRIPT * sys_cfg_monitor_scr_jp[];
extern TMSCRIPT * sys_cfg_demo_scr_jp[];
extern TMSCRIPT * sys_cfg_sound_scr_jp[];
extern const s8 test_menu_str_0[];
extern const s8 test_menu_str_10[];
extern const s8 test_menu_str_11[];
extern const s8 test_menu_str_12[];
extern const s8 test_menu_str_1[];
extern const s8 test_menu_str_2[];
extern const s8 test_menu_str_3[];
extern const s8 test_menu_str_4[];
extern const s8 test_menu_str_5[];
extern const s8 test_menu_str_6[];
extern const s8 test_menu_str_7[];
extern const s8 test_menu_str_8[];
extern const s8 test_menu_str_9[];
extern const s8 test_menu_str_asia_9[];
extern const u16 cfg_top_guide_jp_0[];
extern const u16 cfg_top_reset_guide_jp_0[];
extern const u16 config_top_scr_jp_0[];
extern const u16 sys_cfg_exit_guide_jp_0[];
extern const u16 sys_cfg_item_guide_jp_0[];
extern const u16 sys_cfg_page_scr_jp_0[];
extern const u16 sys_cfg_page_scr_jp_10[];
extern const u16 sys_cfg_page_scr_jp_11[];
extern const u16 sys_cfg_page_scr_jp_12[];
extern const u16 sys_cfg_page_scr_jp_13[];
extern const u16 sys_cfg_page_scr_jp_14[];
extern const u16 sys_cfg_page_scr_jp_15[];
extern const u16 sys_cfg_page_scr_jp_16[];
extern const u16 sys_cfg_page_scr_jp_17[];
extern const u16 sys_cfg_page_scr_jp_18[];
extern const u16 sys_cfg_page_scr_jp_19[];
extern const u16 sys_cfg_page_scr_jp_1[];
extern const u16 sys_cfg_page_scr_jp_20[];
extern const u16 sys_cfg_page_scr_jp_21[];
extern const u16 sys_cfg_page_scr_jp_22[];
extern const u16 sys_cfg_page_scr_jp_23[];
extern const u16 sys_cfg_page_scr_jp_24[];
extern const u16 sys_cfg_page_scr_jp_25[];
extern const u16 sys_cfg_page_scr_jp_26[];
extern const u16 sys_cfg_page_scr_jp_27[];
extern const u16 sys_cfg_page_scr_jp_28[];
extern const u16 sys_cfg_page_scr_jp_29[];
extern const u16 sys_cfg_page_scr_jp_2[];
extern const u16 sys_cfg_page_scr_jp_30[];
extern const u16 sys_cfg_page_scr_jp_31[];
extern const u16 sys_cfg_page_scr_jp_32[];
extern const u16 sys_cfg_page_scr_jp_33[];
extern const u16 sys_cfg_page_scr_jp_34[];
extern const u16 sys_cfg_page_scr_jp_35[];
extern const u16 sys_cfg_page_scr_jp_36[];
extern const u16 sys_cfg_page_scr_jp_37[];
extern const u16 sys_cfg_page_scr_jp_38[];
extern const u16 sys_cfg_page_scr_jp_39[];
extern const u16 sys_cfg_page_scr_jp_3[];
extern const u16 sys_cfg_page_scr_jp_40[];
extern const u16 sys_cfg_page_scr_jp_41[];
extern const u16 sys_cfg_page_scr_jp_42[];
extern const u16 sys_cfg_page_scr_jp_43[];
extern const u16 sys_cfg_page_scr_jp_44[];
extern const u16 sys_cfg_page_scr_jp_45[];
extern const u16 sys_cfg_page_scr_jp_46[];
extern const u16 sys_cfg_page_scr_jp_47[];
extern const u16 sys_cfg_page_scr_jp_48[];
extern const u16 sys_cfg_page_scr_jp_49[];
extern const u16 sys_cfg_page_scr_jp_4[];
extern const u16 sys_cfg_page_scr_jp_50[];
extern const u16 sys_cfg_page_scr_jp_51[];
extern const u16 sys_cfg_page_scr_jp_52[];
extern const u16 sys_cfg_page_scr_jp_53[];
extern const u16 sys_cfg_page_scr_jp_54[];
extern const u16 sys_cfg_page_scr_jp_55[];
extern const u16 sys_cfg_page_scr_jp_56[];
extern const u16 sys_cfg_page_scr_jp_57[];
extern const u16 sys_cfg_page_scr_jp_58[];
extern const u16 sys_cfg_page_scr_jp_59[];
extern const u16 sys_cfg_page_scr_jp_5[];
extern const u16 sys_cfg_page_scr_jp_60[];
extern const u16 sys_cfg_page_scr_jp_61[];
extern const u16 sys_cfg_page_scr_jp_62[];
extern const u16 sys_cfg_page_scr_jp_63[];
extern const u16 sys_cfg_page_scr_jp_64[];
extern const u16 sys_cfg_page_scr_jp_65[];
extern const u16 sys_cfg_page_scr_jp_66[];
extern const u16 sys_cfg_page_scr_jp_67[];
extern const u16 sys_cfg_page_scr_jp_68[];
extern const u16 sys_cfg_page_scr_jp_69[];
extern const u16 sys_cfg_page_scr_jp_6[];
extern const u16 sys_cfg_page_scr_jp_70[];
extern const u16 sys_cfg_page_scr_jp_71[];
extern const u16 sys_cfg_page_scr_jp_72[];
extern const u16 sys_cfg_page_scr_jp_73[];
extern const u16 sys_cfg_page_scr_jp_74[];
extern const u16 sys_cfg_page_scr_jp_75[];
extern const u16 sys_cfg_page_scr_jp_76[];
extern const u16 sys_cfg_page_scr_jp_77[];
extern const u16 sys_cfg_page_scr_jp_78[];
extern const u16 sys_cfg_page_scr_jp_79[];
extern const u16 sys_cfg_page_scr_jp_7[];
extern const u16 sys_cfg_page_scr_jp_80[];
extern const u16 sys_cfg_page_scr_jp_8[];
extern const u16 sys_cfg_page_scr_jp_9[];
extern const u16 sys_cfg_sound_page_scr_jp_0[];
extern const u16 test_menu_scr_jp_0[];

/* 0200060C */
TM_STRING test_menu_str[13] = {
    { 15, 1, 2, test_menu_str_0 },
    { 16, 3, 2, test_menu_str_1 },
    { 16, 5, 2, test_menu_str_2 },
    { 16, 7, 2, test_menu_str_3 },
    { 16, 9, 2, test_menu_str_4 },
    { 16, 11, 2, test_menu_str_5 },
    { 16, 13, 2, test_menu_str_6 },
    { 16, 15, 2, test_menu_str_7 },
    { 16, 17, 2, test_menu_str_8 },
    { 16, 19, 2, test_menu_str_9 },
    { 16, 21, 2, test_menu_str_10 },
    { 13, 26, 2, test_menu_str_11 },
    { 13, 27, 2, test_menu_str_12 },
};

/* 020006A8 */
TM_STRING test_menu_str_asia[12] = {
    { 15, 1, 2, test_menu_str_0 },
    { 16, 3, 2, test_menu_str_1 },
    { 16, 5, 2, test_menu_str_2 },
    { 16, 7, 2, test_menu_str_3 },
    { 16, 9, 2, test_menu_str_4 },
    { 16, 11, 2, test_menu_str_5 },
    { 16, 13, 2, test_menu_str_6 },
    { 16, 15, 2, test_menu_str_7 },
    { 16, 17, 2, test_menu_str_8 },
    { 16, 19, 2, test_menu_str_asia_9 },
    { 13, 26, 2, test_menu_str_11 },
    { 13, 27, 2, test_menu_str_12 },
};

/* 02000738 */
TMSCRIPT test_menu_scr_jp[1] = {
    { 1, 0, test_menu_scr_jp_0 },
};

/* 02000740 */
TMSCRIPT config_top_scr_jp[1] = {
    { 1, 0, config_top_scr_jp_0 },
};

/* 02000748 */
TMSCRIPT sys_cfg_page_scr_jp[2] = {
    { 1, 0, sys_cfg_page_scr_jp_0 }, { 1, 0, sys_cfg_page_scr_jp_1 },
};

/* 02000758 */
/* one script for each coin setting, picked through sys_cfg_coin_scr_jp; provisional name */
TMSCRIPT sys_cfg_coin_text_jp[19] = {
    { 1, 0, sys_cfg_page_scr_jp_2 }, { 1, 0, sys_cfg_page_scr_jp_3 },
    { 1, 0, sys_cfg_page_scr_jp_4 }, { 1, 0, sys_cfg_page_scr_jp_5 },
    { 1, 0, sys_cfg_page_scr_jp_6 }, { 1, 0, sys_cfg_page_scr_jp_7 },
    { 1, 0, sys_cfg_page_scr_jp_8 }, { 1, 0, sys_cfg_page_scr_jp_9 },
    { 1, 0, sys_cfg_page_scr_jp_10 }, { 1, 0, sys_cfg_page_scr_jp_11 },
    { 1, 0, sys_cfg_page_scr_jp_12 }, { 1, 0, sys_cfg_page_scr_jp_13 },
    { 1, 0, sys_cfg_page_scr_jp_14 }, { 1, 0, sys_cfg_page_scr_jp_15 },
    { 1, 0, sys_cfg_page_scr_jp_16 }, { 1, 0, sys_cfg_page_scr_jp_17 },
    { 1, 0, sys_cfg_page_scr_jp_18 }, { 1, 0, sys_cfg_page_scr_jp_19 },
    { 1, 0, sys_cfg_page_scr_jp_20 },
};

/* 020007F0 */
/* one script for each coin chute setting, picked through sys_cfg_chute_scr_jp; provisional name */
TMSCRIPT sys_cfg_chute_text_jp[12] = {
    { 1, 0, sys_cfg_page_scr_jp_21 }, { 1, 0, sys_cfg_page_scr_jp_22 },
    { 1, 0, sys_cfg_page_scr_jp_23 }, { 1, 0, sys_cfg_page_scr_jp_24 },
    { 1, 0, sys_cfg_page_scr_jp_25 }, { 1, 0, sys_cfg_page_scr_jp_26 },
    { 1, 0, sys_cfg_page_scr_jp_27 }, { 1, 0, sys_cfg_page_scr_jp_28 },
    { 1, 0, sys_cfg_page_scr_jp_29 }, { 1, 0, sys_cfg_page_scr_jp_30 },
    { 1, 0, sys_cfg_page_scr_jp_31 }, { 1, 0, sys_cfg_page_scr_jp_32 },
};

/* 02000850 */
/* one script for each continue setting, picked through sys_cfg_continue_scr_jp; provisional name */
TMSCRIPT sys_cfg_continue_text_jp[2] = {
    { 1, 0, sys_cfg_page_scr_jp_33 }, { 1, 0, sys_cfg_page_scr_jp_34 },
};

/* 02000860 */
/* one script for each monitor flip setting, picked through sys_cfg_monitor_scr_jp; provisional name */
TMSCRIPT sys_cfg_monitor_text_jp[2] = {
    { 1, 0, sys_cfg_page_scr_jp_35 }, { 1, 0, sys_cfg_page_scr_jp_36 },
};

/* 02000870 */
/* one script for each demo sound setting, picked through sys_cfg_demo_scr_jp; provisional name */
TMSCRIPT sys_cfg_demo_text_jp[2] = {
    { 1, 0, sys_cfg_page_scr_jp_37 }, { 1, 0, sys_cfg_page_scr_jp_38 },
};

/* 02000880 */
/* one script for each sound mode setting, picked through sys_cfg_sound_scr_jp; provisional name */
TMSCRIPT sys_cfg_sound_text_jp[42] = {
    { 1, 0, sys_cfg_page_scr_jp_39 }, { 1, 0, sys_cfg_page_scr_jp_40 },
    { 1, 0, sys_cfg_page_scr_jp_41 }, { 1, 0, sys_cfg_page_scr_jp_42 },
    { 1, 0, sys_cfg_page_scr_jp_43 }, { 1, 0, sys_cfg_page_scr_jp_44 },
    { 1, 0, sys_cfg_page_scr_jp_45 }, { 1, 0, sys_cfg_page_scr_jp_46 },
    { 1, 0, sys_cfg_page_scr_jp_47 }, { 1, 0, sys_cfg_page_scr_jp_48 },
    { 1, 0, sys_cfg_page_scr_jp_49 }, { 1, 0, sys_cfg_page_scr_jp_50 },
    { 1, 0, sys_cfg_page_scr_jp_51 }, { 1, 0, sys_cfg_page_scr_jp_52 },
    { 1, 0, sys_cfg_page_scr_jp_53 }, { 1, 0, sys_cfg_page_scr_jp_54 },
    { 1, 0, sys_cfg_page_scr_jp_55 }, { 1, 0, sys_cfg_page_scr_jp_56 },
    { 1, 0, sys_cfg_page_scr_jp_57 }, { 1, 0, sys_cfg_page_scr_jp_58 },
    { 1, 0, sys_cfg_page_scr_jp_59 }, { 1, 0, sys_cfg_page_scr_jp_60 },
    { 1, 0, sys_cfg_page_scr_jp_61 }, { 1, 0, sys_cfg_page_scr_jp_62 },
    { 1, 0, sys_cfg_page_scr_jp_63 }, { 1, 0, sys_cfg_page_scr_jp_64 },
    { 1, 0, sys_cfg_page_scr_jp_65 }, { 1, 0, sys_cfg_page_scr_jp_66 },
    { 1, 0, sys_cfg_page_scr_jp_67 }, { 1, 0, sys_cfg_page_scr_jp_68 },
    { 1, 0, sys_cfg_page_scr_jp_69 }, { 1, 0, sys_cfg_page_scr_jp_70 },
    { 1, 0, sys_cfg_page_scr_jp_71 }, { 1, 0, sys_cfg_page_scr_jp_72 },
    { 1, 0, sys_cfg_page_scr_jp_73 }, { 1, 0, sys_cfg_page_scr_jp_74 },
    { 1, 0, sys_cfg_page_scr_jp_75 }, { 1, 0, sys_cfg_page_scr_jp_76 },
    { 1, 0, sys_cfg_page_scr_jp_77 }, { 1, 0, sys_cfg_page_scr_jp_78 },
    { 1, 0, sys_cfg_page_scr_jp_79 }, { 1, 0, sys_cfg_page_scr_jp_80 },
};

/* 020009D0 */
TMSCRIPT sys_cfg_exit_guide_jp[1] = {
    { 1, 0, sys_cfg_exit_guide_jp_0 },
};

/* 020009D8 */
TMSCRIPT sys_cfg_item_guide_jp[1] = {
    { 1, 0, sys_cfg_item_guide_jp_0 },
};

/* 020009E0 */
TMSCRIPT cfg_top_guide_jp[1] = {
    { 1, 0, cfg_top_guide_jp_0 },
};

/* 020009E8 */
TMSCRIPT cfg_top_reset_guide_jp[1] = {
    { 1, 0, cfg_top_reset_guide_jp_0 },
};

/* 020009F0 */
TMSCRIPT* sys_cfg_coin_scr_jp[19] = {
    &sys_cfg_coin_text_jp[0], &sys_cfg_coin_text_jp[1],
    &sys_cfg_coin_text_jp[2], &sys_cfg_coin_text_jp[3],
    &sys_cfg_coin_text_jp[4], &sys_cfg_coin_text_jp[5],
    &sys_cfg_coin_text_jp[6], &sys_cfg_coin_text_jp[7],
    &sys_cfg_coin_text_jp[8], &sys_cfg_coin_text_jp[9],
    &sys_cfg_coin_text_jp[10], &sys_cfg_coin_text_jp[11],
    &sys_cfg_coin_text_jp[12], &sys_cfg_coin_text_jp[13],
    &sys_cfg_coin_text_jp[14], &sys_cfg_coin_text_jp[15],
    &sys_cfg_coin_text_jp[16], &sys_cfg_coin_text_jp[17],
    &sys_cfg_coin_text_jp[18],
};

/* 02000A3C */
TMSCRIPT* sys_cfg_chute_scr_jp[12] = {
    &sys_cfg_chute_text_jp[0], &sys_cfg_chute_text_jp[1],
    &sys_cfg_chute_text_jp[2], &sys_cfg_chute_text_jp[3],
    &sys_cfg_chute_text_jp[4], &sys_cfg_chute_text_jp[5],
    &sys_cfg_chute_text_jp[6], &sys_cfg_chute_text_jp[7],
    &sys_cfg_chute_text_jp[8], &sys_cfg_chute_text_jp[9],
    &sys_cfg_chute_text_jp[10], &sys_cfg_chute_text_jp[11],
};

/* 02000A6C */
TMSCRIPT* sys_cfg_continue_scr_jp[2] = {
    &sys_cfg_continue_text_jp[0], &sys_cfg_continue_text_jp[1],
};

/* 02000A74 */
TMSCRIPT* sys_cfg_monitor_scr_jp[2] = {
    &sys_cfg_monitor_text_jp[0], &sys_cfg_monitor_text_jp[1],
};

/* 02000A7C */
TMSCRIPT* sys_cfg_demo_scr_jp[2] = {
    &sys_cfg_demo_text_jp[0], &sys_cfg_demo_text_jp[1],
};

/* 02000A84 */
TMSCRIPT* sys_cfg_sound_scr_jp[42] = {
    &sys_cfg_sound_text_jp[0], &sys_cfg_sound_text_jp[1],
    &sys_cfg_sound_text_jp[2], &sys_cfg_sound_text_jp[3],
    &sys_cfg_sound_text_jp[4], &sys_cfg_sound_text_jp[5],
    &sys_cfg_sound_text_jp[6], &sys_cfg_sound_text_jp[7],
    &sys_cfg_sound_text_jp[8], &sys_cfg_sound_text_jp[9],
    &sys_cfg_sound_text_jp[10], &sys_cfg_sound_text_jp[11],
    &sys_cfg_sound_text_jp[12], &sys_cfg_sound_text_jp[13],
    &sys_cfg_sound_text_jp[14], &sys_cfg_sound_text_jp[15],
    &sys_cfg_sound_text_jp[16], &sys_cfg_sound_text_jp[17],
    &sys_cfg_sound_text_jp[18], &sys_cfg_sound_text_jp[19],
    &sys_cfg_sound_text_jp[20], &sys_cfg_sound_text_jp[21],
    &sys_cfg_sound_text_jp[22], &sys_cfg_sound_text_jp[23],
    &sys_cfg_sound_text_jp[24], &sys_cfg_sound_text_jp[25],
    &sys_cfg_sound_text_jp[26], &sys_cfg_sound_text_jp[27],
    &sys_cfg_sound_text_jp[28], &sys_cfg_sound_text_jp[29],
    &sys_cfg_sound_text_jp[30], &sys_cfg_sound_text_jp[31],
    &sys_cfg_sound_text_jp[32], &sys_cfg_sound_text_jp[33],
    &sys_cfg_sound_text_jp[34], &sys_cfg_sound_text_jp[35],
    &sys_cfg_sound_text_jp[36], &sys_cfg_sound_text_jp[37],
    &sys_cfg_sound_text_jp[38], &sys_cfg_sound_text_jp[39],
    &sys_cfg_sound_text_jp[40], &sys_cfg_sound_text_jp[41],
};

/* 02000B2C */
/* A one-line script for a sound settings page: a heading and four values in column 18. It is a
   record, not an entry of sys_cfg_sound_scr_jp, and nothing in the program refers to it by name or
   address. */
TMSCRIPT sys_cfg_sound_page_scr_jp[1] = {
    { 1, 0, sys_cfg_sound_page_scr_jp_0 },
};
