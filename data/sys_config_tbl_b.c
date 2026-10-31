/*
 * SYS_CONFIG_TBL_B.C  coin rates and system configuration setting texts
 *
 * coin_rate_tbl gives the coins and credits of each coin setting, read by SYS_CONFIG.C when
 * the settings are put into effect. The coin_setting_str_tbl_, chute_mode_str_tbl_,
 * on_off_str_tbl_, sound_mode_str_tbl_ and monitor_str_tbl_ entries place the value shown for
 * each coin, chute mode, on/off, sound mode, language and monitor setting, and cursor_mark_str
 * and cursor_blank_str are the menu cursor and its blank; these are read by SYS_CONFIG_2.C,
 * the test mode configuration menu. The str_ strings that follow are the setting texts they
 * point at.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u8 coin_rate_tbl[][2];
extern const TM_STRING coin_setting_str_tbl_0[];
extern const TM_STRING coin_setting_str_tbl_1[];
extern const TM_STRING coin_setting_str_tbl_2[];
extern const TM_STRING coin_setting_str_tbl_3[];
extern const TM_STRING coin_setting_str_tbl_4[];
extern const TM_STRING coin_setting_str_tbl_5[];
extern const TM_STRING coin_setting_str_tbl_6[];
extern const TM_STRING coin_setting_str_tbl_7[];
extern const TM_STRING coin_setting_str_tbl_8[];
extern const TM_STRING coin_setting_str_tbl_9[];
extern const TM_STRING coin_setting_str_tbl_10[];
extern const TM_STRING coin_setting_str_tbl_11[];
extern const TM_STRING coin_setting_str_tbl_12[];
extern const TM_STRING coin_setting_str_tbl_13[];
extern const TM_STRING coin_setting_str_tbl_14[];
extern const TM_STRING coin_setting_str_tbl_15[];
extern const TM_STRING coin_setting_str_tbl_16[];
extern const TM_STRING coin_setting_str_tbl_17[];
extern const TM_STRING coin_setting_str_tbl_18[];
extern const TM_STRING chute_mode_str_tbl_0[];
extern const TM_STRING chute_mode_str_tbl_1[];
extern const TM_STRING chute_mode_str_tbl_2[];
extern const TM_STRING chute_mode_str_tbl_3[];
extern const TM_STRING chute_mode_str_tbl_4[];
extern const TM_STRING chute_mode_str_tbl_5[];
extern const TM_STRING chute_mode_str_tbl_6[];
extern const TM_STRING chute_mode_str_tbl_7[];
extern const TM_STRING chute_mode_str_tbl_8[];
extern const TM_STRING chute_mode_str_tbl_9[];
extern const TM_STRING chute_mode_str_tbl_10[];
extern const TM_STRING chute_mode_str_tbl_11[];
extern const TM_STRING on_off_str_tbl_1[];
extern const TM_STRING on_off_str_tbl_0[];
extern const TM_STRING sound_mode_str_tbl_0[];
extern const TM_STRING sound_mode_str_tbl_1[];
extern const TM_STRING sound_mode_str_tbl_2[];
extern const TM_STRING sound_mode_str_tbl_3[];
extern const TM_STRING sound_mode_str_tbl_4[];
extern const TM_STRING sound_mode_str_tbl_5[];
extern const TM_STRING monitor_str_tbl_1[];
extern const s8 cursor_blank_str[];
extern const s8 cursor_mark_str[];
extern const s8 str_1coin_1credit[];
extern const s8 str_1coin_2credits[];
extern const s8 str_1coin_3credits[];
extern const s8 str_1coin_4credits[];
extern const s8 str_1coin_5credits[];
extern const s8 str_1coin_6credits[];
extern const s8 str_1coin_7credits[];
extern const s8 str_1coin_8credits[];
extern const s8 str_1coin_9credits[];
extern const s8 str_2coins_1credit[];
extern const s8 str_3coins_1credit[];
extern const s8 str_4coins_1credit[];
extern const s8 str_5coins_1credit[];
extern const s8 str_6coins_1credit[];
extern const s8 str_7coins_1credit[];
extern const s8 str_8coins_1credit[];
extern const s8 str_9coins_1credit[];
extern const s8 str_2coins_start_1coin_cont[];
extern const s8 str_coin_free_play[];
extern const s8 str_2pl_1chute_single[];
extern const s8 str_2pl_2chutes_single[];
extern const s8 str_2pl_2chutes_multi[];
extern const s8 str_3pl_1chute_single[];
extern const s8 str_3pl_2chutes_single[];
extern const s8 str_3pl_3chutes_single[];
extern const s8 str_3pl_3chutes_multi[];
extern const s8 str_4pl_1chute_single[];
extern const s8 str_4pl_2chutes_single[];
extern const s8 str_4pl_2chutes_multi[];
extern const s8 str_4pl_4chutes_single[];
extern const s8 str_4pl_4chutes_multi[];
extern const s8 str_ON[];
extern const s8 str_OFF_2[];
extern const s8 str_cfg_stereo[];
extern const s8 str_cfg_monaural[];
extern const s8 str_cfg_english[];
extern const s8 str_cfg_spanish[];
extern const s8 str_cfg_portuguese[];
extern const s8 str_NORMAL_3[];
extern const s8 str_FLIP_2[];

/* one row per coin setting (Coin_Mode): { coins, credits } */
const u8 coin_rate_tbl[20][2] = {
    { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 1, 6 }, { 1, 7 }, { 1, 8 },
    { 1, 9 }, { 2, 1 }, { 3, 1 }, { 4, 1 }, { 5, 1 }, { 6, 1 }, { 7, 1 }, { 8, 1 },
    { 9, 1 }, { 1, 1 }, { 0, 0 }, { 0, 0 },
};

