/*
 * GAME_MAIN.C  Game phase dispatcher: title, select, fight, continue, ending
 *
 * Game runs the current game phase from G_No1: Game00 (title / attract entry),
 * Game01 (player select and fight HUD setup via Game01_Sub), Game02 (the fight), Game03 (winner
 * scene), Game04 (loser scene), Game05 (next CPU selection), Game06 (game over), Game07 (continue),
 * Game08 (ending).
 * Game2_1 is the fight frame: round timer (Time_Control), player control
 * (Player_control), vital and combo displays, Game_Management, the seven effect lists and
 * hit_check_main_process.
 * Loop_Demo handles a coin during the demo (Ck_Coin sees a coin, service input or free-play
 * start); Loop_Demo_Sub, Before_Select_Sub and
 * Erase_Insert_Coin serve the attract loop; Disp_Ranking and Request_Break_Sub handle the
 * ranking screen and break-in requests. draw_operator_info places operator text for the current
 * screen mode.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "bg0001.h"
#include "SYS_sub.h"
#include "Entry.h"
#include "entry_2.h"
#include "end_main_c.h"
#include "aboutspr.h"
#include "se_2.h"
#include "se_3.h"
#include "demo00.h"
#include "demo01.h"
#include "demo02_code.h"
#include "RANKING.h"
#include "Manage.h"
#include "manage_2.h"
#include "win_2.h"
#include "continue.h"
#include "next_cpu.h"
#include "sc_trans.h"
#include "sc_clear.h"
#include "cmb_win.h"
#include "VITAL.h"
#include "count.h"
#include "spgauge.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLCNTDAT.h"
#include "plcntdat_2.h"
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
#include "EFFM7.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "HITCHECK.h"
#include "cmb_cont.h"
#include "EFF04.h"
#include "EFF41.h"
#include "eff35.h"
#include "eff56.h"
#include "eff57.h"
#include "EFF58.h"
#include "SLOWF.h"
#include "sc_sub.h"
#include "sc_sub_2.h"
#include "bg000.h"
#include "ta_sub2.h"
#include "tate00.h"
#include "ta_sub.h"
#include "Game_Main.h"
#include "eeprom.h"
#include "SE.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "lose_pl.h"
#include "PLS02.h"

/* G_No3 in Disp_Ranking */
#define G3_RANK_INIT    0       /* save the screen and wipe */
#define G3_RANK_SETUP   1       /* set up the ranking */
#define G3_RANK_COVER   2       /* wait out the cover, then wipe in */
#define G3_RANK_REVIVAL 3       /* finish the wipe */

void Basic_Sub_Suzi(void);
void SF3_logo(s16 y);
void sa_number_put(void);

extern u8 Straight_Lose_Count;  /* provisional name (manage_2.c) */



void Scrn_Move_Set(s32 n, s16 x, s16 y);

void sound_reg_level_set(s16 pitch, s8 volume);

#pragma noregsave(game_frame_task)
#pragma inline(bg0001)



/* Frame task started by mode_init_task: every frame run the current game routine
   (bg0001), then the colour transfer and the frame render pipeline, and sleep
   until the next frame. */
/* provisional name */
void game_frame_task(void) {
    if (DEBUG_SLOW) {
        task_sleep(1);
    }
loop:
    bg0001();
    color_trans_dummy();
    sprite_bank_flip();
    task_sleep(1);
    goto loop;
}



/* Game task jump: run Loop_Demo (G0_DEMO), Game (G0_GAME) or Game_Dummy by the top-level game
   number G_No0. */
void bg0001(void) {
    void (*Main_Jmp_Tbl[3])() = { Loop_Demo, Game, Game_Dummy };
    Main_Jmp_Tbl[G_No0]();
}



