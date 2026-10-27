/*
 * SYS_CONFIG_2.C  Test-mode configuration menu
 *
 * The configuration menu of test mode (config_menu_*, sysconfig_* and gameconfig_page) lets the
 * operator change coin and chute settings, continue, monitor, demo sound, sound mode, voice type,
 * card dispenser, win points and extra options, then save and exit.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CMD_MAIN.h"
#include "cmd_main_2.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "eeprom.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "cram_bank.h"
#include "game_config_main.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "cps3.h"

extern const TM_STRING chute_mode_str_tbl_0[];
extern const TM_STRING chute_mode_str_tbl_1[];
extern const TM_STRING chute_mode_str_tbl_10[];
extern const TM_STRING chute_mode_str_tbl_11[];
extern const TM_STRING chute_mode_str_tbl_2[];
extern const TM_STRING chute_mode_str_tbl_3[];
extern const TM_STRING chute_mode_str_tbl_4[];
extern const TM_STRING chute_mode_str_tbl_5[];
extern const TM_STRING chute_mode_str_tbl_6[];
extern const TM_STRING chute_mode_str_tbl_7[];
extern const TM_STRING chute_mode_str_tbl_8[];
extern const TM_STRING chute_mode_str_tbl_9[];
extern const TM_STRING coin_setting_str_tbl_0[];
extern const TM_STRING coin_setting_str_tbl_1[];
extern const TM_STRING coin_setting_str_tbl_10[];
extern const TM_STRING coin_setting_str_tbl_11[];
extern const TM_STRING coin_setting_str_tbl_12[];
extern const TM_STRING coin_setting_str_tbl_13[];
extern const TM_STRING coin_setting_str_tbl_14[];
extern const TM_STRING coin_setting_str_tbl_15[];
extern const TM_STRING coin_setting_str_tbl_16[];
extern const TM_STRING coin_setting_str_tbl_17[];
extern const TM_STRING coin_setting_str_tbl_18[];
extern const TM_STRING coin_setting_str_tbl_2[];
extern const TM_STRING coin_setting_str_tbl_3[];
extern const TM_STRING coin_setting_str_tbl_4[];
extern const TM_STRING coin_setting_str_tbl_5[];
extern const TM_STRING coin_setting_str_tbl_6[];
extern const TM_STRING coin_setting_str_tbl_7[];
extern const TM_STRING coin_setting_str_tbl_8[];
extern const TM_STRING coin_setting_str_tbl_9[];
extern const TM_STRING monitor_str_tbl_1[];
extern const TM_STRING on_off_str_tbl_0[];
extern const TM_STRING on_off_str_tbl_1[];
extern const TM_STRING sound_mode_str_tbl_0[];
extern const TM_STRING sound_mode_str_tbl_1[];
extern const TM_STRING sound_mode_str_tbl_2[];
extern const TM_STRING sound_mode_str_tbl_3[];
extern const TM_STRING sound_mode_str_tbl_4[];
extern const TM_STRING sound_mode_str_tbl_5[];

s8 cfg_top_cursor;  /* 0206AC74 */
s8 cfg_coin;  /* 0206AC75 */
s8 cfg_continue;  /* 0206AC76 */
s8 cfg_chute;  /* 0206AC77 */
s8 cfg_sound_mode;  /* 0206AC78 */
s8 cfg_demo_sound;  /* 0206AC79 */
s8 cfg_flip_old;  /* 0206AC7A */
s8 cfg_free_play;  /* 0206AC7B */
s8 cfg_coin_special;  /* 0206AC7C */
s8 cfg_cont_forced;  /* 0206AC7D */
s8 cfg_changed;  /* 0206AC7E */
s8 cfg_voice;  /* 0206AC7F */
s8 cfg_dispenser;  /* 0206AC80 */
s8 cfg_win_point;  /* 0206AC81 */
s8 cfg_win_point_vs;  /* 0206AC82 */
s8 cfg_extra;  /* 0206AC83 */
u8 cfg_extra_tail[1];  /* after cfg_extra; nothing refers to it by name or address */
s8 cfg_cursor;  /* 0206AC85 */
s8 cfg_cursor_old;  /* 0206AC86 */
s8 cfg_coin_step;  /* 0206AC87 */
s8 cfg_coin_sel;  /* 0206AC88 */
s8 cfg_reserve;  /* 0206AC89 */
s32 cfg_item_max;  /* 0206AC8C */

void tilemap_put_block(u16 x, u16 y, u16 attr, u16 code);



s8 event_off_flag = 1;  /* 02007D50 */



const TM_STRING* coin_setting_str_tbl[19] = {
    coin_setting_str_tbl_0,
    coin_setting_str_tbl_1,
    coin_setting_str_tbl_2,
    coin_setting_str_tbl_3,
    coin_setting_str_tbl_4,
    coin_setting_str_tbl_5,
    coin_setting_str_tbl_6,
    coin_setting_str_tbl_7,
    coin_setting_str_tbl_8,
    coin_setting_str_tbl_9,
    coin_setting_str_tbl_10,
    coin_setting_str_tbl_11,
    coin_setting_str_tbl_12,
    coin_setting_str_tbl_13,
    coin_setting_str_tbl_14,
    coin_setting_str_tbl_15,
    coin_setting_str_tbl_16,
    coin_setting_str_tbl_17,
    coin_setting_str_tbl_18,
};



