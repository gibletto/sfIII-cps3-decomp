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
extern TMSCRIPT sys_cfg_unref_scr_jp[];
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
extern const u16 sys_cfg_sound_scr_jp_0[];
extern const u16 test_menu_scr_jp_0[];

/* 0200060C */
TM_STRING test_menu_str[13] = {
    { 0xF, 1, 2, test_menu_str_0 },
    { 0x10, 3, 2, test_menu_str_1 },
    { 0x10, 5, 2, test_menu_str_2 },
    { 0x10, 7, 2, test_menu_str_3 },
    { 0x10, 9, 2, test_menu_str_4 },
    { 0x10, 0xB, 2, test_menu_str_5 },
    { 0x10, 0xD, 2, test_menu_str_6 },
    { 0x10, 0xF, 2, test_menu_str_7 },
    { 0x10, 0x11, 2, test_menu_str_8 },
    { 0x10, 0x13, 2, test_menu_str_9 },
    { 0x10, 0x15, 2, test_menu_str_10 },
    { 0xD, 0x1A, 2, test_menu_str_11 },
    { 0xD, 0x1B, 2, test_menu_str_12 },
};

/* 020006A8 */
TM_STRING test_menu_str_asia[12] = {
    { 0xF, 1, 2, test_menu_str_0 },
    { 0x10, 3, 2, test_menu_str_1 },
    { 0x10, 5, 2, test_menu_str_2 },
    { 0x10, 7, 2, test_menu_str_3 },
    { 0x10, 9, 2, test_menu_str_4 },
    { 0x10, 0xB, 2, test_menu_str_5 },
    { 0x10, 0xD, 2, test_menu_str_6 },
    { 0x10, 0xF, 2, test_menu_str_7 },
    { 0x10, 0x11, 2, test_menu_str_8 },
    { 0x10, 0x13, 2, test_menu_str_asia_9 },
    { 0xD, 0x1A, 2, test_menu_str_11 },
    { 0xD, 0x1B, 2, test_menu_str_12 },
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
TMSCRIPT sys_cfg_page_scr_jp[81] = {
    { 1, 0, sys_cfg_page_scr_jp_0 }, { 1, 0, sys_cfg_page_scr_jp_1 },
    { 1, 0, sys_cfg_page_scr_jp_2 }, { 1, 0, sys_cfg_page_scr_jp_3 },
    { 1, 0, sys_cfg_page_scr_jp_4 }, { 1, 0, sys_cfg_page_scr_jp_5 },
    { 1, 0, sys_cfg_page_scr_jp_6 }, { 1, 0, sys_cfg_page_scr_jp_7 },
    { 1, 0, sys_cfg_page_scr_jp_8 }, { 1, 0, sys_cfg_page_scr_jp_9 },
    { 1, 0, sys_cfg_page_scr_jp_10 }, { 1, 0, sys_cfg_page_scr_jp_11 },
    { 1, 0, sys_cfg_page_scr_jp_12 }, { 1, 0, sys_cfg_page_scr_jp_13 },
    { 1, 0, sys_cfg_page_scr_jp_14 }, { 1, 0, sys_cfg_page_scr_jp_15 },
    { 1, 0, sys_cfg_page_scr_jp_16 }, { 1, 0, sys_cfg_page_scr_jp_17 },
    { 1, 0, sys_cfg_page_scr_jp_18 }, { 1, 0, sys_cfg_page_scr_jp_19 },
    { 1, 0, sys_cfg_page_scr_jp_20 }, { 1, 0, sys_cfg_page_scr_jp_21 },
    { 1, 0, sys_cfg_page_scr_jp_22 }, { 1, 0, sys_cfg_page_scr_jp_23 },
    { 1, 0, sys_cfg_page_scr_jp_24 }, { 1, 0, sys_cfg_page_scr_jp_25 },
    { 1, 0, sys_cfg_page_scr_jp_26 }, { 1, 0, sys_cfg_page_scr_jp_27 },
    { 1, 0, sys_cfg_page_scr_jp_28 }, { 1, 0, sys_cfg_page_scr_jp_29 },
    { 1, 0, sys_cfg_page_scr_jp_30 }, { 1, 0, sys_cfg_page_scr_jp_31 },
    { 1, 0, sys_cfg_page_scr_jp_32 }, { 1, 0, sys_cfg_page_scr_jp_33 },
    { 1, 0, sys_cfg_page_scr_jp_34 }, { 1, 0, sys_cfg_page_scr_jp_35 },
    { 1, 0, sys_cfg_page_scr_jp_36 }, { 1, 0, sys_cfg_page_scr_jp_37 },
    { 1, 0, sys_cfg_page_scr_jp_38 }, { 1, 0, sys_cfg_page_scr_jp_39 },
    { 1, 0, sys_cfg_page_scr_jp_40 }, { 1, 0, sys_cfg_page_scr_jp_41 },
    { 1, 0, sys_cfg_page_scr_jp_42 }, { 1, 0, sys_cfg_page_scr_jp_43 },
    { 1, 0, sys_cfg_page_scr_jp_44 }, { 1, 0, sys_cfg_page_scr_jp_45 },
    { 1, 0, sys_cfg_page_scr_jp_46 }, { 1, 0, sys_cfg_page_scr_jp_47 },
    { 1, 0, sys_cfg_page_scr_jp_48 }, { 1, 0, sys_cfg_page_scr_jp_49 },
    { 1, 0, sys_cfg_page_scr_jp_50 }, { 1, 0, sys_cfg_page_scr_jp_51 },
    { 1, 0, sys_cfg_page_scr_jp_52 }, { 1, 0, sys_cfg_page_scr_jp_53 },
    { 1, 0, sys_cfg_page_scr_jp_54 }, { 1, 0, sys_cfg_page_scr_jp_55 },
    { 1, 0, sys_cfg_page_scr_jp_56 }, { 1, 0, sys_cfg_page_scr_jp_57 },
    { 1, 0, sys_cfg_page_scr_jp_58 }, { 1, 0, sys_cfg_page_scr_jp_59 },
    { 1, 0, sys_cfg_page_scr_jp_60 }, { 1, 0, sys_cfg_page_scr_jp_61 },
    { 1, 0, sys_cfg_page_scr_jp_62 }, { 1, 0, sys_cfg_page_scr_jp_63 },
    { 1, 0, sys_cfg_page_scr_jp_64 }, { 1, 0, sys_cfg_page_scr_jp_65 },
    { 1, 0, sys_cfg_page_scr_jp_66 }, { 1, 0, sys_cfg_page_scr_jp_67 },
    { 1, 0, sys_cfg_page_scr_jp_68 }, { 1, 0, sys_cfg_page_scr_jp_69 },
    { 1, 0, sys_cfg_page_scr_jp_70 }, { 1, 0, sys_cfg_page_scr_jp_71 },
    { 1, 0, sys_cfg_page_scr_jp_72 }, { 1, 0, sys_cfg_page_scr_jp_73 },
    { 1, 0, sys_cfg_page_scr_jp_74 }, { 1, 0, sys_cfg_page_scr_jp_75 },
    { 1, 0, sys_cfg_page_scr_jp_76 }, { 1, 0, sys_cfg_page_scr_jp_77 },
    { 1, 0, sys_cfg_page_scr_jp_78 }, { 1, 0, sys_cfg_page_scr_jp_79 },
    { 1, 0, sys_cfg_page_scr_jp_80 },
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
    &sys_cfg_page_scr_jp[2], &sys_cfg_page_scr_jp[3],
    &sys_cfg_page_scr_jp[4], &sys_cfg_page_scr_jp[5],
    &sys_cfg_page_scr_jp[6], &sys_cfg_page_scr_jp[7],
    &sys_cfg_page_scr_jp[8], &sys_cfg_page_scr_jp[9],
    &sys_cfg_page_scr_jp[10], &sys_cfg_page_scr_jp[11],
    &sys_cfg_page_scr_jp[12], &sys_cfg_page_scr_jp[13],
    &sys_cfg_page_scr_jp[14], &sys_cfg_page_scr_jp[15],
    &sys_cfg_page_scr_jp[16], &sys_cfg_page_scr_jp[17],
    &sys_cfg_page_scr_jp[18], &sys_cfg_page_scr_jp[19],
    &sys_cfg_page_scr_jp[20],
};

/* 02000A3C */
TMSCRIPT* sys_cfg_chute_scr_jp[12] = {
    &sys_cfg_page_scr_jp[21], &sys_cfg_page_scr_jp[22],
    &sys_cfg_page_scr_jp[23], &sys_cfg_page_scr_jp[24],
    &sys_cfg_page_scr_jp[25], &sys_cfg_page_scr_jp[26],
    &sys_cfg_page_scr_jp[27], &sys_cfg_page_scr_jp[28],
    &sys_cfg_page_scr_jp[29], &sys_cfg_page_scr_jp[30],
    &sys_cfg_page_scr_jp[31], &sys_cfg_page_scr_jp[32],
};

/* 02000A6C */
TMSCRIPT* sys_cfg_continue_scr_jp[2] = {
    &sys_cfg_page_scr_jp[33], &sys_cfg_page_scr_jp[34],
};

/* 02000A74 */
TMSCRIPT* sys_cfg_monitor_scr_jp[2] = {
    &sys_cfg_page_scr_jp[35], &sys_cfg_page_scr_jp[36],
};

/* 02000A7C */
TMSCRIPT* sys_cfg_demo_scr_jp[2] = {
    &sys_cfg_page_scr_jp[37], &sys_cfg_page_scr_jp[38],
};

/* 02000A84 */
TMSCRIPT* sys_cfg_sound_scr_jp[42] = {
    &sys_cfg_page_scr_jp[39], &sys_cfg_page_scr_jp[40],
    &sys_cfg_page_scr_jp[41], &sys_cfg_page_scr_jp[42],
    &sys_cfg_page_scr_jp[43], &sys_cfg_page_scr_jp[44],
    &sys_cfg_page_scr_jp[45], &sys_cfg_page_scr_jp[46],
    &sys_cfg_page_scr_jp[47], &sys_cfg_page_scr_jp[48],
    &sys_cfg_page_scr_jp[49], &sys_cfg_page_scr_jp[50],
    &sys_cfg_page_scr_jp[51], &sys_cfg_page_scr_jp[52],
    &sys_cfg_page_scr_jp[53], &sys_cfg_page_scr_jp[54],
    &sys_cfg_page_scr_jp[55], &sys_cfg_page_scr_jp[56],
    &sys_cfg_page_scr_jp[57], &sys_cfg_page_scr_jp[58],
    &sys_cfg_page_scr_jp[59], &sys_cfg_page_scr_jp[60],
    &sys_cfg_page_scr_jp[61], &sys_cfg_page_scr_jp[62],
    &sys_cfg_page_scr_jp[63], &sys_cfg_page_scr_jp[64],
    &sys_cfg_page_scr_jp[65], &sys_cfg_page_scr_jp[66],
    &sys_cfg_page_scr_jp[67], &sys_cfg_page_scr_jp[68],
    &sys_cfg_page_scr_jp[69], &sys_cfg_page_scr_jp[70],
    &sys_cfg_page_scr_jp[71], &sys_cfg_page_scr_jp[72],
    &sys_cfg_page_scr_jp[73], &sys_cfg_page_scr_jp[74],
    &sys_cfg_page_scr_jp[75], &sys_cfg_page_scr_jp[76],
    &sys_cfg_page_scr_jp[77], &sys_cfg_page_scr_jp[78],
    &sys_cfg_page_scr_jp[79], &sys_cfg_page_scr_jp[80],
};

/* 02000B2C */
/* a screen script after the sound page's; nothing in the program refers to it (provisional name) */
TMSCRIPT sys_cfg_unref_scr_jp[1] = {
    { 1, 0, sys_cfg_sound_scr_jp_0 },
};
