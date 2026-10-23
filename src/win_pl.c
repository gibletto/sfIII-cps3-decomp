/*
 * win_pl.c  Round winner poses
 *
 * Seven character pose routines select victory animations, movement and voice requests.
 * Judged rounds and stage actions take precedence over the ordinary winning pose.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFM7.h"
#include "PLS02.h"
#include "ta_sub.h"
#include "charmove_2.h"
#include "EFF30.h"
#include "EFF31.h"
#include "EFF32.h"
#include "EFF82.h"
#include "EFF83.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "lose_pl.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "aboutspr.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "SYS_sub.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "sc_trans.h"
#include "fifo.h"
#include "eff36.h"
#include "EFF48.h"
#include "EFFC1.h"
#include "efff6.h"
#include "end_main.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "Com_Pl.h"
#include "win_pl.h"
#include "fighter.h"

#pragma inline(win_select)

s16 win_rno[2];  /* 0201D6C0 */
s16 a_rno;  /* 0201D6C4 */
s16 win_free[2];  /* 0201D6C6 */

void char_move(WORK* wk);
void char_move_z(WORK* wk);
void set_char_move_init();
void set_char_move_init2();

void win_player(PLW* wk) {

    void (*win_jp_tbl[7])(PLW*) = { Win_00000, Win_01000, Win_02000, Win_03000, Win_04000, Win_05000, Win_06000 };
    win_jp_tbl[win_type_tbl[wk->player_number]](wk);
}

/* Win pose type 0: the standard winning pose. */
void Win_00000(PLW* wk) {
    if (pcon_rno[0] == 2 && pcon_rno[1] == 3) {
        Judge_normal_winner(wk);
    } else {
        Normal_normal_Winner(wk);
    }
}

void Win_01000(PLW* wk) {
    s16 work;
    bg_stop = 1;
    if (win_special_check(wk)) {
        return;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        a_rno = win_rno[0] = win_rno[1] = 0;
        wk->wu.routine_no[3]++;

        if (bg_w.stage == 9) {
            if ((Round_num >= Game_setting.set4 * 2) || (PL_Wins[wk->wu.id] >= Game_setting.set4 + 1)) {
                set_char_move_init(&wk->wu, 9, 41);
                win_rno[0] = 1;
                break;
            } else {
            }
        }
        work = win_select(wk, 7);
        set_char_move_init(&wk->wu, 9, work + 32);
        if (work == 4) {
            win_rno[0] = 2;
        }
        break;
    case 1:
    case 9:
        switch (win_rno[0]) {
        case 0:
            char_move(&wk->wu);
            break;
        case 1:
            jijii_fly_up(wk);
            break;
        case 2:
            jijii_jump(wk);
            break;
        }
        break;
    }
}

void jijii_fly_up(PLW* wk) {
    bg_stop = 1;
    switch (win_rno[1]) {
    case 0:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            win_rno[1]++;
            char_move_z(&wk->wu);
            wk->wu.mvxy.a[1].sp = 0xF0000;
            wk->wu.mvxy.d[1].sp = -0x600;
        }
        break;
    case 1:
        if (wk->wu.cg_type != 2) {
            char_move(&wk->wu);
        }
        add_y_sub((WORK_Other*)wk);
        if (wk->wu.xyz[1].disp.pos > 256) {
            win_rno[1]++;
            win_sp_flag = 2;
            set_char_move_init(&wk->wu, 9, 40);
            wk->wu.xyz[1].disp.pos = 200;
        }
        break;
    case 2:
        char_move(&wk->wu);
        break;
    }
}

