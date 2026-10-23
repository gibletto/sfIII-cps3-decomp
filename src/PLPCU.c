/*
 * PLPCU.C  Player caught (being thrown) process
 *
 * Runs a player who is held by the opponent's throw. Player_caught clears the state flags and
 * dispatches Caught_00000-Caught_03000: the victim follows the thrower's catch rectangle (index,
 * flip, offset, priority) each frame, or moves the thrower relative to itself for the second
 * catch kind. check_tsukamare_keizoku_check decides whether the hold continues.
 * caught_cg_type_check and the scdmd_12000-scdmd_28000 routines set up the damage state the
 * victim is released into (blow-away data, vertical speed from buttobi_time_table);
 * scdmd_26000 also sets the horizontal speed from move_power, as Damage_26000 does.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "CALDIR.h"
#include "EFFA7.h"
#include "effa8.h"
#include "effa9.h"
#include "EFFD9.h"
#include "PLS02.h"
#include "EFFE2.h"
#include "PLPCU.h"

void Player_caught(PLW* wk) {
    PLW* emwk = (PLW*)wk->wu.dmg_adrs;
    wk->wu.next_z = wk->wu.my_priority;
    wk->running_f = 0;
    wk->guard_flag = 3;
    wk->guard_chuu = 0;
    wk->tsukami_f = 0;
    wk->tsukamare_f = 1;
    wk->scr_pos_set_flag = 0;
    wk->dm_hos_flag = 0;
    wk->zuru_timer = 0;
    wk->zuru_ix_counter = 0;
    wk->sa_stop_flag = 0;
    wk->atemi_flag = 0;
    wk->caution_flag = 0;
    wk->sa->saeff_ok = 0;
    wk->cancel_timer = 0;
    if (wk->wu.routine_no[3] == 0) {
        wk->ukemi_ok_timer = wk->backup_ok_timer = emwk->wu.cmyd.koc;
        wk->uot_cd_ok_flag = 0;
        wk->ukemi_success = 0;
        wk->wu.dir_old = 1;
    }
    plpcu_lv_00[wk->wu.routine_no[2]](wk, emwk);
}



void Caught_00000(PLW* wk) {}



void Caught_01000(PLW* wk, PLW* emwk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init(&wk->wu, 3, emwk->wu.cmyd.ix);
        wk->wu.cmwk[11] = 0;
    case 1:
        if (check_tsukamare_keizoku_check(wk, emwk) != 0) {
            break;
        }
        if (emwk->wu.curr_rca == 0) {
            break;
        }
        if (emwk->wu.curr_rca->catch_nix == wk->wu.dir_old) {
            char_move(&wk->wu);
        } else {
            char_move_index(&wk->wu, emwk->wu.curr_rca->catch_nix);
            wk->wu.dir_old = emwk->wu.curr_rca->catch_nix;
        }
        wk->wu.rl_flag = emwk->wu.rl_flag ^ emwk->wu.curr_rca->catch_flip;
        if (emwk->wu.rl_flag) {
            wk->wu.xyz[0].disp.pos = emwk->wu.xyz[0].disp.pos - emwk->wu.curr_rca->catch_hos_x;
        } else {
            wk->wu.xyz[0].disp.pos = emwk->wu.xyz[0].disp.pos + emwk->wu.curr_rca->catch_hos_x;
        }
        wk->wu.xyz[1].disp.pos = emwk->wu.xyz[1].disp.pos + emwk->wu.curr_rca->catch_hos_y;
        if (emwk->wu.curr_rca->catch_prio == 2) {
            wk->wu.next_z = emwk->wu.next_z - 1;
        } else {
            wk->wu.next_z = emwk->wu.next_z + 1;
        }
        caught_cg_type_check(wk, emwk);
    }
}



void Caught_02000(PLW* wk, PLW* emwk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        set_char_move_init(&wk->wu, 3, emwk->wu.cmyd.ix);
        wk->wu.cmwk[11] = 0;
    case 1:
        if (check_tsukamare_keizoku_check(wk, emwk) != 0) {
            break;
        }
        if (emwk->wu.curr_rca == 0) {
            break;
        }
        if (emwk->wu.curr_rca->catch_nix == wk->wu.dir_old) {
            char_move(&wk->wu);
        } else {
            char_move_index(&wk->wu, emwk->wu.curr_rca->catch_nix);
            wk->wu.dir_old = emwk->wu.curr_rca->catch_nix;
        }
        wk->wu.rl_flag = emwk->wu.rl_flag ^ emwk->wu.curr_rca->catch_flip;
        if (emwk->wu.rl_flag) {
            emwk->wu.xyz[0].disp.pos = wk->wu.xyz[0].disp.pos + emwk->wu.curr_rca->catch_hos_x;
        } else {
            emwk->wu.xyz[0].disp.pos = wk->wu.xyz[0].disp.pos - emwk->wu.curr_rca->catch_hos_x;
        }
        emwk->wu.xyz[1].disp.pos = wk->wu.xyz[1].disp.pos - emwk->wu.curr_rca->catch_hos_y;
        if (emwk->wu.curr_rca->catch_prio == 2) {
            wk->wu.next_z = emwk->wu.next_z - 1;
        } else {
            wk->wu.next_z = emwk->wu.next_z + 1;
        }
        caught_cg_type_check(wk, emwk);
    }
}



void Caught_03000(PLW* wk) {}


/* provisional name */
void Caught_04000(PLW* wk) {}


