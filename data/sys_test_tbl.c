/*
 * SYS_TEST_TBL.C  tables read by coin_sw.c, colortest.c, end_sub_2.c, game_config_en.c, game_config_jp.c, iotest_out.c, mode_init.c, soundtest.c, sys_test.c, sys_test_2.c, sys_test_2a.c, sys_test_2b.c, sys_test_3.c, sys_test_4.c and test_mode.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u16 scroll_enable_bit_tbl[][2];
extern const TM_STRING iotest_input_scr[];
extern const s16 iotest_1p_sw_x[];
extern const s16 iotest_1p_sw_y[];
extern const s16 iotest_2p_sw_x[];
extern const s16 iotest_2p_sw_y[];
extern const s16 iotest_sys_sw_x[];
extern const s16 iotest_sys_sw_y[];
extern const s16 iotest_1p_diag_x[];
extern const s16 iotest_1p_diag_y[];
extern const s16 iotest_2p_diag_x[];
extern const s16 iotest_2p_diag_y[];
extern const u16 iotest_sw_bit_tbl[];
extern const u16 iotest_diag_bit_tbl[];
extern const u32 iotest_sys_bit_tbl[];
extern const s8 iotest_on_str[];
extern const s8 iotest_off_str[];
extern const char iotest_input_title_str[];
extern const char iotest_service_label_str[];
extern const char str_TEST[];
extern const char iotest_1p_2p_header_str[];
extern const char str_COIN[];
extern const char str_START[];
extern const char str_LEVER[];
extern const char str_SHOT[];
extern const char iotest_input_exit_str[];
extern const TM_STRING iotest_output_scr[];
extern const TM_STRING iotest_dispenser_str[];
extern const char iotest_output_title_str[];
extern const char iotest_coin_lock_1p_str[];
extern const char iotest_coin_lock_2p_str[];
extern const char iotest_elec_counter_str[];
extern const char iotest_output_exit_str[];
extern const char iotest_card_dispenser_str[];
extern const TM_STRING soundtest_menu_scr[];
extern const TM_STRING soundtest_monitor_scr[];
extern const s8 snd_stat_stop_str[];
extern const s8 snd_stat_play_str[];
extern const s8 snd_stat_pause_str[];
extern const s8 snd_stat_blank_str[];
extern const s8 snd_stat_fadein_str[];
extern const s8 snd_stat_fadeout_str[];
extern const s8 pan_bar_str[];
extern const s8 delta_same_str[];
extern const s8 delta_up_str[];
extern const s8 delta_down_str[];
extern const char soundtest_title_str[];
extern const char soundtest_code_label_str[];
extern const char soundtest_help_up_str[];
extern const char soundtest_help_down_str[];
extern const char soundtest_help_right_str[];
extern const char soundtest_help_left_str[];
extern const char soundtest_help_request_str[];
extern const char soundtest_help_stop_str[];
extern const char soundtest_exit_str[];
extern const char soundtest_version_label_str[];
extern const char soundtest_status_label_str[];
extern const char soundtest_channel_header_str[];
extern const char soundtest_ch0_str[];
extern const char soundtest_ch1_str[];
extern const char soundtest_ch2_str[];
extern const char soundtest_ch3_str[];
extern const char soundtest_ch4_str[];
extern const char soundtest_ch5_str[];
extern const char soundtest_ch6_str[];
extern const char soundtest_ch7_str[];
extern const char soundtest_ch8_str[];
extern const char soundtest_ch9_str[];
extern const char soundtest_ch10_str[];
extern const char soundtest_ch11_str[];
extern const char soundtest_ch12_str[];
extern const char soundtest_ch13_str[];
extern const char soundtest_ch14_str[];
extern const char soundtest_ch15_str[];
extern const TM_STRING colortest_scr[];
extern const u16 colortest_palette[];
extern const char colortest_title_str[];
extern const char colortest_hex_header_str[];
extern const char str_RED[];
extern const char str_GREEN[];
extern const char str_BLUE[];
extern const char str_WHITE[];
extern const char colortest_exit_str[];
extern const TM_STRING crosshatch_scr[];
extern const char crosshatch_title_str[];
extern const char crosshatch_exit_str[];
extern const TM_STRING gamedata_scr[];
extern const TM_STRING gamedata_freeplay_str[];
extern const TM_STRING gamedata_card_str[];
extern const char gamedata_title_str[];
extern const char gamedata_coin_counter_str[];
extern const char gamedata_service_counter_str[];
extern const char gamedata_exit_str[];
extern const char gamedata_freeplay_counter_str[];
extern const char gamedata_card_counter_str[];
extern const TM_STRING memtest_menu_scr[];
extern const TM_STRING memtest_ram_scr[];
extern const TM_STRING memtest_simm_scr[];
extern const u32 simm_sum_offset_tbl[];
extern const s8 cdb_test_unit_ready[];
extern const s8 cdb_read_capacity[];
extern const s8 cdb_inquiry[];
extern const s8 cdb_request_sense[];
extern const s8 cdb_read_toc[];
extern const s8 memtest_checking_str[];
extern const s8 memtest_ng_str[];
extern const s8 memtest_ok_str[];
extern const s8 memtest_skip_str[];
extern const char memtest_menu_title_str[];
extern const char memtest_menu_memory_str[];
extern const char memtest_menu_simm_str[];
extern const char memtest_menu_exit_str[];
extern const char memtest_select_help_str[];
extern const char memtest_start_help_str[];
extern const char memtest_ram_title_str[];
extern const char memtest_work_ram_str[];
extern const char memtest_sprite_ram_str[];
extern const char memtest_color_ram_str[];
extern const char memtest_character_ram_str[];
extern const char memtest_ss_ram_str[];
extern const char memtest_eeprom_str[];
extern const char str_FRAM[];
extern const char memtest_cdrom_str[];
extern const char memtest_flash_simm1_str[];
extern const char memtest_simm2_str[];
extern const char memtest_simm3_str[];
extern const char memtest_simm4_str[];
extern const char memtest_simm5_str[];
extern const char memtest_simm6_str[];
extern const char memtest_simm7_str[];
extern const char memtest_simm_title_and_names[];
extern const char str_ONBOARD[];
extern const char str_SIMM1[];
extern const char str_SIMM2[];
extern const char str_SIMM3[];
extern const char str_SIMM4[];
extern const char str_SIMM5[];
extern const char str_SIMM6[];
extern const char str_SIMM7[];
extern const TM_STRING rewrite_menu_scr[];
extern const TM_STRING rewrite_guide_scr[];
extern const TM_STRING rewrite_exit_guide_scr[];
extern const TM_STRING rewrite_not_ready_str[];
extern const char rewrite_title_str[];
extern const char rewrite_all_str[];
extern const char rewrite_character_str[];
extern const char str_EXIT[];
extern const char rewrite_note1_str[];
extern const char rewrite_note2_str[];
extern const char rewrite_note3_str[];
extern const char rewrite_select_help_str[];
extern const char rewrite_start_help_str[];
extern const char rewrite_exit_help_str[];
extern const char str_blank_16[];
extern const char rewrite_cd_not_ready_str[];
extern const u16 sys_palette[];
extern const u8 coin_counter_bit_tbl[];

const u16 scroll_enable_bit_tbl[3][2] = {
    { 1, 0x8000 }, { 0x10, 0x4000 }, { 0x100, 0x2000 },
};

const TM_STRING iotest_input_scr[9] = {
    { 0xC, 2, 2, (const s8 *)iotest_input_title_str },
    { 6, 4, 2, (const s8 *)iotest_service_label_str },
    { 6, 5, 2, (const s8 *)str_TEST },
    { 0x10, 7, 2, (const s8 *)iotest_1p_2p_header_str },
    { 6, 8, 2, (const s8 *)str_COIN },
    { 6, 9, 2, (const s8 *)str_START },
    { 6, 0xB, 2, (const s8 *)str_LEVER },
    { 6, 0xF, 2, (const s8 *)str_SHOT },
    { 0xD, 0x1B, 2, (const s8 *)iotest_input_exit_str },
};

const s16 iotest_1p_sw_x[1] = {
    16,
};

const s16 iotest_1p_sw_y[23] = {
    11, 16, 13, 15, 12, 17, 12, 15, 15, 16, 15, 17, 15, 15, 16, 16,
    16, 17, 16, 17, 8, 17, 9,
};

const s16 iotest_2p_sw_x[1] = {
    36,
};

const s16 iotest_2p_sw_y[23] = {
    11, 36, 13, 35, 12, 37, 12, 35, 15, 36, 15, 37, 15, 35, 16, 36,
    16, 37, 16, 37, 8, 37, 9,
};

const s16 iotest_sys_sw_x[1] = {
    17,
};

const s16 iotest_sys_sw_y[5] = {
    4, 17, 5, 17, 5,
};

const s16 iotest_1p_diag_x[1] = {
    17,
};

const s16 iotest_1p_diag_y[7] = {
    11, 15, 11, 17, 13, 15, 13,
};

const s16 iotest_2p_diag_x[1] = {
    37,
};

const s16 iotest_2p_diag_y[7] = {
    11, 35, 11, 37, 13, 35, 13,
};

const u16 iotest_sw_bit_tbl[12] = {
    1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80,
    0x100, 0x200, 0x800, 0x1000,
};

const u16 iotest_diag_bit_tbl[4] = {
    9, 5, 0xA, 6,
};

const u32 iotest_sys_bit_tbl[3] = {
    1, 4, 2,
};

const s8 iotest_on_str[4] = "1\0\0\x0D";

const s8 iotest_off_str[4] = "0\0\0\x0B";

const char iotest_input_title_str[28] = "1 . I N P U T   T E S T\n";

const char iotest_service_label_str[12] = "SERVICE\n";

const char str_TEST[8] = "TEST\n";

const char iotest_1p_2p_header_str[24] = "1P                  2P\n";

const char str_COIN[8] = "COIN\n\0\0\x12";

const char str_START[8] = "START\n\0\x12";

const char str_LEVER[8] = "LEVER\n\0\x12";

const char str_SHOT[8] = "SHOT\n\0\0\x10";

const char iotest_input_exit_str[24] = "EXIT = 1P START & SHOT1";

const TM_STRING iotest_output_scr[5] = {
    { 0xB, 2, 2, (const s8 *)iotest_output_title_str },
    { 0xA, 5, 2, (const s8 *)iotest_coin_lock_1p_str },
    { 0xA, 7, 2, (const s8 *)iotest_coin_lock_2p_str },
    { 0xA, 0xA, 2, (const s8 *)iotest_elec_counter_str },
    { 0xC, 0x1B, 2, (const s8 *)iotest_output_exit_str },
};

const TM_STRING iotest_dispenser_str[1] = {
    { 0xA, 0xC, 2, (const s8 *)iotest_card_dispenser_str },
};

const char iotest_output_title_str[28] = "2 . O U T P U T   T E S T\n\0\x0B";

const char iotest_coin_lock_1p_str[32] = "COIN LOCK 1P      (1P SHOT1)\n";

const char iotest_coin_lock_2p_str[32] = "COIN LOCK 2P      (2P SHOT1)\n\0\0\x16";

const char iotest_elec_counter_str[32] = "ELECTRIC COUNTER  (1P SHOT2)\n\0\0\x14";

const char iotest_output_exit_str[24] = "EXIT = 1P START & SHOT1";

const char iotest_card_dispenser_str[32] = "CARD DISPENSER    (2P SHOT2)";

const TM_STRING soundtest_menu_scr[9] = {
    { 4, 2, 2, (const s8 *)soundtest_title_str },
    { 0xE, 7, 2, (const s8 *)soundtest_code_label_str },
    { 0xE, 0xB, 2, (const s8 *)soundtest_help_up_str },
    { 0xE, 0xC, 2, (const s8 *)soundtest_help_down_str },
    { 0xE, 0xD, 2, (const s8 *)soundtest_help_right_str },
    { 0xE, 0xE, 2, (const s8 *)soundtest_help_left_str },
    { 0xE, 0xF, 2, (const s8 *)soundtest_help_request_str },
    { 0xE, 0x10, 2, (const s8 *)soundtest_help_stop_str },
    { 0xC, 0x1B, 2, (const s8 *)soundtest_exit_str },
};

const TM_STRING soundtest_monitor_scr[21] = {
    { 4, 0, 2, (const s8 *)soundtest_title_str },
    { 1, 3, 2, (const s8 *)soundtest_version_label_str },
    { 2, 5, 2, (const s8 *)soundtest_status_label_str },
    { 1, 8, 2, (const s8 *)soundtest_channel_header_str },
    { 1, 9, 2, (const s8 *)soundtest_ch0_str },
    { 1, 0xA, 2, (const s8 *)soundtest_ch1_str },
    { 1, 0xB, 2, (const s8 *)soundtest_ch2_str },
    { 1, 0xC, 2, (const s8 *)soundtest_ch3_str },
    { 1, 0xD, 2, (const s8 *)soundtest_ch4_str },
    { 1, 0xE, 2, (const s8 *)soundtest_ch5_str },
    { 1, 0xF, 2, (const s8 *)soundtest_ch6_str },
    { 1, 0x10, 2, (const s8 *)soundtest_ch7_str },
    { 1, 0x11, 2, (const s8 *)soundtest_ch8_str },
    { 1, 0x12, 2, (const s8 *)soundtest_ch9_str },
    { 1, 0x13, 2, (const s8 *)soundtest_ch10_str },
    { 1, 0x14, 2, (const s8 *)soundtest_ch11_str },
    { 1, 0x15, 2, (const s8 *)soundtest_ch12_str },
    { 1, 0x16, 2, (const s8 *)soundtest_ch13_str },
    { 1, 0x17, 2, (const s8 *)soundtest_ch14_str },
    { 1, 0x18, 2, (const s8 *)soundtest_ch15_str },
    { 0xC, 0x1A, 2, (const s8 *)soundtest_exit_str },
};

const s8 snd_stat_stop_str[8] = "STOP \0\0\x1E";

const s8 snd_stat_play_str[8] = "PLAY \0\0\x1E";

const s8 snd_stat_pause_str[8] = "PAUSE\0\0\x1C";

const s8 snd_stat_blank_str[12] = "        \0\x17\0\x16";

const s8 snd_stat_fadein_str[12] = "FADE IN \0\x11\0\x10";

const s8 snd_stat_fadeout_str[12] = "FADE OUT\0\x0B\0\x0A";

const s8 pan_bar_str[20] = "~~~~~~~~~~~~~~~~\0\x01";

const s8 delta_same_str[4] = "-+-";

const s8 delta_up_str[4] = "+--";

const s8 delta_down_str[4] = "--+";

const char soundtest_title_str[44] = "3 . S O U N D   &   V O I C E   T E S T\n\0\x1E\0\x1D";

const char soundtest_code_label_str[16] = "SOUND CODE No\n\0\x15";

const char soundtest_help_up_str[20] = "CODE +01 = 1P UP\n\0\0\x0B";

const char soundtest_help_down_str[20] = "CODE -01 = 1P DOWN\n";

const char soundtest_help_right_str[24] = "CODE +10 = 1P RIGHT\n";

const char soundtest_help_left_str[20] = "CODE -10 = 1P LEFT\n";

const char soundtest_help_request_str[24] = "REQUEST  = 1P SHOT1\n\0\x19\0\x18";

const char soundtest_help_stop_str[24] = "STOP     = 1P SHOT2\n\0\x0D\0\x0C";

const char soundtest_exit_str[24] = "EXIT = 1P START & SHOT1";

const char soundtest_version_label_str[32] = "VERSION:            REQUEST:\n\0\0\x24";

const char soundtest_status_label_str[12] = "STATUS:\n\0\x24\0\x23";

const char soundtest_channel_header_str[48] = "CH NOTE             PITCH   L---R      VOLUME\n\0\x0B";

const char soundtest_ch0_str[4] = "0:\n";

const char soundtest_ch1_str[4] = "1:\n";

const char soundtest_ch2_str[4] = "2:\n";

const char soundtest_ch3_str[4] = "3:\n";

const char soundtest_ch4_str[4] = "4:\n";

const char soundtest_ch5_str[4] = "5:\n";

const char soundtest_ch6_str[4] = "6:\n";

const char soundtest_ch7_str[4] = "7:\n";

const char soundtest_ch8_str[4] = "8:\n";

const char soundtest_ch9_str[4] = "9:\n";

const char soundtest_ch10_str[4] = "A:\n";

const char soundtest_ch11_str[4] = "B:\n";

const char soundtest_ch12_str[4] = "C:\n";

const char soundtest_ch13_str[4] = "D:\n";

const char soundtest_ch14_str[4] = "E:\n";

const char soundtest_ch15_str[4] = "F:\n";

const TM_STRING colortest_scr[7] = {
    { 0xD, 2, 0x1E, (const s8 *)colortest_title_str },
    { 0xB, 4, 0x1E, (const s8 *)colortest_hex_header_str },
    { 6, 5, 0x1E, (const s8 *)str_RED },
    { 4, 0xA, 0x1E, (const s8 *)str_GREEN },
    { 5, 0xF, 0x1E, (const s8 *)str_BLUE },
    { 4, 0x14, 0x1E, (const s8 *)str_WHITE },
    { 0xC, 0x1B, 0x1E, (const s8 *)colortest_exit_str },
};

const u16 colortest_palette[134] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE0,
    0x100, 0x120, 0x140, 0x160, 0x180, 0x1A0, 0x1C0, 0x1E0,
    0x200, 0x220, 0x240, 0x260, 0x280, 0x2A0, 0x2C0, 0x2E0,
    0x300, 0x320, 0x340, 0x360, 0x380, 0x3A0, 0x3C0, 0x3E0,
    0, 0x400, 0x800, 0xC00, 0x1000, 0x1400, 0x1800, 0x1C00,
    0x2000, 0x2400, 0x2800, 0x2C00, 0x3000, 0x3400, 0x3800, 0x3C00,
    0x4000, 0x4400, 0x4800, 0x4C00, 0x5000, 0x5400, 0x5800, 0x5C00,
    0x6000, 0x6400, 0x6800, 0x6C00, 0x7000, 0x7400, 0x7800, 0x7C00,
    0, 0x421, 0x842, 0xC63, 0x1084, 0x14A5, 0x18C6, 0x1CE7,
    0x2108, 0x2529, 0x294A, 0x2D6B, 0x318C, 0x35AD, 0x39CE, 0x3DEF,
    0x4210, 0x4631, 0x4A52, 0x4E73, 0x5294, 0x56B5, 0x5AD6, 0x5EF7,
    0x6318, 0x6739, 0x6B5A, 0x6F7B, 0x739C, 0x77BD, 0x7BDE, 0x7FFF,
    0, 0x10, 0x200, 0x4000, 0x4210, 0,
};

const char colortest_title_str[24] = "4 . C O L O R   B A R\n";

const char colortest_hex_header_str[36] = "0 1 2 3 4 5 6 7 8 9 A B C D E F\n";

const char str_RED[8] = "RED\n";

const char str_GREEN[8] = "GREEN\n";

const char str_BLUE[8] = "BLUE\n";

const char str_WHITE[8] = "WHITE\n";

const char colortest_exit_str[24] = "EXIT = 1P START & SHOT1";

const TM_STRING crosshatch_scr[2] = {
    { 7, 2, 2, (const s8 *)crosshatch_title_str },
    { 0xC, 0x1B, 2, (const s8 *)crosshatch_exit_str },
};

const char crosshatch_title_str[36] = "5 . D O T   C R O S S   H A T C H\n";

const char crosshatch_exit_str[24] = "EXIT = 1P START & SHOT1";

const TM_STRING gamedata_scr[4] = {
    { 0xD, 2, 2, (const s8 *)gamedata_title_str },
    { 0xB, 7, 2, (const s8 *)gamedata_coin_counter_str },
    { 0xB, 9, 2, (const s8 *)gamedata_service_counter_str },
    { 0xC, 0x1B, 2, (const s8 *)gamedata_exit_str },
};

const TM_STRING gamedata_freeplay_str[1] = {
    { 0xB, 0xB, 2, (const s8 *)gamedata_freeplay_counter_str },
};

const TM_STRING gamedata_card_str[1] = {
    { 0xB, 0xB, 2, (const s8 *)gamedata_card_counter_str },
};

const char gamedata_title_str[24] = "6 . G A M E   D A T A\n\0\x03";

const char gamedata_coin_counter_str[20] = "COIN     COUNTER\n";

const char gamedata_service_counter_str[20] = "SERVICE  COUNTER\n\0\0\x06";

const char gamedata_exit_str[24] = "EXIT = 1P START & SHOT1";

const char gamedata_freeplay_counter_str[20] = "FREEPLAY COUNTER\0\x06\0\x06";

const char gamedata_card_counter_str[20] = "CARD     COUNTER\0\x06\0\x06";

const TM_STRING memtest_menu_scr[6] = {
    { 0xB, 1, 2, (const s8 *)memtest_menu_title_str },
    { 0xC, 9, 2, (const s8 *)memtest_menu_memory_str },
    { 0xC, 0xB, 2, (const s8 *)memtest_menu_simm_str },
    { 0xC, 0xD, 2, (const s8 *)memtest_menu_exit_str },
    { 0xC, 0x1A, 2, (const s8 *)memtest_select_help_str },
    { 0xC, 0x1B, 2, (const s8 *)memtest_start_help_str },
};

const TM_STRING memtest_ram_scr[16] = {
    { 9, 1, 2, (const s8 *)memtest_ram_title_str },
    { 0x10, 3, 2, (const s8 *)memtest_work_ram_str },
    { 0x10, 5, 2, (const s8 *)memtest_sprite_ram_str },
    { 0x10, 7, 2, (const s8 *)memtest_color_ram_str },
    { 0x10, 9, 2, (const s8 *)memtest_character_ram_str },
    { 0x10, 0xB, 2, (const s8 *)memtest_ss_ram_str },
    { 0x10, 0xD, 2, (const s8 *)memtest_eeprom_str },
    { 0x10, 0xF, 2, (const s8 *)str_FRAM },
    { 0x10, 0x11, 2, (const s8 *)memtest_cdrom_str },
    { 0x10, 0x13, 2, (const s8 *)memtest_flash_simm1_str },
    { 0x10, 0x14, 2, (const s8 *)memtest_simm2_str },
    { 0x10, 0x15, 2, (const s8 *)memtest_simm3_str },
    { 0x10, 0x16, 2, (const s8 *)memtest_simm4_str },
    { 0x10, 0x17, 2, (const s8 *)memtest_simm5_str },
    { 0x10, 0x18, 2, (const s8 *)memtest_simm6_str },
    { 0x10, 0x19, 2, (const s8 *)memtest_simm7_str },
};

const TM_STRING memtest_simm_scr[8] = {
    { 0xB, 1, 2, (const s8 *)memtest_simm_title_and_names },
    { 0x10, 5, 2, (const s8 *)memtest_flash_simm1_str },
    { 0x10, 7, 2, (const s8 *)memtest_simm2_str },
    { 0x10, 9, 2, (const s8 *)memtest_simm3_str },
    { 0x10, 0xB, 2, (const s8 *)memtest_simm4_str },
    { 0x10, 0xD, 2, (const s8 *)memtest_simm5_str },
    { 0x10, 0xF, 2, (const s8 *)memtest_simm6_str },
    { 0x10, 0x11, 2, (const s8 *)memtest_simm7_str },
};

const u32 simm_sum_offset_tbl[16] = {
    0, 0xAAAAA, 0x155555, 0x1FFFFF, 0x200000, 0x2AAAAA, 0x355555, 0x3FFFFF,
    0x400000, 0x4AAAAA, 0x555555, 0x5FFFFF, 0x600000, 0x6AAAAA, 0x755555, 0x7FFFFF,
};

const s8 cdb_test_unit_ready[6] = {
    0, 0, 0, 0, 0, 0,
};

const s8 cdb_read_capacity[10] = "%";

const s8 cdb_inquiry[6] = {
    18, 0, 0, 0, 36, 0,
};

const s8 cdb_request_sense[6] = {
    3, 0, 0, 0, 18, 0,
};

const s8 cdb_read_toc[12] = "C\0\0\0\0\0\0\0\x0C\0\0\x05";

const s8 memtest_checking_str[12] = "CHECKING...";

const s8 memtest_ng_str[12] = "NG         ";

const s8 memtest_ok_str[12] = "OK         ";

const s8 memtest_skip_str[12] = "SKIP       ";

const char memtest_menu_title_str[32] = "8 . M E M O R Y   C H E C K\n\0\x15\0\x15";

const char memtest_menu_memory_str[24] = "     1. MEMORY CHECK\n\0\0\x0A";

const char memtest_menu_simm_str[20] = "     2. SIMM CHECK\n";

const char memtest_menu_exit_str[16] = "     3. EXIT\n\0\0\x18";

const char memtest_select_help_str[24] = "SELECT = 1P UP or DOWN\n";

const char memtest_start_help_str[20] = "START  = 1P SHOT1\0\0\x18";

const char memtest_ram_title_str[36] = "8 - 1 . M E M O R Y   C H E C K\n\0\x0A\0\x09";

const char memtest_work_ram_str[12] = "WORK RAM\n\0\0\x03";

const char memtest_sprite_ram_str[12] = "SPRITE RAM\n";

const char memtest_color_ram_str[12] = "COLOR RAM\n\0\x1B";

const char memtest_character_ram_str[16] = "CHARACTER RAM\n\0\x1B";

const char memtest_ss_ram_str[8] = "SS RAM\n";

const char memtest_eeprom_str[12] = "EEP ROM\n\0\x1B\0\x1B";

const char str_FRAM[8] = "FRAM\n\0\0\x1A";

const char memtest_cdrom_str[8] = "CD-ROM\n";

const char memtest_flash_simm1_str[16] = "FLASH SIMM1\n\0\x0F\0\x0E";

const char memtest_simm2_str[16] = "      SIMM2\n\0\x07\0\x06";

const char memtest_simm3_str[16] = "      SIMM3\n";

const char memtest_simm4_str[16] = "      SIMM4\n\0\x1E\0\x1E";

const char memtest_simm5_str[16] = "      SIMM5\n\0\x1E\0\x1E";

const char memtest_simm6_str[16] = "      SIMM6\n\0\x1E\0\x1E";

const char memtest_simm7_str[12] = "      SIMM7";

const char memtest_simm_title_and_names[32] = "8 - 2 . S I M M   C H E C K\n\0\x0A\0\x09";

const char str_ONBOARD[12] = "ONBOARD    ";

const char str_SIMM1[12] = "SIMM1      ";

const char str_SIMM2[12] = "SIMM2      ";

const char str_SIMM3[12] = "SIMM3      ";

const char str_SIMM4[12] = "SIMM4      ";

const char str_SIMM5[12] = "SIMM5      ";

const char str_SIMM6[12] = "SIMM6      ";

const char str_SIMM7[12] = "SIMM7      ";

const TM_STRING rewrite_menu_scr[7] = {
    { 0xC, 2, 2, (const s8 *)rewrite_title_str },
    { 0x11, 9, 2, (const s8 *)rewrite_all_str },
    { 0x11, 0xB, 2, (const s8 *)rewrite_character_str },
    { 0x11, 0xD, 2, (const s8 *)str_EXIT },
    { 7, 0x12, 4, (const s8 *)rewrite_note1_str },
    { 7, 0x13, 4, (const s8 *)rewrite_note2_str },
    { 7, 0x14, 4, (const s8 *)rewrite_note3_str },
};

const TM_STRING rewrite_guide_scr[2] = {
    { 0xD, 0x19, 2, (const s8 *)rewrite_select_help_str },
    { 0xD, 0x1A, 2, (const s8 *)rewrite_start_help_str },
};

const TM_STRING rewrite_exit_guide_scr[3] = {
    { 0xD, 0x19, 2, (const s8 *)rewrite_select_help_str },
    { 0xD, 0x1A, 2, (const s8 *)rewrite_exit_help_str },
    { 0xD, 0x1B, 2, (const s8 *)str_blank_16 },
};

const TM_STRING rewrite_not_ready_str[1] = {
    { 0x10, 0xC, 0xE, (const s8 *)rewrite_cd_not_ready_str },
};

const char rewrite_title_str[32] = "9 . G A M E   R E W R I T E\n\0\x24\0\x24";

const char rewrite_all_str[16] = "REWRITE ALL\n\0\x1F\0\x1E";

const char rewrite_character_str[20] = "REWRITE CHARACTER\n\0\x14";

const char str_EXIT[8] = "EXIT\n\0\0\x10";

const char rewrite_note1_str[36] = "NOTE: Rewriting game will erase\n";

const char rewrite_note2_str[40] = "     the prior memory and will take\n\0\x24\0\x23";

const char rewrite_note3_str[40] = "     15~20 min. to load the new one.\0\x10\0\x0F";

const char rewrite_select_help_str[24] = "SELECT = 1P UP or DOWN\n";

const char rewrite_start_help_str[28] = "START  = 1P START & SHOT1\0\0\x28";

const char rewrite_exit_help_str[28] = "START  = 1P SHOT1        \n\0\x20";

const char str_blank_16[28] = "                        \0\x13\0\x12";

const char rewrite_cd_not_ready_str[20] = "CD-ROM NOT READY\0\x09\0\x08";

const u16 sys_palette[256] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x7FFF, 0x77BD, 0x6F7B, 0x6739, 0x5EF7, 0x56B5, 0x4E73,
    0x4631, 0x2D6B, 0x2529, 0, 0, 0, 0, 0,
    0, 0x3BF, 0x37D, 0x33B, 0x2F9, 0x2B7, 0x275, 0x233,
    0x171, 0x12B, 0xE9, 0, 0, 0, 0, 0,
    0, 0x7C00, 0x7400, 0x6C00, 0x6400, 0x5C00, 0x5400, 0x4C00,
    0x4400, 0x2C00, 0x2400, 0, 0, 0, 0, 0,
    0, 0x1F, 0x1D, 0x1B, 0x19, 0x17, 0x15, 0x13,
    0x11, 0xB, 9, 0, 0, 0, 0, 0,
    0, 0x3E0, 0x3A0, 0x360, 0x320, 0x2E0, 0x2A0, 0x260,
    0x220, 0x160, 0x120, 0, 0, 0, 0, 0,
    0, 0x7C1F, 0x741D, 0x6C1B, 0x6419, 0x5C17, 0x5415, 0x4C13,
    0x4411, 0x2C0B, 0x2409, 0, 0, 0, 0, 0,
    0, 0x25F, 0x21D, 0x1FB, 0x1B9, 0x177, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x7FFF, 0x77BD, 0x6F7B, 0x6739, 0x5EF7, 0x56B5, 0x4E73,
    0x4631, 0x2D6B, 0x2529, 0, 0, 0, 0, 0,
    0, 0x7FFF, 0x77BD, 0x6F7B, 0x6739, 0x5EF7, 0x56B5, 0x4E73,
    0x4631, 0x2D6B, 0x2529, 0, 0, 0, 0, 0,
    0, 0x7FFF, 0x77BD, 0x6F7B, 0x6739, 0x5EF7, 0x56B5, 0x4E73,
    0x4631, 0x2D6B, 0x2529, 0, 0, 0, 0, 0,
    0, 0x7FFF, 0x77BD, 0x6F7B, 0x6739, 0x5EF7, 0x56B5, 0x4E73,
    0x4631, 0x2D6B, 0x2529, 0, 0, 0, 0, 0,
    0, 0x7FFF, 0x77BD, 0x6F7B, 0x6739, 0x5EF7, 0x56B5, 0x4E73,
    0x4631, 0x2D6B, 0x2529, 0, 0, 0, 0, 0,
    0, 0x7FFF, 0x77BD, 0x6F7B, 0x6739, 0x5EF7, 0x56B5, 0x4E73,
    0x4631, 0x2D6B, 0x2529, 0, 0, 0, 0, 0,
    0, 0x7FFF, 0x77BD, 0x6F7B, 0x6739, 0x5EF7, 0x56B5, 0x4E73,
    0x4631, 0x2D6B, 0x2529, 0, 0, 0, 0, 0,
    0, 0x7FFF, 0x77BD, 0x6F7B, 0x6739, 0x5EF7, 0x56B5, 0x4E73,
    0x4631, 0x2D6B, 0x2529, 0, 0, 0, 0, 0,
};

const u8 coin_counter_bit_tbl[4] = {
    0xEF, 0x10, 0, 0,
};
