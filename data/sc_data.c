/*
 * SC_DATA.C  text layer HUD tables
 *
 * sc_celllist_scr_tbl gives the screen column base of each text-layer cell list,
 * sc_player_name_chr_tbl the first character of each character's name, tone_down_tbl the
 * character transfers of each screen tone-down, and bcount_mark_chr the characters of each
 * centre message; these are read by SC_TRANS.C, the text layer transfer and put routines.
 * nwdata_tbl gives each character's winner name plate (characters, size and the positions of
 * the name and its second block); read by SC_TRANS.C and MANAGE_2.C (round and match
 * management).
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s8 sc_celllist_scr_tbl[];
extern const u16 sc_player_name_chr_tbl[];
extern const TONE_ENTRY tone_down_tbl[];
extern const u16 bcount_mark_chr[];
extern const NAME_PLATE nwdata_tbl[];

const s8 sc_celllist_scr_tbl[18] = {
    0, 3, 3, 3, 13, 12, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3,
    3, -56,
};

const u16 sc_player_name_chr_tbl[13] = {
    0x408, 0x40E, 0x414, 0x41A, 0x420, 0x426, 0x42C, 0x432, 0x438, 0x43E, 0x444, 0x44A, 0x450,
};

const TONE_ENTRY tone_down_tbl[8] = {
    { 0x80, 0x600, 0 }, { 4, 0x1B0, 0xBA }, { 4, 0x1C0, 0xCA }, { 0x30, 0x12A0, 0x130 },
    { 0x20, 0x13A0, 0x1E0 }, { 0xC0, 0x1000, 0x140 }, { 0x10, 0x12D0, 0x160 }, { 0x10, 0x12E0, 0x170 },
};

const u16 bcount_mark_chr[7] = {
    0xD80, 0xC80, 0xF00, 0xE80, 0xC00, 0xD00, 0xF80,
};

const NAME_PLATE nwdata_tbl[13] = {
    { 0x1100, 8, 4, 15, 9, 24, 9 }, { 0x1120, 9, 4, 14, 9, 25, 9 },
    { 0x1144, 6, 4, 16, 9, 23, 9 }, { 0x115C, 7, 4, 15, 9, 24, 9 },
    { 0x1178, 0xC, 4, 12, 9, 26, 9 }, { 0x11A8, 0xB, 4, 13, 9, 26, 9 },
    { 0x11B4, 8, 4, 14, 9, 24, 9 }, { 0x11D4, 9, 4, 14, 9, 25, 9 },
    { 0x11F8, 0xB, 4, 13, 9, 26, 9 }, { 0x1224, 7, 4, 15, 9, 24, 9 },
    { 0x1240, 9, 4, 14, 9, 26, 9 }, { 0x1264, 7, 4, 15, 9, 24, 9 },
    { 0x1580, 9, 4, 14, 9, 25, 9 },
};
