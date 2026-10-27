/*
 * EFF19.C  Effect 19: animated pieces shown by their parent's pattern
 *
 * effect_19_init (from effect 47) creates seven pieces under the parent work, placed from
 * eff19_data_tbl (position and priority), each with its own animation in eff19_char_table.
 * effect_19_move shows a piece only on its step of the parent's pattern (cg_ix): pieces 1-3 on
 * step 0, piece 4 on step 12, pieces 5 and 6 on step 16; piece 0 is never shown. A shown piece
 * plays its animation once (eff19_char_move) and hides again. The pieces stop during EXE_flag /
 * Game_pause and are freed by compel_dead_check.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"

/* routine_no[0] */
#define R0_INIT         0       /* hidden, note the parent's step */
#define R0_MOVE         1       /* show on the parent's step */
#define R0_KILL         99      /* (default) put the work back */

void eff19_char_move(WORK_Other* ewk);
extern const s16 eff19_data_tbl[7][3];
extern const u32 eff19_char_table[];

void effect_19_move(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;
    if (compel_dead_check(ewk)) {
        ewk->wu.routine_no[0] = R0_KILL;
    } else {
        switch (ewk->wu.routine_no[0]) {
        case R0_INIT:
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
            set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
            ewk->wu.direction = oya->wu.cg_ix;
            ewk->wu.dead_f = 1;
            break;
        case R0_MOVE:
            if (!EXE_flag && !Game_pause) {
                if (ewk->wu.type == 0) {
                    ewk->wu.disp_flag = 0;
                } else {
                    switch (oya->wu.cg_ix) {
                    case 0:
                        if (ewk->wu.type < 4) {
                            ewk->wu.disp_flag = 1;
                        }
                        break;
                    case 12:
                        if (ewk->wu.type == 4) {
                            ewk->wu.disp_flag = 1;
                        }
                        break;
                    case 16:
                        if (ewk->wu.type > 4) {
                            ewk->wu.disp_flag = 1;
                        }
                        break;
                    }
                    eff19_char_move(ewk);
                }
            }
            sort_push_request4(&ewk->wu);
            break;
        default:
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
            break;
        }
    }
}

void eff19_char_move(WORK_Other* ewk) {
    if (ewk->wu.disp_flag) {
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.cg_type = 0;
            ewk->wu.disp_flag = 0;
            char_move_z(&ewk->wu);
        }
    }
}

s32 effect_19_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    data = eff19_data_tbl[0];
    for (i = 0; i < 7; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 19;
        ewk->wu.cgromtype = 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.work_id = 16;
        ewk->my_master = (u32*)oya;
        ewk->wu.type = i;
        ewk->wu.char_index = i;
        ewk->wu.my_family = 2;
        ewk->wu.position_x = *data++;
        ewk->wu.position_y = *data++;
        ewk->wu.my_priority = ewk->wu.position_z = *data++;
        ewk->wu.char_table[0] = eff19_char_table;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2040;
        ewk->wu.sync_suzi = 0;
        ewk->wu.cg_ix = 0;
    }
    return 0;
}
