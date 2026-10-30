/*
 * IOTEST_OUT.C  Test mode: output test page
 *
 * iotest_output_toggle and iotest_output_page are the lamp and coin counter output test page.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "eeprom.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "sys_test_2.h"
#include "cps3.h"

s16 iotest_out1_flag;  /* 0206A1E4 */
s16 iotest_out2_flag;  /* 0206A1E6 */
s32 iotest_hold_flag;  /* 0206A1E8 */
s16 iotest_save_flip;  /* 0206A1EC */


s16 iotest_out_no = 0;  /* 02007C94 */



/* provisional name */
void iotest_output_toggle(void) {
    register u16 trig1;
    register u16 trig2;
    register s32 unused;
    trig1 = ~p1sw_1 & p1sw_0;
    trig2 = ~p2sw_1 & p2sw_0;
    if (trig1 & BUTTON_LP) {
        if (iotest_out1_flag != 0) {
            iotest_out1_flag = 0;
        } else {
            iotest_out1_flag = 1;
        }
        if (iotest_out1_flag != 0) {
            coin_out_latch |= 1;
        } else {
            coin_out_latch &= ~1;
        }
    }
    if (trig2 & BUTTON_LP) {
        if (iotest_out2_flag != 0) {
            iotest_out2_flag = 0;
        } else {
            iotest_out2_flag = 1;
        }
        if (iotest_out2_flag != 0) {
            coin_out_latch |= 2;
        } else {
            coin_out_latch &= ~2;
        }
    }
    if ((p1sw_0 & BUTTON_MP) == BUTTON_MP && (p1sw_1 & BUTTON_MP) != BUTTON_MP) {
        iotest_hold_flag = 1;
        coin_out_latch |= 0x10;
        coin_out_latch |= 0x20;
    } else if ((p1sw_0 & BUTTON_MP) != BUTTON_MP && (p1sw_1 & BUTTON_MP) == BUTTON_MP) {
        iotest_hold_flag = 0;
        coin_out_latch &= ~0x10;
        coin_out_latch &= ~0x20;
    } else if ((p2sw_0 & BUTTON_MP) != BUTTON_MP && (p2sw_1 & BUTTON_MP) == BUTTON_MP) {
        if (Card_Dispenser != 0) {
            card_out_req++;
        }
    }
}



/* provisional name */
s32 iotest_output_page(void) {
    register s32 rc;
    /* Draw the output test page. */
    switch (iotest_out_no) {
    case 0:
        tilemap_fill_all(0, 32);
        tilemap_print_string(0, 0, 0xFFFF, iotest_output_scr);
        if (Card_Dispenser != 0) {
            tilemap_print_string(0, 0, 0xFFFF, iotest_dispenser_str);
        }
        iotest_hold_flag = 0;
        iotest_out1_flag = iotest_out2_flag = 0;
        iotest_save_flip = Monitor_Flip;
        iotest_out_no++;
        break;
    case 1:
        iotest_output_toggle();
        break;
    }
    if ((p1sw_0 & BUTTON_START) && (p1sw_0 & BUTTON_LP)) {
        rc = -1;
        iotest_out_no = 0;
        Monitor_Flip = iotest_save_flip;
        coin_out_latch &= ~1;
        coin_out_latch &= ~2;
        coin_out_latch &= ~0x10;
        coin_out_latch &= ~0x20;
        if (iotest_hold_flag != 0) {
            coin_out_latch &= ~0x10;
            coin_out_latch &= ~0x20;
        }
        return rc;
    }
    rc = 0;
    return rc;
}
