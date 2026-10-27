/*
 * SEL_FLOW.C  Select flow scene
 *
 * A scene in the style of win_2.c's Winner_Scene / Loser_Scene, run step by step through Scene_Tbl[M_No0] and
 * returning Select_Flow_X (its own WIN_X): clear the screen, set up the background, the colours and the effect G0
 * names, switch the screen in (BGM 1, or 32 while Select_Flow_Akebono is clear), drop the loser's character, wait or cut
 * (Check_Scene_Cut(WINNER)), and end once neither E_Number[0][0] nor E_Number[1][0] is 2.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "SYS_sub.h"
#include "sys_test.h"
#include "se_3.h"
#include "color3rd.h"
#include "cmb_win.h"
#include "aboutspr.h"
#include "textsound.h"
#include "sel_pl.h"
#include "win_2.h"
#include "EffG0.h"

s32 Select_Flow_Scene(void);
void Select_Flow_1st(void);
void Select_Flow_2nd(void);
void Select_Flow_3rd(void);
void Select_Flow_4th(void);
void Select_Flow_5th(void);
void Select_Flow_6th(void);
s32 Check_Select_Flow_Entry(void);


/* provisional name: set, the scene uses the akebono scroll layer (effect G0 type 9, effG0_akebono_setup) instead of
   the type 8 sprite, the names of effg0_name_tbl2, and music 1 instead of 32; nothing in the program sets it */
s8 Select_Flow_Akebono;
s16 Select_Flow_X;   /* provisional name: this scene's WIN_X */


/* provisional name */
s32 Select_Flow_Scene(void) {
    void (*Scene_Tbl[6])() = { Select_Flow_1st, Select_Flow_2nd, Select_Flow_3rd, Select_Flow_4th,
                               Select_Flow_5th, Select_Flow_6th };
    Select_Flow_X = 0;
    Scene_Tbl[M_No0]();
    return Select_Flow_X;
}



/* provisional name */
void Select_Flow_1st(void) {
    M_No0++;
    M_No1 = 0;
    System_all_clear_Wait();
    base_y_pos = 0;
    bg_w.bgw[0].wxy[0].cal = bg_w.bgw[0].xy[0].cal = 0x2000000;
    bg_w.bgw[0].xy[1].cal = 0;
    bg_w.bgw[1].wxy[0].cal = bg_w.bgw[1].xy[0].cal = 0x2000000;
    bg_w.bgw[1].xy[1].cal = 0;
    Bg_Off_R(191);
    load_any_color(4);
    load_any_color(0x86);
    if (Select_Flow_Akebono == 0) {
        load_any_color(0x90);
    }
    effect_G0_init(0, 0);
    effect_G0_init(0, 1);
    effect_G0_init(0, 2);
    effect_G0_init(0, 3);
    effect_G0_init(0, 4);
    effect_G0_init(0, 5);
    effect_G0_init(0, 6);
    effect_G0_init(0, 7);
    if (Select_Flow_Akebono == 0) {
        effect_G0_init(0, 8);
    } else {
        effect_G0_init(0, 9);
    }
    load_any_color(0x88);
    if (Select_Flow_Akebono == 0) {
        load_any_color(0x68);
    }
    load_char_gfx(0x5D30, 1);
    bg_w.scno = 2;
    bg_pos_hosei2();
    Bg_Family_Set();
    Cover_Timer = 24;
}



/* provisional name */
void Select_Flow_2nd(void) {
    switch (M_No1) {
    case 0:
        if (--Cover_Timer) {
            break;
        }
        M_No1++;
        tilemap_fill_all(0, 32);
        Clear_Flash_No();
        commit_name_entry_row_both_players(Text_Page_Y);
        Switch_Screen_Init(0, 1);
        break;
    case 1:
        if (Switch_Screen_Revival()) {
            M_No0++;
            M_Timer = 30;
            Forbid_Break = -1;
            Ignore_Entry[LOSER] = 0;
            if (Select_Flow_Akebono == 0) {
                bgm_request(32);
            } else {
                bgm_request(1);
            }
        }
        break;
    }
}



/* provisional name */
void Select_Flow_3rd(void) {
    if (--M_Timer == 0) {
        M_No0++;
        M_Timer = 300;
        plw[LOSER].wu.operator = 0;
        My_char[LOSER] &= 0x7F;
    }
}



/* provisional name */
void Select_Flow_4th(void) {
    if (--M_Timer == 0) {
        M_No0++;
        M_Timer = 170;
    }
}



/* provisional name */
void Select_Flow_5th(void) {
    if (Check_Scene_Cut(WINNER)) {
        M_Timer = 1;
    }
    if (--M_Timer == 0) {
        M_No0++;
    }
}



/* provisional name */
void Select_Flow_6th(void) {
    if (Check_Select_Flow_Entry()) {
        Select_Flow_X = 1;
    }
}



/* provisional name */
s32 Check_Select_Flow_Entry(void) {
    if (E_Number[0][0] == ENTRY_NAME || E_Number[1][0] == ENTRY_NAME) {
        return 0;
    }
    return 1;
}
