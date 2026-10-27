/*
 * EFF14.C  Background colour-cycle writer (effect 14)
 *
 * Animates part of a stage's scroll map by rewriting the palette bits of a rectangle of
 * map cells on a timed script, giving blinking lights and similar colour animation.
 * effect_14_init(id) allocates the work; effect_14_move loads the script, pattern mask and
 * target offset for that id from eff14_data_tbl/eff14_ofs_tbl, follows the scroll page
 * when it changes, and on each script step calls effect_14_write to patch the cell
 * attributes (pattern 1 = recolour, anything else leaves the cell). Scripts loop when they reach a -1 timer.
 * Started from the bgst030, bgst110 and bgst150 stage init routines.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "ta_sub.h"
#include "eff14.h"

/* routine_no[0] */
#define R0_INIT         0       /* load the script for this id */
#define R0_MOVE         1       /* step the script, follow the page */
#define R0_KILL         2       /* put the work back */

E14_WORK eff14_work[8];  /* 0205DF8C */


void effect_14_write(WORK_Other* ewk);



s32 effect_14_init(id, x, y, atr)
    s16 id;
    s16 x;
    s16 y;
    s16 atr;
{
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 14;
    ewk->wu.work_id = 16;
    ewk->wu.type = id;
    return 0;
}



void effect_14_move(WORK_Other* ewk) {
    u32* data;
    u16* ofs;
    s8 scr;
    s8 put;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        data = eff14_data_tbl[ewk->wu.type];
        scr = *data;
        data++;
        ewk->wu.rl_flag = *data;
        data++;
        eff14_work[ewk->wu.rl_flag].scr = scr;
        eff14_work[ewk->wu.rl_flag].adrs = ((E14_SCR*)scrn_map_ptr)[eff14_work[ewk->wu.rl_flag].scr].adrs;
        if (scrn_pos[eff14_work[ewk->wu.rl_flag].scr].cur_y.disp.pos < 0x200) {
            eff14_work[ewk->wu.rl_flag].adrs += 0x2000;
        }
        ofs = &eff14_ofs_tbl[ewk->wu.type];
        eff14_work[ewk->wu.rl_flag].dst = eff14_work[ewk->wu.rl_flag].adrs + *ofs;
        eff14_work[ewk->wu.rl_flag].row = eff14_work[ewk->wu.rl_flag].dst;
        eff14_work[ewk->wu.rl_flag].script_top = (s8*)*data;
        eff14_work[ewk->wu.rl_flag].script = (s8*)*data;
        data++;
        eff14_work[ewk->wu.rl_flag].pattern_top = *data;
        eff14_work[ewk->wu.rl_flag].pattern = (s8*)*data;
        data++;
        data = (u32*)*data;
        eff14_work[ewk->wu.rl_flag].cols = ((s8*)data)[0];
        eff14_work[ewk->wu.rl_flag].rows = ((s8*)data)[1];
        eff14_work[ewk->wu.rl_flag].timer = eff14_work[ewk->wu.rl_flag].script[1];
        eff14_work[ewk->wu.rl_flag].script += 2;
        eff14_work[ewk->wu.rl_flag].col = *(s16*)eff14_work[ewk->wu.rl_flag].script;
        eff14_work[ewk->wu.rl_flag].script += 2;
        ewk->wu.routine_no[0]++;
        break;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (seraph_flag) {
            break;
        }
        if ((akebono_flag == 1 && ewk->wu.position_z <= 69) || EXE_flag != 0 || Game_pause != 0) {
            break;
        }
        put = 0;
        if (eff14_work[ewk->wu.rl_flag].adrs != ((E14_SCR*)scrn_map_ptr)[eff14_work[ewk->wu.rl_flag].scr].adrs) {
            eff14_work[ewk->wu.rl_flag].adrs = ((E14_SCR*)scrn_map_ptr)[eff14_work[ewk->wu.rl_flag].scr].adrs;
            put = 1;
        }
        if (scrn_pos[eff14_work[ewk->wu.rl_flag].scr].cur_y.disp.pos < 0x200) {
            put = 1;
            eff14_work[ewk->wu.rl_flag].adrs += 0x2000;
        }
        ofs = &eff14_ofs_tbl[ewk->wu.type];
        eff14_work[ewk->wu.rl_flag].dst = eff14_work[ewk->wu.rl_flag].adrs + *ofs;
        eff14_work[ewk->wu.rl_flag].row = eff14_work[ewk->wu.rl_flag].dst;
        eff14_work[ewk->wu.rl_flag].timer--;
        if (eff14_work[ewk->wu.rl_flag].timer == 0) {
            eff14_work[ewk->wu.rl_flag].timer = eff14_work[ewk->wu.rl_flag].script[1];
            if (eff14_work[ewk->wu.rl_flag].timer == -1) {
                eff14_work[ewk->wu.rl_flag].script = eff14_work[ewk->wu.rl_flag].script_top;
                eff14_work[ewk->wu.rl_flag].timer = eff14_work[ewk->wu.rl_flag].script[1];
            }
            eff14_work[ewk->wu.rl_flag].script += 2;
            eff14_work[ewk->wu.rl_flag].col = *(s16*)eff14_work[ewk->wu.rl_flag].script;
            eff14_work[ewk->wu.rl_flag].script += 2;
            effect_14_write(ewk);
        } else if (put == 1) {
            effect_14_write(ewk);
        }
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* provisional name */
void effect_14_write(WORK_Other* ewk) {
    s16 i;
    s16 j;
    u16* dst;
    u16 v;
    i = 0;
    if (DEBUG_DISP) {
        *dst = 0xFE00;
    }
    for (; i < eff14_work[ewk->wu.rl_flag].rows; i = i + 1) {
        for (j = 0; j < eff14_work[ewk->wu.rl_flag].cols; j = j + 1) {
            if (*eff14_work[ewk->wu.rl_flag].pattern == 1) {
                eff14_work[ewk->wu.rl_flag].dst += 2;
                dst = (u16*)eff14_work[ewk->wu.rl_flag].dst;
                v = *dst & 0xFE00;
                v = v | eff14_work[ewk->wu.rl_flag].col;
                *dst = v;
                eff14_work[ewk->wu.rl_flag].dst += 2;
                eff14_work[ewk->wu.rl_flag].pattern++;
            } else {
                eff14_work[ewk->wu.rl_flag].dst += 2;
                eff14_work[ewk->wu.rl_flag].dst += 2;
                eff14_work[ewk->wu.rl_flag].pattern++;
            }
        }
        eff14_work[ewk->wu.rl_flag].dst = eff14_work[ewk->wu.rl_flag].row + 0x100;
        eff14_work[ewk->wu.rl_flag].row = eff14_work[ewk->wu.rl_flag].dst;
    }
    eff14_work[ewk->wu.rl_flag].pattern = (s8*)eff14_work[ewk->wu.rl_flag].pattern_top;
}
