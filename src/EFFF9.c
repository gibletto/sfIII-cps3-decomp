/*
 * EFFF9.C  Effect F9: ending message window
 *
 * effect_F9_init(pl_no) (from end_main_c.c) opens the window for the character's ending.
 * effect_F9_move picks the message by Country and Language (effF9_mes_jp / _en / _es / _pt), loads
 * its graphics and shows it as connected cells on family 4 until its time (keep_mes_no) runs out, then
 * calls Rewrite. The ending scripts drive it through Rewrite_End_Message (start a scene's
 * message list from txt_no_tbl), Rewrite (the next message and time pair) and
 * Set_Direct_Message (one given message); each opens a new window, and the old one closes when
 * efff9_suicide is set.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "CMD_MAIN.h"
#include "cmd_main_2.h"
#include "ta_sub.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "EFFF9.h"

/* routine_no[0] */
#define R0_INIT         0       /* load the message */
#define R0_MOVE         1       /* show the message until replaced */
#define R0_END          2       /* hidden for a frame */
#define R0_KILL         3       /* (default) put the work back */

s16 efff9_suicide;
const u16** efff9_txt_no_adrs;
const u16* efff9_txt_scene_adrs;
s16 efff9_PL_NO;
s16 efff9_txt_point;
s16 efff9_message;
s16 keep_mes_no;
s16 efff9_mes_no;

