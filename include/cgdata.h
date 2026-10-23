/*
 * CGDATA.H  Pattern (cg) data: how every sprite number is built from the graphics ROMs
 *
 * cg_data_tbl (06800000) has one entry per cg number, the number an animation frame shows (a script
 * line's `number`): the pattern's origin and its CharGfxSet, or 0 when the number is unused.
 *
 * A CharGfxSet (the cg_XXXX arrays, named after the first cg number that uses them) is three parts:
 *
 *   CG_SET(slot, size, count, cells, prep)
 *       slot   tile cache slot: patterns with the same slot share their tiles, so load_char_gfx loads them
 *              once (cg_slot_tbl); 0x8000 = no cache slot
 *       size   tile memory the pattern needs, in 32-byte units - 1 (simmram blocks of (size >> 5) + 1)
 *       count  number of CG_CHUNK lines, cells number of CG_CELL lines
 *       prep   graphics ROM address of the decompression dictionary loaded before the chunks
 *   CG_CHUNK(src, size, dst)
 *       one DMA from the graphics ROMs (simm3-6) into the pattern's tile memory: src graphics ROM word
 *       address, size in 16-byte units - 1, dst offset in 16-byte units
 *   CG_CELL(code, col, x, y, sz)
 *       one sprite placed from those tiles (CHAR_CELL): code tile number (added to the slot's address),
 *       col palette and flip bits (0x1000 flip x, 0x0800 flip y; added to the colour code), x and y from
 *       the origin, sz sprite size code (tiles wide 8/1/2/4 by the low two bits, tall by the high two)
 *
 * A few sets are followed by one CG_CELL more than their cells count; the tool that made the data left it,
 * and nothing reads it.
 */

#ifndef CGDATA_H
#define CGDATA_H

#define CG_SET(slot, size, count, cells, prep) \
    (u32)(((u32)(slot) << 16) | (size)), (u32)(((u32)(count) << 16) | (cells)), (u32)(prep)

#define CG_CHUNK(src, size, dst) (u32)(src), (u32)(((u32)(size) << 16) | (dst))

#define CG_CELL(code, col, x, y, sz) \
    (u32)(((u32)(code) << 16) | ((col) & 0xFFFF)), (u32)((((u32)(x) & 0xFFFF) << 16) | ((sz) << 12) | ((y) & 0xFFF))

#endif
