/*
 * SEL_PL_X3.C  Character select: second mode check
 *
 * PL_Sel_Mode_2 returns 0 in either screen mode (Game_setting.Screen_Mode). It is linked apart from the rest of
 * the select screen.
 */

#include "structs.h"
#include "work.h"
#include "sel_pl.h"

/* provisional name */
s32 PL_Sel_Mode_2(void) {
    if (Game_setting.Screen_Mode == 0) {
        return 0;
    } else {
        return 0;
    }
}
