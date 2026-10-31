/*
 * SYS_TEST_2A.C  Test mode: screen test page
 *
 * screentest_draw_crosshatch and screentest_page are the crosshatch screen test.
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

/* screentest_no: the screen test page step */
#define SCREEN_DRAW     0       /* screentest_draw_crosshatch */
#define SCREEN_SHOW     1       /* the crosshatch is up */

s16 screentest_no = 0;  /* 0200714C */


/* provisional name */
void screentest_draw_crosshatch(void) {
    register s16 x;
    register s16 y;
    register s16 attr;
    register s16 cols;
    register s16 rows;
    register u16* p;
    switch (screen_mode) {
    case 3:
        cols = 24;
        break;
    case 7:
        cols = 31;
    }
    rows = 14;
    tilemap_fill_all(0, 32);
    p = (u16*)SS_RAM_CACHED;
    for (y = 0; y < rows; y++, p += 0x100 - cols * 4) {
        for (x = 0; x < cols; x++, p += 4) {
            if (y == 0 || x == 0 || x == cols - 1 || y == rows - 1) {
                attr = 8;
            } else {
                attr = 2;
            }
            p[0] = 127;
            p[1] = attr;
            p[2] = 127;
            p[3] = attr | 0x80;
            p[0x80] = 127;
            p[0x81] = attr | 0x40;
            p[0x82] = 127;
            p[0x83] = attr | 0xC0;
        }
    }
    tilemap_print_string(0, 0, 0xFFFF, crosshatch_scr);   /* Crosshatch screen text. */
    screentest_no++;
}



/* provisional name */
s32 screentest_page(void) {
    register s32 rc;
    switch (screentest_no) {
    case SCREEN_DRAW:
        screentest_draw_crosshatch();
        break;
    case SCREEN_SHOW:
        break;
    }
    if ((p1sw_0 & BUTTON_START) && (p1sw_0 & BUTTON_LP)) {
        rc = -1;
        screentest_no = SCREEN_DRAW;
        return rc;
    }
    rc = 0;
    return rc;
}
