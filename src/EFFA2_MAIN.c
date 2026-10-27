/*
 * EFFA2_MAIN.C  Effect A2: break-in banner
 *
 * effect_A2_init (from entry_2.c when a challenger breaks in) creates the effect. On its first frame
 * effect_A2_move clears the banner area of the text layer and starts two effect A3 cell animations;
 * then each frame it draws two more columns of the banner (break_into_banner_trans), and after 40
 * columns it starts the two effect A4 objects and frees itself.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EffA2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "sc_trans.h"
#include "sc_clear.h"

/* routine_no[0] */
#define R0_INIT         0       /* clear the banner area, start the cells */

s32 effect_A3_init();
s32 effect_A4_init();



void effect_A2_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        tilemap_clear_rect(DE_X[3] + 10, Text_Page_Y + 8, DE_X[0] + 36, Text_Page_Y + 18);
        effect_A3_init(0, DE_X[0] + 3, Text_Page_Y + 9, 6, 2, 2, 0, 5, 0);
        effect_A3_init(1, DE_X[0] + 3, Text_Page_Y + 15, 6, 2, 2, 0, 5, 1);
        break_into_banner_trans(0);
        break;
    }
    break_into_banner_trans(ewk->wu.direction);
    ewk->wu.direction++;
    break_into_banner_trans(ewk->wu.direction);
    if (ewk->wu.direction < 40) {
        ewk->wu.direction++;
    } else {
        effect_A4_init(0);
        effect_A4_init(1);
        push_effect_work(&ewk->wu);
    }
}



s32 effect_A2_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 102;
    ewk->wu.direction = 1;
    return 0;
}
