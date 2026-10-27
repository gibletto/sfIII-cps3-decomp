/*
 * DEMO00.C  Attract mode: logos
 *
 * CAPCOM_Logo runs the warning, CAPCOM logo and other intro screens (Logo_Warning,
 * Logo_Capcom, Logo_Etc). Driven by the attract sequence in Game_Main.
 *
 * The warning screen's text (parental_advisory_msg) is initialized data in D.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Game_Main.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "Entry.h"
#include "entry_2.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "SYS_sub.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "cmb_win.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "eeprom.h"
#include "sc_trans.h"
#include "bg000.h"
#include "lose_pl.h"
#include "PLS02.h"
#include "SLOWF.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "demo00.h"

/* D_No1 in Logo_Capcom */
#define LC_INIT         0       /* clear the screen and set up */
#define LC_PAUSE        1       /* wait D_Timer */
#define LC_ANIM         2       /* capcom_logo_anim */
#define LC_FADE_OUT     3       /* request the fade out */
#define LC_FADE_OUT_WAIT 4      /* until it is done, then the next screen */

/* D_No1 in Logo_Warning and Logo_Etc */
#define LW_INIT         0       /* set up */
#define LW_PAUSE        1       /* wait D_Timer, then show it */
#define LW_SHOW         2       /* show it for D_Timer, then fade out */
#define LW_FADE_WAIT    3       /* until the fade is done, then the next screen */
/* provisional name */
s32 CAPCOM_Logo(void) {
    void (*jmp_tbl[3])() = { Logo_Capcom, Logo_Warning, Logo_Etc };
    Next_Demo = 0;
    jmp_tbl[D_No0]();
    return Next_Demo;
}



/* provisional name */
void Logo_Capcom(void) {
    switch (D_No1) {
    case LC_INIT:
        D_No1++;
        tilemap_fill_all(0, 32);
        System_all_clear_Wait();
        bg_etc_write(4);
        bg_pos_hosei2();
        Bg_Family_Set();
        D_Timer = 12;
        break;
    case LC_PAUSE:
        if (--D_Timer <= 0) {
            D_No1++;
            ToneDown(0);
        }
        break;
    case LC_ANIM:
        if (capcom_logo_anim()) {
            D_No1++;
        }
        break;
    case LC_FADE_OUT:
        if (Request_Fade(36, 0)) {
            D_No1++;
            scfont_page1_fill(62, 30);
        }
        break;
    case LC_FADE_OUT_WAIT:
        if (Check_Fade_Complete()) {
            D_No1++;
        }
        break;
    default:
        Next_Demo = 1;
        break;
    }
}



/* provisional name */
void Logo_Warning(void) {
    switch (D_No1) {
    case LW_INIT:
        D_No1++;
        D_Timer = 10;
        scfont_page0_fill(0, 32);
        tilemap_print_string(DE_X[3], 0, 0xFFFF, parental_advisory_msg);
        break;
    case LW_PAUSE:
        if (--D_Timer) {
            break;
        }
        D_No1++;
        D_Timer = 120;
        Scrn_Move_Set(4, 0, 0);
        break;
    case LW_SHOW:
        if (--D_Timer) {
            break;
        }
        if (Request_Fade(34, 0)) {
            D_No1++;
        } else {
            D_Timer = 1;
        }
        break;
    case LW_FADE_WAIT:
        if (Check_Fade_Complete()) {
            D_No1++;
        }
        break;
    default:
        Next_Demo = 1;
        break;
    }
}



/* provisional name */
void Logo_Etc(void) {
    switch (D_No1) {
    case LW_INIT:
        D_No1++;
        D_Timer = 10;
        scfont_page0_fill(0, 32);
        System_all_clear_Wait();
        bg_etc_write(3);
        bg_pos_hosei2();
        Bg_Family_Set();
        break;
    case LW_PAUSE:
        if (--D_Timer) {
            break;
        }
        D_No1++;
        D_Timer = 120;
        Scrn_Move_Set(4, 0, 0);
        break;
    case LW_SHOW:
        if (--D_Timer) {
            break;
        }
        if (Request_Fade(36, 0)) {
            D_No1++;
        } else {
            D_Timer = 1;
        }
        break;
    case LW_FADE_WAIT:
        if (Check_Fade_Complete()) {
            D_No1++;
        }
        break;
    default:
        Next_Demo = 1;
        break;
    }
}



