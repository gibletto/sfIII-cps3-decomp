/*
 * EFFG6.C  Effect G6: particle emitter that trails a moving work
 *
 * effect_G6_init (called from the damage code, PLPDM.c) attaches the emitter to
 * a work and records the work's state. effect_G6_move reads its entry in effg6_data (end flags,
 * life, offset, speed, blink mask, pattern) and, whenever the work has moved, spawns a G9
 * particle at the work's position plus the offset. It ends when the work lands, is hidden, is
 * hit again, changes state, stops moving or the life runs out, depending on the flags.
 * The particle itself is in EFFG9.C.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFG9.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFG6.h"

/* routine_no[0] */
#define R0_INIT         0       /* read the entry from effg6_data */
#define R0_MOVE         1       /* drop particles while the work moves */
#define R0_KILL         2       /* put the work back */

/* effg6_data columns */
#define G6_FLAGS        0       /* end conditions (bit flags) */
#define G6_LIFE         1       /* frames to live, with flag 0x10 */
#define G6_X            2       /* x offset from the work, mirrored by rl_flag */
#define G6_Y            3       /* y offset from the work */
#define G6_SPEED_X      4       /* particle x speed */
#define G6_SPEED_Y      5       /* particle y speed */
#define G6_RATE         6       /* emit mask (low byte), disp_flag (high byte) */
#define G6_PATTERN      7       /* particle pattern */



void effect_G6_move(WORK_Other* ewk) {
    WORK* mwk = (WORK*)ewk->my_master;
    s16* er;
    s16* mr;
    XY* mp;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.dmcal_m = effg6_data[ewk->wu.type][G6_FLAGS];
        ewk->wu.dir_timer = effg6_data[ewk->wu.type][G6_LIFE];
        ewk->wu.next_x = effg6_data[ewk->wu.type][G6_X];
        ewk->wu.next_y = effg6_data[ewk->wu.type][G6_Y];
        ewk->wu.mvxy.a[0].sp = effg6_data[ewk->wu.type][G6_SPEED_X];
        ewk->wu.mvxy.a[1].sp = effg6_data[ewk->wu.type][G6_SPEED_Y];
        ewk->wu.now_koc = effg6_data[ewk->wu.type][G6_RATE];
        ewk->wu.direction = effg6_data[ewk->wu.type][G6_PATTERN];
        if (ewk->wu.rl_flag) {
            ewk->wu.next_x = -ewk->wu.next_x;
        }
        ewk->wu.mvxy.a[0].sp *= 256;
        ewk->wu.mvxy.a[1].sp *= 256;
        ewk->wu.disp_flag = ewk->wu.now_koc / 256;
        ewk->wu.now_koc &= 0xFF;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if ((ewk->wu.dmcal_m & 1) && (ewk->wu.old_pos[1] != mwk->xyz[1].disp.pos)) {
            goto block_22;
        }
        if ((ewk->wu.dmcal_m & 2) && (!mwk->disp_flag)) {
            goto block_22;
        }
        if ((ewk->wu.dmcal_m & 4) && (ewk->wu.dm_vital != mwk->dm_count_up)) {
            goto block_22;
        }
        if (ewk->wu.dmcal_m & 8) {
            er = ewk->wu.old_rno;
            mr = mwk->routine_no;
            if ((er[0] != mr[0]) || (er[1] != mr[1]) || (er[2] != mr[2])) {
            block_22:
                ewk->wu.routine_no[0]++;
                break;
            }
        }
        if ((EXE_flag != 0) || (Game_pause != 0)) {
            break;
        }
        if (ewk->wu.dmcal_m & 0x10) {
            if (ewk->wu.dir_timer-- <= 0) {
                goto block_22;
            }
        }
        if (!((players_timer + ewk->wu.blink_timing) & ewk->wu.now_koc)) {
            if (ewk->wu.dmcal_m & 0x20) {
                if (!mwk->hit_stop) {
                    er = ewk->wu.old_pos;
                    mp = mwk->xyz;
                    if ((er[0] == mp[0].disp.pos) && (er[1] == mp[1].disp.pos)) {
                        goto block_22;
                    }
                }
            } else {
                er = ewk->wu.old_pos;
                mp = mwk->xyz;
                if ((er[0] == mp[0].disp.pos) && (er[1] == mp[1].disp.pos)) {
                    break;
                }
            }
            ewk->wu.old_pos[0] = mwk->xyz[0].disp.pos;
            ewk->wu.old_pos[1] = mwk->xyz[1].disp.pos;
            ewk->wu.xyz[0].disp.pos = ewk->wu.old_pos[0] + ewk->wu.next_x;
            ewk->wu.xyz[1].disp.pos = ewk->wu.old_pos[1] + ewk->wu.next_y;
            ewk->wu.position_z = mwk->position_z;
            effect_G9_init(&ewk->wu);
        }
        break;
    case R0_KILL:
    default:
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_G6_init(wk, dat)
WORK* wk;
u8 dat;
{
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 166;
    ewk->wu.work_id = 0x10;
    ewk->wu.type = dat;
    ewk->wu.rl_flag = wk->rl_flag;
    ewk->wu.my_family = 2;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2020;
    ewk->wu.old_pos[0] = ewk->wu.old_pos[1] = 0;
    ewk->wu.old_rno[0] = wk->routine_no[0];
    ewk->wu.old_rno[1] = wk->routine_no[1];
    ewk->wu.old_rno[2] = wk->routine_no[2];
    ewk->wu.dm_vital = wk->dm_count_up;
    ewk->my_master = (u32*)wk;
    ewk->master_work_id = wk->work_id;
    ewk->master_id = wk->id;
    ewk->wu.blink_timing = wk->blink_timing;
    return 0;
}
