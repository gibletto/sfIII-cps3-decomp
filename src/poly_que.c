/*
 * POLY_QUE.C  Polygon transfer queue
 *
 * poly_queue_init / poly_bank_flip set up the double-buffered transfer queue for the video DMA unit,
 * polygon2d_submit_line / _quad queue transfers (sending a request directly when the unit is idle) and
 * sprite_polygon_flush_queue drains the queue.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "cps3.h"

/* video DMA status: the sprite and polygon list transfers are busy */
#define VIDEO_DMA_STATUS    (*(volatile u16*)DMA_STATUS_REG)
#define VIDEO_DMA_BUSY      6

/* polygon line list address (in CHARACTER RAM, in words) */
#define POLY_LIST_LO        (*(volatile u16*)(VIDEO_REG + 0x96))
#define POLY_LIST_HI        (*(volatile u16*)(VIDEO_REG + 0x98))

/* quad request registers */
#define POLY_QUAD_A_HI      (*(volatile u16*)(VIDEO_REG + 0xA0))
#define POLY_QUAD_A_LO      (*(volatile u16*)(VIDEO_REG + 0xA2))
#define POLY_QUAD_B_HI      (*(volatile u16*)(VIDEO_REG + 0xA4))
#define POLY_QUAD_B_LO      (*(volatile u16*)(VIDEO_REG + 0xA6))
#define POLY_QUAD_ATTR      (*(volatile u16*)(VIDEO_REG + 0xA8))
#define POLY_QUAD_PRI       (*(volatile u16*)(VIDEO_REG + 0xAA))
#define POLY_QUAD_C_LO      (*(volatile u16*)(VIDEO_REG + 0xAC))
#define POLY_QUAD_C_HI      (*(volatile u16*)(VIDEO_REG + 0xAE))    /* | POLY_QUAD_GO starts it */
#define POLY_QUAD_GO        2

#define POLY_COORD_MASK     0x1FFFFF
#define POLY_SOURCE_MASK    0x3FFFFFF

/* poly_dma_state */
#define POLY_IDLE           0
#define POLY_SENDING_LINES  1
#define POLY_SENDING_QUADS  2
#define POLY_SENDING_DIRECT 3   /* a quad sent straight to the registers */

/* poly_order_kind[] and sprite_polygon_flush_queue's kind */
#define POLY_KIND_LINE      1
#define POLY_KIND_QUAD      2

s32 poly_dma_state;  /* 0206A120 */
s16 poly_reserve0;  /* 0206A124 */
s16 poly_reserve1;  /* 0206A126 */
POLY_LINE poly_line_buf[2][POLY_LINE_MAX];  /* 0206A128 */
u32 poly_line_cnt[2];  /* 0206C120 */
u32 poly_line_rd[2];  /* 0206C128 */
POLYCMD poly_quad_buf[2][POLY_QUAD_MAX];  /* 0206C130 */
u32 poly_quad_cnt[2];  /* 0206C530 */
u32 poly_quad_rd[2];  /* 0206C538 */
u32 poly_order_pos[2];  /* 0206C540 */
u16 poly_order_kind[2][POLY_ORDER_MAX];  /* 0206C548 */
s32 poly_wr_bank;  /* 0206CB1C */
s32 poly_rd_bank;  /* 0206CB20 */


u32 poly_buf_offset = 0;  /* 02007390 */
s32 poly_cram_bank = 0;  /* 02007394 */


/* provisional name */
void poly_queue_init(s32 offset) {
    s32 unused[2];
    if (VIDEO_DMA_STATUS & VIDEO_DMA_BUSY) {
        if (VIDEO_DMA_STATUS & 2) {
            while (VIDEO_DMA_STATUS & 2) {
            }
        } else {
            while (VIDEO_DMA_STATUS & 4) {
            }
        }
    }
    poly_dma_state = POLY_IDLE;
    poly_reserve0 = 0;
    poly_reserve1 = 0;
    if (offset != -1) {
        poly_cram_bank = (offset >> 20) & 7;
        poly_buf_offset = offset;
    }
    poly_wr_bank = 0;
    poly_rd_bank = 1;
    poly_line_cnt[0] = 0;
    poly_line_cnt[1] = 0;
    poly_quad_cnt[0] = 0;
    poly_quad_cnt[1] = 0;
    poly_line_rd[0] = 0;
    poly_line_rd[1] = 0;
    poly_quad_rd[0] = 0;
    poly_quad_rd[1] = 0;
    poly_order_pos[0] = 0;
    poly_order_pos[1] = 0;
    *(volatile u16*)IRQ10_ACK = 0;
}



