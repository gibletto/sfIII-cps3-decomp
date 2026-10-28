/*
 * EFF71.C  Effect 71: a stage object that watches the fighters
 *
 * effect_71_init places it by the two characters (eff71_char_tbl) and gives it type 0
 * or 1. Type 0 (eff71_0000) shows pattern 28 at step 1, 3 or 5 by the stage scroll or the x of
 * the fighter it watches (eff71_pattern_get); a super art sends it to pattern 29 and that fighter
 * coming within 32 dots to pattern 30 (eff71_check, eff71_near_check). Type 1 (eff71_1000) plays
 * pattern 40, and 41 when a super art starts.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "ta_sub.h"
#include "aboutspr.h"
#include "EFF71.h"

/* routine_no[0], type 0 */
#define R0_WATCH        0       /* watch the fighters */
#define R0_STARTLED     1       /* startled by a super art */
#define R0_CLOSE        2       /* a fighter came close */

/* routine_no[0], type 1 */
#define R0_START        0       /* start the idle pattern */
#define R0_SUPER        2       /* play the super art pattern */

/* routine_no[1], type 0 watching */
#define R1_INIT         0       /* start the pattern */
#define R1_WATCH        1       /* follow the fighters */
#define R1_TURN         2       /* play the turn, then watch */

/* routine_no[1], type 0 reactions */
#define R1_PLAY         1       /* play it, then watch again */

extern const s16 eff71_char_tbl[];          /* provisional name */

void eff71_0000(WORK_Other* ewk);
void eff71_0000_0000(WORK_Other* ewk);
void eff71_0000_1000(WORK_Other* ewk);
void eff71_0000_2000(WORK_Other* ewk);
static s32 eff71_check(WORK_Other* ewk);
static s32 eff71_near_check();
void eff71_1000(WORK_Other* ewk);
void eff71_1000_0000(WORK_Other* ewk);
void eff71_1000_1000(WORK_Other* ewk);
void eff71_1000_2000(WORK_Other* ewk);



/* the routine of the type */
void effect_71_move(WORK_Other* ewk) {
    void (*eff71_jp[2])() = { eff71_0000, eff71_1000 };
    if (!EXE_flag && !Game_pause) {
        eff71_jp[ewk->wu.type](ewk);
    }
    disp_pos_trans_entry_rs(ewk);
}



/* provisional name */
void eff71_0000(WORK_Other* ewk) {
    void (*eff71_0000_jp[3])() = { eff71_0000_0000, eff71_0000_1000, eff71_0000_2000 };
    eff71_0000_jp[ewk->wu.routine_no[0]](ewk);
}



/* provisional name */
static s32 eff71_pattern_get(WORK_Other* ewk) {
    if (ewk->wu.old_rno[0] == ewk->wu.old_rno[1]) {
        if (bg_w.bgw[1].xy[0].disp.pos < 544) {
            return 1;
        }
        if (bg_w.bgw[1].xy[0].disp.pos < 624) {
            return 3;
        }
        return 5;
    } else if (ewk->wu.old_rno[0] > ewk->wu.old_rno[1]) {
        if (plw[0].wu.position_x < 448) {
            return 1;
        }
        if (plw[0].wu.position_x < 624) {
            return 3;
        }
        return 5;
    }
    if (plw[1].wu.position_x < 448) {
        return 1;
    }
    if (plw[1].wu.position_x < 624) {
        return 3;
    }
    return 5;
}



/* provisional name */
void eff71_0000_0000(WORK_Other* ewk) {
    s16 n;
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        n = eff71_pattern_get(ewk);
        ewk->wu.dir_old = n;
        set_char_move_init2(&ewk->wu, 0, 28, n, 0);
        break;
    case R1_WATCH:
        n = eff71_pattern_get(ewk);
        if (ewk->wu.dir_old != n) {
            set_char_move_init2(&ewk->wu, 0, 28, n, 0);
            ewk->wu.dir_old = n;
            ewk->wu.routine_no[1]++;
        } else {
            eff71_check(ewk);
        }
        break;
    case R1_TURN:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[1] = R1_WATCH;
        }
        break;
    }
}



