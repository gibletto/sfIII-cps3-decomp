/*
 * fifo.c  Word FIFO queue
 *
 * fifo_init sets up a ring buffer of 32-bit entries (size, write pointer, read pointer, count,
 * buffer top) and fifo_get takes the next entry, wrapping the read pointer at the end of the
 * buffer and returning 0 when the queue is empty.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "fifo.h"
/* provisional name */
void fifo_init(q, buf, size)
FIFO32* q;
u32* buf;
s32 size;
{
    q->size = size;
    q->wr = buf;
    q->rd = buf;
    q->count = 0;
    q->base = buf;
}



/* provisional name */
s32 fifo_put(FIFO32* q, u32 dat) {
    register u32* next;
    register u32* wr;
    next = q->wr + 1;
    if ((u32)next >= (u32)q->base + q->size) {
        next = q->base;
    }
    if (next != q->rd) {
        wr = q->wr;
        *wr = dat;
        q->wr = next;
        q->count++;
        return 0;
    }
    return -1;
}



/* provisional name */
s32 fifo_get(FIFO32* q) {
    register u32 dat;
    register u32* rd;
    if (q->wr != q->rd) {
        rd = q->rd;
        dat = *rd;
        rd++;
        q->rd = rd;
        q->count--;
        if ((u32)rd >= (u32)q->base + q->size) {
            q->rd = q->base;
        }
        return dat;
    }
    return 0;
}
