/*
 * EFF85.C  Effect 85: a stage object with a partner
 *
 * effect_85_init (stage code) makes one object at (0x25C, 94)
 * with the eff86_char_table patterns and its effect 86 partner. effect_85_move dispatches through a
 * three-entry table (eff85_0000 start / eff85_0100 run / eff85_0200 free); the run state plays
 * pattern 12 to its end, shows pattern 14, then starts over, while the game runs; it ends when the
 * stage retires it (compel_dead_check).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "EFF86.h"
#include "EFF85.h"

extern const u32 eff86_char_table[];   /* provisional name */



void effect_85_move(WORK_Other* ewk) {
    void (*const eff85_jp_tbl[3])(WORK_Other*) = { eff85_0000, eff85_0100, eff85_0200 };
    eff85_jp_tbl[ewk->wu.routine_no[0]](ewk);
}



void eff85_0000(WORK_Other* ewk) {
    ewk->wu.routine_no[0]++;
    ewk->wu.routine_no[1] = 0;
    ewk->wu.disp_flag = 1;
    set_char_move_init(&ewk->wu, 0, 12);
}



/* the sequence inline */
void eff85_0100(WORK_Other* ewk) {
    if (!EXE_flag && !Game_pause) {
        if (compel_dead_check(ewk)) {
            ewk->wu.routine_no[0]++;
            return;
        }
        switch (ewk->wu.routine_no[1]) {
        case 0:
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                ewk->wu.routine_no[1]++;
            }
            break;
        case 1:
            ewk->wu.routine_no[1]++;
            ewk->wu.disp_flag = 1;
            set_char_move_init(&ewk->wu, 0, 14);
            break;
        case 2:
            ewk->wu.routine_no[1]++;
            break;
        case 3:
            char_move(&ewk->wu);
            break;
        case 4:
            ewk->wu.routine_no[1]++;
            break;
        case 5:
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                ewk->wu.routine_no[0] = 0;
            }
            break;
        }
    }
    disp_pos_trans_entry_r(ewk);
}



void eff85_0200(WORK_Other* ewk)
{
    all_cgps_put_back(&ewk->wu);
    push_effect_work((WORK*)ewk);
}



/* its own object and the effect 86 partner */
s32 effect_85_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 85;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.dead_f = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 96;
    ewk->wu.xyz[0].disp.pos = 0x25C;
    ewk->wu.xyz[1].disp.pos = 94;
    ewk->wu.my_priority = ewk->wu.position_z = 79;
    ewk->wu.sync_suzi = 0;
    ewk->wu.char_table[0] = eff86_char_table;
    effect_86_init(&ewk->wu);
    return 0;
}
