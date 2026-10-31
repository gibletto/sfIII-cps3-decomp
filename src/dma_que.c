/*
 * DMA_QUE.C  Character DMA and colour DMA queue
 *
 * The video hardware has two DMA units. The character DMA reads a list of requests from CHARACTER RAM and
 * copies (or decompresses) graphics from the ROM into CHARACTER RAM. The colour DMA copies a block of colours
 * from the ROM into COLOR RAM, scaling each colour by a fade value on the way.
 * dma_queue_init / dma_queue_flip set up the double-buffered request queue, chr_dma_request queues a
 * character transfer, col_dma_request sends a colour transfer (or queues it while a DMA is busy),
 * col_dma_queue always queues one, and dma_queue_send starts the next waiting transfer.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "cps3.h"

/* video DMA status: the character DMA (bit 1) or the colour DMA (bit 2) is busy */
#define VIDEO_DMA_STATUS    (*(volatile u16*)DMA_STATUS_REG)
#define VIDEO_DMA_BUSY      6

/* character DMA request list address (in CHARACTER RAM, in words); bit 6 of the high word starts it */
#define CHR_DMA_LIST_LO        (*(volatile u16*)(VIDEO_REG + 0x96))
#define CHR_DMA_LIST_HI        (*(volatile u16*)(VIDEO_REG + 0x98))

/* colour DMA registers: source (ROM), destination (colour number), fade, length (colours) */
#define COL_DMA_SRC_HI      (*(volatile u16*)(VIDEO_REG + 0xA0))
#define COL_DMA_SRC_LO      (*(volatile u16*)(VIDEO_REG + 0xA2))
#define COL_DMA_DST_HI      (*(volatile u16*)(VIDEO_REG + 0xA4))
#define COL_DMA_DST_LO      (*(volatile u16*)(VIDEO_REG + 0xA6))
#define COL_DMA_FADE_HI      (*(volatile u16*)(VIDEO_REG + 0xA8))
#define COL_DMA_FADE_LO       (*(volatile u16*)(VIDEO_REG + 0xAA))
#define COL_DMA_LEN_LO      (*(volatile u16*)(VIDEO_REG + 0xAC))
#define COL_DMA_LEN_HI      (*(volatile u16*)(VIDEO_REG + 0xAE))    /* | COL_DMA_GO starts it */
#define COL_DMA_GO        2

#define CHR_DMA_FIELD_MASK     0x1FFFFF
#define CHR_DMA_SRC_MASK    0x3FFFFFF

/* dma_state */
#define DMA_IDLE           0
#define DMA_SENDING_CHR  1
#define DMA_SENDING_COL  2
#define DMA_SENDING_DIRECT 3   /* a colour transfer sent straight to the registers */

/* dma_order_kind[] and dma_queue_send's kind */
#define DMA_KIND_CHR      1
#define DMA_KIND_COL      2

s32 dma_state;  /* 0206A120 */
s16 dma_reserve0;  /* 0206A124 */
s16 dma_reserve1;  /* 0206A126 */
CHR_DMA chr_dma_buf[2][CHR_DMA_MAX];  /* 0206A128 */
u32 chr_dma_cnt[2];  /* 0206C120 */
u32 chr_dma_rd[2];  /* 0206C128 */
COL_DMA col_dma_buf[2][COL_DMA_MAX];  /* 0206C130 */
u32 col_dma_cnt[2];  /* 0206C530 */
u32 col_dma_rd[2];  /* 0206C538 */
u32 dma_order_pos[2];  /* 0206C540 */
u16 dma_order_kind[2][DMA_ORDER_MAX];  /* 0206C548 */
s32 dma_wr_bank;  /* 0206CB1C */
s32 dma_rd_bank;  /* 0206CB20 */


u32 chr_dma_list_ofs = 0;  /* 02007390 */
s32 chr_dma_list_bank = 0;  /* 02007394 */


/* provisional name */
void dma_queue_init(s32 offset) {
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
    dma_state = DMA_IDLE;
    dma_reserve0 = 0;
    dma_reserve1 = 0;
    if (offset != -1) {
        chr_dma_list_bank = (offset >> 20) & 7;
        chr_dma_list_ofs = offset;
    }
    dma_wr_bank = 0;
    dma_rd_bank = 1;
    chr_dma_cnt[0] = 0;
    chr_dma_cnt[1] = 0;
    col_dma_cnt[0] = 0;
    col_dma_cnt[1] = 0;
    chr_dma_rd[0] = 0;
    chr_dma_rd[1] = 0;
    col_dma_rd[0] = 0;
    col_dma_rd[1] = 0;
    dma_order_pos[0] = 0;
    dma_order_pos[1] = 0;
    *(volatile u16*)IRQ10_ACK = 0;
}



