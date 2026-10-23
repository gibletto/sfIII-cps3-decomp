/*
 * PLPAT09.C  Player 09 (Oro) special attack routines
 *
 * Character-specific attack routines for player number 9, dispatched by pl09_extra_attack
 * through pl09_exatt_table.
 * set_tenguiwa (an effect-init routine) summons three rocks from the stage's set for the round
 * and places them from tenguiwa_pos_hosei.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLS02.h"
#include "PLSGAUGE.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFF13_KOTP.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLPAT.h"
#include "PLS01.h"
#include "PLPAT09.h"




void pl09_extra_attack(PLW* wk) {
    pl09_exatt_table[wk->wu.routine_no[2] - 16](wk);
}



void set_tenguiwa(PLW* wk, u8 data) {
    s16 i;
    s16 j;
    s16 num;
    const u8* tengu;
    WORK* tmw;
    tengu = tenguiwa_stand_by[tenguiwa_stage_data[bg_w.stage][Round_num & 3]];
    for (i = 0; i < 3; i++) {
        effect_13_init((WORK*)wk, tengu[random_16_com() & 7]);
    }
    for (j = 0, i = 0; i < 8; i++) {
        if (!get_my_shell_ix((WORK*)wk, i, &tmw)) {
            continue;
        }
        num = tmw->type - 24;
        if (!tenguiwa_type_flag[num]) {
            continue;
        }
        tmw->old_pos[0] = tenguiwa_pos_hosei[j][0];
        tmw->old_pos[1] = tenguiwa_pos_hosei[j][1];
        tmw->old_pos[2] = tenguiwa_pos_hosei[j][2];
        tmw->scr_mv_x = tenguiwa_pos_hosei[j][3];
        tmw->scr_mv_y = tenguiwa_pos_hosei[j][4];
        tmw->direction = tenguiwa_pos_hosei[j][5];
        j++;
        if (j > 2) {
            break;
        }
    }
}
