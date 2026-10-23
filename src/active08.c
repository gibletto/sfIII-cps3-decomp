/*
 * ACTIVE08.C  CPU active patterns for character 08 (Elena)
 *
 * Behaviour patterns for the computer-controlled character 08 in active (attacking) mode.
 * Com_Active in Com_Pl calls Computer08, which runs the pattern chosen in Pattern_Index
 * through Pattern08_Tbl. Each Pattern08_nnnn routine (64 of them) is a short script stepped by
 * CP_Index: walks and approaches, waits, range and area checks, normal, lever, command and jump
 * attacks, random branches to other patterns, and End_Pattern to finish.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Sub.h"
#include "active08.h"



void Computer08(PLW* wk) {
    Pattern08_Tbl[Pattern_Index[wk->wu.id]](wk);
}



void Pattern08_0000(PLW* wk) {
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



void Pattern08_0001(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0002(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x82);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0003(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Adjust_Attack(wk, 9, 0x10);
        break;
    case 1:
        Adjust_Attack(wk, 8, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0004(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 0xB, 0x18, 9);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    case 2:
        Pierce_On(wk);
        break;
    case 3:
        Command_Attack(wk, 8, 1, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0005(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x40);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0006(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0007(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 1, 0xA);
        break;
    case 1:
        Lever_Off(wk);
        break;
    case 2:
        Look(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0008(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8070, 0x8040, 8, 0x100, 0, 0x8068, -1, 0x10);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0009(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    case 2:
        J_Command_Attack(wk, 9, 0x18, 0xA);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0010(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0011(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x102);
        break;
    case 2:
        J_Command_Attack(wk, 9, 0x18, 0xA);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0012(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0013(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x102);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0014(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8038, 8, 0x100, 2, -1, 0x8010, 0x80);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0015(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 0, 0x30, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0016(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x30, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0017(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0018(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Search_Back_Term(wk, 0x60, 1, -1);
        break;
    case 1:
        Jump(wk, 1);
        break;
    case 2:
        Command_Attack(wk, 8, 0, 0xA);
        break;
    case 3:
        Lever_Off(wk);
        break;
    case 4:
        Look(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0019(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x70, -1, 0, 2, 5);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0020(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 9, 0x17, 0xA);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0021(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0022(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8068, 0x8040, 9, 0x40, 0, 0x8070, -1, 0x80);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0023(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x7B, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0024(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 0, 0x60, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0025(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x60, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0026(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0, 0xB);
        break;
    case 1:
        Lever_Off(wk);
        break;
    case 2:
        Look(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0027(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0028(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0xBF, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0029(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 9);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x40);
        break;
    case 3:
        Lever_Attack(wk, 8, 0, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0030(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x20);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x100);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0031(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8068, 0x8040, 8, 0x100, 0, 0x8098, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0032(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Adjust_Attack(wk, 0xB, 0x10);
        break;
    case 1:
        Adjust_Attack(wk, 0xB, 0x20);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0033(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 9, 0, 0x20);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0034(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xB, 0x80);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x40);
        break;
    case 2:
        Normal_Attack(wk, 0xB, 0x202);
        break;
    case 3:
        Pierce_On(wk);
        break;
    case 4:
        Command_Attack(wk, 8, 1, 0xA);
        break;
    case 5:
        Lever_Off(wk);
        break;
    case 6:
        Look(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0035(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0036(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x42);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0037(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0038(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x39, 0x3A, -1, 0);
        break;
    case 1:
        Pierce_On(wk);
        break;
    case 2:
        Adjust_Attack(wk, 8, 0x100);
        break;
    case 3:
        Lever_Attack(wk, 8, 0, 0x20);
        break;
    case 4:
        Lever_Attack(wk, 8, 0, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0039(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0, 0xB);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0040(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x102);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0041(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xB, 0x40);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    case 2:
        Lever_Attack(wk, 8, 0, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0042(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8070, 0x8040, 8, 0x100, 0, 0x8090, -1, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0043(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8068, 0x8040, 8, 0x40, 0, -1, 0x8020, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0044(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8068, 0x8040, 8, 0x40, 0, 0x8090, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0045(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8068, 0x8040, 0xB, 0x200, 0, 0x8090, -1, 0x20);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x12);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0046(PLW* wk) {
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



void Pattern08_0047(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x20, 0);
        break;
    case 1:
        Walk(wk, 0, 0x14, 0);
        break;
    case 2:
        Walk(wk, 1, 0x18, 0);
        break;
    case 3:
        Wait(wk, 0x14);
        break;
    case 4:
        Walk(wk, 0, 0x14, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0048(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait(wk, 0x3C);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0049(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0050(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Attack_Term(wk, 0x8068, 0x8048, 8, 0x200, 2, -1, 0x8010, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0051(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Attack_Term(wk, 0x8068, 0x8048, 8, 0x40, 0, -1, 0x8010, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0052(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Attack_Term(wk, 0x8068, 0x8048, 8, 0x40, 0, -1, 0x8010, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0053(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x17, 0xA);
        break;
    case 2:
        Command_Attack(wk, 8, 1, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0054(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0055(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Command_Attack(wk, 8, 1, 0xA);
        break;
    case 2:
        Command_Attack(wk, 8, 1, 0xA);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0056(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Command_Attack(wk, 8, 1, 0xA);
        break;
    case 2:
        Command_Attack(wk, 8, 1, 0xA);
        break;
    case 3:
        SA_Term(wk, -1, -1, 0x3B, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0057(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x8010, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0058(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x8011, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0059(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x8012, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0060(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0061(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 1, 0xA);
        break;
    case 1:
        SA_Term(wk, -1, -1, 0x3B, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0062(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x39, 0x3A, -1, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Pattern08_0063(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    default:
        End_Pattern(wk);
        break;
    }
}
