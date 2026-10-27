/*
 * plpat10.c  Player 10 (Yang) special attack routines
 *
 * pl10_extra_attack dispatches attack routine numbers 16 and up through pl10_exatt_table; the
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
#include "plpat10.h"


void pl10_extra_attack(PLW* wk) {
    pl10_exatt_table[wk->wu.routine_no[2] - ATTACK_SPECIAL](wk);
}
