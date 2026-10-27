#ifndef WORK_H
#define WORK_H

#include "structs.h"

/* element ix of a table row, addressed from the row start */
#define ROW_ELEM(row, ix) ((&(row)[0])[ix])

extern s32 (*const decode_chcmd[125])();
extern s32 (*const decode_if_lever[16])();
extern s32 (*const Passive_AS_tbl[13])(PLW* wk);
extern s32 (*const Passive_A_tbl[13])(PLW* wk);
extern s32 (*const Passive_BS_tbl[13])(PLW* wk);
extern s32 (*const Passive_B_tbl[13])(PLW* wk);
extern s32 (*const Passive_CS_tbl[13])(PLW* wk);
extern s32 (*const Passive_D_tbl[13])(PLW* wk);
extern const s16 cmb_pos_tbl[2][2][21];
extern const s16 cmb_window_move_tbl[7];
extern const s16 cmb_window_time_tbl[7];
extern const u32 combo_score_tbl[16][2];
extern s16 ID;
extern void (*const plpdm_xxxxx[39])(PLW* wk);
extern const CHAR_INIT_ROM char_init_data[24];
extern s16 old_cmb_flag[2];
extern s8 cmb_stock[2];
extern s8 first_attack;
extern s8 rever_attack[2];
extern s8 paring_attack[2];
extern s8 bonus_pts[2];
extern s16 hit_num;
extern u8 sa_kind;
extern u8 end_flag[2];
extern s16 calc_hit[2][10];
extern s16 score_calc[2][11];
extern s8 cmb_all_stock;
extern s8 sarts_finish_flag[2];
extern s8 last_hit_time;
extern u8 cst_read[2];
extern u8 cst_write[2];
extern CMST_WIN cmst_buff[2][4];
extern void (*const EFF42_Jmp_Tbl[5])();
extern void (*const EFF74_Jmp_Tbl[5])();
extern u32 frw[128][512];
extern u8 frw_tail[4];
extern s16 frwque[128];
extern s16 frwctr;
extern s16 head_ix[8];
extern s16 tail_ix[8];
extern s16 exec_tm[8];
extern struct _TASK task[11];
extern s8 sa_pa_flag;
extern u8 bios_region_code;
extern u8 bios_cd_flags;
extern s8 Coin_Mode;
extern s8 Chute_Mode;
extern s8 Sound_Mode;
extern s8 Win_Point_Com;
extern s8 Win_Point_Human;
extern s8 Win_Point_Com_Max;
extern s8 Win_Point_Human_Max;
extern s8 Win_Point_Com_Min;
extern s8 Win_Point_Human_Min;
extern s8 Win_Point_Split;
extern s8 Cabinet_Type;
extern s8 Area_Type;
extern s8 Area_Alt_Flag;
extern s8 Two_Coin_Start;
extern s8 Free_Play_Enable;
extern s8 Cd_Error_Flag;
extern s16 Config_No_0;
extern s16 Config_No_1;
extern s16 Config_No_2;
extern const char * reg_name_tbl[];
extern u32 task_stack_size[3];
extern s32 task_stack_num;
extern u32* isp_vblank;             /* provisional name */
extern u32* isp_sprite_poly;        /* provisional name */
extern u32* isp_irq_spare;          /* provisional name */
extern void* isp_unused[2];
extern u32* isp_exception;          /* provisional name */
extern u32* isp_frt_compare;        /* provisional name */
extern u32* isp_frt_overflow;       /* provisional name */
extern u8 test_flag;
extern u32 frt_tick_count;          /* provisional name */
extern TCB * current_task;
extern s32 task_sys_w1;
extern s32 task_sys_w2;
extern s32 task_sys_w3;
extern s32 task_free_count;
extern u32 system_timer;
extern u32 task_tick_mask;
extern s8 system_ctrl_flag;
extern s8 task_tick_mode;
extern s8 vsync_flag;
extern u32 frame_pass_count;
extern s8 task_ran_flag;
extern u32 task_sched_context[3];   /* provisional name */
extern SETTINGS game_config_work;
extern EXC_REGS exception_regs;      /* provisional name */
extern u32 exception_code;          /* provisional name */
extern u8 boot_stack[4100];         /* provisional name */
extern u8 task_stack[][1024];
extern TCB task_tbl[8];
extern s32 errno;
extern TM_STRING warning_mes[8][11];
extern TM_STRING parental_advisory_msg[4];
extern const u8* sys_cfg_default_list[3][9];
extern u32 sys_cfg_default_tbl[];
extern u8 * game_cfg_default_tbl[];
extern s8 Monitor_Flip_Old;
extern const FOLLOW_MENU_1ST* Follow_Menu_1st_Unit_Data[13];
extern const FOLLOW_MENU_2ND* Follow_Menu_2nd_Unit_Data[13];
extern TMSCRIPT gcfg_title_scr_jp[1];   /* first of the menu scripts */
extern TMSCRIPT gcfg_guide_scr_jp[1];
extern TMSCRIPT gcfg_exit_guide_scr_jp[1];
extern TMSCRIPT gcfg_screen_scr_jp[2];
extern TMSCRIPT gcfg_round_scr_jp[4];
extern TMSCRIPT gcfg_event_scr_jp[2];
extern TMSCRIPT gcfg_cursor_scr_jp[1];
extern TMSCRIPT gcfg_cursor_clr_scr_jp[1];
extern TMSCRIPT gcfg_gauge_scr_jp[8];
extern TMSCRIPT gcfg_gauge_clr_scr_jp[1];
extern TM_STRING gcfg_screen_str_en[2];
extern TM_STRING gcfg_round_str_en[4];
extern TM_STRING gcfg_event_str_en[2];
extern TM_STRING dbg_menu_str[15];
extern TM_STRING dbg_obj_info_str[];
extern TM_STRING dbg_obj_rel_str[];
extern TM_STRING dbg_all_char_str[];
extern TM_STRING dbg_edit_num_str[];
extern TM_STRING dbg_rec_menu_str[3];
extern TM_STRING dbg_rec_clear_str[3];
extern TM_STRING dbg_rec_nodata_str[2];
extern TM_STRING dbg_hit_size_str[];
extern TM_STRING dbg_hit_part_str[];
extern TM_STRING dbg_cg_head_str[];
extern TM_STRING dbg_cg_att_str[];
extern TM_STRING dbg_cg_rival_str[];
extern TM_STRING dbg_cgd_info_str[];
extern TM_STRING dbg_att_data_str[];
extern TM_STRING dbg_hud_clr_str[];
extern TM_STRING dbg_hud_clr_mid_str[];
extern TM_STRING dbg_hud_clr_low_str[];
extern TM_STRING dbg_hud_clr_bottom_str[];
extern TM_STRING dbg_cm_label_str[];
extern TM_STRING dbg_cgd_type_str[];
extern TM_STRING dbg_cg_group_str[];
extern TM_STRING dbg_edit_group_str[];  /* 020022A0, provisional name: CG group names for the object edit screens */
extern TM_STRING dbg_preview_group_str[];  /* 02001DC0, provisional name: CG group names for the character preview */
extern TM_STRING dbg_pat_status_str[];
extern TM_STRING dbg_extdat_str[];
extern TM_STRING dbg_eftype_names[];
extern TM_STRING dbg_eftype_s_str[];
extern TM_STRING dbg_eftype_usemj_str[];
extern TM_STRING dbg_cancel_on_str[];
extern TM_STRING dbg_cancel_off_str[];
extern TM_STRING dbg_koc_cmlp_str[];
extern TM_STRING dbg_koc_cml2_str[];
extern TM_STRING dbg_koc_cmsw_str[];
extern TM_STRING dbg_koc_cmja_str[];
extern TM_STRING dbg_koc_cmoa_str[];
extern TM_STRING dbg_koc_str[];
extern TM_STRING dbg_waza_kind_str[];
extern TM_STRING dbg_char_name_str[];
extern TM_STRING dbg_act_kind_str[];
extern const TM_STRING * dbg_act_name_tbl[];
extern u32 * dbg_pl_char_tbl[][9];
extern void (*chk_move_jp[27])();
extern void * pl_CMD[];
extern const_s16_arr * player_cmd[];
extern s16 lvr_chk_tbl[2][4];
extern void (*ta_move_tbl[23])();
extern void (*scr_x_mv_jp[])();
extern u32 bg_map_tbl[][4];
extern u32 bg_map_tbl2[][4];
extern HUD_CELL * bg_rewrite_cell_tbl[][4];
extern TILEREQ * bg_etc_cell_tbl[][4];
extern void (*opening_move_jp[19])();
extern void (*end_main_jp[24])(s16);
extern u32 end_map_tbl[];
extern void (*end_400_jp[5])();
extern void (*end_401_jp[5])();
extern void (*end_402_jp[5])();
extern const u16* vital_npos_tbl[4];
extern const u16* vital_attr_tbl[3];
extern const u16 * spgauge_puttbl[2];
extern const u16 * spgauge_postbl[4];
extern u32 fade_adrs_tbl[];
extern const u16 * stngauge_puttbl[2];
extern const u16 * stngauge_postbl[4];
extern const s16 * scr_obj_data[14][3];   /* per stage and area */
extern const s16 * scr_obj_data6[14][3];   /* by stage and area */
extern void (*eff09_tbl[9])(WORK_Other*);   /* eff09_0000-8000 */
extern const s16 * scr_obj_data10[];
extern const s16 * scr_obj_data18[6][4];
extern void (*eff18_jp_tbl[])(WORK_Other*);
extern const s16 * scr_obj_data25[9];
extern void (*eff25_jp_tbl[8])(WORK_Other* ewk);
extern void (*eff26_jp_tbl[6])(WORK_Other*);
extern const s16 * scr_obj_data26[2];   /* two types */
extern const s16 * scr_obj_data27[7];   /* seven types */
extern void (*eff27_jp_tbl[11])(WORK_Other*);
extern void (*eff64_jp_tbl[])(WORK_Other*);
extern void (*eff66_jp_tbl[])(WORK_Other*);
extern const s16 * scr_obj_data87[][4];
extern const s16 * scr_obj_data88[][4];
extern const EFFB8_MESSAGE * effB8_mes_jp[];
extern const EFFB8_MESSAGE * effB8_mes_en[];
extern const EFFB8_MESSAGE * effB8_mes_es[];
extern const EFFB8_MESSAGE * effB8_mes_pt[];
extern u32 * ag_char_table[7];
extern const EFFF9_MESSAGE * effF9_mes_jp[13];
extern const EFFF9_MESSAGE * effF9_mes_en[13];
extern const EFFF9_MESSAGE * effF9_mes_es[13];
extern const EFFF9_MESSAGE * effF9_mes_pt[13];
extern s32 * txt_no_tbl[13];
extern s16 * effH7_move_tbl[];
extern const s16 (*effM4_dir_tbl[])[2];
extern TM_STRING test_menu_str[];
extern TM_STRING test_menu_str_asia[];
extern TMSCRIPT test_menu_scr_jp[];
extern TMSCRIPT sys_cfg_page_scr_jp[];
extern TMSCRIPT sys_cfg_exit_guide_jp[];
extern TMSCRIPT sys_cfg_item_guide_jp[];
extern TMSCRIPT cfg_top_guide_jp[];
extern TMSCRIPT cfg_top_reset_guide_jp[];
extern s16 iotest_in_no;
extern s16 iotest_out_no;
extern s16 soundtest_rep_timer;
extern s16 soundtest_code;
extern s16 soundtest_no;
extern s16 colortest_no;
extern s16 screentest_no;
extern s16 backup_test_no;
extern s16 config_menu_no;
extern s8 * simm_name_tbl[];
extern u8 no_cd_flag;
extern s16 memtest_error;
extern s16 memtest_wait;
extern s16 memtest_cursor;
extern s16 memtest_no;
extern s16 rewrite_no;
extern s16 rewrite_cursor;
extern s8 credit_1p;
extern s8 credit_2p;
extern s8 credit_3p;
extern s8 credit_4p;
extern s8 coin_count_1p;
extern s8 coin_count_2p;
extern s8 coin_count_3p;
extern s8 coin_count_4p;
extern u8 coin_in_flag;
extern u8 coin_out_latch;
extern COINCHUTE * coin_chute_tbl[4];
extern void * coin_sw_tbl[4][2];
extern s8 * credit_ptr_tbl[4];
extern s8 * coin_count_ptr_tbl[4];
extern s32 card_empty_flag;
extern u32 bookkeep_add0;
extern u32 bookkeep_add1;
extern u32 bookkeep_add2;
extern u32 bookkeep_add3;
extern s8 event_off_flag;
extern const TM_STRING * coin_setting_str_tbl[];
extern const TM_STRING * chute_mode_str_tbl[];
extern const TM_STRING * on_off_str_tbl[];
extern const TM_STRING * sound_mode_str_tbl[];
extern const TM_STRING * monitor_str_tbl[];
extern void (*config_menu_tbl[2])(void);
extern void (*config_page_tbl[3])(void);
extern void (*config_top_step_tbl[2])(void);
extern void (*config_top_item_tbl[])(void);
extern void (*sysconfig_step_tbl[2])(void);
extern void (*sysconfig_item_tbl[])(void);
extern void (*sysconfig_item_tbl_b[])(void);
extern void (*sysconfig_item_card_tbl[])(void);
extern void (*sysconfig_item_tbl_c[])(void);
extern void (*sysconfig_item_card_tbl2[])(void);
extern u16 sprite_dummy_code;
extern u16 sprite_head_x;
extern u16 sprite_head_y;
extern u16 sprite_pad_x;
extern u16 sprite_pad_y;
extern u32 spr_pool_busy;
extern u32 poly_buf_offset;
extern s32 poly_cram_bank;
extern TASK_QUEUE task_req_queue;
extern u8 task_req_buff[];
extern s16 test_rno;
extern s16 test_menu_no;
extern s16 test_cursor;
extern s16 test_cursor_on;
extern s16 test_cursor_off;
extern s16 test_font_type;
extern s16 test_cursor_max;
extern SCREEN_WINDOW screen_window[2];
extern volatile s16 screen_disp_ctrl;
extern s16 screen_base_x;
extern s16 screen_base_y;
extern s32 screen_mode;
extern u8 zoom_req_flag;
extern u8 window_req_flag;
extern s16 zoom_adj_x;
extern s16 zoom_adj_y;
extern u16 flip_obj_ofs_x;
extern u16 flip_obj_ofs_y;
extern s16 flip_scr_ofs_x;
extern s16 flip_scr_ofs_y;
extern s16 flip_zoom_ofs_x;
extern s16 flip_zoom_ofs_y;
extern s8 Lv;
extern s8 Rnd;
extern s8 PASSIVE_X;
extern WORK * q_hit_push[32];
extern HS hs[32];
extern s8 ca_check_flag;
extern s16 mkm_wk[32];
extern s16 hpq_in;
extern s16 EXE_flag;
extern s16 SLOW_flag;
extern s16 SLOW_timer;
extern u16 * wipe_dst_ptr;
extern u8 * wipe_back_ptr;
extern u8 * wipe_pat_top;
extern u8 * wipe_pat_ptr;
extern s16 Game_pause;
extern s16 Game_difficulty;
extern s16 Control_Time;
extern s16 Time_in_Time;
extern s16 Counter_hi;
extern s16 Round_Level;
extern u16 Round_Result;

