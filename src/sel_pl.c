/*
 * sel_pl.c  Player (character) select screen
 *
 * Select_Player is called each frame while the character select screen is up. Sel_PL_Control runs
 * the screen-wide sequence (Sel_PL_Cont_*: background, face panel and object setup), the face panel
 * mover, the plate sequence (Player_Select_Control and the PL_Sel_* steps, which slide the name,
 * face and super art plates in as each player decides) and the exit sequence (Check_Exit) that leads
 * on to the VS screen. Sel_PL then runs each player's own state machine (Sel_PL_1st..6th). Per
 * player: the lever moves the cursor over the player's 2 x 5 face grid (ID_of_Face), a button
 * confirms the character and colour, and Sel_Arts_Sub picks one of three super arts. Demo lever
 * data drives the screen in attract mode. Next_CPU is the screen's second entry, for the next
 * fight: the player's choice stands and the opponent is set up. Correct_Control_Time takes time off
 * the select timer after continues.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "bg_sub.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "Eff93.h"
#include "SYS_sub.h"
#include "end_sub_8.h"
#include "EFFECT.h"
#include "EFFD5.h"
#include "effa5.h"
#include "EFFA6.h"
#include "EFF98.h"
#include "Eff50.h"
#include "sys_test.h"
#include "sys_test_5.h"
#include "sc_trans.h"
#include "EFFD6.h"
#include "next_cpu.h"
#include "se_3.h"
#include "EFF42.h"
#include "EFF58.h"
#include "PLS02.h"
#include "Com_Pl.h"
#include "bg000.h"
#include "textsound.h"
#include "sel_pl.h"
#include "fighter.h"

/* Sel_Sub_No[1] in PL_Sel_2nd, both playing */
#define PS2_WAIT        0       /* until one or both have chosen a character */
#define PS2_PLATES      1       /* move both plates into order */

/* Sel_Sub_No[1] in PL_Sel_3rd */
#define PS3_START       0       /* both choosing super arts: order the plates, else finish */
#define PS3_CHALLENGER  1       /* until the challenger's character is chosen */
#define PS3_BOTH        2       /* until that and the champion's super art are chosen */
#define PS3_ARTS        3       /* (default) until the challenger's super art is chosen */

/* Face_No[1]: the face panel move (Move_Face_BG) */
#define FACE_MOVE_IDLE  0       /* until a move is requested */
#define FACE_MOVING     1       /* (default) until the move is done */

/* Select_Status[0]: who is playing; Select_Status[1]: who has chosen a super art (bits) */
#define SEL_1P          1       /* player 1 */
#define SEL_2P          2       /* player 2 */
#define SEL_BOTH        3       /* both players */

/* SP_No[pl][0]: a player's select routine (Sel_PL_Jmp_Tbl) */
#define SP_INIT         0       /* Sel_PL_1st: set up the cursor */
#define SP_WAIT         1       /* Sel_PL_2nd: until the select starts */
#define SP_CHAR         2       /* Sel_PL_3rd: choose a character */
#define SP_ARTS_WAIT    3       /* Sel_PL_4th: until the super art select opens */
#define SP_ARTS         4       /* Sel_PL_5th: choose a super art */
#define SP_DONE         5       /* Sel_PL_6th: done */

/* Face_No[0]: the face panel routine (Face_Tbl) */
#define FACE_DONE       3       /* Face_4th: the face panel is done */

/* declarations the headers do not give */
extern s16 Sel_Arts_Pos[2];
extern s8 Sel_Char_Shot[2];
extern s16 sel_plate_state[2][3];
extern s16 Plate_Step[2];       /* provisional name: each player's plate step in PL_Sel_2nd's second half */
extern s16 Sel_First_PL;        /* provisional name: the player whose character was decided first */
extern s16 Sel_Second_PL;       /* provisional name: the other player */
extern s16 Exit_Wait;
extern s8 vs_object_count;      /* provisional name: set to 4 as the VS plates come on */
extern s16 END_OF_B0;
extern const s8 EM_Cursor_Data[][2];   /* provisional name: the face grid cell of each CPU opponent */
#pragma inline(Setup_BG)
s32 effect_38_init(s16 PL_id, s16 Wait);
s32 effect_39_init(s16 PL_id, s16 Wait);
#include "EFF43.h"
#include "Eff52.h"
#include "EffD8.h"
#include "EffE0.h"
s32 effect_D7_init2();
s32 effect_D7_init(s16 pl_id, s16 plate_id, s16 pos_id, s16 time, s16 type);
s32 effect_E4_init(s16 PL_id, s16 Arts, s16 Type);
s32 effect_B0_init(void);
#include "Eff59.h"
void Setup_Next_EM(void);
void Init_EM_Course(void);
s32 Sel_Arts_Sub_Check();
void Sel_Plate_Order_Step();
s32 Check_First_PL_Decided(void);
void Setup_Yun_Yang_Face();
void Yun_Yang_Face_Other();
void Yun_Yang_Select();
extern u8 Straight_Lose_Count;

s16 Select_Player(void) {
    SEL_PL_X = 0;
    if (Break_Into) {
        return 0;
    }
    Sel_PL_Control();
    ID = 0;
    Sel_PL();
    ID = 1;
    Sel_PL();
    Time_Over = 0;
    return SEL_PL_X;
}



void Sel_PL_Control(void) {
    void (*cont_tbl[4])() = { Sel_PL_Cont_1st, Sel_PL_Cont_2nd, Sel_PL_Cont_3rd, Sel_PL_Cont_4th };
    Setup_Select_Status();
    cont_tbl[S_No]();
    Face_Control();
    Player_Select_Control();
    Check_Exit();
}



