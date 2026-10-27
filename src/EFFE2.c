/*
 * EFFE2.C  Effect E2: flame, electric and ice pieces on a damaged player
 *
 * setup_accessories (called from PLPDM.c when a player is hit) spawns E2 pieces for the
 * damage attribute: four flame pieces for fire (1), one electric piece (2) or four ice pieces for
 * freeze (3), using the standing, crouching or airborne position tables for the character
 * (flames_stand / _crunch / _ariel, thunder_set_pos_SKB, freeze_stand / _crunch / _set_pos_B).
 * effect_E2_init places each piece relative to the given body box of the player, facing away
 * from the player (plef_char_table). effect_E2_move keeps it on the player
 * (effE2_sort_push) until its pattern ends, the player takes another hit, lands or
 * changes pattern; then it plays its fade-out part (effe2_erase_or_die) and frees itself.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFE2.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the pattern */
#define R0_MOVE         1       /* stay on the player */
#define R0_FADE         2       /* play the fade-out part */
#define R0_KILL         3       /* (default) put the work back */



void effect_E2_move(WORK_Other* ewk) {
    PLW* mwk = (PLW*)ewk->my_master;
    ewk->wu.hit_stop = mwk->wu.hit_stop;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.cg_wca_ix = 0;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        effE2_sort_push(&ewk->wu, &mwk->wu);
        break;
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0] = R0_KILL;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                if (ewk->wu.cg_type == 0xFF) {
                    ewk->wu.disp_flag = 0;
                    ewk->wu.routine_no[0] = R0_KILL;
                    break;
                } else if (ewk->wu.cg_type == 1) {
                    ewk->wu.routine_no[0] = R0_FADE;
                    sort_push_request8(&ewk->wu);
                    break;
                }
            }
        }
        if (ewk->wu.dir_old != mwk->wu.dm_count_up) {
            if (ewk->wu.dm_attribute == mwk->wu.dm_attribute) {
                ewk->wu.disp_flag = 0;
                ewk->wu.routine_no[0] = R0_KILL;
                break;
            }
            effe2_erase_or_die(&ewk->wu);
            break;
        }
        if (ewk->wu.type != 0 && ewk->wu.type != 32) {
            if (mwk->wu.xyz[1].disp.pos <= 0) {
                effe2_erase_or_die(&ewk->wu);
                break;
            }
        } else if (mwk->wu.cg_type != 0) {
            effe2_erase_or_die(&ewk->wu);
            break;
        }
        effE2_sort_push(&ewk->wu, &mwk->wu);
        break;
    case R0_FADE:
        if (EXE_flag == 0 && Game_pause == 0) {
            char_move(&ewk->wu);
            if (ewk->wu.cg_type) {
                if (ewk->wu.cg_type == 0xFF) {
                    ewk->wu.disp_flag = 0;
                    ewk->wu.routine_no[0] = R0_KILL;
                    break;
                }
            }
        }
        sort_push_request8(&ewk->wu);
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* provisional name */
void effE2_sort_push(WORK* ewk, WORK* mwk) {
    if (ewk->rl_flag) {
        ewk->position_x = mwk->xyz[0].disp.pos + ewk->old_pos[0];
    } else {
        ewk->position_x = mwk->xyz[0].disp.pos - ewk->old_pos[0];
    }
    ewk->position_y = mwk->xyz[1].disp.pos + ewk->old_pos[1];
    ewk->position_z = mwk->xyz[2].disp.pos + ewk->old_pos[2];
    ewk->xyz[0].disp.pos = ewk->position_x;
    ewk->xyz[1].disp.pos = ewk->position_y;
    ewk->xyz[2].disp.pos = ewk->position_z;
    sort_push_request8(ewk);
}



/* provisional name */
void effe2_erase_or_die(WORK* wk) {
    if (wk->cg_wca_ix != 0) {
        wk->routine_no[0] = R0_FADE;
        char_move_wca(wk);
        sort_push_request8(wk);
    } else {
        wk->disp_flag = 0;
        wk->routine_no[0] = R0_KILL;
    }
}



s32 effect_E2_init(PLW* wk, const s16* data, u8 ff) {
    WORK_Other* ewk;
    s16* bxt;
    s16 ix;
    if (data[3] == 0) {
        return -1;
    }
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 142;
    ewk->wu.work_id = 16;
    if (wk->wu.rl_flag) {
        ewk->wu.rl_flag = 0;
    } else {
        ewk->wu.rl_flag = 1;
    }
    ewk->wu.dir_old = wk->wu.dm_count_up;
    ewk->wu.dm_attribute = wk->wu.dm_attribute;
    ewk->wu.type = wk->wu.pat_status;
    ewk->wu.blink_timing = wk->wu.blink_timing;
    ewk->wu.old_pos[2] = 1;
    ewk->wu.char_index = data[3];
    ewk->my_master = (u32*)wk;
    ewk->wu.target_adrs = (u32*)wk;
    ewk->master_id = wk->wu.id;
    ewk->master_work_id = wk->wu.work_id;
    ewk->master_player = wk->player_number;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_mode = 0x2020;   /* the second store stands; my_col_code is left alone */
    ewk->wu.my_family = 2;
    ewk->wu.my_mr_flag = 0;
    *ewk->wu.char_table = plef_char_table;
    bxt = wk->wu.h_bod->body_dm[data[0]];
    ewk->wu.old_pos[0] = bxt[0] + (bxt[1] >> 1) + data[1];
    ewk->wu.old_pos[1] = bxt[2] + (bxt[3] >> 1) + data[2];
    ewk->wu.charset_id = 0;
    if (ff) {
        if (ewk->wu.char_index & 1) {
            ewk->wu.charset_id = 4;
        } else {
            ewk->wu.charset_id = 5;
        }
    }
    return 0;
}



s32 setup_accessories(wk, data)
PLW* wk;
u8 data;
{
    s16 i;
    switch (data) {
    case 0:
        if (wk->wu.dm_attribute == 1) {
            for (i = 0; i < 4; i++) {
                effect_E2_init(wk, flames_stand[wk->player_number][i], 1);
            }
        }
        if (wk->wu.dm_attribute == 2) {
            effect_E2_init(wk, thunder_set_pos_SKB[wk->player_number], 0);
        }
        if (wk->wu.dm_attribute == 3) {
            for (i = 0; i < 4; i++) {
                effect_E2_init(wk, freeze_stand[wk->player_number][i], 0);
            }
        }
        break;
    case 32:
        if (wk->wu.dm_attribute == 1) {
            for (i = 0; i < 4; i++) {
                effect_E2_init(wk, flames_crunch[wk->player_number][i], 1);
            }
        }
        if (wk->wu.dm_attribute == 2) {
            effect_E2_init(wk, thunder_set_pos_SKB[wk->player_number], 0);
        }
        if (wk->wu.dm_attribute == 3) {
            for (i = 0; i < 4; i++) {
                effect_E2_init(wk, freeze_crunch[wk->player_number][i], 0);
            }
        }
        break;
    default:
        if (wk->wu.dm_attribute == 1) {
            for (i = 0; i < 4; i++) {
                effect_E2_init(wk, flames_ariel[wk->player_number][i], 1);
            }
        }
        if (wk->wu.dm_attribute == 2) {
            effect_E2_init(wk, thunder_set_pos_SKB[wk->player_number], 0);
        }
        if (wk->wu.dm_attribute == 3) {
            for (i = 0; i < 4; i++) {
                effect_E2_init(wk, freeze_set_pos_B[wk->player_number][i], 0);
            }
        }
        break;
    }
}
