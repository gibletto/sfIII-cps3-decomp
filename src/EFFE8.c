/*
 * EFFE8.C  Effect E8: after-image in a burst trail behind a player
 *
 * effect_E8_init is called by the after-image controller E5 (EFFE5.C) to create a whole trail at
 * once; each image is given its slot in the player's position history (zanzou_table).
 * effect_E8_move follows its slot of the trail (effe8_zanzou_process), copying the player's
 * sprite or the recorded frame, with depth and colour from after_image_color by slot. When the
 * controller stops, each image walks back along the trail, rl_waza steps per frame, and frees
 * itself at the head. Each frame it is drawn with sort_push_request (it always follows its own slot);
 * images flagged as attacking get a hit box through get_attdata_of_illusion.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFE5.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFE8.h"

/* routine_no[0] */
#define R0_INIT         0       /* start at its slot of the trail */
#define R0_MOVE         1       /* keep its slot while the controller runs */
#define R0_RETURN       2       /* walk back to the head of the trail */
#define R0_KILL         3       /* (default) put the work back */



void effect_E8_move(WORK_Other* ewk) {
    PLW* mwk = (PLW*)ewk->my_master;
    WORK_Other* cwk = (WORK_Other*)ewk->wu.target_adrs;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.type = ewk->wu.charset_id;
        ewk->wu.cg_att_ix = 0;
        ewk->wu.cg_hit_ix = 0;
        if (ewk->wu.type >= ewk->wu.charset_id) {
            ewk->wu.type = ewk->wu.charset_id;
            ewk->wu.routine_no[0] = R0_MOVE;
        }
        effe8_zanzou_process(ewk, mwk);
        sort_push_request(&ewk->wu);
        break;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
        effe8_zanzou_process(ewk, mwk);
        if (cwk->wu.routine_no[0] != 1 || cwk->wu.routine_no[1] != 1) {
            ewk->wu.routine_no[0] = R0_RETURN;
        }
        sort_push_request(&ewk->wu);
        break;
    case R0_RETURN:
        ewk->wu.type -= ewk->wu.rl_waza;
        if (ewk->wu.type <= 0) {
            ewk->wu.disp_flag = 0;
            ewk->wu.routine_no[0] = R0_KILL;
        } else {
            effe8_zanzou_process(ewk, mwk);
        }
        sort_push_request(&ewk->wu);
        break;
    default:
        if (ewk->wu.old_rno[3]) {
            all_cgps_put_back(ewk);
        }
        push_effect_work((WORK*)ewk);
        break;
    }
}



/* done_rl in WORK, no metamorphose colour swap */
void effe8_zanzou_process(WORK_Other* ewk, PLW* mwk) {
    ewk->wu.position_x = zanzou_table[ewk->master_id][ewk->wu.type].pos_x;
    ewk->wu.position_y = zanzou_table[ewk->master_id][ewk->wu.type].pos_y;
    ewk->wu.position_z = mwk->wu.position_z;
    if (ewk->wu.old_rno[3] == 0) {
        ewk->wu.old_cgnum = ewk->wu.cg_number = mwk->wu.cg_number;
        ewk->wu.rl_flag = mwk->wu.rl_flag;
        ewk->wu.spr.gfx_ofs = mwk->wu.spr.gfx_ofs;
        ewk->wu.spr.gfx_cells = mwk->wu.spr.gfx_cells;
        ewk->wu.spr.sprite_flip = mwk->wu.spr.sprite_flip;
        ewk->wu.cg_flip = mwk->wu.cg_flip;
        ewk->wu.spr.done_rl = mwk->wu.spr.done_rl;
    } else {
        ewk->wu.cg_number = zanzou_table[ewk->master_id][ewk->wu.type].cg_num;
        ewk->wu.rl_flag = zanzou_table[ewk->master_id][ewk->wu.type].flip;
        ewk->wu.cg_flip = zanzou_table[ewk->master_id][ewk->wu.type].cg_flp;
    }
    if (ewk->wu.old_rno[0]) {
        ewk->wu.position_z -= ewk->wu.rl_waza;
    } else {
        ewk->wu.position_z += ewk->wu.rl_waza;
    }
    if (ewk->wu.old_rno[4]) {
        ewk->wu.extra_col = after_image_color[ewk->wu.old_rno[4] + ewk->wu.rl_waza - 1][ewk->master_id];
    } else {
        ewk->wu.extra_col = mwk->wu.current_colcd;
    }
    if (ewk->wu.old_rno[1]) {
        get_attdata_of_illusion(ewk);
    }
}



s32 effect_E8_init(WORK_Other* ek, PLW* mk, s16 data) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.disp_flag = ek->wu.disp_flag;
    ewk->wu.id = 148;
    ewk->wu.type = 0;
    ewk->wu.charset_id = data;
    ewk->wu.rl_waza = data / ek->wu.dmcal_m;
    if (ek->wu.old_rno[1]) {
        ewk->wu.work_id = 8;
    } else {
        ewk->wu.work_id = 16;
    }
    effect_e7_e8_init_union(ewk, ek, mk);
    return 0;
}
