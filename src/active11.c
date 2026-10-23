/*
 * ACTIVE11.C  CPU active patterns for character 11 (Ken)
 *
 * Behaviour patterns for the computer-controlled character 11 in active (attacking) mode.
 * Com_Active in Com_Pl calls Computer11, which runs the pattern chosen in Pattern_Index
 * through Pattern11_Tbl. Each Pattern11_nnnn routine (72 of them) is a short script stepped by
 * CP_Index: walks and approaches, waits, range and area checks, normal, lever, command and jump
 * attacks, random branches to other patterns, and End_Pattern to finish.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Sub.h"
#include "active11.h"



void Computer11(PLW* wk) {
    Pattern11_Tbl[Pattern_Index[wk->wu.id]](wk);
}



void Pattern11_0000(PLW* wk) {
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



void Pattern11_0001(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0002(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0003(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0004(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0005(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0006(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0007(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0008(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0009(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0010(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0011(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0012(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0013(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0014(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x80);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0015(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0016(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0017(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0018(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0019(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0020(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack_SP(wk, 8, 0x100, 0x12);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0021(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0022(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0023(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0024(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0025(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0026(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x20, -1);
        break;
    case 1:
        ETC_Term(wk, 4, 2, 0x13);
        break;
    case 2:
        Next_Another_Menu(wk, 2, 0x37);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0027(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Away(wk, 0xBF, 1);
        break;
    case 1:
        ETC_Term(wk, 4, 2, 0x13);
        break;
    case 2:
        Next_Another_Menu(wk, 2, 0x37);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0028(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Jump(wk, 0);
        break;
    case 2:
        Com_Random_Select(wk, 2, 2, 4, 0x20, 0xA, 4);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0029(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Jump(wk, 0);
        break;
    case 2:
        Com_Random_Select(wk, 2, 2, 4, 0, 0xD, 3);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0030(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Away(wk, 0xBF, 1);
        break;
    case 1:
        Com_Random_Select(wk, 2, 0x11, 0, 0x10, 0x2F, 3);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0031(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x20, -1);
        break;
    case 1:
        Com_Random_Select(wk, 2, 0x11, 0, 0x24, 0x23, 3);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0032(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x20);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0033(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0034(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Away(wk, 0xBF, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0035(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xB, 0x102);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0036(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x200);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0037(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0038(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    case 3:
        Com_Random_Select(wk, 2, 0, 0xA, 0x13, 0x1F, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0039(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0040(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x20, 0, 0x8050, -1, 0x100);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0041(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x100, 0, 0x8050, -1, 0x20);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x20);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0042(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 0xB, 0x100, 0, -1, -1, -1);
        break;
    case 1:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0043(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 0xB, 0x100, 0, 0x8050, -1, 0x40);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x200);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0044(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 9, 0x200, 0, 0x8050, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0045(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 9, 0x40, 0, 0x8050, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x40);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0046(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 9, 0x40, 0, 0x8050, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x40);
        break;
    case 2:
        Command_Attack(wk, 0xC, 0x17, 0xA);
        break;
    case 3:
        Wait(wk, 5);
        break;
    case 4:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0047(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Command_Attack(wk, 0xC, 0, -1);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0048(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x8010, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0049(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x8111, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0050(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x8012, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0051(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Away(wk, 0x7F, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0052(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0053(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0054(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0055(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x10);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0056(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x7F, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0057(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x20, 0, 0x8050, -1, 0x100);
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
        Com_Random_Select(wk, 2, 0x2D, 0x13, 0x13, 0xFF, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0058(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x100, 0, 0x8050, -1, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0059(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0xBF, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0060(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x82);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0061(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x12);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0062(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 3, 2, 0x11);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0063(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 3, 2, 0x12);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0064(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 3, 2, 0x13);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0065(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    case 2:
        Normal_Attack(wk, 0xC, 0x102);
        break;
    case 3:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0066(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    case 4:
        Com_Random_Select(wk, 2, 0, 0xA, 0x13, 0x1F, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0067(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    case 3:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0068(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0069(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 3, 2, 0);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0070(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 3, 2, 0);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern11_0071(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        ETC_Term(wk, 3, 2, 0);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}