void Loop_Demo(void) {
    if (Ck_Coin()) {
        tilemap_fill_all(0, 32);
        wipe_pattern_set(0, 7, 0);
        if (G_No1 != G1_DEMO_RESTART) {
            sound_driver_init();
        }
        sound_reg_level_set(0, 0);
        card_work_clear();
        bg_vbl_trans_flag = 0;
        if (Demo_Flag == 0) {
            sound_request(115);
        }
        G_No0 = G0_GAME;
        G_No1 = G1_TITLE;
        G_No2 = G2_TITLE;
        G_No3 = 0;
        D_No0 = 0;
        D_No1 = 0;
        D_No2 = 0;
        D_No3 = 0;
        Demo_Flag = 1;
        BGM_Stop();
        Before_Select_Sub();
        if (Free_Play) {
            G_No2 = G2_TITLE_FREE;
            Exit_Title_Sub_Entry();
            return;
        } else {
            E_No0 = E0_TITLE;
            E_No1 = 0;
            E_No2 = 0;
            E_No3 = 0;
        }
        return;
    }
    switch (G_No1) {
    case G1_DEMO_INIT:
        G_No1++;
        G_No2 = 0;
        G_No3 = 0;
        D_No0 = 0;
        D_No1 = 0;
        D_No2 = 0;
        D_No3 = 0;
        E_No1 = 99;
        Demo_PL_Index[0] = 0;
        Demo_PL_Index[1] = 0;
        Demo_Stage_Index = 0;
        Select_Demo_Index = 0;
        Text_Page_Y = 0;
        Insert_Y = 20;
        Demo_Flag = 0;
        if (DEBUG_DISP) {
            tilemap_print_hex_block(20, 1, 18, G_No0, 4, 0);
        }
        wipe_pattern_set(0, 7, 0);
        scfont_page0_fill(0, 32);
        break;
    case G1_DEMO_LOGO:
        draw_operator_info(Text_Page_Y);
        Basic_Sub();
        if (CAPCOM_Logo()) {
            Loop_Demo_Sub();
            Erase_Insert_Coin();
            Insert_Y = 20;
            E_No1 = 2;
            bg_vbl_trans_flag = 0;
            if (Country == 4) {
                D_No0 = 1;
                E_No1 = 99;
            } else {
                G_No1 = G1_DEMO_TITLE;
            }
        }
        break;
    case G1_DEMO_WARNING:
        draw_operator_info(Text_Page_Y);
        if (CAPCOM_Logo()) {
            Loop_Demo_Sub();
            D_No0 = 2;
            E_No1 = 99;
        }
        break;
    case G1_DEMO_LOGO_ETC:
        draw_operator_info(Text_Page_Y);
        if (CAPCOM_Logo()) {
            Loop_Demo_Sub();
            Erase_Insert_Coin();
            Insert_Y = 20;
        }
        break;
    case G1_DEMO_TITLE:
        draw_operator_info(Text_Page_Y);
        Basic_Sub();
        if (Title()) {
            Loop_Demo_Sub();
            Erase_Insert_Coin();
            Insert_Y = 15;
            D_No0 = 1;
        }
        break;
    case G1_DEMO_PLAY:
        draw_operator_info(Text_Page_Y);
        if (Play_Demo()) {
            Loop_Demo_Sub();
            Rank_Type = 0;
            Demo_Type = 0;
            Text_Page_Y = 32;
            Scrn_Move_Set(4, 0, 0x100);
            sound_driver_init();
        }
        break;
    case G1_DEMO_RANKING:
        draw_operator_info(Text_Page_Y);
        Basic_Sub();
        if (Ranking() == 0) {
            break;
        }
        Loop_Demo_Sub();
        break;
    case G1_DEMO_PLAY2:
        draw_operator_info(Text_Page_Y);
        if (Play_Demo()) {
            Loop_Demo_Sub();
            Demo_Type = 1;
            Rank_Type = 6;
            Demo_Type = 1;
            Text_Page_Y = 32;
            Scrn_Move_Set(4, 0, 0x100);
            sound_driver_init();
        }
        break;
    case G1_DEMO_RANKING2:
        draw_operator_info(Text_Page_Y);
        Basic_Sub();
        if (Ranking()) {
            Loop_Demo_Sub();
            G_No1 = G1_DEMO_LOGO;
            E_No1 = 99;
        }
        break;
    default:
        switch (G_No2) {
        case 0:
            if (--Cover_Timer == 0) {
                G_No2++;
            }
            break;
        default:
            G_No1 = G1_DEMO_LOGO;
            G_No2 = 0;
            E_No3 = 0;
            E_No1 = 99;
            Demo_PL_Index[0] = 0;
            Demo_PL_Index[1] = 0;
            Demo_Stage_Index = 0;
            Select_Demo_Index = 0;
            Text_Page_Y = 0;
            Demo_Flag = 0;
            break;
        }
        break;
    }
}



