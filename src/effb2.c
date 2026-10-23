/*
 * EFFB2.C  Round-start FIGHT call sequence (effect B2)
 *
 * effect_B2_move waits for the display children's rf_b2_flag counts and timers,
 * then sets Next_Step so the round can begin. It checks Break_Into after each of
 * its first five states. effect_B2_init creates the family-2 controller, chooses
 * normal or final round from Game_setting.set4 and Round_num, then starts effect B3.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLS02.h"
#include "aboutspr.h"
#include "effb2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "effb3.h"
#include "EFFB4.h"







s16 rf_b2_flag;  
s16 b2_curr_no;  



/* its own states */
void effect_B2_move(WORK_Other* ewk) {
    s16 work = rf_b2_flag;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.old_rno[0] = ewk->wu.old_rno[1] = ewk->wu.old_rno[2] = 0;
        rf_b2_flag = 0;
        b2_curr_no = 0;
        b3_Break_Into_check(ewk);
        break;
    case 1:
        if (ewk->wu.type) {
            if (work > 9) {
                ewk->wu.routine_no[0] += 2;
                ewk->wu.hit_stop = 24;
                rf_b2_flag = 0;
            }
        } else if (work > 4) {
            ewk->wu.routine_no[0]++;
            ewk->wu.hit_stop = 24;
            rf_b2_flag = 0;
        }
        b3_Break_Into_check(ewk);
        break;
    case 2:
        if (work) {
            ewk->wu.routine_no[0]++;
            ewk->wu.hit_stop = 24;
        }
        b3_Break_Into_check(ewk);
        break;
    case 3:
        ewk->wu.hit_stop--;
        if (ewk->wu.hit_stop < 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.hit_stop = 24;
            b2_curr_no = 0;
            rf_b2_flag = 0;
        }
        b3_Break_Into_check(ewk);
        break;
    case 4:
        if (ewk->wu.type) {
            if (work > 9) {
                ewk->wu.routine_no[0]++;
                rf_b2_flag = 0;
            }
        } else if (work > 4) {
            ewk->wu.routine_no[0]++;
            rf_b2_flag = 0;
        }
        b3_Break_Into_check(ewk);
        break;
    case 5:
        if (work) {
            ewk->wu.routine_no[0]++;
            rf_b2_flag = 0;
            ewk->wu.hit_stop = 24;
        }
        break;
    case 6:
        ewk->wu.hit_stop--;
        if (ewk->wu.hit_stop < 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.hit_stop = 24;
        }
        break;
    case 7:
        Next_Step = 1;
        ewk->wu.routine_no[0]++;
        break;
    case 8:
        ewk->wu.routine_no[0]++;
        break;
    case 99:
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 b3_Break_Into_check(WORK_Other* ewk) {
    if (Break_Into) {
        ewk->wu.routine_no[0] = 99;
        return 1;
    }
    return 0;
}



/* Family 2; round type comes from Game_setting.set4. */
s32 effect_B2_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 0x70;
    ewk->wu.work_id = 0x10;
    ewk->wu.my_family = 2;
    switch (Game_setting.set4) {
    case 0:
        ewk->wu.type = 0;
        break;
    case 1:
        if (Round_num == 2) {
            ewk->wu.type = 1;
        } else {
            ewk->wu.type = 0;
        }
        break;
    case 2:
        if (Round_num == 4) {
            ewk->wu.type = 1;
        } else {
            ewk->wu.type = 0;
        }
        break;
    case 3:
        if (Round_num == 6) {
            ewk->wu.type = 1;
        } else {
            ewk->wu.type = 0;
        }
        break;
    }
    effect_B3_init(ewk);
    return 0;
}
