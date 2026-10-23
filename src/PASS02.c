/*
 * PASS02.C  CPU passive patterns for character 2 (Ryu)
 *
 * Passive02 is the CPU passive (defensive) routine for character 2, called through
 * Com_Passive's table by character number. It runs the current pattern chosen by Pattern_Index
 * from Passive02_Tbl.
 * The 110 Passive02_xxxx routines are the pattern steps: each is a switch on CP_Index that calls
 * the Com_Sub building blocks (guards, waits for get-up, normal and command attacks, lever
 * releases, reaction terms such as EM_Term) one step at a time and finishes with End_Pattern.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Sub.h"
#include "PASS02.h"



void Passive02(PLW* wk) {
    Passive02_Tbl[Pattern_Index[wk->wu.id]](wk);
}



void Passive02_0000(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xD, M_Lv[wk->wu.id]);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0001(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 1, 0xB);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0002(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x18, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0003(PLW* wk) {
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



void Passive02_0004(PLW* wk) {
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



void Passive02_0005(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0006(PLW* wk) {
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



void Passive02_0007(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8078, -1, 0, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0008(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8078, -1, 0, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0009(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8078, -1, 0, 1, -1);
        break;
    case 1:
        SA_Term(wk, -1, 0x36, -1, 0x47);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0010(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, 0x8058, 0, 1, -1);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x40);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0011(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8030, 8, 0x100, 0, 0x8090, -1, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0012(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8078, 0x8030, 0, 2, 0);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0013(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 1, 0xB);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0014(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        VS_Jump_Guard(wk);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0015(PLW* wk) {
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



void Passive02_0016(PLW* wk) {
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



void Passive02_0017(PLW* wk) {
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



void Passive02_0018(PLW* wk) {
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
        Lever_Attack(wk, 8, 0, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0019(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 1, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0020(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 3, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0021(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x7F, 2);
        break;
    case 1:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0022(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 1:
        Jump_Attack_Term(wk, 0x8070, 0x8040, 8, 0x200, 0, 0x8098, -1, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0023(PLW* wk) {
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



void Passive02_0024(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0xBF, 2);
        break;
    case 1:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 2:
        Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0025(PLW* wk) {
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



void Passive02_0026(PLW* wk) {
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



void Passive02_0027(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xB, 0x102);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0028(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x202);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0029(PLW* wk) {
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



void Passive02_0030(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0031(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Walk(wk, 1, 0x20, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0032(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0033(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Lever_Attack(wk, 8, 0, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0034(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Adjust_Attack(wk, 8, 0x10);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0035(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x82);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0036(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0037(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8008, 0, 1, -1);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0038(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8008, 0, 1, -1);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0039(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8030, 0, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0040(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Pierce_On(wk);
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
    case 4:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0041(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8010, 0, 6, 0x1F);
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



void Passive02_0042(PLW* wk) {
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



void Passive02_0043(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8030, 0, 6, 0x1F);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0044(PLW* wk) {
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



void Passive02_0045(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8010, 0, 6, 0x1F);
        break;
    case 1:
        Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0046(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Status(wk, 2, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0047(PLW* wk) {
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



void Passive02_0048(PLW* wk) {
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



void Passive02_0049(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, -1, 5, 6, 0x1F);
        break;
    case 1:
        Adjust_Attack(wk, 8, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0050(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, -1, 5, 6, 0x1F);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0051(PLW* wk) {
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



void Passive02_0052(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0053(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x18, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0054(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0055(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        J_Command_Attack(wk, 8, 0x18, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0056(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, -1, 0x40, 8, 0x200, 0, 0x8098, -1, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0057(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8038, 8, 0x80, 0, 0x8088, -1, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0058(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Keep_Status(wk, 2, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0059(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, -1, 5, 6, 0x1F);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 9);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0060(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Forced_Guard(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0061(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Get_Up(wk, 0, -1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0062(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 0xB, 0x100);
        break;
    case 1:
        Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0063(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x35, 0x36, -1, 0x47);
        break;
    case 1:
        SA_Term(wk, -1, -1, 0x19, 0x3C);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0064(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x10, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8018, 6, 1, -1);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x40);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0065(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x100);
        break;
    case 2:
        Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0066(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0xBF, 2);
        break;
    case 1:
        SA_Term(wk, 0x35, 0x36, -1, 0x47);
        break;
    case 2:
        SA_Term(wk, -1, -1, 0x19, 0x3C);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0067(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Attack_Complete(wk, 3, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0068(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Attack_Complete(wk, 3, 1);
        break;
    case 1:
        Next_Be_Passive(wk, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0069(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Wait_Attack_Complete(wk, 3, 1);
        break;
    case 1:
        SA_Term(wk, 0x35, -1, 0x37, 0);
        break;
    case 2:
        Wait_Attack_Complete(wk, 3, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0070(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x7F, 2);
        break;
    case 2:
        Wait(wk, 0xA);
        break;
    case 3:
        SA_Term(wk, 0x35, 0x36, -1, 0x47);
        break;
    case 4:
        SA_Term(wk, -1, -1, 0x19, 0x3C);
        break;
    case 1:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 5:
        Wait_Get_Up(wk, 0, -1);
        break;
    case 6:
        Normal_Attack(wk, 8, 0x102);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0071(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x37, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8010, 5, 1, -1);
        break;
    case 2:
        SA_Term(wk, -1, 0x36, -1, 0);
        break;
    case 3:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0072(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x35, -1, -1, 0);
        break;
    case 1:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0073(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x35, -1, 0x37, 0);
        break;
    case 1:
        Adjust_Attack(wk, 0xB, 0x10);
        break;
    case 2:
        Normal_Attack(wk, 0xA, 0x102);
        break;
    case 3:
        Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0074(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, 0x35, 0x36, -1, 0x47);
        break;
    case 1:
        SA_Term(wk, -1, -1, 0x19, 0x3C);
        break;
    case 2:
        Command_Attack(wk, 8, 0x19, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0075(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8040, -1, 5, 6, 0x1F);
        break;
    case 1:
        Normal_Attack(wk, 0xB, 0x12);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0076(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, -1, 5, 6, 0x1C);
        break;
    case 1:
        Lever_Attack(wk, 8, 0, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0077(PLW* wk) {
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



void Passive02_0078(PLW* wk) {
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



void Passive02_0079(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Forced_Guard(wk, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0080(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 9, 0x200, 0, 0x8050, -1, 0x100);
        break;
    case 1:
        Normal_Attack(wk, 9, 0x42);
        break;
    case 2:
        Command_Attack(wk, 0xC, 0x16, 0xA);
        break;
    case 3:
        Wait(wk, 5);
        break;
    case 4:
        SA_Term(wk, 0x35, 0x36, 0x37, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0081(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 9, 0x40, 0, 0x8050, -1, 0x200);
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
        SA_Term(wk, 0x35, 0x36, -1, 0x47);
        break;
    case 5:
        SA_Term(wk, -1, -1, 0x19, 0x3C);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0082(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Approach_Walk(wk, 0x10, 2);
        break;
    case 1:
        EM_Term(wk, -1, 0x8010, 6, 1, -1);
        break;
    case 2:
        Normal_Attack(wk, 9, 0x102);
        break;
    case 3:
        Command_Attack(wk, 0xC, 0x17, 0xA);
        break;
    case 4:
        Wait(wk, 5);
        break;
    case 5:
        SA_Term(wk, 0x35, 0x36, 0x37, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0083(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump(wk, 2);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0084(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, -1, 0x8040, 9, 0x80, 1, 0x8050, -1, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0085(PLW* wk) {
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
        Command_Attack(wk, 8, 0x17, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0086(PLW* wk) {
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



void Passive02_0087(PLW* wk) {
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



void Passive02_0088(PLW* wk) {
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



void Passive02_0089(PLW* wk) {
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



void Passive02_0090(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Command_Attack(wk, 8, 0x17, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0091(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8050, 0x8010, 6, 1, -1);
        break;
    case 1:
        Command_Attack(wk, 0xC, 0x17, 0xA);
        break;
    case 2:
        Wait(wk, 5);
        break;
    case 3:
        SA_Term(wk, 0x35, -1, 0x37, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0092(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8010, 0, 1, -1);
        break;
    case 1:
        Com_Random_Select(wk, 6, 0x60, 0x61, 0x62, 0x63, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0093(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Jump_Attack_Term(wk, 0x8060, 0x8040, 9, 0x40, 0, 0x8050, -1, 0x200);
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
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0094(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, -1, -1, 3, 0x3C);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0095(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, -1, -1, 0xD, 0x3B);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0096(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, -1, -1, 0xF, 0x3C);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0097(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, -1, -1, 0xF, 0);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0098(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, -1, -1, 3, 0x3C);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0099(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        SA_Term(wk, -1, -1, 0x11, 0x3C);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0100(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x8060, 0, 2, 0);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x200);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0101(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x30, 0, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0102(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, -1, 0x30, 0, 1, -1);
        break;
    case 1:
        Jump_Attack_Term(wk, 0x8060, 0x8030, 8, 0x100, 0, 0x8090, -1, 0x20);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0103(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8078, 0x8040, 0, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0104(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8078, 0x8040, 0, 1, -1);
        break;
    case 1:
        J_Command_Attack(wk, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0105(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        EM_Term(wk, 0x8078, 0x8040, 0, 1, -1);
        break;
    case 1:
        SA_Term(wk, -1, 0x36, -1, 0x47);
        break;
    case 2:
        J_Command_Attack(wk, 8, 0x16, 0xA);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0106(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Search_Back_Term(wk, 0x60, 6, 9);
        break;
    case 1:
        Pierce_On(wk);
        break;
    case 2:
        Command_Attack(wk, 8, 1, -1);
        break;
    case 3:
        Com_Random_Select(wk, 6, 0xB, 2, 0xC, 0x5A, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0107(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Com_Random_Select(wk, 6, 7, 0x67, 8, 0x68, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0108(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Com_Random_Select(wk, 6, 9, 0x69, 9, 0x69, 1);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



void Passive02_0109(PLW* wk) {
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
