/*
 * PLPAT08.C  Player 08 (Elena) special attack routines
 *
 * Character-specific attack routines for player number 8. pl08_extra_attack dispatches attack
 * routine numbers 16 and up through pl08_exatt_table.
 * Att_PL08_HEALING runs the healing super art: while the animation plays it restores 1-3 points
 * of vitality per frame (by cg_type) up to full, and a button listed in pl08_hcs_tbl (read from
 * sw_now & 0x3F0) cuts the pose short.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "PLPAT08.h"
#include "PLS02.h"
#include "PLSGAUGE.h"
#include "CALDIR.h"
#include "EFF13_KOTP.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLPAT.h"
#include "PLS01.h"
#include "PLPAT09.h"
#include "cmd_data.h"

/* routine_no[3], Att_PL08_HEALING */
#define HEALING_RUN     1       /* run the animation */


void pl08_extra_attack(PLW* wk) {
    pl08_exatt_table[wk->wu.routine_no[2] - ATTACK_SPECIAL](wk);
}



void Att_PL08_HEALING(PLW* wk) {
    u16 cpsw;
    wk->scr_pos_set_flag = 0;
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        break;
    case HEALING_RUN:
        char_move(&wk->wu);
        if (wk->wu.cmwk[0]) {
            cpsw = (wk->cp->sw_now & CMD_SW_SHOT);
            cpsw >>= 4;
            if (pl08_hcs_tbl[cpsw & 7] || pl08_hcs_tbl[(cpsw & 0x38) >> 3]) {
                wk->wu.cmwk[0] = 0;
                char_move_cmms(&wk->wu);
            }
        }
        if (pcon_dp_flag == 0) {
            switch (wk->wu.cg_type) {
            case 24:
                wk->wu.vital_new += 3;
                break;
            case 22:
                wk->wu.vital_new += 2;
                break;
            case 20:
                wk->wu.vital_new += 1;
            default:
                break;
            }
        }
        if (wk->wu.vital_new > wk->wu.vitality) {
            wk->wu.vital_new = wk->wu.vitality;
        }
        break;
    }
}
