/*
 * EFFE9.C  Ending frame bars (effect E9)
 *
 * effect_E9_init creates two sprites (top and bottom) from effE9_data on family 4 using the
 * end character table. effect_E9_move starts their animation and then just draws them where
 * they were placed. Created by common_end_init01 (end_main_c.c) for every ending.
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
#include "effe9.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the animation */
#define R0_MOVE         1       /* show the bar */



void effect_E9_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, 7, ewk->wu.char_index + 1, 0);
        break;
    case R0_MOVE:
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_E9_init(void) {
    WORK_Other* ewk;
    const s16* data;
    s16 ix;
    s16 i;
    data = effE9_data[0];
    for (i = 0; i < 2; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)((u32)frw + (ix << 11));
        ewk->wu.id = 149;
        ewk->wu.be_flag = 1;
        ewk->wu.type = i;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.char_table[0] = effH3_char_table;
        ewk->wu.my_family = 4;
        ewk->wu.my_col_code = 1;
        ewk->wu.my_priority = ewk->wu.position_z = 20;
        ewk->wu.xyz[0].disp.pos = *data++;
        ewk->wu.xyz[1].disp.pos = *data++;
        ewk->wu.char_index = *data++;
    }
}



/* Top and bottom: position x, position y, picture. */
const s16 effE9_data[2][3] = {
    { 512, 0, 0 },
    { 512, 208, 1 },
};
