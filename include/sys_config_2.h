#ifndef SYS_CONFIG_2_H
#define SYS_CONFIG_2_H

#include "structs.h"

s8 config_menu_run(void);
void config_top_default(void);
void sysconfig_coin(void);
void sysconfig_chute_mode(void);
void sysconfig_language(void);
void sysconfig_win_point(void);
void sysconfig_win_point_human(void);
void sysconfig_voice_type_toggle(void);
void test_menu_print_script_at(const void* script, s16 x, s16 y);
void config_menu_init(void);
void config_menu_dispatch(void);
void config_top_page(void);
void sysconfig_page(void);
void gameconfig_page(void);
void config_top_draw(void);
void config_top_select(void);
void config_top_system(void);
void config_top_game(void);
void config_top_save_exit(void);
void sysconfig_draw(void);
void sysconfig_select(void);
void sysconfig_continue(void);
void sysconfig_monitor(void);
void sysconfig_demo_sound(void);
void sysconfig_sound_mode(void);
void sysconfig_exit(void);
void sysconfig_dispenser(void);
void menu_cursor_redraw(s32 x, s32 y, s32 cur, s32 old);
s8 menu_cursor_vtick(s32 x, s32 y, s8 last, s8 row, s8 wrap);
s8 config_modify_step(void);
void config_menu_load_settings(void);
void config_check_changed(void);
void sysconfig_draw_values(void);
s32 config_differs_from_default(void);
void config_print_setting(const TM_STRING* src, s32 y, s16 attr);

#endif
