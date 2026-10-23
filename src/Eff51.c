/*
 * EFF51.C  Effect 51: zooming message with colour flash
 *
 * Effect 51 is a message object created by effect_51_init with a position, start delay and colour
 * options; it uses sel_pl_char_table and raises the shared Flash_Sign counters.
 * effect_51_move waits for its delay, appears at double size and shrinks to normal size, then
 * waits for the other flashing objects (Flash_Sign) and runs Flash_Violent sequences before
 * it is removed.
 * Flash_Violent runs a timed colour-flash sequence on a work and returns 1 when finished; effects
 * 49, 50 and B5 use it too. effect_51_init is called from RANKING.c; EffG0.c makes effect 51 objects with its
 * own effG0_flash_init.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "Eff51.h"



void effect_51_move(WORK_Other_CONN* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        if (--ewk->wu.dir_timer) {
            return;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.dir_timer = 1;
        ewk->wu.mvxy.a[0].sp = 0xC0000;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
        break;
    case 1:
        if (--ewk->wu.dir_timer == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case 2:
        if ((ewk->wu.my_mr.size.x -= *(s16*)&ewk->wu.mvxy.a[0]) <= 63) {
            ewk->wu.my_mr.size.x = 63;
        }
        if ((ewk->wu.my_mr.size.y -= *(s16*)&ewk->wu.mvxy.a[0]) <= 63) {
            ewk->wu.my_mr.size.y = 63;
        }
        if (ewk->wu.my_mr.size.x <= 63 && ewk->wu.my_mr.size.y <= 63) {
            Flash_Sign[0]--;
            if (ewk->wu.dir_old) {
                ewk->wu.routine_no[0]++;
            } else {
                ewk->wu.routine_no[0] = 99;
            }
            break;
        }
        ewk->wu.position_z++;
        break;
    case 3:
        if (Flash_Sign[0] == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case 4:
        if (--ewk->wu.dir_old == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case 5:
        if (Flash_Violent((WORK_Other*)ewk, 1)) {
            ewk->wu.routine_no[0]++;
            ewk->wu.routine_no[1] = 0;
            ewk->wu.routine_no[2] = 1;
            ewk->wu.routine_no[3] = 3;
            ewk->wu.routine_no[4] = 10;
            ewk->wu.vitality = 0;
        }
        if (ewk->wu.vitality) {
            set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
        }
        break;
    case 6:
        if (Flash_Sign[1] == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case 7:
        if (Flash_Violent((WORK_Other*)ewk, 1)) {
            ewk->wu.routine_no[0]++;
        }
        if (ewk->wu.vitality) {
            set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
        }
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}



s32 effect_51_init(s16 step, s16 x, s16 y, s16 timer, s16 dir_old, s16 col_ofs, s16 use_ofs, s16 col2_ofs) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    Flash_Sign[0]++;
    Flash_Sign[1]++;
    ewk->wu.be_flag = 1;
    ewk->wu.id = 51;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 1;
    ewk->wu.position_z = 10;
    ewk->wu.dir_timer = timer + 120;
    ewk->wu.dir_old = dir_old;
    *ewk->wu.char_table = sel_pl_char_table;
    ewk->wu.char_index = 26;
    ewk->wu.my_mr_flag = 1;
    ewk->wu.my_mr.size.x = 127;
    ewk->wu.my_mr.size.y = 127;
    ewk->wu.dir_step = step;
    ewk->wu.xyz[0].disp.pos = x;
    ewk->wu.xyz[1].disp.pos = y;
    if (use_ofs == 0) {
        ewk->wu.my_col_code = 0x2043;
    } else {
        ewk->wu.my_col_code = col_ofs + 0x2043;
    }
    if (dir_old) {
        ewk->wu.routine_no[2] = 1;
        ewk->wu.routine_no[3] = 1;
        ewk->wu.routine_no[4] = 0;
        ewk->wu.vitality = 0;
        ewk->wu.vital_new = col2_ofs + 0x2043;
        ewk->wu.vital_old = ewk->wu.my_col_code;
    }
    return 0;
}



