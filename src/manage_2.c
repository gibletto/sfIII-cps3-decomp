/*
 * MANAGE_2.C  Round and match management (part 2)
 *
 * Game_Management is called every fight frame (Game2_1) and steps through the C_No phases: stage setup, round
 * call and fight start, the fight, KO / time over judgement (Judge_Winner, Check_Perfect, win marks via
 * Setup_Win_Mark and effect_92_init), winner display and win poses (Disp_Winner), the bonus tally
 * (Additional_Bonus, Bonus_Cut_All), match end, continue and break-in handling (Loser_Sub, Be_Continue,
 * Quick_Entry) and the versus win record (Ck_Win_Record, Disp_Win_Record). It also runs BGM_Fade_Sub.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "manage_2.h"
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
#include "sc_clear.h"
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
s32 effect_58_init();
#include "Eff76.h"
#include "EFF84.h"
#include "bg000.h"
#include "win_2.h"
#include "continue.h"
#include "pow_pow.h"
#include "end_main_c.h"
#include "Entry.h"
#include "entry_2.h"

#include "EFF78.h"

/* C_No2, Game_Manage_8th */
#define CM8_S_WAIT      0       /* wait C_Timer; a button cuts it short */
#define CM8_S_WAIT11    0       /* count down C_Timer */
#define CM8_S_WAIT2     1       /* wait C_Timer; a button cuts it short */
#define CM8_S_WAIT12    1       /* wait C_Timer; a button cuts it short */
#define CM8_S_WAIT3     2       /* wait C_Timer; a button cuts it short */
#define CM8_S_WAIT4     3       /* wait C_Timer; a button cuts it short */
#define CM8_S_WAIT5     4       /* wait C_Timer; a button cuts it short */
#define CM8_S_WAIT6     5       /* wait C_Timer; a button cuts it short */
#define CM8_S_WAIT7     6       /* wait C_Timer; a button cuts it short */
#define CM8_S_WAIT8     7       /* wait C_Timer; a button cuts it short */
#define CM8_S_WAIT9     8       /* wait C_Timer; a button cuts it short */
#define CM8_S_WAIT10    9       /* wait C_Timer; a button cuts it short */

/* C_No1, Game_Manage_2nd */
#define CM2_MESSAGE     0       /* until the message is gone */
#define CM2_REVIVAL     1       /* until the wipe in is done */
#define CM2_ROUND_START 2       /* start effect 84 and clear the round's flags */
#define CM2_APPEAR      3       /* until both entries are over and the controls are ready */

/* C_No1, Game_Manage_5th */
#define CM5_VICTORY     0       /* until the win is shown */
#define CM5_ANNOUNCE    1       /* wait C_Timer (a button cuts it short), then message 3 */
#define CM5_MESSAGE     2       /* until the message is gone */
#define CM5_WIPE        3       /* start the wipe */
#define CM5_WIPE_WAIT   4       /* until the wipe is done */
#define CM5_WIPE2       5       /* start the wipe */
#define CM5_REVIVAL     6       /* until the wipe in is done */
#define CM5_WAIT        7       /* count down C_Timer */

/* C_No1, Game_Manage_6th */
#define CM6_VICTORY     0       /* until the win is shown */
#define CM6_WAIT        1       /* count down C_Timer */

/* C_No1, Game_Manage_7th */
#define CM7_VICTORY     0       /* until the win is shown */
#define CM7_WAIT        1       /* count down C_Timer */
#define CM7_WINNER      2       /* wait C_Timer (a button cuts it short), then show the winner */
#define CM7_CLEAR       3       /* wait C_Timer (a button cuts it short), then clear the winner text */
#define CM7_WAIT2       4       /* count down C_Timer */
#define CM7_MESSAGE     5       /* until the message is gone */
#define CM7_WAIT3       6       /* wait C_Timer; a button cuts it short */
#define CM7_WAIT4       90      /* count down C_Timer */
#define CM7_GALS        91      /* until the gals event is over, then record the win */
#define CM7_WAIT5       92      /* count down C_Timer */

/* C_No1, Game_Manage_8th */
#define CM8_START       0       /* the next round number; bonus or skip */
#define CM8_WAIT        1       /* wait C_Timer; a button cuts it short */
#define CM8_WAIT2       2       /* wait C_Timer; a button cuts it short */
#define CM8_WAIT3       3       /* wait C_Timer; a button cuts it short */
#define CM8_WAIT4       4       /* wait C_Timer; a button cuts it short */

/* C_No1, Game_Manage_9th */
#define CM9_WIPE        0       /* start the wipe */
#define CM9_WAIT        1       /* wait C_Timer; a button cuts it short */

/* C_No1, Game_Manage_10th */
#define CM10_WAIT       0       /* wait C_Timer; a button cuts it short */
#define CM10_WIPE_WAIT  1       /* until the wipe is done */

/* BGM_No: the music fade-in (BGM_Fade_Sub) */
#define BGMF_NONE       0       /* nothing to do */
#define BGMF_WAIT       1       /* wait BGM_Timer, then (default) raise the volume */


void sound_reg_level_set(s16 pitch, s8 volume);

s32 effect_32_init(void);
s32 PL_Sel_Mode_2(void);
s16 gauge_rank_value(s16 v);
void Restore_Loser_Score(void);
s16 Next_VS_Index(void);
s32 Bonus_Cut_All(void);
void Bonus_Count_Effect(s16 n);
void Stock_Loser_Char(void);
extern u8 Straight_Win_Count;  /* provisional name */
extern u8 Straight_Lose_Count;  /* provisional name */
extern const u16 bg_color3_tbl[];  /* provisional name */
#pragma inline(request_center_message)

