/*
 * EFF24_TBL.C  breakable stage object records for effect 25
 *
 * scr_obj_data25_0 .. scr_obj_data25_4 are the records of five breakable objects: family,
 * colour, position, priority, animation, line-scroll sync, the behaviour settings and the type
 * of effect 26 part to add (-1 for none). Reached through scr_obj_data25 by object number in
 * EFF25.C, the bg130 breakable stage objects.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 scr_obj_data25_0[];
extern const s16 scr_obj_data25_1[];
extern const s16 scr_obj_data25_2[];
extern const s16 scr_obj_data25_3[];
extern const s16 scr_obj_data25_4[];

const s16 scr_obj_data25_0[16] = {
    0, 2, 8256, 512, 32, 81, 65, 0, 0, 0, 70, 72, 66, 7, 1, -1,
};

const s16 scr_obj_data25_1[16] = {
    0, 2, 8256, 527, 49, 84, 63, 0, 0, 1, 69, 73, 64, 7, 0, 0,
};

const s16 scr_obj_data25_2[16] = {
    1, 2, 8256, 751, 48, 90, 3, 0, 0, 2, 22, 74, 0, 3, 0, -1,
};

const s16 scr_obj_data25_3[16] = {
    1, 2, 8256, 224, 48, 74, 7, 0, 0, -1, 8, 24, 2, 2, 0, 1,
};

const s16 scr_obj_data25_4[16] = {
    0, 2, 64, 512, 16, 20, 9, 0, 0, -1, 10, 23, 23, 6, 1, -1,
};
