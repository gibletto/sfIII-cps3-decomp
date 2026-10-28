/*
 * meta_col_bcd.c  BCD helpers for scores and counters
 *
 * hex_to_bcd converts a binary number to BCD; abcd and sbcd add and subtract two BCD bytes, and nbcd
 * negates one.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "meta_col_bcd.h"
#include "cps3.h"



s16 bcdext;


/* provisional name */
u32 hex_to_bcd(u32 dat) {
    u32 sum = 0;
    register u32 mask;
    register u8* bcd = (u8*)&sum;
    register const u8* p = bcd_weight_end;
    p--;
    for (mask = 0x8000; mask > 0; mask = mask >> 1) {
        if (dat & mask) {
            bcdext = 0;
            bcd[3] = abcd(bcd[3], *p);
            p--;
            bcd[2] = abcd(bcd[2], *p);
            p--;
            bcd[1] = abcd(bcd[1], *p);
            p--;
            bcd[0] = abcd(bcd[0], *p);
            p--;
        } else {
            p -= 4;
        }
    }
    return sum;
}



/* provisional name */
u8 abcd(u8 a, u8 b) {
    register s32 d;
    if ((u16)(d = (a & 0xF) + (bcdext & 1) + (b & 0xF)) > 9) {
        d -= 10;
        d |= 0x10;
    }
    d += (a & 0xF0) + (b & 0xF0);
    d = (u16)d;
    if (d > 0x99) {
        d -= 0xA0;
        d &= 0xFF;
        bcdext = 1;
    } else {
        bcdext = 0;
    }
    return d;
}


u8 sbcd(u8 a, u8 b) {
    register s16 d, c;
    if ((d = (b & 0xF) - (a & 0xF) - (bcdext & 1)) < 0) {
        d += 10;
        d |= 0x10;
    }
    c = (b & 0xF0) - (a & 0xF0) - (d & 0xF0);
    d &= 0xF;
    if ((d |= c) < 0) {
        d += 160;
        bcdext = 1;
    } else {
        bcdext = 0;
    }
    return d;
}

/* provisional name */
u8 nbcd(u8 a) {
    register s8 d;
    if ((d = 0 - (bcdext & 1) - (a & 0xF)) < 0) {
        d += 2;
        d |= 0x10;
    }
    d |= 0 - (a & 0xF0) - (d & 0xF0);
    if ((d & 0xF0) > 0) {
        d += 48;
        bcdext = 1;
    } else {
        bcdext = 0;
    }
    return d;
}
