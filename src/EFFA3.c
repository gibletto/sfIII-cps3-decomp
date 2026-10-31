/*
 * EFFA3.C  Effect A3: text-layer cell animation
 *
 * Effect A3 animates blocks of text-layer cells: effect_A3_init takes a position, size, step,
 * repeat count and layout and a type whose step data come from EFF91_Init_Data / EFF91_Step_Data.
 * effA3_cell_put writes each frame's code/attribute pairs with tilemap_put_cell and moves the
 * draw position; at the end effA3_area_clear clears the rectangle from EFFA3_Area_Data.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "eff87.h"
#include "eff88.h"
#include "eff89.h"
#include "eff90.h"
#include "eff91.h"
#include "eff92_code.h"
#include "Eff93.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "sc_trans.h"
#include "sc_clear.h"
#include "EFFA3.h"

/* routine_no[0] */
#define R0_INIT         0       /* load the step data */
#define R0_MOVE         1       /* put the cells frame by frame */
#define R0_KILL         2       /* (default) clear the area, put the work back */

/* EFFA3_Area_Data columns */
#define AREA_X1         0       /* left cell */
#define AREA_Y1         1       /* top cell, from Text_Page_Y */
#define AREA_X2         2       /* right cell */
#define AREA_Y2         3       /* bottom cell, from Text_Page_Y */



void effect_A3_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.dir_timer = 1;
        ewk->wu.dir_step = ewk->wu.vitality;
        ewk->wu.step_xy_table = &EFF91_Step_Data[ewk->wu.direction];
        ewk->wu.move_xy_table = ewk->wu.step_xy_table;
        /* fall through */
    case R0_MOVE:
        if (--ewk->wu.dir_timer == 0) {
            effA3_cell_put(ewk);
            if (--ewk->wu.dir_step == 0) {
                if (ewk->wu.dir_old) {
                    if (--ewk->wu.hit_quake == 0) {
                        ewk->wu.routine_no[0] = R0_KILL;
                    } else {
                        ewk->wu.dir_step = ewk->wu.vitality;
                        ewk->wu.move_xy_table = ewk->wu.step_xy_table;
                    }
                } else {
                    ewk->wu.routine_no[0] = R0_KILL;
                }
            }
        }
        break;
    default:
        effA3_area_clear(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* provisional name */
void effA3_area_clear(WORK_Other* ewk) {
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    x1 = EFFA3_Area_Data[ewk->wu.kage_hx][Game_setting.Screen_Mode][AREA_X1];
    y1 = Text_Page_Y + EFFA3_Area_Data[ewk->wu.kage_hx][Game_setting.Screen_Mode][AREA_Y1];
    x2 = EFFA3_Area_Data[ewk->wu.kage_hx][Game_setting.Screen_Mode][AREA_X2];
    y2 = Text_Page_Y + EFFA3_Area_Data[ewk->wu.kage_hx][Game_setting.Screen_Mode][AREA_Y2];
    tilemap_clear_rect(x1, y1, x2, y2);
}


/* provisional name */
void effA3_cell_put(WORK_Other* ewk) {
    s16 x;
    s16 y;
    s16 rows;
    s16 cols;
    s16 code;
    s16 attr;
    ewk->wu.dir_timer = *ewk->wu.move_xy_table++;
    x = ewk->wu.vital_new;
    y = ewk->wu.vital_old;
    for (rows = ewk->wu.dmcal_m; rows > 0; rows--) {
        for (cols = ewk->wu.dm_vital; cols > 0; cols--) {
            code = *ewk->wu.move_xy_table++;
            attr = *ewk->wu.move_xy_table++;
            tilemap_put_cell(x, y, attr, code);
            x++;
        }
        y++;
        x = ewk->wu.vital_new;
    }
    ewk->wu.vital_new += ewk->wu.dmcal_d;
    ewk->wu.vital_old += ewk->wu.hit_stop;
}



s32 effect_A3_init(s16 type, s16 a, s16 b, s16 c, s16 d, s16 e, s16 f, s16 g, s16 h) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 103;
    ewk->wu.vital_new = a;
    ewk->wu.vital_old = b;
    ewk->wu.dm_vital = c;
    ewk->wu.dmcal_m = d;
    ewk->wu.dmcal_d = e;
    ewk->wu.hit_stop = f;
    ewk->wu.hit_quake = g;
    ewk->wu.kage_hx = h;
    ewk->wu.direction = EFF91_Init_Data[type][STEP_INIT_START];
    ewk->wu.dir_old = EFF91_Init_Data[type][STEP_INIT_LOOP];
    ewk->wu.vitality = EFF91_Init_Data[type][STEP_INIT_STEPS];
    return 0;
}
