/*
 * EFF13.C  Effect 13: projectiles (shells)
 *
 * Effect 13 is the projectile work fired by characters. effect_13_move loads its TAMA
 * parameters (life time, attack kind, defence power, colour, kind_of_tama), handles hit
 * results and runs the kind-of-tama process kotp_00000 to kotp_03000; each takes the shell work
 * and its TAMA data record: normal flight and hit handling and special shells such as the
 * tengu stones that attack and return. TAMA records are 24 bytes.
 * Hits reduce the shell's vitality: a light hit spawns an effect 96 flash, enough damage plays
 * the defeat / hit / explode pattern (erdf / erht / erex). Helper routines check screen ranges, aim at the target and relaunch shells.
 * effect_13_init creates a projectile for a player or effect: it registers it as the
 * owner's shell, copies facing, family, colour and weight, and records the owner's
 * player number. Called from the player pattern code (PLPAT09 and others).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLS02.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFF96.h"
#include "effect_2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "HITCHECK.h"
#include "CHARID.h"
#include "PLSGAUGE.h"
#include "PLCNTSET.h"
#include "plcntset_2.h"
#include "EFF13.h"
#include "EFF13_KOTP.h"
#include "fighter.h"

/* routine_no[0], effect_13_move */
#define R0_INIT         0       /* set up from the tama data */
#define R0_MOVE         1       /* run the kind-of-tama process */
#define R0_KILL         2       /* (default) leave the shell list, put back */

/* routine_no[1], kotp_* shell processes */
#define R1_MOVE         0       /* move and animate */
#define R1_HIT          1       /* react to a hit */
#define R1_VANISH       2       /* play the end pattern, then finish */

/* routine_no[2], sub-state of R1_VANISH */
#define R2_DRIFT        0       /* end pattern, still moving */
#define R2_STAY         1       /* end pattern, standing still */

/* routine_no[1], kotp_02000 tengu stones */
#define R1_LEAVE        2       /* fly off the screen, then finish */

/* routine_no[2], kotp_02000 tengu stones */
#define R2_START        0       /* set off toward the home point */
#define R2_APPROACH     1       /* move to the home point */
#define R2_HOME         2       /* hover by the master */
#define R2_ATTACK       3       /* fly at the target */
#define R2_RETURN       4       /* head home after an attack */
#define R2_REBOUND      5       /* bounced off by a hit */



void effect_13_move(WORK_Other* ewk) {
    TAMA* tama = (TAMA*)ewk->wu.my_effadrs;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.charset_id = 11;
        set_char_base_data(&ewk->wu);
        ewk->wu.hf.hit_flag = 0;
        ewk->wu.work_id = tama->my_wkid;
        ewk->wu.dir_timer = tama->life_time;
        ewk->wu.disp_flag = tama->disp_type;
        ewk->wu.blink_timing = ewk->master_id;
        ewk->wu.at_koa = tama->koa;
        ewk->wu.vital_new = tama->def_power;
        ewk->wu.dm_vital = 0;
        ewk->wu.charset_id = tama->kind_of_tama;
        if (ewk->master_id) {
            if (tama->col_2p == 0) {
                ewk->wu.my_col_code = ewk->wu.spr.gfx_cells;
            } else {
                ewk->wu.my_col_code = tcct[tama->col_2p];
            }
        } else if (tama->col_1p == 0) {
            ewk->wu.my_col_code = ewk->wu.spr.gfx_cells;
        } else {
            ewk->wu.my_col_code = tcct[tama->col_1p];
        }
        if (tama->kage_index) {
            ewk->wu.kage_flag = 1;
            ewk->wu.kage_hx = kage_tbl[tama->kage_index][0];
            ewk->wu.kage_hy = kage_tbl[tama->kage_index][1];
            ewk->wu.kage_prio = kage_tbl[tama->kage_index][2];
            ewk->wu.kage_char = kage_tbl[tama->kage_index][3];
        } else {
            ewk->wu.kage_flag = 0;
        }
        if (tama->kind_of_tama == 2) {
            set_tengu_init_pos(ewk, (WORK*)ewk->my_master);
            ewk->wu.disp_flag = 0;
            ewk->wu.dir_old = ((PLW*)ewk->my_master)->sa->id_arts;
            set_char_move_init2(&ewk->wu, 0, tama->chix, random_16_com() & 7, 0);
        } else {
            if (ewk->wu.rl_flag) {
                ewk->wu.xyz[0].disp.pos -= tama->hos_x;
            } else {
                ewk->wu.xyz[0].disp.pos += tama->hos_x;
            }
            ewk->wu.xyz[1].disp.pos += tama->hos_y;
            ewk->wu.position_z = ewk->wu.my_priority;
            setup_mvxy_data(&ewk->wu, tama->data00);
            set_char_move_init(&ewk->wu, 0, tama->chix);
        }
        tama_display(ewk);
        break;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.disp_flag = 0;
            ewk->wu.routine_no[0]++;
            break;
        }
        if (ewk->wu.hit_stop < 0) {
            ewk->wu.hit_stop = -ewk->wu.hit_stop;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            kind_of_tama_process[tama->kind_of_tama](ewk, tama);
        }
        tama_display(ewk);
        hit_push_request(&ewk->wu);
        break;
    case R0_KILL:
    default:
        erase_my_shell_ix((WORK*)ewk->my_master, ewk->wu.myself);
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}


