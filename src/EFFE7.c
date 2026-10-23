/*
 * EFFE7.C  Effect E7: single after-image of a player
 *
 * effect_E7_init is called repeatedly by the after-image controller E5 (EFFE5.C) and sets the
 * image up from the controller's parameters. effect_E7_move takes a frame from the player's
 * position history (effe7_get_zanzou_data, zanzou_table), or follows the player directly, copies
 * the player's sprite, flip and graphics fields, and lives for a fixed number of frames while its
 * depth and colour step through after_image_color. Images flagged as attacking are given a hit
 * box through get_attdata_of_illusion.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFE5.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFE7.h"



void effect_E7_move(WORK_Other* ewk) {
    PLW* mwk = (PLW*)ewk->my_master;
    s16 pricol;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.cg_att_ix = 0;
        ewk->wu.cg_hit_ix = 0;
        effe7_get_zanzou_data(ewk);
    case 1:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        ewk->wu.position_z = mwk->wu.position_z;
        if (ewk->wu.old_rno[3] == 0) {
            ewk->wu.old_cgnum = ewk->wu.cg_number = mwk->wu.cg_number;
            ewk->wu.rl_flag = mwk->wu.rl_flag;
            ewk->wu.spr.gfx_ofs = mwk->wu.spr.gfx_ofs;
            ewk->wu.spr.gfx_cells = mwk->wu.spr.gfx_cells;
            ewk->wu.spr.sprite_flip = mwk->wu.spr.sprite_flip;
            ewk->wu.cg_flip = mwk->wu.cg_flip;
            ewk->wu.spr.done_rl = mwk->wu.spr.done_rl;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            if (--ewk->wu.dir_timer <= 0) {
                ewk->wu.disp_flag = 0;
                ewk->wu.routine_no[0]++;
                break;
            }
        }
        pricol = ewk->wu.dmcal_d - (ewk->wu.dir_timer + ewk->wu.dmcal_m - 1) / ewk->wu.dmcal_m;
        if (ewk->wu.old_rno[0]) {
            ewk->wu.position_z -= pricol;
        } else {
            ewk->wu.position_z += pricol;
        }
        if (ewk->wu.old_rno[4]) {
            ewk->wu.extra_col = after_image_color[ewk->wu.old_rno[4] + pricol][ewk->master_id];
        } else {
            ewk->wu.extra_col = mwk->wu.current_colcd;
        }
        if (ewk->wu.old_rno[1]) {
            get_attdata_of_illusion(ewk);
        }
        sort_push_request(&ewk->wu);
        break;
    case 2:
    default:
        if (ewk->wu.old_rno[3]) {
            all_cgps_put_back(&ewk->wu);
        }
        push_effect_work(&ewk->wu);
        break;
    }
}



void effe7_get_zanzou_data(WORK_Other* ewk) {
    ewk->wu.position_x = zanzou_table[ewk->master_id]->pos_x;
    ewk->wu.position_y = zanzou_table[ewk->master_id]->pos_y;
    ewk->wu.position_z = zanzou_table[ewk->master_id]->pos_z;
    ewk->wu.cg_number = zanzou_table[ewk->master_id]->cg_num;
    ewk->wu.rl_flag = zanzou_table[ewk->master_id]->flip;
    ewk->wu.cg_flip = zanzou_table[ewk->master_id]->cg_flp;
}



s32 effect_E7_init(WORK_Other* ek, PLW* mk) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.disp_flag = ek->wu.disp_flag;
    ewk->wu.id = 147;
    if (ek->wu.old_rno[1]) {
        ewk->wu.work_id = 8;
    } else {
        ewk->wu.work_id = 16;
    }
    effect_e7_e8_init_union(ewk, ek, mk);
    return 0;
}
