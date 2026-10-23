/*
 * PASS03.C  CPU passive patterns for character 3 (Yun)
 *
 * Passive03 is the CPU passive (defensive) routine for character 3, called through
 * Com_Passive's table by character number. It runs the current pattern chosen by Pattern_Index
 * from Passive03_Tbl.
 * The 120 Passive03_xxxx routines are the pattern steps: each is a switch on CP_Index that calls
 * the Com_Sub building blocks (guards, waits for get-up, normal and command attacks, lever
 * releases, reaction terms such as EM_Term) one step at a time and finishes with End_Pattern.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Sub.h"
#include "PASS03.h"



void Passive03(PLW* wk) {
    Passive03_Tbl[Pattern_Index[wk->wu.id]](wk);
}



void Passive03_0000(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0x8B, M_Lv[wk->wu.id]);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0001(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Off(wk);
        break;
    case 1:
        Look(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0002(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 3, -1);
        break;
    case 1:
        Pierce_On(wk);
        break;
    case 2:
        Command_Attack(wk, 8, 0, 0xA);
        break;
    case 3:
        EM_Term(wk, 0x7FFF, -1, 1, 1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0003(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        VS_Jump_Guard(wk);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0004(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Search_Back_Term(wk, 0x70, 6, 0x53);
        break;
    case 1:
        Command_Attack(wk, 8, 1, 0xB);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0005(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Forced_Guard(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0006(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x77, 2);
        break;
    case 1:
        EM_Term(wk, 0x7FFF, -1, 1, 1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0007(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0xB7, 2);
        break;
    case 1:
        Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0008(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Command_Attack(wk, 0xC, 0, 0xB);
        break;
    case 2:
        Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0009(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0010(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8080, 0, 0, 2, 0);
        break;
    case 1:
        Short_Range_Attack(wk, 8, 0x40, 6, 0x1D);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0011(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Attack_Term(wk, 0x8060, -1, 8, 0x8200, 2, 0x8060, -1, 0x8200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0012(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8070, 0, 0, 2, 0);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0013(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, -1, -1, 0x30, 0);
        break;
    case 1:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 2:
        SA_Term(wk, 0x2E, 0x2F, -1, 0);
        break;
    case 3:
        Normal_Attack(wk, 0xB, 0x10);
        break;
    case 4:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 5:
        Normal_Attack(wk, 8, 0x40);
        break;
    case 6:
        Com_Random_Select(wk, 6, 0x37, 0x37, 0x27, 0x27, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0014(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, 0x8050, 0, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0015(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0016(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x2F, 2);
        break;
    case 1:
        Wait_Get_Up(wk, 3, -1);
        break;
    case 2:
        Normal_Attack(wk, 0xB, 0x10);
        break;
    case 3:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 4:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 5:
        Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0017(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Search_Back_Term(wk, 0x70, 6, 0x6C);
        break;
    case 1:
        Pierce_On(wk);
        break;
    case 2:
        Keep_Away(wk, 0x81, 0);
        break;
    case 3:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 4:
        Normal_Attack(wk, 0xB, 0x80);
        break;
    case 5:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 6:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 7:
        Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0018(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x39, 2);
        break;
    case 1:
        Wait_Get_Up(wk, 3, -1);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x82);
        break;
    case 3:
        Normal_Attack(wk, 0xB, 0x102);
        break;
    case 4:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0019(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0020(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 3, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0021(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0022(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Jump_Attack_Term(wk, 0x8060, 0x8030, 0xB, 0x80, 0, 0x8060, -1, 0x40);
        break;
    case 2:
        Normal_Attack(wk, 0xB, 0x10);
        break;
    case 3:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 4:
        Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0023(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Jump_Attack_Term(wk, 0x8060, -1, 0xB, 0x8080, 0, 0x8060, -1, 0x40);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 3:
        Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0024(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Search_Back_Term(wk, 0x70, 6, 0x6C);
        break;
    case 1:
        Pierce_On(wk);
        break;
    case 2:
        Keep_Away(wk, 0x81, 0);
        break;
    case 3:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 4:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0025(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Search_Back_Term(wk, 0x70, 6, 0x68);
        break;
    case 1:
        Pierce_On(wk);
        break;
    case 2:
        Keep_Away(wk, 0x81, 0);
        break;
    case 3:
        Wait_Get_Up(wk, 3, -1);
        break;
    case 4:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0026(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8010, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0027(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0028(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, -1, 8, 0x8200, 2, 0x8060, -1, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0029(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0030(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0031(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x20, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0032(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x2E, 0x2F, -1, 0);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x22);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x12);
        break;
    case 3:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0033(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0034(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xC, 0x20);
        break;
    case 1:
        Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0035(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x82);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x102);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0036(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x82);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x102);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0037(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8008, 6, 1, -1);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0038(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8010, 6, 1, -1);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0039(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 0, 2, 0x42);
        break;
    case 1:
        Branch_Unit_Area(wk, 6, 0x59, 0x5A, 0x5A, 0x5B);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0040(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8060, 0x8008, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x80);
        break;
    case 3:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0041(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8050, 6, 1, -1);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x42);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0042(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, -1, 8, 0x8200, 2, 0x8060, -1, 0x8200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0043(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8028, 6, 1, -1);
        break;
    case 1:
        Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0044(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x39, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0045(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8020, 6, 1, -1);
        break;
    case 1:
        Branch_Unit_Area(wk, 6, 0x59, 0x5A, 0x5B, 0x5B);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0046(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Status(wk, 2, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0047(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xB, 0x82);
        break;
    case 1:
        Branch_Unit_Area(wk, 6, 0x59, 0x5A, 0x5B, 0x5B);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0048(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x82);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0049(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Adjust_Attack(wk, 8, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0050(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x12);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x22);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0051(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 0xB, 0xE, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0052(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0053(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, -1, 8, 0x8200, 2, 0x8060, -1, 0x8200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0054(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Attack_Term(wk, 0x8060, -1, 8, 0x8200, 2, 0x8060, -1, 0x8200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0055(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0056(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8030, 8, 0x40, 0, 0x8060, -1, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0057(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8030, 8, 0x20, 0, 0x8060, -1, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0058(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Status(wk, 2, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0059(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xB, 0x20);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0060(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Forced_Guard(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0061(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x2E, 0x2F, 0x30, 0);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0062(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x2F, 2);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0063(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xC, 0x20);
        break;
    case 1:
        Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0064(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0065(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x2F, 2);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x80);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0066(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 0, 6, 0x40);
        break;
    case 1:
        Branch_Unit_Area(wk, 6, 0x59, 0x5A, 0x5A, 0x5B);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0067(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x19, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0068(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8030, 8, 0x40, 0, 0x8060, -1, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0069(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 0xC, 0, 0xB);
        break;
    case 1:
        Branch_Unit_Area(wk, 6, 0x59, 0x5A, 0x5B, 0x5B);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0070(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Command_Attack(wk, 8, 0, 0xB);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0071(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x2F, 2);
        break;
    case 1:
        Command_Attack(wk, 8, 0x16, 0xA);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0072(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Command_Attack(wk, 0xC, 0, 0xB);
        break;
    case 2:
        Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0073(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0xB7, 2);
        break;
    case 1:
        Hi_Jump_Attack_Term(wk, 0x8060, -1, 0xB, 0x8200, 0, 0x8060, -1, 0x40);
        break;
    case 2:
        Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0074(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x2E, 0x2F, 0x30, 0);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 3:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 4:
        Com_Random_Select(wk, 6, 0x37, 0x37, 0x27, 0x27, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0075(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x2E, -1, 0x30, 0);
        break;
    case 1:
        Approach_Walk(wk, 0x2F, 2);
        break;
    case 2:
        SA_Term(wk, -1, 0x2F, -1, 0);
        break;
    case 3:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 4:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 5:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 6:
        Com_Random_Select(wk, 6, 0x37, 0x37, 0x27, 0x27, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0076(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x2E, -1, 0x30, 0);
        break;
    case 1:
        Approach_Walk(wk, 0xB7, 2);
        break;
    case 2:
        Hi_Jump_Attack_Term(wk, 0x8060, -1, 8, 0x8200, 0, 0x8060, -1, 0x40);
        break;
    case 3:
        Normal_Attack(wk, 0xB, 0x10);
        break;
    case 4:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 5:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 6:
        Com_Random_Select(wk, 6, 0x37, 0x37, 0x27, 0x27, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0077(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8030, 0xB, 0x20, 0, 0x8060, -1, 0x40);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0078(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8050, -1, 8, 0x8200, 0, 0x8060, -1, 0x40);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x10);
        break;
    case 2:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 3:
        Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0079(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8030, 0xB, 0x20, 0, -1, -1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0080(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Attack_Term(wk, 0x8060, 0x8030, 0xB, 0x40, 0, 0x8060, -1, 0x40);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0081(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Attack_Term(wk, 0x8060, -1, 0xB, 0x8100, 0, 0x8060, -1, 0x40);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x10);
        break;
    case 2:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0082(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Attack_Term(wk, 0x8060, 0x8040, 0xB, 0x40, 0, -1, -1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0083(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Attack_Term(wk, 0x8060, 0x8040, 0xB, 0x40, 0, 0x8060, -1, 0x40);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x10);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 3:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 4:
        Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0084(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Attack_Term(wk, 0x8060, -1, 8, 0x8200, 0, 0x8060, -1, 0x40);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x10);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 3:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 4:
        Com_Random_Select(wk, 6, 0x37, 0x37, 0x27, 0x27, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0085(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait(wk, 0xA);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0086(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x2F, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8008, 6, 1, -1);
        break;
    case 2:
        SA_Term(wk, 0x2E, 0x2F, -1, 0);
        break;
    case 3:
        Normal_Attack(wk, 0xB, 0x12);
        break;
    case 4:
        Normal_Attack(wk, 8, 0x42);
        break;
    case 5:
        Com_Random_Select(wk, 6, 0x37, 0x37, 0x27, 0x27, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0087(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x2F, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8008, 6, 1, -1);
        break;
    case 2:
        SA_Term(wk, -1, 0x2F, -1, 0);
        break;
    case 3:
        Normal_Attack(wk, 0xB, 0x10);
        break;
    case 4:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 5:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 6:
        Com_Random_Select(wk, 6, 0x37, 0x37, 0x27, 0x27, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0088(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8028, 6, 1, -1);
        break;
    case 1:
        SA_Term(wk, -1, -1, 0x30, 0);
        break;
    case 2:
        Normal_Attack(wk, 0xB, 0x10);
        break;
    case 3:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 4:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 5:
        Com_Random_Select(wk, 6, 0x37, 0x37, 0x27, 0x27, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0089(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0090(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0091(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0092(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8020, 6, 1, -1);
        break;
    case 1:
        Branch_Unit_Area(wk, 6, 0x59, 0x5A, 0x5B, 0x5B);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0093(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x82);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x82);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0094(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Branch_Unit_Area(wk, 6, 0x59, 0x5A, 0x5B, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0095(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x30, 0);
        break;
    case 1:
        Branch_Unit_Area(wk, 6, 0x59, 0x5A, 0x5B, 0x5B);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0096(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8010, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0097(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x2F, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8008, 6, 1, -1);
        break;
    case 2:
        Lever_Attack(wk, 8, 0, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0098(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x2F, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8010, 6, 1, -1);
        break;
    case 2:
        Normal_Attack(wk, 0xB, 0x10);
        break;
    case 3:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 4:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 5:
        Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0099(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xB, 0x10);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 2:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 3:
        Com_Random_Select(wk, 6, 0x37, 0x37, 0x27, 0x27, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0100(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x30, 0);
        break;
    case 1:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0101(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8080, -1, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0102(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, 0x8050, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x100);
        break;
    case 2:
        Command_Attack(wk, 8, 0x19, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0103(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Search_Back_Term(wk, 0x70, 6, 0x68);
        break;
    case 1:
        Walk(wk, 1, 0x20, 0);
        break;
    case 2:
        Wait_Get_Up(wk, 1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0104(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump(wk, 3, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0105(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Search_Back_Term(wk, 0x70, 6, 0x68);
        break;
    case 1:
        Pierce_On(wk);
        break;
    case 2:
        Command_Attack(wk, 8, 1, 0xA);
        break;
    case 3:
        Wait_Get_Up(wk, 3, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0106(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Search_Back_Term(wk, 0x70, 6, 0x68);
        break;
    case 1:
        Walk(wk, 1, 0x38, 0);
        break;
    case 2:
        Wait_Get_Up(wk, 1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0107(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x2E, 0x2F, 0x30, 0);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0x37, 0x37, 0x27, 0x27, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0108(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0xB7, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0109(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x2E, -1, 0x30, 0);
        break;
    case 1:
        Branch_Unit_Area(wk, 6, 0x59, 0x5A, 0x5B, 0x5B);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0110(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xC, 0x20);
        break;
    case 1:
        SA_Term(wk, 0x2E, 0x2F, -1, 0);
        break;
    case 2:
        Com_Random_Select(wk, 6, 0x37, 0x37, 0x27, 0x27, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0111(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8050, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0112(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8050, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x100);
        break;
    case 2:
        Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0113(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x20, 6, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0114(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, -1, 0x20, 8, 0x200, 1, -1, 0x20, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0115(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 0xB, 0xE, 0xA);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x82);
        break;
    case 2:
        Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0116(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, -1, 0x20, 8, 0x200, 0, -1, 0x20, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0117(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, -1, 0x20, 8, 0x100, 1, -1, 0x20, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0118(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, -1, 0x20, 8, 0x100, 0, -1, 0x20, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive03_0119(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}
