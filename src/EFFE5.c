/*
 * EFFE5.C  Effect E5: after-image controller for a player
 *
 * effect_E5_init (from plcntset_2.c) creates one controller per player and stores it in
 * illusion_work. When the player's move sets image_setup_flag and image_data_index
 * (setup_after_images; erase_after_images clears them), effect_E5_move loads the after-image settings
 * from after_image_data (setup_illusion_data) and then either starts an E7 trail image every few
 * frames or a burst of E8 images at once. Flag bits end the after-images on a timer, when the
 * player's or the opponent's move or state changes, or when the super art ends.
 * effect_e7_e8_init_union and get_attdata_of_illusion set up the E7 / E8 images, with a copy of the
 * player's attack for images that can hit.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFE7.h"
#include "EFFE8.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "HITCHECK.h"
#include "EFFE5.h"



void effect_E5_move(WORK_Other* ewk) {
    PLW* mwk = (PLW*)ewk->my_master;
    s16 i;
    s32 rno;
    s16* er;
    s16* mr;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        switch (ewk->wu.routine_no[1]) {
        case 0:
            if (mwk->image_setup_flag ) {
                ewk->wu.routine_no[1]++;
            }
            break;
        case 1:
            setup_illusion_data(ewk, mwk);
            if (ewk->wu.old_rno[2]) {
                ewk->wu.routine_no[1] = 1;
            } else {
                ewk->wu.routine_no[1] = 0;
            }
            ewk->wu.routine_no[0] = 1;
            ewk->wu.routine_no[2] = 0;
            break;
        }
        break;
    case 1:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            mwk->image_setup_flag = 0;
            break;
        }
        if (ewk->wu.dir_old & 1) {
            if (--ewk->wu.direction == 0) {
                goto off;
            }
        }
        if (ewk->wu.dir_old & 2) {
            er = ewk->wu.routine_no;
            if (er[5] != (mr = mwk->wu.routine_no)[1] || er[6] != mr[2]) {
                goto off;
            }
        }
        if (ewk->wu.dir_old & 4 && mwk->sa->ok != -1) {
            goto off;
        }
        if (ewk->wu.dir_old & 8) {
            rno = ((WORK*)mwk->wu.target_adrs)->routine_no[1];
            if (rno != 4 && rno != 2) {
                goto off;
            }
        }
        if (ewk->wu.dir_old & 0x10) {
            rno = mwk->wu.routine_no[1];
            if (rno != 4 && rno != 2) {
                goto off;
            }
        }
        if (ewk->wu.dir_old & 0x20 && ewk->wu.total_att_set != ((WORK*)mwk->wu.target_adrs)->kind_of_waza) {
            goto off;
        }
        if (ewk->wu.dir_old & 0x40 && ewk->wu.total_paring != mwk->wu.kind_of_waza) {
            goto off;
        }
        if (!mwk->image_setup_flag) {
        off:
            ewk->wu.routine_no[0] = ewk->wu.routine_no[1] = ewk->wu.routine_no[2] = 0;
            mwk->image_setup_flag = 0;
            break;
        }
        switch (ewk->wu.routine_no[1]) {
        case 0:
            if (mwk->image_setup_flag == 0) {
                ewk->wu.routine_no[0] = 0;
                ewk->wu.routine_no[1] = 0;
                break;
            }
            switch (ewk->wu.routine_no[2]) {
            case 0:
                ewk->wu.routine_no[2]++;
                effect_E7_init(ewk, mwk);
            case 1:
                ewk->wu.routine_no[2]++;
                ewk->wu.dir_step = ewk->wu.dmcal_m;
            case 2:
                if (EXE_flag == 0 && Game_pause == 0 && --ewk->wu.dir_step <= 0) {
                    effect_E7_init(ewk, mwk);
                    ewk->wu.routine_no[2] = 1;
                }
                break;
            }
            break;
        case 1:
            if (mwk->image_setup_flag == 0) {
                ewk->wu.routine_no[0] = 0;
                ewk->wu.routine_no[1] = 0;
                break;
            }
            switch (ewk->wu.routine_no[2]) {
            case 0:
                ewk->wu.routine_no[2]++;
                ewk->wu.dir_step = 0;
                for (i = 0; i < ewk->wu.dmcal_d; i++) {
                    ewk->wu.dir_step += ewk->wu.dmcal_m;
                    effect_E8_init(ewk, mwk, ewk->wu.dir_step);
                }
                break;
            }
            break;
        }
        break;
    default:
    case 2:
        push_effect_work(&ewk->wu);
        break;
    }
}



void setup_illusion_data(WORK_Other* ewk, PLW* mwk) {
    const u16* tblh = after_image_data[mwk->image_data_index];
    if (tblh[0] & 0x10) {
        ewk->wu.disp_flag = 1;
    } else {
        ewk->wu.disp_flag = 2;
    }
    ewk->wu.old_rno[3] = tblh[0] & 8;
    ewk->wu.old_rno[2] = tblh[0] & 4;
    ewk->wu.old_rno[1] = tblh[0] & 2;
    ewk->wu.old_rno[0] = tblh[0] & 1;
    ewk->wu.old_rno[4] = tblh[1];
    ewk->wu.dmcal_m = tblh[2];
    ewk->wu.dmcal_d = tblh[3];
    ewk->wu.direction = tblh[4];
    ewk->wu.dir_old = tblh[5];
    ewk->wu.routine_no[5] = mwk->wu.routine_no[1];
    ewk->wu.routine_no[6] = mwk->wu.routine_no[2];
    ewk->wu.total_paring = mwk->wu.kind_of_waza;
    ewk->wu.total_att_set = ((WORK*)mwk->wu.target_adrs)->kind_of_waza;
}



s32 effect_E5_init(PLW* wk) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    wk->illusion_work = &ewk->wu;
    ewk->wu.be_flag = 1;
    ewk->wu.id = 145;
    ewk->wu.work_id = 16;
    ewk->wu.my_family = wk->wu.my_family;
    ewk->wu.cgromtype = wk->wu.cgromtype;
    ewk->wu.my_col_mode = wk->wu.my_col_mode;
    ewk->wu.my_col_code = wk->wu.my_col_code;
    ewk->my_master = (u32*)wk;
    ewk->master_work_id = wk->wu.work_id;
    ewk->master_id = wk->wu.id;
    ewk->master_player = wk->player_number;
    ewk->wu.blink_timing = ewk->master_id;
    return 0;
}



void effect_e7_e8_init_union(WORK_Other* nwk, WORK_Other* ek, PLW* mk) {
    nwk->wu.old_rno[4] = ek->wu.old_rno[4];
    nwk->wu.old_rno[3] = ek->wu.old_rno[3];
    nwk->wu.old_rno[1] = ek->wu.old_rno[1];
    nwk->wu.old_rno[0] = ek->wu.old_rno[0];
    nwk->wu.my_family = mk->wu.my_family;
    nwk->wu.cgromtype = mk->wu.cgromtype;
    nwk->wu.my_col_mode = mk->wu.my_col_mode;
    nwk->wu.my_col_code = mk->wu.my_col_code;
    nwk->wu.my_ext_pri = mk->wu.my_ext_pri;
    nwk->wu.dir_timer = ek->wu.dmcal_d * ek->wu.dmcal_m;
    nwk->wu.dmcal_d = ek->wu.dmcal_d;
    nwk->wu.dmcal_m = ek->wu.dmcal_m;
    nwk->wu.blink_timing = mk->wu.blink_timing;
    nwk->wu.target_adrs = (u32*)ek;
    nwk->my_master = (u32*)mk;
    nwk->master_work_id = mk->wu.work_id;
    nwk->master_id = mk->wu.id;
    nwk->wu.hit_ix_table = mk->wu.hit_ix_table;
    nwk->wu.body_adrs = mk->wu.body_adrs;
    nwk->wu.attack_adrs = mk->wu.attack_adrs;
    nwk->wu.caught_adrs = mk->wu.caught_adrs;
    nwk->wu.hosei_adrs = mk->wu.hosei_adrs;
    nwk->wu.att_ix_table = mk->wu.att_ix_table;
}



void get_attdata_of_illusion(WORK_Other* ewk) {
    ewk->wu.cg_hit_ix = zanzou_table[ewk->master_id][ewk->wu.type].hit_ix;
    ewk->wu.cg_att_ix = zanzou_table[ewk->master_id][ewk->wu.type].renew;
    ewk->wu.xyz[0].disp.pos = ewk->wu.position_x;
    ewk->wu.xyz[1].disp.pos = ewk->wu.position_y;
    ewk->wu.xyz[2].disp.pos = ewk->wu.position_z;
    get_char_data_zanzou(&ewk->wu);
    ewk->wu.att.dipsw = 15;
    ewk->wu.att.at_free4 = 0;
    ewk->wu.att.guard = 10;
    ewk->wu.att.pow = 0;
    ewk->wu.att.piyo = 0;
    ewk->wu.att.hs_you = 0;
    ewk->wu.add_arts_point = 0;
    ewk->wu.at_koa = zanzou_table[ewk->master_id][ewk->wu.type].kowaza;
    if (ewk->wu.cg_hit_ix) {
        hit_push_request(&ewk->wu);
    }
}

/* Turn on after-images from illusion_setup_table[ix]: { who, image data }.
   who 0 = this player, 1 = the opponent, anything else = both. */
void setup_after_images(PLW* wk, u8 ix) {
    PLW* tk = (PLW*)wk->wu.target_adrs;

    switch ((u16)illusion_setup_table[ix][0]) {
    case 0:
        if (wk->image_setup_flag) {
            break;
        }
        wk->image_setup_flag = 1;
        wk->image_data_index = illusion_setup_table[ix][1];
        break;
    default:
        if (wk->image_setup_flag == 0) {
            wk->image_setup_flag = 1;
            wk->image_data_index = illusion_setup_table[ix][1];
        }
        /* fall through */
    case 1:
        if (tk->image_setup_flag) {
            break;
        }
        tk->image_setup_flag = 1;
        tk->image_data_index = illusion_setup_table[ix][1];
    }
}

/* Turn off after-images.  who 0 = this player, 1 = the opponent, anything else = both. */
void erase_after_images(PLW* wk, u8 who)
{
    PLW* tk = (PLW*)wk->wu.target_adrs;

    switch (who) {
    case 0:
        wk->image_setup_flag = 0;
        break;
    default:
        wk->image_setup_flag = 0;
        /* fall through */
    case 1:
        tk->image_setup_flag = 0;
        break;
    }
}
