/*
 * COIN_CHUTE.C  Coin chutes and the service coin (provisional object name)
 *
 * Routines: coin_chutes_update, service_coin_check. Linked as an object of its own after the system
 * font (sys_font_cg).
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


/* provisional name */
void coin_chutes_update(s32 keep) {
    switch (Chute_Mode) {
    case 0:
    case 3:
    case 7:
        if (coin_chute_check(0, keep)) {
            coin_credit_add(0, 0);
        }
        coin_counter_drive(0);
        break;
    case 1:
        if (coin_chute_check(0, keep)) {
            coin_credit_add(0, 0);
        }
        if (coin_chute_check(1, keep)) {
            coin_credit_add(0, 0);
        }
        coin_counter_drive(0);
        break;
    case 2:
        if (coin_chute_check(0, keep)) {
            coin_credit_add(0, 0);
        }
        if (coin_chute_check(1, keep)) {
            coin_credit_add(1, 0);
        }
        coin_counter_drive(0);
        break;
    case 4:
    case 8:
        if (coin_chute_check(0, keep)) {
            coin_credit_add(0, 0);
        }
        if (coin_chute_check(2, keep)) {
            coin_credit_add(0, 0);
        }
        coin_counter_drive(0);
        break;
    case 5:
        if (coin_chute_check(0, keep)) {
            coin_credit_add(0, 0);
        }
        if (coin_chute_check(1, keep)) {
            coin_credit_add(0, 0);
        }
        if (coin_chute_check(2, keep)) {
            coin_credit_add(0, 0);
        }
        coin_counter_drive(0);
        break;
    case 6:
        if (coin_chute_check(0, keep)) {
            coin_credit_add(0, 0);
        }
        if (coin_chute_check(1, keep)) {
            coin_credit_add(1, 0);
        }
        if (coin_chute_check(2, keep)) {
            coin_credit_add(2, 0);
        }
        coin_counter_drive(0);
        break;
    case 9:
        if (coin_chute_check(0, keep)) {
            coin_credit_add(0, 0);
        }
        if (coin_chute_check(2, keep)) {
            coin_credit_add(2, 0);
        }
        coin_counter_drive(0);
        break;
    case 10:
        if (coin_chute_check(0, keep)) {
            coin_credit_add(0, 0);
        }
        if (coin_chute_check(1, keep)) {
            coin_credit_add(0, 0);
        }
        if (coin_chute_check(2, keep)) {
            coin_credit_add(0, 0);
        }
        if (coin_chute_check(3, keep)) {
            coin_credit_add(0, 0);
        }
        coin_counter_drive(0);
        break;
    case 11:
        if (coin_chute_check(0, keep)) {
            coin_credit_add(0, 0);
        }
        if (coin_chute_check(1, keep)) {
            coin_credit_add(1, 0);
        }
        if (coin_chute_check(2, keep)) {
            coin_credit_add(2, 0);
        }
        if (coin_chute_check(3, keep)) {
            coin_credit_add(3, 0);
        }
        coin_counter_drive(0);
        break;
    }
}



/* provisional name */
void service_coin_check(void) {
    if ((syssw_0 & 1) && !(syssw_1 & 1)) {
        bookkeep_service_count();
        coin_in_flag = 1;
        switch (Chute_Mode) {
        case 0:
        case 1:
        case 3:
        case 4:
        case 5:
        case 7:
        case 8:
        case 10:
            credit_1p++;
            coin_chute1_w.dropped = 1;
            if (credit_1p > 9) {
                credit_1p = 9;
            }
            break;
        case 2:
        case 9:
            credit_1p++;
            coin_chute1_w.dropped = 1;
            if (credit_1p > 9) {
                credit_1p = 9;
            }
            credit_2p++;
            coin_chute2_w.dropped = 1;
            if (credit_2p > 9) {
                credit_2p = 9;
            }
            break;
        case 6:
            credit_1p++;
            coin_chute1_w.dropped = 1;
            if (credit_1p > 9) {
                credit_1p = 9;
            }
            credit_2p++;
            coin_chute2_w.dropped = 1;
            if (credit_2p > 9) {
                credit_2p = 9;
            }
            credit_3p++;
            coin_chute3_w.dropped = 1;
            if (credit_3p > 9) {
                credit_3p = 9;
            }
            break;
        case 11:
            credit_1p++;
            coin_chute1_w.dropped = 1;
            if (credit_1p > 9) {
                credit_1p = 9;
            }
            credit_2p++;
            coin_chute2_w.dropped = 1;
            if (credit_2p > 9) {
                credit_2p = 9;
            }
            credit_3p++;
            coin_chute3_w.dropped = 1;
            if (credit_3p > 9) {
                credit_3p = 9;
            }
            credit_4p++;
            coin_chute4_w.dropped = 1;
            if (credit_4p > 9) {
                credit_4p = 9;
            }
            break;
        }
    }
}
