/*
 * SYS_TEST_2.C  Test mode: switch input test page
 *
 * iotest_draw_sw_grid draws the switch grid; iotest_input_page is the switch input test page.
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

s16 iotest_in_no = 0;  /* 02007C90 */



/* provisional name */
void iotest_draw_sw_grid(void) {
    register s16 i;
    register s16 j;
    register s16 diag1;
    register s16 diag2;
    i = j = 0;
    diag1 = diag2 = 0;
    for (; i < 4; i++, j += 2) {
        if ((iotest_diag_bit_tbl[i] & p1sw_0) == iotest_diag_bit_tbl[i]) {
            tilemap_print_string_attr(iotest_1p_diag_x[j], iotest_1p_diag_y[j], 8, iotest_on_str);
            diag1 = 1;
        } else {
            tilemap_print_string_attr(iotest_1p_diag_x[j], iotest_1p_diag_y[j], 2, iotest_off_str);
        }
        if ((iotest_diag_bit_tbl[i] & p2sw_0) == iotest_diag_bit_tbl[i]) {
            tilemap_print_string_attr(iotest_2p_diag_x[j], iotest_2p_diag_y[j], 8, iotest_on_str);
            diag2 = 1;
        } else {
            tilemap_print_string_attr(iotest_2p_diag_x[j], iotest_2p_diag_y[j], 2, iotest_off_str);
        }
    }
    i = j = 0;
    for (; j < 12; i += 2, j++) {
        if (iotest_sw_bit_tbl[j] & p1sw_0) {
            if (j < 4) {
                if (diag1) {
                    tilemap_print_string_attr(iotest_1p_sw_x[i], iotest_1p_sw_y[i], 2, iotest_off_str);
                } else {
                    tilemap_print_string_attr(iotest_1p_sw_x[i], iotest_1p_sw_y[i], 8, iotest_on_str);
                }
            } else {
                tilemap_print_string_attr(iotest_1p_sw_x[i], iotest_1p_sw_y[i], 8, iotest_on_str);
            }
        } else {
            tilemap_print_string_attr(iotest_1p_sw_x[i], iotest_1p_sw_y[i], 2, iotest_off_str);
        }
        if (iotest_sw_bit_tbl[j] & p2sw_0) {
            if (j < 4) {
                if (diag2) {
                    tilemap_print_string_attr(iotest_2p_sw_x[i], iotest_2p_sw_y[i], 2, iotest_off_str);
                } else {
                    tilemap_print_string_attr(iotest_2p_sw_x[i], iotest_2p_sw_y[i], 8, iotest_on_str);
                }
            } else {
                tilemap_print_string_attr(iotest_2p_sw_x[i], iotest_2p_sw_y[i], 8, iotest_on_str);
            }
        } else {
            tilemap_print_string_attr(iotest_2p_sw_x[i], iotest_2p_sw_y[i], 2, iotest_off_str);
        }
    }
    for (i = 0; i < 3; i++) {
        if (i != 1) {
            if (iotest_sys_bit_tbl[i] & syssw_0) {
                tilemap_print_string_attr(iotest_sys_sw_x[i * 2], iotest_sys_sw_y[i * 2], 8, iotest_on_str);
            } else {
                tilemap_print_string_attr(iotest_sys_sw_x[i * 2], iotest_sys_sw_y[i * 2], 2, iotest_off_str);
            }
        }
    }
}



/* provisional name */
s32 iotest_input_page(void) {
    register s32 rc;
    switch (iotest_in_no) {
    case 0:
        tilemap_fill_all(0, 32);
        tilemap_print_string(0, 0, 0xFFFF, iotest_input_scr);
        iotest_in_no++;
        break;
    case 1:
        iotest_draw_sw_grid();
        break;
    }
    if ((p1sw_0 & 0x1000) && (p1sw_0 & 0x10)) {
        rc = -1;
        iotest_in_no = 0;
        return rc;
    }
    rc = 0;
    return rc;
}