const TM_STRING coin_setting_str_tbl_0[1] = {
    { 18, 5, 0xE, str_1coin_1credit },
};

const TM_STRING coin_setting_str_tbl_1[1] = {
    { 18, 5, 0xE, str_1coin_2credits },
};

const TM_STRING coin_setting_str_tbl_2[1] = {
    { 18, 5, 0xE, str_1coin_3credits },
};

const TM_STRING coin_setting_str_tbl_3[1] = {
    { 18, 5, 0xE, str_1coin_4credits },
};

const TM_STRING coin_setting_str_tbl_4[1] = {
    { 18, 5, 0xE, str_1coin_5credits },
};

const TM_STRING coin_setting_str_tbl_5[1] = {
    { 18, 5, 0xE, str_1coin_6credits },
};

const TM_STRING coin_setting_str_tbl_6[1] = {
    { 18, 5, 0xE, str_1coin_7credits },
};

const TM_STRING coin_setting_str_tbl_7[1] = {
    { 18, 5, 0xE, str_1coin_8credits },
};

const TM_STRING coin_setting_str_tbl_8[1] = {
    { 18, 5, 0xE, str_1coin_9credits },
};

const TM_STRING coin_setting_str_tbl_9[1] = {
    { 18, 5, 0xE, str_2coins_1credit },
};

const TM_STRING coin_setting_str_tbl_10[1] = {
    { 18, 5, 0xE, str_3coins_1credit },
};

const TM_STRING coin_setting_str_tbl_11[1] = {
    { 18, 5, 0xE, str_4coins_1credit },
};

const TM_STRING coin_setting_str_tbl_12[1] = {
    { 18, 5, 0xE, str_5coins_1credit },
};

const TM_STRING coin_setting_str_tbl_13[1] = {
    { 18, 5, 0xE, str_6coins_1credit },
};

const TM_STRING coin_setting_str_tbl_14[1] = {
    { 18, 5, 0xE, str_7coins_1credit },
};

const TM_STRING coin_setting_str_tbl_15[1] = {
    { 18, 5, 0xE, str_8coins_1credit },
};

const TM_STRING coin_setting_str_tbl_16[1] = {
    { 18, 5, 0xE, str_9coins_1credit },
};

const TM_STRING coin_setting_str_tbl_17[1] = {
    { 18, 5, 0xE, str_2coins_start_1coin_cont },
};