/* the timer runs out, or a held button cuts it short */
#define BUTTON_CUT_EX(timer, n) (--*(timer) == 0 || Button_Cut_Hold((timer), (n), (n)))



void Game_Management(void) {
    void (*Management_Jmp_Tbl[10])() = { Game_Manage_1st, Game_Manage_2nd, Game_Manage_3rd, Game_Manage_4th, Game_Manage_5th, Game_Manage_6th, Game_Manage_7th, Game_Manage_8th, Game_Manage_9th, Game_Manage_10th };
    if (Break_Into) {
        return;
    }
    Management_Jmp_Tbl[C_No0]();
    BGM_Fade_Sub();
}



void Game_Manage_1st(void) {
    C_No0++;
    win_pause_go = 0;
    if (bg_w.bgw[1].zuubun) {
        zuubun_base_x = 0x200;
    }
    appear_work_clear();
    win_sp_flag = 0;
    BGM_No = BGMF_NONE;
    if (Play_Type == PLAY_VS_CPU) {
        paring_ctr_ori[Player_id] = paring_ctr_vs[0][Player_id] = 0;
    }
    eff_hit_flag_clear();
    Stage_BGM();
    Fade_Flag = 0;
}



void Game_Manage_2nd(void) {
    switch (C_No1) {
    case CM2_MESSAGE:
        request_message = 0;
        if (Demo_Flag == 0 && !(exsw_2 & 0x10)) {
            C_No1 = CM2_ROUND_START;
            effect_32_init();
            PL_Sel_Mode_2();
            break;
        }
        if (--Cover_Timer != 0) {
            break;
        }
        C_No1++;
        Switch_Screen_Init(3, 3);
        effect_32_init();
        PL_Sel_Mode_2();
        break;
    case CM2_REVIVAL:
        if (Switch_Screen_Revival()) {
            C_No1++;
        }
        break;
    case CM2_ROUND_START:
        if (!effect_84_init()) {
            C_No1++;
            Forbid_Break = 0;
            Complete_Victory = 0;
            Conclusion_Flag = 0;
            Perfect_Flag = 0;
            Round_Result = 0;
            Reserve_Cut = 0;
            Next_Step = 0;
            Judge_Round_Flag = 0;
            Stop_Combo = 0;
            if (Demo_Flag) {
                Stop_SG = 0;
            }
            Complete_Judgement = 0;
            judge_flag = 0;
            Music_Fade = 0;
            Round_Operator[0] = plw[0].wu.operator;
            Round_Operator[1] = plw[1].wu.operator;
            CP_No[0][0] = COM_INIT;
            CP_No[1][0] = COM_INIT;
        }
        break;
    case CM2_APPEAR:
        if (Appear_end < 2) {
            break;
        }
        appear_work_clear();
        win_sp_flag = 0;
        if (pcon_rno[0] == PCON_INIT && pcon_rno[1] == APP_WAIT_READY) {
            C_No1++;
            effect_B2_init();
        }
        break;
    default:
        if (Next_Step != 0) {
            C_No0++;
            C_No1 = CM2_MESSAGE;
            Allow_a_battle_f = 1;
            load_char_eff_color(My_char[0], 0);
            load_char_eff_color(My_char[1], 1);
        }
        break;
    }
}



void Game_Manage_3rd(void) {
    if (Demo_Flag != 0 && Conclusion_Flag != 0) {
        C_No0++;
        Forbid_Break = -1;
        Allow_a_battle_f = 0;
    }
}



void Game_Manage_4th(void) {
    switch (Conclusion_Type) {
    case CONCLUSION_KO:
        C_No0 = C0_ROUND_WIN;
        Setup_BGM_Fade_In(150);
        sound_reg_level_set(0, -128);
        Setup_Win_Mark();
        Check_Perfect(Winner_id);
        PL_Wins[Winner_id]++;
        Update_VS_Data();
        Ck_Win_Record();
        Update_Level_Control();
        break;
    case CONCLUSION_DOUBLE_KO:
        Setup_BGM_Fade_In(150);
        sound_reg_level_set(0, -128);
        sound_request(143);
        if (Judge_Next_Disposal()) {
            C_No0 = C0_JUDGE;
            break;
        }
        C_No0 = C0_DRAW;
        Round_Result |= RESULT_DRAW;
        win_type[0][PL_Wins[0]] = WIN_MARK_DRAW;
        win_type[1][PL_Wins[1]] = WIN_MARK_DRAW;
        PL_Wins[0]++;
        PL_Wins[1]++;
        if (PL_Wins[0] >= Game_setting.Battle_Number + 1) {
            Winner_id = 0;
            Loser_id = 1;
        } else if (PL_Wins[1] >= Game_setting.Battle_Number + 1) {
            Winner_id = 1;
            Loser_id = 0;
        }
        Update_VS_Data();
        Ck_Win_Record();
        break;
    default:
        sound_request(156);
        if (plw[0].wu.vital_new != plw[1].wu.vital_new) {
            C_No0 = C0_ROUND_WIN;
            Round_Result |= RESULT_TIME;
            ROW_ELEM(win_type[Winner_id], PL_Wins[Winner_id]) = WIN_MARK_NORMAL;
            Check_Perfect(Winner_id);
            PL_Wins[Winner_id]++;
            Update_VS_Data();
            Ck_Win_Record();
            Update_Level_Control();
            break;
        }
        C_No0 = C0_JUDGE;
        break;
    }
}