void Sel_PL_Cont_1st(void) {
    s16 xx;
    if (Demo_Flag) {
        tilemap_fill_all(0, 32);
    } else {
        tilemap_print_string_attr(DE_X[0] + 14, Text_Page_Y + 23, 18, "                    ");
    }
    S_No++;
    Suicide = 0;
    Face_No[0] = 0;
    Face_No[1] = FACE_MOVE_IDLE;
    Sel_Sub_No[0] = 0;
    Sel_Sub_No[1] = 0;
    Exit_No = 0;
    Fade_Flag = 0;
    for (xx = 0; xx < 4; xx++) {
        SP_No[0][xx] = 0;
        SP_No[1][xx] = 0;
    }
    for (xx = 0; xx < 3; xx++) {
        sel_plate_state[0][xx] = 52;
        sel_plate_state[1][xx] = 52;
    }
    System_all_clear_Wait();
    effect_work_quick_init();
    Setup_BG_General();
    Setup_BG_Layer2();
    Setup_BG_Layer3();
    Setup_EFF69();
    Setup_Cursor_Y();
    Time_Stop = 1;
    Select_Timer = 32;
    Unit_Of_Timer = 40;
    Setup_Face_ID();
    Setup_Yun_Yang_Face(0);
    Setup_Yun_Yang_Face(1);
    Setup_Face_Sub();
    effect_A5_entry();
    effect_42_init(0);
    effect_42_init(1);
    Appear_Cursor = 0;
    Face_MV_Request = 0;
    Face_Status = 0;
    Face_Move = 0;
    Time_Over = 0;
    Move_Super_Arts[0] = 0;
    Move_Super_Arts[1] = 0;
    Flash_Complete[0] = 0;
    Flash_Complete[1] = 0;
    Sel_Char_Shot[0] = 1;
    Sel_Char_Shot[1] = 1;
    Sel_Arts_Pos[0] = 32;
    Sel_Arts_Pos[1] = 95;
}



void Sel_PL_Cont_2nd(void) {
    if (--Cover_Timer == 0) {
        S_No++;
        if (G_No1 == G1_SELECT) {
            Request_E_No = 1;
        }
        Clear_Flash_No();
        Face_MV_Request = 1;
        Face_MV_Time = 10;
        commit_name_entry_row_both_players(Text_Page_Y);
        Scrn_Move_Set(4, 0, 0x100);
        Switch_Screen_Init(0, 1);
    }
}



void Sel_PL_Cont_3rd(void) {
    if (Switch_Screen_Revival()) {
        S_No++;
        Forbid_Break = 0;
        if (G_No1 == G1_SELECT || !Demo_Flag) {
            BGM_Request(2);
            if (E_Number[0][0] != ENTRY_NAME && E_Number[1][0] != ENTRY_NAME) {
                Ranking_00_6th(0);
            }
        }
    }
}



void Sel_PL_Cont_4th(void) {}



/* Sets up the BG layers of the select screen. */
void Initialize_BG(void) {
    Setup_BG_General();
    Setup_BG_Layer2();
    Setup_BG_Layer3();
}



void Setup_EFF69(void) {
    s16 xx;
    for (xx = 0; xx < 6; xx++) {
        Order[xx] = 0;
        effect_D6_init(xx);
    }
}



/* The face plates of one player's grid: player 1's while player 1 is still choosing, else player 2's. */
void Setup_Face_Sub(void) {
    s16 i;
    s16 j;
    s8 ix;
    if (plw[0].wu.operator && Sel_PL_Complete[0] == 0) {
        ix = 0;
    } else {
        ix = 1;
    }
    effect_D5_init2();
    for (i = 0; i <= 1; i++) {
        for (j = 0; j < 5; j++) {
            effect_D5_init(ID_of_Face[ix][i][j]);
        }
    }
}



void Sel_PL(void) {
    void (*Sel_PL_Jmp_Tbl[6])() = { Sel_PL_1st, Sel_PL_2nd, Sel_PL_3rd, Sel_PL_4th, Sel_PL_5th, Sel_PL_6th };
    if (plw[ID].wu.operator != 0) {
        Sel_PL_Jmp_Tbl[SP_No[ID][0]]();
    }
}



void Sel_PL_1st(void) {
    if (Exit_No) {
        return;
    }
    SP_No[ID][0]++;
    Stop_Cursor[ID] = 1;
    Moving_Plate[ID] = 0;
    Moving_Plate_Counter[ID] = 0;
    Select_Start[ID] = 2;
    Select_Arts[ID] = -1;
    effect_38_init(ID, 30);
    effect_39_init(ID, 30);
    if (ID == 1) {
        effect_D8_entry(1, 2);
    } else {
        effect_D8_entry(0, 0);
        effect_D8_entry(0, 1);
    }
    if (Sel_PL_Complete[ID]) {
        Select_Start[ID] = 3;
        return;
    }
    Arts_Y[ID] = Super_Arts[ID] = Last_Super_Arts[ID];
}



void Sel_PL_2nd(void) {
    if (Select_Start[ID]) {
        return;
    }
    SP_No[ID][0]++;
    Stop_Cursor[ID] = 0;
    if (Sel_Char_Shot[0]--) {
        Sound_SE(158);
    }
    if (Demo_Flag == 0) {
        Demo_Ptr[ID] = (s8*)Demo_Lever_Data[Select_Demo_Index];
    }
}



void Sel_PL_3rd(void) {
    if (Stop_Cursor[ID] != 0 || (u8)Face_Move != 0) {
        return;
    }
    if (Demo_Flag == 0) {
        if (ID) {
            Sel_PL_Sub(1, *Demo_Ptr[1]);
        } else {
            Sel_PL_Sub(0, *Demo_Ptr[0]);
        }
        Demo_Ptr[ID]++;
    } else if (ID) {
        Sel_PL_Sub(1, ~p2sw_1 & p2sw_0);
    } else {
        Sel_PL_Sub(0, ~p1sw_1 & p1sw_0);
    }
    if (Sel_PL_Complete[ID] >= 0) {
        return;
    }
    SP_No[ID][0]++;
    Stop_Cursor[ID] = 1;
    paring_ctr_vs[0][ID] = 0;
    paring_ctr_vs[1][ID] = 0;
}



void Sel_PL_4th(void) {
    if (!Select_Arts[ID]) {
        SP_No[ID][0]++;
        Stop_Cursor[ID] = 0;
        Arts_Cursor_No[ID] = 0;
        Arts_Cursor_Timer[ID] = 0;
        if (Sel_Char_Shot[1]--) {
            Sound_SE(159);
        }
    }
}



void Sel_PL_5th(void) {
    if (Stop_Cursor[ID] != 0 || (u8)Face_Move != 0) {
        return;
    }
    if (Demo_Flag == 0) {
        if (ID) {
            Sel_Arts_Sub(1, *Demo_Ptr[1], 0);
        } else {
            Sel_Arts_Sub(0, *Demo_Ptr[0], 0);
        }
        Demo_Ptr[ID]++;
    } else if (ID) {
        Sel_Arts_Sub(1, ~p2sw_1 & p2sw_0, p2sw_0);
    } else {
        Sel_Arts_Sub(0, ~p1sw_1 & p1sw_0, p1sw_0);
    }
    if (Sel_Arts_Complete[ID]) {
        SP_No[ID][0]++;
    }
}



