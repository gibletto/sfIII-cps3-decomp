/*
 * SE_2.C  Screen wipe patterns (part 2)
 *
 * Routines: mix_put_step, wipe_pattern_and_low, wipe_and_row, wipe_and_dot.
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
#include "se_2.h"
#include "cps3.h"


/* provisional name */
void mix_put_step(void) {
    *wipe_dst_ptr = *wipe_back_ptr | *wipe_pat_ptr;
    wipe_dst_ptr++;
    wipe_pat_ptr++;
    wipe_back_ptr++;
}

/* provisional name */
void wipe_pattern_and_low(s16 kind, s16 row) {
    s32 x;
    s16 y;
    wipe_pat_top = wipe_clear_pattern_tbl[kind].adr;
    wipe_pat_top += row * 32;
    wipe_dst_ptr = (u16*)(SS_RAM + 0xD000);
    for (y = 0; y < 192; y++) {
        wipe_pat_ptr = wipe_pat_top;
        for (x = 0; x < 32; x++) {
            wipe_and_dot();
        }
    }
}



/* provisional name */
void wipe_and_row(void) {
    s32 j;
    wipe_pat_ptr = wipe_pat_top;
    for (j = 0; j < 32; j++) {
        *wipe_dst_ptr = *wipe_pat_ptr & *wipe_dst_ptr;
        wipe_dst_ptr++;
        wipe_pat_ptr++;
    }
}



/* provisional name */
void wipe_and_dot(void) {
    *wipe_dst_ptr = *wipe_pat_ptr & *wipe_dst_ptr;
    wipe_dst_ptr++;
    wipe_pat_ptr++;
}