void Setup_Win_Mark(void) {
    if (Round_Result & RESULT_CHIP) {
        win_type[Winner_id][PL_Wins[Winner_id]] = WIN_MARK_CHIP;
        sound_request(121);
        sound_request(143);
        Finish_SE();
        return;
    }
    if (Round_Result & 0x180) {
        win_type[Winner_id][PL_Wins[Winner_id]] = WIN_MARK_SA;
        sound_request(142);
        Finish_SE();
        return;
    }
    win_type[Winner_id][PL_Wins[Winner_id]] = WIN_MARK_NORMAL;
    sound_request(121);
    sound_request(143);
    Finish_SE();
}



/* nothing calls it */
void Control_Music_Fade(void)
{
    if (PB_Music_Off) {
        goto set;
    }
    BGM_No = BGMF_WAIT;
    BGM_Timer = 150;
set:
    sound_reg_level_set(0, -128);
}



void Game_Manage_5th(void) {
    switch (C_No1) {
    case CM5_VICTORY:
        if (Complete_Victory == 0) {
            break;
        }
        C_No1++;
        C_Timer = 30;
        Judge_Round_Flag = 1;
        Event_Judge_Gals = 0;
        break;
    case CM5_ANNOUNCE:
        if (!BUTTON_CUT_EX(&C_Timer, 10)) {
            break;
        }
        C_No1++;
        request_center_message(3);
        sound_request(141);
        bgm_fade_out(182);
        break;
    case CM5_MESSAGE:
        if (request_message) {
            break;
        }
        C_No1++;
        C_Timer = 30;
        break;
    case CM5_WIPE:
        if (!BUTTON_CUT_EX(&C_Timer, 10)) {
            break;
        }
        C_No1++;
        Judge_Winner();
        sc_vram_to_ram();
        Stop_Combo = 1;
        Switch_Screen_Init(3, 3);
        break;
    case CM5_WIPE_WAIT:
        if (Switch_Screen()) {
            C_No1++;
            Switch_Screen_Init(3, 3);
            Cover_Timer = 25;
            compel_bg_init_position();
            judge_flag = 1;
            load_any_color_fade(bg_palette_no_tbl[bg_w.bg_index], 16, 16, 16);
            load_any_color_fade(bg_color2_tbl[bg_w.bg_index], 16, 16, 16);
            if (bg_w.bg_index) {
                load_any_color_fade(bg_color3_tbl[bg_w.bg_index - 1], 16, 16, 16);
            }
            pcon_rno[0] = PCON_INIT;
            pcon_rno[1] = APP_SETUP;
            pcon_rno[2] = 0;
            pcon_rno[3] = 0;
            appear_type = APPEAR_JUDGE;
        }
        break;
    case CM5_WIPE2:
        if (--Cover_Timer != 0) {
            break;
        }
        C_No1++;
        pcon_rno[1] = SETTLE_JUDGE;
        pcon_rno[2] = JG_WAIT;
        Clear_Flash_No();
        Switch_Screen_Init(3, 3);
        break;
    case CM5_REVIVAL:
        if (Switch_Screen_Revival()) {
            C_No1++;
            C_Timer = 60;
            Stop_SG = 0;
            sound_request(7);
        }
        break;
    case CM5_WAIT:
        if (--C_Timer != 0) {
            break;
        }
        C_No0 = C0_ROUND_WIN;
        C_No1 = CM7_WAIT4;
        C_Timer = 30;
        Fade_Half_Flag = 1;
        Complete_Judgement = 1;
        Round_Result |= RESULT_JUDGE;
        win_type[Winner_id][PL_Wins[Winner_id]] = WIN_MARK_JUDGE;
        Check_Perfect(Winner_id);
        PL_Wins[Winner_id]++;
        Update_VS_Data();
        Update_Level_Control();
        break;
    }
}



void Game_Manage_6th(void) {
    switch (C_No1) {
    case CM6_VICTORY:
        if (Complete_Victory) {
            C_No1++;
            C_Timer = 60;
            pcon_rno[1] = SETTLE_JUDGE;
            pcon_rno[2] = JG_IDLE;
            effect_58_init(6, 1, Winner_id + 100);
            effect_92_init(0, win_type[0][PL_Wins[0] - 1]);
            effect_92_init(1, win_type[1][PL_Wins[1] - 1]);
        }
        break;
    case CM6_WAIT:
        if (--C_Timer != 0) {
            break;
        }
        C_No0 = C0_NEXT;
        C_No1 = CM6_VICTORY;
        Round_num++;
        Quick_Entry();
        break;
    }
}



