/*
 * EFF55.C  Effect 55: a bird that lands, flies off and comes back
 *
 * effect_55_init places a bird at (672, 114); effect_55_move runs
 * the routine of its state (eff55_0000/1000/2000). eff55_1000 takes off and flies off to the
 * right (eff55_1000_0000/1000), waits, sometimes crosses back from right to left (2000/3000),
 * then glides in from the left to its perch (4000/5000); eff55_2000 lands it again.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "CALDIR.h"
#include "ta_sub.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "eff56.h"

extern const u32 brz_char_table[];

void eff55_0000(WORK_Other* ewk);
void eff55_1000(WORK_Other* ewk);
void eff55_1000_0000(WORK_Other* ewk);
void eff55_1000_1000(WORK_Other* ewk);
void eff55_1000_2000(WORK_Other* ewk);
void eff55_1000_3000(WORK_Other* ewk);
void eff55_1000_4000(WORK_Other* ewk);
void eff55_1000_5000(WORK_Other* ewk);
void eff55_2000(WORK_Other* ewk);



/* the routine of the bird's state */
void effect_55_move(WORK_Other* ewk) {
    void (*eff55_jp[3])() = { eff55_0000, eff55_1000, eff55_2000 };
    if (!EXE_flag && !Game_pause) {
        eff55_jp[ewk->wu.routine_no[0]](ewk);
    }
    disp_pos_trans_entry_rs(ewk);
}



/* provisional name */
void eff55_0000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 20);
        break;
    case 1:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[0]++;
            ewk->wu.routine_no[1] = 0;
        }
        break;
    }
}



/* provisional name */
void eff55_1000(WORK_Other* ewk) {
    void (*eff55_1000_jp[6])() = { eff55_1000_0000, eff55_1000_1000, eff55_1000_2000, eff55_1000_3000, eff55_1000_4000, eff55_1000_5000 };
    eff55_1000_jp[ewk->wu.routine_no[1]](ewk);
}



/* provisional name */
void eff55_1000_0000(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;
    set_char_move_init(&ewk->wu, 0, 21);
    ewk->wu.mvxy.a[0].sp = 0x18000;
    ewk->wu.mvxy.a[1].sp = 0x80;
    ewk->wu.mvxy.d[0].sp = 0x2800;
    ewk->wu.mvxy.d[1].sp = 0x200;
}



/* provisional name */
void eff55_1000_1000(WORK_Other* ewk) {
    s16 work;
    char_move(&ewk->wu);
    add_x_sub(ewk);
    add_y_sub(ewk);
    if (ewk->wu.xyz[0].disp.pos > 912) {
        work = random_16_com();
        if (work & 1) {
            ewk->wu.routine_no[1] = 4;
            ewk->wu.old_rno[0] = 864;
            ewk->wu.disp_flag = 0;
        } else {
            ewk->wu.routine_no[1] = 2;
            ewk->wu.old_rno[0] = 352;
            ewk->wu.disp_flag = 0;
        }
    }
}



/* provisional name */
void eff55_1000_2000(WORK_Other* ewk) {
    ewk->wu.old_rno[0]--;
    if (ewk->wu.old_rno[0] < 0) {
        ewk->wu.routine_no[1] = 3;
        ewk->wu.disp_flag = 1;
        ewk->wu.rl_flag = 1;
        ewk->wu.mvxy.a[0].sp = -0x18000;
        ewk->wu.mvxy.a[1].sp = 0x180;
        ewk->wu.mvxy.d[0].sp = -0x2800;
        ewk->wu.mvxy.d[1].sp = 0x210;
    }
}



/* provisional name */
void eff55_1000_3000(WORK_Other* ewk) {
    add_x_sub(ewk);
    add_y_sub(ewk);
    char_move(&ewk->wu);
    if (ewk->wu.xyz[0].disp.pos < 96) {
        ewk->wu.rl_flag = 0;
        ewk->wu.routine_no[1] = 4;
        ewk->wu.old_rno[0] = 352;
        ewk->wu.disp_flag = 0;
    }
}



/* provisional name */
void eff55_1000_4000(WORK_Other* ewk) {
    ewk->wu.old_rno[0]--;
    if (ewk->wu.old_rno[0] < 0) {
        ewk->wu.routine_no[1] = 5;
        ewk->wu.disp_flag = 1;
        ewk->wu.xyz[0].disp.pos = 96;
        ewk->wu.xyz[1].disp.pos = 168;
        ewk->wu.old_rno[0] = 160;
        cal_all_speed_data(&ewk->wu, 160, 672, 114, 2, 2);
        ewk->wu.my_priority = 80;
        ewk->wu.position_z = 80;
    }
}



/* provisional name */
void eff55_1000_5000(WORK_Other* ewk) {
    char_move(&ewk->wu);
    ewk->wu.old_rno[0]--;
    if (ewk->wu.old_rno[0] <= 0) {
        ewk->wu.routine_no[0]++;
        ewk->wu.routine_no[1] = 0;
        set_char_move_init(&ewk->wu, 0, 26);
        ewk->wu.xyz[0].disp.pos = 672;
        ewk->wu.xyz[1].disp.pos = 114;
        ewk->wu.my_priority = 86;
        ewk->wu.position_z = 86;
    } else {
        add_x_sub(ewk);
        add_y_sub(ewk);
    }
}



/* provisional name */
void eff55_2000(WORK_Other* ewk) {
    char_move(&ewk->wu);
    if (ewk->wu.cg_type) {
        ewk->wu.routine_no[0] = 0;
        ewk->wu.routine_no[1] = 0;
    }
}



/* (bird at (672, 114), brz_char_table) */
s32 effect_55_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 55;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 0x2058;
    ewk->wu.xyz[0].disp.pos = 672;
    ewk->wu.xyz[1].disp.pos = 114;
    ewk->wu.my_priority = 86;
    ewk->wu.position_z = 86;
    ewk->wu.hit_stop = 0;
    ewk->wu.sync_suzi = 0;
    ewk->wu.char_table[0] = brz_char_table;
    suzi_offset_set(&ewk->wu);
    return 0;
}
