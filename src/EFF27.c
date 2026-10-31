/*
 * EFF27.C  Effect 27: flying pieces of broken stage objects
 *
 * Effect 27 is a fragment thrown out when a stage object breaks. eff27_jp_tbl selects a
 * motion: fly and fall, fly for a time, bounce with a second hop (set_second_hop), or land
 * and play a follow-up animation. dead_check27 removes pieces that have left the screen.
 * effect_27_init is called from effects 25, 26 and J6.
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
#include "EFF27.h"

/* routine_no[0] */
#define R0_INIT         0       /* show and note the parent's state */
#define R0_MOVE         1       /* run the piece's motion routine */
#define R0_END          2       /* one more frame */
#define R0_KILL         99      /* (default) put the work back */

/* routine_no[1], eff27_00: fly and lie */
#define R1_FLY          0       /* fly until it reaches the floor */
#define R1_LIE          1       /* lie on the floor */

/* routine_no[1], eff27_03: fly, hop and rest */
#define R1_HOP          1       /* second hop down to the floor */
#define R1_REST         2       /* until the parent moves on */

/* routine_no[1], eff27_04: fly, land and rest */
#define R1_LAND         1       /* landing animation to its end */

/* routine_no[1], eff27_06: animate in place */
#define R1_ANIM         0       /* animate to the end of the script */
#define R1_HOLD         1       /* hold the last frame */

/* routine_no[1], eff27_08: fly and scatter */
#define R1_SCATTER      1       /* throw out more pieces */
#define R1_LEAVE        2       /* take the piece away */

/* routine_no[1], eff27_09: two animations */
#define R1_NEXT         1       /* move into place, next animation */



extern const s16 scr_obj_data27_0[][19];
extern const s16 scr_obj_data27_1[][19];
extern const s16 scr_obj_data27_2[][19];
extern const s16 scr_obj_data27_3[][19];
extern const s16 scr_obj_data27_4[][19];
extern const s16 scr_obj_data27_5[][19];
extern const s16 scr_obj_data27_6[][19];

/* seven object types */
const s16* scr_obj_data27[7] = {
    scr_obj_data27_0[0],
    scr_obj_data27_1[0],
    scr_obj_data27_2[0],
    scr_obj_data27_3[0],
    scr_obj_data27_4[0],
    scr_obj_data27_5[0],
    scr_obj_data27_6[0],
};
/* 02006BA0 */
void (*eff27_jp_tbl[11])(WORK_Other*) = {
    eff27_00,
    eff27_00,
    eff27_02,
    eff27_03,
    eff27_04,
    eff27_05,
    eff27_06,
    eff27_06,
    eff27_07,
    eff27_08,
    eff27_09,
};


void effect_27_move(WORK_Other* ewk) {
    WORK_Other* oya;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.routine_no[1] = 0;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        oya = (WORK_Other*)ewk->my_master;
        ewk->wu.old_rno[3] = oya->wu.routine_no[1];
    case R0_MOVE:
        if (compel_dead_check(ewk)) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
        if (!EXE_flag && !Game_pause) {
            eff27_jp_tbl[ewk->wu.old_rno[0]](ewk);
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



void eff27_00(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_FLY:
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos < ewk->wu.old_rno[1]) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case R1_LIE:
        if (!ewk->wu.old_rno[0]) {
            dead_check27(ewk);
        }
        break;
    }
}



void eff27_02(WORK_Other* ewk) {
    if (ewk->wu.hit_stop) {
        char_move(&ewk->wu);
    }
    add_x_sub(ewk);
    add_y_sub(ewk);
    ewk->wu.old_rno[1]--;
    if (ewk->wu.old_rno[1] < 0) {
        ewk->wu.routine_no[0] = R0_END;
    }
}



