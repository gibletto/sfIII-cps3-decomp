/*
 * EFFF2_CODE.C  Effect F2: flying objects of an ending scene
 *
 * effect_F2_init(no) (from end_8.c) creates four objects (effH3_char_table) from efff2_data_tbl,
 * starting at row no (priority and pattern; outside the scene's step 1 they all use pattern 8). Each
 * flies in three stages, taking new speeds from efff2_speed_tbl[stage][object] as it passes x 0x1E0
 * and 0x240, and starts again from efff2_pos_tbl past 0x2C0. In step 1 the first object starts four
 * more (effect_F2_init(4)) at its second stage. All are freed when the ending scene moves on
 * (end_w.r_no_2 changes).
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
#include "PLS02.h"
#include "aboutspr.h"
#include "EFFF2_code.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the pattern */
#define R0_START        1       /* go home with the first speeds */
#define R0_FLY          2       /* fly through the three stages */
#define R0_KILL         99      /* (default) put the work back */



extern const s16 efff2_pos_tbl[8][2];
extern const s32 efff2_speed_tbl[3][8][4];
extern const s16 efff2_data_tbl[8][3];



void effect_F2_move(WORK_Other* ewk) {
    const s32* p;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
    case R0_START:
        if (ewk->wu.old_rno[0] != end_w.r_no_2) {
            ewk->wu.routine_no[0] = R0_KILL;
        } else {
            ewk->wu.routine_no[0]++;
            ewk->wu.old_rno[2] = 0;
            p = &efff2_speed_tbl[ewk->wu.old_rno[2]][ewk->wu.old_rno[1]][0];
            ewk->wu.mvxy.a[0].sp = *p++;
            ewk->wu.mvxy.d[0].sp = *p++;
            ewk->wu.mvxy.a[1].sp = *p++;
            ewk->wu.mvxy.d[1].sp = *p;
            ewk->wu.xyz[0].disp.pos = efff2_pos_tbl[ewk->wu.old_rno[1]][0];
            ewk->wu.xyz[1].disp.pos = efff2_pos_tbl[ewk->wu.old_rno[1]][1];
        }
        break;
    case R0_FLY:
        if (ewk->wu.old_rno[0] != end_w.r_no_2) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
        char_move(&ewk->wu);
        add_x_sub(ewk);
        add_y_sub(ewk);
        switch (ewk->wu.old_rno[2]) {
        case 0:
            if (ewk->wu.xyz[0].disp.pos > 0x1E0) {
                ewk->wu.old_rno[2]++;
                p = &efff2_speed_tbl[ewk->wu.old_rno[2]][ewk->wu.old_rno[1]][0];
                ewk->wu.mvxy.a[0].sp = *p++;
                ewk->wu.mvxy.d[0].sp = *p++;
                ewk->wu.mvxy.a[1].sp = *p++;
                ewk->wu.mvxy.d[1].sp = *p;
            }
            break;
        case 1:
            if (ewk->wu.xyz[0].disp.pos > 0x240) {
                ewk->wu.old_rno[2]++;
                p = &efff2_speed_tbl[ewk->wu.old_rno[2]][ewk->wu.old_rno[1]][0];
                ewk->wu.mvxy.a[0].sp = *p++;
                ewk->wu.mvxy.d[0].sp = *p++;
                ewk->wu.mvxy.a[1].sp = *p++;
                ewk->wu.mvxy.d[1].sp = *p;
                if (ewk->wu.old_rno[4]) {
                    if (ewk->wu.old_rno[1] == 0) {
                        effect_F2_init(4);
                    }
                }
            }
            break;
        case 2:
            if (ewk->wu.xyz[0].disp.pos > 0x2C0) {
                ewk->wu.routine_no[0] = R0_START;
            }
            break;
        }
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_F2_init(s16 no) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data_ptr = &efff2_data_tbl[no][0];
    (void)&((WORK*)data_ptr)->id;
    for (i = 0; i < 4; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        (void)&((WORK*)(s32)ix)->id;
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 152;
        ewk->wu.work_id = 16;
        ewk->wu.old_rno[1] = no + i;
        ewk->wu.cgromtype = 1;
        ewk->wu.my_family = 1;
        ewk->wu.old_rno[0] = end_w.r_no_2;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 32;
        ewk->wu.char_table[0] = effH3_char_table;
        ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
        if (end_w.r_no_2 == 1) {
            ewk->wu.char_index = *data_ptr++;
            ewk->wu.old_rno[4] = 1;
        } else {
            ewk->wu.char_index = 8;
            ewk->wu.old_rno[4] = 0;
        }
        ewk->wu.old_rno[3] = *data_ptr++;
    }

}


