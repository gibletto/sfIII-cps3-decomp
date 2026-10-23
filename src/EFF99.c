/*
 * EFF99.C  Effect 99: a mark played once at a fixed position
 *
 * effect_99_init(index, x, y, family) (from effect A0) creates a sprite from eff99_char_table,
 * scaled to 20 x 20 and drawn in front; effect_99_move plays its pattern once and frees it.
 */

#include "structs.h"
#include "work.h"
#include "extern.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "charmove_2.h"

extern const u32 eff99_char_table[];

void effect_99_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case 1:
        if (ewk->wu.cg_type == 0) {
            char_move(&ewk->wu);
        } else {
            ewk->wu.routine_no[0]++;
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
        break;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}

s32 effect_99_init(s16 index, s16 x, s16 y, s16 family) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 99;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.my_family = family;
    ewk->wu.position_z = 1;
    ewk->wu.char_table[0] = (u32*)eff99_char_table;
    ewk->wu.char_index = index;
    ewk->wu.xyz[0].disp.pos = x;
    ewk->wu.xyz[1].disp.pos = y;
    ewk->wu.my_mr_flag = 1;
    ewk->wu.my_mr.size.x = 20;
    ewk->wu.my_mr.size.y = 20;
    return 0;
}
