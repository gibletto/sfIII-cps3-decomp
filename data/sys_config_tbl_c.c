/*
 * SYS_CONFIG_TBL_C.C  test mode configuration menu screens
 *
 * The config_ and sysconfig_ tables place the lines of the configuration menu (x, y, attribute
 * and text): the top menu and its guides, the system configuration page with its exit, card
 * dispenser, voice type, language and win point lines, the modify and return guides and the
 * saving message; the str_ strings are their text. Read by SYS_CONFIG_2.C, the test mode
 * configuration menu.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const TM_STRING config_top_menu_scr[];
extern const TM_STRING config_top_guide_scr[];
extern const TM_STRING config_reset_guide_scr[];
extern const TM_STRING sysconfig_scr[];
extern const TM_STRING sysconfig_exit_scr[];
extern const TM_STRING sysconfig_dispenser_scr[];
extern const TM_STRING sysconfig_winpoint_scr[];
extern const TM_STRING sysconfig_modify_guide[];
extern const TM_STRING sysconfig_return_guide[];
extern const TM_STRING config_saving_scr[];
extern const s8 str_config_menu_title[];
extern const s8 str_config_1_system[];
extern const s8 str_config_2_game[];
extern const s8 str_config_3_default[];
extern const s8 str_config_4_save_exit[];
extern const s8 str_guide_select_up_down[];
extern const s8 str_guide_start_shot1[];
extern const s8 str_guide_reset_shot1_shot2[];
extern const s8 str_sysconfig_title[];
extern const s8 str_sys_1_coin[];
extern const s8 str_sys_2_chute_mode[];
extern const s8 str_sys_3_continue[];
extern const s8 str_sys_4_monitor[];
extern const s8 str_sys_5_demo_sound[];
extern const s8 str_sys_6_sound_mode[];
extern const s8 str_sys_7_exit[];
extern const s8 str_sys_7_language[];
extern const s8 str_sys_8_exit[];
extern const s8 str_sys_7_c_dispenser[];
extern const s8 str_sys_8_win_point[];
extern const s8 str_sys_9_exit[];
extern const s8 str_sys_7_voice_type[];
extern const s8 str_sys_8_win_point_com[];
extern const s8 str_sys_9_win_point_human[];
extern const s8 str_sys_10_exit[];
extern const s8 str_SELECT_OPTION_1P_UP_or_DOWN[];
extern const s8 str_1P_SHOT1_2[];
extern const s8 str_1P_SHOT1_or_SHOT2_2[];
extern const char str_IN_EEPROM[];
extern const char str_saving_configuration[];
extern const s8 gcfg_help_modify_en[];
extern const s8 gcfg_help_return_en[];

const TM_STRING config_top_menu_scr[5] = {
    { 4, 2, 2, str_config_menu_title },
    { 18, 6, 2, str_config_1_system },
    { 18, 8, 2, str_config_2_game },
    { 18, 10, 2, str_config_3_default },
    { 18, 12, 2, str_config_4_save_exit },
};

const TM_STRING config_top_guide_scr[2] = {
    { 13, 26, 2, str_guide_select_up_down },
    { 13, 27, 2, str_guide_start_shot1 },
};

const TM_STRING config_reset_guide_scr[2] = {
    { 13, 26, 2, str_guide_select_up_down },
    { 13, 27, 2, str_guide_reset_shot1_shot2 },
};

const TM_STRING sysconfig_scr[7] = {
    { 1, 2, 2, str_sysconfig_title },
    { 3, 5, 2, str_sys_1_coin },
    { 3, 7, 2, str_sys_2_chute_mode },
    { 3, 9, 2, str_sys_3_continue },
    { 3, 11, 2, str_sys_4_monitor },
    { 3, 13, 2, str_sys_5_demo_sound },
    { 3, 15, 2, str_sys_6_sound_mode },
};

const TM_STRING sysconfig_exit_scr[3] = {
    { 3, 17, 2, str_sys_7_exit },
    { 3, 17, 2, str_sys_7_language },
    { 3, 19, 2, str_sys_8_exit },
};

const TM_STRING sysconfig_dispenser_scr[5] = {
    { 3, 17, 2, str_sys_7_c_dispenser },
    { 3, 19, 2, str_sys_8_win_point },
    { 3, 21, 2, str_sys_9_exit },
    { 3, 17, 2, str_sys_7_voice_type },
    { 3, 19, 2, str_sys_8_exit },
};

const TM_STRING sysconfig_winpoint_scr[4] = {
    { 3, 17, 2, str_sys_7_c_dispenser },
    { 3, 19, 2, str_sys_8_win_point_com },
    { 3, 21, 2, str_sys_9_win_point_human },
    { 2, 23, 2, str_sys_10_exit },
};

const TM_STRING sysconfig_modify_guide[3] = {
    { 7, 25, 2, str_SELECT_OPTION_1P_UP_or_DOWN },
    { 7, 26, 2, gcfg_help_modify_en },
    { 7, 27, 2, str_1P_SHOT1_or_SHOT2_2 },
};

const TM_STRING sysconfig_return_guide[3] = {
    { 7, 25, 2, str_SELECT_OPTION_1P_UP_or_DOWN },
    { 7, 26, 2, gcfg_help_return_en },
    { 7, 27, 2, str_1P_SHOT1_2 },
};

const TM_STRING config_saving_scr[2] = {
    { 5, 12, 0xE, (const s8 *)str_saving_configuration },
    { 5, 14, 0xE, (const s8 *)str_IN_EEPROM },
};

const s8 str_config_menu_title[40] = "7. C O N F I G U R A T I O N   M E N U\n";

const s8 str_config_1_system[12] = "1. SYSTEM\n";

const s8 str_config_2_game[12] = "2. GAME\n\0\x03\0\x04";

const s8 str_config_3_default[12] = "3. DEFAULT\n";

const s8 str_config_4_save_exit[16] = "4. SAVE & EXIT\0\x12";

const s8 str_guide_select_up_down[28] = "SELECT = 1P UP or DOWN   \n\0\x20";

const s8 str_guide_start_shot1[28] = "START  = 1P SHOT1        \0\0\x2E";

const s8 str_guide_reset_shot1_shot2[28] = "RESET  = 1P SHOT1 & SHOT2\0\0\x06";

const s8 str_sysconfig_title[48] = "7-1. S Y S T E M   C O N F I G U R A T I O N\n\0\0\x1E";

const s8 str_sys_1_coin[12] = "1. COIN\n\0\x23\0\x24";

const s8 str_sys_2_chute_mode[16] = "2. CHUTE MODE\n\0\x2C";

const s8 str_sys_3_continue[16] = "3. CONTINUE\n\0\x33\0\x34";

const s8 str_sys_4_monitor[12] = "4. MONITOR\n";

const s8 str_sys_5_demo_sound[16] = "5. DEMO SOUND\n";

const s8 str_sys_6_sound_mode[16] = "6. SOUND MODE";

const s8 str_sys_7_exit[8] = "7. EXIT";

const s8 str_sys_7_language[16] = "7. LANGUAGE\n";

const s8 str_sys_8_exit[8] = "8. EXIT";

const s8 str_sys_7_c_dispenser[16] = "7. C.DISPENSER\n";

const s8 str_sys_8_win_point[16] = "8. WIN POINT\n";

const s8 str_sys_9_exit[8] = "9. EXIT";

const s8 str_sys_7_voice_type[16] = "7. VOICE TYPE\n";

const s8 str_sys_8_win_point_com[20] = "8. WIN POINT COM\n";

const s8 str_sys_9_win_point_human[20] = "9. WIN POINT HUMAN\n";

const s8 str_sys_10_exit[12] = "10. EXIT";

const s8 str_SELECT_OPTION_1P_UP_or_DOWN[36] = "SELECT OPTION  = 1P UP or DOWN    \n";
