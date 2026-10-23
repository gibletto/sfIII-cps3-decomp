/*
 * PLPAT05.C  Player 05 (Necro) special attack routines
 *
 * pl05_extra_attack dispatches attack routine numbers 16 and up through pl05_exatt_table; the
 * table's entries are the shared routines of PLPATUNI.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLSGAUGE.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "PLPAT.h"
#include "PLPAT05.h"


void pl05_extra_attack(PLW* wk) {
    pl05_exatt_table[wk->wu.routine_no[2] - 16](wk);
}
