/*
 * sc_trans.c  Text (fix) layer character transfer and put routines
 *
 * Low-level routines for the text layer used by the HUD, menus and result screens. Character data
 * from sc_chr_data is copied into the text layer's character RAM (sc_chr_trans, sc_chr_block_trans,
 * sc_chr_sheet_trans) or between RAM buffers and video RAM (sc_chr_to_ram, sc_vram_to_ram);
 * sc_chr_save / sc_chr_load keep the name-entry letters while Ranking_00_6th reloads the whole font,
 * and ToneDown loads the screen tone-down characters. The put routines write cells to the text
 * tilemap: square and line blocks (scfont_sqput, scfont_lnput and the reversed forms), fills, single
 * cells and attributes, cell lists and score digits. The HUD transfers built on them draw the player
 * names and faces, the super art numbers and stocks, the stun and max marks, the centre messages
 * (bcount_mark_trans), the round win marks and the combo window (combo_*). SF3_logo puts the logo as a
 * 16 x 6 cell block, and break_into_banner_trans draws the challenger banner a column at a time for
 * effect A2.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
s32 tilemap_put_cell(u16 x, u16 y, u16 attr, u16 code);
void sc_chr_clear();
#include "cps3.h"
#include "fighter.h"
#include "sc_logo.h"
#include "EffA2.h"
#include "cmb_win.h"



u16 *sc_trans_dst;
u8 *sc_bak_ptr;
u8 *sc_trans_src;
u8 sc_trans_src_tail[6];  /* after sc_trans_src; nothing refers to it by name or address */
u16 sc_trans_word;
u8 sc_chr_bak[640];

extern const u16 sc_player_name_chr_tbl[];

extern const u16 sa_number_attr_tbl[];



s32 sc_chr_trans(rows)
u16 rows;
{
    u16* dst = sc_trans_dst;
    u8* src = sc_trans_src;
    s32 i;
    for (i = 0; i < rows * 32; i++) {
        *dst = *src;
        dst++;
        src++;
    }
}



void sc_chr_save(u16 rows) {
    s32 i;
    for (i = 0; i < rows * 32; i++) {
        *sc_bak_ptr = *sc_trans_dst;
        sc_bak_ptr++;
        sc_trans_dst++;
    }
}



void sc_chr_load(u16 rows) {
    s32 i;
    for (i = 0; i < rows * 32; i++) {
        *sc_trans_dst = *sc_bak_ptr;
        sc_bak_ptr++;
        sc_trans_dst++;
    }
}



void sc_chr_block_trans(chr, pos, w, h)
u16 chr;
u16 pos;
u16 w;
u16 h;
{
    s32 i, j, k;
    u16* dst;
    sc_trans_src = (u8*)&sc_chr_data[chr * 32 / 2];
    sc_trans_dst = (u16*)(pos * 64 + (SS_RAM + 0x8000));
    dst = sc_trans_dst;
    i = 0;
    for (; (u16)i < h; i++) {
        for (j = 0; (u16)j < w; j++) {
            k = 0;
            do {
                k += 2;
                {
                    u16 v = *sc_trans_src;
                    *sc_trans_dst = v;
                }
                sc_trans_dst++;
                sc_trans_src++;
                {
                    u16 v = *sc_trans_src;
                    *sc_trans_dst = v;
                }
                sc_trans_dst++;
                sc_trans_src++;
            } while ((u16)k < 32);
        }
        dst += 0x200;
        sc_trans_dst = dst;
    }
}



void sc_chr_sheet_trans(chr, pos, w, h)
u16 chr;
u16 pos;
u16 w;
u16 h;
{
    s32 i, j, k;
    u8* src;
    u16* dst;
    sc_trans_src = (u8*)&sc_chr_data[chr * 32 / 2];
    sc_trans_dst = (u16*)(pos * 64 + (SS_RAM + 0x8000));
    dst = sc_trans_dst;
    src = sc_trans_src;
    i = 0;
    for (; (u16)i < h; i++) {
        for (j = 0; (u16)j < w; j++) {
            k = 0;
            do {
                k += 2;
                {
                    u16 v = *sc_trans_src;
                    *sc_trans_dst = v;
                }
                sc_trans_dst++;
                sc_trans_src++;
                {
                    u16 v = *sc_trans_src;
                    *sc_trans_dst = v;
                }
                sc_trans_dst++;
                sc_trans_src++;
            } while ((u16)k < 32);
        }
        src += 0x200;
        sc_trans_src = src;
        dst = sc_trans_dst = dst + 0x200;
    }
}