void Game_Manage_7th(void) {
    switch (C_No1) {
    case CM7_VICTORY:
        if (Complete_Victory) {
            C_No1++;
            C_Timer = 1;
            Stock_Loser_Char();
            effect_92_init(Winner_id, win_type[Winner_id][PL_Wins[Winner_id] - 1]);
            effect_58_init(6, 1, Winner_id + 100);
        }
        break;
    case CM7_WAIT:
        if (--C_Timer != 0) {
            break;
        }
        C_No1++;
        C_Timer = 10;
        break;
    case CM7_WINNER:
        if (BUTTON_CUT_EX(&C_Timer, 10)) {
            C_No1++;
            C_Timer = 90;
            Disp_Winner();
            if (Round_Operator[Winner_id] == 0 && Perfect_Flag == 0) {
                Check_Fade_Out_BGM(182);
            }
        }
        break;
    case CM7_CLEAR:
        if (Play_Type == PLAY_VS_CPU && Perfect_Flag == 0) {
            if (!BUTTON_CUT_EX(&C_Timer, 50)) {
                break;
            }
        } else {
            if (!BUTTON_CUT_EX(&C_Timer, 0)) {
                break;
            }
        }
        tilemap_clear_rect(DE_X[0] + 12, 9, DE_X[0] + 36, 15);
        if (Perfect_Flag) {
            C_No1++;
            C_Timer = 10;
        } else {
            C_No0++;
            C_No1 = CM7_VICTORY;
            Event_Judge_Gals = -1;
        }
        break;
    case CM7_WAIT2:
        if (--C_Timer != 0) {
            break;
        }
        C_No1++;
        request_center_message(4);
        sound_request(138);
        break;
    case CM7_MESSAGE:
        if (request_message) {
            break;
        }
        C_No1++;
        C_Timer = 6;
        Event_Judge_Gals = -1;
        break;
    case CM7_WAIT3:
        if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
            C_Timer = 1;
        }
        if (--C_Timer != 0) {
            break;
        }
        C_No0++;
        C_No1 = CM7_VICTORY;
        break;
    case CM7_WAIT4:
        if (--C_Timer != 0) {
            break;
        }
        C_No1++;
        Event_Judge_Gals = 3;
        break;
    case CM7_GALS:
        if (Event_Judge_Gals == 0) {
            C_No1++;
            C_Timer = 30;
            Ck_Win_Record();
        }
        break;
    case CM7_WAIT5:
        if (--C_Timer == 0) {
            C_No1 = CM7_VICTORY;
        }
        break;
    }
}



void Stock_Loser_Char(void) {
    if (PL_Wins[WINNER] >= Game_setting.Battle_Number + 1) {
        if (Round_Operator[LOSER] != 0) {
            Win_Record[LOSER] = 0;
            Stock_My_char[LOSER] = My_char[LOSER];
            Stock_Player_Color[LOSER] = Player_Color[LOSER];
        }
    }
}



void Check_Fade_Out_BGM(s16 Time) {
    if (!Music_Fade) {
        if (PL_Wins[Winner_id] >= Game_setting.Battle_Number + 1) {
            Music_Fade = 1;
            bgm_fade_out(Time);
        }
    }
}



