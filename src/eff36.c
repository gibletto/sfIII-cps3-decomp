/*
 * EFF36.C  Effect 36: zooming pictures
 *
 * effect_36_init(typenum) makes eff36_data_num[typenum] objects from the
 * rows of eff36_data_adrs[typenum] (x, y, pattern, old_rno[0]); each object zooms in by its
 * type and stays until op_obj_disp is cleared (eff36_op_check), then removes itself.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "eff36.h"

/* routine_no[0], type 0 */
#define R0_INIT         0       /* show and start the zoom */
#define R0_ZOOM         1       /* zoom in to full size */
#define R0_HOLD         2       /* hold until the opening clears it */
#define R0_KILL         99      /* (default) put the work back */

/* routine_no[0], types 1 and 2 */
#define R0_PAUSE        2       /* hold for a moment */

extern const s16 eff36_data_num[3];
extern const s16* eff36_data_adrs[3];



void effect_36_move(WORK_Other* ewk) {
    switch (ewk->wu.type) {
    case 0:
        switch (ewk->wu.routine_no[0]) {
        case R0_INIT:
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 1;
            set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
            ewk->wu.my_mr_flag = 1;
            ewk->wu.my_mr.size.x = 0;
            ewk->wu.my_mr.size.y = 0;
            disp_pos_trans_entry5(ewk);
            break;
        case R0_ZOOM:
            if (eff36_op_check(ewk)) {
                if (ewk->wu.my_mr.size.x < 63) {
                    ewk->wu.my_mr.size.x += 6;
                    ewk->wu.my_mr.size.y += 6;
                } else {
                    ewk->wu.routine_no[0]++;
                    ewk->wu.my_mr.size.x = 63;
                    ewk->wu.my_mr.size.y = 63;
                }
            }
            disp_pos_trans_entry5(ewk);
            break;
        case R0_HOLD:
            if (eff36_op_check(ewk)) {
                disp_pos_trans_entry5(ewk);
            }
            break;
        default:
            all_cgps_put_back(ewk);
            push_effect_work(&ewk->wu);
            break;
        }
        break;
    case 1:
        switch (ewk->wu.routine_no[0]) {
        case R0_INIT:
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 1;
            set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
            ewk->wu.my_mr_flag = 1;
            ewk->wu.my_mr.size.x = 0;
            ewk->wu.my_mr.size.y = 63;
            disp_pos_trans_entry5(ewk);
            break;
        case R0_ZOOM:
            if (eff36_op_check(ewk)) {
                ewk->wu.my_mr.size.x += 16;
                if (ewk->wu.my_mr.size.x >= 63) {
                    ewk->wu.old_rno[1] = 32;
                    ewk->wu.routine_no[0]++;
                    ewk->wu.my_mr.size.x = 63;
                    ewk->wu.my_mr.size.y = 63;
                }
            }
            disp_pos_trans_entry5(ewk);
            break;
        case R0_PAUSE:
            ewk->wu.old_rno[1]--;
            if (ewk->wu.old_rno[1] < 0) {
                ewk->wu.routine_no[0]++;
            }
            disp_pos_trans_entry5(ewk);
            break;
        default:
            all_cgps_put_back(ewk);
            push_effect_work(&ewk->wu);
            break;
        }
        break;
    case 2:
        switch (ewk->wu.routine_no[0]) {
        case R0_INIT:
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 1;
            set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
            ewk->wu.my_mr_flag = 1;
            ewk->wu.my_mr.size.x = 0;
            ewk->wu.my_mr.size.y = 63;
            disp_pos_trans_entry5(ewk);
            break;
        case R0_ZOOM:
            if (eff36_op_check(ewk)) {
                ewk->wu.my_mr.size.x += 16;
                if (ewk->wu.my_mr.size.x >= 63) {
                    ewk->wu.old_rno[1] = 32;
                    ewk->wu.routine_no[0]++;
                    ewk->wu.my_mr.size.x = 63;
                    ewk->wu.my_mr.size.y = 63;
                }
            }
            disp_pos_trans_entry5(ewk);
            break;
        case R0_PAUSE:
            ewk->wu.old_rno[1]--;
            if (ewk->wu.old_rno[1] < 0) {
                ewk->wu.routine_no[0]++;
            }
            disp_pos_trans_entry5(ewk);
            break;
        default:
            all_cgps_put_back(ewk);
            push_effect_work(&ewk->wu);
            break;
        }
        break;
    }
}



/* the object ends when op_obj_disp is cleared */
/* provisional name */
s32 eff36_op_check(WORK_Other* ewk) {
    if (op_obj_disp) {
        return 1;
    } else {
        ewk->wu.routine_no[0] = R0_KILL;
        ewk->wu.disp_flag = 0;
        return 0;
    }
}



/* Create the zooming pictures for the selected type. */
s32 effect_36_init(s16 typenum) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data_ptr;
    data_ptr = eff36_data_adrs[typenum];
    for (i = 0; i < eff36_data_num[typenum]; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 36;
        ewk->wu.type = typenum;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 64;
        ewk->wu.my_family = 2;
        ewk->wu.my_priority = ewk->wu.position_z = 51;
        ewk->wu.old_rno[2] = i;
        ewk->wu.char_table[0] = etc_char_table;
        ewk->wu.xyz[0].disp.pos = *data_ptr++;
        ewk->wu.xyz[1].disp.pos = *data_ptr++;
        ewk->wu.char_index = *data_ptr++;
        ewk->wu.old_rno[0] = *data_ptr++;
        ewk->wu.mvxy.a[0].sp = -0x30000;
        ewk->wu.mvxy.a[1].sp = 0;
    }
    return 0;
}



const s16 eff36_data_00[1][4] = { { 0x200, 0x78, 0x33, 1 } };
const s16 eff36_data_01[1][4] = { { 0x200, 0x68, 0x31, 1 } };
const s16 eff36_data_02[1][4] = { { 0x200, 0x68, 0x32, 1 } };
const s16 eff36_data_num[3] = { 1, 1, 1 };
const s16* eff36_data_adrs[3] = { eff36_data_00[0], eff36_data_01[0], eff36_data_02[0] };
