/*
 * EFFD9.C  Effect D9: palette change controller for a player
 *
 * effect_D9_init is called by player code (PLPDM.c, PLPCU.c, EFF41.c) with an entry number in
 * color_table_index. effect_D9_move reads the entry's 1P or 2P colour-step table, flag bits and
 * timer, then cycles the player's extra_col (or extra_col_2) through the table each frame.
 * The flags end the effect when the timer runs out, when the player's damage count, pattern or
 * landing changes, when the super art is no longer active, or when the player's move changes;
 * on ending it clears the player's extra colour and frees the work.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFD9.h"

/* routine_no[0] */
#define R0_INIT         0       /* read the colour table entry */
#define R0_MOVE         1       /* cycle the player's colour */
#define R0_KILL         2       /* clear the colour, free the work */



void effect_D9_move(WORK_Other* ewk) {
    PLW* mwk;
    const ColorTableIndex* t, *r;

    mwk = (PLW*)ewk->my_master;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        t = color_table_index;
        r = t;
        if (ewk->master_id) {
            r += ewk->wu.direction;
            ewk->wu.step_xy_table = r->changetbl_2p;
        } else {
            r += ewk->wu.direction;
            ewk->wu.step_xy_table = r->changetbl_1p;
        }
        ewk->wu.vital_old = t[ewk->wu.direction].flag;
        ewk->wu.dir_timer = t[ewk->wu.direction].timer;
        ewk->wu.dir_step = 0;
        ewk->wu.vitality = 0;
        break;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if ((ewk->wu.vital_old & 2) && EXE_flag == 0 && Game_pause == 0) {
            if (--ewk->wu.dir_timer < 0) {
                ewk->wu.routine_no[0] = 3;
                break;
            }
        }
        if (ewk->wu.vital_old & 4) {
            if (ewk->wu.dir_old != mwk->wu.dm_count_up) {
                ewk->wu.routine_no[0] = 3;
                break;
            }
            if (ewk->wu.type != 0 && ewk->wu.type != 32) {
                if (mwk->wu.xyz[1].disp.pos <= 0) {
                    ewk->wu.routine_no[0] = 3;
                    break;
                }
            } else {
                if (mwk->wu.cg_type != 0) {
                    ewk->wu.routine_no[0] = 3;
                    break;
                }
            }
        }
        if ((ewk->wu.vital_old & 8) && mwk->sa->ok != -1) {
            ewk->wu.routine_no[0] = 3;
            break;
        }
        if (--ewk->wu.vitality <= 0) {
            ewk->wu.dir_step += 2;
            if (((const ColorStep*)(ewk->wu.step_xy_table + ewk->wu.dir_step))->timer == 0) {
                ewk->wu.dir_step = 0;
            }
            ewk->wu.vitality = ((const ColorStep*)(ewk->wu.step_xy_table + ewk->wu.dir_step))->timer;
            ewk->wu.vital_new = ((const ColorStep*)(ewk->wu.step_xy_table + ewk->wu.dir_step))->color;
        }
        if (ewk->wu.vital_old & 1) {
            mwk->wu.extra_col = ewk->wu.vital_new;
        } else {
            mwk->wu.extra_col_2 = ewk->wu.vital_new;
        }
        break;
    case R0_KILL:
    default:
        if (ewk->wu.vital_old & 1) {
            mwk->wu.extra_col = 0;
        } else {
            mwk->wu.extra_col_2 = 0;
        }
        push_effect_work(&ewk->wu);
        return;
    }
}



s32 effect_D9_init(wk, data)
PLW* wk;
u8 data;
{
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 139;
    ewk->wu.work_id = 16;
    ewk->wu.direction = data;
    ewk->wu.dir_old = wk->wu.dm_count_up;
    ewk->wu.dm_attribute = wk->wu.dm_attribute;
    ewk->wu.type = wk->wu.pat_status;
    ewk->my_master = (u32*)wk;
    ewk->master_id = wk->wu.id;
    ewk->master_work_id = wk->wu.work_id;
    ewk->master_player = wk->player_number;
    return 0;
}
