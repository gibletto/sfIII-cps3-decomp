/*
 * SYS_TEST_4.C  Test mode CD-ROM rewrite menu
 *
 * Routines: rewrite_menu_init, rewrite_menu_select, rewrite_cd_not_ready, rewrite_page.
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
#include "sys_test.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "cps3.h"



s16 rewrite_no = 0;  /* 02007CDC */
s16 rewrite_cursor = 0;  /* 02007CDE */


/* provisional name */
void rewrite_menu_init(void) {
    rewrite_cursor = 0;
    while (scsi_prevent_allow_medium_removal(0, 1)) {
    }
    tilemap_fill_all(0, 32);
    tilemap_print_string(0, 0, 0xFFFF, rewrite_menu_scr);
    tilemap_print_string(0, 0, 0xFFFF, rewrite_guide_scr);
    tilemap_put_block(15, 9, 2, 62);
    rewrite_no++;
}



/* provisional name */
void rewrite_menu_select(void) {
    s32 unused;
    if ((p1sw_0 & 1) == 1 && (p1sw_1 & 1) != 1) {
        tilemap_put_block(15, rewrite_cursor * 2 + 9, 2, 32);
        if (--rewrite_cursor < 0) {
            rewrite_cursor = 2;
        }
        if (rewrite_cursor == 2) {
            tilemap_print_string(0, 0, 0xFFFF, rewrite_exit_guide_scr);
        } else {
            tilemap_print_string(0, 0, 0xFFFF, rewrite_guide_scr);
        }
        tilemap_put_block(15, rewrite_cursor * 2 + 9, 2, 62);
    } else if ((p1sw_0 & 2) == 2 && (p1sw_1 & 2) != 2) {
        tilemap_put_block(15, rewrite_cursor * 2 + 9, 2, 32);
        if (++rewrite_cursor > 2) {
            rewrite_cursor = 0;
        }
        if (rewrite_cursor == 2) {
            tilemap_print_string(0, 0, 0xFFFF, rewrite_exit_guide_scr);
        } else {
            tilemap_print_string(0, 0, 0xFFFF, rewrite_guide_scr);
        }
        tilemap_put_block(15, rewrite_cursor * 2 + 9, 2, 62);
    }
    if ((p1sw_0 & 0x10) == 0x10 && (p1sw_1 & 0x10) != 0x10) {
        if (rewrite_cursor == 2) {
            rewrite_no++;
        }
    } else if ((p1sw_0 & 0x1000) == 0x1000 && (p1sw_0 & 0x10) == 0x10) {
        tilemap_fill_all(0, 32);
        task_sleep(1);
        if (rewrite_cursor == 0) {
            bios_vector_restart(0x200, 0);
        } else {
            bios_vector_restart(0x208, 0);
        }
    }
}



/* provisional name */
void rewrite_cd_not_ready(void) {
    tilemap_fill_all(0, 32);
    tilemap_print_string(0, 0, 0xFFFF, rewrite_not_ready_str);
    task_sleep(180);
    rewrite_no = 0;
}



/* provisional name */
s32 rewrite_page(void) {
    register s32 rc;
    if (no_cd_flag) {
        return -1;
    }
    rc = 0;
    switch (rewrite_no) {
    case 0:
        rewrite_menu_init();
        break;
    case 1:
        rewrite_menu_select();
        break;
    case 2:
        if (cd_check_drive_inquiry() == 0 && cd_check_disc_id() == 0) {
            while (scsi_prevent_allow_medium_removal(1, 1)) {
            }
            rc = -1;
            rewrite_no = 0;
        } else {
            rewrite_no++;
        }
        break;
    case 3:
        rewrite_cd_not_ready();
        break;
    }
    return rc;
}
