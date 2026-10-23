/*
 * EFF23.C  Effect 23: breakable stage object
 *
 * effect_23_init makes the object at
 * (0x2A0, 48) and its parts (effects 21, 22 and 24) as its children. effect_23_move waits on
 * pattern 7 until eff_hit_check says it was hit, plays pattern 12, and stays broken (pattern 34
 * if eff_hit_flag[type] was already set). effect_23_parts_init makes three
 * broken pieces from eff23_data_tbl that fly off with add_x_sub/add_y_sub.
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
#include "EFF21.h"
#include "EFF22.h"
#include "EFF24.h"
#include "EFF23.h"

extern const s16 eff23_data_tbl[];      /* provisional name */
extern const u32 stg03_char_table[];    /* provisional name (0634EBDC, eff05.c) */



/* Animate the breakable stage object. */
void effect_23_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        if (eff_hit_flag[ewk->wu.type]) {
            set_char_move_init(&ewk->wu, 0, 34);
            ewk->wu.routine_no[0] = 3;
            break;
        }
        set_char_move_init(&ewk->wu, 0, 7);
        break;
    case 1:
        if (!EXE_flag && !Game_pause) {
            if (eff_hit_check(ewk, 0)) {
                ewk->wu.routine_no[0]++;
                set_char_move_init(&ewk->wu, 0, 12);
            } else {
                char_move(&ewk->wu);
            }
        }
        disp_pos_trans_entry_r(ewk);
        break;
    case 2:
        if (!EXE_flag && !Game_pause) {
            char_move(&ewk->wu);
            if (ewk->wu.old_rno[0]) {
                add_x_sub(ewk);
                add_y_sub(ewk);
                if (ewk->wu.xyz[0].disp.pos > 0x380) {
                    ewk->wu.routine_no[0] = 4;
                }
                ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
                ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            } else if (ewk->wu.cg_type) {
                ewk->wu.routine_no[0]++;
            }
        }
        /* fall through */
    case 3:
        disp_pos_trans_entry_r(ewk);
        break;
    case 4:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* Create the object and its parts. */
s32 effect_23_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 23;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.old_rno[0] = 0;
    ewk->wu.type = 8;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 0x2A0;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 48;
    ewk->wu.position_z = ewk->wu.my_priority = 90;
    ewk->wu.char_table[0] = stg03_char_table;
    effect_21_init(ewk);
    effect_22_init(ewk);
    effect_24_init(ewk);
    return 0;
}



/* Create three broken pieces of effect 23. */
/* provisional name */
s32 effect_23_parts_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data_ptr = eff23_data_tbl;
    for (i = 0; i < 3; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 23;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.disp_flag = 1;
        ewk->wu.old_rno[0] = i + 1;
        ewk->wu.my_family = 2;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2040;
        ewk->wu.char_index = *data_ptr++;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = *data_ptr++;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = *data_ptr++;
        *(s16*)&ewk->wu.mvxy.a[0] = *data_ptr++;
        ewk->wu.mvxy.a[0].real.l = *data_ptr++;
        ewk->wu.mvxy.d[0].real.h = *data_ptr++;
        ewk->wu.mvxy.d[0].real.l = *data_ptr++;
        ewk->wu.mvxy.a[1].real.h = *data_ptr++;
        ewk->wu.mvxy.a[1].real.l = *data_ptr++;
        ewk->wu.mvxy.d[1].real.h = *data_ptr++;
        ewk->wu.mvxy.d[1].real.l = *data_ptr++;
        ewk->wu.position_z = ewk->wu.my_priority = 90;
        ewk->wu.char_table[0] = stg03_char_table;
        ewk->wu.routine_no[0] = 2;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
    }
    return 0;
}
