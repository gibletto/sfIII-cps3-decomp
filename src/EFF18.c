/*
 * EFF18.C  Effect 18 (reacting stage objects)
 *
 * Effect 18 is a stage object with a behaviour routine: eff18_00 idles until a player performs a special move
 * and then hops, eff18_01 idles until a perfect victory and then plays its celebration animation. Nothing moves
 * while akebono_flag is set.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFF18.h"



/* object lists, named by their order in the ROM (provisional names) */
extern const s16 scr_obj_data18_0[];
extern const s16 scr_obj_data18_1[];
extern const s16 scr_obj_data18_2[];
extern const s16 scr_obj_data18_3[];
extern const s16 scr_obj_data18_4[];
extern const s16 scr_obj_data18_5[];
extern const s16 scr_obj_data18_6[];
extern const s16 scr_obj_data18_7[];

const s16* scr_obj_data18[6][4] = {
    { scr_obj_data18_0, scr_obj_data18_0, scr_obj_data18_0, scr_obj_data18_0 },
    { scr_obj_data18_1, scr_obj_data18_1, scr_obj_data18_1, scr_obj_data18_1 },
    { scr_obj_data18_2, scr_obj_data18_3, scr_obj_data18_2, scr_obj_data18_3 },
    { scr_obj_data18_4, scr_obj_data18_4, scr_obj_data18_5, scr_obj_data18_5 },
    { scr_obj_data18_6, scr_obj_data18_6, scr_obj_data18_6, scr_obj_data18_6 },
    { scr_obj_data18_7, scr_obj_data18_7, scr_obj_data18_7, scr_obj_data18_7 },
};
void (*eff18_jp_tbl[2])(WORK_Other*) = {
    eff18_00,
    eff18_01,
};



void effect_18_move(WORK_Other* ewk) {
    if (akebono_flag) {
        return;
    }
    if (compel_dead_check(ewk)) {
        ewk->wu.routine_no[0] = 99;
    } else {
        switch (ewk->wu.routine_no[0]) {
        case 0:
            ewk->wu.routine_no[0]++;
        case 1:
            if (!EXE_flag && !Game_pause) {
                eff18_jp_tbl[ewk->wu.routine_no[1]](ewk);
            }
            if (ewk->wu.old_rno[0]) {
                disp_pos_trans_entry_rs(ewk);
            } else {
                disp_pos_trans_entry_s(ewk);
            }
            break;
        default:
            all_cgps_put_back(ewk);
            push_effect_work((WORK*)ewk);
        }
    }
}



/* provisional name */
void eff18_00(WORK* wk) {
    switch (wk->routine_no[2]) {
    case 0:
        wk->routine_no[2]++;
        wk->disp_flag = 1;
        set_char_move_init(wk, 0, wk->dir_old);
    case 1:
        if (either_pl_hissatsu_check()) {
            wk->routine_no[2]++;
            wk->dir_timer = 5;
            wk->direction = 0;
        }
        if (wk->hit_stop) {
            char_move(wk);
        }
        break;
    case 2:
        wk->direction++;
        if (wk->cg_type) {
            wk->cg_type = 0;
            wk->dir_timer -= wk->direction;
            if (wk->dir_timer < 0) {
                wk->routine_no[2] = 4;
                set_char_move_init(wk, 0, wk->dir_step);
            } else {
                wk->routine_no[2]++;
            }
        }
        if (wk->hit_stop) {
            char_move(wk);
        }
        break;
    case 3:
        wk->dir_timer--;
        if (wk->dir_timer < 0) {
            wk->routine_no[2]++;
            set_char_move_init(wk, 0, wk->dir_step);
        }
        if (wk->hit_stop) {
            char_move(wk);
        }
        break;
    case 4:
        char_move(wk);
        if (wk->cg_type) {
            wk->cg_type = 0;
            wk->routine_no[2] = 0;
        }
        break;
    }
}



/* provisional name */
void eff18_01(WORK* wk) {
    switch (wk->routine_no[2]) {
    case 0:
        wk->routine_no[2]++;
        wk->disp_flag = 1;
        set_char_move_init(wk, 0, wk->dir_old);
    case 1:
        if (complete_victory_check()) {
            wk->routine_no[2]++;
        }
        if (wk->hit_stop) {
            char_move(wk);
        }
        break;
    case 2:
        wk->routine_no[2]++;
        set_char_move_init(wk, 0, wk->dir_step);
        break;
    case 3:
        char_move(wk);
        break;
    }
}



/* char_add by stage and area */
s32 effect_18_init(s16 disp_index, s16 cursor_id, s16 sync_bg, s16 master_player) {
    s16 i;
    s16 ix;
    s16 lp_cnt;
    const s16* data_ptr;
    WORK_Other* ewk;

    lp_cnt = scr_obj_num18[disp_index][bg_w.compel_flag];
    if (!lp_cnt) {
        return;
    }
    data_ptr = scr_obj_data18[disp_index][bg_w.compel_flag];
    for (i = 0; i < lp_cnt; i++) {
        ix = pull_effect_work(4);
        if (ix == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 18;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.dead_f = *data_ptr++;
        ewk->wu.my_family = *data_ptr++;
        ewk->wu.my_col_code = *data_ptr++;
        ewk->wu.xyz[0].disp.pos = *data_ptr++;
        ewk->wu.xyz[1].disp.pos = *data_ptr++;
        ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
        ewk->wu.dir_old = *data_ptr++;
        ewk->wu.dir_step = *data_ptr++;
        ewk->wu.hit_stop = *data_ptr++;
        ewk->wu.sync_suzi = *data_ptr++;
        ewk->wu.routine_no[1] = *data_ptr++;
        ewk->wu.old_rno[0] = *data_ptr++;
        ewk->wu.char_table[0] = char_add[bg_w.stage][bg_w.area];
        suzi_offset_set(&ewk->wu);
    }
    return 0;
}
