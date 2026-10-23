/*
 * EFF44.C  Effect 44 (animated stage objects)
 *
 * Effect 44 creates the 14 animated objects of the fixed eff44_obj_data table
 * and animates them until killed. hit_stop is the object's animate flag; objects other than the
 * first are only drawn while range_x_check says they are on screen.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "SYS_sub.h"
#include "EFF44.h"



extern const s16 eff44_obj_data[14][9];  /* provisional name */
extern u32 eff44_char_table[];  /* provisional name */


/* provisional name */
void effect_44_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case 1:
        if (compel_dead_check(ewk)) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (!EXE_flag && !Game_pause && ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        if (ewk->wu.type == 0 || range_x_check(&ewk->wu)) {
            disp_pos_trans_entry_s(ewk);
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



s32 effect_44_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data_ptr = eff44_obj_data[0];
    for (i = 0; i < 14; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 44;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 2;
        ewk->wu.rl_flag = 0;
        ewk->wu.my_col_mode = 0x4000;
        ewk->wu.type = i;
        ewk->wu.dead_f = *data_ptr++;
        ewk->wu.my_family = *data_ptr++;
        ewk->wu.my_col_code = *data_ptr++;
        ewk->wu.xyz[0].disp.pos = *data_ptr++;
        ewk->wu.xyz[1].disp.pos = *data_ptr++;
        ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
        ewk->wu.char_index = *data_ptr++;
        ewk->wu.hit_stop = *data_ptr++;
        ewk->wu.sync_suzi = *data_ptr++;
        ewk->wu.char_table[0] = eff44_char_table;
        suzi_offset_set(&ewk->wu);
    }
    return 0;
}