void tama_display(WORK_Other* ewk) {
    set_quake((PLW*)ewk);
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos + ewk->wu.next_x;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos;
    sort_push_request(&ewk->wu);
}



s32 screen_range_check(WORK* wk) {
    s16 scpx = get_center_position();
    s16 scpxr = scpx + 256;
    s16 scpxl = scpx - 256;
    s16 scpy;
    s16 scpyu;
    scpx = wk->xyz[0].disp.pos;
    if (scpxl < 0) {
        scpxr -= scpxl;
        scpx -= scpxl;
        scpxl = 0;
    }
    if (scpx > scpxr || scpx < scpxl) {
        return 1;
    }
    scpy = get_height_position();
    scpyu = scpy + 288;
    scpy = wk->xyz[1].disp.pos;
    if (scpy > scpyu) {
        return 1;
    }
    return 0;
}



void set_tengu_init_pos(WORK_Other* ewk, WORK* twk) {
    s16 scpx;
    scpx = get_center_position();
    if (twk->rl_flag) {
        scpx -= 320;
    } else {
        scpx += 320;
    }
    ewk->wu.xyz[0].disp.pos = scpx;
    ewk->wu.xyz[1].disp.pos = ewk->wu.direction;
}


void kotp_00000(WORK_Other* ewk, TAMA* twk) {
    if (ewk->wu.hf.hit_flag) {
        ewk->wu.routine_no[1] = R1_HIT;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_MOVE:
        if (ewk->wu.hit_stop) {
            ewk->wu.hit_stop--;
            break;
        }
        add_mvxy_speed(&ewk->wu);
        cal_mvxy_speed(&ewk->wu);
        char_move(&ewk->wu);
        if ((ewk->wu.xyz[1].disp.pos + ewk->wu.cg_jphos) <= 0) {
            ewk->wu.mvxy.a[0].sp = 0;
            ewk->wu.mvxy.a[1].sp = 0;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.d[1].sp = 0;
            set_char_move_init(&ewk->wu, 0, twk->erex);
            ewk->wu.routine_no[1] = R1_VANISH;
            ewk->wu.routine_no[2] = R2_STAY;
            ewk->wu.xyz[1].disp.pos = -ewk->wu.cg_jphos;
            break;
        }
        if (--ewk->wu.dir_timer < 0 || screen_range_check(&ewk->wu) != 0) {
            ewk->wu.mvxy.a[0].sp /= 4;
            ewk->wu.mvxy.a[1].sp /= 4;
            set_char_move_init(&ewk->wu, 0, twk->ernm);
            ewk->wu.routine_no[1] = R1_VANISH;
            ewk->wu.routine_no[2] = R2_DRIFT;
        }
        break;
    case R1_HIT:
        ewk->wu.vital_new -= ewk->wu.dm_vital;
        ewk->wu.dm_vital = 0;
        if (ewk->wu.vital_new < 0x100) {
            if (ewk->wu.hf.hit.player) {
                if (ewk->wu.hf.hit.player & 0xF0) {
                    set_char_move_init(&ewk->wu, 0, twk->erdf);
                } else {
                    set_char_move_init(&ewk->wu, 0, twk->erht);
                }
            } else {
                set_char_move_init(&ewk->wu, 0, twk->erex);
            }
            ewk->wu.routine_no[1] = R1_VANISH;
            ewk->wu.routine_no[2] = R2_STAY;
            ewk->wu.kage_flag = 0;
            ewk->wu.hit_stop = 0;
        } else {
            ewk->wu.routine_no[1] = R1_MOVE;
            if (ewk->wu.hf.hit.player) {
                if (ewk->wu.hf.hit.player & 0xF0) {
                    effect_96_init(&ewk->wu, twk->erdf, ewk->wu.disp_flag, ewk->wu.hit_stop);
                } else {
                    effect_96_init(&ewk->wu, twk->erht, ewk->wu.disp_flag, ewk->wu.hit_stop);
                }
            } else {
                effect_96_init(&ewk->wu, twk->erex, ewk->wu.disp_flag, ewk->wu.hit_stop);
            }
        }
        ewk->wu.hf.hit_flag = 0;
        ewk->wu.hit_quake = 0;
        break;
    case R1_VANISH:
        switch (ewk->wu.routine_no[2]) {
        case R2_DRIFT:
            add_mvxy_speed(&ewk->wu);
            cal_mvxy_speed(&ewk->wu);
        case R2_STAY:
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 0xFF) {
                ewk->wu.disp_flag = 0;
                ewk->wu.routine_no[0] = R0_KILL;
            }
            break;
        }
        break;
    }
}