/* Round_Result: bits for how the round was won (the others are the KO attack's dm_koa) */
#define RESULT_TIME     1       /* won on vitality at time over */
#define RESULT_PERFECT  2       /* the winner took no damage */
#define RESULT_CHIP     0x200   /* KO by chip damage (kezurijini_flag) */
#define RESULT_DRAW     1024    /* a draw: both take the round */
#define RESULT_JUDGE    0x8000  /* decided by the judges */

extern s8 request_message;
extern s8 Winner_id;
extern s8 Loser_id;
extern s16 PL_Wins[2];
extern s8 Break_Into;
extern u8 My_char[2];
extern s8 Super_Arts[2];
extern s8 Fade_Flag;
extern s8 Forbid_Break;
extern s8 Request_Break[2];
extern s16 Fade_R_No0;
extern s16 Fade_R_No1;
extern u8 Fade_Mode;
extern u32 Score[2][3];
/* Score[pl] columns (SCORE_PLUS) */
#define SCORE_CPU       0       /* the score against the CPU */
#define SCORE_VS        1       /* the score of this versus match */
#define SCORE_ROUND     2       /* all points this round, either way */
extern s16 Play_Type;

/* Play_Type */
#define PLAY_VS_CPU     0       /* one player against the CPU */
#define PLAY_VS_PLAYER  1       /* two players against each other (Setup_Play_Type) */