void Loop_Demo_Sub(void) {
    G_No1++;
    G_No2 = 0;
    D_No0 = 0;
    D_No1 = 0;
    D_No2 = 0;
    D_No3 = 0;
    E_No1 = 1;
    Scrn_Move_Set(4, 0, 0);
}



/* provisional name */
void Erase_Insert_Coin(void) {
    tilemap_print_string_attr(DE_X[0] + 16, Insert_Y, 18, "              ");
    tilemap_print_string_attr(DE_X[0] + 16, Insert_Y + 32, 18, "              ");
}



void Before_Select_Sub(void) {
    s16 xx;
    Request_G_No = 0;
    Request_E_No = 0;
    Allow_a_battle_f = 0;
    if (Demo_Flag == 0) {
        Control_Time = 2048;
        Round_Level = 7;
    } else {
        Control_Time = 481;
    }
    VS_Index[0] = -1;
    VS_Index[1] = -1;
    Super_Arts[0] = 0;
    Super_Arts[1] = 0;
    Exec_Wipe = 0;
    Fade_Flag = 0;
    Stock_Com_Color = -1;
    Stock_Com_Arts = -1;
    Straight_Lose_Count = 0;
    Request_Disp_Rank[0][RANK_SCORE] = -1;
    Request_Disp_Rank[0][RANK_WINS] = -1;
    Request_Disp_Rank[1][RANK_SCORE] = -1;
    Request_Disp_Rank[1][RANK_WINS] = -1;
    Rank_In[0][RANK_SCORE] = -1;
    Rank_In[0][RANK_WINS] = -1;
    Rank_In[1][RANK_SCORE] = -1;
    Rank_In[1][RANK_WINS] = -1;
    Clear_Personal_Data(0);
    Clear_Personal_Data(1);
    Last_Player_id = Player_Number = -1;
    Round_Level = 3;
    Time_in_Time = 60;
    xx = system_timer;
    Random_ix16_com = xx & 0x3F;
    Random_ix32_com = xx & 0x7F;
}



void Game(void) {
    void (*Game_Jmp_Tbl[9])() = { Game00, Game01, Game02, Game03, Game04, Game05, Game06, Game07, Game08 };
    Game_Jmp_Tbl[G_No1]();
}



void Game00(void) {
    void (*Game00_Jmp_Tbl[6])() = { Game0_0, Game0_1, Game0_2, Game0_3, Game0_2, Game0_3 };
    Game00_Jmp_Tbl[G_No2]();
    Basic_Sub();
}



void Game0_0(void) {
    if (Title_At_a_Dash() != 0) {
        G_No2++;
    }
}



void Game0_1(void) {
    if (Request_G_No) {
        G_No2++;
    }
}



void Scrn_Move_Set(s32 n, s16 x, s16 y);



/* Title hand-off: step the game routine, save the screen and start wipe 0. */
void Game0_2(void)
{
    G_No2++;
    sc_vram_to_ram();
    Switch_Screen_Init(0, 1);
}



/* provisional name */
void Game0_3(void) {
    if (Switch_Screen()) {
        G_No1++;
        G_No2 = G2_SEL_INIT;
        G_No3 = 0;
        Cover_Timer = 23;
    }
}



