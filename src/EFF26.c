/*
 * EFF26.C  Effect 26: parts of breakable stage objects
 *
 * Effect 26 works belong to an effect 25 object. The eff26_* routines keep them animating
 * while the parent is intact and, when the parent is broken, play their own break animation
 * and throw out pieces (piece_set, effect 27, and effect 28).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "eff28.h"
#include "EFF29.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "EFF27.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFF25.h"
#include "aboutspr.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFF26.h"

/* routine_no[0] */
#define R0_INIT         0       /* show and start the animation */
#define R0_MOVE         1       /* run the part's behaviour routine */
#define R0_END          2       /* one more frame */
#define R0_KILL         99      /* (default) put the work back */

/* routine_no[1], eff26_01: break with the parent */
#define R1_INIT         0       /* check for an already broken parent */
#define R1_STAND        1       /* until the parent breaks */
#define R1_BREAK        2       /* play the break animation */

/* routine_no[1], eff26_02: break and stay */
#define R1_REMAINS      3       /* animate the broken form */

/* routine_no[1], eff26_03: a target once the parent breaks */
#define R1_ARM          3       /* show as a target, unless broken */
#define R1_TARGET       4       /* until a player hits it */

/* routine_no[1], eff26_04: a target once the parent breaks */
#define R1_WHOLE        0       /* until the parent breaks */
#define R1_CRACK        1       /* break animation to its end */
#define R1_CHECK        2       /* a target from now, unless broken */
#define R1_HIT          3       /* until a player hits it */
#define R1_LAST         4       /* last animation, then go */

/* routine_no[1], eff26_05: breaks twice */
#define R1_SMASH        5       /* second break animation */
#define R1_DONE         6       /* stay broken */
#define R1_WRECK        7       /* animate the broken form */



/* 02006C74 */
void (*eff26_jp_tbl[6])(WORK_Other*) = {
    eff26_00,
    eff26_01,
    eff26_02,
    eff26_03,
    eff26_04,
    eff26_05,
};
/* Object records for the two part types. */
const s16* scr_obj_data26[2] = {
    scr_obj_data26_0,
    scr_obj_data26_1,
};


void effect_26_move(WORK_Other* ewk) {
    if (compel_dead_check(ewk)) {
        ewk->wu.routine_no[0] = R0_KILL;
    } else {
        switch (ewk->wu.routine_no[0]) {
        case R0_INIT:
            ewk->wu.routine_no[0]++;
            ewk->wu.routine_no[1] = 0;
            ewk->wu.disp_flag = 1;
            set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
            break;
        case R0_MOVE:
            if (!EXE_flag && !Game_pause) {
                eff26_jp_tbl[ewk->wu.old_rno[2] / 2](ewk);
            }
            disp_pos_trans_entry_rs(ewk);
            break;
        case R0_END:
            ewk->wu.routine_no[0]++;
            break;
        default:
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
            break;
        }
    }
}



void eff26_00(WORK_Other* ewk) {
    WORK_Other* self = ewk;
    ewk = (WORK_Other*)self->my_master;
    if (ewk->wu.routine_no[1] > 1) {
        self->wu.routine_no[0] = R0_END;
        piece_set(self);
        return;
    } else if (self->wu.hit_stop) {
        char_move(&self->wu);
    }
}



void eff26_01(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
    case R1_STAND:
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        if (oya->wu.routine_no[1] > 1) {
            ewk->wu.routine_no[1]++;
            piece_set(ewk);
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
        }
        break;
    case R1_BREAK:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[0] = R0_END;
        }
        break;
    }
}



void eff26_02(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[1] = R1_REMAINS;
            ewk->wu.disp_flag = 1;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[7]);
            break;
        }
    case R1_STAND:
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        if (oya->wu.routine_no[1] > 1) {
            ewk->wu.routine_no[1]++;
            piece_set(ewk);
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
        }
        break;
    case R1_BREAK:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case R1_REMAINS:
        char_move(&ewk->wu);
        break;
    }
}

void eff26_03(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;

    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[1] = R1_ARM;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
            goto case_3;
        }
    case R1_STAND:
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        if (oya->wu.routine_no[1] > 1) {
            ewk->wu.routine_no[1]++;
            piece_set(ewk);
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
            return;
        }
        break;
    case R1_BREAK:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case R1_ARM:
    case_3:
        ewk->wu.routine_no[1]++;
        if (eff_hit_flag[ewk->wu.type]) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
        ewk->wu.disp_flag = 1;
    case R1_TARGET:
        if (eff_hit_check(ewk, ewk->wu.old_rno[4])) {
            if (ewk->wu.old_rno[2] & 1) {
                if (ewk->wu.old_rno[5] > 0) {
                    effect_27_init(ewk, ewk->wu.old_rno[5]);
                }
            }
            ewk->wu.routine_no[0] = R0_END;
        }
        break;
    }
}