/* provisional name */
void eff71_0000_1000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        set_char_move_init(&ewk->wu, 0, 29);
        break;
    case R1_PLAY:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[0] = R0_WATCH;
            ewk->wu.routine_no[1] = R1_INIT;
        }
        break;
    }
}



/* provisional name */
void eff71_0000_2000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_INIT:
        ewk->wu.routine_no[1]++;
        set_char_move_init(&ewk->wu, 0, 30);
        break;
    case R1_PLAY:
        if (either_pl_hissatsu_check()) {
            ewk->wu.routine_no[0] = R0_STARTLED;
            ewk->wu.routine_no[1] = R1_INIT;
        } else {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                ewk->wu.routine_no[0] = R0_WATCH;
                ewk->wu.routine_no[1] = R1_INIT;
            }
        }
        break;
    }
}



/* provisional name */
static s32 eff71_check(WORK_Other* ewk) {
    s16 dx;
    if (either_pl_hissatsu_check()) {
        ewk->wu.routine_no[0] = R0_STARTLED;
        ewk->wu.routine_no[1] = R1_INIT;
        return 0;
    }
    if (!ewk->wu.routine_no[0]) {
        if (ewk->wu.old_rno[0]) {
            dx = ewk->wu.position_x - plw[0].wu.position_x;
            if (eff71_near_check(ewk, dx)) {
                return;
            }
        }
        if (ewk->wu.old_rno[1]) {
            dx = ewk->wu.position_x - plw[1].wu.position_x;
            if (eff71_near_check(ewk, dx)) {
                return;
            }
        }
    }
    return 1;
}



/* provisional name */
static s32 eff71_near_check(WORK_Other* ewk, s16 dx) {
    if (ewk->wu.dir_old == 3) {
        if (dx < 0) {
            dx = -dx;
        }
        if (dx < 32) {
            ewk->wu.routine_no[0] = R0_CLOSE;
            ewk->wu.routine_no[1] = R1_INIT;
            return 1;
        }
    }
    return 0;
}



/* provisional name */
void eff71_1000(WORK_Other* ewk) {
    void (*eff71_1000_jp[3])() = { eff71_1000_0000, eff71_1000_1000, eff71_1000_2000 };
    eff71_1000_jp[ewk->wu.routine_no[0]](ewk);
}



/* provisional name */
void eff71_1000_0000(WORK_Other* ewk) {
    ewk->wu.routine_no[0]++;
    ewk->wu.disp_flag = 1;
    set_char_move_init(&ewk->wu, 0, 40);
}



/* provisional name */
void eff71_1000_1000(WORK_Other* ewk) {
    if (either_pl_hissatsu_check()) {
        ewk->wu.routine_no[0] = R0_SUPER;
        set_char_move_init(&ewk->wu, 0, 41);
    } else {
        char_move(&ewk->wu);
    }
}



/* provisional name */
void eff71_1000_2000(WORK_Other* ewk) {
    char_move(&ewk->wu);
    if (ewk->wu.cg_type) {
        ewk->wu.routine_no[0] = R0_START;
    }
}



/* placed and typed by the two characters */
s32 effect_71_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 pl0;
    s16 pl1;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 71;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.rl_flag = 0;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_code = 0x2058;
    ewk->wu.my_priority = 74;
    ewk->wu.position_z = 74;
    ewk->wu.sync_suzi = 0;
    ewk->wu.char_table[0] = brz_char_table;
    ewk->wu.dir_old = 1;
    pl0 = plw[0].player_number;
    pl1 = plw[1].player_number;
    ewk->wu.old_rno[0] = eff71_char_tbl[pl0];
    ewk->wu.old_rno[1] = eff71_char_tbl[pl1];
    if (pl0 == 9 || pl1 == 9 || pl0 == 7 || pl1 == 7 || pl0 == 8 || pl1 == 8) {

        ewk->wu.type = 0;
        ewk->wu.xyz[0].disp.pos = 608;
        ewk->wu.xyz[1].disp.pos = 53;
    } else {
        ewk->wu.type = 1;
        ewk->wu.xyz[0].disp.pos = 700;
        ewk->wu.xyz[1].disp.pos = 56;
    }
    suzi_offset_set(&ewk->wu);
    return 0;
}
