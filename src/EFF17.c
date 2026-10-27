/*
 * EFF17.C  Effect 17: loads palette 2
 *
 * effect_17_move loads colour set 2 and sets the palette bank (0x3FC00), waits two frames and
 * releases itself. Nothing calls effect_17_init.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "color3rd.h"
#include "textsound.h"
#include "EFF17.h"

/* routine_no[0] */
#define R0_INIT         0       /* load colour set 2 */
#define R0_WAIT         1       /* wait a frame */
#define R0_END          2       /* one more frame */
#define R0_KILL         3       /* (default) put the work back */



s32 effect_17_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 17;
    ewk->wu.work_id = 16;
    return 0;
}



void effect_17_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        load_any_color(2);
        palette_bank_set(0x3FC00);
        ewk->wu.routine_no[0]++;
        break;
    case R0_WAIT:
    case R0_END:
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}
