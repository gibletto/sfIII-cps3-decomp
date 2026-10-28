/*
 * EFF47.C  Effect 47: blinking mark
 *
 * effect_47_move shows a mark (disp_mark_cells) at its position, stepping through its cells
 * two at a time with the durations in eff47_timer_tbl. effect_47_init creates five marks from
 * the colour, position and priority records in eff47_init_data. The marks keep going until
 * no screen wipe is running, then until told to end; type 2 marks are drawn even off screen.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFF19.h"
#include "EFF47.h"
#include "eff05.h"

/* routine_no[0] */
#define R0_INIT         0       /* show and start the blinking */
#define R0_WIPE         1       /* blink until the screen wipe ends */
#define R0_MOVE         2       /* blink until retired */


void disp_mark_cells();



void effect_47_move(WORK_Other* ewk) {
    s16 no;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.cg_ctr = eff47_timer_tbl[0];
        ewk->wu.cg_ix = 0;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
        break;
    case R0_WIPE:
        if (!Exec_Wipe) {
            ewk->wu.routine_no[0]++;
        }
        /* fall through */
    case R0_MOVE:
        if (!EXE_flag && !Game_pause) {
            if (--ewk->wu.cg_ctr == 0) {
                ewk->wu.cg_ix += 2;
                if (ewk->wu.cg_ix > 16) {
                    ewk->wu.cg_ix = 0;
                }
                ewk->wu.cg_ctr = eff47_timer_tbl[ewk->wu.cg_ix / 2];
            }
        }
        if (ewk->wu.type == 2 || range_x_check((WORK*)ewk)) {
            no = ewk->wu.cg_ix / 2;
            disp_mark_cells((WORK*)ewk, no);
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

s32 effect_47_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data = &eff47_init_data[0][0];
    for (i = 0; i < 5; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 47;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.my_col_mode = 0x4200;
        *ewk->wu.char_table = stg00_char_table;
        ewk->wu.type = i;
        ewk->wu.my_family = 2;
        ewk->wu.my_col_code = *data++;
        ewk->wu.xyz[0].disp.pos = *data++;
        ewk->wu.xyz[1].disp.pos = *data++;
        ewk->wu.my_priority = ewk->wu.position_z = *data++;
    }
    effect_19_init(ewk);
    return 0;
}
