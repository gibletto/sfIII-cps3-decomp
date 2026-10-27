/*
 * EFFA9.C  Effect A9: select-screen plate marker
 *
 * effect_A9_init ties the marker to a player and slot (master_id, master_player).
 * effect_A9_move builds its cells with effB8_conn_set for the player's character
 * and follows Plate_X / Plate_Y until sel_plate_state reads 52.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "aboutspr.h"
#include "sc_trans.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "Eff59.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "sc_sub.h"
#include "sc_sub_2.h"
#include "PLS02.h"
#include "effa9.h"

/* routine_no[0] */
#define R0_INIT         0       /* build the cells and show */
#define R0_MOVE         1       /* follow the plate until it is done */
#define R0_KILL         99      /* (default) put the work back */

extern s16 sel_plate_state[2][3];   /* provisional name */
void effB8_conn_set();   /* provisional name */



/* the select-screen plate marker */
void effect_A9_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        effB8_conn_set((WORK_Other_CONN*)ewk, My_char[ewk->master_id], ewk->master_player + 3);
        /* fall through */
    case R0_MOVE:
        if (sel_plate_state[ewk->master_id][ewk->master_player] == 52) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
        ewk->wu.position_x = Plate_X[ewk->master_id][ewk->master_player] - 8;
        ewk->wu.position_y = Plate_Y[ewk->master_id][ewk->master_player] - 5;
        sort_push_request3(&ewk->wu);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* (player, slot) */
s32 effect_A9_init(s8 PL_id, s16 slot) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 109;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 124;
    ewk->wu.my_family = 3;
    ewk->wu.char_table[0] = sel_pl_char_table;
    ewk->master_id = PL_id;
    ewk->master_player = slot;
    ewk->wu.position_z = 43;
    return 0;
}
