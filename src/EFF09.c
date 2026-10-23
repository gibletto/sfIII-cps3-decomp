/*
 * EFF09.C  Effect 09: character props for appearances and win poses
 *
 * Effect 09 is a family of props that belong to a character. effect_09_init2 creates one
 * from eff09_data2 (colour, offset from the owner, priority, animation);
 * effect_09_init creates one from eff09_data.
 * effect_09_move dispatches through eff09_tbl to the behaviour routines eff09_0000 to
 * eff09_8000: plain animations, props thrown and caught, and sean_ball_move, a ball that
 * bounces under gravity and is hit-checked against the players (creating effect B4).
 * Voices are at player * 0x200 and the eff09_1000 prop has a stage 8 Y.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLSGAUGE.h"
#include "ta_sub.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "effb3.h"
#include "EFFB4.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "HITCHECK.h"
#include "PLS02.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFF09.h"


/* initialised work RAM (02006A84) */
void (*eff09_tbl[9])(WORK_Other*) = {
    eff09_0000,
    eff09_1000,
    eff09_2000,
    eff09_3000,
    eff09_4000,
    eff09_5000,
    eff09_6000,
    eff09_7000,
    eff09_8000,
};


void effect_09_move(WORK_Other* ewk) {
    if (compel_dead_check(ewk)) {
        ewk->wu.disp_flag = 0;
        ewk->wu.routine_no[1] = 99;
    }
    eff09_tbl[ewk->wu.routine_no[0]](ewk);
}



void eff09_0000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.dead_f = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case 1:
        if (!EXE_flag && !Game_pause && ewk->wu.hit_stop) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                ewk->wu.routine_no[1]++;
                ewk->wu.disp_flag = 0;
            }
        }
        disp_pos_trans_entry_rs(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



void eff09_1000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.my_priority = ewk->wu.position_z = 67;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 4;
        ewk->wu.old_rno[0] = random_16_com();
        ewk->wu.old_rno[0] &= 1;
        if (ewk->master_id) {
            ewk->wu.type = 10;
        } else {
            ewk->wu.type = 9;
        }
        if (ewk->wu.old_rno[0]) {
            set_char_move_init(&ewk->wu, 0, 25);
        } else {
            set_char_move_init(&ewk->wu, 0, 65);
        }
        sort_push_request(&ewk->wu);
        break;
    case 1:
    case 3:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                ewk->wu.routine_no[1]++;
            }
        }
        if (obr_no_disp_check()) {
            break;
        }
        sort_push_request(&ewk->wu);
        break;
    case 2:
        if (obr_no_disp_check()) {
            break;
        }
        if (bg_w.stage == 8 && bg_w.area == 0) {
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = stage8_base_y - 36;
        }
        if (ewk->wu.old_rno[0] && !EXE_flag && !Game_pause) {
            if (eff_hit_check(ewk, 0)) {
                ewk->wu.routine_no[1]++;
                set_char_move_init(&ewk->wu, 0, 65);
            }
        }
        sort_push_request(&ewk->wu);
        break;
    case 4:
        if (obr_no_disp_check()) {
            break;
        }
        if (bg_w.stage == 8 && bg_w.area == 0) {
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = stage8_base_y - 36;
        }
        sort_push_request(&ewk->wu);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



