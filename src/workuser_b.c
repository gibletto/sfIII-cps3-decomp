/*
 * WORKUSER_B.C  game work, continued
 *
 * The super art selection timer and position and Last_VS_Index (section B).
 */

#include "types.h"
#include "structs.h"

s16 Sel_Tech_No;  /* 020138D0 */
/* after Sel_Tech_No: nothing refers to it by name or address */
u8 Sel_Tech_No_tail[6];  /* 020138D2 */
s16 Sel_Tech_Timer;  /* 020138D8 */
s16 Sel_Tech_X;  /* 020138DA */
s16 Last_VS_Index[2];  /* 020138DC */
