/*
 * EFF86.C  Effect 86: effect 85's partner object
 *
 * effect_86_init places one object (eff86_char_table pattern 13) at (549, 92) for its master;
 * eff86_0000 animates it while the master's routine_no[1] is outside 2-4 and resets it at 4.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "EFF86.h"

/* routine_no[0] */
#define R0_INIT         0       /* start pattern 13 */
#define R0_MOVE         1       /* follow the master's state */
#define R0_KILL         2       /* (default) put the work back */

/* Set pattern 13, then run eff86_0000 every frame. */
void effect_86_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.routine_no[1] = 0;
        ewk->wu.routine_no[2] = 0;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 13);
        /* fall through */
    case R0_MOVE:
        eff86_0000(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* Follow the master's routine_no[1]. */
void eff86_0000(WORK_Other* ewk) {
    WORK* mwk = (WORK*)ewk->my_master;
    if (compel_dead_check(ewk)) {
        ewk->wu.routine_no[0]++;
    } else {
        switch (mwk->routine_no[1]) {
        case 2:
        case 3:
            break;
        case 4:
            set_char_move_init(&ewk->wu, 0, 13);
            break;
        default:
            if (!EXE_flag && !Game_pause) {
                char_move(&ewk->wu);
            }
            disp_pos_trans_entry_r(ewk);
            break;
        }
    }
}



/* Create effect 85's partner object at (549, 92); made with effect 85. */
s32 effect_86_init(WORK* oya) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 86;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.dead_f = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 96;
    ewk->my_master = (u32*)oya;
    ewk->wu.my_family = 2;
    ewk->wu.xyz[0].disp.pos = 549;
    ewk->wu.xyz[1].disp.pos = 92;
    ewk->wu.my_priority = ewk->wu.position_z = 80;
    ewk->wu.char_table[0] = eff86_char_table;
    return 0;
}