/* provisional name */
void poly_bank_flip(void) {
    s32 mask;
    if (poly_line_cnt[poly_wr_bank] + poly_quad_cnt[poly_wr_bank] > 0) {
        if (poly_line_cnt[(u32)poly_rd_bank] + poly_quad_cnt[(u32)poly_rd_bank] == 0) {
            mask = _builtin_get_imask();
            _builtin_set_imask(15);
            poly_wr_bank++;
            poly_wr_bank &= 1;
            poly_rd_bank++;
            poly_rd_bank &= 1;
            poly_line_cnt[poly_wr_bank] = 0;
            poly_quad_cnt[poly_wr_bank] = 0;
            poly_line_rd[poly_wr_bank] = 0;
            poly_quad_rd[poly_wr_bank] = 0;
            poly_order_pos[poly_wr_bank] = 0;
            _builtin_set_imask(mask);
        }
    }
}



/* provisional name */
s32 polygon2d_submit_line(addr, y, x, kind)
u32 addr;
u32 y;
u32 x;
u8 kind;
{
    register POLY_LINE* line;
    if (poly_line_cnt[poly_wr_bank] >= POLY_LINE_MAX) {
        return -1;
    }
    line = &poly_line_buf[poly_wr_bank][poly_line_cnt[poly_wr_bank]];
    if (kind) {
        if (kind == 3) {
            x = 127;
            y = 0;
        }
        kind++;
    }
    if (kind == 4) {
        line->w0 = (kind << 21) | (x & POLY_COORD_MASK);
    } else {
        line->w0 = (((x << 1) & POLY_COORD_MASK) | (kind << 21)) + 1;
    }
    line->w1 = (y >> 3) & POLY_COORD_MASK;
    line->w2 = addr & POLY_SOURCE_MASK;
    poly_line_cnt[poly_wr_bank]++;
    poly_order_kind[poly_wr_bank][poly_order_pos[poly_wr_bank]] = POLY_KIND_LINE;
    return 0;
}



/* provisional name */
s32 polygon2d_submit_quad(a, b, c, lo, hi, pri)
u32 a;
u32 b;
u32 c;
u16 lo;
u16 hi;
s16 pri;
{
    register POLYCMD* cmd;
    s32 unused;
    if ((VIDEO_DMA_STATUS & VIDEO_DMA_BUSY) || poly_dma_state != POLY_IDLE) {
        if (poly_quad_cnt[poly_wr_bank] >= POLY_QUAD_MAX) {
            return -1;
        }
        cmd = &poly_quad_buf[poly_wr_bank][poly_quad_cnt[poly_wr_bank]];
        cmd->a_lo = a >> 1;
        cmd->a_hi = ((a >> 1) & 0x7FF0000) >> 16;
        cmd->b_lo = b >> 1;
        cmd->b_hi = ((b >> 1) & 0x10000) >> 16;
        cmd->c_lo = c >> 1;
        cmd->c_hi = ((c >> 1) & 0x10000) >> 16;
        cmd->attr = (hi << 8 | lo) & 0x7F7F;
        cmd->pri = pri & 0x7F;
        poly_quad_cnt[poly_wr_bank]++;
        poly_order_kind[poly_wr_bank][poly_order_pos[poly_wr_bank]] = POLY_KIND_QUAD;
    } else {
        poly_dma_state = POLY_SENDING_DIRECT;
        POLY_QUAD_A_HI = ((a >> 1) & 0x7FF0000) >> 16;
        POLY_QUAD_A_LO = a >> 1;
        POLY_QUAD_B_HI = ((b >> 1) & 0x10000) >> 16;
        POLY_QUAD_B_LO = b >> 1;
        POLY_QUAD_ATTR = (hi << 8 | lo) & 0x7F7F;
        POLY_QUAD_PRI = pri & 0x7F;
        POLY_QUAD_C_LO = c >> 1;
        POLY_QUAD_C_HI = ((c >> 1) & 0x10000) >> 16 | POLY_QUAD_GO;
    }
    return 0;
}