void Game01(void) {
    Basic_Sub_Suzi();
    switch (G_No2) {
    case G2_SEL_INIT:
        G_No2++;
        S_No = 0;
        S_Sub_No = 0;
        S_Sub2_No = 0;
        S_Sub3_No = 0;
        Break_Into = 0;
        Stop_Combo = 0;
        load_any_color(5);
        load_any_color(135);
        load_char_gfx(0x5B30, 1);
        init_slow_flag();
        break;
    case G2_SEL_MAIN:
        if (Select_Player()) {
            G_No2++;
            Game01_Sub();
            if (Demo_Flag == 0) {
                SF3_logo(0);
            }
            commit_name_entry_row_both_players(0);
            sc_vram_to_ram();
            Switch_Screen_Init(3, 3);
        }
        break;
    default:
        Select_Player();
        if (Switch_Screen()) {
            Cover_Timer = 24;
            Scrn_Move_Set(4, 0, 0);
            appear_type = APPEAR_ENTRY;
            if (Demo_Flag) {
                G_No1 = G1_FIGHT;
                G_No2 = G2_FIGHT_INIT;
                E_No0 = E0_FIGHT;
                E_No1 = 0;
                E_No2 = 0;
                E_No3 = 0;
            } else {
                Demo_Time_Stop = 1;
                plw[0].wu.operator = 0;
                Operator_Status[0] = 0;
                plw[1].wu.operator = 0;
                Operator_Status[1] = 0;
            }
            purge_char_gfx(0x5B30);
            if (plw[0].wu.operator != 0) {
                Sel_Arts_Complete[0] = -1;
            }
            if (plw[1].wu.operator != 0) {
                Sel_Arts_Complete[1] = -1;
            }
            if (plw[0].wu.operator != 0 && plw[1].wu.operator != 0) {
                Play_Type = PLAY_VS_PLAYER;
            } else {
                Play_Type = PLAY_VS_CPU;
            }
            BGM_Stop();
        }
        break;
    }
}



void Game01_Sub(void) {
    tilemap_print_string_attr((*(const s16(*)[2][2])&(Entry_Msg_X_Data[4]))[0][Game_setting.Screen_Mode], 0, 18, "                   ");
    tilemap_print_string_attr((*(const s16(*)[2][2])&(Entry_Msg_X_Data[4]))[1][Game_setting.Screen_Mode], 0, 18, "                   ");
    vital_cont_init();
    combo_cont_init();
    count_cont_init(0);
    player_name();
    player_face();
    sa_number_put();
    Setup_Play_Type();
    PL_Wins[0] = 0;
    PL_Wins[1] = 0;
    Score[0][SCORE_VS] = 0;
    Score[0][SCORE_ROUND] = 0;
    Score[1][SCORE_VS] = 0;
    Score[1][SCORE_ROUND] = 0;
    Score_Sub();
    Disp_Win_Record();
    Clear_Win_Type();
    Disp_Win_Type();
    win_mark_rno[0] = 0;
    win_mark_control(0);
    win_mark_rno[1] = 0;
    win_mark_control(1);
    set_kizetsu_status(0);
    set_kizetsu_status(1);
    set_super_arts_status(0);
    set_super_arts_status(1);
    if (Demo_Flag) {
        spgauge_cont_init();
    } else {
        spgauge_cont_demo_init();
    }
    spgauge_cont_main();
    stngauge_cont_init();
}



void Game05(void) {
    Basic_Sub_Suzi();
    switch (G_No2) {
    case G2_NEXT_INIT:
        G_No2++;
        S_No = 0;
        S_Sub_No = 0;
        S_Sub2_No = 0;
        S_Sub3_No = 0;
        Break_Into = 0;
        Stop_Combo = 0;
        load_any_color(5);
        load_any_color(135);
        init_slow_flag();
        break;
    case G2_NEXT_MAIN:
        if (Next_CPU()) {
            G_No2++;
            Game01_Sub();
            commit_name_entry_row_both_players(0);
            sc_vram_to_ram();
            Switch_Screen_Init(3, 3);
        }
        break;
    default:
        Next_CPU();
        if (Switch_Screen()) {
            Cover_Timer = 24;
            Scrn_Move_Set(4, 0, 0);
            G_No1 = G1_FIGHT;
            G_No2 = G2_FIGHT_INIT;
            E_No0 = E0_FIGHT;
            E_No1 = 0;
            E_No2 = 0;
            E_No3 = 0;
            BGM_Stop();
        }
        break;
    }
}



void Game02(void) {
    void (*Game02_Jmp_Tbl[5])() = { Game2_0, Game2_1, Game2_2, Game2_3, Game2_4 };
    Game02_Jmp_Tbl[G_No2]();
}



void Game2_0(void) {
    Setup_Play_Type();
    System_all_clear_Wait();
    load_any_color(1);
    Game_difficulty = 15;
    Game_timer = 0;
    Game_pause = 0;
    Demo_Time_Stop = 0;
    C_No0 = C0_INIT;
    C_No1 = 0;
    C_No2 = 0;
    C_No3 = 0;
    G_No2 = G2_FIGHT_START;
    G_Timer = 10;
    Round_num = 0;
    Allow_a_battle_f = 0;
    Time_in_Time = 60;
    init_slow_flag();
    load_any_color(0);
    effect_work_quick_init();
    clear_hit_queue();
    pcon_rno[0] = pcon_rno[1] = pcon_rno[2] = pcon_rno[3] = 0;
    ca_check_flag = 1;
    bg_work_clear();
    win_lose_work_clear();
    TATE00();
}



