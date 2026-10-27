/*
 * EFF74.C  Effect 74: birds on the stage
 *
 * effect_74_init places four birds from eff74_data_tbl (brz_char_table). Each runs the routine of its
 * type (eff74_0000 .. eff74_3000): a bird perches (eff74_perch), waits until a player comes within
 * 224 dots, then flies off along one of the eight paths of eff74_move_tbl (eff74_fly_set, eff74_fly)
 * and lands back on its perch when it is off screen or done.
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
#include "EFF74.h"

/* routine_no[0] */
#define R0_PERCH        0       /* settle on the perch */
#define R0_STAY         1       /* stay put */

/* routine_no[1], watching */
#define R1_WATCH        0       /* watch for a player */
#define R1_REST         1       /* rest a while */

/* routine_no[1], flight path from eff74_move_tbl */
#define R1_FLAP         0       /* flap in place, then perch */
#define R1_RIGHT        1       /* fly off to the right */
#define R1_LEFT         2       /* fly off to the left */

extern const s16 eff74_data_tbl[4][3];      /* provisional name */
extern const s32 eff74_move_tbl[8][6];      /* provisional name */
extern const u32 brz_char_table[];

void eff74_0000(WORK_Other* ewk);
void eff74_1000(WORK_Other* ewk);
void eff74_1001(WORK_Other* ewk);
void eff74_2000(WORK_Other* ewk);
void eff74_2001(WORK_Other* ewk);
void eff74_3000(WORK_Other* ewk);
void eff74_3001(WORK_Other* ewk);
void eff74_perch(WORK_Other* ewk);
void eff74_fly(WORK_Other* ewk);
void eff74_rest(WORK_Other* ewk);
void eff74_fly_set();



/* the routine of the bird's type */
void effect_74_move(WORK_Other* ewk) {
    void (*eff74_jp[4])() = { eff74_0000, eff74_1000, eff74_2000, eff74_3000 };
    if (compel_dead_check(ewk)) {
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
    } else {
        if (!EXE_flag && !Game_pause) {
            eff74_jp[ewk->wu.type](ewk);
        }
        disp_pos_trans_entry_rs(ewk);
    }
}



/* provisional name */
void eff74_0000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_PERCH:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 35);
        break;
    case R0_STAY:
        break;
    }
}



/* provisional name */
void eff74_1000(WORK_Other* ewk) {
    void (*eff74_1000_jp[3])() = { eff74_perch, eff74_1001, eff74_fly };
    eff74_1000_jp[ewk->wu.routine_no[0]](ewk);
}



/* provisional name */
void eff74_1001(WORK_Other* ewk) {
    s16 work;
    if (range_abs_check(plw[0].wu.position_y, ewk->wu.position_y, 224)
        || range_abs_check(plw[1].wu.position_y, ewk->wu.position_y, 224)) {
        ewk->wu.routine_no[0]++;
        work = random_16_com();
        work &= 7;
        eff74_fly_set(ewk, work);
    } else {
        char_move(&ewk->wu);
    }
}



/* provisional name */
void eff74_2000(WORK_Other* ewk) {
    void (*eff74_2000_jp[3])() = { eff74_perch, eff74_2001, eff74_fly };
    eff74_2000_jp[ewk->wu.routine_no[0]](ewk);
}



/* provisional name */
void eff74_2001(WORK_Other* ewk) {
    s16 work;
    switch (ewk->wu.routine_no[1]) {
    case R1_WATCH:
        if (range_abs_check(plw[0].wu.position_y, ewk->wu.position_y, 224)
            || range_abs_check(plw[1].wu.position_y, ewk->wu.position_y, 224)) {
            work = random_16_com();
            if (work & 1) {
                ewk->wu.routine_no[0]++;
                work &= 7;
                eff74_fly_set(ewk, work);
            } else {
                ewk->wu.routine_no[1]++;
                ewk->wu.old_rno[2] = 48;
            }
            break;
        }
        char_move(&ewk->wu);
        break;
    case R1_REST:
        eff74_rest(ewk);
        break;
    }
}



/* provisional name */
void eff74_3000(WORK_Other* ewk) {
    void (*eff74_3000_jp[3])() = { eff74_perch, eff74_3001, eff74_fly };
    eff74_3000_jp[ewk->wu.routine_no[0]](ewk);
}



/* provisional name */
void eff74_3001(WORK_Other* ewk) {
    s16 work;
    switch (ewk->wu.routine_no[1]) {
    case R1_WATCH:
        if (range_abs_check(plw[0].wu.position_y, ewk->wu.position_y, 224)
            || range_abs_check(plw[1].wu.position_y, ewk->wu.position_y, 224)) {
            work = random_16_com();
            if (work > 10) {
                ewk->wu.routine_no[0]++;
                work &= 7;
                eff74_fly_set(ewk, work);
            } else {
                ewk->wu.routine_no[1]++;
                ewk->wu.old_rno[2] = 48;
            }
            break;
        }
        char_move(&ewk->wu);
        break;
    case R1_REST:
        eff74_rest(ewk);
        break;
    }
}



/* provisional name */
void eff74_perch(WORK_Other* ewk) {
    ewk->wu.routine_no[0]++;
    ewk->wu.disp_flag = 1;
    set_char_move_init(&ewk->wu, 0, 34);
    ewk->wu.xyz[0].disp.pos = ewk->wu.old_rno[0];
    ewk->wu.xyz[1].disp.pos = ewk->wu.old_rno[1];
}



/* provisional name */
void eff74_fly(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_FLAP:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[0] = R0_PERCH;
        }
        break;
    case R1_RIGHT:
        char_move(&ewk->wu);
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos > 400) {
            ewk->wu.routine_no[0] = R0_PERCH;
        }
        break;
    case R1_LEFT:
        char_move(&ewk->wu);
        add_x_sub(ewk);
        add_y_sub(ewk);
        if (ewk->wu.xyz[0].disp.pos < -416) {
            ewk->wu.routine_no[0] = R0_PERCH;
        }
        break;
    }
}



/* provisional name */
void eff74_rest(WORK_Other* ewk) {
    ewk->wu.old_rno[2]--;
    if (ewk->wu.old_rno[2] < 0) {
        ewk->wu.routine_no[1] = R1_WATCH;
    }
}



/* provisional name */
void eff74_fly_set(ewk, ix)
WORK_Other* ewk;
s16 ix;
{
    const s32* p = eff74_move_tbl[ix];
    ewk->wu.routine_no[1] = *p++;
    ewk->wu.char_index = *p++;
    ewk->wu.mvxy.a[0].sp = *p++;
    ewk->wu.mvxy.a[1].sp = *p++;
    ewk->wu.mvxy.d[0].sp = *p++;
    ewk->wu.mvxy.d[1].sp = *p;
    set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
}



/* four birds */
s32 effect_74_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data_ptr = &eff74_data_tbl[0][0];
    for (i = 0; i < 4; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 74;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.type = i;
        ewk->wu.dead_f = 1;
        ewk->wu.sync_suzi = 0;
        ewk->wu.my_family = 2;
        ewk->wu.my_col_code = 0x2058;
        ewk->wu.char_table[0] = brz_char_table;
        ewk->wu.old_rno[0] = ewk->wu.xyz[0].disp.pos = *data_ptr++;
        ewk->wu.old_rno[1] = ewk->wu.xyz[1].disp.pos = *data_ptr++;
        ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
        suzi_offset_set(&ewk->wu);
    }
    return 0;
}
