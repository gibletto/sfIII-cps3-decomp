/*
 * ACTIVE09.C  CPU active patterns for character 09 (Oro)
 *
 * Behaviour patterns for the computer-controlled character 09 in active (attacking) mode.
 * Com_Active in Com_Pl calls Computer09, which runs the pattern chosen in Pattern_Index
 * through Pattern09_Tbl. Each Pattern09_nnnn routine (80 of them) is a short script stepped by
 * CP_Index: walks and approaches, waits, range and area checks, normal, lever, command and jump
 * attacks, random branches to other patterns, and End_Pattern to finish.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Sub.h"
#include "active09.h"



void Computer09(PLW* wk) {
    Pattern09_Tbl[Pattern_Index[wk->wu.id]](wk);
}



void Pattern09_0000(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Com_Random_Select(wk, 2, 0x47, 0x47, 0x46, 0x46, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0001(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x82);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0002(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8040, -1, 5, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0003(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8060, -1, 5, 1, -1);
        break;
    case 1:
        Adjust_Attack(wk, 8, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0004(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 1, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0005(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0006(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait(wk, 0x3C);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0007(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 1, 0xB);
        break;
    case 1:
        Look(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0008(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8070, 0x8040, 0, 0x100, 0, -1, -1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0009(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8040, -1, 5, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0010(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8060, -1, 5, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0011(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8060, -1, 5, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0012(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8060, -1, 5, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0013(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8068, -1, 5, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0014(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8038, 8, 0x100, 2, 0x8080, -1, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0015(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 0, 0x30, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0016(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x30, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0017(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x58, -1, 5, 2, 0);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0018(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump(wk, 1);
        break;
    case 1:
        Look(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0019(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8068, -1, 0, 2, 5);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0020(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Com_Random_Select(wk, 2, 0x41, 0x42, 0x43, 0x44, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0021(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x80F0, -1, 5, 2, 0);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x19, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0022(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8038, 8, 0x40, 0, 0x8070, -1, 0x80);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0023(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x7F, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0024(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 0, 0x60, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0025(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x60, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0026(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0, 0xB);
        break;
    case 1:
        Look(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0027(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0028(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x7F, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0029(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, -1, 5, 1, -1);
        break;
    case 1:
        Adjust_Attack(wk, 9, 0x80);
        break;
    case 2:
        Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0030(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, -1, 5, 1, -1);
        break;
    case 1:
        Adjust_Attack(wk, 9, 0x80);
        break;
    case 2:
        Lever_Attack(wk, 8, 0, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0031(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8030, 8, 0x100, 0, 0x8098, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0032(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Adjust_Attack(wk, 9, 0x10);
        break;
    case 1:
        Adjust_Attack(wk, 8, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0033(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Adjust_Attack(wk, 9, 0x10);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0034(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0, 0x80);
        break;
    case 1:
        Look(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0035(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8060, -1, 5, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0036(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x80A0, -1, 5, 2, 0);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0037(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0038(PLW* wk) {
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



void Pattern09_0039(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0, 0xB);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0040(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x102);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x19, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0041(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8060, -1, 5, 1, -1);
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



void Pattern09_0042(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x12);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x12);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x12);
        break;
    case 3:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0043(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8030, 8, 0x40, 0, -1, 0x30, 0x4019);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0044(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 8, 0x40, 0, -1, 0x30, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0045(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8030, 8, 0x200, 0, -1, -1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0046(PLW* wk) {
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



void Pattern09_0047(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Command_Attack_Term(wk, 8, 0x19, 0xA, 0x8060, 0x30, 0, -1, 0x30, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0048(PLW* wk) {
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



void Pattern09_0049(PLW* wk) {
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



void Pattern09_0050(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Attack(wk, 8, 0xA, 0x200, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0051(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Attack_Term(wk, -1, 0x30, 8, 0x40, 0, -1, -1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0052(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Command_Attack_Term(wk, 8, 0x19, 0xA, -1, 0x30, 0, -1, -1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0053(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x8012, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0054(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x8011, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0055(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x8011, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0056(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x8011, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0057(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x8011, 0xB);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0058(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x8010, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0059(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8070, -1, 5, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0060(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0061(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0062(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, -1, 0x36, -1, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0063(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8070, 0x8040, 8, 0x100, 0, 0x8098, -1, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0064(PLW* wk) {
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
    case 4:
        SA_Term(wk, 0x35, 0x36, 0x3A, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0065(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    case 1:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0066(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x18, 0xA);
        break;
    case 1:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0067(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    case 1:
        Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0068(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x18, 8);
        break;
    case 1:
        Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0069(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Command_Attack_Term(wk, 8, 0x26, 9, -1, 0x8040, 0, -1, -1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0070(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Look(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0071(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_On(wk, 1, 2);
        break;
    case 1:
        Look(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0072(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8060, 0x8010, 5, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0073(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8040, 0x8010, 5, 1, -1);
        break;
    case 1:
        Adjust_Attack(wk, 8, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0074(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8048, 0x8010, 5, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0075(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8038, 8, 0x40, 0, 0x8060, -1, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0076(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8030, 8, 0x100, 0, 0x8060, -1, 0x20);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0077(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 0xA009, 0x200, 0, 0x8060, -1, 0x40);
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



void Pattern09_0078(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Search_Back_Term(wk, 0x60, 2, 0x4F);
        break;
    case 1:
        Pierce_On(wk);
        break;
    case 2:
        Command_Attack(wk, 8, 1, 0xB);
        break;
    case 3:
        SA_Term(wk, 0x35, -1, 0x3A, 0);
        break;
    case 4:
        Com_Random_Select(wk, 6, 0x36, 0x37, 0x38, 0x39, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern09_0079(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x35, -1, 0x3A, 0);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0x36, 0x37, 0x38, 0x39, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}
