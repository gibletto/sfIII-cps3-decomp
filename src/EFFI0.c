/*
 * EFFI0.C  Effect H9: an empty effect
 *
 * effect_H9_move and effect_H9_init, the last entries of effmovejptbl and effinitjptbl, do nothing
 * and return 0.
 */

#include "structs.h"
#include "work.h"
#include "EFFI0.h"



s32 effect_H9_move(void) {
    return 0;
}



s32 effect_H9_init(void) {
    return 0;
}
