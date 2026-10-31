/*
 * EFFD2.C  Effect D2: four panels of the ending scene changes (effect B0)
 *
 * effect_D2_init creates types 0 and 1, effect_D2_init2 types 2 and 3, with patterns 18 + type.
 * Each plays its pattern once and hides. All leave when the master reaches routine 3.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "effd2.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the pattern */
#define R0_MOVE         1       /* play the pattern once, then hide */
#define R0_KILL         3       /* (default) put the work back */



void effect_D2_move(WORK_Other* ewk) {
    WORK_Other* mwk = (WORK_Other*)ewk->my_master;
    if (mwk->wu.routine_no[0] == 3) {
        ewk->wu.routine_no[0] = R0_KILL;
        ewk->wu.disp_flag = 0;
    }
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R0_MOVE:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
        }
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_D2_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    for (i = 0; i < 2; i++) {
        if ((ix = pull_effect_work(3)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)((u32)frw + (ix << 11));
        ewk->wu.id = 132;
        ewk->wu.be_flag = 1;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->my_master = (u32*)oya;
        ewk->wu.type = i;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_family = 1;
        ewk->wu.char_table[0] = etc_char_table;
        ewk->wu.my_col_code = 127;
        ewk->wu.xyz[0].disp.pos = 0x1FF;
        ewk->wu.xyz[1].disp.pos = 0;
        ewk->wu.my_priority = ewk->wu.position_z = 80;
        ewk->wu.char_index = i + 18;
    }
}



s32 effect_D2_init2(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    for (i = 2; i < 4; i++) {
        if ((ix = pull_effect_work(3)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)((u32)frw + (ix << 11));
        ewk->wu.id = 132;
        ewk->wu.be_flag = 1;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->my_master = (u32*)oya;
        ewk->wu.type = i;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_family = 1;
        ewk->wu.char_table[0] = etc_char_table;
        ewk->wu.my_col_code = 127;
        ewk->wu.xyz[0].disp.pos = 0x1FF;
        ewk->wu.xyz[1].disp.pos = 0;
        ewk->wu.my_priority = ewk->wu.position_z = 80;
        ewk->wu.char_index = i + 18;
    }
}