void Sel_PL_6th(void) {}



/* The face grid is 2 rows of 5; the lever wraps around in both directions. */
void Sel_PL_Sub(PL_id, sw)
s16 PL_id;
u16 sw;
{
    s16 move;
    if (Sel_PL_Complete[PL_id] != 0) {
        return;
    }
    if (Time_Over != 0) {
        sw = BUTTON_LP;
    }
    if (sw == 0) {
        return;
    }
    move = 0;
    if (sw & LEVER_RIGHT) {
        move = 1;
        if (++Cursor_X[PL_id] >= 5) {
            Cursor_X[PL_id] = 0;
        }
    }
    if (sw & LEVER_LEFT) {
        move = 1;
        if (--Cursor_X[PL_id] < 0) {
            Cursor_X[PL_id] = 4;
        }
    }
    if (sw & LEVER_UP) {
        move = 1;
        if (++Cursor_Y[PL_id] >= 2) {
            Cursor_Y[PL_id] = 0;
        }
    }
    if (sw & LEVER_DOWN) {
        move = 1;
        if (--Cursor_Y[PL_id] < 0) {
            Cursor_Y[PL_id] = 1;
        }
    }
    if (move) {
        Sound_SE(ID + 96);
    }
    if (sw & BUTTON_SHOTS) {
        Sel_PL_Complete[PL_id] = 1;
        My_char[PL_id] = ID_of_Face[PL_id][Cursor_Y[PL_id]][Cursor_X[PL_id]];
        Yun_Yang_Select(PL_id, sw);
        if (Last_My_char[PL_id] != My_char[PL_id]) {
            Arts_Y[ID] = Super_Arts[ID] = Last_Super_Arts[ID] = 0;
        }
        Last_My_char[PL_id] = My_char[PL_id];
        Yun_Yang_Face_Other(PL_id);
        Last_Selected_ID = PL_id;
        effect_58_init(6, 20, My_char[PL_id] + PL_id * 16 + 192);
        Sound_SE(ID + 98);
        Setup_PL_Color(PL_id, sw);
        Correct_Control_Time(PL_id);
    }
}



void Setup_PL_Color(PL_id, sw)
s16 PL_id;
u16 sw;
{
    s8 id_0;
    s8 id_1;
    if (plw[PL_id ^ 1].wu.operator == 0) {
        id_0 = -1;
        id_1 = 1;
    } else {
        id_0 = My_char[PL_id];
        id_1 = My_char[PL_id * 1 ^ 1U];
    }
    if (Sel_PL_Complete[PL_id ^ 1] == 0) {
        id_0 = 127;
    }
    switch (sw) {
    case BUTTON_LP:
        if (Player_Color[PL_id ^ 1] == 0 && id_0 == id_1) {
            Player_Color[PL_id] = 3;
        } else {
            Player_Color[PL_id] = 0;
        }
        break;
    case BUTTON_MP:
        if (Player_Color[PL_id ^ 1] == 1 && id_0 == id_1) {
            Player_Color[PL_id] = 4;
        } else {
            Player_Color[PL_id] = 1;
        }
        break;
    case BUTTON_HP:
        if (Player_Color[PL_id ^ 1] == 2 && id_0 == id_1) {
            Player_Color[PL_id] = 5;
        } else {
            Player_Color[PL_id] = 2;
        }
        break;
    case BUTTON_LK:
        if (Player_Color[PL_id ^ 1] == 3 && id_0 == id_1) {
            Player_Color[PL_id] = 0;
        } else if (My_char[PL_id] == PL_YUN || My_char[PL_id] == PL_YANG) {
            Player_Color[PL_id] = 0;
        } else {
            Player_Color[PL_id] = 3;
        }
        break;
    case BUTTON_MK:
        if (Player_Color[PL_id ^ 1] == 4 && id_0 == id_1) {
            Player_Color[PL_id] = 1;
        } else if (My_char[PL_id] == PL_YUN || My_char[PL_id] == PL_YANG) {
            Player_Color[PL_id] = 1;
        } else {
            Player_Color[PL_id] = 4;
        }
        break;
    default:
        if (Player_Color[PL_id ^ 1] == 5 && id_0 == id_1) {
            Player_Color[PL_id] = 2;
        } else if (My_char[PL_id] == PL_YUN || My_char[PL_id] == PL_YANG) {
            Player_Color[PL_id] = 2;
        } else {
            Player_Color[PL_id] = 5;
        }
        break;
    }
}



/* One player's super art select for the frame: up and down move between the three arts, and a button picks
   one. */
void Sel_Arts_Sub(PL_id, sw, sw_0)
s16 PL_id;
u16 sw;
u16 sw_0;
{
    if (Sel_Arts_Complete[PL_id]) {
        return;
    }
    if (Moving_Plate_Counter[PL_id] != 0) {
        return;
    }
    if (Time_Over != 0) {
        sw = BUTTON_LP;
    }
    if (Sel_Arts_Sub_Check(PL_id, sw, sw_0)) {
        return;
    }
    switch (sw) {
    case 0:
        return;
    case LEVER_DOWN:
        Sound_SE(ID + 96);
        Moving_Plate[PL_id] = 2;
        Moving_Plate_Counter[PL_id] = 18;
        OK_Priority[PL_id] = 0;
        if (++Arts_Y[PL_id] > 2) {
            Arts_Y[PL_id] = 0;
        }
        break;
    case LEVER_UP:
        Sound_SE(ID + 96);
        Moving_Plate[PL_id] = 1;
        Moving_Plate_Counter[PL_id] = 18;
        OK_Priority[PL_id] = 0;
        if (--Arts_Y[PL_id] < 0) {
            Arts_Y[PL_id] = 2;
        }
        break;
    }
    if (sw & 0x7F0) {
        Stop_Cursor[ID] = 1;
        Slide_Type = PL_id;
        Sel_Arts_Complete[PL_id] = 1;
        *(s8*)&Last_Super_Arts[PL_id] = *(s8*)&Super_Arts[PL_id] = Arts_Y[PL_id];
        Sound_SE(ID + 98);
    }
}



/* provisional name: a check Sel_Arts_Sub makes before reading the lever; it always says no */
s32 Sel_Arts_Sub_Check(PL_id, sw, sw_0)
s16 PL_id;
u16 sw;
u16 sw_0;
{
    return 0;
}



