/*
 * EFF06.C  Stage scenery objects, set 06
 *
 * Second set of per-stage decorative sprites, identical in structure to EFF05 but driven
 * from the scr_obj_num6/scr_obj_data6 tables and drawn with disp_pos_trans_entry_rs.
 * effect_06_init creates one object per table entry for the current bg_w.stage and bg_w.area;
 * effect_06_move animates it until compel_dead_check retires it, then frees it.
 * Called from every stage BG init routine alongside effect_05_init.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "CHARMOVE.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "eff06.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the animation */
#define R0_MOVE         1       /* draw until retired */
#define R0_KILL         2       /* (default) put the work back */



/* By stage and area; the last stage has none. */
const s16* scr_obj_data6[14][3] = {
    { scr_obj_data6_0_0, scr_obj_data6_0_0, scr_obj_data6_0_0 },
    { scr_obj_data6_1_0, scr_obj_data6_1_0, scr_obj_data6_1_0 },
    { scr_obj_data6_2_0, scr_obj_data6_2_1, scr_obj_data6_2_1 },
    { scr_obj_data6_3_0, scr_obj_data6_3_1, scr_obj_data6_3_1 },
    { scr_obj_data6_4_0, scr_obj_data6_4_1, scr_obj_data6_4_1 },
    { scr_obj_data6_5_0, scr_obj_data6_5_0, scr_obj_data6_5_0 },
    { scr_obj_data6_6_0, scr_obj_data6_6_1, scr_obj_data6_6_1 },
    { scr_obj_data6_7_0, scr_obj_data6_7_0, scr_obj_data6_7_0 },
    { scr_obj_data6_8_0, scr_obj_data6_8_1, scr_obj_data6_8_1 },
    { scr_obj_data6_9_0, scr_obj_data6_9_0, scr_obj_data6_9_0 },
    { scr_obj_data6_3_1, scr_obj_data6_3_0, scr_obj_data6_3_0 },
    { scr_obj_data6_2_1, scr_obj_data6_2_0, scr_obj_data6_2_0 },
    { scr_obj_data6_12_0, scr_obj_data6_12_0, scr_obj_data6_12_0 },
    { 0, 0, 0 },
};



void effect_06_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R0_MOVE:
        if (compel_dead_check(ewk)) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            if (ewk->wu.hit_stop != 0) {
                char_move(&ewk->wu);
            }
        }
        disp_pos_trans_entry_rs(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* tables by stage and area */
s32 effect_06_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 lp_cnt = scr_obj_num6[bg_w.stage][bg_w.area];
    s16 i;
    const s16* data_ptr;
    if (lp_cnt == 0) {
        return;
    }
    data_ptr = scr_obj_data6[bg_w.stage][bg_w.area];
    for (i = 0; i < lp_cnt; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 6;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.my_col_mode = 0x4200;
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
        ewk->wu.char_table[0] = char_add[bg_w.stage][bg_w.area];
        suzi_offset_set(&ewk->wu);
    }
    return 0;
}
