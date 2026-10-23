/*
 * SEL_PL_WORK.C  player select work
 *
 * The character selection screen's position, super art plate positions, demonstration lever pointers and shot flags
 * (section B).
 */

#include "types.h"
#include "structs.h"

s16 SEL_PL_X;  /* 020138F4 */
s16 Sel_Arts_Pos[2];  /* 020138F6 */
s8* Demo_Ptr[2];  /* 020138FC */
s8 Sel_Char_Shot[2];  /* 02013904 */
/* after Sel_Char_Shot: nothing refers to it by name or address */
u8 Sel_Char_Shot_tail[2];  /* 02013906 */