const TM_STRING* chute_mode_str_tbl[12] = {
    chute_mode_str_tbl_0,
    chute_mode_str_tbl_1,
    chute_mode_str_tbl_2,
    chute_mode_str_tbl_3,
    chute_mode_str_tbl_4,
    chute_mode_str_tbl_5,
    chute_mode_str_tbl_6,
    chute_mode_str_tbl_7,
    chute_mode_str_tbl_8,
    chute_mode_str_tbl_9,
    chute_mode_str_tbl_10,
    chute_mode_str_tbl_11,
};



const TM_STRING* on_off_str_tbl[2] = {
    on_off_str_tbl_0,
    on_off_str_tbl_1,
};



const TM_STRING* sound_mode_str_tbl[2] = {
    sound_mode_str_tbl_0,
    sound_mode_str_tbl_1,
};



const TM_STRING* language_str_tbl[3] = {
    sound_mode_str_tbl_2,
    sound_mode_str_tbl_3,
    sound_mode_str_tbl_4,
};



const TM_STRING* voice_type_str_tbl[2] = {
    sound_mode_str_tbl_5,
    on_off_str_tbl_0,
};



const TM_STRING* monitor_str_tbl[2] = {
    sound_mode_str_tbl_5,
    monitor_str_tbl_1,
};






void (*config_menu_tbl[2])(void) = {
    config_menu_init,
    config_menu_dispatch,
};



void (*config_page_tbl[3])(void) = {
    config_top_page,
    sysconfig_page,
    gameconfig_page,
};



void (*config_top_step_tbl[2])(void) = {
    config_top_draw,
    config_top_select,
};



void (*config_top_item_tbl[4])(void) = {
    config_top_system,
    config_top_game,
    config_top_default,
    config_top_save_exit,
};



void (*sysconfig_step_tbl[2])(void) = {
    sysconfig_draw,
    sysconfig_select,
};



void (*sysconfig_item_tbl[7])(void) = {
    sysconfig_coin,
    sysconfig_chute_mode,
    sysconfig_continue,
    sysconfig_monitor,
    sysconfig_demo_sound,
    sysconfig_sound_mode,
    sysconfig_exit,
};



void (*sysconfig_item_tbl_b[8])(void) = {
    sysconfig_coin,
    sysconfig_chute_mode,
    sysconfig_continue,
    sysconfig_monitor,
    sysconfig_demo_sound,
    sysconfig_sound_mode,
    sysconfig_language,
    sysconfig_exit,
};



void (*sysconfig_item_card_tbl[9])(void) = {
    sysconfig_coin,
    sysconfig_chute_mode,
    sysconfig_continue,
    sysconfig_monitor,
    sysconfig_demo_sound,
    sysconfig_sound_mode,
    sysconfig_dispenser,
    sysconfig_win_point,
    sysconfig_exit,
};



void (*sysconfig_item_tbl_c[8])(void) = {
    sysconfig_coin,
    sysconfig_chute_mode,
    sysconfig_continue,
    sysconfig_monitor,
    sysconfig_demo_sound,
    sysconfig_sound_mode,
    sysconfig_voice_type_toggle,
    sysconfig_exit,
};



void (*sysconfig_item_card_tbl2[10])(void) = {
    sysconfig_coin,
    sysconfig_chute_mode,
    sysconfig_continue,
    sysconfig_monitor,
    sysconfig_demo_sound,
    sysconfig_sound_mode,
    sysconfig_dispenser,
    sysconfig_win_point,
    sysconfig_win_point_human,
    sysconfig_exit,
};



s8 config_menu_run(void)
{
  config_menu_tbl[Config_No_0]();
  return cfg_reserve;
}



void config_menu_init(void) {
    s32 i;
    u32 table;
    u32 dst;
    s8* src;
    Config_No_0++;
    Config_No_1 = 0;
    Config_No_2 = 0;
    cfg_top_cursor = 0;
    cfg_cont_forced = 0;
    cfg_reserve = 0;
    cfg_coin_special = Free_Play;
    cfg_coin = Coin_Mode;
    cfg_continue = Continue_Flag;
    cfg_free_play = Two_Coin_Start;
    cfg_sound_mode = Sound_Mode;
    cfg_voice = Language;
    cfg_flip_old = Monitor_Flip;
    cfg_demo_sound = Demo_Sound;
    cfg_chute = Chute_Mode;
    cfg_dispenser = ((s8)Card_Dispenser);
    cfg_win_point = Win_Point_Com;
    cfg_win_point_vs = Win_Point_Human;
    cfg_extra = Voice_Type;
    dst = (u32)&game_config_work;
    src = (s8 *)&Game_setting;
    for (i = 0; i < 16; i++) {
        *(u8*)dst = *src;
        dst++;
        src++;
    }
    game_config_apply();
    if (event_off_flag == 0) {
        if (cfg_coin == 17) {
            table = sys_cfg_default_tbl[Cabinet_Type];
            if (Area_Type) {
                i = Area_Type;
            } else if (Area_Alt_Flag) {
                i = 6;
            } else {
                i = Area_Type;
            }
            dst = *(u32*)(table + i * 4);
            cfg_coin = *(u8*)(dst + 1);
        }
        cfg_continue = 0;
    }
}



