/*
 * EFFF4.C  Effect F4: BG3 flash
 *
 * Effect F4 flashes the screen between the normal scroll layers and BG3: on its first frame it
 * shows only BG3, then toggles the layers every frame for old_rno[0] frames and restores the
 * normal layers, keeping the BG3 sprite slot and position set each frame. akebono_flag cuts the
 * flash short. effect_F4_init is an empty stub.
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
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFF4.h"

/* routine_no[0] */
#define R0_INIT         0       /* show only BG 3 */
#define R0_FLASH        1       /* swap the layers every frame */
#define R0_KILL         2       /* (default) put the work back */

void effect_F4_move(WORK_Other* ewk) {
    s16 i;
    if (akebono_flag) {
        ewk->wu.old_rno[0] = -1;
    }
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        for (i = 0; i < bg_w.scno; i++) {
            Bg_Off_R(1 << i);
        }
        Bg_On_R(8);
        ewk->wu.disp_flag = 1;
        scrn_map_set_now(3, (u32)bg_w.bgw[3].bg_address);
        Scrn_Move_Set_R(3, 0x100 - bg_w.pos_offset, 0x200);
        break;
    case R0_FLASH:
        ewk->wu.old_rno[0]--;
        if (ewk->wu.old_rno[0] > 0) {
            ewk->wu.disp_flag ^= 1;
            if (ewk->wu.disp_flag) {
                for (i = 0; i < bg_w.scno; i++) {
                    Bg_Off_R(1 << i);
                }
                Bg_On_R(8);
            } else {
                for (i = 0; i < bg_w.scno; i++) {
                    Bg_On_R(1 << i);
                }
                Bg_Off_R(8);
            }
        } else {
            ewk->wu.routine_no[0]++;
            for (i = 0; i < bg_w.scno; i++) {
                Bg_On_R(1 << i);
            }
            Bg_Off_R(8);
        }
        scrn_map_set_now(3, (u32)bg_w.bgw[3].bg_address);
        Scrn_Move_Set_R(3, 0x100 - bg_w.pos_offset, 0x200);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



void effect_F4_init(WORK_Other* ewk) {}


/* provisional name */
void effect_F4_dummy(void) {}
