/*
 * EFFG2.C  Effect G2: parts that run after the effect G1 follow points
 *
 * effect_G2_init(parent, type) (from effect G1) makes a part (plef_char_table). effect_G2_move runs it
 * toward its follow point at a speed from effG2_speed_tbl by distance (effG2_distance_tbl), clears the
 * parent's marker once it is close, steps its animation faster while running (effG2_char_move) and
 * changes pattern with the player's state (effG2_char_tbl). After the round (pcon_dp_flag) the parts
 * keep following and take their end patterns from the player's poses; on stage 8's first round they
 * fall away (effG2_fall_tbl) once the stage base moves.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFG2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"

extern const s16 effG2_fall_tbl[4][2];
extern const s16 effG2_char_tbl[4][3];
extern const s16 effG2_speed_tbl[3][4][8];
extern const s16 effG2_distance_tbl[4][8];
void effG2_follow(WORK_Other* ewk, WORK_Other* mwk);
void effG2_char_move(WORK_Other* ewk, s16 type);
void effG2_disp(WORK_Other* ewk);
void effG2_pattern(WORK_Other* ewk, WORK_Other* mwk);

void effect_G2_move(WORK_Other* ewk) {
    WORK_Other* mwk = (WORK_Other*)ewk->my_master;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.xyz[0].disp.pos = ewk->wu.old_pos[0] = mwk->wu.old_rno[ewk->wu.type * 2];
        ewk->wu.xyz[1].disp.pos = ewk->wu.old_pos[1] = mwk->wu.position_y;
        ewk->wu.xyz[2].disp.pos = ewk->wu.old_pos[2] = mwk->wu.position_z;
        ewk->wu.disp_flag = 1;
        ewk->wu.rl_flag = 0;
        set_char_move_init(&ewk->wu, 0, effG2_char_tbl[ewk->wu.type][0]);
        break;
    case 1:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0] = 3;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            effG2_pattern(ewk, mwk);
            effG2_follow(ewk, mwk);
            add_mvxy_speed_direct(&ewk->wu, ewk->wu.dir_timer, 0);
            effG2_char_move(ewk, mwk->wu.dmcal_m);
        }
        if (pcon_dp_flag) {
            ewk->wu.routine_no[0] = 2;
            ewk->wu.routine_no[1] = 0;
            break;
        }
        effG2_disp(ewk);
        break;
    case 2:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0] = 3;
            break;
        }
        switch (ewk->wu.routine_no[1]) {
        case 0:
            if (bg_w.stage == 8 && Round_num == 0) {
                ewk->wu.routine_no[1] = 1;
                ewk->wu.routine_no[2] = 0;
                ewk->wu.dir_old = stage8_base_y;
            } else {
                ewk->wu.routine_no[1] = 2;
                ewk->wu.routine_no[2] = 0;
            }
            break;
        case 1:
            switch (ewk->wu.routine_no[2]) {
            case 0:
                effG2_follow(ewk, mwk);
                add_mvxy_speed_direct(&ewk->wu, ewk->wu.dir_timer, 0);
                effG2_char_move(ewk, mwk->wu.dmcal_m);
                if (ewk->wu.dir_old != stage8_base_y) {
                    ewk->wu.mvxy.a[0].sp = ewk->wu.mvxy.d[0].sp = 0;
                    ewk->wu.mvxy.a[1].sp = effG2_fall_tbl[ewk->wu.type][0] << 8;
                    ewk->wu.mvxy.d[1].sp = effG2_fall_tbl[ewk->wu.type][1] << 8;
                    ewk->wu.mvxy.kop[0] = ewk->wu.mvxy.kop[1] = 0;
                    ewk->wu.kage_flag = 0;
                    ewk->wu.routine_no[2]++;
                }
                break;
            case 1:
                add_mvxy_speed(&ewk->wu);
                cal_mvxy_speed(&ewk->wu);
                if (ewk->wu.mvxy.a[1].sp < -0x100000) {
                    ewk->wu.mvxy.d[1].sp = 0;
                }
                ewk->wu.position_x = ewk->wu.xyz[0].disp.pos;
                ewk->wu.position_y = ewk->wu.xyz[1].disp.pos;
                break;
            }
            break;
        case 2:
            effG2_pattern(ewk, mwk);
            effG2_follow(ewk, mwk);
            add_mvxy_speed_direct(&ewk->wu, ewk->wu.dir_timer, 0);
            effG2_char_move(ewk, mwk->wu.dmcal_m);
            if (mwk->wu.routine_no[1] == 0) {
                if (mwk->wu.routine_no[2] == 40) {
                    ewk->wu.routine_no[1] = 3;
                }
                if (mwk->wu.routine_no[2] == 41) {
                    ewk->wu.routine_no[1] = 4;
                }
            } else if (mwk->wu.routine_no[1] == 1) {
                if (!mwk->wu.routine_no[2] && mwk->wu.routine_no[3] == 3) {
                    ewk->wu.routine_no[1] = 4;
                }
            }
            break;
        case 3:
            effG2_pattern(ewk, mwk);
            effG2_follow(ewk, mwk);
            add_mvxy_speed_direct(&ewk->wu, ewk->wu.dir_timer, 0);
            effG2_char_move(ewk, 2);
            break;
        case 4:
            switch (ewk->wu.routine_no[2]) {
            case 0:
                ewk->wu.routine_no[2]++;
                set_char_move_init(&ewk->wu, 0, effG2_char_tbl[ewk->wu.type][2]);
                break;
            case 1:
                char_move(&ewk->wu);
                if (ewk->wu.cg_type == 0xFF) {
                    ewk->wu.routine_no[2]++;
                }
                break;
            }
            break;
        }
        ewk->wu.old_pos[2] = mwk->wu.position_z - 1;
        effG2_disp(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

void effG2_follow(WORK_Other* ewk, WORK_Other* mwk) {
    s16 i;
    ewk->wu.old_pos[0] = mwk->wu.old_rno[ewk->wu.type * 2];
    ewk->wu.old_pos[1] = mwk->wu.position_y;
    ewk->wu.old_pos[2] = mwk->wu.position_z + 1;
    ewk->wu.dir_step = ewk->wu.xyz[0].disp.pos - ewk->wu.old_pos[0];
    if (ewk->wu.dir_step < 0) {
        ewk->wu.dir_step = -ewk->wu.dir_step;
    }
    if (ewk->wu.dir_step == 0) {
        ewk->wu.dir_timer = 0;
        mwk->wu.cmwk[ewk->wu.type] = 0;
    } else {
        for (i = 7; i > 0; i--) {
            if (ewk->wu.dir_step > effG2_distance_tbl[ewk->wu.type][i - 1]) {
                break;
            }
        }
        if (i < 2) {
            mwk->wu.cmwk[ewk->wu.type] = 0;
            if (ewk->wu.type == 3) {
                mwk->wu.cmwk[2] = 0;
            }
            if (ewk->wu.type == 2) {
                mwk->wu.cmwk[3] = 0;
            }
        }
        ewk->wu.dir_timer = effG2_speed_tbl[mwk->wu.dmcal_m][ewk->wu.type][i];
        if (ewk->wu.xyz[0].disp.pos < ewk->wu.old_pos[0]) {
            ewk->wu.dir_timer = -ewk->wu.dir_timer;
        }
    }
}

void effG2_char_move(WORK_Other* ewk, s16 type) {
    if (type != 1) {
        if (type != 0) {
            char_move(&ewk->wu);
            char_move(&ewk->wu);
        }
        char_move(&ewk->wu);
    }
    char_move(&ewk->wu);
}

void effG2_disp(WORK_Other* ewk) {
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos;
    ewk->wu.position_z = ewk->wu.old_pos[2];
    sort_push_request(&ewk->wu);
}

void effG2_pattern(WORK_Other* ewk, WORK_Other* mwk) {
    if (mwk->wu.routine_no[1] == 1 || mwk->wu.routine_no[1] == 3) {
        if (ewk->wu.char_index != effG2_char_tbl[ewk->wu.type][1]) {
            set_char_move_init(&ewk->wu, 0, effG2_char_tbl[ewk->wu.type][1]);
        }
    } else if (ewk->wu.char_index != effG2_char_tbl[ewk->wu.type][0]) {
        set_char_move_init(&ewk->wu, 0, effG2_char_tbl[ewk->wu.type][0]);
    }
}

s32 effect_G2_init(WORK_Other* mwk, s16 type) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 162;
    ewk->wu.type = type;
    ewk->wu.work_id = 16;
    ewk->wu.my_family = mwk->wu.my_family;
    ewk->wu.cgromtype = mwk->wu.cgromtype;
    ewk->wu.my_col_mode = mwk->wu.my_col_mode;
    ewk->wu.my_col_code = mwk->wu.my_col_code;
    ewk->wu.target_adrs = mwk->my_master;
    ewk->my_master = (u32*)mwk;
    ewk->master_work_id = mwk->master_work_id;
    ewk->master_id = mwk->master_id;
    ewk->master_player = mwk->master_player;
    ewk->wu.blink_timing = ewk->master_id;
    ewk->wu.char_table[0] = plef_char_table;
    return 0;
}
