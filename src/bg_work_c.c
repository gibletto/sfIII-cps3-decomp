/*
 * BG_WORK_C.C  background work, continued
 *
 * The work of effects 50 and A0 (section B).
 */

#include "types.h"
#include "structs.h"

u8 eff50_slide_out;  /* 0205E0CC */
/* after eff50_slide_out: nothing refers to it by name or address */
u8 eff50_slide_out_tail[11];  /* 0205E0CD */
s16 effA0_timer[3];  /* 0205E0D8 */
s16 effA0_count[3];  /* 0205E0DE */
s16 effA0_remaining[3];  /* 0205E0E4 */
/* after effA0_remaining: nothing refers to it by name or address */
u8 effA0_remaining_tail[2];  /* 0205E0EA */
