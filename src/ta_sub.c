/*
 * ta_sub.c  Stage object helpers
 *
 * Shared routines for the stage background tasks and their objects. sync_fam_set / sync_fam_set2 /
 * sync_fam_set3 set a plane's family position from its BG position. range_x_check decides whether an
 * object is on screen (272 dots each side of the view), and the disp_pos_trans_entry_* and
 * pl_eff_trans_entry_* families turn an object's position into screen coordinates and draw it only
 * when it is visible. The add_x_sub / add_y_sub movers apply the acceleration before the speed.
 * eff_hit_check and eff_hit_check_sub test each player against an object's hit box and count contacts
 * in eff_hit_flag (type 5 objects are skipped). Small state checks used by stage objects:
 * complete_victory_check, get_winner_player_number / get_winner_id, either_pl_hissatsu_check (a
 * player is doing a special move), compel_dead_check, pl_shot_on_check / pl_shot_trg_check (a button
 * is down or pressed) and range_abs_check; cal_bg_speed_data* work out a layer's speeds.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "fifo.h"
#include "aboutspr.h"
#include "HITCHECK.h"
#include "ta_sub.h"
#include "bg000.h"
#include "PLS02.h"
#include "ta_sub2.h"
#include "tate00.h"

#pragma inline(obr_no_disp_check)


void sw_dummy_2(void) {}


void sw_dummy_1(void) {}


void bg_frame_deff_init(void);

void sync_fam_set(s16 num_of_bg) {
    s32 x;
    s32 y;
    bg_frame_deff_init();
    bg_pos_hosei_sub3(num_of_bg);
    x = bg_w.bgw[num_of_bg].position_x;
    y = bg_w.bgw[num_of_bg].position_y;
    x = -x & 0x3FF;
    y = (0x300 - (y & 0x3FF)) & 0x3FF;
    Family_Set_W(num_of_bg + 1, x, y);
}


void sync_fam_set2(s16 num_of_bg) {
    s32 x;
    s32 y;
    bg_frame_deff_init();
    bg_pos_hosei_sub2(num_of_bg);
    x = bg_w.bgw[num_of_bg].position_x;
    y = bg_w.bgw[num_of_bg].position_y;
    x = -x & 0x3FF;
    y += 12;
    y = (0x300 - (y & 0x3FF)) & 0x3FF;
    Family_Set_W(num_of_bg + 1, x, y);
}


void sync_fam_set3(bg_no)
s16 bg_no;
{
    s16 pos_work_x;
    s16 pos_work_y;
    s16 pos_x_w;
    s16 pos_y_w;
    if (bg_w.chase_flag & 0xF) {
        pos_x_w = bg_w.bgw[bg_no].chase_xy[0].disp.pos;
    } else {
        pos_x_w = bg_w.bgw[bg_no].xy[0].disp.pos;
    }
    if (bg_w.chase_flag & 0xF0) {
        pos_y_w = bg_w.bgw[bg_no].chase_xy[1].disp.pos;
    } else {
        pos_y_w = bg_w.bgw[bg_no].xy[1].disp.pos;
    }
    pos_work_x = pos_x_w & 0x3FF;
    pos_work_x -= bg_w.pos_offset;
    pos_x_w -= bg_w.pos_offset;
    pos_work_x &= 0x3FF;
    if (bg_w.quake_x_index > 0) {
        pos_work_x += quake_x_tbl[bg_w.quake_x_index];
        pos_x_w += quake_x_tbl[bg_w.quake_x_index];
    }
    bg_w.bgw[bg_no].position_x = pos_work_x & 0x3FF;
    bg_w.bgw[bg_no].abs_x = pos_x_w;
    pos_work_y = pos_y_w & 0x3FF;
    pos_work_y += quake_y_tbl[bg_w.quake_y_index];
    pos_y_w += quake_y_tbl[bg_w.quake_y_index];
    bg_w.bgw[bg_no].position_y = pos_work_y & 0x3FF;
    bg_w.bgw[bg_no].abs_y = pos_y_w;
    pos_work_x = -pos_work_x & 0x3FF;
    pos_work_y = (0x300 - (pos_work_y & 0x3FF)) & 0x3FF;
    ((void (*)(s32 plane, s16 x, s16 y))Family_Set_W)(bg_no + 1, pos_work_x, pos_work_y);
}


s32 range_x_check(WORK* wk) {
    s16 x;
    if ((s8)bg_w.chase_flag & 0xF) {
        x = bg_w.bgw[wk->my_family - 1].chase_xy[0].disp.pos;
    } else {
        x = bg_w.bgw[wk->my_family - 1].wxy[0].disp.pos;
    }
    x -= 272;
    if (x > wk->xyz[0].disp.pos) {
        return 0;
    }
    x = bg_w.bgw[wk->my_family - 1].wxy[0].disp.pos + 272;
    if (wk->xyz[0].disp.pos > x) {
        return 0;
    }
    return 1;
}


void add_x_sub(WORK_Other* ewk) {
    ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp;
    ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
}


void add_x_sub2(WORK_Other* ewk) {
    ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp;
    ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
}


void add_x_sub_flip(WORK_Other* ewk) {
    if (ewk->wu.rl_flag) {
        ewk->wu.mvxy.a[0].sp -= ewk->wu.mvxy.d[0].sp;
        ewk->wu.xyz[0].cal -= ewk->wu.mvxy.a[0].sp;
    } else {
        ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp;
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
    }
}


void add_y_sub(WORK_Other* ewk) {
    ewk->wu.mvxy.a[1].sp += ewk->wu.mvxy.d[1].sp;
    ewk->wu.xyz[1].cal += ewk->wu.mvxy.a[1].sp;
}


void add_y_sub2(WORK_Other* ewk) {
    ewk->wu.mvxy.a[1].sp += ewk->wu.mvxy.d[1].sp;
    ewk->wu.xyz[1].cal += ewk->wu.mvxy.a[1].sp;
}


s32 obr_no_disp_check(void) {
    if (seraph_flag | akebono_flag | sa_pa_flag) {
        return 1;
    }
    return 0;
}


void disp_pos_trans_entry(WORK_Other* ewk) {
    if (obr_no_disp_check()) {
        return;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}


void disp_pos_trans_entry5(WORK_Other* ewk) {
    if (obr_no_disp_check()) {
        return;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}


void disp_pos_trans_entry_r(WORK_Other* ewk) {
    if (obr_no_disp_check() == 0) {
        if (range_x_check((WORK*)ewk) != 0) {
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            sort_push_request4(&ewk->wu);
        }
    }
}


void disp_pos_trans_entry_s(WORK_Other* ewk) {
    if (obr_no_disp_check() == 0) {
        suzi_sync_pos_set(ewk);
        sort_push_request4(&ewk->wu);
    }
}


void disp_pos_trans_entry_rs(WORK_Other* ewk) {
    if (obr_no_disp_check() == 0) {
        if (range_x_check((WORK*)ewk) != 0) {
            suzi_sync_pos_set(ewk);
            sort_push_request4(&ewk->wu);
        }
    }
}


void pl_eff_trans_entry(WORK_Other* ewk) {
    if (obr_no_disp_check() == 0) {
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        sort_push_request(&ewk->wu);
    }
}


void pl_eff_trans_entry_r(WORK_Other* ewk) {
    if (obr_no_disp_check() == 0) {
        if (range_x_check((WORK*)ewk) != 0) {
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            sort_push_request(&ewk->wu);
        }
    }
}


/* Accumulates this effect's hits on the players; returns its hit count. */
s32 eff_hit_check(WORK_Other* ewk, s16 type) {
    if (ewk->wu.type == 5) {
        return 0;
    }
    if (type) {
        if (pcon_dp_flag) {
            eff_hit_flag[ewk->wu.type] += eff_hit_check_sub(ewk, &plw[0]);
            eff_hit_flag[ewk->wu.type] += eff_hit_check_sub(ewk, &plw[1]);
        }
    } else {
        eff_hit_flag[ewk->wu.type] += eff_hit_check_sub(ewk, &plw[0]);
        eff_hit_flag[ewk->wu.type] += eff_hit_check_sub(ewk, &plw[1]);
    }
    return eff_hit_flag[ewk->wu.type];
}


