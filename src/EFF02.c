/*
 * EFF02.C  Effect 02 (hit marks)
 *
 * Effect 02 is the hit mark shown when an attack connects or is guarded. Its entry in the hmdt
 * table chooses the mark (guard and chip variants), colour, direction, position offset, screen
 * quake and hit sound. effect_02_init is called from the hit-check modules (HITCHECK, HITEFEF,
 * HITPLEF, PLPCA). The guard / chip / fsin variant comes from dm_vital bits (0x1F, 0x20; dm_vital
 * is the attack's at_free4), marks move by dir_old with add_pos_dir_016 at an eff02_speed_tbl
 * speed, and there is no direction table.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLS02.h"
#include "EFF02.h"
#include "fighter.h"

/* routine_no[0] */
#define R0_INIT         0       /* pick the mark, sound and colour */
#define R0_MOVE         1       /* animate until the script ends */
#define R0_KILL         2       /* put the work back */

extern const s16 eff02_speed_tbl[];   /* provisional name: hit-mark step speed */



void effect_02_move(WORK_Other* ewk) {
    const HMDT* tad;
    const EXPLEM* edt;
    s32 index;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.char_table[0] = ef01_char_table;
        tad = &hmdt[ewk->wu.kohm];
        if (ewk->wu.vital_old == 2) {
            ewk->wu.kohm = tad->deff;
            if (ewk->wu.dm_vital & 0x1F) {
                ewk->wu.kohm = tad->kezu;
            }
            if (ewk->wu.dm_vital & 0x20) {
                ewk->wu.kohm = tad->fsin;
            }
        }
        tad = &hmdt[ewk->wu.kohm];
        if (tad->hits == 0) {
            if (tad->se) {
                sound_effect_request[tad->se](ewk, tad->se);
            Last_Called_SE = tad->se;
            } else {
                Last_Called_SE = 0;
            }
            push_effect_work(&ewk->wu);
            return;
        }
        if (tad->status & 8) {
            ewk->wu.disp_flag = 2;
        } else {
            ewk->wu.disp_flag = 1;
        }
        if (tad->status & 0x40) {
            if (((PLW*)ewk->wu.target_adrs)->wu.work_id == 1) {
                ewk->wu.dir_timer = ((PLW*)ewk->wu.target_adrs)->player_number;
            } else {
                ewk->wu.dir_timer = ((WORK_Other*)ewk->wu.target_adrs)->master_player;
            }
        }
        if (tad->col) {
            ewk->wu.my_col_code = hcct[tad->col];
        } else if (tad->status & 0x80) {
            ewk->wu.my_col_code = ((PLW*)ewk->wu.target_adrs)->wu.my_col_code + 7;
        }
        if (tad->se) {
            sound_effect_request[tad->se](ewk, tad->se);
            Last_Called_SE = tad->se;
        } else {
            Last_Called_SE = 0;
        }
        if (tad->status & 4) {
            ewk->wu.rl_flag = ewk->wu.dm_rl;
        }
        if (tad->status & 0x10) {
            if (tad->status & 0x20) {
                edt = &explem2[tad->emhix][ewk->wu.dir_timer];
            } else {
                edt = &explem[tad->myhix];
            }
            if (ewk->wu.rl_flag) {
                ewk->wu.xyz[0].disp.pos -= edt->hx;
            } else {
                ewk->wu.xyz[0].disp.pos += edt->hx;
            }
            ewk->wu.xyz[1].disp.pos += edt->hy;
        } else {
            ewk->wu.xyz[0].disp.pos += ewk->wu.old_pos[0];
            ewk->wu.xyz[1].disp.pos += ewk->wu.old_pos[1];
        }
        if (tad->status & 2) {
            ewk->wu.xyz[0].disp.pos += random_16_com() - 7;
            ewk->wu.xyz[1].disp.pos += (random_16_com() & 7) - 3;
        }
        ewk->wu.scr_mv_x = gqdt[tad->quake][GQ_DELAY];
        ewk->wu.scr_mv_y = gqdt[tad->quake][GQ_INDEX];
        ewk->wu.dir_old = tad->dir;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos;
        ewk->wu.position_z = ewk->wu.xyz[2].disp.pos;
        if (tad->status & 0x10) {
            index = edt->chix;
        } else {
            index = tad->hits;
        }
        set_char_move_init(&ewk->wu, 0, index);
        sort_push_request8(&ewk->wu);
        break;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 0xFF) {
                ewk->wu.routine_no[0]++;
                break;
            }
            if (ewk->wu.cg_type != 1 && ewk->wu.dir_old != 4) {
                add_pos_dir_016(&ewk->wu, ewk->wu.dir_step);
            }
            if (ewk->wu.scr_mv_x && --ewk->wu.scr_mv_x == 0) {
                bg_w.quake_y_index = ewk->wu.scr_mv_y;
            }
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos;
        sort_push_request8(&ewk->wu);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_02_init(wk, dmgp, mkst, dmrl)
WORK* wk;
s8 dmgp;
s8 mkst;
s8 dmrl;
{
    WORK_Other* ewk;
    WORK_Other* dwk;
    s16 ix;
    if ((ix = pull_effect_work(2)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 2;
    ewk->wu.work_id = 64;
    ewk->wu.vital_new = dmgp;
    ewk->wu.vital_old = mkst;
    ewk->wu.dm_rl = dmrl;
    ewk->wu.kohm = wk->att.hit_mark;
    ewk->wu.direction = wk->dir_atthit;
    ewk->wu.dir_step = eff02_speed_tbl[wk->kezuri_pow];
    ewk->wu.dm_vital = wk->att.at_free4;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    ewk->wu.my_mr_flag = 0;
    ewk->wu.xyz[0].disp.pos = ewk->wu.position_x = wk->xyz[0].disp.pos;
    ewk->wu.xyz[1].disp.pos = ewk->wu.position_y = wk->xyz[1].disp.pos;
    ewk->wu.xyz[2].disp.pos = 26;
    ewk->wu.old_pos[0] = wk->hit_mark_x - wk->xyz[0].disp.pos;
    ewk->wu.old_pos[1] = wk->hit_mark_y - wk->xyz[1].disp.pos;
    if (wk->work_id == 1) {
        ewk->my_master = (u32*)wk;
        ewk->master_id = wk->id;
        ewk->master_work_id = wk->work_id;
        ewk->wu.target_adrs = wk->target_adrs;
        ewk->wu.my_col_code = wk->my_col_code + 7;
        ewk->master_player = ewk->wu.dir_timer = ((PLW*)wk)->player_number;
    } else {
        dwk = (WORK_Other*)wk;
        ewk->my_master = dwk->my_master;
        ewk->master_id = dwk->master_id;
        ewk->master_work_id = dwk->master_work_id;
        ewk->wu.target_adrs = ((WORK*)dwk->my_master)->target_adrs;
        ewk->wu.my_col_code = ((WORK*)dwk->my_master)->my_col_code + 7;
        ewk->master_player = ewk->wu.dir_timer = dwk->master_player;
    }
    ewk->wu.blink_timing = ewk->master_id;
    return 0;
}
