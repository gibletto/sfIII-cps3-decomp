/*
 * EFF87_TBL.C  stage background object tables for effect 87
 *
 * eff87_loop_tbl gives the number of objects to make per type and compel flag, and
 * scr_obj_data87_0 the object rows (dead flag, family, colour, x, y, priority, animation, hit
 * stop, line-scroll sync), reached through scr_obj_data87 in EFF87.C. Read by EFF87.C, the
 * stage background object.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff87_loop_tbl[][4];
extern const s16 scr_obj_data87_0[];
extern const s16 scr_obj_data87_1_0[];
extern const s16 scr_obj_data87_1_1[];
extern const s16 scr_obj_data87_1_2[];
extern const s16 scr_obj_data87_1_3[];
extern const s16 scr_obj_data87_2_0[];
extern const s16 scr_obj_data87_3_0[];
extern const s16 scr_obj_data87_4_0[];

const s16 eff87_loop_tbl[5][4] = {
    { 0, 0, 0, 0 }, { 0, 1, 1, 3 }, { 1, 1, 1, 1 }, { 1, 1, 0, 0 },
    { 2, 2, 2, 0 },
};

/* type/compel flag 0/0, 0/1, 0/2, 0/3 with no objects; provisional name */
const s16 scr_obj_data87_0[9] = {
    0, 2, 8256, -96, 96, 82, 10, 0, 1,
};

/* type/compel flag 1/0 with no objects; provisional name */
const s16 scr_obj_data87_1_0[1] = {
    0,
};

/* type/compel flag 1/1; provisional name */
const s16 scr_obj_data87_1_1[9] = {
    0, 2, 8256, 512, 64, 79, 5, 1, 0,
};

/* type/compel flag 1/2; provisional name */
const s16 scr_obj_data87_1_2[9] = {
    0, 2, 8256, 512, 64, 79, 5, 1, 0,
};

/* type/compel flag 1/3; provisional name */
const s16 scr_obj_data87_1_3[27] = {
    1, 2, 8280, 496, 96, 90, 17, 0, 0,
    1, 2, 8280, 512, 96, 79, 16, 0, 0,
    0, 2, 64, 528, 64, 92, 6, 1, 0,
};

/* type/compel flag 2/0, 2/1, 2/2, 2/3; provisional name */
const s16 scr_obj_data87_2_0[9] = {
    1, 2, 8277, 416, 72, 80, 28, 0, 0,
};

/* type/compel flag 3/0, 3/1; 3/2, 3/3 with no objects; provisional name */
const s16 scr_obj_data87_3_0[9] = {
    0, 2, 8292, 0, 56, 74, 0, 1, 1,
};

/* type/compel flag 4/0, 4/1, 4/2; 4/3 with no objects; provisional name */
const s16 scr_obj_data87_4_0[19] = {
    1, 2, 8288, 389, 183, 81, 7, 0, 0,
    1, 2, 8288, 704, 49, 81, 15, 1, 0,
    0,
};
