/*
 * TEXTSOUND.C  Text layer printing
 *
 * Text layer routines used by test mode, menus and messages: tilemap_chunk_copy_16b loads font
 * characters, tilemap_fill_all / tilemap_rect_fill clear areas, and the print routines put characters,
 * strings (with attribute), script sequences, hex digits and binary numbers. palette_bank_set and
 * palette_write select and fill the colour RAM bank; tilemap_fill_column0 fills the first column of
 * every row. The module is compiled without optimization; its locals are register variables.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sound_voice.h"
#include "sound_voice_2.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "textsound.h"
#include "cps3.h"

u16 num_font_code;  /* 0206CDC4 */
u32 palette_base;  /* 0206CDC8 */


void tilemap_chunk_copy_16b(s16 *dst, char *src, s32 chunks)
{
    register s32 j;
    register s32 i;
    for (i = 0; i < chunks; i++) {
        for (j = 0; j < 32; j++) {
            *dst = *src;
            dst++;
            src++;
        }
    }
}

/* provisional name */
void palette_bank_set(s32 offset)
{
    palette_base = offset + COLOR_RAM;
    *(volatile u16 *)(SS_REG + 0x24) = (palette_base >> 10) & 0xFF;
}

/* provisional name */
void palette_write(s32 offset, const u16 *src, s32 count)
{
    register s32 i;
    register u16 *dst;
    dst = (u16 *)(offset + (s32)palette_base);
    for (i = 0; i < count; i++) {
        if (*src != 0xFFFF) {
            *dst = *src;
        }
        src++;
        dst++;
    }
}



/* provisional name */
void tilemap_fill_all(u16 attr, u16 code) {
    register u16* p;
    register u16 v;
    if (attr == 0xFFFF && code == 0xFFFF) {
        return;
    }
    if (attr != 0xFFFF && code == 0xFFFF) {
        for (p = (u16*)SS_RAM; p < (u16*)(SS_RAM + 0x3FFF); p += 2) {
            p[1] = (p[1] & 1) | attr;
        }
    } else if (attr == 0xFFFF && code != 0xFFFF) {
        v = (code & 0x100) >> 8;
        for (p = (u16*)SS_RAM; p < (u16*)(SS_RAM + 0x3FFF); p += 2) {
            p[0] = code;
            p[1] = (p[1] & 0xFFFE) | v;
        }
    } else {
        v = ((code & 0x100) >> 8) | attr;
        for (p = (u16*)SS_RAM; p < (u16*)(SS_RAM + 0x3FFF); p += 2) {
            p[0] = code;
            p[1] = v;
        }
    }
}



/* provisional name */
void tilemap_put_block(x, y, attr, code)
u16 x;
u16 y;
u16 attr;
u16 code;
{
    register u16* p;
    register u32 w;
    register u32 h;
    register u32 j;
    register u32 i;
    w = ((code & 0x0E00) >> 9) + 1;
    h = ((code & 0x7000) >> 12) + 1;
    p = (u16*)((x << 2) + (y << 8) + SS_RAM);
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            p[0] = code;
            p[1] = attr | ((code & 0x100) >> 8);
            code++;
            p += 2;
            if (p > (u16*)(SS_RAM + 0x3FFF)) {
                p = (u16*)SS_RAM;
            }
        }
        p += 128 - w * 2;
        if (p > (u16*)(SS_RAM + 0x3FFF)) {
            p = (u16*)SS_RAM;
        }
    }
}



/* provisional name */
u16* tilemap_put_block_next(u16* p, u16 attr, u16 code) {
    register u32 w;
    register u32 h;
    register u32 j;
    register u32 i;
    w = ((code & 0x0E00) >> 9) + 1;
    h = ((code & 0x7000) >> 12) + 1;
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            p[0] = code;
            *(u16*)((u8*)p + 2) = attr | ((code & 0x100) >> 8);
            code++;
            p += 2;
            if (p > (u16*)(SS_RAM + 0x3FFF)) {
                p = (u16*)SS_RAM;
            }
        }
        p += 128 - w * 2;
        if (p > (u16*)(SS_RAM + 0x3FFF)) {
            p = (u16*)SS_RAM;
        }
    }
    p += w << 1;
    p -= h << 7;
    if (p > (u16*)(SS_RAM + 0x3FFF)) {
        p = (u16*)SS_RAM;
    }
    return p;
}



/* provisional name */
void tilemap_put_char(u16 x, u16 y, u16 attr, u16 code) {
    register u16* cell;
    cell = (u16*)((x << 2) + (y << 8) + SS_RAM);
    cell[0] = code;
    cell[1] = ((code & 0x100) >> 8) | attr;
}



/* provisional name */
void tilemap_print_string_attr(u16 x, u16 y, u16 attr, const s8* str) {
    register u16* p;
    p = (u16*)((x << 2) + (y << 8) + SS_RAM);
    while (*str != 0) {
        p[0] = *str;
        p[1] = attr;
        p += 2;
        if (p > (u16*)(SS_RAM + 0x3FFF)) {
            p = (u16*)SS_RAM;
        }
        str++;
    }
}



