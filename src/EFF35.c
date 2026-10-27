/*
 * EFF35.C  Effect 35: flying objects launched by effect 34
 *
 * effect_35_init(parent, type) places an object from eff35_spawn_tbl (position, priority, animation,
 * speed range and the height where it comes down); types 0-10 use eff35_char_table1, types 11 and up
 * eff35_char_table2. eff35_setup gives it a new random vertical speed (eff35_vertical_tbl),
 * horizontal speed (eff35_speed_tbl) and acceleration every few frames. effect_35_move flies the
 * object and removes it once it is beyond x -384..384. When it comes down to its height, an object
 * of the first kind stays there for 50 frames and then goes; one of the second kind goes at once.
 * Each object counts itself in and out of its effect 34 controller and is drawn with
 * disp_seraph_cells.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "ta_sub.h"
#include "eff35.h"

/* routine_no[0] */
#define R0_INIT         0       /* count in with the controller and show */
#define R0_FLY          1       /* fly until it comes down or leaves */
#define R0_LAND         2       /* stay where it came down for a while */
#define R0_KILL         3       /* count out and put the work back */

extern const s16 eff35_spawn_tbl[132];
extern const s32 eff35_vertical_tbl[128];
extern const s32 eff35_speed_tbl[16];
extern const s32 eff35_accel1_tbl[16];
extern const s32 eff35_accel2_tbl[16];
extern const u32 eff35_char_table1[];
extern const u32 eff35_char_table2[];
void eff35_setup(WORK_Other* ewk);
s32 abs();

s32 effect_35_init(WORK_Other* oya, s16 type) {
    WORK_Other* ewk;
    const s16* data;
    s16 ix;
    s16 rnd;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 35;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.type = type;
    ewk->my_master = (u32*)oya;
    ewk->master_work_id = oya->wu.work_id;
    ewk->master_id = oya->wu.id;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 0x204E;
    data = eff35_spawn_tbl + (s32)type * 6;
    ewk->wu.position_x = *data & 0x3FF;
    ewk->wu.xyz[0].disp.pos = *data++;
    ewk->wu.position_y = *data & 0x3FF;
    ewk->wu.xyz[1].disp.pos = *data++;
    ewk->wu.position_z = ewk->wu.my_priority = *data++;
    ewk->wu.char_index = *data++;
    ewk->wu.vitality = *data++;
    ewk->wu.vital_old = *data;
    ewk->wu.dm_vital = 50;
    if (type < 11) {
        ewk->wu.dmcal_m = 0;
    } else {
        ewk->wu.dmcal_m = 1;
    }
    rnd = random_32_com();
    rnd &= 28;
    if (rnd == 0) {
        rnd = 32;
    }
    ewk->wu.vital_new = rnd;
    eff35_setup(ewk);
    if (ewk->wu.dmcal_m == 0) {
        ewk->wu.char_table[0] = eff35_char_table1;
    } else {
        ewk->wu.char_table[0] = eff35_char_table2;
    }
    return 0;
}

void effect_35_move(WORK_Other* ewk) {
    WORK_Other* oya;
    s8 rnd;
    if (ewk->wu.dead_f == 1) {
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
    if (seraph_flag) {
        return;
    }
    if (akebono_flag == 1 && ewk->wu.position_z <= 69) {
        return;
    }
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        oya = (WORK_Other*)ewk->my_master;
        if (ewk->wu.dmcal_m == 0) {
            oya->wu.direction++;
        } else {
            oya->wu.dir_old++;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R0_FLY:
        if (EXE_flag != 0 || Game_pause != 0) {
            disp_seraph_cells(&ewk->wu);
            break;
        } else {
        }
        char_move(&ewk->wu);
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos < -384 || ewk->wu.xyz[0].disp.pos > 384) {
            goto retire;
        } else if (ewk->wu.xyz[1].disp.pos < ewk->wu.vital_old) {
            if (ewk->wu.dmcal_m == 0) {
                ewk->wu.routine_no[0]++;
                ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
                ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
                disp_seraph_cells(&ewk->wu);
                return;
            } else {
            retire:;
                ewk->wu.routine_no[0]++;
                ewk->wu.routine_no[0]++;
                return;
            }
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        ewk->wu.vital_new--;
        if (ewk->wu.vital_new <= 0) {
            rnd = random_32_com();
            if (rnd < 5) {
                rnd = 38;
            }
            ewk->wu.vital_new = rnd;
            eff35_setup(ewk);
        }
        disp_seraph_cells(&ewk->wu);
        break;
    case R0_LAND:
        ewk->wu.dm_vital--;
        if (ewk->wu.dm_vital == 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
            break;
        }
        disp_seraph_cells(&ewk->wu);
        break;
    case R0_KILL:
        oya = (WORK_Other*)ewk->my_master;
        if (ewk->wu.dmcal_m == 0) {
            oya->wu.direction--;
        } else {
            oya->wu.dir_old--;
        }
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

void eff35_setup(WORK_Other* ewk) {
    s8 rnd;
    s8 accel;
    s8 dir;
    rnd = random_32_com();
    ewk->wu.mvxy.a[1].sp = eff35_vertical_tbl[ewk->wu.dmcal_m * 64 + rnd * 2];
    ewk->wu.mvxy.d[1].sp = eff35_vertical_tbl[ewk->wu.dmcal_m * 64 + rnd * 2 + 1];
    rnd = random_16_com();
    if (rnd < ewk->wu.vitality) {
        ewk->wu.mvxy.a[0].sp = abs(eff35_speed_tbl[rnd]);
        dir = random_16_com();
        dir &= 1;
        if (dir == 0) {
            accel = random_16_com();
            ewk->wu.mvxy.d[0].sp = abs(eff35_accel1_tbl[accel]);
        } else {
            accel = random_16_com();
            ewk->wu.mvxy.d[0].sp = abs(eff35_accel2_tbl[accel]);
        }
    } else {
        ewk->wu.mvxy.a[0].sp = eff35_speed_tbl[rnd];
        dir = random_16_com();
        dir &= 1;
        if (dir == 0) {
            rnd = random_16_com();
            ewk->wu.mvxy.d[0].sp = eff35_accel1_tbl[rnd];
        } else {
            rnd = random_16_com();
            ewk->wu.mvxy.d[0].sp = eff35_accel2_tbl[rnd];
        }
    }
}
