/*
 * EFF30.C  Effect 30: an animated object placed from its type
 *
 * effect_30_move places the object at its own position plus the offsets of its type in
 * eff30_data_tbl (X mirrored by rl_flag), starts the type's animation and plays it until it
 * ends or dead_f is set. effect_30_init and eff30_dummy do nothing.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFF30.h"


extern const EFF30_DATA eff30_data_tbl[];    /* provisional name */



void effect_30_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2020;
        if (ewk->wu.rl_flag) {
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos - eff30_data_tbl[ewk->wu.type].x;
        } else {
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos + eff30_data_tbl[ewk->wu.type].x;
        }
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos + eff30_data_tbl[ewk->wu.type].y;
        ewk->wu.position_z = ewk->wu.xyz[2].disp.pos + eff30_data_tbl[ewk->wu.type].z;
        set_char_move_init(&ewk->wu, 0, eff30_data_tbl[ewk->wu.type].index);
        /* fall through */
    case 1:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type == 0xFF) {
                ewk->wu.disp_flag = 0;
                ewk->wu.routine_no[0]++;
                break;
            }
        }
        sort_push_request(&ewk->wu);
        break;
    case 2:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_30_init(void) {
    return 0;
}



/* provisional name */
void eff30_dummy(void) {
}