const TM_STRING coin_setting_str_tbl_18[1] = {
    { 18, 5, 0xE, str_coin_free_play },
};

const TM_STRING chute_mode_str_tbl_0[1] = {
    { 18, 7, 0xE, str_2pl_1chute_single },
};

const TM_STRING chute_mode_str_tbl_1[1] = {
    { 18, 7, 0xE, str_2pl_2chutes_single },
};

const TM_STRING chute_mode_str_tbl_2[1] = {
    { 18, 7, 0xE, str_2pl_2chutes_multi },
};

const TM_STRING chute_mode_str_tbl_3[1] = {
    { 18, 7, 0xE, str_3pl_1chute_single },
};

const TM_STRING chute_mode_str_tbl_4[1] = {
    { 18, 7, 0xE, str_3pl_2chutes_single },
};

const TM_STRING chute_mode_str_tbl_5[1] = {
    { 18, 7, 0xE, str_3pl_3chutes_single },
};

const TM_STRING chute_mode_str_tbl_6[1] = {
    { 18, 7, 0xE, str_3pl_3chutes_multi },
};

const TM_STRING chute_mode_str_tbl_7[1] = {
    { 18, 7, 0xE, str_4pl_1chute_single },
};

const TM_STRING chute_mode_str_tbl_8[1] = {
    { 18, 7, 0xE, str_4pl_2chutes_single },
};

const TM_STRING chute_mode_str_tbl_9[1] = {
    { 18, 7, 0xE, str_4pl_2chutes_multi },
};

const TM_STRING chute_mode_str_tbl_10[1] = {
    { 18, 7, 0xE, str_4pl_4chutes_single },
};

const TM_STRING chute_mode_str_tbl_11[1] = {
    { 18, 7, 0xE, str_4pl_4chutes_multi },
};

const TM_STRING on_off_str_tbl_1[1] = {
    { 18, 11, 0xE, str_ON },
};

const TM_STRING on_off_str_tbl_0[1] = {
    { 18, 11, 0xE, str_OFF_2 },
};

const TM_STRING sound_mode_str_tbl_0[1] = {
    { 18, 16, 0xE, str_cfg_stereo },
};

const TM_STRING sound_mode_str_tbl_1[1] = {
    { 18, 16, 0xE, str_cfg_monaural },
};

const TM_STRING sound_mode_str_tbl_2[1] = {
    { 18, 19, 0xE, str_cfg_english },
};

const TM_STRING sound_mode_str_tbl_3[1] = {
    { 18, 19, 0xE, str_cfg_spanish },
};

const TM_STRING sound_mode_str_tbl_4[1] = {
    { 18, 19, 0xE, str_cfg_portuguese },
};

const TM_STRING sound_mode_str_tbl_5[1] = {
    { 18, 11, 0xE, str_NORMAL_3 },
};

const TM_STRING monitor_str_tbl_1[1] = {
    { 18, 11, 0xE, str_FLIP_2 },
};

const s8 cursor_blank_str[4] = " \0\0\x06";

const s8 cursor_mark_str[4] = ">";

/* provisional name */
const s8 str_1coin_1credit[32] = "1 COIN  1 CREDIT             ";

/* provisional name */
const s8 str_1coin_2credits[32] = "1 COIN  2 CREDITS            ";

/* provisional name */
const s8 str_1coin_3credits[32] = "1 COIN  3 CREDITS            \0\0\x02";

/* provisional name */
const s8 str_1coin_4credits[32] = "1 COIN  4 CREDITS            ";

/* provisional name */
const s8 str_1coin_5credits[32] = "1 COIN  5 CREDITS            ";

/* provisional name */
const s8 str_1coin_6credits[32] = "1 COIN  6 CREDITS            ";

/* provisional name */
const s8 str_1coin_7credits[32] = "1 COIN  7 CREDITS            \0\0\x0C";

/* provisional name */
const s8 str_1coin_8credits[32] = "1 COIN  8 CREDITS            ";

