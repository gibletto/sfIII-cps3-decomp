/*
 * GAME_CONFIG_EN.C  Test-mode game configuration, English page
 *
 * game_config_menu_en runs the GAME CONFIGURATION page shown outside Japan: the same items as the
 * Japanese page, printed with the system font, with lever repeat and star gauges.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
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
#include "cmd_main_2.h"
#include "CMD_MAIN.h"
#include "cps3.h"

extern const char str_NORMAL_2[];
extern const char str_WIDE[];
extern const char str_1_ROUND[];
extern const char str_3_ROUNDS[];
extern const char str_5_ROUNDS[];
extern const char str_7_ROUNDS[];
extern const char str_OFF[];
extern const char str_1_MATCH[];

s8 Config_Item_en;
s8 Config_Exit_en;
s8 Config_Move_en;
s8 Config_Old_en;
s8 Config_New_en;
s8 Config_Org_en;
s16 Config_Attr_en;
s16 Config_Rep_Timer_en[4];
s8 Config_Rep_Count_en[4];


TM_STRING gcfg_screen_str_en[2] = {
    { 0, 0, 2, (void*)str_NORMAL_2 },
    { 0, 0, 2, (void*)str_WIDE },
};

TM_STRING gcfg_round_str_en[4] = {
    { 0, 0, 2, (void*)str_1_ROUND },
    { 0, 0, 2, (void*)str_3_ROUNDS },
    { 0, 0, 2, (void*)str_5_ROUNDS },
    { 0, 0, 2, (void*)str_7_ROUNDS },
};

TM_STRING gcfg_event_str_en[2] = {
    { 0, 0, 2, (void*)str_OFF },
    { 0, 0, 2, (void*)str_1_MATCH },
};
/* provisional name */
s32 game_config_menu_en(void) {
    void (*tbl[2])(void) = { game_config_init_en, game_config_move_en };

    tbl[Config_No_2]();
    if (Config_Exit_en) {
        return 1;
    }
    return 0;
}


/* provisional name */
void game_config_init_en(void) {
    Config_No_2++;
    Config_Exit_en = 0;
    init_render_lists();
    palette_bank_set(0);
    palette_write(0, sys_palette, 0x80);
    tilemap_chunk_copy_16b((s16*)(SS_RAM + 0x8000), (char*)sys_font_cg, 0x8C);
    tilemap_fill_all(0, 32);
    tilemap_print_string(0, 0, 0xFFFF, config_title_str_tbl);
    Config_Item_en = 4;
    Config_New_en = game_config_work.set5;
    Config_Attr_en = (Config_New_en != Game_setting.set5) ? 8 : 2;
    game_config_print_value_en(Config_Attr_en, &gcfg_event_str_en[Config_New_en]);
    Config_Item_en = 3;
    Config_New_en = game_config_work.set4;
    Config_Attr_en = (Config_New_en != Game_setting.set4) ? 8 : 2;
    game_config_print_value_en(Config_Attr_en, &gcfg_round_str_en[Config_New_en]);
    Config_Item_en = 2;
    Config_New_en = game_config_work.set3;
    Config_Attr_en = (Config_New_en != Game_setting.set3) ? 8 : 2;
    game_config_print_gauge_en(Config_New_en, 0xFFFF, Config_Attr_en);
    Config_Item_en = 1;
    Config_New_en = game_config_work.set2;
    Config_Attr_en = (Config_New_en != Game_setting.set2) ? 8 : 2;
    game_config_print_gauge_en(Config_New_en, 0xFFFF, Config_Attr_en);
    Config_Item_en = 0;
    Config_New_en = game_config_work.level;
    Config_Attr_en = (Config_New_en != Game_setting.level) ? 8 : 2;
    game_config_print_gauge_en(Config_New_en, 0xFFFF, Config_Attr_en);
    game_config_draw_cursor_en(62);
}


/* provisional name */
void game_config_move_en(void) {
    void (*Page_Tbl[6])() = { game_config_level_item_en, game_config_damage_item_en, game_config_timer_item_en, game_config_1p_round_item_en, game_config_event_item_en, game_config_exit_item_en };
    game_config_cursor_move_en();
    Page_Tbl[Config_Item_en]();
    game_config_draw_cursor_en(62);
    if (Config_Item_en == 5) {
        tilemap_print_string(0, 0, 0xFFFF, config_help_return_str_tbl);
    } else {
        tilemap_print_string(0, 0, 0xFFFF, config_help_modify_str_tbl);
    }
}


