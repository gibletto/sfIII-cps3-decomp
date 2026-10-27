/*
 * DEMO_TBL.C  operator information headings
 *
 * Game_Data_msg, Income_msg, Service_msg and Card_msg are the headings GAME DATA, INCOME,
 * SERVICE and CARD shown to the operator in some countries while 1P light punch is held. Read
 * by GAME_MAIN.C, the game phase dispatcher.
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
