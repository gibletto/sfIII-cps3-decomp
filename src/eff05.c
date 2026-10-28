/*
 * EFF05.C  Stage scenery objects, set 05 (line-scroll synchronised)
 *
 * Places the fixed decorative sprites that belong to the current stage background.
 * effect_05_init reads the per-stage object list scr_obj_num/scr_obj_data by bg_w.stage
 * and bg_w.area and creates one effect work per entry with its family, colour, position,
 * priority, animation index and line-scroll sync value.
 * effect_05_move starts the animation, draws it through disp_pos_trans_entry_s until the
 * object is retired by compel_dead_check, then frees its graphics and work.
 * Stage background init routines call effect_05_init.
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
#include "EFF45.h"
#include "EFF86.h"
#include "eff05.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the animation */
#define R0_MOVE         1       /* draw until retired */
#define R0_KILL         2       /* (default) put the work back */



/* By stage and area; the last stage has none. */
u32* char_add[14][3] = {
    { stg00_char_table, stg00_char_table, stg00_char_table },
    { stg01_char_table, stg01_char_table, stg01_char_table },
    { stg02_char_table, stg11_char_table, stg11_char_table },
    { stg03_char_table, stg10_char_table, stg10_char_table },
    { stg04_char_table, stg04_char_table, stg04_char_table },
    { stg05_char_table, stg05_char_table, stg05_char_table },
    { stg06_char_table, stg06_char_table, stg06_char_table },
    { stg07_char_table, stg07_char_table, stg07_char_table },
    { eff45_char_table, eff86_char_table, eff86_char_table },
    { brz_char_table, brz_char_table, brz_char_table },
    { stg10_char_table, stg03_char_table, stg03_char_table },
    { stg11_char_table, stg02_char_table, stg02_char_table },
    { stg12_char_table, stg12_char_table, stg12_char_table },
    { 0, 0, 0 },
};


const s16* scr_obj_data[14][3] = {
    { (const s16*)scr_obj_num + 42, (const s16*)scr_obj_num + 42, (const s16*)scr_obj_num + 42 },
    { (const s16*)scr_obj_num + 87, (const s16*)scr_obj_num + 87, (const s16*)scr_obj_num + 87 },
    { (const s16*)scr_obj_num + 124, (const s16*)scr_obj_num + 142, (const s16*)scr_obj_num + 142 },
    { (const s16*)scr_obj_num + 178, (const s16*)scr_obj_num + 232, (const s16*)scr_obj_num + 232 },
    { (const s16*)scr_obj_num + 259, (const s16*)scr_obj_num + 286, (const s16*)scr_obj_num + 286 },
    { (const s16*)scr_obj_num + 331, (const s16*)scr_obj_num + 331, (const s16*)scr_obj_num + 331 },
    { (const s16*)scr_obj_num + 412, (const s16*)scr_obj_num + 475, (const s16*)scr_obj_num + 529 },
    { (const s16*)scr_obj_num + 565, (const s16*)scr_obj_num + 565, (const s16*)scr_obj_num + 565 },
    { (const s16*)scr_obj_num + 583, (const s16*)scr_obj_num + 592, (const s16*)scr_obj_num + 592 },
    { (const s16*)scr_obj_num + 628, (const s16*)scr_obj_num + 628, (const s16*)scr_obj_num + 628 },
    { (const s16*)scr_obj_num + 232, (const s16*)scr_obj_num + 178, (const s16*)scr_obj_num + 178 },
    { (const s16*)scr_obj_num + 142, (const s16*)scr_obj_num + 124, (const s16*)scr_obj_num + 124 },
    { (const s16*)scr_obj_num + 123, (const s16*)scr_obj_num + 123, (const s16*)scr_obj_num + 123 },
    { 0, 0, 0 },
};


void effect_05_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R0_MOVE:
        if (compel_dead_check(ewk) != 0) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (!EXE_flag && !Game_pause && ewk->wu.hit_stop) {
            char_move(&ewk->wu);
        }
        disp_pos_trans_entry_s(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* tables by stage and area, char_table set last */
s32 effect_05_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 lp_cnt = scr_obj_num[bg_w.stage][bg_w.area];
    s16 i;
    const s16* data_ptr;
    if (lp_cnt == 0) {
        return;
    }
    data_ptr = scr_obj_data[bg_w.stage][bg_w.area];
    for (i = 0; i < lp_cnt; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 5;
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