/* provisional name */
void game_config_screen_item_en(void) {
    Config_Move_en = 0;
    if (((s8)game_config_lever_repeat_en(4, 2))) {
        Config_Move_en = -1;
    } else if (((s8)game_config_lever_repeat_en(8, 3))) {
        Config_Move_en = 1;
    } else {
        if ((p1sw_0 & ~p1sw_1) & BUTTON_LP) {
            Config_Move_en = -1;
        }
        if ((p1sw_0 & ~p1sw_1) & BUTTON_MP) {
            Config_Move_en = 1;
        }
    }
    if (Config_Move_en) {
        game_config_work.mode += Config_Move_en;
        game_config_work.mode &= 1;
        Config_New_en = game_config_work.mode;
        if (game_config_work.mode) {
            set_screen_mode(7);
        } else {
            set_screen_mode(3);
        }
        Config_Attr_en = (Config_New_en != Game_setting.mode) ? 8 : 2;
        game_config_print_value_en(Config_Attr_en, &gcfg_screen_str_en[Config_New_en]);
    }
}


/* provisional name */
void game_config_level_item_en(void) {
    Config_Move_en = 0;
    if (game_config_lever_repeat_en(4, 2)) {
        Config_Move_en = -1;
    } else if (game_config_lever_repeat_en(8, 3)) {
        Config_Move_en = 1;
    } else {
        if ((p1sw_0 & ~p1sw_1) & BUTTON_LP) {
            Config_Move_en = -1;
        }
        if ((p1sw_0 & ~p1sw_1) & BUTTON_MP) {
            Config_Move_en = 1;
        }
    }
    if (Config_Move_en) {
        Config_Old_en = game_config_work.level;
        game_config_work.level += Config_Move_en;
        if (game_config_work.level < 0) {
            game_config_work.level = 7;
        }
        if (game_config_work.level > 7) {
            game_config_work.level = 0;
        }
        Config_New_en = game_config_work.level;
        Config_Attr_en = Config_New_en != Game_setting.level ? 8 : 2;
        game_config_print_gauge_en(Config_New_en, Config_Old_en, Config_Attr_en);
    }
}


/* provisional name */
void game_config_damage_item_en(void) {
    Config_Move_en = 0;
    if (game_config_lever_repeat_en(4, 2)) {
        Config_Move_en = -1;
    } else if (game_config_lever_repeat_en(8, 3)) {
        Config_Move_en = 1;
    } else {
        if ((p1sw_0 & ~p1sw_1) & BUTTON_LP) {
            Config_Move_en = -1;
        }
        if ((p1sw_0 & ~p1sw_1) & BUTTON_MP) {
            Config_Move_en = 1;
        }
    }
    if (Config_Move_en) {
        Config_Old_en = game_config_work.set2;
        game_config_work.set2 += Config_Move_en;
        game_config_work.set2 &= 3;
        Config_New_en = game_config_work.set2;
        Config_Attr_en = Config_New_en != Game_setting.set2 ? 8 : 2;
        game_config_print_gauge_en(Config_New_en, Config_Old_en, Config_Attr_en);
    }
}


/* provisional name */
void game_config_timer_item_en(void) {
    Config_Move_en = 0;
    if (game_config_lever_repeat_en(4, 2)) {
        Config_Move_en = -1;
    } else if (game_config_lever_repeat_en(8, 3)) {
        Config_Move_en = 1;
    } else {
        if ((p1sw_0 & ~p1sw_1) & BUTTON_LP) {
            Config_Move_en = -1;
        }
        if ((p1sw_0 & ~p1sw_1) & BUTTON_MP) {
            Config_Move_en = 1;
        }
    }
    if (Config_Move_en) {
        Config_Old_en = game_config_work.set3;
        game_config_work.set3 += Config_Move_en;
        game_config_work.set3 &= 3;
        Config_New_en = game_config_work.set3;
        Config_Attr_en = Config_New_en != Game_setting.set3 ? 8 : 2;
        game_config_print_gauge_en(Config_New_en, Config_Old_en, Config_Attr_en);
    }
}