void kotp_01000(WORK_Other* ewk, TAMA* twk) {
    if (ewk->wu.hf.hit_flag) {
        ewk->wu.routine_no[1] = R1_HIT;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_MOVE:
        if (ewk->wu.hit_stop) {
            ewk->wu.hit_stop--;
            break;
        }
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 0xFF) {
            set_char_move_init(&ewk->wu, 0, twk->ernm);
            ewk->wu.routine_no[1] = R1_VANISH;
            ewk->wu.routine_no[2] = R2_DRIFT;
            break;
        }
        if (screen_range_check(&ewk->wu)) {
            ewk->wu.routine_no[0] = R0_KILL;
            ewk->wu.disp_flag = 0;
        }
        break;
    case R1_HIT:
        if (ewk->wu.hf.hit.player) {
            if (ewk->wu.hf.hit.player & 0xF0) {
                set_char_move_init(&ewk->wu, 0, twk->erdf);
            } else {
                set_char_move_init(&ewk->wu, 0, twk->erht);
            }
        } else {
            set_char_move_init(&ewk->wu, 0, twk->erex);
        }
        ewk->wu.routine_no[1] = R1_VANISH;
        ewk->wu.routine_no[2] = R2_DRIFT;
        ewk->wu.hf.hit_flag = 0;
        ewk->wu.hit_quake = 0;
        break;
    case R1_VANISH:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type == 0xFF) {
            ewk->wu.routine_no[0] = R0_KILL;
            ewk->wu.disp_flag = 0;
        }
        break;
    }
}


