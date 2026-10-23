/*
 * PLPAT06.C  Player 06 special attack routines
 *
 * pl06_extra_attack dispatches attack routine numbers 16 and up through pl06_exatt_table. Player 6
 * is not playable: the table holds Att_DUMMY.
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
#include "PLS01.h"
#include "PLPAT06.h"


void pl06_extra_attack(PLW* wk) {
    pl06_exatt_table[wk->wu.routine_no[2] - 16](wk);
}
