/*
 * EFFC2.C  Effect C2: stage objects that drop on the landing
 *
 * effect_C2_init creates four eff45_char_table objects from effc2_data_tbl (x, y, priority,
 * pattern). Each plays its pattern once bg_land_flag is set, clears bg_etc_flag when the pattern
 * ends, waits for BG1's state 2 and then hides and frees itself.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "EFFC2.h"

extern const s16 effc2_data_tbl[4][4];   /* provisional name */
extern const u32 eff45_char_table[];     /* provisional name */



void effect_C2_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case 1:
        if (bg_land_flag) {
            ewk->wu.routine_no[0]++;
        }
        disp_pos_trans_entry(ewk);
        break;
    case 2:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[0]++;
            bg_etc_flag = 0;
        }
        disp_pos_trans_entry(ewk);
        break;
    case 3:
        if (bg_w.bgw[1].r_no_1 >= 2) {
            ewk->wu.routine_no[0]++;
        }
        disp_pos_trans_entry(ewk);
        break;
    case 4:
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_C2_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data_ptr = &effc2_data_tbl[0][0];
    for (i = 0; i < 4; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 122;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.disp_flag = 0;
        ewk->wu.rl_flag = 0;
        ewk->wu.type = i;
        ewk->wu.my_family = 2;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2040;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = *data_ptr++;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = *data_ptr++;
        ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
        ewk->wu.char_index = *data_ptr++;
        ewk->wu.xyz[0].disp.low = 0;
        ewk->wu.xyz[1].disp.low = 0;
        ewk->wu.char_table[0] = eff45_char_table;
    }
    return 0;
}