void Game_Manage_8th(void) {
    switch (C_No1) {
    case CM8_START:
        Round_num++;
        Quick_Entry();
        if (Check_Bonus_Skip()) {
            break;
        }
        if (Round_Operator[Winner_id]) {
            C_No1++;
            C_Timer = 1;
            Additional_Bonus(Winner_id);
        } else {
            C_No1 = 99;
            C_Timer = 40;
            if (Judge_Round_Flag) {
                bgm_fade_in_stage(180);
            }
        }
        break;
    case CM8_WAIT:
        if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
            C_Timer = 1;
        }
        if (--C_Timer != 0) {
            break;
        }
        C_No1++;
        C_No2 = 0;
        C_Timer = 1;
        break;
    case CM8_WAIT2:
        switch (C_No2) {
        case CM8_S_WAIT:
            if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
                if (Bonus_Cut_All()) {
                    if (Judge_Round_Flag) {
                        bgm_fade_in_stage(180);
                    } else if (Perfect_Flag) {
                        Check_Fade_Out_BGM(0x111);
                    } else {
                        Check_Fade_Out_BGM(0x222);
                    }
                }
            } else {
                if (cmb_all_stock) {
                    break;
                }
                C_No2++;
                C_Timer = 20;
                ToneDown(5);
                sc_celllist_put_scr(7);
                sc_celllist_put_scr(8);
                sc_celllist_put_scr(9);
                if (Judge_Round_Flag) {
                    bgm_fade_out(0x222);
                    bgm_fade_in_stage(180);
                }
            }
            break;
        case CM8_S_WAIT2:
            if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
                if (Bonus_Cut_All()) {
                    Check_Fade_Out_BGM(0x111);
                    break;
                }
                break;
            }
            if (--C_Timer != 0) {
                break;
            }
            C_No2++;
            C_Timer = 20;
            Disp_Digit16x24(Vital_Bonus, DE_X[0] + 35, 8);
            sound_request(Winner_id + 102);
            break;
        case CM8_S_WAIT3:
            if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
                if (Bonus_Cut_All()) {
                    Check_Fade_Out_BGM(0x111);
                    break;
                }
                break;
            }
            if (--C_Timer != 0) {
                break;
            }
            C_No2++;
            C_Timer = 20;
            Disp_Digit16x24(Time_Bonus, DE_X[0] + 35, 12);
            sound_request(Winner_id + 102);
            break;
        case CM8_S_WAIT4:
            if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
                if (Bonus_Cut_All()) {
                    Check_Fade_Out_BGM(0x111);
                    break;
                }
                break;
            }
            if (--C_Timer != 0) {
                break;
            }
            C_No2++;
            C_Timer = 20;
            Disp_Digit16x24(Total_Bonus, DE_X[0] + 35, 16);
            sound_request(Winner_id + 102);
            break;
        case CM8_S_WAIT5:
            if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
                if (Bonus_Cut_All()) {
                    Check_Fade_Out_BGM(0x111);
                    break;
                }
                break;
            }
            if (--C_Timer != 0) {
                break;
            }
            C_No2++;
            C_Timer = 9;
            break;
        case CM8_S_WAIT6:
            if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
                C_Timer = 1;
            }
            if (--C_Timer != 0) {
                break;
            }
            if (Perfect_Flag) {
                C_No2++;
                C_Timer = 10;
            } else {
                C_No2 = CM8_S_WAIT9;
                C_Timer = 10;
            }

            break;
        case CM8_S_WAIT7:
            if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
                if (Bonus_Cut_All()) {
                    Check_Fade_Out_BGM(0x111);
                    break;
                }
                break;
            }
            if (--C_Timer != 0) {
                break;
            }
            C_No2++;
            C_Timer = 10;
            sc_celllist_put_scr(10);
            Disp_Digit16x24(Vital_Bonus + 40000, DE_X[0] + 35, 8);
            sound_request(Winner_id + 102);
            break;
        case CM8_S_WAIT8:
            if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
                if (Bonus_Cut_All()) {
                    Check_Fade_Out_BGM(0x222);
                    break;
                }
                break;
            }
            if (--C_Timer != 0) {
                break;
            }
            C_No2++;
            C_Timer = 10;
            Disp_Digit16x24(Total_Bonus + 40000, DE_X[0] + 35, 16);
            sound_request(Winner_id + 102);
            break;
        case CM8_S_WAIT9:
            if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
                Bonus_Cut_All();
            }
            if (--C_Timer != 0) {
                break;
            }
            C_No2++;
            C_Timer = 20;
            if (Perfect_Flag == 0) {
                break;
            }
            C_Timer = 40;
            effect_89_init(4, DE_X[3] + 10, 8, 36, 3);
            effect_89_init(4, DE_X[3] + 12, 16, 25, 3);

            break;
        case CM8_S_WAIT10:
            if (!Perfect_Flag) {
                if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
                    C_Timer = 1;
                }
            }
            if (--C_Timer != 0) {
                break;
            }
            Disp_Player_Score(Winner_id);
            Check_Fade_Out_BGM(0x222);
            C_No1++;
            C_Timer = 10;

            break;
        }
        break;
    case CM8_WAIT3:
        if (--C_Timer != 0 && !Button_Cut_Hold(&C_Timer, 100, 110)) {
            break;
        }
        tilemap_clear_rect(DE_X[0] + 7, 8, DE_X[0] + 36, 19);
        C_No0++;
        C_No1 = CM8_START;

        break;
    case CM8_WAIT4:
        switch (C_No2) {
        case CM8_S_WAIT11:
            if (--C_Timer != 0) {
                return;
            }
            C_No2++;
            C_Timer = 20;
            if (Perfect_Flag == 0) {
                break;
            }
            effect_89_init(4, DE_X[0] + 10, 8, 36, 3);
            effect_89_init(4, DE_X[0] + 12, 16, 25, 3);
        default:
            break;
        case CM8_S_WAIT12:
            if (!Perfect_Flag) {
                if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
                    C_Timer = 1;
                }
            }
            if (--C_Timer != 0) {
                break;
            }
            C_No1 = CM8_WAIT3;
            C_Timer = 120;
            Disp_Player_Score(Winner_id);
            Check_Fade_Out_BGM(0x222);
            break;
        }
        break;
    default:
        if (!BUTTON_CUT_EX(&C_Timer, 50)) {
            break;
        }
        C_No0++;
        C_No1 = CM8_START;

        break;
    }
}

/* nothing calls it */
void Restore_Loser_Score(void) {
    if (Play_Type == PLAY_VS_PLAYER) {
        return;
    }
    if (PL_Wins[Winner_id] >= Game_setting.Battle_Number + 1) {
        return;
    }
}



s32 Check_Bonus_Skip(void) {
    if (Play_Type == PLAY_VS_CPU) {
        return 0;
    }
    if (Winner_id) {
        if (!(p2sw_0 & 0x7F0)) {
            return 0;
        }
    } else {
        if (!(p1sw_0 & 0x7F0)) {
            return 0;
        }
    }
    C_No0++;
    C_No1 = 0;
    C_No2 = 0;
    C_No3 = 0;
    Additional_Bonus(Winner_id);
    if (Judge_Round_Flag) {
        bgm_fade_in_stage(180);
    } else {
        Check_Fade_Out_BGM(0x222);
    }
    return 1;
}



s32 Bonus_Cut_All(void) {
    if (cmb_all_stock) {
        C_Timer = 1;
        return 0;
    }
    C_No1 = CM8_WAIT4;
    C_No2 = CM8_S_WAIT11;
    C_Timer = 20;
    ToneDown(5);
    if (Perfect_Flag) {
        sc_celllist_put_scr(10);
        sc_celllist_put_scr(8);
        sc_celllist_put_scr(9);
        Disp_Digit16x24(Vital_Bonus + 40000, DE_X[0] + 35, 8);
        Disp_Digit16x24(Time_Bonus, DE_X[0] + 35, 12);
        Disp_Digit16x24(Total_Bonus + 40000, DE_X[0] + 35, 16);
        Bonus_Count_Effect(2);
    } else {
        sc_celllist_put_scr(7);
        sc_celllist_put_scr(8);
        sc_celllist_put_scr(9);
        Disp_Digit16x24(Vital_Bonus, DE_X[0] + 35, 8);
        Disp_Digit16x24(Time_Bonus, DE_X[0] + 35, 12);
        Disp_Digit16x24(Total_Bonus, DE_X[0] + 35, 16);
        Bonus_Count_Effect(1);
    }
    return 1;
}



