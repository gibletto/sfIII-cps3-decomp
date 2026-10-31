/*
 * EFFE3.C  Effect E3: super art flash background
 *
 * effect_E3_init (from tate00.c) creates the effect and clears Flash_MT. While a player's Flash_MT is
 * set, effect_E3_move swaps the stage for a single BG 3 picture: it turns the stage layers off and BG 3
 * on, holds it for the time in effE3_data while effE3_scroll_set positions BG 3 and family 4, then
 * restores the layers and clears the request; sa_pa_flag is set meanwhile. It ends for the finish
 * screen (akebono_flag) and leaves the layers to the alternate background while it is up
 * (seraph_flag).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "fifo.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "effe3.h"

/* routine_no[0] */
#define R0_WAIT         0       /* wait for a request, then switch */
#define R0_HOLD         1       /* hold for the flash time */
#define R0_RESTORE      2       /* restore the stage layers */
#define R0_KILL         99      /* (default) put the work back */

/* effE3_data columns */
#define E3_BG_X         0       /* BG3 x position */
#define E3_BG_Y         1       /* BG3 y position */
#define E3_TIME         2       /* frames the picture is held */




void effect_E3_move(WORK_Other* ewk) {
    s16 i;
    if (akebono_flag) {
        ewk->wu.routine_no[0] = R0_KILL;
        sa_pa_flag = 0;
    }
    switch (ewk->wu.routine_no[0]) {
    case R0_WAIT:
        if (!Flash_MT[0] && !Flash_MT[1]) {
            break;
        }
        sa_pa_flag = 1;
        ewk->wu.routine_no[0]++;
        for (i = 0; i < bg_w.scno; i++) {
            if (scrn_reg_w[i].ctrl & 0x8000) {
                Bg_Off_W(1 << i);
            }
        }
        if (!(scrn_reg_w[3].ctrl & 0x8000)) {
            Bg_On_W(8);
        }
        if (Flash_MT[0]) {
            ewk->wu.old_rno[0] = effE3_data[Flash_MT[0]][E3_TIME];
            ewk->master_id = 0;
        } else {
            ewk->wu.old_rno[0] = effE3_data[Flash_MT[1]][E3_TIME];
            ewk->master_id = 1;
        }
        effE3_scroll_set(ewk);
        return;
        break;
    case R0_HOLD:
        ewk->wu.old_rno[0]--;
        if (ewk->wu.old_rno[0] <= 0) {
            sa_pa_flag = 0;
            ewk->wu.routine_no[0]++;
            break;
        } else {
            effE3_scroll_set(ewk);
        }
        break;
    case R0_RESTORE:
        ewk->wu.routine_no[0] = R0_WAIT;
        Flash_MT[ewk->master_id] = 0;
        if (akebono_flag) {
            return;
        }
        if (seraph_flag) {
            return;
        }
        for (i = 0; i < bg_w.scno; i++) {
            if (!(scrn_reg_w[i].ctrl & 0x8000)) {
                Bg_On_W(1 << i);
            }
        }
        if (scrn_reg_w[3].ctrl & 0x8000) {
            Bg_Off_W(8);
        }
        return;
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
}

/* provisional name */
void effE3_scroll_set(WORK_Other* ewk) {
    s32 x = effE3_data[Flash_MT[ewk->master_id]][E3_BG_X] - bg_w.pos_offset;
    s32 y = effE3_data[Flash_MT[ewk->master_id]][E3_BG_Y];
    scrn_map_set(3, ake_scrl_w[2].adrs);
    Scrn_Move_Set(3, x, y);
    x = -x & 0x3FF;
    y = (0x300 - (y & 0x3FF)) & 0x3FF;
    Family_Set_W(4, x, y);
}


s32 effect_E3_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.id = 143;
    ewk->wu.be_flag = 1;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    Flash_MT[0] = Flash_MT[1] = 0;
    return 0;
}