void Game2_1(void) {
    Game_timer += 1;
    set_EXE_flag();
    Time_Control();
    Player_control();
    vital_cont_main();
    combo_cont_main();
    TATE00();
    Game_Management();
    win_mark_control(0);
    win_mark_control(1);
    move_effect_work(0);
    move_effect_work(1);
    move_effect_work(2);
    move_effect_work(3);
    move_effect_work(4);
    move_effect_work(5);
    move_effect_work(6);
    hit_check_main_process();
}



/* Step 2 of the fight routine (Game02_Jmp_Tbl) has no work. */
void Game2_2(void)
{
}



void Game2_3(void) {
    Game2_1();
    if (--G_Timer) {
        return;
    }
    G_No2 = G2_FIGHT;
    Clear_Flash_No();
}



void Game2_4(void) {
    switch (G_No3) {
    case 0:
        G_No3++;
        Setup_Play_Type();
        System_all_clear_Wait();
        vital_cont_init();
        stngauge_work_clear();
        combo_cont_init();
        count_cont_init(1);
        Score[0][SCORE_ROUND] = 0;
        Score[1][SCORE_ROUND] = 0;
        Score_Sub();
        win_mark_rno[0] = 0;
        win_mark_control(0);
        win_mark_rno[1] = 0;
        win_mark_control(1);
        Game_pause = 0;
        pcon_rno[0] = PCON_INIT;
        pcon_rno[1] = APP_SETUP;
        pcon_rno[2] = 0;
        pcon_rno[3] = 0;
        appear_type = APPEAR_ROUND;
        bg_work_clear();
        win_lose_work_clear();
        if (bg_w.area < 2) {
            bg_w.area++;
        }
        TATE00();
        break;
    default:
        Game2_1();
        if (--G_Timer == 0) {
            G_No2 = G2_FIGHT;
            Clear_Flash_No();
        }
        break;
    }
}



/* The winner scene: runs Winner_Scene, then wipes out to the winner's next stage, or to game over in event
   mode. */
void Game03(void)
{
    move_effect_work(4);
    switch (G_No2) {
    case 0:
        if (Winner_Scene()) {
            if (Game_setting.Event) {
                G_No1 = G1_GAME_OVER;
                G_No2 = G2_OVER_INIT;
                G_No3 = 0;
                E_No0 = E0_GAME_OVER;
                E_No1 = 0;
                E_No2 = 0;
                E_No3 = 0;
            } else {
                G_No2++;
                sc_vram_to_ram();
                Switch_Screen_Init(0, 1);
            }
        }
        break;
    default:
        if (Switch_Screen()) {
            Cover_Timer = 24;
            G_No1 = G1_NEXT_CPU;
            G_No2 = G2_NEXT_INIT;
            G_No3 = 0;
            E_No0 = E0_NEXT_CPU;
            E_No1 = 0;
            E_No2 = 0;
            E_No3 = 0;
            Suicide = 1;
            if (Continue_Flag == 0) {
                break;
            }
            if (Round_Operator[LOSER]) {
                E_Number[LOSER][0] = ENTRY_CONTINUE;
                E_Number[LOSER][1] = 0;
                E_Number[LOSER][2] = 0;
                E_Number[LOSER][3] = 0;
            }
        }
        break;
    }
}



void Game04(void) {
    move_effect_work(4);
    switch (G_No2) {
    case 0:
        if (Loser_Scene()) {
            if (Continue_Flag) {
                G_No1 = G1_CONTINUE;
                G_No2 = 0;
                E_No0 = E0_CONTINUE;
                E_No1 = 0;
                E_No2 = 0;
                E_No3 = 0;
                Cont_No = 0;
                Cont_Sub_No = 0;
                Cont_Sub2_No = 0;
                Cont_Sub3_No = 0;
                if (Continue_Flag) {
                    E_Number[LOSER][0] = ENTRY_CONTINUE;
                    E_Number[LOSER][1] = 0;
                    E_Number[LOSER][2] = 0;
                    E_Number[LOSER][3] = 0;
                }
                while (create_task((void (*)())continue_task, 0, &task_tbl[1], 3, 0) == 0) {
                }
            } else {
                G_No1 = G1_GAME_OVER;
                G_No2 = G2_OVER_INIT;
            }
        }
        break;
    }
}



