/*
 * SC_SUB.C  HUD win marks
 *
 * Per-player HUD pieces drawn on the text layer during a fight. The win mark routines
 * (win_mark_control, win_mark_pos_set, win_mark_new_check, win_mark_write) place one mark per round
 * won and blink a newly won mark using win_mark_blink_tbl. The palette fade control is in sc_sub_2.c
 * and the stun gauge in sc_sub_3.c.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sc_trans.h"
#include "sc_sub_2.h"
#include "sc_sub.h"
#include "cps3.h"

/* win_mark_rno[pl]: the win marks (win_mark_control) */
#define WMARK_INIT      0       /* place the marks, or wait when there are none */
#define WMARK_BLINK     1       /* blink the marks */
#define WMARK_NONE      99      /* (default) no marks: until a new one */



s16 win_mark_rno[2];  /* 02028704 */
s16 win_mark_timer[2];  /* 02028708 */
s16 win_mark_phase[2];  /* 0202870C */
s16 win_mark_num[2];  /* 02028710 */
s16 win_mark_pos[2];  /* 02028714 */


/* provisional name */
void win_mark_control(s16 pl) {
    switch (win_mark_rno[pl]) {
    case WMARK_INIT:
        win_mark_new[pl] = 0;
        if (PL_Wins[pl] == 0) {
            win_mark_rno[pl] = WMARK_NONE;
            return;
        } else {
            win_mark_rno[pl]++;
            win_mark_timer[pl] = 1;
            win_mark_phase[pl] = 0;
            win_mark_pos_set(pl);
        }
        return;
    case WMARK_BLINK:
        if (win_mark_new[pl]) {
            win_mark_new_check(pl);
        }
        if (--win_mark_timer[pl] != 0) {
            return;
        }
        win_mark_write(pl);
        win_mark_timer[pl] = win_mark_blink_tbl[0][win_mark_phase[pl] + 1];
        if (win_mark_phase[pl] != 2) {
            win_mark_phase[pl] += 2;
        } else {
            win_mark_phase[pl] = 0;
        }
        break;
    default:
        if (win_mark_new[pl] != 0) {
            if (win_mark_phase[pl ^ 1] == 0) {
                win_mark_rno[pl] = WMARK_BLINK;
                win_mark_new[pl] = 0;
                win_mark_timer[pl] = 1;
                win_mark_phase[pl] = 0;
                win_mark_pos_set(pl);
            }
        }
        return;
    }
}



/* provisional name */
void win_mark_pos_set(s16 pl) {
    win_mark_num[pl] = PL_Wins[pl] * 2;
    if (pl != 0) {
        win_mark_pos[1] = win_mark_pos_tbl[Game_setting.mode][4];
    } else {
        win_mark_pos[0] = win_mark_pos_tbl[Game_setting.mode][0];
    }
}



/* provisional name */
void win_mark_new_check(pl)
s16 pl;
{
    if (win_mark_phase[pl] == 0) {
        win_mark_new[pl] = 0;
        win_mark_pos_set(pl);
    }
}



/* provisional name */
void win_mark_write(pl)
s16 pl;
{
    u16* cell = (u16*)((SS_RAM + 0x400) + win_mark_pos[pl] * 4);
    s16 n;
    s16 i;
    if (pl == 0) {
        for (n = win_mark_num[pl], i = 0; n > 0; n -= 2, cell -= 4) {
            cell[1] = win_mark_blink_tbl[win_type[pl][i]][win_mark_phase[pl]] | (cell[1] & 1);
            cell[3] = win_mark_blink_tbl[win_type[pl][i]][win_mark_phase[pl]] | (cell[-1] & 1);
            i++;
        }
    } else {
        for (n = win_mark_num[pl], i = 0; n > 0; n -= 2, cell += 4) {
            cell[1] = win_mark_blink_tbl[win_type[pl][i]][win_mark_phase[pl]] | (cell[1] & 1);
            cell[3] = win_mark_blink_tbl[win_type[pl][i]][win_mark_phase[pl]] | (cell[3] & 1);
            i++;
        }
    }
}