void kotp_02000(WORK_Other* ewk, TAMA* twk) {
    PLW* mwk = (PLW*)ewk->my_master;
    if (ewk->wu.hf.hit_flag) {
        ewk->wu.routine_no[1] = R1_HIT;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_MOVE:
        if (ewk->wu.hit_stop) {
            ewk->wu.hit_stop--;
            break;
        }
        char_move(&ewk->wu);
        switch (ewk->wu.routine_no[2]) {
        case R2_START:
            ewk->wu.routine_no[2] = R2_APPROACH;
            ewk->wu.disp_flag = 1;
            ewk->wu.dir_timer = twk->data00;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.d[1].sp = -0x7000;
            cal_initial_speed(&ewk->wu,
                              ewk->wu.dir_timer,
                              mwk->wu.xyz[0].disp.pos + ewk->wu.old_pos[0],
                              mwk->wu.xyz[1].disp.pos + ewk->wu.old_pos[1]);
            break;
        case R2_APPROACH:
            add_mvxy_speed_no_use_rl(&ewk->wu);
            cal_mvxy_speed(&ewk->wu);
            if (check_tengu_attack(&ewk->wu, &mwk->wu, twk)) {
                break;
            }
            if (--ewk->wu.dir_timer < 0) {
                ewk->wu.routine_no[2] = R2_HOME;
            }
            break;
        case R2_HOME:
            ewk->wu.position_z = mwk->wu.position_z + ewk->wu.old_pos[2];
            if (mwk->sa->ok != -1 || ewk->wu.dir_old != mwk->sa->id_arts) {
                ewk->wu.routine_no[1] = R1_LEAVE;
                ewk->wu.routine_no[2] = R2_START;
                ewk->wu.cg_hit_ix = 0;
                make_speed_xy_back(&ewk->wu, &mwk->wu, twk);
                break;
            }
            if (check_tengu_attack(&ewk->wu, &mwk->wu, twk)) {
                break;
            }
            set_tengu_my_home(&ewk->wu, &mwk->wu);
            if (ewk->wu.dir_step > 8) {
                ewk->wu.routine_no[2] = R2_APPROACH;
                ewk->wu.dir_timer = 8;
                cal_all_speed_data(&ewk->wu, ewk->wu.dir_timer, ewk->wu.dmcal_m, ewk->wu.dmcal_d, 2, 2);
            }
            break;
        case R2_ATTACK:
            add_mvxy_speed_no_use_rl(&ewk->wu);
            cal_mvxy_speed(&ewk->wu);
            if (--ewk->wu.dir_timer < 0) {
                ewk->wu.routine_no[2] = R2_RETURN;
                ewk->wu.att_hit_ok = 0;
                ewk->wu.dir_timer = twk->hos_x;
                set_tengu_my_home(&ewk->wu, &mwk->wu);
                cal_all_speed_data(&ewk->wu, ewk->wu.dir_timer, ewk->wu.dmcal_m, ewk->wu.dmcal_d, 2, 2);
            }
            break;
        case R2_RETURN:
            add_mvxy_speed_no_use_rl(&ewk->wu);
            cal_mvxy_speed(&ewk->wu);
            ewk->wu.cg_hit_ix = 0;
            if (--ewk->wu.dir_timer < 0) {
                ewk->wu.routine_no[2] = R2_HOME;
            }
            break;
        case R2_REBOUND:
            set_tengu_my_home(&ewk->wu, &mwk->wu);
            ewk->wu.routine_no[2] = R2_RETURN;
            ewk->wu.cg_hit_ix = 0;
            ewk->wu.dir_timer = twk->hos_y;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.d[1].sp = -0x4000;
            cal_initial_speed(&ewk->wu, ewk->wu.dir_timer, ewk->wu.dmcal_m, ewk->wu.dmcal_d);
        }
        break;
    case R1_HIT:
        ewk->wu.routine_no[1] = R1_MOVE;
        ewk->wu.routine_no[2] = R2_REBOUND;
        ewk->wu.hf.hit_flag = 0;
        ewk->wu.cg_hit_ix = 0;
        set_hit_stop_hit_quake(&ewk->wu);
        break;
    case R1_LEAVE:
        add_mvxy_speed_no_use_rl(&ewk->wu);
        cal_mvxy_speed(&ewk->wu);
        if (--ewk->wu.dir_timer < 0) {
            ewk->wu.routine_no[0] = R0_KILL;
            ewk->wu.disp_flag = 0;
        }
        ewk->wu.cg_hit_ix = 0;
        break;
    }
}