extern s8 Personal_Continue_Flag[2];
extern s8 Personal_Disp_Flag;
extern s8 WINNER;
extern s8 LOSER;
extern s16 Conclusion_Type;

/* Conclusion_Type: how the round ended (settle_check, time_over_check) */
#define CONCLUSION_KO   0       /* one player KO */
#define CONCLUSION_DOUBLE_KO 1  /* both players KO */
#define CONCLUSION_TIME_OVER 2  /* time over */

extern s16 win_type[2][4];

/* win_type[pl][round]: the win mark of each round won (Setup_Win_Mark) */
#define WIN_MARK_NORMAL 1       /* a KO or a win on time */
#define WIN_MARK_PERFECT 3      /* a perfect */
#define WIN_MARK_SA     4       /* a super art finish */
#define WIN_MARK_DRAW   5       /* a draw */
#define WIN_MARK_JUDGE  6       /* the judges' decision */
#define WIN_MARK_CHIP   7       /* a chip damage KO */

extern s8 win_pause_go;
extern s16 message_index;
extern s16 Conclusion_Flag;
extern s8 New_Challenger;
extern s8 Champion;
extern s8 Complete_Judgement;
extern s8 Perfect_Flag;
extern s16 Fade_Gap_Timer;
extern s8 Fade_Half_Flag;
extern u32 Vital_Bonus;
extern u32 Time_Bonus;
extern u32 Total_Bonus;
extern u32 Round_Perfect_Bonus;
extern s16 win_mark_new[2];
extern s8 Next_Step;
extern s8 judge_flag;
extern u8 sc_chr_ram[];
extern s8 Cover_Timer;
extern s16 Text_Page_Y;
extern s8 E_07_Flag[2];
extern s8 Personal_Timer[2];
extern s8 Request_E_No;
extern s8 Request_G_No;
extern s16 G_Timer;
extern s16 G_No0;
extern s16 G_No1;
extern s16 G_No2;
extern s16 G_No3;

/* G_No0: the top-level game routine (bg0001) */
#define G0_DEMO         0       /* no game: the attract loop (match_state_0_fight) */
#define G0_GAME         1       /* a game in progress (game_phase_dispatch) */

/* G_No1 under G0_DEMO: the attract loop */
#define G1_DEMO_INIT    0       /* reset the loop */
#define G1_DEMO_LOGO    1       /* the CAPCOM logo */
#define G1_DEMO_WARNING 2       /* the warning screen (Country 4) */
#define G1_DEMO_LOGO_ETC 3      /* the screen after the warning */
#define G1_DEMO_TITLE   4       /* the title */
#define G1_DEMO_PLAY    5       /* a demo fight */
#define G1_DEMO_RANKING 6       /* the ranking */
#define G1_DEMO_PLAY2   7       /* a second demo fight */
#define G1_DEMO_RANKING2 8      /* another ranking, then back to the logo */
#define G1_DEMO_RESTART 99      /* (default) after a game: wait out the cover, then the logo */

/* G_No1 under G0_GAME: the game phase (game_phase_dispatch) */
#define G1_TITLE        0       /* Game00: the title, until a start button */
#define G1_SELECT       1       /* Game01: player select */
#define G1_FIGHT        2       /* Game02: the fight */
#define G1_WINNER       3       /* Game03: winner scene */
#define G1_LOSER        4       /* Game04: loser scene */
#define G1_NEXT_CPU     5       /* Game05: the next CPU opponent */
#define G1_GAME_OVER    6       /* Game06: game over and ranking */
#define G1_CONTINUE     7       /* Game07: continue */
#define G1_ENDING       8       /* Game08: ending */

/* G_No2 under G1_FIGHT: the Game02 routine */
#define G2_FIGHT_INIT   0       /* Game2_0: set up the fight */
#define G2_FIGHT        1       /* Game2_1: the fight */
#define G2_FIGHT_START  3       /* Game2_3: the round start, for G_Timer frames */
#define G2_ROUND_RESET  4       /* Game2_4: clear the stage work and displays for the next round */


extern s16 D_Timer;
extern s16 D_No0;
extern s16 D_No1;
extern s16 D_No2;
extern s16 D_No3;
extern u8 Present_Rank[2];
extern s8 Rank_In[2][2];   /* two rankings */
extern s8 Request_Disp_Rank[2][2];
/* Rank_In[pl][], Request_Disp_Rank[pl][]: one entry per ranking (Check_Ranking) */
#define RANK_SCORE      0       /* score */
#define RANK_WINS       1       /* consecutive wins (Win_Record) */
extern s8 Rank_Demo_Loop;
extern s8 Rank_Type;
extern s8 Flash_Rank_Time;
extern s8 Flash_Rank_Interval;
extern s8 Rank;
extern s8 Rank_X;
extern s16 Rank_Pos_X;
extern s16 Rank_Pos_Y;
extern s16 E_Timer;
extern s16 E_No0;
extern s16 E_No1;
extern s16 E_No2;
extern s16 E_No3;

/* E_No0: the entry task's routine (entry_main), following the game phase */
#define E0_DEMO         0       /* Entry_00: flash INSERT COIN / FREE PLAY */
#define E0_TITLE        1       /* Entry_01: wait for a start button */
#define E0_SELECT       2       /* Entry_02: player select */
#define E0_SELECTED     3       /* Entry_03: both players have chosen */
#define E0_FIGHT        4       /* Entry_04: a fight or bonus stage */
#define E0_WINNER       5       /* Entry_03: winner scene */
#define E0_LOSER        6       /* Entry_06: loser scene */
#define E0_CONTINUE     7       /* Entry_07: continue */
#define E0_GAME_OVER    8       /* Entry_08: game over */
#define E0_NEXT_CPU     9       /* Entry_03: next opponent screens */
#define E0_ENDING       10      /* Entry_10: ending */