void config_menu_dispatch(void) {
    /* per-page handler table in work RAM (02007E04), indexed by Config_No_1 */
    config_page_tbl[Config_No_1]();
}



void config_top_page(void)
{
    config_top_step_tbl[Config_No_2]();
}



void config_top_draw(void)
{
    Config_No_2++;
    if (Area_Type) {
        tilemap_fill_all(0, 0x20);
    } else {
        tilemap_fill_all(0, 0x1200);
    }
    task_sleep(1);
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, config_top_menu_scr);
    } else {
        tilemap_chunk_copy_16b((short *)(SS_RAM + 0x8000), (char *)jp_menu_font_cg, 512);
        tilemap_print_script_seq(0, 0, 0xFFFF, config_top_scr_jp);
    }
}



void config_top_select(void) {
    if (Area_Type) {
        cfg_top_cursor = menu_cursor_vtick(16, 6, 3, cfg_top_cursor, 0);
    } else {
        cfg_top_cursor = menu_cursor_vtick(6, 4, 3, cfg_top_cursor, 0);
    }
    config_top_item_tbl[cfg_top_cursor]();
    if (config_differs_from_default()) {
        if (Area_Type) {
            tilemap_rect_fill(18, 10, 10, 1, 8, 0xFFFF);
        } else {
            tilemap_rect_fill(8, 8, 34, 2, 8, 0xFFFF);
        }
    } else {
        if (Area_Type) {
            tilemap_rect_fill(18, 10, 10, 1, 2, 0xFFFF);
        } else {
            tilemap_rect_fill(8, 8, 34, 2, 2, 0xFFFF);
        }
    }
}



void config_top_system(void) {
    u16 trig;
    trig = ~p1sw_1 & p1sw_0;
    if (trig & 0x10) {
        Config_No_1 = 1;
        Config_No_2 = 0;
    } else if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, config_top_guide_scr);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, cfg_top_guide_jp);
    }
}



void config_top_game(void) {
    u16 trig;
    trig = ~p1sw_1 & p1sw_0;
    if (trig & 0x10) {
        Config_No_1 = 2;
        Config_No_2 = 0;
    } else if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, config_top_guide_scr);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, cfg_top_guide_jp);
    }
}



void config_top_default(void) {
    register s8 ix;
    u32 table;
    u32 p;
    s8* dst;
    if ((p1sw_0 & 0x30) == 0x30) {
        if ((p1sw_1 & 0x30) != 0x30) {
            table = sys_cfg_default_tbl[Cabinet_Type];
            if (Area_Type != 0) {
                ix = Area_Type;
            } else if (Area_Alt_Flag != 0) {
                ix = 6;
            } else {
                ix = Area_Type;
            }
            p = *(u32*)(table + ix * 4);
            cfg_coin = *(u8*)(p + 1);
            cfg_continue = *(u8*)(p + 2);
            cfg_chute = *(u8*)(p + 3);
            cfg_sound_mode = *(u8*)(p + 4);
            cfg_voice = *(u8*)(p + 9);
            Monitor_Flip = *(u8*)(p + 6);
            cfg_demo_sound = *(u8*)(p + 5);
            cfg_coin_special = Free_Play;
            cfg_dispenser = *(u8*)(p + 10);
            cfg_win_point = *(u8*)(p + 11);
            cfg_win_point_vs = *(u8*)(p + 12);
            cfg_extra = *(u8*)(p + 13);
            if (Coin_Mode == 17) {
                cfg_free_play = 1;
                cfg_continue = 1;
            } else {
                cfg_free_play = 0;
            }
            p = (u32)game_cfg_default_tbl[ix];
            dst = (s8 *)&game_config_work;
            for (ix = 0; ix < 16; ix++) {
                *dst = *(s8*)p;
                dst++;
                p++;
            }
            game_config_apply();
            Config_No_1 = 0;
            Config_No_2 = 0;
        }
    }
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, config_reset_guide_scr);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, cfg_top_guide_jp);
        tilemap_print_script_seq(0, 0, 0xFFFF, cfg_top_reset_guide_jp);
    }
}