void Game08(void) {
    switch (G_No2) {
    case G2_END_INIT:
        G_No2 = G2_END_MAIN;
        break;
    case G2_END_MAIN:
        if (Ending_main(plw[WINNER].player_number)) {
            G_No1 = G1_GAME_OVER;
            G_No2 = G2_OVER_INIT;
            E_No0 = E0_GAME_OVER;
            E_No1 = 0;
            E_No2 = 0;
            E_No3 = 0;
            Clear_Personal_Data(WINNER);
            plw[WINNER].wu.operator = 0;
            Operator_Status[WINNER] = 0;
            Last_Player_id = Player_Number = -1;
        }
        break;
    }
    move_effect_work(4);
}



void Game06(void) {
    s16 xx;
    Basic_Sub_Ex();
    if (Break_Into) {
        return;
    }
    switch (G_No2) {
    case G2_OVER_INIT:
        G_No2 += 1;
        Stock_Com_Color = -1;
        Stock_Com_Arts = -1;
        Last_Player_id = -1;
        Control_Time = 481;
        sc_vram_to_ram();
        Switch_Screen_Init(0, 1);
        break;
    case G2_OVER_SETUP:
        if (Switch_Screen()) {
            G_No2 += 1;
            Cover_Timer = 24;
            System_all_clear_Wait();
            bg_etc_write(1);
            tilemap_print_string_attr(DE_X[0] + 14, Text_Page_Y + 5, 18, "                     ");
            tilemap_print_string_attr(DE_X[0] + 14, Text_Page_Y + 7, 18, "                ");
            bg_pos_hosei2();
            Bg_Family_Set();
            load_any_color(4);
            effect_58_init(6, 50, 157);
            for (xx = 0; xx < 8; xx++) {
                effect_40_init(xx, xx * 4 + 20);
            }
        }
        break;
    case G2_OVER_COVER:
        if (--Cover_Timer == 0) {
            E_No0 = E0_GAME_OVER;
            E_No1 = 0;
            E_No2 = 0;
            E_No3 = 0;
            G_No2 += 1;
            Clear_Flash_No();
            Switch_Screen_Init(0, 1);
        }
        break;
    case G2_OVER_REVIVAL:
        if (Switch_Screen_Revival()) {
            G_No2 += 1;
            G_Timer = 29;
            Ignore_Entry[LOSER] = 0;
            BGM_Request(10);
        }
        break;
    case G2_OVER_WAIT:
        if (--G_Timer == 0) {
            G_No2 += 1;
            G_Timer = 150;
            Forbid_Break = 0;
        }
        break;
    case G2_OVER_MESSAGE:
        if (--G_Timer) {
            break;
        }
        if (Check_Disp_Rank_Request()) {
            G_No2 = G2_OVER_NAME;
            effect_58_init(8, 40, 28);
        } else {
            G_Timer = 1;
            G_No2 = G2_OVER_EXIT;
        }
        break;
    case G2_OVER_NAME:
        if (E_Number[0][0] != ENTRY_NAME && E_Number[1][0] != ENTRY_NAME) {
            G_No2 += 1;
            G_No3 = 0;
            G_Timer = 20;
        }
        break;
    case G2_OVER_RANK_SEL:
        if (--G_Timer) {
            break;
        }
        if (Request_Disp_Rank[0][RANK_SCORE] >= 0 || Request_Disp_Rank[1][RANK_SCORE] >= 0) {
            G_No2 += 1;
            Rank_Type = 0;
            Present_Rank[0] = Rank_In[0][RANK_SCORE];
            Present_Rank[1] = Rank_In[1][RANK_SCORE];
        } else {
            G_No2 = G2_OVER_RANKING2;
            Rank_Type = 6;
            Present_Rank[0] = Rank_In[0][RANK_WINS];
            Present_Rank[1] = Rank_In[1][RANK_WINS];
        }
        break;
    case G2_OVER_RANKING:
        if (Disp_Ranking()) {
            if (Request_Disp_Rank[0][RANK_WINS] >= 0 || Request_Disp_Rank[1][RANK_WINS] >= 0) {
                G_No2 += 1;
                G_No3 = 0;
                Rank_Type = 6;
                Present_Rank[0] = Rank_In[0][RANK_WINS];
                Present_Rank[1] = Rank_In[1][RANK_WINS];
            } else {
                G_No2 = G2_OVER_EXIT;
                G_Timer = 1;
            }
        }
        break;
    case G2_OVER_RANKING2:
        if (Disp_Ranking()) {
            G_No2 += 1;
            G_Timer = 1;
        }
        break;
    case G2_OVER_EXIT:
        if (--G_Timer) {
            break;
        }
        G_No2 += 1;
        Request_Disp_Rank[0][RANK_SCORE] = -1;
        Request_Disp_Rank[0][RANK_WINS] = -1;
        Request_Disp_Rank[1][RANK_SCORE] = -1;
        Request_Disp_Rank[1][RANK_WINS] = -1;
        Rank_In[0][RANK_SCORE] = -1;
        Rank_In[0][RANK_WINS] = -1;
        Rank_In[1][RANK_SCORE] = -1;
        Rank_In[1][RANK_WINS] = -1;
        for (xx = 0; xx <= 12; xx++) {
            Break_Com[0][xx] = 0;
            Break_Com[1][xx] = 0;
        }
        sc_vram_to_ram();
        Switch_Screen_Init(0, 1);
        break;
    default:
        if (Switch_Screen()) {
            Cover_Timer = 24;
            Clear_Personal_Data(LOSER);
            Clear_Flash_No();
            Forbid_Break = 0;
            scfont_page0_fill(0, 32);
            if (Request_Break[0] != 0 || Request_Break[1] != 0) {
                Request_Break_Sub(0);
                Request_Break_Sub(1);
                G_No1 = G1_SELECT;
                G_No2 = G2_SEL_INIT;
                G_No3 = 0;
                E_No0 = E0_SELECT;
                E_No1 = 0;
                E_No2 = 0;
                E_No3 = 0;
                break;
            }
            G_No0 = G0_DEMO;
            G_No1 = G1_DEMO_RESTART;
            G_No2 = 0;
            G_No3 = 0;
            E_No0 = E0_DEMO;
            E_No1 = 99;
            E_No2 = 0;
            E_No3 = 0;
            D_No0 = 0;
            D_No1 = 0;
            D_No2 = 0;
            D_No3 = 0;
            System_all_clear_Wait();
        }
        break;
    }
}