void jijii_jump(PLW* wk) {
    s16 id_w;
    bg_stop = 1;
    id_w = wk->wu.id ^ 1;
    wk->wu.position_z = plw[id_w].wu.position_z - 1;
    wk->wu.my_priority = wk->wu.position_z;
    switch (win_rno[1]) {
    case 0:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 9) {
            win_rno[1]++;
            if (wk->wu.rl_flag) {
                wk->wu.mvxy.a[0].sp = 0x60000;
                wk->wu.mvxy.d[0].sp = 0x1000;
            } else {
                wk->wu.mvxy.a[0].sp = -0x60000;
                wk->wu.mvxy.d[0].sp = -0x1000;
            }
            wk->wu.mvxy.a[1].sp = 0xA0000;
            wk->wu.mvxy.d[1].sp = -0x600;
        }
        break;
    case 1:
        if (wk->wu.cg_type != 99) {
            char_move(&wk->wu);
        }
        add_x_sub((WORK_Other*)wk);
        add_y_sub((WORK_Other*)wk);
        if (wk->wu.rl_flag) {
            if (wk->wu.xyz[0].disp.pos > bg_w.bgw[1].xy[0].disp.pos + 320) {
                win_rno[1]++;
                effect_work_kill(3, 13);
            }
            break;
        }
        if (wk->wu.xyz[0].disp.pos < bg_w.bgw[1].xy[0].disp.pos - 320) {
            win_rno[1]++;
            effect_work_kill(3, 13);
        }
        break;
    case 2:
        win_rno[1]++;
        set_char_move_init2(&wk->wu, 9, 36, 7, 0);
        win_free[wk->wu.id] = 48;
        break;
    case 3:
        win_free[wk->wu.id]--;
        if (win_free[wk->wu.id] > 0) {
            break;
        }
        win_rno[1]++;
        if (wk->wu.rl_flag) {
            wk->wu.xyz[0].disp.pos = bg_w.bgw[1].xy[0].disp.pos - 328;
            wk->wu.mvxy.a[0].sp = 0x18000;
        } else {
            wk->wu.xyz[0].disp.pos = bg_w.bgw[1].xy[0].disp.pos + 328;
            wk->wu.mvxy.a[0].sp = -0x18000;
        }
        wk->wu.mvxy.d[0].sp = 0;
        wk->wu.xyz[1].cal = 0;
    case 4:
        add_x_sub((WORK_Other*)wk);
        char_move(&wk->wu);
        break;
    }
}

void Win_02000(PLW* wk) {
    bg_stop = 1;
    if (win_special_check(wk)) {
        return;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        a_rno = win_rno[0] = win_rno[1] = 0;
        if ((Round_num >= Game_setting.set4 * 2) || (PL_Wins[wk->wu.id] >= Game_setting.set4 + 1)) {
            if (win_2000_tbl[bg_w.bg_index]) {
                wk->wu.routine_no[3]++;
                set_char_move_init(&wk->wu, 9, 40);
                break;
            }
        }
    default:
        Normal_normal_Winner(wk);
        break;
    }
}

void Win_03000(PLW* wk) {
    s16 work;
    bg_stop = 1;
    if (win_special_check(wk)) {
        return;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        a_rno = win_rno[0] = win_rno[1] = 0;
        work = win_select(wk, 3);
        if ((Round_num >= Game_setting.set4 * 2) || (PL_Wins[wk->wu.id] >= Game_setting.set4 + 1)) {
            set_char_move_init(&wk->wu, 9, Win_3001_tbl[work]);
        } else {
            set_char_move_init(&wk->wu, 9, Win_3000_tbl[work]);
        }
        break;
    default:
        char_move(&wk->wu);
        break;
    }
}

void Win_04000(PLW* wk) {
    s16 work;
    bg_stop = 1;
    if (win_special_check(wk)) {
        return;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        a_rno = win_rno[0] = win_rno[1] = 0;
        if ((Round_num >= Game_setting.set4 * 2) || (PL_Wins[wk->wu.id] >= Game_setting.set4 + 1)) {
            set_char_move_init(&wk->wu, 9, 36);
            break;
        }
        exset_char_move_init(&wk->wu, 9, 32);
        if (Demo_Sound != 0 || Demo_Flag != 0) {
            work = win_select(wk, 3);
            work = Check_Voice_SE(Win_4000_voice_tbl[work]);
            sound_request_pan(work, 64, 64, 0, 2);
        }
        break;
    default:
    case 1:
        char_move(&wk->wu);
        break;
    }
}

void Normal_normal_Winner(PLW* wk) {
    s16 work;
    bg_stop = 1;
    if (bg_w.stage == 8 && bg_w.area == 0 && Game_setting.set4 > 0) {
        win_stage8_action(wk);
        return;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        work = win_select(wk, 7);
        set_char_move_init(&wk->wu, 9, work + 32);
        break;
    case 1:
    case 9:
        char_move(&wk->wu);
        break;
    }
}

void Judge_normal_winner(PLW* wk) {
    s16 work;
    bg_stop = 1;
    if (bg_w.stage == 8 && bg_w.area == 0 && Game_setting.set4 > 0) {
        win_stage8_action(wk);
        return;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        a_rno = win_rno[0] = win_rno[1] = 0;
        wk->wu.routine_no[3]++;
        work = win_select(wk, 3);
        set_char_move_init(&wk->wu, 9, work + 52);
        break;
    case 1:
    case 9:
        char_move(&wk->wu);
        break;
    }
}

