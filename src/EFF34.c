/*
 * EFF34.C  Effect 34: flying object generator
 *
 * effect_34_init (from bgst030's stage) creates the controller. On its first frame effect_34_move
 * launches two groups of effect 35 objects, a random number of types from a random row of
 * eff34_first_tbl and of eff34_second_tbl. After that, each time a random wait from eff34_wait_tbl
 * runs out, it launches one more object of each kind while fewer than 16 of the first kind and 8 of
 * the second are flying (30 and 15 once Conclusion_Flag is set); the effect 35 objects count
 * themselves in the controller's direction and dir_old. It pauses during EXE_flag / Game_pause, while
 * the alternate background is up (seraph_flag) and, below priority 70, during the finish screen
 * (akebono_flag).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "ta_sub.h"
extern const s16 eff34_first_tbl[56];
extern const s16 eff34_second_tbl[56];
extern const s16 eff34_wait_tbl[32];
s32 effect_35_init(WORK_Other* ewk, s16 type);

#define GROUP_WORK(value) ((WORK*)(value))

s32 effect_34_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 34;
    ewk->wu.work_id = 16;
    ewk->wu.direction = 0;
    ewk->wu.dir_step = 0;
    ewk->wu.dir_old = 0;
    ewk->wu.dir_timer = 0;
    return 0;
}

void effect_34_move(WORK_Other* ewk) {
    s8 num;
    s8 rnd;
    s16 i;
    const s16* data;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[1] = 0;
        ewk->wu.routine_no[2] = 0;
        ewk->wu.routine_no[3] = 0;
        ewk->wu.routine_no[0]++;
    case 1:
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
        case 0:
            num = random_32_com();
            num &= 7;
            if ((s8)num == 0) {
                num = 4;
            }
            rnd = random_32_com();
            rnd &= 7;
            data = eff34_first_tbl;
            i = 0;
            data += (s8)(rnd * 7);
            if (0) {}
            goto first_group;
            first_group:;
            for (; i < (s8)num; i++, data++) {
                effect_35_init(ewk, *data);
                if (0) {}
            }
            (void)GROUP_WORK(num)->id;
            rnd = random_32_com();
            ewk->wu.vitality = eff34_wait_tbl[rnd];
            num = random_32_com();
            num &= 7;
            if ((s8)num == 0) {
                num = 3;
            }
            rnd = random_32_com();
            rnd &= 7;
            data = eff34_second_tbl;
            i = 0;
            data += (s8)(rnd * 7);
            if (0) {}
            goto second_group;
            second_group:;
            for (; i < (s8)num; i++, data++) {
                effect_35_init(ewk, *data);
                if (0) {}
            }
            (void)GROUP_WORK(eff34_wait_tbl)->id;
            (void)GROUP_WORK(0)->be_flag;
            rnd = random_32_com();
            ewk->wu.vital_new = eff34_wait_tbl[rnd];
            ewk->wu.routine_no[1]++;
            break;
        case 1:
            if (Conclusion_Flag) {
                ewk->wu.dir_step = 30;
                ewk->wu.dir_timer = 15;
            } else {
                ewk->wu.dir_step = 16;
                ewk->wu.dir_timer = 8;
            }
            switch (ewk->wu.routine_no[2]) {
            case 0:
                if (ewk->wu.vitality == 0) {
                    ewk->wu.routine_no[2]++;
                } else {
                    ewk->wu.vitality--;
                }
                break;
            case 1:
                if (ewk->wu.direction < ewk->wu.dir_step) {
                    num = random_32_com();
                    num &= 15;
                    if ((s8)num > 10) {
                        num -= 10;
                    }
                    effect_35_init(ewk, (s8)num);
                    rnd = random_32_com();
                    ewk->wu.vitality = eff34_wait_tbl[rnd];
                    ewk->wu.routine_no[2]--;
                }
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
                if (ewk->wu.dir_old < ewk->wu.dir_timer) {
                    num = random_32_com();
                    num &= 15;
                    if ((s8)num > 10) {
                        num -= 10;
                    }
                    num += 11;
                    effect_35_init(ewk, (s8)num);
                    rnd = random_32_com();
                    ewk->wu.vital_new = eff34_wait_tbl[rnd];
                    ewk->wu.routine_no[3]--;
                }
                break;
            }
        }
        break;
    case 2:
    default:
        goto effect_retire;
        effect_retire:;
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}
