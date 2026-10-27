/*
 * EFF08.C  Effect 08: companion stage object
 *
 * effect_07_init starts this object with the effect 07 work as master. It animates
 * while the master shows pattern 2 and restarts when the master does.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "bg000.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLS02.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "aboutspr.h"
#include "CHARMOVE.h"
#include "ta_sub.h"
#include "eff08.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the animation */
#define R0_MOVE         1       /* animate with the master, restart with it */

extern const u32 eff08_char_table[];   /* provisional name */



/* Follows its master. */
void effect_08_move(WORK_Other* ewk) {
    WORK_Other* oya;
    oya = (WORK_Other*)ewk->my_master;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        /* fall through */
    case R0_MOVE:
        if (!EXE_flag && !Game_pause) {
            if (!oya->wu.routine_no[0]) {
                if (oya->wu.char_index == 2) {
                    ewk->wu.char_index = 0;
                    ewk->wu.routine_no[0] = R0_INIT;
                }
            } else if (oya->wu.char_index == 2) {
                char_move(&ewk->wu);
            }
        }
        sort_push_request4(&ewk->wu);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* Create one object for the master. */
s32 effect_08_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->my_master = (u32*)oya;
    ewk->wu.be_flag = 1;
    ewk->wu.id = 8;
    ewk->wu.work_id = 16;
    ewk->wu.my_priority = 64;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.position_x = 432;
    ewk->wu.position_y = 118;
    ewk->wu.position_z = 70;
    ewk->wu.char_table[0] = eff08_char_table;
    ewk->wu.char_index = 0;
    return 0;
}
