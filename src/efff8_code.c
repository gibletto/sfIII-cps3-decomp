/*
 * EFFF8_CODE.C  Effect F8: after-image of a character
 *
 * effect_F8_init sets up the after-images of a character (setup_after_images, set 6).
 * effect_F8_move plays one after-image: it takes its visibility and animation from
 * effF8_type_tbl by its type, its facing from the master and its colour from whether the
 * master's id is nonzero, then follows the master just behind it until its animation ends or
 * dead_f is set.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFE5.h"
#include "efff8_code.h"


extern const EFFF8_TYPE effF8_type_tbl[];    /* provisional name */



void effect_F8_move(WORK_Other* ewk) {
    WORK* mwk = (WORK*)ewk->my_master;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = effF8_type_tbl[ewk->wu.type].disp;
        ewk->wu.blink_timing = ewk->master_id;
        ewk->wu.rl_flag = mwk->rl_flag;
        if (ewk->master_id) {
            ewk->wu.my_col_code = 0x20A8;
        } else {
            ewk->wu.my_col_code = 0x20A0;
        }
        set_char_move_init(&ewk->wu, 0, effF8_type_tbl[ewk->wu.type].index);
        break;
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
        ewk->wu.position_x = mwk->position_x;
        ewk->wu.position_y = mwk->position_y;
        ewk->wu.position_z = mwk->position_z - 1;
        sort_push_request(&ewk->wu);
        break;
    case 2:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



void effect_F8_init(PLW* wk) {
    setup_after_images(wk, 6);
}
