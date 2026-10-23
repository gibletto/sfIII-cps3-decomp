/*
 * EFFC8.C  Effect C8: entrance prop that follows the player's animation
 *
 * effect_C8_init is called by the entrance routine Appear_07000 (appear.c) and creates a sprite
 * at the player's position with the player's palette (etc_char_table). effect_C8_move keeps its
 * frame in step with the player's entrance animation (cg_ix) while the entrance runs; when the
 * entrance reaches its last step the prop is thrown clear, 61 dots to the side, with speeds from
 * effc8_data_tbl, and it is hidden and freed when its pattern ends.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "EFFC8.h"



/* case 3 not gated by EXE_flag/Game_pause, drawn only while it runs */
void effect_C8_move(WORK_Other* ewk) {
    PLW* oya_pl = (PLW*)ewk->my_master;
    s16 work;
    const s32* ptr;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 12);
        break;
    case 1:
        switch (oya_pl->wu.routine_no[3]) {
        case 1:
            break;
        case 0:
        case 2:
            if (oya_pl->wu.cg_ix != ewk->wu.cg_ix) {
                work = oya_pl->wu.cg_ix / oya_pl->wu.cgd_type + 1;
                set_char_move_init2(&ewk->wu, 0, 12, work + 1, 0);
                ewk->wu.cg_ix = oya_pl->wu.cg_ix;
            }
            break;
        case 3:
            ewk->wu.routine_no[0]++;
            break;
        }
        pl_eff_trans_entry(ewk);
        break;
    case 2:
        ewk->wu.routine_no[0]++;
        set_char_move_init(&ewk->wu, 0, 13);
        ptr = effc8_data_tbl;
        if (oya_pl->wu.id) {
            ewk->wu.xyz[0].disp.pos += 61;
            ewk->wu.mvxy.a[0].sp = *ptr++;
            ewk->wu.mvxy.d[0].sp = *ptr++;
            ewk->wu.mvxy.a[1].sp = *ptr++;
            ewk->wu.mvxy.d[1].sp = *ptr++;
        } else {
            ewk->wu.xyz[0].disp.pos -= 61;
            ewk->wu.mvxy.a[0].sp = -*ptr;
            ptr++;
            ewk->wu.mvxy.d[0].sp = -*ptr;
            ptr++;
            ewk->wu.mvxy.a[1].sp = *ptr++;
            ewk->wu.mvxy.d[1].sp = *ptr++;
        }
        ewk->wu.xyz[1].disp.pos = 137;
        pl_eff_trans_entry(ewk);
        break;
    case 3:
        add_x_sub(ewk);
        add_y_sub(ewk);
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[0]++;
        }
        pl_eff_trans_entry(ewk);
        break;
    case 4:
        break;
    case 5:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_C8_init(PLW* wk) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(2)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 128;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_family = 2;
    ewk->wu.rl_flag = wk->wu.rl_flag;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_priority = ewk->wu.position_z = 20;
    *ewk->wu.char_table = etc_char_table;
    ewk->wu.my_col_code = wk->wu.my_col_code;
    ewk->my_master = (u32*)wk;
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = wk->wu.xyz[0].disp.pos;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = wk->wu.xyz[1].disp.pos;
    ewk->wu.xyz[0].disp.low = ewk->wu.xyz[1].disp.low = 0;
    return 0;
}
