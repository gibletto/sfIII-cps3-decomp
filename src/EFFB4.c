/*
 * EFFB4.C  Effect B4: ball hit spark
 *
 * Effect B4 (spawned by EFF09.c when the entrance ball hits a player) plays a random mark from
 * s_mark_tbl at its parent's position, then frees itself.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "aboutspr.h"
#include "effb9.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLS02.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFFB4.h"

/* routine_no[0] */
#define R0_INIT         0       /* pick a random mark and show it */
#define R0_MOVE         1       /* animate until the pattern's cue */
#define R0_END          2       /* one more frame */
#define R0_KILL         3       /* (default) put the work back */



/* Runs even while EXE_flag or Game_pause is set. */
void effect_B4_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.old_rno[0] = random_16_com();
        ewk->wu.old_rno[0] &= 0x1F;
        ewk->wu.char_index += s_mark_tbl[ewk->wu.old_rno[0]];
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R0_MOVE:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[0]++;
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case R0_END:
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
}



s32 effect_B4_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 114;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->my_master = (u32*)oya;
    ewk->master_id = 0;
    ewk->wu.my_col_mode = 0;
    ewk->wu.my_col_code = 0x20;
    ewk->wu.my_family = 2;
    ewk->wu.position_z = oya->wu.position_z - 1;
    ewk->wu.char_table[0] = etc_char_table;
    ewk->wu.char_index = 34;
    ewk->wu.sync_suzi = 0;
    ewk->wu.rl_flag = 0;
    ewk->wu.xyz[0].disp.pos = oya->wu.xyz[0].disp.pos;
    ewk->wu.xyz[1].disp.pos = oya->wu.xyz[1].disp.pos;
    suzi_offset_set(&ewk->wu);
    return 0;
}
