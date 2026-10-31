/*
 * EFFC4.C  Effect C4: bouncing object
 *
 * effect_C4_move starts the object's pattern and runs it through three flight phases whose speeds
 * come from effC4_sp_tbl: each time it falls below the floor the next phase starts (a bounce),
 * with a landing sound requested on the first landing. After the last bounce it slides left,
 * still animating, and is hidden and freed once it passes x 128. It shows a shadow and uses
 * direct_03_char_table. effect_C4_init creates it at its master's position with a shadow.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "EFFC4.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the first flight */
#define R0_FLY          1       /* first flight, sound on landing */
#define R0_BOUNCE       2       /* first bounce */
#define R0_BOUNCE2      3       /* second bounce */
#define R0_SLIDE        4       /* slide left until x 128 */
#define R0_END          5       /* one more frame */
#define R0_KILL         6       /* (default) put the work back */



void effect_C4_move(WORK_Other* ewk) {
    const s32* spd;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        spd = effC4_sp_tbl[ewk->wu.routine_no[0]];
        ewk->wu.mvxy.a[0].sp = *spd++;
        ewk->wu.mvxy.a[1].sp = *spd++;
        ewk->wu.mvxy.d[0].sp = *spd++;
        ewk->wu.mvxy.d[1].sp = *spd;
        break;
    case R0_FLY:
    case R0_BOUNCE:
    case R0_BOUNCE2:
        if (EXE_flag == 0 && Game_pause == 0) {
            if (ewk->wu.cg_type != 2) {
                char_move(&ewk->wu);
            }
            add_x_sub(ewk);
            add_y_sub(ewk);
            if (ewk->wu.xyz[1].disp.pos < 0) {
                if (ewk->wu.routine_no[0] == R0_FLY) {
                    Sound_SE(0x139);
                }
                ewk->wu.routine_no[0]++;
                spd = effC4_sp_tbl[ewk->wu.routine_no[0]];
                ewk->wu.mvxy.a[0].sp = *spd++;
                ewk->wu.mvxy.a[1].sp = *spd++;
                ewk->wu.mvxy.d[0].sp = *spd++;
                ewk->wu.mvxy.d[1].sp = *spd;
                char_move_z(&ewk->wu);
            }
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos;
        sort_push_request(&ewk->wu);
        break;
    case R0_SLIDE:
        if (EXE_flag == 0 && Game_pause == 0) {
            add_x_sub(ewk);
            char_move(&ewk->wu);
            if (ewk->wu.xyz[0].disp.pos < 128) {
                ewk->wu.routine_no[0]++;
            }
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos;
        sort_push_request(&ewk->wu);
        break;
    case R0_END:
        ewk->wu.routine_no[0]++;
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}


s32 effect_C4_init(WORK* wk) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 124;
    ewk->wu.work_id = 16;
    ewk->wu.type = wk->id;
    ewk->wu.cgromtype = 1;
    ewk->wu.disp_flag = 1;
    ewk->wu.my_family = 2;
    ewk->wu.char_index = 6;
    ewk->master_id = wk->id;
    ewk->wu.my_col_mode = wk->my_col_mode;
    ewk->wu.my_col_code = wk->my_col_code;
    ewk->wu.my_priority = ewk->wu.position_z = 16;
    ewk->wu.xyz[0].cal = wk->xyz[0].cal;
    ewk->wu.xyz[1].cal = wk->xyz[1].cal;
    ewk->wu.char_table[0] = direct_03_char_table;
    ewk->wu.kage_flag = 1;
    ewk->wu.kage_hx = -9;
    ewk->wu.kage_hy = -11;
    ewk->wu.kage_char = 11;
    ewk->wu.kage_prio = ewk->wu.position_z + 1;
}
