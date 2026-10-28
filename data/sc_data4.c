/*
 * SC_DATA4.C  stun gauge and combo message tables
 *
 * stngauge_puttbl_0 and _1 are the cell codes of the stun gauge, stngauge_postbl_0 ..
 * stngauge_postbl_1_2 the cell columns of each player's gauge for the two screen modes, and
 * stun_genkai_tbl the stun limit of each character; read by SC_SUB_3.C, the stun gauge
 * control. cmb_pos_tbl gives the combo message window columns by screen mode and side,
 * cmb_window_move_tbl and cmb_window_time_tbl each message kind's slide and display time, and
 * combo_score_tbl the first-hit and per-hit points of each combo kind; read by CMB_CONT.C, the
 * combo, reversal and parry bonus control.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u16 stngauge_puttbl_0[];
extern const u16 stngauge_puttbl_1[];
extern const u16 stngauge_postbl_0[];
extern const u16 stngauge_postbl_1[];
extern const u16 stngauge_postbl_0_2[];
extern const u16 stngauge_postbl_1_2[];
extern const s16 stun_genkai_tbl[];
extern const s16 cmb_pos_tbl[][2][21];
extern const s16 cmb_window_move_tbl[];
extern const s16 cmb_window_time_tbl[];
extern const u32 combo_score_tbl[][2];

const u16 stngauge_puttbl_0[9] = {
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8,
};

const u16 stngauge_puttbl_1[9] = {
    0x170, 0x171, 0x172, 0x173, 0x174, 0x175, 0x176, 0x177, 0x178,
};

const u16 stngauge_postbl_0[11] = {
    20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,
};

const u16 stngauge_postbl_1[11] = {
    27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
};

const u16 stngauge_postbl_0_2[11] = {
    27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,
};

const u16 stngauge_postbl_1_2[11] = {
    34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
};

const s16 stun_genkai_tbl[14] = {
    88, 80, 64, 64, 72, 64, 88, 64, 64, 72, 64, 64, 64, -9,
};

const s16 cmb_pos_tbl[2][2][21] = {
    {
        { 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27 },
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 },
    },
    {
        { 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41 },
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 },
    },
};

const s16 cmb_window_move_tbl[7] = {
    12, 16, 20, 16, 12, 10, 12,
};

const s16 cmb_window_time_tbl[7] = {
    28, 40, 60, 60, 50, 50, 24,
};

/* one row per score_calc slot: { score, score per combo hit } */
const u32 combo_score_tbl[11][2] = {
    { 300, 200 }, { 500, 400 }, { 1000, 600 }, { 1000, 600 },
    { 2000, 800 }, { 3000, 600 }, { 4000, 800 }, { 5000, 1000 },
    { 6000, 2000 }, { 8000, 2000 }, { 9000, 3000 },
};
