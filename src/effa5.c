/*
 * EFFA5.C  Effect A5: select timer
 *
 * Effect A5 (effect_A5_entry, started by sel_pl.c) is the select-screen timer:
 * it counts Select_Timer down in BCD every 40 frames, holds while Time_Stop is set,
 * and sets Time_Over 30 frames after the timer reaches zero. Exit_No retires the timer and sets
 * Time_Stop to -1.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "eff87.h"
#include "eff88.h"
#include "eff89.h"
#include "eff90.h"
#include "eff91.h"
#include "eff92_code.h"
#include "Eff93.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "sc_trans.h"
#include "effa5.h"

/* routine_no[0] */
#define R0_WAIT         0       /* wait while the timer is stopped */
#define R0_COUNT        1       /* count the timer down */
#define R0_ZERO         2       /* at zero: time over after 30 frames */
#define R0_OVER         3       /* time over until the timer is reset */
#define R0_KILL         4       /* (default) put the work back */




/* retire the timer when Exit_No is set */
void effect_A5_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_WAIT:
        if (Exit_No) {
            ewk->wu.routine_no[0] = R0_KILL;
            Time_Stop = -1;
            break;
        }
        if (Time_Stop == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case R0_COUNT:
        if (Exit_No) {
            ewk->wu.routine_no[0] = R0_KILL;
            Time_Stop = -1;
            break;
        }
        if (--Unit_Of_Timer) {
            break;
        }
        Unit_Of_Timer = 40;
        bcdext = 0;
        if ((Select_Timer = sbcd(1, Select_Timer)) == 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.dir_timer = 30;
        }
        break;
    case R0_ZERO:
        if (Exit_No) {
            ewk->wu.routine_no[0] = R0_KILL;
            Time_Stop = -1;
            break;
        }
        if (Select_Timer) {
            ewk->wu.routine_no[0] = R0_COUNT;
            Unit_Of_Timer = 40;
        } else if (--ewk->wu.dir_timer == 0) {
            Time_Over = 1;
            ewk->wu.routine_no[0]++;
        }
        break;
    case R0_OVER:
        Time_Over = 1;
        if (Exit_No) {
            ewk->wu.routine_no[0] = R0_KILL;
            Time_Stop = -1;
            break;
        }
        if (Select_Timer) {
            ewk->wu.routine_no[0] = R0_COUNT;
            Unit_Of_Timer = 40;
        }
        break;
    default:
        push_effect_work(&ewk->wu);
        break;
    }
}



u32 effect_A5_entry(void)
{
    WORK_Other* ewk;
    s16 ix;

    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 105;
    return 0;
}
