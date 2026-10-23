/*
 * EFF46.C  Effect 46: appearance object that flies off
 *
 * Effect 46 is a small object beside a winner (effect_46_init takes the owner's colour,
 * pose side and position): it picks one of eight patterns at random, runs its animation (twice
 * as fast while pl_shot_on_check is set for its master), switches to the chosen pattern at
 * cg_type 1, then at cg_type 9 sets win_rno[1] and frees itself.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLS02.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFF46.h"



extern const s16 eff46_char_tbl[8];



void effect_46_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        ewk->wu.old_rno[0] = random_16_com();
        ewk->wu.old_rno[0] &= 7;
        ewk->wu.old_rno[0] = eff46_char_tbl[ewk->wu.old_rno[0]];
        break;
    case 1:
        char_move(&ewk->wu);
        if (pl_shot_on_check(ewk->master_id)) {
            char_move(&ewk->wu);
        }
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[0]++;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[0]);
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case 2:
        char_move(&ewk->wu);
        if (pl_shot_on_check(ewk->master_id)) {
            char_move(&ewk->wu);
        }
        if (ewk->wu.cg_type == 9) {
            ewk->wu.routine_no[0]++;
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case 3:
        win_rno[1] = 1;
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



s32 effect_46_init(WORK* wk) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 46;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->my_master = (u32*)wk;
    ewk->master_id = wk->id;
    ewk->wu.my_col_mode = wk->my_col_mode;
    ewk->wu.my_col_code = wk->my_col_code;
    ewk->wu.my_family = 2;
    ewk->wu.position_z = wk->position_z - 1;
    *ewk->wu.char_table = etc2_char_table;
    ewk->wu.char_index = 0;
    ewk->wu.sync_suzi = 0;
    if (wk->rl_flag) {
        ewk->wu.rl_flag = 0;
        ewk->wu.xyz[0].disp.pos = wk->xyz[0].disp.pos + 64;
    } else {
        ewk->wu.rl_flag = 1;
        ewk->wu.xyz[0].disp.pos = wk->xyz[0].disp.pos - 64;
    }
    ewk->wu.xyz[1].disp.pos = wk->xyz[1].disp.pos + 96;
    suzi_offset_set(&ewk->wu);
    return 0;
}
