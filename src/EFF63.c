/*
 * EFF63.C  Effect 63: breakable stage object
 *
 * effect_63_init makes one object at (0x330, 52) of type 7. effect_63_move starts it by
 * eff_hit_flag[type] (pattern 31, 33, or broken at once with pattern 30), takes a hit (pattern 32),
 * waits for its pattern to end, takes hits until eff_hit_flag[7] is 2 (pattern 34), sets off effect
 * 27 (type 6) at the pattern's signal 2 and stays broken after signal 1.
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
#include "EFF27.h"
#include "EFF63.h"
#include "eff05.h"

/* routine_no[0] */
#define R0_INIT         0       /* pick the pattern by the hit state */
#define R0_WAIT         1       /* wait for the first hit */
#define R0_SHAKE        2       /* play the hit pattern */
#define R0_HIT          3       /* take hits until broken */
#define R0_BREAK        4       /* break, set off the blast */
#define R0_SETTLE       5       /* play on to the last signal */
#define R0_BROKEN       6       /* stay broken */
#define R0_KILL         99      /* (default) put the work back */



/* update the breakable stage object */
void effect_63_move(WORK_Other* ewk) {
    if (compel_dead_check(ewk) != 0) {
        ewk->wu.routine_no[0] = R0_KILL;
    } else if (EXE_flag || Game_pause) {
        disp_pos_trans_entry_rs(ewk);
    } else {
        switch (ewk->wu.routine_no[0]) {
        case R0_INIT:
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 1;
            switch (eff_hit_flag[ewk->wu.type]) {
            case 0:
                set_char_move_init(&ewk->wu, 0, 31);
                break;
            case 1:
                set_char_move_init(&ewk->wu, 0, 33);
                break;
            case 2:
                ewk->wu.routine_no[0] = R0_BROKEN;
                set_char_move_init(&ewk->wu, 0, 37);
                break;
            }
            break;
        case R0_WAIT:
            if (eff_hit_check(ewk, 0)) {
                ewk->wu.routine_no[0]++;
                set_char_move_init(&ewk->wu, 0, 32);
            }
            disp_pos_trans_entry_rs(ewk);
            break;
        case R0_SHAKE:
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                ewk->wu.routine_no[0]++;
            }
            disp_pos_trans_entry_rs(ewk);
            break;
        case R0_HIT:
            eff_hit_check(ewk, 0);
            if (eff_hit_flag[7] == 2) {
                ewk->wu.routine_no[0]++;
                set_char_move_init(&ewk->wu, 0, 34);
            }
            disp_pos_trans_entry_rs(ewk);
            break;
        case R0_BREAK:
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 2) {
                ewk->wu.routine_no[0]++;
                ewk->wu.cg_type = 0;
                effect_27_init(ewk, 6);
            }
            disp_pos_trans_entry_rs(ewk);
            break;
        case R0_SETTLE:
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 1) {
                ewk->wu.routine_no[0]++;
            }
            /* fall through */
        case R0_BROKEN:
            disp_pos_trans_entry_rs(ewk);
            break;
        default:
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
            return;
        }
    }
}



s32 effect_63_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 63;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.type = 7;
    ewk->wu.dead_f = 1;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 0x163;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 52;
    ewk->wu.position_z = ewk->wu.my_priority = 74;
    ewk->wu.char_table[0] = stg06_char_table;
    ewk->wu.hit_stop = 0;
    ewk->wu.sync_suzi = 1;
    suzi_offset_set(&ewk->wu);
    return 0;
}
