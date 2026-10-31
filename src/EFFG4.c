/*
 * EFFG4.C  Effect G4: one-shot effect placed from gill_eff_data
 *
 * effect_G4_init creates the effect at its master's position with the master's palette and
 * facing (plef_char_table); the entry number selects a record in gill_eff_data, and the next
 * record is used when the master faces left. From entry 38 the palette's 0x2000 bit is cleared.
 * effect_G4_move applies the record's x/y/z offset and pattern, plays it once and frees itself.
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
#include "EFFG4.h"

/* routine_no[0] */
#define R0_INIT         0       /* place from the record */
#define R0_MOVE         1       /* play the pattern once */
#define R0_KILL         2       /* put the work back */



void effect_G4_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        if (ewk->wu.rl_flag) {
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos + gill_eff_data[ewk->wu.type].hx;
        } else {
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos - gill_eff_data[ewk->wu.type].hx;
        }
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos + gill_eff_data[ewk->wu.type].hy;
        ewk->wu.position_z = ewk->wu.xyz[2].disp.pos + gill_eff_data[ewk->wu.type].hz;
        set_char_move_init(&ewk->wu, 0, gill_eff_data[ewk->wu.type].chix);
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
        sort_push_request(&ewk->wu);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_G4_init(WORK* wk, u8 data) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 164;
    ewk->wu.work_id = 16;
    ewk->wu.type = data;
    ewk->wu.rl_flag = wk->rl_flag;
    ewk->wu.my_family = wk->my_family;
    ewk->wu.cgromtype = wk->cgromtype;
    ewk->wu.my_col_mode = wk->my_col_mode;
    ewk->wu.my_col_code = wk->my_col_code;
    if (wk->rl_flag) {
        ewk->wu.type++;
    }
    ewk->my_master = (u32*)wk;
    ewk->master_work_id = wk->work_id;
    ewk->master_id = wk->id;
    ewk->wu.xyz[0].disp.pos = wk->position_x;
    ewk->wu.xyz[1].disp.pos = wk->position_y;
    ewk->wu.xyz[2].disp.pos = wk->position_z;
    ewk->wu.char_table[0] = plef_char_table;
    return 0;
}
