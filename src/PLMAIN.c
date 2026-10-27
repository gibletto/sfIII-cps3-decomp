/*
 * PLMAIN.C  Player move routine for a fight
 *
 * Player_move (called from player control) is the per-frame routine of a player work. It takes
 * the lever and buttons from the operator or the CPU (CPU_Sub), saves the previous state, runs
 * the command check (waza_check) and dispatches on routine_no[0]:
 * player_mv_0000 initialises the player (vitality, shadow, stun, super-art state), player_mv_1000
 * runs the entry, player_mv_2000 waits for the entry pose, and player_mv_4000 runs the game
 * routines with lever checks, hit stop (check_hit_stop, select_hit_stop) and timers
 * (look_after_timers, which also runs the super-art gauge process).
 * The super-art gauge processes sag_normal, sag_timer and sag_rebirth handle stock, timed and
 * rebirth type arts.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Pl.h"
#include "PLS01.h"
#include "PLPNM.h"
#include "appear.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "PLS00.h"
#include "PLCNTDAT.h"
#include "EFFECT.h"
#include "bg_sub.h"
#include "cmd_main_2.h"
#include "PLSGAUGE.h"
#include "EFFG3.h"
#include "fighter.h"
#include "PLMAIN.h"

/* sa->sa_rno: the super art stock (sag_normal, sag_timer, sag_rebirth) */
#define SA_NONE         0       /* no stock */
#define SA_READY        1       /* a stock is ready (ok) */
#define SA_USED         2       /* the art was started: spend the stock once it takes */
#define SA_TIMER_WAIT   3       /* sag_timer: it took, wait out the freeze */
#define SA_TIMER_RUN    4       /* sag_timer: the gauge runs down */
#define SA_REBIRTH      3       /* sag_rebirth: it took */

void Player_move(PLW* wk, u16 lv_data) {
    s16 i;
    if (wk->wu.operator) {
        wk->cp->sw_lvbt = lv_data;
    } else if (wk->sa_stop_flag != 1) {
        wk->cp->sw_lvbt = CPU_Sub(wk);
    } else {
        wk->cp->sw_lvbt = 0;
    }
    if (wk->dead_flag) {
        wk->cp->sw_lvbt = 0;
    }
    if (wk->wkey_flag) {
        wk->cp->sw_lvbt = 0;
    }
    for (i = 0; i < 8; i++) {
        wk->wu.old_rno[i] = wk->wu.routine_no[i];
    }
    for (i = 0; i < 3; i++) {
        wk->wu.old_pos[i] = wk->wu.xyz[i].disp.pos;
    }
    get_saikinnno_idouryou(wk);
    wk->old_gdflag = wk->guard_flag;
    wk->wu.renew_attack = 0;
    wk->wu.vital_old = wk->wu.vital_new;
    set_rl_waza(wk);
    if (wk->sa_stop_flag != 1) {
        waza_check(wk);
    }
    wk->wu.cmwk[10] = wk->cp->lgp;
    wk->wu.cmwk[11] += wk->cp->lgp;
    wk->wu.cmwk[11] &= 0x7FFF;
    wk->wu.cmwk[12] = wk->cp->sw_new;
    wk->wu.cmwk[13] = wk->cp->sw_now;
    plmain_lv_00[wk->wu.routine_no[0]](wk);
}



void player_mv_0000(PLW* wk) {
    s16 i;
    s32 k;
    for (i = 0, k = 0; i < 8; i++, k += 2) {
        *(s16*)((s32)wk->old_pos_data + k) = 0;
    }
    setup_vitality(&wk->wu, (wk->player_number));
    set_player_shadow(wk);
    wk->bullet_hcnt = wk->bhcnt_timer = 0;
    wk->wu.hit_stop = wk->wu.dm_stop = 0;
    wk->wu.hit_quake = wk->wu.dm_quake = 0;
    wk->tsukamarenai_flag = 0;
    wk->zuru_timer = 0;
    wk->zuru_flag = 0;
    wk->tsukami_f = wk->tsukamare_f = 0;
    clear_kizetsu_point(wk);
    wk->ukemi_ok_timer = 0;
    wk->uot_cd_ok_flag = 0;
    wk->ukemi_success = 0;
    clear_my_shell_ix(&wk->wu);
    wk->sa->sa_rno = 0;
    wk->sa->ok = 0;
    wk->dm_hos_flag = 0;
    wk->kezurijini_flag = 0;
    wk->wu.extra_col = wk->wu.extra_col_2 = 0;
    wk->sa_stop_flag = 0;
    wk->wu.routine_no[0] = PLAYER_MV_PLACE;
    if (wk->player_number == PL_ELENA) {
        effect_G1_init(wk);
    }
}



