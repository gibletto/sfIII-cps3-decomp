/*
 * EFFB1.C  Effect B1: the mark shown over effect B0
 *
 * effect_B1_init (from EFFB0) loads colour set 0x89 and makes a sprite on family 1 at x 0x200,
 * priority 10, owned by the effect B0 work. effect_B1_move plays pattern dir_step + 22 of its
 * owner with sound 105 and draws it for a frame or two; it leaves at once when the owner has
 * reached routine 3.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "CHARMOVE.h"
#include "se_3.h"
#include "EFFB1.h"
#include "EFFB1_INIT.h"

void load_any_color();



void effect_B1_move(WORK_Other* ewk) {
    WORK_Other* mwk = (WORK_Other*)ewk->my_master;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, mwk->wu.dir_step + 22);
        Sound_SE(105);
        disp_pos_trans_entry(ewk);
        break;
    case 1:
        if (mwk->wu.routine_no[0] == 3) {
            ewk->wu.routine_no[0] = 2;
            ewk->wu.disp_flag = 0;
        }
        ewk->wu.routine_no[0]++;
        disp_pos_trans_entry(ewk);
        break;
    case 2:
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_B1_init(PLW* wk) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    load_any_color(0x89);
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 111;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->my_master = (u32*)wk;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 1;
    *ewk->wu.char_table = etc_char_table;
    ewk->wu.my_col_code = 0x206E;
    ewk->wu.xyz[0].disp.pos = 0x200;
    ewk->wu.xyz[1].disp.pos = 0;
    ewk->wu.my_priority = ewk->wu.position_z = 10;
}
