/*
 * EFF16.C  Effect 16: a blinking object on BG 1
 *
 * effect_16_init(type) makes one; effect_16_all_init makes types 0-14 unless test_flag is set
 * (nothing calls it). effect_16_move places it from eff16_data_tbl[type] (x, y and cg_number) at
 * double size, blinks it (disp_flag 2) for 20 frames relative to BG 1, and releases it then or
 * when dead_f is set.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "EFF16.h"

/* routine_no[0] */
#define R0_INIT         0       /* place it at double size */
#define R0_BLINK        1       /* blink for 20 frames */
#define R0_KILL         2       /* put the work back */

/* eff16_data_tbl columns */
#define EFF16_X         0       /* x from BG 1 */
#define EFF16_Y         1       /* y from BG 1 */
#define EFF16_CG        3       /* cell number */

extern const s16 eff16_data_tbl[15][4];  /* provisional name (06433720): x, y, -, cg_number */



void effect_16_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 2;
        ewk->wu.blink_timing = 2;
        ewk->wu.dir_timer = 20;
        ewk->wu.old_cgnum = 0;
        ewk->wu.cg_number = 1;
        ewk->wu.xyz[0].disp.pos = eff16_data_tbl[ewk->wu.type][EFF16_X];
        ewk->wu.xyz[1].disp.pos = eff16_data_tbl[ewk->wu.type][EFF16_Y];
        ewk->wu.cg_number = eff16_data_tbl[ewk->wu.type][EFF16_CG];
        ewk->wu.my_priority = ewk->wu.position_z = 24;
        ewk->wu.my_mr_flag = 1;
        ewk->wu.my_mr.size.x = 127;
        ewk->wu.my_mr.size.y = 127;
        break;
    case R0_BLINK:
        ewk->wu.dir_timer--;
        if (ewk->wu.dead_f != 0 || ewk->wu.dir_timer <= 0) {
            ewk->wu.disp_flag = 0;
            ewk->wu.routine_no[0]++;
            break;
        }
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos + bg_w.bgw[1].wxy[0].disp.pos;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos + bg_w.bgw[1].wxy[1].disp.pos;
        sort_push_request(&ewk->wu);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_16_init(s16 type) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 16;
    ewk->wu.type = type;
    ewk->wu.work_id = 16;
    ewk->wu.my_family = 2;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4400;
    ewk->wu.my_col_code = 0x2000;
    return 0;
}



/* provisional name */
/* Unreferenced: create every type at once. */
s32 effect_16_all_init(void) {
    if (test_flag) {
        return 0;
    }
    effect_16_init(0);
    effect_16_init(1);
    effect_16_init(2);
    effect_16_init(3);
    effect_16_init(4);
    effect_16_init(5);
    effect_16_init(6);
    effect_16_init(7);
    effect_16_init(8);
    effect_16_init(9);
    effect_16_init(10);
    effect_16_init(11);
    effect_16_init(12);
    effect_16_init(13);
    effect_16_init(14);
}