s32 eff_hit_check_sub(WORK_Other* ewk, PLW* pl) {
    if (pl->wu.routine_no[1] == PLAYER_DAMAGE) {
        if (pl->wu.routine_no[2] < DAMAGE_AIR || pl->wu.routine_no[2] >= DAMAGE_AIR_END) {
            return 0;
        }
        if (hit_check_subroutine(
                &pl->wu, &ewk->wu, &pl_hit_eff[pl->player_number][0], &eff_hit_data[ewk->wu.type][0])) {
            return 1;
        }
    }
    return 0;
}


void eff_hit_flag_clear(void) {
    s16 i;
    s16* ptr;
    ptr = &eff_hit_flag[0];
    for (i = 0; i < 0xB; i++) {
        *ptr++ = 0;
    }
}


s32 complete_victory_check(void) {
    if (!Allow_a_battle_f && Conclusion_Flag == 1 && C_No0 >= C0_FIGHT && Complete_Victory) {
        return 1;
    }
    return 0;
}


s16 get_winner_player_number(void) {
    return plw[Winner_id].player_number;
}


s8 get_winner_id(void) {
    return Winner_id;
}


u32 range_abs_check(s16 a, s16 b, s16 range)
{
    s16 dist;
    dist = a - b;
    if (dist < 0) {
        dist = -dist;
    }
    if (dist < range) {
        return 1;
    }
    return 0;
}


