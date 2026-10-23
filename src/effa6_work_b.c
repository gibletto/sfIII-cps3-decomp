/*
 * EFFA6_WORK_B.C  effect A6 work, continued
 *
 * The line scroll mode (section B).
 */

#include "types.h"
#include "structs.h"

s16 line_scroll_mode;  /* 0205E104 */
/* after line_scroll_mode: nothing refers to it by name or address */
u8 line_scroll_mode_tail[2];  /* 0205E106 */
