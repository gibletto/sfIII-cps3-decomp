/*
 * EFFB7.C  Effect B7: rank-in number
 *
 * Effect B7 shows a rank-in number (pattern old_rno[0] + 1) for name entry until it is killed.
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

/* routine_no[0] */
#define R0_INIT         0       /* show the number */
#define R0_MOVE         1       /* draw it for the name entry */
#define R0_END          2       /* one more frame */
#define R0_KILL         3       /* (default) put the work back */

void effect_B7_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, 7, ewk->wu.old_rno[0] + 1, 0);
        break;
    case R0_MOVE:
        disp_pos_trans_entry(ewk);
        break;
    case R0_END:
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}


/* my_col_code 67 */
s32 effect_B7_init(s8 pl) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    for (i = 0; i < 2; i++) {
        if ((ix = pull_effect_work(3)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->my_master = (u32*)&name_wk[pl];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 117;
        ewk->wu.work_id = 16;
        ewk->wu.type = i;
        ewk->wu.cgromtype = 1;
        ewk->wu.disp_flag = 0;
        ewk->wu.rl_flag = 0;
        ewk->wu.my_family = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 67;
        ewk->wu.my_priority = ewk->wu.position_z = 10;
        ewk->wu.position_y = 104;
        ewk->wu.xyz[1].cal = 104 << 16;
        ewk->wu.xyz[0].disp.low = 0;
        ewk->wu.char_index = 7;
        *ewk->wu.char_table = etc_char_table;
        if (i) {
            ewk->wu.old_rno[0] = name_wk[pl].rank_in * 2 + 1;
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 0x210;
        } else {
            ewk->wu.old_rno[0] = name_wk[pl].rank_in * 2;
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 0x200;
        }
    }
    return 0;
}