void scfont_sqput(x, y, w, h, attr, code)
s16 x;
s16 y;
u16 w;
u16 h;
u16 attr;
s16 code;
{
    u16 row;
    u16 col;

    for (row = 0; row < h; row++) {
        for (col = 0; col < w; col++) {
            tilemap_put_cell(x + col, y + row, attr, code + row * 16 + col);
        }
    }
}



void scfont_sqput_rev(x, y, w, h, attr, code)
s16 x;
s16 y;
u16 w;
u16 h;
s16 attr;
s16 code; {
    u16 i;
    u16 j;
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            tilemap_put_cell(x + w - 1 - i, y + j, attr + 0x80, code + j * 16 + i);
        }
    }
}



void scfont_lnput(x, y, w, h, attr, code)
s16 x;
s16 y;
u16 w;
u16 h;
s16 attr;
s16 code;
{
    u16 row;
    u16 col;
    s16 n;

    n = 0;
    for (row = 0; row < h; row++) {
        for (col = 0; col < w; col++) {
            tilemap_put_cell(x + col, (s16)(y + row), attr, code + n);
            n++;
        }
    }
}



void scfont_lnput_rev(x, y, w, h, attr, code)
s16 x;
s16 y;
u16 w;
u16 h;
s16 attr;
s16 code;
{
    u16 row;
    u16 col;
    s16 n;

    n = 0;
    for (row = 0; row < h; row++) {
        for (col = 0; col < w; col++) {
            tilemap_put_cell(x + w - 1 - col, y + row, attr + 0x80, code + n);
            n++;
        }
    }
}



void scfont_fill(s16 x, s16 y, u16 w, u16 h, s16 attr, s16 code) {
    u16 i;
    u16 j;
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            tilemap_put_cell(x + i, y + j, attr, code);
        }
    }
}




void sc_chr_clear(pos, n)
u16 pos;
u16 n;
{
    u16 i;
    u16 k;
    u8* blank;
    sc_trans_src = (u8*)&sc_chr_data[0x20 * 16];       /* character 0x20, the blank */
    blank = sc_trans_src;
    sc_trans_dst = (u16*)((SS_RAM + 0x8000) + pos * 64);
    for (i = 0; i < n; i++) {
        for (k = 0; k < 16; k++) {
            *sc_trans_dst = *sc_trans_src;
            sc_trans_dst++;
            sc_trans_src++;
            *sc_trans_dst = *sc_trans_src;
            sc_trans_dst++;
            sc_trans_src++;
        }
        sc_trans_src = blank;
    }
}



void sc_chr_to_ram(u16 n) {
    s32 i;
    for (i = 0; i < n; i++) {
        *sc_bak_ptr = *sc_trans_src;
        sc_bak_ptr++;
        sc_trans_src++;
    }
}



void Ranking_00_6th(s8 flag) {
    s32 n;
    if (flag) {
        sc_trans_dst = (u16*)(SS_RAM + 0xB580);
        sc_bak_ptr = &sc_chr_bak[0];
        sc_chr_save(10);
        sc_trans_dst = (u16*)(SS_RAM + 0xB980);
        sc_bak_ptr = &sc_chr_bak[320];
        sc_chr_save(10);
    }
    sc_trans_src = (u8*)sc_chr_data;
    sc_trans_dst = (u16*)(SS_RAM + 0x8000);
    for (n = 0; n < 0x2800; n++) {
        sc_trans_word = 0;
        sc_trans_word = *sc_trans_src;
        *sc_trans_dst = sc_trans_word;
        sc_trans_dst++;
        sc_trans_src++;
    }
    if (flag) {
        sc_trans_dst = (u16*)(SS_RAM + 0xB580);
        sc_bak_ptr = &sc_chr_bak[0];
        sc_chr_load(10);
        sc_trans_dst = (u16*)(SS_RAM + 0xB980);
        sc_bak_ptr = &sc_chr_bak[320];
        sc_chr_load(10);
    }
}