/* provisional name */
s32 polygon2d_queue_quad(u32 a, u32 b, u32 c, u16 lo, u16 hi, s16 pri) {
    register POLYCMD* cmd;
    s32 unused;
    if (poly_quad_cnt[poly_wr_bank] >= POLY_QUAD_MAX) {
        return -1;
    }
    cmd = &poly_quad_buf[poly_wr_bank][poly_quad_cnt[poly_wr_bank]];
    cmd->a_lo = a >> 1;
    cmd->a_hi = ((a >> 1) & 0x7FF0000) >> 16;
    cmd->b_lo = b >> 1;
    cmd->b_hi = ((b >> 1) & 0x10000) >> 16;
    cmd->c_lo = c >> 1;
    cmd->c_hi = ((c >> 1) & 0x10000) >> 16;
    cmd->attr = (hi << 8 | lo) & 0x7F7F;
    cmd->pri = pri & 0x7F;
    poly_quad_cnt[poly_wr_bank]++;
    poly_order_kind[poly_wr_bank][poly_order_pos[poly_wr_bank]] = POLY_KIND_QUAD;
    return 0;
}

/* provisional name */
void sprite_poly_queue_drain_try(void)
{
    if ((VIDEO_DMA_STATUS & VIDEO_DMA_BUSY) == 0 && poly_dma_state == POLY_IDLE) {
        if (poly_line_cnt[poly_rd_bank] > 0) {
            sprite_polygon_flush_queue(POLY_KIND_LINE);
        } else if (poly_quad_cnt[poly_rd_bank] > 0) {
            sprite_polygon_flush_queue(POLY_KIND_QUAD);
        }
    }
}



/* Wait until the video DMA has finished with the sprite and polygon lists, then
   send the waiting polygon queue: the line queue if it holds entries, otherwise
   the quad queue.  A request in state 3 is simply dropped. */
/* provisional name */
void sprite_poly_queue_drain_wait(void)
{
    while (VIDEO_DMA_STATUS & VIDEO_DMA_BUSY) {
    }
    switch (poly_dma_state) {
    case POLY_SENDING_LINES:
    case POLY_SENDING_QUADS:
        poly_dma_state = POLY_IDLE;
        if (poly_line_cnt[poly_rd_bank] > 0) {
            sprite_polygon_flush_queue(POLY_KIND_LINE);
        } else if (poly_quad_cnt[poly_rd_bank] > 0) {
            sprite_polygon_flush_queue(POLY_KIND_QUAD);
        }
        break;
    case POLY_SENDING_DIRECT:
        poly_dma_state = POLY_IDLE;
    case POLY_IDLE:
    default:
        break;
    }
}



/* provisional name */
void sprite_polygon_flush_queue(s32 kind) {
    union {
        POLY_LINE* line;
        POLYCMD* quad;
    } cmd;
    POLY_LINE* out;
    s32 i;
    s32 n;
    s32 unused;
    switch (kind) {
    case POLY_KIND_LINE:
        if (poly_line_cnt[poly_rd_bank] > POLY_LINE_MAX) {
            n = POLY_LINE_MAX;
        } else {
            n = poly_line_cnt[poly_rd_bank];
        }
        out = (POLY_LINE*)((poly_buf_offset & 0xFFFFF) + CHARACTER_RAM);
        cram_bank_set(poly_cram_bank);
        for (i = 0; i < n; i++) {
            cmd.line = &poly_line_buf[poly_rd_bank][poly_line_rd[poly_rd_bank] + i];
            out[i].w0 = cmd.line->w0;
            out[i].w1 = cmd.line->w1;
            out[i].w2 = cmd.line->w2;
            poly_line_cnt[poly_rd_bank]--;
        }
        poly_line_rd[poly_rd_bank] += n;
        out[i].w0 = 0x01000000;
        out[i].w1 = 0;
        out[i].w2 = 0;
        POLY_LIST_LO = ((u32)out - CHARACTER_RAM) >> 2;
        POLY_LIST_HI = ((((u32)out - CHARACTER_RAM) >> 18) & 0x3F) | 0x40;
        cram_bank_restore();
        break;
    case POLY_KIND_QUAD:
        cmd.quad = &poly_quad_buf[poly_rd_bank][poly_quad_rd[poly_rd_bank]];
        poly_dma_state = POLY_SENDING_QUADS;
        POLY_QUAD_A_HI = cmd.quad->a_hi;
        POLY_QUAD_A_LO = cmd.quad->a_lo;
        POLY_QUAD_B_HI = cmd.quad->b_hi;
        POLY_QUAD_B_LO = cmd.quad->b_lo;
        POLY_QUAD_ATTR = cmd.quad->attr;
        POLY_QUAD_PRI = cmd.quad->pri;
        POLY_QUAD_C_LO = cmd.quad->c_lo;
        POLY_QUAD_C_HI = cmd.quad->c_hi | POLY_QUAD_GO;
        poly_quad_cnt[poly_rd_bank]--;
        poly_quad_rd[poly_rd_bank]++;
    default:
        break;
    }
}
