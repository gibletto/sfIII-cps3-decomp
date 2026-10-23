/*
 * EFFB8.C  Effect B8: the winner's message banner
 *
 * Effect B8 is the win message shown after a match. effect_B8_init takes the winner and chooses the
 * message: the opponent's line when the straight-win, straight-loss or versus win count is a multiple of 8,
 * otherwise one of the four lines of the set for the winner's remaining vitality (effB8_vital_rank), not the
 * same line twice in a row. effect_B8_move picks effB8_mes_jp / _en / _es / _pt by Country and Language,
 * loads the line's graphics and connected sprites and holds the banner until Suicide; on death it purges
 * the line's graphics. With extra switch 2 bit 2 on, player 1's buttons cycle characters and messages
 * through effB8_mes_change_init. effB8_conn_set and effB8_conn_purge load and free the connected cells of
 * a character's entry in effB8_conn_tbl.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLS02.h"
#include "EFFB8.h"



s16 test_pl_no;
s16 test_mes_no;
s16 test_in;

extern const EFFB8_MESSAGE* effB8_conn_tbl[];

extern u8 Straight_Win_Count;
extern u8 Straight_Lose_Count;



void effect_B8_move(WORK_Other_CONN* ewk) {
    const CONN* conn_data;
    const u16* chr_data;
    u16 sw;
    u16 chr;
    s16 num;
    s16 i;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        switch (Country) {
        case 1:
            conn_data = effB8_mes_jp[ewk->master_player][mes_already].conn;
            chr_data = effB8_mes_jp[ewk->master_player][mes_already].chr;
            break;
        case 4:
            conn_data = effB8_mes_en[ewk->master_player][mes_already].conn;
            chr_data = effB8_mes_en[ewk->master_player][mes_already].chr;
            break;
        default:
            conn_data = effB8_mes_jp[ewk->master_player][mes_already].conn;
            chr_data = effB8_mes_jp[ewk->master_player][mes_already].chr;
            break;
        }
        switch (Country) {
        case 1:
            conn_data = effB8_mes_jp[ewk->master_player][mes_already].conn;
            chr_data = effB8_mes_jp[ewk->master_player][mes_already].chr;
            break;
        case 3:
            switch (Language) {
            case 0:
                conn_data = effB8_mes_en[ewk->master_player][mes_already].conn;
                chr_data = effB8_mes_en[ewk->master_player][mes_already].chr;
                break;
            case 1:
                conn_data = effB8_mes_es[ewk->master_player][mes_already].conn;
                chr_data = effB8_mes_es[ewk->master_player][mes_already].chr;
                break;
            case 2:
                conn_data = effB8_mes_pt[ewk->master_player][mes_already].conn;
                chr_data = effB8_mes_pt[ewk->master_player][mes_already].chr;
                break;
            }
            break;
        case 5:
            conn_data = effB8_mes_es[ewk->master_player][mes_already].conn;
            chr_data = effB8_mes_es[ewk->master_player][mes_already].chr;
            break;
        case 6:
            conn_data = effB8_mes_pt[ewk->master_player][mes_already].conn;
            chr_data = effB8_mes_pt[ewk->master_player][mes_already].chr;
            break;
        case 7:
            switch (Language) {
            case 0:
                conn_data = effB8_mes_en[ewk->master_player][mes_already].conn;
                chr_data = effB8_mes_en[ewk->master_player][mes_already].chr;
                break;
            case 1:
                conn_data = effB8_mes_es[ewk->master_player][mes_already].conn;
                chr_data = effB8_mes_es[ewk->master_player][mes_already].chr;
                break;
            case 2:
                conn_data = effB8_mes_pt[ewk->master_player][mes_already].conn;
                chr_data = effB8_mes_pt[ewk->master_player][mes_already].chr;
                break;
            }
            break;
        case 2:
            conn_data = effB8_mes_en[ewk->master_player][mes_already].conn;
            chr_data = effB8_mes_en[ewk->master_player][mes_already].chr;
            break;
        case 4:
            conn_data = effB8_mes_en[ewk->master_player][mes_already].conn;
            chr_data = effB8_mes_en[ewk->master_player][mes_already].chr;
            break;
        default:
            conn_data = effB8_mes_en[ewk->master_player][mes_already].conn;
            chr_data = effB8_mes_en[ewk->master_player][mes_already].chr;
        }
        for (i = 0; i < chr_data[0]; i++) {
            load_char_gfx(chr_data[i + 1], 1);
        }
        ewk->num_of_conn = chr_data[i + 1];
        ewk->wu.disp_flag = 1;
        ewk->wu.cg_number = 0;
        ewk->wu.old_cgnum = 0;
        for (i = 0; i < ewk->num_of_conn; i++) {
            ewk->conn[i].nx = conn_data[i].nx;
            ewk->conn[i].ny = conn_data[i].ny;
            ewk->conn[i].col = conn_data[i].col;
            ewk->conn[i].chr = conn_data[i].chr;
        }
        ewk->wu.vitality = 240;
        ewk->wu.cg_number++;
        ewk->wu.cg_number &= 0x7FFF;
        break;
    case 1:
        if (Suicide == 1) {
            ewk->wu.disp_flag = 0;
            ewk->wu.routine_no[0]++;
            break;
        }
        if (exsw_2 & 4) {
            sw = (u16)(p1sw_0 & ~p1sw_1);
            if (sw & 0x180) {
                ewk->wu.routine_no[0]++;
                test_in = 1;
                if (sw & 0x80) {
                    test_pl_no++;
                    if (test_pl_no > 12) {
                        test_pl_no = 0;
                    }
                }
                if (sw & 0x100) {
                    test_mes_no++;
                    if (test_mes_no > 23) {
                        test_mes_no = 0;
                    }
                }
                effB8_mes_change_init(test_pl_no, test_mes_no);
            }
        }
        ewk->wu.cg_number++;
        ewk->wu.cg_number &= 0x7FFF;
        sort_push_request3(&ewk->wu);
        break;
    case 2:
        ewk->wu.routine_no[0]++;
        break;
    default:
        (void)((WORK*)Country)->id;
        if (test_in == 0) {
            switch (Country) {
            case 1:
                chr_data = effB8_mes_jp[ewk->master_player][mes_already].chr;
                break;
            case 4:
                chr_data = effB8_mes_en[ewk->master_player][mes_already].chr;
                break;
            default:
                chr_data = effB8_mes_jp[ewk->master_player][mes_already].chr;
                break;
            }
            num = *chr_data;
            chr_data++;
            for (i = 0; i < num; i = i + 1) {
                chr = *chr_data;
                purge_char_gfx(chr);
                chr_data = chr_data + 1;
            }
        }
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

s32 effect_B8_init(s8 WIN_PL_NO) {
    PLW* wk;
    WORK_Other_CONN* ewk;
    s16 work_index;
    s16 vital;
    s8 count;
    u16 message;

    test_in = 0;
    wk = &plw[WIN_PL_NO];
    work_index = pull_effect_work(4);
    if (work_index == -1) {
        return -1;
    }
    ewk = (WORK_Other_CONN*)frw[work_index];
    ewk->wu.routine_no[0] = 0;
    wk_set(ewk);
    ewk->my_master = (u32*)wk;
    ewk->master_work_id = wk->wu.work_id;
    ewk->master_id = wk->wu.id;
    ewk->master_player = wk->player_number;
    test_pl_no = wk->player_number;
    vital = wk->wu.vital_new;
    if (Play_Type == 0) {
        if (wk->wu.operator) {
            count = Straight_Win_Count;
        } else {
            count = Straight_Lose_Count;
        }
    } else {
        count = Win_Record[wk->wu.id];
    }
    if (count % 8 == 0) {
        message = ((PLW*)wk->wu.target_adrs)->player_number + 11;
    } else {
        message = (random_32_com() & 3) + effB8_vital_rank(vital);
        if (mes_already == message) {
            message = (message & 0xFC) | ((message + 1) & 3);
        }
    }
    mes_already = message;
    test_mes_no = message;
    return 0;
}



/* provisional name */
s32 effB8_vital_rank(s16 vital) {
    if (vital < 32) {
        return 8;
    } else if (vital > 128) {
        return 4;
    } else {
        return 0;
    }
}