extern s16 F_No0[2];
extern s16 F_No1[2];
extern s16 F_No2[2];
extern s16 F_Timer[2];
extern s16 E_Number[2][4];

/* E_Number[pl][0]: a player's entry state (Entry_Main_Sub) */
#define ENTRY_NONE      0       /* not playing: may join or break in */
#define ENTRY_CONTINUE  1       /* the continue count (Entry_Continue_Sub) */
#define ENTRY_NAME      2       /* name entry for the ranking */
#define ENTRY_NAME_WAIT 3       /* until the game-over or select screen, then name entry or GAME OVER */
#define ENTRY_LOSER     5       /* lost, in the loser scene: may continue (Loser_Scene_Sub) */
#define ENTRY_GAME_OVER 8       /* GAME OVER for this player (In_Game_Sub, In_Over_Sub) */

extern s16 ENTRY_X;
extern s16 C_Timer;
extern s16 C_No0;
extern s16 C_No1;
extern s16 C_No2;
extern s16 C_No3;

/* C_No0: the round management routine (Game_Management) */
#define C0_INIT         0       /* Game_Manage_1st: set up the stage */
#define C0_ROUND_START  1       /* Game_Manage_2nd: wipe in and call the round */
#define C0_FIGHT        2       /* Game_Manage_3rd: until the round is decided */
#define C0_DECIDE       3       /* Game_Manage_4th: score the round by Conclusion_Type */
#define C0_JUDGE        4       /* Game_Manage_5th: the judges' decision */
#define C0_DRAW         5       /* Game_Manage_6th: a draw */
#define C0_ROUND_WIN    6       /* Game_Manage_7th: the round's winner */
#define C0_ROUND_END    7       /* Game_Manage_8th: the round scores and bonuses */
#define C0_NEXT         8       /* Game_Manage_9th: the next round, or the match is over */
#define C0_MATCH_END    9       /* Game_Manage_10th: on to the winner or loser scene */

extern s8 Complete_Victory;
extern s8 Demo_Flag;
extern s8 Demo_Stage_Index;
extern s16 S_No;
extern s16 S_Sub_No;
extern s16 S_Sub2_No;
extern s16 S_Sub3_No;
extern s16 Flash_Complete[2];
extern s16 Sel_PL_Complete[2];
extern s16 Sel_Arts_Complete[2];
extern s16 Select_Start[2];
extern s16 Cursor_X[2];
extern s16 Arts_Y[2];
extern s16 Cursor_Y_Pos[][3];
extern s16 Stop_Cursor[2];
extern s16 Move_Super_Arts[2];
extern s16 Battle_Country;
extern s16 Face_Status;
extern s8 Face_MV_Request;
extern s8 Face_Move;
extern s8 Appear_Cursor;
extern s8 Select_Timer;
extern s8 Time_Stop;
extern s8 Time_Over;
extern s16 Unit_Of_Timer;
extern s8 Player_id;
extern s8 Last_Player_id;
extern s8 Player_Number;
extern s8 COM_id;
extern s8 EM_id;
extern s16 Plate_X[2][3];
extern s16 Plate_Y[2][3];
extern s16 SP_No[2][4];
extern s16 Sel_Sub_No[2];
extern s16 Arts_Cursor_No[2];
extern s16 Arts_Cursor_Timer[2];
extern s16 Exit_No;
extern s16 Select_Arts[2];
extern s8 Select_Status[2];
extern s8 Select_Demo_Index;
extern u8 Country;
extern s16 mes_already;
extern s16 CP_No[2][4];

/* CP_No[pl][0]: the computer player's routine (Com_Jmp_Tbl) */
#define COM_INIT        0       /* Com_Initialize */
#define COM_FREE        1       /* Com_Free */
#define COM_ACTIVE      2       /* Com_Active */
#define COM_BEFORE_FOLLOW 3     /* Com_Before_Follow */
#define COM_FOLLOW      4       /* Com_Follow */
#define COM_BEFORE_PASSIVE 5    /* Com_Before_Passive */
#define COM_PASSIVE     6       /* Com_Passive */
#define COM_GUARD       7       /* Com_Guard */
#define COM_VS_SHELL    8       /* Com_VS_Shell: against a projectile */
#define COM_SHELL_GUARD 9       /* Check_No12_Shell_Guard: guarding a projectile */
#define COM_DAMAGE      10      /* Com_Damage */
#define COM_FLOAT       11      /* Com_Float */
#define COM_FLIP        12      /* Com_Flip */
#define COM_CAUGHT      13      /* Com_Caught */
#define COM_WAIT_LIE    14      /* Com_Wait_Lie */
#define COM_CATCH       15      /* Com_Catch */

