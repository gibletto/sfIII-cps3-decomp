/*
 * EFF70.C  Effect 70: the three pieces of the breakable stage object
 *
 * effect_70_init (from effect 69) places three pieces from eff70_data_tbl. effect_70_move follows the
 * state of the effect 69 object: on each new state a piece takes its animation for that state from
 * eff70_char_tbl. Piece 0 stays hidden until the first hit.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "CHARMOVE.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
void eff70_wait(WORK_Other* ewk);
void eff70_react(WORK_Other* ewk);
void eff70_broken(WORK_Other* ewk);
extern const u32 stg01_char_table[];
extern const s16 eff70_data_tbl[3][4];
extern const s16 eff70_char_tbl[3][4];
void (*eff70_jp[4])(WORK_Other*) = { eff70_wait, eff70_react, eff70_broken, eff70_broken };

void effect_70_move(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = ewk->wu.type == 0 ? 0 : 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        ewk->wu.routine_no[1] = oya->wu.routine_no[1];
        break;
    case 1:
        if (compel_dead_check(ewk)) {
            ewk->wu.routine_no[0] = 99;
            break;
        }
        if (!EXE_flag && !Game_pause) {
            if (oya->wu.routine_no[1] != ewk->wu.routine_no[1]) {
                ewk->wu.routine_no[2] = 0;
                ewk->wu.routine_no[1] = oya->wu.routine_no[1];
            }
            eff70_jp[ewk->wu.routine_no[1]](ewk);
        }
        disp_pos_trans_entry_rs(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

void eff70_wait(WORK_Other* ewk) {
}

void eff70_react(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.routine_no[2]++;
        switch (ewk->wu.type) {
        case 0:
            ewk->wu.disp_flag = 1;
            break;
        default:
            set_char_move_init(&ewk->wu, 0, eff70_char_tbl[ewk->wu.type][ewk->wu.routine_no[1]]);
            break;
        }
        break;
    case 1:
    default:
        break;
    }
}

void eff70_broken(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.routine_no[2]++;
        set_char_move_init(&ewk->wu, 0, eff70_char_tbl[ewk->wu.type][ewk->wu.routine_no[1]]);
        break;
    case 1:
    default:
        break;
    }
}

s32 effect_70_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data = eff70_data_tbl[0];
    for (i = 0; i < 3; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 70;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.type = i;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.sync_suzi = 0;
        ewk->wu.char_table[0] = stg01_char_table;
        ewk->my_master = (u32*)oya;
        ewk->wu.dead_f = 1;
        ewk->wu.my_family = 2;
        ewk->wu.my_col_code = 0x2040;
        ewk->wu.xyz[0].disp.pos = *data++;
        ewk->wu.xyz[1].disp.pos = *data++;
        ewk->wu.my_priority = ewk->wu.position_z = *data++;
        ewk->wu.char_index = *data++;
        suzi_offset_set(&ewk->wu);
    }
    return 0;
}