/* provisional names: four routines nothing calls */
s32 Sel_PL_Dummy_1(void) {
    return 0;
}



s32 Sel_PL_Dummy_2(void) {
    return 0;
}



s32 Sel_PL_Dummy_3(void) {
    return 0;
}



s32 Sel_PL_Dummy_4(void) {
    for (;;) {
        return 0;
    }
}



void Face_Control(void) {
    void (*Face_Tbl[4])() = { Face_1st, Face_2nd, Face_3rd, Face_4th };
    Face_Tbl[Face_No[0]]();
    Move_Face_BG();
}



void Face_1st(void) {
    switch (Select_Status[1]) {
    case SEL_1P:
    case SEL_2P:
        if (Sel_Arts_Complete[Select_Status[1] - 1] < 0) {
            Face_MV_Request = 2;
            Face_MV_Time = 5;
            Face_No[0]++;
        }
        break;
    default:
        if (Sel_Arts_Complete[0] < 0 && Sel_Arts_Complete[1] < 0) {
            Face_MV_Request = 2;
            Face_MV_Time = 5;
            Face_No[0] = FACE_DONE;
        }
        break;
    }
}



void Face_2nd(void) {
    if (Move_Super_Arts[0] == 0 && Move_Super_Arts[1] == 0 && Select_Status[1] == SEL_BOTH && Face_Move == 0) {
        Face_MV_Request = 1;
        Face_MV_Time = 20;
        Face_No[0]++;
    }
}



void Face_3rd(void) {
    if (Sel_PL_Complete[0] < 0 && Sel_PL_Complete[1] < 0) {
        Face_MV_Request = 2;
        Face_MV_Time = 5;
        Face_No[0] = FACE_DONE;
    }
}



void Face_4th(void) {}



void Move_Face_BG(void) {
    switch (Face_No[1]) {
    case FACE_MOVE_IDLE:
        if (Face_MV_Request == 0) {
            break;
        }
        Face_Move = Face_MV_Request;
        effect_93_init(Face_Move, Face_MV_Time);
        Face_No[1]++;
        break;
    default:
        if (Face_MV_Request = Face_Move) {
            break;
        }
        Face_No[1] = FACE_MOVE_IDLE;
        break;
    }
}



void Player_Select_Control(void) {
    void (*Obj_Tbl[5])() = { PL_Sel_Begin, PL_Sel_2nd, PL_Sel_3rd, PL_Sel_4th, PL_Sel_5th };
    Obj_Tbl[Sel_Sub_No[0]]();
}



/* provisional name */
void PL_Sel_Begin(void) {
    Sel_Sub_No[0]++;
    Order[0] = 1;
    Order_Timer[0] = 30;
}



void PL_Sel_2nd(void) {
    switch (Select_Status[1]) {
    case SEL_1P:
    case SEL_2P:
        if (Sel_PL_Complete[Select_Status[1] - 1] < 0) {
            Order[0] = 3;
            Order_Timer[0] = 1;
            Order[3] = 2;
            Order_Timer[3] = 1;
            if (Select_Status[1] == SEL_1P) {
                Order_Dir[0] = 8;
                Order_Dir[3] = 8;
            } else {
                Order_Dir[0] = 4;
                Order_Dir[3] = 4;
            }
            Sel_Sub_No[0]++;
            Sel_Sub_No[1] = PS3_START;
            Plate_Step[0] = 0;
            Plate_Step[1] = 0;
            Setup_Plates(Select_Status[1] - 1);
            if (Select_Status[0] == SEL_BOTH) {
                Move_Super_Arts[Champion] = 1;
                effect_D7_init(Champion, Super_Arts[Champion], 0, 30, 0);
                effect_D7_init(Champion, Super_Arts[Champion], 0, 30, 1);
                OK_Priority[Champion] = 0;
            }
        }
        break;
    default:
        switch (Sel_Sub_No[1]) {
        case PS2_WAIT:
            if ((Sel_PL_Complete[0] < 0 && Sel_PL_Complete[1] != 0) || (Sel_PL_Complete[1] < 0 && Sel_PL_Complete[0] != 0)) {
                Order[0] = 3;
                Order_Timer[0] = 1;
                Order[3] = 2;
                Order_Timer[3] = 1;
                if (Champion == 0) {
                    Order_Dir[0] = 8;
                    Order_Dir[3] = 8;
                } else {
                    Order_Dir[0] = 4;
                    Order_Dir[3] = 4;
                }
                Sel_Sub_No[0] = 3;
                Setup_Plates(0);
                Setup_Plates(1);
            } else if (Check_First_PL_Decided()) {
                Order[0] = 4;
                Order[Sel_First_PL + 4] = 2;
                Order_Timer[0] = 1;
                Order_Timer[Sel_First_PL + 4] = 1;
                if (Sel_Second_PL == 0) {
                    Order_Dir[0] = 4;
                    Order_Dir[Sel_First_PL + 4] = 4;
                } else {
                    Order_Dir[0] = 8;
                    Order_Dir[Sel_First_PL + 4] = 8;
                }
                Setup_Plates(Sel_First_PL);
                Sel_Sub_No[1]++;
            }
            break;
        case PS2_PLATES:
            Sel_Plate_Order_Step(Sel_Second_PL);
            Sel_Plate_Order_Step(Sel_First_PL);
            if (Plate_Step[0] == 99 && Plate_Step[1] == 99) {
                Sel_Sub_No[0] = 4;
            }
            break;
        }
        break;
    }
}



/* provisional name: each player's plates are ordered off once their character, then their super art, is decided */
void Sel_Plate_Order_Step(s16 pl) {
    switch (Plate_Step[pl]) {
    case 0:
        if (Sel_PL_Complete[pl] < 0) {
            Order[pl + 1] = 3;
            Order[pl + 4] = 2;
            Order_Timer[pl + 1] = 1;
            Order_Timer[pl + 4] = 1;
            if (pl == 0) {
                Order_Dir[1] = 4;
                Order_Dir[pl + 4] = 8;
            } else {
                Order_Dir[2] = 8;
                Order_Dir[pl + 4] = 4;
            }
            Setup_Plates(pl);
            Plate_Step[pl]++;
        }
        break;
    case 1:
        if (Sel_Arts_Complete[pl] < 0) {
            Order[pl + 4] = 3;
            Order_Timer[pl + 4] = 1;
            if (pl == 0) {
                Order_Dir[pl + 4] = 4;
            } else {
                Order_Dir[pl + 4] = 8;
            }
            Plate_Step[pl] = 99;
        }
        break;
    }
}



