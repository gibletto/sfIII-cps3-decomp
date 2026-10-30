/*
 * TEST_MODE.C  Test-mode task
 *
 * test_mode_task enters test mode from the test switch, draws the menu, runs the I/O, sound,
 * colour, screen, backup RAM, configuration, memory and CD pages, and restarts the game task
 * on exit.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Sub.h"
#include "ACTIVE00.h"
#include "active01.h"
#include "active02.h"
#include "active03.h"
#include "active04.h"
#include "active05.h"
#include "active07.h"
#include "active08.h"
#include "active09.h"
#include "active11.h"
#include "active12.h"
#include "FOLLOW01.h"
#include "FOLLOW02.h"
#include "fifo.h"
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
#include "pass00.h"
#include "PASS01.h"
#include "PASS02.h"
#include "PASS03.h"
#include "PASS04.h"
#include "PASS05.h"
#include "PASS07.h"
#include "PASS08.h"
#include "PASS09.h"
#include "PASS11.h"
#include "PASS12.h"
#include "SHELL00.h"
#include "SHELL01.h"
#include "SHELL03.h"
#include "SHELL04.h"
#include "SHELL11.h"
#include "SHELL12.h"
#include "Entry.h"
#include "entry_2.h"
#include "CMD_MAIN.h"
#include "cmd_main_2.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "PLS02.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sc_trans.h"
#include "Manage.h"
#include "manage_2.h"
#include "bg0001.h"
#include "Com_Pl.h"
#include "cps3.h"
#include "fighter.h"
#include "RANKING.h"

/* test_rno: the test mode task's routine */
#define TEST_WAIT       0       /* test_mode_wait: wait for the test switch */
#define TEST_MENU_INIT  1       /* test_menu_init: draw the test menu */
#define TEST_MENU       2       /* test_menu_run: the menu and its pages */
#define TEST_EXIT       3       /* test_mode_exit: leave the test mode */

/* test_menu_no: the test menu page */
#define MENU_SELECT     0       /* test_menu_select: move the cursor */
#define MENU_INPUT      1       /* iotest_input_page */
#define MENU_OUTPUT     2       /* iotest_output_page */
#define MENU_SOUND      3       /* soundtest_page */
#define MENU_COLOR      4       /* colortest_page */
#define MENU_SCREEN     5       /* screentest_page */
#define MENU_GAMEDATA   6       /* gamedata_page */
#define MENU_CONFIG     7       /* config_menu_page */
#define MENU_MEMORY     8       /* memtest_page */
#define MENU_REWRITE    9       /* rewrite_page, or leave in Country 2 */
#define MENU_EXIT       10      /* leave the test mode */

s16 test_rno;  /* 0200DC94 */
s16 test_menu_no;  /* 0200DC96 */
s16 test_cursor;  /* 0200DC98 */
s16 test_cursor_on;  /* 0200DC9A */
s16 test_cursor_off;  /* 0200DC9C */
s16 test_font_type;  /* 0200DC9E */
s16 test_cursor_max;  /* 0200DCA0 */

void tilemap_put_block(u16 x, u16 y, u16 attr, u16 code);

#pragma noregsave(test_mode_task)


/* provisional name */
void test_mode_task(void) {
    test_rno = test_cursor = 0;
    do {
        switch (test_rno) {
        case TEST_WAIT:
            test_mode_wait();
            break;
        case TEST_MENU_INIT:
            test_menu_init();
            sprite_bank_flip();
            break;
        case TEST_MENU:
            test_menu_run();
            sprite_bank_flip();
            break;
        case TEST_EXIT:
            test_mode_exit();
            break;
        }
        task_sleep(1);
    } while (1);
}

/* Wait for the test switch; on a press, stop the game and open the test menu. */
/* provisional name */
void test_mode_wait(void)
{
    if ((syssw_0 & 2) && test_sw_lock == 0) {
        test_flag = 1;
        coin_lock_set(-1);
        if (Game_setting.Screen_Mode) {
            set_screen_mode(7);
        } else {
            set_screen_mode(3);
        }
        BGM_Stop();
        bg_vbl_trans_flag = 0;
        Demo_Flag = 1;
        Scrn_Pos_Init();
        Family_Init();
        init_render_lists();
        palette_bank_set(0x3FC00);
        tilemap_fill_all(0, 32);
        config_menu_load_settings();
        kill_tasks_by_func(mode_init_task);
        kill_tasks_by_priority(3, 1);
        test_rno += 1;
    }
}



