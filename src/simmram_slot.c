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

#define SIMM_SLOT_SHIFT 12      /* 4 KB slots, numbered from 1 */
#define SIMM_SLOT_CG    0x20    /* character numbers per slot */

/* provisional name */
u32 simmram_slot_to_offset(s16 slot) {
    return (slot - 1) << SIMM_SLOT_SHIFT;
}

/* provisional name */
u16 simmram_slot_to_cg_no(s16 n) {
    return (u16)(n - 1) * SIMM_SLOT_CG;
}
