/*
 * PASS11.C  CPU passive patterns for character 11 (Ken)
 *
 * Passive11 is the CPU passive (defensive) routine for character 11, called through
 * Com_Passive's table by character number. It runs the current pattern chosen by Pattern_Index
 * from Passive11_Tbl.
 * The 231 Passive11_xxxx routines are the pattern steps: each is a switch on CP_Index that calls
 * the Com_Sub building blocks (guards, waits for get-up, normal and command attacks, lever
 * releases, reaction terms such as EM_Term) one step at a time and finishes with End_Pattern.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Sub.h"
#include "PASS11.h"



void Passive11(PLW* wk) {
    Passive11_Tbl[Pattern_Index[wk->wu.id]](wk);
}



void Passive11_0000(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0x8B, M_Lv[wk->wu.id]);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0001(PLW* wk) {
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



void Passive11_0002(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 0xB, 0xE, 0xA);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0003(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, 0x28, 7, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0004(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8090, 0x28, 7, 1, -1);
        break;
    case 1:
        SA_Term(wk, -1, 0x31, -1, 0x47);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0005(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 0xB, 0xE, 0xA);
        break;
    case 1:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x47);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0006(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
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



void Passive11_0007(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8008, 6, 1, -1);
        break;
    case 2:
        Lever_Attack(wk, 8, 0, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0008(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8008, 6, 1, -1);
        break;
    case 2:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0009(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8020, 6, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0010(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8010, 6, 1, -1);
        break;
    case 2:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 3:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0011(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0012(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0013(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0014(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x80);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0015(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack_SP(wk, 8, 0x100, 0x12);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0016(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0017(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0018(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0019(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8018, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x20);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0020(PLW* wk) {
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



void Passive11_0021(PLW* wk) {
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



void Passive11_0022(PLW* wk) {
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



void Passive11_0023(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0024(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0025(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0026(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0027(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0028(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0029(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        J_Command_Attack(wk, 0xB, 0x18, 0xA);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0030(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 2:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0031(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x10);
        break;
    case 2:
        Lever_Attack(wk, 9, 0, 0x100);
        break;
    case 3:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0032(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x10);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x20);
        break;
    case 3:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0033(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0034(PLW* wk) {
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



void Passive11_0035(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0036(PLW* wk) {
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



void Passive11_0037(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0038(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8080, -1, 6, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0039(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8080, -1, 6, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0040(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8080, -1, 6, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0041(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8080, -1, 6, 1, -1);
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



void Passive11_0042(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Forced_Guard(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0043(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Command_Attack_Term(wk, 8, 0x18, 0xA, -1, 0x30, 0, -1, -1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0044(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x38, 8, 0x200, 2, -1, -1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0045(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8018, 6, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0046(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8018, 6, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0047(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8018, 6, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0048(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0049(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x80);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0050(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x10);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0051(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Hi_Jump_Attack_Term(wk, 0x8060, 0x8030, 8, 0x40, 0, -1, -1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0052(PLW* wk) {
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



void Passive11_0053(PLW* wk) {
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



void Passive11_0054(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 3, -1);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0055(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0056(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x20);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0057(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 3, -1);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x22);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0058(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0059(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0060(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0061(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Lie(wk, 0);
        break;
    case 1:
        Approach_Walk(wk, 0x47, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0062(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 3, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0063(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Turn_Over_On(wk);
        break;
    case 1:
        Wait_Get_Up(wk, 0, 0);
        break;
    case 2:
        Search_Back_Term(wk, 0xE0, 6, 0x42);
        break;
    case 3:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x100, 0, 0x8050, -1, 0x100);
        break;
    case 4:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 5:
        Normal_Attack(wk, 8, 0x82);
        break;
    case 6:
        Normal_Attack(wk, 8, 0x102);
        break;
    case 7:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0064(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0065(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, 0);
        break;
    case 1:
        Search_Back_Term(wk, 0xE0, 6, 0x42);
        break;
    case 2:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 0xB, 0x100, 0, 0x8050, -1, 0x200);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0066(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, 0);
        break;
    case 1:
        Branch_Wait_Area(wk, 0x14, 0xF, 5, 1);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0067(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, 0);
        break;
    case 1:
        Branch_Wait_Area(wk, 0x14, 0xF, 5, 1);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0068(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Lie(wk, 0);
        break;
    case 1:
        Approach_Walk(wk, 0x7F, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0069(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0070(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, 0);
        break;
    case 1:
        Search_Back_Term(wk, 0xE0, 6, 0x42);
        break;
    case 2:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 0xB, 0x200, 0, 0x8050, -1, 0x100);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0071(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Lie(wk, 0);
        break;
    case 1:
        Jump(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0072(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Lie(wk, 0);
        break;
    case 1:
        Approach_Walk(wk, 0xBF, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0073(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 3, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0074(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8040, 0x8010, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x80);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0075(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, 0x8040, 0, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x82);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0076(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0077(PLW* wk) {
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



void Passive11_0078(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0xE, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0079(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Command_Attack(wk, 8, 0, -1);
        break;
    case 2:
        Branch_Unit_Area(wk, 6, 0x53, 0x2F, 0x24, 0x25);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0080(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x100, 0, 0x8050, -1, 0x20);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x102);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0081(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 0xB, 0x100, 0, 0x8050, -1, 0x40);
        break;
    case 1:
        EM_Term(wk, 0x8057, 0x8000, 4, 6, 0x94);
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



void Passive11_0082(PLW* wk) {
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
        Com_Random_Select(wk, 2, 0x2D, 0x94, 0x94, 0xFF, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0083(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0084(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0085(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0086(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0xBF, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0087(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0088(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0089(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Command_Attack(wk, 0xC, 0, -1);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0090(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0091(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Lever_Attack(wk, 0xC, 0, 0x100);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0092(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Lever_Attack(wk, 0xC, 0, 0x100);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0093(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8080, 0x28, 7, 1, -1);
        break;
    case 1:
        Lever_Attack(wk, 9, 0, 0x100);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0094(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0095(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0096(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0097(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8018, 6, 1, -1);
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



void Passive11_0098(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0099(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0100(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0101(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x102);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0102(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 0xB, 0x100, 0, -1, -1, -1);
        break;
    case 1:
        EM_Term(wk, 0x8057, 0x8000, 4, 6, 0x94);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0103(PLW* wk) {
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



void Passive11_0104(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x202);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0105(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8018, 6, 1, -1);
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



void Passive11_0106(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 8, 0x100, 0, -1, -1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0107(PLW* wk) {
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



void Passive11_0108(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8038, 6, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0109(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8038, 0, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0110(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x20);
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



void Passive11_0111(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x20);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0112(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x7F, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0113(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Normal_Attack_SP(wk, 8, 0x100, 0x12);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0114(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x100, 0, 0x8050, -1, 0x20);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x102);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0115(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 0xB, 0x100, 0, 0x8050, -1, 0x20);
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



void Passive11_0116(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Forced_Guard(wk, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0117(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0118(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0119(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 1:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0120(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x12);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0121(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8018, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x82);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0122(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0123(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0124(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x82);
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



void Passive11_0125(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xB, 0x82);
        break;
    case 1:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0126(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x102);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0127(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 1:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x100, 0, 0x8050, -1, 0x20);
        break;
    case 2:
        Normal_Attack(wk, 0xB, 0x12);
        break;
    case 3:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 4:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0128(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 1:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 0xB, 0x100, 0, -1, -1, -1);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0129(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 1:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x20, 0, 0x8050, -1, 0x100);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x12);
        break;
    case 3:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 4:
        Normal_Attack(wk, 8, 0x102);
        break;
    case 5:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0130(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x80);
        break;
    case 1:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 0xB, 0x100, 0, 0x8050, -1, 0x40);
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



void Passive11_0131(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0132(PLW* wk) {
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



void Passive11_0133(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 0xB, 0x100, 0, 0x8050, -1, 0x40);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x200);
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



void Passive11_0134(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x20, 0, 0x8050, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x40);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0135(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8018, 6, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0136(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8040, 6, 1, -1);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0137(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0138(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0139(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0140(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
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



void Passive11_0141(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, 0);
        break;
    case 1:
        Branch_Wait_Area(wk, 0x14, 0xF, 5, 1);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0142(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8040, 6, 1, -1);
        break;
    case 2:
        Command_Attack(wk, 0xC, 0x17, 0xA);
        break;
    case 3:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0143(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8010, 6, 1, -1);
        break;
    case 2:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 3:
        Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0144(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8008, 6, 1, -1);
        break;
    case 2:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 3:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 4:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0145(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8008, 6, 1, -1);
        break;
    case 2:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 3:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 4:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0146(PLW* wk) {
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



void Passive11_0147(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0148(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0149(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Command_Attack(wk, 8, 0, -1);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 3:
        Normal_Attack(wk, 9, 0x102);
        break;
    case 4:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0150(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0151(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Command_Attack(wk, 8, 0, -1);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 3:
        Normal_Attack(wk, 0xB, 0x82);
        break;
    case 4:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 5:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0152(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x100);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0xA9, 0xA8, 0xB9, 0x86, 3);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0153(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
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



void Passive11_0154(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Away(wk, 0xBF, 0);
        break;
    case 1:
        Wait_Get_Up(wk, 0, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0155(PLW* wk) {
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



void Passive11_0156(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Away(wk, 0xBF, 0);
        break;
    case 1:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0157(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0158(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0159(PLW* wk) {
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



void Passive11_0160(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x100, 0, 0x8050, -1, 0x20);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x102);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0161(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 0xB, 0x100, 0, 0x8050, -1, 0x40);
        break;
    case 1:
        EM_Term(wk, -1, 0x8000, 4, 1, -1);
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



void Passive11_0162(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x10);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0163(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x100, 0, 0x8050, -1, 0x100);
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
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    case 5:
        Com_Random_Select(wk, 6, 0x2D, 0xFF, 0xFF, 0xFF, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0164(PLW* wk) {
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



void Passive11_0165(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 9, 0x200, 0, 0x8050, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x202);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0166(PLW* wk) {
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



void Passive11_0167(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 9, 0x200, 0, 0x8050, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x202);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0168(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x20, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0169(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0170(PLW* wk) {
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



void Passive11_0171(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Away(wk, 0xBF, 0);
        break;
    case 1:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0172(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Away(wk, 0x50, 3);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0x3F, 0x40, 0x41, 0x43, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0173(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x100, 0, 0x8050, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x82);
        break;
    case 3:
        Normal_Attack(wk, 8, 0x102);
        break;
    case 4:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    case 5:
        Com_Random_Select(wk, 6, 0x2D, 0xFF, 0xFF, 0xFF, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0174(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8010, 6, 1, -1);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x40);
        break;
    case 3:
        Command_Attack(wk, 0xC, 0x17, 0xA);
        break;
    case 4:
        Wait(wk, 5);
        break;
    case 5:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0175(PLW* wk) {
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



void Passive11_0176(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 2:
        Normal_Attack(wk, 0xB, 0x100);
        break;
    case 3:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    case 4:
        Com_Random_Select(wk, 6, 0x2D, 0xFF, 0xFF, 0xFF, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0177(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x100);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    case 3:
        Com_Random_Select(wk, 6, 0x2D, 0xFF, 0xFF, 0xFF, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0178(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 9, 0x40, 0, 0x8050, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x40);
        break;
    case 2:
        J_Command_Attack(wk, 0xC, 0x16, 0xA);
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



void Passive11_0179(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0180(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    case 1:
        Command_Attack(wk, 0xC, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0181(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    case 2:
        Command_Attack(wk, 0xC, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0182(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x47, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0183(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 9, 0x40, 0, 0x8050, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x40);
        break;
    case 2:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0184(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x100, 0, 0x8050, -1, 0x100);
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
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    case 5:
        Com_Random_Select(wk, 6, 0x2D, 0xFF, 0xFF, 0xFF, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0185(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8018, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0186(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0x2D, 0xFF, 0xFF, 0xFF, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0187(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x17, 9);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0x2D, 0xFF, 0xFF, 0xFF, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0188(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0x2D, 0xFF, 0xFF, 0xFF, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0189(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8090, 0x28, 7, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0190(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8090, 0x28, 7, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0191(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x60, 2);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0x3F, 0x40, 0x41, 0x43, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0192(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Away(wk, 0xBF, 1);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0xBA, 1, 0xAF, 0x92, 3);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0193(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x20, -1);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0xBA, 1, 0xAF, 0x92, 3);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0194(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x100);
        break;
    case 1:
        Com_Random_Select(wk, 6, 1, 1, 0xC0, 0xC0, 4);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0195(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x200);
        break;
    case 1:
        Com_Random_Select(wk, 6, 1, 1, 0xC0, 0xC0, 4);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0196(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8090, 0x28, 7, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0197(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8090, 0x28, 7, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0198(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        VS_Jump_Guard(wk);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0199(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xC, 0x40);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0200(PLW* wk) {
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



void Passive11_0201(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 9, 0x40);
        break;
    case 1:
        Command_Attack(wk, 0xC, 0x17, 0xA);
        break;
    case 2:
        Wait(wk, 5);
        break;
    case 3:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0202(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8018, 6, 1, -1);
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



void Passive11_0203(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x14, -1);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0xC6, 0xC4, 0xC5, 0x2F, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0204(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Search_Back_Term(wk, 0x60, 6, 0x2F);
        break;
    case 1:
        Pierce_On(wk);
        break;
    case 2:
        Command_Attack(wk, 8, 1, -1);
        break;
    case 3:
        Com_Random_Select(wk, 6, 0x51, 0x1C, 0x4D, 0x25, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0205(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 0xB, 0xE, 0xA);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x82);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x102);
        break;
    case 3:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0206(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Away(wk, 0xBF, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0207(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Jump(wk, 0);
        break;
    case 2:
        Com_Random_Select(wk, 6, 0x53, 0x54, 0x13, 0x25, 4);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0208(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Jump(wk, 0);
        break;
    case 2:
        Com_Random_Select(wk, 6, 0x53, 0x54, 1, 0x25, 3);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0209(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0210(PLW* wk) {
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



void Passive11_0211(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x10, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8010, 6, 1, -1);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x40);
        break;
    case 3:
        J_Command_Attack(wk, 0xC, 0x16, 0xA);
        break;
    case 4:
        Wait(wk, 5);
        break;
    case 5:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0212(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x10, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8018, 6, 1, -1);
        break;
    case 2:
        J_Command_Attack(wk, 0xC, 0x16, 0xA);
        break;
    case 3:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0213(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 1:
        Next_Another_Menu(wk, 6, 0x73);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0214(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x100, 0, 0x8050, -1, 0x40);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x102);
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



void Passive11_0215(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0216(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x100, 0, 0x8050, -1, 0x20);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x102);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0217(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8058, 0x8040, 9, 0x20, 0, 0x8050, -1, 0x100);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0218(PLW* wk) {
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



void Passive11_0219(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Command_Attack(wk, 8, 0, -1);
        break;
    case 2:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 3:
        Normal_Attack(wk, 0xC, 0x102);
        break;
    case 4:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 5:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0220(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
        break;
    case 1:
        Command_Attack(wk, 8, 0, -1);
        break;
    case 2:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 3:
        Normal_Attack(wk, 9, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0221(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8008, 6, 1, -1);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        Lever_Attack(wk, 8, 0, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0222(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8008, 6, 1, -1);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        Lever_Attack(wk, 8, 0, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0223(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8008, 6, 1, -1);
        break;
    case 2:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 3:
        Lever_Attack(wk, 8, 0, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0224(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8020, 6, 1, -1);
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



void Passive11_0225(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0226(PLW* wk) {
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
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0227(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0228(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0229(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive11_0230(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 6, 1, -1);
        break;
    case 1:
        SA_Term(wk, 0x30, 0x31, 0x32, 0x7F);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x200);
        break;
    case 3:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}
