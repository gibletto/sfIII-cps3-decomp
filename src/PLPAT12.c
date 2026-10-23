/*
 * PLPAT12.C  Player 12 (Sean) special attack routines
 *
 * pl12_extra_attack dispatches attack routine numbers 16 and up through pl12_exatt_table; the
 * table's entries are the shared routines of PLPATUNI.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLSGAUGE.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "effd6_code.h"
#include "EFFD7.h"
#include "PLPAT.h"
#include "PLS01.h"
#include "PLS02.h"
#include "PLPAT12.h"


void pl12_extra_attack(PLW* wk) {
    pl12_exatt_table[wk->wu.routine_no[2] - 16](wk);
}
