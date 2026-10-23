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
s32 effect_67_init(WORK_Other* oya, s16 type);
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
    case 0:
        ewk->wu.routine_no[1] = 0;
        ewk->wu.routine_no[2] = 0;
        ewk->wu.routine_no[3] = 0;
        ewk->wu.routine_no[0]++;
        /* fall through */
    case 1:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0]++;
            break;
        }
        if (EXE_flag != 0) {
            break;
        }
        goto burst_pause;
    burst_pause:;
        if (Game_pause != 0) {
            break;
        }
        goto burst_seraph;
    burst_seraph:;
        if (seraph_flag) {
            break;
        }

        if (akebono_flag == 1 && ewk->wu.position_z <= 69) {
            break;
        }
        switch (ewk->wu.routine_no[1]) {
        case 0:
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
        case 1:
            switch (ewk->wu.routine_no[2]) {
            case 0:
                if (ewk->wu.vitality == 0) {
                    ewk->wu.routine_no[2]++;
                } else {
                    ewk->wu.vitality--;
                }
                break;
            case 1:
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
            case 0:
                if (ewk->wu.vital_new == 0) {
                    ewk->wu.routine_no[3]++;
                } else {
                    ewk->wu.vital_new--;
                }
                break;
            case 1:
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
    case 2:
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