void player_mv_1000(PLW* wk) {
    APPEAR_DATA* dtbl;
    s16 ap_work;
    switch (appear_type) {
    case APPEAR_STAND:
        plmv_1010(wk);
        plmv_1020(wk, 0x60);
        Appear_end++;
        break;
    case APPEAR_JUDGE:
        plmv_1010(wk);
        plmv_1020(wk, 0x80);
        break;
    case APPEAR_ENTRY:
    case APPEAR_ROUND:
        wk->wu.routine_no[0] = PLAYER_MV_APPEAR;
        wk->wu.routine_no[1] = PLAYER_NORMAL;
        wk->wu.routine_no[2] = NORMAL_APPEAR;
        wk->wu.routine_no[3] = RN3_START;
        wk->wu.disp_flag = 1;
        Appear_hv[wk->wu.id] = home_visitor_check(wk);
        if (Appear_hv[wk->wu.id]) {
            ap_work = appear_type_hv_tbl[wk->player_number][bg_w.stage][bg_w.area];
        } else {
            ap_work = appear_type_tbl[wk->player_number][bg_w.stage][bg_w.area];
        }
        dtbl = &appear_data[ap_work];
        appear_data_set(wk, dtbl);
        break;
    }
    Player_normal(wk);
}


void plmv_1010(PLW* wk) {
    wk->wu.routine_no[0] = PLAYER_MV_READY;
    wk->wu.routine_no[1] = PLAYER_NORMAL;
    wk->wu.routine_no[2] = NORMAL_STAND;
    wk->wu.routine_no[3] = RN3_START;
    wk->wu.disp_flag = 1;
}



void plmv_1020(PLW* wk, s16 step) {
    if (wk->wu.id) {
        wk->wu.rl_flag = 0;
        wk->wu.xyz[0].disp.pos = step + get_center_position();
        wk->wu.xyz[1].disp.pos = 0;
    } else {
        wk->wu.rl_flag = 1;
        wk->wu.xyz[0].disp.pos = get_center_position() - step;
        wk->wu.xyz[1].disp.pos = 0;
    }
}



void player_mv_2000(PLW* wk) {
    if (wk->wu.routine_no[2] == NORMAL_STAND) {
        wk->wu.routine_no[0] = PLAYER_MV_READY;
        wk->wu.disp_flag = 1;
        wk->wu.cg_type = 0;
    }
    Player_normal(wk);
}



void player_mv_3000(PLW* wk) {
    Player_normal(wk);
}



void player_mv_4000(PLW* wk) {
    wk->permited_koa = 0;
    check_lever_data(wk);
    if (wk->tsukamare_f) {
        wk->wu.hit_stop = wk->wu.dm_stop = 0;
    }
    if (check_hit_stop(wk) != 0) {
    } else {
        plmain_lv_02[wk->wu.routine_no[1]](wk);
        if (Timer_Freeze == 0) {
            if (wk->zuru_timer > 0) {
                wk->zuru_timer -= 2;
            }
        }
        if (wk->zuru_timer < 0) {
            wk->zuru_flag = 1;
        } else {
            wk->zuru_flag = 0;
        }
    }
    if (Timer_Freeze == 0) {
        look_after_timers(wk);
    }
}