/* provisional name */
void dma_queue_flip(void) {
    s32 mask;
    if (chr_dma_cnt[dma_wr_bank] + col_dma_cnt[dma_wr_bank] > 0) {
        if (chr_dma_cnt[(u32)dma_rd_bank] + col_dma_cnt[(u32)dma_rd_bank] == 0) {
            mask = _builtin_get_imask();
            _builtin_set_imask(15);
            dma_wr_bank++;
            dma_wr_bank &= 1;
            dma_rd_bank++;
            dma_rd_bank &= 1;
            chr_dma_cnt[dma_wr_bank] = 0;
            col_dma_cnt[dma_wr_bank] = 0;
            chr_dma_rd[dma_wr_bank] = 0;
            col_dma_rd[dma_wr_bank] = 0;
            dma_order_pos[dma_wr_bank] = 0;
            _builtin_set_imask(mask);
        }
    }
}



/* provisional name */
s32 chr_dma_request(src, dst, size, mode)
u32 src;
u32 dst;
u32 size;
u8 mode;
{
    register CHR_DMA* req;
    if (chr_dma_cnt[dma_wr_bank] >= CHR_DMA_MAX) {
        return -1;
    }
    req = &chr_dma_buf[dma_wr_bank][chr_dma_cnt[dma_wr_bank]];
    /* mode 0 copies, 1 and 2 decompress 6 and 8 bit graphics, 3 loads the decompression table */
    if (mode) {
        if (mode == 3) {
            size = 127;
            dst = 0;
        }
        mode++;
    }
    if (mode == 4) {
        req->ctrl = (mode << 21) | (size & CHR_DMA_FIELD_MASK);
    } else {
        req->ctrl = (((size << 1) & CHR_DMA_FIELD_MASK) | (mode << 21)) + 1;
    }
    req->dst = (dst >> 3) & CHR_DMA_FIELD_MASK;
    req->src = src & CHR_DMA_SRC_MASK;
    chr_dma_cnt[dma_wr_bank]++;
    dma_order_kind[dma_wr_bank][dma_order_pos[dma_wr_bank]] = DMA_KIND_CHR;
    return 0;
}



/* provisional name */
/* fade1..fade3: one fade value per colour channel; bit 6 turns the fade on, bit 5 fades towards white
   instead of black, bits 0-4 are the level */
s32 col_dma_request(src, dst, size, fade1, fade2, fade3)
u32 src;
u32 dst;
u32 size;
u16 fade1;
u16 fade2;
s16 fade3;
{
    register COL_DMA* cmd;
    s32 unused;
    if ((VIDEO_DMA_STATUS & VIDEO_DMA_BUSY) || dma_state != DMA_IDLE) {
        if (col_dma_cnt[dma_wr_bank] >= COL_DMA_MAX) {
            return -1;
        }
        cmd = &col_dma_buf[dma_wr_bank][col_dma_cnt[dma_wr_bank]];
        cmd->src_lo = src >> 1;
        cmd->src_hi = ((src >> 1) & 0x7FF0000) >> 16;
        cmd->dst_lo = dst >> 1;
        cmd->dst_hi = ((dst >> 1) & 0x10000) >> 16;
        cmd->len_lo = size >> 1;
        cmd->len_hi = ((size >> 1) & 0x10000) >> 16;
        cmd->fade_hi = (fade2 << 8 | fade1) & 0x7F7F;
        cmd->fade_lo = fade3 & 0x7F;
        col_dma_cnt[dma_wr_bank]++;
        dma_order_kind[dma_wr_bank][dma_order_pos[dma_wr_bank]] = DMA_KIND_COL;
    } else {
        dma_state = DMA_SENDING_DIRECT;
        COL_DMA_SRC_HI = ((src >> 1) & 0x7FF0000) >> 16;
        COL_DMA_SRC_LO = src >> 1;
        COL_DMA_DST_HI = ((dst >> 1) & 0x10000) >> 16;
        COL_DMA_DST_LO = dst >> 1;
        COL_DMA_FADE_HI = (fade2 << 8 | fade1) & 0x7F7F;
        COL_DMA_FADE_LO = fade3 & 0x7F;
        COL_DMA_LEN_LO = size >> 1;
        COL_DMA_LEN_HI = ((size >> 1) & 0x10000) >> 16 | COL_DMA_GO;
    }
    return 0;
}