void eff26_04(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;
    switch (ewk->wu.routine_no[1]) {
    case R1_WHOLE:
        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[1] = R1_CHECK;
            goto case_2;
        }
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        if (oya->wu.routine_no[1] > 1) {
            ewk->wu.routine_no[1]++;
            piece_set(ewk);
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
        }
        break;
    case R1_CRACK:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case R1_CHECK:
    case_2:
        ewk->wu.routine_no[1]++;
        if (eff_hit_flag[ewk->wu.type]) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
    case R1_HIT:
        if (eff_hit_check(ewk, ewk->wu.old_rno[4])) {
            ewk->wu.routine_no[1]++;
            if (ewk->wu.old_rno[2] & 1) {
                if (ewk->wu.old_rno[5] > 0) {
                    effect_27_init(ewk, ewk->wu.old_rno[5]);
                }
            }
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[3]);
        }
    case R1_LAST:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[0] = R0_END;
        }
        break;
    }
}



void eff26_05(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;

    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[2] = 3;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
            goto case_3;
        }
    case R1_STAND:
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        if (oya->wu.routine_no[1] > 1) {
            ewk->wu.routine_no[1]++;
            piece_set(ewk);
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
        }
        break;
    case R1_BREAK:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case R1_ARM:
    case_3:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        if (eff_hit_flag[ewk->wu.type]) {
            ewk->wu.routine_no[1] = R1_WRECK;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[7]);
            break;
        }
    case R1_TARGET:
        if (eff_hit_check(ewk, ewk->wu.old_rno[4])) {
            ewk->wu.routine_no[1]++;
            if (ewk->wu.old_rno[2] & 1) {
                if (ewk->wu.old_rno[5] > 0) {
                    effect_27_init(ewk, ewk->wu.old_rno[5]);
                }
            }
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[3]);
        }
        break;
    case R1_SMASH:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case R1_DONE:
        break;
    case R1_WRECK:
        char_move(&ewk->wu);
        break;
    }
}



/* char_add by stage and area */
s32 effect_26_init(WORK_Other* oya, s16 type26) {
    WORK_Other* ewk;
    s16 ix;
    s16 lp_cnt = eff26_num[type26];
    s16 i;
    const s16* data_ptr;
    if (lp_cnt) {
        if (!type26) {
            effect_28_init(oya);
        }
        data_ptr = scr_obj_data26[type26];
        for (i = 0; i < lp_cnt; i++) {
            if ((ix = pull_effect_work(4)) == -1) {
                return -1;
            }
            ewk = (WORK_Other*)frw[ix];
            ewk->wu.be_flag = 1;
            ewk->wu.id = 26;
            ewk->wu.work_id = 16;
            ewk->my_master = (u32*)oya;
            ewk->wu.cgromtype = 1;
            ewk->wu.rl_flag = 0;
            ewk->wu.my_col_mode = 0x4200;
            ewk->wu.dead_f = *data_ptr++;
            ewk->wu.type = (s8)*data_ptr++;
            ewk->wu.my_family = *data_ptr++;
            ewk->wu.my_col_code = *data_ptr++;
            ewk->wu.xyz[0].disp.pos = *data_ptr++;
            ewk->wu.xyz[1].disp.pos = *data_ptr++;
            ewk->wu.position_z = *data_ptr++;
            ewk->wu.char_index = *data_ptr++;
            ewk->wu.hit_stop = *data_ptr++;
            ewk->wu.sync_suzi = *data_ptr++;
            ewk->wu.old_rno[0] = *data_ptr++;
            ewk->wu.old_rno[1] = *data_ptr++;
            ewk->wu.old_rno[2] = *data_ptr++;
            ewk->wu.old_rno[3] = *data_ptr++;
            ewk->wu.old_rno[7] = *data_ptr++;
            ewk->wu.old_rno[4] = *data_ptr++;
            ewk->wu.old_rno[5] = *data_ptr++;
            ewk->wu.char_table[0] = char_add[bg_w.stage][bg_w.area];
            suzi_offset_set((WORK*)ewk);
        }
        return 0;
    }
}