/* provisional name */
void Caught_05000(PLW* wk) {}


/* provisional name */
void Caught_06000(PLW* wk) {}


/* provisional name */
void Caught_07000(PLW* wk) {}


/* provisional name */
void Caught_08000(PLW* wk) {}



void caught_cg_type_check(PLW* wk, PLW* emwk) {
    switch (wk->wu.cg_type) {
    case 2:
        wk->wu.hit_quake = wk->wu.dm_quake;
        wk->wu.dm_quake = 0;
        wk->wu.cg_type = 0;
        break;
    case 3:
        effect_A7_init(wk);
        wk->wu.cg_type = 0;
        break;
    case 9:
        if (wk->dead_flag == 0) {
            char_move_z((WORK*)wk);
        } else {
            char_move_cmms((WORK*)wk);
        }
        wk->wu.routine_no[1] = wk->wu.cmmd.koc;
        wk->wu.routine_no[2] = wk->wu.cmmd.ix;
        wk->wu.routine_no[3] = wk->wu.cmmd.pat;
        switch (wk->wu.now_koc) {
        case 1:
            if (caught_dm_chg_tbl1[wk->wu.char_index][0]) {
                wk->wu.char_index = caught_dm_chg_tbl1[wk->wu.char_index][1] + wk->wu.dm_attlv;
                exset_char_move_init(&wk->wu, 1, wk->wu.char_index);
            }
            break;
        case 6:
            if (caught_dm_chg_tbl6[wk->wu.char_index][0]) {
                wk->wu.char_index = caught_dm_chg_tbl6[wk->wu.char_index][1] + wk->wu.dm_attlv;
                exset_char_move_init(&wk->wu, 6, wk->wu.char_index);
            }
            break;
        }
        wk->dm_ix = wk->wu.char_index;
        if (wk->wu.xyz[1].disp.pos < 0) {
            wk->wu.xyz[1].cal = 0;
        }
        setup_cu_dm_init_data[wk->wu.routine_no[2] - 12](wk);
        get_catch_off_data(wk, emwk->wu.att.reaction);
        if (wk->ukemi_success == 0) {
            wk->ukemi_ok_timer = wk->backup_ok_timer;
            wk->uot_cd_ok_flag = 0;
        }
        break;
    }
}



s32 check_tsukamare_keizoku_check(PLW* wk, PLW* emwk) {
    if (emwk->tsukami_f == 0) {
        wk->wu.routine_no[1] = 1;
        wk->wu.routine_no[2] = 88;
        wk->wu.routine_no[3] = 0;
        wk->wu.dm_stop = wk->wu.hit_stop = 0;
        return 1;
    }
    return 0;
}



