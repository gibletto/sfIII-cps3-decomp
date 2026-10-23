#ifndef SC_TRANS_H
#define SC_TRANS_H

#include "structs.h"

s32 sc_chr_trans();
void sc_chr_save(u16 rows);
void sc_chr_load(u16 rows);
void sc_chr_block_trans();
void sc_chr_sheet_trans();
void scfont_sqput(s16 x, s16 y, u16 w, u16 h, u16 attr, s16 code);
void scfont_sqput_rev(s16 x, s16 y, u16 w, u16 h, s16 attr, s16 code);
void scfont_fill(s16 x, s16 y, u16 w, u16 h, s16 attr, s16 code);
void sc_chr_clear();
void sc_chr_to_ram(u16 n);
void score8x16_put(u16 x, u16 y, u16 attr, u16 code);
void score16x24_put(u16 x, u16 y, u16 attr, s32 n);
void sc_celllist_put(u8 ix);
void sc_celllist_put_scr(u8 ix);
void sc_celllist_put_pos(u8 kind, u8 dx, u8 dy);
void sc_attr_put(u16 x, u16 y, u16 attr);
void player_name_trans(void);
void player_name(void);
void sa_number_trans(void);
void bcount_digit_trans(u8 mode, u16 top, u16 bottom);
void bcount_mark_trans(u8 mode);
void sa_stock_chr_trans(s8 pl, s16 n);
void win_mark_put(s16 pl, u16 n, s16 attr);
void Ranking_00_6th(s8 flag);
s32 ToneDown(s8 tone);
void scfont_lnput(s16 x, s16 y, u16 w, u16 h, s16 attr, s16 code);
void scfont_lnput_rev(s16 x, s16 y, u16 w, u16 h, s16 attr, s16 code);
s32 tilemap_put_cell(u16 x, u16 y, u16 attr, u16 code);
void winner_name_put(s8 chr);
void player_face_char_set();
void player_face(void);
void naming_set(s8 pl, s16 place, u16 chr);

#endif
