/*
 * EFF32.C  Effect 32: an object fixed to background layer 1
 *
 * effect_32_move shows the object at the scroll position of BG 1 (sort_push_request3) until
 * dead_f is set. effect_32_init and eff32_dummy do nothing.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFF32.h"



void effect_32_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.old_cgnum = 0;
        ewk->wu.cg_number = 1;
        ewk->wu.position_z = 1;
        ewk->wu.my_priority = 1;
        break;
    case 1:
        if (ewk->wu.dead_f) {
            ewk->wu.disp_flag = 0;
            ewk->wu.routine_no[0]++;
            break;
        }
        ewk->wu.position_x = bg_w.bgw[1].wxy[0].disp.pos;
        ewk->wu.position_y = bg_w.bgw[1].wxy[1].disp.pos;
        (void)bg_w.bgw[0].wxy[0].disp.pos;
        sort_push_request3(&ewk->wu);
        break;
    case 2:
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_32_init(void) {
    return 0;
}



/* provisional name */
void eff32_dummy(void) {
}