void set_tengu_my_home(WORK* ewk, WORK* mwk) {
    if (mwk->pat_status < 32) {
        ewk->dmcal_m = mwk->xyz[0].disp.pos + ewk->old_pos[0];
        ewk->dmcal_d = mwk->xyz[1].disp.pos + ewk->old_pos[1];
    } else {
        ewk->dmcal_m = mwk->xyz[0].disp.pos + ewk->scr_mv_x;
        ewk->dmcal_d = mwk->xyz[1].disp.pos + ewk->scr_mv_y;
    }
    ewk->dir_step = cal_move_quantity2(ewk->xyz[0].disp.pos, ewk->xyz[1].disp.pos, ewk->dmcal_m, ewk->dmcal_d);
}


s32 check_tengu_attack(WORK* ewk, WORK* mwk, TAMA* twk) {
    if (mwk->cg_ja.atix == 0) {
        return 0;
    }
    ewk->routine_no[2] = R2_ATTACK;
    ewk->att_hit_ok = 1;
    ewk->rl_flag = mwk->rl_flag;
    ewk->dir_timer = twk->life_time;
    if (mwk->xyz[1].disp.pos > 0) {
        make_speed_xy_att(ewk, mwk, ewk->dir_timer, 2, 0);
    } else {
        make_speed_xy_att(ewk, mwk, ewk->dir_timer, 0, 2);
    }
    return 1;
}


void make_speed_xy_att(WORK* ewk, WORK* mwk, s16 tm, u8 xsw, u8 ysw) {
    s16 ax;
    s16 ay;
    get_target_att_position(mwk, &ax, &ay);
    cal_all_speed_data(ewk, tm, ax, ay, xsw, ysw);
}


void make_speed_xy_back(WORK* ewk, WORK* mwk, TAMA* twk) {
    s16 bx;
    s16 by;
    ewk->dmcal_m = ewk->xyz[0].disp.pos;
    ewk->dmcal_d = ewk->xyz[1].disp.pos;
    ewk->mvxy.d[0].sp = 0;
    ewk->mvxy.d[1].sp = -0x7000;
    ewk->dir_timer = twk->data01;
    set_tengu_init_pos((WORK_Other*)ewk, mwk);
    bx = ewk->xyz[0].disp.pos;
    by = ewk->xyz[1].disp.pos;
    ewk->xyz[0].disp.pos = ewk->dmcal_m;
    ewk->xyz[1].disp.pos = ewk->dmcal_d;
    cal_initial_speed(ewk, ewk->dir_timer, bx, by);
}