void effect_F9_move(WORK_Other_CONN* ewk) {
    const u16* chr_data;
    const CONN* conn_data;
    s16 i;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        switch (Country) {
        case 1:
            conn_data = effF9_mes_jp[ewk->master_player][mes_already].conn;
            chr_data = effF9_mes_jp[ewk->master_player][mes_already].chr;
            break;
        case 2:
            conn_data = effF9_mes_en[ewk->master_player][mes_already].conn;
            chr_data = effF9_mes_en[ewk->master_player][mes_already].chr;
            break;
        case 3:
            switch (Language) {
            case 0:
                conn_data = effF9_mes_en[ewk->master_player][mes_already].conn;
                chr_data = effF9_mes_en[ewk->master_player][mes_already].chr;
                break;
            case 1:
                conn_data = effF9_mes_es[ewk->master_player][mes_already].conn;
                chr_data = effF9_mes_es[ewk->master_player][mes_already].chr;
                break;
            case 2:
                conn_data = effF9_mes_pt[ewk->master_player][mes_already].conn;
                chr_data = effF9_mes_pt[ewk->master_player][mes_already].chr;
                break;
            }
            break;
        case 4:
            conn_data = effF9_mes_en[ewk->master_player][mes_already].conn;
            chr_data = effF9_mes_en[ewk->master_player][mes_already].chr;
            break;
        case 5:
            conn_data = effF9_mes_es[ewk->master_player][mes_already].conn;
            chr_data = effF9_mes_es[ewk->master_player][mes_already].chr;
            break;
        case 6:
            conn_data = effF9_mes_pt[ewk->master_player][mes_already].conn;
            chr_data = effF9_mes_pt[ewk->master_player][mes_already].chr;
            break;
        case 7:
            switch (Language) {
            case 0:
                conn_data = effF9_mes_en[ewk->master_player][mes_already].conn;
                chr_data = effF9_mes_en[ewk->master_player][mes_already].chr;
                break;
            case 1:
                conn_data = effF9_mes_es[ewk->master_player][mes_already].conn;
                chr_data = effF9_mes_es[ewk->master_player][mes_already].chr;
                break;
            case 2:
                conn_data = effF9_mes_pt[ewk->master_player][mes_already].conn;
                chr_data = effF9_mes_pt[ewk->master_player][mes_already].chr;
                break;
            }
            break;
        default:
            conn_data = effF9_mes_en[ewk->master_player][mes_already].conn;
            chr_data = effF9_mes_en[ewk->master_player][mes_already].chr;
            break;
        }
        for (i = 0; i < chr_data[0]; i++) {
            load_char_gfx(chr_data[i + 1], 1);
        }
        ewk->num_of_conn = chr_data[i + 1];
        ewk->wu.disp_flag = 1;
        ewk->wu.old_cgnum = ewk->wu.cg_number = 0;
        for (i = 0; i < ewk->num_of_conn; i++) {
            ewk->conn[i].nx = conn_data[i].nx;
            ewk->conn[i].ny = conn_data[i].ny;
            ewk->conn[i].col = conn_data[i].col;
            ewk->conn[i].chr = conn_data[i].chr;
        }
        efff9_suicide = 0;
        ewk->wu.vitality = 240;
        ewk->wu.cg_number++;
        ewk->wu.cg_number &= 0x7FFF;
        break;
    case R0_MOVE:
        if (keep_mes_no == 0) {
            Rewrite();
            ewk->wu.cg_number++;
            ewk->wu.cg_number &= 0x7FFF;
            sort_push_request3(&ewk->wu);
            break;
        }
        keep_mes_no--;
        if (efff9_suicide == 1) {
            ewk->wu.disp_flag = 0;
            ewk->wu.routine_no[0] += 2;
            break;
        }
        ewk->wu.cg_number++;
        ewk->wu.cg_number &= 0x7FFF;
        sort_push_request3(&ewk->wu);
        break;
    case R0_END:
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

s32 effect_F9_init(s16 pl_no)
{
    WORK_Other* ewk;
    s16 ix;

    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.routine_no[0] = R0_INIT;
    mes_already = 0;
    efff9_suicide = 0;
    efff9_txt_point = 0;
    efff9_wk_set((WORK_Other_CONN*)ewk);
    efff9_PL_NO = pl_no;
    ewk->master_player = efff9_PL_NO;
    return 0;
}

void efff9_wk_set(WORK_Other_CONN* ewk) {
    ewk->wu.be_flag = 1;
    ewk->wu.id = 159;
    ewk->wu.work_id = 16;
    ewk->wu.rl_flag = 0;
    ewk->wu.cgromtype = 1;
    ewk->wu.sync_suzi = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0;
    ewk->wu.my_family = 4;
    ewk->wu.my_priority = 5;
    if (Game_setting.Screen_Mode == 0) {
        ewk->wu.position_x = 376;
    } else {
        ewk->wu.position_x = 392;
    }
    ewk->wu.position_y = 24;
    ewk->wu.position_z = 5;
}

s32 Rewrite_End_Message(u16 mes_no) {
    WORK_Other* ewk;
    s16 ix;
    ix = pull_effect_work(4);
    if (ix == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    efff9_mes_no = mes_no;
    ewk->wu.routine_no[0] = R0_INIT;
    efff9_suicide = 1;
    ewk->master_player = efff9_PL_NO;
    efff9_wk_set((WORK_Other_CONN*)ewk);
    efff9_txt_point = 2;
    efff9_txt_no_adrs = txt_no_tbl[efff9_PL_NO];
    efff9_txt_scene_adrs = efff9_txt_no_adrs[mes_no];
    efff9_message = efff9_txt_scene_adrs[0];
    keep_mes_no = *(s16*)(efff9_txt_scene_adrs + 1);
    mes_already = efff9_message;
    return 0;
}

s32 Set_Direct_Message(s16 mes) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.routine_no[0] = R0_INIT;
    efff9_suicide = 0;
    ewk->master_player = efff9_PL_NO;
    efff9_wk_set((WORK_Other_CONN*)ewk);
    mes_already = mes;
    return 0;
}

s32 Rewrite(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.routine_no[0] = R0_INIT;
    efff9_suicide = 1;
    ewk->master_player = efff9_PL_NO;
    efff9_wk_set((WORK_Other_CONN*)ewk);
    efff9_txt_no_adrs = txt_no_tbl[efff9_PL_NO];
    efff9_txt_scene_adrs = efff9_txt_no_adrs[efff9_mes_no];
    efff9_message = efff9_txt_scene_adrs[efff9_txt_point];
    keep_mes_no = efff9_txt_scene_adrs[efff9_txt_point + 1];
    efff9_txt_point += 2;
    mes_already = efff9_message;
    return 0;
}