void config_top_save_exit(void) {
    u16 e;
    s32 i;
    s32 u;
    s8* s;
    s8* d;
    s32 v;
    e = ~p1sw_1 & p1sw_0;
    if (e & 0x10) {
        config_check_changed();
        Free_Play = cfg_coin_special;
        Two_Coin_Start = cfg_free_play;
        Coin_Mode = cfg_coin;
        Chute_Mode = cfg_chute;
        Continue_Flag = cfg_continue;
        cfg_flip_old = Monitor_Flip;
        Demo_Sound = cfg_demo_sound;
        Sound_Mode = cfg_sound_mode;
        Language = cfg_voice;
        Card_Dispenser = cfg_dispenser;
        Win_Point_Com = cfg_win_point;
        Win_Point_Human = cfg_win_point_vs;
        Voice_Type = cfg_extra;
        s = (s8*)&game_config_work;
        d = (s8*)&Game_setting;
        for (i = 0; i < 16; i++) {
            *d = *s;
            s++;
            d++;
        }
        coin_chute1_w.per_credit = coin_rate_tbl[Coin_Mode][COIN_RATE_COINS];
        coin_chute1_w.credits = coin_rate_tbl[Coin_Mode][COIN_RATE_CREDITS];
        coin_chute2_w.per_credit = coin_rate_tbl[Coin_Mode][COIN_RATE_COINS];
        coin_chute2_w.credits = coin_rate_tbl[Coin_Mode][COIN_RATE_CREDITS];
        coin_chute3_w.per_credit = coin_rate_tbl[Coin_Mode][COIN_RATE_COINS];
        coin_chute3_w.credits = coin_rate_tbl[Coin_Mode][COIN_RATE_CREDITS];
        coin_chute4_w.per_credit = coin_rate_tbl[Coin_Mode][COIN_RATE_COINS];
        coin_chute4_w.credits = coin_rate_tbl[Coin_Mode][COIN_RATE_CREDITS];
        if (Coin_Mode != 17) {
            Two_Coin_Start = 0;
        } else {
            Two_Coin_Start = 1;
            Continue_Flag = 1;
        }
        if (cfg_changed) {
            if (Area_Type == 0) {
                tilemap_chunk_copy_16b((s16*)(SS_RAM + 0x8000), (char*)sys_font_cg, 140);
            }
            tilemap_fill_all(0, 0x20);
            tilemap_print_string(0, 0, 0xFFFF, config_saving_scr);
            task_sleep(1);
            eeprom_config_save();
            task_sleep(1);
            tilemap_fill_all(0, 0x20);
        }
        cfg_reserve = 1;
    } else if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, config_top_guide_scr);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, cfg_top_guide_jp);
    }
}



void sysconfig_page(void) {
    sysconfig_step_tbl[Config_No_2]();
}



void sysconfig_draw(void) {
    Config_No_2++;
    cfg_cursor = 0;
    cfg_cursor_old = 0;
    cfg_coin_step = 0;
    if (Area_Type) {
        tilemap_fill_all(0, 32);
    } else {
        tilemap_fill_all(0, 0x1200);
    }
    task_sleep(1);
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_scr);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_page_scr_jp);
    }
    switch (Area_Type) {
    case 0:
        cfg_item_max = 6;
        break;
    case 2:
    case 8:
        cfg_item_max = 7;
        tilemap_print_string(0, 0, 0xFFFF, &sysconfig_dispenser_scr[3]);
        break;
    case 3:
    case 4:
        if (Win_Point_Split == 0) {
            cfg_item_max = 8;
            tilemap_print_string(0, 0, 0xFFFF, sysconfig_dispenser_scr);
        } else {
            cfg_item_max = 9;
            tilemap_print_string(0, 0, 0xFFFF, sysconfig_winpoint_scr);
        }
        break;
    case 5:
        cfg_item_max = 7;
        tilemap_print_string(0, 0, 0xFFFF, &sysconfig_exit_scr[1]);
        break;
    default:
        cfg_item_max = 6;
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_exit_scr);
        break;
    }
}



void sysconfig_select(void) {
    if (Area_Type != 0) {
        cfg_cursor = menu_cursor_vtick(1, 5, cfg_item_max, cfg_cursor, 1);
    } else {
        cfg_cursor = menu_cursor_vtick(2, 4, cfg_item_max, cfg_cursor, 1);
    }
    if (cfg_cursor != cfg_cursor_old) {
        if (cfg_cursor == 2) {
            if (cfg_coin == 17 || event_off_flag == 0) {
                if (cfg_cursor > cfg_cursor_old) {
                    cfg_cursor_old = cfg_cursor;
                    cfg_cursor++;
                } else {
                    cfg_cursor_old = cfg_cursor;
                    cfg_cursor--;
                }
                if (Area_Type == 0) {
                    menu_cursor_redraw(2, 4, cfg_cursor, cfg_cursor_old);
                } else {
                    menu_cursor_redraw(1, 5, cfg_cursor, cfg_cursor_old);
                }
            }
        }
        if (cfg_cursor == 7 && (Area_Type == 3 || Area_Type == 4) && cfg_dispenser == 0) {
            if (cfg_cursor > cfg_cursor_old) {
                cfg_cursor_old = cfg_cursor;
                cfg_cursor++;
                if (Win_Point_Split != 0) {
                    cfg_cursor++;
                }
            } else {
                cfg_cursor_old = cfg_cursor;
                cfg_cursor--;
            }
            if (Area_Type == 0) {
                menu_cursor_redraw(2, 4, cfg_cursor, cfg_cursor_old);
            } else {
                menu_cursor_redraw(1, 5, cfg_cursor, cfg_cursor_old);
            }
        }
        if (cfg_cursor == 8 && (Area_Type == 3 || Area_Type == 4) && cfg_dispenser == 0) {
            if (cfg_cursor > cfg_cursor_old) {
                cfg_cursor_old = cfg_cursor;
                cfg_cursor++;
            } else {
                cfg_cursor_old = cfg_cursor;
                cfg_cursor--;
                if (Win_Point_Split != 0) {
                    cfg_cursor--;
                }
            }
            if (Area_Type == 0) {
                menu_cursor_redraw(2, 4, cfg_cursor, cfg_cursor_old);
            } else {
                menu_cursor_redraw(1, 5, cfg_cursor, cfg_cursor_old);
            }
        }
        cfg_cursor_old = cfg_cursor;
        if (cfg_cursor == 0) {
            cfg_coin_step = 0;
        }
    }
    switch (Area_Type) {
    case 2:
    case 8:
        sysconfig_item_tbl_c[cfg_cursor]();
        break;
    case 3:
    case 4:
        if (Win_Point_Split == 0) {
            sysconfig_item_card_tbl[cfg_cursor]();
        } else {
            sysconfig_item_card_tbl2[cfg_cursor]();
        }
        break;
    case 5:
        sysconfig_item_tbl_b[cfg_cursor]();
        break;
    default:
        sysconfig_item_tbl[cfg_cursor]();
        break;
    }
    sysconfig_draw_values();
}