s32 check_hit_stop(PLW* wk) {
    WORK* emwk = (WORK*)wk->wu.target_adrs;
    s16 num = 0;
    if (wk->wu.dm_stop != 0 && wk->wu.hit_stop != 0) {
        if (wk->wu.routine_no[3] != RN3_START) {
            wk->wu.hit_stop = select_hit_stop(wk->wu.hit_stop, wk->wu.dm_stop);
            wk->wu.dm_stop = 0;
        } else {
            wk->wu.dm_stop = select_hit_stop(wk->wu.dm_stop, wk->wu.hit_stop);
            wk->wu.hit_stop = 0;
            return 0;
        }
    }
    if (wk->wu.hit_stop) {
        num = 1;
        if (wk->wu.hit_stop > 0) {
            if (wk->sa_stop_flag == 2 && wk->wu.hit_stop == 44) {
                wk->sa_stop_lvdir = wk->cp->sw_lvbt;
                wk->sa_stop_flag = 1;
            }
            wk->wu.hit_stop--;
        } else {
            wk->wu.hit_stop++;
            char_move(&wk->wu);
        }
        if (wk->wu.routine_no[3] == RN3_START) {
            if (wk->wu.routine_no[1] == 1 || wk->wu.routine_no[1] == 3) {
                if (emwk->routine_no[1] != 1 && emwk->routine_no[1] != 3) {
                    num = 0;
                }
            }
        }
    }
    Timer_Freeze = 0;
    if (wk->sa_stop_flag) {
        Timer_Freeze = 1;
    }
    return num;
}



s32 select_hit_stop(s16 ms, s16 sb) {
    s8 maf = 0;
    if (ms < 0) {
        ms = -ms;
        maf = 1;
    }
    if (sb < 0) {
        sb = -sb;
    }
    if (ms < sb) {
        ms = sb;
    }
    if (maf) {
        ms = -ms;
    }
    return ms;
}



void look_after_timers(PLW* wk) {
    if (wk->tsukamarenai_flag) {
        wk->tsukamarenai_flag--;
    }
    if (wk->uot_cd_ok_flag) {
        wk->ukemi_ok_timer--;
        if (wk->ukemi_ok_timer <= 0) {
            wk->ukemi_ok_timer = 0;
            wk->uot_cd_ok_flag = 0;
            wk->ukemi_success = 0;
        } else if (check_ukemi_flag(wk)) {
            wk->ukemi_ok_timer = 0;
            wk->uot_cd_ok_flag = 0;
            wk->ukemi_success = 1;
        }
    }
    if (wk->bullet_hcnt) {
        if (--wk->bhcnt_timer <= 0) {
            wk->bullet_hcnt = 0;
        }
    }
    if (wk->py->now.quantity.h) {
        wk->py->now.timer -= wk->py->recover;
        if (wk->py->now.quantity.h <= 0) {
            wk->py->now.timer = 0;
        }
    }
    sag_jmp_tbl[wk->sa->gauge_type](wk);
    if (exsw_0 & 0x8000) {
        wk->cp->waza_flag[wk->sa->nmsa_g_ix] = 9;
    }
}



void demo_set_sa_full(SA_WORK* sa) {
    switch (sa->gauge_type) {
    case SA_GAUGE_STOCK:
        sa->sa_rno = SA_READY;
        sa->ok = 1;
        sa->store = sa->store_max;
        sa->id_arts++;
        break;
    case SA_GAUGE_TIMER:
        sa->sa_rno = SA_READY;
        sa->ok = 1;
        sa->store = sa->store_max;
        sa->id_arts++;
        break;
    case SA_GAUGE_STOCK2:
        break;
    case SA_GAUGE_REBIRTH:
        sa->sa_rno = SA_READY;
        sa->ok = 1;
        sa->store = sa->store_max;
        break;
    }
}



/* provisional name */
void sag_normal(PLW* wk) {
    switch (wk->sa->sa_rno) {
    case SA_NONE:
        if (wk->sa->store) {
            wk->sa->sa_rno = SA_READY;
            wk->sa->ok = 1;
            wk->sa->id_arts++;
        }
        wk->sa->saeff_ok = 0;
        break;
    case SA_READY:
        if (wk->sa->ok == -1) {
            wk->sa->sa_rno = SA_USED;
            wk->sa->saeff_ok = 1;
            sa_gauge_flash[wk->wu.id] = 1;
        }
        break;
    case SA_USED:
        switch (wk->sa->saeff_ok) {
        case -1:
            if (pcon_dp_flag == 0) {
                wk->sa->store--;
            }
            wk->sa->saeff_ok = 0;
            wk->sa->sa_rno = SA_NONE;
            wk->sa->ok = 0;
            break;
        case 1:
            if (wk->wu.routine_no[1] == PLAYER_ATTACK) {
                break;
            }
        default:
            wk->sa->saeff_ok = 0;
            wk->sa->sa_rno = SA_NONE;
            wk->sa->ok = 0;
            break;
        }
        break;
    default:
        wk->sa->sa_rno = SA_NONE;
        wk->sa->ok = 0;
        wk->sa->store = 0;
        wk->sa->saeff_ok = 0;
        break;
    }
}



