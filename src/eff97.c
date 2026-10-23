/*
 * EFF97.C  Entrance prop thrown aside (effect 97)
 *
 * A prop that appears beside a fighter during his entrance (created from Appear_15000).
 * effect_97_init places it 108 dots in front of the fighter; effect_97_move plays its
 * animation until the fighter's appearance reaches the right step, then switches to a
 * second pattern and throws it off the screen with speed and gravity before freeing it.
 * Its position follows the line scroll through suzi_sync_pos_set.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "eff97.h"



/* not gated by EXE_flag/Game_pause, case 3 draws only while moving */
void effect_97_move(WORK_Other* ewk) {
    s32 kc = 16;

    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 44);
    case 1:
        char_move(&ewk->wu);
        if (plw[ewk->master_id].wu.routine_no[2] == 1 && plw[ewk->master_id].wu.routine_no[3] == 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.old_rno[0] = kc;
        }
        suzi_sync_pos_set(ewk);
        sort_push_request4(&ewk->wu);
        break;
    case 2:
        ewk->wu.old_rno[0]--;
        if (ewk->wu.old_rno[0] > 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.rl_flag ^= 1;
            set_char_move_init(&ewk->wu, 0, 45);
            ewk->wu.old_rno[0] = kc;
            ewk->wu.mvxy.a[1].sp = 0xE8000;
            ewk->wu.mvxy.d[1].sp = -0x6000;
            if (plw[ewk->master_id].wu.id) {
                ewk->wu.mvxy.a[0].sp = 0xA8000;
                ewk->wu.mvxy.d[0].sp = 0x1000;
            } else {
                ewk->wu.mvxy.a[0].sp = -0xA8000;
                ewk->wu.mvxy.d[0].sp = -0x1000;
            }
        }
        suzi_sync_pos_set(ewk);
        sort_push_request4(&ewk->wu);
        break;
    case 3:
        ewk->wu.old_rno[0]--;
        if (ewk->wu.old_rno[0] > 0) {
            add_x_sub(ewk);
            add_y_sub(ewk);
            suzi_sync_pos_set(ewk);
            sort_push_request4(&ewk->wu);
        } else {
            ewk->wu.routine_no[0]++;
        }
        break;
    case 4:
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
    }
}



s32 effect_97_init(PLW* oya) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 97;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->my_master = (u32*)oya;
    ewk->master_id = oya->wu.id;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = oya->wu.my_col_code;
    ewk->wu.my_family = 2;
    ewk->wu.my_priority = ewk->wu.position_z = oya->wu.my_priority;
    ewk->wu.sync_suzi = 0;
    ewk->wu.xyz[1].disp.pos = 40;
    *ewk->wu.char_table = etc_char_table;
    if (oya->wu.id) {
        ewk->wu.rl_flag = 1;
        ewk->wu.xyz[0].disp.pos = oya->wu.xyz[0].disp.pos + 104;
    } else {
        ewk->wu.rl_flag = 0;
        ewk->wu.xyz[0].disp.pos = oya->wu.xyz[0].disp.pos - 104;
    }
    suzi_offset_set(&ewk->wu);
    return 0;
}
