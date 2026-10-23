/*
 * PLPAT02.C  Player 02 (Ryu) special attack routines
 *
 * pl02_extra_attack dispatches attack routine numbers 16 and up through pl02_exatt_table; the
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
#include "PLPAT02.h"


void pl02_extra_attack(PLW* wk) {
    pl02_exatt_table[wk->wu.routine_no[2] - 16](wk);
}