void eff09_2000(WORK_Other* ewk) {
    s16 work;
    const s32* ptr;
    u16 sw_work;
    const s16* pl_hit_ptr;
    PLW* hit_pl;
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        Appear_free = 0;
        if (ewk->master_id) {
            sw_work = p2sw_0;
        } else {
            sw_work = p1sw_0;
        }
        if (sw_work & 0x1000) {
            work = 0;
        } else {
            work = random_16_com();
            work &= 1;
        }
        ewk->wu.dir_step = work;
        ptr = eff09_2000_data[ewk->wu.dir_step];
        ewk->wu.mvxy.a[0].sp = *ptr++;
        ewk->wu.mvxy.a[1].sp = *ptr++;
        ewk->wu.mvxy.d[0].sp = *ptr++;
        ewk->wu.mvxy.d[1].sp = *ptr++;
        if (ewk->wu.rl_flag) {
            ewk->wu.mvxy.a[0].sp = -ewk->wu.mvxy.a[0].sp;
            ewk->wu.mvxy.d[0].sp = -ewk->wu.mvxy.d[0].sp;
        }
        ewk->wu.old_rno[0] = ewk->wu.old_rno[1] = ewk->wu.old_rno[2] = ewk->wu.old_rno[3] = 0;
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case 1:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
            if (ewk->wu.xyz[0].disp.pos > 784 || ewk->wu.xyz[0].disp.pos < 240) {
                ewk->wu.routine_no[1] = 99;
                Appear_free = 1;
            }
            if (ewk->master_id) {
                sw_work = p2sw_0;
                hit_pl = &plw[0];
                pl_hit_ptr = &plw[0].wu.h_bod->body_dm[0][0];
            } else {
                sw_work = p1sw_0;
                hit_pl = &plw[1];
                pl_hit_ptr = &plw[1].wu.h_bod->body_dm[0][0];
            }
            sean_ball_move(ewk, sw_work);
            if (hit_check_subroutine(&hit_pl->wu, &ewk->wu, pl_hit_ptr, sean_ball_hit)) {
                ewk->wu.routine_no[1]++;
                ball_bound_set(ewk);
                set_char_move_init2(&hit_pl->wu, 9, 63, 1, 0);
                Appear_free = 2;
                effect_B4_init(ewk);
                work = random_16_com();
                work &= 7;
                add_super_arts_gauge(plw[ewk->master_id].sa, 1);
                break;
            }
            if (ewk->wu.xyz[1].disp.pos < 0) {
                Sound_SE((ewk->master_id * 0x200) + 0x157);
                ewk->wu.routine_no[1]++;
                ball_bound_set(ewk);
                Appear_free = 1;
            }
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case 2:
        if (!EXE_flag && !Game_pause) {
            if (ewk->wu.xyz[0].disp.pos > 784 || ewk->wu.xyz[0].disp.pos < 240 || ewk->wu.xyz[1].disp.pos < -56) {
                ewk->wu.routine_no[1]++;
            } else {
                add_x_sub(ewk);
                add_y_sub(ewk);
            }
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case 3:
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



void sean_ball_move(ewk, sw_work)
WORK_Other* ewk;
u16 sw_work;
{
    if (!plw[ewk->master_id].wu.operator) {
        return;
    }
    if (sw_work & 1) {
        ewk->wu.old_rno[0]++;
        if (ewk->wu.old_rno[0] < 8) {
            ewk->wu.mvxy.d[1].sp += eff09_add_tbl0[ewk->wu.dir_step][0];
        }
    }
    if (sw_work & 2) {
        ewk->wu.old_rno[1]++;
        if (ewk->wu.old_rno[1] < 8) {
            ewk->wu.mvxy.d[1].sp += eff09_add_tbl0[ewk->wu.dir_step][1];
        }
    }
    if (sw_work & 4) {
        ewk->wu.old_rno[2]++;
        if (ewk->wu.rl_flag) {
            if (ewk->wu.old_rno[2] < 4) {
                ewk->wu.mvxy.d[0].sp += eff09_add_tbl1[ewk->wu.dir_step][0];
            }
        } else if (ewk->wu.old_rno[2] < 8) {
            ewk->wu.mvxy.d[0].sp += eff09_add_tbl2[ewk->wu.dir_step][0];
        }
    }
    if (sw_work & 8) {
        ewk->wu.old_rno[3]++;
        if (ewk->wu.rl_flag) {
            if (ewk->wu.old_rno[3] < 8) {
                ewk->wu.mvxy.d[0].sp += eff09_add_tbl1[ewk->wu.dir_step][1];
            }
        } else if (ewk->wu.old_rno[3] < 4) {
            ewk->wu.mvxy.d[0].sp += eff09_add_tbl2[ewk->wu.dir_step][1];
        }
    }
}



void ball_bound_set(WORK_Other* ewk) {
    ewk->wu.mvxy.a[0].sp = -0x40000;
    ewk->wu.mvxy.a[1].sp = 0x60000;
    ewk->wu.mvxy.d[0].sp = -0x1000;
    ewk->wu.mvxy.d[1].sp = -0x8000;
    ewk->wu.dir_timer = 12;
    if (ewk->wu.rl_flag) {
        ewk->wu.mvxy.a[0].sp = -ewk->wu.mvxy.a[0].sp;
        ewk->wu.mvxy.d[0].sp = -ewk->wu.mvxy.d[0].sp;
    }
}



void eff09_3000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (Exec_Wipe) {
            ewk->wu.routine_no[1] = 99;
            break;
        }
        Sound_SE((Winner_id * 0x200) + 0x136);
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.old_rno[0] = 96;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[0], ewk->wu.xyz[0].disp.pos, 16, 1, 2);
        break;
    case 1:
        if (!EXE_flag && !Game_pause) {
            ewk->wu.old_rno[0]--;
            if (ewk->wu.old_rno[0] <= 0) {
                ewk->wu.routine_no[1]++;
            } else {
                add_y_sub(ewk);
            }
            char_move(&ewk->wu);
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case 2:
        if (Exec_Wipe) {
            Sound_SE((Winner_id * 0x200) + 0x130);
        }
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



void eff09_4000(WORK_Other* ewk) {
    s16 work;
    s16 work2;
    WORK* oya_ptr;
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.kage_flag = 1;
        ewk->wu.kage_hx = 2;
        ewk->wu.kage_hy = -3;
        ewk->wu.kage_prio = 71;
        ewk->wu.kage_char = 0;
        ewk->wu.my_col_code = 0x2000;
        ewk->wu.position_z = ewk->wu.my_priority = 20;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        oya_ptr = (WORK*)ewk->my_master;
        ewk->wu.rl_flag = oya_ptr->rl_flag;
        if (oya_ptr->rl_flag) {
            work = bg_w.bgw[1].xy[0].disp.pos - 272;
            work2 = oya_ptr->xyz[0].disp.pos - 88;
        } else {
            work = bg_w.bgw[1].xy[0].disp.pos + 272;
            work2 = oya_ptr->xyz[0].disp.pos + 88;
        }
        ewk->wu.xyz[0].disp.pos = work;
        ewk->wu.old_rno[0] = 202;
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[0], work2, 0, 0, 2);
        break;
    case 1:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            add_x_sub(ewk);
            ewk->wu.old_rno[0]--;
            if (ewk->wu.old_rno[0] <= 0) {
                ewk->wu.routine_no[1]++;
                set_char_move_init(&ewk->wu, 0, 29);
            }
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case 2:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



void eff09_5000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case 1:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



void eff09_6000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case 1:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 9) {
            ewk->wu.routine_no[1]++;
            ewk->wu.disp_flag = 2;
            ewk->wu.blink_timing = 1;
        }
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    case 2:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 0xFF) {
            ewk->wu.routine_no[1]++;
        } else {
            suzi_sync_pos_set(ewk);
            sort_push_request(&ewk->wu);
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
    }
}