/* provisional name: the first player to decide sets Sel_First_PL / Sel_Second_PL and the plate steps */
s32 Check_First_PL_Decided(void) {
    if (Sel_PL_Complete[0] < 0) {
        Sel_First_PL = 0;
        Sel_Second_PL = 1;
        Plate_Step[0] = 1;
        Plate_Step[1] = 0;
        return 1;
    }
    if (Sel_PL_Complete[1] < 0) {
        Sel_First_PL = 1;
        Sel_Second_PL = 0;
        Plate_Step[1] = 1;
        Plate_Step[0] = 0;
        return 1;
    }
    return 0;
}



/* By the super art chosen: the row (0 to 2) each of the three plates takes. */
const s16 Arts_Y_Data[3][3] = {
    { 0, 1, 2 }, { 2, 0, 1 }, { 1, 2, 0 },
};


/* provisional name */
const s16 Setup_Aborigine_time[3][3] = {
    { 30, 25, 20 }, { 20, 30, 25 }, { 25, 20, 30 },
};


void Setup_Plates(PL_id)
s8 PL_id;
{
    Move_Super_Arts[PL_id] = 3;
    Select_Arts[PL_id] = 6;
    effect_D7_init(PL_id, 0, Arts_Y_Data[Super_Arts[PL_id]][0], Setup_Aborigine_time[Super_Arts[PL_id]][0], 0);
    effect_D7_init(PL_id, 0, Arts_Y_Data[Super_Arts[PL_id]][0], Setup_Aborigine_time[Super_Arts[PL_id]][0], 1);
    effect_D7_init(PL_id, 1, Arts_Y_Data[Super_Arts[PL_id]][1], Setup_Aborigine_time[Super_Arts[PL_id]][1], 0);
    effect_D7_init(PL_id, 1, Arts_Y_Data[Super_Arts[PL_id]][1], Setup_Aborigine_time[Super_Arts[PL_id]][1], 1);
    effect_D7_init(PL_id, 2, Arts_Y_Data[Super_Arts[PL_id]][2], Setup_Aborigine_time[Super_Arts[PL_id]][2], 0);
    effect_D7_init(PL_id, 2, Arts_Y_Data[Super_Arts[PL_id]][2], Setup_Aborigine_time[Super_Arts[PL_id]][2], 1);
}



void PL_Sel_3rd(void) {
    switch (Sel_Sub_No[1]) {
    case PS3_START:
        if (Select_Status[1] == SEL_BOTH) {
            Order[3] = 4;
            Order[New_Challenger + 1] = 2;
            Order_Timer[3] = 1;
            Order_Timer[New_Challenger + 1] = 1;
            if (Champion == 0) {
                Order_Dir[3] = 4;
                Order_Dir[New_Challenger + 1] = 4;
            } else {
                Order_Dir[3] = 8;
                Order_Dir[New_Challenger + 1] = 8;
            }
            Sel_Sub_No[1]++;
        } else {
            if (Sel_Arts_Complete[Select_Status[1] - 1] >= 0) {
                break;
            }
            Order[3] = 3;
            Order_Timer[3] = 1;
            if (Champion == 0) {
                Order_Dir[3] = 4;
            } else {
                Order_Dir[3] = 8;
            }
            Sel_Sub_No[0] = 4;
        }
        break;
    case PS3_CHALLENGER:
        if (Sel_Arts_Complete[Champion] < 0) {
            Order[Champion + 4] = 3;
            Order_Timer[Champion + 4] = 1;
            if (Champion == 0) {
                Order_Dir[Champion + 4] = 4;
            } else {
                Order_Dir[Champion + 4] = 8;
            }
        }
        if (Sel_PL_Complete[New_Challenger] >= 0) {
            break;
        }
        Sel_Sub_No[1]++;
        Order[New_Challenger + 1] = 3;
        Order[New_Challenger + 4] = 2;
        Order_Timer[New_Challenger + 1] = 1;
        Order_Timer[New_Challenger + 4] = 1;
        if (New_Challenger == 0) {
            Order_Dir[New_Challenger + 1] = 4;
            Order_Dir[New_Challenger + 4] = 8;
        } else {
            Order_Dir[New_Challenger + 1] = 8;
            Order_Dir[New_Challenger + 4] = 4;
        }
        Setup_Plates(New_Challenger);
        /* fall through */
    case PS3_BOTH:
        if (Sel_Arts_Complete[Champion] < 0) {
            Order[Champion + 4] = 3;
            Order_Timer[Champion + 4] = 1;
            if (Champion == 0) {
                Order_Dir[Champion + 4] = 4;
            } else {
                Order_Dir[Champion + 4] = 8;
            }
        }
        if (Sel_PL_Complete[New_Challenger] < 0 && Sel_Arts_Complete[Champion] < 0) {
            Sel_Sub_No[1]++;
        }
        break;
    default:
        if (Sel_Arts_Complete[New_Challenger] < 0) {
            Sel_Sub_No[0] = 4;
            Order[New_Challenger + 4] = 3;
            Order_Timer[New_Challenger + 4] = 1;
            if (New_Challenger == 0) {
                Order_Dir[New_Challenger + 4] = 4;
            } else {
                Order_Dir[New_Challenger + 4] = 8;
            }
        }
        break;
    }
}



void PL_Sel_4th(void) {
    if (Sel_Arts_Complete[0] < 0 && Sel_Arts_Complete[1] < 0) {
        Order[3] = 3;
        Order_Timer[3] = 1;
        if (Champion == 0) {
            Order_Dir[Champion + 3] = 4;
        } else {
            Order_Dir[Champion + 3] = 8;
        }
    }
}



void PL_Sel_5th(void) {}



void Setup_Select_Status(void) {
    if (plw[0].wu.operator) {
        Select_Status[0] = SEL_1P;
    } else {
        Select_Status[0] = 0;
    }
    if (plw[1].wu.operator) {
        Select_Status[0] |= SEL_2P;
    }
    if (Sel_Arts_Complete[0] != -1 && plw[0].wu.operator) {
        Select_Status[1] = SEL_1P;
    } else {
        Select_Status[1] = 0;
    }
    if (Sel_Arts_Complete[1] != -1 && plw[1].wu.operator) {
        Select_Status[1] |= SEL_2P;
    }
}



