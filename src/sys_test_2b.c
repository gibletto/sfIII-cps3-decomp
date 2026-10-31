/*
 * SYS_TEST_2B.C  Test mode: game data page
 *
 * gamedata_page shows the game data counters (gamedata_show_counters, gamedata_print_counters) and
 * clears the card counter (gamedata_clear_card_counter) under gamedata_draw_title.
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
#include "sys_test_2b.h"
#include "cps3.h"



s16 backup_test_no = 0;  /* 02007150 */


/* provisional name */
void gamedata_print_counters(void) {
    s32 unused;
    u32 val[4];
    eeprom_read(8, (volatile u16*)(EEP_ROM_READ + EEP_BOOK_COIN), (u16*)val);
    tilemap_print_hex_block(30, 7, 2, hex_to_bcd(val[0]), 6, 0);
    tilemap_print_hex_block(30, 9, 2, hex_to_bcd(val[1]), 6, 0);
    if (Free_Play_Enable != 0) {
        tilemap_print_hex_block(30, 11, 2, hex_to_bcd(val[2]), 6, 0);
        if (Area_Type == 3 || Area_Type == 4) {
            tilemap_print_hex_block(30, 13, 2, hex_to_bcd(val[3]), 6, 0);
        }
    } else {
        if (Area_Type == 3 || Area_Type == 4) {
            tilemap_print_hex_block(30, 11, 2, hex_to_bcd(val[3]), 6, 0);
        }
    }
}



/* provisional name */
void gamedata_draw_title(void) {
    tilemap_fill_all(0, 32);
    tilemap_print_string(0, 0, 0xFFFF, gamedata_scr);
    if (Free_Play_Enable != 0) {
        tilemap_print_string(0, 0, 0xFFFF, gamedata_freeplay_str);
        if (Area_Type == 3 || Area_Type == 4) {
            tilemap_print_string(0, 2, 0xFFFF, gamedata_card_str);
        }
    } else {
        if (Area_Type == 3 || Area_Type == 4) {
            tilemap_print_string(0, 0, 0xFFFF, gamedata_card_str);
        }
    }
    backup_test_no++;
}



/* provisional name */
void gamedata_show_counters(void) {
    gamedata_print_counters();
    backup_test_no++;
}



/* provisional name */
void gamedata_clear_card_counter(void) {
    if ((p1sw_0 & BUTTON_MK) && (p1sw_0 & BUTTON_HK) && (p1sw_0 & 0x400)) {
        book_card_count = 0;
        if (eeprom_write(2, (volatile u16*)(EEP_ROM + 0x170), (u16*)&book_card_count)) {
            eeprom_error_halt();
        }
        backup_test_no--;
    }
}



/* provisional name */
s32 gamedata_page(void) {
    register s32 rc;
    switch (backup_test_no) {
    case 0:
        gamedata_draw_title();
        break;
    case 1:
        gamedata_show_counters();
        break;
    case 2:
        gamedata_clear_card_counter();
        break;
    }
    if ((p1sw_0 & BUTTON_START) && (p1sw_0 & BUTTON_LP)) {
        rc = -1;
        backup_test_no = 0;
        return rc;
    }
    rc = 0;
    return rc;
}
