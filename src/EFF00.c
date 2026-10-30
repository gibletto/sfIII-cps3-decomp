/*
 * EFF00.C  Effect 00 (judgement box display)
 *
 * Effect 00 draws a character's judgement boxes over it: ten rows, the five body boxes, the
 * three attack boxes, the caught box and the hosei box, plus origin and floor marks. Which boxes
 * are shown is chosen by the extra DIP switches (the bit of the master's side) or judge_disp_all;
 * in the debug editors it shows the edited or looked-up box set instead. effect_00_init is
 * called from the debug screens in CMD_MAIN.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFF00.h"
#include "fighter.h"

/* routine_no[0] */
#define R0_INIT         0       /* set up from the master */
#define R0_MOVE         1       /* follow the master and show its boxes */
#define R0_KILL         2       /* put the work back */



void effect_00_move(WORK_Other_JUDGE* ewk) {
    u16 dip;
    ewk->fade_cja.l += 0x2000;
    ewk->fade_cja.w = ewk->fade_cja.w & 3;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        renewal_table_address(ewk, ewk->my_master);
        ewk->wu.cgromtype = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = ewk->wu.spr.disp_colcd = 0x203F;
        ewk->wu.my_priority = ewk->wu.position_z = 16;
        ewk->wu.cg_number = 0x4000;
        ewk->curr_ja = ewk->look_up_flag = 0;
        break;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (ewk->my_master->waku_work_index != ewk->wu.myself) {
            ewk->wu.routine_no[0]++;
            break;
        }
        dip = exsw_1 & 0x3F00;
        if ((ewk->master_id == 0 && (dip & 0x1000) != 0) || (ewk->master_id == 1 && (dip & 0x2000) != 0) || judge_disp_all != 0) {
            if (judge_disp_all) {
                ewk->ja_disp_bit = jdb[15] + 0x400;
                ewk->wu.spr.gfx_cells = jdb2[15] + 2;
            } else {
                dip = (dip >> 8) & 0xF;
                ewk->ja_disp_bit = jdb[dip] + 0x400;
                ewk->wu.spr.gfx_cells = jdb2[dip] + 2;
            }
        } else {
            ewk->wu.spr.gfx_cells = 0;
            ewk->ja_disp_bit = 0;
        }
        renewal_table_address(ewk, ewk->my_master);
        renewal_table_data(ewk);
        sort_push_request2((WORK_Other*)ewk);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back((WORK_Other*)ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



void renewal_table_address(WORK_Other_JUDGE* ewk, WORK* twk) {
    ewk->wu.rl_flag = twk->rl_flag;
    if (judge_disp_all == 0) {
        if (twk->disp_flag) {
            ewk->wu.disp_flag = 1;
        } else {
            ewk->wu.disp_flag = 0;
        }
    }
    if (Debug_Box_Edit) {
        ewk->wu.h_bod = (BODY_BOX*)dbg_copy_buf.h_bod;
        ewk->wu.h_att = (ATTACK_BOX*)dbg_copy_buf.h_att;
        ewk->wu.h_cau = (CAUGHT_BOX*)dbg_copy_buf.h_cau;
        ewk->wu.h_hos = (HOSEI_BOX*)dbg_copy_buf.h_hos;
    } else if (ewk->look_up_flag) {
        ewk->wu.h_bod = (BODY_BOX*)dbg_look_buf.h_bod;
        ewk->wu.h_att = (ATTACK_BOX*)dbg_look_buf.h_att;
        ewk->wu.h_cau = (CAUGHT_BOX*)dbg_look_buf.h_cau;
        ewk->wu.h_hos = (HOSEI_BOX*)dbg_look_buf.h_hos;
    } else {
        ewk->wu.h_bod = twk->h_bod;
        ewk->wu.h_att = twk->h_att;
        ewk->wu.h_cau = twk->h_cau;
        ewk->wu.h_hos = twk->h_hos;
    }
    if (test_flag) {
        ewk->wu.position_x = twk->position_x;
        ewk->wu.position_y = twk->position_y;
    } else {
        ewk->wu.position_x = twk->xyz[0].disp.pos;
        ewk->wu.position_y = twk->xyz[1].disp.pos;
    }
}



void renewal_table_data(WORK_Other_JUDGE* ewk) {
    u16* mm;
    u16* nn;
    s16 i;
    s16 j;
    mm = (u16*)ewk->wu.h_bod;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 4; j++) {
            *(&ewk->jx[i][0] + j) = mm[i * 4 + j];
        }
    }
    mm = (u16*)ewk->wu.h_att;
    for (i = 1; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            ewk->jx[i + 5][j] = mm[i * 4 + j];
        }
    }
    mm = (u16*)ewk->wu.h_att;
    nn = (u16*)ewk->wu.h_cau;
    for (j = 0; j < 4; j++) {
        ewk->jx[5][j] = mm[j];
        ewk->jx[8][j] = nn[j];
    }
    mm = (u16*)ewk->wu.h_hos;
    for (j = 0; j < 4; j++) {
        ewk->jx[9][j] = mm[j];
    }
    for (i = 0; i < 10; i++) {
        ewk->ja[i * 4][0] = ewk->ja[i * 4 + 2][0] = ewk->jx[i][0];
        ewk->ja[i * 4 + 1][0] = ewk->ja[i * 4 + 3][0] = ewk->jx[i][0] + ewk->jx[i][1];
        ewk->ja[i * 4 + 2][1] = ewk->ja[i * 4 + 3][1] = ewk->jx[i][2];
        ewk->ja[i * 4][1] = ewk->ja[i * 4 + 1][1] = ewk->jx[i][2] + ewk->jx[i][3];
    }
    ewk->ja[40][0] = ewk->ja[40][1] = 0;
    ewk->ja[41][0] = 0;
    ewk->ja[41][1] = -ewk->wu.position_y;
}



s32 effect_00_init(WORK* wk) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(0)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 0;
    ewk->wu.work_id = 128;
    ewk->wu.charset_id = wk->charset_id;
    ewk->wu.my_family = wk->my_family;
    ewk->wu.my_ext_pri = wk->my_ext_pri;
    ewk->my_master = (u32*)wk;
    ewk->master_work_id = wk->work_id;
    ewk->master_id = wk->id;
    wk->waku_work_index = ewk->wu.myself;
    return 0;
}
