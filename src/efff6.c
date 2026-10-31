/*
 * EFFF6.C  Effect F6: opening step counter
 *
 * effect_F6_init creates the counter and starts effect F7 with it as master. effect_F6_move
 * advances routine_no[0] every old_rno[1] frames and sets op_w.free_work at step 23.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "efff6.h"
#include "efff7.h"

/* routine_no[1] */
#define R1_INIT         0       /* clear the done flag */
#define R1_COUNT        1       /* count the steps up to 23 */
#define R1_END          2       /* one more frame */
#define R1_KILL         3       /* put the work back */



/* Advance the opening step counter. */
void effect_F6_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        ewk->wu.old_rno[3] = 0;
        /* fall through */
    case R1_COUNT:
        ewk->wu.old_rno[2]--;
        if (ewk->wu.old_rno[2] <= 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.old_rno[2] = ewk->wu.old_rno[1];
            if (ewk->wu.routine_no[0] == 23) {
                op_w.free_work = 1;
                ewk->wu.routine_no[1]++;
                ewk->wu.old_rno[3] = 1;
            }
        }
        break;
    case R1_END:
        ewk->wu.routine_no[1]++;
        break;
    case R1_KILL:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* Create the step counter of an opening scene and its six sprites (effect F7) when the scene starts. */
s32 effect_F6_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.id = 156;
    ewk->wu.be_flag = 1;
    ewk->wu.work_id = 0x10;
    ewk->wu.cgromtype = 1;
    ewk->wu.old_rno[2] = ewk->wu.old_rno[1] = 2;
    effect_F7_init(ewk);
    return 0;
}
