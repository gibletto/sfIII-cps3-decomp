/*
 * EFF03.C  Effect 03: player-attached move effects
 *
 * Effect 03 is a general effect attached to a player or to another effect, described by a
 * plef_data entry: display flag, facing, offset from the master, priority, colour, optional
 * shadow and whether it follows the master (eff03_disp_pos) or stays where it was placed.
 * It animates with plef_char_table until its script ends or it is killed.
 * effect_03_init is called from effects C9, D7, H9 and I8.
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
#include "EFF03.h"

/* routine_no[0] */
#define R0_INIT         0       /* set up from plef_data */
#define R0_MOVE         1       /* animate, following the master if asked */
#define R0_KILL         2       /* put the work back */



void effect_03_move(WORK_Other* ewk) {
    const PLEF* plef;
    s16* pos;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        plef = plef_data;
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = plef[ewk->wu.type].dspf;
        ewk->wu.blink_timing = ewk->master_id;
        if (plef[ewk->wu.type].sel_rl) {
            ewk->wu.rl_flag = ewk->wu.rl_waza;
        }
        if (ewk->wu.rl_flag) {
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos + plef[ewk->wu.type].hx;
        } else {
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos - plef[ewk->wu.type].hx;
        }
        ewk->wu.position_y = plef[ewk->wu.type].hy + ewk->wu.xyz[1].disp.pos;
        ewk->wu.position_z = ewk->wu.xyz[2].disp.pos + plef[ewk->wu.type].hz;
        if (plef[ewk->wu.type].sel_pri) {
            ewk->wu.position_z = plef[ewk->wu.type].hz;
        }
        if (plef[ewk->wu.type].sel_col) {
            ewk->wu.my_col_code = plef[ewk->wu.type].color | 0x2000;
        } else {
            ewk->wu.my_col_code += plef[ewk->wu.type].color;
        }
        if (plef[ewk->wu.type].mts) {
            ewk->wu.kage_flag = 1;
            ewk->wu.kage_hx = plef_kage_data[plef[ewk->wu.type].mts][0];
            ewk->wu.kage_hy = plef_kage_data[plef[ewk->wu.type].mts][1];
            ewk->wu.kage_prio = plef_kage_data[plef[ewk->wu.type].mts][2];
            ewk->wu.kage_char = plef_kage_data[plef[ewk->wu.type].mts][3];
        }
        set_char_move_init(&ewk->wu, 0, plef[ewk->wu.type].chix);
        if (plef[ewk->wu.type].ichi) {
            ewk->wu.xyz[0].disp.pos = plef[ewk->wu.type].hx;
            ewk->wu.xyz[1].disp.pos = plef[ewk->wu.type].hy;
            ewk->wu.xyz[2].disp.pos = plef[ewk->wu.type].hz;
            if (!ewk->wu.rl_flag) {
                pos = &ewk->wu.xyz[0].disp.pos;
                *pos = -*pos;
            }
        } else {
            ewk->wu.xyz[0].disp.pos = ewk->wu.position_x;
            ewk->wu.xyz[1].disp.pos = ewk->wu.position_y;
            ewk->wu.xyz[2].disp.pos = ewk->wu.position_z;
        }
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                if (ewk->wu.cg_type == 0xFF) {
                    ewk->wu.routine_no[0]++;
                    break;
                }
                ewk->wu.disp_flag = 2;
            }
        }
        eff03_disp_pos(&ewk->wu, (WORK*)ewk->my_master);
        sort_push_request(&ewk->wu);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
    }
}


void eff03_disp_pos(WORK* ewk, WORK* mwk) {
    if (plef_data[ewk->type].ichi) {
        ewk->position_x = mwk->position_x + ewk->xyz[0].disp.pos;
        ewk->position_y = mwk->position_y + ewk->xyz[1].disp.pos;
        ewk->position_z = mwk->position_z + ewk->xyz[2].disp.pos;
    } else {
        ewk->position_x = ewk->xyz[0].disp.pos;
        ewk->position_y = ewk->xyz[1].disp.pos;
    }
}



s32 effect_03_init(WORK* wk, u8 data) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 3;
    ewk->wu.work_id = 16;
    ewk->wu.type = data;
    ewk->wu.rl_waza = wk->rl_flag;
    ewk->wu.my_family = wk->my_family;
    ewk->wu.cgromtype = wk->cgromtype;
    ewk->wu.my_col_mode = wk->my_col_mode;
    ewk->wu.my_col_code = wk->my_col_code;
    ewk->my_master = (u32*)wk;
    if (wk->work_id == 1) {
        ewk->master_work_id = wk->work_id;
        ewk->master_id = wk->id;
    } else {
        ewk->master_work_id = ((WORK_Other*)wk)->master_work_id;
        ewk->master_id = ((WORK_Other*)wk)->master_id;
    }
    ewk->wu.xyz[0].disp.pos = wk->position_x;
    ewk->wu.xyz[1].disp.pos = wk->position_y;
    ewk->wu.xyz[2].disp.pos = wk->position_z;
    ewk->wu.char_table[0] = plef_char_table;
    return 0;
}