void eff27_03(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_FLY:
        if (ewk->wu.cg_type != 2) {
            char_move(&ewk->wu);
        }
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos < ewk->wu.old_rno[1]) {
            char_move_z(&ewk->wu);
            ewk->wu.routine_no[1]++;
            set_second_hop(ewk);
        }
        break;
    case R1_HOP:
        if (ewk->wu.cg_type != 2) {
            char_move(&ewk->wu);
        }
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos <= ewk->wu.old_rno[2]) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case R1_REST:
        if (ewk->wu.cg_type != 1) {
            char_move(&ewk->wu);
        }
        dead_check27(ewk);
        break;
    }
}



void eff27_04(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_FLY:
        if (ewk->wu.cg_type != 2) {
            char_move(&ewk->wu);
        }
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos < ewk->wu.old_rno[1]) {
            char_move_z(&ewk->wu);
            ewk->wu.routine_no[1]++;
        }
        break;
    case R1_LAND:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case R1_REST:
        dead_check27(ewk);
        break;
    }
}



void eff27_05(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_FLY:
        if (ewk->wu.cg_type != 2) {
            char_move(&ewk->wu);
        }
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos < ewk->wu.old_rno[1]) {
            char_move_z(&ewk->wu);
            ewk->wu.routine_no[1]++;
        }
        break;
    case R1_LAND:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 1) {
            ewk->wu.routine_no[1]++;
            set_second_hop(ewk);
        }
        break;
    case R1_REST:
        eff27_03(ewk);
        break;
    }
}



void eff27_06(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_ANIM:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type != 1) {
            break;
        }
        if (ewk->wu.old_rno[0] == 6) {
            ewk->wu.routine_no[1]++;
            break;
        }
        ewk->wu.routine_no[0] = R0_END;
        break;
    case R1_HOLD:
        break;
    }
}



void eff27_07(WORK_Other* ewk) {
    const s16* ptr;
    switch (ewk->wu.routine_no[1]) {
    case R1_FLY:
        if (ewk->wu.cg_type != 2) {
            char_move(&ewk->wu);
        }
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos < ewk->wu.old_rno[1]) {
            char_move_z(&ewk->wu);
            ewk->wu.routine_no[1]++;
            ewk->wu.xyz[1].disp.pos = ewk->wu.old_rno[1];
            ewk->wu.mvxy.d[0].sp = ewk->wu.mvxy.d[0].sp >> 1;
            ewk->wu.mvxy.d[1].sp = ewk->wu.mvxy.d[1].sp >> 1;
            ptr = scr_obj_data27[ewk->wu.type];
            ptr += 11;
            ptr += ewk->wu.direction * 19;
            *(s16*)&ewk->wu.mvxy.a[0] = *ptr++;
            ewk->wu.mvxy.a[0].real.l = *ptr++;
            ptr += 2;
            ewk->wu.mvxy.a[1].real.h = *ptr++;
            ewk->wu.mvxy.a[1].real.l = *ptr++;
            ewk->wu.mvxy.a[0].sp = ewk->wu.mvxy.a[0].sp >> 1;
            ewk->wu.mvxy.a[1].sp = ewk->wu.mvxy.a[1].sp << 1;
        }
        break;
    case R1_HOP:
        if (ewk->wu.cg_type != 2) {
            char_move(&ewk->wu);
        }
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[1].disp.pos <= ewk->wu.old_rno[2]) {
            ewk->wu.routine_no[1]++;
            effect_27_init(ewk, 3);
        }
        break;
    case R1_REST:
        if (ewk->wu.cg_type != 1) {
            char_move(&ewk->wu);
        }
        dead_check27(ewk);
        break;
    }
}



void eff27_08(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_FLY:
        eff27_03(ewk);
        break;
    case R1_SCATTER:
        effect_27_init(ewk, 4);
        ewk->wu.routine_no[1]++;
        break;
    case R1_LEAVE:
        ewk->wu.routine_no[0] = R0_END;
        break;
    }
}



void eff27_09(WORK* wk) {
    switch (wk->routine_no[1]) {
    case R1_ANIM:
        char_move(wk);
        if (wk->cg_type == 1) {
            wk->routine_no[1]++;
            wk->xyz[0].disp.pos = wk->old_rno[1];
            wk->xyz[1].disp.pos = wk->old_rno[2];
            if (*(s16*)&wk->mvxy.a[0] > 0) {
                set_char_move_init(wk, 0, *(s16*)&wk->mvxy.a[0]);
            }
        }
        break;
    case R1_NEXT:
        char_move(wk);
        break;
    }
}



