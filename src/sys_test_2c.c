/*
 * SYS_TEST_2C.C  Test mode: configuration menu page
 *
 * config_menu_page runs the configuration menu (config_menu_run) as a test mode page and resets its
 * state when the menu returns.
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
#include "sys_test_2c.h"
#include "cps3.h"



s16 config_menu_no = 0;  /* 02007CAC */


/* provisional name */
s16 config_menu_page(void) {
    register s16 rc;
    switch (config_menu_no) {
    case 0:
        Config_No_0 = 0;
        rc = 0;
        config_menu_no++;
        break;
    case 1:
        rc = config_menu_run();
        break;
    }
    if (rc != 0) {
        config_menu_no = 0;
    }
    return rc;
}
