/*
 * EFFA1.C  Effect A1: a mark that slides along its row
 *
 * effect_A1_init(type, family) (nothing calls it) places mark type + 1 of eff99_char_table, scaled to
 * 20 x 20, at the left of the row effect A0 uses for that type (128 or 160 above the family's BG
 * position). effect_A1_move slides it right 8 dots a frame and frees it after 368 dots.
 */

#include "structs.h"
#include "work.h"
#include "extern.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "charmove_2.h"

extern const u32 eff99_char_table[];

void effect_A1_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case 1:
        ewk->wu.xyz[0].disp.pos += 8;
        char_move(&ewk->wu);
        if (ewk->wu.dir_timer < ewk->wu.xyz[0].disp.pos) {
            ewk->wu.routine_no[0]++;
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
        break;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}

s32 effect_A1_init(s16 type, s16 family) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 101;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.my_family = family;
    ewk->wu.position_z = 1;
    ewk->wu.char_table[0] = (u32*)eff99_char_table;
    ewk->wu.char_index = type + 1;
    ewk->wu.my_mr_flag = 1;
    ewk->wu.my_mr.size.x = 20;
    ewk->wu.my_mr.size.y = 20;
    ewk->wu.xyz[0].disp.pos = bg_w.bgw[family - 1].xy[0].disp.pos + 8;
    ewk->wu.dir_timer = ewk->wu.xyz[0].disp.pos + 368;
    if (type) {
        ewk->wu.xyz[1].disp.pos = bg_w.bgw[family - 1].xy[1].disp.pos + 128;
    } else {
        ewk->wu.xyz[1].disp.pos = bg_w.bgw[family - 1].xy[1].disp.pos + 160;
    }
    return 0;
}
