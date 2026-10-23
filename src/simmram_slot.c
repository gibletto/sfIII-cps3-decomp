/*
 * SIMMRAM_SLOT.C  SIMM RAM slot numbers
 *
 * simmram_slot_to_offset / _to_cg_no turn a SIMM RAM slot number into its byte offset and its character number.
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
u32 simmram_slot_to_offset(s16 slot) {
    return (slot - 1) << 12;
}

/* provisional name */
u16 simmram_slot_to_cg_no(s16 n) {
    return (u16)(n - 1) * 0x20;
}
