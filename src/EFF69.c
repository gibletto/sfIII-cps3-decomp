/*
 * EFF69.C  Effect 69: a stage object that breaks after repeated hits
 *
 * effect_69_init (from bgst010's stage) places the object at (192, 48) with stg01_char_table and
 * creates its three effect 70 pieces. Each time a player hits it (eff_hit_check) while the stage's
 * hit count eff_hit_flag[6] is ahead of its state, it moves on one state and ignores hits for 96
 * frames; at the fourth state (eff69_break) it plays its broken pattern and starts effect 60 type 1.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "CHARMOVE.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "EFF70.h"
#include "EFF60.h"
#include "eff05.h"

/* routine_no[0] */
#define R0_INIT         0       /* show */
#define R0_MOVE         1       /* take hits until retired */
#define R0_KILL         99      /* (default) put the work back */

/* routine_no[2] */
#define R2_INIT         0       /* play the broken pattern */
#define R2_STAY         1       /* stay broken */

void eff69_2000(WORK_Other* ewk);
void eff69_wait(WORK_Other* ewk);
void eff69_break(WORK_Other* ewk);

void effect_69_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 16);
        break;
    case R0_MOVE:
        if (compel_dead_check(ewk)) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
        if (!EXE_flag && !Game_pause) {
            eff69_2000(ewk);
        }
        disp_pos_trans_entry_rs(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

void eff69_2000(WORK_Other* ewk) {
    void (*eff69_jp[4])(WORK_Other*) = { eff69_wait, eff69_wait, eff69_wait, eff69_break };
    eff69_jp[ewk->wu.routine_no[1]](ewk);
}

void eff69_wait(WORK_Other* ewk) {
    if (!ewk->wu.hit_stop) {
        if (eff_hit_check(ewk, 0)) {
            if (eff_hit_flag[6] > (s8)ewk->wu.routine_no[1]) {
                ewk->wu.routine_no[1]++;
                ewk->wu.routine_no[2] = R2_INIT;
                ewk->wu.hit_stop = 96;
            }
        }
    } else {
        ewk->wu.hit_stop--;
    }
}

void eff69_break(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case R2_INIT:
        ewk->wu.routine_no[2]++;
        set_char_move_init(&ewk->wu, 0, 19);
        effect_60_init(1);
        break;
    case R2_STAY:
    default:
        break;
    }
}

s32 effect_69_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 69;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.type = 6;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.dead_f = 1;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.hit_stop = 0;
    ewk->wu.xyz[0].disp.pos = 192;
    ewk->wu.xyz[1].disp.pos = 48;
    ewk->wu.my_priority = ewk->wu.position_z = 80;
    ewk->wu.sync_suzi = 0;
    ewk->wu.char_table[0] = stg01_char_table;
    suzi_offset_set(&ewk->wu);
    effect_70_init(ewk);
    return 0;
}