/* provisional name */
void sag_timer(PLW* wk) {
    switch (wk->sa->sa_rno) {
    case SA_NONE:
        if (wk->sa->store) {
            wk->sa->sa_rno = SA_READY;
            wk->sa->ok = 1;
            wk->sa->id_arts++;
        }
        wk->sa->saeff_ok = 0;
        break;
    case SA_READY:
        if (wk->sa->ok == -1) {
            wk->sa->sa_rno = SA_USED;
            wk->sa->saeff_ok = 1;
            sa_gauge_flash[wk->wu.id] = 1;
        }
        break;
    case SA_USED:
        switch (wk->sa->saeff_ok) {
        case -1:
            if (pcon_dp_flag == 0) {
                wk->sa->store--;
            }
            wk->sa->gauge.s.h = wk->sa->gauge_len;
            wk->sa->gauge.s.l = -1;
            wk->sa->sa_rno = SA_TIMER_WAIT;
            wk->sa->saeff_ok = 0;
            break;
        case 1:
            if (wk->wu.routine_no[1] == PLAYER_ATTACK) {
                break;
            }
        default:
            wk->sa->saeff_ok = 0;
            wk->sa->sa_rno = SA_NONE;
            wk->sa->ok = 0;
            break;
        }
        break;
    case SA_TIMER_WAIT:
        wk->sa->gauge.i -= wk->sa->dtm;
        if (wk->sa->gauge.s.h < 1) {
            wk->sa->gauge.i = 0;
            wk->sa->ok = 0;
            wk->sa->sa_rno = SA_NONE;
        }
        break;
    default:
        wk->sa->sa_rno = SA_NONE;
        wk->sa->ok = 0;
        wk->sa->store = 0;
        break;
    }
}


/* provisional name */
void sag_timer_dummy(void) {}



/* provisional name */
void sag_rebirth(PLW* wk) {
    switch (wk->sa->sa_rno) {
    case SA_NONE:
        if (wk->sa->store) {
            wk->sa->sa_rno = SA_READY;
            wk->sa->ok = 1;
        }
        wk->sa->saeff_ok = 0;
        break;
    case SA_READY:
        if (wk->sa->ok == -1) {
            wk->sa->sa_rno = SA_USED;
            wk->sa->saeff_ok = 1;
            sa_gauge_flash[wk->wu.id] = 1;
        }
        break;
    case SA_USED:
        switch (wk->sa->saeff_ok) {
        case -1:
            wk->sa->store--;
            wk->sa->gauge.i = 0;
            wk->sa->saeff_ok = 0;
            wk->sa->sa_rno = SA_REBIRTH;
            break;
        case 1:
            return;
        default:
            wk->sa->saeff_ok = 0;
            wk->sa->sa_rno = SA_NONE;
            wk->sa->ok = 0;
            break;
        }
        break;
    case SA_REBIRTH:
        return;
    default:
        wk->sa->sa_rno = SA_NONE;
        wk->sa->ok = 0;
        wk->sa->store = 0;
        wk->sa->saeff_ok = 0;
        break;
    }
}



void get_saikinnno_idouryou(PLW* wk) {
    s16 i;
    for (i = 0; i < 7; i++) {
        wk->old_pos_data[i] = wk->old_pos_data[i + 1];
    }
    wk->old_pos_data[i] = wk->wu.xyz[0].disp.pos;
    wk->move_distance = wk->old_pos_data[7] - wk->old_pos_data[0];
    wk->move_power = cal_move_quantity2(wk->old_pos_data[0], 0, wk->old_pos_data[7], 0);
    wk->move_power >>= 3;
}
