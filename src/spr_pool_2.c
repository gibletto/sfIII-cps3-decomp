/*
 * SPR_POOL_2.C  SIMM RAM slot address helpers
 *
 * Conversions from a SIMM RAM slot number to its page offset, address and character code, and the
 * X shift of a sprite list.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "cps3.h"

/* provisional name */
u32 simmram_slot_to_page_offset(s16 slot) {
    return (slot - 1) << 8;
}


/* provisional name */
u32 simmram_slot_addr(s16 slot) {
    return ((slot - 1) << 8) + (SPRITE_RAM + 0x2000);
}



/* provisional name */
u16 simmram_slot_to_code(s16 n) {
    return (u16)(n - 1) * 0x10 + 0x200;
}



/* provisional name */
void sprite_list_shift_x(SPR16* dst, SPR16* src, s16 dx, s32 n) {
    do {
        *dst = *src;
        dst->x += dx;
        src++;
        dst++;
    } while (--n);
}
