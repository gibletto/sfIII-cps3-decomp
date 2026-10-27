/*
 * EFFC7.C  Effect C7: the parry (blocking) mark
 *
 * effect_C7_init creates the mark for a player who has just parried, recording the parry type
 * and the player's character (ef01_char_table). effect_C7_move places it on its first frame at
 * the offset for that type and character in paring_mark_data (mirrored for facing) and chooses
 * its depth against the player, then plays the mark's pattern in the list-8 sort queue and frees
 * itself when the pattern ends or the work is killed. effc7_sort_push queues the sprite.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFC7.h"

/* routine_no[0] */
#define R0_INIT         0       /* place the mark */
#define R0_MOVE         1       /* play the mark */
#define R0_KILL         2       /* put the work back */






#pragma inline(effc7_sort_push)

void effect_C7_move(WORK_Other* ewk) {
    WORK* mwk = (WORK*)ewk->my_master;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.xyz[2].disp.pos = 26;
        ewk->wu.next_z = mwk->position_z;
        if (mwk->rl_flag) {
            ewk->wu.position_x = mwk->position_x + paring_mark_data[ewk->wu.direction][0];
        } else {
            ewk->wu.position_x = mwk->position_x - paring_mark_data[ewk->wu.direction][0];
        }
        ewk->wu.position_y = mwk->position_y + paring_mark_data[ewk->wu.direction][1];
        if (ewk->wu.position_z == ewk->wu.xyz[2].disp.pos) {
            ewk->wu.position_z = ewk->wu.next_z;
        } else {
            ewk->wu.position_z = ewk->wu.xyz[2].disp.pos;
        }
        set_char_move_init(&ewk->wu, 0, 0);
        effc7_sort_push(&ewk->wu, mwk);
        break;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 0xFF) {
                ewk->wu.routine_no[0]++;
                break;
            }
        }
        effc7_sort_push(&ewk->wu, mwk);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}





void effc7_sort_push(WORK* ewk, WORK* _p1) {
    sort_push_request8(ewk);
}



s32 effect_C7_init(PLW* wk, u8 data) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(2)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 127;
    ewk->wu.work_id = 64;
    ewk->wu.rl_flag = wk->wu.rl_flag;
    ewk->wu.direction = data;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2020;
    ewk->wu.my_family = wk->wu.my_family;
    ewk->my_master = (u32*)wk;
    ewk->master_id = wk->wu.id;
    ewk->master_work_id = wk->wu.work_id;
    ewk->master_player = wk->player_number;
    *ewk->wu.char_table = ef01_char_table;
    return 0;
}
