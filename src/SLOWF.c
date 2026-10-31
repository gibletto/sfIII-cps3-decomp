/*
 * SLOWF.C  Slow-motion control
 *
 * Controls the game's slow motion. init_slow_flag clears it; set_conclusion_slow starts the
 * round-conclusion slow motion (95 frames); set_EXE_flag runs once per frame, easing SLOW_flag
 * off through slow_timer_to_flag as the timer runs down, and sets EXE_flag from Game_timer so
 * that works only execute on every (SLOW_flag + 1)-th frame. Nothing changes while paused.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SLOWF.h"

s16 EXE_flag;  /* 0200EB10 */
s16 SLOW_flag;  /* 0200EB12 */
s16 SLOW_timer;  /* 0200EB14 */



void init_slow_flag(void) {
    EXE_flag = 0;
    SLOW_flag = 0;
    SLOW_timer = 0;
}



void set_conclusion_slow(void) {
    SLOW_timer = 95;
}



void set_EXE_flag(void) {
    s16 tmw;

    if (Game_pause) {
        return;
    }
    if (SLOW_timer) {
        if (--SLOW_timer != 0) {
            tmw = SLOW_timer / 8;
            if (tmw > 31) {
                tmw = 31;
            }
            SLOW_flag = slow_timer_to_flag[tmw];
        } else {
            SLOW_flag = 0;
        }
    }
    EXE_flag = Game_timer % (SLOW_flag + 1);
}