/* provisional name */
s32 col_dma_queue(u32 src, u32 dst, u32 size, u16 fade1, u16 fade2, s16 fade3) {
    register COL_DMA* cmd;
    s32 unused;
    if (col_dma_cnt[dma_wr_bank] >= COL_DMA_MAX) {
        return -1;
    }
    cmd = &col_dma_buf[dma_wr_bank][col_dma_cnt[dma_wr_bank]];
    cmd->src_lo = src >> 1;
    cmd->src_hi = ((src >> 1) & 0x7FF0000) >> 16;
    cmd->dst_lo = dst >> 1;
    cmd->dst_hi = ((dst >> 1) & 0x10000) >> 16;
    cmd->len_lo = size >> 1;
    cmd->len_hi = ((size >> 1) & 0x10000) >> 16;
    cmd->fade_hi = (fade2 << 8 | fade1) & 0x7F7F;
    cmd->fade_lo = fade3 & 0x7F;
    col_dma_cnt[dma_wr_bank]++;
    dma_order_kind[dma_wr_bank][dma_order_pos[dma_wr_bank]] = DMA_KIND_COL;
    return 0;
}

/* provisional name */
void dma_queue_drain_try(void) {
    if ((VIDEO_DMA_STATUS & VIDEO_DMA_BUSY) == 0 && dma_state == DMA_IDLE) {
        if (chr_dma_cnt[dma_rd_bank] > 0) {
            dma_queue_send(DMA_KIND_CHR);
        } else if (col_dma_cnt[dma_rd_bank] > 0) {
            dma_queue_send(DMA_KIND_COL);
        }
    }
}



/* Wait until the video DMA units are idle, then send the next waiting transfer:
   a character transfer if any is queued, otherwise a colour transfer.  A colour
   transfer that was sent straight to the registers (state 3) needs nothing more. */
/* provisional name */
void dma_queue_drain_wait(void) {
    while (VIDEO_DMA_STATUS & VIDEO_DMA_BUSY) {
    }
    switch (dma_state) {
    case DMA_SENDING_CHR:
    case DMA_SENDING_COL:
        dma_state = DMA_IDLE;
        if (chr_dma_cnt[dma_rd_bank] > 0) {
            dma_queue_send(DMA_KIND_CHR);
        } else if (col_dma_cnt[dma_rd_bank] > 0) {
            dma_queue_send(DMA_KIND_COL);
        }
        break;
    case DMA_SENDING_DIRECT:
        dma_state = DMA_IDLE;
        /* fall through */
    case DMA_IDLE:
    default:
        break;
    }
}



/* provisional name */
void dma_queue_send(s32 kind) {
    union {
        CHR_DMA* chr;
        COL_DMA* col;
    } cmd;
    CHR_DMA* out;
    s32 i;
    s32 n;
    s32 unused;
    switch (kind) {
    case DMA_KIND_CHR:
        if (chr_dma_cnt[dma_rd_bank] > CHR_DMA_MAX) {
            n = CHR_DMA_MAX;
        } else {
            n = chr_dma_cnt[dma_rd_bank];
        }
        out = (CHR_DMA*)((chr_dma_list_ofs & 0xFFFFF) + CHARACTER_RAM);
        cram_bank_set(chr_dma_list_bank);
        for (i = 0; i < n; i++) {
            cmd.chr = &chr_dma_buf[dma_rd_bank][chr_dma_rd[dma_rd_bank] + i];
            out[i].ctrl = cmd.chr->ctrl;
            out[i].dst = cmd.chr->dst;
            out[i].src = cmd.chr->src;
            chr_dma_cnt[dma_rd_bank]--;
        }
        chr_dma_rd[dma_rd_bank] += n;
        out[i].ctrl = 0x01000000;
        out[i].dst = 0;
        out[i].src = 0;
        CHR_DMA_LIST_LO = ((u32)out - CHARACTER_RAM) >> 2;
        CHR_DMA_LIST_HI = ((((u32)out - CHARACTER_RAM) >> 18) & 0x3F) | 0x40;
        cram_bank_restore();
        break;
    case DMA_KIND_COL:
        cmd.col = &col_dma_buf[dma_rd_bank][col_dma_rd[dma_rd_bank]];
        dma_state = DMA_SENDING_COL;
        COL_DMA_SRC_HI = cmd.col->src_hi;
        COL_DMA_SRC_LO = cmd.col->src_lo;
        COL_DMA_DST_HI = cmd.col->dst_hi;
        COL_DMA_DST_LO = cmd.col->dst_lo;
        COL_DMA_FADE_HI = cmd.col->fade_hi;
        COL_DMA_FADE_LO = cmd.col->fade_lo;
        COL_DMA_LEN_LO = cmd.col->len_lo;
        COL_DMA_LEN_HI = cmd.col->len_hi | COL_DMA_GO;
        col_dma_cnt[dma_rd_bank]--;
        col_dma_rd[dma_rd_bank]++;
        /* fall through */
    default:
        break;
    }
}
