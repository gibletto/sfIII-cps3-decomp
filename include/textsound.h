#ifndef TEXTSOUND_H
#define TEXTSOUND_H

#include "structs.h"

void tilemap_put_char(u16 x, u16 y, u16 attr, u16 code);
void tilemap_rect_fill(u16 x, u16 y, u16 w, u16 h, u16 attr, u16 code);
void tilemap_fill_column0(u16 attr, u16 code);
void palette_write(s32 offset, const u16 *src, s32 count);
void palette_bank_set(s32 offset);
u16* tilemap_put_block_next(u16* p, u16 attr, u16 code);
void tilemap_fill_all(u16 attr, u16 code);
void tilemap_print_binary(u16 x, u16 y, u16 attr, const s8* data, u16 n);
void tilemap_print_script_seq(u16 x, u16 y, u16 pal, const TMSCRIPT* scr);
void tilemap_print_hex_block(u16 x, u16 y, u16 attr, u32 value, u16 digits, u16 mode);
void tilemap_print_string(u16 x, u16 y, u16 attr, const TM_STRING* sc);
void tilemap_print_string_attr(u16 x, u16 y, u16 attr, const s8* str);
void tilemap_chunk_copy_16b(s16 *dst, char *src, s32 chunks);
void tilemap_print_hex(u16 x, u16 y, u16 attr, u32 value, u16 digits, u16 mode);

#endif
