/*
 * BG_WORK_B.C  background work, continued
 *
 * The effect BG addresses (section B).
 */

#include "types.h"
#include "structs.h"

BG_ADRS eff_bg_adrs[6];  /* 0205DF3C */
/* after eff_bg_adrs: nothing refers to it by name or address */
u8 eff_bg_adrs_tail[32];  /* 0205DF6C */