/* provisional name */
s32 Check_Disp_Rank_Request(void) {
    if (Request_Disp_Rank[0][RANK_SCORE] >= 0 || Request_Disp_Rank[0][RANK_WINS] >= 0) {
        return 1;
    }
    if (Request_Disp_Rank[1][RANK_SCORE] >= 0 || Request_Disp_Rank[1][RANK_WINS] >= 0) {
        return 1;
    }
    return 0;
}



/* Puts a waiting break-in request (Request_Break) through Ck_Break_Into, making the player an operator. */
void Request_Break_Sub(PL_id)
s16 PL_id;
{
    if (Request_Break[PL_id]) {
        Ck_Break_Into(0, 0, PL_id);
        plw[PL_id].wu.operator = 1;
        Operator_Status[PL_id] = 1;
    }
}



s32 Disp_Ranking(void) {
    switch (G_No3) {
    case G3_RANK_INIT:
        G_No3++;
        sc_vram_to_ram();
        Switch_Screen_Init(0, 0);
        break;
    case G3_RANK_SETUP:
        if (Switch_Screen()) {
            Cover_Timer = 24;
            G_No3++;
            D_No0 = 1;
            D_No1 = 0;
            D_No2 = 0;
            D_No3 = 0;
            Clear_Personal_Data(0);
            Clear_Personal_Data(1);
        }
        break;
    case G3_RANK_COVER:
        Ranking();
        if (--Cover_Timer) {
            break;
        }
        G_No3++;
        Switch_Screen_Init(0, 0);
        break;
    case G3_RANK_REVIVAL:
        Ranking();
        if (Switch_Screen_Revival() != 0) {
            G_No3++;
            Forbid_Break = 0;
            BGM_Request(8);
        }
        break;
    default:
        if (Ranking() == 0) {
            break;
        }
        BGM_Stop();
        return 1;
    }
    return 0;
}



