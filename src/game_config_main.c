/*
 * game_config_main.c  Game configuration menu dispatch
 *
 * One routine called from gameconfig_page in the configuration test menu (sys_config.c).
 * For Country 1 it steps the Japanese-language settings screen through Setting_Tbl
 * (game_config_init_jp, then game_config_move_jp) and reports exit when Config_Exit_jp is
 * set; for the other regions it runs the English menu, game_config_menu_en. Returns 1 when the
 * operator leaves the page so the caller can apply and save the new settings.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CMD_MAIN.h"
#include "cmd_main_2.h"
#include "game_config_main.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "Com_Pl.h"
#include "aboutspr.h"
#include "SYS_sub.h"
#include "CALDIR.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFF00.h"
#include "EFF02.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "PLS01.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "fifo.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "bg000.h"
#include "HITCHECK.h"
#include "PLCNTDAT.h"
#include "plcntdat_2.h"
#include "cps3.h"



/* provisional name */
s8 game_config_main(void) {
    void (*Setting_Tbl[2])() = { game_config_init_jp, game_config_move_jp };

    if (Country == 1) {
        Setting_Tbl[Config_No_2]();
        if (Config_Exit_jp) {
            return 1;
        }
        return 0;
    } else {
        if (game_config_menu_en()) {
            return 1;
        }
        return 0;
    }
}



s32 game_config_menu(void) {
    void (*Setting_Tbl[2])() = { game_config_init_jp, game_config_move_jp };
    if (Country == 1) {
        Setting_Tbl[Config_No_2]();
    } else {
        game_config_menu_en();
    }
    if (Config_Exit_jp) {
        return 1;
    }
    return 0;
}



