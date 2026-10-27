/*
 * END_MAIN_TBL_C.C  ending type table
 *
 * end_type_tbl gives, per ending character, which of the two colour and fade sets the ending
 * uses (its colour load, the fade that closes the scenes and the fade into the staff roll).
 * Read by END_MAIN_C.C, the ending main control.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s8 end_type_tbl[];

const s8 end_type_tbl[16] = {
    0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
};
