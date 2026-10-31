/*
 * EFFG5.C  Effect G5: burst of small flying drops
 *
 * setup_ase_extra spawns num_of_ase[] G5 drops around a work's direction, with directions and speeds
 * from ase_dir_hosei, ase_speed_hosei and ase_delta_hosei chosen at random. effect_G5_init
 * creates one drop (plef_char_table) at the work's position; effect_G5_move flies it outward
 * with add_pos_dir_064, slowing by its delta each frame, plays pattern 8 or 9 at random and
 * frees it when the pattern ends. Drops are drawn through the list-8 sort queue.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLS02.h"
#include "EFFG5.h"

/* routine_no[0] */
#define R0_INIT         0       /* pick a pattern and set off */
#define R0_MOVE         1       /* fly outward, slowing down */
#define R0_KILL         2       /* put the work back */



s32 effect_G5_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2020;
        add_pos_dir_064(&ewk->wu, ewk->wu.dir_old * 2);
        set_char_move_init(&ewk->wu, 0, (random_16_com() & 1) + 8);
        /* fall through */
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            ewk->wu.dir_old += ewk->wu.dir_step;
            if (ewk->wu.dir_old < 0) {
                ewk->wu.dir_old = 0;
            }
            add_pos_dir_064(&ewk->wu, ewk->wu.dir_old);
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 0xFF) {
                ewk->wu.disp_flag = 0;
                ewk->wu.routine_no[0]++;
                break;
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



s32 effect_G5_init(wk, dr, sp, dl)
WORK* wk;
s16 dr;
s16 sp;
s16 dl;
{
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 165;
    ewk->wu.work_id = 16;
    ewk->wu.direction = dr;
    ewk->wu.dir_old = sp;
    ewk->wu.dir_step = dl;
    ewk->wu.my_family = wk->my_family;
    ewk->wu.cgromtype = 1;
    ewk->wu.xyz[0].disp.pos = wk->position_x;
    ewk->wu.xyz[1].disp.pos = wk->position_y;
    ewk->wu.position_z = wk->position_z + 1;
    ewk->wu.char_table[0] = plef_char_table;
    return 0;
}



void setup_ase_extra(WORK* wk, s16 num) {
    s16 i;
    s16 way;
    s16 rnd_00;
    s16 rnd_01;
    way = wk->direction * 4;
    rnd_00 = random_16_com() & 3;
    rnd_01 = random_16_com() & 3;
    for (i = 0; i < num_of_ase[num]; i++) {
        effect_G5_init(
            wk, way + ase_dir_hosei[rnd_00][i] & 0x3F, ase_speed_hosei[rnd_01][i], ase_delta_hosei[rnd_01][i]);
    }
}
