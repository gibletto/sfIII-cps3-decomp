/*
 * CHARID.C  Character base data setup
 *
 * set_char_base_data loads a work's character data pointers from the char_init_data entry
 * selected by charset_id: the ten cg script tables (normal, damage, catch, caught, attack,
 * super art, ...), step and move tables, overlap tables, the body/attack/caught/hosei judgement
 * tables and the colour, priority and family settings. Called when players and character-based
 * effects are initialised. set_char_base_data_init is its companion for a work that is being
 * initialised (it leaves the priority alone).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARID.h"


void set_char_base_data(WORK* wk) {
    const CHAR_INIT_ROM* cdat = &char_init_data[wk->charset_id];
    wk->char_table[0] = cdat->nmca;
    wk->char_table[1] = cdat->dmca;
    wk->char_table[6] = cdat->btca;
    wk->char_table[2] = cdat->caca;
    wk->char_table[3] = cdat->cuca;
    wk->char_table[4] = cdat->atca;
    wk->char_table[5] = cdat->saca;
    wk->char_table[7] = cdat->exca;
    wk->char_table[8] = cdat->cbca;
    wk->char_table[9] = cdat->yuca;
    wk->step_xy_table = cdat->stxy;
    wk->move_xy_table = (s16*)cdat->mvxy;
    wk->overlap_char_tbl = cdat->ovct;
    wk->olc_ix_table = cdat->ovix;
    wk->rival_catch_tbl = cdat->rict;
    wk->hit_ix_table = cdat->hiit;
    wk->body_adrs = cdat->boda;
    wk->attack_adrs = cdat->atta;
    wk->caught_adrs = cdat->caua;
    wk->hosei_adrs = cdat->hosa;
    wk->att_ix_table = cdat->atit;
    wk->cgromtype = cdat->cgromtype;
    wk->my_col_mode = cdat->my_cm;
    wk->my_col_code = cdat->my_cc;
    wk->my_priority = cdat->my_pr;
    wk->my_family = cdat->my_fm;
    wk->my_ext_pri = cdat->my_ep;
    wk->position_z = wk->my_priority;
}

/* provisional name */
void set_char_base_data_init(WORK* wk) {
    const CHAR_INIT_ROM* cdat = &char_init_data[wk->charset_id];
    wk->char_table[0] = cdat->nmca;
    wk->char_table[1] = cdat->dmca;
    wk->char_table[6] = cdat->btca;
    wk->char_table[2] = cdat->caca;
    wk->char_table[3] = cdat->cuca;
    wk->char_table[4] = cdat->atca;
    wk->char_table[5] = cdat->saca;
    wk->char_table[7] = cdat->exca;
    wk->char_table[8] = cdat->cbca;
    wk->char_table[9] = cdat->yuca;
    wk->step_xy_table = cdat->stxy;
    wk->move_xy_table = (s16*)cdat->mvxy;
    wk->overlap_char_tbl = cdat->ovct;
    wk->olc_ix_table = cdat->ovix;
    wk->rival_catch_tbl = cdat->rict;
    wk->hit_ix_table = cdat->hiit;
    wk->body_adrs = cdat->boda;
    wk->attack_adrs = cdat->atta;
    wk->caught_adrs = cdat->caua;
    wk->hosei_adrs = cdat->hosa;
    wk->att_ix_table = cdat->atit;
    wk->cgromtype = cdat->cgromtype;
    wk->my_col_mode = cdat->my_cm;
    wk->my_col_code = cdat->my_cc;
    wk->my_family = cdat->my_fm;
    wk->my_ext_pri = cdat->my_ep;
}
