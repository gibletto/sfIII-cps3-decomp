/*
 * EFF72.C  Effect 72: occasional stage animation parts
 *
 * effect_72_init (no arguments, from the stage code) places one brz_char_table object at
 * (0x19B, 80) and its effect 73 partner; effect_72_move runs two phases through a table while the game
 * runs (not during an OB roll) and draws with disp_pos_trans_entry_rs: eff72_00 shows animation
 * 13 until either player starts a super art, then eff72_01 plays animation 51 once and goes back.
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
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "eff73.h"
#include "EFF72.h"



void eff72_00(WORK_Other* ewk);
void eff72_01(WORK_Other* ewk);



/* two phases through a table (eff72_00, eff72_01) */
void effect_72_move(WORK_Other* ewk) {
    void (*jmp_tbl[2])() = { eff72_00, eff72_01 };
    if (!EXE_flag && !Game_pause) {
        jmp_tbl[ewk->wu.routine_no[0]](ewk);
    }
    disp_pos_trans_entry_rs(ewk);
}



/* effect 72 phase 0 */
/* provisional name */
void eff72_00(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 13);
        break;
    case 1:
        if (either_pl_hissatsu_check()) {
            ewk->wu.routine_no[0] = 1;
            ewk->wu.routine_no[1] = 0;
            break;
        }
        char_move(&ewk->wu);
        break;
    }
}



/* effect 72 phase 1 */
/* provisional name */
void eff72_01(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        set_char_move_init(&ewk->wu, 0, 51);
        break;
    case 1:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[0] = 0;
            ewk->wu.routine_no[1] = 0;
        }
        break;
    }
}



/* Create a brz_char_table object and its effect 73 partner. */
s32 effect_72_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 72;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 0x2058;
    ewk->wu.my_priority = 75;
    ewk->wu.position_z = 75;
    ewk->wu.sync_suzi = 0;
    ewk->wu.char_table[0] = brz_char_table;
    ewk->wu.xyz[0].disp.pos = 0x19B;
    ewk->wu.xyz[1].disp.pos = 80;
    suzi_offset_set(&ewk->wu);
    effect_73_init(ewk);
    return 0;
}
