/*
 * EFF52.C  Effect 52: the stage marker of the select screen
 *
 * effect_52_init places sel_pl_char_table pattern 5 at the Battle_Country position of eff52_pos_tbl and loads
 * colours 86-94; effect_52_move shows it after one frame, plays the pattern until it ends (then Next_Step), and
 * removes it on a Suicide request.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "bg_sub_5.h"
#include "Eff52.h"

/* routine_no[0] */
#define R0_WAIT         0       /* count the delay down, then show */
#define R0_PLAY         1       /* play the pattern, then step on */
#define R0_MOVE         2       /* stay until told to go */
#define R0_KILL         3       /* (default) put the work back */

extern const s16 eff52_pos_tbl[];

void load_any_color();



void effect_52_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_WAIT:
        if (--ewk->wu.dir_timer) {
            return;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R0_PLAY:
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[0]++;
            Next_Step = 1;
        } else {
            char_move(&ewk->wu);
        }
        break;
    case R0_MOVE:
        if (Suicide) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
    suzi_sync_pos_set(ewk);
    sort_push_request4(&ewk->wu);
}



s32 effect_52_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 52;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4600;
    ewk->wu.my_col_code = 0;
    ewk->wu.my_family = 1;
    ewk->wu.my_priority = 80;
    ewk->wu.position_z = 80;
    ewk->wu.char_table[0] = sel_pl_char_table;
    ewk->wu.char_index = 5;
    ewk->wu.xyz[0].disp.pos = eff52_pos_tbl[Battle_Country * 2];
    ewk->wu.xyz[1].disp.pos = eff52_pos_tbl[Battle_Country * 2 + 1];
    ewk->wu.dir_timer = 1;
    for (i = 86; i < 95; i++) {
        load_any_color(i);
    }
    ewk->wu.sync_suzi = 1;
    suzi_offset_set(&ewk->wu);
    return 0;
}
