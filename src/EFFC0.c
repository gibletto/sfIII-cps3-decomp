/*
 * EFFC0.C  Effect C0: animation attached to a player in damage state 25
 *
 * effect_C0_init creates the effect on a player (plef_char_table). effect_C0_move shows the
 * pattern given for the player's character in plhos_data and keeps it at the offset from the
 * same table, a little in front of the player, only while the player stays in damage routine 25
 * (Damage_25000 in PLPDM.c, where lever/button mashing (cp->lgp) shortens the timer). Its
 * animation is stepped extra times per frame by hok_table_ef, so it runs faster the harder the
 * player mashes. It hides and frees itself when the player leaves that state or on Suicide.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFC0.h"

/* routine_no[0] */
#define R0_INIT         0       /* start the pattern */
#define R0_MOVE         1       /* stay on the player while held */
#define R0_KILL         2       /* put the work back */

/* plhos_data columns */
#define PLHOS_X         0       /* x offset in front of the player */
#define PLHOS_Y         1       /* y offset from the player */
#define PLHOS_CHAR      2       /* animation number */



void effect_C0_move(WORK_Other* ewk) {
    PLW* mwk = (PLW*)ewk->my_master;
    s16 i;
    s16 hok;

    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2020;
        set_char_move_init(&ewk->wu, 0, plhos_data[mwk->player_number][PLHOS_CHAR]);
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 1;
            break;
        }
        {
            s16* r = mwk->wu.routine_no;
            if (r[1] != PLAYER_DAMAGE || r[2] != 25) {
                ewk->wu.routine_no[0]++;
                ewk->wu.disp_flag = 1;
                break;
            }
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            i = 0;
            if (mwk->cp->lgp > 13) {
                hok = 3;
            } else {
                hok = hok_table_ef[mwk->cp->lgp / 2];
            }
            for (; i < hok; i++) {
                char_move(&ewk->wu);
            }
        }
        ewk->wu.position_x = mwk->wu.position_x;
        if (mwk->wu.rl_flag) {
            ewk->wu.position_x += plhos_data[mwk->player_number][PLHOS_X];
        } else {
            ewk->wu.position_x -= plhos_data[mwk->player_number][PLHOS_X];
        }
        ewk->wu.position_y = mwk->wu.position_y + plhos_data[mwk->player_number][PLHOS_Y];
        ewk->wu.position_z = mwk->wu.position_z - 4;
        sort_push_request(&ewk->wu);
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
    }
}



s32 effect_C0_init(PLW* wk, s32 _p1) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 120;
    ewk->wu.work_id = 16;
    ewk->wu.my_family = wk->wu.my_family;
    ewk->wu.cgromtype = 1;
    ewk->wu.position_x = wk->wu.position_x;
    ewk->wu.position_y = wk->wu.position_y;
    ewk->wu.position_z = wk->wu.position_z - 4;
    ewk->my_master = (u32*)wk;
    ewk->master_work_id = wk->wu.work_id;
    ewk->master_id = wk->wu.id;
    *ewk->wu.char_table = plef_char_table;
    return 0;
}