s32 either_pl_hissatsu_check(void) {
    if (plw[0].wu.routine_no[1] == PLAYER_ATTACK && plw[0].wu.routine_no[2] >= ATTACK_SPECIAL) {
        return 1;
    }
    if (plw[1].wu.routine_no[1] == PLAYER_ATTACK && plw[1].wu.routine_no[2] >= ATTACK_SPECIAL) {
        return 1;
    }
    return 0;
}


s32 compel_dead_check(WORK_Other* ewk) {
    if (bg_w.compel_on && ewk->wu.dead_f) {
        return 1;
    }
    return 0;
}


s32 pl_shot_on_check(pl)
s16 pl;
{
    if (pl) {
        if (p2sw_0 & 0x7F0) {
            return 1;
        }
        return 0;
    }
    if (p1sw_0 & 0x7F0) {
        return 1;
    }
    return 0;
}

/* Chase speeds and win/lose pose state. */


/* a loop over the players */
void win_lose_work_clear(void) {
    s16 i;
    a_rno = 0;
    lose_rno[2] = 0;
    for (i = 0; i < 2; i++) {
        win_rno[i] = 0;
        win_free[i] = 0;
        lose_rno[i] = 0;
        lose_free[i] = 0;
    }
}


#pragma inline(bg_speed_disp)
static void bg_speed_disp(s8 r1, s8 r2, s8 stage, s8 area) {}

static void chase_xy_disp(s32 cal, s16 pos, s16 low) {}