/* provisional name */
void tilemap_rect_fill(u16 x, u16 y, u16 w, u16 h, u16 attr, u16 code) {
    register u16* p;
    register s32 col;
    register s32 row;
    register s32 skip;
    if (attr == 0xFFFF && code == 0xFFFF) {
        return;
    }
    p = (u16*)((x << 2) + (y << 8) + SS_RAM);
    skip = 0x80 - w * 2;
    if (attr != 0xFFFF && code == 0xFFFF) {
        for (row = 0; row < h; row++) {
            for (col = 0; col < w; col++) {
                p[1] = (p[1] & 1) | attr;
                p += 2;
                if (p > (u16*)(SS_RAM + 0x3FFF)) {
                    p = (u16*)SS_RAM;
                }
            }
            p += skip;
            if (p > (u16*)(SS_RAM + 0x3FFF)) {
                p = (u16*)SS_RAM;
            }
        }
    } else if (attr == 0xFFFF && code != 0xFFFF) {
        for (row = 0; row < h; row++) {
            for (col = 0; col < w; col++) {
                p[0] = code;
                p[1] = (p[1] & 0xFFFE) | ((code & 0x100) >> 8);
                p += 2;
                if (p > (u16*)(SS_RAM + 0x3FFF)) {
                    p = (u16*)SS_RAM;
                }
            }
            p += skip;
            if (p > (u16*)(SS_RAM + 0x3FFF)) {
                p = (u16*)SS_RAM;
            }
        }
    } else {
        for (row = 0; row < h; row++) {
            for (col = 0; col < w; col++) {
                p[0] = code;
                p[1] = attr | ((code & 0x100) >> 8);
                p += 2;
                if (p > (u16*)(SS_RAM + 0x3FFF)) {
                    p = (u16*)SS_RAM;
                }
            }
            p += skip;
            if (p > (u16*)(SS_RAM + 0x3FFF)) {
                p = (u16*)SS_RAM;
            }
        }
    }
}



/* provisional name */
void tilemap_print_hex_block(u16 x, u16 y, u16 attr, u32 value, u16 digits, u16 mode) {
    register u16* p;
    register u32 mask;
    register s32 i;
    s32 cells;
    s32 started;
    u16 d;
    cells = (((num_font_code & 0x7000) >> 12) + 1) * (((num_font_code & 0xE00) >> 9) + 1);
    p = (u16*)((x << 2) + (y << 8) + SS_RAM);
    started = 0;
    mask = 15 << ((digits - 1) * 4);
    for (i = digits; i > 0; i--) {
        d = (value & mask) >> ((i - 1) * 4);
        if (i == digits && (mode & 4)) {
            if (d < 0) {
                p[0] = '-';
                d &= 0x7FFF;
            } else {
                p[0] = '+';
            }
            p[1] = attr;
            p += 2;
        }
        if (started == 0) {
            if (d == 0) {
                if (i == 1) {
                    p = tilemap_put_block_next(p, attr, cells * d + num_font_code);
                } else {
                    switch (mode & 3) {
                    case 1:
                        p[0] = ' ';
                        p[1] = attr;
                    case 2:
                        p += 2;
                    case 3:
                        break;
                    default:
                        p = tilemap_put_block_next(p, attr, cells * d + num_font_code);
                        break;
                    }
                }
            } else {
                started = 1;
                p = tilemap_put_block_next(p, attr, cells * d + num_font_code);
            }
        } else {
            p = tilemap_put_block_next(p, attr, cells * d + num_font_code);
        }
        if (p > (u16*)(SS_RAM + 0x3FFF)) {
            p = (u16*)SS_RAM;
        }
        mask >>= 4;
    }
}



/* provisional name */
void tilemap_print_hex(u16 x, u16 y, u16 attr, u32 value, u16 digits, u16 mode) {
    register u16* p;
    register u32 mask;
    register s32 i;
    s32 started;
    u16 d;
    p = (u16*)((x << 2) + (y << 8) + SS_RAM);
    started = 0;
    mask = 15 << ((digits - 1) * 4);
    for (i = digits; i > 0; i--) {
        d = (value & mask) >> ((i - 1) * 4);
        if (i == digits && (mode & 4)) {
            if (d < 0) {
                p[0] = '-';
                d &= 0x7FFF;
            } else {
                p[0] = '+';
            }
            p[1] = attr;
            p += 2;
        }
        if (started == 0) {
            if (d == 0) {
                if (i == 1) {
                    p[0] = d;
                    p[1] = attr;
                } else {
                    switch (mode & 3) {
                    case 1:
                        p[0] = ' ';
                        p[1] = attr;
                    case 2:
                        p += 2;
                    case 3:
                        break;
                    default:
                        p[0] = d;
                        p[1] = attr;
                        p += 2;
                        break;
                    }
                }
            } else {
                started = 1;
                p[0] = d;
                p[1] = attr;
                p += 2;
            }
        } else {
            p[0] = d;
            p[1] = attr;
            p += 2;
        }
        if (p > (u16*)(SS_RAM + 0x3FFF)) {
            p = (u16*)SS_RAM;
        }
        mask >>= 4;
    }
}