void Bonus_Count_Effect(s16 n) {
    s16 i;
    s16 t;
    for (i = 0, t = 1; i < n; i++, t += 10) {
        effect_58_init(6, t, Winner_id + 102);
    }
}



void Additional_Bonus(s16 PL_id) {
    u16 rank;
    if (Perfect_Flag) {
        Vital_Bonus = 60000;
        Round_Perfect_Bonus = 40000;
    } else {
        Vital_Bonus = plw[PL_id].wu.vital_new * 100 / 160;
        Vital_Bonus *= 600;
        Round_Perfect_Bonus = 0;
    }
    rank = gauge_rank_value(*(s16*)&round_timer);
    Time_Bonus = *(s16*)&round_timer * rank;
    Total_Bonus = Vital_Bonus + Time_Bonus;
    Score[PL_id][Play_Type] += Total_Bonus + Round_Perfect_Bonus;
    if (Score[PL_id][Play_Type] >= 9999900) {
        ROW_ELEM(Score[PL_id], Play_Type) = 9999900;
    }
}



void Game_Manage_9th(void) {
    s8 *winner;
    switch (C_No1) {
    case CM9_WIPE:
        if (*(*(winner = &WINNER) + PL_Wins) >= Game_setting.Battle_Number + 1) {
            C_No0++;
            C_Timer = 75;
            sc_vram_to_ram();
            if (Play_Type == PLAY_VS_PLAYER) {
                Control_Time = SC_Personal_Time[*winner];
                card_win_check(0);
                Stock_My_char[LOSER] = My_char[LOSER];
                Stock_Player_Color[LOSER] = Player_Color[LOSER];
            } else if (Round_Operator[*winner]) {
                card_win_check(0);
                SC_Personal_Time[*winner] = Control_Time;
            } else {
                Win_Record[*winner] = 0;
                Stock_My_char[LOSER] = My_char[LOSER];
                Stock_Player_Color[LOSER] = Player_Color[LOSER];
            }
        } else {
            C_No1++;
            if (bg_w.stage == 8 && bg_w.area == 0) {
                C_Timer = 150;
            } else {
                C_Timer = 60;
            }
            satime_stock_clear();
            sc_vram_to_ram();
            Stop_Combo = 1;
            BGM_Timer = 1;
            Switch_Screen_Init(3, 3);
        }
        break;
    case CM9_WAIT:
        if (!(bg_w.stage == 8 && bg_w.area == 0)) {
            if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
                C_Timer = 1;
            }
        }
        if (--C_Timer > 0) {
            return;
        }
        C_No1++;
    default:
        if (Switch_Screen()) {
            G_No2 = G2_ROUND_RESET;
            G_No3 = 0;
            G_Timer = 4;
            C_No0 = C0_ROUND_START;
            C_No1 = C_No2 = C_No3 = 0;
            Cover_Timer = 25;
        }
        break;
    }
}



void Game_Manage_10th(void) {
    switch (C_No1) {
    case CM10_WAIT:
        if (Button_Cut_Hold(&C_Timer, 0x7FFF, 0x7FFF)) {
            C_Timer = 1;
        }
        if (--C_Timer <= 0) {
            C_No1++;
            Cover_Timer = 25;
            sc_vram_to_ram();
            Stop_Combo = 1;
            Switch_Screen_Init(3, 3);
        }
        break;
    case CM10_WIPE_WAIT:
        if (Switch_Screen()) {
            SE_All_Off();
            Check_Naming(0);
            Check_Naming(1);
            pcon_rno[0] = PCON_INIT;
            pcon_rno[1] = APP_SETUP;
            pcon_rno[2] = 0;
            pcon_rno[3] = 0;
            appear_type = APPEAR_ENTRY;
            Continue_Coin2[WINNER] = 0;
            if (Round_Operator[WINNER]) {
                G_No1 = G1_WINNER;
                G_No2 = 0;
                G_No3 = 0;
                M_No0 = 0;
                M_No1 = 0;
                M_No2 = 0;
                M_No3 = 0;
                E_No0 = E0_WINNER;
                E_No1 = 0;
                E_No2 = 0;
                E_No3 = 0;
                Straight_Lose_Count = 0;
                if (++Straight_Win_Count == 0) {
                    Straight_Win_Count = 0xFF;
                }
                Check_Ending();
                Continue_Coin2[WINNER] = 0;
                Clear_Flash_No();
            } else {
                G_No1 = G1_LOSER;
                G_No2 = 0;
                G_No3 = 0;
                M_No0 = 0;
                M_No1 = 0;
                M_No2 = 0;
                M_No3 = 0;
                E_No0 = E0_LOSER;
                E_No1 = 0;
                E_No2 = 0;
                E_No3 = 0;
                E_07_Flag[0] = 0;
                E_07_Flag[1] = 0;
                Straight_Win_Count = 0;
                if (++Straight_Lose_Count == 0) {
                    Straight_Lose_Count = 0xFF;
                }
                Clear_Flash_No();
                Continue_Coin2[LOSER]++;
                if (Round_Level < 7) {
                    if (--Round_Level < 0) {
                        Round_Level = 0;
                    }
                }
            }
        }
        break;
    }
}