s32 ToneDown(s8 tone) {
    const TONE_ENTRY* e = (const TONE_ENTRY*)((const s8*)tone_down_tbl + (s8)(tone * sizeof(TONE_ENTRY)));
    sc_trans_src = (u8*)sc_chr_data + e->chr * 32;
    sc_trans_dst = (u16*)((SS_RAM + 0x8000) + e->pos * 64);
    return sc_chr_trans(e->n);
}







s32 tilemap_put_cell(u16 x, u16 y, u16 attr, u16 code) {
    u16* cell = (u16*)(SS_RAM + x * 4 + y * 0x100);
    cell[0] = code;
    cell[1] = ((code & 0x100) >> 8) | attr;
}



void score8x16_put(u16 x, u16 y, u16 attr, u16 code) {
    code += 0x60;
    tilemap_put_cell(x, y, attr, code);
    tilemap_put_cell(x, y + 1, attr, code + 0x10);
}



void score16x24_put(u16 x, u16 y, u16 attr, s32 n) {
    s32 code = n * 6 + 0x140;
    tilemap_put_cell(x, y, attr, code);
    tilemap_put_cell(x + 1, y, attr, code + 1);
    tilemap_put_cell(x, y + 1, attr, code + 2);
    tilemap_put_cell(x + 1, y + 1, attr, code + 3);
    tilemap_put_cell(x, y + 2, attr, code + 4);
    tilemap_put_cell(x + 1, y + 2, attr, code + 5);
}



void sc_celllist_put(u8 ix) {
    const CELL_ENTRY* const* tbl = sc_celllist_tbl + ix;
    const CELL_ENTRY* p = *tbl;
    u16 x;
    for (x = p->x; x != 100; x = p->x) {
        tilemap_put_cell(p->x, p->y, p->attr, p->code);
        p++;
    }
}



void sc_celllist_put_scr(u8 ix) {
    const CELL_ENTRY* const* tbl = sc_celllist_tbl + ix;
    s8 k = sc_celllist_scr_tbl[ix];
    const CELL_ENTRY* p = *tbl;
    u16 x;
    for (x = p->x; x != 100; x = p->x) {
        tilemap_put_cell(DE_X[k] + p->x, p->y, p->attr, p->code);
        p++;
    }
}



void sc_celllist_put_pos(u8 kind, u8 dx, u8 dy) {
    const CELL_ENTRY* const* tbl = sc_celllist_tbl + kind;
    s8 k = sc_celllist_scr_tbl[kind];
    const CELL_ENTRY* p = *tbl;
    u16 x;
    for (x = p->x; x != 100; x = p->x) {
        tilemap_put_cell(DE_X[k] + p->x + dx, p->y + dy, p->attr, p->code);
        p++;
    }
}



void sc_attr_put(u16 x, u16 y, u16 attr) {
    u16* cell = (u16*)(SS_RAM + x * 4 + y * 0x100);
    cell[1] = (cell[0] & 1) | attr;
}



void player_name_trans(void) {
    u16 i;
    sc_trans_dst = (u16*)(SS_RAM + 0x8840);
    for (i = 0; i < 2; i++) {
        sc_trans_src = (u8*)(sc_player_name_chr_tbl[My_char[i] & 0x7F] * 32 + (s32)sc_chr_data);
        sc_chr_trans(6);
        sc_trans_dst = (u16*)(SS_RAM + 0x89C0);
    }
}