void Basic_Sub(void) {
    bg_w.bgw[0].old_pos_x = bg_w.bgw[0].xy[0].disp.pos;
    move_effect_work(0);
    move_effect_work(1);
    move_effect_work(2);
    move_effect_work(3);
    move_effect_work(4);
    move_effect_work(6);
    move_effect_work(5);
    bg_w.bgw[0].hos_xy[0].disp.pos = bg_w.bgw[0].wxy[0].disp.pos = bg_w.bgw[0].xy[0].disp.pos;
    bg_pos_hosei2();
    Bg_Family_Set();
}



void Basic_Sub_Ex(void) {
    move_effect_work(0);
    move_effect_work(1);
    move_effect_work(2);
    move_effect_work(3);
    move_effect_work(4);
    move_effect_work(6);
    move_effect_work(5);
}



/* provisional name */
/* Basic_Sub with layer 0's line scroll redone. */
void Basic_Sub_Suzi(void) {
    bg_w.bgw[0].old_pos_x = bg_w.bgw[0].xy[0].disp.pos;
    move_effect_work(0);
    move_effect_work(1);
    move_effect_work(2);
    move_effect_work(3);
    move_effect_work(4);
    move_effect_work(6);
    move_effect_work(5);
    bg_w.bgw[0].hos_xy[0].disp.pos = bg_w.bgw[0].wxy[0].disp.pos = bg_w.bgw[0].xy[0].disp.pos;
    suzi_line_calc(0);
    bg_pos_hosei2();
    Bg_Family_Set();
}



static void Setup_BG(BG_INDEX, X, Y)
s16 BG_INDEX;
s32 X;
s32 Y;
{
    bg_w.bgw[BG_INDEX].xy[0].disp.pos = X;
    bg_w.bgw[BG_INDEX].xy[1].disp.pos = Y;
    bg_w.bgw[BG_INDEX].xy[0].disp.low = 0;
    bg_w.bgw[BG_INDEX].xy[1].disp.low = 0;
    bg_w.bgw[BG_INDEX].position_x = X;
    bg_w.bgw[BG_INDEX].position_y = Y;
}



/* Stage 13's layers at the origin, and layer 0's line scroll. */
void Setup_BG_General(void) {
    s16 i;
    Zoomf_Init();
    bg_w.stage = 13;
    bg_w.area = 0;
    bg_initialize();
    for (i = 0; i < bg_w.scno; i++) {
        bg_w.bgw[i].xy[0].disp.pos = 0;
        bg_w.bgw[i].xy[1].disp.pos = 0;
        bg_w.bgw[i].xy[0].disp.low = 0;
        bg_w.bgw[i].xy[1].disp.low = 0;
        bg_w.bgw[i].position_x = 0;
        bg_w.bgw[i].position_y = 0;
        bg_w.bgw[i].hos_xy[0].disp.pos = bg_w.bgw[i].wxy[0].disp.pos = bg_w.bgw[i].xy[0].disp.pos;
    }
    bg_w.bgw[0].pos_x_work = bg_w.bgw[0].xy[0].disp.pos = 0;
    bg_w.bgw[0].suzi_c_no = simmram_small_page_alloc_40(1);
    bg_w.bgw[0].suzi_adrs = (u16*)simmram_slot_addr(bg_w.bgw[0].suzi_c_no);
    scrn_linescroll_set_now(0, bg_w.bgw[0].suzi_adrs);
    memset(bg_w.bgw[0].suzi_adrs, 0, 0x1000);
    Bg_On_R(16);
    suzi_line_clear(0);
    bg_w.bgw[0].zuubun = 120;
    bg_w.bgw[0].no_suzi_line = 0x300;
    bg_w.bgw[0].u_line = 0;
    bg_w.bgw[0].d_line = 0x100;
    bg_w.bgw[0].start_suzi = bg_w.bgw[0].suzi_adrs + 0x600;
    bg_w.bgw[0].old_pos_x = bg_w.bgw[0].xy[0].disp.pos;
    bg_pos_hosei2();
    Bg_Family_Set();
}



/* provisional name */
void Setup_BG_Layer2(void) {
    Setup_BG(2, 512, 0);
    Bg_Family_Set_Ex(2);
}



/* provisional name */
void Setup_BG_Layer3(void) {
    bg_w.bgw[1].xy[0].disp.pos = 256;
    bg_w.bgw[1].xy[1].disp.pos = 128;
    bg_w.bgw[1].xy[0].disp.low = 0;
    bg_w.bgw[1].xy[1].disp.low = 0;
    bg_w.bgw[1].position_x = 256;
    bg_w.bgw[1].position_y = 128;
    bg_w.bgw[1].hos_xy[0].disp.pos = bg_w.bgw[1].wxy[0].disp.pos = bg_w.bgw[1].xy[0].disp.pos;
}



/* Cursor y of the three rows, for each player; Setup_Cursor_Y copies them into Cursor_Y_Pos. */
const s16 Cursor_Y_Data[6] = {
    80, 104, 128, 80, 104, 128,
};


void Setup_Cursor_Y(void) {
    s16 i;
    s16 j;
    s32 p;

    p = (s32)Cursor_Y_Pos;
    for (i = 2, j = 0; i >= 0; i--, j++) {
        *(s16*)(p + i * 2) = Cursor_Y_Data[j];
    }
    p = (s32)Cursor_Y_Pos;
    for (i = 2, j = 3; i >= 0; i--, j++) {
        *(s16*)(p + i * 2 + 6) = Cursor_Y_Data[j];
    }
}



/* provisional name */
/* The next opponent from the player's course, skipping those already beaten; a new course on the
   first fight, and the course restarts when the player picks another character. */
void Setup_Next_EM(void) {
    Setup_ID();
    paring_counter[COM_id] = 0;
    paring_bonus_r[COM_id] = 0;
    if (VS_Index[Player_id] == -1) {
        SC_Personal_Time[Player_id] = 481;
        Control_Time = 481;
        Init_EM_Course();
        Stock_Com_Color = -1;
        Stock_Com_Arts = -1;
        Straight_Lose_Count = 0;
    } else if (Used_char[Player_id] != My_char[Player_id]) {
        VS_Index[Player_id] = 0;
        EM_Course[Player_id] = 0;
        Stock_Com_Color = -1;
        Stock_Com_Arts = -1;
        Straight_Lose_Count = 0;
    }
    Used_char[Player_id] = My_char[Player_id];
    if (VS_Index[Player_id] >= 6) {
        EM_id = 0;
        return;
    } else {
        EM_id = EM_Candidate_Data[Used_char[Player_id]][EM_Course[Player_id]][VS_Index[Player_id]];
    }
    if (Break_Com[Player_id][EM_id] != 0) {
        for (; VS_Index[Player_id] <= 5; VS_Index[Player_id]++) {
            EM_id = EM_Candidate_Data[Used_char[Player_id]][EM_Course[Player_id]][VS_Index[Player_id]];
            if (Break_Com[Player_id][EM_id] == 0) {
                return;
            }
        }
        EM_id = 0;
        VS_Index[Player_id] = 6;
    }
}



