/*
 * EFF62.C  Effect 62: companion figure
 *
 * effect_62_init (from effect 61) places the figure from eff62_layout_tbl with the result character
 * table. effect_62_move animates it while its master is in states 1 (except steps 2 and 3), 3, 5 and
 * 6 and leaves it undrawn otherwise. For the result (type set) it plays pattern 22 when the side it
 * belongs to (the master's old_rno[0], flipped) won the round (get_winner_id) and pattern 21 when that
 * side lost.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "bg_sub.h"
#include "bg_sub_5.h"
#include "ta_sub.h"
#include "EFF62.h"

/* routine_no[0] */
#define R0_INIT         0       /* set up from the master */
#define R0_MOVE         1       /* animate with the master */

/* routine_no[2] */
#define R2_INIT         0       /* pick the win or lose pose */
#define R2_ANIM         1       /* animate */

s16 get_winner_id(void);
void eff62_normal(WORK_Other* ewk);
void eff62_result(WORK_Other* ewk);

const s16 eff62_layout_tbl[2][5] = {
    { 88, 448, 58, 77, 0 },
    { 0x2058, 536, 64, 77, 20 }
};

void effect_62_move(WORK_Other* ewk) {
    WORK* mwk;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.routine_no[1] = 0;
        ewk->wu.routine_no[2] = R2_INIT;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        mwk = (WORK*)ewk->my_master;
        ewk->wu.old_rno[0] = mwk->old_rno[0] ^ 1;
    case R0_MOVE:
        if (ewk->wu.type) {
            eff62_result(ewk);
        } else {
            eff62_normal(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}

void eff62_normal(WORK_Other* ewk) {
    WORK* mwk = (WORK*)ewk->my_master;
    switch (mwk->routine_no[0]) {
    case 1:
        switch (mwk->routine_no[1]) {
        case 2:
        case 3:
            break;
        default:
            if (!EXE_flag && !Game_pause) {
                char_move(&ewk->wu);
            }
            disp_pos_trans_entry_rs(ewk);
            break;
        }
        break;
    case 2:
    case 4:
        break;
    case 3:
    case 5:
    case 6:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
        }
        disp_pos_trans_entry_rs(ewk);
        break;
    }
}

void eff62_result(WORK_Other* ewk) {
    WORK* mwk = (WORK*)ewk->my_master;
    s16 winner;
    switch (mwk->routine_no[0]) {
    case 1:
        char_move(&ewk->wu);
        disp_pos_trans_entry_rs(ewk);
        return;
    }
    switch (ewk->wu.routine_no[2]) {
    case R2_INIT:
        winner = get_winner_id();
        if (winner == ewk->wu.old_rno[0]) {
            set_char_move_init(&ewk->wu, 0, 22);
        } else {
            set_char_move_init(&ewk->wu, 0, 21);
        }
        ewk->wu.routine_no[2]++;
        break;
    case R2_ANIM:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
        }
        break;
    }
    disp_pos_trans_entry_rs(ewk);
}

s32 effect_62_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    const s16* data_ptr = eff62_layout_tbl[0];
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 62;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.type = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->my_master = (u32*)oya;
    ewk->wu.my_family = 2;
    ewk->wu.sync_suzi = 0;
    ewk->wu.my_col_code = *data_ptr++;
    ewk->wu.xyz[0].disp.pos = *data_ptr++;
    ewk->wu.xyz[1].disp.pos = *data_ptr++;
    ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
    ewk->wu.char_index = *data_ptr;
    ewk->wu.char_table[0] = result_char_table;
    suzi_offset_set(&ewk->wu);
    return 0;
}