void player_name(void) {
    u16 i;
    u16 x1;
    s16 y1;
    u16 x2;
    s16 y2;
    player_name_trans();
    if (Game_setting.mode == 0) {
        x1 = 2;
        y1 = 1;
        x2 = 40;
        y2 = 1;
    } else {
        x1 = 2;
        y1 = 1;
        x2 = 54;
        y2 = 1;
    }
    for (i = 0; i < 6; i++) {
        tilemap_put_cell(x1 + i, y1, 20, i + 33);
    }
    for (i = 0; i < 6; i++) {
        tilemap_put_cell(x2 + i, y2, 20, i + 39);
    }
}



void sa_number_trans(void) {
    sc_trans_dst = (u16*)(SS_RAM + 0xCD00);
    sc_trans_src = (u8*)sc_chr_data + 0x13600;
    sc_chr_trans(12);
}

void sa_number_put(void) {
    u16 x1, y1, x2, y2;
    s8 arts;
    sa_number_trans();
    if (Game_setting.mode == 0) {
        x1 = 0;
        y1 = 0;
        x2 = 46;
        y2 = 0;
    } else {
        x1 = 0;
        y1 = 0;
        x2 = 60;
        y2 = 0;
    }
    if (My_char[0] & 0x7F) {
        scfont_lnput(x1, y1, 2, 2, sa_number_attr_tbl[arts], (arts = Super_Arts[0]) * 4 + 0x134);
    }
    if (My_char[1] & 0x7F) {
        scfont_lnput(x2, y2, 2, 2, sa_number_attr_tbl[arts], (arts = Super_Arts[1]) * 4 + 0x134);
    }
}



void stun_mark_put(s8 pl) {
    u16 i;
    const s16* pos = &smark_pos_tbl[My_char[pl] & 0x7F][pl][Game_setting.mode];
    s16 code = smark_kind_tbl[My_char[pl] & 0x7F] * 6;
    for (i = 0; i < smark_kind_tbl[My_char[pl] & 0x7F] + 6; i++) {
        tilemap_put_cell(*pos + i, 3, 2, code + i + 49);
    }
}




void max_mark_chr_trans(pl, n)
s8 pl;
s16 n;
{
    sc_trans_dst = (u16*)((SS_RAM + 0xB400) + pl * 0x400);
    sc_trans_src = (u8*)sc_chr_data + ((n * 6 + 0x680) << 5);
    sc_chr_trans(6);
}



void tilemap_clear_rect(x0, y0, x1, y1)
    u32 x0;
    u32 y0;
    u32 x1;
    u32 y1;
{
    u16 *line;
    u16 row;
    u16 col;

    line = (u16 *)(SS_RAM + (u16)x0 * 4 + (u16)y0 * 0x100);
    for (row = 0; row < (u16)y1 - (u16)y0 + 1; row++) {
        for (col = 0; col < (u16)x1 - (u16)x0 + 1; col++) {
            line[col * 2] = 0x20;
            line[col * 2 + 1] = 0;
        }
        line += 0x80;
    }
}



void bcount_mark_trans(u8 mode) {
    sc_trans_dst = (u16*)(SS_RAM + 0xE000);
    sc_trans_src = (u8*)sc_chr_data + bcount_mark_chr[mode] * 32;
    sc_chr_trans(128);
    if (mode == 0) {
        sc_celllist_put_scr(11);
    } else {
        sc_celllist_put_scr(6);
    }
}




void bcount_digit_trans(u8 mode, u16 top, u16 bottom) {
    sc_trans_src = (u8*)(sc_chr_data + top * 96 + 0xBC00);
    switch (mode) {
    case 0:
        sc_trans_dst = (u16*)(SS_RAM + 0xBC00);
        sc_chr_trans(6);
        break;
    case 1:
        sc_bak_ptr = &sc_chr_ram[0x1E00];
        sc_chr_to_ram(192);
        break;
    }
    sc_trans_src = (u8*)(sc_chr_data + bottom * 96 + 0xBC00);
    switch (mode) {
    case 0:
        sc_trans_dst = (u16*)(SS_RAM + 0xBD80);
        sc_chr_trans(6);
        break;
    case 1:
        sc_bak_ptr = &sc_chr_ram[0x1EC0];
        sc_chr_to_ram(192);
        break;
    }
}



