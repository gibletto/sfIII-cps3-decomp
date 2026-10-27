/*
 * PLPAT01.C  Player 01 (Alex) special attack routines
 *
 * pl01_extra_attack dispatches attack routine numbers 16 and up through pl01_exatt_table; the
 * table's entries are the shared routines of PLPATUNI.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLSGAUGE.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "PLPAT.h"
#include "PLS01.h"
#include "PLS02.h"
#include "PLPAT01.h"


void pl01_extra_attack(PLW* wk) {
    pl01_exatt_table[wk->wu.routine_no[2] - ATTACK_SPECIAL](wk);
}
