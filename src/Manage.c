/*
 * MANAGE.C  FBI warning screen
 *
 * FBI_Warning runs the FBI warning screen through FBI_Warning_1st (FBI_Warning_2nd is empty).
 * attract_menu_str holds the attract sequence titles and the coin and start prompts; nothing reads it.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "manage_2.h"
#include "Manage.h"
#include "SYS_sub.h"
#include "aboutspr.h"
#include "demo00.h"
#include "demo01.h"
#include "demo02_code.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sc_trans.h"
#include "cmb_win.h"
#include "VITAL.h"
#include "count.h"
#include "spgauge.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "eff87.h"
#include "eff88.h"
#include "eff89.h"
#include "eff90.h"
#include "eff91.h"
#include "eff92_code.h"
#include "Eff93.h"
#include "EffG0.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "Eff81.h"
#include "effb2.h"
#include "appear.h"
#include "ta_sub.h"
#include "eff35.h"
#include "eff56.h"
#include "eff57.h"
#include "EFF58.h"
#include "Eff76.h"
#include "EFF84.h"
#include "bg000.h"
#include "win_2.h"
#include "continue.h"
#include "pow_pow.h"
#include "end_main.h"
#include "Entry.h"
#include "entry_2.h"



extern const s8 str_199X_CAPCOM[];
extern const s8 str_EYE_CATCH_Part1[];
extern const s8 str_EYE_CATCH_Part2[];
extern const s8 str_FBI[];
extern const s8 str_INSERT_COIN_2[];
extern const s8 str_PLAY_DEMO[];
extern const s8 str_PUSH_1_OR_2_START_BUTTON[];
extern const s8 str_Q_SOUND[];
extern const s8 str_RANKING[];
extern const s8 str_SELECT_PLAYER[];
extern const s8 str_SELECT_PLAYER_2[];
extern const s8 str_STREET_FIGHTER_III_2[];
extern const s8 str_blank_3[];



/* 02000C88 */
/* The attract sequence titles and the coin / start prompts at two screen positions; nothing in the
   program reads them (provisional name). */
TM_STRING attract_menu_str[24] = {
    { 19, 8, 0xE, str_Q_SOUND },
    { 16, 8, 0xE, str_EYE_CATCH_Part1 },
    { 16, 8, 0xE, str_EYE_CATCH_Part2 },
    { 14, 8, 0xE, str_STREET_FIGHTER_III_2 },
    { 18, 19, 0xE, str_199X_CAPCOM },
    { 16, 8, 0xE, str_PLAY_DEMO },
    { 16, 8, 0xE, str_RANKING },
    { 16, 8, 0xE, str_FBI },
    { 27, 8, 0xE, str_Q_SOUND },
    { 24, 8, 0xE, str_EYE_CATCH_Part1 },
    { 24, 8, 0xE, str_EYE_CATCH_Part2 },
    { 22, 8, 0xE, str_STREET_FIGHTER_III_2 },
    { 24, 19, 0xE, str_199X_CAPCOM },
    { 24, 8, 0xE, str_PLAY_DEMO },
    { 24, 8, 0xE, str_RANKING },
    { 24, 8, 0xE, str_FBI },
    { 16, 8, 0xE, str_SELECT_PLAYER },
    { 24, 8, 0xE, str_SELECT_PLAYER_2 },
    { 18, 13, 0xE, str_INSERT_COIN_2 },
    { 18, 13, 0xE, str_blank_3 },
    { 11, 12, 0xE, str_PUSH_1_OR_2_START_BUTTON },
    { 26, 13, 0xE, str_INSERT_COIN_2 },
    { 26, 13, 0xE, str_blank_3 },
    { 19, 12, 0xE, str_PUSH_1_OR_2_START_BUTTON },
};


/* provisional name */
void FBI_Warning(void) {
    void (*jmp_tbl[2])() = { FBI_Warning_1st, FBI_Warning_2nd };
    jmp_tbl[D_No0]();
}



/* provisional name */
void FBI_Warning_1st(void) {
    s16 x;
    switch (D_No1) {
    case 0:
        D_No1++;
        D_Timer = 120;
        Set_Mode_Pos(&x, 8, 21);
        tilemap_print_string_attr(x, 8, 18, FBI_msg);    /* Warning text. */
        break;
    case 1:
        if (--D_Timer) {
            break;
        }
        D_No1++;
        scfont_page0_fill(0, 32);
        D_Timer = 40;
        break;
    case 2:
        if (--D_Timer == 0) {
            if (G_No1 == 12) {
                G_No1 = 1;
                D_No0 = D_No1 = D_No2 = D_No3 = 0;
                return;
            } else {
                G_No1++;
                D_No0 = D_No1 = D_No2 = D_No3 = 0;
            }
        }
        break;
    }
}



/* provisional name */
void FBI_Warning_2nd(void) {}