void Check_Naming(id)
s16 id;
{
    if (Game_setting.Event) {
        return;
    }
    if (E_Number[id][0] != ENTRY_NAME) {
        Rank_In[id][RANK_SCORE] = -1;
        Rank_In[id][RANK_WINS] = -1;
    }
}



void Ck_Win_Record(void) {
    s16 w;
    s16 l;
    if (Play_Type == PLAY_VS_PLAYER) {
        if (PL_Wins[0] >= Game_setting.Battle_Number + 1 || PL_Wins[1] >= Game_setting.Battle_Number + 1) {
            if (PL_Wins[0] >= Game_setting.Battle_Number + 1) {
                w = 0;
                l = 1;
            } else {
                w = 1;
                l = 0;
            }
            if (++Win_Record[w] <= 99) {
                Disp_Win_Record_Sub(w);
                Erase_Win_Record(l);
            } else {
                Win_Record[w] = 99;
            }
        }
    }
}



void Disp_Win_Record_Sub(PL_id)
s16 PL_id;
{
    s16 xx;
    s16 Wins_Buff;
    switch (Win_Record[PL_id]) {
    case 1:
        tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[0][PL_id][Game_setting.Screen_Mode], 0, 18, "WIN");
        break;
    case 2:
        tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[0][PL_id][Game_setting.Screen_Mode], 0, 18, "WINS");
        break;
    }
    xx = Win_Record[PL_id] / 10;
    if (xx > 0) {
        tilemap_print_hex_block(ENTRY_LOSER_X_PAIRS[0][PL_id][Game_setting.Screen_Mode] - 3, 0, 18, (s8)xx, 1, 1);
    }
    Wins_Buff = Win_Record[PL_id] % 10;
    tilemap_print_hex_block(ENTRY_LOSER_X_PAIRS[0][PL_id][Game_setting.Screen_Mode] - 2, 0, 18, (s8)Wins_Buff, 1, 1);
}



void Disp_Win_Record(void) {
    s16 pl;
    s16 digit;
    s16 num;
    if (Play_Type != PLAY_VS_PLAYER) {
        return;
    }
    if (Win_Record[0] == 0 && Win_Record[1] == 0) {
        return;
    }
    if (Win_Record[0]) {
        pl = 0;
    } else {
        pl = 1;
    }
    if (Win_Record[Winner_id] > 1) {
        tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[0][pl][Game_setting.Screen_Mode], 0, 18, "WINS");
    } else {
        tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[0][pl][Game_setting.Screen_Mode], 0, 18, "WIN");
    }
    digit = Win_Record[pl] / 10;
    if (digit > 0) {
        tilemap_print_hex_block(ENTRY_LOSER_X_PAIRS[0][pl][Game_setting.Screen_Mode] - 3, 0, 18, (s8)digit, 1, 1);
    }
    num = Win_Record[pl] % 10;
    tilemap_print_hex_block(ENTRY_LOSER_X_PAIRS[0][pl][Game_setting.Screen_Mode] - 2, 0, 18, (s8)num, 1, 1);
}



void Erase_Win_Record(PL_id)
s16 PL_id;
{
    if (Win_Record[PL_id] != 0) {
        tilemap_print_string_attr(ENTRY_LOSER_X_PAIRS[0][PL_id][Game_setting.Screen_Mode] - 3, 0, 18, "       ");
        Win_Record[PL_id] = 0;
    }
}



void Disp_Winner(void) {
    s8 ch;
    const NAME_PLATE* p;
    if (Play_Type == PLAY_VS_PLAYER) {
        ch = My_char[Winner_id] & 0x7F;
        winner_name_put(ch);
        p = &nwdata_tbl[ch];
        effect_89_init(3, (s16)(p->x + DE_X[0]), p->y, (s16)p->w, (s16)p->h);
        effect_89_init(1, (s16)(p->x2 + DE_X[0]), p->y2, 10, 4);
        sound_request(ch + 176);
    } else {
        if (Round_Operator[Winner_id] != 0) {
            bcount_mark_trans(5);
            effect_89_init(1, DE_X[0] + 12, 9, 23, 4);
            sound_request(155);
        } else {
            bcount_mark_trans(6);
            effect_89_init(2, DE_X[0] + 12, 9, 24, 4);
            sound_request(154);
        }
    }
}



void Update_Level_Control(void) {
    if (Round_Operator[Winner_id]) {
        if (!Round_Operator[Loser_id]) {
            Control_Time += 40;
            if (Control_Time > Limit_Time) {
                Control_Time = Limit_Time;
                return;
            }
        }
    } else {
        if ((Control_Time -= 30) < 0) {
            Control_Time = 0;
        }
    }
}



void complete_victory_pause(void)
{
    Complete_Victory = 1;
}



void request_center_message(s16 Kind_of_Message) {
    request_message = 1;
    message_index = Kind_of_Message;
}



s32 Judge_Next_Disposal(void) {
    if (PL_Wins[0] != PL_Wins[1]) {
        return 0;
    }
    if (PL_Wins[0] >= Game_setting.Battle_Number) {
        return 1;
    }
    return 0;
}



void Check_Perfect(s16 PL_id) {

    if (plw[PL_id].wu.vitality == plw[PL_id].wu.vital_new) {
        Perfect_Flag = 1;
        Round_Result |= RESULT_PERFECT;
        win_type[PL_id][PL_Wins[PL_id]] = WIN_MARK_PERFECT;
    }
}