extern s16 CP_Index[2][8];
extern s16 Pattern_Index[2];
extern s16 Timer_00[2];
extern s16 Timer_01[2];
extern s8 Combo_Speed[2];
extern s16 PL_Distance[2];
extern s16 Area_Number[2];
extern u16 Lever_Buff[2];
extern u16 Lever_Pool[2];
extern const_s16_arr Tech_Address[2];
extern s16 Tech_Index[2];
extern s16 Random_ix16_com;
extern s16 Random_ix32_com;
extern s16 M_Timer;
extern s16 VS_Tech[2];
extern s8 Exec_Wipe;
extern s16 Guard_Type[2];
extern s16 Separate_Area[2][3];
extern u32 * Shell_Address[2];
extern u16 Free_Lever[2];
extern s8 Passive_Flag[2];
extern s8 Flip_Flag[2];
extern s16 Air_Guard_Type[2];
extern s8 Lie_Flag[2];
extern s16 Term_No[2];
extern s8 Attack_Flag[2];
extern s8 Passive_Mode;
extern s8 Limited_Flag[2];
extern s8 Shell_Ignore_Timer[2];
extern s16 Com_Width_Data[2];
extern s8 Event_Judge_Gals;
extern u8 EJG_index[4];
extern s8 Guard_Flag[2];
extern u16 Lever_Squat[2];
extern u16 M_Lv[2];
extern s8 Pierce_Menu[2];
extern s8 Counter_Attack[2];
extern s16 zuubun_base_x;
extern s8 Face_MV_Time;
extern s8 Before_Jump[2];
extern s8 Stop_Combo;
extern u8 Stock_Hit_Flag[2];
extern s8 Rolling_Flag[2];
extern u8 Continue_Coin[2];
extern s16 Cursor_Y[2];
extern s8 Last_Arts_PL;
extern s8 Moving_Plate[2];
extern s8 Naming_Cut[2];
extern s8 Moving_Plate_Counter[2];
extern s8 OK_Priority[2];
extern s8 Player_Color[2];
extern s8 PP_Priority[2][3];
extern u8 Stock_My_char[2];
extern s8 Stock_Player_Color[2];
extern s16 Insert_Y;
extern s8 Version_Type;
extern s8 BGM_Fade_Out_Flag;
extern s16 zoom_request_flag;
extern s16 zoom_request_level;
extern s16 Stock_Com_Color;
extern s8 Stock_Com_Arts;
extern s8 Stop_SG;
extern s16 Last_Selected_ID;
extern s16 Last_Called_SE;
extern s8 Round_Operator[2];
extern s8 another_bg[2];
extern s8 bg_test_flag;
extern s8 Last_Super_Arts[2];
extern s8 Last_My_char[2];
extern s8 Continue_Menu[2];
extern s8 Timer_Freeze;
extern s8 Rapid_No[2][4];
extern s16 Rapid_Index[2];
extern s8 Standing_Timer[2];
extern s8 Before_Look[2];
extern s16 Shell_Separate_Area[2][3];
extern s16 Attack_Counter[2];
extern s16 Last_Attack_Counter[2];
extern s8 Attack_Count_No0[2];
extern s16 Com_Color_Shot;
extern s8 Standing_Master_Timer[2];
extern s8 No_Death;
extern s8 Flash_MT[2];
extern s8 Squat_Timer[2];
extern s8 Squat_Master_Timer[2];
extern s8 Turn_Over[2];
extern s16 Distance_XX_Index[2];
extern u16 Resume_Lever[2][20];
extern s8 Turn_Over_Timer[2];
extern s8 Jump_Pass_Timer[2][4];
extern s8 sa_gauge_flash[2];
extern s8 Receive_Flag[2];
extern s8 Disposal_Again[2];
extern volatile s8 BGM_Fade_Level;
extern u8 Decided_My_char[2];
extern u16 EM_Course[2];
extern s8 Break_Com[2][13];
extern s8 Sel_Exit_Flag;
extern u16 Lever_Store[2][3];
extern s16 Return_CP_No[2];
extern s16 Return_CP_Index[2];
extern s16 Return_Pattern_Index[2];
extern s8 aiuchi_flag;
extern u8 paring_counter[2];
extern u8 paring_bonus_r[2];
extern u8 paring_ctr_vs[2][2];
extern u8 paring_ctr_ori[2];
extern u8 Type_of_Attack[2];
extern u16 Lever_LR[2];
extern s16 Last_Eftype[2];
extern u16 DENJIN_No[2];
extern u8 DENJIN_Term[2];
extern u16 SC_Personal_Time[2];
extern u8 Attack_Count_Buff[2][4];
extern u8 Attack_Count_Index[2];
extern s16 Guard_Counter[2];
extern u8 CC_Value[2];
extern u8 Continue_Coin2[2];
extern s16 kage_gfx_ofs[64];
extern s16 kage_gfx_cells[64];
extern u16 seraph_gfx_ofs[48];
extern s16 seraph_gfx_cells[48];
extern s16 Limit_Time;
extern u8 Weak_PL;
extern u8 Bullet_No[2];
extern u8 Bullet_Counter[2];
extern s8 ID_of_Face[2][2][5];
extern s16 Exit_Timer;
extern s8 Win_Record[2];
extern s16 BGM_No;
extern u16 BGM_Timer;
extern s8 Continue_Count[2];
extern s16 Last_VS_Index[2];
extern RANK_DATA Ranking_Data[12];   /* two rankings of 6 */
extern RANK_DATA Present_Data[2];
extern s16 Cont_No;
extern s16 Cont_Sub_No;
extern s16 Cont_Sub2_No;
extern s16 Cont_Sub3_No;
extern s16 Cont_Timer;
extern s16 SEL_PL_X;
extern s8 * Demo_Ptr[2];
extern s8 Config_Item_jp;
extern s8 Config_Exit_jp;
extern s8 Config_Move_jp;
extern s8 Config_Old_jp;
extern s8 Config_New_jp;
extern s8 Config_Org_jp;
extern s16 Config_Attr_jp;
extern s16 Config_Rep_Timer_jp[4];
extern s8 Config_Rep_Count_jp[4];
extern s8 Config_Item_en;
extern s8 Config_Exit_en;
extern s8 Config_Move_en;
extern s8 Config_Old_en;
extern s8 Config_New_en;
extern s8 Config_Org_en;
extern s16 Config_Attr_en;
extern s16 Config_Rep_Timer_en[4];
extern s8 Config_Rep_Count_en[4];
/* debug and test features left in the source, switched off */
#define DEBUG_DISP 0 /* extra debug and test screen output */
#define DEBUG_EDIT 0 /* extra debug editor state changes */
#define DEBUG_SLOW 0 /* slow motion: an extra frame of sleep per game frame */

extern s8 Debug_R_No;
extern s8 Debug_Select_No;
extern s8 Debug_Menu_No;
extern s8 Debug_Tool_No;
extern s16 Debug_Rep_Timer[21];
extern s8 Debug_Rep_Count[21];
extern s16 Debug_RGB[4];
extern s8 Debug_RL_Flag[2];
extern s8 Debug_CG_Flip[2];
extern s8 Debug_Flip_Work[2];
extern s8 Debug_Flip_Mask[2];
extern s8 Debug_Play_Flag;
extern s8 Debug_Snap_Disp;
extern s8 Debug_Dec_Disp;
extern s16 Debug_Rec_Frame;
extern s16 Debug_Rec_Count;
extern s8 Debug_PL_id;
extern s8 Debug_Command;
extern s8 Debug_Edit_Sub;
extern s8 Debug_Hit_Sub;
extern s8 Debug_Box_Edit;
extern s8 dbg_copy_done;
extern s8 dbg_snap_req;
extern s8 dbg_hud_mode;
extern s8 dbg_rec_menu;
extern s8 dbg_save_mode;
extern s8 dbg_look_mode;
extern s8 dbg_kakusyuku_mode;
extern s8 dbg_rec_exist;
extern s8 dbg_cmd_panel;
extern s8 dbg_col_ix[2];
extern s16 dbg_judge_eff_ix;
extern s16 dbg_zoom_x;
extern s16 dbg_zoom_y;
extern s16 dbg_old_cgd_type;
extern s16 dbg_hud_x;
extern s16 dbg_copy_pat;
extern s16 dbg_copy_char;
extern u8 dbg_copy_char_tail[2];
extern u16 dbg_p1sw_0;
extern u16 dbg_p1sw_1;
extern u16 dbg_p2sw_0;
extern u16 dbg_p2sw_1;
extern s16 dbg_dipsw_0;
extern s16 dbg_dipsw_1;
extern s16 * dbg_edit_box;
extern s16 dbg_col_char;
extern PLW * dbg_pl;
extern DBG_SLOT * dbg_slot;
extern s16 dbg_slot_w[2][9];
extern SNAPSHOT* dbg_snap_ptr;
extern SNAPSHOT dbg_snap_w[][128];
extern WORK_Other * dbg_ghost_ewk[2][3];
extern PATTERN_BUF dbg_look_buf;
extern u8 dbg_look_buf_tail[20];
extern PATTERN_BUF dbg_copy_buf;
extern u8 dbg_copy_buf_tail[20];
extern PATTERN_BUF dbg_edit_buf;
extern u8 dbg_edit_buf_tail[20];
extern WORK_Other_JUDGE * dbg_judge_ewk;
extern u8 dbg_look_judge[];
extern HITA_BOX dbg_look_body[];
extern u8 dbg_look_caught[];
extern HITA_BOX dbg_look_attack[];
extern u8 dbg_look_hosei[];
extern u8 dbg_edit_judge[];
extern u8 dbg_edit_body[];
extern u8 dbg_edit_caught[];
extern u8 dbg_edit_attack[];
extern u8 dbg_edit_hosei[];
extern u8 dbg_copy_judge[];
extern u8 dbg_copy_body[];
extern u8 dbg_copy_caught[];
extern u8 dbg_copy_attack[];
extern u8 dbg_copy_hosei[];
extern T_PL_LVR t_pl_lvr[2];
extern WAZA_WORK waza_work[2][48];    /* 48 entries */
extern u16 sw_work;
extern s16 * cmd_tbl_ptr;
extern s16 waza_type[2];
extern T_PL_LVR * chk_pl;
extern WAZA_WORK * waza_ptr;
extern WORK_CP wcp[2];
extern s16 cmd_id;
extern PLW * cmd_pl;
extern s16 eff_hit_flag[11];
extern AKE_SCRL ake_scrl_w[3];
extern BG bg_w;
extern s16 stage8_base_y;          /* provisional name */
extern s16 scr_cg_c_no;
extern s16 ake_cg_c_no;
extern BGW * bgw_ptr;
extern u16 suzi_line_buf[];
extern MVXY bg_mvxy;
extern s16 bg_stop;
extern s16 base_y_pos;
extern s16 bg_ofs_work[3];
extern s16 bg_zoom_x_pos;
extern s16 bg_sp_work;
extern s16 bg_land_flag;
extern s8 demo_car_flag[2];
extern s16 bg_etc_flag;
extern s16 bg_stop2;
extern s16 chase_x;
extern s16 chase_y;
extern s16 chase_time_x;
extern s16 chase_time_y;
extern s8 seraph_flag;
extern s8 aku_flag;
extern s8 bg_select_no;
extern s8 bg_app;
extern s16 Name_00[2];
extern NAME_WK name_wk[2];
extern NAME_WK * name_ptr;
extern SC_NAME_WK sc_name_wk[2][4];
extern SC_NAME_WK * nsc_ptr;
extern RANK_NAME_W rank_name_w[2];
extern s16 Name_Input_f;
extern s16 naming_cnt;   /* one counter */
extern s16 n_disp_flag;
extern s16 Appear_end;
extern s16 appear_work[2];
extern s8 Appear_flag[2];
extern s8 Appear_free;
extern s8 Appear_hv[2];
extern s16 app_counter[2];
extern s16 win_rno[2];
extern s16 a_rno;
extern s16 win_free[2];
extern s16 lose_rno[3];
extern s16 lose_free[2];
extern OP_W op_w;
extern s16 op_obj_disp;
extern END_W end_w;