void cal_bg_speed_data(bg_num, tm)
s16 bg_num;
s16 tm;
{
    MotionState ms;
    XY* xy = bg_w.bgw[bg_num].chase_xy;
    bg_speed_disp(bg_w.bg_r_1, bg_w.bg_r_2, bg_w.stage, bg_w.area);
    if (0) {
        return;
    }
    chase_xy_disp(xy->cal, xy->disp.pos, xy->disp.low);
    xy[0].disp.low = xy[1].disp.low = 0;
    (void)&((WORK*)bg_num)->be_flag;
    ms.timer = tm;
    ms.timer2 = (((ms.timer - 1) * ms.timer) / 2) + ms.timer;
    ms.x.ps.h = chase_x - bg_w.bgw[bg_num].chase_xy[0].disp.pos;
    ms.y.ps.h = chase_y - bg_w.bgw[bg_num].chase_xy[1].disp.pos;
    ms.y.ps.l = 0;
    ms.x.ps.l = 0;
    if (!ms.timer) {
        ms.amy = 0;
        ms.amx = 0;
        ms.spy = ms.dly = 0;
        ms.dlx = 0;
        ms.spx = 0;
    } else {
        ms.amx = ms.x.pl % ms.timer2;
        ms.spx = ms.dlx = ms.x.pl / ms.timer2;
        ms.amy = ms.y.pl % ms.timer2;
        ms.spy = ms.dly = ms.y.pl / ms.timer2;
    }
    bg_mvxy.a[0].sp = ms.spx;
    bg_mvxy.d[0].sp = ms.dlx;
    bg_mvxy.a[1].sp = ms.spy;
    bg_mvxy.d[1].sp = ms.dly;
    bg_w.bgw[bg_num].chase_xy[0].cal += ms.amx;
    bg_w.bgw[bg_num].chase_xy[1].cal += ms.amy;
    bg_mvxy.kop[0] = bg_mvxy.kop[1] = 0;
}


void cal_bg_speed_data_x(bg_num, tm, dummy)
s16 bg_num;
s16 tm;
s16 dummy;
{
    MotionState ms;
    bg_w.bgw[bg_num].chase_xy[0].disp.low = 0;
    ms.timer = tm;
    ms.timer2 = (ms.timer - 1) * ms.timer / 2 + ms.timer;
    ms.x.ps.h = chase_x - bg_w.bgw[bg_num].chase_xy[0].disp.pos;
    ms.x.ps.l = 0;
    if (!ms.timer) {
        ms.amx = 0;
        ms.dlx = 0;
        ms.spx = 0;
    } else {
        ms.amx = ms.x.pl % ms.timer2;
        ms.spx = ms.dlx = ms.x.pl / ms.timer2;
    }
    bg_mvxy.a[0].sp = ms.spx;
    bg_mvxy.d[0].sp = ms.dlx;
    bg_w.bgw[bg_num].chase_xy[0].cal += ms.amx;
    bg_mvxy.kop[0] = 0;
}


void cal_bg_speed_data_y(bg_num, tm, dummy)
s16 bg_num;
s16 tm;
s16 dummy;
{
    MotionState ms;
    bg_w.bgw[bg_num].chase_xy[1].disp.low = 0;
    ms.timer = tm;
    ms.timer2 = (ms.timer - 1) * ms.timer / 2 + ms.timer;
    ms.y.ps.h = chase_y - bg_w.bgw[bg_num].chase_xy[1].disp.pos;
    ms.y.ps.l = 0;
    if (!ms.timer) {
        ms.amy = 0;
        ms.dly = 0;
        ms.spy = 0;
    } else {
        ms.amy = ms.y.pl % ms.timer2;
        ms.spy = ms.dly = ms.y.pl / ms.timer2;
    }
    bg_mvxy.a[1].sp = ms.spy;
    bg_mvxy.d[1].sp = ms.dly;
    bg_w.bgw[bg_num].chase_xy[1].cal += ms.amy;
    bg_mvxy.kop[1] = 0;
}


s32 pl_shot_trg_check(void) {
    u16 sw;
    if (plw[0].wu.operator) {
        sw = ~p1sw_1 & p1sw_0;
        if (sw & 0x7F0) return 1;
    }
    if (plw[1].wu.operator) {
        sw = ~p2sw_1 & p2sw_0;
        if (sw & 0x7F0) return 1;
    }
    return 0;
}


