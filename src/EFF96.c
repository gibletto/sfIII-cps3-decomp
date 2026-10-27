/*
 * EFF96.C  Effect 96: one-shot animation attached to a player or shell
 *
 * effect_96_init copies the owner's work id, facing, family, colour and position into a new
 * effect (list 3) with a given character index, and records the owning player and id (from
 * a player work or from another effect's master fields). effect_96_move plays the pattern from
 * ef13_char_table, honouring hit stop and the game pause, and frees itself when the pattern ends
 * or dead_f is set. Spawned by the shell effect EFF13.
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
#include "EFF96.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the pattern */
#define R0_MOVE         1       /* animate until the pattern ends */
#define R0_KILL         2       /* put the work back */



void effect_96_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.char_table[0] = ef13_char_table;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.disp_flag = 0;
            ewk->wu.routine_no[0]++;
        }
        if (ewk->wu.hit_stop) {
            ewk->wu.hit_stop--;
        } else if (EXE_flag == 0 && Game_pause == 0) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 0xFF) {
                ewk->wu.disp_flag = 0;
                ewk->wu.routine_no[0]++;
            }
        }
        sort_push_request(&ewk->wu);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_96_init(wk, chix, dspf, _p3)
WORK* wk;
u8 chix;
s8 dspf;
s32 _p3;
{
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 96;
    ewk->wu.work_id = wk->work_id;
    ewk->wu.blink_timing = wk->blink_timing;
    ewk->wu.char_index = chix;
    ewk->wu.disp_flag = dspf;
    ewk->wu.hit_stop = 0;
    ewk->wu.rl_flag = wk->rl_flag;
    ewk->wu.my_family = wk->my_family;
    ewk->wu.cgromtype = wk->cgromtype;
    ewk->wu.my_col_mode = wk->my_col_mode;
    ewk->wu.my_col_code = wk->my_col_code;
    ewk->wu.position_x = wk->position_x;
    ewk->wu.position_y = wk->position_y;
    ewk->wu.position_z = 26;
    if (wk->work_id == 1) {
        ewk->master_player = ((PLW*)wk)->player_number;
        ewk->master_id = wk->id;
    } else {
        ewk->master_player = ((WORK_Other*)wk)->master_player;
        ewk->master_id = ((WORK_Other*)wk)->master_id;
    }
    return 0;
}