void sa_stock_chr_trans(s8 pl, s16 n) {
    sc_trans_dst = (u16*)((SS_RAM + 0xB400) + pl * 0x400);
    sc_trans_src = (u8*)(sc_chr_data + n * 64 + 0x9600);
    sc_chr_trans(6);
}






void win_mark_put(s16 pl, u16 n, s16 attr) {
    const s16* e;
    sc_trans_src = (u8*)&sc_chr_data[n * 32] + 0xBDC0;
    sc_trans_dst = (u16*)((SS_RAM + 0x8400) + pl * 128);
    sc_chr_trans(2);
    e = &vmark_tbl[pl * 6];
    tilemap_put_cell(e[0] + DE_X[3], e[1], attr, e[2]);
    tilemap_put_cell(e[3] + DE_X[3], e[4], attr, e[5]);
}



void naming_set(s8 pl, s16 place, u16 chr) {
    sc_trans_src = (u8*)&sc_chr_data[chr * 32] + 0x7400;
    sc_trans_dst = (u16*)(SS_RAM + 0xB580 + pl * 0x400 + place * 0x80);
    sc_chr_trans(2);
}



void winner_name_put(s8 ch) {
    const u16 *p = (const u16*)&nwdata_tbl[ch];
    sc_chr_block_trans(p[0], 0x180, p[1], p[2]);
    sc_chr_block_trans(0x15A4, 0x1C0, 10, 4);
    scfont_sqput(p[3] + DE_X[0], p[4], p[1], p[2], 44, 0x180);
    scfont_sqput(DE_X[0] + p[5], p[6], 10, 4, 44, 0x1C0);
}



void player_face_char_set(void) {
    sc_chr_block_trans((My_char[0] & 0x7F) * 8 + 0x2EA, 0x100, 4, 2);
    if ((My_char[1] & 0x7F) == 0) {
        sc_chr_block_trans(0x352, 0x104, 4, 2);
    } else {
        sc_chr_block_trans((My_char[1] & 0x7F) * 8 + 0x2EA, 0x104, 4, 2);
    }
}



void player_face(void) {
    u16 x1, y1, x2, y2;
    player_face_char_set();
    if (Game_setting.mode == 0) {
        x1 = 1;
        y1 = 3;
        x2 = 43;
        y2 = 3;
    } else {
        x1 = 3;
        y1 = 3;
        x2 = 55;
        y2 = 3;
    }
    polygon2d_submit_quad(0x027E5000 + (My_char[0] & 0x7F) * 0xC0 + Player_Color[0] * 32, 0x3FC00, 32, 0, 0, 0);
    polygon2d_submit_quad(0x027E5000 + (My_char[1] & 0x7F) * 0xC0 + Player_Color[1] * 32, 0x3FE00, 32, 0, 0, 0);
    scfont_sqput_rev(x1, y1, 4, 2, 0, 0x100);
    scfont_sqput(x2, y2, 4, 2, 32, 0x104);
}



u32 SF3_logo(s16 y) {
    scfont_sqput(DE_X[3] + 19, y + 12, 10, 2, 22, 214);
}



void break_into_banner_trans(s16 kind) {
    switch (kind) {
    case 0:
        sc_chr_clear(320, 192);
        sc_celllist_put_pos(12, 0, Text_Page_Y);
        ToneDown(4);
        break;
    default:
        sc_trans_src = (u8*)sc_chr_data + (kind - 1) * 128 + 0x26000;
        sc_trans_dst = (u16*)(SS_RAM + 0xD000 + (kind - 1) * 256);
        sc_chr_trans(4);
        break;
    }
}



void combo_message_set(s8 pl, s8 kind) {
    const u16* fr = combo_mtbl[kind].v;
    u16 y = pl * 2 + 30;
    s32 code;
    sc_chr_sheet_trans(fr[0], code = pl * 32 + 0x140, fr[1], fr[2]);
    scfont_sqput((u16)combo_mpos_tbl[kind][pl], y, fr[1], fr[2], 38, code);
    tilemap_put_cell(combo_mclr_pos_tbl[kind][pl], y, 22, 32);
    tilemap_put_cell(combo_mclr_pos_tbl[kind][pl], y + 1, 22, 32);
}



