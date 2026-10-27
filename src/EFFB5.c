/*
 * EFFB5.C  Effect B5: name-entry letters (move)
 *
 * Each of the three B5 works shows one letter of a player's ranking name entry; the master is
 * the player's name-entry work (name_wk). effect_B5_move shows the letter chosen in np->code,
 * blinks the letter under the cursor (current_name_move, alternating with the cursor pattern
 * every 16 frames), fixes the letter with naming_set when that position is entered, redraws it
 * when the code changes, and colour-flashes the name when the entry is complete (r_no_0 == 7).
 * The init, effect_B5_init, is in EFFB5_INIT.C and is called from n_input.c.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Eff51.h"
#include "ta_sub.h"
#include "sc_trans.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFB5.h"

/* routine_no[0] */
#define R0_INIT         0       /* show the chosen letter */
#define R0_INPUT        1       /* blink under the cursor until entered */
#define R0_FIXED        2       /* entered: redraw when it changes */
#define R0_FLASH        3       /* flash the finished name */
#define R0_HOLD         4       /* stay as it is */



void effect_B5_move(WORK_Other* ewk) {
    NAME_WK* np = (NAME_WK*)ewk->my_master;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.hit_stop = 0;
        ewk->wu.old_rno[3] = 0;
        ewk->wu.old_rno[1] = 47;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, 6, np->code[ewk->wu.old_rno[2]] + 1, 0);
    case R0_INPUT:
    case_1:
        if (np->end_flag[ewk->wu.type]) {
            ewk->wu.disp_flag = 1;
            set_char_move_init2(&ewk->wu, 0, 6, np->code[ewk->wu.old_rno[2]] + 1, 0);
            naming_set(np->id, ewk->wu.type, np->code[ewk->wu.old_rno[2]]);
            ewk->wu.routine_no[0]++;
        } else {
            current_name_move(ewk, np);
        }
        break;
    case R0_FIXED:
        if (np->r_no_0 == 7) {
            ewk->wu.routine_no[0] = R0_FLASH;
            ewk->wu.routine_no[2] = 1;
            ewk->wu.routine_no[3] = 3;
            ewk->wu.routine_no[4] = 0;
            ewk->wu.vitality = 0;
            ewk->wu.vital_new = 66;
            ewk->wu.vital_old = 67;
        }
        if (np->end_flag[ewk->wu.type] == 0) {
            ewk->wu.old_rno[0] = 0;
            ewk->wu.old_rno[4] = 0;
            ewk->wu.routine_no[0] = R0_INPUT;
            set_char_move_init2(&ewk->wu, 0, 6, np->code[ewk->wu.old_rno[2]] + 1, 0);
            ewk->wu.old_rno[3] = np->code[np->index];
            naming_set(np->id, ewk->wu.type, np->code[ewk->wu.old_rno[2]]);
            goto case_1;
        }
        if (ewk->wu.old_rno[3] != np->code[ewk->wu.type]) {
            ewk->wu.old_rno[0] = 0;
            ewk->wu.old_rno[4] = 1;
            set_char_move_init2(&ewk->wu, 0, 6, np->code[ewk->wu.old_rno[2]] + 1, 0);
            naming_set(np->id, ewk->wu.type, np->code[ewk->wu.old_rno[2]]);
            ewk->wu.old_rno[3] = np->code[ewk->wu.type];
        }
        break;
    case R0_FLASH:
        if (Flash_Violent(ewk, 9)) {
            ewk->wu.routine_no[0]++;
        }
        if (ewk->wu.vitality) {
            set_char_move_init2(&ewk->wu, 0, 6, np->code[ewk->wu.old_rno[2]] + 1, 0);
        }
        break;
    case R0_HOLD:
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work(&ewk->wu);
        break;
    }
    if (ewk->wu.old_rno[3] != np->code[ewk->wu.type]) {
        ewk->wu.old_rno[4] = 0;
        ewk->wu.old_rno[0] = 0;
        set_char_move_init2(&ewk->wu, 0, 6, np->code[ewk->wu.type] + 1, 0);
        naming_set(np->id, ewk->wu.type, np->code[ewk->wu.old_rno[2]]);
        ewk->wu.old_rno[3] = np->code[ewk->wu.type];
    }
    disp_pos_trans_entry(ewk);
}

void current_name_move(WORK_Other* ewk, NAME_WK* np)
{
    if (np->index != ewk->wu.old_rno[2]) {
        return;
    }
    switch (ewk->wu.hit_stop) {
    case 0:
        ewk->wu.hit_stop++;
        ewk->wu.old_rno[4] = 0;
        ewk->wu.old_rno[0] = 0;
        set_char_move_init2(&ewk->wu, 0, 6, np->code[ewk->wu.old_rno[2]] + 1, 0);
        ewk->wu.old_rno[3] = np->code[np->index];
        break;
    case 1:
        if (np->r_no_0 > 5) {
            ewk->wu.routine_no[0]++;
        } else {
            ewk->wu.old_rno[0]++;
            if (ewk->wu.old_rno[0] > 16) {
                ewk->wu.old_rno[0] = 0;
                ewk->wu.old_rno[4]++;
                if (ewk->wu.old_rno[4] > 2) {
                    ewk->wu.old_rno[4] = 0;
                }
                if (ewk->wu.old_rno[4] != 2) {
                    set_char_move_init2(&ewk->wu, 0, 6, np->code[np->index] + 1, 0);
                } else {
                    set_char_move_init2(&ewk->wu, 0, 6, 48, 0);
                }
            }
        }
        break;
    }
}