void eff09_7000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        ewk->wu.old_rno[0] = 32;
        if (ewk->master_id) {
            ewk->wu.mvxy.a[0].sp = 0x30000;
            ewk->wu.mvxy.a[1].sp = 0x90000;
            ewk->wu.mvxy.d[0].sp = 0x1000;
            ewk->wu.mvxy.d[1].sp = -0x6000;
        } else {
            ewk->wu.mvxy.a[0].sp = -0x30000;
            ewk->wu.mvxy.a[1].sp = 0x90000;
            ewk->wu.mvxy.d[0].sp = -0x1000;
            ewk->wu.mvxy.d[1].sp = -0x6000;
        }
        break;
    case 1:
        ewk->wu.old_rno[0]--;
        if (ewk->wu.old_rno[0] < 0) {
            ewk->wu.routine_no[1]++;
            break;
        }
        char_move(&ewk->wu);
        add_x_sub(ewk);
        add_y_sub(ewk);
        suzi_sync_pos_set(ewk);
        sort_push_request(&ewk->wu);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



void eff09_8000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.dead_f = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case 1:
        if (ewk->wu.hit_stop) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 0xFF) {
                ewk->wu.routine_no[1]++;
                ewk->wu.disp_flag = 0;
            }
        }
        disp_pos_trans_entry_s(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_09_init(WORK_Other* mk, s8 kind) {
    WORK_Other* ewk;
    const s16* data;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.type = kind;
    data = (const s16*)((const u8*)eff09_data + (s8)((s8)ewk->wu.type * 18));
    ewk->wu.be_flag = 1;
    ewk->wu.id = 9;
    ewk->wu.work_id = 16;
    ewk->wu.my_priority = 64;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.char_table[0] = eff09_char_table;
    ewk->wu.routine_no[0] = *data++;
    ewk->wu.my_family = *data++;
    ewk->wu.my_col_code = *data++;
    ewk->wu.xyz[0].disp.pos = *data++;
    ewk->wu.xyz[1].disp.pos = *data++;
    ewk->wu.my_priority = ewk->wu.position_z = *data++;
    ewk->wu.char_index = *data++;
    ewk->wu.hit_stop = *data++;
    ewk->wu.sync_suzi = *data++;
    suzi_offset_set(&ewk->wu);
    return 0;
}



s32 effect_09_init2(WORK* wk, u8 data) {
    WORK_Other* ewk;
    s16 ix;
    const s16* data_ptr;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.type = data;
    ewk->my_master = (u32*)wk;
    ewk->wu.be_flag = 1;
    ewk->wu.id = 9;
    ewk->wu.work_id = 16;
    ewk->master_id = wk->id;
    ewk->wu.cgromtype = 1;
    *ewk->wu.char_table = etc_char_table;
    ewk->wu.my_col_mode = wk->my_col_mode;
    data_ptr = eff09_data2[ewk->wu.type];
    ewk->wu.routine_no[0] = *data_ptr++;
    ewk->wu.my_col_code = *data_ptr++;
    ewk->wu.my_col_code += wk->my_col_code;
    ewk->wu.my_family = wk->my_family;
    if (data != 4) {
        ewk->wu.rl_flag = wk->rl_flag;
    } else {
        ewk->wu.rl_flag = 0;
    }
    ewk->wu.xyz[0].disp.pos = wk->xyz[0].disp.pos;
    if (wk->rl_flag) {
        ewk->wu.xyz[0].disp.pos -= *data_ptr++;
    } else {
        ewk->wu.xyz[0].disp.pos += *data_ptr++;
    }
    ewk->wu.xyz[1].disp.pos = *data_ptr++;
    ewk->wu.xyz[1].disp.pos += wk->xyz[1].disp.pos;
    ewk->wu.my_priority = wk->my_priority;
    ewk->wu.my_priority += *data_ptr++;
    ewk->wu.position_z = ewk->wu.my_priority;
    ewk->wu.char_index = *data_ptr++;
    ewk->wu.hit_stop = *data_ptr++;
    ewk->wu.sync_suzi = *data_ptr++;
    suzi_offset_set(&ewk->wu);
    return 0;
}
