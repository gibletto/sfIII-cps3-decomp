/*
 * EFF91.C  Effect 91: tilemap cell animation
 *
 * effect_91: plays a tilemap cell animation into a rectangle, optionally looping.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sc_trans.h"
#include "fifo.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "CALDIR.h"
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
#include "eff91.h"
#include "cps3.h"



void effect_91_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.dir_timer = 1;
        ewk->wu.dir_step = ewk->wu.vitality;
        ewk->wu.step_xy_table = &EFF91_Step_Data[ewk->wu.direction];
        ewk->wu.move_xy_table = ewk->wu.step_xy_table;
    case 1:
        if (--ewk->wu.dir_timer == 0) {
            eff91_cell_data_set(ewk);
            if (--ewk->wu.dir_step == 0) {
                if (ewk->wu.dir_old) {
                    ewk->wu.dir_step = ewk->wu.vitality;
                    ewk->wu.move_xy_table = ewk->wu.step_xy_table;
                } else {
                    ewk->wu.routine_no[0] = 2;
                }
            }
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}

/* Paint the next frame of the text-layer panel: the script holds a
   { code, attr } pair for every cell of the dm_vital x dmcal_m rectangle
   whose top-left cell is (vital_new, vital_old).  Bit 8 of the attribute
   carries the code's bank bit. */
/* provisional name */
void eff91_cell_data_set(WORK_Other* ewk)
{
    u16* row;
    u16* cell;
    u16* dst;
    s16* code;
    u16 attr;
    s16 h;
    s16 w;

    cell = (u16*)(ewk->wu.vital_new * 4 + (ewk->wu.vital_old << 8) + SS_RAM);
    ewk->wu.dir_timer = *ewk->wu.move_xy_table++;
    row = cell;
    for (h = ewk->wu.dmcal_m; h > 0; h--) {
        cell = row;
        for (w = ewk->wu.dm_vital; w > 0;) {
            w--;
            *cell++ = *ewk->wu.move_xy_table++ | (((*cell++ = *ewk->wu.move_xy_table++) & 0x100) >> 8);
        }
        row = row + 128;
    }
}



s32 effect_91_init(s16 type, s16 a, s16 b, s16 c, s16 d) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 91;
    ewk->wu.vital_new = a;
    ewk->wu.vital_old = b;
    ewk->wu.dm_vital = c;
    ewk->wu.dmcal_m = d;
    ewk->wu.direction = EFF91_Init_Data[type][0];
    ewk->wu.dir_old = EFF91_Init_Data[type][1];
    ewk->wu.vitality = EFF91_Init_Data[type][2];
    return 0;
}
