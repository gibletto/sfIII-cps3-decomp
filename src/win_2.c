/*
 * WIN_2.C  Winner and loser scenes
 *
 * Scene routines called from Game_Main between matches. Winner_Scene and Loser_Scene run the win and
 * lose screens step by step through one table each: Win_1st to Win_7th set up the background, the
 * colours and the effects, switch the screen in and start the BGM (Check_Win_BGM picks it),
 * count down and wait for a button (Check_Scene_Cut); the loser's own steps Lose_4th, Lose_6th and
 * Lose_7th clear the loser's character and fade out. Both return WIN_X, 1 when the scene is over.
 *
 * The win screen loads colours 11 and 12, moves the first background layer 22 to the side of the winner
 * (+22 for player 2, -22 for player 1) and the second layer back by as much, and always starts effect 58.
 * Win_Record is a byte per player.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "eff87.h"
#include "eff88.h"
#include "eff89.h"
#include "eff90.h"
#include "eff91.h"
#include "eff92_code.h"
#include "Eff93.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "SYS_sub.h"
#include "end_main.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sc_trans.h"
#include "cmb_win.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "EFF49.h"
#include "eff56.h"
#include "eff57.h"
#include "EFF58.h"
#include "Eff76.h"
#include "EFFA7.h"
#include "effa8.h"
#include "effa9.h"
#include "aboutspr.h"
#include "bg000.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "continue.h"
#include "pow_pow.h"
#include "win_2.h"
#include "fighter.h"



/* effect_95_init takes the kind and the player, effect_B8_init the player only */
s32 effect_95_init();
s32 effect_B8_init();


s16 WIN_X;



s16 Winner_Scene(void) {
    void (*Scene_Tbl[7])() = { Win_1st, Win_2nd, Win_3rd, Win_4th, Win_5th, Win_6th, Win_7th };
    WIN_X = 0;
    Scene_Tbl[M_No0]();
    if (Break_Into) {
        return 0;
    } else {
        return WIN_X;
    }
}



void Win_1st(void) {
    M_No0++;
    Cover_Timer = 24;
}



void Win_2nd(void) {
    s16 ofs;
    M_No0++;
    M_No1 = 0;
    Suicide = 0;
    System_all_clear_Wait();
bg_set:;
    base_y_pos = 40;
    bg_etc_write(0);
    bg_pos_hosei2();
    Bg_Family_Set();
    if (WINNER == 1) {
        ofs = 22;
    } else {
        ofs = -22;
    }
    bg_w.bgw[0].position_x += ofs;
    bg_w.bgw[1].position_x = bg_w.bgw[0].position_x - ofs;
    bg_w.bgw[1].position_y = bg_w.bgw[0].position_y;
    bg_w.bgw[0].xy[0].disp.pos += ofs;
    bg_w.bgw[1].xy[0].disp.pos = bg_w.bgw[0].xy[0].disp.pos - ofs;
    bg_w.bgw[1].xy[1].disp.pos = bg_w.bgw[0].xy[1].disp.pos;
    Bg_Family_Set_Ex(1);
    load_any_color(11);
    load_any_color(12);
    load_any_color(4);
    load_any_color(0x86);
    win_slide_flag = 1;
    effect_95_init(13, WINNER);
    effect_95_init(0, LOSER);
    effect_B8_init(WINNER);
    effect_58_init(4, 1, -1);
    effect_H3_init();
}



void Win_3rd(void) {
    switch (M_No1) {
    case 0:
        if (--Cover_Timer) {
            break;
        }
        M_No1++;
        tilemap_fill_all(0, 32);
        Clear_Flash_No();
        commit_name_entry_row_both_players(Text_Page_Y);
        if (G_No1 == 3) {
            Scrn_Move_Set(4, 0, 0x100);
        }
        Switch_Screen_Init(0, 1);
        break;
    case 1:
        if (Switch_Screen_Revival()) {
            M_No0++;
            M_Timer = 30;
            Forbid_Break = -1;
            Ignore_Entry[LOSER] = 0;
            if (Play_Type == 0) {
                bgm_request(4);
            } else if (Check_Win_BGM()) {
                bgm_request(4);
            } else {
                bgm_request(5);
            }
        }
        break;
    }
}



void Win_4th(void) {
    if (--M_Timer == 0) {
        M_No0++;
        M_Timer = 1;
    }
}



void Win_5th(void) {
    if (--M_Timer == 0) {
        M_No0++;
        M_Timer = 170;
        Forbid_Break = 0;
    }
}



void Win_6th(void) {
    if (Check_Scene_Cut(WINNER)) {
        M_Timer = 1;
    }
    if (--M_Timer == 0) {
        M_No0++;
        WIN_X = 1;
    }
}



void Win_7th(void) {
    WIN_X = 1;
}



s16 Loser_Scene(void) {
    void (*Scene_Tbl[8])() = { Win_1st, Win_2nd, Win_3rd, Lose_4th, Win_5th, Lose_6th, Lose_7th, Win_7th };
    WIN_X = 0;
    Scene_Tbl[M_No0]();
    if (Break_Into) {
        return 0;
    } else {
        return WIN_X;
    }
}



void Lose_4th(void) {
    if (--M_Timer == 0) {
        M_No0++;
        if (Request_Break[0] != 0 || Request_Break[1] != 0) {
            M_Timer = 30;
        } else {
            M_Timer = 120;
        }
        plw[LOSER].wu.operator = 0;
        My_char[LOSER] &= 0x7F;
    }
}



void Lose_6th(void) {
    if (Check_Scene_Cut(LOSER)) {
        M_Timer = 1;
    }
    if (--M_Timer == 0) {
        if (Request_Fade(38, 0)) {
            M_No0++;
            Forbid_Break = 0;
        } else {
            M_Timer = 1;
        }
    }
}



void Lose_7th(void) {
    if (Check_Fade_Complete_SP()) {
        M_No0++;
        Suicide = 1;
        if (Break_Into == 0) {
            WIN_X = 1;
        }
    }
}



s32 Check_Scene_Cut(id)
s16 id;
{
    if (id) {
        return p2sw_0 & 0x7F0;
    }
    return p1sw_0 & 0x7F0;
}



s32 Check_Win_BGM(void) {
    if (Win_Record[WINNER] == 0) {
        return 1;
    }
    return Win_Record[WINNER] % 10;
}
