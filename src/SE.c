/*
 * SE.C  Screen wipe patterns
 *
 * The wipe routines (wipe_pattern_*, mix_or_* / mix_put_*, mix_or_step)
 * OR or AND one step of a wipe-out or wipe-in pattern into the fix-layer character graphics, column
 * by column; Switch_Screen and Switch_Screen_Revival in SYS_sub call them.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "se_3.h"
#include "SE.h"
#include "cps3.h"

u16 * wipe_dst_ptr;  /* 0200EED4 */
u8 * wipe_back_ptr;  /* 0200EED8 */
const u8 * wipe_pat_top;  /* 0200EEDC */
const u8 * wipe_pat_ptr;  /* 0200EEE0 */

void mix_or_128(void);

void mix_put_128(void);



/* provisional name */
void wipe_pattern_or_cols(s16 kind, s16 row) {
    const u8* src;
    const u8* map;
    u16* dst;
    s16 x;
    s16 y;
    src = wipe_column_tbl[kind].adr;
    src += wipe_column_tbl[kind].w * row;
    map = wipe_set_pattern_tbl[kind].adr;
    map += row * 32;
    dst = (u16*)(SS_RAM + 0x8000);
    for (y = 0; y < 400; y++, dst += 32) {
        for (x = 0; x < wipe_column_tbl[kind].w; x++) {
            dst[src[x]] |= map[src[x]];
        }
    }
}



/* provisional name */
void wipe_pattern_restore_cols(s16 kind, s16 row) {
    const u8* src;
    const u8* map;
    u8* cell;
    u32 dst;
    s16 x;
    s16 y;
    src = wipe_column_tbl[kind].adr;
    src += wipe_column_tbl[kind].w * row;
    map = wipe_clear_pattern_tbl[kind].adr;
    cell = sc_chr_ram;
    map += row * 32;
    dst = (SS_RAM + 0x8000);
    for (y = 0; y < 400; y++) {
        for (x = 0; x < wipe_column_tbl[kind].w; x++) {
            *(u16*)(dst + src[x] * 2U) = cell[src[x]] | map[src[x]];
        }
        dst += 64;
        cell += 32;
    }
}



/* provisional name */
void wipe_pattern_set_512(s16 kind, s16 row, s16 mix) {
    wipe_pat_top = wipe_set_pattern_tbl[kind].adr;
    if (mix) {
        wipe_pat_top = wipe_clear_pattern_tbl[kind].adr;
    }
    wipe_pat_top += row * 32;
    wipe_dst_ptr = (u16*)(SS_RAM + 0x8000);
    if (!mix) {
        mix_or_512();
    } else {
        wipe_back_ptr = sc_chr_ram;
        mix_put_512();
    }
}



/* provisional name */
void mix_or_512(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 512; i++) {
        wipe_pat_ptr = wipe_pat_top;
        for (j = 0; j < 32; j++) {
            *wipe_dst_ptr = *wipe_pat_ptr | *wipe_dst_ptr;
            wipe_dst_ptr++;
            wipe_pat_ptr++;
        }
    }
}



/* provisional name */
void mix_put_512(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 512; i++) {
        wipe_pat_ptr = wipe_pat_top;
        for (j = 0; j < 32; j++) {
            *wipe_dst_ptr = *wipe_back_ptr | *wipe_pat_ptr;
            wipe_dst_ptr++;
            wipe_pat_ptr++;
            wipe_back_ptr++;
        }
    }
}



/* provisional name */
void wipe_pattern_set(s16 kind, s16 row, s16 mix) {
    wipe_pat_top = wipe_set_pattern_tbl[kind].adr;
    if (mix) {
        wipe_pat_top = wipe_clear_pattern_tbl[kind].adr;
    }
    wipe_pat_top += row * 32;
    wipe_dst_ptr = (u16*)(SS_RAM + 0x8000);
    if (!mix) {
        mix_or_128();
    } else {
        wipe_back_ptr = sc_chr_ram;
        mix_put_128();
    }
}



/* provisional name */
void mix_or_128(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 128; i++) {
        wipe_pat_ptr = wipe_pat_top;
        for (j = 0; j < 32; j++) {
            *wipe_dst_ptr = *wipe_pat_ptr | *wipe_dst_ptr;
            wipe_dst_ptr++;
            wipe_pat_ptr++;
        }
    }
}



/* provisional name */
void mix_put_128(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 128; i++) {
        wipe_pat_ptr = wipe_pat_top;
        for (j = 0; j < 32; j++) {
            *wipe_dst_ptr = *wipe_back_ptr | *wipe_pat_ptr;
            wipe_dst_ptr++;
            wipe_pat_ptr++;
            wipe_back_ptr++;
        }
    }
}


/* provisional name */
void mix_or_step(void) {
    *wipe_dst_ptr = *wipe_dst_ptr | *wipe_pat_ptr;
    wipe_dst_ptr++;
    wipe_pat_ptr++;
}