/* provisional name */
void test_menu_init(void) {
    test_rno += 1;
    test_menu_no = MENU_SELECT;
    se_voice_stop_all();
    bg_vbl_trans_flag = Debug_R_No = Debug_Select_No = Debug_Menu_No = 0;
    tilemap_fill_all(0, 32);
    palette_write(0, sys_palette, 256);
    switch (Country) {
    case 1:
        test_font_type = 1;
        tilemap_chunk_copy_16b((s16*)(SS_RAM + 0x8000), (char*)jp_menu_font_cg, 512);
        tilemap_fill_all(0, 0x1200);
        tilemap_print_script_seq(0, 0, 0xFFFF, test_menu_scr_jp);
        test_cursor_on = 0x1204;
        test_cursor_off = 0x1200;
        if (config_differs_from_default()) {
            tilemap_rect_fill(21, 16, 4, 2, 8, 0xFFFF);
        }
        break;
    default:
        test_font_type = 0;
        tilemap_chunk_copy_16b((s16*)(SS_RAM + 0x8000), (char*)sys_font_cg, 140);
        tilemap_fill_all(0, 32);
        tilemap_print_string(0, 0, 0xFFFF, Country == 2 ? test_menu_str_asia : test_menu_str);
        test_cursor_on = 62;
        test_cursor_off = 32;
        if (config_differs_from_default()) {
            tilemap_rect_fill(19, 15, 14, 1, 8, 0xFFFF);
        }
        break;
    }
    tilemap_put_block(test_cursor_x_tbl[test_font_type], test_cursor_y_tbl[test_font_type][test_cursor], 2,
                             test_cursor_on);
    if (DEBUG_DISP) {
        test_cursor = 0;
        tilemap_print_string(0, 0, 0xFFFF, test_menu_str);
    }
    if (Country == 2) {
        test_cursor_max = 8;
    } else {
        test_cursor_max = 9;
    }
    task_sleep(1);
}



/* provisional name */
void test_menu_run(void) {
    s16 done = 0;
    switch (test_menu_no) {
    case MENU_SELECT:
        test_menu_select();
        break;
    case MENU_INPUT:
        done = iotest_input_page();
        break;
    case MENU_OUTPUT:
        done = iotest_output_page();
        break;
    case MENU_SOUND:
        done = soundtest_page();
        break;
    case MENU_COLOR:
        done = colortest_page();
        break;
    case MENU_SCREEN:
        done = screentest_page();
        break;
    case MENU_GAMEDATA:
        done = gamedata_page();
        break;
    case MENU_CONFIG:
        done = config_menu_page();
        break;
    case MENU_MEMORY:
        done = memtest_page();
        break;
    case MENU_REWRITE:
        if (Country == 2) {
            test_rno++;
        } else {
            done = rewrite_page();
        }
        break;
    case MENU_EXIT:
        test_rno += 1;
        break;
    }
    if (done != 0) {
        test_rno = TEST_MENU_INIT;
    }
}



/* provisional name */
void test_menu_select(void) {
    u16 sw = ~p1sw_1 & p1sw_0;
    if (sw & LEVER_UP) {
        tilemap_put_block(test_cursor_x_tbl[test_font_type], test_cursor_y_tbl[test_font_type][test_cursor], 2,
                                 test_cursor_off);
        test_cursor--;
        if (test_cursor < 0) {
            test_cursor = test_cursor_max;
        }
        tilemap_put_block(test_cursor_x_tbl[test_font_type], test_cursor_y_tbl[test_font_type][test_cursor], 2,
                                 test_cursor_on);
    } else if (sw & LEVER_DOWN) {
        tilemap_put_block(test_cursor_x_tbl[test_font_type], test_cursor_y_tbl[test_font_type][test_cursor], 2,
                                 test_cursor_off);
        test_cursor++;
        if (test_cursor > test_cursor_max) {
            test_cursor = 0;
        }
        tilemap_put_block(test_cursor_x_tbl[test_font_type], test_cursor_y_tbl[test_font_type][test_cursor], 2,
                                 test_cursor_on);
    } else if (sw & BUTTON_LP) {
        test_menu_no = test_cursor + 1;
        tilemap_chunk_copy_16b((s16*)(SS_RAM + 0x8000), (char*)sys_font_cg, 140);
        tilemap_fill_all(0, 32);
    }
}

/* provisional name */
void test_mode_exit(void)
{
    tilemap_fill_all(0, 32);
    test_rno = test_menu_no = test_cursor = 0;
    coin_lock_set(-1);
    Cd_Error_Flag = 1;
    switch_read(1);
    if (Game_setting.Screen_Mode) {
        set_screen_mode(7);
    } else {
        set_screen_mode(3);
    }
    Scrn_Pos_Init();
    Family_Init();
    coin_work_init();
    init_render_lists();
    palette_bank_set(0x3FC00);
    while (create_task((void (*)())mode_init_task, 0, &task_tbl[0], 0, 0) == 0) {
    }
    destroy_current_task();
}