/* provisional name */
/* provisional name */
void game_config_1p_round_item_en(void) {
    Config_Move_en = 0;
    if (((s8)game_config_lever_repeat_en(4, 2))) {
        Config_Move_en = -1;
    } else if (((s8)game_config_lever_repeat_en(8, 3))) {
        Config_Move_en = 1;
    } else {
        if ((p1sw_0 & ~p1sw_1) & BUTTON_LP) {
            Config_Move_en = -1;
        }
        if ((p1sw_0 & ~p1sw_1) & BUTTON_MP) {
            Config_Move_en = 1;
        }
    }
    if (Config_Move_en) {
        game_config_work.set4 += Config_Move_en;
        game_config_work.set4 &= 3;
        Config_New_en = game_config_work.set4;
        Config_Attr_en = (Config_New_en != Game_setting.set4) ? 8 : 2;
        game_config_print_value_en(Config_Attr_en, &gcfg_round_str_en[Config_New_en]);
    }
}


void game_config_event_item_en(void) {
    Config_Move_en = 0;
    if (((s8)game_config_lever_repeat_en(4, 2))) {
        Config_Move_en = -1;
    } else if (((s8)game_config_lever_repeat_en(8, 3))) {
        Config_Move_en = 1;
    } else {
        if ((p1sw_0 & ~p1sw_1) & BUTTON_LP) {
            Config_Move_en = -1;
        }
        if ((p1sw_0 & ~p1sw_1) & BUTTON_MP) {
            Config_Move_en = 1;
        }
    }
    if (Config_Move_en) {
        game_config_work.set5 += Config_Move_en;
        game_config_work.set5 &= 1;
        Config_New_en = game_config_work.set5;
        Config_Attr_en = (Config_New_en != Game_setting.set5) ? 8 : 2;
        game_config_print_value_en(Config_Attr_en, &gcfg_event_str_en[Config_New_en]);
    }
}


/* provisional name */


/* provisional name */
void game_config_exit_item_en(void) {
    if ((~p1sw_1 & p1sw_0) & BUTTON_LP) {
        Config_Exit_en = 1;
    }
}


/* provisional name */
s8 game_config_lever_repeat_en(u16 sw, s16 ix) {
    if (~p1sw_1 & p1sw_0 & sw) {
        return 1;
    }
    if (p1sw_0 & sw) {
        Config_Rep_Timer_en[ix]++;
        if (Config_Rep_Timer_en[ix] > 10) {
            Config_Rep_Count_en[ix]++;
            if (Config_Rep_Count_en[ix] > 8) {
                Config_Rep_Count_en[ix] = 0;
                return 1;
            }
        }
    } else {
        Config_Rep_Timer_en[ix] = 0;
        Config_Rep_Count_en[ix] = 0;
    }
    return 0;
}


/* provisional name */
void game_config_cursor_move_en(void) {
    game_config_draw_cursor_en(32);
    if (((s8)game_config_lever_repeat_en(1, 0))) {
        Config_Item_en--;
        if (Config_Item_en < 0) {
            Config_Item_en = 5;
        }
    } else if (((s8)game_config_lever_repeat_en(2, 1))) {
        Config_Item_en++;
        if (Config_Item_en > 5) {
            Config_Item_en = 0;
        }
    }
}


/* provisional name */
void game_config_draw_cursor_en(s16 code) {
    s32 y;

    y = Config_Item_en;
    y += y;
    y += 4;
    tilemap_put_block(1, y, 2, code);
}

/* provisional name */
void game_config_print_gauge_en(u32 x, u32 old_x, s16 attr) {
    s32 y;
    u16 ix;

    y = Config_Item_en;
    y += y;
    ix = x;
    y += 4;
    x += 0x1D;
    if ((u16)old_x != 0xFFFF) {
        old_x += 0x1D;
        tilemap_put_block(old_x, y, 2, gcfg_gauge_clr_chr_en);
    }
    tilemap_put_block(x, y, attr, gcfg_gauge_chr_en[ix]);
}


/* provisional name */
void game_config_print_value_en(s16 attr, const TM_STRING* str) {
    s32 y;

    y = Config_Item_en;
    y += y;
    y += 4;
    ((void(*)(s32 x, s32 y, s32 attr, const TM_STRING* str))tilemap_print_string)(24, y, attr, str);
}