void kotp_03000(WORK_Other* ewk, TAMA* twk) {
    if (ewk->wu.hf.hit_flag) {
        ewk->wu.routine_no[1] = R1_HIT;
    }
    switch (ewk->wu.routine_no[1]) {
    case R1_MOVE:
        if (ewk->wu.hit_stop) {
            ewk->wu.hit_stop--;
            break;
        }
        add_mvxy_speed(&ewk->wu);
        cal_mvxy_speed(&ewk->wu);
        char_move(&ewk->wu);
        if ((ewk->wu.xyz[1].disp.pos + ewk->wu.cg_jphos) <= 0) {
            ewk->wu.mvxy.a[0].sp = 0;
            ewk->wu.mvxy.a[1].sp = 0;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.d[1].sp = 0;
            set_char_move_init(&ewk->wu, 0, twk->ernm);
            ewk->wu.routine_no[1] = R1_VANISH;
            ewk->wu.routine_no[2] = R2_STAY;
            ewk->wu.xyz[1].disp.pos = -ewk->wu.cg_jphos;
            break;
        }
        if (--ewk->wu.dir_timer >= 0 && !screen_range_check(&ewk->wu)) {
            break;
        }
        ewk->wu.disp_flag = 0;
        ewk->wu.routine_no[0] = R0_KILL;
        break;
    case R1_HIT:
        ewk->wu.vital_new -= ewk->wu.dm_vital;
        ewk->wu.hit_stop = 0;
        ewk->wu.hit_quake = 0;
        if (ewk->wu.vital_new < 0x100) {
            if (ewk->wu.hf.hit.player) {
                if (ewk->wu.hf.hit.player & 0xF0) {
                    set_char_move_init(&ewk->wu, 0, twk->erdf);
                } else {
                    set_char_move_init(&ewk->wu, 0, twk->erht);
                    ewk->wu.routine_no[1] = R1_VANISH;
                    ewk->wu.routine_no[2] = R2_STAY;
                    ewk->wu.mvxy.a[0].sp = 0;
                    ewk->wu.mvxy.a[1].sp = 0;
                    ewk->wu.mvxy.d[0].sp = 0;
                    ewk->wu.mvxy.d[1].sp = 0;
                    ewk->wu.hf.hit_flag = 0;
                    ewk->wu.kage_flag = 0;
                    break;
                }
            } else {
                set_char_move_init(&ewk->wu, 0, twk->erex);
            }
            ewk->wu.routine_no[1] = R1_VANISH;
            ewk->wu.routine_no[2] = R2_DRIFT;
            ewk->wu.disp_flag = 2;
            ewk->wu.mvxy.a[0].sp = -ewk->wu.mvxy.a[0].sp;
            ewk->wu.mvxy.a[0].sp /= 3;
            ewk->wu.mvxy.a[1].sp = 0;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.hf.hit_flag = 0;
            ewk->wu.kage_flag = 0;
            break;
        }
        ewk->wu.routine_no[1] = R1_MOVE;
        ewk->wu.hf.hit_flag = 0;
        break;
    case R1_VANISH:
        switch (ewk->wu.routine_no[2]) {
        case R2_DRIFT:
            add_mvxy_speed(&ewk->wu);
            cal_mvxy_speed(&ewk->wu);
        case R2_STAY:
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 0xFF) {
                ewk->wu.disp_flag = 0;
                ewk->wu.routine_no[0] = R0_KILL;
            }
            break;
        }
        break;
    }
}



s32 effect_13_init(wk, data)
WORK* wk;
u8 data;
{
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    write_my_shell_ix(wk, ix);
    if (wk->work_id == 1 && wk->rl_flag == 1 && ((PLW*)wk)->player_number == PL_GILL) {
        data++;
    }
    ewk->wu.be_flag = 1;
    ewk->wu.id = 13;
    ewk->wu.type = data;
    ewk->wu.operator = wk->operator;
    ewk->wu.rl_flag = wk->rl_flag;
    ewk->wu.my_family = wk->my_family;
    ewk->wu.cgromtype = wk->cgromtype;
    ewk->wu.my_col_mode = wk->my_col_mode;
    ewk->wu.spr.gfx_cells = wk->my_col_code;
    ewk->wu.weight_level = wk->weight_level;
    ewk->my_master = (u32*)wk;
    if (wk->work_id == 1) {
        ewk->master_player = ((PLW*)wk)->player_number;
        ewk->master_id = wk->id;
        ewk->master_work_id = wk->work_id;
    } else {
        ewk->master_player = ((WORK_Other*)wk)->master_player;
        ewk->master_id = ((WORK_Other*)wk)->master_id;
        ewk->master_work_id = ((WORK_Other*)wk)->master_work_id;
    }
    ewk->wu.xyz[0] = wk->xyz[0];
    ewk->wu.xyz[1] = wk->xyz[1];
    ewk->wu.my_effadrs = (u32*)&tama_data[data];
    return 0;
}
