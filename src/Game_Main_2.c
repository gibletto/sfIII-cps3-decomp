/*
 * GAME_MAIN_2.C  Operator text position for the screen mode
 *
 * tilemap_print_string_origin prints a string at the text origin; Set_Mode_Pos and
 * Set_Mode_Pos_copy place operator text for the current screen mode.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "Entry.h"
#include "entry_2.h"
#include "end_main.h"
#include "aboutspr.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "demo00.h"
#include "demo01.h"
#include "demo02_code.h"
#include "RANKING.h"
#include "Manage.h"
#include "manage_2.h"
#include "win_2.h"
#include "next_cpu.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sc_trans.h"
#include "cmb_win.h"
#include "VITAL.h"
#include "count.h"
#include "spgauge.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLCNTDAT.h"
#include "plcntdat_2.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "EFFM7.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "HITCHECK.h"
#include "cmb_cont.h"
#include "eff35.h"
#include "eff56.h"
#include "eff57.h"
#include "EFF58.h"
#include "SLOWF.h"
#include "sc_sub.h"
#include "sc_sub_2.h"
#include "bg000.h"
#include "ta_sub2.h"
#include "tate00.h"
#include "ta_sub.h"
#include "Game_Main.h"
#include "eeprom.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "lose_pl.h"
#include "PLS02.h"

/* provisional name */
void tilemap_print_string_origin(str)
TM_STRING* str;
{
    tilemap_print_string(0, 0, 0xFFFF, str);
}



/* provisional name */
void Set_Mode_Pos_copy(s16* value, s16 add, s16 init) {
    *value = init;
    if (Game_setting.mode) {
        *value += add;
    }
}



/* provisional name */
void Set_Mode_Pos(s16* value, s16 add, s16 init) {
    *value = init;
    if (Game_setting.mode) {
        *value += add;
    }
}