void sysconfig_coin(void) {
    register s8 step;
    switch (cfg_coin_step) {
    case 0:
        cfg_coin_step++;
        cfg_coin_sel = cfg_coin;
        if (cfg_coin_sel == 9) {
            if (Area_Type == 3) {
                cfg_coin_sel = 2;
            } else if (Area_Type == 4) {
                cfg_coin_sel = 3;
            }
        }
    case 1:
    default:
        cfg_coin_special = 0;
        if (Area_Type == 3) {
            step = config_modify_step();
            cfg_coin_sel += step;
            if (cfg_coin_sel < 0) {
                cfg_coin_sel = 2;
            }
            if (cfg_coin_sel >= 3) {
                cfg_coin_sel = 0;
            }
            if (cfg_coin_sel == 2) {
                cfg_coin = 9;
            } else {
                cfg_coin = cfg_coin_sel;
            }
        } else if (Area_Type == 4) {
            step = config_modify_step();
            cfg_coin_sel += step;
            if (cfg_coin_sel < 0) {
                cfg_coin_sel = 3;
            }
            if (cfg_coin_sel >= 4) {
                cfg_coin_sel = 0;
            }
            if (cfg_coin_sel == 3) {
                cfg_coin = 9;
            } else {
                cfg_coin = cfg_coin_sel;
            }
        } else {
            if (Free_Play_Enable != 0) {
                step = config_modify_step();
                cfg_coin += step;
                if (event_off_flag != 0) {
                    if (cfg_coin < 0) {
                        cfg_coin = 18;
                    }
                    if (cfg_coin >= 19) {
                        cfg_coin = 0;
                    }
                } else {
                    if (cfg_coin == 17) {
                        if (step == 1) {
                            cfg_coin = 18;
                        } else if (step == -1) {
                            cfg_coin = 16;
                        }
                    }
                    if (cfg_coin < 0) {
                        cfg_coin = 18;
                    }
                    if (cfg_coin >= 19) {
                        cfg_coin = 0;
                    }
                }
            } else {
                step = config_modify_step();
                cfg_coin += step;
                if (event_off_flag != 0) {
                    if (cfg_coin < 0) {
                        cfg_coin = 17;
                    }
                    if (cfg_coin >= 18) {
                        cfg_coin = 0;
                    }
                } else {
                    if (cfg_coin < 0) {
                        cfg_coin = 16;
                    }
                    if (cfg_coin >= 17) {
                        cfg_coin = 0;
                    }
                }
            }
            if (cfg_coin == 17) {
                if (cfg_continue == 0) {
                    cfg_cont_forced = 1;
                    cfg_continue = 1;
                }
            } else if (Free_Play_Enable != 0 && cfg_coin == 18) {
                cfg_coin_special = 1;
                cfg_cont_forced = 0;
            } else if (cfg_cont_forced) {
                cfg_cont_forced = 0;
                cfg_continue = 0;
            }
        }
        break;
    }
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_modify_guide);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_item_guide_jp);
    }
}



void sysconfig_chute_mode(void) {
    register s8 step;
    step = config_modify_step();
    cfg_chute += step;
    switch (Cabinet_Type) {
    case 0:
        if (cfg_chute < 0) {
            cfg_chute = 2;
        } else if (cfg_chute >= 3) {
            cfg_chute = 0;
        }
        break;
    case 1:
        if (cfg_chute < 3) {
            cfg_chute = 6;
        } else if (cfg_chute >= 7) {
            cfg_chute = 3;
        }
        break;
    case 2:
        if (cfg_chute < 7) {
            cfg_chute = 11;
        } else if (cfg_chute >= 12) {
            cfg_chute = 7;
        }
        break;
    }
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_modify_guide);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_item_guide_jp);
    }
}