/* The super art a computer player takes at random (random_16_com() & 7). */
const u8 Arts_Rnd_Data[8] = {
    0, 0, 0, 1, 1, 1, 2, 2,
};


s32 Setup_Com_Arts(void) {
    if (Stock_Com_Arts == -1) {
        return Arts_Rnd_Data[random_16_com() & 7];
    }
    return Stock_Com_Arts;
}



/* provisional name */
void Init_EM_Course(void) {
    s16 i;
    EM_Course[Player_id] = random_32_com() & 3;
    Last_Player_id = Player_id;
    VS_Index[Player_id] = 0;
    for (i = 0; i <= 12; i++) {
        (&Break_Com[Player_id][0])[i] = 0;
    }
}



void Setup_ID(void) {
    if (Operator_Status[0] == 0) {
        COM_id = 0;
        Player_id = 1;
    } else {
        COM_id = 1;
        Player_id = 0;
    }
}



/* The select screen's second entry, for the next fight: the player's choice stands, the opponent is
   set up and the exit runs on to the VS screen. */
s32 Next_CPU(void) {
    void (*Next_CPU_Tbl[4])() = { Next_CPU_1st, Next_CPU_2nd, Next_CPU_3rd, Next_CPU_4th };
    SEL_PL_X = 0;
    Next_CPU_Tbl[S_No]();
    return SEL_PL_X;
}



/* provisional name */
const s16 Sel_Shot_Data[6] = {
    16, 32, 64, 128, 256, 512,
};


void Next_CPU_1st(void) {
    s16 pl;
    S_No++;
    Exit_Timer = 20;
    SEL_PL_X = 0;
    Suicide = 0;
    Exit_No = 1;
    System_all_clear_Wait();
    effect_work_quick_init();
    Setup_BG_General();
    Setup_BG_Layer2();
    Setup_BG_Layer3();
    Setup_Cursor_Y();
    Setup_Face_ID();
    Setup_Yun_Yang_Face(0);
    Setup_Yun_Yang_Face(1);
    Setup_Face_Sub();
    if (plw[0].wu.operator) {
        pl = 0;
    } else {
        pl = 1;
    }
    effect_38_init(pl, -1);
    effect_39_init(pl, -1);
    effect_D7_init2(pl, Super_Arts[pl], 0);
    effect_D7_init2(pl, Super_Arts[pl], 1);
    effect_98_init(pl, Super_Arts[pl], 0);
    effect_E4_init(pl, Super_Arts[pl], 0);
    OK_Priority[pl] = 0;
}



void Next_CPU_2nd(void) {
    Sel_PL_Cont_2nd();
}



void Next_CPU_3rd(void) {
    Sel_PL_Cont_3rd();
}



void Next_CPU_4th(void) {
    if (Break_Into) {
        return;
    }
    Check_Exit();
}



void Check_Exit(void) {
    s16 cx;
    s16 cy;
    switch (Exit_No) {
    case 0:
        if (plw[0].wu.operator != 0 && Sel_Arts_Complete[0] >= 0) {
            break;
        }
        if (plw[1].wu.operator != 0 && Sel_Arts_Complete[1] >= 0) {
            break;
        }
        Exit_No++;
        if (Demo_Flag == 0) {
            break;
        }
        E_No0 = E0_SELECTED;
        E_No1 = 0;
        E_No2 = 0;
        E_No3 = 0;
        break;
    case 1:
        Sel_Exit_Flag = 0;
        if (plw[0].wu.operator != 0 && plw[1].wu.operator != 0) {
            Exit_Timer = 1;
            Exit_No++;
            Battle_Country = My_char[New_Challenger];
            break;
        }
        if (Cut_Cut_Cut()) {
            Exit_Timer = 1;
        } else {
            Exit_Timer = 60;
        }
        Exit_No++;
        Setup_Next_EM();
        Battle_Country = My_char[COM_id] = EM_id;
        Super_Arts[COM_id] = Stock_Com_Arts = Setup_Com_Arts();
        Setup_Com_Color();
        Setup_PL_Color(COM_id, Com_Color_Shot);
        Request_Disp_Rank[COM_id][RANK_SCORE] = -1;
        Request_Disp_Rank[COM_id][RANK_WINS] = -1;
        if (EM_id == PL_GILL) {
            break;
        }
        effect_50_init(1 ^ COM_id);
        break;
    case 2:
        if (Cut_Cut_Cut()) {
        } else if (--Exit_Timer != 0) {
            break;
        }
        Exit_No++;
        Next_Step = 0;
        effect_A6_init();
        break;
    case 3:
        if (Next_Step == 0) {
            break;
        }
        Exit_No++;
        Next_Step = 0;
        effect_52_init();
        break;
    case 4:
        if (Next_Step == 0) {
            break;
        }
        Exit_No++;
        Next_Step = 0;
        effect_59_init(5);
        if (plw[0].wu.operator != 0 && plw[1].wu.operator != 0) {
            break;
        }
        if (plw[0].wu.operator) {}
        if (EM_id == PL_GILL) {
            effect_38_init(COM_id, 30);
            effect_39_init(COM_id, 30);
            effect_D7_init(COM_id, Super_Arts[COM_id], 0, 40, 0);
            effect_D7_init(COM_id, Super_Arts[COM_id], 0, 40, 1);
            OK_Priority[COM_id] = 0;
        } else {
            cx = Cursor_X[COM_id];
            cy = Cursor_Y[COM_id];
            Cursor_X[COM_id] = EM_Cursor_Data[EM_id][0];
            ((LoHi16*)&Cursor_Y[COM_id])->h = EM_Cursor_Data[EM_id][1];
            effect_38_init(COM_id, 30);
            effect_39_init(COM_id, 30);
            effect_D7_init(COM_id, Super_Arts[COM_id], 0, 40, 0);
            effect_D7_init(COM_id, Super_Arts[COM_id], 0, 40, 1);
            OK_Priority[COM_id] = 0;
            Cursor_X[COM_id] = cx;
            Cursor_Y[COM_id] = cy;
        }
        break;
    case 5:
        if (Next_Step == 0) {
            break;
        }
        if (Request_Fade(30, 0)) {
            Exit_No++;
            Next_Step = 0;
            Forbid_Break = 0;
            BGM_Request(3);
        }
        break;
    case 6:
        if (Check_Fade_Complete_SP()) {
            Exit_No++;
            Exit_Wait = 3;
            Suicide = 1;
            vs_object_count = 4;
            effect_E0_init(0, 35, 72);
            effect_E0_init(1, 40, 71);
            effect_43_init(0, 33);
            effect_43_init(1, 42);
        }
        break;
    case 7:
        if (--Exit_Wait) {
            break;
        }
        Exit_No++;
        effect_B0_init();
        break;
    case 8:
        Exit_No++;
        Forbid_Break = 0;
        break;
    case 9:
        if (Sel_Exit_Flag) {
            Exit_No = 99;
            SEL_PL_X = 1;
            Forbid_Break = 1;
        } else if (END_OF_B0) {
            Exit_No++;
            Forbid_Break = 0;
        }
        break;
    case 10:
        if (END_OF_B0 != 2) {
            break;
        }
        Exit_No++;
        SEL_PL_X = 1;
        break;
    case 11:
        SEL_PL_X = 1;
        break;
    default:
        Forbid_Break = 1;
        SEL_PL_X = 1;
        break;
    }
}



