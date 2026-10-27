/*
 * EFF79_TBL.C  centre-screen message times
 *
 * Time_Data gives the time each requested message stays on the screen, indexed by
 * request_message. Read by EFF84.C, the centre-screen message controller.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s8 Time_Data[];

const s8 Time_Data[8] = "PZ222";
