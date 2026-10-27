/*
 * EFFD4.C  Effect D4: suction pull of an attack
 *
 * effect_D4_init creates the effect at its master's position (not in bonus stages), taking its
 * facing, pull direction and duration from sel_suikomi_tbl, and spawns two G3 effects.
 * While the master stays in its attack state (routine_no[1] == 4) and the timer runs,
 * effect_D4_move moves the opponent toward (or, with dmcal_m == -1, away from) the master each
 * frame; the speed is looked up by x/y distance in swallow_areas_x / _y (distance2speed) and
 * swallow_speeds. In push mode it also moves the opponent's live shells. It can be limited to
 * one side of the master and stops during a super-art freeze.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFG3.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFD4.h"

/* routine_no[0] */
#define R0_INIT         0       /* start pulling */
#define R0_MOVE         1       /* pull while the attack lasts */
#define R0_KILL         2       /* put the work back */



void effect_D4_move(WORK_Other* ewk) {
    PLW* wk = (PLW*)ewk->wu.target_adrs;
    PLW* mwk = (PLW*)ewk->my_master;
    WORK* swk;
    s32 rl;
    s32 add_x;
    s32 add_y;
    s32 i;
    s32 j;
    ewk->wu.position_x = mwk->wu.position_x;
    ewk->wu.position_y = mwk->wu.position_y;
    ewk->wu.position_z = mwk->wu.position_z;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (mwk->wu.routine_no[1] != PLAYER_ATTACK) {
            ewk->wu.dir_timer = 0;
            ewk->wu.routine_no[0]++;
            break;
        }
        ewk->wu.dir_timer -= 1;
        if (ewk->wu.dir_timer <= 0) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag != 0 || Game_pause != 0) {
            break;
        }
        if (ewk->wu.xyz[0].cal < wk->wu.xyz[0].cal) {
            rl = 1;
        } else {
            rl = 0;
        }
        if ((ewk->wu.dmcal_d || mwk->sa_stop_flag) &&
            (!ewk->wu.dmcal_d || rl != ewk->wu.rl_flag || mwk->sa_stop_flag)) {
            return;
        }
        i = distance2speed(ewk, &wk->wu, 0);
        ewk->wu.mvxy.a[0].sp = swallow_speeds[i];
        ewk->wu.mvxy.d[0].sp = 0;
        i = distance2speed(ewk, &wk->wu, 1);
        ewk->wu.mvxy.a[1].sp = swallow_speeds[i];
        ewk->wu.mvxy.d[1].sp = 0;
        ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp;
        ewk->wu.mvxy.a[1].sp += ewk->wu.mvxy.d[1].sp;
        add_x = ewk->wu.mvxy.a[0].sp;
        add_y = -ewk->wu.mvxy.a[1].sp;
        if (ewk->wu.dmcal_m == -1) {
            add_x = -add_x;
            add_y = -add_y;
        }
        if (rl) {
            wk->wu.xyz[0].cal -= add_x;
        } else {
            wk->wu.xyz[0].cal += add_x;
        }
        wk->wu.xyz[1].cal += add_y;
        if (ewk->wu.dmcal_m != -1) {
            break;
        }
        for (j = 0; j < 8; j++) {
            if (wk->wu.shell_ix[j] == -1) {
                continue;
            }
            swk = (WORK*)frw[wk->wu.shell_ix[j]];
            if (!swk->be_flag) {
                continue;
            }
            if (ewk->wu.xyz[0].cal < swk->xyz[0].cal) {
                rl = 1;
            } else {
                rl = 0;
            }
            i = distance2speed(ewk, swk, 0);
            ewk->wu.mvxy.a[0].sp = swallow_speeds[i];
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp;
            add_x = -ewk->wu.mvxy.a[0].sp;
            if (rl) {
                swk->xyz[0].cal -= add_x;
            } else {
                swk->xyz[0].cal += add_x;
            }
        }
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 distance2speed(WORK_Other* ewk, WORK* wk, s32 dir) {
    register s32 x, y;

    x = y = 0;
    if (ewk->wu.xyz[0].disp.pos < wk->xyz[0].disp.pos) {
        x = wk->xyz[0].disp.pos - ewk->wu.xyz[0].disp.pos;
    } else if (ewk->wu.xyz[0].disp.pos > wk->xyz[0].disp.pos) {
        x = ewk->wu.xyz[0].disp.pos - wk->xyz[0].disp.pos;
    }
    if (x >= 512) {
        x = 511;
    }
    x >>= 4;
    if (ewk->wu.xyz[1].disp.pos < wk->xyz[1].disp.pos) {
        y = wk->xyz[1].disp.pos - ewk->wu.xyz[1].disp.pos;
    }
    if (y >= 192) {
        y = 191;
    }
    y >>= 4;
    if (!dir) {
        return swallow_areas_x[y][x];
    }
    return swallow_areas_y[y][x];
}



s32 effect_D4_init(WORK* wk, u8 data) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 134;
    ewk->wu.work_id = 16;
    ewk->wu.type = data;
    ewk->wu.my_family = wk->my_family;
    ewk->wu.cgromtype = wk->cgromtype;
    ewk->wu.my_col_mode = wk->my_col_mode;
    ewk->wu.my_col_code = wk->my_col_code;
    ewk->my_master = (u32*)wk;
    ewk->master_work_id = wk->work_id;
    ewk->master_id = wk->id;
    ewk->wu.target_adrs = wk->target_adrs;
    ewk->wu.xyz[0].disp.pos = wk->position_x;
    ewk->wu.xyz[1].disp.pos = wk->position_y;
    ewk->wu.xyz[2].disp.pos = wk->position_z;
    ewk->wu.position_x = wk->position_x;
    ewk->wu.position_y = wk->position_y;
    ewk->wu.position_z = wk->position_z;
    ewk->wu.rl_flag = wk->rl_flag + sel_suikomi_tbl[data][1] & 1;
    ewk->wu.dmcal_d = sel_suikomi_tbl[data][2];
    ewk->wu.dmcal_m = sel_suikomi_tbl[data][3];
    ewk->wu.dir_timer = sel_suikomi_tbl[data][4];
    effect_G3_init(&ewk->wu, 0);
    effect_G3_init(&ewk->wu, 1);
    return 0;
}
