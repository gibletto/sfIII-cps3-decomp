/*
 * EFF07.C  Effect 07: stage background object
 *
 * effect_07_init creates one object at (463, 77) and starts effect 08 with it as master.
 * effect_07_move cycles its animation through the 16 entries of eff07_char_index_tbl
 * and draws it with sort_push_request4.
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
#include "eff08.h"
#include "EFF07.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the next animation */
#define R0_MOVE         1       /* animate; at its cue, restart with the next one */

extern const s16 eff07_char_index_tbl[18];   /* provisional name */
extern const u32 eff07_char_table[];   /* provisional name */



/* Play the object's animations in the order of eff07_char_index_tbl and draw it. */
void effect_07_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        /* fall through */
    case R0_MOVE:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                ewk->wu.cg_type = 0;
                ewk->wu.old_rno[0]++;
                ewk->wu.old_rno[0] &= 0xF;
                ewk->wu.char_index = eff07_char_index_tbl[ewk->wu.old_rno[0]];
                ewk->wu.routine_no[0] = R0_INIT;
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



/* Create the stage background object at (463, 77) and its effect 08 object when the stage
 * background is set up. */
s32 effect_07_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 7;
    ewk->wu.work_id = 16;
    ewk->wu.my_priority = 64;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 89;
    ewk->wu.position_x = 463;
    ewk->wu.position_y = 77;
    ewk->wu.position_z = 74;
    ewk->wu.char_table[0] = eff07_char_table;
    ewk->wu.char_index = 0;
    ewk->wu.position_x &= 0x3FF;
    ewk->wu.position_y &= 0x3FF;
    ewk->wu.old_rno[0] = 0;
    effect_08_init(ewk);
    return 0;
}