void Judge_Winner(void) {
    if (Score[0][SCORE_ROUND] == Score[1][SCORE_ROUND]) {
        if (Play_Type == PLAY_VS_CPU) {
            Winner_id = Player_id;
            Loser_id = COM_id;
        } else {
            Winner_id = Champion;
            Loser_id = Champion ^ 1;
        }
    } else if (Score[0][SCORE_ROUND] > Score[1][SCORE_ROUND]) {
        Winner_id = 0;
        Loser_id = 1;
    } else {
        Winner_id = 1;
        Loser_id = 0;
    }
}



s32 Check_Ending(void) {
    if (Play_Type == PLAY_VS_PLAYER) {
        return 0;
    }
    Last_VS_Index[WINNER] = Next_VS_Index();
    if (Last_VS_Index[WINNER] >= 7) {
        G_No1 = G1_ENDING;
        G_No2 = G2_END_INIT;
        E_No0 = E0_ENDING;
        plw[WINNER].wu.operator = 0;
        Operator_Status[WINNER] = 0;
        sound_reg_level_set(0, 0);
        Control_Time = 481;
        Ending_init();
        Stock_My_char[WINNER] = My_char[WINNER];
        Stock_Player_Color[WINNER] = Player_Color[WINNER];
        return 1;
    }
    return 0;
}



s16 Next_VS_Index(void) {
    s16 em;
    if (VS_Index[WINNER] >= 7) {
        return 7;
    }
    ROW_ELEM(Last_VS_Index, WINNER) = VS_Index[WINNER];
    for (; Last_VS_Index[WINNER] <= 5; Last_VS_Index[WINNER]++) {
        em = EM_Candidate_Data[Used_char[WINNER]][EM_Course[WINNER]][Last_VS_Index[WINNER]];
        if (Break_Com[WINNER][em] == 0) {
            return Last_VS_Index[WINNER];
        }
    }
    return 6;
}



void Quick_Entry(void) {
    if (Check_Entry_Again()) {
        Forbid_Break = 0;
    }
    if (PL_Wins[Winner_id] >= Game_setting.Battle_Number + 1) {
        if (plw[LOSER].wu.operator) {
            Loser_Sub();
            Be_Continue();
        }
        sc_vram_to_ram();
    }
}



s32 Check_Entry_Again(void) {
    if (Play_Type == PLAY_VS_PLAYER) {
        return 1;
    }
    if (VS_Index[WINNER] < 5) {
        return 1;
    }
    return 0;
}



void Loser_Sub(void) {
    plw[LOSER].wu.operator = 0;
    Operator_Status[LOSER] = 0;
    Sel_PL_Complete[LOSER] = 0;
    Sel_Arts_Complete[LOSER] = 0;
    if (Game_setting.Event == 0) {
        tilemap_clear_rect(Score_X_Pos_Data[LOSER][Game_setting.Screen_Mode] - 7, Text_Page_Y, Score_X_Pos_Data[LOSER][Game_setting.Screen_Mode], Text_Page_Y + 1);
    }
    tilemap_print_string_attr(Loser_X_Pos_Data[LOSER][Game_setting.Screen_Mode] - 2, 0, 18, "      ");
}



void Be_Continue(void) {
    if (Continue_Flag != 0 && Game_setting.Event == 0) {
        Continue_Count[LOSER] = 9;
        E_Number[LOSER][0] = ENTRY_LOSER;
        E_Number[LOSER][1] = 0;
        E_Number[LOSER][2] = 0;
        E_Number[LOSER][3] = 0;
    } else {
        E_Number[LOSER][0] = ENTRY_GAME_OVER;
        E_Number[LOSER][1] = 0;
        E_Number[LOSER][2] = 0;
        E_Number[LOSER][3] = 0;
        Stock_My_char[LOSER] = My_char[LOSER];
        Stock_Player_Color[LOSER] = Player_Color[LOSER];
    }
}



void Update_VS_Data(void) {
    if (PL_Wins[Winner_id] < Game_setting.Battle_Number + 1) {
        return;
    }
    WINNER = Winner_id;
    LOSER = Loser_id;
    if (Play_Type != PLAY_VS_CPU || Round_Operator[Winner_id] == 0) {
        return;
    }
    Break_Com[Winner_id][EM_id] = 1;
    Stock_Com_Color = -1;
    Stock_Com_Arts = -1;
    VS_Index[Player_id]++;
    if (++Round_Level > 7) {
        Round_Level = 7;
    }
}



void BGM_Fade_Sub(void) {
    s8* v = &BGM_Vol;
    switch (BGM_No) {
    case BGMF_WAIT:
        if (--BGM_Timer == 0) {
            BGM_No++;
            BGM_Timer = 1;
            *v = -128;
        }
        break;
    default:
        if (--BGM_Timer == 0) {
            BGM_Timer = 2;
            if (++*v == 0) {
                BGM_No = BGMF_NONE;
            }
        }
        sound_reg_level_set(0, *v);
        break;
    case BGMF_NONE:
        break;
    }
}



void Setup_BGM_Fade_In(s16 time) {
    if (PB_Music_Off) {
        return;
    }
    BGM_No = BGMF_WAIT;
    BGM_Timer = time;
}



void Update_Personal_Time(s16 id) {
    if (Continue_Coin2[id] == 0) {
        SC_Personal_Time[id] = Control_Time;
    }
}








