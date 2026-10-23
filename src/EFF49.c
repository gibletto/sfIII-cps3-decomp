/*
 * EFF49.C  Effect 49 (continue count down digit)
 *
 * Effect 49 is the loser's continue count: it waits dir_timer frames, zooms in from
 * 127 while rising in priority, then shows Continue_Count[LOSER] (playing a sound as
 * each new digit comes up) until the count runs out, waits dir_old frames and zooms out.
 * Flash_Violent runs a timed colour-flash sequence on a work and returns 1
 * when finished.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "charmove_2.h"
#include "se_3.h"
#include "Eff51.h"
#include "EFF49.h"

void set_char_move_init2();
extern const s16 eff49_pos_tbl[10];



void effect_49_move(WORK_Other* ewk) {
    s16 num;
    Flash_Violent(ewk, E_07_Flag[LOSER]);
    switch (ewk->wu.routine_no[0]) {
    case 0:
        if (--ewk->wu.dir_timer != 0) {
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
        ewk->wu.my_priority++;
        ewk->wu.position_z++;
        if ((ewk->wu.my_mr.size.x -= *(s16*)&ewk->wu.mvxy.a[0]) <= 63) {
            ewk->wu.my_mr.size.x = 63;
        }
        if ((ewk->wu.my_mr.size.y -= *(s16*)&ewk->wu.mvxy.a[0]) <= 63) {
            ewk->wu.my_mr.size.y = 63;
        }
        if (ewk->wu.my_mr.size.x <= 63 && ewk->wu.my_mr.size.y <= 63) {
            if (ewk->wu.dir_step != 18) {
                ewk->wu.routine_no[0] = 4;
            } else {
                ewk->wu.routine_no[0]++;
                ewk->wu.direction = 9;
            }
        }
        break;
    case 3:
        if ((num = Continue_Count[LOSER]) < 0) {
            ewk->wu.routine_no[0] = 5;
            set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, 10, 0);
        } else {
            set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, num + 10, 0);
            if (ewk->wu.direction != num) {
                ewk->wu.direction = num;
                Sound_SE(Continue_Count[LOSER] + 0x90);
            }
        }
        break;
    case 4:
        if (Continue_Count[LOSER] < 0) {
            ewk->wu.routine_no[0] = 5;
        }
        ewk->wu.vitality = 0;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
        break;
    case 5:
        if (--ewk->wu.dir_old == 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.mvxy.a[0].sp = 0x120000;
        }
        break;
    case 6:
        if ((ewk->wu.my_mr.size.x -= *(s16*)&ewk->wu.mvxy.a[0]) <= 0) {
            ewk->wu.my_mr.size.x = 0;
        }
        if (ewk->wu.my_mr.size.x <= 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}



s32 Flash_Violent(ewk, start)
WORK_Other* ewk;
s16 start;
{
    ewk->wu.vitality = 0;
    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (start) {
            ewk->wu.routine_no[1]++;
        }
        break;
    case 1:
        if (--ewk->wu.routine_no[2]) {
            break;
        }
        ewk->wu.routine_no[1]++;
        ewk->wu.routine_no[2] = color_flash_tbl[ewk->wu.routine_no[4]];
        ewk->wu.routine_no[4]++;
        ewk->wu.my_col_code = ewk->wu.vital_new;
        ewk->wu.vitality = 1;
        break;
    case 2:
        if (--ewk->wu.routine_no[2]) {
            break;
        }
        if (--ewk->wu.routine_no[3]) {
            ewk->wu.routine_no[1]--;
            ewk->wu.routine_no[2] = color_flash_tbl[ewk->wu.routine_no[4]];
            ewk->wu.routine_no[4]++;
        } else {
            ewk->wu.routine_no[1]++;
        }
        ewk->wu.my_col_code = ewk->wu.vital_old;
        ewk->wu.vitality = 1;
        break;
    default:
        return 1;
    }
    return 0;
}



s32 effect_49_init(s16 Num, s16 Wait) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 49;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2043;
    ewk->wu.my_family = 1;
    ewk->wu.my_priority = 10;
    ewk->wu.position_z = 10;
    ewk->wu.dir_timer = Wait;
    ewk->wu.dir_old = Wait;
    *ewk->wu.char_table = sel_pl_char_table;
    ewk->wu.char_index = 23;
    ewk->wu.my_mr_flag = 1;
    ewk->wu.my_mr.size.x = 127;
    ewk->wu.my_mr.size.y = 127;
    if (Num != 9) {
        ewk->wu.dir_step = Num;
    } else {
        ewk->wu.dir_step = 18;
    }
    ewk->wu.xyz[0].disp.pos = bg_w.bgw[0].xy[0].disp.pos;
    ewk->wu.xyz[0].disp.pos += eff49_pos_tbl[Num];
    ewk->wu.xyz[1].disp.pos = bg_w.bgw[0].xy[1].disp.pos + 32;
    ewk->wu.routine_no[2] = 1;
    ewk->wu.routine_no[3] = 3;
    ewk->wu.routine_no[4] = 0;
    ewk->wu.vitality = 0;
    ewk->wu.vital_new = 0x2045;
    ewk->wu.vital_old = 0x2043;
    return 0;
}
