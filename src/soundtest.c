/*
 * SOUNDTEST.C  Test mode: sound test page
 *
 * soundtest_* is the sound test: title, code select, monitor task, pan, balance and level bars.
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

/* soundtest_no: the sound test page step */
#define SOUND_TITLE     0       /* soundtest_draw_title */
#define SOUND_SELECT    1       /* soundtest_code_select: choose and play codes */

s16 soundtest_rep_timer = 30;  /* 02007140 */
s16 soundtest_code = 0;  /* 02007142 */
s16 soundtest_no = 0;  /* 02007144 */



/* provisional name */
void soundtest_draw_title(void) {
    tilemap_fill_all(0, 32);
    tilemap_print_string(0, 0, 0xFFFF, soundtest_menu_scr);
    soundtest_no++;
}



/* provisional name */
void soundtest_code_select(void) {
    register u16 trig;
    register u8 sys;
    register s32 unused;
    sys = ~syssw_1 & syssw_0;
    if (p1sw_0 == p1sw_1) {
        if (soundtest_rep_timer == 0) {
            trig = p1sw_0;
        } else {
            soundtest_rep_timer--;
            trig = ~p1sw_1 & p1sw_0;
        }
    } else {
        soundtest_rep_timer = 30;
        trig = ~p1sw_1 & p1sw_0;
    }
    if (trig & LEVER_RIGHT) {
        soundtest_code += 16;
    } else if (trig & LEVER_LEFT) {
        soundtest_code -= 16;
    } else if (trig & LEVER_UP) {
        soundtest_code += 1;
    } else if (trig & LEVER_DOWN) {
        soundtest_code -= 1;
    }
    trig = ~p1sw_1 & p1sw_0;
    if (trig & BUTTON_LP) {
        sound_request(soundtest_code);
    } else if (trig & BUTTON_MP) {
        bgm_stop();
    }
    tilemap_print_hex_block(30, 7, 2, soundtest_code, 4, 0);
}



/* provisional name */
s32 soundtest_page(void) {
    register s32 rc;
    switch (soundtest_no) {
    case SOUND_TITLE:
        soundtest_draw_title();
        break;
    case SOUND_SELECT:
        soundtest_code_select();
        break;
    }
    if ((p1sw_0 & BUTTON_START) && (p1sw_0 & BUTTON_LP)) {
        rc = -1;
        soundtest_no = SOUND_TITLE;
        soundtest_code = 0;
        soundtest_rep_timer = 30;
        sound_driver_init();
        return rc;
    }
    rc = 0;
    return rc;
}

/* provisional name */
void soundtest_monitor_task(void) {
    s32 i;
    s16 status;
    u16 on;
    u16 bit;
    u16 req;
    s32 level;
    u16 pan;
    u16 level_l;
    u16 level_r;
    u32 voice;
    s32 unused1;
    s32 unused2;
    req = 0;
    tilemap_fill_all(0, 32);
    tilemap_print_string(0, 0, 0xFFFF, soundtest_monitor_scr);
    tilemap_print_hex(30, 3, 2, req, 4, 0);
    status = sound_driver_version();
    tilemap_print_hex(10, 3, 2, status, 4, 0);
    task_sleep(1);
    for (;;) {
        if ((p1sw_0 & 0x1010) != 0x1010) {
            break;
        }
        task_sleep(1);
    }
    for (;;) {
        if ((p1sw_0 & 0x1010) == 0x1010) {
            break;
        }
        if ((p1sw_0 & LEVER_LEFT) == LEVER_LEFT && (p1sw_1 & LEVER_LEFT) != LEVER_LEFT) {
            req--;
            tilemap_print_hex(30, 3, 2, req, 4, 0);
        } else if ((p1sw_0 & LEVER_RIGHT) == LEVER_RIGHT && (p1sw_1 & LEVER_RIGHT) != LEVER_RIGHT) {
            req++;
            tilemap_print_hex(30, 3, 2, req, 4, 0);
        } else if ((p1sw_0 & LEVER_UP) == LEVER_UP && (p1sw_1 & LEVER_UP) != LEVER_UP) {
            req += 16;
            tilemap_print_hex(30, 3, 2, req, 4, 0);
        } else if ((p1sw_0 & LEVER_DOWN) == LEVER_DOWN && (p1sw_1 & LEVER_DOWN) != LEVER_DOWN) {
            req -= 16;
            tilemap_print_hex(30, 3, 2, req, 4, 0);
        } else if ((p1sw_0 & BUTTON_LP) == BUTTON_LP && (p1sw_1 & BUTTON_LP) != BUTTON_LP) {
            sound_request((s16)req);
        } else if ((p1sw_0 & BUTTON_MP) == BUTTON_MP && (p1sw_1 & BUTTON_MP) != BUTTON_MP) {
            sound_driver_init();
        }
        status = sound_status_read();
        if (status & 1) {
            tilemap_print_string_attr(10, 5, 2, snd_stat_stop_str);
        }
        if (status & 2) {
            tilemap_print_string_attr(10, 5, 2, snd_stat_play_str);
        }
        if (status & 4) {
            tilemap_print_string_attr(10, 5, 2, snd_stat_pause_str);
        }
        tilemap_print_string_attr(10, 9, 2, snd_stat_blank_str);
        if (status & 8) {
            tilemap_print_string_attr(10, 6, 2, snd_stat_fadein_str);
        }
        if (status & 0x10) {
            tilemap_print_string_attr(10, 6, 2, snd_stat_fadeout_str);
        }
        on = snd_key_on_reg;
        bit = 1;
        voice = SOUND_REG;
        for (i = 0; i < 16; i++) {
            pan = *(volatile u16*)(voice + 12);
            if ((on & bit) == 0) {
                soundtest_print_pan_bar(4, i + 9, -1);
            } else {
                soundtest_print_pan_bar(4, i + 9, ((pan & 0xFFF) + 1) / 256);
            }
            level_l = *(volatile u16*)(voice + 28);
            level_r = *(volatile u16*)(voice + 30);
            tilemap_print_hex(21, i + 9, 2, pan, 4, 0);
            level = ((level_l & 0x7FFF) + (level_r & 0x7FFF)) / 2 + 1;
            soundtest_print_level_bar(40, i + 9, (u32)level >> 12);
            soundtest_print_lr_balance(30, i + 9, level_l, level_r);
            bit <<= 1;
            voice += 32;
        }
        task_sleep(1);
    }
    sound_driver_init();
    task_sleep(1);
}



/* provisional name */
void soundtest_print_pan_bar(s32 x, s32 y, s32 pan) {
    tilemap_print_string_attr(x, y, 2, pan_bar_str);
    if (pan != -1) {
        tilemap_put_char(x + (pan & 0xF), y, 2, 35);
    }
}



/* provisional name */
void soundtest_print_lr_balance(s32 x, s32 y, s32 now, s32 old) {
    if (now == old) {
        tilemap_print_string_attr(x, y, 2, delta_same_str);
    } else if (now > old) {
        tilemap_print_string_attr(x, y, 2, delta_up_str);
    } else {
        tilemap_print_string_attr(x, y, 2, delta_down_str);
    }
}



/* provisional name */
void soundtest_print_level_bar(s32 x, s32 y, s32 level) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (i < level) {
            tilemap_put_char(x + i, y, 2, 17);
        } else {
            tilemap_put_char(x + i, y, 2, 45);
        }
    }
}
