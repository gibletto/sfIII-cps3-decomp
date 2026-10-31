/*
 * FOLLOW01.C  Unused follow-up table
 *
 * Follow01 runs the Follow01_xxxx entries of Follow01_Tbl, a four-entry follow-up table like the
 * one in FOLLOW02.C. Nothing calls it.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Sub.h"
#include "FOLLOW01.h"



/* provisional name */
void Follow01(PLW* wk) {
    Follow01_Tbl[Pattern_Index[wk->wu.id]](wk);
}



/* provisional name */
void Follow01_0000(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



/* provisional name */
void Follow01_0001(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 1:
        Command_Attack(wk, 2, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



/* provisional name */
void Follow01_0002(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x10);
        break;
    case 1:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 2:
        Normal_Attack(wk, 8, 0x100);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}



/* provisional name */
void Follow01_0003(PLW* wk) {
    switch (CP_Index[wk->wu.id][0]) {
    case 0:
        Normal_Attack(wk, 8, 0x20);
        break;
    case 1:
        Command_Attack(wk, 2, 8, 0x16, 8);
        break;
    default:
        End_Pattern(wk);
        break;
    }
}
