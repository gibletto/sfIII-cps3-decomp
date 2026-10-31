/*
 * EFF60.C  Effect 60: flashing stage object
 *
 * effect_60_init(type) (from the bgst050 and bgst170 stages and effect 69) sets an object up from
 * flash_obj_data60[type]: family, colour, position, priority, animation and line-scroll sync, drawn
 * from the stage's character table (char_add by stage and area). effect_60_move draws it blinking
 * and runs its animation only while its hit_stop word is set, until compel_dead_check ends it.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "color3rd.h"
#include "ta_sub.h"
#include "bg_sub_5.h"
#include "EFF60.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the animation */
#define R0_FLASH        1       /* blink and animate until retired */
#define R0_KILL         2       /* put the work back */

extern const s16 flash_obj_data60_0[9];
extern const s16 flash_obj_data60_1[9];


const s16* flash_obj_data60[2] = {
    flash_obj_data60_0,
    flash_obj_data60_1,
};


void effect_60_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        ewk->wu.disp_flag = 2;
        ewk->wu.blink_timing = 1;
        break;
    case R0_FLASH:
        if (compel_dead_check(ewk)) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (!EXE_flag && !Game_pause && ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        disp_pos_trans_entry_rs(ewk);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}


s32 effect_60_init(s16 type) {
    WORK_Other* ewk;
    s16 ix;
    const s16* data_ptr;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    data_ptr = flash_obj_data60[type];
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 60;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.type = type;
    ewk->wu.dead_f = *data_ptr++;
    ewk->wu.my_family = *data_ptr++;
    ewk->wu.my_col_code = *data_ptr++;
    ewk->wu.xyz[0].disp.pos = *data_ptr++;
    ewk->wu.xyz[1].disp.pos = *data_ptr++;
    ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
    ewk->wu.char_index = *data_ptr++;
    ewk->wu.hit_stop = *data_ptr++;
    ewk->wu.sync_suzi = *data_ptr;
    ewk->wu.char_table[0] = char_add[bg_w.stage][bg_w.area];
    suzi_offset_set(&ewk->wu);
    return 0;
}