/* end_w.r_no_1: a character's ending script (end_0x000 in end_N.c) */
#define END1_INIT       0       /* set up the character's ending */
#define END1_SCENES     1       /* each scene for its timer; after the last, the staff roll */
#define END1_DONE       2       /* hold the last screen */

extern s8 end_etc_flag;
extern s8 ending_all_end;
extern s8 end_fade_flag;
extern s8 end_no_cut;
extern s16 end_fade_timer;
extern s8 end_name_cut;
extern s8 end_staff_flag;
extern u8 end_cont_coin;
extern SELPL card_pl_w[2];
extern s16 card_msg_cnt;
extern s16 cd_ready_flag;
extern s16 cd_spin_timer;
extern s16 roll_rate2;
extern s16 roll_stop;
extern u8 col_trans_req_tbl[256];
extern s16 col_trans_req_cnt0;
extern s16 col_trans_req_cnt1;
extern s16 col_trans_req_cnt2;
extern s32 col_trans_result;
extern u16 * sc_trans_dst;
extern u8 * sc_bak_ptr;
extern u8 * sc_trans_src;
extern u8 sc_trans_src_tail[6];
extern u16 sc_trans_word;
extern s16 vital_col_ix;
extern s16 vital_dot_pos;
extern s16 vital_red_ofs;
extern s16 vital_yel_ofs;
extern u16 gauge_stop_flag[2];
extern u16 gauge_stop_flag[2];
extern VITAL_BAR vit_bar[2];
extern ROUND_TIMER round_timer;
extern COUNT_WORK count_work;
extern s8 Old_Stop_SG;
extern s8 Exec_Wipe_F;
extern s8 time_clear[2];
extern s16 spg_number;
extern s16 spg_work;
extern s16 spg_offset;
extern s8 time_num;
extern s8 time_timer;
extern s8 time_flag;
extern s16 col;
extern SPG_DAT spg_dat[2];
extern s16 win_mark_rno[2];
extern s16 win_mark_timer[2];
extern s16 win_mark_phase[2];
extern s16 win_mark_num[2];
extern s16 win_mark_pos[2];
extern s8 fade_layer_num;
extern s16 fade_cont_rno;
extern s8 fade_end_timer;
extern FADE_LAYER fade_layer[];
extern s16 stn_number;
extern s16 stn_work;
extern s16 stn_offset;
extern STN_DAT sdat[2];
extern E14_WORK eff14_work[8];
extern s16 rf_b2_flag;
extern s16 b2_curr_no;
extern WORK_Other * oya_adrs;
extern s16 test_pl_no;
extern s16 test_mes_no;
extern s16 test_in;
extern WORK_Other * oya_p;
extern s16 efff9_suicide;
extern s32 * efff9_txt_no_adrs;
extern u16 * efff9_txt_scene_adrs;
extern s16 efff9_PL_NO;
extern s16 efff9_txt_point;
extern s16 efff9_message;
extern s16 keep_mes_no;
extern s16 efff9_mes_no;
extern s16 pcon_rno[4];

/* pcon_rno[0]: the player control phase (player_main_process, player_bonus_process) */
#define PCON_INIT       0       /* plcnt_init: the round start (appear_initalize) */
#define PCON_MOVE       1       /* plcnt_move: the fight */
#define PCON_DIE        2       /* plcnt_die: the round is decided (settle_process) */

/* pcon_rno[1] under PCON_INIT: the appear_initalize step */
#define APP_SETUP       0       /* set up the players */
#define APP_WAIT_READY  1       /* pli_1000: until both are ready, then PCON_MOVE */

/* pcon_rno[1] under PCON_DIE: how the round was decided */
#define SETTLE_KO       0       /* settle_type_00000: a KO */
#define SETTLE_DOUBLE_KO 1      /* settle_type_10000: a double KO */
#define SETTLE_TIME_OVER 2      /* settle_type_20000: time over */
#define SETTLE_JUDGE    3       /* settle_type_30000: the judges' decision (idle at pcon_rno[2] 0) */

extern s16 appear_type;

/* appear_type: how the players come on at a round start (appear_initalize, player_mv_1000) */
#define APPEAR_STAND    0       /* set up the players and stand them in place */
#define APPEAR_ENTRY    1       /* set up the players, then their appear pose */
#define APPEAR_ROUND    2       /* reset the players for a new round, then the appear pose */
#define APPEAR_JUDGE    3       /* after the judges' decision: stand them apart again */

extern u8 round_slow_flag;
extern u8 pcon_dp_flag;
extern u8 pl_eff_disp_stop;
extern u8 pl_eff_disp_stop_tail[1];
extern u8 win_sp_flag;
extern char dead_voice_flag;
extern PLW plw[2];
extern SA_WORK super_arts[2];
extern PiyoriType piyori_type[2];
extern ComboType combo_type[2];
extern ComboType remake_power[2];
extern ZanzouTableEntry zanzou_table[2][48];
extern s16 bcdext;
extern SCRLPOS fm_pos[8];
extern SCRLPOS scrn_pos[5];
extern SCROLL_CTRL scrn_reg_w[4];
extern SPRPTR scrn_map_ptr[];
extern u16 scrn_line_prm[][2];
extern SCRN_MODE scrn_mode_prm[];
extern u16 Screen_Switch;
extern u16 Screen_Switch_Buffer;
extern u8 Screen_Switch_Req;
extern s16 iotest_out1_flag;
extern s16 iotest_out2_flag;
extern s32 iotest_hold_flag;
extern s16 iotest_save_flip;
extern u32 scsi_sense_key;
extern u32 scsi_sense_asc;
extern s8 scsi_sense_buf[];
extern SCSI_INQUIRY scsi_inquiry_data;
extern SCSI_CAPACITY scsi_capacity;
extern s8 scsi_toc_buf[];
extern s8 cd_sector_buf[];
extern s32 scsi_error;
extern s16 scsi_cdb_len;
extern COINCHUTE coin_chute1_w;
extern COINCHUTE coin_chute2_w;
extern COINCHUTE coin_chute3_w;
extern COINCHUTE coin_chute4_w;
/* lever and button words p1sw_0 .. p4sw_1 (_0 this frame, _1 the last; SHOT1-SHOT6 are LP-HK).
   sw_to_lvbt moves the kicks up one bit for the command words of cmd_data.h */
