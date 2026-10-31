/*
 * COUNT.C  Round timer
 *
 * Routines: count_cont_init, count_cont_reset, count_cont_main, counter_control.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sc_trans.h"
#include "PLS01.h"
#include "count.h"
#include "cps3.h"



ROUND_TIMER round_timer;
COUNT_WORK count_work;



void count_cont_init(pl)
u8 pl;
{
    (*&count_work).hoji_counter = hoji_counter_tbl[Game_setting.Timer_Speed];
    Counter_hi = 99;
    Counter_low = hoji_counter_tbl[Game_setting.Timer_Speed];
    *(s16*)&round_timer = Counter_hi;
    bcount_digit_trans(pl, 9, 9);
    if (pl == 0) {
        sc_celllist_put_scr(3);
    }
    round_timer.size.full = 0x630000;
    Timer_Freeze = 0;
}



/* provisional name */
void count_cont_reset(void) {
    (*&count_work).hoji_counter = hoji_counter_tbl[Game_setting.Timer_Speed];
    Counter_hi = 99;
    Counter_low = hoji_counter_tbl[Game_setting.Timer_Speed];
    *(s16*)&round_timer = Counter_hi;
    bcount_digit_trans(0, 9, 9);
}



/* The round timer: it counts down unless a stop flag is set, and does not flash in the last seconds. */
void count_cont_main(void) {
    if (Break_Into) {
        return;
    }
    if (Timer_Freeze) {
        return;
    }
    if (EXE_flag != 0) {
        return;
    }
    if (Game_pause != 0) {
        return;
    }
    counter_control();
}



void counter_control(void) {
    u16 hi;
    u16 lo;
    if (Counter_hi == 0) {
        return;
    }
    if (Counter_low != 0) {
        Counter_low--;
        return;
    }
    Counter_low = (*&count_work).hoji_counter;
    Counter_hi--;
    *(s16*)&round_timer = Counter_hi;
    hi = Counter_hi;
    hi = hi / 10;
    lo = Counter_hi - hi * 10;
    bcount_digit_trans(0, hi, lo);
    sc_celllist_put_scr(3);
}
