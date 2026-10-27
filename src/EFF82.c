/*
 * EFF82.C  Effect 82: start of the stage character's scene after a perfect victory
 *
 * effect_82_init (from bgst110's stage) creates the controller and its effect 77 stage character with
 * its companions (effects 78, 79 and 80). In the first area, once a round has been decided
 * (Conclusion_Flag, C_No0 2 or more) with a perfect victory (Complete_Victory) over character 7,
 * effect_82_move goes to state 1 with the loser as master_id, which starts the companions' scene.
 */

#include "structs.h"
#include "work.h"
#include "extern.h"
#include "EFF82.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "fighter.h"

/* routine_no[0] */
#define R0_WAIT         0       /* wait for a perfect victory */
#define R0_SCENE        1       /* the companions play their scene */
#define R0_CLEAR        2       /* the companions free themselves */

s32 effect_77_init(WORK_Other* ewk);

void effect_82_move(WORK_Other* ewk) {
    if (bg_w.area || Allow_a_battle_f || Conclusion_Flag != 1 || C_No0 < 2) {
        return;
    }
    switch (ewk->wu.routine_no[0]) {
    case R0_WAIT:
        if (Conclusion_Flag && Complete_Victory != 0 && plw[Loser_id].player_number == PL_IBUKI) {
            ewk->wu.routine_no[0]++;
            ewk->master_id = Loser_id;
        }
        break;
    case R0_SCENE:
    case R0_CLEAR:
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

s32 effect_82_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 82;
    ewk->wu.work_id = 16;
    effect_77_init(ewk);
    return 0;
}