/* provisional name */
const s8 str_1coin_9credits[32] = "1 COIN  9 CREDITS            ";

/* provisional name */
const s8 str_2coins_1credit[32] = "2 COINS 1 CREDIT             \0\0\x06";

/* provisional name */
const s8 str_3coins_1credit[32] = "3 COINS 1 CREDIT             ";

/* provisional name */
const s8 str_4coins_1credit[32] = "4 COINS 1 CREDIT             ";

/* provisional name */
const s8 str_5coins_1credit[32] = "5 COINS 1 CREDIT             ";

/* provisional name */
const s8 str_6coins_1credit[32] = "6 COINS 1 CREDIT             \0\0\x10";

/* provisional name */
const s8 str_7coins_1credit[32] = "7 COINS 1 CREDIT             ";

/* provisional name */
const s8 str_8coins_1credit[32] = "8 COINS 1 CREDIT             ";

/* provisional name */
const s8 str_9coins_1credit[32] = "9 COINS 1 CREDIT             \0\0\x0A";

/* provisional name */
const s8 str_2coins_start_1coin_cont[32] = "2 COINS START 1 COIN CONTINUE";

/* provisional name */
const s8 str_coin_free_play[32] = "FREE PLAY                    ";

/* provisional name */
const s8 str_2pl_1chute_single[28] = "2 PLAYERS 1 CHUTER  SINGLE ";

/* provisional name */
const s8 str_2pl_2chutes_single[28] = "2 PLAYERS 2 CHUTERS SINGLE ";

/* provisional name */
const s8 str_2pl_2chutes_multi[28] = "2 PLAYERS 2 CHUTERS MULTI  ";

/* provisional name */
const s8 str_3pl_1chute_single[28] = "3 PLAYERS 1 CHUTER  SINGLE ";

/* provisional name */
const s8 str_3pl_2chutes_single[28] = "3 PLAYERS 2 CHUTERS SINGLE ";

/* provisional name */
const s8 str_3pl_3chutes_single[28] = "3 PLAYERS 3 CHUTERS SINGLE ";

/* provisional name */
const s8 str_3pl_3chutes_multi[28] = "3 PLAYERS 3 CHUTERS MULTI  ";

/* provisional name */
const s8 str_4pl_1chute_single[28] = "4 PLAYERS 1 CHUTER  SINGLE ";

/* provisional name */
const s8 str_4pl_2chutes_single[28] = "4 PLAYERS 2 CHUTERS SINGLE ";

/* provisional name */
const s8 str_4pl_2chutes_multi[28] = "4 PLAYERS 2 CHUTERS MULTI  ";

/* provisional name */
const s8 str_4pl_4chutes_single[28] = "4 PLAYERS 4 CHUTERS SINGLE ";

/* provisional name */
const s8 str_4pl_4chutes_multi[28] = "4 PLAYERS 4 CHUTERS MULTI  ";

const s8 str_ON[8] = "ON    ";

const s8 str_OFF_2[8] = "OFF   \0\x02";

const s8 str_cfg_stereo[12] = "STEREO  \0\x07\0\x08";

const s8 str_cfg_monaural[12] = "MONAURAL\0\x0D\0\x0E";

/* provisional name */
const s8 str_cfg_english[16] = "ENGLISH     \0\x15\0\x16";

/* provisional name */
const s8 str_cfg_spanish[16] = "SPANISH     \0\x1D\0\x1E";

/* provisional name */
const s8 str_cfg_portuguese[16] = "PORTUGUESE  ";

const s8 str_NORMAL_3[8] = "NORMAL";

const s8 str_FLIP_2[72] = "FLIP  \0\0\0\0\x01\xFF\x02\0\x03\xFF\x3F\x0F\0\x0D\0\0\0\0\0\0\x01\xFF\x02\0\x03\xBF\x3F\x0F\0\x0D\0\0\0\0\0\0\x01\xFF\x02\0\x03\x7F\x3F\x0F\0\x0D\0\0\0\0\0\0\x01\xFF\x02\0\x03\x3F\x3F\x0F\0\x0D";
