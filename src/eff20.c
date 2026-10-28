/*
 * EFF20.C  Effect 20: flying object generator
 *
 * effect_20_init (from bgst110's stage) creates the controller. effect_20_move first launches one or
 * two effect 67 objects of each type; after 60 frames, and then after each random wait from
 * eff20_wait_tbl, it launches one more of type 0 while fewer than 7 are flying and one more of type 1
 * while fewer than 4 are. It pauses during EXE_flag / Game_pause, while the alternate background is up
 * (seraph_flag) and, below priority 70, during the finish screen (akebono_flag).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFF67.h"

/* routine_no[0] */
#define R0_INIT         0       /* clear the sub-states */
#define R0_MOVE         1       /* launch objects until the work dies */
#define R0_KILL         2       /* put the work back */

/* routine_no[1] */
#define R1_FIRST        0       /* launch the first objects of both types */
#define R1_MORE         1       /* then keep both types topped up */

/* routine_no[2] */
#define R2_WAIT         0       /* count the type 0 wait down */
#define R2_LAUNCH       1       /* launch a type 0 when fewer than 7 */

/* routine_no[3] */
#define R3_WAIT         0       /* count the type 1 wait down */
#define R3_LAUNCH       1       /* launch a type 1 when fewer than 4 */

extern const s16 eff20_wait_tbl[32];

s32 effect_20_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 20;
    ewk->wu.work_id = 16;
    ewk->wu.direction = 0;
    ewk->wu.dir_old = 0;
    return 0;
}

void effect_20_move(WORK_Other* ewk) {
    s8 num;
    s16 i;
    s16 j;
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[1] = R1_FIRST;
        ewk->wu.routine_no[2] = R2_WAIT;
        ewk->wu.routine_no[3] = R3_WAIT;
        ewk->wu.routine_no[0]++;
        /* fall through */
    case R0_MOVE:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag == 0 && Game_pause == 0) {
            if (seraph_flag) {
                break;
            }
        } else {
            break;
        }
        if (akebono_flag == 1 && ewk->wu.position_z <= 69) {
            break;
        }
        switch (ewk->wu.routine_no[1]) {
        case R1_FIRST:
            num = random_32_com();
            num &= 2;
            if (num == 0) {
                num = 1;
            }
            for (i = 0; i < num; i++) {
                effect_67_init(ewk, 0);
            }
            ewk->wu.vitality = 60;
            num = random_32_com();
            num &= 2;
            if (num == 0) {
                num = 1;
            }
            for (j = 0; j < num; j++) {
                effect_67_init(ewk, 1);
            }
            ewk->wu.vital_new = 60;
            ewk->wu.routine_no[1]++;
            break;
        case R1_MORE:
            switch (ewk->wu.routine_no[2]) {
            case R2_WAIT:
                if (ewk->wu.vitality == 0) {
                    ewk->wu.routine_no[2]++;
                } else {
                    ewk->wu.vitality--;
                }
                break;
            case R2_LAUNCH:
                if (ewk->wu.direction < 7) {
                    effect_67_init(ewk, 0);
                    num = random_32_com();
                    ewk->wu.vitality = eff20_wait_tbl[num];
                    ewk->wu.routine_no[2]--;
                }
                break;
            default:
                break;
            }
            switch (ewk->wu.routine_no[3]) {
            case R3_WAIT:
                if (ewk->wu.vital_new == 0) {
                    ewk->wu.routine_no[3]++;
                } else {
                    ewk->wu.vital_new--;
                }
                break;
            case R3_LAUNCH:
                if (ewk->wu.dir_old < 4) {
                    effect_67_init(ewk, 1);
                    num = random_32_com();
                    ewk->wu.vital_new = eff20_wait_tbl[num];
                    ewk->wu.routine_no[3]--;
                }
                break;
            default:
                break;
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

const s16 eff20_wait_tbl[32] = {
    18, 34, 48, 54, 60, 68, 80, 88,
    98, 104, 118, 124, 128, 138, 144, 154,
    158, 168, 174, 188, 200, 218, 224, 248,
    268, 288, 300, 328, 338, 460, 480, 600,
};
