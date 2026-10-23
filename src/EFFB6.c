/*
 * EFFB6.C  Effect B6: palette cycle
 *
 * effect_B6_init(type) creates an object that steps every 4 frames through the six colours of
 * row type of effB6_col_tbl. Normally each colour is loaded with load_any_color; while a fade is
 * running (Fade_Flag), or while judge_flag is 1, it is loaded through load_any_color_fade with
 * the fade layer's level or full white. The object ends when its dead_f is set to 1.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "color3rd.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFB6.h"

extern const u16 effB6_col_tbl[2][6];    /* provisional name */

void load_any_color();



s32 effect_B6_init(s8 type) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 116;
    ewk->wu.work_id = 16;
    ewk->wu.rl_flag = type;
    ewk->wu.rl_waza = 4;
    ewk->wu.weight_level = 0;
    return 0;
}



void effect_B6_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag != 0 || Game_pause != 0) {
            break;
        }
        ewk->wu.rl_waza--;
        if (ewk->wu.rl_waza != 0) {
            break;
        }
        ewk->wu.rl_waza = 4;
        if (Fade_Flag == 0) {
            if (judge_flag == 1) {
                load_any_color_fade(effB6_col_tbl[ewk->wu.rl_flag][ewk->wu.weight_level], 16, 16, 16);
            } else {
                load_any_color(effB6_col_tbl[ewk->wu.rl_flag][ewk->wu.weight_level]);
            }
        } else {
            load_any_color_fade(effB6_col_tbl[ewk->wu.rl_flag][ewk->wu.weight_level],
                                fade_layer[0].v10, fade_layer[0].v12, fade_layer[0].v14);
        }
        if (ewk->wu.weight_level == 5) {
            ewk->wu.weight_level = 0;
        } else {
            ewk->wu.weight_level++;
        }
        break;
    case 1:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}
