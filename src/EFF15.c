/*
 * EFF15.C  Effect 15: a falling stone
 *
 * effect_15_init (from effect 04, the falling stones controller) makes one stone: its position,
 * priority, cell, side speed limit and floor come from a row of eff15_data_tbl, and
 * eff15_speed_set picks random speeds. effect_15_move counts the stone in its parent (direction),
 * drops it under the speeds, re-aims it at random intervals, lets it lie on the floor for 30 frames
 * once it lands and removes it (counting it out) when it leaves the screen.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "PLS02.h"
#include "EFFECT.h"
#include "effect_2.h"

/* routine_no[0] */
#define R0_INIT         0       /* count the stone in its parent */
#define R0_FALL         1       /* fall, re-aiming now and then */
#define R0_LIE          2       /* lie on the floor for 30 frames */
#define R0_KILL         3       /* count it out, put the work back */

void eff15_speed_set(WORK_Other* ewk);

extern const s16 eff15_data_tbl[];   /* provisional name: 6 per type */
extern const s32 eff15_y_speed_tbl[];   /* provisional name */
extern const s32 eff15_x_speed_tbl[];   /* provisional name */
extern const s32 eff15_x_acc_tbl[];   /* provisional name */
extern const s32 eff15_x_acc_tbl2[];   /* provisional name */
int abs(int);

#define STONE_SPEED_W(value) ((WORK*)(s16)(value))

s32 effect_15_init(WORK* wk, s16 data) {
    WORK_Other* ewk;
    s16 ix;
    s16 num;
    const s16* data_ptr;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 15;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.type = data;
    ewk->my_master = (u32*)wk;
    ewk->master_work_id = wk->work_id;
    ewk->master_id = wk->id;
    ewk->wu.my_family = 1;
    ewk->wu.my_col_code = 99;
    data_ptr = &eff15_data_tbl[data * 6];
    ewk->wu.position_x = *data_ptr & 0x3FF;
    ewk->wu.xyz[0].disp.pos = *data_ptr++;
    ewk->wu.position_y = *data_ptr & 0x3FF;
    ewk->wu.xyz[1].disp.pos = *data_ptr++;
    ewk->wu.position_z = ewk->wu.my_priority = *data_ptr++;
    ewk->wu.char_index = *data_ptr++;
    ewk->wu.vitality = *data_ptr++;
    ewk->wu.vital_old = *data_ptr;
    ewk->wu.dm_vital = 30;
    num = random_32_com();
    num &= 28;
    if (num == 0) {
        num = 32;
    }
    ewk->wu.vital_new = num;
    eff15_speed_set(ewk);
    ewk->wu.char_table[0] = ef01_char_table;
    return 0;
}

void effect_15_move(WORK_Other* ewk) {
    WORK_Other* oya;
    s8 num;
    if (ewk->wu.dead_f == 1) {
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        oya = (WORK_Other*)ewk->my_master;
        oya->wu.direction++;
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R0_FALL:
        if (EXE_flag == 0 && Game_pause == 0) {
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
            if (ewk->wu.xyz[0].disp.pos < 0x120 || ewk->wu.xyz[0].disp.pos > 0x2C0) {
                ewk->wu.routine_no[0]++;
                ewk->wu.routine_no[0]++;
                return;
            }

            if (ewk->wu.xyz[1].disp.pos < ewk->wu.vital_old) {
                ewk->wu.routine_no[0]++;
                ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
                ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
                sort_push_request4(&ewk->wu);
                return;
            }
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            ewk->wu.vital_new--;
            if (ewk->wu.vital_new <= 0) {
                num = random_32_com();
                if (num < 5) {
                    num = 38;
                }
                ewk->wu.vital_new = num;
                eff15_speed_set(ewk);
            }
        }
        sort_push_request4(&ewk->wu);
        break;
    case R0_LIE:
        ewk->wu.dm_vital--;
        if (ewk->wu.dm_vital == 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
            break;
        }
        sort_push_request4(&ewk->wu);
        break;
    case R0_KILL:
        oya = (WORK_Other*)ewk->my_master;
        oya->wu.direction--;
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

/* provisional name */
void eff15_speed_set(WORK_Other* ewk) {
    s8 num;
    const s32* p;
    const s32* q;
    num = random_32_com();
    q = &eff15_y_speed_tbl[num * 2];
    ewk->wu.mvxy.a[1].sp = q[0];
    ewk->wu.mvxy.d[1].sp = q[1];
    (void)&STONE_SPEED_W(num)->id;
    num = random_16_com();
    p = &eff15_x_speed_tbl[num];
    if (num < ewk->wu.vitality) {
        ewk->wu.mvxy.a[0].sp = abs(*p);
        num = random_16_com();
        num &= 1;
        if (num == 0) {
            num = random_16_com();
            ewk->wu.mvxy.d[0].sp = abs(eff15_x_acc_tbl[num]);
        } else {
            num = random_16_com();
            ewk->wu.mvxy.d[0].sp = abs(eff15_x_acc_tbl2[num]);
        }
    } else {
        (void)&STONE_SPEED_W(num)->id;
        ewk->wu.mvxy.a[0].sp = *p;
        num = random_16_com();
        num &= 1;
        if (num == 0) {
            num = random_16_com();
            ewk->wu.mvxy.d[0].sp = eff15_x_acc_tbl[num];
        } else {
            num = random_16_com();
            ewk->wu.mvxy.d[0].sp = eff15_x_acc_tbl2[num];
        }
    }
}