void sysconfig_continue(void) {
    if (cfg_coin != 17) {
        if (event_off_flag != 0 && config_modify_step()) {
            cfg_continue ^= 1;
        }
    }
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_modify_guide);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_item_guide_jp);
    }
}



void sysconfig_monitor(void) {
    if (config_modify_step()) {
        Monitor_Flip ^= 1;
    }
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_modify_guide);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_item_guide_jp);
    }
}



void sysconfig_demo_sound(void) {
    if (config_modify_step()) {
        cfg_demo_sound ^= 1;
    }
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_modify_guide);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_item_guide_jp);
    }
}



void sysconfig_sound_mode(void) {
    if (config_modify_step()) {
        cfg_sound_mode ^= 1;
    }
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_modify_guide);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_item_guide_jp);
    }
}



void sysconfig_language(void) {
    register s8 step;
    step = config_modify_step();
    cfg_voice += step;
    if (cfg_voice < 0) {
        cfg_voice = 1;
    } else if (cfg_voice > 1) {
        cfg_voice = 0;
    }
    tilemap_print_string(0, 0, 0xFFFF, sysconfig_modify_guide);
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_modify_guide);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_item_guide_jp);
    }
}



void sysconfig_dispenser(void) {
    if (config_modify_step()) {
        cfg_dispenser ^= 1;
    }
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_modify_guide);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_item_guide_jp);
    }
}



void sysconfig_win_point(void) {
    register s8 step;
    step = config_modify_step();
    cfg_win_point += step;
    if (cfg_win_point < Win_Point_Com_Min) {
        cfg_win_point = Win_Point_Com_Max;
    } else if (cfg_win_point > Win_Point_Com_Max) {
        cfg_win_point = Win_Point_Com_Min;
    }
    if (Win_Point_Split == 0) {
        tilemap_print_hex_block(18, 19, 2, hex_to_bcd(cfg_win_point), 2, 1);
    } else {
        tilemap_print_hex_block(25, 19, 2, hex_to_bcd(cfg_win_point), 2, 1);
    }
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_modify_guide);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_item_guide_jp);
    }
}



void sysconfig_win_point_human(void) {
    register s8 step;
    step = config_modify_step();
    cfg_win_point_vs += step;
    if (cfg_win_point_vs < Win_Point_Human_Min) {
        cfg_win_point_vs = Win_Point_Human_Max;
    } else if (cfg_win_point_vs > Win_Point_Human_Max) {
        cfg_win_point_vs = Win_Point_Human_Min;
    }
    tilemap_print_hex_block(25, 21, 2, hex_to_bcd(cfg_win_point_vs), 2, 1);
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_modify_guide);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_item_guide_jp);
    }
}



void sysconfig_voice_type_toggle(void) {
    if (config_modify_step()) {
        cfg_extra ^= 1;
    }
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_modify_guide);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_item_guide_jp);
    }
    if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_modify_guide);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_item_guide_jp);
    }
}



void sysconfig_exit(void) {
    u16 trig;
    trig = ~p1sw_1 & p1sw_0;
    if (trig & 0x10) {
        Config_No_1 = 0;
        Config_No_2 = 0;
    } else if (Area_Type) {
        tilemap_print_string(0, 0, 0xFFFF, sysconfig_return_guide);
    } else {
        tilemap_print_script_seq(0, 0, 0xFFFF, sys_cfg_exit_guide_jp);
    }
}



void gameconfig_page(void) {
    u32 p;
    u32 table;
    s32 ix;
    switch (game_config_main()) {
    case 1:
        Config_No_1 = 0;
        Config_No_2 = 0;
        game_config_apply();
        if (event_off_flag == 0) {
            if (cfg_coin == 17) {
                table = sys_cfg_default_tbl[Cabinet_Type];
                if (Area_Type) {
                    ix = Area_Type;
                } else if (Area_Alt_Flag) {
                    ix = 6;
                } else {
                    ix = Area_Type;
                }
                p = *(u32*)(table + ix * 4);
                cfg_coin = *(u8*)(p + 1);
            }
            cfg_continue = 0;
        }
    case 0:
        break;
    }
}