#define LEVER_UP        1
#define LEVER_DOWN      2
#define LEVER_LEFT      4
#define LEVER_RIGHT     8
#define BUTTON_LP       0x10
#define BUTTON_MP       0x20
#define BUTTON_HP       0x40
#define BUTTON_LK       0x80
#define BUTTON_MK       0x100
#define BUTTON_HK       0x200
#define BUTTON_SHOTS    0x3F0
#define BUTTON_START    0x1000
#define BUTTON_PUNCHES  0x70    /* LP, MP and HP */
#define LEVER_ALL       0xF     /* all four lever bits */
#define LEVER_LR        0xC     /* LEVER_LEFT and LEVER_RIGHT (also in a sw_lvbt word) */

/* WORK_CP lever_dir (sw_pick_up) and PLW jpdir: the lever relative to the facing */
#define LVDIR_NEUTRAL   0       /* neither forward nor back */
#define LVDIR_FORWARD   1       /* toward the way the player faces */
#define LVDIR_BACK      2       /* away from it */
extern u16 p1sw_0;
extern u16 p1sw_1;
extern u16 p2sw_0;
extern u16 p2sw_1;
extern u16 p3sw_0;
extern u16 p3sw_1;
extern u16 p4sw_0;
extern u16 p4sw_1;
extern u8 syssw_0;
extern u8 syssw_1;
extern u16 exsw_0;
extern u16 exsw_1;
extern u16 exsw_2;
extern u16 exsw_3;
extern u16 exsw_4;
extern u16 exsw_5;
extern u16 exsw_6;
extern u16 exsw_7;
extern u16 card_sw_0;
extern u16 card_sw_1;
extern u16 coin_sw_hist[];
extern u16 coin_sw_now[4];
extern s16 card_out_req;
extern u16 card_out_busy;
extern u8 card_out_busy_tail[128];
extern u32 book_coin_count;
extern u32 book_service_count;
extern u32 book_free_count;
extern u32 book_card_count;
extern u16 eep_dummy;
extern u16 eep_strobe_0;
extern u16 eep_strobe_1;
extern u16 eep_strobe_2;
extern u16 eeprom_test_save[64];
extern u8 eeprom_w[6];
extern u8 eeprom_saved_flip;
extern u8 eeprom_saved_flip_tail[25];
extern u8 eeprom_game_cfg[];
extern u8 eeprom_backup_cfg[];
extern s16 eeprom_retry;
extern SETTINGS Game_setting;
extern s8 cfg_top_cursor;
extern s8 cfg_coin;
extern s8 cfg_continue;
extern s8 cfg_chute;
extern s8 cfg_sound_mode;
extern s8 cfg_demo_sound;
extern s8 cfg_flip_old;
extern s8 cfg_free_play;
extern s8 cfg_coin_special;
extern s8 cfg_cont_forced;
extern s8 cfg_changed;
extern s8 cfg_voice;
extern s8 cfg_dispenser;
extern s8 cfg_win_point;
extern s8 cfg_win_point_vs;
extern s8 cfg_extra;
extern u8 cfg_extra_tail[1];
extern s8 cfg_cursor;
extern s8 cfg_cursor_old;
extern s8 cfg_coin_step;
extern s8 cfg_coin_sel;
extern s8 cfg_reserve;
extern s32 cfg_item_max;
extern s32 frame_ready;
extern SPRITE_ENTRY spr_entry_a[512];
extern SPRITE_ENTRY spr_entry_b[512];
extern SPRITE_ENTRY * spr_prio_a[0x80];
extern SPRITE_ENTRY * spr_prio_b[0x80];
extern u16 spr_cnt0_a;
extern u16 spr_cnt0_b;
extern u16 spr_cnt1_a;
extern u16 spr_cnt1_b;
extern u16 spr_cnt2_a;
extern u16 spr_cnt2_b;
extern u16 spr_cnt3_a;
extern u16 spr_cnt3_b;
extern u16 spr_cnt4_a;
extern u16 spr_cnt4_b;
extern u8 spr_bank;
extern s8 spr_list_ready;
extern s16 simm40_owner[];
extern s16 simm40_link[];
extern s16 simm40_used[];
extern s16 simm10_owner[];
extern s16 simm10_link[];
extern s16 simm10_used[];
/* a player's routine_no[0]: the plmain_lv_00 routine that runs it */
#define PLAYER_MV_INIT  0       /* player_mv_0000: set up the work */
#define PLAYER_MV_PLACE 1       /* player_mv_1000: place the player for the round */
#define PLAYER_MV_APPEAR 2      /* player_mv_2000: the appear pose */
#define PLAYER_MV_READY 3       /* player_mv_3000: ready, until both players are */
#define PLAYER_MV_FIGHT 4       /* player_mv_4000: the fight, by routine_no[1] */

/* a player's routine_no[1]: the plmain_lv_02 routine that runs it */
#define PLAYER_NORMAL   0       /* Player_normal */
#define PLAYER_DAMAGE   1       /* Player_damage: being hit */
#define PLAYER_CATCH    2       /* Player_catch: throwing */
#define PLAYER_CAUGHT   3       /* Player_caught: being thrown */
#define PLAYER_ATTACK   4       /* Player_attack: special moves and super arts (hissatsu_setup_union) */

/* a player's routine_no[2] under PLAYER_NORMAL: some of the plpnm_lv_00 routines */
#define NORMAL_APPEAR   0       /* Normal_00000: appear_player, the round-start entry */
#define NORMAL_STAND    1       /* Normal_01000: standing */
#define NORMAL_DASH     5       /* Normal_05000: the forward dash (normal_05, by player number) */
#define NORMAL_WIN      40      /* Normal_40000: win_player, the win pose */
#define NORMAL_LOSE     41      /* Normal_41000: lose_player */

/* a player's routine_no[2] under PLAYER_DAMAGE: some of the plpdm_lv_00 routines */
#define DAMAGE_AIR      14      /* Damage_14000 - 23000: the airborne hits (setup_butt_own_data) */
#define DAMAGE_AIR_END  24      /* the first routine past them */
#define DAMAGE_STUN     25      /* Damage_25000: stunned (kizetsu) */

/* a player's routine_no[2] under PLAYER_ATTACK: 16 and up index the fighter's plNN_exatt_table (each
   fighter's names are in cmd_data.c) */
#define ATTACK_SPECIAL  16      /* the first of them: plNN_exatt_table[routine_no[2] - ATTACK_SPECIAL] */

/* a player's routine_no[3]: the step within its move routine (the other steps are the move's own) */
#define RN3_START       0       /* the first step of a move routine: set up its animation */
#define RN3_DONE        9       /* a win or lose pose's script has ended */

