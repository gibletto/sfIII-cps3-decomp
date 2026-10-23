/*
 * EFF56.C  Effect 56: a stage object that crosses the screen
 *
 * effect_56_init (from bg140_layer0_init) makes it off-screen on the left. eff56_0000 waits
 * old_rno[0] frames and shows it; eff56_1000 zooms it to 12, moves it right with its pattern
 * until it passes 0x1FE, then puts it back on the left and waits 600 frames.
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
#include "bg_sub_5.h"
#include "aboutspr.h"
#include "eff56.h"

extern const u32 eff56_char_table[];    /* provisional name (061F9C34) */

void eff56_0000(WORK_Other* ewk);
void eff56_1000(WORK_Other* ewk);



void effect_56_move(WORK_Other* ewk) {
    void (*eff56_jp[2])() = { eff56_0000, eff56_1000 };
    if (compel_dead_check(ewk)) {
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
    } else {
        if (!EXE_flag && !Game_pause) {
            eff56_jp[ewk->wu.routine_no[0]](ewk);
        }
        if (range_x_check(&ewk->wu)) {
            suzi_sync_pos_set(ewk);
            sort_push_request4(&ewk->wu);
        }
    }
}



/* provisional name */
/* waits old_rno[0] frames */
void eff56_0000(WORK_Other* ewk) {
    ewk->wu.old_rno[0]--;
    if (ewk->wu.old_rno[0] < 0) {
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
    }
}



/* provisional name */
/* crosses the screen */
void eff56_1000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.my_mr_flag = 1;
        ewk->wu.routine_no[1]++;
        ewk->wu.my_mr.size.x = 12;
        ewk->wu.my_mr.size.y = 12;
        ewk->wu.mvxy.a[0].sp = 0x2500;
        ewk->wu.mvxy.d[0].sp = 0;
        break;
    case 1:
        char_move(&ewk->wu);
        if (ewk->wu.xyz[0].disp.pos > 0x1FE) {
            ewk->wu.routine_no[1]++;
        } else {
            add_x_sub(ewk);
        }
        break;
    case 2:
        ewk->wu.routine_no[0] = 0;
        ewk->wu.routine_no[1] = 0;
        ewk->wu.xyz[0].disp.pos = -0x100;
        ewk->wu.xyz[1].disp.pos = 112;
        ewk->wu.disp_flag = 0;
        ewk->wu.old_rno[0] = 600;
        set_char_move_init(&ewk->wu, 0, 0);
        break;
    }
}



/* provisional name */
/* empty */
void eff56_dummy(void) {
}



s32 effect_56_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 56;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.dead_f = 1;
    ewk->wu.sync_suzi = 1;
    ewk->wu.my_family = 1;
    ewk->wu.my_col_code = 87;
    ewk->wu.xyz[0].disp.pos = -0x100;
    ewk->wu.xyz[1].disp.pos = 112;
    ewk->wu.my_mr_flag = 1;
    ewk->wu.position_z = ewk->wu.my_priority = 81;
    ewk->wu.old_rno[0] = 108;
    ewk->wu.disp_flag = 0;
    ewk->wu.char_table[0] = eff56_char_table;
    set_char_move_init(&ewk->wu, 0, 0);
    suzi_offset_set(&ewk->wu);
    return 0;
}
