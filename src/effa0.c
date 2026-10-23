/*
 * EFFA0.C  Effect A0: two rows of result marks
 *
 * effect_A0_init(family) (nothing calls it) starts the effect on a BG family. effect_A0_move puts out a
 * mark in each of two rows every other frame (effect 99 types 1 and 2, 32 dots apart, 160 and 128
 * above the family's BG position), twelve per row, and then frees itself. effA0_timer, effA0_count
 * and effA0_remaining hold each row's state.
 */

#include "structs.h"
#include "work.h"
#include "extern.h"
#include "EFFECT.h"
#include "effect_2.h"

extern s16 effA0_timer[3];
extern s16 effA0_count[3];
extern s16 effA0_remaining[3];
s32 effect_99_init();
void effA0_count_move();
void effA0_set_x();
void effA0_set_y();

void effect_A0_move(WORK_Other* ewk) {
    effA0_count_move(ewk, 1);
    effA0_count_move(ewk, 2);
    if (effA0_remaining[1] < 0 && effA0_remaining[2] < 0) {
        push_effect_work(&ewk->wu);
    }
}

void effA0_count_move(WORK_Other* ewk, s32 side) {
    if (effA0_remaining[(s16)side] >= 0) {
        if (--effA0_timer[(s16)side] == 0) {
            effA0_set_x(ewk, (s16)side);
            effA0_set_y(ewk, (s16)side);
            effect_99_init(side, ewk->wu.xyz[0].disp.pos, ewk->wu.xyz[1].disp.pos, ewk->wu.dir_timer);
            effA0_timer[(s16)side] = 2;
            effA0_remaining[(s16)side]--;
            effA0_count[(s16)side]++;
        }
    }
}

void effA0_set_x(WORK_Other* ewk, s16 side) {
    ewk->wu.xyz[0].disp.pos = bg_w.bgw[ewk->wu.dir_timer - 1].xy[0].disp.pos + effA0_count[side] * 32;
}

void effA0_set_y(WORK_Other* ewk, s16 side) {
    if (side == 2) {
        ewk->wu.xyz[1].disp.pos = bg_w.bgw[ewk->wu.dir_timer - 1].xy[1].disp.pos + 128;
    } else {
        ewk->wu.xyz[1].disp.pos = bg_w.bgw[ewk->wu.dir_timer - 1].xy[1].disp.pos + 160;
    }
}

s32 effect_A0_init(s16 family) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 100;
    ewk->wu.dir_timer = family;
    effA0_timer[1] = 1;
    effA0_timer[2] = 1;
    effA0_count[1] = 0;
    effA0_count[2] = 0;
    effA0_remaining[1] = 11;
    effA0_remaining[2] = 11;
    return 0;
}