s32 win_special_check(PLW* wk) {
    if (pcon_rno[0] == 2 && pcon_rno[1] == 3) {
        Judge_normal_winner(wk);
        return 1;
    }
    if (bg_w.stage == 8 && bg_w.area == 0 && Game_setting.set4 > 0) {
        win_stage8_action(wk);
        return 1;
    }
    return 0;
}

void Win_05000(PLW* wk) {
    s16 work;
    if (win_special_check(wk)) {
        return;
    }
    bg_stop = 0;
    switch (wk->wu.routine_no[3]) {
    case 0:
        a_rno = win_rno[0] = win_rno[1] = 0;
        wk->wu.routine_no[3]++;
        if ((Round_num >= Game_setting.set4 * 2) || (PL_Wins[wk->wu.id] >= Game_setting.set4 + 1)) {
            set_char_move_init(&wk->wu, 9, 36);
            if (wk->wu.rl_flag) {
                wk->wu.mvxy.a[0].sp = 0x20000;
            } else {
                wk->wu.mvxy.a[0].sp = -0x20000;
            }
            wk->wu.mvxy.d[0].sp = 0;
            wk->wu.mvxy.a[1].sp = 0x80000;
            wk->wu.mvxy.d[1].sp = -0x6000;
            win_rno[0] = 0;
            break;
        }
        work = win_select(wk, 3);
        set_char_move_init(&wk->wu, 9, work + 32);
        win_rno[0] = 1;
        break;
    default:
        if (win_rno[0]) {
            Normal_normal_Winner(wk);
            break;
        } else {
            switch (win_rno[1]) {
            case 0:
                if (0) {
                }
                goto win_fall_move;
            win_fall_move:;
                char_move(&wk->wu);
                add_x_sub((WORK_Other*)wk);
                add_y_sub((WORK_Other*)wk);
                if (wk->wu.xyz[1].disp.pos < 0) {
                    win_rno[1]++;
                    wk->wu.xyz[1].cal = 0;
                    char_move_z(&wk->wu);
                }
                break;
            case 1:
                char_move(&wk->wu);
                break;
            }
        }
    }
}

void Win_06000(PLW* wk) {
    s16 work;
    bg_stop = 1;
    if (win_special_check(wk)) {
        return;
    }
    switch (wk->wu.routine_no[3]) {
    case 0:
        a_rno = win_rno[0] = win_rno[1] = 0;
        wk->wu.routine_no[3]++;
        if ((Round_num >= Game_setting.set4 * 2) || (PL_Wins[wk->wu.id] >= Game_setting.set4 + 1)) {
            work = win_select(wk, 3);
            set_char_move_init(&wk->wu, 9, work + 36);
        } else {
            work = win_select(wk, 3);
            set_char_move_init(&wk->wu, 9, work + 32);
        }
        break;
    default:
        Normal_normal_Winner(wk);
        break;
    }
}

void win_stage8_action(PLW* wk) {
    bg_stop = 1;
    switch (wk->wu.routine_no[3]) {
    case 0:
        complete_victory_pause();
        wk->wu.routine_no[3]++;
        exset_char_move_init(&wk->wu, 9, 60);
        a_rno = 0;
        break;
    case 1:
    case 9:
        switch (a_rno) {
        case 0:
            if (bg_w.bgw[1].r_no_1 >= 1) {
                a_rno++;
                set_char_move_init(&wk->wu, 9, 61);
                wk->wu.mvxy.a[1].sp = 0x68000;
                wk->wu.mvxy.d[1].sp = -0x4000;
                win_free[wk->wu.id] = 110;
            } else {
                char_move(&wk->wu);
            }
            break;
        case 1:
            if (pl_shot_on_check(wk->wu.id)) {
                C_Timer--;
            }
            win_free[wk->wu.id]--;
            if (win_free[wk->wu.id] < 0) {
                wk->wu.routine_no[3]++;
            } else {
                add_y_sub((WORK_Other*)wk);
            }
            /* fall through */
        case 2:
            char_move(&wk->wu);
            wk->wu.kage_flag = 0;
            break;
        }
        break;
    }
}

s32 win_select(PLW* wk, s16 num) {
    s16 work = random_16_com();
    work &= num;
    return work;
}