/* provisional name: records the lever into the demo data (nothing calls it) */
void Record_Demo_Lever(void) {
    if (ID) {
        *Demo_Ptr[ID] = ~p2sw_1 & p2sw_0;
    } else {
        *Demo_Ptr[ID] = ~p1sw_1 & p1sw_0;
    }
    Demo_Ptr[ID]++;
}



void Setup_Face_ID(void) {
    s16 i, j;

    for (i = 0; i <= 1; i++) {
        for (j = 0; j <= 4; j++) {
            ID_of_Face[0][i][j] = Face_Cursor_Data[0][i][j];
            ID_of_Face[1][i][j] = Face_Cursor_Data[0][i][j];
        }
    }
}



/* provisional name: Yun (3) and Yang (10) share a face cell; a player who has decided on one leaves the
   other player's cell on the other */
void Setup_Yun_Yang_Face(pl)
s16 pl;
{
    if (plw[pl].wu.operator != 0 && Sel_PL_Complete[pl] != 0) {
        if (My_char[pl] == PL_YANG) {
            ID_of_Face[pl][0][3] = 10;
            ID_of_Face[pl ^ 1][0][3] = 3;
        } else if (My_char[pl] == PL_YUN) {
            ID_of_Face[pl ^ 1][0][3] = 10;
        }
    }
}



/* provisional name: once a player picks Yun or Yang, the other player's shared cell shows the other twin */
void Yun_Yang_Face_Other(pl)
s16 pl;
{
    if (!Sel_PL_Complete[pl ^ 1]) {
        if (My_char[pl] == PL_YUN) {
            ID_of_Face[pl ^ 1][0][3] = 10;
        } else if (My_char[pl] == PL_YANG) {
            ID_of_Face[pl ^ 1][0][3] = 3;
        }
    }
}



/* provisional name: buttons 0x380 on Yun's cell pick Yang, unless the other player already has him */
void Yun_Yang_Select(pl, sw)
s16 pl;
u16 sw;
{
    if (sw & 0x380) {
        if (My_char[pl] == PL_YUN) {
            if (plw[pl ^ 1].wu.operator && Sel_PL_Complete[pl ^ 1] != 0 && My_char[pl ^ 1] == PL_YANG) {
                return;
            }
            My_char[pl] = (s8)10;
            ID_of_Face[pl][0][3] = (u8)10;
        }
    }
}



/* provisional name: a player on Yang keeps Yang in the shared cell (nothing calls it) */
void Yun_Yang_Face_Keep(s16 pl) {
    if (plw[pl].wu.operator != 0 && My_char[pl] == PL_YANG) {
        ID_of_Face[pl][0][3] = 10;
    }
}



/* provisional name */
const s16 Com_Color_Data[16] = {
    BUTTON_LP, BUTTON_LP, BUTTON_LP, BUTTON_LP, BUTTON_LP, BUTTON_LP, BUTTON_MP, BUTTON_MP,
    BUTTON_HP, BUTTON_HP, BUTTON_LK, BUTTON_LK, BUTTON_MK, BUTTON_MK, BUTTON_HK, BUTTON_HK,
};


void Setup_Com_Color(void) {
    if (EM_id == PL_GILL) {
        if (My_char[COM_id] == PL_GILL) {
            Com_Color_Shot = BUTTON_LP;
        } else if (COM_id == 0) {
            Com_Color_Shot = BUTTON_LP;
        } else {
            Com_Color_Shot = BUTTON_MP;
        }
    } else if (Stock_Com_Color == -1) {
        Com_Color_Shot = Stock_Com_Color = Com_Color_Data[random_16_com()];
    } else {
        Com_Color_Shot = Stock_Com_Color;
    }
}



/* Taken off Control_Time by continues (Continue_Coin): row 0 before VS_Index 6, row 1 from it. */
const s16 Correct_Control_Time_Data[2][16] = {
    { 0, 0, 45, 90, 135, 180, 180, 270, 270, 315, 315, 350, 405, 450, 450, 450 },
    { 0, 0, 30, 70, 115, 150, 150, 195, 195, 245, 245, 300, 300, 360, 420, 480 },
};


/* Takes time off the player's select time (SC_Personal_Time, into Control_Time) for the player's continues,
   more late in the game. */
void Correct_Control_Time(PL_id)
s16 PL_id;
{
    u8 cont;
    u8 late;
    if (Play_Type == PLAY_VS_PLAYER) {
        return;
    }
    if (Continue_Coin[PL_id] == 0) {
        return;
    }
    if (VS_Index[PL_id] >= 6) {
        late = 1;
    } else {
        late = 0;
    }
    if (Continue_Coin[PL_id] >= 16) {
        cont = 16;
    } else {
        cont = Continue_Coin[PL_id];
    }
    Control_Time = (s16)SC_Personal_Time[PL_id] - Correct_Control_Time_Data[late][cont];
    if (Control_Time < 0) {
        Control_Time = 0;
    }
}
