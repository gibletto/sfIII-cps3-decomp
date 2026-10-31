/*
 * COLORTEST.C  Test mode: colour test page
 *
 * colortest_* is the palette grid test.
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

/* colortest_no: the colour test page step */
#define COLOR_TITLE     0       /* colortest_draw_title */
#define COLOR_GRID      1       /* colortest_draw_palette_grid */
#define COLOR_SHOW      2       /* the grid is up */

s16 colortest_no = 0;  /* 02007148 */


void tilemap_put_block(s32 x, s32 y, s32 attr, u16 code);



/* provisional name */
void colortest_draw_title(void) {
    tilemap_fill_all(0, 32);
    tilemap_print_string(0, 0, 0xFFFF, colortest_scr);
    palette_write(0, colortest_palette, 0x85);
    colortest_no++;
}



/* provisional name */
void colortest_draw_palette_grid(void) {
    register s16 i;
    register s16 j;
    register s16 k;
    register s32 x;
    register s32 y;
    register s16 bank;
    x = 10;
    y = 5;
    bank = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 16; k++) {
                tilemap_put_block(x, y, (i * 2 + bank) * 2, k + 16);
                x++;
            }
            switch (i) {
            case 0:
                tilemap_put_block(x, y, 16, 17);
                break;
            case 1:
                tilemap_put_block(x, y, 16, 18);
                break;
            case 2:
                tilemap_put_block(x, y, 16, 19);
                break;
            case 3:
                tilemap_put_block(x, y, 16, 20);
            }
            x++;
            for (k = 0; k < 15; k++) {
                tilemap_put_block(x, y, (i * 2 + bank + 1) * 2, k + 17);
                x++;
            }
            x = 10;
            y++;
        }
        y++;
    }
    colortest_no++;
}



/* provisional name */
s32 colortest_page(void) {
    register s32 rc;
    switch (colortest_no) {
    case COLOR_TITLE:
        colortest_draw_title();
        break;
    case COLOR_GRID:
        colortest_draw_palette_grid();
        break;
    case COLOR_SHOW:
        break;
    }
    if ((p1sw_0 & BUTTON_START) && (p1sw_0 & BUTTON_LP)) {
        rc = -1;
        colortest_no = COLOR_TITLE;
        return rc;
    }
    rc = 0;
    return rc;
}
