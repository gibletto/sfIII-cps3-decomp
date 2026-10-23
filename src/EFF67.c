/*
 * EFF67.C  Effect 67: flying objects launched by effect 20
 *
 * effect_67_init(parent, type) places an object from one of eight random rows of eff67_data_tbl[type]
 * (position, priority, speed range, the height where it comes down, animation) and gives it random
 * starting speeds (eff67_accel_tbl, eff67_speed_x_tbl, eff67_speed_y_tbl). effect_67_move flies it,
 * taking new random speeds every few frames, and removes it once it leaves x 128..0x3A0. When it comes
 * down to its height, a type 0 object stays there 50 frames and then goes; a type 1 object goes at
 * once. Each object counts itself in and out of its effect 20 parent. Objects pause while the
 * alternate background is up (seraph_flag) and, below priority 70, during the finish screen
 * (akebono_flag).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "EFF67.h"
int abs(int);
extern const s16 eff67_data_tbl[2][48];
extern const s32 eff67_accel_tbl[2][64];
extern const s32 eff67_speed_x_tbl[2][16];
extern const s32 eff67_speed_y_tbl[2][16];
extern const s32 eff67_speed_y2_tbl[2][16];
extern const u32 eff67_char_table[];

s32 effect_67_init(WORK_Other* oya, s16 type) {
    WORK_Other* ewk;
    s16 ix;
    s16 rnd;
    const s16* data;
    (void)eff67_accel_tbl;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 67;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.type = type;
    ewk->my_master = (u32*)oya;
    ewk->master_work_id = oya->wu.work_id;
    ewk->master_id = oya->wu.id;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.char_table[0] = eff67_char_table;
    rnd = random_32_com();
    rnd &= 7;
    data = eff67_data_tbl[(u8)type] + rnd * 6;
    if (type == 0) {
        ewk->wu.char_index = 0;
        ewk->wu.my_family = 2;
    } else {
        ewk->wu.char_index = 2;
        ewk->wu.my_family = 1;
    }
    ewk->wu.position_x = *data & 0x3FF;
    ewk->wu.xyz[0].disp.pos = *data++;
    ewk->wu.position_y = *data & 0x3FF;
    ewk->wu.xyz[1].disp.pos = *data++;
    ewk->wu.position_z = ewk->wu.my_priority = *data++;
    ewk->wu.vitality = *data++;
    ewk->wu.vital_old = *data++;
    ewk->wu.char_index = *data;
    ewk->wu.dm_vital = 50;
    rnd = random_32_com();
    rnd = rnd + rnd;
    if (rnd == 0) {
        rnd = 16;
    }
    ewk->wu.vital_new = rnd;
    rnd = random_32_com();
    if (rnd < ewk->wu.vitality) {
        ewk->wu.mvxy.a[1].sp = eff67_accel_tbl[ewk->wu.type][rnd * 2];
        ewk->wu.mvxy.d[1].sp = eff67_accel_tbl[ewk->wu.type][rnd * 2 + 1];
    } else {
        ewk->wu.mvxy.a[1].sp = abs(eff67_accel_tbl[ewk->wu.type][rnd * 2]);
        ewk->wu.mvxy.d[1].sp = abs(eff67_accel_tbl[ewk->wu.type][rnd * 2 + 1]);
    }
    rnd = random_32_com();
    ewk->wu.mvxy.a[0].sp = eff67_speed_x_tbl[ewk->wu.type][rnd];
    rnd = random_16_com();
    ewk->wu.mvxy.d[0].sp = eff67_speed_y_tbl[ewk->wu.type][rnd];
}

void effect_67_move(WORK_Other* ewk) {
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
    case 0:
        oya = (WORK_Other*)ewk->my_master;
        if (ewk->wu.type == 0) {
            oya->wu.direction++;
        } else {
            oya->wu.dir_old++;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case 1:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag != 0 || Game_pause != 0) {
            disp_seraph_cells(&ewk->wu);
            break;
        } else {
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
            if (ewk->wu.xyz[0].disp.pos < 128 || ewk->wu.xyz[0].disp.pos > 0x3A0) {
                ewk->wu.routine_no[0]++;
                ewk->wu.routine_no[0]++;
                break;
            }
            if (ewk->wu.xyz[1].disp.pos < ewk->wu.vital_old) {
                if (ewk->wu.type == 0) {
                    ewk->wu.routine_no[0]++;
                    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
                    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
                    disp_seraph_cells(&ewk->wu);
                    return;
                } else {
                    ewk->wu.routine_no[0]++;
                    ewk->wu.routine_no[0]++;
                    return;
                }
            }
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            ewk->wu.vital_new--;
            if (ewk->wu.vital_new == 0) {
                rnd = random_32_com();
                if (rnd < 4) {
                    rnd = 16;
                }
                ewk->wu.vital_new = rnd;
                rnd = random_32_com();
                if (rnd < ewk->wu.vitality) {
                    ewk->wu.mvxy.d[1].sp = eff67_accel_tbl[ewk->wu.type][rnd * 2 + 1];
                } else {
                    ewk->wu.mvxy.d[1].sp = abs(eff67_accel_tbl[ewk->wu.type][rnd * 2 + 1]);
                }
                rnd = random_16_com();
                if (rnd > 6) {
                    rnd = random_16_com();
                    ewk->wu.mvxy.d[0].sp = eff67_speed_y_tbl[ewk->wu.type][rnd];
                } else {
                    rnd = random_16_com();
                    ewk->wu.mvxy.d[0].sp = eff67_speed_y2_tbl[ewk->wu.type][rnd];
                }
            }
        }
        disp_seraph_cells(&ewk->wu);
        break;
    case 2:
        ewk->wu.dm_vital--;
        if (ewk->wu.dm_vital == 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
            break;
        }
        disp_seraph_cells(&ewk->wu);
        break;
    case 3:
        oya = (WORK_Other*)ewk->my_master;
        if (ewk->wu.type == 0) {
            oya->wu.direction--;
        } else {
            oya->wu.dir_old--;
        }
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}
