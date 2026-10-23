/*
 * PLPAT11.C  Player 11 (Ken) special attack routines
 *
 * pl11_extra_attack dispatches attack routine numbers 16 and up through pl11_exatt_table; the
 * table's entries are the shared routines of PLPATUNI.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLS02.h"
#include "PLSGAUGE.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "PLPAT.h"
#include "PLPAT11.h"
#include "plpat10.h"


void pl11_extra_attack(PLW* wk) {
    pl11_exatt_table[wk->wu.routine_no[2] - 16](wk);
}