void sysconfig_draw_values(void) {
    s16 attr;
    attr = 2;
    if (cfg_coin != Coin_Mode) {
        attr = 8;
    }
    if (Area_Type) {
        config_print_setting(coin_setting_str_tbl[cfg_coin], 5, attr);
    } else {
        tilemap_print_script_seq(0, 0, attr, sys_cfg_coin_scr_jp[cfg_coin]);
    }
    attr = 2;
    if (cfg_chute != Chute_Mode) {
        attr = 8;
    }
    if (Area_Type) {
        config_print_setting(chute_mode_str_tbl[cfg_chute], 7, attr);
    } else {
        tilemap_print_script_seq(0, 0, attr, sys_cfg_chute_scr_jp[cfg_chute]);
    }
    attr = 2;
    if (cfg_continue != Continue_Flag) {
        attr = 8;
    }
    if (Area_Type) {
        config_print_setting(on_off_str_tbl[cfg_continue], 9, attr);
    } else {
        tilemap_print_script_seq(0, 0, attr, sys_cfg_continue_scr_jp[cfg_continue]);
    }
    attr = 2;
    if (Monitor_Flip != eeprom_w[6]) {
        attr = 8;
    }
    if (Area_Type) {
        config_print_setting(monitor_str_tbl[Monitor_Flip], 11, attr);
    } else {
        tilemap_print_script_seq(0, 0, attr, sys_cfg_monitor_scr_jp[Monitor_Flip]);
    }
    attr = 2;
    if (cfg_demo_sound != Demo_Sound) {
        attr = 8;
    }
    if (Area_Type) {
        config_print_setting(on_off_str_tbl[cfg_demo_sound], 13, attr);
    } else {
        tilemap_print_script_seq(0, 0, attr, sys_cfg_demo_scr_jp[cfg_demo_sound]);
    }
    attr = 2;
    if (cfg_sound_mode != Sound_Mode) {
        attr = 8;
    }
    if (Area_Type) {
        config_print_setting(sound_mode_str_tbl[cfg_sound_mode], 15, attr);
    } else {
        tilemap_print_script_seq(0, 0, attr, sys_cfg_sound_scr_jp[cfg_sound_mode]);
    }
    if (Area_Type == 5) {
        attr = 2;
        if (cfg_voice != Language) {
            attr = 8;
        }
        config_print_setting(language_str_tbl[cfg_voice], 17, attr);
    }
    if (Area_Type == 3 || Area_Type == 4) {
        attr = 2;
        if (cfg_dispenser != (s8)Card_Dispenser) {
            attr = 8;
        }
        config_print_setting(on_off_str_tbl[cfg_dispenser], 17, attr);
        if (Win_Point_Split == 0) {
            attr = 2;
            if (cfg_win_point != Win_Point_Com) {
                attr = 8;
            }
            tilemap_print_hex_block(18, 19, attr, hex_to_bcd(cfg_win_point), 2, 2);
        } else {
            attr = 2;
            if (cfg_win_point != Win_Point_Com) {
                attr = 8;
            }
            tilemap_print_hex_block(25, 19, attr, hex_to_bcd(cfg_win_point), 2, 2);
            attr = 2;
            if (cfg_win_point_vs != Win_Point_Human) {
                attr = 8;
            }
            tilemap_print_hex_block(25, 21, attr, hex_to_bcd(cfg_win_point_vs), 2, 2);
        }
    }
    if (Area_Type == 2 || Area_Type == 8) {
        attr = 2;
        if (cfg_extra != Voice_Type) {
            attr = 8;
        }
        config_print_setting(voice_type_str_tbl[cfg_extra], 17, attr);
    }
}



void config_print_setting(const TM_STRING* src, s32 y, s16 attr) {
    TM_STRING e;
    e.x = src->x;
    e.y = y;
    e.attr = attr;
    e.str = src->str;
    tilemap_print_string(0, 0, 0xFFFF, &e);
}



void test_menu_print_script_at(const void* script, s16 px, s16 y) {
    tilemap_print_script_seq(0, px, y, script);
}



void config_check_changed(void) {
    register s8 i;
    s8* saved;
    s8* edited;
    s32 unused[4];
    cfg_changed = 0;
    if (cfg_coin != Coin_Mode) {
        cfg_changed = 1;
    } else if (cfg_chute != Chute_Mode) {
        cfg_changed = 1;
    } else if (cfg_continue != Continue_Flag) {
        cfg_changed = 1;
    } else if (cfg_flip_old != Monitor_Flip) {
        cfg_changed = 1;
    } else if (cfg_demo_sound != Demo_Sound) {
        cfg_changed = 1;
    } else if (cfg_sound_mode != Sound_Mode) {
        cfg_changed = 1;
    } else if (cfg_voice != Language) {
        cfg_changed = 1;
    } else if (cfg_dispenser != ((s8)Card_Dispenser)) {
        cfg_changed = 1;
    } else if (cfg_win_point != Win_Point_Com) {
        cfg_changed = 1;
    } else if (cfg_win_point_vs != Win_Point_Human) {
        cfg_changed = 1;
    } else if (cfg_extra != Voice_Type) {
        cfg_changed = 1;
    }
    saved = (s8 *)&game_config_work;
    edited = (s8 *)&Game_setting;
    for (i = 0; i < 8; i++) {
        if (*edited != *saved) {
            cfg_changed = 1;
        }
        edited++;
        saved++;
    }
}



