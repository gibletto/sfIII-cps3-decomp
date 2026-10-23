/*
 * DEMO_TBL.C  tables read by Game_Main.c: the bookkeeping screen's labels
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s8 Game_Data_msg[];
extern const s8 Income_msg[];
extern const s8 Service_msg[];
extern const s8 Card_msg[];

const s8 Game_Data_msg[12] = "GAME DATA\0\xD3\x23";

const s8 Income_msg[8] = "INCOME";

const s8 Service_msg[8] = "SERVICE";

const s8 Card_msg[5] = "CARD";
