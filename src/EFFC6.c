/*
 * EFFC6.C  Effect C6: overlay part of the entrance car
 *
 * effect_C6_init (called by effect_C5_init) creates a sprite that rides with the entrance car C5,
 * one priority step in front of it, with the same palette and facing. effect_C6_move copies the
 * car's x each frame and plays pattern 10 while the car drives in; when the car stops it plays
 * pattern 11 (pattern 19 when the opponent is character 0x11) and hides once that pattern
 * signals its end.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFFC6.h"

/* routine_no[0] */
#define R0_INIT         0       /* start pattern 10 */
#define R0_DRIVE        1       /* ride with the car */
#define R0_STOP         2       /* play the stop pattern */
#define R0_END          3       /* one more frame */
#define R0_KILL         4       /* (default) put the work back */



/* Runs even while EXE_flag or Game_pause is set; it shows pattern 11 once its master reaches step 2. */
void effect_C6_move(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 10);
        break;
    case R0_DRIVE:
        if (oya->wu.routine_no[0] >= 2) {
            ewk->wu.routine_no[0]++;
            set_char_move_init(&ewk->wu, 0, 11);
        } else {
            char_move(&ewk->wu);
        }
        ewk->wu.xyz[0].cal = oya->wu.xyz[0].cal;
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case R0_STOP:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[0]++;
        }
        ewk->wu.xyz[0].cal = oya->wu.xyz[0].cal;
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case R0_END:
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_C6_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 126;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.disp_flag = 0;
    ewk->my_master = (u32*)oya;
    ewk->wu.my_family = 2;
    ewk->wu.char_index = 10;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_priority = ewk->wu.position_z = oya->wu.my_priority - 1;
    ewk->wu.xyz[0].cal = oya->wu.xyz[0].cal;
    ewk->wu.xyz[1].cal = oya->wu.xyz[1].cal;
    ewk->wu.rl_flag = oya->wu.rl_flag;
    ewk->wu.char_table[0] = etc_char_table;
    ewk->wu.my_col_code = oya->wu.my_col_code;
    suzi_offset_set(&ewk->wu);
}
