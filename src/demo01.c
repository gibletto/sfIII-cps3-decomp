/*
 * DEMO01.C  Attract mode: title
 *
 * Title and Title_At_a_Dash run the title sequence and opening.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Game_Main.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "Entry.h"
#include "entry_2.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "SYS_sub.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "cmb_win.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "eeprom.h"
#include "sc_trans.h"
#include "bg000.h"
#include "lose_pl.h"
#include "PLS02.h"
#include "SLOWF.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "demo01.h"
#include "demo02_code.h"

void SF3_logo(s16 y);



/* title palettes and opening sequence */
s32 Title(void) {
    switch (D_No1) {
    case 0:
        D_No1++;
        D_Timer = 10;
        wipe_pattern_set(0, 7, 0);
        tilemap_fill_all(0, 32);
        System_all_clear_Wait();
        load_any_color(130);
        load_any_color(2);
        Text_Page_Y = 32;
        Scrn_Move_Set(4, 0, 0x100);
        E_No1 = 1;
        op_w.r_no_0 = 0;
        op_w.r_no_1 = 0;
        op_w.r_no_2 = 0;
        op_w.mv_ctr = 0;
        break;
    case 1:
        if (opening_demo_tick()) {
            D_No1++;
            D_Timer = 40;
        }
        break;
    case 2:
        if (--D_Timer == 0) {
            D_No1++;
            Setup_Demo_PL();
            Setup_Demo_Arts();
            Setup_Demo_Stage();
            SF3_logo(0);
            sc_vram_to_ram();
            Switch_Screen_Init(0, 1);
        }
        break;
    case 3:
        if (Switch_Screen()) {
            D_No1++;
            Cover_Timer = 22;
            Scrn_Move_Set(4, 0, 0);
        }
        break;
    default:
        return 1;
    }
    return 0;
}



/* palettes 130 and 2 */
s32 Title_At_a_Dash(void) {
    switch (D_No1) {
    case 0:
        D_No1++;
        Scrn_Move_Set(4, 0, 0);
        System_all_clear_Wait();
        load_any_color(130);
        load_any_color(2);
        op_w.r_no_0 = 21;
        op_w.mv_ctr = op_w.r_no_2 = op_w.r_no_1 = 0;
        break;
    case 1:
        if (opening_demo_tick()) {
            D_No1++;
            D_Timer = 16;
            credit_display_render(1);
            Disp_Start_Message();
        }
        break;
    default:
        if (--D_Timer == 0) {
            ToneDown(0);
            return 1;
        }
        break;
    }
    return 0;
}
