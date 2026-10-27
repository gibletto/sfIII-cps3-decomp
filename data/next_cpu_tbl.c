/*
 * NEXT_CPU_TBL.C  Japanese game configuration value scripts
 *
 * Text-layer scripts of the Japanese GAME CONFIGURATION page of test mode, continued from
 * GAME_CONFIG_JP_TBL.C: the values of the screen, round and event items (gcfg_screen_scr_jp_0,
 * gcfg_round_scr_jp_0 .. 3, gcfg_event_scr_jp_0 and 1), the cursor and its blank
 * (gcfg_cursor_scr_jp_0, gcfg_cursor_clr_scr_jp_0) and the star gauges (gcfg_gauge_scr_jp_0 ..
 * 7, gcfg_gauge_clr_scr_jp_0). Read by GAME_CONFIG_JP.C through its gcfg_*_scr_jp script
 * tables.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u16 gcfg_screen_scr_jp_0[];
extern const u16 gcfg_round_scr_jp_0[];
extern const u16 gcfg_round_scr_jp_1[];
extern const u16 gcfg_round_scr_jp_2[];
extern const u16 gcfg_round_scr_jp_3[];
extern const u16 gcfg_event_scr_jp_0[];
extern const u16 gcfg_event_scr_jp_1[];
extern const u16 gcfg_cursor_scr_jp_0[];
extern const u16 gcfg_cursor_clr_scr_jp_0[];
extern const u16 gcfg_gauge_scr_jp_0[];
extern const u16 gcfg_gauge_scr_jp_1[];
extern const u16 gcfg_gauge_scr_jp_2[];
extern const u16 gcfg_gauge_scr_jp_3[];
extern const u16 gcfg_gauge_scr_jp_4[];
extern const u16 gcfg_gauge_scr_jp_5[];
extern const u16 gcfg_gauge_scr_jp_6[];
extern const u16 gcfg_gauge_scr_jp_7[];
extern const u16 gcfg_gauge_clr_scr_jp_0[];

const u16 gcfg_screen_scr_jp_0[9] = {
    4, 0, 0, 2, 0x12D8, 0x13C8, 0x12F8, 0x1314,
    0,
};

const u16 gcfg_round_scr_jp_0[9] = {
    4, 0, 0, 2, 0x1218, 0x13B4, 0x1388, 0x138C,
    0,
};

const u16 gcfg_round_scr_jp_1[9] = {
    4, 0, 0, 2, 0x1220, 0x13B4, 0x1388, 0x138C,
    0,
};

const u16 gcfg_round_scr_jp_2[9] = {
    4, 0, 0, 2, 0x1228, 0x13B4, 0x1388, 0x138C,
    0,
};

const u16 gcfg_round_scr_jp_3[9] = {
    4, 0, 0, 2, 0x1230, 0x13B4, 0x1388, 0x138C,
    0,
};

const u16 gcfg_event_scr_jp_0[9] = {
    4, 0, 0, 2, 0x12D8, 0x13C8, 0x12F8, 0x1314,
    0,
};

const u16 gcfg_event_scr_jp_1[9] = {
    4, 0, 0, 2, 0x1218, 0x12F8, 0x12C0, 0x12BC,
    0,
};

const u16 gcfg_cursor_scr_jp_0[6] = {
    1, 0, 0, 2, 0x1204, 0,
};

const u16 gcfg_cursor_clr_scr_jp_0[6] = {
    1, 0, 0, 2, 0x1200, 0,
};

const u16 gcfg_gauge_scr_jp_0[6] = {
    1, 0, 0, 2, 0x1218, 0,
};

const u16 gcfg_gauge_scr_jp_1[6] = {
    1, 0, 0, 2, 0x121C, 0,
};

const u16 gcfg_gauge_scr_jp_2[6] = {
    1, 0, 0, 2, 0x1220, 0,
};

const u16 gcfg_gauge_scr_jp_3[6] = {
    1, 0, 0, 2, 0x1224, 0,
};

const u16 gcfg_gauge_scr_jp_4[6] = {
    1, 0, 0, 2, 0x1228, 0,
};

const u16 gcfg_gauge_scr_jp_5[6] = {
    1, 0, 0, 2, 0x122C, 0,
};

const u16 gcfg_gauge_scr_jp_6[6] = {
    1, 0, 0, 2, 0x1230, 0,
};

const u16 gcfg_gauge_scr_jp_7[6] = {
    1, 0, 0, 2, 0x1234, 0,
};

const u16 gcfg_gauge_clr_scr_jp_0[7] = {
    1, 0, 0, 2, 0x13CC, 0, 0x707,
};