s32 config_differs_from_default(void) {
    register s8 ix;
    u32 table;
    u32 p;
    s8* name;
    s32 result;
    result = 0;
    table = sys_cfg_default_tbl[Cabinet_Type];
    if (Area_Type) {
        ix = Area_Type;
    } else if (Area_Alt_Flag) {
        ix = 6;
    } else {
        ix = Area_Type;
    }
    p = *(u32*)(table + ix * 4);
    if (*(u8*)(p + 1) != cfg_coin) {
        result = -1;
    } else if (*(u8*)(p + 2) != cfg_continue) {
        result = -1;
    } else if (*(u8*)(p + 3) != cfg_chute) {
        result = -1;
    } else if (*(u8*)(p + 4) != cfg_sound_mode) {
        result = -1;
    } else if (*(u8*)(p + 5) != cfg_demo_sound) {
        result = -1;
    } else if (*(u8*)(p + 6) != Monitor_Flip) {
        result = -1;
    } else if (*(u8*)(p + 9) != cfg_voice) {
        result = -1;
    } else if (*(u8*)(p + 10) != cfg_dispenser) {
        result = -1;
    } else if (*(u8*)(p + 11) != cfg_win_point) {
        result = -1;
    } else if (*(u8*)(p + 12) != cfg_win_point_vs) {
        result = -1;
    } else if (*(u8*)(p + 13) != cfg_extra) {
        result = -1;
    }
    p = (u32)game_cfg_default_tbl[ix];
    name = (s8 *)&game_config_work;
    for (ix = 0; ix < 8; ix++) {
        if (*name != *(s8*)p) {
            result = -1;
        }
        name++;
        p++;
    }
    return result;
}



s8 config_modify_step(void) {
    u16 trig;
    s8 step;
    trig = ~p1sw_1 & p1sw_0;
    step = 0;
    if (trig & 0xC) {
        if (trig & 8) {
            step = 1;
        } else {
            step = -1;
        }
    }
    if (trig & 0x10) {
        step = 1;
    }
    if (trig & 0x20) {
        step = -1;
    }
    return step;
}



s8 menu_cursor_vtick(s32 x, s32 y, s8 last, s8 row, s8 wrap) {
    u16 trig;
    s32 off;
    trig = ~p1sw_1 & p1sw_0;
    if (trig & 3) {
        if (trig & 2) {
            off = row * 2;
            if (Area_Type) {
                tilemap_print_string_attr(x, y + off, 2, cursor_blank_str);
            } else {
                if (wrap) {
                    if (row == last) {
                        off += 2;
                    }
                } else {
                    if (row == last) {
                        off += 2;
                    }
                }
                tilemap_put_block(x, y + off, 2, 0x1200);
            }
            row++;
            if (wrap) {
                if (row > last) {
                    row = 0;
                }
            } else {
                if (row > last) {
                    row = 0;
                }
            }
        } else {
            off = row * 2;
            if (Area_Type) {
                tilemap_print_string_attr(x, y + off, 2, cursor_blank_str);
            } else {
                if (wrap) {
                    if (row == last) {
                        off += 2;
                    }
                } else {
                    if (row == last) {
                        off += 2;
                    }
                }
                tilemap_put_block(x, y + off, 2, 0x1200);
            }
            row--;
            if (wrap) {
                if (row < 0) {
                    row = last;
                }
            } else {
                if (row < 0) {
                    row = last;
                }
            }
        }
    }
    off = row * 2;
    if (Area_Type) {
        tilemap_print_string_attr(x, y + off, 2, cursor_mark_str);
    } else {
        if (wrap) {
            if (row == last) {
                off += 2;
            }
        } else {
            if (row == last) {
                off += 2;
            }
        }
        tilemap_put_block(x, y + off, 2, 0x1204);
    }
    return row;
}



void menu_cursor_redraw(s32 x, s32 y, s32 cur, s32 old) {
    s32 off;
    off = old * 2;
    if (Area_Type) {
        tilemap_print_string_attr(x, y + off, 2, cursor_blank_str);
    } else {
        tilemap_put_block(x, y + off, 2, 0x1200);
    }
    off = cur * 2;
    if (Area_Type) {
        tilemap_print_string_attr(x, y + off, 2, cursor_mark_str);
    } else {
        tilemap_put_block(x, y + off, 2, 0x1204);
    }
}



void config_menu_load_settings(void) {
    s32 i;
    u32 table;
    u32 dst;
    s8* src;
    cfg_top_cursor = 0;
    cfg_cont_forced = 0;
    cfg_reserve = 0;
    cfg_coin_special = Free_Play;
    cfg_coin = Coin_Mode;
    cfg_continue = Continue_Flag;
    cfg_free_play = Two_Coin_Start;
    cfg_sound_mode = Sound_Mode;
    cfg_voice = Language;
    cfg_flip_old = Monitor_Flip;
    cfg_demo_sound = Demo_Sound;
    cfg_chute = Chute_Mode;
    cfg_dispenser = ((s8)Card_Dispenser);
    cfg_win_point = Win_Point_Com;
    cfg_win_point_vs = Win_Point_Human;
    cfg_extra = Voice_Type;
    dst = (u32)&game_config_work;
    src = (s8 *)&Game_setting;
    for (i = 0; i < 16; i++) {
        *(u8*)dst = *src;
        dst++;
        src++;
    }
    game_config_apply();
    if (event_off_flag == 0) {
        if (cfg_coin == 17) {
            table = sys_cfg_default_tbl[Cabinet_Type];
            if (Area_Type) {
                i = Area_Type;
            } else if (Area_Alt_Flag) {
                i = 6;
            } else {
                i = Area_Type;
            }
            dst = *(u32*)(table + i * 4);
            cfg_coin = *(u8*)(dst + 1);
        }
        cfg_continue = 0;
    }
}
