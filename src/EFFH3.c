/*
 * EFFH3.C  Effect H3: ending pictures
 *
 * Effect H3: effect_H3_init loads the picture palette and graphics, homes BG2 and creates five
 * still pictures from effH3_data_tbl, which effect_H3_move draws until they are freed.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "ta_sub.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "end_main.h"
#include "effh5.h"
#include "effh6_code.h"
#include "EFFH3.h"

/* routine_no[0] */
#define R0_INIT         0       /* show the picture */
#define R0_MOVE         1       /* draw until freed */




/* char index 7 */
void effect_H3_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, 7, ewk->wu.char_index + 1, 0);
        break;
    case R0_MOVE:
        disp_pos_trans_entry(ewk);
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
}



/* char gfx 0xAC48, char table effH3_char_table */
s32 effect_H3_init(void) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    const s16* data_ptr;
    load_any_color(0x8E);
    load_char_gfx(0x7448, 1);
    bg_w.bgw[2].wxy[0].cal = bg_w.bgw[2].xy[0].cal = 0x2000000;
    bg_w.bgw[2].xy[1].cal = 0;
    bg_w.bgw[2].position_x = 512 - bg_w.pos_offset;
    bg_w.bgw[2].position_y = 0;
    end_fam_set(2);
    data_ptr = &effH3_data_tbl[0][0];
    for (i = 0; i < 5; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)((u32)frw + (ix << 11));
        ewk->wu.id = 173;
        ewk->wu.be_flag = 1;
        ewk->wu.type = i;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.char_table[0] = effH3_char_table;
        ewk->wu.my_family = 3;
        ewk->wu.my_col_code = 1;
        ewk->wu.my_priority = ewk->wu.position_z = 40;
        ewk->wu.xyz[0].disp.pos = *data_ptr++;
        ewk->wu.xyz[1].disp.pos = *data_ptr++;
        ewk->wu.char_index = *data_ptr++;
    }
    return 0;
}



