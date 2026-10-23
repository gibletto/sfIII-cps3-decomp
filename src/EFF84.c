/*
 * EFF84.C  Effect 84: centre-screen message controller
 *
 * effect_84_init (from manage_2.c) creates the controller. When request_message is set, effect_84_move
 * draws message message_index on the text layer (bcount_mark_trans) with effect 89 over it, pausing
 * the game for messages 0-2. After the time in Time_Data for the request it clears the message area,
 * requests the dead voice, clears request_message and resumes play.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sc_clear.h"
#include "eff89.h"
#include "PLSGAUGE.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFF84.h"

void bcount_mark_trans(u8 ix);

void effect_84_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        if (request_message) {
            ewk->wu.routine_no[0]++;
            ewk->wu.dir_timer = Time_Data[request_message];
        }
        break;
    case 1:
        switch (ewk->wu.routine_no[1]) {
        case 0:
            switch (message_index) {
            case 0:
                Game_pause = -1;
                bcount_mark_trans(0);
                effect_89_init(0, DE_X[3] + 14, 9, 18, 6);
                break;
            case 1:
                Game_pause = -1;
                bcount_mark_trans(1);
                effect_89_init(1, DE_X[3] + 12, 9, 24, 4);
                break;
            case 2:
                Game_pause = -1;
                bcount_mark_trans(2);
                effect_89_init(3, DE_X[3] + 12, 9, 24, 4);
                break;
            case 3:
                bcount_mark_trans(3);
                effect_89_init(3, DE_X[3] + 12, 9, 24, 4);
                break;
            case 4:
            default:
                bcount_mark_trans(4);
                effect_89_init(1, DE_X[3] + 12, 9, 24, 4);
                break;
            }
            ewk->wu.routine_no[1]++;
            break;
        case 1:
            if (--ewk->wu.dir_timer == 0) {
                tilemap_clear_rect(DE_X[3] + 11, 9, DE_X[3] + 36, 16);
                dead_voice_request();
                request_message = 0;
                Game_pause = 0;
                ewk->wu.routine_no[0] = ewk->wu.routine_no[1] = 0;
            }
            break;
        }
        break;
    case 2:
        break;
    default:
        break;
    }
}

s32 effect_84_init(void) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 84;
    return 0;
}