void Game07(void) {
    Basic_Sub();
    switch (G_No2) {
    case 0:
        break;
    default:
        if (--G_Timer == 0) {
            Forbid_Break = 0;
            G_No0 = G0_DEMO;
            G_No1 = G1_DEMO_INIT;
            G_No2 = 0;
            G_No3 = 0;
            E_No0 = E0_DEMO;
            E_No1 = 0;
            E_No2 = 0;
            E_No3 = 0;
            D_No0 = 0;
            D_No1 = 0;
            D_No2 = 0;
            D_No3 = 0;
            scfont_page0_fill(0, 32);
            Clear_Flash_No();
            System_all_clear_Wait();
            Scrn_Move_Set(4, 0, 0);
            ToneDown(0);
        }
        break;
    }
}



/* provisional name */
void Game_Dummy(void) {
}



/* provisional name: with exsw_3 bit 0, G_No0-2 and E_No0-2 are shown in hex */
void Disp_Game_No(void) {
    if (exsw_3 & 1) {
        tilemap_print_hex_block(20, 1, 18, G_No0, 1, 1);
        tilemap_print_hex_block(20, 2, 18, G_No1, 1, 1);
        tilemap_print_hex_block(20, 3, 18, G_No2, 1, 1);
        tilemap_print_hex_block(22, 1, 18, E_No0, 1, 1);
        tilemap_print_hex_block(22, 2, 18, E_No1, 1, 1);
        tilemap_print_hex_block(22, 3, 18, E_No2, 1, 1);
        tilemap_print_hex_block(25, 1, 18, 18, 4, 1);
    }
}



void Time_Control(void) {
    if (Allow_a_battle_f != 0 && Demo_Time_Stop == 0) {
        count_cont_main();
        if (Control_Time >= Limit_Time) {
            Control_Time = Limit_Time;
        } else if (--Time_in_Time == 0) {
            Time_in_Time = 60;
            Control_Time++;
        }
    }
}


s32 Ck_Coin(void) {
    s16 pl;
    if (Free_Play) {
        pl = -1;
        if (~p1sw_1 & p1sw_0 & BUTTON_START) {
            pl = 0;
        } else if (~p2sw_1 & p2sw_0 & BUTTON_START) {
            pl = 1;
        }
        if (pl == -1) {
            return 0;
        }
        bg_vbl_trans_flag = 0;
        bookkeep_freeplay_count();
        if (Game_setting.Event) {
            plw[0].wu.operator = 1;
            plw[1].wu.operator = 1;
            Operator_Status[0] = 1;
            Operator_Status[1] = 1;
            return 1;
        } else {
            plw[pl].wu.operator = 1;
            Operator_Status[pl] = 1;
            Champion = pl;
            plw[pl ^ 1].wu.operator = 0;
            Operator_Status[pl ^ 1] = 0;
            return 1;
        }
    } else if (coin_chute1_w.dropped | coin_chute2_w.dropped) {
        return 1;
    }
    return coin_chute1_w.count | coin_chute2_w.count | credit_1p | credit_2p;
}



/* provisional name */
void draw_operator_info(s32 y) {
    if (Country == 6 || Country == 5) {
        if (p1sw_0 & BUTTON_LP) {
            tilemap_print_string_attr(34, y + 16, 18, Game_Data_msg);
            tilemap_print_string_attr(29, y + 17, 18, Income_msg);
            tilemap_print_string_attr(29, y + 18, 18, Service_msg);
            tilemap_print_string_attr(29, y + 19, 18, Card_msg);
            tilemap_print_hex_block(39, y + 17, 18, hex_to_bcd(*(s32*)&book_coin_count), 6, 0);
            tilemap_print_hex_block(39, y + 18, 18, hex_to_bcd(*(s32*)&book_service_count), 6, 0);
            tilemap_print_hex_block(39, y + 19, 18, hex_to_bcd(*(s32*)&book_card_count), 6, 0);
        } else {
            tilemap_clear_rect(29, y + 16, 47, y + 19);
        }
    }
}
