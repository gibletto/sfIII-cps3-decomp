/*
 * EFFD1.C  Effect D1, the falling object
 *
 * Effect D1 is created under a parent effect, 138 dots above it (pattern 17). fall_data_set aims
 * it to land 32 dots or more in front of the parent, taking the distance between the two players
 * into account, over 44 frames; effect_D1_move flies it there, moves it to priority 20 for the
 * last part of the drop and keeps animating after landing.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "EFFD1.h"

/* routine_no[0] */
#define R0_INIT         0       /* aim at the landing point */
#define R0_FALL         1       /* fly toward it */
#define R0_DROP         2       /* last part of the drop, in front */
#define R0_LAND         3       /* animate on the floor */



void effect_D1_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        fall_data_set(ewk);
        pl_eff_trans_entry(ewk);
        break;
    case R0_FALL:
        if (!ewk->wu.cg_type) {
            char_move(&ewk->wu);
        }
        ewk->wu.old_rno[0]--;
        if (ewk->wu.old_rno[0] < 36) {
            ewk->wu.routine_no[0]++;
            ewk->wu.my_priority = ewk->wu.position_z = 20;
        }
        add_x_sub(ewk);
        add_y_sub(ewk);
        pl_eff_trans_entry(ewk);
        break;
    case R0_DROP:
        if (!ewk->wu.cg_type) {
            char_move(&ewk->wu);
        }
        ewk->wu.old_rno[0]--;
        if (ewk->wu.old_rno[0] != 0) {
            add_x_sub(ewk);
            add_y_sub(ewk);
        } else {
            ewk->wu.routine_no[0]++;
        }
        pl_eff_trans_entry(ewk);
        break;
    case R0_LAND:
        char_move(&ewk->wu);
        pl_eff_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



void fall_data_set(WORK_Other* ewk) {
    WORK_Other* oya_ef = (WORK_Other*)ewk->my_master;
    s16 pos_work;
    s16 id_work;
    ewk->wu.old_rno[0] = 44;
    id_work = oya_ef->master_id ^ 1;
    pos_work = plw[oya_ef->master_id].wu.xyz[0].disp.pos - plw[id_work].wu.xyz[0].disp.pos;
    if (ewk->wu.rl_flag) {
        ewk->wu.xyz[0].disp.pos += 32;
        if (pos_work > 0) {
            pos_work = 32;
        } else if (pos_work > -32) {
            pos_work = 32;
        } else {
            pos_work = -pos_work;
        }
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[0], oya_ef->wu.xyz[0].disp.pos + pos_work, -8, 2, 1);
    } else {
        ewk->wu.xyz[0].disp.pos -= 32;
        if (pos_work > 0) {
            if (pos_work < 32) {
                pos_work = 32;
            }
        } else {
            pos_work = 32;
        }
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[0], oya_ef->wu.xyz[0].disp.pos - pos_work, -8, 2, 1);
    }
}


/* Create the object that drops from 138 dots above its parent, started by the parent's move data
 * through effinitjptbl (which ignores the result: there is no final return). */
s32 effect_D1_init(WORK_Other* oya, s32 _p1) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 131;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.disp_flag = 0;
    ewk->my_master = (u32*)oya;
    ewk->wu.my_family = 2;
    ewk->wu.char_index = 17;
    ewk->master_id = oya->master_id;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_priority = ewk->wu.position_z = oya->wu.position_z;
    ewk->wu.sync_suzi = 1;
    ewk->wu.rl_flag = oya->wu.rl_flag;
    if (oya->master_id) {
        ewk->wu.my_col_code = 22;
    } else {
        ewk->wu.my_col_code = 6;
    }
    ewk->wu.char_table[0] = etc_char_table;
    ewk->wu.xyz[1].disp.pos = oya->wu.xyz[1].disp.pos + 138;
    ewk->wu.xyz[0].disp.pos = oya->wu.xyz[0].disp.pos;
}