void combo_hitnum_set(s8 pl, s8 kind, u16 hits) {
    s16 x = combo_hitpos_tbl[kind][pl];
    s16 y = pl * 2 + 30;
    u16 tens = hits / 10;
    u16 ones = hits - tens * 10;
    if (tens != 0) {
        tilemap_put_cell(x, y, 12, tens + 96);
        tilemap_put_cell(x, y + 1, 12, tens + 112);
    } else {
        tilemap_put_cell(x, y, 12, 32);
        tilemap_put_cell(x, y + 1, 12, 32);
    }
    tilemap_put_cell(x + 1, y, 12, ones + 96);
    tilemap_put_cell(x + 1, y + 1, 12, ones + 112);
    tilemap_put_cell(x + 2, y, 12, 32);
    tilemap_put_cell(x + 2, y + 1, 12, 32);
}



s16 combo_pts_set(s8 PL, u32 pts) {
    u32 number = pts;
    s16 digit[4];
    s16 i;
    s16 first;
    s32 xx;
    u16 x;
    s16 y;
    s16 y2;
    s16 x2;
    xx = 100000;
    first = -1;
    for (i = 3; i >= 0; i--, xx = xx / 10) {
        digit[i] = number / xx;
        number -= digit[i] * xx;
        if (first < 0) {
            if (digit[i] != 0) {
                first = i;
            }
        }
    }
    x = (15 - first) * PL;
    y = PL * 2 + 34;
    for (i = first; i >= 0; i--, x++) {
        score8x16_put(x, y, 12, digit[i]);
    }
    score8x16_put(x, y, 12, 0);
    score8x16_put(x + 1, y, 12, 0);
    tilemap_put_cell(x + 2, y, 22, 32);
    tilemap_put_cell(x + 2, y2 = y + 1, 22, 0xBE);
    tilemap_put_cell(x + 3, y, 22, 32);
    tilemap_put_cell(x + 3, y2, 22, 0xBF);
    if (PL == 0) {
        tilemap_put_cell(x2 = x + 4, y, 22, 32);
        tilemap_put_cell(x2, y2, 22, 32);
    } else {
        tilemap_put_cell(x2 = 14 - first, y, 22, 32);
        tilemap_put_cell(x2, y2, 22, 32);
    }
    return first + 6;
}



void combo_window_slide(s8 pl, s16 x, s16 y, s16 n) {
    u32* src = (u32*)(SS_RAM + ((y * 4 + pl * 2 + 30) << 8) + ((pl * 19) << 2));
    u32* dst = (u32*)(x * 4 + y * 0x300 + (SS_RAM + 0x700));
    s32 d;
    u16 i;
    d = (pl == 0) ? 1 : -1;
    for (i = 0; i < n + 1; i++) {
        dst[0] = src[0];
        *(u32*)((s32)dst + 0x100) = src[0x40];
        dst += d;
        src += d;
    }
}



void combo_window_erase(s8 col, s8 kind, s16 row) {
    u32* cell = (u32*)((SS_RAM + 0x700) + combo_erase_pos_tbl[Game_setting.mode][kind][col] * 4 + row * 0x300);
    u16 i;
    for (i = 0; i < combo_erase_len_tbl[kind]; i++) {
        cell[0] = 0x200000;
        cell[0x40] = 0x200000;
        cell++;
    }
}



void combo_window_all_clear(void) {
    u32 *cell = (u32*)(SS_RAM + 0x700);
    u16 width;
    u16 x, y;
    if (Game_setting.mode == 0) {
        width = 48;
    } else {
        width = 62;
    }
    for (x = 0; x < width; x++) {
        for (y = 0; y < 5; y++) {
            *(u32*)((s32)cell + y * 0x100) = 0x200000;
        }
        cell++;
    }
}



void sc_vram_to_ram(void) {
    sc_trans_dst = (u16*)(SS_RAM + 0x8000);
    sc_bak_ptr = sc_chr_ram;
    sc_chr_save(0x200);
}
