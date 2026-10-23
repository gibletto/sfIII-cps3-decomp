/*
 * EFF92_CODE.C  Effect 92: win marks
 *
 * effect_92_init (from manage_2.c): draws a side's win marks from the win-mark request table and
 * raises the side's done flag.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "fifo.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "eff92_code.h"
#include "cps3.h"



void effect_92_move(WORK_Other* ewk) {
    s32 kind;
    s32 col;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        if (--ewk->wu.dir_timer != 0) {
            return;
        }
        kind = *ewk->wu.move_xy_table++;
        ewk->wu.dir_timer = *ewk->wu.move_xy_table++;
        if ((u16)kind == 0x8000) {
            kind = ewk->wu.dmcal_m;
        }
        col = win_mark_col_tbl[(u16)kind];
        win_mark_put(ewk->master_id * 4 + PL_Wins[ewk->master_id] - 1, kind, col);
        if (ewk->wu.dir_timer == -1) {
            ewk->wu.routine_no[0]++;
            ewk->wu.dir_timer = 1;
        }
        break;
    default:
        if (--ewk->wu.dir_timer != 0) {
            return;
        } else {
            win_mark_new[ewk->master_id] = 1;
            push_effect_work((WORK*)ewk);
            break;
        }
    }
}



/* provisional name */
s32 effect_92_init(master_id, cal)
s16 master_id;
s16 cal;
{
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 92;
    ewk->master_id = master_id;
    ewk->wu.dmcal_m = cal;
    ewk->wu.move_xy_table = Rewrite_Mark_Data;
    ewk->wu.dir_timer = 1;
    return 0;
}
