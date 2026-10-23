/*
 * EFFA4.C  Effect A4: row of effect 89 objects
 *
 * Effect A4 calls effect_89_init 21 times, two columns apart, starting later for player 2.
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
#include "EFFA3.h"

void effect_A4_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        if (--ewk->wu.dir_timer) {
            break;
        }
        effect_89_init(ewk->master_id + 6, ewk->wu.dir_old, Text_Page_Y + 11, 2, 4);
        if (--ewk->wu.dir_step != 0) {
            ewk->wu.dir_timer = 1;
            ewk->wu.dir_old += 2;
        } else {
            push_effect_work(&ewk->wu);
            return;
        }
        break;
    }
}



s32 effect_A4_init(s16 PL_id) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 104;
    ewk->master_id = PL_id;
    ewk->wu.direction = 0;
    ewk->wu.dir_step = 21;
    ewk->wu.dir_old = DE_X[0] + 3;
    if (PL_id) {
        ewk->wu.dir_timer = 5;
    } else {
        ewk->wu.dir_timer = 1;
    }
    return 0;
}
