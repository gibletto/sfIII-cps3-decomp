/*
 * EFFB5_INIT.C  Effect B5 init
 *
 * effect_B5_init creates the three name-entry letter works (B5) for a player, 24 dots apart on
 * BG1 (called from n_input.c).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "PLS02.h"
#include "EFFB6.h"



/* my_col_code 67 */
s32 effect_B5_init(s16 PL_id) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    s16 x = 0x1F0;
    for (i = 0; i < 3; i++) {
        if ((ix = pull_effect_work(3)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->my_master = (u32*)&name_wk[PL_id];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 115;
        ewk->wu.work_id = 16;
        ewk->wu.old_rno[2] = i;
        ewk->wu.type = i;
        ewk->wu.cgromtype = 1;
        ewk->wu.disp_flag = 0;
        ewk->wu.rl_flag = 0;
        ewk->wu.my_family = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 67;
        ewk->wu.my_priority = ewk->wu.position_z = 10;
        ewk->wu.position_y = 80;
        ewk->wu.xyz[1].cal = 0x500000;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = x;
        ewk->wu.xyz[0].disp.low = 0;
        ewk->wu.char_index = 6;
        ewk->wu.char_table[0] = etc_char_table;
        x = x + 24;
    }
    return 0;
}