void scdmd_12000(PLW* wk) {
    wk->dm_step_tbl = dm_step_data[select_hit_dsd[wk->wu.dm_impact][get_weight_point(&wk->wu)]];
    wk->wu.cmwk[14] = damage_pause_table[0][wk->wu.dm_attlv];
}



void scdmd_14000(PLW* wk) {
    setup_butt_own_data(&wk->wu);
    wk->wu.mvxy.a[1].sp = wk->wu.mvxy.d[1].sp = wk->wu.mvxy.kop[1] = 0;
}



void scdmd_16000(PLW* wk) {
    setup_butt_own_data(&wk->wu);
    cal_initial_speed_y(&wk->wu, buttobi_time_table[wk->dm_ix], 0);
}



void scdmd_17000(PLW* wk) {
    if (wk->wu.dm_butt_type) {
        setup_butt_own_data(&wk->wu);
    } else {
        setup_butt_own_data_ex(&wk->wu, 0);
    }
    cal_initial_speed_y(&wk->wu, buttobi_time_table[wk->dm_ix], wk->wu.xyz[1].disp.pos);
}



void scdmd_18000(PLW* wk) {
    if (wk->wu.dm_butt_type) {
        setup_butt_own_data(&wk->wu);
    } else {
        setup_butt_own_data_ex(&wk->wu, 0);
    }
    cal_initial_speed_y(&wk->wu, buttobi_time_table[wk->dm_ix], wk->wu.xyz[1].disp.pos);
}



void scdmd_19000(PLW* wk) {
    if (wk->wu.dm_butt_type) {
        setup_butt_own_data(&wk->wu);
    } else {
        setup_butt_own_data_ex(&wk->wu, 0);
    }
    cal_initial_speed_y(&wk->wu, buttobi_time_table[wk->dm_ix], 0);
}



void scdmd_20000(void) { setup_butt_own_data(); }



void scdmd_21000(PLW* wk) {
    setup_butt_own_data(&wk->wu);
    wk->wu.mvxy.a[1].sp = wk->wu.mvxy.d[1].sp = wk->wu.mvxy.kop[1] = 0;
}



void scdmd_23000(WORK* wk) {
    if (wk->xyz[1].disp.pos < 0) {
        wk->xyz[1].cal = 0;
    }
    setup_butt_own_data(wk);
}


void scdmd_24000(PLW* wk) {
    wk->wu.routine_no[2] = 0;
    wk->wu.routine_no[3] = 1;
}



void scdmd_25000(PLW* wk) {}



void scdmd_26000(PLW* wk) {
    if (wk->wu.dm_butt_type) {
        setup_butt_own_data(&wk->wu);
    } else {
        setup_butt_own_data_ex(&wk->wu, 0);
    }
    cal_initial_speed_y(&wk->wu, buttobi_time_table[wk->dm_ix], 0);
    *(s16*)&wk->wu.mvxy.a[0] = wk->move_power;
    wk->wu.mvxy.a[0].real.l = 0;
    wk->wu.mvxy.a[0].sp *= 3;
    wk->wu.mvxy.a[0].sp /= 4;
    wk->wu.mvxy.d[0].sp = 0;
    if (*(s16*)&wk->wu.mvxy.a[0] > 4) {
        *(s16*)&wk->wu.mvxy.a[0] = 4;
    }
    if (*(s16*)&wk->wu.mvxy.a[0] < 1) {
        *(s16*)&wk->wu.mvxy.a[0] = 1;
    }
}


void scdmd_27000(PLW* wk) {
    setup_butt_own_data(&wk->wu);
    wk->wu.mvxy.a[1].sp = wk->wu.mvxy.d[1].sp = wk->wu.mvxy.kop[1] = 0;
}



void scdmd_28000(PLW* wk) {
    if (wk->wu.dm_butt_type) {
        setup_butt_own_data(&wk->wu);
    } else {
        setup_butt_own_data_ex(&wk->wu, 0);
    }
    cal_initial_speed_y(&wk->wu, buttobi_time_table[wk->dm_ix], wk->wu.xyz[1].disp.pos);
}

