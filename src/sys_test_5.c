/*
 * SYS_TEST_5.C  Coin lockout
 *
 * Routines: coin_lockout_update.
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
#include "sys_test_5.h"
#include "cps3.h"



/* provisional name */
void coin_lockout_update(void) {
    if (Free_Play != 0) {
        coin_lock_set(-1);
    } else {
        switch (Chute_Mode) {
        case 0:
        case 3:
        case 7:
            coin_lock_check(0, 0);
            coin_lock_set(1);
            break;
        case 1:
            coin_lock_check(0, 0);
            coin_lock_check(0, 1);
            break;
        case 2:
            coin_lock_check(0, 0);
            coin_lock_check(1, 1);
            break;
        case 4:
        case 8:
            coin_lock_check(0, 0);
            coin_lock_check(0, 2);
            break;
        case 5:
            coin_lock_check(0, 0);
            coin_lock_check(0, 1);
            coin_lock_check(0, 2);
            break;
        case 6:
            coin_lock_check(0, 0);
            coin_lock_check(1, 1);
            coin_lock_check(2, 2);
            break;
        case 9:
            coin_lock_check(0, 0);
            coin_lock_check(2, 2);
            break;
        case 10:
            coin_lock_check(0, 0);
            coin_lock_check(0, 1);
            coin_lock_check(0, 2);
            coin_lock_check(0, 3);
            break;
        case 11:
            coin_lock_check(0, 0);
            coin_lock_check(1, 1);
            coin_lock_check(2, 2);
            coin_lock_check(3, 3);
            break;
        }
    }
}
