/*
 * EFFA5.C  Effect A5: select timer
 *
 * effect_A5_entry creates the select-screen timer. It counts Select_Timer down in
 * BCD every 40 frames and sets Time_Over 30 frames after zero. Time_Stop holds the
 * countdown; Exit_No retires the timer and sets Time_Stop to -1.
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




/* Retire the timer when Exit_No is set. */
void effect_A5_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        if (Exit_No) {
            ewk->wu.routine_no[0] = 4;
            Time_Stop = -1;
            break;
        }
        if (Time_Stop == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case 1:
        if (Exit_No) {
            ewk->wu.routine_no[0] = 4;
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
    case 2:
        if (Exit_No) {
            ewk->wu.routine_no[0] = 4;
            Time_Stop = -1;
            break;
        }
        if (Select_Timer) {
            ewk->wu.routine_no[0] = 1;
            Unit_Of_Timer = 40;
        } else if (--ewk->wu.dir_timer == 0) {
            Time_Over = 1;
            ewk->wu.routine_no[0]++;
        }
        break;
    case 3:
        Time_Over = 1;
        if (Exit_No) {
            ewk->wu.routine_no[0] = 4;
            Time_Stop = -1;
            break;
        }
        if (Select_Timer) {
            ewk->wu.routine_no[0] = 1;
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