/* provisional name */
void tilemap_print_binary(u16 x, u16 y, u16 attr, const s8* data, u16 n) {
    register u16* p;
    register u32 mask;
    p = (u16*)((x << 2) + (y << 8) + SS_RAM);
    mask = 0x80;
    while (n > 0) {
        if (*data & mask) {
            p[0] = '1';
            p[1] = attr;
        } else {
            p[0] = '0';
            p[1] = attr;
        }
        p += 2;
        if (p > (u16*)(SS_RAM + 0x3FFF)) {
            p = (u16*)SS_RAM;
        }
        mask >>= 1;
        if (mask == 0) {
            mask = 0x80;
            data++;
        }
        n--;
    }
}



/* provisional name */
void tilemap_print_script_seq(u16 x, u16 y, u16 pal, const TMSCRIPT* scr) {
    register u16* dst;
    register u32 col;
    register u32 row;
    register s32 i;
    register s32 n;
    register u32 w;
    register u32 h;
    register u16 d;
    register u16 attr;
    register const u16* blk;
    register const TMLINE* line;
    u8* s;
    if (scr->kind == 0) {
        line = scr->data;
        dst = (u16*)((line->x << 2) + (line->y << 8) + SS_RAM);
        if (x + y != 0) {
            dst += x * 2 + y * 128;
        }
        for (s = line->str; *s != 0; s++) {
            if (*s == 10) {
                line++;
                dst = (u16*)((line->x << 2) + (line->y << 8) + SS_RAM);
                if (x + y != 0) {
                    dst += x * 2 + y * 128;
                }
                s = line->str;
            }
            dst[0] = *s;
            if (pal == 0xFFFF) {
                dst[1] = line->attr;
            } else {
                dst[1] = pal;
            }
            dst += 2;
            if (dst > (u16*)(SS_RAM + 0x3FFF)) {
                dst = (u16*)SS_RAM;
            }
        }
    } else {
        blk = scr->data;
        while (*blk != 0) {
            n = blk[0];
            attr = blk[3];
            dst = (u16*)((blk[1] << 2) + (blk[2] << 8) + SS_RAM);
            if (x + y != 0) {
                dst += x * 2 + y * 128;
            }
            blk += 4;
            for (i = 0; i < n; i++) {
                d = *blk;
                w = ((d & 0xE00) >> 9) + 1;
                h = ((d & 0x7000) >> 12) + 1;
                for (row = 0; row < h; row++) {
                    for (col = 0; col < w; col++) {
                        dst[0] = d;
                        if (pal == 0xFFFF) {
                            dst[1] = ((d & 0x100) >> 8) | attr;
                        } else {
                            dst[1] = ((d & 0x100) >> 8) | pal;
                        }
                        d++;
                        dst += 2;
                        if (dst > (u16*)(SS_RAM + 0x3FFF)) {
                            dst = (u16*)SS_RAM;
                        }
                    }
                    dst += 0x80 - (w << 1);
                    if (dst > (u16*)(SS_RAM + 0x3FFF)) {
                        dst = (u16*)SS_RAM;
                    }
                }
                dst += w << 1;
                dst -= h << 7;
                if (dst > (u16*)(SS_RAM + 0x3FFF)) {
                    dst = (u16*)SS_RAM;
                }
                blk++;
            }
        }
    }
}



/* provisional name */
void tilemap_print_string(u16 x, u16 y, u16 attr, const TM_STRING* sc) {
    register u16* p;
    register const u8* s;
    p = (u16*)((sc->x << 2) + (sc->y << 8) + SS_RAM);
    if (x + y != 0) {
        p += x * 2 + y * 128;
    }
    for (s = (const u8*)sc->str; *s != 0; s++) {
        if (*s == 10) {
            sc++;
            p = (u16*)((sc->x << 2) + (sc->y << 8) + SS_RAM);
            if (x + y != 0) {
                p += x * 2 + y * 128;
            }
            s = (const u8*)sc->str;
        }
        p[0] = *s;
        if (attr == 0xFFFF) {
            p[1] = sc->attr;
        } else {
            p[1] = attr;
        }
        p += 2;
        if (p > (u16*)(SS_RAM + 0x3FFF)) {
            p = (u16*)SS_RAM;
        }
    }
}



/* provisional name */
void tilemap_fill_column0(u16 attr, u16 code) {
    register u16* p;
    register u16 v;
    if ((system_ctrl_flag & 0x81) != 0x81) {
        return;
    }
    p = (u16*)SS_RAM;
    v = ((code & 0x100) >> 8) | attr;
    for (; p < (u16*)(SS_RAM + 0x3FFF); p += 128) {
        p[0] = code;
        p[1] = v;
    }
}


