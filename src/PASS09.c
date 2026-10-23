/*
 * PASS09.C  CPU passive patterns for character 9 (Oro)
 *
 * Passive09 is the CPU passive (defensive) routine for character 9, called through
 * Com_Passive's table by character number. It runs the current pattern chosen by Pattern_Index
 * from Passive09_Tbl.
 * The 112 Passive09_xxxx routines are the pattern steps: each is a switch on CP_Index that calls
 * the Com_Sub building blocks (guards, waits for get-up, normal and command attacks, lever
 * releases, reaction terms such as EM_Term) one step at a time and finishes with End_Pattern.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Sub.h"
#include "PASS09.h"



void Passive09(PLW* wk) {
    Passive09_Tbl[Pattern_Index[wk->wu.id]](wk);
}



void Passive09_0000(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xD, M_Lv[wk->wu.id]);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0001(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 1, 0xB);
        break;
    case 1:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0002(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x80F0, -1, 5, 6, 0x2A);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x19, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0003(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0, 0xB);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0004(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0, 0xB);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xB);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0005(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0006(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Look(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0007(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_On(wk, -1, 2);
        break;
    case 1:
        EM_Term(wk, 0x8078, -1, 6, 1, -1);
        break;
    case 2:
        Check_Store_Lever(wk, 0x16, 1, -1);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0008(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_On(wk, -1, 2);
        break;
    case 1:
        EM_Term(wk, 0x8078, -1, 6, 1, -1);
        break;
    case 2:
        Check_Store_Lever(wk, 0x16, 1, -1);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0009(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_On(wk, -1, 2);
        break;
    case 1:
        EM_Term(wk, 0x8078, -1, 6, 1, -1);
        break;
    case 2:
        Check_Store_Lever(wk, 0x16, 1, -1);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0010(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 1, 6, 7);
        break;
    case 1:
        EM_Term(wk, 0x8030, 0x8038, 6, 1, -1);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0011(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8030, 8, 0x20, 2, 0x8090, -1, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0012(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8070, 0, 6, 2, 0);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0013(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 1, 0xB);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0014(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        VS_Jump_Guard(wk);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0015(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 1, 6, 0x6C);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 3:
        Normal_Attack(wk, 8, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0016(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 2:
        Lever_Attack(wk, 8, 0, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0017(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x7F, 2);
        break;
    case 1:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0018(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x7F, 2);
        break;
    case 1:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 2:
        EM_Term(wk, 0x8050, -1, 5, 6, 0x1C);
        break;
    case 3:
        Lever_Attack(wk, 8, 0, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0019(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0020(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 3, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0021(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x7F, 2);
        break;
    case 1:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0022(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Jump_Attack_Term(wk, 0x8070, 0x8040, 8, 0x100, 0, 0x8098, -1, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0023(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Jump_Attack_Term(wk, 0x8060, 0x8038, 8, 0x40, 0, 0x8088, -1, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0024(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0xBF, 2);
        break;
    case 1:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0025(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 3, -1);
        break;
    case 1:
        Command_Attack(wk, 8, 0, 0xB);
        break;
    case 2:
        EM_Term(wk, 0x7FFF, -1, 1, 1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0026(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x7F, 2);
        break;
    case 1:
        EM_Term(wk, 0x7FFF, -1, 1, 1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0027(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xB, 0x102);
        break;
    case 1:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0028(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0029(PLW* wk) {
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



void Passive09_0030(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0031(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x20, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0032(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0033(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0034(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 1, 6, 0x6C);
        break;
    case 1:
        Adjust_Attack(wk, 8, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0035(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x82);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0036(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0037(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8008, 6, 1, -1);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0038(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8008, 6, 1, -1);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0039(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_On(wk, -1, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0040(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8010, 6, 6, 0x1F);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x100);
        break;
    case 3:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0041(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 1, 6, 0x6D);
        break;
    case 1:
        Lever_On(wk, -1, 2);
        break;
    case 2:
        EM_Term(wk, -1, 0x8010, 6, 6, 0x1F);
        break;
    case 3:
        Normal_Attack(wk, 9, 0x22);
        break;
    case 4:
        Check_Store_Lever(wk, 0x16, 1, -1);
        break;
    case 5:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0042(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Look(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0043(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        Lever_On(wk, -1, 2);
        break;
    case 2:
        EM_Term(wk, -1, 0x8050, 6, 6, 0x1F);
        break;
    case 3:
        Check_Store_Lever(wk, 0x16, 1, -1);
        break;
    case 4:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0044(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8008, 3, 1, -1);
        break;
    case 2:
        Lever_Attack(wk, 8, 0, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0045(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8010, 6, 6, 0x1F);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0046(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Status(wk, 2, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0047(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xB, 0x82);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0048(PLW* wk) {
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



void Passive09_0049(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 1, 6, 0x6D);
        break;
    case 1:
        EM_Term(wk, 0x8050, -1, 3, 6, 0x1F);
        break;
    case 2:
        Adjust_Attack(wk, 8, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0050(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, -1, 3, 6, 0x1F);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0051(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x12);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x12);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0052(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0053(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x58, -1, 5, 6, 0x2A);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0054(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0055(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x80A0, -1, 5, 6, 0x2A);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0056(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8050, 0x40, 8, 0x200, 0, 0x8098, -1, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0057(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8038, 8, 0x80, 0, 0x8088, -1, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0058(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Status(wk, 2, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0059(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_On(wk, -1, 2);
        break;
    case 1:
        EM_Term(wk, 0x8050, -1, 3, 6, 0x1F);
        break;
    case 2:
        Check_Store_Lever(wk, 0x16, 1, -1);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0060(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Forced_Guard(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0061(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0062(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xC, 0x100);
        break;
    case 1:
        ETC_Term(wk, 1, 6, 0x6E);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0063(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x35, -1, 0x3A, 0);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0x60, 0x61, 0x62, 0x63, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0064(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        ETC_Term(wk, 1, 6, 0x6E);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x10);
        break;
    case 3:
        Normal_Attack(wk, 9, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0065(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x100);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0066(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0xBF, 2);
        break;
    case 1:
        SA_Term(wk, 0x35, 0x36, -1, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0067(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Attack_Complete(wk, 3, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0068(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 0, 0x15, 0);
        break;
    case 1:
        Walk(wk, 1, 0x13, 0);
        break;
    case 2:
        Walk(wk, 0, 0x10, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0069(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Attack_Complete(wk, 3, 1);
        break;
    case 1:
        SA_Term(wk, 0x35, -1, 0x3A, 0);
        break;
    case 2:
        Wait_Attack_Complete(wk, 3, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0070(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x7F, 2);
        break;
    case 1:
        SA_Term(wk, 0x35, -1, 0x3A, 0);
        break;
    case 2:
        Com_Random_Select(wk, 6, 0x60, 0x61, 0x62, 0x63, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0071(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, -1, -1, 0x3A, 0);
        break;
    case 1:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0072(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x35, -1, -1, 0);
        break;
    case 1:
        EM_Term(wk, 0x8070, 0x8010, 5, 6, 0x1C);
        break;
    case 2:
        Lever_Attack(wk, 8, 0, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0073(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x10);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0074(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x35, -1, 0x3A, 0);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0x60, 0x61, 0x62, 0x63, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0075(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 1, 6, 0x6C);
        break;
    case 1:
        Lever_On(wk, -1, 2);
        break;
    case 2:
        EM_Term(wk, 0x8040, -1, 3, 6, 0x1F);
        break;
    case 3:
        Normal_Attack(wk, 0xB, 0x12);
        break;
    case 4:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0076(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 1, 6, 0x6E);
        break;
    case 1:
        EM_Term(wk, 0x8050, -1, 5, 6, 0x1C);
        break;
    case 2:
        Lever_Attack(wk, 8, 0, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0077(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Attack_Complete(wk, 3, 1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0078(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0079(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Forced_Guard(wk, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0080(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 0xA009, 0x200, 0, 0x8050, -1, 0x200);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x22);
        break;
    case 2:
        Command_Attack(wk, 0xC, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0081(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8050, 0x8040, 9, 0x40, 0, 0x8050, -1, 0x200);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x100);
        break;
    case 2:
        Command_Attack(wk, 0xC, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0082(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x10, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8010, 6, 1, -1);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x100);
        break;
    case 3:
        Command_Attack(wk, 0xC, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0083(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump(wk, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0084(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, -1, 0x8040, 9, 0x80, 1, 0x8050, -1, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0085(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0xE, 0xA);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x102);
        break;
    case 3:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0086(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Away(wk, 0xBF, 0);
        break;
    case 1:
        Wait_Get_Up(wk, 3, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0087(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8040, 0x8040, 9, 0x100, 0, 0x8050, -1, 0x200);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0088(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 0xA009, 0x100, 0, 0x8050, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x12);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 3:
        Normal_Attack(wk, 8, 0x102);
        break;
    case 4:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    case 5:
        Com_Random_Select(wk, 6, 0x2D, 0xFF, 0xFF, 0xFF, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0089(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Command_Attack(wk, 8, 0, -1);
        break;
    case 2:
        Branch_Unit_Area(wk, 6, 0x20, 0x3B, 0x36, 0x5A);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0090(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0091(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, 0x8010, 6, 1, -1);
        break;
    case 1:
        Command_Attack(wk, 0xC, 0x18, 0xA);
        break;
    case 2:
        Wait(wk, 5);
        break;
    case 3:
        SA_Term(wk, 0x35, -1, 0x3A, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0092(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Com_Random_Select(wk, 6, 0x60, 0x61, 0x62, 0x63, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0093(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 9, 0x40, 0, 0x8050, -1, 0x200);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x102);
        break;
    case 2:
        Command_Attack(wk, 0xC, 0x18, 0xA);
        break;
    case 3:
        Wait(wk, 5);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0094(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, -1, 0x36, -1, 0x36);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0095(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, -1, 0x36, -1, 0x37);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0096(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, -1, 0x36, -1, 0x38);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0097(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, -1, 0x36, -1, 0x39);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0098(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8010, 5, 6, 0x1F);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x100);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0099(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 1, 6, 0x6D);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x20);
        break;
    case 2:
        Com_Random_Select(wk, 6, 5, 5, 0x64, 0x5A, 4);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0100(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0101(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Command_Attack_Term(wk, 8, 0x26, 9, -1, 0x8040, 0, -1, -1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0102(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_On(wk, 1, 2);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x102);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0103(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_On(wk, 1, 2);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x102);
        break;
    case 3:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0104(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_On(wk, 1, 2);
        break;
    case 1:
        Jump(wk, 0);
        break;
    case 2:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0105(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_On(wk, 1, 2);
        break;
    case 1:
        Jump(wk, 0);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0106(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_On(wk, -1, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x30, 6, 1, -1);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0107(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8070, 6, 2, 0);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0108(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 1, 6, 0x28);
        break;
    case 1:
        EM_Term(wk, 0x8038, 0x8008, 5, 1, -1);
        break;
    case 2:
        Adjust_Attack(wk, 8, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0109(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 1, 6, 0x28);
        break;
    case 1:
        EM_Term(wk, 0x8040, 0x8008, 5, 1, -1);
        break;
    case 2:
        Adjust_Attack(wk, 8, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0110(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 1, 6, 0x28);
        break;
    case 1:
        EM_Term(wk, 0x8068, 0x8008, 5, 1, -1);
        break;
    case 2:
        Adjust_Attack(wk, 8, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive09_0111(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x7F, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}