void wk_set(WORK_Other_CONN* ewk) {
    ewk->wu.be_flag = 1;
    ewk->wu.id = 118;
    ewk->wu.work_id = 16;
    ewk->wu.rl_flag = 0;
    ewk->wu.cgromtype = 1;
    ewk->wu.sync_suzi = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 88;
    ewk->wu.my_family = 2;
    ewk->wu.my_priority = 35;
    if (Game_setting.mode == 0) {
        ewk->wu.position_x = 0x238;
    } else {
        ewk->wu.position_x = 0x280;
    }
    ewk->wu.position_y = 24;
    ewk->wu.position_z = 35;
}



/* provisional name */
s32 effB8_mes_change_init(s16 pl, s16 mes_no) {
    WORK_Other_CONN* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other_CONN*)frw[ix];
    ewk->wu.routine_no[0] = 0;
    wk_set(ewk);
    ewk->master_player = pl;
    mes_already = mes_no;
    return 0;
}



/* provisional name */
void effB8_conn_set(ewk, pl, mes_no)
    WORK_Other_CONN* ewk;
    s8 pl;
    u16 mes_no;
{
    const CONN* conn_data;
    const u16* chr_data;
    s16 i;
    ewk->wu.rl_flag = 0;
    ewk->wu.cgromtype = 1;
    pl &= 0x7F;
    conn_data = effB8_conn_tbl[pl][mes_no].conn;
    chr_data = effB8_conn_tbl[pl][mes_no].chr;
    for (i = 0; i < chr_data[0]; i++) {
        load_char_gfx(chr_data[i + 1], 1);
    }
    ewk->num_of_conn = chr_data[i + 1];
    ewk->wu.disp_flag = 1;
    ewk->wu.cg_number = 0;
    ewk->wu.old_cgnum = 0;
    for (i = 0; i < ewk->num_of_conn; i++) {
        ewk->conn[i].nx = conn_data[i].nx;
        ewk->conn[i].ny = conn_data[i].ny;
        ewk->conn[i].col = conn_data[i].col;
        ewk->conn[i].chr = conn_data[i].chr;
    }
    ewk->wu.cg_number++;
    ewk->wu.cg_number &= 0x7FFF;
}



/* provisional name */
void effB8_conn_purge(ewk, pl, mes_no)
    WORK_Other_CONN* ewk;
    s8 pl;
    u16 mes_no;
{
    const u16* chr_data;
    u16 chr;
    s16 num;
    s16 i;
    pl &= 0x7F;
    chr_data = effB8_conn_tbl[pl][mes_no].chr;
    num = *chr_data;
    chr_data++;
    for (i = 0; i < num; i++) {
        chr = *chr_data;
        purge_char_gfx(chr);
        chr_data++;
    }
    all_cgps_put_back(&ewk->wu);
}