#define POLY_LINE_MAX   0x155   /* polygon transfer queue entries per bank (poly_que.c) */
#define POLY_QUAD_MAX   32
#define POLY_ORDER_MAX  0x175
extern s32 poly_dma_state;
extern s16 poly_reserve0;
extern s16 poly_reserve1;
extern POLY_LINE poly_line_buf[2][POLY_LINE_MAX];
extern u32 poly_line_cnt[2];
extern u32 poly_line_rd[2];
extern POLYCMD poly_quad_buf[2][POLY_QUAD_MAX];
extern u32 poly_quad_cnt[2];
extern u32 poly_quad_rd[2];
extern u32 poly_order_pos[2];
extern u16 poly_order_kind[2][POLY_ORDER_MAX];
extern s32 poly_wr_bank;
extern s32 poly_rd_bank;
extern SPRITE_LIST sprite_list_w[4];
extern u16 num_font_code;
extern u32 palette_base;
extern const u16 * snd_attack_ptr;
extern const u16 * snd_decay_ptr;
extern const u16 * snd_lfo_rate_ptr;
extern const u16 * snd_pitch_lfo_ptr;
extern const u16 * snd_vol_lfo_ptr;
extern SNDSAMPLE * snd_sample_tbl;
extern u8 ** snd_bank_tbl;
extern u32 snd_fade_level;
extern u32 snd_fade_speed;
extern SNDVOICE bgm_voice[16];
extern SNDVOICE se_voice[16];
extern SNDRAMP se_pan_ramp[16];
extern s16 voice_state_init_pair_work;
extern u16 snd_wave_bias;
extern SOUND_CTRL snd_ctrl;
extern u16 bgm_tick_step;
extern u16 se_tick_step[16];
extern s8 sound_sample_submit_work4;
extern u8 bgm_master_vol;
extern u8 snd_master_vol;
extern u8 snd_stereo;
extern u8 gSeqStatus[16];
extern u16 sound_init_data[21];
extern u32 * snd_seq_data;
extern SNDRAMP se_ramp_req;
extern u16 snd_reg_save;
extern u16 snd_seq_max;
extern u8 bgm_status_save[16];
extern u8 sound_sample_submit_work7;
extern u8 sound_sample_submit_work7_tail[1];
extern u8 bgm_master_vol_init;
extern s16 cram_bank_old;
extern s16 cram_bank_now;

extern s8 Monitor_Flip;
extern s8 Continue_Flag;
extern s8 Demo_Sound;
extern s8 Language;
extern s8 Free_Play;
extern u8 Card_Dispenser;
extern s8 Voice_Type;
extern TM_STRING insert_coin_mes[9];
extern TMSCRIPT * sys_cfg_coin_scr_jp[];
extern TMSCRIPT * sys_cfg_chute_scr_jp[];
extern TMSCRIPT * sys_cfg_continue_scr_jp[];
extern TMSCRIPT * sys_cfg_monitor_scr_jp[];
extern TMSCRIPT * sys_cfg_demo_scr_jp[];
extern TMSCRIPT * sys_cfg_sound_scr_jp[];
extern s8 unused_flag_a;
extern s8 unused_flag_b;
extern s8 unused_flag_c;
extern SCROLL_WINDOW zoom_frame[2];
extern CharGfxSlot cg_slot_tbl[384];
extern CharGfxEntry * cg_data_list;
extern s8 Judge_Round_Flag;
extern s8 Reserve_Cut;
extern s8 Wipe_Count;
extern u8 Wipe_Limit;
extern u8 Wipe_Mode;
extern u8 Wipe_Kind;
extern s16 F_No3[2];
extern s8 Next_Demo;
extern s16 M_No0;
extern s16 M_No1;
extern s16 M_No2;
extern s16 M_No3;
extern s8 Demo_Time_Stop;
extern s8 win_slide_flag;   /* provisional name: set while the win screen slides (win_2.c, EFF58.c) */
extern s8 judge_disp_all;
extern s8 PB_Music_Off;
extern u16 pcon_timer;
extern u8 CC_Type;
extern s16 hitmark_gfx_ofs[2][224];
extern s16 hitmark_gfx_cells[224];
extern s16 WIN_X;
extern s8 bg_vbl_trans_flag;
extern BG_ADRS eff_bg_adrs[6];
extern u8 Allow_a_battle_f;
extern s16 DE_X[19];
extern s16 Face_No[2];
extern s8 Flash_Sign[2];
extern u16 Game_timer;
extern s8 Ignore_Entry[2];
extern s8 Operator_Status[2];
extern s16 Order[100];
extern s8 Order_Dir[100];
extern s8 Order_Timer[100];
extern u8 Round_num;
extern s8 Suicide;
extern s16 VS_Index[2];
extern u32 * char_add[14][3];   /* per stage and area */

extern void (*Name_Jmp_Tbl[8])();
extern void (*Name_Jmp_scs[8])();
extern s16 Counter_low;
extern u16 Fade_Number;
extern s8 Ranking_X;
extern s8 Demo_PL_Index[2];   /* [1] is only cleared (match_state_0_fight) */
extern s16 zoom_req_flag_old;
extern s16 scr_req_x;
extern s16 scr_req_y;
extern s16 Last_Pattern_Index[2];
extern s8 akebono_flag;
extern s16 op_end_flag;
extern TMSCRIPT config_top_scr_jp[];
extern s8 test_sw_lock;
extern s16 Random_ix16_ex_com;
extern s16 Random_ix32_ex_com;
extern SUZI_CALC suzi_calc_w[2];
extern s16 ls_cnt1;
extern s16 ls_rate1;

/* Records of these arrays are reached the way the game computes their offset: with shifts and adds,
 * cut to 16 bits. */
#define WCP(x) (*(WORK_CP*)((u8*)wcp + (s16)(((x) << 10) + ((x) << 2) + ((x) << 1))))
#define WAZA(x, j) (*(WAZA_WORK*)((u8*)waza_work + (s16)(((x) << 10) + ((x) << 8) + ((x) << 6)) + (s16)(((j) << 5) - ((j) << 2))))
#define PLAYER(x) (*(PLW*)((u8*)plw + (s16)(((x) << 10) + ((x) << 7) + ((x) << 4) + ((x) << 3))))
#define CMST(x, j) (*(CMST_WIN_R*)((u8*)cmst_buff + (u8)((x) * 112) + (s8)(((j) << 5) - ((j) << 2))))
#define SE_VOICE(x) (*(SNDVOICE*)((u8*)se_voice + (s16)((x) * sizeof(SNDVOICE))))
/* Record offsets computed per use: WCP_OFS(ofs, n) sets ofs to the offset of record n, WCP_AT(ofs)
   is the record, WCP_MUL(ofs, n) does both in one expression (one use per full expression). */
#define WCP_OFS(ofs, n) ((ofs) = (n), (ofs) *= (s16)sizeof(WORK_CP))
#define WCP_AT(ofs) (*(WORK_CP*)((u8*)wcp + (ofs)))
#define WCP_MUL(ofs, n) WCP_AT((WCP_OFS(ofs, n), (ofs)))
#define PL_CMD_NUM(x) ((const s16*)((const u8*)pl_cmd_num + (s16)((x) << 4)))
#define CMB_POS(mode, pl, k) (*(const s16*)((u8*)cmb_pos_tbl + (u8)(((mode) << 6) + ((mode) << 4) + ((mode) << 2)) + (s8)(((pl) << 5) + ((pl) << 3) + ((pl) << 1)) + (k) * 2))

#endif