void set_second_hop(WORK_Other* ewk) {
    const s16* ptr;
    ewk->wu.xyz[1].disp.pos = ewk->wu.old_rno[1];
    ewk->wu.mvxy.d[0].sp = ewk->wu.mvxy.d[0].sp >> 1;
    ewk->wu.mvxy.d[1].sp = ewk->wu.mvxy.d[1].sp >> 1;
    ptr = scr_obj_data27[ewk->wu.type];
    ptr += 11;
    ptr += ewk->wu.direction * 19;
    *(s16*)&ewk->wu.mvxy.a[0] = *ptr++;
    ewk->wu.mvxy.a[0].real.l = *ptr++;
    ptr += 2;
    ewk->wu.mvxy.a[1].real.h = *ptr++;
    ewk->wu.mvxy.a[1].real.l = *ptr++;
    ewk->wu.mvxy.a[0].sp = ewk->wu.mvxy.a[0].sp >> 1;
    ewk->wu.mvxy.a[1].sp = ewk->wu.mvxy.a[1].sp >> 1;
}



void dead_check27(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;
    if (ewk->wu.old_rno[3] != oya->wu.routine_no[1]) {
        ewk->wu.routine_no[0] = R0_END;
    }
}



s32 effect_27_init(WORK_Other* oya, s16 type) {
    s16 lp_cnt;
    s16 i;
    s16 ix;
    const s16* data_ptr;
    WORK_Other* ewk;

    lp_cnt = scr_obj_num27[type];
    if (lp_cnt) {
        data_ptr = scr_obj_data27[type];
        for (i = 0; i < lp_cnt; i++) {
            ix = pull_effect_work(4);
            if (ix == -1) {
                return -1;
            }
            ewk = (WORK_Other*)frw[ix];
            ewk->my_master = (u32*)oya;
            ewk->wu.be_flag = 1;
            ewk->wu.id = 0x1B;
            ewk->wu.work_id = 0x10;
            ewk->wu.cgromtype = 1;
            ewk->wu.rl_flag = 0;
            ewk->wu.my_col_mode = 0x4200;
            ewk->wu.type = type;
            ewk->wu.direction = i;
            ewk->wu.dead_f = 1;
            ewk->wu.my_family = *data_ptr++;
            ewk->wu.my_col_code = *data_ptr++;
            ewk->wu.xyz[0].disp.pos = *data_ptr++;
            ewk->wu.xyz[1].disp.pos = *data_ptr++;
            ewk->wu.xyz[0].disp.pos += oya->wu.xyz[0].disp.pos;
            ewk->wu.xyz[1].disp.pos += oya->wu.xyz[1].disp.pos;
            ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
            ewk->wu.char_index = *data_ptr++;
            ewk->wu.hit_stop = *data_ptr++;
            ewk->wu.sync_suzi = *data_ptr++;
            ewk->wu.old_rno[0] = *data_ptr++;
            ewk->wu.old_rno[1] = *data_ptr++;
            ewk->wu.old_rno[2] = *data_ptr++;
            *(s16*)&ewk->wu.mvxy.a[0] = *data_ptr++;
            ewk->wu.mvxy.a[0].real.l = *data_ptr++;
            ewk->wu.mvxy.d[0].real.h = *data_ptr++;
            ewk->wu.mvxy.d[0].real.l = *data_ptr++;
            ewk->wu.mvxy.a[1].real.h = *data_ptr++;
            ewk->wu.mvxy.a[1].real.l = *data_ptr++;
            ewk->wu.mvxy.d[1].real.h = *data_ptr++;
            ewk->wu.mvxy.d[1].real.l = *data_ptr++;
            ewk->wu.char_table[0] = char_add[bg_w.stage][bg_w.area];
            suzi_offset_set(&ewk->wu);
        }
        return 0;
    }
}
