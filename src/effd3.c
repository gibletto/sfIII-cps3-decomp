/*
 * EFFD3.C  Effect D3: special finish screens
 *
 * effect_D3 runs the special finish screen (created from PLCNTSET): it flashes a sequence of BG3
 * pictures on the timings of ake_timer_tbl with the other BG layers off, then turns them back on.
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
#include "SYS_sub.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "aboutspr.h"
#include "eff20.h"
#include "effg8.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "Manage.h"
#include "manage_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "effd3.h"



void effect_D3_move(WORK_Other* ewk) {
    s16 i;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0] += 1;
        ewk->wu.old_rno[1] = 0;
        ewk->wu.dir_timer = ake_timer_tbl[0];
        ewk->wu.old_rno[0] = 64;
        ewk->wu.old_rno[2] = 0;
        ewk->wu.disp_flag = 0;
        for (i = 0; i < bg_w.scno; i++) {
            Bg_Off_R(1 << i);
        }
        Bg_On_R(8);
        akebono_flag = 1;
        Sound_SE(117);
        scrn_map_set(3, ake_scrl_w[1].adrs);
        Scrn_Move_Set(3, ake_pos_tbl[0][0] - bg_w.pos_offset, ake_pos_tbl[0][1]);
        Bg_Off_R(0x80);
        break;
    case 1:
        ewk->wu.dir_timer -= 1;
        if (ewk->wu.dir_timer < 0) {
            ewk->wu.old_rno[1] += 1;
            if (ewk->wu.old_rno[1] < ewk->wu.old_rno[0]) {
                ewk->wu.old_rno[2] += 1;
                ewk->wu.old_rno[2] &= 3;
                ewk->wu.dir_timer = ake_timer_tbl[ewk->wu.old_rno[1]];
                for (i = 0; i < bg_w.scno; i++) {
                    Bg_Off_W(1 << i);
                }
                Bg_On_W(8);
                akebono_flag = 1;
            } else {
                ewk->wu.routine_no[0] += 1;
                ewk->wu.old_rno[0] = 8;
                ewk->wu.old_rno[1] = 0;
                for (i = 0; i < bg_w.scno; i++) {
                    Bg_On_W(1 << i);
                }
                if (scrn_reg_w[3].ctrl & 0x8000) {
                    Bg_Off_W(8);
                }
                akebono_flag = 0;
            }
        }
        scrn_map_set(3, ake_scrl_w[1].adrs);
        bg_w.bgw[3].position_x = ake_pos_tbl[ewk->wu.old_rno[2]][0] - bg_w.pos_offset;
        bg_w.bgw[3].position_y = ake_pos_tbl[ewk->wu.old_rno[2]][1];
        ake_Family_Set();
        break;
    default:
        akebono_flag = 0;
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_D3_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.id = 133;
    ewk->wu.be_flag = 1;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.old_rno[1] = 0;
    return 0;
}
