/*
 * EFF04.C  Effect 04: falling stones controller
 *
 * effect_04_init starts the controller. effect_04_move first drops ten stones (effect 15) from a
 * row of eff04_stone_tbl picked at random, then keeps dropping one every eff04_wait_tbl frames
 * (picked at random) while fewer than 48 are down (direction counts them, dir_step holds the
 * limit). It ends when its work dies.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLS02.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"

/* routine_no[0] */
#define R0_INIT         0       /* clear the sub-states */
#define R0_MOVE         1       /* drop stones until the work dies */
#define R0_KILL         2       /* put the work back */

/* routine_no[1] */
#define R1_FIRST        0       /* drop the first ten stones */
#define R1_MORE         1       /* then one at a time */

/* routine_no[2] */
#define R2_WAIT         0       /* count the wait down */
#define R2_DROP         1       /* drop a stone while below the limit */


extern const s16 eff04_stone_tbl[56];   /* provisional name: rows of 7, ten read from a row */
extern const s16 eff04_wait_tbl[32];   /* provisional name */
s32 effect_15_init();



s32 effect_04_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 4;
    ewk->wu.work_id = 16;
    ewk->wu.direction = 0;
    ewk->wu.dir_step = 0;
    return 0;
}



void effect_04_move(WORK_Other* ewk) {
    const s16* data_ptr;
    s16 i;
    s8 num;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[1] = R1_FIRST;
        ewk->wu.routine_no[2] = R2_WAIT;
        ewk->wu.routine_no[3] = 0;
        ewk->wu.routine_no[0]++;
        /* fall through */
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag != 0 || Game_pause != 0) {
            break;
        }
        switch (ewk->wu.routine_no[1]) {
        case R1_FIRST:
            num = random_32_com();
            data_ptr = eff04_stone_tbl;
            for (i = 0, data_ptr += (num = (num & 7) * 7); i < 10; i++) {
                effect_15_init(&ewk->wu, *data_ptr);
                data_ptr++;
            }
            num = random_32_com();
            ewk->wu.vitality = eff04_wait_tbl[num];
            ewk->wu.routine_no[1]++;
            break;
        case R1_MORE:
            ewk->wu.dir_step = 48;
            switch (ewk->wu.routine_no[2]) {
            case R2_WAIT:
                if (ewk->wu.vitality == 0) {
                    ewk->wu.routine_no[2]++;
                } else {
                    ewk->wu.vitality--;
                }
                break;
            case R2_DROP:
                if (ewk->wu.direction < ewk->wu.dir_step) {
                    num = random_32_com();
                    num &= 15;
                    if (num > 10) {
                        num -= 10;
                    }
                    effect_15_init(&ewk->wu, num);
                    num = random_32_com();
                    ewk->wu.vitality = eff04_wait_tbl[num];
                    ewk->wu.routine_no[2]--;
                }
            }
        }
        break;
    case R0_KILL:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}
